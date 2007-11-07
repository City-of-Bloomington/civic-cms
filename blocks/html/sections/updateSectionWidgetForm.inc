<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param SectionWidget $this->sectionWidget
 */
?>
<h2><?php echo View::escape($this->sectionWidget->getSection()->getName()); ?></h2>
<h2>Edit <?php echo View::escape($this->sectionWidget->getWidget()->getName()); ?> Widget</h2>
<form method="post" action="<?php echo $_SERVER['PHP_SELF']; ?>">
<fieldset><legend>Widget</legend>
	<input name="sectionWidget_id" type="hidden" value="<?php echo $this->sectionWidget->getId(); ?>" />
	<table>
	<tr><td><label for="sectionWidget-panel_id">Panel</label></td>
		<td><select name="sectionWidget[panel_id]" id="sectionWidget-panel_id">
			<?php
				$list = new PanelList();
				$list->find();
				foreach($list as $panel)
				{
					$selected = ($this->sectionWidget->getPanel_id()==$panel->getId()) ? 'selected="selected"' : '';
					echo "<option value=\"{$panel->getId()}\" $selected>$panel</option>";
				}
			?>
			</select>
		</td>
	</tr>
	<tr><td><label for="sectionWidget[layout_order]">Order</label></td>
		<td><input name="sectionWidget[layout_order]" id="sectionWidget-layout_order" size="2" maxlength="2" value="<?php echo $this->sectionWidget->getLayout_order(); ?>" /></td></tr>
	<tr><td colspan="2">The system will use this number to position this widget in relation to other wigets
			whenever this widget is displayed
	</td></tr>
	</table>
</fieldset>
<?php
	# If the Widget uses any extra data parameters, include those fields as well
	if ($this->sectionWidget->usesData())
	{
		include $this->sectionWidget->getDataFieldsetInclude();
	}
?>
<fieldset><legend>Submit</lgend>
	<button type="submit" class="submit">Submit</button>
	<button type="button" class="cancel" onclick="document.location.href='<?php echo BASE_URL; ?>/sections/updateWidgets.php?section_id=<?php echo $this->sectionWidget->getSection_Id(); ?>';">Cancel</button>
</fieldset>
</form>
