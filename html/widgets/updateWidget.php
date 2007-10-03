<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param GET widget_id
 */
	verifyUser(array('Administrator','Webmaster'));

	if (isset($_GET['widget_id'])) { $widget = new WidgetInstallation($_GET['widget_id']); }

	if (isset($_POST['widget']))
	{
		$widget = new WidgetInstallation($_POST['widget_id']);

		foreach($_POST['widget'] as $field=>$value)
		{
			$set = 'set'.ucfirst($field);
			$widget->$set($value);
		}
		$widget->setGlobal_data($widget->getWidget()->serializePost($_POST));

		try
		{
			$widget->save();
			Header('Location: home.php');
			exit();
		}
		catch (Exception $e) { $_SESSION['errorMessages'][] = $e; }
	}

	$template = new Template();
	$template->blocks[] = new Block('widgets/updateWidgetForm.inc',array('widget'=>$widget));
	$template->render();
?>