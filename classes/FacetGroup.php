<?php
/**
 * @copyright 2007-2009 City of Bloomington, Indiana
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
class FacetGroup extends ActiveRecord
{
	private $id;
	private $name;
	private $description;

	private $facets = array();
	private $related_groups = array();
	private $departments = array();

	/**
	 * This will load all fields in the table as properties of this class.
	 * You may want to replace this with, or add your own extra, custom loading
	 */
	public function __construct($id=null)
	{
		if ($id) {
			$pdo = Database::getConnection();
			if (is_numeric($id)) {
				$sql = 'select * from facetGroups where id=?';
			}
			else {
				$sql = 'select * from facetGroups where name=?';
			}
			$query = $pdo->prepare($sql);
			$query->execute(array($id));

			$result = $query->fetchAll();
			if (!count($result)) {
				throw new Exception('facets/unknownFacetGroup');
			}
			foreach ($result[0] as $field=>$value) {
				if ($value) $this->$field = $value;
			}
		}
		else {
			// This is where the code goes to generate a new, empty instance.
			// Set any default values for properties that need it here
		}
	}

	/**
	 * Checks for required fields.  Throw an exception if anything is missing.
	 * @throws Exception
	 */
	public function validate()
	{
		if (!$this->name) {
			throw new Exception('missingName');
		}
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
		$fields['name'] = $this->name;
		$fields['description'] = $this->description ? $this->description : null;

		// Split the fields up into a preparedFields array and a values array.
		// PDO->execute cannot take an associative array for values, so we have
		// to strip out the keys from $fields
		$preparedFields = array();
		foreach ($fields as $key=>$value) {
			$preparedFields[] = "$key=?";
			$values[] = $value;
		}
		$preparedFields = implode(",",$preparedFields);


		if ($this->id) {
			$this->update($values,$preparedFields);
		}
		else {
			$this->insert($values,$preparedFields);
		}

		$this->saveRelatedGroups();
		$this->saveDepartments();
	}

	private function update($values,$preparedFields)
	{
		$pdo = Database::getConnection();

		$sql = "update facetGroups set $preparedFields where id={$this->id}";
		$query = $pdo->prepare($sql);
		$query->execute($values);
	}

	private function insert($values,$preparedFields)
	{
		$pdo = Database::getConnection();

		$sql = "insert facetGroups set $preparedFields";
		$query = $pdo->prepare($sql);
		$query->execute($values);
		$this->id = $pdo->lastInsertID();
	}

	//----------------------------------------------------------------
	// Generic Getters
	//----------------------------------------------------------------
	public function getId()
	{
		return $this->id;
	}

	public function getName()
	{
		return $this->name;
	}

	public function getDescription()
	{
		return $this->description;
	}

	//----------------------------------------------------------------
	// Generic Setters
	//----------------------------------------------------------------
	public function setName($string)
	{
		$this->name = trim($string);
	}

	public function setDescription($string)
	{
		$this->description = trim(str_replace(array("\r\n","\n","\r"),' ',$string));
	}

	//----------------------------------------------------------------
	// Custom Functions
	//----------------------------------------------------------------
	/**
	 * @return string
	 */
	public function __toString()
	{
		return $this->name;
	}

	/**
	 * @return string
	 */
	public function getURL()
	{
		return BASE_URL.'/facets/viewFacetGroup.php?facetGroup_id='.$this->id;
	}

	/**
	 * @return array An array of FacetGroups
	 */
	public function getRelatedGroups()
	{
		$pdo = Database::getConnection();

		if ($this->id) {
			if (!count($this->related_groups)) {
				$query = $pdo->prepare('select relatedGroup_id from facetGroups_related where facetGroup_id=?');
				$query->execute(array($this->id));
				$result = $query->fetchAll();
				foreach ($result as $row) {
					$this->related_groups[$row['relatedGroup_id']] = new FacetGroup($row['relatedGroup_id']);
				}
			}
		}
		return $this->related_groups;
	}

	/**
	 * @param array $group_ids
	 */
	public function setRelatedGroups(array $group_ids)
	{
		$this->related_groups = array();
		foreach ($group_ids as $id) {
			$group = new FacetGroup($id);
			$this->related_groups[$id] = $group;
		}
	}

	/**
	 * Returns whether this group is related to some other group
	 * @param FacetGroup $group
	 * @return boolean
	 */
	public function isRelated(FacetGroup $group)
	{
		return array_key_exists($group->getId(),$this->getRelatedGroups());
	}

	private function saveRelatedGroups()
	{
		if ($this->id) {
			$pdo = Database::getConnection();
			$query = $pdo->prepare('delete from facetGroups_related where facetGroup_id=?');
			$query->execute(array($this->id));

			$query = $pdo->prepare('insert facetGroups_related values(?,?)');
			foreach ($this->getRelatedGroups() as $group) {
				$query->execute(array($this->id,$group->getId()));
			}
		}
	}

	/**
	 * @return array An array of Facets with facet_id as the index
	 */
	public function getFacets()
	{
		if (!count($this->facets)) {
			$list = new FacetList(array('facetGroup_id'=>$this->id));
			foreach ($list as $facet) {
				$this->facets[$facet->getId()] = $facet;
			}
		}
		return $this->facets;
	}

	/**
	 * @return boolean
	 */
	public function hasFacet($facet)
	{
		return in_array($facet->getId(),array_keys($this->getFacets()));
	}

	/**
	 * @return array An array of Departments with department_id as the index
	 */
	public function getDepartments()
	{
		if ($this->id) {
			if (!count($this->departments)) {
				$list = new DepartmentList(array('facetGroup_id'=>$this->id));
				foreach ($list as $department) {
					$this->departments[$department->getId()] = $department;
				}
			}
		}
		return $this->departments;
	}

	/**
	 * @param array $department_ids
	 */
	public function setDepartments(array $department_ids)
	{
		$this->departments = array();
		foreach ($department_ids as $id) {
			$department = new Department($id);
			$this->departments[$department->getId()] = $department;
		}
	}

	/**
	 * @param Department $department
	 * @return boolean
	 */
	public function hasDepartment($department)
	{
		return in_array($department->getId(),array_keys($this->getDepartments()));
	}

	private function saveDepartments()
	{
		if ($this->id) {
			$pdo = Database::getConnection();

			$query = $pdo->prepare('delete from facetGroup_departments where facetGroup_id=?');
			$query->execute(array($this->id));

			$query = $pdo->prepare('insert facetGroup_departments values(?,?)');
			foreach ($this->getDepartments() as $department) {
				$query->execute(array($this->id,$department->getId()));
			}
		}
	}

	/**
	 * Returns the number of documents associated with the facets
	 * in this facet group
	 */
	public function hasDocuments($fields=null)
	{
		$count = 0;
		foreach ($this->getFacets() as $facet) {
			$count+= count($facet->getDocuments($fields));
		}
		return $count;
	}
}
