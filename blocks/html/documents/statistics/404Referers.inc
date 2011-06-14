<h1>Referers</h1>
<ul>
<?php
/**
 * @copyright Copyright (C) 2008 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param array $this->referers
 */
foreach($this->referers as $referer)
{
	$url = View::escape($referer);
	echo "<li><a href=\"$url\">$url</a></li>\n";
}
?>
</ul>
