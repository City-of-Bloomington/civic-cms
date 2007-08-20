<?php
/**
 * @copyright Copyright (C) 2006,2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param string $content
 * @param string $content_field_name
 */
 	# The FCKEditor does not currently support Safari
 	$browser = get_browser();
 	if ($browser->browser != 'Safari')
 	{
		include APPLICATION_HOME.'/html/editors/fckeditor/FCKeditor.php';
		$FCKeditor = new FCKeditor($content_field_name);
		$FCKeditor->BasePath = BASE_URL.'/editors/fckeditor/';
		$FCKeditor->ToolbarSet = 'Custom';
		$FCKeditor->Value = $content;

		$FCKeditor->create();
	}
	else
	{
		echo "<p>The Safari web browser is not yet supported for content editing.</p>";
	}
?>