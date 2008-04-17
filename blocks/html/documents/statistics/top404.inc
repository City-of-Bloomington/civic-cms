<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param array $this->requests
 */
?>
<h2>Top 404</h2>
<table>
<tr><th>Requested URL</th><th>Count</th><th></th></tr>
<?php
	foreach($this->requests as $hit)
	{
		$referers = BASE_URL."/documents/statistics/404Referers.php?path=$hit[path]";
		$path = View::escape($hit['path']);
		echo "
		<tr><td>$path</td>
			<td>$hit[count]</td>
			<td><button type=\"button\" onclick=\"window.open('$referers');\">Referrers</button></td>
		</tr>
		";
	}
?>
</table>
