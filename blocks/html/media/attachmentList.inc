<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param AttachmentList $this->attachmentList
 */
?>
<div class="interfaceBox">
	<div class="titleBar">Attachments</div>
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
		foreach($this->attachmentList as $attachment)
		{
			$url = new URL($_SERVER['REQUEST_URI']);
			$url->parameters['department_id'] = $attachment->getDepartment_id();

			$title = View::escape($attachment->getTitle());
			$department = View::escape($attachment->getDepartment()->getName());

			if (userHasRole(array('Administrator','Webmaster')))
			{
				$deleteButton = "<button type=\"button\" class=\"deleteSmall\" onclick=\"FRAMEWORK.deleteConfirmation('".BASE_URL."/media/deleteMedia.php?media_id={$attachment->getId()}');\">Delete</button>";
			}
			else { $deleteButton = ''; }
			echo "
			<tr><td>$deleteButton</td>
				<td><a href=\"{$attachment->getURL()}\" class=\"{$attachment->getExtension()}\">{$attachment->getFilename()}</a></td>
				<td>$title</td>
				<td><a href=\"{$url->getURL()}\">$department</a></td>
				<td>{$attachment->getUploaded('%D')}</td>
			</tr>
			";
		}
	?>
	</table>
</div>
