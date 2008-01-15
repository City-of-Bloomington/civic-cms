<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param array $this->media An array of media objects to display
 */
?>
<div class="widget">
	<h1><?php echo View::escape($this->displayName); ?></h1>
	<?php
		if (count($this->media))
		{
			echo '<ul>';
			foreach($this->media as $media)
			{
				echo "<li><img src=\"".BASE_URL."/media/media.php?size=thumbnail;media_id={$media->getId()}\" class=\"image thubnail\" /></li>";
			}
			echo '</ul>';
		}
	?>
</div>
