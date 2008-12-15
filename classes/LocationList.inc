<?php
/**
 * @copyright Copyright (C) 2006-2008 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
class LocationList extends PDOResultIterator
{
	public function __construct($fields=null)
	{
		$this->select = 'select locations.id as id from locations';
		if (is_array($fields)) $this->find($fields);
	}

	public function find($fields=null,$sort='name',$limit=null,$groupBy=null)
	{
		$this->sort = $sort;
		$this->limit = $limit;
		$this->groupBy = $groupBy;
		$this->joins = '';

		$options = array();
		$parameters = array();
		if (isset($fields['id']))
		{
			$options[] = 'id=:id';
			$parameters[':id'] = $fields['id'];
		}
		if (isset($fields['name']))
		{
			$options[] = 'name=:name';
			$parameters[':name'] = $fields['name'];
		}
		if (isset($fields['locationType_id']))
		{
			$options[] = 'locationType_id=:locationType_id';
			$parameters[':locationType_id'] = $fields['locationType_id'];
		}
		if (isset($fields['address']))
		{
			$options[] = 'address=:address';
			$parameters[':address'] = $fields['address'];
		}
		if (isset($fields['phone']))
		{
			$options[] = 'phone=:phone';
			$parameters[':phone'] = $fields['phone'];
		}
		if (isset($fields['description']))
		{
			$options[] = 'description=:description';
			$parameters[':description'] = $fields['description'];
		}
		if (isset($fields['website']))
		{
			$options[] = 'website=:website';
			$parameters[':website'] = $fields['website'];
		}
		if (isset($fields['content']))
		{
			$options[] = 'content=:content';
			$parameters[':content'] = $fields['content'];
		}
		if (isset($fields['department_id']))
		{
			$options[] = 'department_id=:department_id';
			$parameters[':department_id'] = $fields['department_id'];
		}
		if (isset($fields['handicap_accessible']))
		{
			if ($fields['handicap_accessible']) { $options = "handicap_accessible"; }
			else { $options = "!handicap_accessible"; }
		}

		# Latitude and longitude are being used for calculating distance.  We can't use them
		# for an exact search as well
		/*
		if (isset($fields['latitude']))
		{
			$options[] = 'latitude=:latitude';
			$parameters[':latitude'] = $fields['latitude'];
		}
		if (isset($fields['longitude']))
		{
			$options[] = 'longitude=:longitude';
			$parameters[':longitude'] = $fields['longitude'];
		}
		*/

		# Finding on fields from other tables required joining those tables.
		# You can add fields from other tables to $options by adding the join SQL
		# to $this->joins here
		if (is_array($fields) && array_key_exists('locationGroup_id',$fields))
		{
			$this->joins.= ' left join locationGroup_locations on id=location_id';
			if ($fields['locationGroup_id'])
			{
				$options[] = 'locationGroup_id=:locationGroup_id';
				$parameters[':locationGroup_id'] = $fields['locationGroup_id'];
			}
			else { $options[] = 'locationGroup_id is null'; }
		}

		if ($sort=='distance')
		{
				# Ordering by distance requires giving a point to calculate distance from
				if (isset($fields['latitude']) && isset($fields['longitude']))
				{
				# We're going to modify the SQL to select distance as well as the ID
				# That way, we'll have distance as a field to order by
				$this->select = "select distinct locations.id,
								((latitude-:latA)*(latitude-:latB)*(36./25.)+
								(longitude-:lonA)*(longitude-:lonB)) as distance from locations";
				$options[] = '(latitude is not null and longitude is not null)';
				$parameters[':latA'] = $fields['latitude'];
				$parameters[':latB'] = $fields['latitude'];
				$parameters[':lonA'] = $fields['longitude'];
				$parameters[':lonB'] = $fields['longitude'];
				}
				# Without a point, we can't sort by distance
				else { $sort = 'name'; }
		}

		$this->populateList($options,$parameters);
	}


	protected function loadResult($key) { return new Location($this->list[$key]); }
}
