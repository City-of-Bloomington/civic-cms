<?php
/**
 * @copyright Copyright (C) 2006,2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param string $this->title
 */
	if (!isset($this->title)) { $this->title = "City of Bloomington"; }
	include APPLICATION_HOME.'/includes/xhtmlStrictHeader.inc';
?>
<script type="text/javascript">
	opener.location.reload();
	self.close();
</script>
<?php
	include APPLICATION_HOME.'/includes/xhtmlFooter.inc';
?>