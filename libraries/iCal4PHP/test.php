<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
	include './Recur.inc';

	#$recur = new Recur('FREQ=DAILY;BYDAY=MO,TU,WE,TH,FR;COUNT=10');
	#$recur = new Recur('FREQ=YEARLY;BYWEEKNO=2,32,48');
	#$recur = new Recur('FREQ=MONTHLY;BYMONTHDAY=15,16');
	#$recur = new Recur('FREQ=MONTHLY;BYDAY=MO,WE');
	$recur = new Recur('FREQ=MONTHLY;WKST=SU;INTERVAL=2;BYDAY=5TU');
	$start = strtotime('2007-10-26 17:07:00');
	$end = strtotime('+2 years',$start);
	$dates = $recur->getDates($start,$end);

	echo "Test returned: \n";
	foreach($dates as $date) { echo date('r',$date)."\n"; }

	#$t = time();

	#$t = strtotime('-1 Sunday',$t);
	#echo date('r',$t);



