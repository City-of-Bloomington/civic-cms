<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
	class CalendarWidget extends Widget
	{
		public function __construct()
		{
			$this->className = 'CalendarWidget';
			$this->displayName = 'Calendar';
			$this->includeFile = 'sidebar.inc';
			$this->description = 'Shows a small calendar with event dates highlighted';
		}

		public function render($template)
		{
			$this->renderIncludeFile($this);
		}
	}
?>