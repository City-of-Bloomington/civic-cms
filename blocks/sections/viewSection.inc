<?php
/**
 * @copyright Copyright (C) 2006 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 */
/*
	$this->section
*/
	if (userHasRole('Publisher') && $_SESSION['USER']->getDepartment_id()==$this->section->getDepartment_id())
	{
		echo "
		<div class=\"contextualMenu\">
			<span class=\"title\">{$this->section->getName()}</span>
			<ul><li><a href=\"".BASE_URL."/sections/editPage.php?section_id={$this->section->getId()}\">Edit Page</a></li>
			</ul>
		</div>
		";
	}
	else { echo "<h1>{$this->section->getName()}</h1>"; }
?>