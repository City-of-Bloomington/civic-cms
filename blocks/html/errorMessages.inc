<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param array $this->errorMessages
 */
?>
<div id="errorMessages">
	<h1>Important Message</h1>
	<?php
		foreach($this->errorMessages as $e)
		{
			$error = $e->getMessage();
			if (file_exists(APPLICATION_HOME."/blocks/html/errorMessages/$error.inc"))
			{
				$block = new Block("errorMessages/$error.inc",array('error'=>$e));
				echo $block->render();
			}
			else
			{
				echo "<p>$error</p>";
			}
		}
	?>
</div>