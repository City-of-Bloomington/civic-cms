<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param Event $this->event
 * @param URL $this->return_url
 * @param int $this->instance_id
 */
?>
<form id="eventForm" method="post" action="<?php echo $_SERVER['PHP_SELF']; ?>">
<fieldset><legend>Description</legend>
	<?php
		$content = $this->event->getDescription();
		$content_field_name = 'description';
		include APPLICATION_HOME.'/includes/editors/'.EDITOR.'/editor_init.inc';
	?>
</fieldset>
<fieldset><legend>Submit</legend>
		<input type="hidden" name="tab" id="tab" value="sections" />
		<input type="hidden" name="action" id="action" value="next" />
		<input type="hidden" name="continue" id="continue" value="true" />
		<input type="hidden" name="return_url" id="return_url" value="<?php echo $this->return_url; ?>" />
		<input type="hidden" name="instance_id" id="instance_id" value="<?php echo $this->instance_id; ?>" />
		<button type="submit" class="next">Next</button>
		<button type="button" class="cancel" onclick="document.location.href='<?php echo $this->return_url; ?>';">Cancel</button>
		<button type="button" class="save" onclick="FRAMEWORK.processTabbedForm('eventForm','description','save');">Save</button>
</fieldset>
</form>