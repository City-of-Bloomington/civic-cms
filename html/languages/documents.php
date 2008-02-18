<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param GET language
 */
$language = new Language($_GET['language']);
$list = new DocumentList(array('lang'=>$_GET['language']));

$template = new Template();
$template->blocks[] = new Block('languages/breadcrumbs.inc',array('language'=>$language));
$template->blocks[] = new Block('languages/documentList.inc',array('documentList'=>$list,'language'=>$language));
echo $template->render();
