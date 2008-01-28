<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
	class Panel extends ActiveRecord
	{
		private $id;
		private $div_id;

		private $widgets = array();

		/**
		 * This will load all fields in the table as properties of this class.
		 * You may want to replace this with, or add your own extra, custom loading
		 */
		public function __construct($id=null)
		{
			if ($id)
			{
				$PDO = Database::getConnection();
				if (is_numeric($id)) { $sql = 'select * from panels where id=?'; }
				else { $sql = 'select * from panels where div_id=?'; }
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

			$fields = array();
			$fields['div_id'] = $this->div_id ? $this->div_id : null;

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

			$sql = "update panels set $preparedFields where id={$this->id}";
			if (false === $query = $PDO->prepare($sql)) { $e = $PDO->errorInfo(); throw new Exception($sql.$e[2]); }
			if (false === $query->execute($values)) { $e = $PDO->errorInfo(); throw new Exception($sql.$e[2]); }
		}

		private function insert($values,$preparedFields)
		{
			$PDO = Database::getConnection();

			$sql = "insert panels set $preparedFields";
			if (false === $query = $PDO->prepare($sql)) { $e = $PDO->errorInfo(); throw new Exception($sql.$e[2]); }
			if (false === $query->execute($values)) { $e = $PDO->errorInfo(); throw new Exception($sql.$e[2]); }
			$this->id = $PDO->lastInsertID();
		}

		public function getWidgets($document=null)
		{
			if (!count($this->widgets))
			{
				# Get all the global widgets that should be in this panel
				$list = new WidgetInstallationList();
				$list->find(array('global_panel_id'=>$this->id),'global_layout_order');
				foreach($list as $widget) { $this->widgets[] = $widget; }

				# Get any document widgets that should be in this panel
				if (isset($document))
				{
					foreach($document->getWidgets(array('panel_id'=>$this->id)) as $widget)
					{
						$this->widgets[] = $widget;
					}
				}
			}
			return $this->widgets;
		}

		public function __toString() { return $this->div_id; }

		/**
		 * Generic Getters
		 */
		public function getId() { return $this->id; }
		public function getDiv_id() { return $this->div_id; }

		/**
		 * Generic Setters
		 */
		public function setDiv_id($string) { $this->div_id = trim($string); }
	}
?>