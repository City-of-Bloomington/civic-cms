<?php
/**
 * @copyright Copyright (C) 2006 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 */
?>
<form method="get" action="<?php echo BASE_URL; ?>/documents/updateDocument.php">
<fieldset>
	<input name="return_url" type="hidden" value="<?php echo "http://$_SERVER[SERVER_NAME]$_SERVER[REQUEST_URI]"; ?>" />
	<select name="documentType_id" onchange="this.form.submit();">
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
