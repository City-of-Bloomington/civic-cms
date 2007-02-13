<?php
include '../configuration.inc';

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
	$variableName = Inflector::singularize($tableName);

/**
 * Generate home.php
 */
$PHP = "\${$variableName}List = new {$className}List();
	\${$variableName}List->find();

	\$template = new Template();
	\$template->blocks[] = new Block('{$variableName}s/{$variableName}List.inc',array('{$variableName}List'=>\${$variableName}List));
	\$template->render();";

$contents = "<?php\n";
$contents.= COPYRIGHT;
$contents.="
	$PHP
?>";

	$dir = APPLICATION_HOME."/scripts/stubs/html/$tableName";
	if (!is_dir($dir)) { mkdir($dir,0770,true); }
	file_put_contents("$dir/home.php",$contents);

/**
 * Generate the Add controller
 */
$PHP = "verifyUser();

	if (isset(\$_POST['{$variableName}']))
	{
		\${$variableName} = new {$className}();
		foreach(\$_POST['{$variableName}'] as \$field=>\$value)
		{
			\$set = 'set'.ucfirst(\$field);
			\${$variableName}->\$set(\$value);
		}

		try
		{
			\${$variableName}->save();
			Header('Location: home.php');
			exit();
		}
		catch(Exception \$e) { \$_SESSION['errorMessages'][] = \$e; }
	}

	\$template = new Template();
	\$template->blocks[] = new Block('{$variableName}s/add{$className}Form.inc');
	\$template->render();";
$contents = "<?php\n";
$contents.= COPYRIGHT;
$contents.="
	$PHP
?>";
	file_put_contents("$dir/add{$className}.php",$contents);


/**
 * Generate the Update controller
 */
$PHP = "verifyUser();

	if (isset(\$_GET['$key[Column_name]'])) { \${$variableName} = new {$className}(\$_GET['$key[Column_name]']); }
	if (isset(\$_POST['$key[Column_name]']))
	{
		\${$variableName} = new {$className}(\$_POST['$key[Column_name]']);
		foreach(\$_POST['$variableName'] as \$field=>\$value)
		{
			\$set = 'set'.ucfirst(\$field);
			\${$variableName}->\$set(\$value);
		}

		try
		{
			\${$variableName}->save();
			Header('Location: home.php');
			exit();
		}
		catch (Exception \$e) { \$_SESSION['errorMessages'][] = \$e; }
	}

	\$template = new Template();
	\$template->blocks[] = new Block('{$variableName}s/update{$className}Form.inc',array('{$variableName}'=>\${$variableName}));
	\$template->render();";
$contents = "<?php\n";
$contents.= COPYRIGHT;
$contents.="
	$PHP
?>";
	file_put_contents("$dir/update{$className}.php",$contents);
	echo "$className\n";
}
?>