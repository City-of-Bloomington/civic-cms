<?php
/**
 * @copyright Copyright (C) 2008 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param PendingUser $this->pendingUser
 */
$url = new URL(BASE_URL.'/users/pending/activate.php');
$url->hash = $this->pendingUser->getHash();

echo "
You have requested an account with the City of Bloomington's website.

Go to this URL to activate your account:
$url

";
