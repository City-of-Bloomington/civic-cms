<div><div class="titleBar">Guides</div>
<ul><?php
		$guides = new TagGroup('Guides');
		foreach($guides->getTags() as $tag)
		{
			$name = View::escape($tag->getName());
			echo "<li><a href=\"".BASE_URL."/tags/viewTag.php?tag_id={$tag->getId()}\">$name</a></li>\n";
		}
	?>
</ul>
</div>
