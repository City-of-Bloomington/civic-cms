<?php
/**
 * @copyright Copyright (C) 2006,2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
?>
BEGIN:VCALENDAR
PRODID:<?php echo BASE_URL; ?>/calendars
VERSION:2.0
<?php
	$this->includeBlocks();
?>
END:VCALENDAR