<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
?>
<h2><?php
		if (userHasRole(array('Administrator','Webmaster')))
		{
			echo "<button type=\"button\" class=\"addSmall\" onclick=\"document.location.href='".BASE_URL."/facets/addFacet.php';\">Add</button>";
		}
	?>
	Facets
</h2>
