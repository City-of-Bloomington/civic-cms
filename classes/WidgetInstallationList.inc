<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 */
	class WidgetInstallationList extends PDOResultIterator
	{

		public function __construct($fields=null,$sort='id')
		{
			$this->select = 'select widgets.id as id from widgets';
			$this->sort = $sort;
			if (is_array($fields)) $this->find($fields);
		}


		public function find($fields=null,$sort='id',$limit=null,$groupBy=null)
		{
			$this->sort = $sort;
			$this->limit = $limit;
			$this->groupBy = $groupBy;

			if (is_array($fields))
			{
				foreach($fields as $key=>$value)
				{
					if (!is_array($value) && !is_object($value)) { $fields[$key] = addslashes($value); }
				}
			}

			$options = array();
			if (isset($fields['id'])) { $options[] = "id='$fields[id]'"; }
			if (isset($fields['class'])) { $options[] = "class='$fields[class]'"; }
			if (isset($fields['isGlobal'])) { $options[] = "isGlobal='$fields[isGlobal]'"; }
			if (isset($fields['global_panel_id'])) { $options[] = "global_panel_id='$fields[global_panel_id]'"; }
			if (isset($fields['global_layout_order'])) { $options[] = "global_layout_order='$fields[global_layout_order]'"; }
			if (isset($fields['global_data'])) { $options[] = "global_data='$fields[global_data]'"; }
			if (isset($fields['isDefault'])) { $options[] = "isDefault='$fields[isDefault]'"; }
			if (isset($fields['default_panel_id'])) { $options[] = "default_panel_id='$fields[default_panel_id]'"; }
			if (isset($fields['default_layout_order'])) { $options[] = "default_layout_order='$fields[default_layout_order]'"; }
			if (isset($fields['default_data'])) { $options[] = "default_data='$fields[default_data]'"; }


			# Finding on fields from other tables required joining those tables.
			# You can add fields from other tables to $options by adding the join SQL
			# to $this->joins here
			if (isset($fields['section_id']))
			{
				$this->joins = ' left join section_widgets s on w.id=s.widget_id';
				$options[] = "section_id='$fields[section_id]'";
			}

			if (isset($fields['global_panel']))
			{
				$this->joins = ' left join panels gp on w.global_panel_id=gp.id';
				$options[] = "gp.div_id='$fields[global_panel]'";
			}

			if (isset($fields['default_panel']))
			{
				$this->joins = ' left join panels dp on w.default_panel_id=dp.id';
				$options[] = "dp.div_id='$fields[default_panel]'";
			}

			$this->populateList($options);
		}


		protected function loadResult($key) { return new WidgetInstallation($this->list[$key]); }
	}
?>