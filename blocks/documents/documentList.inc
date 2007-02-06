<?php
/**
 * @copyright Copyright (C) 2006 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 */
/*
	$this->documentList
	$this->title
*/
	if (userHasRole('Content Creator'))
	{
		echo "
		<div class=\"contextualMenu\">
			<span class=\"title\">Create New:</span>
			<ul>
		";
				$list = new DocumentTypeList();
				$list->find();
				foreach($list as $type)
				{
					echo "<li><button type=\"button\" onclick=\"window.open('".BASE_URL."/documents/addDocument.php?documentType_id={$type->getId()}');\">$type</button></li>";
				}
		echo "
			</ul>
		</div>
		";
	}
?>
<div class="interfaceBox">
	<div class="titleBar"><?php echo $this->title; ?>
	</div>
	<table>
	<thead>
		<tr><th></th>
			<th>Title</th>
			<th>Created</th>
			<th>Published</th>
			<th>Retired</th>
		</tr>
	</thead>
	<tbody>
	<?php
		foreach($this->documentList as $document)
		{
			if ($document->permitsEditingBy($_SESSION['USER'])) { $editButton = "<button type=\"button\" class=\"editSmall\" onclick=\"window.open('".BASE_URL."/documents/updateDocument.php?document_id={$document->getId()}');\">Edit</button>"; }
			else { $editButton = ""; }

			list($creationDate,$creationTime) = explode(" ",$document->getCreated());
			if ($document->getRetireDate()) { $retireDate = $document->getRetireDate(); }
			else
			{
				if ($document->permitsEditingBy($_SESSION['USER']))
				{
					$retireDate = "<button type=\"button\" class=\"retire\" onclick=\"document.location.href='".BASE_URL."/documents/retireDocument.php?document_id={$document->getId()}';\">Retire</button>";
				}
			}
			echo "
			<tr><td>$editButton</td>
				<td><a href=\"".BASE_URL."/documents/viewDocument.php?document_id={$document->getId()}\">{$document->getTitle()}</a></td>
				<td>$creationDate</td>
				<td>{$document->getPublishDate()}</td>
				<td>$retireDate</td>
			</tr>
			";
		}
	?>
	</tbody>
	</table>
</div>