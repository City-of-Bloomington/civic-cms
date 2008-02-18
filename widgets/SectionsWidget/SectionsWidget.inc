<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
class SectionsWidget extends Widget
{
	protected $section;
	protected $currentSection;

	public function __construct()
	{
		$this->className = 'SectionsWidget';
		$this->displayName = 'Sections';
		$this->includeFile = 'sidebar.inc';
		$this->description = 'Lists the sub-sections for the current section';
	}

	public function render($template)
	{
		if (isset($template->document))
		{
			$ancestors = $template->currentAncestors;
			if (count($ancestors))
			{
				$this->currentSection = end($ancestors);
				$path = array_reverse($ancestors);
				foreach($path as $section)
				{
					if ($section->hasChildren())
					{
						$this->section = $section;
						break;
					}
				}
			}
		}
		# If we can't figure out where the user is, just display the top
		# level navigation
		if (!$this->section) { $this->section = new Section(1); }
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
