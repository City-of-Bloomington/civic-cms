<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
	function getFilebrowserCallback($media)
	{
		$title = htmlspecialchars($media->getTitle(),ENT_QUOTES);
		return "selectImage('{$media->getURL()}','$title');return false;";
	}
?>
<script type="text/javascript" src="<?php echo BASE_URL; ?>/editors/tiny_mce/tiny_mce_popup.js"></script>
<script type="text/javascript">
	function selectImage(url,alt)
	{
		var win = tinyMCE.getWindowArg("window");
		win.document.getElementById(tinyMCE.getWindowArg("input")).value = url;
		win.document.getElementById('alt').value = alt;
		self.close();
	}
</script>
