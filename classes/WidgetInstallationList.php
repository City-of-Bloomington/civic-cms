<?php
/**
 * @copyright Copyright (C) 2007-2008 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
class WidgetInstallationList extends PDOResultIterator
{
	public function __construct($fields=null)
	{
		$this->select = 'select widgets.id as id from widgets';
		if (is_array($fields)) $this->find($fields);
	}

	public function find($fields=null,$sort='class',$limit=null,$groupBy=null)
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
		if (isset($fields['class']))
		{
			$options[] = 'class=:class';
			$parameters[':class'] = $fields['class'];
		}
		if (isset($fields['global_panel_id']))
		{
			$options[] = 'global_panel_id=:global_panel_id';
			$parameters[':global_panel_id'] = $fields['global_panel_id'];
		}
		if (isset($fields['global_layout_order']))
		{
			$options[] = 'global_layout_order=:global_layout_order';
			$parameters[':global_layout_order'] = $fields['global_layout_order'];
		}
		if (isset($fields['global_data']))
		{
			$options[] = 'global_data=:global_data';
			$parameters[':global_data'] = $fields['global_data'];
		}
		if (isset($fields['default_panel_id']))
		{
			$options[] = 'default_panel_id=:default_panel_id';
			$parameters[':default_panel_id'] = $fields['default_panel_id'];
		}
		if (isset($fields['default_layout_order']))
		{
			$options[] = 'default_layout_order=:default_layout_order';
			$parameters[':default_layout_order'] = $fields['default_layout_order'];
		}
		if (isset($fields['default_data']))
		{
			$options[] = 'default_data=:default_data';
			$parameters[':default_data'] = $fields['default_data'];
		}


		# Finding on fields from other tables required joining those tables.
		# You can add fields from other tables to $options by adding the join SQL
		# to $this->joins here
		if (isset($fields['section_id']))
		{
			$this->joins = ' left join section_widgets s on w.id=s.widget_id';
			$options[] = 'section_id=:section_id';
			$parameters[':section_id'] = $fields['section_id'];
		}

		if (isset($fields['global_panel']))
		{
			$this->joins = ' left join panels gp on w.global_panel_id=gp.id';
			$options[] = 'gp.div_id=:global_panel';
			$parameters[':global_panel'] = $fields['global_panel'];
		}

		if (isset($fields['default_panel']))
		{
			$this->joins = ' left join panels dp on w.default_panel_id=dp.id';
			$options[] = 'dp.div_id=:default_panel';
			$parameters[':default_panel'] = $fields['default_panel'];
		}

		$this->populateList($options,$parameters);
	}

	protected function loadResult($key) { return new WidgetInstallation($this->list[$key]); }
}
