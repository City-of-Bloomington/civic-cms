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
		global $BAD_LINK_EXPRESSIONS;

		# Strip off the brackets
		$link = substr($matches[0],1,-1);
		if (preg_match('/\|/',$link)) { list($linkText,$link) = explode('|',$link); }

		# Links starting with slash get treated like relative links
		if (substr($link,0,1)=='/')
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
			foreach($BAD_LINK_EXPRESSIONS as $regex)
			{
				if (preg_match($regex,$link)) { return "<span style=\"background-color:red\">[$title]</span>"; }
			}
			return "<a href=\"$link\">$title</a>";
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
						$type = strtoupper($media->getExtension());
						$size = self::size_readable($media->getFilesize());
						return "<a href=\"{$media->getURL()}\" class=\"{$media->getExtension()}\">$linkText ($type $size)</a>";
					}
				break;

				case 'locationGroup':
					$list = new LocationGroupList(array('name'=>$link));
					if (count($list))
					{
						$locationGroup = $list[0];
						$linkText = isset($linkText) ? $linkText : View::escape($locationGroup->getName());
						$url = BASE_URL.'/locations/?locationGroup_id='.$locationGroup->getId();
						return "<a href=\"$url\">$linkText</a>";
					}
				break;

				case 'location':
					$list = new LocationList(array('name'=>$link));
					if (count($list))
					{
						$location = $list[0];
						$linkText = isset($linkText) ? $linkText : View::escape($location->getName());
						$url = BASE_URL.'/locations/viewLocation.php?location_id='.$location->getId();
						return "<a href=\"$url\">$linkText</a>";
					}
				break;

				case 'calendar':
					$list = new CalendarList(array('name'=>$link));
					if (count($list))
					{
						$calendar = $list[0];
						$linkText = isset($linkText) ? $linkText : View::escape($calendar->getName());
						$url = BASE_URL.'/calendars/home.php?calendar_id='.$calendar->getId();
						return "<a href=\"$url\">$linkText</a>";
					}
				break;

				case 'facet':
					$list = new FacetList(array('name'=>$link));
					if (count($list))
					{
						$facet = $list[0];
						$linkText = isset($linkText) ? $linkText : View::escape($facet->getName());
						$url = BASE_URL.'/facets/viewFacet.php?facet_id='.$facet->getId();
						return "<a href=\"$url\">$linkText</a>";
					}
				break;

				case 'event':
				break;

				case 'language':
				break;

				case 'anchor':
					if (isset($linkText)) { return "<a id=\"$link\">$linkText</a>"; }
					else { return "<a id=\"$link\" />"; }
				break;

				case 'mailto':
					$linkText = isset($linkText) ? $linkText : $link;
					$url = "mailto:$link";
					return "<a href=\"$url\">$linkText</a>";
				break;

			}
		}


		# If we've got down here, all that's left is to check for Document title
		if (preg_match('/\#/',$link)) { list($title,$anchor) = explode('#',$link); }
		else { $title = $link; }
		if ($title)
		{
			$wikiTitle = WikiMarkup::wikify($title);
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

	public static function size_readable ($size, $retstring='%01.2f %s')
	{
        // adapted from code at http://aidanlister.com/repos/v/function.size_readable.php
        $sizes = array('B', 'K', 'MB', 'GB');
        $lastsizestring = end($sizes);
        foreach ($sizes as $sizestring)
        {
                if ($size < 1024) { break; }
                if ($sizestring != $lastsizestring) { $size /= 1024; }
        }
        if ($sizestring == $sizes[0]) { $retstring = '%01d %s'; } // Bytes aren't normally fractional
        return sprintf($retstring, $size, $sizestring);
	}
}
?>