<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
	class SectionsWidget extends Widget
	{
		protected $document;

		public function __construct()
		{
			$this->className = 'SectionsWidget';
			$this->displayName = 'Sections';
			$this->includeFile = 'sidebar.inc';
			$this->description = 'Lists the sub-sections for the current section';
		}

		public function setData($string) { }
		public function serializePost(array $post) { }

		public function render($template)
		{
			if (isset($template->document))
			{
				$this->document = $template->document;
				$this->renderIncludeFile($this);
			}
		}
	}
?>