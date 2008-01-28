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
	 * @param int $documentType_id Limit the hits to only documents of this type
	 */
	public static function getTopDocuments($numDocuments=10,$documentType_id=null)
	{
		$numDocuments = (int) $numDocuments;
		$PDO = Database::getConnection();

		if ($documentType_id)
		{
			$sql = "select l.document_id,count(*) as count from document_accesslog l
					left join documents d on l.document_id=d.id where d.documentType_id=?
					group by l.document_id order by count desc limit $numDocuments";
			$query = $PDO->prepare($sql);
			$query->execute(array($documentType_id));
		}
		else
		{
			$sql = "select document_id,count(*) as count from document_accesslog
					group by document_id order by count desc limit $numDocuments";
			$query = $PDO->prepare($sql);
			$query->execute();
		}
		return self::prepareHits($query->fetchAll());
	}

	/**
	 * Returns an array of the most access Documents for a given Department
	 * @param Department $department
	 * @param int $numDocuments How many documents to return
	 */
	public static function getTopDepartmentDocuments($department,$numDocuments=10)
	{
		$numDocuments = (int) $numDocuments;
		$PDO = Database::getConnection();

		$sql = "select document_id,count(*) as count from document_accesslog
				left join documents on document_id=id
				where department_id=?
				group by document_id order by count desc limit $numDocuments";
		$query = $PDO->prepare($sql);
		$query->execute(array($department->getId()));

		return self::prepareHits($query->fetchAll());
	}

	/**
	 * Takes a PDO $results array and assembles the $hits information
	 * @param array $results The PDO results array
	 */
	private static function prepareHits($results)
	{
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