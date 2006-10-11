<?php
/**
 * @copyright Copyright (C) 2006 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 */
/*
	$this->category
	$this->FCKeditor
*/
?>
<h1><?php echo View::sanitizeString($this->category->getName()); ?></h1>
<form method="post" action="<?php echo $_SERVER['PHP_SELF']; ?>">
<fieldset><legend>Page</legend>
	<input name="id" type="hidden" value="<?php echo $this->category->getId(); ?>" />

	<?php $this->FCKeditor->Create(); ?>

	<button type="submit" class="save">Save</button>
	<button type="button" class="cancel" onclick="document.location.href='<?php echo BASE_URL; ?>/categories/viewCategory.php?category_id=<?php echo $this->category->getId(); ?>';">Cancel</button>
</fieldset>
</form>