<?php
/**
 * @copyright Copyright (C) 2006-2008 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param Event $this->event
 * @param EventRecurrence $this->event
 */
?>
<h2>
<?php
	if (isset($_SESSION['USER']) && $this->event->permitsEditingBy($_SESSION['USER']))
	{
		echo "
		<a class=\"editSmall button\" href=\"".BASE_URL."/events/updateEvent.php?event_id={$this->event->getId()};return_url={$this->event->getURL()}\">Edit</a>
		<button type=\"button\" class=\"deleteSmall\" onclick=\"FRAMEWORK.deleteConfirmation('".BASE_URL."/events/deleteEvent.php?event_id={$this->event->getId()}');\">Delete</button>
		";
	}
	echo View::escape($this->event->getTitle());
?>
</h2>
<?php
	$format = $this->event->isAllDayEvent() ? 'M j Y' : 'M j Y g:i A';
	$start = $this->event->getStart($format);
	$end = $this->event->getEnd($format);

	if ($this->event->isAllDayEvent()) { echo "<p>$start</p>"; }
	else { echo "<p>$start - $end</p>"; }

	$location = View::escape($this->event->getLocation()->getName());
	$name = View::escape($this->event->getContact_name());
	$phone = View::escape($this->event->getContact_phone());
	$email = View::escape($this->event->getContact_email());

	$description = WikiMarkup::parse($this->event->getDescription());
	echo "
	<p><strong>Location:</strong> <a href=\"{$this->event->getLocation()->getURL()}\">$location</a></p>
	<p><strong>Contact:</strong> $name. $phone, $email</p>
	<div>$description</div>
	";

	if (!$this->event instanceof EventRecurrence && $this->event->getRRule())
	{
		echo "<div>{$this->event->getRRule()}</div>";
	}
?>
