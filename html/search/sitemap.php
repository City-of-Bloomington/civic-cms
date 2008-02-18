<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
$template = new Template();

$template->blocks[] = new Block('search/sitemapHeader.inc');

$startingSection = new Section(1);
$template->blocks[] = new Block('sections/listSections.inc',array('section'=>$startingSection));

$template->blocks[] = new Block('documentTypes/documentTypeList.inc');
$template->blocks[] = new Block('calendars/calendarList.inc');
$template->blocks[] = new Block('locations/locationTree.inc');
$template->blocks[] = new Block('languages/languageList.inc');
$template->blocks[] = new Block('facets/facetTree.inc');
$template->blocks[] = new Block('feeds/sitemap.inc');

echo $template->render();
