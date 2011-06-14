<?php
/**
 * @copyright Copyright (C) 2007-2008 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param Section $this->section
 */
?>
<div class="contextualMenu">
<ul><li><a class="editSmall button" href="<?php echo BASE_URL; ?>/sections/updateSection.php?section_id=<?php echo $this->section->getId(); ?>">Edit</a></li>
	<li><button type="button"
				class="deleteSmall"
				onclick="FRAMEWORK.deleteConfirmation('<?php echo BASE_URL; ?>/sections/deleteSection.php?section_id=<?php echo $this->section->getId(); ?>');">
			Delete
		</button>
	</li>
	<li><a class="widgets" href="<?php echo BASE_URL; ?>/sections/updateWidgets.php?section_id=<?php echo $this->section->getId(); ?>">Widgets</a></li>
</ul>
</div>
