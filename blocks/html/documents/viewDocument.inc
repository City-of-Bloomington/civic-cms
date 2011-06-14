<?php
/**
 * @copyright Copyright (C) 2006,2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param Document $this->document
 * @param Section $this->section (optional)
 * Some documents are not in sections, and will not produce a section obejct
 */
# We want to render PHP code harmless in the markup, unless
# it's specifically enabled by some Webmaster
if ($this->document->getContent($_SESSION['LANGUAGE']))
{
	$lang = $_SESSION['LANGUAGE'];
}
else
{
	# Try and find a language we do have, English first
	if ($this->document->getContent('en')) { $lang = 'en'; }
	else
	{
		foreach($this->document->getContent() as $l=>$content)
		{
			if ($content)
			{
				$lang = $l;
				break;
			}
		}
	}
}
# If we still couldn't find a language, then somehow, this document
# has no content.  Just display a blank page in English
if (!isset($lang)) { $lang = 'en'; }


if ($this->document->PHPIsEnabled())
{
	include $this->document->getContentFilename($lang);
}
else
{
	echo WikiMarkup::parse($this->document->getContent($lang));
}
