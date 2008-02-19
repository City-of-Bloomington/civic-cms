<?php
/**
 * @copyright Copyright (C) 2008 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param string $this->message
 */
?>
<h1>Success</h1>
<p>Notifications were sent out to the subscribers</p>
<p>Here is a copy of the message that was sent out:</p>
<pre>
<code>
<?php echo View::escape($this->message); ?>
</code>
</pre>