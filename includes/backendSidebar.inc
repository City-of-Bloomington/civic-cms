<div class="left sidebar">
<?php
	if (userHasRole('Administrator')) { include APPLICATION_HOME.'/includes/sidebarBoxes/Administrator.inc'; }
	if (userHasRole('Webmaster')) { include APPLICATION_HOME.'/includes/sidebarBoxes/Webmaster.inc'; }
	if (userHasRole('Content Creator')) { include APPLICATION_HOME.'/includes/sidebarBoxes/ContentCreator.inc'; }
?>
</div>