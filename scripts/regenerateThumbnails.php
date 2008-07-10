<?php
/**
 * @copyright Copyright (C) 2008 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
include '../configuration.inc';

$images = new ImageList();
$images->find();
foreach($images as $image)
{
	$file = "{$image->getDirectory()}/{$image->getInternalFilename()}";
	Image::resize($file,'thumbnail');
	echo "$file\n";
}
