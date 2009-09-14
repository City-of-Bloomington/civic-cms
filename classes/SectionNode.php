<?php
/**
 * @copyright Copyright (C) 2007-2008 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 *
 * Represents a node in the layout of the site.  Sections can be in multiple places
 * in the site.  So what we have is really a Directed Graph.
 * We are using the Nested Set algorithm for storing the nodes in the database.
 * See: http://dev.mysql.com/tech-resources/articles/hierarchical-data.html
 *
 * Anytime you create a new section/parent pair, you have to regenerate the index
 * So, for this class, the only thing that should be updated is the placement.
 */
class SectionNode extends ActiveRecord
{
	private $id;
	private $section_id;
	private $parent_id;
	private $placement; # The order of this node in relation to it's siblings

	private $section;
	private $parent;

	/**
	 * This will load all fields in the table as properties of this class.
	 * You may want to replace this with, or add your own extra, custom loading
	 */
	public function __construct($id=null)
	{
		if ($id)
		{
			$PDO = Database::getConnection();
			$sql = 'select * from section_parents where id=?';

			$query = $PDO->prepare($sql);
			$query->execute(array($id));

			$result = $query->fetchAll();
			if (!count($result)) { throw new Exception('sections/unknownSectionNode'); }
			foreach($result[0] as $field=>$value) { if ($value) $this->$field = $value; }
		}
		else
		{
			# This is where the code goes to generate a new, empty instance.
			# Set any default values for properties that need it here
		}
	}


	public function save()
	{
		# Check for required fields here.  Throw an exception if anything is missing.
		if (!$this->section_id || !$this->parent_id) { throw new Exception('missingRequiredFields'); }

		# If we don't have a placement yet, calculate one
		if (!$this->placement)
		{
			$PDO = Database::getConnection();
			$query = $PDO->prepare('select ifnull(max(placement)+1,1) as placement from section_parents where parent_id=?');
			$query->execute(array($this->parent_id));
			$result = $query->fetchAll();
			$this->placement = $result[0]['placement'];
		}

		if ($this->id) { $this->update(); }
		else { $this->insert(); }
	}

	private function update()
	{
		$PDO = Database::getConnection();

		$sql = "update section_parents set placement=? where id={$this->id}";
		$query = $PDO->prepare($sql);
		$query->execute(array($this->placement));
	}

	private function insert()
	{
		$PDO = Database::getConnection();

		$sql = 'insert section_parents set section_id=?,parent_id=?,placement=?';
		$query = $PDO->prepare($sql);
		$query->execute(array($this->section_id,$this->parent_id,$this->placement));
		$this->id = $PDO->lastInsertID();

		self::updateSectionIndex();
	}
	public function delete()
	{
		$PDO = Database::getConnection();

		$query = $PDO->prepare('delete from section_parents where id=?');
		$query->execute(array($this->id));

		self::updateSectionIndex();
	}

	public function moveUp()
	{
		# To move a Node up, we need to swap it's placement with the Node above
		if ($this->placement != 1)
		{
			$PDO = Database::getConnection();
			# Find the node above this one
			$query = $PDO->prepare('select id from section_parents where parent_id=? and placement<? order by placement desc limit 1');
			$query->execute(array($this->parent_id,$this->placement));
			$result = $query->fetchAll();

			$node = new SectionNode($result[0]['id']);

			$p = $node->placement;
			$node->placement = $this->placement;
			$this->placement = $p;

			$node->save();
			$this->save();
		}
	}

	public function moveDown()
	{
		# To move a Node down, we need to swap it's placement with the Node below
		if ($this->placement != 1)
		{
			$PDO = Database::getConnection();
			# Find the node above this one
			$query = $PDO->prepare('select id from section_parents where parent_id=? and placement>? order by placement limit 1');
			$query->execute(array($this->parent_id,$this->placement));
			$result = $query->fetchAll();

			$node = new SectionNode($result[0]['id']);

			$p = $node->placement;
			$node->placement = $this->placement;
			$this->placement = $p;

			$node->save();
			$this->save();
		}
	}

	/**
	 * We're using a seperate table to as an index to the tree, according to the
	 * Nested Set algorithm:
	 * See: http://dev.mysql.com/tech-resources/articles/hierarchical-data.html
	 * Whenever you insert or remove a node, you must update the index
	 */
	public static function updateSectionIndex()
	{
		$PDO = Database::getConnection();
		# Update the index
		$query = $PDO->prepare('delete from sectionIndex');
		$query->execute();

		self::createPrePostOrder(1,1);
	}
	private static function createPrePostOrder($section_id,$pre)
	{
		$PDO = Database::getConnection();

		$post = $pre + 1;

		$children = array();
		$query = $PDO->prepare('select section_id from section_parents where parent_id=?');
		$query->execute(array($section_id));
		$result = $query->fetchAll(PDO::FETCH_ASSOC);
		foreach($result as $row) { $children[] = $row['section_id']; }
		foreach($children as $id) { $post = self::createPrePostOrder($id,$post); }

		$query = $PDO->prepare('insert sectionIndex values(?,?,?)');
		$query->execute(array($section_id,$pre,$post));

		return $post++;
	}

	/**
	 * Generic Getters
	 */
	public function getId() { return $this->id; }
	public function getSection_id() { return $this->section_id; }
	public function getParent_id() { return $this->parent_id; }
	public function getPlacement() { return $this->placement; }

	public function getSection()
	{
		if ($this->section_id)
		{
			if (!$this->section) { $this->section = new Section($this->section_id); }
			return $this->section;
		}
		else return null;
	}

	public function getParent()
	{
		if ($this->parent_id)
		{
			if (!$this->parent) { $this->parent = new Section($this->parent_id); }
			return $this->parent;
		}
		else return null;
	}

	/**
	 * Generic Setters
	 */
	public function setPlacement($int) { $this->placement = preg_replace('/[^0-9]/','',$int); }

	# Sections should be read only once this is saved in the database
	public function setSection_id($int)
	{
		if (!$this->id)
		{
			$this->section = new Section($int);
			$this->section_id = $int;
		}
	}
	public function setSection($section)
	{
		if (!$this->id)
		{
			$this->section_id = $section->getId();
			$this->section = $section;
		}
	}

	# Parents should be read only once this is saved in the database
	public function setParent_id($int)
	{
		if (!$this->id)
		{
			$this->parent = new Section($int);
			$this->parent_id = $int;
		}
	}
	public function setParent($parent)
	{
		if (!$this->id)
		{
			$this->parent_id = $parent->getId();
			$this->parent = $parent;
		}
	}
}
