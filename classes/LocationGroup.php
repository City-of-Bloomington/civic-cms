<?php
/**
 * @copyright 2007-2008 City of Bloomington, Indiana
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
class LocationGroup extends ActiveRecord
{
	private $id;
	private $name;
	private $department_id;
	private $description;
	private $defaultFlag;

	private $department;

	/**
	 * This will load all fields in the table as properties of this class.
	 * You may want to replace this with, or add your own extra, custom loading
	 */
	public function __construct($id=null)
	{
		$PDO = Database::getConnection();

		if ($id)
		{
			$sql = 'select * from locationGroups where id=?';

			$query = $PDO->prepare($sql);
			$query->execute(array($id));

			$result = $query->fetchAll();
			if (!count($result)) { throw new Exception('locations/unknownLocationGroup'); }
			foreach($result[0] as $field=>$value) { if ($value) $this->$field = $value; }
		}
		else
		{
			# This is where the code goes to generate a new, empty instance.
			# Set any default values for properties that need it here
			$this->department_id = $_SESSION['USER']->getDepartment_id();
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
		if (!$this->name) { throw new Exception('missingRequiredFields'); }

		# Make sure there can only be one default locationGroup
		if ($this->isDefault()) {
			$pdo = Database::getConnection();
			$pdo->query('update locationGroups set defaultFlag=null');
		}

		$fields = array();
		$fields['name'] = $this->name;
		$fields['department_id'] = $this->department_id;
		$fields['description'] = $this->description ? $this->description : null;
		$fields['defaultFlag'] = $this->defaultFlag ? 1 : null;

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

		$sql = "update locationGroups set $preparedFields where id={$this->id}";
		$query = $PDO->prepare($sql);
		$query->execute($values);
	}

	private function insert($values,$preparedFields)
	{
		$PDO = Database::getConnection();

		$sql = "insert locationGroups set $preparedFields";
		$query = $PDO->prepare($sql);
		$query->execute($values);
		$this->id = $PDO->lastInsertID();
	}

	public function delete()
	{
		if ($this->id)
		{
			$PDO = Database::getConnection();

			$query = $PDO->prepare('delete from locationGroup_locations where locationGroup_id=?');
			$query->execute(array($this->id));

			$query = $PDO->prepare('delete from locationGroups where id=?');
			$query->execute(array($this->id));
		}
	}

	public function permitsEditingBy($user)
	{
		if ($user->hasRole(array('Administrator','Webmaster','Publisher'))) { return true; }
		if ($user->hasRole('Content Creator') && $user->getDepartment_id()==$this->department_id) { return true; }
		return false;
	}

	public function getLocations()
	{
		return new LocationList(array('locationGroup_id'=>$this->id));
	}

	public function __toString() { return $this->name; }
	public function getURL() { return BASE_URL.'/locations/?locationGroup_id='.$this->id; }
	public function isDefault() { return $this->defaultFlag ? true : false; }

	/**
	 * Generic Getters
	 */
	public function getId() { return $this->id; }
	public function getName() { return $this->name; }
	public function getDepartment_id() { return $this->department_id; }
	public function getDescription() { return $this->description; }
	public function getDefaultFlag() { return $this->defaultFlag; }
	public function getDepartment()
	{
		if ($this->department_id)
		{
			if (!$this->department) { $this->department = new Department($this->department_id); }
			return $this->department;
		}
		else return null;
	}

	/**
	 * Generic Setters
	 */
	public function setName($string) { $this->name = trim($string); }
	public function setDepartment_id($int) { $this->department = new Department($int); $this->department_id = $int; }
	public function setDescription($text) { $this->description = trim($text); }
	public function setDepartment($department) { $this->department_id = $department->getId(); $this->department = $department; }
	public function setDefaultFlag($boolean) { $this->defaultFlag = $boolean ? 1 : null; }
}
