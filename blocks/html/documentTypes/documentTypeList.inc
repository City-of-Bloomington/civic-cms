<?php
/**
 * @copyright Copyright (C) 2006-2008 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
?>
<div class="interfaceBox">
<h2>Document Types</h2>
<ul>
<?php
	$list = new DocumentTypeList();
	$list->find();
	foreach($list as $type)
	{
		echo '<li>';
		if (userHasRole(array('Administrator','Webmaster')))
		{
			echo "<a class=\"editSmall button\" href=\"".BASE_URL."/documentTypes/updateDocumentType.php?documentType_id={$type->getId()}\">Edit</a>";
		}
		echo View::escape($type->getType());
		$count = count($type->getDocuments());
		echo " <a href=\"".BASE_URL."/documentTypes/documents.php?documentType_id={$type->getId()}\">($count)</a></li>";
	}
?>
</ul>
</div>
