<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
	class WidgetInstallation extends ActiveRecord
	{
		private $id;
		private $class;
		private $global_panel_id;
		private $global_layout_order;
		private $global_data;
		private $default_panel_id;
		private $default_layout_order;
		private $default_data;

		private $global_panel;
		private $default_panel;
		private $widget;

		private $sections;


		/**
		 * This will load all fields in the table as properties of this class.
		 * You may want to replace this with, or add your own extra, custom loading
		 */
		public function __construct($id)
		{
			$PDO = Database::getConnection();

			if (is_numeric($id)) { $sql = 'select * from widgets where id=?'; }
			else { $sql = 'select * from widgets where class=?'; }
			$query = $PDO->prepare($sql);
			$query->execute(array($id));

			$result = $query->fetchAll();
			if (count($result))
			{
				foreach($result[0] as $field=>$value) { if ($value) $this->$field = $value; }
			}
			else
			{
				# This is where the code goes to generate a new, empty instance.
				# Set any default values for properties that need it here
				if (!is_numeric($id)) { $this->class = $id; }
			}
		}


		/**
		 * This generates generic SQL that should work right away.
		 * You can replace this $fields code with your own custom SQL
		 * for each property of this class,
		 */
		public function save()
		{
			# Before you can have a layout order, you must say which panel the widget is going on
			if (!$this->global_panel_id) { $this->global_layout_order = null; }
			if (!$this->default_panel_id) { $this->default_layout_order = null; }

			# Check for required fields here.  Throw an exception if anything is missing.

			$fields = array();
			$fields['class'] = $this->class ? $this->class : null;
			$fields['global_panel_id'] = $this->global_panel_id ? $this->global_panel_id : null;
			$fields['global_layout_order'] = $this->global_layout_order ? $this->global_layout_order : null;
			$fields['global_data'] = $this->global_data ? $this->global_data : null;
			$fields['default_panel_id'] = $this->default_panel_id ? $this->default_panel_id : null;
			$fields['default_layout_order'] = $this->default_layout_order ? $this->default_layout_order : null;
			$fields['default_data'] = $this->default_data ? $this->default_data : null;

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

			$sql = "update widgets set $preparedFields where id={$this->id}";
			if (false === $query = $PDO->prepare($sql)) { $e = $PDO->errorInfo(); throw new Exception($sql.$e[2]); }
			if (false === $query->execute($values)) { $e = $PDO->errorInfo(); throw new Exception($sql.$e[2]); }
		}

		private function insert($values,$preparedFields)
		{
			$PDO = Database::getConnection();

			$sql = "insert widgets set $preparedFields";
			if (false === $query = $PDO->prepare($sql)) { $e = $PDO->errorInfo(); throw new Exception($sql.$e[2]); }
			if (false === $query->execute($values)) { $e = $PDO->errorInfo(); throw new Exception($sql.$e[2]); }
			$this->id = $PDO->lastInsertID();
		}

		public function delete()
		{
			$PDO = Database::getConnection();

			if ($this->id)
			{
				$sql = 'delete from section_widgets where widget_id=?';
				if (false === $query = $PDO->prepare($sql)) { $e = $PDO->errorInfo(); throw new Exception($sql.$e[2]); }
				if (false === $query->execute(array($this->id))) { $e = $PDO->errorInfo(); throw new Exception($sql.$e[2]); }

				$sql = 'delete from widgets where id=?';
				if (false === $query = $PDO->prepare($sql)) { $e = $PDO->errorInfo(); throw new Exception($sql.$e[2]); }
				if (false === $query->execute(array($this->id))) { $e = $PDO->errorInfo(); throw new Exception($sql.$e[2]); }
			}
		}

		public function isGlobal() { return $this->global_panel_id ? true : false; }
		public function isDefault() { return $this->default_panel_id ? true : false; }

		public function getSections()
		{
			if (!$this->sections) { $this->sections = new SectionWidgetList(array('widget_id'=>$this->id)); }
			return $this->sections;
		}


		/**
		 * Aliases for the Widget class functions
		 */
		public function getWidget()
		{
			if (!$this->widget)
			{
				$this->widget = Widget::load($this->class);
				if ($this->isGlobal() && $this->global_data) { $this->widget->setData($this->global_data); }
			}
			return $this->widget;
		}
		public function getStatus() { return $this->id ? 'installed' : 'uninstalled'; }
		public function getInstallation() { return $this; }
		public function getDisplayName() { return $this->getWidget()->getDisplayName(); }
		public function getName() { return $this->getWidget()->getName(); }
		public function getIncludeFile() { return $this->getWidget()->getIncludeFile(); }
		public function getDescription() { return $this->getWidget()->getDescription(); }

		public function render($template) { $this->getWidget()->render($template); }

		public function __toString() { return $this->getWidget()->getName(); }

		/**
		 * Generic Getters
		 */
		public function getId() { return $this->id; }
		public function getClass() { return $this->class; }
		public function getGlobal_panel_id() { return $this->global_panel_id; }
		public function getGlobal_layout_order() { return $this->global_layout_order; }
		public function getGlobal_data() { return $this->global_data; }
		public function getDefault_panel_id() { return $this->default_panel_id; }
		public function getDefault_layout_order() { return $this->default_layout_order; }
		public function getDefault_data() { return $this->default_data; }

		public function getGlobal_panel()
		{
			if ($this->global_panel_id)
			{
				if (!$this->global_panel) { $this->global_panel = new Global_panel($this->global_panel_id); }
				return $this->global_panel;
			}
			else return null;
		}

		public function getDefault_panel()
		{
			if ($this->default_panel_id)
			{
				if (!$this->default_panel) { $this->default_panel = new Default_panel($this->default_panel_id); }
				return $this->default_panel;
			}
			else return null;
		}

		/**
		 * Generic Setters
		 */
		public function setClass($string) { $this->class = trim($string); }
		public function setGlobal_panel_id($int) { $this->global_panel = new Panel($int); $this->global_panel_id = $int; }
		public function setGlobal_layout_order($int) { $this->global_layout_order = preg_replace('/[^0-9]/','',$int); }
		public function setGlobal_data($string) { $this->global_data = trim($string); }
		public function setDefault_panel_id($int) { $this->default_panel = new Panel($int); $this->default_panel_id = $int; }
		public function setDefault_layout_order($int) { $this->default_layout_order = preg_replace('/[^0-9]/','',$int); }
		public function setDefault_data($string) { $this->default_data = trim($string); }

		public function setGlobal_panel($panel) { $this->global_panel_id = $panel->getId(); $this->global_panel = $panel; }
		public function setDefault_panel($panel) { $this->default_panel_id = $panel->getId(); $this->default_panel = $panel; }
	}
?>