<?php
/**
 * @copyright Copyright (C) 2006,2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param Document $this->document
 */
	if (isset($_SESSION['USER']) && $this->document->permitsEditingBy($_SESSION['USER']))
	{
		$url = new URL(BASE_URL.'/documents/updateDocument.php');
		$url->parameters['document_id'] = $this->document->getId();
		$url->parameters['return_url'] = "http://$_SERVER[SERVER_NAME]$_SERVER[REQUEST_URI]";
		$editButton = "<button type=\"button\" class=\"editSmall\" onclick=\"document.location.href='$url';\">Edit</button>";
		#$editButton = "<a href=\"".BASE_URL."/documents/updateDocument.php?document_id={$this->document->getId()}\" class=\"editSmall\">Edit</a>";
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
?>