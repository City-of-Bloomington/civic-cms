<?php
/**
 * @copyright Copyright (C) 2008 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
class YouTubeWidget extends Widget
{
	public $XMLFeedURL;
	public $numVideosToDisplay;

	public function __construct()
	{
		$this->className = 'YouTubeWidget';
		$this->displayName = 'YouTube Widget';
		$this->includeFile = 'include.inc';
		$this->description = 'Displays a list of videos from a YouTube feed';
	}

	public function render($template)
	{
		echo $this->renderIncludeFile($this);
	}

	/**
	 * The application can call this to find out whether this widget uses stored data
	 * @return boolean
	 */
	public function usesData() { return true; }
	/**
	 * Unserializes the string field from the database into a variable
	 * @param string $string
	 */
	public function setData($string)
	{
		$data = unserialize($string);
		$this->XMLFeedURL = $data['XMLFeedURL'];
		$this->numVideosToDisplay = $data['numVideosToDisplay'];
	}
	/**
	 * Serializes an array into a string that can be inserted into the database
	 * This will usually be from a form posting.  The form should have used
	 * this widget's dataFields include so we know what array to expect
	 * @param array $post
	 * @return string Serialized data for the widget
	 */
	public function serializePost(array $post)
	{
		$data = array();
		$data['XMLFeedURL'] = $_POST['XMLFeedURL'];
		$data['numVideosToDisplay'] = $_POST['numVideosToDisplay'];
		return serialize($data);
	}
	/**
	 * This lets the application ask for the path to the file holding the form fields
	 * this widgets wants used
	 * @return string Path to include file
	 */
	public function getDataFieldsetInclude() { return dirname(__FILE__).'/dataFields.inc'; }
}
