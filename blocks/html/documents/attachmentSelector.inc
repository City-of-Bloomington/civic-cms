<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param AttachmentList $this->attachmentList
 */
?>
<script type="text/javascript">
	function selectAttachment(media_id)
	{
		window.opener.addAttachment(media_id);
		self.close();
	}
</script>
<div class="interfaceBox">
	<div class="titleBar">Attachments</div>
	<table>
	<tr>
	<?php
		$url = new URL($_SERVER['REQUEST_URI']);
		$url->parameters['sort'] = 'filename'; echo "<td><a href=\"{$url->getURL()}\">Filename</a></td>";
		$url->parameters['sort'] = 'title'; echo "<td><a href=\"{$url->getURL()}\">Title</a></td>";
		$url->parameters['sort'] = 'department_id'; echo "<td><a href=\"{$url->getURL()}\">Department</a></td>";
		$url->parameters['sort'] = 'uploaded desc'; echo "<td><a href=\"{$url->getURL()}\">Uploaded</a></td>";
	?>
	</tr>
	<?php
		foreach($this->attachmentList as $attachment)
		{
			$url = new URL($_SERVER['REQUEST_URI']);
			$url->parameters['department_id'] = $attachment->getDepartment_id();

			$title = View::escape($attachment->getTitle());
			$department = View::escape($attachment->getDepartment()->getName());
			echo "
			<tr><td><a href=\"{$attachment->getURL()}\" class=\"{$attachment->getExtension()}\" onclick=\"selectAttachment({$attachment->getId()}); return false;\">
					{$attachment->getFilename()}</a>
				</td>
				<td>$title</td>
				<td><a href=\"{$url->getURL()}\">$department</a></td>
				<td>{$attachment->getUploaded('%D')}</td>
			</tr>
			";
		}
	?>
	</table>
</div>
