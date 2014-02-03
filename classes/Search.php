<?php
/**
 * Class for working with a previously created search index.  Before this class
 * will work, you must have run /scripts/install_search.php
 *
 * @copyright 2007-2014 City of Bloomington, Indiana
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
require_once SOLR_PHP_CLIENT.'/Apache/Solr/Service.php';
class Search
{
	public $solrClient;

	const ITEMS_PER_PAGE  = 10;

	public function __construct()
	{
		$this->solrClient = new Apache_Solr_Service(
			SOLR_SERVER_HOSTNAME,
			SOLR_SERVER_PORT,
			SOLR_SERVER_PATH
		);
	}

	/**
	 * Takes Objects from the content manager and adds them to the search index
	 * we can add support for different things from the content manager as time goes on
	 * @param Object $entry
	 */
	public function add($entry)
	{
		$document = new Apache_Solr_Document();

		if ($entry instanceof Document) {
			$recordType = 'document';
			$type = $entry->getDocumentType()->isSeperateInSearch() ? $entry->getDocumentType()->getType() : 'Documents';
			$content = strip_tags(implode("\n",$entry->getContent()));
			$combined = "{$entry->getTitle()} {$entry->getDescription()} $content";

			$document->addField('type', $type);
			$document->addField('content', $content);
		}
		elseif ($entry instanceof Event) {
			$recordType = 'event';
			$description = strip_tags($entry->getDescription());
			$combined = "{$entry->getTitle()} $description";
		}
		elseif ($entry instanceof Media) {
			$recordType = 'media';
			$combined = "{$entry->getTitle()} {$entry->getDescription()}";
		}
		else { throw new Exception('search/unknownType'); }

		$document->addField('recordKey', "{$recordType}_{$entry->getId()}");
		$document->addField('recordType', $recordType);
		$document->addField("{$recordType}_id", $entry->getId());
		$document->addField('title', $entry->getTitle());
		$document->addField('description', $entry->getDescription());
		$document->addField('combined', $combined);

		$this->solrClient->addDocument($document);
	}

	/**
	 * Removed an entry from the search index
	 *
	 * @param Object $entry
	 */
	public function remove($entry)
	{
		if ($entry instanceof Document) {
			$this->solrClient->deleteById('document_'.$entry->getId());
		}
		elseif ($entry instanceof Event) {
			$this->solrClient->deleteById('event_'.$entry->getId());
		}
		elseif ($entry instanceof Media) {
			$this->solrClient->deleteById('media_'.$entry->getId());
		}
		else { throw new Exception('search/unknownType'); }
	}

	/**
	 * Alias of add
	 *
	 * Adding a document again to Solr will update the existing record
	 */
	public function update($entry) { $this->add($entry); }

	/**
	 * Alias for Search::remove
	 */
	public function delete($entry) { $this->remove($entry); }

	/**
	 * @param array $_GET
	 * @param string type One of the types known to the Search class (see Search->add())
	 * @return SolrObject
	 */
	public function find(&$get)
	{
		// Start with all the default query values
		$query = !empty($get['search'])
			? "{!df=combined}$get[search]"
			: '*:*';
		$additionalParameters = [];


		// Pagination
		$rows = self::ITEMS_PER_PAGE;
		$startingPage = 0;
		if (!empty($get['page'])) {
			$page = (int)$get['page'];
			if ($page < 1) { $page = 1; }

			// Solr rows start at 0, but pages start at 1
			$startingPage = ($page - 1) * $rows;
		}

		// Facets
		$additionalParameters['facet'] = 'true';
		$additionalParameters['facet.field'] = ['recordType','type'];

		// FQ
		$fq = [];
		if (!empty($get['recordType'])) { $fq[] = "recordType:$get[recordType]"; }
		if (!empty($get['type']      )) { $fq[] =       "type:$get[type]";       }
		if (count($fq)) { $additionalParameters['fq'] = $fq; }

		$solrResponse = $this->solrClient->search($query, $startingPage, $rows, $additionalParameters);
		return $solrResponse;
	}

	/**
	 * @param Apache_Solr_Response $object
	 * @return array An array of CRM models based on the search results
	 */
	public static function hydrateDocs(Apache_Solr_Response $o)
	{
		$models = array();
		if (isset($o->response->docs) && $o->response->docs) {
			foreach ($o->response->docs as $doc) {
				$class = ucfirst($doc->recordType);
				$id = "{$doc->recordType}_id";
				$m = new $class($doc->$id);
				$models[] = $m;
			}
		}
		else {
			header('HTTP/1.1 404 Not Found', true, 404);
		}
		return $models;
	}

	/**
	 * Retrieves full facet counts for a query
	 *
	 * Takes a solrResponse, drops the FQ and does a facet-only query
	 * Returns the facet results
	 *
	 * @param Apache_Solr_Response $solrResponse
	 * @return Apache_Solr_Response
	 */
	public function facetQuery(Apache_Solr_Response $solrResponse)
	{
		print_r($solrResponse);
	}
}
