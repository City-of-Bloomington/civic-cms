<?php
/**
 * @copyright Copyright (C) 2006 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param Document $this->document
 * @param string $this->language
 * @param array $this->sectionList
 */
?>
<form method="post" action="<?php echo $_SERVER['PHP_SELF']; ?>">
	<fieldset><legend>Document Info</legend>
		<input name="document_id" type="hidden" value="<?php echo $this->document->getId(); ?>" />
		<table>
		<tr><td><label for="document-title">Title</label></td>
			<td><input name="document[title]" id="document-title" value="<?php echo $this->document->getTitle(); ?>" /></td></tr>

		<tr><td><label for="document-publishDate-mon">Publish Date</label></td>
			<td><select name="document[publishDate][mon]" id="document-publishDate-mon"><option></option>
				<?php
					$publishDate = $this->document->dateStringToArray($this->document->getPublishDate());
					for($i=1; $i<=12; $i++)
					{
						if ($i!=$publishDate['mon']) { echo "<option>$i</option>"; }
						else { echo "<option selected=\"selected\">$i</option>"; }
					}
				?>
				</select>
				<select name="document[publishDate][mday]"><option></option>
				<?php
					for($i=1; $i<=31; $i++)
					{
						if ($i!=$publishDate['mday']) { echo "<option>$i</option>"; }
						else { echo "<option selected=\"selected\">$i</option>"; }
					}
				?>
				</select>
				<input name="document[publishDate][year]" id="document-publishDate-year" size="4" maxlength="4" value="<?php echo $publishDate['year']; ?>" />
			</td>
		</tr>
		<tr><td><label for="document-retireDate-mon">Retire Date</label></td>
			<td><select name="document[retireDate][mon]" id="document-retireDate-mon"><option></option>
				<?php
					$retireDate = $this->document->dateStringToArray($this->document->getRetireDate());
					for($i=1; $i<=12; $i++)
					{
						if ($i!=$retireDate['mon']) { echo "<option>$i</option>"; }
						else { echo "<option selected=\"selected\">$i</option>"; }
					}
				?>
				</select>
				<select name="document[retireDate][mday]"><option></option>
				<?php
					for($i=1; $i<=31; $i++)
					{
						if ($i!=$retireDate['mday']) { echo "<option>$i</option>"; }
						else { echo "<option selected=\"selected\">$i</option>"; }
					}
				?>
				</select>
				<input name="document[retireDate][year]" id="document-retireDate-year" size="4" maxlength="4" value="<?php echo $retireDate['year']; ?>" />
			</td>
		</tr>
		</table>
	</fieldset>
	<fieldset><legend>Content</legend>
		<table>
		<tr><td><label for="lang">Current Language</label></td>
			<td><select name="lang" id="lang" onchange="document.location.href='updateDocument.php?document_id=<?php echo $this->document->getId(); ?>;lang='+this[this.selectedIndex].value;">
				<?php
					$list = new LanguageList();
					$list->find();
					foreach($list as $language)
					{
						if ($_SESSION['LANGUAGE'] == $language->getCode()) { echo "<option value=\"{$language->getCode()}\" selected=\"selected\">{$language->getNative()}</option>"; }
						else { echo "<option value=\"{$language->getCode()}\">{$language->getNative()}</option>"; }
					}
				?>
				</select>
			</td>
		</tr>
		</tr>
		</table>
		<?php include APPLICATION_HOME.'/includes/editors/'.EDITOR.'.inc'; ?>
	</fieldset>

	<fieldset><legend>Sections</legend>
	<table>
		<?php
			foreach ($this->sectionList as $section)
			{
				if ($this->document->hasSection($section)) { $checked="checked=\"checked\""; } else { $checked=""; }
				echo "
				<tr><td><input name=\"document[sections][{$section->getId()}]\" id=\"document-sections-{$section->getId()}\" type=\"checkbox\" value=\"{$section->getId()}\" $checked /></td>
					<td><label for=\"document-sections-{$section->getId()}\">{$section}</label></td></tr>
				";
			}
		?>
	</table>
	</fieldset>

	<fieldset><legend>Facets</legend>
	<?php
		$facets = new FacetList();
		$facets->find();
		foreach($facets as $facet)
		{
			if ($this->document->hasFacet($facet)) { $checked = "checked=\"checked\""; } else { $checked = ""; }
			echo "<label><input type=\"checkbox\" name=\"document[facets][{$facet->getId()}]\" value=\"{$facet->getId()}\" $checked />{$facet->getName()}</label>";
		}
	?>
	</fieldset>

	<fieldset><legend>Submit</legend>
		<button type="submit" class="submit">Submit</button>
		<button type="button" class="cancel" onclick="self.close();">Cancel</button>
	</fieldset>
</form>
<?php
	# Buttons for downloading and uploading the raw source HTML
	if (userHasRole('Webmaster'))
	{
		echo "
		<form method=\"post\" action=\"".BASE_URL."/documents/uploadSource.php\" enctype=\"multipart/form-data\">
		<fieldset><legend>Document Source Code</legend>
			<button type=\"button\" class=\"download\" onclick=\"document.location.href='".BASE_URL."/documents/downloadSource.php?document_id={$this->document->getId()};lang={$this->language->getCode()}';\">Download</button>

			<input name=\"document_id\" type=\"hidden\" value=\"{$this->document->getId()}\" />
			<input name=\"lang\" type=\"hidden\" value=\"{$this->language->getCode()}\" />
			<input name=\"content\" type=\"file\" />
			<button type=\"submit\" class=\"upload\">Upload</button>
		</fieldset>
		</form>
		";
	}
?>