<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
	class AttachmentsWidget extends Widget
	{
		protected $document;

		public function __construct()
		{
			$this->className = 'AttachmentsWidget';
			$this->displayName = 'Attachments';
			$this->includeFile = 'sidebar.inc';
			$this->description = 'Lists all attachments for the current document';
		}

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