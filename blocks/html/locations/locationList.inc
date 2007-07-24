<?php
/**
 * @copyright Copyright (C) 2006,2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param LocationGroup $this->locationGroup
 */
?>
<h2>Locations</h2>
<form method="get" action="<?php echo $_SERVER['PHP_SELF']; ?>">
<fieldset><legend>Location Group</legend>
	<select name="locationGroup_id" onchange="this.form.submit();">
		<option value="null">Other</option>
	<?php
		$list = new LocationGroupList();
		$list->find();
		foreach($list as $group)
		{
			$name = View::escape($group->getName());

			if (isset($this->locationGroup) && $this->locationGroup->getId()==$group->getId()) { $selected = 'selected="selected"'; }
			else { $selected = ''; }

			echo "<option value=\"{$group->getId()}\" $selected>$name</option>\n";
		}
	?>
	</select>
</fieldset>
</form>

<div class="interfaceBox">
	<div class="titleBar">
		<button type="button" class="addSmall" onclick="document.location.href='<?php echo BASE_URL; ?>/locations/addLocation.php';">Add</button>
		<?php
			if (isset($this->locationGroup))
			{
				$name = View::escape($this->locationGroup->getName());
				$list = new LocationList(array('locationGroup_id'=>$this->locationGroup->getId()));
			}
			else
			{
				$name = 'Other';
				$list = new LocationList(array('locationGroup_id'=>null));
			}
			echo $name;
		?>
	</div>
	<ul><?php
			foreach($list as $location)
			{
				$name = View::escape($location->getName());

				if ($location->permitsEditingBy($_SESSION['USER']))
				{
					$button = "<button type=\"button\" class=\"editSmall\" onclick=\"document.location.href='".BASE_URL."/locations/updateLocation.php?id={$location->getId()}';\">Edit</button>";
				}
				else { $button = ''; }

				echo "<li>$button $name</li>\n";
			}
		?>
	</ul>
</div>
