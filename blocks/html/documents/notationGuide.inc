<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
?>
<h1>Links</h1>
<table>
<tr><th colspan="2">Link to a document in the site</th></tr>
<tr><td><ul><li>[pagetitle]</li>
			<li>[document_id]</li>
			<li>[page_title#anchor]</li>
			<li>[document_id#anchor]</li>
		</ul>
		Examples
		<ul><li>[Information and Technology Services]</li>
			<li>[2]</li>
		</ul>
	</td>
	<td><p>Creates an internal link to the specified page.  You can
		specify a page either by Title or by ID number.
		Appending the optional '#' sign followed by an anchor name will lead
		into a specific bookmarked point of the desired page.</p>
	</td>
</tr>
<tr><th colspan="2">Link to an external site</th></tr>
<tr><td><ul><li>[url]</li></ul>
		Example
		<ul><li>[http://www.google.com]</li></ul>
	</td>
	<td><p>Creates a link to the specified website</p></td>
</tr>

<tr><th colspan="2">Link to a file</th></tr>
<tr><td><ul><li>[file:filename.ext]</li>
			<li>[file:media_id]</li>
		</ul>
		Examples
		<ul><li>[file:apartmentrow.pdf]</li>
			<li>[file:1]</li>
		</ul>
	</td>
	<td><p>Creates a link to a file that has been uploaded to the site.
			The file can be of any type: image, PDF, Word Doc, etc.
			The link will allow the user to download the file.</p>
		<p>Note: in the case of images, this will not display the image.
			If you want the image displayed, see the syntax for either
			[image:] or [thumbnail:]</p>
	</td>
</tr>

<tr><th colspan="2">Link to an email address</th></tr>
<tr><td><ul><li>[email:address]</li></ul>
		Example
		<ul><li>[email:inghamn@bloomington.in.gov]</li></ul>
	</td>
	<td><p>Creates a mailto: link to the address provided.</p></td>
</tr>

<tr><th colspan="2">Link to a Calendar</th></tr>
<tr><td><ul><li>[calendar:title]</li>
			<li>[calendar:ID]</li>
		</ul>
		Examples
		<ul><li>[calendar:Government]</li>
			<li>[calendar:1]</li>
		</ul>
	</td>
	<td><p>Creates a link to the calendar page.  You can provide either the name
			or the ID number for the calendar.</p>
	</td>
</tr>

<tr><th colspan="2">Link to an Event</th></tr>
<tr><td><ul><li>[event:title]</li>
			<li>[event:ID]</li></ul>
		Examples
		<ul><li>[event:Christmas Day]</li>
			<li>[event:88]</li>
		</ul>
	</td>
	<td><p>Creates a link to an event.  You can provide either the title
			or the ID number of the event.</p>
	</td>
</tr>

<tr><th colspan="2">Link to a Location</th></tr>
<tr><td><ul><li>[location:name]</li>
			<li>[location:ID]</li>
		</ul>
		Examples
		<ul><li>[location:City Hall - Showers Common]</li>
			<li>[location:129]</li>
		</ul>
	</td>
	<td><p>Creates a link to a Location. You can provide either the name
			or ID number for the Location.</p>
	</td>
</tr>


<tr><th colspan="2">Link to a Location Group</th></tr>
<tr><td><ul><li>[locationGroup:name]</li>
			<li>[locationGroup:ID]</li>
		</ul>
		Examples
		<ul><li>[locationGroup:Parks]</li>
			<li>[locationGroup:1]</li>
		</ul>
	</td>
	<td><p>Creates a link to a Location Group.  You can provide either the
		name or the ID number for the Location Group.</p>
	</td>
</tr>

<tr><th colspan="2">Link to a Facet</th></tr>
<tr><td><ul><li>[facet:name]</li>
			<li>[facet:ID]</li>
		</ul>
		Examples
		<ul><li>[facet:Business Guide]</li>
			<li>[facet:28]</li>
		</ul>
	</td>
	<td><p>Creates a link to a list of documents for a Facet.  You can provide
		either the name or the ID number for the Facet.</p>
	</td>
</tr>

</table>


<h1>Images</h1>
<p>Use this syntax to display an image in the body of a document.</p>
<table>
<tr><th colspan="2">Display an Image</th></tr>
<tr><td><ul><li>[image:filename.ext]</li>
			<li>[image:ID]</li>
		</ul>
		Examples
		<ul><li>[image:its_group_photo_200510.jpg]</li>
			<li>[image:2]</li>
		</ul>
	</td>
	<td><p>This will display the image.</p></td>
</tr>

<tr><th colspan="2">Display a Thumbnail for an image.</th></tr>
<tr><td><ul><li>[thumbnail:filename.ext]</li>
			<li>[thumbnail:ID]</li>
		</ul>
		Examples
		<ul><li>[thumbnail:its_group_photo_200510.jpg]</li>
			<li>[thumbnail:2]</li>
		</ul>
	</td>
	<td><p>This will display a small version of the image.</p></td>
</tr>
</table>
