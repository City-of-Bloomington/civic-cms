<?php
/**
 * @copyright Copyright (C) 2008 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
?>
<fieldset><legend>Top Documents</legend>
	<p>Choose a document type.</p>
	<select name="documentType_id" id="documentType_id">
	<option></option>
	<?php
		$current_id = $this->widget->documentType->getId();

		$list = new DocumentTypeList();
		$list->find();
		foreach($list as $type)
		{
			$name = View::escape($type->getType());
			$selected = $current_id==$type->getId() ? 'selected="selected"' : '';
			echo "<option value=\"{$type->getId()}\" $selected>$name</option>";
		}
	?>
	</select>
</fieldset>
