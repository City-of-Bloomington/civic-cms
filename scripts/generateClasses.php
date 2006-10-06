<?php
$copyright = "/**
 * @copyright Copyright (C) 2006 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 */";

include("../configuration.inc");

$tables = array();
foreach($PDO->query("show tables") as $row) { list($tables[]) = $row; }

foreach($tables as $tableName)
{
	$fields = array();
	foreach($PDO->query("describe $tableName") as $row)
	{
		$type = ereg_replace("[^a-z]","",$row['Type']);

		if (ereg("int",$type)) { $type = "int"; }
		if (ereg("enum",$type) || ereg("varchar",$type)) { $type = "string"; }


		$fields[] = array('Field'=>$row['Field'],'Type'=>$type);
	}

	$result = $PDO->query("show index from $tableName where key_name='PRIMARY'")->fetchAll();
	if (count($result) != 1) { continue; }
	$key = $result[0];


	$className = Inflector::classify($tableName);
	#--------------------------------------------------------------------------
	# Constructor
	#--------------------------------------------------------------------------
	$constructor = "
		/**
		 * This will load all fields in the table as properties of this class.
		 * You may want to replace this with, or add your own extra, custom loading
		 */
		public function __construct(\$$key[Column_name]=null)
		{
			global \$PDO;

			if (\$$key[Column_name])
			{
				\$sql = \"select * from $tableName where $key[Column_name]=\$$key[Column_name]\";
				\$result = \$PDO->query(\$sql);
				if (\$result)
				{
					if (\$row = \$result->fetch())
					{
						# You may want to replace this line to do your own custom loading
						foreach(\$row as \$field=>\$value) { if (\$value) \$this->\$field = \$value; }

						\$result->closeCursor();
					}
					else { throw new Exception(\$sql); }
				}
				else { \$e = \$PDO->errorInfo(); throw new Exception(\$sql.\$e[2]); }
			}
			else
			{
				# This is where the code goes to generate a new, empty instance.
				# Set any default values for properties that need it here
			}
		}
	";

	#--------------------------------------------------------------------------
	# Properties
	#--------------------------------------------------------------------------
	$properties = "";
	$linkedProperties = array();
	foreach($fields as $field)
	{
		$properties.= "\t\tprivate \$$field[Field];\n";

		if (substr($field['Field'],-3) == "_id") { $linkedProperties[] = $field['Field']; }
	}
	if (count($linkedProperties))
	{
		$properties.="\n\n";
		foreach($linkedProperties as $property)
		{
			$field = substr($property,0,-3);
			$properties.= "\t\tprivate \$$field;\n";
		}
	}

	#--------------------------------------------------------------------------
	# Getters
	#--------------------------------------------------------------------------
	$getters = "";
	foreach($fields as $field)
	{
		$fieldFunctionName = ucwords($field['Field']);
		$getters.= "\t\tpublic function get$fieldFunctionName() { return \$this->$field[Field]; }\n";
	}
	foreach($linkedProperties as $property)
	{
		$field = substr($property,0,-3);
		$fieldFunctionName = ucwords($field);
		$getters.= "
		public get$fieldFunctionName()
		{
			if (\$this->$property)
			{
				if (!\$this->$field) { \$this->$field = new $fieldFunctionName(\$this->$property); }
				return \$this->$field;
			}
			else return null;
		}
		";
	}


	#--------------------------------------------------------------------------
	# Setters
	#--------------------------------------------------------------------------
	$setters = "";
	foreach($fields as $field)
	{
		if ($field['Field'] != $key['Column_name'])
		{
			$fieldFunctionName = ucwords($field['Field']);
			switch ($field['Type'])
			{
				case "int":
					if (in_array($field['Field'],$linkedProperties))
					{
						$property = substr($field['Field'],0,-3);
						$object = ucfirst($property);
						$setters.= "\t\tpublic function set$fieldFunctionName(\$$field[Type]) { \$this->$property = new $object(\$int); \$this->$field[Field] = \$$field[Type]; }\n";
					}
					else
					{
						$setters.= "\t\tpublic function set$fieldFunctionName(\$$field[Type]) { \$this->$field[Field] = ereg_replace(\"[^0-9]\",\"\",\$$field[Type]); }\n";
					}
				break;

				case "string":
					$setters.= "\t\tpublic function set$fieldFunctionName(\$$field[Type]) { \$this->$field[Field] = trim(\$$field[Type]); }\n";
				break;

				case "date":
					$setters.= "\t\tpublic function set$fieldFunctionName(\$$field[Type]) { \$this->$field[Field] = is_array(\$$field[Type]) ? \$this->dateArrayToString(\$$field[Type]) : \$$field[Type]; }\n";
				break;

				case "float":
					$setters.= "\t\tpublic function set$fieldFunctionName(\$$field[Type]) { \$this->$field[Field] = ereg_replace(\"[^0-9.\-]\",\"\",\$$field[Type]); }\n";
				break;

				default:
					$setters.= "\t\tpublic function set$fieldFunctionName(\$$field[Type]) { \$this->$field[Field] = \$$field[Type]; }\n";
			}
		}
	}
	$setters.= "\n";
	foreach($linkedProperties as $field)
	{
		$property = substr($field,0,-3);
		$object = ucfirst($property);
		$setters.= "\t\tpublic function set$object(\$$object) { \$this->$field = {$object}->getId(); \$this->$property = \$$object; }\n";
	}

	#--------------------------------------------------------------------------
	# Output the class
	#--------------------------------------------------------------------------
$contents = "<?php
$copyright
	class $className extends ActiveRecord
	{
$properties

$constructor

		/**
		 * This generates generic SQL that should work right away.
		 * You can replace this \$fields code with your own custom SQL
		 * for each property of this class,
		 */
		public function save()
		{
			# Check for required fields here.  Throw an exception if anything is missing.

			\$fields = array();
";
			foreach($fields as $field)
			{
				if ($field['Field'] != $key['Column_name'])
				{
					$contents.="\t\t\t\$fields[] = \$this->$field[Field] ? \"$field[Field]='{\$this->$field[Field]}'\" : \"$field[Field]=null\";\n";
				}
			}
$contents.= "
			\$fields = implode(\",\",\$fields);


			if (\$this->$key[Column_name]) { \$this->update(\$fields); }
			else { \$this->insert(\$fields); }
		}

		private function update(\$fields)
		{
			global \$PDO;

			\$sql = \"update $tableName set \$fields where $key[Column_name]={\$this->$key[Column_name]}\";
			if (false === \$PDO->exec(\$sql)) { \$e = \$PDO->errorInfo(); throw new Exception(\$sql.\$e[2]); }
		}

		private function insert(\$fields)
		{
			global \$PDO;

			\$sql = \"insert $tableName set \$fields\";
			if (false === \$PDO->exec(\$sql)) { \$e = \$PDO->errorInfo(); throw new Exception(\$sql.\$e[2]); }
			\$this->$key[Column_name] = \$PDO->lastInsertID();
		}


$getters

$setters
	}
?>";
	echo "$className\n";
	file_put_contents(APPLICATION_HOME."/scripts/classStubs/$className.inc",$contents);
}
?>