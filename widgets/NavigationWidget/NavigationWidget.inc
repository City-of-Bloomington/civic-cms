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
						$currentlyMatchedSections = 0;
						foreach($ancestors as $vector)
						{
							# Choose the best matched ancestral line we can find
							# It will be the line with the most sections in common with our previous one
							if (count($_SESSION['vector']) < count($vector))
							{
								# To be a candidate, all sections in SESSION[vector] must be in the vector
								$count = count(array_intersect(array_keys($_SESSION['vector']),array_keys($vector)));
								if ($count < count($_SESSION['vector'])) { $count = 0; }
							}
							else
							{
								# To be a candidate, all sections in $vector must be in SESSION[vector]
								$count = count(array_intersect(array_keys($vector),array_keys($_SESSION['vector'])));
								if ($count < count($vector)) { $count = 0; }
							}

							if ($count > $currentlyMatchedSections)
							{
								$this->ancestors = $vector;
								$currentlyMatchedSections = $count;
							}
						}
					}

					# If we weren't able to find a vector, just use the first available
					if (!$this->ancestors)
					{
						# If we don't have any ancestors, just show the top level navigation
						if (count($ancestors)) { $this->ancestors = $ancestors[0]; }
					}

					# Remember the ancestral line we're on
					$this->ancestors[$section->getId()] = $section;
					$_SESSION['vector'] = $this->ancestors;
				}
			}

			# If all else fails, just render the top level sections
			if (!isset($this->ancestors))
			{
				$this->section = new Section(1);
				$this->ancestors = array(1=>$this->section);
			}

			$this->renderIncludeFile($this);
		}
	}
?>