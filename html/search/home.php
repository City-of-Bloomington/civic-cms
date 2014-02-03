<?php
/**
 * @copyright 2007-2014 City of Bloomington, Indiana
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param GET search
 * @param GET type Document, Event
 */
$template = new Template();
$template->blocks[] = new Block('search/searchForm.inc');

if (isset($_GET['search']) && $_GET['search']) {
	$search = new Search();

	// Apply recordType and type FQ to only the results search.
	// The Tab search needs to go against everything, so we
	// can get the full counts of each type of result
	$tabQuery = $_GET;
	if (isset($tabQuery['recordType'])) { unset($tabQuery['recordType']); }
	if (isset($tabQuery['type']      )) { unset($tabQuery['type']);       }

	if (empty($_GET['recordType'])) {
		$_GET['recordType'] = 'document';
	}
	if ($_GET['recordType'] == 'document' && empty($_GET['type'])) {
		$_GET['type'] = 'Documents';
	}

	$tabResults  = $search->find($tabQuery);
	$pageResults = $search->find($_GET);

	$template->blocks[] = new Block('search/resultTabs.inc', ['solrObject'=>$tabResults] );
	$template->blocks[] = new Block('search/results.inc', ['results'=>Search::hydrateDocs($pageResults)]);

	// Solr rows start at 0, but pages start at 1
	$currentPage = round($pageResults->response->start/Search::ITEMS_PER_PAGE) + 1;

	$paginator = new Zend_Paginator(new SolrPaginatorAdapter($pageResults));
	$paginator->setItemCountPerPage(Search::ITEMS_PER_PAGE);
	$paginator->setCurrentPageNumber($currentPage);
	$template->blocks[] = new Block('pageNavigation.inc', ['paginator'=>$paginator]);
}
echo $template->render();
