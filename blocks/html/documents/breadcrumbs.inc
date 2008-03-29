<?php
/**
 * @copyright Copyright (C) 2006,2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param Document $this->document
 * @param array $this->currentAncestors
 */
echo "
<div id=\"pageTitle\">
	<div class=\"breadcrumbs\">
		<ul>
";
		foreach($this->currentAncestors as $section)
		{
			$name = View::escape($section);
			echo "\t\t<li><a href=\"{$section->getURL()}\">$name</a></li>\n";

			$currentSection = $section->getId();
		}
echo "
		</ul>
	</div>
";

$title = View::escape($this->document->getTitle());
echo "
	<h1>$title</h1>
</div>
";

if ($this->document->getBanner_media_id())
{
	$src = $this->document->getBanner()->getURL('original');
	$alt = View::escape($this->document->getBanner()->getTitle());
	echo "
	<div id=\"pageBanner\">
		<img src=\"$src\" alt=\"$alt\" />
	</div>
	";
}
