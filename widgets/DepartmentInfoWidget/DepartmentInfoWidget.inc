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
			if (isset($template->document))
			{
				$this->department = $template->document->getDepartment();
				$this->renderIncludeFile($this);
			}
		}
	}
?>