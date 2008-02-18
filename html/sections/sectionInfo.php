<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param GET section_id
 * @param POST sectionNodes The placement of child nodes may be posted for the section
 */
	verifyUser(array('Administrator','Webmaster'));

	if (isset($_GET['section_id'])) { $section = new Section($_GET['section_id']); }

	if (isset($_POST['nodePlacement']))
	{
		foreach($_POST['nodePlacement'] as $node_id=>$placement)
		{
			$node = new SectionNode($node_id);

			# All the nodes should be children of the current section.
			# The first parent we come to should work, since they should all be the same
			if (!isset($section)) { $section = $node->getParent(); }

			$node->setPlacement($placement);
			try { $node->save(); }
			catch (Exception $e) { $_SESSION['errorMessages'][] = $e; }
		}
	}

	$template = new Template();
	$template->blocks[] = new Block('sections/sectionToolbar.inc',array('section'=>$section));
	$template->blocks[] = new Block('sections/sectionInfo.inc',array('section'=>$section));
	echo $template->render();
?>