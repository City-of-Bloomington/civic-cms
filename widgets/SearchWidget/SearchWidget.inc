<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
	class SearchWidget extends Widget
	{
		public function __construct()
		{
			$this->className = 'SearchWidget';
			$this->displayName = 'Search';
			$this->includeFile = 'sidebar.inc';
			$this->description = 'Displays a search box';
		}

		public function setData($string) { }
		public function serializePost(array $post) { }

		public function render($template)
		{
			$this->renderIncludeFile($this);
		}
	}
?>