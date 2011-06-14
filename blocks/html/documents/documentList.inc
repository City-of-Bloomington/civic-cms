<?php
/**
 * @copyright Copyright (C) 2006-2008 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Inghamn <inghamn@bloomington.in.gov>
 * @param DocumentList $this->documentList
 * @param string $this->title
 */
?>
<div class="interfaceBox">
	<h2>
		<?php
			echo View::escape($this->title);
			include APPLICATION_HOME.'/blocks/html/documents/addDocumentToolbar.inc';

			$url = new URL($_SERVER['SERVER_NAME'].$_SERVER['REQUEST_URI']);
		?>
	</h2>
	<table>
	<thead>
		<tr><th>Filters:</th>
			<th></th>
			<th></th>
			<th></th>
			<th><?php
					echo "
					<select name=\"by\" onchange=\"document.location.href='{$url->script}?filter=modifiedBy-'+this.options[this.selectedIndex].value;\">
					<option></option>
					";
					$list = new UserList();
					$list->find();
					foreach($list as $user)
					{
						$by = substr($user->getFirstname(),0,1).substr($user->getLastname(),0,1);
						echo "<option value=\"{$user->getId()}\">$by</option>";
					}
				?>
				</select>
			</th>
			<th></th>
			<th><?php
					echo "
					<select name=\"documentType_id\" onchange=\"document.location.href='{$url->script}?filter=documentType_id-'+this.options[this.selectedIndex].value;\">
					<option></option>
					";
					$list = new DocumentTypeList();
					$list->find();
					foreach($list as $type)
					{
						echo "<option value=\"{$type->getId()}\">$type</option>";
					}
				?>
				</select>
			</th>
		</tr>
		<tr>
		<?php
			if (!isset($url->parameters['sort'])) { $url->parameters['sort'] = ''; }

			# If title's in the sort array, toggle it
			$temp = $url;
			$temp->parameters['sort'] = $temp->parameters['sort']=='title' ? 'title desc' : 'title';
			echo "<th><a href=\"$temp\">Title</a></th>\n";

			$temp = $url;
			$temp->parameters['sort'] = $temp->parameters['sort']=='created desc' ? 'created' : 'created desc';
			echo "<th><a href=\"$temp\">Created</a></th>\n";

			$temp->parameters['sort'] = $temp->parameters['sort']=='publishDate desc' ? 'publishDate' : 'publishDate desc';
			echo "<th><a href=\"$temp\">Published</a></th>\n";

			$temp->parameters['sort'] = $temp->parameters['sort']=='modified desc' ? 'modified' : 'modified desc';
			echo "<th><a href=\"$temp\">Modified</a></th>\n";

			echo "<th>By</th>\n";

			$temp->parameters['sort'] = $temp->parameters['sort']=='retireDate desc' ? 'retireDate' : 'retireDate desc';
			echo "<th><a href=\"$temp\">Retired</a></th>\n";

			$temp->parameters['sort'] = $temp->parameters['sort']=='type' ? 'type desc' : 'type';
			echo "<th><a href=\"$temp\">Type</a></th>\n";
		?>
		</tr>
	</thead>
	<tbody>
	<?php
		foreach($this->documentList as $document)
		{
			if ($document->permitsEditingBy($_SESSION['USER']))
			{
				$url =  new URL(BASE_URL.'/documents/updateDocument.php');
				$url->parameters['document_id'] = $document->getId();
				$url->parameters['lang'] = $_SESSION['LANGUAGE'];
				$url->parameters['return_url'] = new URL("$_SERVER[SERVER_NAME]$_SERVER[REQUEST_URI]");
			}
			else { $url = new URL($document->getURL()); }

			$url->parameters['tab'] = 'info';

			$modifiedBy = substr($document->getModifiedByUser()->getFirstname(),0,1).substr($document->getModifiedByUser()->getLastname(),0,1);

			$title = View::escape($document->getTitle());
			$partialTitle = substr($title,0,20);

			$class = $document->isActive() ? '' : 'class="unpublished"';

			echo "
			<tr><td style=\"width:100px; white-space:nowrap; overflow:hidden;\">
					<a href=\"{$document->getURL()}\" title=\"$title\" $class>$partialTitle</a></td>
				<td>{$document->getCreated('%D')}</td>
				<td>{$document->getPublishDate('%D')}</td>
				<td>{$document->getModified('%D')}</td>
				<td>$modifiedBy</td>
				<td>{$document->getRetireDate('%D')}</td>
				<td>{$document->getDocumentType()}</td>
			</tr>
			";



			if ($document->permitsEditingBy($_SESSION['USER']))
			{
				# Show all the editing buttons
				$retireButton = !$document->getRetireDate() ? "<a class=\"retire\" href=\"".BASE_URL."/documents/retireDocument.php?document_id={$document->getId()}\">Retire</a>" : "";

				if($_SESSION['USER']->hasWatch($document))
				{
					$watch = "<a class=\"unwatch button\" href=\"".BASE_URL."/documents/removeWatch.php?document_id={$document->getId()}\">Unwatch</a>";
				}
				else
				{
					$watch = "<a class=\"watch button\" href=\"".BASE_URL."/documents/addWatch.php?document_id={$document->getId()}\">Watch</a>";
				}

				# Documents that are homepages should not be deleted.
				# At least until we can work out a way to choose new homepages for sections
				$deleteButton = $document->isHomepage() ? '' : "<button type=\"button\" class=\"delete\" onclick=\"FRAMEWORK.deleteConfirmation('".BASE_URL."/documents/deleteDocument.php?document_id={$document->getId()}');\">Delete</button>";

				echo "
				<tr><td colspan=\"7\">
						<a class=\"edit\" href=\"".BASE_URL."/documents/updateDocument.php?document_id={$document->getId()}\">Edit</a>
						<a class=\"view\" href=\"{$document->getURL()}\">View</a>
						$deleteButton
						$retireButton
						$watch
					</td>
				</tr>
				";
			}

		}
	?>
	</tbody>
	</table>
</div>
