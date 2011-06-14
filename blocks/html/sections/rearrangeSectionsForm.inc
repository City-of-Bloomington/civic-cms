<?php
/**
 * @copyright Copyright (C) 2006,2007,2008 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param Section $this->section
 */
	function listEditableSections($section)
	{
		foreach($section->getChildren() as $section)
		{
			$name = View::escape($section->getName());
			echo "
			<li><input name=\"node[{$section->getNode_id()}]\" id=\"node-{$section->getNode_id()}\" size=\"2\" maxlength=\"2\" value=\"{$section->getPlacement()}\" />
				<label for=\"node-{$section->getNode_id()}\">
					<a href=\"{$section->getDocument()->getURL()}\">$name</a>
				</label>
			";
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
<p>The site will use the numbers you give to order the sections in relation to their siblings.  You can use any number from 0-99.
Un-numbered sections may be ordered differently each time they are displayed.</p>
<form method="post" action="<?php echo $_SERVER['SCRIPT_NAME']; ?>">
<fieldset><legend>Sections Layout</legend>
	<ul style="list-style-type:none">
		<?php listEditableSections($this->section); ?>
	</ul>

	<button type="submit" class="save">Save</button>
	<a class="done" href="home.php">Done</a>
</fieldset>
</form>
