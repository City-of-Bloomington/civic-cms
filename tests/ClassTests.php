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

/**
* Load the configuration file for the testing instance
* This should point to the test database, so we don't muck
* around with production
*/
require_once './configuration.inc';

# Load all the tests we're going to run for this suite
require_once 'classes/BackupTest.php';
require_once 'classes/CalendarListTest.php';
require_once 'classes/CalendarTest.php';
require_once 'classes/DepartmentListTest.php';
require_once 'classes/DepartmentTest.php';
require_once 'classes/DocumentLinkListTest.php';
require_once 'classes/DocumentLinkTest.php';
require_once 'classes/DocumentListTest.php';
require_once 'classes/DocumentTest.php';
require_once 'classes/DocumentTypeListTest.php';
require_once 'classes/DocumentTypeTest.php';
require_once 'classes/EventListTest.php';
require_once 'classes/EventRecurrenceTest.php';
require_once 'classes/EventTest.php';
require_once 'classes/FacetGroupListTest.php';
require_once 'classes/FacetGroupTest.php';
require_once 'classes/FacetListTest.php';
require_once 'classes/FacetTest.php';
require_once 'classes/ImageListTest.php';
require_once 'classes/ImageTest.php';
require_once 'classes/LanguageListTest.php';
require_once 'classes/LanguageTest.php';
require_once 'classes/LocationGroupListTest.php';
require_once 'classes/LocationGroupTest.php';
require_once 'classes/LocationListTest.php';
require_once 'classes/LocationTest.php';
require_once 'classes/LocationTypeListTest.php';
require_once 'classes/LocationTypeTest.php';
require_once 'classes/MediaListTest.php';
require_once 'classes/MediaTest.php';
require_once 'classes/PanelListTest.php';
require_once 'classes/PanelTest.php';
require_once 'classes/RoleListTest.php';
require_once 'classes/RoleTest.php';
require_once 'classes/SearchTest.php';
require_once 'classes/SectionDocumentTest.php';
require_once 'classes/SectionDocumentListTest.php';
require_once 'classes/SectionListTest.php';
require_once 'classes/SectionNodeListTest.php';
require_once 'classes/SectionNodeTest.php';
require_once 'classes/SectionTest.php';
require_once 'classes/SectionWidgetListTest.php';
require_once 'classes/SectionWidgetTest.php';
require_once 'classes/UserListTest.php';
require_once 'classes/UserTest.php';
require_once 'classes/WatchTest.php';
require_once 'classes/WidgetInstallationListTest.php';
require_once 'classes/WidgetInstallationTest.php';
require_once 'classes/WidgetTest.php';
require_once 'classes/WikiMarkupTest.php';

class ClassTests
{
	public static function main()
	{
		PHPUnit_TextUI_TestRunner::run(self::suite());
	}

	public static function suite()
	{
		$suite = new PHPUnit_Framework_TestSuite('Classes');

		$suite->addTestSuite('BackupTest');
		$suite->addTestSuite('CalendarListTest');
		$suite->addTestSuite('CalendarTest');
		$suite->addTestSuite('DepartmentListTest');
		$suite->addTestSuite('DepartmentTest');
		$suite->addTestSuite('DocumentLinkListTest');
		$suite->addTestSuite('DocumentLinkTest');
		$suite->addTestSuite('DocumentListTest');
		$suite->addTestSuite('DocumentTest');
		$suite->addTestSuite('DocumentTypeListTest');
		$suite->addTestSuite('DocumentTypeTest');
		$suite->addTestSuite('EventListTest');
		$suite->addTestSuite('EventRecurrenceTest');
		$suite->addTestSuite('EventTest');
		$suite->addTestSuite('FacetGroupListTest');
		$suite->addTestSuite('FacetGroupTest');
		$suite->addTestSuite('FacetListTest');
		$suite->addTestSuite('FacetTest');
		$suite->addTestSuite('ImageListTest');
		$suite->addTestSuite('ImageTest');
		$suite->addTestSuite('LanguageListTest');
		$suite->addTestSuite('LanguageTest');
		$suite->addTestSuite('LocationGroupListTest');
		$suite->addTestSuite('LocationGroupTest');
		$suite->addTestSuite('LocationListTest');
		$suite->addTestSuite('LocationTest');
		$suite->addTestSuite('LocationTypeListTest');
		$suite->addTestSuite('LocationTypeTest');
		$suite->addTestSuite('MediaListTest');
		$suite->addTestSuite('MediaTest');
		$suite->addTestSuite('PanelListTest');
		$suite->addTestSuite('PanelTest');
		$suite->addTestSuite('RoleListTest');
		$suite->addTestSuite('RoleTest');
		$suite->addTestSuite('SearchTest');
		$suite->addTestSuite('SectionDocumentListTest');
		$suite->addTestSuite('SectionDocumentTest');
		$suite->addTestSuite('SectionListTest');
		$suite->addTestSuite('SectionNodeListTest');
		$suite->addTestSuite('SectionNodeTest');
		$suite->addTestSuite('SectionTest');
		$suite->addTestSuite('SectionWidgetListTest');
		$suite->addTestSuite('SectionWidgetTest');
		$suite->addTestSuite('UserListTest');
		$suite->addTestSuite('UserTest');
		$suite->addTestSuite('WatchTest');
		$suite->addTestSuite('WidgetInstallationListTest');
		$suite->addTestSuite('WidgetInstallationTest');
		$suite->addTestSuite('WidgetTest');
		$suite->addTestSuite('WikiMarkupTest');

		return $suite;
	}
}

if (PHPUnit_MAIN_METHOD == 'ClassTests::main') {
	ClassTests::main();
}
