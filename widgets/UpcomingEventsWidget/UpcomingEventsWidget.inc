<?php
/**
 * @copyright Copyright (C) 2006,2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
class UpcomingEventsWidget extends Widget
{
	protected $recurrenceArray = array();

	public $calendar_id;
	public $numDays = 5;
	public $isSectionBased = true;

	public function __construct()
	{
		$this->className = 'UpcomingEventsWidget';
		$this->displayName = 'Upcoming Events';
		$this->includeFile = 'sidebar.inc';
		$this->description = 'Lists events happening in the next week for the current section';
	}

	public function render($template)
	{
		# We want the Homepage to always display events from the entire site,
		# even though this is usually a global widget and is marked as section-based
		$isHomepage = (isset($template->document) && $template->document->getId()==1) ? true : false;
		if ($this->isSectionBased && !$isHomepage)
		{
			$search = array();
			if (isset($template->document))
			{
				$sections = array();
				foreach($template->document->getSections() as $section) { $sections[] = $section->getId(); }
				if (count($sections)) { $search['section_id'] = $sections; }
			}
			else
			{
				# There shouldn't be any sections with an ID of 0
				$search['section_id'] = 0;
			}
		}
		else { $search = null; }


		$t = getdate();
		$rangeStart = mktime(0,0,0,$t['mon'],$t['mday'],$t['year']);
		$rangeEnd = strtotime("+{$this->numDays} days",$rangeStart);

		$calendar = ($this->calendar_id > 0) ? new Calendar($this->calendar_id) : new Calendar();
		$this->recurrenceArray = $calendar->getEventRecurrenceArray($rangeStart,$rangeEnd,$search);

		echo $this->renderIncludeFile($this);
	}

	/**
	 * The application can call this to find out whether this widget uses stored data
	 * @return boolean
	 */
	public function usesData() { return true; }
	/**
	 * Unserializes the string field from the database into class variables
	 * @param string $string
	 */
	public function setData($string)
	{
		$data = unserialize($string);
		$this->calendar_id = isset($data['calendar_id']) ? $data['calendar_id'] : null;
		$this->numDays = isset($data['numDays']) ? $data['numDays'] : 5;

		# The default for this should be true.
		# If developers do not explicityly turn off the section based feature, then
		# this widget should only show events for the current section
		# or show no events for a null section
		$this->isSectionBased = isset($data['isSectionBased']) ? $data['isSectionBased'] : true;
	}
	/**
	 * Serializes an array into a string that can be inserted into the database
	 * This will usually be from a form posting.  The form should have used
	 * this widget's dataFields include so we know what array to expect
	 * @param array $post
	 */
	public function serializePost(array $post)
	{
		$data = array();
		if (isset($_POST['calendar_id']) && $_POST['calendar_id']) { $data['calendar_id'] = (int) $_POST['calendar_id']; }
		if (isset($_POST['numDays']) && $_POST['numDays']) { $data['numDays'] = (int) $_POST['numDays']; }
		if (isset($_POST['isSectionBased'])) { $data['isSectionBased'] = $_POST['isSectionBased']=='true' ? true : false; }
		return serialize($data);
	}
	/**
	 * This lets the application ask for the path to the file holding the form fields
	 * this widgets wants used
	 * @return string Path to include file
	 */
	public function getDataFieldsetInclude() { return dirname(__FILE__).'/dataFields.inc'; }
}
