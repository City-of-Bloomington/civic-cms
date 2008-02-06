<?php
/**
 * @copyright Copyright (C) 2008 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param PendingUser $this->pendingUser
 */
?>
<p>Your account is pending.  You should received an email with instructions on how to
activate your account.  If you have not received this email, we can
<a href="<?php echo BASE_URL; ?>/users/pending/sendEmail.php?email=<?php echo $this->pendingUser->getEmail(); ?>">resend it</a>.</p>