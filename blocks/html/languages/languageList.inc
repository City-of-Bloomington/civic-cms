<?php
/**
 * @copyright Copyright (C) 2007-2008 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
?>
<div class="interfaceBox">
<h2>Languages</h2>
<p>Use the links below to search our website for documents that have been translated into that language.</p>
<ul>
<?php
	$list = new LanguageList();
	$list->find();
	foreach($list as $language)
	{
		# Find out how many documents we have
		$documentCount = $language->getNumDocuments();

		# Don't bother showing English
		if ($documentCount && $language->getCode()!= 'en')
		{
			echo "
			<li><a href=\"".BASE_URL."/languages/documents.php?language={$language->getCode()}\">
				{$language->getNative()} ({$language->getEnglish()}) ($documentCount)</a>
			</li>
			";
		}
	}
?>
</ul>
</div>
