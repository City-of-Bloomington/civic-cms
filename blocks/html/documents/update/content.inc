<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param Document $this->document
 * @param string $this->language
 */
?>
<form id="documentForm" method="post" action="<?php echo $_SERVER['PHP_SELF']; ?>">
	<fieldset><legend>Content</legend>
		<input type="hidden" name="tab" id="tab" value="sections" />
		<input type="hidden" name="action" id="action" value="next" />

		<table>
		<tr><td><label for="lang">Current Language</label></td>
			<td><select name="lang" id="lang" onchange="FRAMEWORK.processTabbedForm('documentForm','content','next');">
				<?php
					$list = new LanguageList();
					$list->find();
					foreach($list as $language)
					{
						if ($this->language->getCode() == $language->getCode()) { echo "<option value=\"{$language->getCode()}\" selected=\"selected\">{$language->getNative()}</option>"; }
						else { echo "<option value=\"{$language->getCode()}\">{$language->getNative()}</option>"; }
					}
				?>
				</select>
			</td>
		</tr>
		</tr>
		</table>
		<?php
			if (!$this->document->isLocked())
			{
				include APPLICATION_HOME.'/includes/editors/'.EDITOR.'.inc';
			}
			else
			{
				echo "
				<p>Content editing has been locked by {$this->document->getLockedByUser()->getUsername()}.</p>
				<p>You will need to contact that person, or an Administrator, to edit this content.</p>
				";
			}
		?>
	</fieldset>

</form>
