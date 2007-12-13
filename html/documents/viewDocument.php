<?php
/**
 * @copyright Copyright (C) 2006,2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
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
	$template = new Template();

	try
	{
		if (isset($_GET['document_id'])) { $document = new Document($_GET['document_id']); }
		if (isset($_POST['document_id'])) { $document = new Document($_POST['document_id']); }
	}
	catch (Exception $e) { $_SESSION['errorMessages'][] = $e; }

	if (isset($document))
	{
		$template->document = $document;
		$template->title = $document->getTitle();

		#------------------------------------------------------------
		# Set up the breadcrumbs
		#------------------------------------------------------------
		$ancestors = array();
		foreach($document->getSections() as $parent)
		{
			$temp = $parent->getAncestors();
			foreach($temp as $i=>$vector) { $temp[$i][$parent->getId()] = $parent; }

			$ancestors = array_merge($ancestors,$temp);
		}

		if (count($ancestors))
		{
			if (isset($_SESSION['previousSectionId']))
			{
				# Choose the current ancestral line by looking at the last section
				# of each ancestral line
				foreach($ancestors as $i=>$vector)
				{
					$test = end($vector);
					if ($test->getId()==$_SESSION['previousSectionId'])
					{
						# This is the current ancestral line
						$currentAncestors = $test;
					}
				}
			}
			else
			{
				# We don't have a previous section to compare
				# Use the shortest vector in ancestors as the current
				$shortest = 0;
				foreach($ancestors as $i=>$vector)
				{
					if ($shortest)
					{
						if (count($vector) < count($ancestors[$shortest]))
						{
							$shortest = $i;
						}
					}
				}

				$currentAncestors = $ancestors[$shortest];
			}
		}
		else { $currentAncestors = array(); }


		$breadcrumbs = new Block('documents/breadcrumbs.inc');
		$breadcrumbs->document = $document;
		$breadcrumbs->currentAncestors = $currentAncestors;
		$template->blocks[] = $breadcrumbs;

		if (!$document->isActive())
		{
			#$_SESSION['errorMessages'][] = new Exception('documents/unavailable');
			$template->blocks[] = new Block('documents/unavailable.inc',array('document'=>$document));

			if (isset($_SESSION['USER']) && $document->permitsEditingBy($_SESSION['USER']))
			{
				$template->blocks[] = new Block('documents/viewDocument.inc',array('document'=>$document));
			}
			else
			{
				try
				{
					$search = new Search();
					$results = $search->find($document->getTitle());
				}
				catch (Exception $e) { exception_handler($e); }


				$currentType = isset($_GET['type']) ? Inflector::pluralize($_GET['type']) : 'Documents';
				$type = strtolower($currentType);


				if (isset($results[$type]) && count($results[$type]))
				{
					# If we've got a lot of results, split them up into seperate pages
					if ($results[$type] > 10)
					{
						$resultArray = new ArrayObject($results[$type]);
						$pages = new Paginator($resultArray,10);

						# Make sure we're asking for a page that actually exists
						$page = (isset($_GET['page']) && $_GET['page']) ? (int)$_GET['page'] : 0;
						if (!$pages->offsetExists($page)) { $page = 0; }

						$resultsList = new LimitIterator($resultArray->getIterator(),$pages[$page],$pages->getPageSize());
					}
					else { $resultsList = $this->results[$type]; }
				}
				else { $resultList = array(); }
				if (isset($results))
				{
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

					if (isset($pages))
					{
						$pageNavigation = new Block('pageNavigation.inc');
						$pageNavigation->page = $page;
						$pageNavigation->pages = $pages;
						$pageNavigation->url = new URL("$_SERVER[SERVER_NAME]$_SERVER[REQUEST_URI]");

						$template->blocks[] = $pageNavigation;
					}
				}
			}
		}
		else
		{
			$template->blocks[] = new Block('documents/viewDocument.inc',array('document'=>$document));
		}


		# If we don't have a specific section we're in yet,
		# choose one of the sections for this Document.
		$sections = $document->getSections();
		if (!isset($section))
		{
			# The section list returned will not be zero based.  To get the
			# first element, you have to call current()
			$section = count($sections) ? current($sections) : null;
		}

		foreach($sections as $s)
		{
			# Find out which Sections this Document is a homepage of
			if ($s->getDocument_id() === $document->getId())
			{
				$template->blocks[] = new Block('sections/subsections.inc',array('section'=>$s));

				# Check for Featured Documents in this Section
				$types = new DocumentTypeList();
				$types->find();
				foreach($types as $type)
				{
					$documentList = new DocumentList(array('documentType_id'=>$type->getId(),'section_id'=>$s->getId(),'featured'=>1,'active'=>date('Y-m-d')));
					if (count($documentList))
					{
						$featuredDocuments = new Block('sections/featuredDocuments.inc');
						$featuredDocuments->documentType = $type;
						$featuredDocuments->documentList = $documentList;
						$featuredDocuments->section = $s;

						$template->blocks[] = $featuredDocuments;
					}
				}

				$template->blocks[] = new Block('sections/documents.inc',array('section'=>$s,'document'=>$document));
			}
		}
	}

	$template->render();
