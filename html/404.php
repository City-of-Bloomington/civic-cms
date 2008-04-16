<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
 	$u = new URL($_SERVER['SERVER_NAME'].$_SERVER['REQUEST_URI']);
	$path = str_replace(BASE_URL.'/','',$u->getURL());
	$url = urldecode($path);
 	$url = explode('?',$url);

 	$title = $url[0];
 	if (substr($title,-1)=='/') { $title = substr($title,0,-1); }
	$wikiTitle = WikiMarkup::wikify($title);

	$list = new DocumentList(array('wikiTitle_or_alias'=>$wikiTitle));
	switch (count($list))
	{
		case 0:
			FileNotFoundLog::log($path);

			$string = str_replace('-',' ',$wikiTitle);
			$template = new Template();
			$template->blocks[] = new Block('404.inc');
			try
			{
				$search = new Search();
				$results = $search->find($string,null,false);

				$template->blocks[] = new Block('search/searchForm.inc',array('search'=>$string));
				$template->blocks[] = new Block('search/results.inc',array('results'=>$results));
			}
			catch (Exception $e) { exception_handler($e); }
			echo $template->render();
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
			$template->blocks[] = new Block('search/results.inc',array('results'=>$list));
			echo $template->render();
	}
