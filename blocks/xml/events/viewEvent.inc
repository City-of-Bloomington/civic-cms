<?php
/**
 * @copyright 2006-2010 City of Bloomington, Indiana
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param Event $this->event
 * @param EventRecurrence $this->event
 */
$title = View::escape($this->event->getTitle());
$description = View::escape(WikiMarkup::parse($this->event->getDescription()));
$location = View::escape($this->event->getLocation()->getName());
$name = View::escape($this->event->getContact_name());
$phone = View::escape($this->event->getContact_phone());
$email = View::escape($this->event->getContact_email());
echo "
<event id=\"{$this->event->getId()}\">
	<start>{$this->event->getStart('Y-m-d H:i:s')}</start>
	<title>$title</title>
	<location id=\"{$this->event->getLocation()->getId()}\">
		$location
	</location>
	<description>$description</description>
	<contact>
		<name>$name</name>
		<phone>$phone</phone>
		<email>$email</email>
	</contact>
</event>
";

