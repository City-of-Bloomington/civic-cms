<?php
/**
 * @copyright Copyright (C) 2007-2008 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * Creates a new set of index data for out search engine.
 * Loads all the current documents into the new index
 */
# This must be a full path, in order to be able to run
# the index_search CRON script
include '/var/www/sites/content_manager/configuration.inc';

# The class file has the ini_set definition we need to do Zend stuff
require_once APPLICATION_HOME.'/classes/Search.inc';

# Create the new index
Zend_Search_Lucene::create(APPLICATION_HOME.'/data/search_index');
echo APPLICATION_HOME."/data/search_index created\n";

# Find out how much memory we've got available
$memory_limit = ini_get('memory_limit');
$meg = 1024 * 1024;

# Load all the documents into the new index
$search = new Search();


$documents = new DocumentList();
$documents->find(array('active'=>date('Y-m-d')));
foreach($documents as $document)
{
	$search->add($document);
	$used_memory = round(memory_get_usage()/$meg);
	echo "Added document: {$document->getId()} - {$used_memory}M/$memory_limit\n";
}
echo "Optimizing\n";
$search->optimize();

# Load all the events into the new index
$events = new EventList();
$events->find();
foreach($events as $event)
{
	$search->add($event);
	$used_memory = round(memory_get_usage()/$meg);
	echo "Added event: {$event->getId()} - {$used_memory}M/$memory_limit\n";
}
echo "Optimizing\n";
$search->optimize();

# Load all the Media into the new Index
$list = new MediaList();
$list->find();
foreach($list as $media)
{
	$search->add($media);
	$used_memory = round(memory_get_usage()/$meg);
	echo "Added media: {$media->getId()} - {$used_memory}M/$memory_limit\n";
}
echo "Optimizing\n";
$search->optimize();

echo "Search now has {$search->count()} entries\n";
