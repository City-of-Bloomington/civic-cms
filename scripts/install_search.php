<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * Creates a new set of index data for out search engine.
 * Loads all the current documents into the new index
 */
 	# This must be a full path, in order to be able to run
 	# the index_search CRON script
	include '/var/www/sites/content_manager/configuration.inc';

	# The class file has the ini_set definition we need to do Zend stuff
	require_once(APPLICATION_HOME.'/classes/Search.inc');

 	# Create the new index
	Zend_Search_Lucene::create(APPLICATION_HOME.'/data/search_index');
	echo APPLICATION_HOME."/data/search_index created\n";

	# Zend Search Lucene uses a TON of memory.
	# Make sure to allow PHP enough memory
	ini_set('memory_limit','128M');
	$memory_limit = ini_get('memory_limit');

	# Load all the documents into the new index
	$search = new Search();


	$documents = new DocumentList();
	$documents->find();
	$c = 0;
	foreach($documents as $document)
	{
		$c++;
		$search->add($document);
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

	# Load all the events into the new index
	$events = new EventList();
	$events->find();
	$c = 0;
	foreach($events as $event)
	{
		$c++;
		$search->add($event);
		$used_memory = memory_get_usage();
		echo "Added event: {$event->getId()} - $used_memory/$memory_limit\n";
		if ($c>=200)
		{
			echo "Optimizing\n";
			$search->optimize();
			$c = 0;
		}
	}

	# Load all the Media into the new Index
	$list = new MediaList();
	$list->find();
	$c = 0;
	foreach($list as $media)
	{
		$c++;
		$search->add($media);
		$used_memory = memory_get_usage();
		echo "Added media: {$media->getId()} - $used_memory/$memory_limit\n";
		if ($c>=200)
		{
			echo "Optimizing\n";
			$search->optimize();
			$c = 0;
		}
	}

	echo "Search now has {$search->count()} entries\n";
