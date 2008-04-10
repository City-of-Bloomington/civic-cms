<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param array $this->searches
 */
?>
<h2>Top Searches</h2>
<table>
<tr><th>Query String</th><th>Count</th></tr>
<?php
	foreach($this->searches as $hit)
	{
		$string = View::escape($hit['queryString']);
		echo "
		<tr><td><a href=\"".BASE_URL."/search/?search=$string\">$string</a></td>
			<td>$hit[count]</td>
		</tr>\n
		";
	}
?>
</table>
