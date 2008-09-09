<?php
/**
 * @copyright Copyright (C) 2008 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
?>
<script type="text/javascript" src="<?php echo BASE_URL; ?>/js/yui/build/utilities/utilities.js"></script>
<script type="text/javascript" src="<?php echo BASE_URL; ?>/js/yui/build/yahoo-dom-event/yahoo-dom-event.js"></script>
<script type="text/javascript" src="<?php echo BASE_URL; ?>/js/yui/build/calendar/calendar-min.js"></script>

<h1>Add Alert</h1>
<form method="post" action="<?php echo $_SERVER['SCRIPT_NAME']; ?>" class="yui-skin-sam">
<fieldset><legend>Alert Info</legend>
	<table>

	<tr><td><label for="alert-title" class="required">Title</label></td>
		<td><input name="alert[title]" id="alert-title" /></td></tr>

	<tr><td><label for="start-date" class="required">Start</label></td>
		<td><input name="start[date]" id="start-date" value="<?php echo date('n/j/Y'); ?>" onfocus="FRAMEWORK.popupCalendar(this);" />
			<input name="start[time]" id="start-time" value="<?php echo date('h:ia'); ?>" />
		</td>
	</tr>
	<tr><td><label for="end-date" class="required">End</label></td>
		<td><input name="end[date]" id="end-date" value="<?php echo date('n/j/Y'); ?>" onfocus="FRAMEWORK.popupCalendar(this);" />
			<input name="end[time]" id="end-time" value="<?php echo date('h:ia'); ?>" />
		</td>
	</tr>

	<tr><td><label for="alert-url">URL</label></td>
		<td><input name="alert[url]" id="alert-url" /></td></tr>

	<tr><td><label for="alert-text" class="required">Message</label></td>
		<td><textarea name="alert[text]" id="alert-text" rows="3" cols="60"></textarea></td></tr>

	</table>

	<button type="submit" class="submit">Submit</button>
	<a class="cancel" href="<?php echo BASE_URL; ?>/alerts">Cancel</a>
</fieldset>
</form>
