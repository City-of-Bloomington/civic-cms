<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
class SearchLog
{
	/**
	 * Returns the most popular search strings
	 * @param int $numHits The maximum number of hits you want returned
	 */
	public static function getTopSearches($numHits=25)
	{
		$PDO = Database::getConnection();
		$sql = "select queryString,count(*) as count from search_log
				group by queryString order by count desc limit $numHits";
		$query = $PDO->prepare($sql);
		$query->execute();
		$results = $query->fetchAll();

		return $results;
	}
}