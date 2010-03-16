<?php
/**
 * @copyright Copyright (C) 2007-2008 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param Document $this->document
 */
if (isset($this->document))
{
	$languages = $this->document->getLanguages();

	echo "<div id=\"languages\" class=\"tabBar\"><ul>";
		$page = new URL($_SERVER['SERVER_NAME'].$_SERVER['REQUEST_URI']);
		foreach($languages as $language)
		{
			$page->parameters['lang'] = $language->getCode();
			$class = ($language->getCode()==$_SESSION['LANGUAGE']) ? 'class="current"' : '';
			echo "<li $class><a href=\"{$page->getURL()}\">{$language->getNative()}</a></li>";
		}
	echo "</ul></div>";
}
