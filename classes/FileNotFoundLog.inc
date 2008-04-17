<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
class FileNotFoundLog
{
	public static function log($string)
	{
		$PDO = Database::getConnection();

		$referer = isset($_SERVER['HTTP_REFERER']) ? $_SERVER['HTTP_REFERER'] : null;

		$query = $PDO->prepare('insert file_not_found_log set path=?,referer=?');
		$query->execute(array($string,$referer));
	}

	/**
	 * Returns the top asked for URLs that errored out, along with
	 * the number of times that URL was requested
	 */
	public static function getTopRequests($numRequests=25)
	{
		$hits = array();

		$PDO = Database::getConnection();
		$sql = "select path,count(*) as count from file_not_found_log
				group by path order by count desc limit $numRequests";
		$query = $PDO->prepare($sql);
		$query->execute();
		$result = $query->fetchAll();

		return $result;
	}

	/**
	 * Returns all the referrers for a URL that errored out
	 * @param string $path The path from the 404 error log
	 */
	public static function getReferers($path)
	{
		$output = array();
		$PDO = Database::getConnection();

		$query = $PDO->prepare('select distinct referer from file_not_found_log where path=?');
		$query->execute(array($path));
		$results = $query->fetchAll();
		foreach($results as $row) { $output[] = $row['referer']; }
		return $output;
	}
}