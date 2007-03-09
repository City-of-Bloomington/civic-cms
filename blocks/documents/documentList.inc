<?php
/**
 * @copyright Copyright (C) 2006 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 */
/*
	$this->documentList
	$this->title
*/
?>
<div class="interfaceBox">
	<div class="titleBar"><?php echo $this->title; ?>
	</div>
	<table>
	<thead>
		<tr>
		<?php
			$url = new URL($_SERVER['REQUEST_URI']);
			$url->parameters['sort'] = 'title'; echo "<th><a href={$url->getURL()}>Title</a></th>";
			$url->parameters['sort'] = 'created desc'; echo "<th><a href={$url->getURL()}>Created</a></th>";
			$url->parameters['sort'] = 'publishDate desc'; echo "<th><a href={$url->getURL()}>Published</a></th>";
			$url->parameters['sort'] = 'modified desc'; echo "<th><a href={$url->getURL()}>Modified</a></th>";
			echo "<th>By</th>";
			$url->parameters['sort'] = 'retireDate desc'; echo "<th><a href={$url->getURL()}>Retired</a></th>";
		?>
			<th></th>
		</tr>
	</thead>
	<tbody>
	<?php
		foreach($this->documentList as $document)
		{
			$url = $document->permitsEditingBy($_SESSION['USER']) ?
					BASE_URL."/documents/updateDocument.php?document_id={$document->getId()};lang=$_SESSION[LANGUAGE]" :
					BASE_URL.'/documents/viewDocument.php?document_id='.$document->getId();

			$modifiedBy = substr($document->getModifiedByUser()->getFirstname(),0,1).substr($document->getModifiedByUser()->getLastname(),0,1);

			echo "
			<tr><td style=\"width:100px; white-space:nowrap; overflow:hidden;\">
					<a href=\"$url\" onclick=\"window.open('$url');return false;\">{$document->getTitle()}</a></td>
				<td>{$document->getCreated('%D')}</td>
				<td>{$document->getPublishDate('%D')}</td>
				<td>{$document->getModified('%D')}</td>
				<td>$modifiedBy</td>
				<td>{$document->getRetireDate('%D')}</td>
			";
			if ($document->permitsEditingBy($_SESSION['USER']))
			{
				# Show all the editing buttons
				$retireButton = !$document->getRetireDate() ? "<a href=\"".BASE_URL."/documents/retireDocument.php?document_id={$document->getId()}\">Retire</a>" : "";
				echo "
				<td><a href=\"".BASE_URL."/documents/viewDocument.php?document_id={$document->getId()}\" onclick=\"window.open('".BASE_URL."/documents/viewDocument.php?document_id={$document->getId()}');return false;\">View</a>
					<a href=\"/documents/attachments.php?document_id={$document->getId()}\">Attachments</a>
					$retireButton
				</td>
				";
			}
			else { echo "<td></td>"; }

			echo "</tr>";
		}
	?>
	</tbody>
	</table>
</div>
