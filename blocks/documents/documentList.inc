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

			echo "
			<tr><td><a href=\"$url\" onclick=\"window.open('$url');return false;\">{$document->getTitle()}</a></td>
				<td>{$document->getCreated('%D')}</td>
				<td>{$document->getPublishDate('%D')}</td>
				<td>{$document->getModified('%D')}</td>
				<td>{$document->getModifiedByUser()->getUsername()}</td>
				<td>{$document->getRetireDate('%D')}</td>
			";
			if ($document->permitsEditingBy($_SESSION['USER']))
			{
				# Show all the editing buttons
				$retireButton = !$document->getRetireDate() ? "<button type=\"button\" class=\"retire\" onclick=\"document.locaation.href='';\">Retire</button>" : "";
				echo "
				<td><form method=\"get\" action=\"".BASE_URL."/documents/updateDocument.php\">
					<fieldset>
						<input name=\"document_id\" type=\"hidden\" value=\"{$document->getId()}\" />
						<select name=\"lang\" onchange=\"this.form.target='_blank';this.form.submit();\">
							<option value=\"\">Edit</option>
				";
						$list = new LanguageList();
						$list->find();
						foreach($list as $language)
						{
							echo "<option value=\"{$language->getCode()}\">{$language->getNative()}</option>";
						}
				echo "
						</select>
						<button type=\"button\" class=\"view\" onclick=\"window.open('".BASE_URL."/documents/viewDocument.php?document_id={$document->getId()}');\">View</button>
						$retireButton
					</fieldset>
					</form>
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