<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
 	$url = urldecode(basename($_SERVER['REQUEST_URI']));
 	$url = explode('?',$url);

 	$title = $url[0];
	$wikiTitle = WikiMarkup::wikify($title);

	$list = new DocumentList(array('wikiTitle_or_alias'=>$wikiTitle,'active'=>date('Y-m-d')));
	switch (count($list))
	{
		case 0:
			$_GET['search'] = str_replace('-',' ',$wikiTitle);
			include APPLICATION_HOME.'/html/documents/search.php';
		break;

		case 1:
			if (isset($url[1]))
			{
				$params = explode(';',$url[1]);
				foreach($params as $param)
				{
					$param = explode('=',$param);
					if (count($param)==2) { $_GET[$param[0]] = $param[1]; }
				}
			}
			$document = $list[0];
			$_GET['document_id'] = $document->getId();
			include APPLICATION_HOME.'/html/documents/viewDocument.php';
		break;

		default:
			$template = new Template();
			$template->blocks[] = new Block('documents/searchResults.inc',array('results'=>$list));
			$template->render();
	}
?>