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
	<div id="main-content-container">
		<?php
			include $dir.'/partials/leftSidebar.inc';
			include $dir.'/partials/rightSidebar.inc';

			$lang = new Language(DEFAULT_LANGUAGE);
			if (isset($_SESSION['LANGUAGE']) && $_SESSION['LANGUAGE']) {
				try {
					$lang = new Language($_SESSION['LANGUAGE']);
				}
				catch (Exception $e) {
				}
			}

			$languageDirection = $lang->getDirection()=='rtl' ? 'dir="rtl"' : '';
		?>
		<div id="mainContent" <?php echo "xml:lang=\"{$lang->getCode()}\" lang=\"{$lang->getCode()}\" $languageDirection"; ?>>
		<?php
			include FRAMEWORK.'/errorMessages.php';

			echo $this->includeBlocks();

			$panel = new Panel('mainContent');
			$widgets = isset($this->document)
					? $panel->getWidgets($this->document)
					: $panel->getWidgets();

			foreach ($widgets as $widget) {
				$widget->render($this);
			}
		?>
		</div>
	</div>
	<?php include $dir.'/partials/footer.inc'; ?>
</body>
</html>
<?php include $dir.'/partials/garbageCollection.inc'; ?>
