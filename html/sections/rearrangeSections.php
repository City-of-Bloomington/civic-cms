<?php
/**
 * @copyright Copyright (C) 2006 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 */
	verifyUser('Webmaster');

	if (isset($_POST['node']))
	{
		$query = $PDO->prepare("update section_parents set placement=? where node_id=?");
		foreach($_POST['node'] as $node_id=>$placement)
		{
			if (trim($placement)) { $query->execute(array($placement,$node_id)); }
		}
	}

	$template = new Template('backend');
	$template->blocks[] = new Block('sections/rearrangeSectionsForm.inc',array('section'=>new Section(1)));
	$template->render();
?>