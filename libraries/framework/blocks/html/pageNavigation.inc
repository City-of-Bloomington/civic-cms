<?php
/**
 * @copyright 2007-2009 City of Bloomington, Indiana
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param array $this->pages
 * @param int $this->page
 * @param URL $this->url
 */
if (count($this->pages) > 1) {
	$maxNumLinks = 10;
	$url = $this->url;

	// Make sure the page we're asking for actually exists
	if (!$this->pages->offsetExists($this->page))
	{
		$this->page = 0;
	}

	echo '<ul class="pageNavigation">';

	// Show the Back button
	if ($this->page != 0) {
		$url->page = 0;
		echo "
		<li><button type=\"button\" class=\"first\" onclick=\"document.location.href='$url';\">
				First
			</button>
		</li>
		";

		$url->page = $this->page-1;
		echo "
		<li><button type=\"button\" class=\"back\" onclick=\"document.location.href='$url';\">
				Back
			</button>
		</li>
		";
	}

	// Show the page number links
	// Show only $maxNumLinks pages at a time
	$start = $this->page<=$maxNumLinks/2 ? 0 : $this->page-$maxNumLinks/2;
	$links = new LimitIterator($this->pages->getIterator(),$start,$maxNumLinks);
	foreach ($links as $i=>$index) {
		$displayNumber = $i+1;
		$url->page = $i;
		$class = ($i == $this->page) ? 'class="current"' : '';
		echo "<li><a href=\"$url\" $class>$displayNumber</a></li>";
	}

	// Show the Next button
	if ($this->page != $this->pages->getLastIndex()) {
		$url->page = $this->page+1;
		echo "
		<li><button type=\"button\" class=\"next\" onclick=\"document.location.href='$url';\">
				Next
			</button>
		</li>
		";

		$url->page = $this->pages->getLastIndex();
		echo "
		<li><button type=\"button\" class=\"last\" onclick=\"document.location.href='$url';\">
				Last
			</button>
		</li>
		";
	}

	echo '</ul>';
}
