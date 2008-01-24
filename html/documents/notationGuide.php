<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
$page = isset($_GET['page']) ? $_GET['page'] : '';
switch ($page)
{
	case 'attachments':
		$guide = new Block('documents/notationGuide/attachments.inc');
	break;

	case 'facets':
		$guide = new Block('documents/notationGuide/facets.inc');
	break;

	case 'images':
		$guide = new Block('documents/notationGuide/images.inc');
	break;

	default:
		$guide = new Block('documents/notationGuide/links.inc');
}

$template = new Template('popup');
$template->blocks[] = new Block('documents/notationGuide/toc.inc');
$template->blocks[] = $guide;
$template->render();
