<?php
/**
 * @copyright Copyright (C) 2008 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
class DepartmentsWidget extends Widget
{
	public $content;
	protected $department;

	public function __construct()
	{
		$this->className = 'DepartmentsWidget';
		$this->displayName = 'City Offices';
		$this->includeFile = 'include.inc';
		$this->description = 'Displays the list of departments in a drop down.';
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
		$this->content = $string;
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
		return $_POST['content'];
	}
	/**
	 * This lets the application ask for the path to the file holding the form fields
	 * this widgets wants used
	 * @return string Path to include file
	 */
	public function getDataFieldsetInclude() { return dirname(__FILE__).'/dataFields.inc'; }
}
