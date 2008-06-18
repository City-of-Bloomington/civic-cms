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
<form id="eventForm" method="post" action="<?php echo $_SERVER['SCRIPT_NAME']; ?>">
<fieldset><legend>Sections</legend>
	<p>Where on the site do you want this event to show up?</p>
	<table>
	<?php
		$sections = new SectionList();
		if (userHasRole(array('Administrator','Webmaster'))) { $sections->find(); }
		else { $sections->find(array('department_id'=>$_SESSION['USER']->getDepartment_id())); }

		foreach($sections as $section)
		{
			$checked = $this->event->hasSection($section) ? 'checked="checked"' : '';
			$name = View::escape($section->getName());
			echo "
			<tr><td><input name=\"event[sections][{$section->getId()}]\" id=\"event-sections-{$section->getId()}\" type=\"checkbox\" value=\"{$section->getId()}\" $checked /></td>
				<td><label for=\"event-sections-{$section->getId()}\">$name</label></td></tr>
			";
		}
	?>
	</table>
</fieldset>
<fieldset><legend>Submit</legend>
		<input type="hidden" name="tab" id="tab" value="info" />
		<input type="hidden" name="action" id="action" value="next" />
		<input type="hidden" name="continue" id="continue" value="true" />
		<input type="hidden" name="return_url" id="return_url" value="<?php echo $this->return_url; ?>" />
		<input type="hidden" name="instance_id" id="instance_id" value="<?php echo $this->instance_id; ?>" />
		<button type="submit" class="next">Next</button>
		<a class="cancel" href="<?php echo $this->return_url; ?>">Cancel</a>
		<button type="button" class="save" onclick="FRAMEWORK.processTabbedForm('eventForm','info','save');">Save</button>
</fieldset>
</form>
