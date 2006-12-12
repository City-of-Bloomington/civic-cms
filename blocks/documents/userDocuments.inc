<?php
/**
 * @copyright Copyright (C) 2006 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 */
/*
	$this->documentList
	$this->user
*/
?>
<div class="interfaceBox">
	<div class="titleBar">
	<?php
		if (userHasRole('Content Creator')) { echo "<button type=\"button\" class=\"addSmall\" onclick=\"document.location.href='".BASE_URL."/documents/addDocument.php?return_url=".$_SERVER['REQUEST_URI']."';\">Add</button>"; }
		echo "{$this->user->getFirstname()} {$this->user->getLastname()}'s Documents";
	?>
	</div>
	<table>
	<tr><th></th>
		<th></th>
		<th>Created on</th></tr>
	<?php
		foreach($this->documentList as $document)
		{
			if ($_SESSION['USER']->canEdit($document)) { $editButton = "<button type=\"button\" class=\"editSmall\" onclick=\"document.location.href='".BASE_URL."/documents/updateDocument.php?document_id={$document->getId()};return_url=$_SERVER[REQUEST_URI]';\">Edit</button>"; }
			else { $editButton = ""; }
			echo "
			<tr><td>$editButton</td>
				<td><a href=\"".BASE_URL."/documents/viewDocument.php?document_id={$document->getId()}\">{$document->getTitle()}</a></td>
				<td>{$document->getCreated()}</td></tr>
			";
		}
	?>
	</table>
</div>