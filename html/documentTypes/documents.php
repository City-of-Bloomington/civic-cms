<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param GET documentType_id
 * @param GET tagGroup_id
 *
 * Displays the documents of a given DocumentType, organized by Tag
 */
	$type = new DocumentType($_GET['documentType_id']);

	$template = (isset($_GET['format'])) ? new Template($_GET['format'],$_GET['format']) : new Template();

	$block = new Block('documentTypes/documents.inc',array('documentType'=>$type));
	if (isset($_GET['tagGroup_id']))
	{
		if (is_numeric($_GET['tagGroup_id']) && $_GET['tagGroup_id']>0)
		{
			$block->tagGroup = new TagGroup($_GET['tagGroup_id']);
		}
	}
	else
	{
		# Load the default Tag Group
		if ($type->getDefaultTagGroup_id()) { $block->tagGroup = $type->getDefaultTagGroup(); }
	}

	$template->blocks[] = $block;
	$template->render();
?>
