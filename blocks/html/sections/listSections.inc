<?php
/**
 * @copyright Copyright (C) 2006,2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param Section $this->section
 */
	function listEditableSections($section)
	{
		foreach($section->getChildren() as $placement=>$section)
		{
			$name = View::escape($section->getName());
			if (userHasRole('Webmaster'))
			{
				$buttons = "
				<button type=\"button\" class=\"editSmall\" onclick=\"document.location.href='".BASE_URL."/sections/updateSection.php?section_id={$section->getId()}';\">Edit</button>
				<button type=\"button\" class=\"deleteSmall\" onclick=\"FRAMEWORK.deleteConfirmation('".BASE_URL."/sections/deleteSection.php?section_id={$section->getId()}');\">Delete</button>
				<button type=\"button\" class=\"widgets\" onclick=\"document.location.href='".BASE_URL."/sections/updateWidgets.php?section_id={$section->getId()}';\">Widgets</button>
				";

			}
			echo "
			<li><a href=\"".BASE_URL."/documents/viewDocument.php?document_id={$section->getDocument_id()}\">
				$name</a>
				$buttons
			";

			if ($section->hasChildren())
			{
				echo "<ul>";
				listEditableSections($section);
				echo "</ul>";
			}

			echo "</li>";
		}
	}
?>
<div class="interfaceBox">
<?php
	if (userHasRole('Webmaster'))
	{
		echo "
		<div class=\"contextualMenu\">
			<span class=\"title\">Sections</span>
			<ul><li><a href=\"".BASE_URL."/sections/addSection.php\">Add</a></li>
				<li><a href=\"".BASE_URL."/sections/rearrangeSections.php\">Rearrange</a></li>
			</ul>
		</div>
		";
	}
	else { echo "<div class=\"titleBar\">Sections</div>"; }
?>
	<ul class="expandable">
		<?php listEditableSections($this->section); ?>
	</ul>
</div>
<script type="text/javascript">
/*
http://www.kryogenix.org/code/browser/aqlists/

Stuart Langridge, November 2002
sil@kryogenix.org
*/
addEvent(window, "load", makeTreesC);

function makeTreesC()
{
	uls = document.getElementsByTagName("ul");
	for (i=0; i<uls.length; i++)
	{
		if (uls[i].nodeName == "UL" && uls[i].className == "expandable") { processULELC(uls[i]); }
	}
}

function processULELC(ul)
{
	if (!ul.childNodes || ul.childNodes.length == 0) return;
	// Iterate LIs
	for (var itemi=0;itemi<ul.childNodes.length;itemi++)
	{
		var item = ul.childNodes[itemi];
		if (item.nodeName == "LI")
		{
			// Iterate things in this LI
			var a;
			var subul = '';
			for (j=0; j<item.childNodes.length; j++)
			{
				var sitem = item.childNodes[j];
				switch (sitem.nodeName)
				{
					case "A": a = sitem; break;
					case "UL": subul = sitem;
								processULELC(subul);
								break;
				}
			}
			if (subul) { associateELC(a,subul); }
			else { a.parentNode.className = "bullet"; }
		}
	}
}

function associateELC(a,ul)
{
	if (a.parentNode.className.indexOf('open') == -1) { a.parentNode.className = 'closed'; }
	a.onclick = function()
	{
		this.parentNode.className = (this.parentNode.className=='open') ? "closed" : "open";
		return false;
	}
}

/*              Utility functions                    */

function addEvent(obj, evType, fn)
{
	/* adds an eventListener for browsers which support it
		Written by Scott Andrew: nice one, Scott */
	if (obj.addEventListener)
	{
		obj.addEventListener(evType, fn, false);
		return true;
	}
	else if (obj.attachEvent)
	{
		var r = obj.attachEvent("on"+evType, fn);
		return r;
	}
	else { return false; }
}
</script>
