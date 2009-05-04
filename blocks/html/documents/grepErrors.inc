<?php
/**
 * @copyright 2009 City of Bloomington, Indiana
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param array $this->errors
 */
?>
<div class="interfaceBox">
	<h1>Grep Errors</h1>
	<p>We found these files hanging around, even though they have been deleted from the database.</p>
	<table>
	<?php
		foreach ($this->errors as $filename) {
			echo "
			<tr><td>$filename</td></tr>
			";
		}
	?>
	</table>
</div>
