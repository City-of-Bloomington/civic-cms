<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param ImageList $this->imageList
 * @param Department $this->department
 */
?>
<h2><?php echo $this->department; ?></h2>
<script type="text/javascript">
	function selectImage(url,width,height,alt)
	{
		window.opener.SetUrl( url, width, height, alt);
		self.close();
	}
</script>
<?php
	foreach($this->imageList as $image)
	{
		echo "
		<div class=\"thumbnail\">
			<a href=\"{$image->getURL()}\" onclick=\"selectImage('{$image->getURL()}',{$image->getWidth()},{$image->getHeight()},'{$image->getTitle()}');return false;\">
			<img src=\"".BASE_URL."/media/thumbnail.php?media_id={$image->getId()}\" alt=\"{$image->getTitle()}\" />
			{$image->getFilename()}</a>
		</div>
		";
	}
?>