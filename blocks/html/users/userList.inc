<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param UserList $this->userList
 */
	if (userHasRole("Administrator"))
	{
		$addButton = "<button type=\"button\" class=\"addSmall\" onclick=\"document.location.href='".BASE_URL."/users/addUser.php';\">Add</button>";
	}
	else { $addButton = ""; }
?>
<div class="interfaceBox">
	<h1><?php echo $addButton; ?>Users</h1>
	<table>
	<?php
		foreach($this->userList as $user)
		{
			if (userHasRole("Administrator"))
			{
				$editButton = "<button type=\"button\" class=\"editSmall\" onclick=\"document.location.href='updateUser.php?id={$user->getId()}'\">Edit</button>";
				$deleteButton = "<button type=\"button\" class=\"deleteSmall\" onclick=\"FRAMEWORK.deleteConfirmation('deleteUser.php?id={$user->getId()}');\">Delete</button>";
			}
			else
			{
				$editButton = "";
				$deleteButton = "";
			}

			$firstname = View::escape($user->getFirstname());
			$lastname = View::escape($user->getLastname());
			$department = View::escape($user->getDepartment()->getName());
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