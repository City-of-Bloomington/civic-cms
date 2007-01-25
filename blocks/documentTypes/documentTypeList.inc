<?php
/**
 * @copyright Copyright (C) 2006 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 */
/*
	$this->documentTypeList
*/
?>
<div class="interfaceBox">
	<div class="titleBar">
		<?php if (userHasRole('Administrator')) { echo "<button type=\"button\" class=\"addSmall\" onclick=\"document.location.href='".BASE_URL."/documentTypes/addDocumentType.php';\">Add</button>"; } ?>
		Document Types
	</div>
<ul>
<?php
	foreach($this->documentTypeList as $type)
	{
		echo "<li>";
		if (userHasRole('Administrator')) { echo "<button type=\"button\" class=\"editSmall\" onclick=\"document.location.href='".BASE_URL."/documentTypes/updateDocumentType.php?documentType_id={$type->getId()}';\">Edit</button>"; }
		echo "$type</li>";
	}
?>
</ul>
</div>