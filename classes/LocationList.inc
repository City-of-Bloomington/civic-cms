<?php
/**
 * @copyright Copyright (C) 2006,2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
	class LocationList extends PDOResultIterator
	{

		public function __construct($fields=null,$sort=null,$limit=null,$groupBy=null)
		{
			$this->select = "select distinct locations.id as id from locations";
			if (is_array($fields)||$sort||$limit||$groupBy)
			{
				$this->find($fields,$sort,$limit,$groupBy);
			}
		}


		public function find($fields=null,$sort="id",$limit=null,$groupBy=null)
		{
			$this->sort = $sort;
			$this->limit = $limit;
			$this->groupBy = $groupBy;

			$options = array();
			if (isset($fields['id'])) { $options[] = "id='$fields[id]'"; }
			if (isset($fields['name'])) { $options[] = "name='$fields[name]'"; }
			if (isset($fields['locationType_id'])) { $options[] = "locationType_id='$fields[locationType_id]'"; }
			if (isset($fields['address'])) { $options[] = "address='$fields[address]'"; }
			if (isset($fields['description'])) { $options[] = "description='$fields[description]'"; }
			if (isset($fields['directions'])) { $options[] = "directions='$fields[directions]'"; }
			if (isset($fields['latitude'])) { $options[] = "latitude='$fields[latitude]'"; }
			if (isset($fields['longitude'])) { $options[] = "longitude='$fields[longitude]'"; }
			if (isset($fields['department_id'])) { $options[] = "department_id='$fields[department_id]'"; }


			# Finding on fields from other tables required joining those tables.
			# You can add fields from other tables to $options by adding the join SQL
			# to $this->joins here
			if (array_key_exists('locationGroup_id',$fields))
			{
				$this->joins.= ' left join locationGroup_locations on id=location_id';
				$options[] = $fields['locationGroup_id'] ? "locationGroup_id='$fields[locationGroup_id]'" : "locationGroup_id is null";
			}

			$this->populateList($options);
		}


		protected function loadResult($key) { return new Location($this->list[$key]); }
	}
?>