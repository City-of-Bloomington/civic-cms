<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * Creates a new set of index data for out search engine.
 * Loads all the current documents into the new index
 */
 	# Create the new index
	include '../configuration.inc';

	# The class file has the ini_set definition we need to do Zend stuff
	require_once(APPLICATION_HOME.'/classes/Search.inc');

	Zend_Search_Lucene::create(APPLICATION_HOME.'/data/search_index');
	echo APPLICATION_HOME."/data/search_index created\n";


	ini_set('memory_limit','128M');
	$memory_limit = ini_get('memory_limit');

	# Load all the documents into the index
	$search = new Search();
	$documents = new DocumentList();
	$documents->find();
	$c = 0;
	foreach($documents as $document)
	{
		$c++;
		$search->addDocument($document);
		$used_memory = memory_get_usage();
		echo "Added document: {$document->getId()} - $used_memory/$memory_limit\n";
		if ($c>=200)
		{
			echo "Optimizing\n";
			$search->optimize();
			$c = 0;
		}
	}

	$search->optimize();

	echo "Search now has {$search->count()} documents\n";
?>