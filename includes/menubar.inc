<?php
/**
 * @copyright Copyright (C) 2006,2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
?>
<div class="menuBar">
<ul>
<?php
	#$sectionNodeList = new SectionNodeList(array('parent_id'=>1));
	#foreach($sectionNodeList as $node)
	$sectionList = new SectionList(array('parent_id'=>1));
	foreach($sectionList as $section)
	{
		#$section = $node->getSection();
		echo "<li><a href=\"".BASE_URL."/sections/viewSection.php?section_id={$section->getId()}\">";
		echo View::escape($section->getName());
		echo '</a></li>';
	}
?>
</ul>
</div>
<div class="menuBar">
<ul><li><a href="<?php echo BASE_URL; ?>/calendars">Calendars</a></li>
	<li><a href="<?php echo BASE_URL; ?>/documentTypes/documents.php?documentType_id=5">News</a></li>
	<li><a href="<?php echo BASE_URL; ?>/locations">Locations</a></li>
	<li><a href="<?php echo BASE_URL; ?>/community_profile">Community Profile</a></li>
	<li><a href="<?php echo BASE_URL; ?>/documents/az_index.php">A-Z Index</a></li>
	<li><a href="<?php echo BASE_URL; ?>/facets">Facets</a></li>
	<li><form method="get" action="<?php echo BASE_URL; ?>/documents/search.php">
		<fieldset>
			<label for="search">SEARCH</label>
			<input name="search" id="search" />
			<button type="submit" class="search">search</button>
		</fieldset>
		</form>
	</li>
</ul>
</div>
