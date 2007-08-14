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

	# Load all the documents into the index
	$search = new Search();
	$documents = new DocumentList();
	$documents->find();
	foreach($documents as $document)
	{
		$search->addDocument($document);
		echo "Added document: {$document->getId()}\n";
	}

	$search->optimize();

	echo "Search now has {$search->count()} documents\n";
?>