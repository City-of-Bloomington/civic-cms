<?php
/**
 * @copyright Copyright (C) 2006,2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param Department $this->department
 */
?>
<h1>Edit <?php echo View::escape($this->department->getName()); ?></h1>
<form method="post" action="<?php echo $_SERVER['PHP_SELF']; ?>">
<fieldset><legend>Department Info</legend>
	<input name="department_id" type="hidden" value="<?php echo View::escape($this->department->getId()); ?>" />
	<table>
	<tr><td><label for="department-name">Name</label></td>
		<td><input name="department[name]" id="department-name" value="<?php echo View::escape($this->department->getName()); ?>" /></td></tr>

	<tr><td><label for="department-address1">Address</label></td>
		<td><input name="department[address1]" id="department-address1" value="<?php echo View::escape($this->department->getAddress1()); ?>" /></td></tr>

	<tr><td><label for="department-address2">Address</label></td>
		<td><input name="department[address2]" id="department-address2" value="<?php echo View::escape($this->department->getAddress2()); ?>" /></td></tr>

	<tr><td><label for="department-city">City</label></td>
		<td><input name="department[city]" id="department-city" value="<?php echo View::escape($this->department->getCity()); ?>" />
			<label for="department-state">State</label>
			<input name="department[state]" id="department-state" size="2" value="<?php echo View::escape($this->department->getState()); ?>" />
			<label for="department-zip">Zip</label>
			<input name="department[zip]" id="department-zip" size="5" value="<?php echo View::escape($this->department->getZip()); ?>" />
		</td></tr>

	<tr><td><label for="department-phone">Phone</label></td>
		<td><input name="department[phone]" id="department-phone" value="<?php echo View::escape($this->department->getPhone()); ?>" /></td></tr>

	<tr><td><label for="department-email">Email</label></td>
		<td><input name="department[email]" id="department-email" value="<?php echo View::escape($this->department->getEmail()); ?>" /></td></tr>
	</table>
</fieldset>

<fieldset><legend>Homepage</legend>
<p>Enter the docment_id for the home page you want to use for this department.</p>
<div>
	<label for="department-document_id">Document ID</label>
	<input name="department[document_id]" id="department-document_id" size="3" value="<?php echo $this->department->getDocument_id(); ?>" />
</div>
</fieldset>

<fieldset><legend>Submit</legend>
	<button type="submit" class="submit">Submit</button>
	<button type="button" class="cancel" onclick="document.location.href='<?php echo BASE_URL; ?>/departments';">Cancel</button>
</fieldset>
</form>
