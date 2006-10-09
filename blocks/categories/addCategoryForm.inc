<?php
	function printCategoryOptions($category,$depth)
	{
		$depthIndicator = str_repeat("-",$depth);
		echo "<option value=\"{$category->getId()}\">$depthIndicator".View::sanitizeString($category->getName())."</option>";
		if ($category->hasChildren())
		{
			foreach($category->getChildren() as $child) { printCategoryOptions($child,$depth+1); }
		}
	}
?>
<form method="post" action="<?php echo $_SERVER['PHP_SELF']; ?>">
<fieldset><legend>Category Info</legend>
	<table>
	<tr><td><label for="category-name">Name</label></td>
		<td><input name="category[name]" id="category-name" /></td></tr>
	<tr><td><label for="category-parents">Parents</label></td>
		<td><select name="category[parents][]" size="10" multiple="multiple"><option></option>
			<?php
				$categories = new CategoryList(array("parent_id"=>1));
				foreach($categories as $category)
				{
					printCategoryOptions($category,0);
				}
			?>
			</select>
		</td>
	</tr>
	</table>

	<button type="submit" class="submit">Submit</button>
	<button type="button" class="done" onclick="document.location.href='<?php echo BASE_URL; ?>/categories';">Done</button>
</fieldset>
</form>