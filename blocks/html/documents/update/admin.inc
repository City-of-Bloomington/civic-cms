<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param Document $this->document
 * @param Language $this->language
 * @param URL $this->return_url
 * @param int $this->instance_id
 */
?>
<h1>Document Admin</h1>

<form id="documentForm" method="post" action="<?php echo $_SERVER['SCRIPT_NAME']; ?>" enctype="multipart/form-data">
	<fieldset><legend>Alias</legend>
	<p>This is an alternative title used to find this document when the user types this into the URL</p>
	<table>
	<tr><td><label for="document-alias">Alias</label></td>
	<td><input name="document[alias]" id="document-alias" size="60" value="<?php echo View::escape($this->document->getAlias()); ?>" /></td></tr>
	</table>
	</fieldset>

	<fieldset><legend>Skin</legend>
		<p>You can set a sepcific skin for this document.  The name you choose here should match
			the directory name in /html/skins.</p>
		<table>
			<tr><td><label for="document-skin">Skin</label></td>
				<td><input name="document[skin]" id="document-skin" value="<?php echo View::escape($this->document->getSkin()); ?>" /></td>
			</tr>
		</table>
	</fieldset>

	<fieldset><legend>Banner</legend>
	<p>Banner images will not be resized when displayed.  They will be used in their original form.
		Please choose or upload an appropriately sized image.</p>
	<table>
	<tr><td><label for="document-banner_media_id">Banner</label></td>
		<td><button type="button" class="browse" onclick="startImageBrowser('banner-image','document-banner_media_id','original');">Choose Media</button>
			<button type="button" class="deleteSmall" onclick="removeImage('banner-image','document-banner_media_id');">Delete</button>
			<input name="document[banner_media_id]" id="document-banner_media_id" type="hidden" value="<?php echo $this->document->getBanner_media_id(); ?>" />
			<span id="banner-image">
			<?php
				if ($this->document->getBanner_media_id())
				{
					echo "<img src=\"{$this->document->getBanner_media()->getURL('original')}\" />";
				}
			?>
			</span>
		</td>
	</tr>
	</table>
	</fieldset>

	<fieldset><legend>Icon</legend>
	<p>Icons will be displayed as thumbnails when the document is featured.</p>
	<table>
	<tr><td><label for="document-icon_media_id">Icon</label></td>
		<td><button type="button" class="browse" onclick="startImageBrowser('icon-thumbnail','document-icon_media_id','thumbnail');">Choose Media</button>
			<button type="button" class="deleteSmall" onclick="removeImage('icon-thumbnail','document-icon_media_id');">Delete</button>
			<input name="document[icon_media_id]" id="document-icon_media_id" type="hidden" value="<?php echo $this->document->getIcon_media_id(); ?>" />
			<span id="icon-thumbnail">
			<?php
				if ($this->document->getIcon_media_id())
				{
					echo "<img src=\"{$this->document->getIcon_media()->getURL('thumbnail')}\" />";
				}
			?>
			</span>
			<script type="text/javascript">
			var span = {}
			var field = {}
			var size = '';
			function startImageBrowser(span_id,field_id,targetSize)
			{
				span = document.getElementById(span_id);
				field = document.getElementById(field_id);
				size = targetSize;
				window.open('<?php echo BASE_URL; ?>/media/imageBrowser.php');
			}
			function handleSelection(media_id)
			{
				field.value = media_id;

				while (span.hasChildNodes()) { span.removeChild(span.firstChild); }
				var img = document.createElement('img');
				img.src = '<?php echo BASE_URL; ?>/media/media.php?size='+size+';media_id='+media_id;
				span.appendChild(img);
			}
			function removeImage(span_id,field_id)
			{
				span = document.getElementById(span_id);
				field = document.getElementById(field_id);

				while(span.hasChildNodes()) { span.removeChild(span.firstChild); }
				field.value = '';
			}
			</script>
		</td>
	</tr>
	</table>

	<fieldset><legend>Language</legend>
		<input type="hidden" name="tab" id="tab" value="info" />
		<input type="hidden" name="action" id="action" value="next" />
		<input type="hidden" name="return_url" value="<?php echo $this->return_url; ?>" />
		<input type="hidden" name="instance_id" value="<?php echo $this->instance_id; ?>" />
		<input type="hidden" name="continue" id="continue" value="true" />

		<label for="lang">Language</label>
		<select name="lang" id="lang" onchange="FRAMEWORK.processTabbedForm('documentForm','admin','next');">
			<?php
				$list = new LanguageList();
				$list->find();
				foreach($list as $language)
				{
					if ($this->language->getCode() == $language->getCode()) { echo "<option value=\"{$language->getCode()}\" selected=\"selected\">{$language->getEnglish()}</option>"; }
					else { echo "<option value=\"{$language->getCode()}\">{$language->getEnglish()}</option>"; }
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
					<select name=\"locked\" id=\"locked\" onchange=\"FRAMEWORK.processTabbedForm('documentForm','admin','next');\">
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
		<?php
			if (!$this->document->isLocked())
			{
				$xmllang = "xml:lang=\"{$this->language}\"";
				$lang = "lang=\"{$this->language}\"";
				$dir = $this->language->getDirection()=='rtl' ? 'dir="rtl"' : '';
		?>
			<textarea name="source_<?php echo $this->language ?>" rows="30" cols="100" <?php echo "$xmllang $lang $dir"; ?>><?php echo View::escape($this->document->getContent($this->language->getCode())); ?></textarea>
			<div>
				<?php
					# You can't download anything until we've saved the document, and have a document_id
					if ($this->document->getId())
					{
						echo "<a class=\"download\" href=\"".BASE_URL."/documents/downloadSource.php?document_id={$this->document->getId()};lang={$this->language->getCode()}\">Download</a>";
					}
				?>
				<input name="source" type="file" />
				<button type="button" class="upload" onclick="FRAMEWORK.processTabbedForm('documentForm','admin','next');">Upload</button>
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
