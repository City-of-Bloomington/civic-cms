<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
	class AdminToolsWidget extends Widget
	{
		public function __construct()
		{
			$this->className = 'AdminToolsWidget';
			$this->displayName = 'Admin';
			$this->includeFile = 'sidebar.inc';
			$this->description = 'Shows links to all the stuff a user can do';
		}

		public function render($template)
		{
			if (isset($_SESSION['USER']))
			{
				$this->renderIncludeFile($this);
			}
		}
	}
?>