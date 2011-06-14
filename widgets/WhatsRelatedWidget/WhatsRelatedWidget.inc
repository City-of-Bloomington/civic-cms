<?php
/**
 * @copyright Copyright (C) 2006 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
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

	public function render($template)
	{
		if (count($template->document->getRelatedDocuments()))
		{
			echo $this->renderIncludeFile($this);
		}
	}

	/**
	 * This widget does not use an extra data
	 */
	public function usesData() { return false; }
	/**
	 * @ignore
	 */
	public function setData($string) { }
	/**
	 * @ignore
	 */
	public function serializePost(array $post) { }
	/**
	 * @ignore
	 */
	public function getDataFieldsetInclude() { return null; }
}
