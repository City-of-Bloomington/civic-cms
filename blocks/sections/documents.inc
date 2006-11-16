<?php
/**
 * @copyright Copyright (C) 2006 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 */
/*
	$this->section
*/
	$this->editMode = ( userHasRole(array('Publisher','Content Creator')) &&
						$_SESSION['USER']->getDepartment_id()==$this->section->getDepartment_id() ) ? true : false;
?>
<div class="interfaceBox">
	<div class="titleBar">
		<?php if ($this->editMode) { echo "<button type=\"button\" class=\"addSmall\" onclick=\"document.location.href='".BASE_URL."/documents/addDocument.php?section_id={$this->section->getId()}';\">Add</button>"; } ?>
		Documents
	</div>
	<ul>
	<?php
		foreach($this->section->getDocuments() as $document)
		{
			echo "<li>";
			if ($this->editMode) { echo "<button type=\"button\" class=\"editSmall\" onclick=\"document.location.href='".BASE_URL."/documents/updateDocument.php?document_id={$document->getId()}';\">Edit</button>"; }
			echo "<a href=\"".BASE_URL."/documents/viewDocument.php?document_id={$document->getId()}\">{$document->getId()}</a>";
			echo "</li>";
		}
	?>
	</ul>
</div>