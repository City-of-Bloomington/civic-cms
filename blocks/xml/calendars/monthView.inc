<?php
/**
 * @copyright Copyright (C) 2006-2008 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param object $this->calendar The calendar holding all the events we want to display
 * @param array $this->date A date so we know which year/month to display
 */
	$start = mktime(0,0,0,$this->date['mon'],1,$this->date['year']);
	$end = strtotime('+1 month',$start);

	$recurrences = $this->calendar->getEventRecurrenceArray($start,$end);

	$date = getdate($start);
	$year = $date['year'];
	$month = $date['mon'];
?>
<events>
<?php

	# Loop through all the days of the month
	$day = 1;
	$lastDayOfMonth = date('j',strtotime('-1 day',$end));
	while($day <= $lastDayOfMonth)
	{
		# Markup for a single day in the calendar
		$url = new URL(BASE_URL.'/calendars');
		$url->parameters = array('year'=>$year,'mon'=>$month,'mday'=>$day);
		if ($this->calendar->getId()) { $url->parameters['calendar_id'] = $this->calendar->getId(); }
		$url->parameters['view'] = 'day';

		$dayOfWeek = date('l',mktime(0,0,0,$month,$day,$year));
		$hasEvent = (isset($recurrences[$year][$month][$day]) && count($recurrences[$year][$month][$day])) ? ' hasEvent' : '';

		if (isset($recurrences[$year][$month][$day]))
		{
			foreach($recurrences[$year][$month][$day] as $recurrence)
			{
				$title = View::escape($recurrence->getTitle());
			$location = View::escape($recurrence->getLocation()->getName());
			$description = View::escape(WikiMarkup::parse($recurrence->getDescription()));
				echo "
				<event id=\"{$recurrence->getId()}\">
				<start>{$recurrence->getStart('Y-m-d H:i:s')}</start>
				<title>$title</title>
				<location id=\"{$recurrence->getLocation()->getId()}\">
					$location
				</location>
				<description>$description</description>
			</event>
				";
			}
		}
		$day++;
	}
?>
</events>
