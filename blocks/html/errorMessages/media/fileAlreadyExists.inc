<?php
/**
 * @copyright Copyright (C) 2007-2008 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param Exception $this->error
 */
?>
<p>That file has already been uploaded.</p>
<p>Someone has previously uploaded that file.<p>
<?php
	$list = new MediaList(array('md5'=>$this->error->getMd5()));
	if (count($list))
	{
		$media = $list[0];
		$function = ($media->getMedia_type() == 'image') ? 'insert' : 'addAttachment';

		echo "
		<p>Here's the file we've found already in the system.  Click this link to use this file.
		<a href=\"{$media->getURL()}\" onclick=\"$function('{$media->getId()}');return false;\" class=\"{$media->getExtension()}\">{$media->getFilename()}</a>
		</p>
		";
	}
?>