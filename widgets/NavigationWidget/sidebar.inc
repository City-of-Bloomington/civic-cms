<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param array $this->ancestors
 * @param Section $this->section
 * @param Document $this->document
 */
	$list = '';
	foreach($this->section->getChildren() as $child)
	{
		$name = View::escape($child->getName());
		$list.= "<li><a href=\"".BASE_URL."/sections/viewSection.php?section_id={$child->getId()}\">$name</a></li>\n";
	}
	if ($list) { $list = "<ul>$list</ul>"; }

 	$name = View::escape($this->section->getName());
 	$currentSectionListItem = "<li class=\"current\"><a href=\"".BASE_URL."/sections/viewSection.php?section_id={$this->section->getId()}\">$name</a>$list</li>\n";


	# Now start working backward through the ancestors and created the list
	$this->ancestors = array_reverse($this->ancestors,true);
	$count = 0;
	$temp = '';
	foreach($this->ancestors as $ancestor)
	{
		$count++;

		if ($count==1)
		{
			# This is the parent section
			# List all the children of this parent (siblings of the current section)
			$list = '';
			foreach($ancestor->getChildren() as $child)
			{
				if ($child->getId() == $this->section->getId()) { $list.=$currentSectionListItem; }
				else
				{
					$name = View::escape($child->getName());
					$list.= "<li><a href=\"".BASE_URL."/sections/viewSection.php?section_id={$child->getId()}\">$name</a></li>\n";
				}
			}
			if ($ancestor->getId() != 1)
			{
				$name = View::escape($ancestor->getName());
				$temp.= "<li class=\"current\"><a href=\"".BASE_URL."/sections/viewSection.php?section_id={$ancestor->getId()}\">$name</a><ul>$list</ul></li>\n";
			}
			else
			{
				$temp.="<ul>$list</ul>\n";
			}
		}
		else
		{
			# This is a non-expanded ancestor
			if ($ancestor->getId() != 1)
			{
				$name = View::escape($ancestor->getName());
				$temp = "<li><a href=\"".BASE_URL."/sections/viewSection.php?section_id={$ancestor->getId()}\">$name</a></li>$temp\n";
			}
		}
	}
?>
<div>
	<div class="titleBar">
		<form method="get" action="<?php echo BASE_URL; ?>/documents/search.php">
		<fieldset>
			<input name="search" id="search" size="7" />
			<button type="submit" class="search">Search</button>
		</fieldset>
		</form>
	</div>
	<ul><?php echo $temp; ?></ul>
</div>
