<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param GET document_id
 *
 * This should load a document and send the document's icon to the browser
 */
	Header("Content-type: image/gif");
	readfile(APPLICATION_HOME.'/html/skins/default/images/citylogo-blue.gif');
?>