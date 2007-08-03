<div class="tabBar">
<ul>
<?php
/**
* @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
* @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
* @author Cliff Ingham <inghamn@bloomington.in.gov>
* @param string $this->current_tab
*/
	$href = new URL(BASE_URL.'/documents/updateDocument.php');

	$tabs = array('info','content','sections','facets','attachments','links');

	foreach($tabs as $tab)
	{
		# If we've already hit the current tab, then class will be set.
		# On this next iteration, we can store the name of the next tab
		if (isset($class) && $class) { $this->next_tab = $tab; }

		# Display each tab, in turn
		$name = ucfirst($tab);
		$href->parameters['tab'] = $tab;
		$onclick = "FRAMEWORK.processTabbedForm('documentForm','$tab','next');return false;";
		$class = $this->current_tab==$tab ? 'class="current"' : '';
		echo "<li><a href=\"$href\" onclick=\"$onclick\" $class>$name</a></li>";
	}
	if (!isset($this->next_tab)) { $this->next_tab = $tabs[0]; }

	# Access to the Source tab is controlled seperately
	if(userHasRole('Webmaster') || userHasRole('Administrator'))
	{
		$href->parameters['tab'] = 'source';
		$class = $this->current_tab=='source' ? 'class="current"' : '';
		$onclick = "FRAMEWORK.processTabbedForm('documentForm','source','next');return false;";
		echo "<li><a href=\"$href\" onclick=\"$onclick\" $class>Source</a></li>";
	}
?>
</ul>
</div>
<div>
	<p>Move on to the next tab.  The document will not be saved to the database until you click the "Save" button.</p>
	<button type="submit" class="next" onclick="FRAMEWORK.processTabbedForm('documentForm','<?php echo $this->next_tab; ?>','next');">Next</button>
	<button type="cancel" class="cancel" onclick="self.close();">Cancel</button>
	<button type="button" class="save" onclick="FRAMEWORK.processTabbedForm('documentForm','<?php echo $this->current_tab; ?>','save');">Save</button>
</div>
