<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
	class Attachment extends Media
	{
		public function __construct($media_id=null)
		{
			parent::__construct($media_id);

			$this->media_type = 'attachment';
		}
	}
?>