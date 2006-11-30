<?php
/**
 * @copyright Copyright (C) 2006 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 */
/*
	$this->document
*/
	$languages = $this->document->getLanguages();
	#if (count($languages) > 1)
	#{
		$page = new URL($_SERVER['REQUEST_URI']);
		echo "<div>";
		foreach($languages as $language)
		{
			$page->parameters['lang'] = $language->getCode();
			echo "<a href=\"{$page->getURL()}\">{$language->getNative()}</a>";
		}
		echo "</div>";
	#}


	echo $this->document->getContent();
?>