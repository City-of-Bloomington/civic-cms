<?php
/**
 * @copyright 2007-2012 City of Bloomington, Indiana
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param Calendar $this->calendar
 */
$TIMEZONE = 'US-Eastern';
$DTSTAMP = "DTSTAMP:".gmdate('Ymd\THis\Z');

foreach($this->calendar->getEvents() as $event) {

	if ($event->isAllDayEvent()) {
		$start = $event->getStart('Ymd');
		$end = $event->getEnd('Ymd');

		$vevent[] = "UID:$start-{$event->getId()}@$_SERVER[SERVER_NAME]";

		$DTSTART = "DTSTART;VALUE=DATE:$start";
		$DTEND = $end ? "DTEND;VALUE=DATE:$end" : '';
	}
	else {
		$start = $event->getStart('Ymd\THis');
		$end = $event->getEnd('Ymd\THis');
		$DTSTART = "DTSTART;TZID=$TIMEZONE:$start";
		$DTEND = $end ? "DTEND;TZID=$TIMEZONE:$end" : '';
	}

	//$CREATED = "CREATED:$TIMEZONE:".$event->getCreated('Ymd\THis');
	//$LAST_MODIFIED = "LAST-MODIFIED;TZID=$TIMEZONE:".$event->getModified('Ymd\THis');

	$SUMMARY = fold('SUMMARY:'.escape($event->getTitle()));
	$DESCRIPTION = fold('DESCRIPTION:'.escape($event->getDescription()));

	$locationName = $event->getLocation() ? $event->getLocation()->getName() : '';
	$LOCATION = fold('LOCATION:'.escape($locationName));

	# icalendar format requires everything be flush left.
	$vevent = array(
		'BEGIN:VEVENT',
		"UID:$start-{$event->getId()}@$_SERVER[SERVER_NAME]",
		$SUMMARY,
		$LOCATION,
		$DTSTART
	);
	if ($DTEND) { $vevent[] = $DTEND; }
	$vevent[] = $DESCRIPTION;
	if ($event->getRrule()) { $vevent[] = "RRULE:{$event->getRrule()}"; }
	$vevent[] = "END:VEVENT\n";
	echo implode("\n", $vevent);
}


/**
 * Word wraps strings to iCal's 72 character limit
 *
 * @param string $string
 * @return string
 *
 * Returns a string the complied with iCal's 72 character line limit
 * Lines are folded according to RFC 2445
 */
function fold($string) {
	$string = preg_replace('/[\s*\r*\n*]/',' ',trim($string));
	return trim(preg_replace("/(.{1,72})/i","\\1\r\n ",$string));
}

/**
 * @param string $string
 * @return string
 */
function escape($string) {
	// The order of replacements here is important
	// We don't want to replace all the backslashes we're inserting.
	// Make sure to do the backslash replacement first.
	return str_replace(array("\\", '"', ';', "\r"),array("\\\\", '\"', '\;', ''),$string);
}

/**
 * Takes a getdate() array and returns an iCalendar timestamp string
 *
 * @param array $date PHP getdate array
 */
function formatTimestamp(array $date) {
	$string = "$date[year]$date[mon]$date[mday]";
	if (isset($date['hours'])) { $string.= "T$date[hours]$date[minutes]"; }
	return $string;
}
