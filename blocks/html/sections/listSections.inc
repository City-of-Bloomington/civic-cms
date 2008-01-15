<?php
/**
 * @copyright Copyright (C) 2006,2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param Section $this->section
 */
	include_once APPLICATION_HOME.'/includes/js/tree.inc';

	function listSections($parent)
	{
		foreach($parent->getChildNodes() as $node)
		{
			$section = $node->getSection();

			$name = View::escape($section->getName());
			if (userHasRole(array('Administrator','Webmaster')))
			{
				echo "
				<li class=\"closed\">
					<a href=\"".BASE_URL."/sections/sectionInfo.php?section_id={$section->getId()}\">$name</a>
					<button type=\"button\" class=\"info\" onclick=\"document.location.href='".BASE_URL."/sections/sectionInfo.php?section_id={$section->getId()}';\">Info</button>
					<button type=\"button\" class=\"view\" onclick=\"document.location.href='".BASE_URL."/sections/viewSection.php?section_id={$section->getId()}';\">View</button>
				";
			}
			else
			{
				echo "
				<li class=\"closed\">
					<a href=\"{$section->getURL()}\">$name</a>
				";
			}

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
	if (userHasRole(array('Administrator','Webmaster')))
	{
		echo "
		<div class=\"contextualMenu\">
			<span class=\"title\">Sections</span>
			<ul><li><a href=\"".BASE_URL."/sections/addSection.php\">Add</a></li></ul>
		</div>
		";
	}
	else { echo "<div class=\"titleBar\"><a href=\"".BASE_URL."/sections\">Sections</a></div>"; }
?>
	<ul><li>
		<?php
			# Start with the top section
			$section = new Section($this->section->getId());
			$name = View::escape($section->getName());
			if (userHasRole(array('Administrator','Webmaster')))
			{
				echo "
				<a href=\"".BASE_URL."/sections/sectionInfo.php?section_id={$section->getId()}\">$name</a>
				<button type=\"button\" class=\"info\" onclick=\"document.location.href='".BASE_URL."/sections/sectionInfo.php?section_id={$section->getId()}';\">Info</button>
				<button type=\"button\" class=\"view\" onclick=\"document.location.href='".BASE_URL."/sections/viewSection.php?section_id={$section->getId()}';\">View</button>
				<ul class=\"expandable\">
				";
			}
			else
			{
				echo "
				<a href=\"{$section->getURL()}\">$name</a>
				<ul class=\"expandable\">
				";
			}

			listSections($section);

			echo "</ul>";
		?>
		</li>
	</ul>
</div>
