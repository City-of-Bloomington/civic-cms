<?php
/**
 * @copyright Copyright (C) 2006,2007 City of Bloomington, Indiana. All rights reserved.
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
		echo View::escape($this->event->getSummary());
	?>
	</div>
	<?php
		$format = $this->event->isAllDayEvent() ? 'M j' : 'M j g:i A';
		$start = date($format,strtotime("{$this->event->getStartDate()} {$this->event->getStartTime()}"));
		$end = date($format,strtotime("{$this->event->getEndDate()} {$this->event->getEndTime()}"));

		if ($this->event->isAllDayEvent()) { echo "<p>$start</p>"; }
		else { echo "<p>$start - $end</p>"; }

		if ($this->event->getRRule()) { echo "<p>{$this->event->getRRule()}</p>"; }

		$location = View::escape($this->event->getLocation()->getName());
		$name = View::escape($this->event->getContact_name());
		$phone = View::escape($this->event->getContact_phone());
		$email = View::escape($this->event->getContact_email());

		echo "
		<p><strong>Location:</strong> $location</p>
		<p><strong>Contact:</strong> $name. $phone, $email</p>
		<div>{$this->event->getDescription()}</div>
		";
	?>
</div>
