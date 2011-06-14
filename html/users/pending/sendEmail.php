<?php
/**
 * @copyright Copyright (C) 2008 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param GET email
 */
# This is disabled for now
Header('Location: '.BASE_URL);
/*
$pending = new PendingUser($_GET['email']);

$instructions = new Block('users/pending/activationInstructions.inc');
$instructions->pendingUser = $pending;

$email = new Template('email','text');
$email->blocks[] = $instructions;

$pending->notify($email->render());

Header('Location: view.php?email='.$pending->getEmail());
*/
