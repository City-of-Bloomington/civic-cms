<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param DocumentType $this->documentType (optional)
 */
?>
<div id="breadcrumbs">
<ul><li><a href="<?php echo BASE_URL; ?>">Home</a></li>
	<?php
		if(isset($this->documentType))
		{
			$name = View::escape(Inflector::pluralize($this->documentType));
			echo "<li><a href=\"".BASE_URL."/documentTypes/documents.php?documentType_id={$this->documentType->getId()}\">$name</a></li>";
		}
		else
		{
			echo "<li><a href=\"".BASE_URL."/documentTypes\">Document Types</a></li>";
		}
	?>
</div>
