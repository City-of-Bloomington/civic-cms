<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param char $this->letter
 */
?>
<div class="breadcrumbs">
<ul><li><a href="<?php echo BASE_URL; ?>">Home</a></li>
	<li><a href="<?php echo BASE_URL; ?>/documents/az_index.php">A-Z Index</a></li>
</ul>
</div>
<div class="tabBar">
<ul>
<?php
	$alphabet = array('A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z');
	foreach($alphabet as $letter)
	{
		$class = ($this->letter == $letter) ? 'class="current"' : '';
		echo "<li><a href=\"".BASE_URL."/documents/az_index.php?letter=$letter\" $class>$letter</a></li>";
	}
?>
</ul>
</div>
<?php
	echo "<h1>{$this->letter}</h1>";

	$service = new DocumentType('Service');
	$list = new DocumentList(array('documentType_id'=>$service->getId(),'first_letter'=>$this->letter));
	if (count($list))
	{
		echo '<h3>Services</h3><ul>';
		foreach($list as $document)
		{
			$title = View::escape($document->getTitle());
			echo "<li><a href=\"".BASE_URL."/documents/viewDocument.php?document_id={$document->getId()}\">$title</a></li>";
		}
		echo '</ul>';
	}

	$list = new DepartmentList(array('first_letter'=>$this->letter));
	if (count($list))
	{
		echo '<h3>Departments</h3><ul>';
		foreach($list as $department)
		{
			if ($department->getDocument_id())
			{
				$title = View::escape($department->getDocument()->getTitle());
				echo "<li><a href=\"".BASE_URL."/documents/viewDocument.php?document_id={$department->getDocument()->getId()}\">$title</a></li>";
			}
		}
		echo '</ul>';
	}
?>
