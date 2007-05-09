<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
?>
<h2>Event</h2>
<div class="tabBar">
<ul><li><a href="<?php echo BASE_URL; ?>/events/updateEvent.php?tab=info" onclick="FRAMEWORK.processTabbedForm('eventForm','info','next');return false;">Event</a></li>
	<li><a href="<?php echo BASE_URL; ?>/events/updateEvent.php?tab=sections" onclick="FRAMEWORK.processTabbedForm('eventForm','sections','next');return false;">Sections</a></li>
	<li><a href="<?php echo BASE_URL; ?>/events/updateEvent.php?tab=recurrence" onclick="FRAMEWORK.processTabbedForm('eventForm','recurrence','next');return false;">Recurrance</a></li>
</div>
