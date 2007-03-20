<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
	$title = "Media Browser";
	include(APPLICATION_HOME."/includes/xhtmlTransitionalHeader.inc");
?>
<head>
	<meta http-equiv="Content-Type" content="application/xhtml+xml; charset=utf-8" />
	<meta http-equiv="Content-Script-Type" content="text/javascript" />
	<link rel="SHORTCUT ICON" href="/favicon.ico" />
	<style type="text/css" media="screen">
		@import url("<?php echo BASE_URL; ?>/skins/default/skin.css");
	</style>
	<style type="text/css" media="print">@import url("<?php echo BASE_URL; ?>/skins/default/print.css");</style>
	<title><?php echo $title; ?></title>
</head>
<body>
<div class="left sidebar">
	<div><div class="titleBar">Departments</div>
		<ul>
		<?php
			$departments = new DepartmentList();
			$departments->find();
			$url = new URL($_SERVER['PHP_SELF']);
			foreach($departments as $department)
			{
				$url->parameters['department_id'] = $department->getId();
				echo "<li><a href=\"{$url->getURL()}\">$department</a></li>";
			}
		?>
		</ul>
	</div>
</div>
<div id="backendContent">
	<?php
		include FRAMEWORK.'/errorMessages.inc';
		$this->includeBlocks();
	?>
</div>
<?php
	include FRAMEWORK.'/xhtmlFooter.inc';
?>