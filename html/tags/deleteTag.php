<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param GET tag_id
 */
	verifyUser(array('Administrator','Webmaster'));

	$tag = new Tag($_GET['tag_id']);
	$tag->delete();

	Header('Location: home.php');
?>
