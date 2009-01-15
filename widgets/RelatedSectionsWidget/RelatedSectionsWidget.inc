<?php
/**
 * Lists any of the multiple sections for the current document
 *
 * If the document is the homepage of a section, we also
 * include the parents of the section if there are multiple parents
 *
 * @copyright Copyright (C) 2007-2009 City of Bloomington, Indiana
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
	 * @param Template $template
	 */
	public function render($template)
	{
		$this->sectionList = array();

		if (isset($template->document)) {
			foreach ($template->document->getSections() as $section) {
				// If this is a homepage, add the section's parents as Related Sections
				if (count($section->getParents() > 1)) {
					foreach ($section->getParents() as $parent) {
						$this->sectionList[$parent->getId()] = $parent;
					}
				}

				// Add all the document's sections as Related Sections
				if (!array_key_exists($section->getId(),$this->sectionList)) {
					$this->sectionList[$section->getId()] = $section;
				}
			}

			// Only display this block if there's more than one Related Section
			if (count($this->sectionList) > 1) {
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
