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
		$this->description = 'Shows other sections the current section is a child of';
	}

	public function render($template)
	{
		global $section;
		if ($section)
		{
			if (isset($template->document))
			{
				$sections = $section->getParents();
				foreach($sections as $id=>$section)
				{
					if (in_array($id,array_keys($template->currentAncestors)))
					{
						unset($sections[$id]);
					}
				}
				$this->sectionList = $sections;

				if (count($this->sectionList))
				{
					echo $this->renderIncludeFile($this);
				}
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
