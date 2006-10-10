<?php
/*
	$this->categoryList
*/
	if (userHasRole("Administrator")) { $addButton = "<button type=\"button\" class=\"addSmall\" onclick=\"document.location.href='".BASE_URL."/categories/addCategory.php';\">Add</button>"; }
	function listEditableCategories($categoryList)
	{
		foreach($categoryList as $category)
		{
			echo "<li>";
			if (userHasRole("Administrator")) { echo "<button type=\"button\" class=\"editSmall\" onclick=\"document.location.href='".BASE_URL."/categories/updateCategory.php?category_id={$category->getId()}';\">Edit</button>"; }
			echo "<a href=\"".BASE_URL."/categories/viewCategory.php?category_id={$category->getId()}\">";
			echo View::sanitizeString($category->getName());
			echo "</a>";
			if ($category->hasChildren())
			{
				echo "<ul>";
				listEditableCategories($category->getChildren());
				echo "</ul>";
			}
			echo "</li>";
		}
	}
?>
<div class="interfaceBox">
	<div class="titleBar"><?php echo $addButton; ?>Categories</div>
	<ul>
		<?php listEditableCategories($this->categoryList); ?>
	</ul>
</div>