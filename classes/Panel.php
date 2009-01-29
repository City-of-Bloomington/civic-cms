<?php
/**
 * @copyright Copyright (C) 2007-2008 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
class Panel extends ActiveRecord
{
	private $id;
	private $name;

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
			if (ctype_digit($id)) { $sql = 'select * from panels where id=?'; }
			else { $sql = 'select * from panels where name=?'; }

			$query = $PDO->prepare($sql);
			$query->execute(array($id));

			$result = $query->fetchAll();
			if (!count($result)) { throw new Exception('panels/unknownPanel'); }
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
		if (!$this->name) { throw new Exception('missingRequiredFields'); }

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
	}

	private function update($values,$preparedFields)
	{
		$PDO = Database::getConnection();

		$sql = "update panels set $preparedFields where id={$this->id}";
		$query = $PDO->prepare($sql);
		$query->execute($values);
	}

	private function insert($values,$preparedFields)
	{
		$PDO = Database::getConnection();

		$sql = "insert panels set $preparedFields";
		$query = $PDO->prepare($sql);
		$query->execute($values);
		$this->id = $PDO->lastInsertID();
	}


	public function __toString() { return $this->name; }

	#----------------------------------------------------------------
	# Generic Getters
	#----------------------------------------------------------------
	public function getId() { return $this->id; }
	public function getName() { return $this->name; }

	#----------------------------------------------------------------
	# Generic Setters
	#----------------------------------------------------------------
	public function setName($string) { $this->name = trim($string); }

	#----------------------------------------------------------------
	# Custom Functions
	#----------------------------------------------------------------
	/**
	 * Returns an array of widgets.  The widgets should include both
	 * global and document widgets.  We should merge the two lists
	 * so layout_orders should apply across the full set
	 * @param Document $document
	 * @return array
	 */
	public function getWidgets($document=null)
	{
		$widgets = array();
		if (!count($this->widgets))
		{
			# Get all the global widgets that should be in this panel
			$list = new WidgetInstallationList();
			$list->find(array('global_panel_id'=>$this->id),'global_layout_order');
			foreach($list as $widget)
			{
				$order = $widget->getGlobal_layout_order() ? $widget->getGlobal_layout_order() : 0;
				$widgets[$order][] = $widget;
			}

			# Get any document widgets that should be in this panel
			if (isset($document))
			{
				foreach($document->getWidgets(array('panel_id'=>$this->id)) as $widget)
				{
					$order = $widget->getLayout_order() ? $widget->getLayout_order() : 0;
					$widgets[$order][] = $widget;
				}
			}
		}
		ksort($widgets);
		foreach($widgets as $order=>$list)
		{
			foreach($list as $widget) { $this->widgets[] = $widget; }
		}
		return $this->widgets;
	}

}
