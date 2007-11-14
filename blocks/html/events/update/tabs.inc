<h1>Event</h1>
<div class="tabBar">
<ul>
<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param string $this->currentTab
 */
	$href = new URL("http://$_SERVER[SERVER_NAME]$_SERVER[PHP_SELF]");
	$tabs = array('info','description','sections');

	foreach($tabs as $tab)
	{
		# If we've already hit the current tab, then class will be set.
		# On this next iteration, we can store the name of the next tab
		if (isset($class) && $class) { $this->next_tab = $tab; }

		# Display each tab, in turn
		$name = ucfirst($tab);
		$href->parameters['tab'] = $tab;
		$onclick = "FRAMEWORK.processTabbedForm('eventForm','$tab','next');return false;";
		$class = $this->currentTab==$tab ? 'class="current"' : '';
		echo "<li><a href=\"$href\" onclick=\"$onclick\" $class>$name</a></li>";
	}
	if (!isset($this->next_tab)) { $this->next_tab = $tabs[0]; }
?>
</ul>
</div>
