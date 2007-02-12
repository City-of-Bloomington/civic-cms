<?php
/**
 * @copyright Copyright (C) 2006 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 */
	class WhatsRelated extends Widget
	{
		public function __construct()
		{
			$this->name = 'WhatsRelated';
			$this->includeFile = 'sidebar.inc';
			$this->description = "Lists other documents in the site that match a document's facets";
		}

		public function render()
		{
			if (count($this->document->getRelatedDocuments()))
			{
				include APPLICATION_HOME.'/widgets/WhatsRelated/sidebar.inc';
			}
		}
	}
?>