<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
	class AttachmentList extends MediaList
	{
		public function __construct($fields=null,$sort=null,$limit=null,$groupBy=null)
		{
			# We want to make sure to tell MediaList to only find
			# attachments.  But the mediaList will execute a find
			# if we set $fields in the contructor
			if (is_array($fields))
			{
				# We've got $fields we're looking for, go ahead and
				# let MediaList find them.
				$fields['media_type'] = 'attachment';
				parent::__construct($fields,$sort);
			}
			else
			{
				# Don't do a find quite yet.  Wait until it's called explicitly
				parent::__construct(null,$sort);
			}
		}

		public function find($fields=null,$sort=null,$limit=null,$groupBy=null)
		{
			$fields['media_type'] = 'attachment';
			parent::find($fields,$sort,$limit,$groupBy);
		}

		# Override the generic MediaList so we return Attachments
		protected function loadResult($key) { return new Attachment($this->list[$key]); }
	}
?>