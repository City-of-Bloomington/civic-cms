<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param GET section_id
 */
	verifyUser(array('Administrator','Webmaster'));
	$section = new Section($_GET['section_id']);

	if (isset($_GET['parent_id']))
	{
		$parent = new Section($_GET['parent_id']);

		$sectionNode = new SectionNode();
		$sectionNode->setSection($section);
		$sectionNode->setParent($parent);

		try { $sectionNode->save(); }
		catch (Exception $e) { $_SESSION['errorMessages'][] = $e; }
	}

	$template = new Template();
	$template->blocks[] = new Block('sections/sectionToolbar.inc',array('section'=>$section));
	$template->blocks[] = new Block('sections/sectionInfo.inc',array('section'=>$section));
	$template->blocks[] = new Block('sections/addParentForm.inc',array('section'=>$section));
	echo $template->render();
?>