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
		$string = trim($string);
		$string = preg_replace('/[^A-Za-z0-9_\s]/','',$string);
		$string = preg_replace('/\s+/','_',$string);
		return strtolower($string);
	}

	public static function parse($string)
	{
		return preg_replace_callback('/\[[^]]+\]/',array('WikiMarkup','callback'),$string);
	}

	public static function callback($matches)
	{
		# Strip off the brackets
		$link = substr($matches[0],1,-1);
		if (ereg("\|",$link)) { list($linkText,$link) = explode('|',$link); }

		# You should only be able to specify either an attachment or an anchor.
		# Having both in a link makes no sense.
		if (ereg("\^",$link)) { list($link,$attachmentFilename) = explode('^',$link); }
		if (ereg("\#",$link)) { list($link,$anchor) = explode('#',$link); }

		if ($link)
		{
			$wikiTitle = WikiMarkup::wikify($link);
			$list = new DocumentList(array('wikiTitle_or_alias'=>$wikiTitle));
			if (count($list))
			{
				# Draw a link to the first document we find
				$document = $list[0];
				$title = View::escape($document->getTitle());

				$url = $document->getURL();
			}
			else
			{
				# We couldn't find a Document Title that matched
				# Check if this is supposed to be a full URL
				$pattern = '/(www\.|https?:\/\/)([\w\.]+)([\#\,\/\~\?\&\=\;\%\-\w+\.]+)/';
				if (preg_match($pattern,$link))
				{
					# If they didn't put in an http://, we need to add it to the url
					$url = $link;
					if (!ereg('://',$url)) { $url = 'http://'.$url; }
				}
			}
		}
		if (isset($attachmentFilename))
		{
			$list = new MediaList(array('filename'=>$attachmentFilename));
			if (count($list))
			{
				$media = $list[0];
				$title = View::escape($media->getTitle());

				$url = $media->getURL();
			}
		}
		if (isset($anchor)) { $url = isset($url) ? $url."#$anchor" : "#$anchor"; }

		if (isset($url))
		{
			$title = isset($title) ? $title : $url;
			$title = isset($linkText) ? $linkText : $title;
			return "<a href=\"$url\">$title</a>";
		}
		else { return $matches[0]; }
	}
}
?>