<?php
/**
 * @copyright Copyright (C) 2006 Cliff Ingham. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 */
	function listSections($sectionList)
	{
		foreach($sectionList as $section)
		{
			echo "<li><a href=\"".BASE_URL."/sections/viewSection.php?section_id={$section->getId()}\">";
			echo View::sanitizeString($section->getName());
			echo "</a>";
			if ($section->hasChildren())
			{
				echo "<ul>";
				listSections($section->getChildren());
				echo "</ul>";
			}
			echo "</li>";
		}
	}
?>
<div id="sidebar">
	<div>
		<div class="titleBar"><a href="<?php echo BASE_URL; ?>/sections">Sections</a></div>
		<ul>
			<?php
				$sections = new SectionList(array("parent_id"=>1));
				listSections($sections);
			?>
		</ul>
	</div>
	<?php
		if (isset($_SESSION['USER']))
		{
			if (in_array("Administrator",$_SESSION['USER']->getRoles())) { include(APPLICATION_HOME."/includes/sidebarBoxes/Administrator.inc"); }
			if (in_array("Webmaster",$_SESSION['USER']->getRoles())) { include(APPLICATION_HOME."/includes/sidebarBoxes/Webmaster.inc"); }
		}

		if (isset($this->widgets)) { foreach($this->widgets as $widget) { $widget->render(); } }
	?>
</div>