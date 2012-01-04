<?php
/**
 * @copyright 2006-2011 City of Bloomington, Indiana
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
	verifyUser('Administrator');
	if (isset($_POST['user']))
	{
		$user = new User();
		foreach($_POST['user'] as $field=>$value)
		{
			$set = 'set'.ucfirst($field);
			$user->$set($value);
		}

		try
		{
			// Load their information from LDAP, ADS, etc.
			if ($user->getAuthenticationMethod() != 'local') {
				$externalIdentity = $user->getAuthenticationMethod();
				$identity = new $externalIdentity($user->getUsername());

				$user->setFirstname($identity->getFirstname());
				$user->setLastname($identity->getLastname());
				$user->setEmail($identity->getEmail());
			}

			$user->save();
			Header('Location: home.php');
			exit();
		}
		catch (Exception $e) { $_SESSION['errorMessages'][] = $e; }
	}

	$template = new Template();
	$template->blocks[] = new Block('users/addUserForm.inc');
	echo $template->render();
