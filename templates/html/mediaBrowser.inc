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
<div id="main-content-container">
	<div id="leftSidebar" class="left sidebar">
		<div><h1>Departments</h1>
			<ul>
			<?php
				$departments = new DepartmentList();
				$departments->find();
				$url = new URL($_SERVER['SERVER_NAME'].$_SERVER['SCRIPT_NAME']);
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
			echo $this->includeBlocks();
		?>
	</div>
</div>
<?php
	include APPLICATION_HOME.'/includes/xhtmlFooter.inc';
?>