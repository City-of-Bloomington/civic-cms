<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param GET skin
 *
 * Passing a skin name as a parameter in the URL should be handled
 * by /configuration.inc.  So all we need to do is list the skins with an HREF
 */
	$template = new Template('backend');
	$template->blocks[] = new Block('skins/skinList.inc');
	echo $template->render();
