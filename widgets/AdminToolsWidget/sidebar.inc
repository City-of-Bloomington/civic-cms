<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
	$links = array();
	$links['Calendars'] = "<li><a href=\"".BASE_URL."/calendars\">Calendars</a></li>";
	$links['Locations'] = "<li><a href=\"".BASE_URL."/locations\">Locations</a></li>";

	if ( userHasRole('Content Creator') || userHasRole('Publisher') )
	{
		$links['Documents'] = "<li><a href=\"".BASE_URL."/documents\">My Documents</a></li>";
	}
	if (userHasRole('Administrator'))
	{
		$links['Users'] = "<li><a href=\"".BASE_URL."/users\">Users</a></li>";
		$links['Departments'] = "<li><a href=\"".BASE_URL."/departments\">Departments</a></li>";
		$links['Backups'] = "<li><a href=\"".BASE_URL."/backups\">Backups</a></li>";
	}

	if (userHasRole('Webmaster') || userHasRole('Administrator'))
	{
		$links['Documents'] = "<li><a href=\"".BASE_URL."/documents\">Documents</a></li>";
		$links['Sections'] = "<li><a href=\"".BASE_URL."/sections\">Sections</a></li>";
		$links['Facets'] = "<li><a href=\"".BASE_URL."/facets\">Facets</a></li>";
		$links['DocumentTypes'] = "<li><a href=\"".BASE_URL."/documentTypes\">Document Types</a></li>";
		$links['Attachments'] = "<li><a href=\"".BASE_URL."/media/attachments.php\">Attachments</a></li>";
		$links['Widgets'] = "<li><a href=\"".BASE_URL."/widgets\">Widgets</a></li>";
	}

?>
<div><div class="titleBar">Admin</div>
<ul>
<?php
	foreach($links as $name=>$listItem)
	{
		echo "\t$listItem\n";
	}
?>
</ul>
</div>
