<?php
/**
 * @copyright 2006-2009 City of Bloomington, Indiana
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param GET document_id
 * @param POST document_id
 * @param array $navigation
 *
 * Documents in the system that have forms should post to themselves.
 * Forms must include document_id as a hidden field.
 * Documents that include forms are expected to have the PHP code
 * inside themselves to process their own POST
 */
$format = isset($_GET['format']) ? strtolower($_GET['format']) : 'html';
switch($format) {
	case 'print':
		$template = new Template('print','html');
		break;
	case 'contentonly':
		$template = new Template('contentonly','html');
		break;
	default:
		$template = new Template();
}

try {
	if (isset($_GET['document_id']) && $_GET['document_id']) {
		$document = new Document($_GET['document_id']);
	}
	elseif (isset($_POST['document_id']) && $_POST['document_id']) {
		$document = new Document($_POST['document_id']);
	}
	else {
		$document = new Document(1);
	}
}
catch (Exception $e) {
	header('http/1.1 404 Not Found');
	header('Status: 404 Not Found');
	$template->blocks[] = new Block('errorMessages/404.inc');
	$template->blocks[] = new Block('search/searchForm.inc');
}

if (isset($document)) {
	if ($document->getId()==1) { $template->setFilename('homepage'); }

	$document->logAccess();

	$template->document = $document;
	$template->title = $document->getTitle();

	#------------------------------------------------------------
	# Set up the BreadCrumbs
	#------------------------------------------------------------
	$p = isset($_SESSION['previousSectionId']) ? $_SESSION['previousSectionId'] : null;
	if (isset($_GET['section_id'])) {
		$s = $_GET['section_id'];
		$_SESSION['previousSectionId'] = $s;
	}
	else {
		$s = null;
	}
	$currentAncestors = $document->getBreadcrumbs($s,$p);
	$template->currentAncestors = $currentAncestors;

	# Don't display the breadcrumbs on the homepage
	if ($document->getId() != 1) {
		$breadcrumbs = new Block('documents/breadcrumbs.inc');
		$breadcrumbs->document = $document;
		$breadcrumbs->currentAncestors = $currentAncestors;
		$template->blocks[] = $breadcrumbs;
	}

	# The current section should be pulled from the URL
	# If there isn't one in the URL, try pulling it from $currentAncestors
	if (isset($_GET['section_id'])) {
		try {
			$currentSection = new Section($_GET['section_id']);
		}
		catch(Exception $e)
		{
			if (count($currentAncestors)) {
				$currentSection = end($currentAncestors);
			}
		}
	}
	elseif(count($currentAncestors)) {
		$currentSection = end($currentAncestors);
	}

	#------------------------------------------------------------
	# Create the panel for alerts
	#------------------------------------------------------------
	$template->blocks[] = new Block('alerts/alertPanel.inc',array('document'=>$document));


	#------------------------------------------------------------
	# Set up the content of the document
	#------------------------------------------------------------
	$viewDocument = new Block('documents/viewDocument.inc');
	$viewDocument->document = $document;
	if (isset($currentSection)) {
		$viewDocument->section = $currentSection;
	}

	if (!$document->isActive()) {
		$template->blocks[] = new Block('documents/unavailable.inc',array('document'=>$document));

		if (isset($_SESSION['USER']) && $document->permitsEditingBy($_SESSION['USER'])) {
			$template->blocks[] = $viewDocument;
		}
		else {
			/*
			try {
				$search = new Search();
				$results = $search->find($document->getTitle());
			}
			catch (Exception $e) {
				exception_handler($e);
			}

			$currentType = isset($_GET['type']) ? Inflector::pluralize($_GET['type']) : 'Documents';

			if (isset($results[$currentType]) && count($results[$currentType])) {
				# If we've got a lot of results, split them up into seperate pages
				if ($results[$currentType] > 10) {
					$resultArray = new ArrayObject($results[$currentType]);
					$pages = new Paginator($resultArray,10);

					# Make sure we're asking for a page that actually exists
					$page = (isset($_GET['page']) && $_GET['page']) ? (int)$_GET['page'] : 0;
					if (!$pages->offsetExists($page)) {
						$page = 0;
					}

					$resultsList = new LimitIterator($resultArray->getIterator(),
													$pages[$page],
													$pages->getPageSize());
				}
				else {
					$resultsList = $this->results[$currentType];
				}
			}
			else {
				$resultsList = array();
			}

			if (isset($results)) {
				$type = strtolower($currentType);

				$resultsTab = new Block('search/resultTabs.inc');
				$resultsTab->currentType = $currentType;
				$resultsTab->type = $type;
				$resultsTab->results = $results;

				$resultBlock = new Block('search/results.inc');
				$resultBlock->results = $resultsList;
				$resultBlock->currentType = $currentType;
				$resultBlock->type = $type;

				$template->blocks[] = $resultsTab;
				$template->blocks[] = $resultBlock;

				if (isset($pages)) {
					$pageNavigation = new Block('pageNavigation.inc');
					$pageNavigation->page = $page;
					$pageNavigation->pages = $pages;
					$pageNavigation->url = new URL($_SERVER['SERVER_NAME'].$_SERVER['REQUEST_URI']);

					$template->blocks[] = $pageNavigation;
				}
			}
			*/
		}
	}
	else {
		$template->blocks[] = $viewDocument;
	}


	# If we're viewing the homepage of the current section
	foreach ($document->getHomeSections() as $section) {
		# Check for Featured Documents in this Section
		$types = new DocumentTypeList();
		$types->find();
		foreach ($types as $type) {
			$documentList = new DocumentList(array('documentType_id'=>$type->getId(),
												'section_id'=>$section->getId(),
												'featured'=>1,
												'active'=>date('Y-m-d')));
			if (count($documentList)) {
				$featuredDocuments = new Block('sections/featuredDocuments.inc');
				$featuredDocuments->documentType = $type;
				$featuredDocuments->documentList = $documentList;
				$featuredDocuments->section = $section;

				$template->blocks[] = $featuredDocuments;
			}
		}

		$template->section = $section;
	}
}
echo $template->render();
