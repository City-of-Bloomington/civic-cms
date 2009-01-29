<?php
/**
 * @copyright Copyright (C) 2008 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
class Alert extends ActiveRecord
{
	private $id;
	private $title;
	private $alertType_id;
	private $startTime;
	private $endTime;
	private $url;
	private $text;

	private $alertType;

	/**
	 * This will load all fields in the table as properties of this class.
	 * You may want to replace this with, or add your own extra, custom loading
	 */
	public function __construct($id=null)
	{
		if ($id)
		{
			$PDO = Database::getConnection();
			
			if (ctype_digit($id)) { $where = 'where id=?'; }
			else { $where = 'where title=?'; }
			
			$sql = "select id,title,alertType_id,url,text,
					unix_timestamp(startTime) as startTime,
					unix_timestamp(endTime) as endTime
					from alerts $where";
			$query = $PDO->prepare($sql);
			$query->execute(array($id));

			$result = $query->fetchAll(PDO::FETCH_ASSOC);
			if (count($result))
			{
				foreach($result[0] as $field=>$value)  { if ($value) $this->$field = $value; }
			}
			else
			{
				# If they passed in a string for the constructor, use that string
				# as the title, and go ahead and create a new Alert
				if (!ctype_digit($id)) { $this->title = $id; }
				else { throw new Exception('alerts/unknownAlert'); }
			}
		}
		else
		{
			# This is where the code goes to generate a new, empty instance.
			# Set any default values for properties that need it here
			$this->setAlertType(new AlertType('Custom'));
		}
	}
	
	/**
	 * Throws an exception if anything's wrong
	 * @throws Exception $e
	 */
	public function validate()
	{
		# Check for required fields here.  Throw an exception if anything is missing.
		if (!$this->title || !$this->text || !$this->startTime || !$this->endTime || !$this->alertType_id)
		{
			throw new Exception('missingRequiredFields');
		}
		
		if ($this->endTime <= $this->startTime) { throw new Exception('invalidEndTime'); }
	}

	/**
	 * This generates generic SQL that should work right away.
	 * You can replace this $fields code with your own custom SQL
	 * for each property of this class,
	 */
	public function save()
	{
		$this->validate();
		
		$fields = array();
		$fields['title'] = $this->title;
		$fields['alertType_id'] = $this->alertType_id;
		$fields['startTime'] = date('Y-m-d H:i:s',$this->startTime);
		$fields['endTime'] = date('Y-m-d H:i:s',$this->endTime);
		$fields['text'] = $this->text;
		$fields['url'] = $this->url ? $this->url : null;

		# Split the fields up into a preparedFields array and a values array.
		# PDO->execute cannot take an associative array for values, so we have
		# to strip out the keys from $fields
		$preparedFields = array();
		foreach($fields as $key=>$value)
		{
			$preparedFields[] = "$key=?";
			$values[] = $value;
		}
		$preparedFields = implode(",",$preparedFields);


		if ($this->id) { $this->update($values,$preparedFields); }
		else { $this->insert($values,$preparedFields); }
	}

	private function update($values,$preparedFields)
	{
		$PDO = Database::getConnection();

		$sql = "update alerts set $preparedFields where id={$this->id}";
		$query = $PDO->prepare($sql);
		$query->execute($values);
	}

	private function insert($values,$preparedFields)
	{
		$PDO = Database::getConnection();

		$sql = "insert alerts set $preparedFields";
		$query = $PDO->prepare($sql);
		$query->execute($values);
		$this->id = $PDO->lastInsertID();
	}

	public function delete()
	{
		if ($this->id)
		{
			$PDO = Database::getConnection();
			$query = $PDO->prepare('delete from alerts where id=?');
			$query->execute(array($this->id));
		}
	}
	#----------------------------------------------------------------
	# Generic Getters
	#----------------------------------------------------------------
	public function getId() { return $this->id; }
	public function getTitle() { return $this->title; }
	public function getAlertType_id() { return $this->alertType_id; }

	public function getStartTime($format=null)
	{
		if ($format && $this->startTime)
		{
			if (strpos($format,'%')!==false) { return strftime($format,$this->startTime); }
			else { return date($format,$this->startTime); }
		}
		else return $this->startTime;
	}

	public function getEndTime($format=null)
	{
		if ($format && $this->endTime)
		{
			if (strpos($format,'%')!==false) { return strftime($format,$this->endTime); }
			else { return date($format,$this->endTime); }
		}
		else return $this->endTime;
	}
	public function getUrl() { return $this->url; }
	public function getText() { return $this->text; }

	public function getAlertType()
	{
		if ($this->alertType_id)
		{
			if (!$this->alertType) { $this->alertType = new AlertType($this->alertType_id); }
			return $this->alertType;
		}
		else return null;
	}
		
	#----------------------------------------------------------------
	# Generic Setters
	#----------------------------------------------------------------
	public function setTitle($string) { $this->title = trim($string); }
	public function setAlertType_id($int) { $this->alertType = new AlertType($int); $this->alertType_id = $int; }

	public function setStartTime($timestamp)
	{
		if (is_array($timestamp)) { $this->startTime = $this->dateArrayToTimestamp($timestamp); }
		elseif(ctype_digit($timestamp)) { $this->startTime = $timestamp; }
		else { $this->startTime = strtotime($timestamp); }
	}

	public function setEndTime($timestamp)
	{
		if (is_array($timestamp)) { $this->endTime = $this->dateArrayToTimestamp($timestamp); }
		elseif(ctype_digit($timestamp)) { $this->endTime = $timestamp; }
		else { $this->endTime = strtotime($timestamp); }
	}
	public function setUrl($string) { $this->url = trim($string); }
	public function setText($text) { $this->text = $text; }

	public function setAlertType($alertType) { $this->alertType_id = $alertType->getId(); $this->alertType = $alertType; }


	
	#----------------------------------------------------------------
	# Custom Functions
	# We recommend adding all your custom code down here at the bottom
	#----------------------------------------------------------------
}
