<?php
/*
	$this->sectionList
*/
	if (userHasRole("Webmaster")) { $addButton = "<button type=\"button\" class=\"addSmall\" onclick=\"document.location.href='".BASE_URL."/sections/addSection.php';\">Add</button>"; }
	function listEditableSections($sectionList)
	{
		foreach($sectionList as $section)
		{
			echo "<li>";
			if (userHasRole("Webmaster")) { echo "<button type=\"button\" class=\"editSmall\" onclick=\"document.location.href='".BASE_URL."/sections/updateSection.php?section_id={$section->getId()}';\">Edit</button>"; }
			echo "<a href=\"".BASE_URL."/sections/viewSection.php?section_id={$section->getId()}\">";
			echo View::sanitizeString($section->getName());
			echo "</a>";
			if ($section->hasChildren())
			{
				echo "<ul>";
				listEditableSections($section->getChildren());
				echo "</ul>";
			}
			echo "</li>";
		}
	}
?>
<div class="interfaceBox">
	<div class="titleBar"><?php echo $addButton; ?>Sections</div>
	<ul>
		<?php listEditableSections($this->sectionList); ?>
	</ul>
</div>