<?php
/*
	$this->section
*/
	function listEditableSections($section)
	{
		foreach($section->getChildren() as $placement=>$section)
		{
			echo "<li>";
			if (userHasRole("Webmaster")) { echo "<button type=\"button\" class=\"editSmall\" onclick=\"document.location.href='".BASE_URL."/sections/updateSection.php?section_id={$section->getId()}';\">Edit</button>"; }
			echo "<a href=\"".BASE_URL."/documents/viewDocument.php?document_id={$section->getDocument_id()}\">";
			echo View::sanitizeString($section->getName());
			echo "</a>";
			if ($section->hasChildren())
			{
				echo "<ul>";
				listEditableSections($section);
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
			<ul><li><a href=\"".BASE_URL."/sections/addSection.php\">Add</a></li>
				<li><a href=\"".BASE_URL."/sections/rearrangeSections.php\">Rearrange</a></li>
			</ul>
		</div>
		";
	}
	else { echo "<div class=\"titleBar\">Sections</div>"; }
?>
	<ul>
		<?php listEditableSections($this->section); ?>
	</ul>
</div>