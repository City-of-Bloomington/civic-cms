<?php
/**
 * @copyright Copyright (C) 2007-2008 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
?>
<div class="interfaceBox">
<h2><?php
		if (userHasRole('Administrator'))
		{
			echo "<a href=\"".BASE_URL."/languages/addLanguage.php\" class=\"addSmall button\">Add</a>";
		}
	?>
	Languages
</h2>
<p>Use the links below to search our website for documents that have been translated into that language.</p>
<ul>
<?php
	$list = new LanguageList();
	$list->find();
	foreach($list as $language)
	{
		# Find out how many documents we have
		$documentCount = $language->getNumDocuments();

		# Admininstrators need to see the whole list no matter what.
		# Folks browsing the site only need to see the languages that have documents
		# We don't want to list english
		if ((userHasRole('Administrator') || $documentCount) && $language->getCode()!= 'en')
		{
			$button = userHasRole('Administrator') ? "<a href=\"".BASE_URL."/languages/updateLanguage.php?language_id={$language->getId()}\" class=\"editSmall button\">Edit</a>" : '';
			echo "
			<li>$button
				<a href=\"".BASE_URL."/languages/documents.php?language={$language->getCode()}\">
				{$language->getNative()} ({$language->getEnglish()}) ($documentCount)</a>
			</li>
			";
		}
	}
?>
</ul>
</div>
