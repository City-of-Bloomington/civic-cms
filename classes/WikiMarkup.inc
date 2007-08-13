<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
class WikiMarkup
{
	public static function parse($string)
	{
		return preg_replace_callback('/\[[^]]+\]/',array('WikiMarkup','callback'),$string);
	}

	public static function callback($matches)
	{
		# Strip off the brackets
		$documentTitle = substr($matches[0],1,-1);
		if (ereg("\|",$documentTitle)) { list($linkText,$documentTitle) = explode('|',$documentTitle); }

		# You should only be able to specify either an attachment or an anchor.
		# Having both in a link makes no sense.
		if (ereg("\^",$documentTitle)) { list($documentTitle,$attachmentFilename) = explode('^',$documentTitle); }
		if (ereg("\#",$documentTitle)) { list($documentTitle,$anchor) = explode('#',$documentTitle); }

		if ($documentTitle)
		{
			$documentTitle = html_entity_decode($documentTitle);
			$list = new DocumentList(array('title_or_alias'=>$documentTitle));
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
				if (preg_match($pattern,$documentTitle))
				{
					# If they didn't put in an http://, we need to add it to the url
					$url = $documentTitle;
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