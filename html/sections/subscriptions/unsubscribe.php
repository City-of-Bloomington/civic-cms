<?php
/**
 * @copyright Copyright (C) 2008 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param GET section_id
 * @param GET return_url
 */
if (isset($_SESSION['USER']))
{
	try
	{
		$list = new SectionSubscriptionList(array('section_id'=>$_GET['section_id'],'user_id'=>$_SESSION['USER']->getId()));
		$subscription = $list[0];
		$subscription->delete();
	}
	catch (Exception $e) { $_SESSION['errorMessages'][] = $e; }
}
Header("Location: $_GET[return_url]");