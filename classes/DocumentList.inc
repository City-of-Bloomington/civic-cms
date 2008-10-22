<?php
/**
 * @copyright Copyright (C) 2006-2008 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
class DocumentList extends PDOResultIterator
{
	public function __construct($fields=null)
	{
		$this->select = 'select documents.id as id from documents';
		if (is_array($fields)) $this->find($fields);
	}

	public function find($fields=null,$sort='title',$limit=null,$groupBy=null)
	{
		$this->sort = $sort;
		$this->limit = $limit;
		$this->groupBy = $groupBy;
		$this->joins = '';

		# Sorting on type needs to join the documentTypes table
		if (preg_match('/type/',$this->sort))
		{
			$this->joins.= ' left join documentTypes t on documentType_id=t.id';
		}

		$options = array();
		$parameters = array();
		if (isset($fields['id']))
		{
			$options[] = 'id=:id';
			$parameters[':id'] = $fields['id'];
		}
		if (isset($fields['title']))
		{
			$options[] = 'title=:title';
			$parameters[':title'] = $fields['title'];
		}
		if (isset($fields['wikiTitle']))
		{
			$options[] = 'wikiTitle=:wikiTitle';
			$parameters[':wikiTitle'] = $fields['wikiTitle'];
		}
		if (isset($fields['alias']))
		{
			$options[] = 'alias=:alias';
			$parameters[':alias'] = $fields['alias'];
		}
		if (isset($fields['feature_title']))
		{
			$options[] = 'feature_title=:feature_title';
			$parameters[':feature_title'] = $fields['feature_title'];
		}
		if (isset($fields['created']))
		{
			$options[] = 'created=:created';
			$parameters[':created'] = $fields['created'];
		}
		if (isset($fields['createdBy']))
		{
			$options[] = 'createdBy=:createdBy';
			$parameters[':createdBy'] = $fields['createdBy'];
		}
		if (isset($fields['modified']))
		{
			$options[] = 'modified=:modified';
			$parameters[':modified'] = $fields['modified'];
		}
		if (isset($fields['modifiedBy']))
		{
			$options[] = 'modifiedBy=:modifiedBy';
			$parameters[':modifiedBy'] = $fields['modifiedBy'];
		}
		if (isset($fields['publishDate']))
		{
			$options[] = 'publishDate=:publishDate';
			$parameters[':publishDate'] = $fields['publishDate'];
		}
		if (isset($fields['retireDate']))
		{
			$options[] = 'retireDate=:retireDate';
			$parameters[':retireDate'] = $fields['retireDate'];
		}
		if (isset($fields['department_id']))
		{
			$options[] = 'department_id=:department_id';
			$parameters[':department_id'] = $fields['department_id'];
		}
		if (isset($fields['documentType_id']))
		{
			$options[] = 'documentType_id=:documentType_id';
			$parameters[':documentType_id'] = $fields['documentType_id'];
		}
		if (isset($fields['description']))
		{
			$options[] = 'description=:description';
			$parameters[':description'] = $fields['description'];
		}
		if (isset($fields['lockedBy']))
		{
			$options[] = 'lockedBy=:lockedBy';
			$parameters[':lockedBy'] = $fields['lockedBy'];
		}
		if (isset($fields['enablePHP']))
		{
			$options[] = 'enablePHP=:enablePHP';
			$parameters[':enablePHP'] = $fields['enablePHP'];
		}
		if (isset($fields['banner_media_id']))
		{
			$options[] = 'banner_media_id=:banner_media_id';
			$parameters[':banner_media_id'] = $fields['banner_media_id'];
		}
		if (isset($fields['icon_media_id']))
		{
			$options[] = 'icon_media_id=:icon_media_id';
			$parameters[':icon_media_id'] = $fields['icon_media_id'];
		}

		# Provide a way to find out active documents.  Documents are active during the time
		# between their Publish and Retire dates.
		if (isset($fields['active']))
		{
			$options[] = '(publishDate<=:active_start and (retireDate is null or retireDate>:active_end))';
			$parameters[':active_start'] = $fields['active'];
			$parameters[':active_end'] = $fields['active'];
		}

		if (isset($fields['first_letter']))
		{
			$options[] = 'upper(substr(title,1,1))=:first_letter';
			$parameters[':first_letter'] = $fields['first_letter'];
		}


		if (isset($fields['rangeStart']))
		{
			$options[] = 'publishDate > from_unixtime(:rangeStart)';
			$parameters[':rangeStart'] = $fields['rangeStart'];
		}
		if (isset($fields['rangeEnd']))
		{
			$options[] = '(retireDate is null or retireDate < from_unixtime(:rangeEnd))';
			$parameters[':rangeEnd'] = $fields['rangeEnd'];
		}

		# Finding on fields from other tables required joining those tables.
		# You can add fields from other tables to $options by adding the join SQL
		# to $this->joins here
		if (isset($fields['wikiTitle_or_alias']))
		{
			$options[] = "(wikiTitle=:wta_wiki or alias=:wta_alias)";
			$parameters[':wta_wiki'] = $fields['wikiTitle_or_alias'];
			$parameters[':wta_alias'] = $fields['wikiTitle_or_alias'];
		}

		if (isset($fields['section_id']) || isset($fields['featured']))
		{
			$this->joins.= ' left join sectionDocuments s on documents.id=s.document_id';
			if (isset($fields['section_id']))
			{
				$options[] = 'section_id=:section_id';
				$parameters[':section_id'] = $fields['section_id'];
			}
			if (isset($fields['featured']))
			{
				$options[] = 'featured=:featured';
				$parameters[':featured'] = $fields['featured'];
			}
		}

		if (isset($fields['lang']))
		{
			$PDO = Database::getConnection();
			$query = $PDO->prepare('create temporary table if not exists language_ids (id int unsigned not null primary key)');
			$query->execute();

			# This is just in case we have a previous temp table hanging around.
			$query = $PDO->prepare('delete from language_ids');
			$query->execute();

			$query = $PDO->prepare('insert language_ids set id=?');

			$glob = glob(APPLICATION_HOME.'/data/documents/*/*/*/*.'.$fields['lang']);
			foreach($glob as $file)
			{
				$id = basename($file,'.'.$fields['lang']);
				$query->execute(array($id));
			}

			$this->joins = ' right join language_ids l on documents.id=l.id';
		}

		/**
		 * Pass in an array of facet_ids to get a list of documents matching
		 * all the desired facets
		 * @param array $fields['facet_ids']
		 */
		if (isset($fields['facet_ids']))
		{
			$facets = implode(',',$fields['facet_ids']);
			$this->joins.= " inner join document_facets df on documents.id=df.document_id and df.facet_id in ($facets)";
			$this->groupBy = 'documents.id having count(*)='.count($fields['facet_ids']);
		}

		if (isset($fields['facet_id']))
		{
			$this->joins.= ' left join document_facets f on documents.id=f.document_id';
			$options[] = 'facet_id=:facet_id';
			$parameters[':facet_id'] = $fields['facet_id'];
		}

		if (isset($fields['media_id']))
		{
			$this->joins.= ' left join media_documents m on documents.id=m.document_id';
			$options[] = 'media_id=:media_id';
			$parameters[':media_id'] = $fields['media_id'];
		}

		$this->populateList($options,$parameters);
	}

	public function grep($regex)
	{
		$regex = escapeshellarg($regex);

		$this->list = array();

		$dir = APPLICATION_HOME.'/data/documents/';
		$files = explode("\n",shell_exec("grep -lR --exclude '*.svn*' $regex $dir"));
		foreach($files as $file)
		{
			$d = explode('.',basename($file));
			if ($d[0]) { $this->list[] = $d[0]; }
		}
	}

	protected function loadResult($key) { return new Document($this->list[$key]); }
}
