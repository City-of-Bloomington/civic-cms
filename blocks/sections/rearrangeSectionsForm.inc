<?php
/*
	$this->section
*/
	function listEditableSections($section)
	{
		foreach($section->getChildren() as $section)
		{
			echo "
			<li><input name=\"node[{$section->getNode_id()}]\" id=\"node-{$section->getNode_id()}\" size=\"2\" maxlength=\"2\" value=\"{$section->getPlacement()}\" />
				<label for=\"node-{$section->getNode_id()}\">
					<a href=\"".BASE_URL."/sections/viewSection.php?section_id={$section->getId()}\">
			";
					echo View::sanitizeString($section->getName());
				echo "</a></label>";
				if ($section->hasChildren())
				{
					echo "<ul style=\"list-style-type:none\">";
					listEditableSections($section);
					echo "</ul>";
				}
			echo "</li>";
		}
	}
?>
<h1>Reorder the Sections</h1>
<form method="post" action="<?php echo $_SERVER['PHP_SELF']; ?>">
<fieldset><legend>Sections Layout</legend>
	<ul style="list-style-type:none">
		<?php listEditableSections($this->section); ?>
	</ul>

	<button type="submit" class="submit">Submit</button>
	<button type="button" class="done" onclick="document.location.href='home.php';">Done</button>
</fieldset>
</form>