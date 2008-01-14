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
		$string = preg_replace('/[^A-Za-z0-9_\-\/\s]/','',$string);
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
		$fullURLPattern = '/^(www\.|https?:\/\/)([\w\.]+)([\#\,\/\~\?\&\=\;\%\-\w+\.]+)/';
		if (preg_match($fullURLPattern,$link))
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
			list($type,$linkTarget) = explode(':',$link,2);
			$type = trim($type);
			$linkTarget = trim($linkTarget);
			$t = isset($linkText) ? $linkText : null;

			$parse = $type.'Markup';
			# Colon specified types are declared as private functions
			# They are written at the bottom of this script
			if (method_exists('WikiMarkup',$parse) && $markup = self::$parse($linkTarget,$t))
			{
				return $markup;
			}
		}


		# If we've got down here, all that's left is to check for Document title
		$class = '';
		if (preg_match('/\#/',$link)) { list($title,$anchor) = explode('#',$link); }
		else { $title = $link; }
		if ($title)
		{
			$wikiTitle = WikiMarkup::wikify($title);
			$list = ctype_digit($wikiTitle) ? new DocumentList(array('id'=>$wikiTitle)) : new DocumentList(array('wikiTitle_or_alias'=>$wikiTitle));
			if (count($list))
			{
				# Draw a link to the first document we find
				$document = $list[0];
				if (!isset($linkText)) { $linkText = View::escape($document->getTitle()); }
				$url = $document->getURL();

				if (!$document->isActive()) { $class = 'class="unpublished"'; }
			}
		}
		if (isset($anchor)) { $url = isset($url) ? "$url#$anchor" : "#$anchor"; }
		if (isset($url))
		{
			$linkText = isset($linkText) ? $linkText : $url;
			return "<a href=\"$url\" $class>$linkText</a>";
		}
		else { return "<span style=\"background-color:red\">$matches[0]</span>"; }
	}

	public static function size_readable ($size, $retstring='%01.2f %s')
	{
        // adapted from code at http://aidanlister.com/repos/v/function.size_readable.php
        $sizes = array('B', 'KB', 'MB', 'GB');
        $lastsizestring = end($sizes);
        foreach ($sizes as $sizestring)
        {
                if ($size < 1024) { break; }
                if ($sizestring != $lastsizestring) { $size /= 1024; }
        }
        if ($sizestring == $sizes[0]) { $retstring = '%01d %s'; } // Bytes aren't normally fractional
        return sprintf($retstring, $size, $sizestring);
	}


	#----------------------------------------------------------------
	# Colon-specifed Markup functions.
	# These functions parse the target and return appropriate markup if they can
	# find the target in the system.  If not, they should return false
	#----------------------------------------------------------------
	private static function fileMarkup($linkTarget,$linkText=null)
	{
		$list = ctype_digit($linkTarget) ? new MediaList(array('id'=>$linkTarget)) : new MediaList(array('filename'=>$linkTarget));
		if (count($list))
		{
			$media = $list[0];
			if (!isset($linkText)) { $linkText = View::escape($media->getTitle()); }
			$type = strtoupper($media->getExtension());
			$size = self::size_readable($media->getFilesize());
			return "<a href=\"{$media->getURL()}\" class=\"{$media->getExtension()}\">$linkText <em>($type $size)</em></a>";
		}
		else { return false; }
	}

	private static function locationGroupMarkup($linkTarget,$linkText=null)
	{
		$list = ctype_digit($linkTarget) ? new LocationGroupList(array('id'=>$linkTarget)) : new LocationGroupList(array('name'=>$linkTarget));
		if (count($list))
		{
			$locationGroup = $list[0];
			$linkText = isset($linkText) ? $linkText : View::escape($locationGroup->getName());
			$url = BASE_URL.'/locations/?locationGroup_id='.$locationGroup->getId();
			return "<a href=\"$url\">$linkText</a>";
		}
		else { return false; }
	}

	private static function locationMarkup($linkTarget,$linkText=null)
	{
		$list = ctype_digit($linkTarget) ? new LocationList(array('id'=>$linkTarget)) : new LocationList(array('name'=>$linkTarget));
		if (count($list))
		{
			$location = $list[0];
			$linkText = isset($linkText) ? $linkText : View::escape($location->getName());
			$url = BASE_URL.'/locations/viewLocation.php?location_id='.$location->getId();
			return "<a href=\"$url\">$linkText</a>";
		}
		else { return false; }
	}
	private static function calendarMarkup($linkTarget,$linkText=null)
	{
		$list = ctype_digit($linkTarget) ? new CalendarList(array('id'=>$linkTarget)) : new CalendarList(array('name'=>$linkTarget));
		if (count($list))
		{
			$calendar = $list[0];
			$linkText = isset($linkText) ? $linkText : View::escape($calendar->getName());
			$url = BASE_URL.'/calendars/home.php?calendar_id='.$calendar->getId();
		}
		else
		{
			$linkText = isset($linkText) ? $linkText : 'All Calendars';
			$url = BASE_URL.'/calendars';
		}

		return "<a href=\"$url\">$linkText</a>";
	}
	private static function facetMarkup($linkTarget,$linkText=null)
	{
		$list = ctype_digit($linkTarget) ? new FacetList(array('id'=>$linkTarget)) : new FacetList(array('name'=>$linkTarget));
		if (count($list))
		{
			$facet = $list[0];
			$linkText = isset($linkText) ? $linkText : View::escape($facet->getName());
			$url = BASE_URL.'/facets/viewFacet.php?facet_id='.$facet->getId();
			return "<a href=\"$url\">$linkText</a>";
		}
		else { return false; }
	}
	private static function eventMarkup($linkTarget,$linkText=null)
	{
		return false;
	}
	private static function languageMarkup($linkTarget,$linkText=null)
	{
		return false;
	}
	private static function anchorMarkup($linkTarget,$linkText=null)
	{
		if (isset($linkText)) { return "<a id=\"$linkTarget\">$linkText</a>"; }
		else { return "<a id=\"$linkTarget\" />"; }
	}
	private static function mailtoMarkup($linkTarget,$linkText=null)
	{
		$linkText = isset($linkText) ? $linkText : $linkTarget;
		$url = "mailto:$linkTarget";
		return "<a href=\"$url\">$linkText</a>";
	}
	private static function imageMarkup($linkTarget,$linkText=null)
	{
		# Parse any user-specified alignment
		if (strpos($linkTarget,',')!==false)
		{
			list($linkTarget,$align) = explode(',',$linkTarget);
			$align = strtolower($align);
		}

		# If the link is a URL, use that as the src
		$fullURLPattern = '/^(www\.|https?:\/\/)([\w\.]+)([\#\,\/\~\?\&\=\;\%\-\w+\.]+)/';
		if (preg_match($fullURLPattern,$linkTarget))
		{
			$url = $linkTarget;
			$alt = '';
		}
		# Otherwise look for an image with $linkTarget as a filename
		else
		{
			$list = ctype_digit($linkTarget) ? new ImageList(array('id'=>$linkTarget)) : new ImageList(array('filename'=>$linkTarget));
			if (count($list))
			{
				$image = $list[0];
				$url = $image->getURL();
				$alt = View::escape($image->getTitle());
			}
			# We couldn't find an image with that filename, just display the raw text
			else { return false; }
		}

		$caption = isset($linkText) ? '<span class="caption">'.View::escape($linkText).'</span>' : '';
		$style = isset($align) ? "style=\"float:$align\"" : '';
		if ($caption)
		{
			return "<span class=\"image\" $style><img src=\"$url\" alt=\"$alt\" />$caption</span>";
		}
		else
		{
			return "<img src=\"$url\" alt=\"$alt\" $style />";
		}
	}
	private static function thumbnailMarkup($linkTarget,$linkText=null)
	{
		# Parse any user-specified alignment
		if (strpos($linkTarget,',')!==false)
		{
			list($linkTarget,$align) = explode(',',$linkTarget);
			$align = strtolower($align);
		}

		$list = ctype_digit($linkTarget) ? new ImageList(array('id'=>$linkTarget)) : new ImageList(array('filename'=>$linkTarget));
		if (count($list))
		{
			$image = $list[0];
			$url = BASE_URL.'/media/media.php?size=thumbnail;media_id='.$image->getId();
			$alt = View::escape($image->getTitle());
		}
		# We couldn't find an image with that filename, just display the raw text
		else { return false; }

		$caption = isset($linkText) ? '<span class="caption">'.View::escape($linkText).'</span>' : '';
		$style = isset($align) ? "style=\"float:$align\"" : '';
		if ($caption)
		{
			return "<span class=\"image thumbnail\" $style><img src=\"$url\" alt=\"$alt\" />$caption</span>";
		}
		else
		{
			return "<img src=\"$url\" alt=\"$alt\" $style />";
		}
	}
}