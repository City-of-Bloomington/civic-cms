<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param GET event_id
 */
	verifyUser();

	$event = new Event($_GET['event_id']);
	if ($event->permitsEditingBy($_SESSION['USER']))
	{
		$event->delete();
	}
	Header('Location: ../calendars');
