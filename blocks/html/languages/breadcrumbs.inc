<?php
/**
 * @copyright Copyright (C) 2007-2008 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param Language $this->language (optional)
 */
if (isset($this->language))
{
	$title = "{$this->language->getNative()} ({$this->language->getEnglish()})";
}
else
{
	$title = 'Translations';
}
?>
<div id="pageTitle">
	<div class="breadcrumbs">
	<ul><li><a href="<?php echo BASE_URL; ?>">Home</a></li>
		<li><a href="<?php echo BASE_URL; ?>/languages">Languages</a></li>
	</ul>
	</div>
	<h1><?php echo $title; ?></h1>
</div>