<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
class SearchWidget extends Widget
{
	protected $search;

	public function __construct()
	{
		$this->className = 'SearchWidget';
		$this->displayName = 'Search';
		$this->includeFile = 'sidebar.inc';
		$this->description = 'Displays a search box';
	}

	public function render($template)
	{
		$this->search = isset($_GET['search']) ? $_GET['search'] : '';
		echo $this->renderIncludeFile($this);
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
