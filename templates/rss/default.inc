<?php header('Content-type: application/rss+xml'); ?>
<?xml version="1.0" encoding="utf-8" ?>
<rss version="2.0">
<?php
	echo $this->includeBlocks();
?>
</rss>
