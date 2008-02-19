<?php
/**
 * @copyright Copyright (C) 2008 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param GET email
 */
$pending = new PendingUser($_GET['email']);

$instructions = new Block('users/pending/activationInstructions.inc');
$instructions->pendingUser = $pending;

$email = new Template('email','text');
$email->blocks[] = $instructions;

$pending->notify($email->render());

Header('Location: view.php?email='.$pending->getEmail());
