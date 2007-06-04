<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param Section $this->section
 */
?>
<div class="contextualMenu">
<ul><li><button type="button" class="editSmall" onclick="document.location.href='<?php echo BASE_URL; ?>/sections/updateSection.php?section_id=<?php echo $this->section->getId(); ?>';">Edit</button></li>
	<li><button type="button" class="deleteSmall" onclick="FRAMEWORK.deleteConfirmation('<?php echo BASE_URL; ?>/sections/deleteSection.php?section_id=<?php echo $this->section->getId(); ?>');">Delete</button></li>
	<li><button type="button" class="widgets" onclick="document.location.href='<?php echo BASE_URL; ?>/sections/updateWidgets.php?section_id=<?php echo $this->section->getId(); ?>';">Widgets</button></li>
</ul>
</div>