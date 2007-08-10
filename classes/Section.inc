<?php
/**
 * @copyright Copyright (C) 2006,2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
	class Section extends ActiveRecord
	{
		private $id;
		private $name;
		private $nickname;
		private $document_id;

		private $document;

		private $childNodes;
		private $parentNodes;

		private $parents = array();
		private $children = array();
		private $ancestors = array();
		private $descendants = array();

		private $departments = array();
		private $newDepartmentIds = array();
		private $deletedDepartmentIds = array();


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
			if (!$this->name) { throw new Exception('sections/missingName'); }
			if (!count($this->getDepartments())) { throw new Exception('sections/missingDepartment'); }

			# If this is not a New Section, you must have a document_id
			if ($this->id && !$this->document_id) { throw new Exception('sections/missingHomeDocument'); }


			$fields = array();
			$fields['name'] = $this->name ? $this->name : null;
			$fields['nickname'] = $this->nickname ? $this->nickname : null;

			# If document_id is null here, it means this is a new Section
			# The new home document should be created during the Insert()
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

			$this->saveDepartments();
		}

		private function update($values,$preparedFields)
		{
			# Make sure we still have a document assigned
			if (!$this->document_id) { throw new Exception('missingHomeDocument'); }

			global $PDO;

			$sql = "update sections set $preparedFields where id={$this->id}";
			if (false === $query = $PDO->prepare($sql)) { $e = $PDO->errorInfo(); throw new Exception($sql.$e[2]); }
			if (false === $query->execute($values)) { $e = $PDO->errorInfo(); throw new Exception($sql.$e[2]); }
		}

		private function insert($values,$preparedFields)
		{
			global $PDO;

			# Have to do an Insert first, so we can have a section_id to assign to the Document
			$sql = "insert sections set $preparedFields";
			if (false === $query = $PDO->prepare($sql)) { $e = $PDO->errorInfo(); throw new Exception($sql.$e[2]); }
			if (false === $query->execute($values)) { $e = $PDO->errorInfo(); throw new Exception($sql.$e[2]); }
			$this->id = $PDO->lastInsertID();

			# New Sections need a default document created for them
			if (!$this->document_id)
			{
				$document = new Document();
				$document->setDepartment($_SESSION['USER']->getDepartment());
				$document->setTitle($this->name);
				$document->setContent("<h2>{$this->name}</h2>",$_SESSION['LANGUAGE']);
				$document->setDocumentType_id(1,$_SESSION['LANGUAGE']);
				$document->addSection($this);
				$document->save();
				$this->setDocument($document);
			}

			# Now we just need to update the document_id field
			$query = $PDO->prepare('update sections set document_id=? where id=?');
			$query->execute(array($this->getDocument_id(),$this->getId()));
		}

		public function delete()
		{
			global $PDO;

			if ($this->getDocument()) { $this->getDocument()->delete(); }

			$PDO->beginTransaction();

				$sql = "delete from document_sections where section_id={$this->id}";
				if (false === $PDO->exec($sql)) { $e = $PDO->errorInfo(); $PDO->rollBack(); throw new Exception($sql.$e[2]); }

				$sql = "delete from section_parents where section_id={$this->id} or parent_id={$this->id}";
				if (false === $PDO->exec($sql)) { $e = $PDO->errorInfo(); $PDO->rollBack(); throw new Exception($sql.$e[2]); }

				$sql = "delete from section_departments where section_id={$this->id}";
				if (false === $PDO->exec($sql)) { $e = $PDO->errorInfo(); $PDO->rollBack(); throw new Exception($sql.$e[2]); }

				$sql = "delete from section_widgets where section_id={$this->id}";
				if (false === $PDO->exec($sql)) { $e = $PDO->errorInfo(); $PDO->rollBack(); throw new Exception($sql.$e[2]); }

				$sql = "delete from event_sections where section_id={$this->id}";
				if (false === $PDO->exec($sql)) { $e = $PDO->errorInfo(); $PDO->rollBack(); throw new Exception($sql.$e[2]); }

				$sql = "delete from sectionIndex where section_id={$this->id}";
				if (false === $PDO->exec($sql)) { $e = $PDO->errorInfo(); $PDO->rollBack(); throw new Exception($sql.$e[2]); }

				$sql = "delete from sections where id={$this->id}";
				if (false === $PDO->exec($sql)) { $e = $PDO->errorInfo(); $PDO->rollBack(); throw new Exception($sql.$e[2]); }

			$PDO->commit();
		}


		public function getChildNodes()
		{
			if (!$this->childNodes) { $this->childNodes = new SectionNodeList(array('parent_id'=>$this->id)); }
			return $this->childNodes;
		}
		public function getParentNodes()
		{
			if (!$this->parentNodes) { $this->parentNodes = new SectionNodeList(array('section_id'=>$this->id)); }
			return $this->parentNodes;
		}

		public function hasChildren() { return count($this->getChildNodes()); }

		/**
		 * Returns an array of Sections with the section_id as the array index
		 */
		public function getChildren()
		{
			if (!count($this->children))
			{
				foreach($this->getChildNodes() as $child)
				{
					$this->children[$child->getSection()->getId()] = $child->getSection();
				}
			}
			return $this->children;
		}
		/**
		 * Returns an array of Sections with the section_id as the array index
		 */
   		public function getParents()
   		{
			if (!count($this->parents))
			{
				foreach($this->getParentNodes() as $parent)
				{
					$this->parents[$parent->getParent()->getId()] = $parent->getParent();
				}
			}
			return $this->parents;
   		}
		public function hasParent($section) { return array_key_exists($section->getId(),$this->getParents()); }

   		/**
   		 * Returns a Multi-demensional array of ancestors.  One vector for
   		 * each parent this section has.
   		 * This is done by looking at the sectionIndex, a Nested Set
   		 * See: http://dev.mysql.com/tech-resources/articles/hierarchical-data.html
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
   				foreach($result as $section)
   				{
					$sql ="select distinct p.section_id from sectionIndex s
							left join sectionIndex p on p.preOrder<$section[preOrder] and $section[preOrder]<p.postOrder
							and s.section_id=$section[section_id]
							where p.section_id is not null
							order by p.preOrder";
					$query = $PDO->prepare($sql);
					$query->execute();
					$result = $query->fetchAll();

					$vector = array();
					foreach($result as $row)
					{
						$vector[$row['section_id']] = new Section($row['section_id']);
					}
					$this->ancestors[] = $vector;
   				}
			}
			return $this->ancestors;
   		}

		/**
		 * A Section's descendants are the same no matter how many places the section exists in the tree
		 * So we only get a single dimensional array with the list of descendants, nearest first
		 * This is using a Nested Set as the sectionIndex
		 * See: http://dev.mysql.com/tech-resources/articles/hierarchical-data.html
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
   				# We can only look up departments from the database once we have a section_id
   				if ($this->id)
   				{
		   			$list = new DepartmentList(array('section_id'=>$this->id));
		   			foreach($list as $department) { $this->departments[$department->getId()] = $department; }
		   		}
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
			if (!count($this->documents)) { $this->documents = new DocumentList(array('section_id'=>$this->id,'active'=>date('Y-m-d'))); }
			return $this->documents;
   		}
   		public function getDocumentLinks() { return new DocumentLinkList(array('section_id'=>$this->id)); }


		/**
		 * Widget functions
		 */
		public function getWidgets()
		{
			if (!count($this->widgets))
			{
				$list = new SectionWidgetList(array('section_id'=>$this->id));
				foreach($list as $widget) { $this->widgets[$widget->getWidget_id()] = $widget; }
			}
			return $this->widgets;
		}
		public function hasWidget($widget) { return array_key_exists($widget->getId(),$this->getWidgets()); }



		private function quote($string) { return "'$string'"; }
		public function permitsPostingBy($user)
		{
			if ($user->hasRole(array('Administrator','Webmaster','Publisher'))) { return true; }
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
		public function getNickname() { return $this->nickname; }
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
		public function setNickname($string) { $this->nickname = trim($string); }
		public function setDocument_id($int) { $this->document = new Document($int); $this->document_id = $int; }
		public function setDocument($document) { $this->document_id = $document->getId(); $this->document = $document; }
	}
?>