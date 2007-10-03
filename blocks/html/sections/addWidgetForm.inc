<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param Section $this->section
 * @param WidgetInstallation $this->widget
 */
?>
<h2><?php echo View::escape($this->section->getName()); ?></h2>
<h2>Add <?php echo View::escape($this->widget->getName()); ?> Widget</h2>
<form method="post" action="<?php echo $_SERVER['PHP_SELF']; ?>">
<fieldset><legend>Widget</legend>
	<input name="sectionWidget[section_id]" type="hidden" value="<?php echo $this->section->getId(); ?>" />
	<input name="sectionWidget[widget_id]" type="hidden" value="<?php echo $this->widget->getId(); ?>" />
	<table>
	<tr><td><label for="sectionWidget-panel_id">Panel</label></td>
		<td><select name="sectionWidget[panel_id]" id="sectionWidget-panel_id">
			<?php
				$list = new PanelList();
				$list->find();
				foreach($list as $panel)
				{
					echo "<option value=\"{$panel->getId()}\">$panel</option>";
				}
			?>
			</select>
		</td>
	</tr>
	<tr><td><label for="sectionWidget[layout_order]">Order</label></td>
		<td><input name="sectionWidget[layout_order]" id="sectionWidget-layout_order" size="2" maxlength="2" /></td></tr>
	<tr><td colspan="2">The system will use this number to position this widget in relation to other wigets
			whenever this widget is displayed
	</td></tr>
	</table>
</fieldset>
<?php
	# If the Widget uses any extra data parameters, include those fields as well
	$className = $this->widget->getWidget()->getClassname();
	if (is_file(APPLICATION_HOME."/widgets/$className/dataFields.inc"))
	{
		include APPLICATION_HOME."/widgets/$className/dataFields.inc";
	}
?>
<fieldset><legend>Submit</lgend>
	<button type="submit" class="submit">Submit</button>
	<button type="button" class="cancel" onclick="self.close();">Cancel</button>
</fieldset>
</form>
