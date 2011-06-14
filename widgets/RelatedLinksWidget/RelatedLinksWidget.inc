<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
class RelatedLinksWidget extends Widget
{
	protected $document;

	public function __construct()
	{
		$this->className = 'RelatedLinksWidget';
		$this->displayName = 'Related Links';
		$this->includeFile = 'sidebar.inc';
		$this->description = 'Shows links related to the current Document';
	}

	public function render($template)
	{
		if (isset($template->document))
		{
			$this->document = $template->document;

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
