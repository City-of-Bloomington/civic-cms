<?php
/**
 * @copyright Copyright (C) 2006,2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param GET documentType_id
 * @param GET section_id (Optionally include a section to pre-select)
 */
	# Make sure they're allowed to edit stuff in this section
	verifyUser(array('Administrator','Webmaster','Content Creator'));
	if (isset($_GET['section_id']))
	{
		$section = new Section($_GET['section_id']);
		if (!$section->permitsEditingBy($_SESSION['USER'])) { unset($section); }
	}

	# Set the current language we're working with
	$language = isset($_REQUEST['lang']) ? new Language($_REQUEST['lang']) : new Language($_SESSION['LANGUAGE']);

	# If they pass a documentType_id in the URL, start a new Add Document process
	if (isset($_GET['documentType_id']))
	{
		$type = new DocumentType($_GET['documentType_id']);
		$_SESSION['document'] = new Document();
		if (isset($section)) { $_SESSION['document']->addSection($section); }
		$_SESSION['document']->setDocumentType($type,$_SESSION['LANGUAGE']);
	}




	# Handle any document data that's been posted
	if (isset($_POST['document']))
	{
		foreach($_POST['document'] as $field=>$value)
		{
			$set = "set".ucfirst($field);
			$_SESSION['document']->$set($value);
		}
	}
	# Content has to be handled specially
	$languageList = new LanguageList();
	$languageList->find();
	foreach($languageList as $l)
	{
		$contentField = "content_{$l->getCode()}";
		if (isset($_POST[$contentField]))
		{
			if ($_POST[$contentField])
			{
				$_SESSION['document']->setContent($_POST[$contentField],$l->getCode());
			}
			else
			{
				$_SESSION['errorMessages'][] = new Exception('documents/missingContent');
				$_REQUEST['tab'] = 'content';
			}
		}
	}

	/*
	 Attachments cannot be created until we have a document_id.
	 Which means we cannot do attachments until we've saved the document.
	 Attachments cannot be done while adding a document, only when updating.
	*/
	# Raw source code handling
	if (isset($_FILES['source']) && $_FILES['source']['name'])
	{
		# Make sure they're allowed to edit the raw source code
		if (userHasRole('Webmaster'))
		{
			$_SESSION['document']->setContent(file_get_contents($_FILES['source']['tmp_name']),$_POST['lang']);
		}
	}
	# Save the document only when they ask for it
	if (isset($_POST['action']) && $_POST['action']=='save')
	{
		try
		{
			$_SESSION['document']->save();
			unset($_SESSION['document']);
			$template = new Template('closePopup');
			$template->render();
			exit();
		}
		catch (Exception $e) { $_SESSION['errorMessages'][] = $e; }
	}




	/*
		Since we cannot do attachments while adding a document, we need to use a
		different set of tabs.  However, we can still use the same form blocks
		used when updating documents.  Just make sure to not handle attachments.
	*/
	# Figure out which tab we're supposed to show
	$tab = isset($_REQUEST['tab']) ? $_REQUEST['tab'] : 'info';
	$template = new Template('popup');
	$template->blocks[] = new Block('documents/add/tabs.inc');

	$form = new Block("documents/update/$tab.inc",array('document'=>$_SESSION['document']));
	# Handle any extra data the current tab needs
	switch ($tab)
	{
		case 'content':
			$form->language = $language;
		break;

		case 'sections':
			$form->sectionList = new SectionList(array('postable_by'=>$_SESSION['USER']));
		break;

		case 'source':
			# Make sure they're allowed to edit the raw source code
			if (!userHasRole('Webmaster')) { $form = new Block('documents/udpate/info.inc',array('document'=>$_SESSION['document'])); }
			$form->language = $language;
		break;

		default:
	}

	$template->blocks[] = $form;
	$template->render();
?>