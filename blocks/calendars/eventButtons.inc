<?php
/**
 * @copyright Copyright (C) 2006 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param Calendar $this->calendar
 *
 */
	$url = new URL(BASE_URL.'/calendars/addEvent.php');
	if ($this->calendar->getId()) { $url->parameters['calendar_id'] = $this->calendar->getId(); }
?>
<div>
	<button type="button" class="addEvent" onclick="document.location.href='<?php echo $url->getURL(); ?>';">Add Event</button>
</div>