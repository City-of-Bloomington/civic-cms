<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
class DocumentAccessLog
{
	/**
	 * Returns an array of the most accessed Documents and how
	 * often they were accessed.
	 * @param int $numDocuments How many documents you want returned
	 */
	public static function getTopDocuments($numDocuments=10)
	{
		$numDocuments = (int) $numDocuments;
		$PDO = Database::getConnection();

		$sql = "select document_id,count(*) as count from document_accesslog
				group by document_id order by count desc limit $numDocuments";
		$query = $PDO->prepare($sql);
		$query->execute();
		$results = $query->fetchAll();


		$hits = array();
		foreach($results as $row)
		{
			$hit['document_id'] = $row['document_id'];
			$hit['document'] = new Document($row['document_id']);
			$hit['count'] = $row['count'];
			$hits[] = $hit;
		}
		return $hits;
	}
}