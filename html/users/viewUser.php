<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param GET user_id
 * @param GET username
 *
 * You can send this page either a user_id or a username.
 * We want to display the user's information from LDAP
 */
	if (isset($_GET['user_id']))
	{
		$user = new User($_GET['user_id']);
		$_GET['username'] = $user->getUsername();
	}

	$template = new Template();
	$template->blocks[] = new Block('users/userInfo.inc',array('username'=>$_GET['username']));
	$template->render();
?>