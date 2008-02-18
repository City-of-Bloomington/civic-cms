<?php
/**
 * @copyright Copyright (C) 2006,2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param GET document_id If we're editing a document, this will be set
 * @param GET documentType_id If we're creating a new document, this *may* be set
 * @param GET lang
 * @param GET/POST return_url
 * @param GET/POST instance_id
 */
	verifyUser(array('Webmaster','Administrator','Content Creator','Publisher'));

	# Set the current language we're working with
	$language = isset($_REQUEST['lang']) ? new Language($_REQUEST['lang']) : new Language($_SESSION['LANGUAGE']);

	# Keep track of where to send them back to
	$return_url = isset($_REQUEST['return_url']) ? new URL($_REQUEST['return_url']) : new URL(BASE_URL.'/documents');


	# Documents are stored in the SESSION while they are edited.  To be able
	# to keep track of which document we're editing we'll create an instance_id
	# The instance_id must be passed between all forms
	if (isset($_REQUEST['instance_id']))
	{
		$instance_id = $_REQUEST['instance_id'];

		# Make sure the document is actually still loaded in the SESSION
		if (!isset($_SESSION['document'][$instance_id]))
		{
			$_SESSION['errorMessages'][] = new Exception('documents/documentNoLongerAvailable.inc');
		}
	}
	# If they don't pass an instance_id, this must be the first time to this page
	else
	{
		# If they pass in a document_id, load the document for editing
		if (isset($_GET['document_id']))
		{
			$document = new Document($_GET['document_id']);
		}
		# Otherwise they're adding a new document
		else
		{
			$document = new Document();

			if (isset($_GET['documentType_id']))
			{
				$document->setDocumentType_id($_GET['documentType_id'],$language->getCode());
			}
		}

		# Create a new instance
		if (!isset($_SESSION['document'])) { $_SESSION['document'] = array(); }
		$_SESSION['document'][] = $document;
		$keys = array_keys($_SESSION['document']);
		$instance_id = end($keys);
	}


	# Make sure they're allowed to be editing this document
	if (!$_SESSION['document'][$instance_id]->permitsEditingBy($_SESSION['USER']))
	{
		$_SESSION['errorMessages'][] = "noAccessAllowed";
		Header("Location: $return_url");
		exit();
	}


	# Handle any document data that's been posted
	if (isset($_POST['document']))
	{
		foreach($_POST['document'] as $field=>$value)
		{
			$set = "set".ucfirst($field);
			$_SESSION['document'][$instance_id]->$set($value);
		}
	}

	# Only Administrators and webmasters can change the Department
	if (userHasRole(array('Administrator','Webmaster')))
	{
		if (isset($_POST['department_id'])) { $_SESSION['document'][$instance_id]->setDepartment_id($_POST['department_id']); }
	}

	# Content has to be handled specially
	$languageList = new LanguageList();
	$languageList->find();
	foreach($languageList as $l)
	{
		$contentField = "content_{$l->getCode()}";
		if (isset($_POST[$contentField]))
		{
			$_SESSION['document'][$instance_id]->setContent($_POST[$contentField],$l->getCode());
		}

		$sourceField = "source_{$l->getCode()}";
		if (isset($_POST[$sourceField]))
		{
			$_SESSION['document'][$instance_id]->setSource($_POST[$sourceField],$l->getCode());
		}
	}

	# Handle document locking
	if (isset($_POST['locked']))
	{
		# Make sure they're allowed to change the lock status
		if (!$_SESSION['document'][$instance_id]->isLocked() || userHasRole('Administrator') || $_SESSION['USER']->getId()==$_SESSION['document'][$instance_id]->getLockedBy())
		{
			if ($_POST['locked']==='Locked')
			{
				if (!$_SESSION['document'][$instance_id]->isLocked()) { $_SESSION['document'][$instance_id]->setLockedByUser($_SESSION['USER']); }
			}
			else
			{
				$_SESSION['document'][$instance_id]->setLockedBy(null);
			}
		}
	}

	# PHP code inside the content can only be allowed by an Administrator, or a Webmaster
	if (isset($_POST['enablePHP']))
	{
		if (userHasRole(array('Administrator','Webmaster')))
		{
			$_SESSION['document'][$instance_id]->setEnablePHP($_POST['enablePHP']);
		}
	}

	# Sections are going to be added and removed one at a time
	if (isset($_POST['section']))
	{
		if (isset($_POST['section']['add']) && $_POST['section']['add'])
		{
			try { $_SESSION['document'][$instance_id]->addSection($_POST['section']['add']); }
			catch (Exception $e) { $_SESSION['errorMessages'][] = $e; }
		}

		if (isset($_POST['section']['remove']))
		{
			try { $_SESSION['document'][$instance_id]->removeSection($_POST['section']['remove']); }
			catch (Exception $e) { $_SESSION['errorMessages'][] = $e; }
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
			$attachment = new Media();
			$attachment->setTitle($_POST['attachment']['title']);
			$attachment->setDescription($_POST['attachment']['description']);
			try
			{
				$attachment->setFile($_FILES['attachment']);
				$attachment->save();
				$_SESSION['document'][$instance_id]->attach($attachment);
			}
			catch(Exception $e)
			{
				if ($e->getMessage()=='media/fileAlreadyExists')
				{
					try
					{
						$md5 = $attachment->getMd5();
						$media = new Media($md5);
						$_SESSION['document'][$instance_id]->attach($media);
						$_SESSION['errorMessages'][] = new Exception('media/existingFileFound');
					}
					catch(Exception $e) { $_SESSION['errorMessages'][] = $e; }
				}
				else { $_SESSION['errorMessages'][] = $e; }
			}
		}
		# Handle selecting existing media to attach
		elseif ($_POST['attachment']['media_id'] && is_numeric($_POST['attachment']['media_id']))
		{
			$media = new Media($_POST['attachment']['media_id']);
			$_SESSION['document'][$instance_id]->attach($media);
		}
	}

	# Links handling
	if (isset($_POST['documentLink']) && $_POST['documentLink']['href'])
	{
		$link = new DocumentLink();
		$link->setDocument_id($_SESSION['document'][$instance_id]->getId());
		foreach($_POST['documentLink'] as $field=>$value)
		{
			$set = 'set'.ucfirst($field);
			$link->$set($value);
		}
		try { $link->save(); }
		catch (Exception $e) { $_SESSION['errorMessages'][] = $e; }
	}

	# Raw source code handling
	if (isset($_FILES['source']) && $_FILES['source']['name'])
	{
		# Make sure they're allowed to edit the raw source code
		if (userHasRole(array('Administrator','Webmaster')))
		{
			$_SESSION['document'][$instance_id]->setSource(file_get_contents($_FILES['source']['tmp_name']),$_POST['lang']);
		}
	}

	# Save the document only when they ask for it
	if (isset($_POST['action']) && ($_POST['action']=='save'||$_POST['action']=='saveAndContinue') )
	{
		try
		{
			$_SESSION['document'][$instance_id]->save();
			if ($_POST['continue'] != 'true')
			{
				unset($_SESSION['document'][$instance_id]);
				Header("Location: $return_url");
				exit();
			}
		}
		catch (Exception $e) { $_SESSION['errorMessages'][] = $e; }
	}



	# Figure out which tab we're supposed to show
	$tab = isset($_REQUEST['tab']) ? $_REQUEST['tab'] : 'info';
	$template = new Template('popup');
	$template->title = $_SESSION['document'][$instance_id]->getTitle();

	$tabs = new Block('documents/update/tabs.inc');
	$tabs->current_tab = $tab;
	$tabs->return_url = $return_url;
	$tabs->document = $_SESSION['document'][$instance_id];
	$template->blocks[] = $tabs;

	$form = new Block("documents/update/$tab.inc");
	$form->document = $_SESSION['document'][$instance_id];
	$form->return_url = $return_url;
	$form->instance_id = $instance_id;
	# Handle any extra data the current tab needs
	switch ($tab)
	{
		case 'content':
			$form->language = $language;
		break;

		case 'sections':
		break;

		case 'attachments':
		break;

		case 'admin':
			# Make sure they're allowed to edit the raw source code
			if ( !(userHasRole('Webmaster') || userHasRole('Administrator')) )
			{
				$form = new Block('documents/update/info.inc',array('document'=>$_SESSION['document'][$instance_id]));
			}
			$form->language = $language;
		break;

		case 'facets':
			$groups = new FacetGroupList();
			if ( !(userHasRole(array('Administrator','Webmaster'))) )
			{
				$groups->find(array('department_id'=>$_SESSION['USER']->getDepartment_id()));
			}
			else  { $groups->find(); }
			$form->facetGroupList = $groups;
		break;

		default:
	}

	$template->blocks[] = $form;
	echo $template->render();
