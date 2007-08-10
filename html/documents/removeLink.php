<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param GET link_id
 */
	verifyUser(array('Administrator','Webmaster','Content Creator','Publisher'));
	$link = new DocumentLink($_GET['link_id']);
	if ($link->getDocument()->permitsEditingBy($_SESSION['USER']))
	{
		try { $link->delete(); }
		catch (Exception $e) { };
	}
?>