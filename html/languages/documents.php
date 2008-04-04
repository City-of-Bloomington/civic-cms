<?php
/**
 * @copyright Copyright (C) 2007-2008 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param GET language
 */
if (isset($_GET['language']) && $_GET['language'])
{
	try { $language = new Language($_GET['language']); }
	catch(Exception $e)
	{
		$_SESSION['errorMessages'][] = $e;
		Header('Location: index.php');
		exit();
	}
	$list = new DocumentList(array('lang'=>$_GET['language']));

	$template = new Template();
	$template->blocks[] = new Block('languages/breadcrumbs.inc',array('language'=>$language));
	$template->blocks[] = new Block('languages/documentList.inc',array('documentList'=>$list,'language'=>$language));
	echo $template->render();
}
else
{
	Header('Location: index.php');
}
