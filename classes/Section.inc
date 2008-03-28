<?php
/**
 * @copyright Copyright (C) 2006,2007,2008 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
class Section extends ActiveRecord
{
	private $id;
	private $name;
	private $nickname;
	private $sectionDocument_id;
	private $highlightSubscription;

	private $sectionDocument;

	private $childNodes;
	private $parentNodes;

	private $parents = array();
	private $children = array();
	private $ancestors = array();

	private $departments = array();
	private $newDepartmentIds = array();
	private $deletedDepartmentIds = array();

	private $documents = array();


	private $widgets = array();
	private $newWidgets = array();
	private $deletedWidgets = array();


	/**
	 * This will load all fields in the table as properties of this class.
	 * You may want to replace this with, or add your own extra, custom loading
	 */
	public function __construct($id=null)
	{
		if ($id)
		{
			$PDO = Database::getConnection();
			$sql = 'select * from sections where id=?';

			$query = $PDO->prepare($sql);
			$query->execute(array($id));

			$result = $query->fetchAll(PDO::FETCH_ASSOC);
			if (!count($result)) { throw new Exception('sections/unknownSection'); }
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

		# If this is not a New Section, you must have a sectionDocument_id
		if ($this->id && !$this->sectionDocument_id) { throw new Exception('sections/missingHomeDocument'); }


		$fields = array();
		$fields['name'] = $this->name ? $this->name : null;
		$fields['nickname'] = $this->nickname ? $this->nickname : null;
		$fields['highlightSubscription'] = $this->highlightSubscription ? true : false;

		# If sectionDocument_id is null here, it means this is a new Section
		# The new home document should be created during the Insert()
		$fields['sectionDocument_id'] = $this->sectionDocument_id ? $this->sectionDocument_id : null;

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
		if (!$this->sectionDocument_id) { throw new Exception('missingHomeDocument'); }

		$PDO = Database::getConnection();

		$sql = "update sections set $preparedFields where id={$this->id}";
		$query = $PDO->prepare($sql);
		$query->execute($values);
	}

	private function insert($values,$preparedFields)
	{
		$PDO = Database::getConnection();

		# Have to do an Insert first, so we can have a section_id to assign to the Document
		$sql = "insert sections set $preparedFields";
		$query = $PDO->prepare($sql);
		$query->execute($values);
		$this->id = $PDO->lastInsertID();

		# New Sections need a default document created for them
		if (!$this->sectionDocument_id)
		{
			$document = new Document();
			$document->setDepartment($_SESSION['USER']->getDepartment());
			$document->setTitle($this->name);
			$document->setContent("<h2>{$this->name}</h2>",$_SESSION['LANGUAGE']);
			$document->setDocumentType_id(1,$_SESSION['LANGUAGE']);
			$document->save();

			# Now we link the document to the section
			$sectionDocument = new SectionDocument();
			$sectionDocument->setSection_id($this->id);
			$sectionDocument->setDocument_id($document->getId());
			$sectionDocument->save();
			$this->sectionDocument_id = $sectionDocument->getId();
		}

		$query = $PDO->prepare('update sections set sectionDocument_id=? where id=?');
		$query->execute(array($this->sectionDocument_id,$this->id));
	}

	public function delete()
	{
		$PDO = Database::getConnection();

		$query = $PDO->prepare('update sections set sectionDocument_id=null where id=?');
		$query->execute(array($this->id));

		$PDO->beginTransaction();

		try
		{
			$query = $PDO->prepare('delete from sectionDocuments where section_id=?');
			$query->execute(array($this->id));

			$query = $PDO->prepare('delete from section_parents where section_id=? or parent_id=?');
			$query->execute(array($this->id,$this->id));

			$query = $PDO->prepare('delete from section_departments where section_id=?');
			$query->execute(array($this->id));

			$query = $PDO->prepare('delete from section_widgets where section_id=?');
			$query->execute(array($this->id));

			$query = $PDO->prepare('delete from event_sections where section_id=?');
			$query->execute(array($this->id));

			$query = $PDO->prepare('delete from sectionIndex where section_id=?');
			$query->execute(array($this->id));

			$query = $PDO->prepare('delete from sections where id=?');
			$query->execute(array($this->id));

			$PDO->commit();
		}
		catch (Exception $e)
		{
			$PDO->rollBack();
			throw $e;
		}
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
		if (!count($this->ancestors))
		{
			$PDO = Database::getConnection();
			# Since a section can be in multiple places in the tree
			# We have to do the SQL query for each place this section is in the tree
			$this->ancestors = array();
			$query = $PDO->prepare('select * from sectionIndex where section_id=?');
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
		$PDO = Database::getConnection();
		$sql = "select distinct s.section_id from sectionIndex s
				left join sectionIndex p on p.preOrder<s.preOrder and s.preOrder<p.postOrder
				where p.section_id=? order by s.preOrder";
		$query = $PDO->prepare($sql);
		$query->execute(array($this->id));
		$result = $query->fetchAll();

		$descendants = array();
		foreach($result as $row) { $descendants[$row['section_id']] = new Section($row['section_id']); }

		return $descendants;
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
		$PDO = Database::getConnection();

		# Clear out all the old departments
		if (count($this->deletedDepartmentIds))
		{
			$ids = implode(",",$this->deletedDepartmentIds);
			$query = $PDO->prepare("delete from section_departments where section_id=? and department_id in ($ids)");
			$query->execute(array($this->id));
		}

		# Add in the new ones
		if (count($this->newDepartmentIds))
		{
			$query = $PDO->prepare('insert section_departments set section_id=?,department_id=?');
			foreach($this->newDepartmentIds as $id) { $query->execute(array($this->id,$id)); }
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

	/**
	 * Document Fuctions
	 */
	public function getSectionDocuments($sort='title')
	{
		$list = new SectionDocumentList();
		$list->find(array('section_id'=>$this->id),$sort);
		return $list;
	}

	public function addDocument($document)
	{
		$list = new SectionDocumentList(array('section_id'=>$this->id,'document_id'=>$document->getId()));
		if (!count($list))
		{
			$sectionDocument = new SectionDocument();
			$sectionDocument->setSection_id($this->id);
			$sectionDocument->setDocument_id($document->getId());
			$sectionDocument->save();
		}
	}
	public function setDocument_id($int)
	{
		$document = new Document($int);

		# See if this document is already attached to this section
		$list = new SectionDocumentList(array('section_id'=>$this->id,'document_id'=>$document->getId()));
		if (count($list))
		{
			$sectionDocument = $list[0];
		}
		else
		{
			# Create a new SectionDocument for this
			$sectionDocument = new SectionDocument();
			$sectionDocument->setSection_id($this->id);
			$sectionDocument->setDocument_id($document->getId());
			$sectionDocument->save();
		}
		$this->setSectionDocument($sectionDocument);
	}
	public function getDocuments($sort='title')
	{
		if (!count($this->documents))
		{
			$this->documents = new DocumentList();
			$this->documents->find(array('section_id'=>$this->id,'active'=>date('Y-m-d')),$sort);
		}
		return $this->documents;
	}
	public function hasDocument($document)
	{
		if (!$document instanceof Document) { $document = new Document($document); }
		$list = new SectionDocumentList(array('section_id'=>$this->id,'document_id'=>$document->getId()));
		return count($list);
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

	public function permitsPostingBy($user)
	{
		if ($user->hasRole(array('Administrator','Webmaster','Publisher'))) { return true; }
		if ($user->hasRole('Content Creator'))
		{
			if (in_array($user->getDepartment_id(),array_keys($this->getDepartments()))) { return true; }
		}
		return false;
	}
	public function permitsEditingBy($user)
	{
		if ($user->hasRole('Webmaster')) { return true; }
		return false;
	}

	/**
	 * Subscription functions
	 */
	public function getSubscriptions()
	{
		return new SectionSubscriptionList(array('section_id'=>$this->id));
	}

	public function getURL() { return BASE_URL.'/sections/viewSection.php?section_id='.$this->id; }
	public function __toString() { return $this->name; }
	public function isHighlightedSubscription() { return $this->getHighlightSubscription(); }

	/**
	 * Generic Getters
	 */
	public function getId() { return $this->id; }
	public function getName() { return $this->name; }
	public function getNickname() { return $this->nickname; }
	/**
	 * The section document is the Homepage for this section.
	 *
	 * Sections have many documents, only one of which is the homepage.
	 * sectionDocument_id is the ID from the sectionDocuments table for the entry
	 * for the home document
	 * Not to be confused with the ID for the document itself
	 */
	public function getSectionDocument_id() { return $this->sectionDocument_id; }
	/**
	 * The section document is the Homepage for this section.
	 *
	 * Sections have many documents, only one of which is the homepage.
	 * sectionDocument is the entry corresponding to the homepage
	 * Not to be confused with the document itself
	 */
	public function getSectionDocument()
	{
		if ($this->sectionDocument_id && !$this->sectionDocument)
		{
			$this->sectionDocument = new SectionDocument($this->sectionDocument_id);
		}
		return $this->sectionDocument;
	}
	/**
	 * Returns the Home document for this section
	 */
	public function getDocument() { return $this->getSectionDocument()->getDocument(); }
	/**
	 * Returns the ID for the Home document of this section
	 */
	public function getDocument_id() { return $this->getDocument()->getId(); }
	public function getHighlightSubscription() { return $this->highlightSubscription; }

	/**
	 * Generic Setters
	 */
	public function setName($string) { $this->name = trim($string); }
	public function setNickname($string) { $this->nickname = trim($string); }
	public function setSectionDocument_id($int) { $this->sectionDocument = new SectionDocument($int); $this->sectionDocument_id = $int; }
	public function setSectionDocument($sectionDocument) { $this->sectionDocument_id = $sectionDocument->getId(); $this->sectionDocument = $sectionDocument; }
	public function setHighlightSubscription($bool) { $this->highlightSubscription = $bool ? true : false; }
}
