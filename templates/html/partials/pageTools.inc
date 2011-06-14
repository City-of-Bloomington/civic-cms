<?php
/**
 * @copyright Copyright (C) 2008 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param Document $this->document
 */
$page = new URL($_SERVER['SERVER_NAME'].$_SERVER['REQUEST_URI']);
if (isset($page->lang)) { unset($page->lang); }
$printURL = clone $page;
$printURL->format = 'print';

$editButton = '';
$deleteButton = '';
$watchButton = '';
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
	<li><a class=\"editSmall button\"
			href=\"$url\"
			onmouseover=\"FRAMEWORK.popupTooltip('Edit this document');\"
			onmouseout=\"FRAMEWORK.hideTooltip();\">
			Edit
		</a>
	</li>
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
		<li><button type=\"button\"
					class=\"deleteSmall\"
					onclick=\"FRAMEWORK.deleteConfirmation('$deleteURL');\"
					onmouseover=\"FRAMEWORK.popupTooltip('Delete this document');\"
					onmouseout=\"FRAMEWORK.hideTooltip();\">
				Delete
			</button>
		</li>
		";
	}

	#----------------------------------------------------------------
	# Document Watch Button
	#----------------------------------------------------------------
	if($_SESSION['USER']->hasWatch($this->document))
	{
		$watchButton = "
		<li><a class=\"unwatch button\"
				href=\"".BASE_URL."/documents/removeWatch.php?document_id={$this->document->getId()};return_url=$return_url\"
				onmouseover=\"FRAMEWORK.popupTooltip('Stop watching this page.  You will no longer receive emails when changes are made to this page.');\"
				onmouseout=\"FRAMEWORK.hideTooltip();\">
				Unwatch
			</a>
		</li>
		";
	}
	else
	{
		$watchButton = "
		<li><a class=\"watch button\"
				href=\"".BASE_URL."/documents/addWatch.php?document_id={$this->document->getId()};return_url=$return_url\"
				onmouseover=\"FRAMEWORK.popupTooltip('Watch this page.  You will receive emails when changes are made to this page.');\"
				onmouseout=\"FRAMEWORK.hideTooltip();\">
				Watch
			</a>
		</li>
		";
	}
}

echo "
<div id=\"pageTools\">
	<ul>$editButton
		$deleteButton
		$watchButton
		<li><button type=\"button\" class=\"printSmall\" onclick=\"window.open('$printURL');\">Print</button></li>
		<li><form method=\"get\" action=\"{$page->getProtocol()}{$page->getScript()}\">
			<fieldset>
";
			foreach($page->parameters as $field=>$value)
			{
				echo "<input name=\"$field\" type=\"hidden\" value=\"$value\" />";
			}
			$disabled = (count($this->document->getLanguages())==1) ? 'disabled="disabled"' : '';
echo "
				<select name=\"lang\" onchange=\"this.form.submit();\" $disabled>
";
				foreach($this->document->getLanguages() as $language)
				{
					$selected = ($language->getCode()==$_SESSION['LANGUAGE']) ? 'selected="selected"' : '';
					echo "<option value=\"{$language->getCode()}\" $selected>{$language->getNative()}</option>";
				}
echo "
				</select>
			</fieldset>
			</form>
		</li>
	</ul>
</div>
";
