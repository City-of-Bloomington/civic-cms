<?php
/**
 * @copyright Copyright (C) 2006,2007,2008 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param Section $this->section
 */
	function printSectionOptions($section,$depth,$sectionToEdit,$currentSection)
	{
		$depthIndicator = str_repeat("-",$depth);
		$checked = $sectionToEdit->hasParent($section) ? "checked=\"checked\"" : "";
		echo "<li><label>";

		# Sections should not be allowed to be parents of themselves
		if ($section->getId() != $currentSection->getId())
		{
			echo "<input name=\"section[parents][{$section->getId()}]\" type=\"checkbox\" value=\"{$section->getId()}\" $checked />";
		}
		echo "$section</label></li>";
		if ($section->hasChildren())
		{
			echo "<ul>";
			foreach($section->getChildren() as $child) { printSectionOptions($child,$depth+1,$sectionToEdit,$currentSection); }
			echo "</ul>";
		}
	}
?>
<h1>Edit <?php echo $this->section; ?></h1>
<form method="post" action="<?php echo $_SERVER['PHP_SELF']; ?>">
<fieldset><legend>Section Info</legend>
	<input name="id" type="hidden" value="<?php echo $this->section->getId(); ?>" />
	<table>
	<tr><td><label for="section-name" class="required">Name</label></td>
		<td><input name="section[name]" id="section-name" size="60" value="<?php echo View::escape($this->section->getName()); ?>" /></td></tr>
	<tr><td><label for="section-nickname">Nickname</label></td>
		<td><input name="section[nickname]" id="nickname" size="60" value="<?php echo View::escape($this->section->getNickname()); ?>" /></td></tr>
	</table>
</fieldset>

<fieldset><legend>Homepage</legend>
<p>You can set the document_id that will be used as the home page for this section.</p>
<div><label for="section-document_id">Document ID</label>
	<input name="section[document_id]" id="section-document_id" size="3" value="<?php echo $this->section->getDocument_id(); ?>" />
</div>
</fieldset>

<fieldset><legend>Subscription Highlight</legend>
<p>If you make this section a Highlighted Subscription, it will show up on the special
"Subscriptions" page.</p>
<div>
<label>Highlight this subscription?</label>
<label><input name="section[highlightSubscription]" type="radio" value="yes" <?php if($this->section->isHighlightedSubscription()) echo 'checked="checked"'; ?> />Yes</label>
<label><input name="section[highlightSubscription]" type="radio" value="no" <?php if(!$this->section->isHighlightedSubscription()) echo 'checked="checked"'; ?> />No</label>
</div>
</fieldset>

<fieldset><legend class="required">Departments</legend>
	<p>Choose the departments that will be allowed to post content to this section.</p>
	<p>You must choose at least one.</p>
	<table>
	<?php
		$departments = new DepartmentList();
		$departments->find();
		foreach($departments as $department)
		{
			$name = View::escape($department->getName());
			$checked = $this->section->hasDepartment($department) ? "checked=\"checked\"" : "";
			echo "
			<tr><td><input type=\"checkbox\" name=\"section[departments][{$department->getId()}]\" id=\"section-departments-{$department->getId()}\" value=\"{$department->getId()}\" $checked /></td>
				<td><label for=\"section-departments-{$department->getId()}\">$name</label></td></tr>
			";
		}
	?>
	</table>
</fieldset>

<fieldset><legend>Submit</legend>
	<button type="submit" class="submit">Submit</button>
	<a class="cancel" href="<?php echo BASE_URL; ?>/sections/sectionInfo.php?section_id=<?php echo $this->section->getId(); ?>">Cancel</a>
</fieldset>
</form>
