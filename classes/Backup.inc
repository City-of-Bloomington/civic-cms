<?php
/**
 * @copyright Copyright (C) 2007-2008 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
class Backup
{
	private $path;
	private $filename;

	public function __construct($filename=null)
	{
		$this->path = APPLICATION_HOME.'/backups';
		$this->filename = $filename ? basename($filename) : date('Y-m-d').'.tar.gz';
	}

	public function save()
	{
		$backup  = "{$this->path}/{$this->filename}";

		# Delete any old backup with this name.  We want to create a fresh copy
		if (file_exists($backup)) { unlink($backup); }

		exec(MYSQL_PATH.'/bin/mysqldump -u '.DB_USER.' -p'.DB_PASS.' --opt '.DB_NAME.' > '.APPLICATION_HOME.'/data/database.sql');
		exec('tar cz -C '.APPLICATION_HOME." -f $backup data");

		if (!file_exists($backup)) { throw new Exception('backups/createFailed'); }
	}

	public function __toString() { return $this->filename; }
	public function getFilename() { return $this->filename; }
	public function getFilesize() { return filesize("{$this->path}/{$this->filename}"); }
	public function getPath() { return $this->path; }
}
