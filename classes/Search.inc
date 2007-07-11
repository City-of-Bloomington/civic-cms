<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * Class for working with a previously created search index.  Before this class
 * will work, you must have run /scripts/install_search.php
 */
	ini_set('include_path',ini_get('include_path').ZEND);
	require_once('Zend/Search/Lucene.php');

	class Search
	{
		private $search;

		public function __construct()
		{
			$this->search = Zend_Search_Lucene::open(APPLICATION_HOME.'/data/search_index');
		}

		public function addDocument($document)
		{
			$doc = new Zend_Search_Lucene_Document();
			$doc->addField(Zend_Search_Lucene_Field::Keyword('document_id',$document->getId()));
			$doc->addField(Zend_Search_Lucene_Field::UnStored('title',$document->getTitle()));
			$doc->addField(Zend_Search_Lucene_Field::UnStored('content',implode("\n",$document->getContent())));
			$this->search->addDocument($doc);
		}

		public function removeDocument($document)
		{
			$term  = new Zend_Search_Lucene_Index_Term($document->getId(),'document_id');
			$queryTerm = new Zend_Search_Lucene_Search_Query_Term($term);

			$query = new Zend_Search_Lucene_Search_Query_Boolean();
			$query->addSubquery($queryTerm, true /* required */);

			$hits = $this->search->find($query);
			foreach($hits as $hit)
			{
				$this->search->delete($hit->id);
			}
		}

		public function updateDocument($document)
		{
			$this->removeDocument($document);
			$this->addDocument($document);
		}

		public function find($query)
		{
			$results = array();
			$hits = $this->search->find($query);
			foreach($hits as $hit)
			{
				$results[] = new Document($hit->document_id);
			}
			return $results;
		}

		public function count() { return $this->search->count(); }
		public function numDocs() { return $this->search->numDocs(); }
	}
?>