<?php
/**
 * @copyright Copyright (C) 2006 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 */
/**
 * A container class for transferring section_parents data
 * This should work as sections, so we can iterate over an array
 * of these as Sections.  This class should be ready-only
 */
	class SectionNode extends Section
	{
		private $node_id;
		private $section_id;
		private $parent_id;
		private $placement;

		public function __construct($node_id)
		{
			global $PDO;

			$query = $PDO->prepare("select * from section_parents where node_id=?");
			$query->execute(array($node_id));
			$result = $query->fetchAll();
			foreach($result[0] as $field=>$value) { if ($value) $this->$field = $value; }

			parent::__construct($this->section_id);
		}

		public function getNode_id() { return $this->node_id; }
		public function getSection_id() { return $this->section_id; }
		public function getParent_id() { return $this->parent_id; }
		public function getPlacement() { return $this->placement; }
	}
?>