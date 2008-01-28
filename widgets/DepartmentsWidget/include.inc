<?php
/**
 * @copyright Copyright (C) 2008 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
?>
<div class="widget">
	<h1>City Offices</h1>
	<?php
		echo WikiMarkup::parse($this->content);
	?>
	<form method="get" action="<?php echo BASE_URL; ?>/documents/viewDocument.php">
	<fieldset><legend>Departments</legend>
		<select name="document_id" onchange="this.form.submit();">
			<option value="">City Departments</option>
		<?php
			$list = new DepartmentList();
			$list->find();
			foreach($list as $department)
			{
				$name = View::escape($department->getName());
				echo "<option value=\"{$department->getDocument_id()}\">$name</option>";
			}
		?>
		</select>
	</fieldset>
	</form>
</div>