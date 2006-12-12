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
	<ul>
		<li><a href="<?php echo BASE_URL; ?>/documents/updateDocument.php?document_id=<?php echo $this->document->getId(); ?>;return_url=<?php echo $_SERVER['REQUEST_URI']; ?>">Edit</a></li>
		<?php
			if ($_SESSION['USER']->hasWatch($this->document)) { echo "<li><a href=\"".BASE_URL."/documents/removeWatch.php?document_id={$this->document->getId()}\">Unwatch</a></li>"; }
			else { echo "<li><a href=\"".BASE_URL."/documents/addWatch.php?document_id={$this->document->getId()}\">Watch</a></li>"; }
		?>
		<li><form method="get" action="<?php echo BASE_URL; ?>/documents/updateDocument.php">
				<input name="document_id" type="hidden" value="<?php echo $this->document->getId(); ?>" />
				<select name="lang" onchange="this.form.submit();">
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
			</form>
		</li>
	</ul>
</div>