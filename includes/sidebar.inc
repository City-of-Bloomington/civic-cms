<?php
/**
 * @copyright Copyright (C) 2006 Cliff Ingham. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 */
/*
	$this->document
*/
?>
<div id="sidebar">
	<?php
		if (isset($_SESSION['USER']))
		{
			if (in_array("Administrator",$_SESSION['USER']->getRoles())) { include(APPLICATION_HOME."/includes/sidebarBoxes/Administrator.inc"); }
			if (in_array("Webmaster",$_SESSION['USER']->getRoles())) { include(APPLICATION_HOME."/includes/sidebarBoxes/Webmaster.inc"); }
		}

		if (isset($this->widgets))
		{
			foreach($this->widgets as $widget)
			{
				include(APPLICATION_HOME."/widgets/$widget/sidebar/{$widget}.inc");
			}
		}
		include(APPLICATION_HOME."/includes/sidebarBoxes/Facets.inc");

		if (isset($this->document))
		{
			$languages = $this->document->getLanguages();
			#if (count($languages) > 1)
			#{
				include(APPLICATION_HOME."/includes/documents/languages.inc");
			#}
		}
	?>
</div>