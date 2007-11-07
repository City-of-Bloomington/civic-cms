<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
class FacetGroupWidget extends Widget
{
	/**
	 * The group this widget is supposed to render.
	 */
	protected $facetGroup;

	public function __construct()
	{
		$this->className = 'FacetGroupWidget';
		$this->displayName = 'Facet Group Links';
		$this->includeFile = 'sidebar.inc';
		$this->description = 'Displays links to the facets in the chosen group';
	}

	/**
	 * Unserializes the string field from the database into a variable
	 * @param string $string
	 */
	public function setData($string)
	{
		$this->facetGroup = new FacetGroup($string);
	}

	/**
	 * Serializes an array into a string that can be insterted into the database
	 * This will usually be from a form posting.  The form should have used
	 * this widget's dataFields include so we know what array to expect
	 * @param array $post
	 */
	public function serializePost(array $post)
	{
		if(isset($_POST['facetGroup_id']))
		{
			return $_POST['facetGroup_id'];
		}
	}

	/**
	 * The application can call this to find out whether this widget uses stored data
	 * @return boolean
	 */
	public function usesData() { return true; }

	/**
	 * This lets the application ask for the path to the file holding the form fields
	 * this widgets wants used
	 * @return string Path to include file
	 */
	public function getDataFieldsetInclude() { return dirname(__FILE__).'/dataFields.inc'; }


	public function render($template)
	{
		$this->renderIncludeFile($this);
	}
}
