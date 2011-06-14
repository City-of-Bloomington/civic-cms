<?php
/**
 * @copyright Copyright (C) 2008 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
verifyUser();

#if (isset($_POST['section']))
#{
#	$_SESSION['USER']->setSubscriptions(array_keys($_POST['section']));
#}

#$list = new SectionList(array('highlightSubscription'=>1));
$template = new Template();
#$template->blocks[] = new Block('sections/subscriptions/highlightedSubscriptions.inc',array('sectionList'=>$list));
echo $template->render();
