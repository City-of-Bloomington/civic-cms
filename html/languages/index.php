<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
	$template = new Template();
	$template->blocks[] = new Block('languages/breadcrumbs.inc');
	$template->blocks[] = new Block('languages/languageList.inc');
	echo $template->render();
