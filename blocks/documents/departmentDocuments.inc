<?php
/**
 * @copyright Copyright (C) 2006 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 */
/*
	$this->documentList
	$this->department
*/
?>
<div class="interfaceBox">
	<div class="titleBar"><?php echo "{$this->department->getName()} Documents"; ?></div>
	<table>
	<tr><th></th>
		<th></th>
		<th>Created on</th></tr>
	<?php
		foreach($this->documentList as $document)
		{
			if ($_SESSION['USER']->canEdit($document)) { $editButton = "<button type=\"button\" class=\"editSmall\" onclick=\"document.location.href='".BASE_URL."/documents/updateDocument.php?document_id={$document->getId()}';\">Edit</button>"; }
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