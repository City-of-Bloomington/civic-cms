<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param TagGroupList $this->tagGroupList
 */
?>
<div class="interfaceBox">
	<div class="titleBar">
		<button type="button" class="addSmall" onclick="document.location.href='<?php echo BASE_URL; ?>/tags/addTagGroup.php';">Add</button>
		Tag Groups
	</div>
	<ul><?php
			foreach($this->tagGroupList as $tagGroup)
			{
				echo "
				<li><button type=\"button\" class=\"editSmall\" onclick=\"document.location.href='".BASE_URL."/tags/updateTagGroup.php?tagGroup_id={$tagGroup->getId()}';\">Edit</button>
					$tagGroup</li>
				";
			}
		?>
	</ul>
</div>
