<?php
/**
 * @copyright 2010 City of Bloomington, Indiana
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
$list = new LocationGroupList();
$list->find();
$groups = array();
foreach ($list as $group) {
	$groups[] = array('id'=>$group->getId(),
						'name'=>$group->getName(),
						'description'=>strip_tags($group->getDescription()));

}
echo json_encode($groups);