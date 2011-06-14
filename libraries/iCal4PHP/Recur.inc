<?php
/**
 * This code is a port of the Recur class from iCal4J
 * available from http://sourceforge.net/projects/ical4j/
 * iCal4J is written by Ben Fortuna and is available
 * under his hown licencse
 *
 * @copyright 2007-2010 City of Bloomington, Indiana
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
require_once dirname(__FILE__).'/WeekDay.inc';

class Recur
{
	private $frequency;
	private $until;
	private $count;
	private $interval = 1;

	/**
	 * These should be arrays of Integers
	 */
	private $secondList = array();
    private $minuteList = array();
    private $hourList = array();
    private $monthDayList = array();
    private $yearDayList = array();
    private $weekNoList = array();
    private $monthList = array();
    private $setPosList = array();

	/**
	 * This should be an array of WeekDay objects
	 * WeekDays represent SU,MO,TU,WE,TH,FR,SA
	 * Plus they have an offset
	 */
	private $dayList = array();

	private $weekStartDay = 'Sunday';
	private $experimentalValues = array();
	private $calIncField;


	/**
	 * @param String $rrule A valid iCal RRULE string
	 */
	public function __construct($rrule=null)
	{
		if ($rrule) {
			$rules = explode(';',$rrule);
			foreach ($rules as $rule) {
				list($field,$value) = explode('=',$rule);
				switch ($field) {
					case 'FREQ': $this->setFrequency($value); break;
					case 'UNTIL': $this->setUntil($value); break;
					case 'COUNT': $this->setCount($value); break;
					case 'INTERVAL': $this->setInterval($value); break;
					case 'BYSECOND': $this->setBySecond($value); break;
					case 'BYMINUTE': $this->setByMinute($value); break;
					case 'BYHOUR': $this->setByHour($value); break;
					case 'BYDAY': $this->setByDay($value); break;
					case 'BYMONTHDAY': $this->setByMonthDay($value); break;
					case 'BYYEARDAY': $this->setByYearDay($value); break;
					case 'BYWEEKNO': $this->setByWeekNo($value); break;
					case 'BYMONTH': $this->setByMonth($value); break;
					case 'BYSETPOS': $this->setBySetPos($value); break;
					case 'WKST': $this->setWeekStartDay($value); break;

					// assume experimental value..
					default : $this->experimentalValues[$field] = $value;
				}
			}
			$this->validateFrequency();
		}
	}


    /**
     * Returns a list of timestamps in the specified period represented by this recur.
     *
     * This method includes a base date argument, which indicates the start of the fist occurrence of this recurrence.
     * The base date is used to inject default values to return a set of dates in the correct format.
     * For example, if the search start date (start) is Wed, Mar 23, 12:19PM,
     * but the recurrence is Mon - Fri, 9:00AM - 5:00PM,
     * the start dates returned should all be at 9:00AM, and not 12:19PM.
     *
     * @return a list of timestamps represented by this recur instance
     * @param timestamp $periodStart the starting timestamp of the period
     * @param timestamp $periodEnd the ending timestamp of the period
     * @param timestamp $seed the timestamp of this Recurrence's first instance
     */
	public function getDates($periodStart,$periodEnd=null,$seed=null)
	{
		if (!$periodEnd) {
			$periodEnd = strtotime('+1 year',$periodStart);
		}
		if (!$seed) {
			$seed = $periodStart;
		}
		if ($this->until && $this->until < $periodEnd) {
			$periodEnd = $this->until;
		}

		$dates = array();
		$cal = $seed;

		$invalidCandidateCount = 0;
		while ((!$this->count) || ($this->count > count($dates))) {
			if ($this->until && $cal > $this->until) {
				break;
			}
			if ($cal > $periodEnd) {
				break;
			}
			if ($this->count
					&& (count($dates) + $invalidCandidateCount) >= $this->count) {
				break;
			}

			$candidates = $this->getCandidates($cal);
			foreach($candidates as $candidate) {
                // don't count candidates that occur before the seed date..
                if ($candidate >= $seed) {
                	if ($candidate < $periodStart || $candidate > $periodEnd) {
						$invalidCandidateCount++;
					}
                	elseif ($this->count
							&& (count($dates) + $invalidCandidateCount)>=$this->count) {
						break;
					}
                	elseif (!($this->until && $candidate > $this->until)) {
						$dates[] = $candidate;
					}
                }
			}
			// We went through all the candidates, and still need more
			// Go to the start of the next time period
			$d = getdate($cal);
			switch ($this->calIncField) {
				case 'months':
					$cal = mktime(0,0,0,$d['mon']+1,1,$d['year']);
				break;

				default:
					$cal = strtotime("+{$this->interval} {$this->calIncField}",$cal);
			}
		}
		sort($dates);
		return $dates;
	}

    /**
     * Returns a list of possible dates generated from the applicable BY* rules, using the specified date as a seed.
     *
     * @param timestamp the seed date
     * @return array An array of timestamps
     */
	public function getCandidates($date)
	{
		$dates = array($date);
		$dates = $this->getMonthVariants($dates);
		$dates = $this->getWeekNoVariants($dates);
		$dates = $this->getYearDayVariants($dates);
		$dates = $this->getMonthDayVariants($dates);
		$dates = $this->getDayVariants($dates);
		$dates = $this->getHourVariants($dates);
		$dates = $this->getMinuteVariants($dates);
		$dates = $this->getSecondVariants($dates);
		$dates = $this->applySetPosRules($dates);

		return $dates;
	}

    /**
     * Applies BYSETPOS rules to candidate timestamps.
     *
     * Valid positions are from 1 to the size of the array.
     * Invalid positions are ignored.
     *
     * @param array $dates An array of timestamps
     * @return array An array of timestamps
     */
	private function applySetPosRules(array $dates)
	{
		// return if no SETPOS rules specified
		if (!count($this->getSetPosList())) {
			return $dates;
		}
		// sort the array before processing
		sort($dates);
		$setPosDates = array();
		$size = count($dates);
		foreach ($this->getSetPosList() as $pos) {
			if ($pos > 0 && $pos <= $size) {
				$setPosDates[] = $dates[$pos - 1];
			}
			elseif ($pos < 0 && $pos >= -$size) {
				$setPosDates[] = $dates($size + $pos);
			}
		}
		return $setPosDates;
	}

	/**
     * Applies BYMONTH rules specified in this Recur instance to the specified date list.
     *
     * If no BYMONTH rules are specified the date list is returned unmodified.
     *
     * @param array $dates An array of timestamps
     * @return array An array of timestamps
     */
    private function getMonthVariants(array $dates)
    {
    	if (!count($this->monthList)) {
			return $dates;
		}

    	$monthlyDates = array();
    	foreach ($dates as $date) {
    		$currentMonth = date('n',$date);
			foreach ($this->monthList as $targetMonth) {
				if ($targetMonth < $currentMonth) {
					$targetMonth+=12;
				}
				$distance = $targetMonth - $currentMonth;
				$monthlyDates[] = strtotime("+$distance months",$date);
			}
    	}
        return $monthlyDates;
    }

    /**
     * Applies BYSECOND rules specified in this Recur instance to the specified date list.
     *
     * If no BYSECOND rules are specified the date list is returned unmodified.
     *
     * @param array $dates An array of timestamps
     * @return array An array of timestamps
     */
    private function getSecondVariants(array $dates)
    {
    	if (!count($this->secondList)) {
			return $dates;
		}

    	$secondlyDates = array();
    	foreach ($dates as $date) {
			$cal = getdate($date);
			foreach ($this->secondList as $second) {
				$secondlyDates[] = mktime($cal['hours'],$cal['minutes'],$second,
											$cal['mon'],$cal['mday'],$cal['year']);
			}
    	}
        return $secondlyDates;
    }

    /**
     * Applies BYWEEKNO rules specified in this Recur instance to the specified date list.
     *
     * If no BYWEEKNO rules are specified the date list is returned unmodified.
     *
     * @param array $dates An array of timestamps
     * @return array An array of timestamps
     */
    private function getWeekNoVariants(array $dates)
    {
    	if (!count($this->weekNoList)) {
			return $dates;
		}

    	$weekNoDates = array();
    	foreach ($dates as $date) {
    		$cal = getdate($date);
    		$year = $cal['year'];
			$currentWeek = date('W',$date);
			$currentWeekDay = date('N',$date) - 1;
			foreach ($this->weekNoList as $targetWeek) {
				$y = ($targetWeek < $currentWeek) ? $year+1 : $year;
				$week = $this->getWeek($targetWeek,$y);
				$target = getdate($week[$currentWeekDay]);
				$weekNoDates[] = mktime($cal['hours'],$cal['minutes'],$cal['seconds'],
										$target['mon'],$target['mday'],$target['year']);
			}
    	}
    	return $weekNoDates;
    }

	/**
	 * Returns an array of timestamps for the given week,year
	 *
	 * Returns timestamps in an array Mon-Sun, 0-6
	 *
	 * @param int $weekNumber
	 * @param int $year
	 */
	private function getWeek ($weekNumber, $year)
	{
		// Count from '0104' because January 4th is always in week 1
		// (according to ISO 8601).
		$time = strtotime($year.'0104 +'.($weekNumber - 1).' weeks');

		// Get the time of the first day of the week
		$mondayTime = strtotime('-'.(date('w', $time) - 1).' days',$time);

		// Get the times of days 0 -> 6
		$dayTimes = array ();
		for ($i = 0; $i < 7; ++$i) {
			$dayTimes[] = strtotime('+' . $i . ' days', $mondayTime);
		}

		// Return timestamps for mon-sun.
		return $dayTimes;
	}

    /**
     * Applies BYYEARDAY rules specified in this Recur instance to the specified date list.
     *
     * If no BYYEARDAY rules are specified the date list is returned unmodified.
     *
     * @param array $dates An array of timestamps
     * @return array An array of timestamps
     */
    private function getYearDayVariants(array $dates)
    {
    	if (!count($this->yearDayList)) {
			return $dates;
		}

        $yearDayDates = array();
        foreach ($dates as $date) {
			// PHP's year days start counting at 0
			// iCalendar starts counding at 1
        	$currentYearDay = date('z',$date) + 1;
        	$year = date('Y',$date);
        	foreach ($this->yearDayList as $targetYearDay) {
        		if ($targetYearDay < $currentYearDay) {
        			$numDays = date('z',mktime(0,0,0,12,31,$year))+1;
        			$targetYearDay+=$numDays;
        		}
        		$distance = $targetYearDay - $currentYearDay;
        		$yearDayDates[] = strtotime("+$distance days",$date);
        	}
        }
        return $yearDayDates;
    }

    /**
     * Applies BYMONTHDAY rules specified in this Recur instance to the specified date list.
     *
     * If no BYMONTHDAY rules are specified the date list is returned unmodified.
     *
     * @param array $dates An array of timestamps
     * @return array An array of timestamps
     */
    private function getMonthDayVariants(array $dates)
    {
    	if (!count($this->monthDayList)) {
			return $dates;
		}

    	$monthDayDates = array();
    	foreach ($dates as $date) {
    		$cal = getdate($date);
    		foreach($this->monthDayList as $monthDay) {
    			$monthDayDates[] = mktime($cal['hours'],$cal['minutes'],$cal['seconds'],
											$cal['mon'],$monthDay,$cal['year']);
    		}
    	}
        return $monthDayDates;
    }

    /**
     * Applies BYDAY rules specified in this Recur instance to the specified date list.
     *
     * If no BYDAY rules are specified the date list is returned unmodified.
     *
     * @param array $dates An array of timestamps
     * @return array An array of timestamps
     */
    private function getDayVariants(array $dates)
    {
    	if (!count($this->dayList)) {
			return $dates;
		}

    	$weekDayDates = array();
    	foreach ($dates as $date) {
			foreach ($this->dayList as $weekDay) {
                // if BYYEARDAY or BYMONTHDAY is specified filter existing list
                if (count($this->yearDayList) || count($this->monthDayList)) {
                	$currentDayOfWeek = date('l',$date);
                	if ($weekDay->getDayName() == $currentDayOfWeek) {
                		$weekDayDates[] = $date;
                	}
                }
                else {
                	$absDays = $this->getAbsWeekDays($date,$weekDay);
					$weekDayDates = array_merge($weekDayDates,$absDays);
                }
			}
    	}

        return $weekDayDates;
    }

    /**
     * Returns a list of applicable dates corresponding to the specified week day in accordance
     * with the frequency specified by this recurrence rule.
     *
     * @param int $date timestamp
     * @param WeekDay $weekDay
     * @return array An array of timestamps
     */
    private function getAbsWeekDays($date,WeekDay $weekDay)
    {
    	$cal = $date;
    	$days = array();
    	$calDay = $weekDay->getDayName();

    	if ($this->frequency == 'DAILY') {
    		$current = getdate($cal);
    		if ($current['weekday'] == $calDay) {
				$days[] = $cal;
			}
    	}
    	elseif ($this->frequency == 'WEEKLY' || count($this->weekNoList)) {
    		// Find the target day in the current week
    		$t = $cal;

    		// Back up to Sunday
    		$current = getdate($t);
    		if ($current['weekday']!='Sunday') {
    			$sunday = getdate(strtotime('-1 Sunday',$cal));
    			$t = mktime($current['hours'],$current['minutes'],$current['seconds'],
							$sunday['mon'],$sunday['mday'],$sunday['year']);
    		}
    		// Move head to the target day
    		if  ($weekDay->getDayName() != 'Sunday') {
    			$target = getdate(strtotime("+1 {$weekDay->getDayName()}",$t));
    			$t = mktime($current['hours'],$current['minutes'],$current['seconds'],
							$target['mon'],$target['mday'],$target['year']);
    		}
    		$days[] = $t;
    	}
    	elseif ($this->frequency == 'MONTHLY' || count($this->monthList)) {
    		// Add all of this weekDay's dates for the current month
    		$currentMonth = date('n',$cal);

    		$t = getdate($cal);
    		$cal = mktime($t['hours'],$t['minutes'],$t['seconds'],$t['mon'],1,$t['year']);
    		if (date('l',$cal) != $weekDay->getDayName()) {
    			// If the first day of the month is not valid,
    			// jump ahead to the first valid day
    			$target = getdate(strtotime("+1 {$weekDay->getDayName()}",$cal));
    			$cal = mktime($t['hours'],$t['minutes'],$t['seconds'],
								$target['mon'],$target['mday'],$target['year']);
    		}
			while (date('n',$cal)==$currentMonth) {
    			$days[] = $cal;
    			$target = getdate(strtotime('+1 week',$cal));
    			$cal = mktime($t['hours'],$t['minutes'],$t['seconds'],
								$target['mon'],$target['mday'],$target['year']);
    		}
    	}
    	elseif ($this->frequency == 'YEARLY') {
			// Add all of this weekDays dates for the current year
			$current = getdate($cal);

			// Go to the first day of the year
			$cal = mktime($current['hours'],$current['minutes'],$current['seconds'],
							1,1,$current['year']);
			if (!date('l',$cal) == $weekDay->getDayName()) {
				$target = getdate(strtotime("+1 {$weekDay->getDayName()}",$cal));
				$cal = mktime($current['hours'],$current['minutes'],$current['seconds'],
								$target['mon'],$target['mday'],$target['year']);
			}
			while (date('Y',$cal) == $current['year']) {
				$days[] = $cal;
				$cal = strtotime('+1 week',$cal);
			}
    	}
        return $this->getOffsetDates($days, $weekDay->getOffset());
    }

    /**
     * Returns a single-element sublist containing the element of $dates at $offset.
     *
     * Valid offsets are from 1 to the size of the list.
     * If an invalid offset is supplied, all elements from $dates are returned
     *
     * @param array $dates An array of timestamps
     * @param int $offset
     * @return array An array of timestamps
     */
    private function getOffsetDates(array $dates,$offset)
    {
    	if ($offset == 0) {
			return $dates;
		}

    	$offsetDates = array();
    	$size = count($dates);

    	if ($offset < 0 && $offset >= -$size) {
			$offsetDates[] = $dates[$size + $offset];
		}
    	elseif ($offset > 0 && $offset <= $size) {
			$offsetDates[] = $dates[$offset - 1];
		}
    	return $offsetDates;
    }

    /**
     * Applies BYHOUR rules specified in this Recur instance to the specified date list.
     *
     * If no BYHOUR rules are specified the date list is returned unmodified.
     *
     * @param array $dates An array of timestamps
     * @return array An array of timestamps
     */
    private function getHourVariants(array $dates)
    {
    	if (!count($this->hourList)) {
			return $dates;
		}

    	$hourlyDates = array();
    	foreach ($dates as $date) {
    		$cal = getdate($date);
    		foreach ($this->hourList as $hour) {
				$hourlyDates[] = mktime($hour,$cal['minutes'],$cal['seconds'],
										$cal['mon'],$cal['mday'],$cal['year']);
    		}
    	}
        return $hourlyDates;
    }

    /**
     * Applies BYMINUTE rules specified in this Recur instance to the specified date list.
     *
     * If no BYMINUTE rules are specified the date list is returned unmodified.
     *
     * @param array $dates an array of timestamps
     */
    private function getMinuteVariants(array $dates)
    {
    	if (!count($this->minuteList)) {
			return $dates;
		}

    	$minutelyDates = array();
    	foreach ($dates as $date) {
			$cal = getdate($date);
			foreach ($this->minuteList as $minute) {
				$minutelyDates[] = mktime($cal['hours'],$minute,$cal['seconds'],
											$cal['mon'],$cal['mday'],$cal['year']);
			}
    	}
        return $minutelyDates;
    }


    private function validateFrequency()
    {
        if ($this->frequency == null) {
			throw new Exception('A recurrence rule MUST contain a FREQ rule part.');
		}
        switch ($this->getFrequency()) {
			case 'SECONDLY':	$this->calIncField = 'seconds';	break;
			case 'MINUTELY':	$this->calIncField = 'minutes'; break;
			case 'HOURLY':		$this->calIncField = 'hours';	break;
			case 'DAILY':		$this->calIncField = 'days';	break;
			case 'WEEKLY':		$this->calIncField = 'weeks';	break;
			case 'MONTHLY':		$this->calIncField = 'months';	break;
			case 'YEARLY':		$this->calIncField = 'years';	break;
			default:
				throw new Exception("Invalid FREQ rule part '{$this->frequency}' in recurrence rule");
        }
    }


	public function __toString()
	{
		$b = "FREQ={$this->frequency}";
		if ($this->interval >= 1) {
			$b.=";INTERVAL={$this->interval}";
		}
		if ($this->until != null) {
			$b.=";UNTIL={$this->until}";
		}
		if ($this->count >= 1) {
			$b.=";COUNT={$this->count}";
		}
		if (count($this->getMonthList())) {
			$b.=";BYMONTH=".implode(',',$this->monthList);
		}
		if (count($this->getWeekNoList())) {
			$b.=";BYWEEKNO=".implode(',',$this->weekNoList);
		}
		if (count($this->getYearDayList())) {
			$b.=";BYYEARDAY=".implode(',',$this->yearDayList);
		}
		if (count($this->getMonthDayList())) {
			$b.=";BYMONTHDAY=".implode(',',$this->monthDayList);
		}
		if (count($this->getDayList())) {
			$b.=";BYDAY=".implode(',',$this->dayList);
		}
		if (count($this->getHourList())) {
			$b.=";BYHOUR=".implode(',',$this->hourList);
		}
		if (count($this->getMinuteList())) {
			$b.=";BYMINUTE=".implode(',',$this->minuteList);
		}
		if (count($this->getSecondList())) {
			$b.=";BYSECOND=".implode(',',$this->secondList);
		}
		if (count($this->getSetPosList())) {
			$b.=";BYSETPOS=".implode(',',$this->setPosList);
		}
		return $b;
	}

	/**
	 * @return array An array of WeekDay objects
	 */
	public function getDayList()
	{
		return $this->dayList;
	}

	/**
	 * @return array Integers 0-23
	 */
	public function getHourList()
	{
		return $this->hourList;
	}

	/**
	 * @return array Integers 0-59
	 */
	public function getMinuteList()
	{
		return $this->minuteList;
	}

	/**
	 * @return array Integers 1-31
	 */
	public function getMonthDayList()
	{
		return $this->monthDayList;
	}

	/**
	 * @return array Integers 1-12
	 */
	public function getMonthList()
	{
		return $this->monthList;
	}

	/**
	 * @return array Integers 0-59
	 */
	public function getSecondList()
	{
		return $this->secondList;
	}

	/**
	 * @return array Integers 1-366
	 */
	public function getSetPosList()
	{
		return $this->setPosList;
	}

	/**
	 * @return array Integers 1-53
	 */
	public function getWeekNoList()
	{
		return $this->weekNoList;
	}

	/**
	 * @return array Integers 1-366
	 */
	public function getYearDayList()
	{
		return $this->yearDayList;
	}

	/**
	 * @return int
	 */
	public function getCount()
	{
		return $this->count;
	}

	/**
	 * Returns the hash of experimental values
	 * @return array
	 */
	public function getExperimentalValues()
	{
		return $this->experimentalValues;
	}

	/**
	 * @return string
	 */
	public function getFrequency()
	{
		return $this->frequency;
	}

	/**
	 * @return string
	 */
	public function getInterval()
	{
		return $this->interval;
	}

	/**
	 * @return timestamp
	 */
	public function getUntil()
	{
		return $this->until;
	}

	/**
	 * @return string
	 */
	public function getWeekStartDay()
	{
		return $this->weekStartDay;
	}


	public function setFrequency($string)
	{
		$this->frequency = $string;
	}

	public function setCount($int)
	{
		$this->count = (int)$int;
		$this->until = null;
	}

	public function setInterval($int)
	{
		$this->interval = (int)$int;
	}

	public function setBySecond($string)
	{
		foreach (explode(',',$string) as $number) {
			$this->secondList[] = (int) $number;
		}
	}

	public function setByMinute($string)
	{
		foreach (explode(',',$string) as $number) {
			$this->minuteList[] = (int) $number;
		}
	}

	public function setByHour($string)
	{
		foreach (explode(',',$string) as $number) {
			$this->hourList[] = (int) $number;
		}
	}

	public function setByDay($string)
	{
		foreach(explode(',',$string) as $day) {
			$this->dayList[] = new WeekDay($day);
		}
	}

	public function setByMonthDay($string)
	{
		foreach (explode(',',$string) as $number) {
			$this->monthDayList[] = (int) $number;
		}
	}

	public function setByYearDay($string)
	{
		foreach (explode(',',$string) as $number) {
			$this->yearDayList[] = (int) $number;
		}
	}

	public function setByWeekNo($string)
	{
		foreach (explode(',',$string) as $number) {
			$this->weekNoList[] = (int) $number;
		}
	}

	public function setByMonth($string)
	{
		foreach (explode(',',$string) as $number) {
			$this->monthList[] = (int) $number;
		}
	}

	public function setBySetPos($string)
	{
		foreach (explode(',',$string) as $number) {
			$this->setPosList[] = (int) $number;
		}
	}

	public function setWeekStartDay($string)
	{
		$this->weekStartDay = $string;
	}

	public function setUntil($string)
	{
		$until = $string;
		if ($until && strpos($string,'T')) {
			preg_match('/([0-9]{4})([0-9]{2})([0-9]{2})T([0-9]{2})([0-9]{2})([0-9]{2})/',$until,$regs);
			$this->until = mktime($regs[4],$regs[5],$regs[6],$regs[2],$regs[3],$regs[1]);
		}
		else {
			preg_match('/([0-9]{4})([0-9]{2})([0-9]{2})/',$until,$regs);
			$this->until = mktime(0,0,0,$regs[2],$regs[3],$regs[1]);
		}
		$this->count = null;
	}
}
