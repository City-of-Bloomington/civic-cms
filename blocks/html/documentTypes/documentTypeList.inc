<?php
/**
 * @copyright Copyright (C) 2006,2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
?>
<div class="interfaceBox">
	<h1>
		<?php
			if (userHasRole(array('Administrator','Webmaster')))
			{
				echo "<button type=\"button\" class=\"addSmall\" onclick=\"document.location.href='".BASE_URL."/documentTypes/addDocumentType.php';\">Add</button>";
			}
		?>
		<a href="<?php echo BASE_URL; ?>/documentTypes">Document Types</a>
	</h1>
<ul>
<?php
	$list = new DocumentTypeList();
	$list->find();
	foreach($list as $type)
	{
		echo '<li>';
		if (userHasRole(array('Administrator','Webmaster')))
		{
			echo "<button type=\"button\" class=\"editSmall\" onclick=\"document.location.href='".BASE_URL."/documentTypes/updateDocumentType.php?documentType_id={$type->getId()}';\">Edit</button>";
		}
		echo View::escape($type->getType());
		$count = count($type->getDocuments());
		echo " <a href=\"".BASE_URL."/documentTypes/documents.php?documentType_id={$type->getId()}\">($count)</a></li>";
	}
?>
</ul>
</div>
