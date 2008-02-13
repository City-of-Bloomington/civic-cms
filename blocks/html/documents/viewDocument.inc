<?php
/**
 * @copyright Copyright (C) 2006,2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param Document $this->document
 * @param Section $this->section
 */

$title = View::escape($this->document->getTitle());

$page = new URL("http://$_SERVER[SERVER_NAME]$_SERVER[REQUEST_URI]");
if (isset($page->lang)) { unset($page->lang); }
$printURL = $page;
$printURL->format = 'print';
$rss = BASE_URL.'/sections/viewSection.php?format=rss;section_id='.$this->section->getId();

$subscriptionButton = '';
$watch = '';
if (isset($_SESSION['USER']))
{
	$return_url = new URL("http://$_SERVER[SERVER_NAME]$_SERVER[REQUEST_URI]");
	if ($_SESSION['USER']->hasSubscription($this->section))
	{
		$subscriptionButton = "
		<li><button type=\"button\"
					class=\"unsubscribe\"
					onclick=\"document.location.href='".BASE_URL."/sections/subscriptions/unsubscribe.php?section_id={$this->section->getId()};return_url=$return_url';\"
					onmouseover=\"FRAMEWORK.popupTooltip('Unsubscribe to {$this->section->getName()}.  You will no longer receive emails when new things are added.');\"
					onmouseout=\"FRAMEWORK.hideTooltip();\">
				Unsubscribe
			</button>
		</li>
		";
	}
	else
	{
		$subscriptionButton = "
		<li><button type=\"button\"
					class=\"subscribe\"
					onclick=\"document.location.href='".BASE_URL."/sections/subscriptions/subscribe.php?section_id={$this->section->getId()};return_url=$return_url';\"
					onmouseover=\"FRAMEWORK.popupTooltip('Subscribe to {$this->section->getName()}.  You will receive email notices when new things are added to this section.');\"
					onmouseout=\"FRAMEWORK.hideTooltip();\">
				Subscribe
			</button>
		</li>
		";
	}
	if($_SESSION['USER']->hasWatch($this->document))
	{
		$watch = "
		<li><button type=\"button\"
					class=\"unwatch\"
					onclick=\"document.location.href='".BASE_URL."/documents/removeWatch.php?document_id={$this->document->getId()};return_url=$return_url';\"
					onmouseover=\"FRAMEWORK.popupTooltip('Stop watching this page.  You will no longer receive emails when changes are made to this page.');\"
					onmouseout=\"FRAMEWORK.hideTooltip();\">
				Unwatch
			</button>
		</li>
		";
	}
	else
	{
		$watch = "
		<li><button type=\"button\"
					class=\"watch\"
					onclick=\"document.location.href='".BASE_URL."/documents/addWatch.php?document_id={$this->document->getId()};return_url=$return_url';\"
					onmouseover=\"FRAMEWORK.popupTooltip('Watch this page.  You will receive emails when changes are made to this page.');\"
					onmouseout=\"FRAMEWORK.hideTooltip();\">
				Watch
			</button>
		</li>
		";
	}
}
echo "
<div id=\"documentToolbox\">
	<div>
		<ul>$watch
			$subscriptionButton
			<li><button type=\"button\" class=\"rss\" onclick=\"document.location.href='$rss';\">RSS</button></li>
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
	$url = new URL(BASE_URL.'/documents/updateDocument.php');
	$url->parameters['document_id'] = $this->document->getId();
	$url->parameters['return_url'] = "http://$_SERVER[SERVER_NAME]$_SERVER[REQUEST_URI]";
	$editButton = "
	<button type=\"button\"
			class=\"editSmall\"
			onclick=\"document.location.href='$url';\"
			onmouseover=\"FRAMEWORK.popupTooltip('Edit this document');\"
			onmouseout=\"FRAMEWORK.hideTooltip();\">
		Edit
	</button>
	";

	# Documents that are homepages should not be deleted.
	# At least until we can work out a way to choose new homepages for sections
	$deleteButton = $this->document->isHomepage() ? '' : "<button type=\"button\" class=\"delete\" onclick=\"FRAMEWORK.deleteConfirmation('".BASE_URL."/documents/deleteDocument.php?document_id={$this->document->getId()}');\">Delete</button>";

	$url = new URL(BASE_URL.'/sections/subscriptions/notify.php');
	$url->document_id = $this->document->getId();
	$url->return_url = "http://$_SERVER[SERVER_NAME]$_SERVER[REQUEST_URI]";
	$notifyButton = "
	<button type=\"button\"
			class=\"notify\"
			onclick=\"document.location.href='$url';\"
			onmouseover=\"FRAMEWORK.popupTooltip('Notify Subscribers.  This will send an email out to all people subscribed to this section.');\"
			onmouseout=\"FRAMEWORK.hideTooltip();\">
		Notify
	</button>
	";

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
