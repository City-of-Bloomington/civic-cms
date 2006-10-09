<?php
/**
 * @copyright Copyright (C) 2006 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 */
	class Category extends ActiveRecord
	{
		private $id;
		private $name;

		private $parents;



		/**
		 * This will load all fields in the table as properties of this class.
		 * You may want to replace this with, or add your own extra, custom loading
		 */
		public function __construct($id=null)
		{
			global $PDO;

			if ($id)
			{
				$sql = "select * from categories where id=$id";
				$result = $PDO->query($sql);
				if ($result)
				{
					if ($row = $result->fetch())
					{
						# You may want to replace this line to do your own custom loading
						foreach($row as $field=>$value) { if ($value) $this->$field = $value; }

						$result->closeCursor();
					}
					else { throw new Exception($sql); }
				}
				else { $e = $PDO->errorInfo(); throw new Exception($sql.$e[2]); }
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
			$fields[] = $this->name ? "name='{$this->name}'" : "name=null";

			$fields = implode(",",$fields);


			if ($this->id) { $this->update($fields); }
			else { $this->insert($fields); }

			$this->updateParents();
		}

		private function update($fields)
		{
			global $PDO;

			$sql = "update categories set $fields where id={$this->id}";
			if (false === $PDO->exec($sql)) { $e = $PDO->errorInfo(); throw new Exception($sql.$e[2]); }
		}

		private function insert($fields)
		{
			global $PDO;

			$sql = "insert categories set $fields";
			if (false === $PDO->exec($sql)) { $e = $PDO->errorInfo(); throw new Exception($sql.$e[2]); }
			$this->id = $PDO->lastInsertID();
		}

		private function updateParents()
		{
			global $PDO;

			$parents = $this->getParents();
			if (!count($parents)) { $parents[] = new Category(1); }


			$sql = "delete from category_parents where category_id={$this->id}";
			if (false === $PDO->exec($sql)) { $e = $PDO->errorInfo(); throw new Exception($sql.$e[2]); }

			$statement = $PDO->prepare("insert category_parents set category_id={$this->id},parent_id=?");
			foreach($parents as $parent)
			{
				if (false === $statement->execute(array($parent->getId()))) { $e = $PDO->errorInfo(); throw new Exception($sql.$e[2]); }
			}

			$sql = "delete from categoryIndex";
			if (false === $PDO->exec($sql)) { $e = $PDO->errorInfo(); throw new Exception($sql.$e[2]); }

			$this->createPrePostOrder(1,1);
		}

		private function createPrePostOrder($category_id,$pre)
		{
			global $PDO;

			$post = $pre + 1;

			$children = array();
			$sql = "select category_id from category_parents where parent_id=$category_id";
			foreach($PDO->query($sql) as $row) { $children[] = $row['category_id']; }
			foreach($children as $id) { $post = $this->createPrePostOrder($id,$post); }

			$sql = "insert categoryIndex values($category_id,$pre,$post)";
			if (false === $PDO->exec($sql)) { $e = $PDO->errorInfo(); throw new Exception($sql.$e[2]); }

			return $post++;
		}

		/**
		 * Returns the number of children for this category
		 * Useful if you just want to know if we have children, or
		 * if you want to know how many children there are
		 */
		public function hasChildren()
		{
			global $PDO;

			$sql = "select count(*) from category_parents where parent_id={$this->id}";
			$result = $PDO->query($sql);
			list($count) = $result->fetch();
			$result->closeCursor();
			return $count;
		}
		/**
		 * Find out if a given category is a parent of this category
		 */
		public function hasParent($category)
		{
			foreach($this->getParents() as $parent) { if ($category->getId() == $parent->getId()) { return true; } }
			return false;
		}

		public function __toString() { return $this->name; }

		public function getId() { return $this->id; }
		public function getName() { return $this->name; }
		public function getChildren() { return new CategoryList(array('parent_id'=>$this->id)); }
   		public function getParents()
   		{
			global $PDO;

			if (!$this->parents)
			{
				$this->parents = array();
				$sql = "select parent_id from category_parents where category_id={$this->id}";
				$query = $PDO->prepare($sql);
				$query->execute();
				$result = $query->fetchAll();
				foreach($result as $row) { $this->parents[] = new Category($row['parent_id']); }
			}
			return $this->parents;
   		}


		public function setName($string) { $this->name = trim($string); }
		/**
		 * Takes an array of parent_id's to be associated with this category
		 * A Category cannot have itself for a parent
		 */
		public function setParents(array $array)
		{
			$this->parents = array();
			foreach($array as $id) { if ($id != $this->id) { $this->parents[] = new Category($id); } }
		}
	}
?>