<?php
/**
 * @copyright Copyright (C) 2006 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 */
/*
	$this->document
	$this->FCKeditor
*/
?>
<form method="post" action="<?php echo $_SERVER['PHP_SELF']; ?>">
	<fieldset><legend>Document Info</legend>
	<input name="document_id" type="hidden" value="<?php echo $this->document->getId(); ?>" />

	<?php $this->FCKeditor->create(); ?>

	</fieldset>
</form>