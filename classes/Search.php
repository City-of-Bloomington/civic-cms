<?php
/**
 * @copyright Copyright (C) 2007-2008 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * Class for working with a previously created search index.  Before this class
 * will work, you must have run /scripts/install_search.php
 */
ini_set('include_path',ini_get('include_path').':'.ZEND.':');
require_once 'Zend/Search/Lucene.php';

# Zend Search Lucene uses a TON of memory.
# Make sure to allow PHP enough memory
ini_set('memory_limit',SEARCH_MEMORY_LIMIT);

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
		Zend_Search_Lucene_Search_QueryParser::setDefaultEncoding('utf-8');
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

		# The UTF8 analyzer is case-sensitive.  So we need to lowercase everything before indexing
		if ($entry instanceof Document)
		{
			$title = strtolower($entry->getTitle());
			$description = strtolower($entry->getDescription());
			$content = strtolower(strip_tags(implode("\n",$entry->getContent())));
			$combined = "$title $description $content";

			$type = $entry->getDocumentType()->isSeperateInSearch() ? $entry->getDocumentType()->getType() : 'Document';
			$doc->addField(Zend_Search_Lucene_Field::Keyword('type',$type));
			$doc->addField(Zend_Search_Lucene_Field::Keyword('document_id',$entry->getId()));
			$doc->addField(Zend_Search_Lucene_Field::UnStored('title',$title,'utf-8'));
			$doc->addField(Zend_Search_Lucene_Field::UnStored('description',$description,'utf-8'));
			$doc->addField(Zend_Search_Lucene_Field::UnStored('content',$content,'utf-8'));
			$doc->addField(Zend_Search_Lucene_Field::UnStored('combined',$combined,'utf-8'));
		}
		elseif ($entry instanceof Event)
		{
			$title = strtolower($entry->getTitle());
			$description = strtolower(strip_tags($entry->getDescription()));
			$combined = "$title $description";

			$doc->addField(Zend_Search_Lucene_Field::Keyword('type','Event'));
			$doc->addField(Zend_Search_Lucene_Field::Keyword('event_id',$entry->getId()));
			$doc->addField(Zend_Search_Lucene_Field::UnStored('title',$title,'utf-8'));
			$doc->addField(Zend_Search_Lucene_Field::UnStored('description',$description,'utf-8'));
			$doc->addField(Zend_Search_Lucene_Field::UnStored('combined',$combined,'utf-8'));
		}
		elseif ($entry instanceof Media)
		{
			$title = strtolower($entry->getTitle());
			$description = strtolower($entry->getDescription());
			$combined = "$title $description";

			$doc->addField(Zend_Search_Lucene_Field::Keyword('type','Media'));
			$doc->addField(Zend_Search_Lucene_Field::Keyword('media_id',$entry->getId()));
			$doc->addField(Zend_Search_Lucene_Field::UnStored('title',$title,'utf-8'));
			$doc->addField(Zend_Search_Lucene_Field::UnStored('description',$description,'utf-8'));
			$doc->addField(Zend_Search_Lucene_Field::UnStored('combined',$combined,'utf-8'));
		}
		else { throw new Exception('search/unknownType'); }

		$this->search->addDocument($doc);
	}

	/**
	 * Removed an entry from the search index
	 * @param Object $entry
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
		elseif ($entry instanceof Media)
		{
			$term  = new Zend_Search_Lucene_Index_Term($entry->getId(),'media_id');
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
		$this->remove($entry);
		$this->add($entry);
	}

	/**
	 * Does a search using Zend_Search_Lucene's built in query parser
	 *
	 * @param string $string The text to search for
	 * @param string type One of the types known to the Search class (see Search->add())
	 */
	public function find($string,$type=null,$logging=true)
	{
		if ($logging) { $this->log($string); }

		$string = strtolower(str_replace(array('\\','"',"'"),'',$string));

		Zend_Search_Lucene::setDefaultSearchField('combined');
		try { $query = Zend_Search_Lucene_Search_QueryParser::parse($string); }
		catch (Exception $e)
		{
			# If the query parser has any trouble, we're just going to ignore it.
			# The end result is that the user will just not get any hits on their search
		}

		if ($type)
		{
			$typeTerm  = new Zend_Search_Lucene_Index_Term($type,'type');
			$typeQuery = new Zend_Search_Lucene_Search_Query_Term($typeTerm);
			$query->addSubquery($typeQuery,true /* required */);
		}

		$hits = $this->search->find($query);

		$results = array();
		foreach($hits as $hit)
		{
			$type = Inflector::pluralize($hit->type);
			switch ($hit->type)
			{
				case 'Event':
					try { $results[$type][] = new Event($hit->event_id); }
					catch(Exception $e) { }
				break;

				case 'Media':
					try { $results[$type][] = new Media($hit->media_id); }
					catch(Exception $e) { }
				break;

				# Anything not listed above should be a type of Document
				default:
					try { $results[$type][] = new Document($hit->document_id); }
					catch(Exception $e) { }
				break;
			}
		}
		return $results;
	}

	public function optimize() { $this->search->optimize(); }

	public function count() { return $this->search->count(); }
	public function numDocs() { return $this->search->numDocs(); }

	private function log($string)
	{
		$PDO = Database::getConnection();
		$query = $PDO->prepare('insert search_log set queryString=?');
		$query->execute(array($string));
	}
}
