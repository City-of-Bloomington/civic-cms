<?php
/**
 * @copyright Copyright (C) 2008 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 *
 * Form used to create an un-privileged, public account.
 * These will be locally authenticated, using their email address as the username
 */
?>
<h1>Request an Account</h1>
<p>You can create your own account here.</p>
<p>Once you have requested an account, you will receive an email with instructions on
how to activate that account.  Account requests that are not activated within a period of time
are deleted.</p>

<form method="post" action="<?php echo $_SERVER['SCRIPT_NAME']; ?>">
<fieldset><legend>Login Information</legend>
	<table>
	<tr><td><label for="email" class="required">Email Address</label></td>
		<td><input name="email" id="email" size="60" /></td></tr>
	<tr><td><label for="password" class="required">Password</label></td>
		<td><input name="password" id="password" type="password" /></td></tr>
	<tr><td><label for="retype" class="required">Retype Password</label></td>
		<td><input name="retype" id="retype" type="password" /></td></tr>
	</table>
</fieldset>
<button type="submit" class="submit">Submit</button>
</form>