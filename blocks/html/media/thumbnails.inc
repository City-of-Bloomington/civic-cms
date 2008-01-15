<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param ImageList $this->imageList
 * @param Department $this->department
 * @param Image $this->image (optional) The chosen or Uploaded Image
 */
$department = View::escape($this->department->getName());
echo "
<h1>Choose an existing image</h1>
<h2>$department</h2>
<p>Copy the image link that you want, and paste it into your document.</p>
";

foreach($this->imageList as $image)
{
	$title = htmlspecialchars($image->getTitle(),ENT_QUOTES);
	echo "
	<span class=\"image thumbnail\">
		<a href=\"{$image->getURL()}\" onclick=\"insert('{$image->getId()}');return false;\">
			<img src=\"".BASE_URL."/media/media.php?media_id={$image->getId()};size=thumbnail\" alt=\"$title\" />
		</a>
		<span class=\"caption\">{$image->getId()}</span>
	</span>
	";
}
?>
<script type="text/javascript">
function insert(media_id)
{
	window.opener.handleSelection(media_id);
	self.close();
}
</script>