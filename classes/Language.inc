<?php
/**
 * @copyright Copyright (C) 2007-2008 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 */
class Language extends ActiveRecord
{
	private $id;
	private $code;
	private $english;
	private $native;

	/**
	 * This will load all fields in the table as properties of this class.
	 * You may want to replace this with, or add your own extra, custom loading
	 */
	public function __construct($id=null)
	{
		if ($id)
		{
			$PDO = Database::getConnection();
			if (is_numeric($id)) { $sql = 'select * from languages where id=?'; }
			else { $sql = 'select * from languages where code=?'; }

			$query = $PDO->prepare($sql);
			$query->execute(array($id));

			$result = $query->fetchAll();
			if (!count($result)) { throw new Exception('languages/unknownLanguage'); }
			foreach($result[0] as $field=>$value) { if ($value) $this->$field = $value; }
		}
		else
		{
			# This is where the code goes to generate a new, empty instance.
			# Set any default values for properties that need it here
		}
	}


	/**
	 * This generates generic SQL that should work right away.
	 * You can replace this $fields code with your own custom SQL
	 * for each property of this class,
	 */
	public function save()
	{
		# Check for required fields here.  Throw an exception if anything is missing.

		$fields = array();
		$fields['code'] = $this->code ? $this->code : null;
		$fields['english'] = $this->english ? $this->english : null;
		$fields['native'] = $this->native ? $this->native : null;

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

		$sql = "update languages set $preparedFields where id={$this->id}";
		$query = $PDO->prepare($sql);
		$query->execute($values);
	}

	private function insert($values,$preparedFields)
	{
		$PDO = Database::getConnection();

		$sql = "insert languages set $preparedFields";
		$query = $PDO->prepare($sql);
		$query->execute($values);
		$this->id = $PDO->lastInsertID();
	}

	/**
	 * Returns the number of documents in the system for this language
	 */
	public function getNumDocuments()
	{
		return count(glob(APPLICATION_HOME.'/data/documents/*/*/*/*.'.$this->code));
	}

	/**
	 * Generic Getters
	 */
	public function getId() { return $this->id; }
	public function getCode() { return $this->code; }
	public function getEnglish() { return $this->english; }
	public function getNative() { return $this->native; }

	/**
	 * Generic Setters
	 */
	public function setCode($char) { $this->code = $char; }
	public function setEnglish($string) { $this->english = trim($string); }
	public function setNative($string) { $this->native = trim($string); }
}
