<?php
/**
 * @copyright Copyright (C) 2006,2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param array $this->languages
 */
?>
<div class="widget">
	<h1>Languages</h1>
	<ul>
	<?php
		$page = new URL($_SERVER['SERVER_NAME'].$_SERVER['REQUEST_URI']);
		foreach($this->languages as $language)
		{
			$page->parameters['lang'] = $language->getCode();
			echo "<li><a href=\"{$page->getURL()}\">{$language->getNative()}</a></li>";
		}
	?>
	</ul>
</div>
