<?php
/**
 * @copyright Copyright (C) 2006 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 */
/*
	$this->widgetList
*/
?>
<h1>Widgets</h1>
<table>
<tr><th>Name</th>
	<th>Description</th>
	<th>Status</th>
	<th></th>
</tr>
<?php
	foreach($this->widgetList as $widget)
	{
		if ($widget->getStatus() == "installed")
		{
			$button = "<button type=\"button\" class=\"deleteSmall\" onclick=\"document.location.href='".BASE_URL."/widgets/uninstall.php?widget={$widget->getName()}';\">Uninstall</button>";
		}
		else { $button = "<button type=\"button\" class=\"addSmall\" onclick=\"document.location.href='".BASE_URL."/widgets/install.php?widget={$widget->getName()}';\">Install</button>"; }
		echo "
		<tr><td>{$widget->getName()}</td>
			<td>{$widget->getDescription()}</td>
			<td>{$widget->getStatus()}</td>
			<td>$button</td>
		</tr>
		";
	}

?>
</table>