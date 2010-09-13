<?php
/**
 * List  a good number of events, based on MAX_DAYS_AHEAD and MAX_EVENTS
 * This screen navigates two weeks forward and back
 *
 * @copyright 2010 City of Bloomington, Indiana
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param Calendar $this->calendar
 * @param array $this->date
 */
$MAX_DAYS_AHEAD = 60;
$MAX_EVENTS = 30;
$rangeStart = !isset($this->date)
			? time()
			: mktime(0,0,0,$this->date['mon'],$this->date['mday'],$this->date['year']);

$recurrences = $this->calendar->getEventRecurrenceArray($rangeStart);
$numDaysAhead = 0;
$numEventsDisplayed = 0;



$events = array();
echo "<events>";
while ($numDaysAhead<=$MAX_DAYS_AHEAD && $numEventsDisplayed<=$MAX_EVENTS) {
	$timestamp = strtotime("+$numDaysAhead day",$rangeStart);
	$date = getdate($timestamp);

	$year = $date['year'];
	$month = $date['mon'];
	$day = $date['mday'];

if (isset($recurrences[$year][$month][$day])) {
		foreach ($recurrences[$year][$month][$day] as $recurrence) {
			$title = View::escape($recurrence->getTitle());
			$location = View::escape($recurrence->getLocation()->getName());
			$description = WikiMarkup::parse(View::escape($recurrence->getDescription()));
			echo "
			<event id=\"{$recurrence->getId()}\">
				<start>{$recurrence->getStart('Y-m-d H:i:s')}</start>
				<title>$title</title>
				<location>$location</location>
				<description>$description</description>
			</event>
			";
			
			$numEventsDisplayed++;
		}
	}
	$numDaysAhead++;
}
echo "</events>";
?>
