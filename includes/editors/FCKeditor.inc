<?php
/**
 * @copyright Copyright (C) 2006,2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param Document $this->document
 * @param Language $this->language
 */
 	include APPLICATION_HOME.'/html/editors/fckeditor/FCKeditor.php';
	$FCKeditor = new FCKeditor('content');
	$FCKeditor->BasePath = BASE_URL.'/editors/fckeditor/';
	$FCKeditor->ToolbarSet = 'Custom';
	if (isset($this->document)) { $FCKeditor->Value = $this->document->getContent($this->language->getCode()); }

	$FCKeditor->create();
?>