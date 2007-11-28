<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param Document $this->document
 * @param Language $this->language
 * @param URL $this->return_url
 * @param int $this->instance_id
 */
?>
<h1>Document Admin</h1>

<form id="documentForm" method="post" action="<?php echo $_SERVER['PHP_SELF']; ?>" enctype="multipart/form-data">
	<fieldset><legend>Alias</legend>
	<p>This is an alternative title used to find this document when the user types this into the URL</p>
	<table>
	<tr><td><label for="document-alias">Alias</label></td>
	<td><input name="document[alias]" id="document-alias" value="<?php echo View::escape($this->document->getAlias()); ?>" /></td></tr>
	</table>
	</fieldset>

	<fieldset><legend>Language</legend>
		<input type="hidden" name="tab" id="tab" value="info" />
		<input type="hidden" name="action" id="action" value="next" />
		<input type="hidden" name="return_url" value="<?php echo $this->return_url; ?>" />
		<input type="hidden" name="instance_id" value="<?php echo $this->instance_id; ?>" />
		<input type="hidden" name="continue" id="continue" value="true" />

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
	<fieldset><legend>Locking and PHP Code</legend>
		<p>If you are going to enable PHP code for this document, it is <strong>highly recommended</strong> that you
			also lock the content when you are done.</p>
		<div>
			<?php
				if (!$this->document->isLocked() || userHasRole('Administrator') || $_SESSION['USER']->getId()==$this->document->getLockedBy())
				{
					# They are allowed to change the locked status
					if ($this->document->isLocked())
					{
						$locked = 'selected="selected"';
						$unlocked = '';
					}
					else
					{
						$locked ='';
						$unlocked = 'selected="selected"';
					}
					echo "
					<label for=\"locked\">Locking</label>
					<select name=\"locked\" id=\"locked\" onchange=\"FRAMEWORK.processTabbedForm('documentForm','source','next');\">
						<option $locked>Locked</option>
						<option $unlocked>Unlocked</option>
					</select>
					";
				}
				else
				{
					echo "
					<p>Content editing has been locked by {$this->document->getLockedByUser()->getUsername()}.</p>
					<p>You will need to contact that person, or an Administrator, to edit this content.</p>
					";
				}
			?>
		</div>
		<div>
			<label for="enablePHP">Enable PHP Code?</label>
			<select name="enablePHP" id="enablePHP">
				<option value="1" <?php if($this->document->PHPIsEnabled()) echo 'selected="selected"'; ?>>Yes</option>
				<option value="0" <?php if(!$this->document->PHPIsEnabled()) echo 'selected="selected"'; ?>>No</option>
			</select>
		</div>
	</fieldset>

	<fieldset><legend>Source Code</legend>
	<p>Content provided here is used <em>as is</em>!.
		There will be no stripping or escaping of characters, tags, code, or anything else.  Use with discretion.</p>
		<?php if (!$this->document->isLocked()) { ?>
			<textarea name="source_<?php echo $this->language->getCode(); ?>" rows="30" cols="100"><?php echo View::escape($this->document->getContent($this->language->getCode())); ?></textarea>
			<div>
				<?php
					# You can't download anything until we've saved the document, and have a document_id
					if ($this->document->getId())
					{
						echo "<button type=\"button\" class=\"download\" onclick=\"document.location.href='".BASE_URL."/documents/downloadSource.php?document_id={$this->document->getId()};lang={$this->language->getCode()}';\">Download</button>";
					}
				?>
				<input name="source" type="file" />
				<button type="button" class="upload" onclick="FRAMEWORK.processTabbedForm('documentForm','source','next');">Upload</button>
			</div>
		<?php
			}
			else
			{
				echo "
				<p>Content editing has been locked by {$this->document->getLockedByUser()->getUsername()}.</p>
				<p>You will need to contact that person, or an Administrator, to edit this content.</p>
				";
			}
		?>
	</fieldset>

</form>
