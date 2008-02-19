<?php
/**
 * @copyright Copyright (C) 2007,2008 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param UserList $this->userList
 * @param string $this->authenticationMethod
 */
?>
<div class="interfaceBox">
	<div class="tabBar">
		<ul><?php
				$class = $this->authenticationMethod==='LDAP' ? 'class="current"' : '';
				echo "<li $class><a href=\"".BASE_URL."/users?authenticationMethod=LDAP\">LDAP</a></li>";

				$class = $this->authenticationMethod==='local' ? 'class="current"' : '';
				echo "<li $class><a href=\"".BASE_URL."/users?authenticationMethod=local\">local</a></li>";
			?>
		</ul>
	</div>
	<h1><?php
			if (userHasRole('Administrator')) { echo "<a class=\"addSmall\" href=\"".BASE_URL."/users/addUser.php\">Add</a>"; }
			echo $this->authenticationMethod.' Users';
		?>
	</h1>
	<table>
	<?php
		foreach($this->userList as $user)
		{
			if (userHasRole("Administrator"))
			{
				$editButton = "<a class=\"editSmall\" href=\"updateUser.php?id={$user->getId()}\">Edit</a>";
				$deleteButton = "<button type=\"button\" class=\"deleteSmall\" onclick=\"FRAMEWORK.deleteConfirmation('deleteUser.php?id={$user->getId()}');\">Delete</button>";
			}
			else
			{
				$editButton = "";
				$deleteButton = "";
			}

			$firstname = View::escape($user->getFirstname());
			$lastname = View::escape($user->getLastname());
			$department = $user->getDepartment_id() ? View::escape($user->getDepartment()->getName()) : '';
			echo "
			<tr><td>{$editButton}{$deleteButton}</td>
				<td><a href=\"".BASE_URL."/users/viewUser.php?user_id={$user->getId()}\">{$user->getUsername()}</a></td>
				<td><a href=\"".BASE_URL."/users/viewUser.php?user_id={$user->getId()}\">$firstname $lastname</a></td>
				<td>{$user->getAuthenticationMethod()}</td>
				<td>$department</td>
				<td>
			";
					foreach($user->getRoles() as $role) { echo "$role "; }
			echo "</td></tr>";
		}
	?>
	</table>
</div>
