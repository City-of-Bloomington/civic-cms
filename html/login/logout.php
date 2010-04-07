<?php
/**
 * Logs a user out of the system
 *
 * @copyright 2006-2010 City of Bloomington, Indiana
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
session_destroy();
header('Location: '.BASE_URL);
