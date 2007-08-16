<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param MediaList $this->mediaList
 * @param Department $this->department ( optional )
 */
	$title = isset($this->department) ? View::escape($this->department->getName()) : '';
?>
<script type="text/javascript">
	function selectAttachment(media_id)
	{
		window.opener.addAttachment(media_id);
		self.close();
	}
</script>
<div class="interfaceBox">
	<div class="titleBar"><?php echo $title; ?> Media</div>
	<table>
	<tr>
	<?php
		$url = new URL($_SERVER['REQUEST_URI']);
		$url->parameters['sort'] = 'filename'; echo "<th><a href=\"{$url->getURL()}\">Filename</a></th>";
		$url->parameters['sort'] = 'title'; echo "<th><a href=\"{$url->getURL()}\">Title</a></th>";
		$url->parameters['sort'] = 'uploaded desc'; echo "<th><a href=\"{$url->getURL()}\">Uploaded</a></th>";
	?>
	</tr>
	<?php
		foreach($this->mediaList as $media)
		{
			$url = new URL($_SERVER['REQUEST_URI']);
			$url->parameters['department_id'] = $media->getDepartment_id();

			$title = View::escape($media->getTitle());
			$department = View::escape($media->getDepartment()->getName());
			echo "
			<tr><td><a href=\"{$media->getURL()}\" class=\"{$media->getExtension()}\" onclick=\"selectAttachment({$media->getId()}); return false;\">
					{$media->getFilename()}</a>
				</td>
				<td>$title</td>
				<td>{$media->getUploaded('%D')}</td>
			</tr>
			";
		}
	?>
	</table>
</div>
