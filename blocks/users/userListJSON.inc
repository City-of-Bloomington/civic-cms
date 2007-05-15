<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param UserList $this->userList
 */
	$objects = array();
	foreach($this->userList as $user)
	{
		$objects[] = "{'id':'{$user->getId()}','lastname':'{$user->getLastname()}','firstname':'{$user->getFirstname()}'}";
	}
	echo '['.implode(',',$objects).']';
?>