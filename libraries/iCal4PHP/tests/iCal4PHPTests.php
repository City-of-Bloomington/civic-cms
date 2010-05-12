<?php
/**
* @copyright 2007-2010 City of Bloomington, Indiana
* @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
* @author Cliff Ingham <inghamn@bloomington.in.gov>
*/
require_once 'PHPUnit/Framework.php';

require_once './iCal4PHP/WeekDayTest.php';
require_once './iCal4PHP/RecurTest.php';


class iCal4PHPTests
{
	public static function suite()
	{
		$suite = new PHPUnit_Framework_TestSuite('iCal4PHP');

		$suite->addTestSuite('WeekDayTest');
		$suite->addTestSuite('RecurTest');

		return $suite;
	}
}
