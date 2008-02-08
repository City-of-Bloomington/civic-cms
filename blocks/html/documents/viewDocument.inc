<?php
/**
 * @copyright Copyright (C) 2006,2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param Document $this->document
 * @param Section $this->section
 */
if (isset($_SESSION['USER']) && $this->document->permitsEditingBy($_SESSION['USER']))
{
	$url = new URL(BASE_URL.'/documents/updateDocument.php');
	$url->parameters['document_id'] = $this->document->getId();
	$url->parameters['return_url'] = "http://$_SERVER[SERVER_NAME]$_SERVER[REQUEST_URI]";
	$editButton = "<button type=\"button\" class=\"editSmall\" onclick=\"document.location.href='$url';\">Edit</button>";
}
else { $editButton = ""; }

$title = View::escape($this->document->getTitle());

$page = new URL("http://$_SERVER[SERVER_NAME]$_SERVER[REQUEST_URI]");
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
	<h1>$editButton $title</h1>
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
