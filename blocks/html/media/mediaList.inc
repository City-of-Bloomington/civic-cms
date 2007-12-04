<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param MediaList $this->mediaList
 */
	$url = new URL("http://$_SERVER[SERVER_NAME]$_SERVER[REQUEST_URI]");
?>
<form id="filter" method="get" action="<?php echo BASE_URL; ?>/media">
<div class="interfaceBox">
	<div class="titleBar">Media</div>
	<?php
		echo "
		<input name=\"mime_type\" id=\"mime_type\" type=\"hidden\" value=\"{$url->mime_type}\" />
		<input name=\"department_id\" id=\"department_id\" type=\"hidden\" value=\"{$url->department_id}\" />
		<input name=\"page\" id=\"page\" type=\"hidden\" value=\"{$url->page}\" />
		<input name=\"sort\" id=\"sort\" type=\"hidden\" value=\"{$url->sort}\" />
		";
	?>
	<table>
	<tr><th><select onchange="document.getElementById('mime_type').value=this.options[this.selectedIndex].value;this.form.submit();">
				<option></option>
				<?php
					foreach(Media::getExtensions() as $ext=>$info)
					{
						$selected = (isset($url->mime_type) && $url->mime_type===$info['mime_type']) ? 'selected="selected"' : '';
						echo "<option value=\"$info[mime_type]\" $selected>$ext</option>";
					}
				?>
			</select>
		</th>
		<th></th>
		<th><select onchange="document.getElementById('department_id').value=this.options[this.selectedIndex].value;this.form.submit();">
			<option></option>
			<?php
				$list = new DepartmentList();
				$list->find();
				foreach($list as $department)
				{
					$name = View::escape(substr($department->getName(),0,20));
					$selected = (isset($url->department_id) && $url->department_id===$department->getId()) ? 'selected="selected"' : '';
					echo "<option value=\"{$department->getId()}\" $selected>$name</option>";
				}
			?>
			</select>
		</th>
	</tr>
	<tr>
	<?php
		# Objects are always passed by reference.  So we must explicitly clone
		# the data, if we don't want to mess up the original version
		$sortingURL = new URL($url->getURL());

		$sortingURL->sort = $url->sort==='filename' ? 'filename+desc' : 'filename';
		echo "<th><a href=\"$sortingURL\">Filename</a></th>";

		$sortingURL->sort = $url->sort==='title' ? 'title+desc' : 'title';
		echo "<th><a href=\"$sortingURL\">Title</a></th>";

		$sortingURL->sort = 'department_id';
		echo "<th><a href=\"$sortingURL\">Department</a></th>";

		$sortingURL->sort = $url->sort==='uploaded' ? 'uploaded+desc' : 'uploaded';
		echo "<th><a href=\"$sortingURL\">Uploaded</a></th>";
	?>
	</tr>
	<?php
		foreach($this->mediaList as $media)
		{
			$title = View::escape($media->getTitle());
			$department = View::escape(substr($media->getDepartment()->getName(),0,20));

			$filename = substr($media->getFilename(),0,25);

			echo "
			<tr><td><a href=\"".BASE_URL."/media/info.php?media_id={$media->getId()}\" class=\"{$media->getExtension()}\">$filename</a></td>
				<td>$title</td>
				<td>$department</td>
				<td>{$media->getUploaded('%D')}</td>
			</tr>
			";
		}
	?>
	</table>
</div>
</form>
