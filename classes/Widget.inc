<?php
/**
 * @copyright Copyright (C) 2006,2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
	abstract class Widget
	{
		protected $className;
		protected $displayName;
		protected $includeFile;
		protected $description;

		private $status;
		private $installation;

		public $editDataLink = '';

		/**
		 * Widgets must declare this function.  It's up to the individual
		 * widget what format to serialize their data in, though.
		 * They could use XML, JSON, serialize(), whatever
		 * @param string $serializedData
		 */
		abstract public function setData($serializedData);
		abstract public function serializePost(array $post);

		public static function load($classname)
		{
			global $PDO;

			if (is_file(APPLICATION_HOME."/widgets/$classname/$classname.inc"))
			{
				require_once APPLICATION_HOME."/widgets/$classname/$classname.inc";
				return new $classname();
			}
		}

		public function getInstallation()
		{
			if (!$this->installation)
			{
				$this->installation = new WidgetInstallation($this->className);
			}
			return $this->installation;
		}

		public function install()
		{
			$this->getInstallation()->save();
			$this->status = 'installed';
		}
		public function uninstall()
		{
			$this->getInstallation()->delete();
			$this->status = 'uninstalled';
		}

		public function getStatus()
		{
			global $PDO;

			if (!$this->status)
			{
				$query = $PDO->prepare('select count(*) as count from widgets where class=?');
				$query->execute(array($this->className));
				$result = $query->fetchAll();
				if ($result[0]['count'] == 1) { $this->status = 'installed'; }
				else { $this->status = 'uninstalled'; }
			}
			return $this->status;
		}

		public static function findAll()
		{
			$widgets = array();
			$list = new DirectoryIterator(APPLICATION_HOME."/widgets");
			foreach($list as $dir)
			{
				if (is_file("{$dir->getPathname()}/{$dir->getFilename()}.inc"))
				{
					$widgets[] = Widget::load($dir->getFilename());
				}
			}
			return $widgets;
		}
		public static function findInstalled()
		{
			$list = new WidgetInstallationList();
			$list->find();
			return $list;
		}

		protected function renderIncludeFile($widget)
		{
			include APPLICATION_HOME.'/widgets/'.get_class($widget).'/'.$widget->includeFile;
		}

		/**
		 * Aliases for the WidgetInstallation functions
		 */
		public function getId() { return $this->getInstallation()->getId(); }
		public function getGlobal_panel_id() { return $this->getInstallation()->getGlobal_panel_id(); }
		public function getGlobal_layout_order() { return $this->getInstallation()->getGlobal_layout_order(); }
		public function getDefault_panel_id() { return $this->getInstallation()->getDefault_panel_id(); }
		public function getDefault_layout_order() { return $this->getInstallation()->getDefault_layout_order(); }
		public function getWidget() { return $this; }

		public function getGlobal_panel() { return $this->getInstallation()->getGlobal_panel(); }
		public function getDefault_panel() { return $this->getInstallation()->getDefault_panel(); }

		public function isGlobal()
		{
			if ($this->getInstallation()) { return $this->installation->isGlobal(); }
			else { return false; }
		}
		public function isDefault()
		{
			if ($this->getInstallation()) { return $this->installation->isDefault(); }
			else { return false; }
		}

		public function __toString() { return $this->displayName; }

		/**
		 * Generic Getters
		 */
		public function getClassName() { return $this->className; }
		public function getName() { return $this->displayName; }
		public function getIncludeFile() { return $this->includeFile; }
		public function getDescription() { return $this->description; }
	}
?>