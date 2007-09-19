<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param Media $this->media
 */
	$title = View::escape($this->media->getTitle());
?>
<div class="interfaceBox">
	<div class="titleBar">
	<?php
		if ($this->media->permitsEditingBy($_SESSION['USER']))
		{
			echo "
			<button type=\"button\" class=\"editSmall\" onclick=\"document.location.href='".BASE_URL."/media/updateMedia.php?media_id={$this->media->getId()}';\">Edit</button>
			<button type=\"button\" class=\"deleteSmall\" onclick=\"FRAMEWORK.deleteConfirmation('".BASE_URL."/media/deleteMedia.php?media_id={$this->media->getId()}');\">Delete</button>
			";
		}
		echo $title;
	?>
	</div>
	<table>
	<tr><th>Filename</th>
		<td><?php echo "<a href=\"{$this->media->getURL()}\">{$this->media->getFilename()}</a>"; ?></td></tr>
	<tr><th>Title</th>
		<td><?php echo $title; ?></td></tr>
	<tr><th>Mime Type</th>
		<td><?php echo $this->media->getMime_type(); ?></td></tr>
	<tr><th>Media Type</th>
		<td><?php echo $this->media->getMedia_type(); ?></td></tr>
	<tr><th>Last Modified By</th>
		<td><?php echo $this->media->getUser()->getUsername(); ?></td></tr>
	<tr><th>Uploaded</th>
		<td><?php echo $this->media->getUploaded('%D'); ?></td></tr>
	<tr><th>Department</th>
		<td><?php echo View::escape($this->media->getDepartment()); ?></td></tr>
	<tr><th>Description</th>
		<td><?php echo View::escape($this->media->getDescription()); ?></td></tr>
	</table>
	<?php
		if ($this->media->getMedia_type()==='image')
		{
			$title = addslashes($title);
			echo "<img src=\"{$this->media->getURL()}\" alt=\"$title\" />";
		}
	?>
</div>