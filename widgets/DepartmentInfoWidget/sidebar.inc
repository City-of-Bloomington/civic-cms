<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param Department $this->department
 */
?>
<div class="widget">
	<h1>Directory</h1>
<table>
<?php
	$name = View::escape($this->department->getName());
	$address1 = View::escape($this->department->getAddress1());
	$address2 = View::escape($this->department->getAddress2());
	$city = View::escape($this->department->getCity());
	$state = View::escape($this->department->getState());
	$zip = View::escape($this->department->getZip());
	$phone = View::escape($this->department->getPhone());
	$email = View::escape($this->department->getEmail());

	$name = "<a href=\"".BASE_URL."/directory\">$name</a>";

	echo "<tr><th>$name</th></tr>";
	if ($address1) { echo "<tr><td>$address1</td></tr>\n"; }
	if ($address2) { echo "<tr><td>$address2</td></tr>\n"; }
	if ($city || $state || $zip) { echo "<tr><td>$city $state $zip</td></tr>"; }
	if ($phone) { echo "<tr><td>$phone</td></tr>"; }
	if ($email) { echo "<tr><td>$email</td></tr>"; }
?>
</table>
</div>
