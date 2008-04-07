<?php
/**
* @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
* @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
* @author Cliff Ingham <inghamn@bloomington.in.gov>
*/
if (!defined('PHPUnit_MAIN_METHOD')) {
	define('PHPUnit_MAIN_METHOD', 'ClassTests::main');
}

require_once 'PHPUnit/Framework.php';
require_once 'PHPUnit/TextUI/TestRunner.php';

require_once './iCal4PHP/WeekDayTest.php';
require_once './iCal4PHP/RecurTest.php';


class iCal4PHPTests
{
	public static function main()
	{
		PHPUnit_TextUI_TestRunner::run(self::suite());
	}

	public static function suite()
	{
		$suite = new PHPUnit_Framework_TestSuite('iCal4PHP');

		$suite->addTestSuite('WeekDayTest');
		$suite->addTestSuite('RecurTest');

		return $suite;
	}
}