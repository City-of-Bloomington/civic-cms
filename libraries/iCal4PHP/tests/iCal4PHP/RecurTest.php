<?php
require_once 'PHPUnit/Framework.php';
require_once dirname(__FILE__).'../../../Recur.inc';

class RecurTest extends PHPUnit_Framework_TestCase
{
    public function testCreate()
    {
    	$recur = new Recur("FREQ=MONTHLY;INTERVAL=2;BYDAY=3MO");
    	$this->assertEquals($recur->getFrequency(),'MONTHLY');
    	$this->assertEquals($recur->getInterval(),2);

    	$days = $recur->getDayList();
    	$this->assertTrue(count($days)==1);
    	$this->assertTrue($days[0]->getDay()=='MO');
    	$this->assertTrue($days[0]->getOffset()==3);
    }

    public function testByMonth()
    {
		$recur = new Recur('FREQ=YEARLY;BYMONTH=3,10,12');
		$start = strtotime('2010-04-01');
		$end = strtotime('+1 year',$start);
		$dates = $recur->getDates($start,$end);

		$this->assertTrue(count($dates)==3);
		$this->assertEquals(date('Y-m-d',$dates[0]),'2010-10-01');
		$this->assertEquals(date('Y-m-d',$dates[1]),'2010-12-01');
		$this->assertEquals(date('Y-m-d',$dates[2]),'2011-03-01');
    }

    public function testByWeekNo()
    {
		$recur = new Recur('FREQ=YEARLY;BYWEEKNO=2,32,48');
		$start = time();
		$end = strtotime('+1 year',$start);
		$dates = $recur->getDates($start,$end);

		$this->assertTrue(count($dates)==3);
    }

    public function testByYearDay()
    {
		$recur = new Recur('FREQ=YEARLY;BYYEARDAY=2,32,48');
		$start = time();
		$end = strtotime('+1 year',$start);
		$dates = $recur->getDates($start,$end);

		$this->assertTrue(count($dates)==3);
    }

    public function testByMonthDay()
    {
		$recur = new Recur('FREQ=MONTHLY;BYMONTHDAY=15,16');
		$start = time();
		$end = strtotime('+1 year',$start);
		$dates = $recur->getDates($start,$end);

		$this->assertTrue(count($dates)==24);
	}

	public function testWeeklyByDay()
	{
		$recur = new Recur('FREQ=WEEKLY;BYDAY=MO,WE');
		$start = strtotime('2007-10-26 17:07:00');
		$end = strtotime('+1 month',$start);
		$dates = $recur->getDates($start,$end);

		$this->assertTrue(count($dates)==8);
	}

	public function testMonthlyByDay()
	{
		$recur = new Recur('FREQ=MONTHLY;BYDAY=MO,WE');
		$start = strtotime('2007-10-26 17:07:00');
		$end = strtotime('+2 month',$start);
		$dates = $recur->getDates($start,$end);

		$this->assertEquals(count($dates),18);
	}

	public function testYearlyByDay()
	{
		$recur = new Recur('FREQ=YEARLY;BYDAY=MO,WE');
		$start = strtotime('2007-10-26 17:07:00');
		$end = strtotime('+2 month',$start);
		$dates = $recur->getDates($start,$end);

		$this->assertEquals(count($dates),18);
	}

	public function testUntil()
	{
		$recur = new Recur('FREQ=DAILY;UNTIL=20071015T030000');
		$seed = strtotime('2007-10-03 03:00:00');

		$start = strtotime('2007-10-01');
		$end = strtotime('2007-10-30');
		$dates = $recur->getDates($start,$end,$seed);
		$this->assertEquals(count($dates),13);
	}

	public function testSingleDayRange()
	{
		$recur = new Recur('FREQ=MONTHLY;INTERVAL=1;COUNT=6;BYDAY=4FR');
		$seed = strtotime('2008-01-25 13:30:00');

		$rangeStart = strtotime('2008-02-22');
		$rangeEnd = strtotime('+1 day',$rangeStart);
		$dates = $recur->getDates($rangeStart,$rangeEnd,$seed);
		$this->assertEquals(count($dates),1);
	}

    /**
     * This test creates a rule outside of the specified boundaries to
     * confirm that the returned date list is empty.
     * <pre>
     *  Weekly on Tuesday and Thursday for 5 weeks:
     *
     *  DTSTART;TZID=US-Eastern:19970902T090000
     *  RRULE:FREQ=WEEKLY;UNTIL=19971007T000000Z;WKST=SU;BYDAY=TU,TH
     *  or
     *
     *  RRULE:FREQ=WEEKLY;COUNT=10;WKST=SU;BYDAY=TU,TH
     *
     *  ==> (1997 9:00 AM EDT)September 2,4,9,11,16,18,23,25,30;October 2
     * </pre>
     */
    public function testBoundaryProcessing()
    {
    	$recur = new Recur('FREQ=WEEKLY;UNTIL=19971007T000000Z;WKST=SU;BYDAY=TU,TH');
    	$seed = strtotime('1997-09-02 09:00:00');

    	$start = time();
    	$end = strtotime('+2 years',$start);
    	$dates = $recur->getDates($start,$end,$seed);
    	$this->assertEquals(count($dates),0);
    }

    public function testOpenEndedRecurrence()
    {
    	$start = strtotime('2007-10-09 06:00:00');
    	$recur = new Recur('FREQ=MONTHLY;INTERVAL=1;BYDAY=2TU');
    	$dates = $recur->getDates(1191902400,'',1191967200);

    	$this->assertTrue(count($dates)>10);
	}

}
