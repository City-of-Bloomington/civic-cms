<?php
/**
 * @copyright Copyright (C) 2006 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 */
	abstract class Widget extends View
	{
		protected $name;
		protected $includeFile;

		public static function load($name)
		{
			if (is_file(APPLICATION_HOME."/widgets/$name/$name.inc"))
			{
				require_once(APPLICATION_HOME."/widgets/$name/$name.inc");
				return new $name();
			}
		}

		public function install()
		{
			global $PDO;

			$query = $PDO->prepare("insert widgets values(?)");
			$query->execute(array($this->name));
		}

		public function uninstall()
		{
			global $PDO;

			$query = $PDO->prepare("delete from section_widgets where widget_name=?");
			$query->execute(array($this->name));

			$query = $PDO->prepare("delete from widgets where name=?");
			$query->excecute(array($this->name));
		}

		public function getStatus()
		{
			global $PDO;

			$query = $PDO->prepare("select count(*) as count from widgets where name=?");
			$query->execute(array($this->name));
			$result = $query->fetchAll();
			if ($result[0]['count'] == 1) { return "installed"; }
			else { return "uninstalled"; }
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
			global $PDO;

			$widgets = array();

			$sql = "select name from widgets";
			foreach($PDO->query($sql) as $row) { $widgets[] = Widget::load($row['name']); }
			return $widgets;
		}

		public function __toString() { return $this->name; }
		public function getName() { return $this->name; }
		public function getIncludeFile() { return $this->includeFile; }
	}
?>