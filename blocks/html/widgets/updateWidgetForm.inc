<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param WidgetInstallation $this->widget
 */
?>
<h2>Edit <?php echo View::escape($this->widget->getName()); ?></h2>
<form method="post" action="<?php echo $_SERVER['PHP_SELF']; ?>">
<fieldset><legend>Global Widget</legend>
	<input name="widget_id" type="hidden" value="<?php echo $this->widget->getId(); ?>" />
	<p>Set this information if you want the widget to always be used throughout the site</p>
	<table>
	<tr><td><label for="widget-global_panel_id">Panel</label></td>
		<td><select name="widget[global_panel_id]" id="widget-global_panel_id"><option></option>
			<?php
				$panels = new PanelList();
				$panels->find();
				foreach($panels as $panel)
				{
					$selected = ($this->widget->getGlobal_panel_id() === $panel->getId()) ? 'selected="selected"' : '';
					echo "<option value=\"{$panel->getId()}\" $selected>$panel</option>";
				}
			?>
			</select>
		</td>
	</tr>
	<tr><td><label for="widget-global_layout_order">Layout Order</label></td>
		<td><input name="widget[global_layout_order]" id="widget-global_layout_order" size="2" maxlength="2" value="<?php echo $this->widget->getGlobal_layout_order(); ?>" /></td>
	</tr>
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

<fieldset><legend>Default Widget</legend>
	<p>Set this information if you want the widget to be used by default for all newly created Sections</p>
	<p>When you create a new Section, the system will add all the Widgets that have this default information
	to the newly created Section.</p>
	<table>
	<tr><td><label for="widget-default_panel_id">Panel</label></td>
		<td><select name="widget[default_panel_id]" id="widget-default_panel_id"><option></option>
			<?php
				foreach($panels as $panel)
				{
					$selected = ($this->widget->getDefault_panel_id() === $panel->getId()) ? 'selected="selected"' : '';
					echo "<option value=\"{$panel->getId()}\" $selected>$panel</option>";
				}
			?>
			</select>
		</td>
	</tr>
	<tr><td><label for="widget-Default_layout_order">Layout Order</label></td>
		<td><input name="widget[Default_layout_order]" id="widget-Default_layout_order" size="2" maxlength="2" value="<?php echo $this->widget->getDefault_layout_order(); ?>" /></td>
	</tr>
	</table>
</fieldset>

<fieldset><legend>Submit</legend>
	<button type="submit" class="submit">Submit</button>
	<button type="button" class="cancel" onclick="document.location.href='<?php echo BASE_URL; ?>/widgets';">Cancel</button>
</fieldset>
</form>
