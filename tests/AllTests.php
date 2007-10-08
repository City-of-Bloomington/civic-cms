<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
if (!defined('PHPUnit_MAIN_METHOD')) {
    define('PHPUnit_MAIN_METHOD', 'AllTests::main');
}

require_once 'PHPUnit/Framework.php';

/**
 * Load the configuration file for the testing instance
 * This should point to the test database, so we don't muck
 * around with production
 */
include_once './configuration.inc';

# Load all the test suites
require_once './AllTestsSuite.php';
require_once './ClassTests.php';

class AllTests
{
	public static function main()
	{
		PHPUnit_TextUI_TestRunner::run(self::suite());
	}

	public static function suite()
	{
		$suite = new AllTestsSuite();
		$suite->addTest(ClassTests::suite());
		// ...

		return $suite;
	}
}
if (PHPUnit_MAIN_METHOD == 'AllTests::main') {
    AllTests::main();
}
