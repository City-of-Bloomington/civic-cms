<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
?>
<div class="interfaceBox">
	<div class="titleBar">
		Backups
		<button type="button" class="addSmall" onclick="document.location.href='<?php echo BASE_URL; ?>/backups/create.php';">Add</button>
	</div>
	<table>
	<?php
		$list = new DirectoryIterator(APPLICATION_HOME.'/backups');
		foreach($list as $file)
		{
			if (substr(basename($file),0,1) !== '.')
			{
				$backup = new Backup($file);

				echo "
				<tr><td>$backup</td>
					<td><button type=\"button\" class=\"download\" onclick=\"document.location.href='".BASE_URL."/backups/download.php?backup=$backup';\">Download</button>
					</td>
				</tr>
				";
			}
		}
	?>
	</table>
</div>
