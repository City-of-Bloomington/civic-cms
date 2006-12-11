<?php
/**
 * @copyright Copyright (C) 2006 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 */
	class WhatsNew extends Widget
	{
		public function __construct()
		{
			$this->name = "WhatsNew";
			$this->includeFile = "sidebar.inc";
		}

		public function render() { include(APPLICATION_HOME."/widgets/WhatsNew/sidebar.inc"); }
	}
?>