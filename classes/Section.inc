<?php
/**
 * @copyright Copyright (C) 2006 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 */
	class Section extends ActiveRecord
	{
		private $id;
		private $name;
		private $department_id;
		private $document_id;

		private $department;
		private $document;

		private $parents;
		private $ancestors = array();
		private $documents;
		private $widgets = array();


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
			if (!$this->name || !$this->department_id) { throw new Exception("missingRequiredFields"); }

			# New Sections need a default document created for them
			if (!$this->document_id)
			{
				$document = new Document();
				$document->setDepartment($this->getDepartment());
				$document->setTitle($this->name);
				$document->setContent("<h2>{$this->name}</h2>");
				$document->save();
				$this->setDocument($document);
			}

			$fields = array();
			$fields['name'] = $this->name ? $this->name : null;
			$fields['department_id'] = $this->department_id ? $this->department_id : null;
			$fields['document_id'] = $this->document_id ? $this->document_id : null;

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

			$this->updateParents();
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


		private function updateParents()
		{
			global $PDO;

			$parents = $this->getParents();
			if (!count($parents)) { $parents[] = new Section(1); }


			$sql = "delete from section_parents where section_id={$this->id}";
			if (false === $PDO->exec($sql)) { $e = $PDO->errorInfo(); throw new Exception($sql.$e[2]); }

			$statement = $PDO->prepare("insert section_parents set section_id={$this->id},parent_id=?");
			foreach($parents as $parent)
			{
				if (false === $statement->execute(array($parent->getId()))) { $e = $PDO->errorInfo(); throw new Exception($sql.$e[2]); }
			}

			$sql = "delete from sectionIndex";
			if (false === $PDO->exec($sql)) { $e = $PDO->errorInfo(); throw new Exception($sql.$e[2]); }

			$this->createPrePostOrder(1,1);
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
		/**
		 * Find out if a given section is a parent of this section
		 */
		public function hasParent($section)
		{
			$parents = $this->getParents();
			foreach($parents as $parent) { if ($section->getId() == $parent->getId()) { return true; } }
			return false;
		}

		public function __toString() { return $this->name; }

		public function getId() { return $this->id; }
		public function getName() { return $this->name; }
		public function getChildren() { return new SectionList(array('parent_id'=>$this->id)); }
		public function getDepartment_id() { return $this->department_id; }
		public function getDocument_id() { return $this->document_id; }
		public function getDepartment()
		{
			if ($this->department_id)
			{
				if (!$this->department) { $this->department = new Department($this->department_id); }
				return $this->department;
			}
			else return null;
		}
		public function getDocument()
		{
			if ($this->document_id)
			{
				if (!$this->document) { $this->document = new Document($this->document_id); }
				return $this->document;
			}
			else return null;
		}
   		public function getParents()
   		{
			global $PDO;

			if (!$this->parents)
			{
				$this->parents = array();
				$query = $PDO->prepare("select parent_id from section_parents where section_id=?");
				$query->execute(array($this->id));
				$result = $query->fetchAll();
				foreach($result as $row) { $this->parents[] = new Section($row['parent_id']); }
			}
			return $this->parents;
   		}
   		/**
   		 * Returns a Multi-demensional array of ancestors.  One vector for
   		 * each parent this section has.
   		 */
   		public function getAncestors()
   		{
   			global $PDO;
   			if (!count($this->ancestors))
   			{
   				$this->ancestors = array();
   				$query = $PDO->prepare("select * from sectionIndex where section_id=?");
   				$query->execute(array($this->id));
   				$result = $query->fetchAll();
   				foreach($result as $index=>$section)
   				{
   					$ancestors = array();
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

   		public function getDocuments()
   		{
			if (!count($this->documents)) { $this->documents = new DocumentList(array('section_id'=>$this->id)); }
			return $this->documents;
   		}
   		public function getWidgets()
   		{
   			global $PDO;

   			if (!count($this->widgets))
   			{
				$this->widgets = array();

				$sql = "select * from section_widgets where section_id={$this->id} order by layout_order";
				foreach($PDO->query($sql) as $row) { $this->widgets[$row['layout_order']] = Widget::load($row['widget_name']); }
			}
			return $this->widgets;
   		}
   		public function hasWidget($name)
   		{
			foreach($this->getWidgets() as $widget) { if ($widget->getName() == $name) { return true; } }
			return false;
   		}
   		public function addWidget($widget)
   		{
			if (!$this->hasWidget($widget->getName())) { $this->widgets[] = $widget; }
   		}
   		public function saveWidgets()
   		{
   			global $PDO;
			$query = $PDO->prepare("delete from section_widgets where section_id={$this->id}");
			$query->execute();

			$query = $PDO->prepare("insert section_widgets values($this->id,?,?)");
			foreach($this->getWidgets() as $key=>$widget)
			{
				$query->execute(array($widget->getName,$key));
			}
   		}


		public function setName($string) { $this->name = trim($string); }
		public function setDepartment_id($int) { $this->department = new Department($int); $this->department_id = $int; }
		public function setDocument_id($int) { $this->document = new Document($int); $this->document_id = $int; }

		public function setDepartment($department) { $this->department_id = $department->getId(); $this->department = $department; }
		public function setDocument($document) { $this->document_id = $document->getId(); $this->document = $document; }
		/**
		 * Takes an array of parent_id's to be associated with this section
		 * A Section cannot have itself for a parent
		 */
		public function setParents(array $array)
		{
			$this->parents = array();
			foreach($array as $id) { if ($id != $this->id) { $this->parents[] = new Section($id); } }
		}
	}
?>