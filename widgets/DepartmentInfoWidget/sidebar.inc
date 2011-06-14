<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param Department $this->department
 */
?>
<div class="widget">
	<h1>Contact Info</h1>
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

	echo "<address>$name<br />";
	if ($address1) { echo "$address1<br />"; }
	if ($address2) { echo "$address2<br />"; }
	if ($city || $state || $zip) { echo "$city $state $zip<br />"; }
	if ($phone) { echo "$phone<br />"; }
	if ($email) { echo "$email<br />"; }
	echo "</address>";
?>
</table>
</div>
