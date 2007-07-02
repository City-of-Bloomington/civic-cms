<?php
/**
 * @copyright Copyright (C) 2006,2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param GET document_id
 * @param GET lang
 */
	verifyUser(array('Webmaster','Administrator','Content Creator'));

	# If they passing a document_id in the URL, start a new Document Updating process
	if (isset($_GET['document_id'])) { $_SESSION['document'] = new Document($_GET['document_id']); }

	# Make sure they're allowed to be editing this document
	if (!$_SESSION['document']->permitsEditingBy($_SESSION['USER']))
	{
		$_SESSION['errorMessages'][] = "noAccessAllowed";
		$template = new Template('closePopup');
		$template->render();
		exit();
	}

	# Set the current language we're working with
	$language = isset($_REQUEST['lang']) ? new Language($_REQUEST['lang']) : new Language($_SESSION['LANGUAGE']);




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

	# Attachments need to be saved right away
	# CONTENT_LENGTH will be set if there's a POST.  If it's too big, most
	# likely they were trying to upload an attachment.
	if (isset($_SERVER['CONTENT_LENGTH']))
	{
		if ($_SERVER['CONTENT_LENGTH'] > 1000000 * (int)ini_get('post_max_size'))
		{
			$_SESSION['errorMessages'][] = new Exception('media/uploadFailed');

			# If CONTENT_LENGTH is too big, the entire POST will be deleted.
			# They were most likely uploading an attachment, so we should send them
			# back to the attachments tab.
			$_REQUEST['tab'] = 'attachments';

		}
	}
	if (isset($_POST['attachment']))
	{
		# Handle uploading of new media attachments
		if (isset($_FILES['attachment']) && $_FILES['attachment']['name'])
		{
			$attachment = new Attachment();
			$attachment->setTitle($_POST['attachment']['title']);
			$attachment->setDescription($_POST['attachment']['description']);
			try
			{
				$attachment->setFile($_FILES['attachment']);
				$attachment->save();
			}
			catch(Exception $e) { $_SESSION['errorMessages'][] = $e; }

			$_SESSION['document']->attach($attachment);
		}
		# Handle selecting existing media to attach
		elseif ($_POST['attachment']['media_id'] && is_numeric($_POST['attachment']['media_id']))
		{
			$media = new Attachment($_POST['attachment']['media_id']);
			$_SESSION['document']->attach($media);
		}
	}

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



	# Figure out which tab we're supposed to show
	$tab = isset($_REQUEST['tab']) ? $_REQUEST['tab'] : 'info';
	$template = new Template('popup');
	$template->blocks[] = new Block('documents/update/tabs.inc');

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

		case 'attachments':
		break;

		case 'source':
			# Make sure they're allowed to edit the raw source code
			if (!userHasRole('Webmaster')) { $form = new Block('documents/update/info.inc',array('document'=>$_SESSION['document'])); }
			$form->language = $language;
		break;

		default:
	}

	$template->blocks[] = $form;
	$template->render();
?>