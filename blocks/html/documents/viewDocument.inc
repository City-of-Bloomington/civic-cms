<?php
/**
 * @copyright Copyright (C) 2006,2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param Document $this->document
 * @param Section $this->section
 */

$title = View::escape($this->document->getTitle());

$page = new URL($_SERVER['SERVER_NAME'].$_SERVER['REQUEST_URI']);
if (isset($page->lang)) { unset($page->lang); }
$printURL = $page;
$printURL->format = 'print';
$rss = BASE_URL.'/sections/viewSection.php?format=rss;section_id='.$this->section->getId();
echo "
<div id=\"documentToolbox\">
	<div>
		<ul><li><button type=\"button\" class=\"rss\" onclick=\"document.location.href='$rss';\">RSS</button></li>
			<li><button type=\"button\" class=\"printSmall\" onclick=\"window.open('$printURL');\">Print</button></li>
			<li><form method=\"get\" action=\"{$page->getProtocol()}{$page->getScript()}\">
";
				foreach($page->parameters as $field=>$value)
				{
					echo "<input name=\"$field\" type=\"hidden\" value=\"$value\" />";
				}
echo "
					<select name=\"lang\" onchange=\"this.form.submit();\">
";
					foreach($this->document->getLanguages() as $language)
					{
						$selected = ($language->getCode()==$_SESSION['LANGUAGE']) ? 'selected="selected"' : '';
						echo "<option value=\"{$language->getCode()}\" $selected>{$language->getNative()}</option>";
					}
echo "
					</select>
				</form>
			</li>
		</ul>
	</div>
";

if (isset($_SESSION['USER']) && $this->document->permitsEditingBy($_SESSION['USER']))
{
	$return_url = new URL($_SERVER['SERVER_NAME'].$_SERVER['REQUEST_URI']);

	#----------------------------------------------------------------
	# Edit Button
	#----------------------------------------------------------------
	$url = new URL(BASE_URL.'/documents/updateDocument.php');
	$url->document_id = $this->document->getId();
	$url->return_url = $return_url;
	$editButton = "
	<button type=\"button\"
			class=\"editSmall\"
			onclick=\"document.location.href='$url';\"
			onmouseover=\"FRAMEWORK.popupTooltip('Edit this document');\"
			onmouseout=\"FRAMEWORK.hideTooltip();\">
		Edit
	</button>
	";

	#----------------------------------------------------------------
	# Delete Button
	# Documents that are homepages should not be deleted.
	# At least until we can work out a way to choose new homepages for sections
	#----------------------------------------------------------------
	$deleteURL = new URL(BASE_URL.'/documents/deleteDocument.php?document_id='.$this->document->getId());
	if (!$this->document->isHomepage())
	{
		$deleteButton = "
		<button type=\"button\"
				class=\"delete\"
				onclick=\"FRAMEWORK.deleteConfirmation('$deleteURL');\"
				onmouseover=\"FRAMEWORK.popupTooltip('Delete this document');\"
				onmouseout=\"FRAMEWORK.hideTooltip();\">
			Delete
		</button>
		";
	}
	else { $deleteButton = ''; }

	#----------------------------------------------------------------
	# Subscription Notifications Button
	#----------------------------------------------------------------
	$url = new URL(BASE_URL.'/sections/subscriptions/notify.php');
	$url->document_id = $this->document->getId();
	$url->return_url = $return_url;
	$notifyButton = "
	<button type=\"button\"
			class=\"notify\"
			onclick=\"document.location.href='$url';\"
			onmouseover=\"FRAMEWORK.popupTooltip('Notify Subscribers.  This will send an email out to all people subscribed to this section.');\"
			onmouseout=\"FRAMEWORK.hideTooltip();\">
		Notify
	</button>
	";

	#----------------------------------------------------------------
	# Document Watch Button
	#----------------------------------------------------------------
	if($_SESSION['USER']->hasWatch($this->document))
	{
		$watchButton = "
		<button type=\"button\"
				class=\"unwatch\"
				onclick=\"document.location.href='".BASE_URL."/documents/removeWatch.php?document_id={$this->document->getId()};return_url=$return_url';\"
				onmouseover=\"FRAMEWORK.popupTooltip('Stop watching this page.  You will no longer receive emails when changes are made to this page.');\"
				onmouseout=\"FRAMEWORK.hideTooltip();\">
			Unwatch
		</button>
		";
	}
	else
	{
		$watchButton = "
		<button type=\"button\"
				class=\"watch\"
				onclick=\"document.location.href='".BASE_URL."/documents/addWatch.php?document_id={$this->document->getId()};return_url=$return_url';\"
				onmouseover=\"FRAMEWORK.popupTooltip('Watch this page.  You will receive emails when changes are made to this page.');\"
				onmouseout=\"FRAMEWORK.hideTooltip();\">
			Watch
		</button>
		";
	}

	echo "<div>$editButton $deleteButton $notifyButton</div>";
}
echo "
	<h1>$title</h1>
</div>
";


# We want to render PHP code harmless in the markup, unless
# it's specifically enabled by some Webmaster
if ($this->document->getContent($_SESSION['LANGUAGE']))
{
	$lang = $_SESSION['LANGUAGE'];
}
else
{
	# Try and find a language we do have, English first
	if ($this->document->getContent('en')) { $lang = 'en'; }
	else
	{
		foreach($this->document->getContent() as $l=>$content)
		{
			if ($content)
			{
				$lang = $l;
				break;
			}
		}
	}
}
# If we still couldn't find a language, then somehow, this document
# has no content.  Just display a blank page in English
if (!isset($lang)) { $lang = 'en'; }


if ($this->document->PHPIsEnabled())
{
	include $this->document->getContentFilename($lang);
}
else
{
	echo WikiMarkup::parse($this->document->getContent($lang));
}
