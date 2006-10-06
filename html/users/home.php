<?php
	verifyUser("Administrator");
	$view = new View();

	$userList = new UserList();
	$userList->find();
	$view->blocks[] = new Block("users/userList.inc",array("userList"=>$userList));

	$view->render();
?>