<?php
	verifyUser('Administrator');
	$template = new Template('backend');

	$userList = new UserList();
	$userList->find();
	$template->blocks[] = new Block('users/userList.inc',array('userList'=>$userList));

	$template->render();
?>