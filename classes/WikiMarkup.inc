<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
class WikiMarkup
{
	/**
	 * @param string $string
	 * Formats a string to be safely used as a portion of a URL
	 */
	public static function wikify($string)
	{
		$string = html_entity_decode(trim($string));
		$string = preg_replace('/[^A-Za-z0-9_\-\s]/','',$string);
		$string = preg_replace('/[\s\-_]+/','-',$string);
		return strtolower($string);
	}

	/**
	 * Parses a string and replaces anything inside of square brackets that
	 * the callback function knows about
	 * @param string $string
	 */
	public static function parse($string)
	{
		# Grabs everything that's inside of square brackets
		return preg_replace_callback('/\[[^]]+\]/',array('WikiMarkup','callback'),$string);
	}

	/**
	 * Replaces content inside of square brackets.
	 * This function knows how to create links from markup in the form of
	 * [/some/relative/path]
	 * [http://some.external.url]
	 * [file:filename.ext]
	 * [calendar:Calendar Name]
	 * [anchor:Name]
	 * [mailto:EmailAddress]
	 * [Document Title#anchor]
	 *
	 * All of these can be prepended with custom text for the link, using the
	 * pipe to seperate
	 * [My Custom Text|file:filename.pdf]
	 * [Something Special|Document Title]
	 */
	public static function callback($matches)
	{
		# Strip off the brackets
		$link = substr($matches[0],1,-1);
		if (preg_match('/\|/',$link)) { list($linkText,$link) = explode('|',$link); }

		# Links starting with slash get treated like relative links
		if ($link[0]=='/')
		{
			$title = isset($linkText) ? $linkText : $link;
			return "<a href=\"$link\">$title</a>";
		}

		# Check if this is supposed to be a full URL
		$pattern = '/(www\.|https?:\/\/)([\w\.]+)([\#\,\/\~\?\&\=\;\%\-\w+\.]+)/';
		if (preg_match($pattern,$link))
		{
			# If they didn't put in an http://, we need to add it to the url
			if (!preg_match('/:\/\//',$link)) { $link = 'http://'.$link; }

			$title = isset($linkText) ? $linkText : $link;

			# They should not be trying to do full URLS to bloomington.in.gov
			if (preg_match('/bloomington.in.gov/',$link)) { return "<span style=\"background-color:red\">[$title]</span>"; }
			else { return "<a href=\"$link\">$title</a>"; }
		}

		# Check for all the colon specified link types
		if (preg_match('/:/',$link))
		{
			list($type,$link) = explode(':',$link);
			switch ($type)
			{
				case 'file':
					$list = new MediaList(array('filename'=>$link));
					if (count($list))
					{
						$media = $list[0];
						if (!isset($linkText)) { $linkText = View::escape($media->getTitle()); }
						return "<a href=\"{$media->getURL()}\" class=\"{$media->getExtension()}\">$linkText</a>";
					}
				break;

				case 'location':
				break;

				case 'calendar':
					$calendar = new Calendar($link);
					if ($calendar->getId())
					{
						$url = BASE_URL.'/calendars/home.php?calendar_id='.$calendar->getId();
					}
				break;

				case 'event':
				break;

				case 'language':
				break;

				case 'anchor':
					if (isset($linkText)) { return "<a name=\"$link\">$linkText</a>"; }
					else { return "<a name=\"$link\" />"; }
				break;

				case 'mailto':
					$url = "mailto:$link";
				break;

			}
			if (isset($url))
			{
				$title = isset($linkText) ? $linkText : $url;
				return "<a href=\"$url\">$title</a>";
			}
		}


		# If we've got down here, all that's left is to check for Document title
		if (preg_match('/\#/',$link)) { list($title,$anchor) = explode('#',$link); }
		else { $title = $link; }
		if ($title)
		{
			$wikiTitle = WikiMarkup::wikify($link);
			$list = new DocumentList(array('wikiTitle_or_alias'=>$wikiTitle));
			if (count($list))
			{
				# Draw a link to the first document we find
				$document = $list[0];
				if (!isset($linkText)) { $linkText = View::escape($document->getTitle()); }
				$url = $document->getURL();
			}
		}
		if (isset($anchor)) { $url = isset($url) ? "$url#$anchor" : "#$anchor"; }
		if (isset($url))
		{
			$linkText = isset($linkText) ? $linkText : $url;
			return "<a href=\"$url\">$linkText</a>";
		}
		else { return "<span style=\"background-color:red\">$matches[0]</span>"; }
	}
}
?>