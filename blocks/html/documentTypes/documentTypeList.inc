<?php
/**
 * @copyright Copyright (C) 2006,2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param array $this->documentTypeList
 */
?>
<div class="interfaceBox">
	<div class="titleBar">
		<?php
			if (userHasRole(array('Administrator','Webmaster')))
			{
				echo "<button type=\"button\" class=\"addSmall\" onclick=\"document.location.href='".BASE_URL."/documentTypes/addDocumentType.php';\">Add</button>";
			}
		?>
		Document Types
	</div>
<ul>
<?php
	foreach($this->documentTypeList as $type)
	{
		echo '<li>';
		if (userHasRole(array('Administrator','Webmaster')))
		{
			echo "<button type=\"button\" class=\"editSmall\" onclick=\"document.location.href='".BASE_URL."/documentTypes/updateDocumentType.php?documentType_id={$type->getId()}';\">Edit</button>";
		}
		echo View::escape($type->getType());
		$count = count($type->getDocuments());
		echo " ($count)</li>";
	}
?>
</ul>
</div>