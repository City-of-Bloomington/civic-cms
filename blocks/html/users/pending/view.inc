<?php
/**
 * @copyright Copyright (C) 2008 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param PendingUser $this->pendingUser
 */
?>
<p>Your account is pending.  You should received an email with instructions on how to
activate your account.  If you have not received this email, we can
<a href="<?php echo BASE_URL; ?>/users/pending/sendEmail.php?email=<?php echo $this->pendingUser->getEmail(); ?>">resend it</a>.</p>

<p>After you activate you account you can set up your preferences and
select the notifications you'd like to receive.</p>
