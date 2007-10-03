<?php
/**
 * @copyright Copyright (C) 2006 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param Document $this->document
 */
	class UpcomingEventsWidget extends Widget
	{
		protected $upcomingEvents = array();

		public function __construct()
		{
			$this->className = 'UpcomingEventsWidget';
			$this->displayName = 'Upcoming Events';
			$this->includeFile = 'sidebar.inc';
			$this->description = 'Lists events happening in the next week for the current section';
		}

		public function setData($string) { }
		public function serializePost(array $post) { }

		public function render($template)
		{
			global $PDO;

			if (isset($template->document))
			{
				$sections = array();
				foreach($template->document->getSections() as $section) { $sections[] = $section->getId(); }
				if (count($sections))
				{
					$sections = implode(',',$sections);


					$sql = "select event_id from event_sections s
							left join events e on s.event_id=e.id
							where section_id in ($sections)
							and now()<=startDate and startDate<=(now() + interval 7 day)";
					$query = $PDO->query($sql);

					foreach($query->fetchAll() as $row)
					{
						$this->upcomingEvents[] = new Event($row['event_id']);
					}

					$this->renderIncludeFile($this);
				}
			}
		}
	}
?>