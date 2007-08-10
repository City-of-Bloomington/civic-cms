<?php
/**
 * @copyright Copyright (C) 2006,2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param Document $this->document
 */
?>
<script type="text/javascript">
	function toggleSubsections(button)
	{
		var subsections = document.getElementById('subsections');
		if (subsections.style.display === 'none')
		{
			// Display the subsections
			subsections.style.display = '';
			button.class = 'less';
			button.firstChild.nodeValue = 'Less Sections';
		}
		else
		{
			// Hide the subsections
			subsections.style.display = 'none';
			button.class = 'more';
			button.firstChild.nodeValue = 'More Sections';
		}
	}
</script>
<div><button type="button" class="more" onclick="toggleSubsections(this);">More Sections</button></div>
<div id="subsections" style="display:none;">
<?php
	foreach($this->document->getSections() as $section)
	{
		$name = View::escape($section->getName());
		echo "
		<div class=\"interfaceBox\">
			<div class=\"titleBar\">$name Sections</div>
			<ul>
		";
		foreach($section->getChildren() as $child)
		{
			$name = View::escape($child->getName());
			echo "<li><a href=\"".BASE_URL."/sections/viewSection.php?section_id={$child->getName()}\">$name</a></li>\n";
		}
		echo "
			</ul>
		</div>
		";
	}
?>
</div>
