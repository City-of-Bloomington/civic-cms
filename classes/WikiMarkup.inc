<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
class WikiMarkup
{
	public static $CURRENT_URL = null;

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
		# This is a recursive regular expression, matching balanced square brackets
		$pattern = "/\[((?>[^][]+)|(?R))*\]/";

		# The callback function will determine what to do with each type
		# of thing found in the square brackets
		return preg_replace_callback($pattern,array('WikiMarkup','callback'),$string);
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

		# See if there's caption stuff.  LinkText is the custom content the
		# users have included
		if (preg_match("/\|[^]]*$/",$link))
		{
			preg_match("/(.*)(\|[^]]*$)/",$link,$m);
			$linkText = $m[1];
			# Strip the pipe '|' off the link
			$link = substr($m[2],1);
		}
		else { $linkText = null; }

		# Links starting with slash get treated like relative links
		if (substr($link,0,1)=='/')
		{
			return self::relativeLinkMarkup($link,$linkText);
		}

		# Check if this is supposed to be a full URL
		$fullURLPattern = '/^(www\.|https?:\/\/)([\w\.]+)([\#\,\/\~\?\&\=\;\%\-\w+\.]+)/';
		if (preg_match($fullURLPattern,$link))
		{
			return self::fullURLMarkup($link,$linkText);
		}

		# Check for all the colon specified link types
		if (preg_match('/:/',$link))
		{
			preg_match('/^([^:]*):(.*)/',$link,$matches);
			$type = trim($matches[1]);
			$linkTarget = trim($matches[2]);

			# Colon specified types are declared as private functions
			# They are written at the bottom of this script
			$parseFunction = $type.'Markup';
			if (method_exists('WikiMarkup',$parseFunction) && $markup = self::$parseFunction($linkTarget,$linkText))
			{
				return $markup;
			}
		}

		# Check for a link to a Document
		if ($markup = self::documentLinkMarkup($link,$linkText))
		{
			return $markup;
		}

		# We could not find a match for the syntax they typed.  They must have typed
		# something invalid.  Make it big and red, so they don't do it again
		return "<span class=\"badlink\">$matches[0]</span>";
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

	/**
	 * Parses the target and returns appropriate markup for relative links
	 * @param string $linkTarget This should become the URL in the HREF
	 * @param string $linkText This should used as the content of the <a> tag
	 */
	/*
		Becuase we're using recursion to parse all the balannced square brackets
		We have to keep track of when we're inside of <a> tags.  <a> tags are
		not allowed to be nested.

		What we're trying to do is defer <a> tag rendering to the innermost
		content.  In order to do this we keep track of the CURRENT_URL.

		The order of things is:
		1 set CURRENT_URL to the link the parse call is asked to render
		2 parse any inner content (If there are any hrefs in the inner content
			the inner calls will reset CURRENT_URL
		3 Check to see if CURRENT_URL is still the same as the link you're
			trying to render.
			If it is, go ahead and render the link
			If it has changed, then the inner content has a link
				In this case, just output the inner content
		4 Set CURRENT_URL to null, so that outer calls know somethings changed
	*/
	private static function relativeLinkMarkup($link,$linkText=null)
	{
		# Tell all inner parse calls that they are inside of
		# the link we're handling here
		self::$CURRENT_URL = $link;

		# Parse the inner custom content for more square brackets
		$title = $linkText ? self::parse($linkText) : $link;

		if (self::$CURRENT_URL == $link)
		{
			self::$CURRENT_URL = null;
			$link = BASE_URL.$link;
			return "<a href=\"$link\">$title</a>";
		}
		else
		{
			self::$CURRENT_URL = null;
			return $title;
		}
	}

	private static function fullURLMarkup($link,$linkText=null)
	{
		# BAD URLS are specified in configuration.inc
		global $BAD_LINK_EXPRESSIONS;

		# They should not be trying to do URLs to bad places
		foreach($BAD_LINK_EXPRESSIONS as $regex)
		{
			if (preg_match($regex,$link)) { return "<span class=\"badlink\">[$link]</span>"; }
		}

		# If they didn't put in an http://, we need to add it to the url
		if (!preg_match('/:\/\//',$link)) { $link = 'http://'.$link; }

		self::$CURRENT_URL = $link;
		$title = $linkText ? self::parse($linkText) : $link;
		if (self::$CURRENT_URL != $link)
		{
			self::$CURRENT_URL = null;
			return $title;
		}
		else
		{
			self::$CURRENT_URL = null;
			return "<a href=\"$link\">$title</a>";
		}
	}

	/*
		Document markup must make sure to set a VALID URL in
		CURRENT_URL before parsing the linkText.  The parse()
		must assume that CURRENT_URL is always a valid URL
	*/
	private static function documentLinkMarkup($link,$linkText=null)
	{
		# For Document Links, we must look up the Document first, to
		# to make sure we have a valid $url
		$class = '';
		if (preg_match('/\#/',$link)) { list($document_id,$anchor) = explode('#',$link); }
		else { $document_id = $link; }
		if ($document_id)
		{
			$wikiTitle = WikiMarkup::wikify($document_id);
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
			self::$CURRENT_URL = $url;
			$linkText = $linkText ? self::parse($linkText) : null;
			if (self::$CURRENT_URL==$url)
			{
				self::$CURRENT_URL = null;
				$linkText = $linkText ? $linkText : $url;
				return "<a href=\"$url\" $class>$linkText</a>";
			}
			else
			{
				self::$CURRENT_URL = null;
				return $linkText;
			}
		}
		else { return self::parse($linkText); }
	}

	#----------------------------------------------------------------
	# Colon-specifed Markup functions.
	# These functions parse the target and return appropriate markup if they can
	# find the target in the system.  If not, they should return false
	#----------------------------------------------------------------
	private static function fileMarkup($linkTarget,$linkText=null)
	{
		try
		{
			$media = new Media($linkTarget);

			self::$CURRENT_URL = $media->getURL();
			$title = $linkText ? self::parse($linkText) : null;

			# If we didn't render an href inside of the linkText
			if (self::$CURRENT_URL == $media->getURL('original'))
			{
				# We should go ahead and render this href
				if (!$title) { $title = View::escape($media->getTitle()); }
				$type = strtoupper($media->getExtension());
				$size = self::size_readable($media->getFilesize());

				self::$CURRENT_URL = null;

				return "<a href=\"{$media->getURL('original')}\" class=\"{$media->getExtension()}\">$title <em>($type $size)</em></a>";
			}
			else
			{
				# We rendered an href inside of the linkText.  we should just
				# return that, instead of rendering an href
				self::$CURRENT_URL = null;
				return $title;
			}
		}
		catch (Exception $e)
		{
			self::$CURRENT_URL = null;
			return self::parse($linkText);
		}
	}

	private static function locationGroupMarkup($linkTarget,$linkText=null)
	{
		$list = ctype_digit($linkTarget) ? new LocationGroupList(array('id'=>$linkTarget)) : new LocationGroupList(array('name'=>$linkTarget));
		if (count($list))
		{
			$locationGroup = $list[0];

			self::$CURRENT_URL = $locationGroup->getURL();
			$title = $linkText ? self::parse($linkText) : null;

			if (self::$CURRENT_URL == $locationGroup->getURL())
			{
				$title = $title ? $title : View::escape($locationGroup->getName());
				self::$CURRENT_URL = null;
				return "<a href=\"{$locationGroup->getURL()}\">$title</a>";
			}
			else
			{
				self::$CURRENT_URL = null;
				return $title;
			}
		}
		else
		{
			self::$CURRENT_URL = null;
			return $linkText;
		}
	}

	private static function locationMarkup($linkTarget,$linkText=null)
	{
		$list = ctype_digit($linkTarget) ? new LocationList(array('id'=>$linkTarget)) : new LocationList(array('name'=>$linkTarget));
		if (count($list))
		{
			$location = $list[0];

			self::$CURRENT_URL = $location->getURL();
			$title = $linkText ? self::parse($linkText) : null;

			if (self::$CURRENT_URL == $location->getURL())
			{
				if (!$title) { $title = View::escape($location->getName()); }
				self::$CURRENT_URL = null;
				return "<a href=\"{$location->getURL()}\">$title</a>";
			}
			else
			{
				self::$CURRENT_URL = null;
				return $title;
			}
		}
		else
		{
			self::$CURRENT_URL = null;
			return $linkText;
		}
	}
	private static function calendarMarkup($linkTarget,$linkText=null)
	{
		$list = ctype_digit($linkTarget) ? new CalendarList(array('id'=>$linkTarget)) : new CalendarList(array('name'=>$linkTarget));
		if (count($list))
		{
			$calendar = $list[0];
			$title = View::escape($calendar->getName());
			$url = BASE_URL.'/calendars?calendar_id='.$calendar->getId();
		}
		else
		{
			$title = 'All Calendars';
			$url = BASE_URL.'/calendars';
		}

		self::$CURRENT_URL = $url;
		$title = $linkText ? self::parse($linkText) : $title;
		if (self::$CURRENT_URL == $url)
		{
			self::$CURRENT_URL = null;
			return "<a href=\"$url\">$title</a>";
		}
		else
		{
			self::$CURRENT_URL = null;
			return $linkText;
		}
	}
	private static function facetMarkup($linkTarget,$linkText=null)
	{
		$list = ctype_digit($linkTarget) ? new FacetList(array('id'=>$linkTarget)) : new FacetList(array('name'=>$linkTarget));
		if (count($list))
		{
			$facet = $list[0];

			self::$CURRENT_URL = $facet->getURL();
			$title = $linkText ? self::parse($linkText) : null;

			if (self::$CURRENT_URL == $facet->getURL())
			{
				if (!$title) { $title = View::escape($facet->getName()); }
				self::$CURRENT_URL = null;
				return "<a href=\"{$facet->getURL()}\">$title</a>";
			}
			else
			{
				self::$CURRENT_URL = null;
				return $title;
			}
		}
		else
		{
			self::$CURRENT_URL = null;
			return $linkText;
		}
	}
	private static function eventMarkup($linkTarget,$linkText=null)
	{
		if (preg_match('|^/(\d{4})/(\d{1,2})/(\d{1,2})/(.*)|',$linkTarget,$matches))
		{
			$year = $matches[1];
			$month = $matches[2];
			$day = $matches[3];
			$linkTarget = $matches[4];
		}

		try
		{
			$event = new Event($linkTarget);
			$url = new URL($event->getURL());
			if (isset($year)) { $url->date = "$year-$month-$day"; }

			self::$CURRENT_URL = $url->getURL();
			$title = $linkText ? self::parse($linkText) : null;
			if (self::$CURRENT_URL == $url->getURL())
			{
				if (!$title) { $title = View::escape($event->getTitle()); }
				self::$CURRENT_URL = null;
				return "<a href=\"$url\">$title</a>";
			}
			else
			{
				self::$CURRENT_URL = null;
				return $title;
			}
		}
		catch (Exception $e)
		{
			self::$CURRENT_URL = null;
			return $linkText;
		}
	}
	private static function languageMarkup($linkTarget,$linkText=null)
	{
		return false;
	}
	private static function anchorMarkup($linkTarget,$linkText=null)
	{
		self::$CURRENT_URL = $linkTarget;
		$title = $linkText ? self::parse($linkText) : null;

		if (self::$CURRENT_URL==$linkTarget)
		{
			self::$CURRENT_URL = null;
			if ($title) { return "<a id=\"$linkTarget\">$title</a>"; }
			else { return "<a id=\"$linkTarget\"></a>"; }
		}
		else
		{
			self::$CURRENT_URL = null;
			return $title;
		}
	}
	private static function mailtoMarkup($linkTarget,$linkText=null)
	{
		self::$CURRENT_URL = $linkTarget;
		$title = $linkText ? self::parse($linkText) : null;

		if (self::$CURRENT_URL==$linkTarget)
		{
			self::$CURRENT_URL = null;
			$url = "mailto:$linkTarget";
			if ($title) { return "<a href=\"$url\">$title</a>"; }
			else { return "<a href=\"$url\">$linkTarget</a>"; }
		}
		else
		{
			self::$CURRENT_URL = null;
			return $title;
		}
	}


	/*
		Images will work slightly different from the linkMarkup functions
		Images need to check to see if they're being used in a CURRENT_URL
		IF so, they need to render the CURRENT_URL as an HREf around the image

		If the image does end up rendering an HREF, it needs to update
		CURRENT_URL, so that the upper parse() calls know not to render theirs

		An Image needs to decide if it's going to render an HREF around the
		image tag BEFORE the caption is parsed.  Otherwise the caption
		will reset the CURRENT_URL,
	*/
	private static function imageMarkup($linkTarget,$linkText=null)
	{
		# Decide whether we're going to wrap the <img> tag with an HREF
		$imageLink = self::$CURRENT_URL ? self::$CURRENT_URL : null;

		$caption = $linkText ? self::parse($linkText) : null;

		# Parse for any left or right alignment
		if (preg_match('/^([^,]*),(left|right)/',$linkTarget,$m))
		{
			$linkTarget = $m[1];
			$align = $m[2];
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
				$width = $image->getWidth('medium');
				$height = $image->getHeight('medium');
			}
			# We couldn't find an image with that filename, just display the raw text
			else { return $caption; }
		}

		# Wrap the Image an CURRENT_URL, if there is one
		$imageTag = "<img src=\"$url\" alt=\"$alt\" width=\"$width\" height=\"$height\" />";
		if ($imageLink)
		{
			$imageTag = "<a href=\"$imageLink\">$imageTag</a>";
			self::$CURRENT_URL = null;
		}
		# If there isn't a CURRENT_URL, create a link to the Original Sized Image
		else
		{
			# Only draw this link if the picture was resized
			if ($image->getWidth()!=$width || $image->getHeight()!=$height)
			{
				$imageTag = "
				<a href=\"{$image->getURL('original')}\"
					onmouseover=\"FRAMEWORK.popupTooltip('Enlarge This Image','enlarge');\"
					onmouseout=\"FRAMEWORK.hideTooltip();\">
				$imageTag
				</a>
				";
				self::$CURRENT_URL = null;
			}
		}

		# Wrap the caption in a span
		$caption = $caption ? "<span class=\"caption\">$caption</span>" : null;

		# Add the size and alignment;
		if (isset($width) || isset($align))
		{
			$width = isset($width) ? "width:{$width}px;" : '';
			$align = isset($align) ? "float:$align;" : '';
			$style = "style=\"$width$align\"";
		}
		else { $style = ''; }

		return "<span class=\"image\" $style>$imageTag $caption</span>";
	}
	private static function thumbnailMarkup($linkTarget,$linkText=null)
	{
		# Decide whether we're going to wrap the <img> tag with an HREF
		$imageLink = self::$CURRENT_URL ? self::$CURRENT_URL : null;

		$caption = $linkText ? self::parse($linkText) : null;

		# Parse for any left or right alignment
		if (preg_match('/^([^,]*),(left|right)/',$linkTarget,$m))
		{
			$linkTarget = $m[1];
			$align = $m[2];
		}

		$list = ctype_digit($linkTarget) ? new ImageList(array('id'=>$linkTarget)) : new ImageList(array('filename'=>$linkTarget));
		if (count($list))
		{
			$image = $list[0];
			$url = BASE_URL.'/media/media.php?size=thumbnail;media_id='.$image->getId();
			$alt = View::escape($image->getTitle());
			$width = $image->getWidth('thumbnail');
			$height = $image->getHeight('thumbnail');
		}
		# We couldn't find an image with that filename, just display the raw text
		else { return $caption; }

		# Wrap the Image in in a link to CURRENT_URL, if there is one
		$imageTag = "<img src=\"$url\" alt=\"$alt\" width=\"$width\" height=\"$height\" />";
		if ($imageLink)
		{
			$imageTag = "<a href=\"$imageLink\">$imageTag</a>";
			self::$CURRENT_URL = null;
		}
		# If there isn't a CURRENT_URL, create a link to the Original Sized Image
		else
		{
			# Only draw this link if the picture was resized
			if ($image->getWidth()!=$width || $image->getHeight()!=$height)
			{
				$imageTag = "
				<a href=\"{$image->getURL('original')}\"
					onmouseover=\"FRAMEWORK.popupTooltip('Enlarge This Image','enlarge');\"
					onmouseout=\"FRAMEWORK.hideTooltip();\">
				$imageTag
				</a>
				";
				self::$CURRENT_URL = null;
			}
		}

		# Wrap the caption in a span
		$caption = $caption ? "<span class=\"caption\">$caption</span>" : null;

		# Add the size and alignment;
		if (isset($width) || isset($align))
		{
			$width = isset($width) ? "width:{$width}px;" : '';
			$align = isset($align) ? "float:$align;" : '';
			$style = "style=\"$width$align\"";
		}
		else { $style = ''; }

		return "<span class=\"image thumbnail\" $style>$imageTag $caption</span>";
	}
}
