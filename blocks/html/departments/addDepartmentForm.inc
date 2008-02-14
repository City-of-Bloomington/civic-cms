<?php
/**
 * @copyright Copyright (C) 2006,2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
?>
<h1>New Department</h1>
<form method="post" action="<?php echo $_SERVER['PHP_SELF']; ?>">
<fieldset><legend>Department Info</legend>
	<table>
	<tr><td><label for="department-name">Name</label></td>
		<td><input name="department[name]" id="department-name" size="60" /></td></tr>

	<tr><td><label for="department-address1">Address</label></td>
		<td><input name="department[address1]" id="department-address1" size="60" /></td></tr>

	<tr><td><label for="department-address2">Address</label></td>
		<td><input name="department[address2]" id="department-address2" size="60" /></td></tr>

	<tr><td><label for="department-city">City</label></td>
		<td><input name="department[city]" id="department-city" size="60" />
			<label for="department-state">State</label>
			<input name="department[state]" id="department-state" size="2" />
			<label for="department-zip">Zip</label>
			<input name="department[zip]" id="department-zip" size="5" />
		</td></tr>

	<tr><td><label for="department-phone">Phone</label></td>
		<td><input name="department[phone]" id="department-phone" size="60" /></td></tr>

	<tr><td><label for="department-email">Email</label></td>
		<td><input name="department[email]" id="department-email" size="60" /></td></tr>

	<tr><td><label for="department-ldap_name">LDAP Name</label></td>
		<td><input name="department[ldap_name]" id="department-ldap_name" size="60" /></td></tr>

	<tr><td><label for="department-location_id">Location</label></td>
		<td><select name="department[location_id]" id="department-location_id"><option></option>
			<?php
				$list = new LocationList();
				$list->find();
				foreach($list as $location)
				{
					$name = View::escape($location->getName());
					echo "<option value=\"{$location->getId()}\">$name</option>";
				}
			?>
			</select>
		</td>
	</tr>
	</table>
</fieldset>

<fieldset><legend>Homepage</legend>
<p>Enter the docment_id for the home page you want to use for this department.</p>
<div>
	<label for="department-document_id">Document ID</label>
	<input name="department[document_id]" id="department-document_id" size="3" />
</div>
</fieldset>

<fieldset><legend>Submit</legend>
	<button type="submit" class="submit">Submit</button>
	<a class="cancel" href="<?php echo BASE_URL; ?>/departments">Cancel</a>
</fieldset>
</form>
