<?php
/**
 * @copyright Copyright (C) 2008 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
class AlertList extends PDOResultIterator
{
	public function __construct($fields=null)
	{
		$this->deleteExpiredAlerts();

		$this->select = 'select alerts.id as id from alerts';
		if (is_array($fields)) $this->find($fields);
	}

	public function find($fields=null,$sort='startTime',$limit=null,$groupBy=null)
	{
		$this->sort = $sort;
		$this->limit = $limit;
		$this->groupBy = $groupBy;

		$options = array();
		if (isset($fields['id'])) { $options[] = "id='$fields[id]'"; }
		if (isset($fields['title'])) { $options[] = "title='$fields[title]'"; }
		if (isset($fields['alertType_id'])) { $options[] = "alertType_id='$fields[alertType_id]'"; }
		if (isset($fields['startTime'])) { $options[] = "startTime='$fields[startTime]'"; }
		if (isset($fields['endTime'])) { $options[] = "endTime='$fields[endTime]'"; }
		if (isset($fields['url'])) { $options[] = "url='$fields[url]'"; }
		if (isset($fields['text'])) { $options[] = "text='$fields[text]'"; }

		if (isset($fields['alertType']))
		{
			$this->joins.= ' left join alertTypes on alerts.alertType_id=alertTypes.id';
			if ($fields['alertType'] instanceof AlertType)
			{
				$options[] = "alertTypes.name='{$fields['alertType']->getName()}'";
			}
			else { $options[] = "alertTypes.name='$fields[alertType]'"; }
		}


		# Finding on fields from other tables required joining those tables.
		# You can add fields from other tables to $options by adding the join SQL
		# to $this->joins here

		$this->populateList($options);
	}

	public function deleteExpiredAlerts()
	{
		$PDO = Database::getConnection();
		$PDO->query('delete from alerts where endTime<now()');
	}

	public static function deleteWeatherAlerts()
	{
		$PDO = Database::getConnection();
		$type = new AlertType('Weather');
		$query = $PDO->prepare('delete from alerts where alertType_id=?');
		$query->execute(array($type->getId()));
	}

	protected function loadResult($key) { return new Alert($this->list[$key]); }
}
