<?php
/**
 * @copyright Copyright (C) 2006,2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param GET documentType_id
 * @param GET section_id (Optionally include a section to pre-select)
 * @param GET/POST return_url
 * @param GET/POST instance_id
 */
	# Make sure they're allowed to edit stuff in this section
	verifyUser(array('Administrator','Webmaster','Content Creator','Publisher'));

	# Set the current language we're working with
	$language = isset($_REQUEST['lang']) ? new Language($_REQUEST['lang']) : new Language($_SESSION['LANGUAGE']);

	# Keep track of where to send them back to
	$return_url = isset($_REQUEST['return_url']) ? new URL($_REQUEST['return_url']) : new URL(BASE_URL.'/documents');


	# Documents are stored in the SESSION while they are edited.  To be able
	# to keep track of which document we're editing we'll create an instance_id
	# The instance_id must be passed between all forms
	if (isset($_REQUEST['instance_id'])) { $instance_id = $_REQUEST['instance_id']; }
	else
	{
		# Create a new instance
		if (!isset($_SESSION['document'])) { $_SESSION['document'] = array(); }
		$_SESSION['document'][] = new Document();
		$keys = array_keys($_SESSION['document']);
		$instance_id = end($keys);
		$_SESSION['document'][$instance_id] = new Document();

		if (isset($_GET['documentType_id']))
		{
			$type = new DocumentType($_GET['documentType_id']);
			$_SESSION['document'][$instance_id]->setDocumentType($type,$_SESSION['LANGUAGE']);
		}

		if (isset($_GET['section_id']))
		{
			$section = new Section($_GET['section_id']);
			if (!$section->permitsEditingBy($_SESSION['USER'])) { unset($section); }
			else { $_SESSION['document'][$instance_id]->addSection($section); }
		}
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
			if ($_POST['locked']=='yes')
			{
				if (!$_SESSION['document'][$instance_id]->isLocked()) { $_SESSION['document'][$instance_id]->setLockedByUser($_SESSION['USER']); }
			}
			else
			{
				$_SESSION['document'][$instance_id]->setLockedBy(null);
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
		if (userHasRole(array('Administrator','Webmaster')))
		{
			$_SESSION['document'][$instance_id]->setSource(file_get_contents($_FILES['source']['tmp_name']),$_POST['lang']);
		}
	}
	# Save the document only when they ask for it
	if (isset($_POST['action']) && $_POST['action']=='save')
	{
		try
		{
			$_SESSION['document'][$instance_id]->save();
			unset($_SESSION['document'][$instance_id]);
			Header("Location: $return_url");
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
	$template->blocks[] = new Block('documents/add/tabs.inc',array('current_tab'=>$tab,'return_url'=>$return_url));

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
			$form->sectionList = new SectionList(array('postable_by'=>$_SESSION['USER']));
		break;

		case 'source':
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
	$template->render();
?>
