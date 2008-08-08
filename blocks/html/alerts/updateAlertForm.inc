<?php
/**
 * @copyright Copyright (C) 2008 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param Alert $this->alert
 */
?>
<script type="text/javascript" src="http://yui.yahooapis.com/2.5.2/build/utilities/utilities.js"></script>
<script type="text/javascript" src="http://yui.yahooapis.com/2.5.2/build/yahoo-dom-event/yahoo-dom-event.js"></script>
<script type="text/javascript" src="http://yui.yahooapis.com/2.5.2/build/calendar/calendar-min.js"></script>

<h1>Add Alert</h1>
<form method="post" action="<?php echo $_SERVER['SCRIPT_NAME']; ?>" class="yui-skin-sam">
<fieldset><legend>Alert Info</legend>
	<input name="alert_id" type="hidden" value="<?php echo $this->alert->getId(); ?>" />
	<table>

	<tr><td><label for="alert-title" class="required">Title</label></td>
		<td><input name="alert[title]" id="alert-title" value="<?php echo View::escape($this->alert->getTitle()); ?>" /></td></tr>

	<tr><td><label for="start-date" class="required">Start</label></td>
		<td><input name="start[date]" id="start-date" value="<?php echo $this->alert->getStartTime('n/j/Y'); ?>" onfocus="FRAMEWORK.popupCalendar(this);" />
			<input name="start[time]" id="start-time" value="<?php echo $this->alert->getStartTime('h:ia'); ?>" />
		</td>
	</tr>
	<tr><td><label for="end-date" class="required">End</label></td>
		<td><input name="end[date]" id="end-date" value="<?php echo $this->alert->getEndTime('n/j/Y'); ?>" onfocus="FRAMEWORK.popupCalendar(this);" />
			<input name="end[time]" id="end-time" value="<?php echo $this->alert->getEndTime('h:ia'); ?>" />
		</td>
	</tr>

	<tr><td><label for="alert-url">url</label></td>
		<td><input name="alert[url]" id="alert-url" value="<?php echo View::escape($this->alert->getUrl()); ?>" /></td></tr>

	<tr><td><label for="alert-text" class="required">Message</label></td>
		<td><textarea name="alert[text]" id="alert-text" rows="3" cols="60"><?php echo View::escape($this->alert->getText()); ?></textarea></td></tr>

	</table>

	<button type="submit" class="submit">Submit</button>
	<a class="cancel" href="<?php echo BASE_URL; ?>/alerts">Cancel</a>
</fieldset>
</form>