<?php
/**
 * @copyright Copyright (C) 2006 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 */
$return_url = new URL($_SERVER['SERVER_NAME'].$_SERVER['REQUEST_URI']);
?>
<form method="get" action="<?php echo BASE_URL; ?>/documents/updateDocument.php">
<fieldset>
	<input name="return_url" type="hidden" value="<?php echo $return_url; ?>" />
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
