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
		* Generate the list block
		*/
	$getId = "get".ucwords($key['Column_name']);
	$HTML = "<div class=\"interfaceBox\">
	<div class=\"titleBar\">
		<button type=\"button\" class=\"addSmall\" onclick=\"document.location.href='<?php echo BASE_URL; ?>/$tableName/add$className.php';\">Add</button>
		{$className}s
	</div>
	<ul><?php
			foreach(\$this->{$variableName}List as \${$variableName})
			{
				echo \"
				<li><button type=\\\"button\\\" class=\\\"editSmall\\\" onclick=\\\"document.location.href='\".BASE_URL.\"/$tableName/update$className.php?$key[Column_name]={\${$variableName}->{$getId}()}';\\\">Edit</button>
					$variableName</li>
				\";
			}
		?>
	</ul>
</div>";

$contents = "<?php\n";
$contents.= COPYRIGHT;
$contents.="
?>
$HTML";

	$dir = APPLICATION_HOME."/scripts/stubs/blocks/$tableName";
	if (!is_dir($dir)) { mkdir($dir,0770,true); }
	file_put_contents("$dir/{$variableName}List.inc",$contents);


/**
 * Generate the addForm
 */
$HTML = "<h1>Add $className</h1>
<form method=\"post\" action=\"<?php echo \$_SERVER['PHP_SELF']; ?>\">
<fieldset><legend>$className Info</legend>
	<table>
";
foreach($fields as $field)
{
	if ($field['Field'] != $key['Column_name'])
	{
		$fieldFunctionName = ucwords($field['Field']);
		switch ($field['Type'])
		{
			case "date":
			$HTML.="
	<tr><td><label for=\"{$variableName}-$field[Field]-mon\">Start Date</label></td>
		<td><select name=\"{$variableName}[$field[Field]][mon]\" id=\"{$variableName}-$field[Field]-mon\"><option></option>
			<?php
				\$now = getdate();
				for(\$i=1; \$i<=12; \$i++)
				{
					if (\$i!=\$now['mon']) { echo \"<option>\$i</option>\"; }
					else { echo \"<option selected=\"selected\">\$i</option>\"; }
				}
			?>
			</select>
			<select name=\"{$variableName}[$field[Field]][mday]\"><option></option>
			<?php
				for(\$i=1; \$i<=31; \$i++)
				{
					if (\$i!=\$now['mday']) { echo \"<option>\$i</option>\"; }
					else { echo \"<option selected=\"selected\">\$i</option>\"; }
				}
			?>
			</select>
			<input name=\"{$variableName}[$field[Field]][year]\" id=\"{$variableName}-$field[Field]-year\" size=\"4\" maxlength=\"4\" value=\"<?php echo \$now['year']; ?>\" />
		</td>
	</tr>";
				break;

			default:
		$HTML.= "
	<tr><td><label for=\"{$variableName}-$field[Field]\">Name</label></td>
		<td><input name=\"{$variableName}[$field[Field]]\" id=\"{$variableName}-$field[Field]\" /></td></tr>
		";
		}
	}
}
	$HTML.= "
	</table>

	<button type=\"submit\" class=\"submit\">Submit</button>
	<button type=\"button\" class=\"cancel\" onclick=\"document.location.href='<?php echo BASE_URL; ?>/{$variableName}s';\">Cancel</button>
</fieldset>
</form>";

$contents = "<?php\n";
$contents.= COPYRIGHT;
$contents.="
?>
$HTML";
file_put_contents("$dir/add{$className}Form.inc",$contents);

/**
 * Generate the Update Form
 */
$HTML = "<h1>Update $className</h1>
<form method=\"post\" action=\"<?php echo \$_SERVER['PHP_SELF']; ?>\">
<fieldset><legend>$className Info</legend>
	<input name=\"$key[Column_name]\" type=\"hidden\" value=\"<?php echo \$this->$getId(); ?>\" />
	<table>
";
foreach($fields as $field)
{
	if ($field['Field'] != $key['Column_name'])
	{
		$fieldFunctionName = ucwords($field['Field']);
		switch ($field['Type'])
		{
			case "date":
			$HTML.="
	<tr><td><label for=\"{$variableName}-$field[Field]-mon\">Start Date</label></td>
		<td><select name=\"{$variableName}[$field[Field]][mon]\" id=\"{$variableName}-$field[Field]-mon\"><option></option>
			<?php
				\$$field[Field] = \$this->{$variableName}->dateStringToArray(\$this->{$variableName}->get$fieldFunctionName());
				for(\$i=1; \$i<=12; \$i++)
				{
					if (\$i!=\$$field[Field]['mon']) { echo \"<option>\$i</option>\"; }
					else { echo \"<option selected=\"selected\">\$i</option>\"; }
				}
			?>
			</select>
			<select name=\"{$variableName}[$field[Field]][mday]\"><option></option>
			<?php
				for(\$i=1; \$i<=31; \$i++)
				{
					if (\$i!=\$$field[Field]['mday']) { echo \"<option>\$i</option>\"; }
					else { echo \"<option selected=\"selected\">\$i</option>\"; }
				}
			?>
			</select>
			<input name=\"{$variableName}[$field[Field]][year]\" id=\"{$variableName}-$field[Field]-year\" size=\"4\" maxlength=\"4\" value=\"<?php echo \$$field[Field]['year']; ?>\" />
		</td>
	</tr>";
				break;

			default:
		$HTML.= "
	<tr><td><label for=\"{$variableName}-$field[Field]\">Name</label></td>
		<td><input name=\"{$variableName}[$field[Field]]\" id=\"{$variableName}-$field[Field]\" value=\"<?php echo \$this->{$variableName}->get$fieldFunctionName(); ?>\" /></td></tr>
		";
		}
	}
}
	$HTML.= "
	</table>

	<button type=\"submit\" class=\"submit\">Submit</button>
	<button type=\"button\" class=\"cancel\" onclick=\"document.location.href='<?php echo BASE_URL; ?>/{$variableName}s';\">Cancel</button>
</fieldset>
</form>";
$contents = "<?php\n";
$contents.= COPYRIGHT;
$contents.="
?>
$HTML";
file_put_contents("$dir/update{$className}Form.inc",$contents);

	echo "$className\n";
}
?>