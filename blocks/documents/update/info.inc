<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param Document $this->document
 */
?>
<form id="documentForm" method="post" action="<?php echo $_SERVER['PHP_SELF']; ?>">
	<fieldset><legend>Document Info</legend>
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

	<fieldset><legend>Next</legend>
		<p>Move on to the next tab.  The document will not be saved to the database until you click the "Save" button.</p>
		<input type="hidden" name="tab" id="tab" value="content" />
		<input type="hidden" name="action" id="action" value="next" />
		<button type="submit" class="next">Next</button>
		<button type="cancel" class="cancel" onclick="self.close();">Cancel</button>
		<button type="button" class="save" onclick="processTabbedForm('documentForm','info','save');">Save</button>
	</fieldset>
</form>
