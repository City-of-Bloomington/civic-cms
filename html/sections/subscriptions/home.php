<?php
/**
 * @copyright Copyright (C) 2008 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
$list = new SectionList(array('highlightSubscription'=>1));

$template = new Template();
$template->blocks[] = new Block('sections/subscriptions/highlightedSubscriptions.inc',array('sectionList'=>$list));
if (isset($_SESSION['USER']))
{
	$mySubscriptions = new Block('sections/subscriptions/subscriptions.inc');
	$mySubscriptions->title = 'My Subscriptions';
	$mySubscriptions->subscriptionList = $_SESSION['USER']->getSubscriptions();
	$template->blocks[] = $mySubscriptions;
}
$template->render();