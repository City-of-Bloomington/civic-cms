<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
class DepartmentInfoWidget extends Widget
{
	protected $department;

	public function __construct()
	{
		$this->className = 'DepartmentInfoWidget';
		$this->displayName = 'Department Info';
		$this->includeFile = 'sidebar.inc';
		$this->description = 'Displays contact information for the Department that owns the current document.';
	}

	public function render($template)
	{
		if (isset($_GET['section_id']) && isset($template->document))
		{
			$section = new Section($_GET['section_id']);
			if ($section->getSectionDocument_id() == $template->document->getId())
			{
				$this->department = $template->document->getDepartment();
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
