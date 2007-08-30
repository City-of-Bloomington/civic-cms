<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * Class for working with a previously created search index.  Before this class
 * will work, you must have run /scripts/install_search.php
 */
	ini_set('include_path',ini_get('include_path').ZEND);
	require_once 'Zend/Search/Lucene.php';

	class Search
	{
		private $search;

		public function __construct()
		{
			$this->search = Zend_Search_Lucene::open(APPLICATION_HOME.'/data/search_index');
			$this->search->setMaxBufferedDocs(ZEND_SEARCH_MAX_BUFFERED_DOCS);
			$this->search->setMaxMergeDocs(ZEND_SEARCH_MAX_MERGE_DOCS);
			$this->search->setMergeFactor(ZEND_SEARCH_MERGE_FACTOR);
		}

		public function addDocument($document)
		{
			$doc = new Zend_Search_Lucene_Document();
			$doc->addField(Zend_Search_Lucene_Field::Keyword('document_id',$document->getId()));
			$doc->addField(Zend_Search_Lucene_Field::UnStored('title',$document->getTitle()));
			$doc->addField(Zend_Search_Lucene_Field::UnStored('content',strip_tags(implode("\n",$document->getContent()))));

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

		public function find($string)
		{
			try
			{
				$userQuery = Zend_Search_Lucene_Search_QueryParser::parse($string);
				$query = new Zend_Search_Lucene_Search_Query_Boolean();
				$query->addSubquery($userQuery, true /* required */);
			}
			catch (Exception $e)
			{
				# The string they entered threw an exception when we tried to parse it
				# The string is most likely invalid.
				# Clean the string of anything that could be bad and try again
				$query = strtolower($string);
				$query = preg_replace('/[^a-z0-9\s]/','',$query);
				$query = preg_replace('/\b(and)\b|\b(or)\b|\b(not)\b/',' ',$query);
			}

			$hits = $this->search->find($query);

			$results = array();
			foreach($hits as $hit)
			{
				$results[] = new Document($hit->document_id);
			}
			return $results;
		}

		public function optimize() { $this->search->optimize(); }

		public function count() { return $this->search->count(); }
		public function numDocs() { return $this->search->numDocs(); }
	}
?>