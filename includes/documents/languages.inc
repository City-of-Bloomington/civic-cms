<?php
/**
 * @copyright Copyright (C) 2006 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 */
/*
	$this->document
	$languages
*/
?>
<div><div class="titleBar">Languages</div>
<ul>
<?php
	$page = new URL($_SERVER['REQUEST_URI']);
	foreach($languages as $language)
	{
		$page->parameters['lang'] = $language->getCode();
		echo "<li><a href=\"{$page->getURL()}\">{$language->getNative()}</a></li>";
	}
?>
</ul>
</div>