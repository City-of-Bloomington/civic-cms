<?php
/**
 * @copyright Copyright (C) 2008 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param SectionList $this->sectionList
 */

?>
<div class="interfaceBox">
	<h1>Highlighted Subscriptions</h1>
	<ul><?php
			$return_url = "http://$_SERVER[SERVER_NAME]$_SERVER[REQUEST_URI]";
			foreach($this->sectionList as $section)
			{
				$name = View::escape($section->getName());

				$button = '';
				if (isset($_SESSION['USER']))
				{
					if ($_SESSION['USER']->hasSubscription($section))
					{
						$button = "
						<button type=\"button\"
								class=\"unsubscribe\"
								onclick=\"document.location.href='".BASE_URL."/sections/subscriptions/unsubscribe.php?section_id={$section->getId()};return_url=$return_url';\">
							Unsubscribe
						</button>
						";
					}
					else
					{
						$button = "
						<button type=\"button\"
								class=\"subscribe\"
								onclick=\"document.location.href='".BASE_URL."/sections/subscriptions/subscribe.php?section_id={$section->getId()};return_url=$return_url';\">
							Subscribe
						</button>
						";
					}
				}
				echo "
				<li><a href=\"{$section->getURL()}\">$name</a>
					$button
				</li>
				";
			}
		?>
	</ul>
</div>
