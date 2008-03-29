<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
class RelatedSectionsWidget extends Widget
{
	protected $sectionList;

	public function __construct()
	{
		$this->className = 'RelatedSectionsWidget';
		$this->displayName = 'Related Sections';
		$this->includeFile = 'sidebar.inc';
		$this->description = 'Shows other sections for the information being displayed';
	}

	/**
	 * We want to show other sections for the document
	 */
	public function render($template)
	{
		if (isset($template->document))
		{
			$this->sectionList = $template->document->getSections();
			if (count($this->sectionList) > 1)
			{
				echo $this->renderIncludeFile($this);
			}
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
