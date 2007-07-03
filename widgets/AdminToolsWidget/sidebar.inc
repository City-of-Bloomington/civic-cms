<div><div class="titleBar">Admin</div>
<ul>
<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
	if (userHasRole('Administrator'))
	{
		echo "
		<li><a href=\"".BASE_URL."/users\">Users</a></li>
		<li><a href=\"".BASE_URL."/departments\">Departments</a></li>
		<li><a href=\"".BASE_URL."/backups\">Backups</a></li>
		";

	}

	if (userHasRole('Webmaster') || userHasRole('Administrator'))
	{
		echo "
		<li><a href=\"".BASE_URL."/documents\">Documents</a></li>
		<li><a href=\"".BASE_URL."/sections\">Sections</a></li>
		<li><a href=\"".BASE_URL."/facets\">Facets</a></li>
		<li><a href=\"".BASE_URL."/documentTypes\">Document Types</a></li>
		<li><a href=\"".BASE_URL."/locations\">Locations</a></li>
		<li><a href=\"".BASE_URL."/calendars\">Calendars</a></li>
		<li><a href=\"".BASE_URL."/media/attachments.php\">Attachments</a></li>
		<li><a href=\"".BASE_URL."/widgets\">Widgets</a></li>
		";
	}

	if ( userHasRole('Content Creator') || userHasRole('Publisher') )
	{
		echo "
		<li><a href=\"".BASE_URL."/documents\">My Documents</a></li>
		";
	}
?>
</ul>
</div>
