<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
	class SectionWidgetList extends PDOResultIterator
	{

		public function __construct($fields=null,$sort='layout_order')
		{
			$this->select = 'select section_widgets.id as id from section_widgets';
			$this->sort = $sort;
			if (is_array($fields)) $this->find($fields);
		}


		public function find($fields=null,$sort='layout_order',$limit=null,$groupBy=null)
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
			if (isset($fields['section_id'])) { $options[] = "section_id='$fields[section_id]'"; }
			if (isset($fields['widget_id'])) { $options[] = "widget_id='$fields[widget_id]'"; }
			if (isset($fields['panel_id'])) { $options[] = "panel_id='$fields[panel_id]'"; }
			if (isset($fields['layout_order'])) { $options[] = "layout_order='$fields[layout_order]'"; }

			if (isset($fields['section_id_array']))
			{
				$list = implode(',',$fields['section_id_array']);
				$options[] = "section_id in ($list)";
			}

			# Finding on fields from other tables required joining those tables.
			# You can add fields from other tables to $options by adding the join SQL
			# to $this->joins here
			if (isset($fields['panel']))
			{
				$this->joins = ' left join panels on id=panel_id';
				$options[] = "div_id='$fields[panel]'";
			}

			$this->populateList($options);
		}


		protected function loadResult($key) { return new SectionWidget($this->list[$key]); }
	}
?>