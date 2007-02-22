<?php
/**
 * @copyright Copyright (C) 2006 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param Event $this->event
 */
?>
<div class="interfaceBox">
	<div class="titleBar">
	<?php
		if (isset($_SESSION['USER']) && $this->event->permitsEditingBy($_SESSION['USER']))
		{
			echo "<button type=\"button\" class=\"editSmall\" onclick=\"document.location.href='".BASE_URL."/calendars/updateEvent.php?event_id={$this->event->getId()}';\">Edit</button>";
		}
		echo $this->event->getSummary();
	?>
	</div>
	<?php
		$start = date('Y-m-d g:i A',strtotime($this->event->getStart()));
		$end = date('Y-m-d g:i A',strtotime($this->event->getEnd()));
		echo "
		<p>$start - $end</p>
		<p><strong>Location:</strong> {$this->event->getLocation()}</p>
		<p>{$this->event->getDescription()}</p>
		";
	?>
</div>