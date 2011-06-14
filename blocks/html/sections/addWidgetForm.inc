<?php
/**
 * @copyright Copyright (C) 2007,2008 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param Section $this->section
 * @param WidgetInstallation $this->widgetInstallation
 */
?>
<h1><?php echo View::escape($this->section->getName()); ?></h1>
<h1>Add <?php echo View::escape($this->widgetInstallation->getName()); ?> Widget</h1>
<form method="post" action="<?php echo $_SERVER['SCRIPT_NAME']; ?>">
<fieldset><legend>Widget</legend>
	<input name="sectionWidget[section_id]" type="hidden" value="<?php echo $this->section->getId(); ?>" />
	<input name="sectionWidget[widget_id]" type="hidden" value="<?php echo $this->widgetInstallation->getId(); ?>" />
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
	if ($this->widgetInstallation->getWidget()->usesData())
	{
		$this->widget = $this->widgetInstallation->getWidget();
		$this->widget->setData($this->widgetInstallation->getGlobal_data());
		include $this->widget->getDataFieldsetInclude();
	}
?>
<fieldset><legend>Submit</lgend>
	<button type="submit" class="submit">Submit</button>
	<a class="cancel" href="<?php echo BASE_URL; ?>/sections/updateWidgets.php?section_id=<?php echo $this->section->getId(); ?>">Cancel</a>
</fieldset>
</form>
