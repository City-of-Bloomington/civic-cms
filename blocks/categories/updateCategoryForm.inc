<?php
/*
	$this->category
*/
	function printCategoryOptions($category,$depth,$categoryToEdit)
	{
		$depthIndicator = str_repeat("-",$depth);
		if ($categoryToEdit->hasParent($category))
			{ echo "<option value=\"{$category->getId()}\" selected=\"selected\">$depthIndicator {$category->getName()}</option>"; }
		else { echo "<option value=\"{$category->getId()}\">$depthIndicator {$category->getName()}</option>"; }
		if ($category->hasChildren())
		{
			foreach($category->getChildren() as $child) { printCategoryOptions($child,$depth+1,$categoryToEdit); }
		}
	}
?>
<form method="post" action="<?php echo $_SERVER['PHP_SELF']; ?>">
<fieldset><legend>Category Info</legend>
	<input name="id" type="hidden" value="<?php echo $this->category->getId(); ?>" />
	<table>
	<tr><td><label for="category-name">Name</label></td>
		<td><input name="category[name]" id="category-name" value="<?php echo $this->category->getName(); ?>" /></td></tr>
	<tr><td><label for="category-parents">Parents</label></td>
		<td><select name="category[parents][]" size="10" multiple="multiple"><option></option>
			<?php
				$categories = new CategoryList(array("parent_id"=>"null"));
				foreach($categories as $category)
				{
					printCategoryOptions($category,0,$this->category);
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