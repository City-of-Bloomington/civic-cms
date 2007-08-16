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
<div class="interfaceBox">
	<div class="titleBar"><?php echo $title; ?> Media</div>
	<table>
	<tr><th></th>
	<?php
		$url = new URL($_SERVER['REQUEST_URI']);
		$url->parameters['sort'] = 'filename'; echo "<th><a href=\"{$url->getURL()}\">Filename</a></th>";
		$url->parameters['sort'] = 'title'; echo "<th><a href=\"{$url->getURL()}\">Title</a></th>";
		$url->parameters['sort'] = 'department_id'; echo "<th><a href=\"{$url->getURL()}\">Department</a></th>";
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

			if (userHasRole(array('Administrator','Webmaster')))
			{
				$deleteButton = "<button type=\"button\" class=\"deleteSmall\" onclick=\"FRAMEWORK.deleteConfirmation('".BASE_URL."/media/deleteMedia.php?media_id={$media->getId()}');\">Delete</button>";
			}
			else { $deleteButton = ''; }
			echo "
			<tr><td>$deleteButton</td>
				<td><a href=\"{$media->getURL()}\" class=\"{$media->getExtension()}\">{$media->getFilename()}</a></td>
				<td>$title</td>
				<td><a href=\"{$url->getURL()}\">$department</a></td>
				<td>{$media->getUploaded('%D')}</td>
			</tr>
			";
		}
	?>
	</table>
</div>
