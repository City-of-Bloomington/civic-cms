<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param Section $this->section
 * @param SectionWidgetList $this->sectionWidgetList
 */
?>
<h1><?php echo $this->section->getName(); ?></h1>
<div class="interfaceBox">
	<h2>Widgets</h2>
	<table>
	<tr><th></th><th>Widget</th><th>Panel</th><th>Order</th></tr>
	<?php
		foreach($this->sectionWidgetList as $widget)
		{
			$name = View::escape($widget->getName());
			echo "
			<tr><td><a class=\"editSmall\" href=\"".BASE_URL."/sections/updateWidget.php?sectionWidget_id={$widget->getId()}\">Edit</a>
					<a class=\"deleteSmall\" href=\"".BASE_URL."/sections/removeWidget.php?sectionWidget_id={$widget->getId()}\">delete</a></td>
				<td>$name</td>
				<td>{$widget->getPanel()}</td>
				<td>{$widget->getLayout_order()}</td></tr>
			";
		}
	?>
	</table>
</div>

<div class="interfaceBox">
	<h2>Available Widgets</h2>
	<table>
	<?php
		$list = new WidgetInstallationList();
		$list->find();
		foreach($list as $widget)
		{
			#if (!$this->section->hasWidget($widget))
			#{
				$name = View::escape($widget->getName());
				$description = View::escape($widget->getDescription());
				echo "
				<tr><td><a class=\"addSmall\" href=\"".BASE_URL."/sections/addWidget.php?section_id={$this->section->getId()};widget_id={$widget->getId()}\">Add</a></td>
					<td>$name</td>
					<td>$description</td></tr>
				";
			#}
		}
	?>
	</table>
</div>
