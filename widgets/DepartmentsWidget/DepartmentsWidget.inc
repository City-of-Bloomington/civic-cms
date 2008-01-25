<?php
/**
 * @copyright Copyright (C) 2008 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
class DepartmentsWidget extends Widget
{
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
		$this->renderIncludeFile($this);
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

