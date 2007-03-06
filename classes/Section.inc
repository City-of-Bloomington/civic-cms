<?php
/**
 * @copyright Copyright (C) 2006 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 */
	class Section extends ActiveRecord
	{
		private $id;
		private $name;
		private $document_id;

		private $document;

		private $departments = array();
		private $newDepartmentIds = array();
		private $deletedDepartmentIds = array();

		private $parents = array();
		private $newParentIds = array();
		private $deletedParentIds = array();

		private $children = array();
		private $ancestors = array();
		private $descendants = array();
		private $documents;

		private $widgets = array();
		private $newWidgets = array();
		private $deletedWidgets = array();


		/**
		 * This will load all fields in the table as properties of this class.
		 * You may want to replace this with, or add your own extra, custom loading
		 */
		public function __construct($id=null)
		{
			global $PDO;

			if ($id)
			{
				$sql = "select * from sections where id=?";
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
			if (!$this->name) { throw new Exception("missingRequiredFields"); }

			# Sections must have a parent.  Even if they haven't chosen a parent, make it
			# a child of HOME
			if (!count($this->getParents())) { $this->setParents(array(1)); }

			# New Sections need a default document created for them
			if (!$this->document_id)
			{
				$document = new Document();
				$document->setDepartment($_SESSION['USER']->getDepartment());
				$document->setTitle($this->name);
				$document->setContent("<h2>{$this->name}</h2>",$_SESSION['LANGUAGE']);
				$document->setDocumentType_id(1);
				$document->save();
				$this->setDocument($document);
			}

			$fields = array();
			$fields['name'] = $this->name ? $this->name : null;
			$fields['document_id'] = $this->document_id ? $this->document_id : null;
			#$fields['placement'] = $this->placement ? $this->placement : null;

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

			$this->saveParents();
			$this->saveDepartments();
			$this->saveWidgets();
		}

		private function update($values,$preparedFields)
		{
			# Make sure we still have a document assigned
			if (!$this->document_id) { throw new Exception("missingRequiredFields"); }

			global $PDO;

			$sql = "update sections set $preparedFields where id={$this->id}";
			if (false === $query = $PDO->prepare($sql)) { $e = $PDO->errorInfo(); throw new Exception($sql.$e[2]); }
			if (false === $query->execute($values)) { $e = $PDO->errorInfo(); throw new Exception($sql.$e[2]); }
		}

		private function insert($values,$preparedFields)
		{
			global $PDO;

			$sql = "insert sections set $preparedFields";
			if (false === $query = $PDO->prepare($sql)) { $e = $PDO->errorInfo(); throw new Exception($sql.$e[2]); }
			if (false === $query->execute($values)) { $e = $PDO->errorInfo(); throw new Exception($sql.$e[2]); }
			$this->id = $PDO->lastInsertID();

			$this->document->addSection($this);
			$this->document->save();
		}



		private function createPrePostOrder($section_id,$pre)
		{
			global $PDO;

			$post = $pre + 1;

			$children = array();
			$sql = "select section_id from section_parents where parent_id=$section_id";
			foreach($PDO->query($sql) as $row) { $children[] = $row['section_id']; }
			foreach($children as $id) { $post = $this->createPrePostOrder($id,$post); }

			$sql = "insert sectionIndex values($section_id,$pre,$post)";
			if (false === $PDO->exec($sql)) { $e = $PDO->errorInfo(); throw new Exception($sql.$e[2]); }

			return $post++;
		}

		/**
		 * Returns the number of children for this section
		 * Useful if you just want to know if we have children, or
		 * if you want to know how many children there are
		 */
		public function hasChildren()
		{
			global $PDO;

			$query = $PDO->prepare("select count(*) as count from section_parents where parent_id=?");
			$query->execute(array($this->id));
			$result = $query->fetchAll();
			return $result[0]['count'];
		}
		public function getChildren()
		{
			global $PDO;
			if (!count($this->children))
			{
				$query = $PDO->prepare("select node_id from section_parents where parent_id={$this->id} order by isnull(placement),placement");
				$query->execute();
				$result = $query->fetchAll();

				foreach($result as $row) { $this->children[] = new SectionNode($row['node_id']); }
			}
			return $this->children;
		}
		/**
		 * Section Parent functions
		 */
   		public function getParents()
   		{
			global $PDO;

			if (!count($this->parents))
			{
				$query = $PDO->prepare("select parent_id from section_parents where section_id=?");
				$query->execute(array($this->id));
				$result = $query->fetchAll();
				foreach($result as $row) { $this->parents[$row['parent_id']] = new Section($row['parent_id']); }
			}
			return $this->parents;
   		}
		private function saveParents()
		{
			global $PDO;

			# Clear out all the old parents
			if (count($this->deletedParentIds))
			{
				$ids = implode(',',$this->deletedParentIds);
				$query = $PDO->prepare("delete from section_parents where section_id={$this->id} and parent_id in ($ids)");
				$query->execute();
			}

			# Add in all the new parents
			if (count($this->newParentIds))
			{
				$query = $PDO->prepare("insert section_parents set section_id={$this->id},parent_id=?");
				foreach($this->newParentIds as $id) { $query->execute(array($id)); }
			}

			# Update the index
			$sql = "delete from sectionIndex";
			if (false === $PDO->exec($sql)) { $e = $PDO->errorInfo(); throw new Exception($sql.$e[2]); }

			$this->createPrePostOrder(1,1);
		}
		public function setParents(array $parentIds)
		{
			# Any $parentIds that are not in $this->parents need to be added
			$this->newParentIds = array_diff($parentIds,array_keys($this->getParents()));
			foreach($this->newParentIds as $id) { $this->parents[$id] = new Section($id); }

			# Unset any $this->parents that are not in $parentIds
			$this->deletedParentIds = array_diff(array_keys($this->parents),$parentIds);
			foreach($this->deletedParentIds as $id) { unset($this->parents[$id]); }
		}
		public function hasParent($section) { return array_key_exists($section->getId(),$this->getParents()); }
   		/**
   		 * Returns a Multi-demensional array of ancestors.  One vector for
   		 * each parent this section has.
   		 */
   		public function getAncestors()
   		{
   			global $PDO;
   			if (!count($this->ancestors))
   			{
   				# Since a section can be in multiple places in the tree
   				# We have to do the SQL query for each place this section is in the tree
   				$this->ancestors = array();
   				$query = $PDO->prepare("select * from sectionIndex where section_id=?");
   				$query->execute(array($this->id));
   				$result = $query->fetchAll();
   				foreach($result as $index=>$section)
   				{
					$sql ="select distinct p.section_id from sectionIndex s
							left join sectionIndex p on p.preOrder<$section[preOrder] and $section[preOrder]<p.postOrder
							and s.section_id=$section[section_id]
							where p.section_id is not null
							order by p.preOrder";
					$query = $PDO->prepare($sql);
					$query->execute();
					$result = $query->fetchAll();
					foreach($result as $row) { $this->ancestors[$index][] = new Section($row['section_id']); }
   				}
			}
			return $this->ancestors;
   		}

		/**
		 * A Section's descendants are the same no matter how many places the section exists in the tree
		 * So we only get a single dimensional array with the list of descendants, nearest first
		 */
		public function getDescendants()
   		{
   			global $PDO;

   			if (!count($this->descendants))
   			{
   				$sql = "select distinct s.section_id from sectionIndex s
						left join sectionIndex p on p.preOrder<s.preOrder and s.preOrder<p.postOrder
						where p.section_id={$this->id} order by s.preOrder";
				$query = $PDO->query($sql);
				$result = $query->fetchAll();
				foreach($result as $row) { $this->descendants[$row['section_id']] = new Section($row['section_id']); }
   			}
   			return $this->descendants;
   		}


   		/**
   		 * Department Functions
   		 */
   		public function getDepartments()
   		{
   			if (!count($this->departments))
   			{
		   		$list = new DepartmentList(array('section_id'=>$this->id));
		   		foreach($list as $department) { $this->departments[$department->getId()] = $department; }
   			}
   			return $this->departments;
   		}
   		private function saveDepartments()
   		{
   			global $PDO;
			# Clear out all the old departments
			if (count($this->deletedDepartmentIds))
			{
				$ids = implode(",",$this->deletedDepartmentIds);
				$query = $PDO->prepare("delete from section_departments where section_id={$this->id} and department_id in ($ids)");
				$query->execute();
			}

			# Add in the new ones
			if (count($this->newDepartmentIds))
			{
				$query = $PDO->prepare("insert section_departments set section_id={$this->id},department_id=?");
				foreach($this->newDepartmentIds as $id) { $query->execute(array($id)); }
			}
   		}
		public function setDepartments(array $departmentIds)
		{
			# Make sure to call $this->getDepartments() at least once to ensure that
			# the current departments are loaded before trying to determine which ones are new

			# Any $departmentIds that are not in $this->departments need to be added
			$this->newDepartmentIds = array_diff($departmentIds,array_keys($this->getDepartments()));
			foreach($this->newDepartmentIds as $id) { $this->departments[$id] = new Department($id); }

			# Unset any $this->departments that are not in $departmentIds
			$this->deletedDepartmentIds = array_diff(array_keys($this->departments),$departmentIds);
			foreach($this->deletedDepartmentIds as $id) { unset($this->departments[$id]); }
		}
		public function hasDepartment($department) { return array_key_exists($department->getId(),$this->getDepartments()); }

   		public function getDocuments()
   		{
			if (!count($this->documents)) { $this->documents = new DocumentList(array('section_id'=>$this->id)); }
			return $this->documents;
   		}

		/**
		 * Widget functions
		 */
		public function getWidgets()
		{
			global $PDO;

			if (!count($this->widgets))
			{
				$sql = "select widget_name from section_widgets where section_id={$this->id}";
				foreach($PDO->query($sql) as $row) { $this->widgets[] = $row['widget_name']; }
			}
			return $this->widgets;
		}
		private function quote($string) { return "'$string'"; }
		private function saveWidgets()
		{
			global $PDO;

			# Clear out all the old widgets
			if (count($this->deletedWidgets))
			{
				$names = implode(',',array_map(array($this,'quote'),$this->deletedWidgets));
				$query = $PDO->prepare("delete from section_widgets where section_id={$this->id} and widget_name in ($names)");
				$query->execute();
			}

			# Add in the new ones
			if (count($this->newWidgets))
			{
				$query = $PDO->prepare("insert section_widgets set section_id={$this->id},widget_name=?");
				foreach($this->newWidgets as $name) { $query->execute(array($name)); }
			}
		}
		public function setWidgets(array $widgets)
		{
			# Make sure to call $this->getWidgets() at least once to ensure that
			# the current widgets are loaded before trying to determine which ones are new

			# Any $widgets that are not in $this->widgets need to be added
			$this->newWidgets = array_diff($widgets,$this->getWidgets());

			# Flag any $this->widgets that are not in $widgets to be deleted
			$this->deletedWidgets = array_diff($this->widgets,$widgets);

			$this->widgets = $widgets;
		}
		public function hasWidget($widget) { return in_array($widget,$this->getWidgets()); }
		public function permitsPostingBy($user)
		{
			if ($user->hasRole(array('Administrator','Webmaster'))) { return true; }
			if ($user->hasRole('Content Creator') && $user->getDepartment_id()==$this->department_id) { return true; }
			return false;
		}
   		public function permitsEditingBy($user)
   		{
   			if ($user->hasRole('Webmaster')) { return true; }
			return false;
   		}


		public function __toString() { return $this->name; }

		/**
		 * Generic Getters
		 */
		public function getId() { return $this->id; }
		public function getName() { return $this->name; }
		public function getDocument_id() { return $this->document_id; }
		public function getDocument()
		{
			if ($this->document_id)
			{
				if (!$this->document) { $this->document = new Document($this->document_id); }
				return $this->document;
			}
			else return null;
		}

		/**
		 * Generic Setters
		 */
		public function setName($string) { $this->name = trim($string); }
		public function setDocument_id($int) { $this->document = new Document($int); $this->document_id = $int; }
		public function setDocument($document) { $this->document_id = $document->getId(); $this->document = $document; }
	}
?>