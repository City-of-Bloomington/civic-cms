<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
?>
<h1>Translations</h1>
<p>Use the links below to search our website for documents that have been translated into that language.</p>
<ul>
<?php
	$list = new LanguageList();
	$list->find();
	foreach($list as $language)
	{
		# Don't bother showing English
		if ($language->getCode()!= 'en')
		{
			echo "
			<li><a href=\"".BASE_URL."/languages/documents.php?lang={$language->getCode()}\">
				{$language->getNative()}</a>
			</li>
			";
		}
	}
?>
</ul>