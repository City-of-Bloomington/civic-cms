<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
	class FacetGroup extends ActiveRecord
	{
		private $id;
		private $name;

		private $facets = array();
		private $related_groups = array();
		private $departments = array();

		/**
		 * This will load all fields in the table as properties of this class.
		 * You may want to replace this with, or add your own extra, custom loading
		 */
		public function __construct($id=null)
		{
			global $PDO;

			if ($id)
			{
				if (is_numeric($id)) { $sql = 'select * from facetGroups where id=?'; }
				else { $sql = 'select * from facetGroups where name=?'; }
				try
				{
					$query = $PDO->prepare($sql);
					$query->execute(array($id));
				}
				catch (Exception $e) { throw $e; }

				$result = $query->fetchAll();
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
			if (!$this->name) { throw new Exception('missingName'); }

			$fields = array();
			$fields['name'] = $this->name;

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

			$this->saveRelatedGroups();
			$this->saveDepartments();
		}

		private function update($values,$preparedFields)
		{
			global $PDO;

			$sql = "update facetGroups set $preparedFields where id={$this->id}";
			if (false === $query = $PDO->prepare($sql)) { $e = $PDO->errorInfo(); throw new Exception($sql.$e[2]); }
			if (false === $query->execute($values)) { $e = $PDO->errorInfo(); throw new Exception($sql.$e[2]); }
		}

		private function insert($values,$preparedFields)
		{
			global $PDO;

			$sql = "insert facetGroups set $preparedFields";
			if (false === $query = $PDO->prepare($sql)) { $e = $PDO->errorInfo(); throw new Exception($sql.$e[2]); }
			if (false === $query->execute($values)) { $e = $PDO->errorInfo(); throw new Exception($sql.$e[2]); }
			$this->id = $PDO->lastInsertID();
		}

		public function getRelatedGroups()
		{
			global $PDO;

			if ($this->id)
			{
				if (!count($this->related_groups))
				{
					$sql = "select relatedGroup_id from facetGroups_related where facetGroup_id={$this->id}";
					$query = $PDO->query($sql);
					$result = $query->fetchAll();
					foreach($result as $row)
					{
						$this->related_groups[$row['relatedGroup_id']] = new FacetGroup($row['relatedGroup_id']);
					}
				}
			}
			return $this->related_groups;
		}

		public function setRelatedGroups(array $group_ids)
		{
			$this->related_groups = array();
			foreach($group_ids as $id)
			{
				$group = new FacetGroup($id);
				$this->related_groups[$id] = $group;
			}
		}

		private function saveRelatedGroups()
		{
			global $PDO;
			if ($this->id)
			{
				$sql = "delete from facetGroups_related where facetGroup_id={$this->id}";
				if (false === $PDO->exec($sql)) { $e = $PDO->errorInfo(); throw new Exception($sql.$e[2]); }

				$query = $PDO->prepare('insert facetGroups_related values(?,?)');
				foreach($this->getRelatedGroups() as $group)
				{
					$query->execute(array($this->id,$group->getId()));
				}
			}
		}

		public function __toString() { return $this->name; }

		public function getFacets()
		{
			if (!count($this->facets))
			{
				$list = new FacetList(array('facetGroup_id'=>$this->id));
				foreach($list as $facet) { $this->facets[$facet->getId()] = $facet; }
			}
			return $this->facets;
		}
		public function hasFacet($facet) { return in_array($facet->getId(),array_keys($this->getFacets())); }


		public function getDepartments()
		{
			if ($this->id)
			{
				if (!count($this->departments))
				{
					$list = new DepartmentList(array('facetGroup_id'=>$this->id));
					foreach($list as $department) { $this->departments[$department->getId()] = $department; }
				}
			}
			return $this->departments;
		}
		public function setDepartments(array $department_ids)
		{
			$this->departments = array();
			foreach($department_ids as $id)
			{
				$department = new Department($id);
				$this->departments[$department->getId()] = $department;
			}
		}
		public function hasDepartment($department) { return in_array($department->getId(),array_keys($this->getDepartments())); }
		private function saveDepartments()
		{
			global $PDO;

			$sql = "delete from facetGroup_departments where facetGroup_id={$this->id}";
			if (false === $PDO->exec($sql)) { $e = $PDO->errorInfo(); throw new Exception($sql.$e[2]); }

			$query = $PDO->prepare('insert facetGroup_departments values(?,?)');
			foreach($this->getDepartments() as $department)
			{
				$query->execute(array($this->id,$department->getId()));
			}
		}

		/**
		 * Returns the number of documents associated with the facets
		 * in this facet group
		 */
		public function hasDocuments($fields=null)
		{
			$count = 0;
			foreach($this->getFacets() as $facet)
			{
				$count+= count($facet->getDocuments($fields));
			}
			return $count;
		}


		/**
		 * Generic Getters
		 */
		public function getId() { return $this->id; }
		public function getName() { return $this->name; }

		/**
		 * Generic Setters
		 */
		public function setName($string) { $this->name = trim($string); }
	}
?>