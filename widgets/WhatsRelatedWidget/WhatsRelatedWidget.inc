<?php
/**
 * @copyright Copyright (C) 2006 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
	class WhatsRelatedWidget extends Widget
	{
		public function __construct()
		{
			$this->className = 'WhatsRelatedWidget';
			$this->displayName = 'Whats Related';
			$this->includeFile = 'sidebar.inc';
			$this->description = "Lists other documents in the site that match a document's facets";
		}

		public function setData($string) { }
		public function serializePost(array $post) { }

		public function render($template)
		{
			if (count($template->document->getRelatedDocuments()))
			{
				$this->renderIncludeFile($this);
			}
		}
	}
?>