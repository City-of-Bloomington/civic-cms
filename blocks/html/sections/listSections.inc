<?php
/**
 * @copyright Copyright (C) 2006,2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param Section $this->section
 */
	function listSections($parent)
	{
		foreach($parent->getChildNodes() as $node)
		{
			$section = $node->getSection();

			$name = View::escape($section->getName());
			echo "
			<li><a href=\"".BASE_URL."/sections/sectionInfo.php?section_id={$section->getId()}\">$name</a>
				<button type=\"button\" class=\"info\" onclick=\"document.location.href='".BASE_URL."/sections/sectionInfo.php?section_id={$section->getId()}';\">Info</button>
				<button type=\"button\" class=\"view\" onclick=\"document.location.href='".BASE_URL."/sections/viewSection.php?section_id={$section->getId()}';\">View</button>
			";

			if ($section->hasChildren())
			{
				echo "<ul>";
				listSections($section);
				echo "</ul>";
			}

			echo "</li>";
		}
	}
?>
<div class="interfaceBox">
<?php
	if (userHasRole('Webmaster'))
	{
		echo "
		<div class=\"contextualMenu\">
			<span class=\"title\">Sections</span>
			<ul><li><a href=\"".BASE_URL."/sections/addSection.php\">Add</a></li></ul>
		</div>
		";
	}
	else { echo "<div class=\"titleBar\">Sections</div>"; }
?>
	<ul><li>
		<?php
			# Start with the top section
			$section = new Section($this->section->getId());
			$name = View::escape($section->getName());
			echo "
			<a href=\"".BASE_URL."/sections/sectionInfo.php?section_id={$section->getId()}\">$name</a>
			<button type=\"button\" class=\"info\" onclick=\"document.location.href='".BASE_URL."/sections/sectionInfo.php?section_id={$section->getId()}';\">Info</button>
			<button type=\"button\" class=\"view\" onclick=\"document.location.href='".BASE_URL."/sections/viewSection.php?section_id={$section->getId()}';\">View</button>
			<ul class=\"expandable\">
			";

			listSections($section);

			echo "</ul>";
		?>
		</li>
	</ul>
</div>
<script type="text/javascript" src="<?php echo BASE_URL; ?>/tree.js"></script>
