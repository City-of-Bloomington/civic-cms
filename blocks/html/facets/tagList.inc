<?php
/**
 * @copyright Copyright (C) 2006,2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param TagList $this->tagList
 * @param string $this->title
 * @param TagGroup $this->tagGroup (optional)
 */
?>
<div class="interfaceBox">
	<div class="titleBar">
		<?php
			$url = new URL(BASE_URL.'/tags/updateTagGroup.php');
			if (isset($this->tagGroup))
			{
				if (userHasRole(array('Administrator','Webmaster')))
				{
					$url->parameters['tagGroup_id'] = $this->tagGroup->getId();
					echo "<button type=\"button\" class=\"editSmall\" onclick=\"document.location.href='$url';\">Add</button>";
				}
			}
			echo View::escape($this->title);
		?>
	</div>
	<ul><?php
			foreach($this->tagList as $tag)
			{
				echo '<li>';
				if (userHasRole(array('Administrator','Webmaster')))
				{
					echo "
					<button type=\"button\" class=\"editSmall\" onclick=\"document.location.href='".BASE_URL."/tags/updateTag.php?tag_id={$tag->getId()}';\">Edit</button>
					<button type=\"button\" class=\"deleteSmall\" onclick=\"FRAMEWORK.deleteConfirmation('".BASE_URL."/tags/deleteTag.php?tag_id={$tag->getId()}');\">Delete</button>
					";
				}

				$name = View::escape($tag->getName());
				echo "<a href=\"".BASE_URL."/tags/viewTag.php?tag_id={$tag->getId()}\">$name</a></li>";
			}
		?>
	</ul>
</div>
