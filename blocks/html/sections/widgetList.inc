<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param Section $this->section
 * @param SectionWidgetList $this->sectionWidgetList
 */
?>
<h2><?php echo $this->section->getName(); ?></h2>
<div class="interfaceBox">
	<div class="titleBar">Widgets</div>
	<table>
	<tr><th>Widget</th><th>Panel</th><th>Order</th></tr>
	<?php
		foreach($this->sectionWidgetList as $widget)
		{
			echo "
			<tr><td><button type=\"button\" class=\"deleteSmall\" onclick=\"document.location.href='".BASE_URL."/sections/removeWidget.php?sectionWidget_id={$widget->getId()}';\">delete</button></td>
				<td>{$widget->getName()}</td>
				<td>{$widget->getPanel()}</td>
				<td>{$widget->getLayout_order()}</td></tr>
			";
		}
	?>
	</table>
</div>

<div class="interfaceBox">
	<div class="titleBar">Available Widgets</div>
	<table>
	<?php
		$list = new WidgetInstallationList();
		$list->find();
		foreach($list as $widget)
		{
			if (!$this->section->hasWidget($widget))
			{
				echo "
				<tr><td><button type=\"button\" class=\"addSmall\" onclick=\"window.open('".BASE_URL."/sections/addWidget.php?section_id={$this->section->getId()};widget_id={$widget->getId()}');\">Add</button></td>
					<td>{$widget->getName()}</td>
					<td>{$widget->getDescription()}</td></tr>
				";
			}
		}
	?>
	</table>
</div>
