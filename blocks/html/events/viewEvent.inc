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
			echo "<button type=\"button\" class=\"editSmall\" onclick=\"window.open('".BASE_URL."/events/updateEvent.php?event_id={$this->event->getId()}');\">Edit</button>";
		}
		echo $this->event->getSummary();
	?>
	</div>
	<?php
		$format = $this->event->isAllDayEvent() ? 'M j' : 'M j g:i A';
		$start = date($format,strtotime("{$this->event->getStartDate()} {$this->event->getStartTime()}"));
		$end = date($format,strtotime("{$this->event->getEndDate()} {$this->event->getEndTime()}"));

		if ($this->event->isAllDayEvent()) { echo "<p>$start</p>"; }
		else { echo "<p>$start - $end</p>"; }

		if ($this->event->getRRule()) { echo "<p>{$this->event->getRRule()}</p>"; }

		echo "
		<p><strong>Location:</strong> {$this->event->getLocation()}</p>
		<p><strong>Contact:</strong> {$this->event->getContact_name()}. {$this->event->getContact_phone()}, {$this->event->getContact_email()}</p>
		<p>{$this->event->getDescription()}</p>
		";
	?>
</div>