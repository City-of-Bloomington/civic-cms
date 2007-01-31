<?php
/**
 * @copyright Copyright (C) 2006 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 */
 	include(APPLICATION_HOME.'/html/editors/FCKeditor/FCKeditor.inc');
	$FCKeditor = new FCKeditor('content');
	$FCKeditor->BasePath = BASE_URL.'/editors/FCKeditor/';
	$FCKeditor->ToolbarSet = 'Custom';
	if (isset($this->document)) { $FCKeditor->Value = $this->document->getContent(); }

	$FCKeditor->create();
?>