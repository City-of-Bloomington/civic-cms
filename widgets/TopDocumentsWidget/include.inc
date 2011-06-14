<?php
/**
 * @copyright Copyright (C) 2008 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param DocumentType $this->documentType
 */
	$name = View::escape(Inflector::pluralize($this->documentType->getType()));
?>
<div class="widget">
	<h1>Top <?php echo $name; ?></h1>
	<ol>
	<?php
		$hits = DocumentAccessLog::getTopDocuments(7,$this->documentType->getId());
		foreach($hits as $hit)
		{
			$title = View::escape($hit['document']->getTitle());
			echo "<li><a href=\"{$hit['document']->getURL()}\">$title</a></li>";
		}
	?>
	</ol>
	<div class="viewMoreLink">
		<a href="<?php echo BASE_URL; ?>/documentTypes/documents.php?documentType_id=<?php echo $this->documentType->getId(); ?>">
			More <?php echo $name; ?>
		</a>
	</div>
</div>
