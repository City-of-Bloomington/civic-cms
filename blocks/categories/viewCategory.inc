<?php
/**
 * @copyright Copyright (C) 2006 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 */
/*
	$this->category
*/
	if (userHasRole('Administrator'))
	{
		echo "
		<div class=\"contextualMenu\">
			<span class=\"title\">{$this->category->getName()}</span>
			<ul><li><a href=\"".BASE_URL."/categories/editPage.php?category_id={$this->category->getId()}\">Edit Page</a></li>
			</ul>
		</div>
		";
	}
	else { echo "<h1>{$this->category->getName()}</h1>"; }

	echo $this->category->getContent();
?>