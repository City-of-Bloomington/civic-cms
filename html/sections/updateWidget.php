<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param GET sectionWidget_id
 * Used to edit a single instance of a widget in a section
 */
	if (isset($_GET['sectionWidget_id'])) { $sectionWidget = new SectionWidget($_GET['sectionWidget_id']); }
	if (isset($_POST['sectionWidget_id']))
	{
		$sectionWidget = new SectionWidget($_POST['sectionWidget_id']);
		foreach($_POST['sectionWidget'] as $field=>$value)
		{
			$set = 'set'.ucfirst($field);
			$sectionWidget->$set($value);
		}
		$sectionWidget->setData($sectionWidget->getWidget()->getWidget()->serializePost($_POST));

		try
		{
			$sectionWidget->save();
			Header('Location: updateWidgets.php?section_id='.$sectionWidget->getSection_id());
			exit();
		}
		catch (Exception $e) { $_SESSION['errorMessages'][] = $e; }
	}

	$template = new Template();
	$template->blocks[] = new Block('sections/updateSectionWidgetForm.inc',array('sectionWidget'=>$sectionWidget));
	echo $template->render();
?>
