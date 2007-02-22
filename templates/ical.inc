<?php
/**
 * @copyright Copyright (C) 2006 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 */
/*
	$this->calendar
*/
	function fold($string) { return trim(preg_replace("/(.{1,72})/i","\\1\r\n ",trim($string))); }
	/**
	 * Takes a getdate() array and returns an iCalendar timestamp string
	 */
	function formatTimestamp(array $date)
	{
		$string = "$date[year]$date[mon]$date[mday]";
		if (isset($date['hours'])) { $string.= "T$date[hours]$date[minutes]"; }
		return $string;
	}
?>
BEGIN:VCALENDAR
PRODID:http://<?php echo $_SERVER['HTTP_HOST'].BASE_URL; ?>/calendars
VERSION:2.0
<?php
	foreach($this->calendar->getEvents() as $event)
	{
		$created = formatTimestamp($event->dateStringToArray($event->getCreated()));
		$start = formatTimestamp($event->dateStringToArray($event->getStart()));
		$end = formatTimestamp($event->dateStringToArray($event->getEnd()));

		$summary = fold('SUMMARY:'.$event->getSummary());
		$description = fold('DESCRIPTION:'.$event->getDescription());

		echo "
BEGIN:VEVENT
UID:$created-{$event->getId()}@$_SERVER[HTTP_HOST]
$summary
LOCATION:{$event->getLocation()->getName()}
DTSTAMP:$created
DTSTART:$start
DTEND:$end
$description
END:VEVENT
";
	}
?>
END:VCALENDAR