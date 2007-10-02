<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param Document $this->document
 * @param URL $this->return_url
 * @param int $this->instance_id
 */
?>
<form id="documentForm" method="post" action="<?php echo $_SERVER['PHP_SELF']; ?>">
	<fieldset><legend>Document Info</legend>
		<input type="hidden" name="tab" id="tab" value="content" />
		<input type="hidden" name="action" id="action" value="next" />
		<input type="hidden" name="return_url" value="<?php echo $this->return_url; ?>" />
		<input type="hidden" name="instance_id" value="<?php echo $this->instance_id; ?>" />
		<input type="hidden" name="continue" id="continue" value="true" />

		<table>
		<tr><td><label for="document-documentType_id">Type</label></td>
			<td><select name="document[documentType_id]" id="document-documentType_id">
				<?php
					$list = new DocumentTypeList();
					$list->find();
					foreach($list as $type)
					{
						$selected = $this->document->getDocumentType_id()==$type->getId() ? 'selected="selected"' : '';
						echo "<option value=\"{$type->getId()}\" $selected>$type</option>";
					}
				?>
				</select>
			</td>
		</tr>
		<?php
			# Departments should only be changeable by Webmasters and Administrators
			if (userHasRole(array('Administrator','Webmaster')))
			{
				echo "
				<tr><td><label for=\"department_id\">Department</label></td>
					<td><select name=\"department_id\" id=\"department_id\">
				";
					$list = new DepartmentList();
					$list->find();
					foreach($list as $department)
					{
						$name = View::escape($department->getName());
						$selected = $department->getId()==$this->document->getDepartment_id() ? 'selected="selected"' : '';
						echo "<option value=\"{$department->getId()}\" $selected>$name</option>";
					}
				echo "
						</select>
					</td>
				</tr>
				";
			}
		?>
		<tr><td><label for="document-title" class="required">Title</label></td>
			<td><input name="document[title]" id="document-title" value="<?php echo View::escape($this->document->getTitle()); ?>" /></td></tr>
		<tr><td><label for="document-alias">Alias</label></td>
			<td><input name="document[alias]" id="document-alias" value="<?php echo View::escape($this->document->getAlias()); ?>" /></td></tr>
		<tr><td><label for="document-feature_title">Action Title</label></td>
			<td><input name="document[feature_title]" id="document-feature_title" value="<?php echo View::escape($this->document->getFeature_title()); ?>" /></td></tr>
		<tr><td colspan="2">
				<label for="document-description">Description</label>
				<textarea name="document[description]" id="document-description" rows="3" cols="60"><?php echo View::escape($this->document->getDescription()); ?></textarea>
		</td></tr>

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

</form>
