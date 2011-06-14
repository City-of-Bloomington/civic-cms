<?php
/**
 * @copyright 2009 City of Bloomington, Indiana
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
class SectionDocumentsWidget extends Widget
{
	protected $section;
	protected $document;

	public function __construct()
	{
		$this->className = 'SectionDocumentsWidget';
		$this->displayName = 'Section Documents';
		$this->includeFile = 'documents.inc';
		$this->description = 'Lists the child documents for the current section';
	}

	public function render($template)
	{
		if (isset($template->section) && isset($template->document)) {
			$this->section = $template->section;
			$this->document = $template->document;

			// We don't want to show this box on the homepage for now
			if ($this->section->getId() != 1) {
				echo $this->renderIncludeFile($this);
			}
		}
	}

	/**
	 * The application can call this to find out whether this widget uses stored data
	 * @return boolean
	 */
	public function usesData()
	{
		return false;
	}
	/**
	 * Unserializes the string field from the database into a variable
	 * @param string $string
	 */
	public function setData($string)
	{
	}
	/**
	 * Serializes an array into a string that can be inserted into the database
	 * This will usually be from a form posting.  The form should have used
	 * this widget's dataFields include so we know what array to expect
	 * @param array $post
	 * @return string Serialized data for the widget
	 */
	public function serializePost(array $post)
	{
	}
	/**
	 * This lets the application ask for the path to the file holding the form fields
	 * this widgets wants used
	 * @return string Path to include file
	 */
	public function getDataFieldsetInclude()
	{
	}
}
