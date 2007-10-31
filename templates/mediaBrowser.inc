<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param string $this->title
 */
	if (!isset($this->title)) { $this->title = "Media Browser"; }
	include APPLICATION_HOME.'/includes/xhtmlStrictHeader.inc';
?>
<div class="left sidebar">
	<div><div class="titleBar">Departments</div>
		<ul>
		<?php
			$departments = new DepartmentList();
			$departments->find();
			$url = new URL($_SERVER['PHP_SELF']);
			foreach($departments as $department)
			{
				$name = View::escape($department->getName());
				$url->parameters['department_id'] = $department->getId();
				echo "<li><a href=\"{$url->getURL()}\">$name</a></li>";
			}
		?>
		</ul>
	</div>
</div>
<div id="backendContent">
	<?php
		include FRAMEWORK.'/errorMessages.inc';
		$this->includeBlocks();
	?>
</div>
<?php
	include FRAMEWORK.'/xhtmlFooter.inc';
?>