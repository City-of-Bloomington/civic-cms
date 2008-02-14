<?php
/**
 * @copyright Copyright (C) 2008 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param Document $this->document
 * @param srting $this->return_url
 */
?>
<h1>Notify Subscribers</h1>
<form method="post" action="<?php echo $_SERVER['PHP_SELF']; ?>">
<fieldset><legend>Message</legend>
	<input name="document_id" type="hidden" value="<?php echo $this->document->getId(); ?>" />
	<input name="return_url" type="hidden" value="<?php echo $this->return_url; ?>" />

	<div>
		<textarea name="message" rows="3" cols="60"></textarea>
	</div>

	<div>
		<button type="submit" class="submit">Submit</button>
		<a class="cancel" href="<?php echo $this->return_url; ?>">Cancel</a>
	</div>
</form>
