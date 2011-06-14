<div class="tabBar">
<ul>
<?php
/**
* @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
* @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
* @author Cliff Ingham <inghamn@bloomington.in.gov>
* @param string $this->current_tab
* @param URL $this->return_url
*/
	$tabs = array('info','content','sections','facets','attachments','links');

	foreach($tabs as $tab)
	{
		# If we've already hit the current tab, then class will be set.
		# On this next iteration, we can store the name of the next tab
		if (isset($class) && $class) { $this->next_tab = $tab; }

		# Display each tab, in turn
		$name = ucfirst($tab);
		$onclick = "FRAMEWORK.processTabbedForm('documentForm','$tab','next');return false;";
		$class = $this->current_tab==$tab ? 'class="current"' : '';
		echo "<li $class><a onclick=\"$onclick\">$name</a></li>";
	}
	if (!isset($this->next_tab)) { $this->next_tab = $tabs[0]; }

	# Access to the Admin tab is controlled seperately
	if(userHasRole('Webmaster') || userHasRole('Administrator'))
	{
		$class = $this->current_tab=='admin' ? 'class="current"' : '';
		$onclick = "FRAMEWORK.processTabbedForm('documentForm','admin','next');return false;";
		echo "<li $class><a onclick=\"$onclick\">Admin</a></li>";
	}
?>
</ul>
</div>
<div>
	<p>Move on to the next tab.  The document will not be saved to the database until you click the "Save" button.</p>
	<button type="submit" class="next" onclick="FRAMEWORK.processTabbedForm('documentForm','<?php echo $this->next_tab; ?>','next');">Next</button>
	<a class="cancel" href="<?php echo $this->return_url; ?>">Cancel</a>
	<button type="button" class="save" onclick="FRAMEWORK.processTabbedForm('documentForm','<?php echo $this->current_tab; ?>','save');">Save</button>
	<button type="button" class="saveAndContinue" onclick="FRAMEWORK.processTabbedForm('documentForm','<?php echo $this->current_tab; ?>','saveAndContinue');">Save and Continue</button>
</div>
