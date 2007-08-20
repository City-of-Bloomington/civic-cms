<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
	function getFilebrowserCallback($media)
	{
		$title = View::escape(addslashes($media->getTitle()));
		return "selectImage('{$media->getURL()}',{$media->getWidth()},{$media->getHeight()},'$title');return false;"
	}
?>
<script type="text/javascript">
	function selectImage(url,width,height,alt)
	{
		window.opener.SetUrl( url, width, height, alt);
		self.close();
	}
</script>
