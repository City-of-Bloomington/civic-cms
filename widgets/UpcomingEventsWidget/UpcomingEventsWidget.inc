<?php
/**
 * @copyright Copyright (C) 2006,2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
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

	public function render($template)
	{

		if (isset($template->document))
		{
			$sections = array();
			foreach($template->document->getSections() as $section) { $sections[] = $section->getId(); }
			if (count($sections))
			{
				$search = array();
				$search['section_id'] = $sections;

				$t = getdate();
				$search['rangeStart'] = mktime(0,0,0,$t['mon'],$t['mday'],$t['year']);
				$search['rangeEnd'] = strtotime('+7 days',$search['rangeStart']);

				$list = new EventList();
				$list->find($search,'start');

				$upcomingEvents = array();
				foreach($list as $event)
				{
					$recurrences = $event->getRecurrences($search['rangeStart'],$search['rangeEnd']);
					if (count($recurrences)) { $upcomingEvents = array_merge($upcomingEvents,$recurrences); }
				}
				$this->upcomingEvents = $upcomingEvents;

				$this->renderIncludeFile($this);
			}
		}
	}

	/**
	 * This widget does not use an extra data
	 */
	public function usesData() { return false; }
	/**
	 * @ignore
	 */
	public function setData($string) { }
	/**
	 * @ignore
	 */
	public function serializePost(array $post) { }
	/**
	 * @ignore
	 */
	public function getDataFieldsetInclude() { return null; }
}
