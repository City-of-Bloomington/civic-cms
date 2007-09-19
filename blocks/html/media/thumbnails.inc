<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param ImageList $this->imageList
 * @param Department $this->department
 */
?>
<h2>Choose an existing image</h2>
<h3><?php echo $this->department; ?></h3>
<?php
	include APPLICATION_HOME.'/includes/editors/'.EDITOR.'/filebrowser_init.inc';
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
?>
