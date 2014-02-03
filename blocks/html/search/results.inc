<?php
/**
 * @copyright 2007-2014 City of Bloomington, Indiana
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param Array $this->results An array of Documents
 */
if (count($this->results)) {
	# Show the results
	foreach($this->results as $hit) {
		#------------------------------------------------------------
		# Document Results
		#------------------------------------------------------------
		if ($hit instanceof Document) {
			$title = View::escape($hit->getTitle());

			$description = $hit->getDescription() ? $hit->getDescription() : $hit->getContent('en');
			$description = View::escape(View::limitWords(strip_tags(WikiMarkup::parse($description)),30));

			$size_in_bytes = strlen($hit->getContent('en'));
			if ($size_in_bytes>1000) {
				$size = round($size_in_bytes/1024);
				$size.='k';
			}
			else { $size = $size_in_bytes.'bytes'; }

			if ($hit->isActive()) {
				echo "
				<div class=\"searchResult\">
					<h3><a href=\"{$hit->getURL()}\">$title</a></h3>
					<p>$description</p>
					<span><a href=\"{$hit->getURL()}\">".BASE_URL."/{$hit->getWikiTitle()}</a> - $size
						- last updated {$hit->getModified('%D')}</span>
				</div>
				";
			}
		}
		#------------------------------------------------------------
		# Event Results
		#------------------------------------------------------------
		elseif ($hit instanceof Event) {
			$title = View::escape($hit->getTitle());
			$description = View::escape(View::limitWords(strip_tags($hit->getDescription()),30));
			echo "
			<div class=\"searchResult\">
				<h3><a href=\"{$hit->getURL()}\">$title</a></h3>
				<p>$description</p>
				<span>last updated {$hit->getModified('%D')}</span>
			</div>
			";
		}

		#------------------------------------------------------------
		# Media Results
		#------------------------------------------------------------
		elseif ($hit instanceof Media) {
			$title = View::escape($hit->getTitle());
			$description = View::escape(View::limitWords(strip_tags($hit->getDescription()),30));
			$class = $hit->getExtension();
			echo "
			<div class=\"searchResult\">
				<h3><a href=\"{$hit->getURL('original')}\" class=\"$class\">$title</a></h3>
				<p>$description</p>
				<span>uploaded {$hit->getUploaded('%D')}</span>
			</div>
			";
		}
	}
}
else {
	echo "<p>We were unable to find any results that match your search terms.</p>";
}
