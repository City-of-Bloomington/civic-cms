<?php
/**
 * @copyright Copyright (C) 2007-2008 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
?>
<div class="interfaceBox">
	<h2>
		Backups
		<a class="addSmall button" href="<?php echo BASE_URL; ?>/backups/create.php">Add</a>
	</h2>
	<table>
	<?php
		$files = array();
		$list = new DirectoryIterator(APPLICATION_HOME.'/backups');
		foreach($list as $file)
		{
			if (substr(basename($file),-2) === 'gz')
			{
				$files[] = $file->getFilename();
			}
		}
		sort($files);
		foreach($files as $file)
		{
			$backup = new Backup($file);

			echo "
			<tr><td>$backup</td>
				<td><a class=\"download button\" href=\"".BASE_URL."/backups/download.php?backup=$backup\">Download</a>
				</td>
			</tr>
			";
		}
	?>
	</table>
</div>
