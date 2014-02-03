<?php
/**
 * @copyright 2012-2013 City of Bloomington, Indiana
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
include '../../configuration.inc';
$search = new Search();
$search->solrClient->deleteByQuery('*:*');
$search->solrClient->commit();

$pdo = Database::getConnection();

$recordTypes = ['documents'=>'Document', 'events'=>'Event', 'media'=>'Media'];

foreach ($recordTypes as $table=>$class) {
	$sql = "select id from $table";
	$query = $pdo->query($sql);
	$results = $query->fetchAll();

	$c = 0;
	foreach ($results as $row) {
		$document = new $class($row['id']);
		$search->add($document);
		$c++;
		echo "$class id:$row[id] count:$c\n";
	}
	echo "Committing\n";
	$search->solrClient->commit();
	echo "Optimizing\n";
	$search->solrClient->optimize();
}

echo "Done\n";
