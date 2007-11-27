<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * Class for working with a previously created search index.  Before this class
 * will work, you must have run /scripts/install_search.php
 */
	ini_set('include_path',ini_get('include_path').ZEND.':');
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

			# Set up all the stop words.  Words that we don't want to bother indexing.
			$stopWordsFilter = new Zend_Search_Lucene_Analysis_TokenFilter_StopWords();
			$stopWordsFilter->loadFromFile(APPLICATION_HOME.'/includes/search/stopwords.txt');

			# This analyzer is case-sensitive, but it's the only one that can handle UTF8 characters
			# We'll need to remember to lowercase search queries before doing the search
			$analyzer = new Zend_Search_Lucene_Analysis_Analyzer_Common_Utf8();
			$analyzer->addFilter($stopWordsFilter);

			Zend_Search_Lucene_Analysis_Analyzer::setDefault($analyzer);
		}

		/**
		 * Takes Objects from the content manager and adds them to the search index
		 * we can add support for different things from the content manager as time goes on
		 * @param Object $entry
		 */
		public function add($entry)
		{
			$doc = new Zend_Search_Lucene_Document();

			if ($entry instanceof Document)
			{
				$doc->addField(Zend_Search_Lucene_Field::Keyword('type','Document'));
				$doc->addField(Zend_Search_Lucene_Field::Keyword('document_id',$entry->getId()));
				$doc->addField(Zend_Search_Lucene_Field::UnStored('title',$entry->getTitle(),'utf-8'));
				$doc->addField(Zend_Search_Lucene_Field::UnStored('content',strtolower(strip_tags(implode("\n",$entry->getContent()))),'utf-8'));
			}
			elseif ($entry instanceof Event)
			{
				$doc->addField(Zend_Search_Lucene_Field::Keyword('type','Event'));
				$doc->addField(Zend_Search_Lucene_Field::Keyword('event_id',$entry->getId()));
				$doc->addField(Zend_Search_Lucene_Field::UnStored('title',$entry->getTitle(),'utf-8'));
				$doc->addField(Zend_Search_Lucene_Field::UnStored('content',strtolower(strip_tags($entry->getDescription())),'utf-8'));
			}
			else { throw new Exception('search/unknownType'); }

			$this->search->addDocument($doc);
		}

		/**
		 * Removed an entry from the search index
		 * @param Obejct $entry
		 */
		public function remove($entry)
		{
			if ($entry instanceof Document)
			{
				$term  = new Zend_Search_Lucene_Index_Term($entry->getId(),'document_id');
			}
			elseif ($entry instanceof Event)
			{
				$term  = new Zend_Search_Lucene_Index_Term($entry->getId(),'event_id');
			}
			else { throw new Exception('search/unknownType'); }


			$queryTerm = new Zend_Search_Lucene_Search_Query_Term($term);
			$query = new Zend_Search_Lucene_Search_Query_Boolean();
			$query->addSubquery($queryTerm, true /* required */);

			$hits = $this->search->find($query);
			foreach($hits as $hit)
			{
				$this->search->delete($hit->id);
			}
		}

		public function update($entry)
		{
			$this->removeDocument($entry);
			$this->addDocument($entry);
		}

		public function find($string,$type=null)
		{
			$string = strtolower($string);
			try
			{
				$userQuery = Zend_Search_Lucene_Search_QueryParser::parse($string);
				$query = new Zend_Search_Lucene_Search_Query_Boolean();
				$query->addSubquery($userQuery, true /* required */);

				if ($type)
				{
					$typeTerm  = new Zend_Search_Lucene_Index_Term($type,'type');
					$typeQuery = new Zend_Search_Lucene_Search_Query_Term($typeTerm);
	                $query->addSubquery($typeQuery,true /* required */);
				}
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
				switch ($hit->type)
				{
					case 'Document':
						try { $results['documents'][] = new Document($hit->document_id); }
						catch(Exception $e)
						{
							# If there's a failure with the Document, just don't add anything to the results
						}
					break;

					case 'Event':
						try { $results['events'][] = new Event($hit->event_id); }
						catch(Exception $e)
						{
							# If there's a failure with the Event, just don't add anything to the results
						}
					break;
				}
			}
			return $results;
		}

		public function optimize() { $this->search->optimize(); }

		public function count() { return $this->search->count(); }
		public function numDocs() { return $this->search->numDocs(); }
	}
