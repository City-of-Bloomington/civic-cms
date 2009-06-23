<?php
/**
 * @copyright Copyright (C) 2008 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
	$title = View::escape($this->title);
	$content = WikiMarkup::parse($this->content);
?>
<div class="widget <?php echo $this->class; ?>">
	<h1><?php echo $title; ?></h1>
	<?php echo $content; ?>
</div>
