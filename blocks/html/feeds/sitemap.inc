<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
	/**
	 * This fires off the JavaScript that turns an expandable UL into a tree
	 * This library has a bug - it will freeze if the <li> elements are not on their
	 * own line.  Make sure to put line breaks for each <li>
	 */
	include_once APPLICATION_HOME.'/includes/js/tree.inc';
?>
<div class="interfaceBox">
<h1><a href="<?php echo BASE_URL; ?>/feeds">Feeds</a></h1>
<ul class="expandable">
	<li>
		<a href="<?php echo BASE_URL; ?>/feeds">RSS</a>
		<ul>
		<?php
			$list = new DocumentTypeList();
			$list->find();
			foreach($list as $type)
			{
				$name = View::escape($type->getType());
				$url = BASE_URL.'/documentTypes/documents.php?format=rss;documentType_id='.$type->getId();
				echo "
				<li>
					<a href=\"$url\">$name</a>
				</li>
				";
			}
		?>
		</ul>
	</li>
	<li>
		<a href="<?php echo BASE_URL; ?>/feeds">Calendars</a>
		<ul>
		<?php
			$list = new CalendarList();
			$list->find();
			foreach($list as $calendar)
			{
				$name = View::escape($calendar->getName());
				$url = new URL(BASE_URL.'/calendars?format=ical;calendar_id='.$calendar->getId());
				$url->setProtocol('webcal://');
				echo "
				<li>
					<a href=\"$url\">$name</a>
				</li>
				";
			}
		?>
		</ul>
	</li>
	<li>
		<a href="<?php echo BASE_URL; ?>/feeds">KML</a>
		<ul>
		<?php
			$list = new LocationGroupList();
			$list->find();
			foreach($list as $group)
			{
				$name = View::escape($group->getName());
				$url = BASE_URL.'/locations?format=kml;locationGroup_id='.$group->getId();
				echo "
				<li>
					<a href=\"$url\">$name</a>
				</li>
				";
			}
		?>
		</ul>
	</li>
</ul>
</div>