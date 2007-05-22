<?php
/**
 * @copyright Copyright (C) 2006,2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param string $this->title
 */
	if (!isset($this->title)) { $this->title = "Content Manager - City of Bloomington"; }
	include APPLICATION_HOME.'/includes/xhtmlTransitionalHeader.inc';
	include APPLICATION_HOME.'/includes/banner.inc';
	include APPLICATION_HOME.'/includes/menubar.inc';
?>
<div id="mainContent">
	<?php
		include FRAMEWORK.'/errorMessages.inc';

		$this->includeBlocks();
	?>
</div>
<?php
	include APPLICATION_HOME.'/includes/footer.inc';
	include FRAMEWORK.'/xhtmlFooter.inc';
?>