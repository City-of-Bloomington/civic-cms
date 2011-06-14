<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
?>
<h1>Skins</h1>
<table>
<tr><th>Name</th><th>Preview</th></tr>
<?php
	$list = new DirectoryIterator(APPLICATION_HOME.'/html/skins');
	foreach($list as $dir)
	{
		if ($dir!='.' && $dir!='..')
		{
			if (is_file(APPLICATION_HOME."/html/skins/$dir/screen.css"))
			{
				$skin = basename($dir);

				$glob = glob(APPLICATION_HOME."/html/skins/$skin/preview.*");
				$preview = (count($glob)) ? "<img src=\"".BASE_URL."/skins/$skin/".basename($glob[0])."\" />" : '';

				echo "
				<tr><td><a href=\"".BASE_URL."/skins?skin=$skin\">$skin</a></td>
					<td><a href=\"".BASE_URL."/skins?skin=$skin\">$preview</a></td>
				</tr>
				";
			}
		}
	}
?>
</table>