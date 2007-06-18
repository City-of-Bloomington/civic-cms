<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param GET sectionNode_id
 */
	verifyUser(array('Administrator','Webmaster'));

	$node = new SectionNode($_GET['sectionNode_id']);
	$section_id = $node->getSection_id();

	$node->delete();

	Header("Location: sectionInfo.php?section_id=$section_id");
?>