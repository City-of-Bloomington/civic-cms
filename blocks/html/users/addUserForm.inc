<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
?>
<h1>New User</h1>
<form method="post" action="<?php echo $_SERVER['PHP_SELF']; ?>">
<fieldset><legend>Login Info</legend>
	<table>
	<tr><td><label for="user-authenticationMethod">Authentication</label></td>
		<td><select name="user[authenticationMethod]" id="user-authenticationMethod">
				<option <?php if(isset($_POST['user']['authenticationMethod']) && $_POST['user']['authenticationMethod']=="LDAP") echo "selected=\"selected\""; ?>>LDAP</option>
				<option <?php if(isset($_POST['user']['authenticationMethod']) && $_POST['user']['authenticationMethod']=="local") echo "selected=\"selected\""; ?>>local</option>
			</select>
		</td>
	</tr>
	<tr><td><label for="user-username">Username</label></td>
		<td><input name="user[username]" id="user-username" size="30" value="<?php if(isset($_POST['user']['username'])) echo View::escape($_POST['user']['username']); ?>" /></td></tr>
	<tr><td><label for="user-password">Password</label></td>
		<td><input name="user[password]" id="user-password" size="30" /></td></tr>
	<tr><td><label for="user-department_id">Department</label></td>
		<td><select name="user[department_id]" id="user-department_id">
			<?php
				$departments = new DepartmentList();
				$departments->find();
				foreach($departments as $department)
				{
					$name = View::escape($department->getName());
					echo "<option value=\"{$department->getId()}\">$name</option>";
				}
			?>
			</select>
		</td>
	</tr>
	<tr><td><label for="user[roles]">Roles</label></td>
		<td><select name="user[roles][]" id="user-roles" size="5" multiple="multiple">
			<?php
				$roles = new RoleList();
				$roles->find();
				foreach($roles as $role)
				{
					$selected = (isset($_POST['user']['roles']) && in_array($role,$_POST['user']['roles'])) ? 'selected="selected"' : '';
					echo "<option $selected>$role</option>";
				}
			?>
			</select>
		</td>
	</tr>
	</table>

</fieldset>
<fieldset><legend>Personal Info</legend>
	<p>This information is only necessary for local users.  For LDAP authentication, this information will be pulled from LDAP.</p>
	<table>
	<tr><td><label for="user-firstname">Firstname</label></td>
		<td><input name="user[firstname]" id="user-firstname" size="30" value="<?php if(isset($_POST['user']['firstname'])) echo View::escape($_POST['user']['firstname']); ?>" /></td></tr>
	<tr><td><label for="user-lastname">Lastname</label></td>
		<td><input name="user[lastname]" id="user-lastname" size="30" value="<?php if(isset($_POST['user']['lastname'])) echo View::escape($_POST['user']['lastname']); ?>" /></td></tr>
	<tr><td><label for="user-email">Email</label></td>
		<td><input name="user[email]" id="user-email" size="60" value="<?php if(isset($_POST['user']['email'])) echo View::escape($_POST['user']['email']); ?>" /></td></tr>
	</table>

	<button type="submit" class="submit">Submit</button>
	<a class="cancel" href="<?php echo BASE_URL; ?>/users">Cancel</a>
</fieldset>
</form>