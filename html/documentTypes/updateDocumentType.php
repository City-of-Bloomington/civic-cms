<?php
/**
 * @copyright Copyright (C) 2006-2008 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param GET documentType_id
 */
verifyUser(array('Administrator','Webmaster'));

if (isset($_GET['documentType_id'])) { $documentType = new DocumentType($_GET['documentType_id']); }
if (isset($_POST['documentType']))
{
	$documentType = new DocumentType($_POST['documentType_id']);
	foreach($_POST['documentType'] as $field=>$value)
	{
		$set = "set".ucfirst($field);
		$documentType->$set($value);
	}
	$documentInfoFields = array();
	foreach($_POST['documentInfoFields'] as $field=>$order)
	{
		if ($order) { $documentInfoFields[$order] = $field; }
	}
	$documentType->setDocumentInfoFields($documentInfoFields);

	try
	{
		$documentType->save();
		Header("Location: home.php");
		exit();
	}
	catch (Exception $e) { $_SESSION['errorMessages'][] = $e; }
}

$template = new Template('backend');
$template->blocks[] = new Block('documentTypes/updateDocumentTypeForm.inc',array('documentType'=>$documentType));
echo $template->render();
