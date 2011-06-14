<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param User $this->user
 */
?>
<h1>Edit <?php echo $this->user->getUsername(); ?></h1>
<form method="post" action="<?php echo $_SERVER['SCRIPT_NAME']; ?>">
<fieldset><legend>Login Info</legend>
	<input name="id" type="hidden" value="<?php echo $this->user->getId(); ?>" />
	<table>
	<tr><td><label for="user-authenticationMethod">Authentication</label></td>
		<td><select name="user[authenticationMethod]" id="user-authenticationMethod">
				<option <?php if ($this->user->getAuthenticationMethod()=='LDAP') echo "selected=\"selected\""; ?>>LDAP</option>
				<option <?php if ($this->user->getAuthenticationMethod()=='local') echo "selected=\"selected\""; ?>>local</option>
			</select>
		</td>
	</tr>
	<tr><td><label for="user-username">Username</label></td>
		<td><input name="user[username]" id="user-username" value="<?php echo $this->user->getUsername(); ?>" size="30" /></td></tr>
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
					$selected = ($this->user->getDepartment_id() == $department->getId()) ? 'selected="selected"' : '';
					echo "<option value=\"{$department->getId()}\" $selected>$name</option>";
				}
			?>
			</select>
		</td>
	</tr>
	<tr><td><label for="user-roles">Roles</label></td>
		<td><select name="user[roles][]" id="user-roles" size="5" multiple="multiple">
			<?php
				$roles = new RoleList();
				$roles->find();
				foreach($roles as $role)
				{
					$selected = (in_array($role,$this->user->getRoles())) ? 'selected="selected"' : '';
					echo "<option $selected>$role</option>";
				}
			?>
			</select>
		</td>
	</tr>
	</table>

</fieldset>
<fieldset><legend>Personal Info</legend>
	<table>
	<tr><td><label for="user-firstname">Firstname</label></td>
		<td><input name="user[firstname]" id="user-firstname" size="30" value="<?php echo View::escape($this->user->getFirstname()); ?>" /></td></tr>
	<tr><td><label for="user-lastname">Lastname</label></td>
		<td><input name="user[lastname]" id="user-lastname" size="30" value="<?php echo View::escape($this->user->getLastname()); ?>" /></td></tr>
	<tr><td><label for="user-email">Email</label></td>
		<td><input name="user[email]" id="user-email" size="60" value="<?php echo View::escape($this->user->getEmail()); ?>" /></td></tr>
	</table>

	<button type="submit" class="submit">Submit</button>
	<a class="cancel" href="<?php echo BASE_URL; ?>/users">Cancel</a>
</fieldset>
</form>
