<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param Document $this->document
 * @param URL $this->return_url
 * @param int $this->instance_id
 */
?>
<form id="documentForm" method="post" action="<?php echo $_SERVER['PHP_SELF']; ?>">
	<fieldset><legend>Current Sections</legend>
	<p>This Document is currently showing up in these sections on the site.</p>
		<input type="hidden" name="tab" id="tab" value="facets" />
		<input type="hidden" name="action" id="action" value="next" />
		<input type="hidden" name="return_url" value="<?php echo $this->return_url; ?>" />
		<input type="hidden" name="instance_id" value="<?php echo $this->instance_id; ?>" />
		<input type="hidden" name="continue" id="continue" value="true" />

		<input type="hidden" name="section[remove]" id="section-remove" />
		<?php
			$previousIds = array();
			if (count($this->document->getSections()))
			{
				echo '<ul>';
				foreach($this->document->getSectionDocuments() as $sectionDocument)
				{
					$section = $sectionDocument->getSection();
					$previousIds[] = $section->getId();
					$name = View::escape($section->getName());

					echo "
					<li><button type=\"button\" class=\"deleteSmall\" onclick=\"removeSection({$sectionDocument->getId()});\">Delete</button>
						<a href=\"{$section->getURL()}\">$name</a>
					";
					if ($sectionDocument->isFeatured())
					{
						# Print the button to unfeatured it
						echo "
						(featured)
						<button type=\"button\" class=\"unfeature\" onclick=\"updateSectionDocument({$sectionDocument->getId()},0);\">Don't feature</button>
						";
					}
					else
					{
						# Print the button to feature it
						echo "<button type=\"button\" class=\"feature\" onclick=\"updateSectionDocument({$sectionDocument->getId()},1);\">Feature It</button>";
					}
				}
				echo '</ul';

			}
		?>
	</fieldset>

	<fieldset><legend>Add this document to a section</legend>
		<input name="section[add]" id="section-add" type="hidden" />
	<?php
		if ($this->document->getId())
		{
			echo '<p>You can choose from the following sections, to make this document show up there.</p>';

			$tree = array();

			# Load all the sections the user is allowed to edit
			$list = new SectionList();
			if (userHasRole(array('Administrator','Webmaster'))) { $list->find(); }
			else { $list->find(array('department_id'=>$_SESSION['USER']->getDepartment_id())); }

			#echo "<ul>";
			foreach($list as $section)
			{
				#echo "<li>{$section->getId()}:{$section->getName()}";
				$ancestors = $section->getAncestors();
				foreach($ancestors as $vector)
				{
					$key = '';
					#$c = count($vector);
					#echo "<p>{$section->getName()} has $c ancestors</p>";
					#echo "<ul>";
					foreach($vector as $id=>$s)
					{
						$key.= "$id-";
					#	echo "<li>$id:{$s->getName()}</li>";
					}
					$tree[$key]['vector'] = $vector;
					$tree[$key]['sections'][$section->getId()] = $section->getName();
					#echo "</ul>";
				}
				#echo "</li>";
			}
			#echo "</ul>";
			#print_r($tree);

			foreach($tree as $key=>$vector)
			{
				foreach($vector['sections'] as $id=>$s)
				{
					if (!in_array($id,$previousIds))
					{
						$previousIds[] = $id;
					}
					else
					{
						# Clear this entry out of the tree
						unset($tree[$key]['sections'][$id]);
					}
				}
			}

			# Now just display everything left in the tree
			foreach($tree as $key=>$vector)
			{
				if (count($vector['sections']))
				{
					echo "<div class=\"interfaceBox\"><div class=\"breadcrumbs\"><ul>";
					foreach($vector['vector'] as $p)
					{
						$name = View::escape($p->getName());
						echo "<li>$name</li>";
					}
					echo "</ul></div>";

					echo "<ul>";
					foreach($vector['sections'] as $id=>$s)
					{
						$s = View::escape($s);
						echo "
						<li><button type=\"button\" class=\"addSmall\" onclick=\"addSection($id);\">Add</button>
							$s
						</li>
						";
					}
					echo "</ul></div>";
				}

			}
		}
		else
		{
			echo '<p>You cannot assign sections until the document is saved.</p>';
		}
	?>
	</fieldset>
</form>
<script type="text/javascript">
function addSection(section_id)
{
	document.getElementById('section-add').value = section_id;
	FRAMEWORK.processTabbedForm('documentForm','sections','next');
}
function removeSection(sectionDocument_id)
{
	document.getElementById('section-remove').value = sectionDocument_id;
	FRAMEWORK.processTabbedForm('documentForm','sections','next');
}

var updateRequest = FRAMEWORK.getXMLHttpRequestObject();
function updateSectionDocument(sectionDocument_id,featured)
{
	updateRequest.open("get","<?php echo BASE_URL; ?>/documents/updateSectionDocument.php?sectionDocument_id="+sectionDocument_id+";featured="+featured);
	updateRequest.onreadystatechange = handleUpdateResult;
	updateRequest.send(null);
}

function handleUpdateResult()
{
	if (updateRequest.readyState == 4)
	{
		FRAMEWORK.processTabbedForm('documentForm','sections','next');
	}
}

</script>
