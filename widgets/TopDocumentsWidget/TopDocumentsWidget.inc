<?php
/**
 * @copyright Copyright (C) 2008 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
class TopDocumentsWidget extends Widget
{
	/**
	 * The documentType this widget is supposed to render.
	 */
	public $documentType;

	public function __construct()
	{
		$this->className = 'TopDocumentsWidget';
		$this->displayName = 'Top Documents';
		$this->includeFile = 'include.inc';
		$this->description = 'Displays links to the top documents for the DocumentType provided';
	}

	public function render($template)
	{
		$this->renderIncludeFile($this);
	}

	/**
	 * The application can call this to find out whether this widget uses stored data
	 * @return boolean
	 */
	public function usesData() { return true; }
	/**
	 * Unserializes the string field from the database into a variable
	 * @param string $string
	 */
	public function setData($string)
	{
		$this->documentType = new DocumentType($string);
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
		return $_POST['documentType_id'];
	}
	/**
	 * This lets the application ask for the path to the file holding the form fields
	 * this widgets wants used
	 * @return string Path to include file
	 */
	public function getDataFieldsetInclude() { return dirname(__FILE__).'/dataFields.inc'; }
}