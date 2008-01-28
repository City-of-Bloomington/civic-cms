<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
?>
<h1>Document Content Search</h1>
<p>This page will perform a regular expression search for Documents.</p>
<form id="grepForm" method="get" action="<?php echo $_SERVER['PHP_SELF']; ?>">
<fieldset><legend>Grep</legend>
	<table>
	<tr><td><label for="grep">Grep</label></td>
		<td><input name="grep" id="grep" size="60" value="<?php if (isset($_GET['grep'])) echo $_GET['grep']; ?>" /></td></tr>
	</table>

	<button type="submit" class="search">Search</button>
</fieldset>
<fieldset><legend>Predefined Searches</legend>
<script type="text/javascript">
function grep(string)
{
	document.getElementById('grep').value = string;
	document.getElementById('grepForm').submit();
}
</script>
	<table>
	<tr><th>Forms</th>
		<td><a href="#" onclick="grep('&lt;form');">&lt;form</a></td>
		<td>Find documents that have forms in them.</td>
	</tr>
	<tr><th>Image tags</th>
		<td><a href="#" onclick="grep('&lt;img');">&lt;img</a></td>
		<td>Find documents that have image tags in them.  These are not using
			the [image:] syntax.</td>
	</tr>
	</table>
</fieldset>
</form>
