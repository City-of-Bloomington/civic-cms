<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
	Header('Content-type: text/css');
	Header('Cache-control: must-revalidate');
	Header('Expires: '.gmdate('D, d M Y H:i:s',time()+3600).' GMT');
	include APPLICATION_HOME."/html/skins/$_SESSION[skin]/screen.css";
?>