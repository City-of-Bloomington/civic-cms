<?php
/**
 * @copyright Copyright (C) 2006 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param Document $this->document
 */
	class UpcomingEventsWidget extends Widget
	{
		public function __construct()
		{
			$this->name = "UpcomingEvents";
			$this->includeFile = "sidebar.inc";
			$this->description = "Lists events happening in the next week for the current section";
		}

		public function render()
		{
			global $PDO;

			$sections = array();
			foreach($this->document->getSections() as $section) { $sections[] = $section->getId(); }
			$sections = implode(',',$sections);


			$sql = "select event_id from event_sections s
					left join events e on s.event_id=e.id
					where section_id in ($sections)
					and now()<=start and start<=(now() + interval 7 day)";
			$query = $PDO->query($sql);

			$upcomingEvents = array();
			foreach($query->fetchAll() as $row)
			{
				$upcomingEvents[] = new Event($row['event_id']);
			}

			include(APPLICATION_HOME."/widgets/{$this->name}/{$this->includeFile}");
		}
	}
?>