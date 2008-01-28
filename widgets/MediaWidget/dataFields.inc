<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param Widget $this->widget
 */
?>
<fieldset><legend>Select Media</legend>
<p>Enter the IDs or filenames of the Media you want include.</p>
<div>
	<button type="button" class="browse" onclick="window.open('<?php echo BASE_URL; ?>/media/imageBrowser.php');">Browse Images</button>
	<script type="text/javascript">
	// This declares the function that will handle the return value from the
	// image browser.  The image browser will call this function with the
	// media_id of the image the user selected
	function handleSelection(media_id)
	{
		media = document.getElementById('media');
		if (media.value) { media.value = media.value+','+media_id; }
		else { media.value = media_id; }
	}
	</script>
</div>
<div><?php
		$ids = array();
		foreach($this->widget->media as $media)
		{
			$ids[] = $media->getId();
		}
		$ids = implode(',',$ids);
	?>
	<input name="media" id="media" size="60" value="<?php echo $ids; ?>" />
</div>
</fieldset>
