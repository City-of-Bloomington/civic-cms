<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param ImageList $this->imageList
 * @param Department $this->department
 * @param Image $this->image (optional) The chosen or Uploaded Image
 */
include APPLICATION_HOME.'/includes/editors/'.EDITOR.'/filebrowser_init.inc';
if (isset($this->image))
{
	# If they've uploaded or chosen an image, fire off the
	# javascript necessary to get the WYSIWYG editor to take the image
	$title = View::escape($this->image->getTitle());
	echo "
	<script type=\"text/javascript\">
		selectImage('{$this->image->getURL()}','$title');
	</script>
	";
}
else
{
	$department = View::escape($this->department->getName());
	echo "
	<h2>Choose an existing image</h2>
	<h3>$department</h3>
	";

	foreach($this->imageList as $image)
	{
		$callback = getFilebrowserCallback($image);
		$title = htmlspecialchars($image->getTitle(),ENT_QUOTES);
		echo "
		<div class=\"thumbnail\">
			<a href=\"{$image->getURL()}\" onclick=\"$callback\">
			<img src=\"".BASE_URL."/media/thumbnail.php?media_id={$image->getId()}\" alt=\"$title\" />
			{$image->getFilename()}</a>
		</div>
		";
	}
}
?>
