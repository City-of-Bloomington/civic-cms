<?php
/**
 * @copyright Copyright (C) 2008 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param AlertList $this->alertList
 */
echo "
<h1>Alerts</h1>
<table>
<tr><th><a class=\"addSmall button\" href=\"".BASE_URL."/alerts/addAlert.php\">Add</a></th>
	<th>Title</th>
	<th>Start</th>
	<th>End</th>
	<th>Message</th>
</tr>
";
foreach($this->alertList as $alert)
{
	$title = View::escape($alert->getTitle());
	$contents = View::escape($alert->getText());
	echo "
	<tr><td><a class=\"editSmall button\" href=\"".BASE_URL."/alerts/updateAlert.php?alert_id={$alert->getId()}\">Edit</a>
			<a class=\"deleteSmall button\" href=\"".BASE_URL."/alerts/deleteAlert.php?alert_id={$alert->getId()}\">Delete</a>
		</td>
		<td>$title</td>
		<td>{$alert->getStartTime('n/j/Y h:ia')}</td>
		<td>{$alert->getEndTime('n/j/Y h:ia')}</td>
		<td>$contents</td>
	</tr>
	";
}
echo "</table>";


$panel = new Panel('alerts');
$widgets = isset($this->document) ? $panel->getWidgets($this->document) : $panel->getWidgets();
foreach($widgets as $widget) { $widget->render($this); }
