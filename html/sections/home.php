<?php
/**
 * @copyright Copyright (C) 2006,2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
$template = new Template();

$sectionTree = new Block('sections/listSections.inc');
try
{
	$section = new Section(1);
	$sectionTree->section = $section;
}
catch(Exception $e) { }
$template->blocks[] = $sectionTree;

if (userHasRole(array('Administrator','Webmaster')))
{
	$list = new SectionList(array('parent_id'=>'null'));
	$template->blocks[] = new Block('sections/unassignedSections.inc',array('sectionList'=>$list));
}
echo $template->render();
