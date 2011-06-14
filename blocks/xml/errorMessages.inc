<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param array $this->errorMessages
 */
?>
<errorList>
	<?php
		foreach($this->errorMessages as $e)
		{
			$error = $e->getMessage();
			$xmlFormattedError = htmlspecialchars($error,ENT_NOQUOTES);
			echo "
			<error>
				<message>$xmlFormattedError</message>
				<explanation>
			";

			# For errors in XML format, we can just include the HTML error message inside
			# the explanation element.
			if (file_exists(APPLICATION_HOME."/blocks/html/errorMessages/$error.inc"))
			{
				include APPLICATION_HOME."/blocks/html/errorMessages/$error.inc";
			}
			else
			{
				echo "<p>$error</p>";
			}
			echo "
				</explanation>
			</error>
			";
		}
	?>
</errorList>
