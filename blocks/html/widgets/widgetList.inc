<?php
/**
 * @copyright Copyright (C) 2006-2008 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham
 * @param WidgetInstallationList $this->widgetInstallationList
 */
?>
<h1>Installed Widgets</h1>
<table>
<tr><th></th>
	<th>Name</th>
	<th>Description</th>
	<th>Global</th>
	<th>Default</th>
</tr>
<?php
	$installed = array();
	foreach($this->widgetInstallationList as $widget)
	{
		$installed[] = $widget->getClass();

		$global = $widget->isGlobal() ? 'yes' : 'no';
		$default = $widget->isDefault() ? 'yes' : 'no';

		$name = View::escape($widget->getName());
		$description = View::escape($widget->getDescription());
		echo "
		<tr><td><a class=\"editSmall button\" href=\"".BASE_URL."/widgets/updateWidget.php?widget_id={$widget->getId()}\">Edit</a>
				<a class=\"deleteSmall button\" href=\"".BASE_URL."/widgets/uninstall.php?widget_id={$widget->getId()}\">Uninstall</a></td>
			<td>$name</td>
			<td>$description</td>
			<td>$global</td>
			<td>$default</td>
		</tr>
		";
	}
?>
</table>


<h1>Available Widgets</h1>
<table>
<tr><th></th>
	<th>Widget</th>
	<th>Description</th></tr>
<?php
	foreach(Widget::findAll() as $widget)
	{
		if (!in_array($widget->getClassName(),$installed))
		{
			$name = View::escape($widget->getName());
			$description = View::escape($widget->getDescription());
			echo "
			<tr><td><a class=\"addSmall button\" href=\"".BASE_URL."/widgets/install.php?widget={$widget->getClassName()}\">Install</a></td>
				<td>$name</td>
				<td>$description</td></tr>
			";
		}
	}
?>
</table>
