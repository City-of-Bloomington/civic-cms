<?php
/**
 * @copyright Copyright (C) 2006,2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param string $this->title
 */
	$startTime = microtime(1);
?>
<?xml version="1.0" encoding="UTF-8"?>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="en">
<head>
	<meta http-equiv="Content-Type" content="application/xhtml+xml; charset=utf-8" />
	<meta http-equiv="Content-Script-Type" content="text/javascript" />
	<link rel="SHORTCUT ICON" href="/favicon.ico" />
	<style type="text/css" media="screen">
		@import url("<?php echo BASE_URL; ?>/skins/<?php echo $_SESSION['skin']; ?>/skin.css");
	</style>
	<style type="text/css" media="print">@import url("<?php echo BASE_URL; ?>/skins/<?php echo $_SESSION['skin']; ?>/print.css");</style>
	<script type="text/javascript" src="/functions.js"></script>
	<title><?php echo $this->title; ?></title>
</head>
<body>
