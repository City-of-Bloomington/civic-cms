<?php
/**
 * @copyright Copyright (C) 2008 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param Language $this->language
 */
?>
<h1>Edit <?php echo $this->language->getEnglish(); ?></h1>
<form method="post" action="<?php echo $_SERVER['SCRIPT_NAME']; ?>">
<fieldset><legend>Language</legend>
	<input type="hidden" name="language_id" value="<?php echo $this->language->getId(); ?>" />
	<table>
	<tr><td><label for="language-code">Code</label></td>
		<td><input name="language[code]" id="language-code" size="3" maxlength="3" value="<?php echo $this->language->getCode(); ?>" /></td></tr>
	<tr><td><label for="language-english">English Name</label></td>
		<td><input name="language[english]" id="language-english" value="<?php echo $this->language->getEnglish(); ?>" /></td></tr>
	<tr><td><label for="language-native">Native Name</label></td>
		<td><input name="language[native]" id="language-native" value="<?php echo $this->language->getNative(); ?>" /></td></tr>
	<tr><td><label for="language-direction">Direction</label></td>
		<td><select name="language[direction]" id="language-direction">
				<option value="ltr" <?php if($this->language->getDirection()=='ltr') echo 'selected="selected"'; ?>>Left to Right</option>
				<option value="rtl" <?php if($this->language->getDirection()=='rtl') echo 'selected="selected"'; ?>>Right to Left</option>
			</select>
		</td>
	</tr>
	</table>

	<button type="submit" class="submit">Submit</button>
	<a href="<?php echo BASE_URL; ?>/languages" class="cancel">Cancel</a>
</fieldset>
</form>
