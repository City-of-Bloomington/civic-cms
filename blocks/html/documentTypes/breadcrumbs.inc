<?php
/**
 * @copyright Copyright (C) 2007-2008 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param DocumentType $this->documentType (optional)
 */
$title = 'Document Types';
$href = new URL($_SERVER['SERVER_NAME'].$_SERVER['PHP_SELF']);
$href->facetGroup_id = 'none';
if (isset($this->documentType))
{
	$title = View::escape(Inflector::pluralize($this->documentType->getType()));
	$href->documentType_id = $this->documentType->getId();
}
?>
<div id="pageTitle">
	<div class="breadcrumbs">
	<ul><li><a href="<?php echo BASE_URL; ?>">Home</a></li>
		<li><a href="<?php echo $href; ?>"><?php echo $title; ?></a></li>
	</ul>
	</div>
	<h1>
	<?php
		if (userHasRole(array('Administrator','Webmaster')))
		{
			echo "<a class=\"addSmall\" href=\"".BASE_URL."/documentTypes/addDocumentType.php\">Add</a>";
		}
		echo "<a href=\"$href\">$title</a>";
	?>
	</h1>
</div>
