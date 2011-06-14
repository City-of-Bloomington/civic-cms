<?php
/**
 * @copyright Copyright (C) 2006 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
	verifyUser(array('Administrator','Webmaster'));

	if (isset($_POST['node']))
	{
		$query = $PDO->prepare("update section_parents set placement=? where node_id=?");
		foreach($_POST['node'] as $node_id=>$placement)
		{
			if (trim($placement)) { $query->execute(array($placement,$node_id)); }
		}
	}

	$template = new Template();
	$template->blocks[] = new Block('sections/rearrangeSectionsForm.inc',array('section'=>new Section(1)));
	echo $template->render();
?>