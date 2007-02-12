<?php
/**
 * @copyright Copyright (C) 2006 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 */
/*
	$this->document
	$this->section ( Optional section to pre-select )
*/
?>
<form method="post" action="<?php echo $_SERVER['PHP_SELF']; ?>">
	<fieldset><legend>Document Info</legend>
		<input name="document[documentType_id]" type="hidden" value="<?php echo $this->document->getDocumentType_id(); ?>" />

		<table>
		<tr><td><label for="document-title">Title</label></td>
			<td><input name="document[title]" id="document-title" <?php if (isset($this->document)) echo "value=\"{$this->document->getTitle()}\""; ?> /></td></tr>
		</table>
	</fieldset>
	<fieldset><legend>Content</legend>
		<table>
		<tr><td><label for="lang">Current Language</label></td>
			<td><select name="lang" id="lang">
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
		</table>
		<?php include APPLICATION_HOME.'/includes/editors/'.EDITOR.'.inc'; ?>
	</fieldset>

	<fieldset><legend>Sections</legend>
	<table>
		<?php
			$sections = new SectionList(array('department_id'=>$_SESSION['USER']->getDepartment_id()));
			foreach ($sections as $section)
			{
				if (isset($this->section) && $section->getId()==$this->section->getId()) { $checked="checked=\"checked\""; } else { $checked=""; }
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
			echo "<label><input type=\"checkbox\" name=\"document[facets][{$facet->getId()}]\" value=\"{$facet->getId()}\" />{$facet->getName()}</label>";
		}
	?>
	</fieldset>

	<fieldset><legend>Submit</legend>
		<button type="submit" class="submit">Submit</button>
		<button type="button" class="cancel" onclick="self.close();">Cancel</button>
	</fieldset>
</form>