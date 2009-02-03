<?php
/**
 * @copyright 2009 City of Bloomington, Indiana
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
class DocumentFacetsWidget extends Widget
{
	protected $document;

	public function __construct()
	{
		$this->className = 'DocumentFacetsWidget';
		$this->displayName = 'Document Facets';
		$this->includeFile = 'include.inc';
		$this->description = 'Lists all facets for the current document';
	}

	public function render($template)
	{
		if (isset($template->document)) {
			$this->document = $template->document;
			echo $this->renderIncludeFile($this);
		}
	}

	/**
	 * This widget does not use an extra data
	 */
	public function usesData()
	{
		return false;
	}
	/**
	 * @ignore
	 */
	public function setData($string)
	{

	}
	/**
	 * @ignore
	 */
	public function serializePost(array $post)
	{

	}
	/**
	 * @ignore
	 */
	public function getDataFieldsetInclude()
	{
		return null;
	}
}
