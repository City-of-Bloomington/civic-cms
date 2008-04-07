<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
class WeekDay
{
	private $day;
	private $offset = 0;

	private $names = array('SU'=>'Sunday','MO'=>'Monday','TU'=>'Tuesday','WE'=>'Wednesday',
							'TH'=>'Thursday','FR'=>'Friday','SA'=>'Saturday');

	public function __construct($string,$offset=null)
	{
		if ($offset)
		{
			$this->day = $string;
			$this->offset = (int) $offset;
		}
		else
		{
			# Parse the string for an offset
			if (strlen($string) > 2)
			{
				$this->day = substr($string,-2);
				$this->offset = (int) substr($string,0,-2);
			}
			else { $this->day = $string; }
		}
	}

	public function __toString()
	{
		if ($this->offset) { return $this->offset.$this->day; }
		else { return $this->day; }
	}

	public function getDayName() { return $this->names[$this->day]; }

	public function getDay() { return $this->day; }
	public function getOffset() { return $this->offset; }
}