<?php
/**
 * @copyright Copyright (C) 2008 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param SectionList $this->sectionList
 */
?>
<div id="pageTitle">
	<div class="breadcrumbs">
		<ul><li><a href="<?php echo BASE_URL; ?>">Home</a></li>
			<li><a href="<?php echo BASE_URL; ?>/subscriptions">Subscriptions</a></li>
		</ul>
	</div>
	<h1>Subscriptions</h1>
</div>
<form method="post" action="<?php echo $_SERVER['PHP_SELF']; ?>">
<fieldset><legend>Manage your subscriptions</legend>
<table>
<?php
	$return_url = new URL($_SERVER['SERVER_NAME'].$_SERVER['REQUEST_URI']);
	foreach($this->sectionList as $section)
	{
		$name = View::escape($section->getName());

		$subscribeButton = '';
		$checked = $_SESSION['USER']->hasSubscription($section) ? 'checked="checked"' : '';
		$subscribeButton = "<input name=\"section[{$section->getId()}]\" id=\"section-{$section->getId()}\" type=\"checkbox\" $checked />";

		#------------------------------------------------
		# Notify Button
		#------------------------------------------------
		$notifyButton = '';
		if ($section->permitsPostingBy($_SESSION['USER']))
		{
			$url = new URL(BASE_URL.'/sections/subscriptions/notify.php');
			$url->section_id = $section->getId();
			$url->return_url = $return_url;
			$notifyButton = "
			<a class=\"notify button\"
				href=\"$url\"
				onmouseover=\"FRAMEWORK.popupTooltip('Notify Subscribers.  This will send an email out to all people subscribed to this section.');\"
				onmouseout=\"FRAMEWORK.hideTooltip();\">
				Notify
			</a>
			";
		}
		echo "
		<tr><td>$subscribeButton</td>
			<td>$notifyButton</td>
			<td><label for=\"section-{$section->getId()}\">
					<a href=\"{$section->getURL()}\">$name</a>
				</label>
			</td>
		</tr>
		";
	}
?>
</table>
<button type="submit" class="save">Save</button>
</fieldset>
</form>
