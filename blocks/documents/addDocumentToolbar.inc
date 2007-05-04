<?php
/**
 * @copyright Copyright (C) 2006 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 */
?>
<form method="get" action="<?php echo BASE_URL; ?>/documents/addDocument.php">
<fieldset>
	<select name="documentType_id" onchange="this.form.target='_blank';this.form.submit();">
		<option value="">Add</option>
		<?php
			$list = new DocumentTypeList();
			$list->find();
			foreach($list as $type)
			{
				echo "<option value=\"{$type->getId()}\">New $type</option>";
			}
		?>
	</select>
</fieldset>
</form>
