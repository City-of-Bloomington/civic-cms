<?php
/**
 * @copyright Copyright (C) 2006 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 */
/*
	$this->FCKeditor
	$this->response
	$this->section ( Optional section to pre-select )
*/
?>
<h1>New Document</h1>
<form method="post" action="<?php echo $_SERVER['PHP_SELF']; ?>">
	<fieldset><legend>Document Info</legend>
		<table>
		<tr><td><label for="document-title">Title</label></td>
			<td><input name="document[title]" id="document-title" /></td></tr>
		</table>
		<?php $this->FCKeditor->create(); ?>
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
		<button type="button" class="cancel" onclick="document.location.href='<?php echo $this->response; ?>';">Cancel</button>
	</fieldset>
</form>