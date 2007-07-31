<div class="tabBar">
<ul>
<?php
/**
* @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
* @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
* @author Cliff Ingham <inghamn@bloomington.in.gov>
* @param string $this->current_tab
*/
	$href = new URL(BASE_URL.'/documents/addDocument.php');

	$tabs = array('info','content','sections','facets');

	foreach($tabs as $tab)
	{
		$name = ucfirst($tab);
		$href->parameters['tab'] = $tab;
		$onclick = "FRAMEWORK.processTabbedForm('documentForm','$tab','next');return false;";
		$class = $this->current_tab==$tab ? 'class="current"' : '';
		echo "<li><a href=\"$href\" onclick=\"$onclick\" $class>$name</a></li>";
	}

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
