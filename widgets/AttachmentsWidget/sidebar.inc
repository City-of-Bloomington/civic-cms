<?php
/**
 * @copyright Copyright (C) 2007-2008 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param Document $this->document
 */
if (isset($this->document) && count($this->document->getAttachments()))
{
	echo "
	<div class=\"attachments widget\">
		<h1>Attachments</h1>
		<ul>
	";
	foreach($this->document->getAttachments() as $attachment)
	{
		echo "
			<li>
				<a href=\"{$attachment->getURL()}\"
					class=\"{$attachment->getExtension()}\"
					onClick=\"_gaq.push(['_trackEvent', 'Sidebar Attachments', '{$attachment->getURL()}']);\">
						{$attachment->getTitle()}
				</a>
			</li>
		";
	}
	echo "
		</ul>
	</div>
	";
}
