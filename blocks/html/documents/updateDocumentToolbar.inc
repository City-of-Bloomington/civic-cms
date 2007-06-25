<?php
/**
 * @copyright Copyright (C) 2006,2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param Document $this->document
 */
?>
<div class="contextualMenu">
	<ul><li><button type="button" class="edit" onclick="window.open('<?php echo BASE_URL; ?>/documents/updateDocument.php?document_id=<?php echo $this->document->getId(); ?>');">Edit</button></li>
		<li><form method="get" action="<?php echo BASE_URL; ?>/documents/updateDocument.php">
			<fieldset>
				<input name="document_id" type="hidden" value="<?php echo $this->document->getId(); ?>" />
				<select name="lang" onsubmit="this.form.target='_blank';this.form.submit;">
				<option value="">Edit Translation</option>
				<?php
					$list = new LanguageList();
					$list->find();
					foreach($list as $language)
					{
						echo "<option value=\"{$language->getCode()}\">{$language->getNative()}</option>";
					}
				?>
				</select>
			</fieldset>
			</form>
		</li>
		<?php
			# Buttons for Watch and UnWatch
			$url = $_SESSION['USER']->hasWatch($this->document) ? BASE_URL."/documents/removeWatch.php?document_id={$this->document->getId()}" : BASE_URL."/documents/addWatch.php?document_id={$this->document->getId()}";
			if ($_SESSION['USER']->hasWatch($this->document)) { echo "<li><button type=\"button\" class=\"removeWatch\" onclick=\"document.location.href='$url';\">Unwatch</button></li>"; }
			else { echo "<li><button type=\"button\" class=\"watch\" onclick=\"document.location.href='$url';\">Watch</button></li>"; }


			# Buttons for downloading and uploading the raw source HTML
			if (userHasRole('Webmaster'))
			{
				echo "
				<li><button type=\"button\" class=\"download\" onclick=\"document.location.href='".BASE_URL."/documents/downloadSource.php?document_id={$this->document->getId()}';\">Download</button></li>
				<li><form method=\"post\" action=\"".BASE_URL."/documents/uploadSource.php\" enctype=\"multipart/form-data\">
					<fieldset>
						<input name=\"document_id\" type=\"hidden\" value=\"{$this->document->getId()}\" />
						<input name=\"content\" type=\"file\" />
						<button type=\"submit\" class=\"upload\">Upload</button>
					</fieldset>
					</form>
				</li>
				";
			}
		?>
	</ul>
</div>
