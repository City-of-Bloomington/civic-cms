<?php
/**
 * @copyright Copyright (C) 2008 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
?>
<fieldset><legend>Alerts</legend>
	<p>Choose an alert type.</p>
	<select name="alertType_id" id="alertType_id">
	<option></option>
	<?php
		$current_id = $this->widget->alertType->getId();

		$list = new AlertTypeList();
		$list->find();
		foreach($list as $type)
		{
			$name = View::escape($type->getName());
			$selected = $current_id==$type->getId() ? 'selected="selected"' : '';
			echo "<option value=\"{$type->getId()}\" $selected>$name</option>";
		}
	?>
	</select>
</fieldset>
