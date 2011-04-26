<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param Calendar $this->calendar
 */
	$TIMEZONE = 'US-Eastern';
	$DTSTAMP = "DTSTAMP:".gmdate('Ymd\THis\Z');

	foreach($this->calendar->getEvents() as $event)
	{
		if ($event->isAllDayEvent())
		{
			$start = $event->getStart('Ymd');
			$end = $event->getEnd('Ymd');
			$DTSTART = "DTSTART;VALUE=DATE:$start";
			$DTEND = "DTEND;VALUE=DATE:$end";
		}
		else
		{
			$start = $event->getStart('Ymd\THis');
			$end = $event->getEnd('Ymd\THis');
			$DTSTART = "DTSTART;TZID=$TIMEZONE:$start";
			$DTEND = "DTEND;TZID=$TIMEZONE:$end";
		}

		$CREATED = "CREATED:$TIMEZONE:".$event->getCreated('Ymd\THis');
		$LAST_MODIFIED = "LAST-MODIFIED;TZID=$TIMEZONE:".$event->getModified('Ymd\THis');

		$SUMMARY = fold('SUMMARY:'.$event->getTitle());
		$DESCRIPTION = fold('DESCRIPTION:'.$event->getDescription());

		$locationName = $event->getLocation() ? $event->getLocation()->getName() : '';
		$LOCATION = fold('LOCATION:$locationName');

# icalendar format requires everything be flush left.
		echo "
BEGIN:VEVENT
UID:$start-{$event->getId()}@$_SERVER[SERVER_NAME]
$SUMMARY
$LOCATION
$DTSTART
$DTEND
$DESCRIPTION
";
if ($event->getRrule()) { echo "RRULE:{$event->getRrule()}\n"; }
echo "END:VEVENT
";
	}


	function fold($string)
	{
		$string = preg_replace('/[\s*\r*\n*]/',' ',trim($string));
		return trim(preg_replace("/(.{1,72})/i","\\1\r\n ",$string));
	}
	/**
	* @param array $date PHP getdate array
	 * Takes a getdate() array and returns an iCalendar timestamp string
	 */
	function formatTimestamp(array $date)
	{
		$string = "$date[year]$date[mon]$date[mday]";
		if (isset($date['hours'])) { $string.= "T$date[hours]$date[minutes]"; }
		return $string;
	}
?>
