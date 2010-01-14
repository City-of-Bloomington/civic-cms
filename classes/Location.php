<?php
/**
 * @copyright 2006-2009 City of Bloomington, Indiana
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
class Location
{
	private $id;
	private $name;
	private $locationType_id;
	private $address;
	private $phone;
	private $description;
	private $website;
	private $content;
	private $latitude;
	private $longitude;
	private $department_id;
	private $handicap_accessible;

	private $locationType;
	private $department;
	private $groups = array();

	/**
	 * This will load all fields in the table as properties of this class.
	 * You may want to replace this with, or add your own extra, custom loading
	 */
	public function __construct($id=null)
	{
		if ($id)
		{
			$PDO = Database::getConnection();
			$sql = 'select * from locations where id=?';
			$query = $PDO->prepare($sql);
			$query->execute(array($id));

			$result = $query->fetchAll();
			if (!count($result)) { throw new Exception('locations/unknownLocation'); }
			foreach($result[0] as $field=>$value) { if ($value) $this->$field = $value; }
		}
		else
		{
			# This is where the code goes to generate a new, empty instance.
			# Set any default values for properties that need it here
			$this->locationType_id = 1;
			if (isset($_SESSION['USER'])) { $this->department_id = $_SESSION['USER']->getDepartment_id(); }
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
		if (!$this->name) { throw new Exception('missingName'); }
		if (!$this->description) { throw new Exception('missingDescription'); }
		if (!$this->address) { throw new Exception('locations/missingAddress'); }
		if (!$this->department_id) { throw new Exception('locations/missingDepartment'); }

		$fields = array();
		$fields['name'] = $this->name ? $this->name : null;
		$fields['locationType_id'] = $this->locationType_id ? $this->locationType_id : 1;
		$fields['address'] = $this->address ? $this->address : null;
		$fields['phone'] = $this->phone ? $this->phone : null;
		$fields['description'] = $this->description ? $this->description : null;
		$fields['website'] = $this->website ? $this->website : null;
		$fields['content'] = $this->content ? $this->content : null;
		$fields['latitude'] = $this->latitude ? $this->latitude : null;
		$fields['longitude'] = $this->longitude ? $this->longitude : null;
		$fields['department_id'] = $this->department_id;
		$fields['handicap_accessible'] = $this->handicap_accessible ? true : false;

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

		$this->saveLocationGroups();
	}

	private function update($values,$preparedFields)
	{
		$PDO = Database::getConnection();

		$sql = "update locations set $preparedFields where id={$this->id}";
		$query = $PDO->prepare($sql);
		$query->execute($values);
	}

	private function insert($values,$preparedFields)
	{
		$PDO = Database::getConnection();

		$sql = "insert locations set $preparedFields";
		$query = $PDO->prepare($sql);
		$query->execute($values);
		$this->id = $PDO->lastInsertID();
	}

	public function delete()
	{
		if($this->id)
		{
			$PDO = Database::getConnection();

			$query = $PDO->prepare('update events set location_id=null where location_id=?');
			$query->execute(array($this->id));

			$query = $PDO->prepare('delete from locationGroup_locations where location_id=?');
			$query->execute(array($this->id));

			$query = $PDO->prepare('delete from locations where id=?');
			$query->execute(array($this->id));
		}
	}

	private function saveLocationGroups()
	{
		if ($this->id)
		{
			$PDO = Database::getConnection();

			$query = $PDO->prepare('delete from locationGroup_locations where location_id=?');
			$query->execute(array($this->id));

			$query = $PDO->prepare('insert locationGroup_locations values(?,?)');
			foreach($this->groups as $id=>$group)
			{
				$query->execute(array($id,$this->id));
			}
		}
	}


	/**
	 * Generic Getters
	 */
	public function getId() { return $this->id; }
	public function getName() { return $this->name; }
	public function getLocationType_id() { return $this->locationType_id; }
	public function getAddress() { return $this->address; }
	public function getPhone() { return $this->phone; }
	public function getDescription() { return $this->description; }
	public function getWebsite() {return $this->website; }
	public function getContent() { return $this->content; }
	public function getLatitude() { return $this->latitude; }
	public function getLongitude() { return $this->longitude; }
	public function getDepartment_id() { return $this->department_id; }
	public function getHandicap_accessible() { return $this->handicap_accessible; }
	public function getDepartment()
	{
		if ($this->department_id)
		{
			if (!$this->department) { $this->department = new Department($this->department_id); }
			return $this->department;
		}
		else return null;
	}
	public function getLocationType()
	{
		if ($this->locationType_id)
		{
			if (!$this->locationType) { $this->locationType = new LocationType($this->locationType_id); }
			return $this->locationType;
		}
		else return null;
	}

	/**
	 * Generic Setters
	 */
	public function setName($string) { $this->name = trim($string); }
	public function setLocationType_id($int) { $this->locationType = new LocationType($int); $this->locationType_id = $int; }
	public function setAddress($string) { $this->address = trim($string); }
	public function setPhone($string) { $this->phone = trim($string); }
	public function setDescription($string) { $this->description = trim(str_replace(array("\r\n","\n","\r"),' ',$string)); }
	public function setWebsite($string) { $this->website = trim($string); }
	public function setContent($text) { $this->content = $text; }
	public function setLatitude($float) { $this->latitude = preg_replace('/[^0-9.\-]/','',$float); }
	public function setLongitude($float) { $this->longitude = preg_replace('/[^0-9.\-]/','',$float); }
	public function setDepartment_id($int) { $this->department = new Department($int); $this->department_id = $int; }
	public function setHandicap_accessible($bool) { $this->handicap_accessible = $bool ? true : false; }

	public function setDepartment($department) { $this->department_id = $department->getId(); $this->department = $department; }
	public function setLocationType($locationType) { $this->locationType_id = $locationType->getId(); $this->locationType = $locationType; }

	/**
	 * Custom Functions
	 */
	public function __toString() { return $this->name; }
	public function getType() { return $this->getLocationType()->getType(); }
	public function getURL() { return BASE_URL.'/locations/viewLocation.php?location_id='.$this->id; }
	public function isHandicapAccessible() { return $this->handicap_accessible ? true : false; }

	public function getLocationGroups()
	{
		if ($this->id)
		{
			if (!count($this->groups))
			{
				$list = new LocationGroupList(array('location_id'=>$this->id));
				foreach($list as $group) { $this->groups[$group->getId()] = $group; }
			}
		}
		return $this->groups;
	}
	public function hasGroup($group)
	{
		$id = is_int($group) ? $group : $group->getId();
		return in_array($id,array_keys($this->getLocationGroups()));
	}
	public function setLocationGroups(array $group_ids)
	{
		$this->groups = array();
		foreach($group_ids as $id)
		{
			$this->groups[$id] = new LocationGroup($id);
		}
	}

	public function permitsEditingBy($user)
	{
		if ($user->hasRole(array('Administrator','Webmaster','Publisher'))) { return true; }
		if ($user->hasRole('Content Creator') && $user->getDepartment_id()==$this->department_id) { return true; }
		return false;
	}

	/**
	 * Calculates the distance in miles
	 *
	 * This function calculates distance in miles based on the
	 * spherical law of cosines.  It should be accurate down to about 3ft.
	 * This formula was taken from:
	 * http://www.movable-type.co.uk/scripts/latlong.html
	 *
	 * @param float $latitude
	 * @param float $longitude
	 * @return float
	 */
	public function getDistance($latitude,$longitude)
	{
		//$earthRadius = 6371; // Kilometers
		$earthRadius = 3958; // Miles
		//$milesConversion = 0.621371192237334;

		if ($this->latitude && $this->longitude) {
			$distance = acos(sin(deg2rad($this->latitude)) * sin(deg2rad($latitude))
						+ cos(deg2rad($this->latitude)) * cos(deg2rad($latitude))
						* cos(deg2rad($longitude - $this->longitude))) * $earthRadius;
			return $distance;
		}
	}

	/**
	 * @return FacetGroupList
	 */
	public function getFacetGroups()
	{
		return new FacetGroupList(array('location_id'=>$this->id));
	}

	/**
	 * Returns facets for this Location
	 *
	 * You can pass in additional search parameters
	 *
	 * @param array $fields
	 * @return FacetList
	 */
	public function getFacets(array $fields=null)
	{
		if ($this->id) {
			$search = array('location_id'=>$this->id);
			if ($fields) {
				$search = array_merge($search,$fields);
			}
			return new FacetList($search);
		}
		return array();
	}

	/**
	 * Takes an array of id numbers for facets and saves them to the database
	 *
	 * @param array $facet_ids The array of ID numbers for the facets
	 */
	public function setFacets(array $facet_ids)
	{
		// We need an ID to save the facets.  If they're adding a new Location,
		// we have to save the Location to the database, and get an ID back,
		// before we add the facets
		if (!$this->id) {
			$this->save();
		}

		$PDO = Database::getConnection();

		$query = $PDO->prepare('delete from location_facets where location_id=?');
		$query->execute(array($this->id));

		$query = $PDO->prepare('insert location_facets values(?,?)');
		foreach($facet_ids as $facet_id) {
			$query->execute(array($this->id,$facet_id));
		}
	}

	/**
	 * @param Facet $facet
	 * @return boolean
	 */
	public function hasFacet($facet)
	{
		$PDO = Database::getConnection();
		$query = $PDO->prepare('select facet_id from location_facets where location_id=? and facet_id=?');
		$query->execute(array($this->id,$facet->getId()));
		$result = $query->fetchAll();
		return count($result) ? true : false;
	}
}
