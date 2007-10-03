<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
	class FacetGroupWidget extends Widget
	{
		protected $facetGroup;

		public function __construct()
		{
			$this->className = 'FacetGroupWidget';
			$this->displayName = 'Facet Group Links';
			$this->includeFile = 'sidebar.inc';
			$this->description = 'Displays links to the facets in the chosen group';
		}

		public function setData($string)
		{
			$this->facetGroup = new FacetGroup($string);
		}

		public function serializePost(array $post)
		{
			if(isset($_POST['facetGroup_id'])) { return $_POST['facetGroup_id']; }
		}

		public function render($template)
		{
			$this->renderIncludeFile($this);
		}
	}
?>