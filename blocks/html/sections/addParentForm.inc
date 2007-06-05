<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param Section $this->section
 */
	$url = new URL($_SERVER['PHP_SELF']);
	$url->parameters['section_id'] = $this->section->getId();

	function listSections($parent,$currentSection,$url)
	{
		foreach($parent->getChildren() as $section)
		{
			$name = View::escape($section->getName());
			$url->parameters['parent_id'] = $section->getId();
			echo "<li>";

				if ($currentSection->getId() != $section->getId() && !$currentSection->hasParent($section))
				{
					echo "
					<a href=\"$url\">$name</a>
					<button type=\"button\" class=\"addSmall\" onclick=\"document.location.href='$url';\">Add</button>
					";
				}
				else { echo "<a href=\"#\">$name</a>"; }

			if ($section->hasChildren())
			{
				echo "<ul>";
				listSections($section,$currentSection,$url);
				echo "</ul>";
			}

			echo "</li>";
		}
	}
?>
<div class="interfaceBox">
	<div class="titleBar">Add Parents</div>

	<p>Choose parents for this section:</p>
	<ul class="expandable">
		<?php
			# Start with the top section
			$section = new Section(1);
			listSections($section,$this->section,$url);
		?>
	</ul>
	<script type="text/javascript" src="<?php echo BASE_URL; ?>/tree.js"></script>
</div>