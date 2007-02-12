<?php
/**
 * @copyright Copyright (C) 2006 Cliff Ingham. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 */
/*
	$this->document
*/
?>
<div class="left sidebar">
	<?php
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