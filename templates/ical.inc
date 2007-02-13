<?php
/**
 * @copyright Copyright (C) 2006 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 */
/*
	$this->calendar
*/
?>
BEGIN:VCALENDAR
PRODID:http://<?php $_SERVER['HTTP_HOST']; ?>/<?php echo BASE_URL; ?>/calendars
VERSION:2.0
<?php
	foreach($this->calendar->getEvents() as $event)
	{

	}
?>
END:VCALENDAR