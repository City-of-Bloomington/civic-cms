<?php
/**
* @copyright Copyright (C) 2006 Cliff Ingham. All rights reserved.
* @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
*/
	function listCategories($categoryList)
	{
		foreach($categoryList as $category)
		{
			echo "<li><a href=\"".BASE_URL."/categories/viewCategory.php?category_id={$category->getId()}\">";
			echo View::sanitizeString($category->getName());
			echo "</a>";
			if ($category->hasChildren())
			{
				echo "<ul>";
				listCategories($category->getChildren());
				echo "</ul>";
			}
			echo "</li>";
		}
	}
?>
<div id="sidebar">
	<div>
		<div class="titleBar"><a href="<?php echo BASE_URL; ?>/categories">Categories</a></div>
		<ul>
			<?php
				$categories = new CategoryList(array("parent_id"=>1));
				listCategories($categories);
			?>
		</ul>
	</div>
	<?php
		if (!isset($_SESSION['USER'])) { include(FRAMEWORK."/sidebarBoxes/loginBox.inc"); }
		else { if (in_array("Administrator",$_SESSION['USER']->getRoles())) { include(APPLICATION_HOME."/includes/sidebarBoxes/Administrator.inc"); } }
	?>
</div>