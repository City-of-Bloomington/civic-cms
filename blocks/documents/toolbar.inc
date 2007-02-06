<?php
/**
 * @copyright Copyright (C) 2006 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 */
/*
	$this->document
*/
?>
<div class="contextualMenu">
	<span class="title">This Document:</span>
	<ul><li><button type="button" class="edit" onclick="window.open('<?php echo BASE_URL; ?>/documents/updateDocument.php?document_id=<?php echo $this->document->getId(); ?>');">Edit</button></li>
		<?php
			$url = $_SESSION['USER']->hasWatch($this->document) ? BASE_URL."/documents/removeWatch.php?document_id={$this->document->getId()}" : BASE_URL."/documents/addWatch.php?document_id={$this->document->getId()}";
			if ($_SESSION['USER']->hasWatch($this->document)) { echo "<li><button type=\"button\" class=\"removeWatch\" onclick=\"document.location.href='$url';\">Unwatch</button></li>"; }
			else { echo "<li><button type=\"button\" class=\"watch\" onclick=\"document.location.href='$url';\">Watch</button></li>"; }
		?>
	</ul>
</div>
<div class="contextualMenu">
	<span class="title">Edit Translation:</span>
	<ul>
	<?php
		$list = new LanguageList();
		$list->find();
		foreach($list as $language)
		{
			echo "<li><button type=\"button\" onclick=\"window.open('".BASE_URL."/documents/updateDocument.php?document_id={$this->document->getId()};lang={$language->getCode()}');\">{$language->getNative()}</button></li>";
		}
	?>
	</ul>
</div>
<?php
	if (userHasRole('Webmaster'))
	{
		echo "
		<div class=\"contextualMenu\">
			<span class=\"title\">Source:</span>
			<ul><li><button type=\"button\" class=\"download\" onclick=\"document.location.href='".BASE_URL."/documents/downloadSource.php?document_id={$this->document->getId()}';\">Download</button></li>
				<li><form method=\"post\" action=\"".BASE_URL."/documents/uploadSource.php\" enctype=\"multipart/form-data\">
					<div>
						<input name=\"document_id\" type=\"hidden\" value=\"{$this->document->getId()}\" />
						<input name=\"content\" type=\"file\" />
						<button type=\"submit\" class=\"upload\">Upload</button>
					</div>
					</form>
				</li>
			</ul>
		</div>
		";
	}


	# Create the New Document Menu
	$sections = $this->document->getSections();
	foreach($sections as $section)
	{
		# Make sure they are allowed to create a new document in the section they're viewing
		if (isset($_SESSION['USER']) && $section->permitsEditingBy($_SESSION['USER']))
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
						echo "<li><button type=\"button\" onclick=\"window.open('".BASE_URL."/documents/addDocument.php?section_id={$section->getId()};documentType_id={$type->getId()}');\">$type</button></li>";
					}
			echo "
				</ul>
			</div>
			";

			break;
		}
	}
?>