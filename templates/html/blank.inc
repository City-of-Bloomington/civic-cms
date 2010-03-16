<?xml version="1.0" encoding="UTF-8"?>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.1//EN" "http://www.w3.org/TR/xhtml11/DTD/xhtml11.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="en" >
<?php
	$dir = dirname(__FILE__);
	include $dir.'/partials/header.inc';
?>
<body>
	<?php
		include $dir.'/partials/banner.inc';
		include $dir.'/partials/menubar.inc';
	?>
	<div>
		<?php
			include FRAMEWORK.'/errorMessages.php';
			echo $this->includeBlocks();
		?>
	</div>
	<?php include APPLICATION_HOME.'/includes/footer.inc'; ?>
</body>
</html>
<?php include $dir.'/partials/garbageCollection.inc'; ?>
