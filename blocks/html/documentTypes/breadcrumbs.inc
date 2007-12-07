<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param DocumentType $this->documentType (optional)
 */
?>
<div class="breadcrumbs">
<ul><li><a href="<?php echo BASE_URL; ?>">Home</a></li>
	<?php
		if(isset($this->documentType))
		{
			$name = View::escape(Inflector::pluralize($this->documentType));
			echo "<li>$name</li>";
		}
	?>
</div>
