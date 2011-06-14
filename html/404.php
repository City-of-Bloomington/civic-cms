<?php
/**
 * @copyright 2007-2010 City of Bloomington, Indiana
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
$u = new URL($_SERVER['SERVER_NAME'].$_SERVER['REQUEST_URI']);
$path = str_replace(BASE_URL.'/','',$u->getURL());
$url = urldecode($path);
$url = explode('?',$url);

$title = $url[0];
if (substr($title,-1)=='/') {
	$title = substr($title,0,-1);
}
$wikiTitle = WikiMarkup::wikify($title);

$list = new DocumentList(array('wikiTitle_or_alias'=>$wikiTitle));
$count = count($list);
switch (count($list)) {
	case 0:
		header('http/1.1 404 Not Found');
		header('Status: 404 Not Found');
		FileNotFoundLog::log($path);
		$template = new Template();
		$template->blocks[] = new Block('errorMessages/404.inc');
		$template->blocks[] = new Block('search/searchForm.inc');
		echo $template->render();
	break;

	case 1:
		if (isset($url[1])) {
			$params = explode(';',$url[1]);
			foreach($params as $param) {
				$param = explode('=',$param);
				if (count($param)==2) {
					$_GET[$param[0]] = $param[1];
				}
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
