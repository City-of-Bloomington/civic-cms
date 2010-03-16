<?xml version="1.0" encoding="UTF-8"?>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.1//EN" "http://www.w3.org/TR/xhtml11/DTD/xhtml11.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="en" >
<?php
	$dir = dirname(__FILE__);
	include $dir.'/partials/header.inc';
?>
<boyd>
	<div id="main-content-container">
		<div id="leftSidebar" class="left sidebar">
			<div><h1>Departments</h1>
				<ul>
				<?php
					$departments = new DepartmentList();
					$departments->find();
					$url = new URL($_SERVER['SERVER_NAME'].$_SERVER['SCRIPT_NAME']);
					foreach ($departments as $department) {
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
				include FRAMEWORK.'/errorMessages.php';
				echo $this->includeBlocks();
			?>
		</div>
	</div>
</body>
</html>
<?php include $dir.'/partials/garbageCollection.inc'; ?>
