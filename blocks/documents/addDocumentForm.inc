<?php
/**
 * @copyright Copyright (C) 2006 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 */
/*
	$this->section
	$this->FCKeditor
*/
?>
<form method="post" action="<?php echo $_SERVER['PHP_SELF']; ?>">
	<fieldset><legend>Document Info</legend>
	<input name="section_id" type="hidden" value="<?php echo $this->section->getId(); ?>" />

	<p><?php echo $this->section->getDepartment()->getName(); ?></p>

	<?php $this->FCKeditor->create(); ?>

	</fieldset>

	<fieldset><legend>Sections</legend>
	</fieldset>

	<fieldset><legend>Facets</legend>
	</fieldset>
</form>