<?php
/**
 * @copyright Copyright (C) 2006,2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param Document $this->document
 */
	if (isset($_SESSION['USER']) && $this->document->permitsEditingBy($_SESSION['USER']))
	{
		$editButton = "<button type=\"button\" class=\"editSmall\" onclick=\"window.open('".BASE_URL."/documents/updateDocument.php?document_id={$this->document->getId()}');\">Edit</button>";
	}
	else { $editButton = ""; }

	$title = View::escape($this->document->getTitle());
	echo "<h2>$editButton $title</h2>";


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
			foreach($this->getContent() as $l=>$content)
			{
				if ($content)
				{
					$lang = $l;
					break;
				}
			}
		}
	}
	if ($this->document->PHPIsEnabled())
	{
		include $this->document->getContentFilename($lang);
	}
	else
	{
		echo WikiMarkup::parse($this->document->getContent($lang));
	}
?>