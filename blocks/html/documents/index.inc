<?php
/**
 * @copyright Copyright (C) 2007-2008 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param char $this->letterGroup
 */
?>
<div id="pageTitle">
	<div class="breadcrumbs">
	<ul><li><a href="<?php echo BASE_URL; ?>">Home</a></li>
		<li><a href="<?php echo BASE_URL; ?>/documents/az_index.php">A-Z Index</a></li>
	</ul>
	</div>
	<h1>A-Z Index</h1>
</div>
<div class="tabBar">
<ul><li <?php if ($this->letterGroup=='A,B,C') echo 'class="current"'; ?>>
		<a href="<?php echo BASE_URL; ?>/documents/az_index.php?letterGroup=A,B,C">A - C</a>
	</li>
	<li <?php if ($this->letterGroup=='D,E,F') echo 'class="current"'; ?>>
		<a href="<?php echo BASE_URL; ?>/documents/az_index.php?letterGroup=D,E,F">D - F</a>
	</li>
	<li <?php if ($this->letterGroup=='G,H,I') echo 'class="current"'; ?>>
		<a href="<?php echo BASE_URL; ?>/documents/az_index.php?letterGroup=G,H,I">G - I</a>
	</li>
	<li <?php if ($this->letterGroup=='J,K,L') echo 'class="current"'; ?>>
		<a href="<?php echo BASE_URL; ?>/documents/az_index.php?letterGroup=J,K,L">J - L</a>
	</li>
	<li <?php if ($this->letterGroup=='M,N,O') echo 'class="current"'; ?>>
		<a href="<?php echo BASE_URL; ?>/documents/az_index.php?letterGroup=M,N,O">M - O</a>
	</li>
	<li <?php if ($this->letterGroup=='P,Q,R') echo 'class="current"'; ?>>
		<a href="<?php echo BASE_URL; ?>/documents/az_index.php?letterGroup=P,Q,R">P - R</a>
	</li>
	<li <?php if ($this->letterGroup=='S,T,U') echo 'class="current"'; ?>>
		<a href="<?php echo BASE_URL; ?>/documents/az_index.php?letterGroup=S,T,U">S - U</a>
	</li>
	<li <?php if ($this->letterGroup=='V,W,X') echo 'class="current"'; ?>>
		<a href="<?php echo BASE_URL; ?>/documents/az_index.php?letterGroup=V,W,X">V - X</a>
	</li>
	<li <?php if ($this->letterGroup=='Y-Z') echo 'class="current"'; ?>>
		<a href="<?php echo BASE_URL; ?>/documents/az_index.php?letterGroup=Y,Z">Y - Z</a>
	</li>
</ul>
</div>
<?php
	$letterGroup = array();
	$g = explode(',',$_GET['letterGroup']);
	foreach($g as $l)
	{
		$letterGroup[] = strtoupper(substr($l,0,1));
	}

	foreach($letterGroup as $letter)
	{
		echo "<h2>$letter</h2>";

		$service = new DocumentType('Service');
		$list = new DocumentList(array('documentType_id'=>$service->getId(),'first_letter'=>$letter));
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

		$list = new DepartmentList(array('first_letter'=>$letter));
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
	}
?>
