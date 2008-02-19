<?php
/**
 * @copyright Copyright (C) 2008 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param string $this->message
 * @param array $this->documents
 */
echo "{$this->message}\n\n";
foreach($this->documents as $document)
{
echo "
{$document->getTitle()}
{$document->getURL()}

";
}
