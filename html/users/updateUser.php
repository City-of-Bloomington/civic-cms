<?php
/*
	$_GET variables:	id
	---------------------------------------------------------------------------
	$_POST variables:	id
						user [ authenticationMethod		# Optional
								username				password
								roles					firstname
														lastname
														department
														phone
							]
*/
	verifyUser("Administrator");

	$view = new View();
	$form = new Block("users/updateUserForm.inc");
	if (isset($_GET['id'])) { $form = new User($_GET['user']); }

	if (isset($_POST['user']))
	{
		$user = new User($_POST['id']);
		foreach($_POST['user'] as $field=>$value)
		{
			$set = "set".ucfirst($field);
			$user->$set($value);
		}

		$view->user = $user;
		try
		{
			$user->save();
			Header("Location: home.php");
			exit();
		}
		catch (Exception $e)
		{
			$_SESSION['errorMessages'][] = $e;
			$form->user = $user;
		}
	}

	$view->blocks[] = $form;
	$view->render();
?>