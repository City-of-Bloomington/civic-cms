<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param array $this->hits
 */
?>
<h1>Most Popular Documents</h1>
<table>
<tr><th>ID</th><th>Document</th><th>Hits</th></tr>
<?php
	foreach($this->hits as $hit)
	{
		$title = View::escape($hit['document']->getTitle());
		echo "
		<tr><th>$hit[document_id]</th>
			<td><a href=\"{$hit['document']->getURL()}\">$title</a></td>
			<td>$hit[count]</td>
		</tr>
		";
	}
?>
</table>
