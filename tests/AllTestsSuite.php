<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
class AllTestsSuite extends PHPUnit_Framework_TestSuite
{
    public static function suite()
    {
        return new AllTestsSuite('AllTests');
    }

    protected function setUp()
    {
    	/*
		$PDO = Database::getConnection();
		$PDO->exec('drop database test');
		$PDO->exec('create database test');
		$PDO = Database::getConnection(true);

		# Load the database schema
		$user = DB_USER;
		$pass = DB_PASS;
		$name = DB_NAME;
		$home = APPLICATION_HOME;
		exec("/usr/local/mysql/bin/mysql -u $user -p$pass $name < $home/scripts/mysql.sql");

		# Insert some default test data
		$query = $PDO->prepare('insert departments set id=?,name=?');
		$query->execute(array(1,'Test Department'));

		$query = $PDO->prepare('insert users (username,firstname,lastname,department_id) values(?,?,?,?)');
		$query->execute(array('testuser','Test','User',1));

		$query = $PDO->prepare("insert user_roles values(?,(select id from roles where role='Administrator'))");
		$query->execute(array(1));

		$query = $PDO->prepare('insert documents (id,title,created,createdBy,modifiedBy,publishDate,department_id) values(?,?,?,?,?,?,?)');
		$query->execute(array(1,'Home','2006-11-15',1,1,'2006-11-15',1));

		$query = $PDO->prepare('insert sections (id,name,nickname,document_id) values(?,?,?,?)');
		$query->execute(array(1,'Home',1,1));

		$query = $PDO->prepare('insert section_departments values(?,?)');
		$query->execute(array(1,1));

    	$query = $PDO->prepare('insert calendars values(?,?,?,?)');
    	$query->execute(array(1,'Test','Test Calendar',1));

    	$query = $PDO->prepare('insert events (id,startDate,startTime,endDate,endTime,summary,calendar_id,user_id) values(?,?,?,?,?,?,?,?)');
    	$query->execute(array(1,'2006-06-13','16:15:00','2006-12-31','18:00:00','Test',1,1));
    	*/
    }

    protected function tearDown()
    {

    }
}
