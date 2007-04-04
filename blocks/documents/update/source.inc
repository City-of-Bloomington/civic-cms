<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param Document $this->document
 * @param Language $this->language
 */
?>
<h2>Document Source Code</h2>
<p>This page lets you upload a text file to be used as the content of this document.  Content is used <em>as is</em>!.
There will be no stripping or escaping of characters, tags, code, or anything else.  Use with discretion.</p>

<form id="updateDocumentForm" method="post" action="<?php echo $_SERVER['PHP_SELF']; ?>" enctype="multipart/form-data">
	<fieldset><legend>Language</legend>
		<label for="lang">Language</label>
		<select name="lang" id="lang">
			<?php
				$list = new LanguageList();
				$list->find();
				foreach($list as $language)
				{
					if ($this->language->getCode() == $language->getCode()) { echo "<option value=\"{$language->getCode()}\" selected=\"selected\">{$language->getNative()}</option>"; }
					else { echo "<option value=\"{$language->getCode()}\">{$language->getNative()}</option>"; }
				}
			?>
		</select>
	</fieldset>

	<fieldset><legend>Source Code</legend>
		<button type="button" class="download" onclick="document.location.href='<?php echo BASE_URL; ?>/documents/downloadSource.php?document_id=<?php echo $this->document->getId(); ?>;lang=<?php echo $this->language->getCode(); ?>';">Download</button>
		<input name="source" type="file" />
		<button type="button" class="upload" onclick="updateDocument('source','next');">Upload</button>
	</fieldset>

	<fieldset><legend>Next</legend>
		<p>Move on to the next tab.  The document will not be saved to the database until you click the "Save" button.</p>
		<input type="hidden" name="tab" id="tab" value="info" />
		<input type="hidden" name="action" id="action" value="next" />
		<button type="submit" class="next">Next</button>
		<button type="cancel" class="cancel" onclick="self.close();">Cancel</button>
		<button type="button" class="save" onclick="updateDocument('source','save');">Save</button>
	</fieldset>
</form>
