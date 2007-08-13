<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
	class NavigationWidget extends Widget
	{
		protected $section;
		protected $document;
		protected $ancestors;

		public function __construct()
		{
			$this->className = 'NavigationWidget';
			$this->displayName = 'Navigation';
			$this->includeFile = 'sidebar.inc';
			$this->description = 'Displays a two-level, collapsing navigation for Sections';
		}

		public function render($template)
		{
			global $section;
			if ($section)
			{
				$this->section = $section;

				if (isset($template->document))
				{
					$this->document = $template->document;

					# Figure out which ancestral line we want to display in the navigation
					$ancestors = $this->section->getAncestors();
					if (isset($_SESSION['vector']))
					{
						foreach($ancestors as $vector)
						{
							if (count($_SESSION['vector']) < count($vector))
							{
								# If all of the sections are in this vector, use this one
								$intersect = array_intersect(array_keys($_SESSION['vector']),array_keys($vector));
								if (count($intersect)==count($_SESSION['vector'])) { $this->ancestors = $vector; }
							}
							else
							{
								$intersect = array_intersect(array_keys($vector),array_keys($_SESSION['vector']));
								if (count($intersect)==count($vector)) { $this->ancestors = $vector; }
							}
						}
					}

					# If we weren't able to find a vector, just use the first available
					if (!$this->ancestors)
					{
						# If we don't have any ancestors, just show the top level navigation
						if (count($ancestors)) { $this->ancestors = $ancestors[0]; }
						else { $this->ancestors = array(new Section(1)); }
					}

					# Remember the ancestral line we've chosen
					$_SESSION['vector'] = $this->ancestors;

					$this->renderIncludeFile($this);
				}
			}
		}
	}
?>