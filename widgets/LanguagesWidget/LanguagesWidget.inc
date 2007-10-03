<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
	class LanguagesWidget extends Widget
	{
		protected $languages;

		public function __construct()
		{
			$this->className = 'LanguagesWidget';
			$this->displayName = 'Languages';
			$this->includeFile = 'sidebar.inc';
			$this->description = 'Displays the list of available translations for a document';
		}

		public function setData($string) { }
		public function serializePost(array $post) { }

		public function render($template)
		{
			if (isset($template->document))
			{
				$this->languages = $template->document->getLanguages();
				$this->renderIncludeFile($this);
			}
		}
	}
?>