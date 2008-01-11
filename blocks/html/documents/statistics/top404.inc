<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param array $this->requests
 */
?>
<h1>Top 404</h1>
<table>
<tr><th>Requested URL</th><th>Count</th></tr>
<?php
	foreach($this->requests as $hit)
	{
		$path = View::escape($hit['path']);
		echo "
		<tr><td>$path</td>
			<td>$hit[count]</td></tr>
		";
	}
?>
</table>
