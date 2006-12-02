<?php
/**
 * @copyright Copyright (C) 2006 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 */
	class Watch
	{
		private $document_id;
		private $user_id;

		private $document;
		private $user;

		public function __construct($document,$user)
		{
			if (is_numeric($document)) { $this->document_id = $document; }
			else
			{
				$this->document_id = $document->getId();
				$this->document = $document;
			}
			if (is_numeric($user)) { $this->user_id = $user; }
			else
			{
				$this->user_id = $user->getId();
				$this->user = $user;
			}
		}

		public function notify()
		{
			$to = $this->getUser()->getEmail();
			$headers = "From: ".ADMINISTRATOR_EMAIL;
			$message = "Document: {$this->getDocument_id()} has been updated.\n";
			mail($to,APPLICATION_NAME." watch list",$message,$headers);
		}

		public function getDocument_id() { return $this->document_id; }
		public function getUser_id() { return $this->user_id; }
		public function getDocument()
		{
			if (!$this->document) { $this->document = new Document($this->document_id); }
			return $this->document;
		}
		public function getUser()
		{
			if (!$this->user) { $this->user = new User($this->user_id); }
			return $this->user;
		}

		public function setDocument_id($id) { $this->document_id = $id; }
		public function setUser_id($id) { $this->user_id = $id; }
		public function setDocument($document) { $this->document_id = $document->getId(); $this->document = $document; }
		public function setUser($user) { $this->user_id = $user->getId(); $this->user = $user; }
	}
?>