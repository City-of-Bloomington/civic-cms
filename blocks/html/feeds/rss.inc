<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
?>
<h2>RSS Feeds</h2>
<table>
<?php
	$list = new DocumentTypeList();
	$list->find();
	foreach($list as $type)
	{
		$name = View::escape($type->getType());
		$url = BASE_URL.'/documentTypes/documents.php?format=rss;documentType_id='.$type->getId();
		echo "<tr><th>$name</th><td><a href=\"$url\">$url</a></td></tr>";
	}
?>
</table>
