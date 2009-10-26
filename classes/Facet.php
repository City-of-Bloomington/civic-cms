<?php
/**
 * @copyright 2006-2009 City of Bloomington, Indiana
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
class Facet extends ActiveRecord
{
	private $id;
	private $name;
	private $facetGroup_id;
	private $description;
	private $ordering;

	private $facetGroup;
	private $documents;

	/**
	 * This will load all fields in the table as properties of this class.
	 * You may want to replace this with, or add your own extra, custom loading
	 */
	public function __construct($id=null)
	{
		if ($id) {
			$PDO = Database::getConnection();
			$query = $PDO->prepare('select * from facets where id=?');
			$query->execute(array($id));

			$result = $query->fetchAll();
			if (!count($result)) {
				throw new Exception('facets/unknownFacet');
			}
			foreach($result[0] as $field=>$value) {
				if ($value) {
					$this->$field = $value;
				}
			}
		}
		else {
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
		if (!$this->name) {
			throw new Exception('missingName');
		}
		if (!$this->facetGroup_id) {
			throw new Exception('facets/missingGroup');
		}

		$fields = array();
		$fields['name'] = $this->name;
		$fields['facetGroup_id'] = $this->facetGroup_id;
		$fields['description'] = $this->description ? $this->description : null;
		$fields['ordering'] = $this->ordering ? $this->ordering : null;

		# Split the fields up into a preparedFields array and a values array.
		# PDO->execute cannot take an associative array for values, so we have
		# to strip out the keys from $fields
		$preparedFields = array();
		foreach($fields as $key=>$value) {
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
	}

	private function update($values,$preparedFields)
	{
		$PDO = Database::getConnection();

		$sql = "update facets set $preparedFields where id={$this->id}";
		$query = $PDO->prepare($sql);
		$query->execute($values);
	}

	private function insert($values,$preparedFields)
	{
		$PDO = Database::getConnection();

		$sql = "insert facets set $preparedFields";
		$query = $PDO->prepare($sql);
		$query->execute($values);
		$this->id = $PDO->lastInsertID();
	}

	public function delete()
	{
		$PDO = Database::getConnection();
		if ($this->id) {
			$query = $PDO->prepare('delete from document_facets where facet_id=?');
			$query->execute(array($this->id));

			$query = $PDO->prepare('delete from facets where id=?');
			$query->execute(array($this->id));
		}
	}

	//----------------------------------------------------------------
	// Generic Getters
	//----------------------------------------------------------------
	public function getId() { return $this->id; }
	public function getName() { return $this->name; }
	public function getFacetGroup_id() { return $this->facetGroup_id; }
	public function getDescription() { return $this->description; }
	public function getOrdering() { return $this->ordering; }
	public function getFacetGroup()
	{
		if ($this->facetGroup_id) {
			if (!$this->facetGroup) {
				$this->facetGroup = new FacetGroup($this->facetGroup_id);
			}
			return $this->facetGroup;
		}
		else return null;
	}



	//----------------------------------------------------------------
	// Generic Setters
	//----------------------------------------------------------------
	public function setName($string)
	{
		$this->name = trim($string);
	}

	public function setFacetGroup_id($int)
	{
		$this->facetGroup = new FacetGroup($int);
		$this->facetGroup_id = $int;
	}

	public function setDescription($string)
	{
		$this->description = trim($string);
	}

	public function setOrdering($int)
	{
		$this->ordering = (int) $int;
	}

	public function setFacetGroup($facetGroup)
	{
		$this->facetGroup_id = $facetGroup->getId();
		$this->facetGroup = $facetGroup;
	}

	//----------------------------------------------------------------
	// Custom Functions
	// We recommend adding all your custom code down here at the bottom
	//----------------------------------------------------------------
	public function __toString()
	{
		return $this->name;
	}

	public function getURL()
	{
		return BASE_URL.'/facets/viewFacet.php?facet_id='.$this->id;
	}

	/**
	 * @param FacetGroup $group
	 * @return boolean
	 */
	public function hasGroup($group)
	{
		return in_array($group->getId(),array_keys($this->getGroups()));
	}


	/**
	 * Facets are related to each other if they both have the same documents
	 * @return FacetList
	 */
	public function getRelatedFacets()
	{
		return new FacetList(array('documentList'=>$this->getDocuments()));
	}

	public function getRelatedGroups()
	{
		return $this->getFacetGroup()->getRelatedGroups();
	}

	/**
	 * Returns everything that's been tagged with this Facet
	 *
	 * Facets can be used for Documents and/or Locations.  This will return
	 * an array of mixed data (Documents and Locations.)
	 *
	 * @return array
	 */
	public function getItems()
	{
		$items = array();
		if ($this->id) {
			$pdo = Database::getConnection();
			$sql = "(select 'Document' as type,df.document_id as id,title as name
					from document_facets df
					left join documents docs on df.document_id=docs.id
					where df.facet_id=?
					and (docs.publishDate<=now() and (retireDate is null or retireDate>now())))
					union
					(select 'Location' as type,lf.location_id as id,locs.name as name
					from location_facets lf
					left join locations locs on lf.location_id=locs.id
					where lf.facet_id=?)
					order by name";
			$query = $pdo->prepare($sql);
			$query->execute(array($this->id,$this->id));
			$result = $query->fetchAll();
			foreach ($result as $row) {
				$items[] = new $row['type']($row['id']);
			}
		}
		return $items;
	}

	/**
	 * @param array $fields
	 *  Pass in an array of extra fields used to populate the DocumentList
	 */
	public function getDocuments($fields=null)
	{
		if (!is_array($fields)) {
			$fields = array();
		}
		$fields['facet_id'] = $this->id;
		$fields['active'] = date('Y-m-d');

		if (!$this->documents) {
			$this->documents = new DocumentList($fields);
		}
		return $this->documents;
	}
}
