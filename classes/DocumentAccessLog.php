<?php
/**
 * This class writes hits to an accesslog table.
 *
 * Because reading from this table o display statistics is very, very slow,
 * we've also provided a CRON script to update various Summary Tables in the database.
 * see also: /scripts/updateSummaryTables.sh
 *			/scripts/updateSummaryTables.sql
 *
 * This class is currently set to read from these Summary tables; however,
 * the SQL to read directly from the accesslog is still provided, just
 * commented out.
 * If you don't mind the slowness of reading data, then you can uncomment
 * the accesslog selects.  This could be useful if you only update the Summary
 * tables once a month and don't display statistics very often.
 *
 * If however, you want to use the statistics often (for example, in a
 * Top Documents widget, displayed on every page), you should leave the
 * Summary Table selects in place, and add the provided script to your CRON

 * @copyright 2007-2009 City of Bloomington, Indiana
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 *
 */
class DocumentAccessLog
{
	/**
	 * Records the hit for one document
	 * @param Document $document
	 */
	public static function logHit($document)
	{
		$pdo = Database::getConnection();

		$query = $pdo->prepare('insert document_accesslog set document_id=?');
		$query->execute(array($document->getId()));

		/**
		* The summary tables need to be updated periodically.
		* Right now, we've created a cron script to do this.  If you
		* don't use the cron script, but still want to use the summary tables,
		* you will need to uncomment this code.
		* This will check if it's time to update the summary tables on every
		* page request.  The cron script is the more effecient solution, as
		* it doesn't impact anyone browsing the website
		*/
		// Check to see if it's time to update the summary tables
		//$result = $pdo->query('select ifnull(datediff(curdate(),max(date)),1) as days_since_last_generated from document_hits_daily');
		//$r = $result->fetchAll();
		//if ($r[0]['days_since_last_generated'] > 0)
		//{
		//	self::updateSummaryTables();
		//}
	}

	/**
	 * Returns an array of the most accessed Documents and how
	 * often they were accessed.
	 * @param int $numDocuments How many documents you want returned
	 * @param int $documentType_id Limit the hits to only documents of this type
	 */
	public static function getTopDocuments($numDocuments=10,$documentType_id=null)
	{
		$numDocuments = (int) $numDocuments;
		$pdo = Database::getConnection();

		if ($documentType_id) {
			// This is the query to read directly from the access_log
			// While accurate, it is very, very slow
			//$sql = "select l.document_id,count(*) as count from document_accesslog l
			//		left join documents d on l.document_id=d.id
			//		where d.documentType_id=?
			//		group by l.document_id order by count desc limit $numDocuments";

			// This query reads from Summary tables
			$sql = "select document_id,hits as count from document_hits_running_totals
					left join documents on document_id=id
					where documentType_id=?
					and (publishDate is null or publishDate<now())
					and (retireDate is null or retireDate>now())
					order by count desc limit $numDocuments";
			$query = $pdo->prepare($sql);
			$query->execute(array($documentType_id));
		}
		else {
			// This is the query to read directly from the access_log
			// While accurate, it is very, very slow
			//$sql = "select document_id,count(*) as count from document_accesslog
			//		group by document_id order by count desc limit $numDocuments";

			// This query reads from Summary tables
			$sql = "select document_id,hits as count from document_hits_running_totals
					left join documents on document_id=id
					where (publishDate is null or publishDate<now())
					and (retireDate is null or retireDate>now())
					order by count desc limit $numDocuments";
			$query = $pdo->prepare($sql);
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
		$pdo = Database::getConnection();

		// This is the query to read directly from the access_log
		// While accurate, it is very, very slow
		//$sql = "select document_id,count(*) as count from document_accesslog
		//		left join documents on document_id=id
		//		where department_id=?
		//		group by document_id order by count desc limit $numDocuments";

		// This query reads from Summary tables
		$sql = "select document_id,sum(hits) as count from document_hits_yearly
				left join documents on document_id=id
				where department_id=?
				group by document_id order by count desc limit $numDocuments";
		$query = $pdo->prepare($sql);
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
		foreach ($results as $row) {
			$hit['document_id'] = $row['document_id'];
			$hit['document'] = new Document($row['document_id']);
			$hit['count'] = $row['count'];
			$hits[] = $hit;
		}
		return $hits;
	}

	private static function updateSummaryTables()
	{
		$pdo = Database::getConnection();

		$pdo->exec('delete from document_hits_yearly');
		$pdo->exec('delete from document_hits_monthly');
		$pdo->exec('delete from document_hits_daily');

		$pdo->exec("insert document_hits_yearly
					select year(access_time) as year,document_id,count(*) from document_accesslog
					left join documents on document_id=id where id is not null
					group by year,document_id");

		$pdo->exec("insert document_hits_monthly
					select concat_ws('-',year(access_time),month(access_time),1) as date,document_id,count(*) from document_accesslog
					left join documents on document_id=id where id is not null
					group by date,document_id");

		$pdo->exec("insert document_hits_daily
					select date(access_time) as date,document_id,count(*) from document_accesslog
					left join documents on document_id=id where id is not null
					group by date,document_id");
	}
}
