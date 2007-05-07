<?php
	$title = "Content Manager - City of Bloomington";
	include APPLICATION_HOME.'/includes/xhtmlTransitionalHeader.inc';
	include(APPLICATION_HOME."/includes/banner.inc");
	include(APPLICATION_HOME."/includes/leftSidebar.inc");
?>
<div id="backendContent">
	<?php
		include FRAMEWORK.'/errorMessages.inc';

		$this->includeBlocks();
	?>
</div>
<?php
	include APPLICATION_HOME.'/includes/footer.inc';
	include FRAMEWORK.'/xhtmlFooter.inc';
?>