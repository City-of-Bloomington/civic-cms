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
	<div class="titleBar">
		<?php
			echo $this->title;
			include APPLICATION_HOME.'/blocks/html/documents/addDocumentToolbar.inc';
		?>
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
					new URL(BASE_URL."/documents/updateDocument.php?document_id={$document->getId()};lang=$_SESSION[LANGUAGE]") :
					new URL(BASE_URL.'/documents/viewDocument.php?document_id='.$document->getId());
			$url->parameters['tab'] = 'info';

			$modifiedBy = substr($document->getModifiedByUser()->getFirstname(),0,1).substr($document->getModifiedByUser()->getLastname(),0,1);

			$partialTitle = substr($document->getTitle(),0,20);

			echo "
			<tr><td style=\"width:100px; white-space:nowrap; overflow:hidden;\">
					<a href=\"$url\" onclick=\"window.open('$url');return false;\" title=\"{$document->getTitle()}\">$partialTitle</a></td>
			";
			if ($document->permitsEditingBy($_SESSION['USER']))
			{
				# Show all the editing buttons
				#$url->parameters['tab'] = 'attachments';
				# <a href=\"$url\" onclick=\"window.open('$url');return false;\">Attachments</a>
				$retireButton = !$document->getRetireDate() ? "<a href=\"".BASE_URL."/documents/retireDocument.php?document_id={$document->getId()}\">Retire</a>" : "";
				$watch = $_SESSION['USER']->hasWatch($document) ? "<a href=\"".BASE_URL."/documents/removeWatch.php?document_id={$document->getId()}\">Unwatch</a>" : "<a href=\"".BASE_URL."/documents/addWatch.php?document_id={$document->getId()}\">Watch</a>";

				echo "
				<td><a href=\"".BASE_URL."/documents/viewDocument.php?document_id={$document->getId()}\" onclick=\"window.open('".BASE_URL."/documents/viewDocument.php?document_id={$document->getId()}');return false;\">View</a>
					<a href=\"".BASE_URL."/documents/deleteDocument.php?document_id={$document->getId()}\" onclick=\"FRAMEWORK.deleteConfirmation('".BASE_URL."/documents/deleteDocument.php?document_id={$document->getId()}');return false;\">Delete</a>
					$retireButton
					$watch
				</td>
				";
			}
			else { echo "<td></td>"; }
			echo "
				<td>{$document->getCreated('%D')}</td>
				<td>{$document->getPublishDate('%D')}</td>
				<td>{$document->getModified('%D')}</td>
				<td>$modifiedBy</td>
				<td>{$document->getRetireDate('%D')}</td>
			";

			echo "</tr>";
		}
	?>
	</tbody>
	</table>
</div>