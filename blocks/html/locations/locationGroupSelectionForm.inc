<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param LocationGroup $this->locationGroup
 */
?>
<h2>Locations</h2>
<form method="get" action="<?php echo $_SERVER['PHP_SELF']; ?>">
<fieldset><legend>Location Group</legend>
	<select name="locationGroup_id" onchange="this.form.submit();">
		<option value="null">Other</option>
	<?php
		$list = new LocationGroupList();
		$list->find();
		foreach($list as $group)
		{
			$name = View::escape($group->getName());

			if (isset($this->locationGroup) && $this->locationGroup->getId()==$group->getId()) { $selected = 'selected="selected"'; }
			else { $selected = ''; }

			echo "<option value=\"{$group->getId()}\" $selected>$name</option>\n";
		}
	?>
	</select>
</fieldset>
</form>
