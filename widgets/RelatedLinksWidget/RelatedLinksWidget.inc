<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
	class RelatedLinksWidget extends Widget
	{
		protected $section;
		protected $document;

		public function __construct()
		{
			$this->className = 'RelatedLinksWidget';
			$this->displayName = 'Related Links';
			$this->includeFile = 'sidebar.inc';
			$this->description = 'Shows links from all the documents in the current section';
		}

		public function render($template)
		{
			global $section;
			if ($section)
			{
				if (isset($template->document))
				{
					$this->section = $section;
					$this->document = $template->document;

					$this->renderIncludeFile($this);
				}
			}
		}
	}
?>