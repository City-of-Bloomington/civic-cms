<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
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
	$title = View::escape($image->getTitle());
	$width = $image->getWidth('thumbnail');
	$height = $image->getHeight('thumbnail');
	$src = $image->getURL('thumbnail');

	echo "
	<span class=\"image thumbnail\" style=\"width:{$width}px;height:150px;float:left;\">
		<a href=\"{$image->getURL()}\" onclick=\"insert('{$image->getId()}');return false;\">
			<img src=\"$src\" width=\"$width\" height=\"$height\" alt=\"$title\" />
		</a>
		<span class=\"caption\">{$image->getInternalFilename()}</span>
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
