<?php
require_once 'PHPUnit/Framework.php';

require_once dirname(__FILE__).'../../../WeekDay.inc';

class WeekDayTest extends PHPUnit_Framework_TestCase
{
	protected function setUp()
	{
	}

	protected function tearDown()
	{
	}

    public function testParsing()
    {
    	$weekday = new WeekDay('-1SU');
    	$this->assertTrue($weekday->getOffset()==-1,'Negative offset not parsed');
    	$this->assertTrue($weekday->getDay()=='SU','Day not parsed with negative offset');

    	$weekday = new WeekDay('+2SU');
    	$this->assertTrue($weekday->getOffset()==2,'Positive offset not parsed');
    	$this->assertTrue($weekday->getDay()=='SU','Day not parsed with positive offset');

    	$weekday = new WeekDay('2SU');
    	$this->assertTrue($weekday->getOffset()==2,'Positive offset not parsed');
    	$this->assertTrue($weekday->getDay()=='SU','Day not parsed with positive offset');

    	$weekday = new WeekDay('SU');
    	$this->assertTrue($weekday->getOffset()==0,'Undefined offset not parsed');
    	$this->assertTrue($weekday->getDay()=='SU','Day not parsed without offset');
    }

    public function testGetDayName()
    {
    	$weekday = new WeekDay('TU');
    	$this->assertEquals($weekday->getDayName(),'Tuesday');
    }

    public function test__toString()
    {
    	$weekday = new WeekDay('-1SU');
    	$this->assertTrue($weekday=='-1SU','Negative offset not serialized correctly');

    	$weekday = new WeekDay('2SU');
    	$this->assertTrue($weekday=='2SU','Positive offset not serialized correctly');

    	$weekday = new WeekDay('SU');
    	$this->assertTrue($weekday=='SU','Undefined offset not serialized correctly');
    }

}
