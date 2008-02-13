<?php
/**
 * @copyright Copyright (C) 2008 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param string $this->title
 * @param SectionSubscriptionList $this->subscriptionList
 */
?>
<div class="interfaceBox">
	<h1><?php echo View::escape($this->title); ?></h1>
	<ul><?php
			$return_url = "http://$_SERVER[SERVER_NAME]$_SERVER[REQUEST_URI]";
			foreach($this->subscriptionList as $subscription)
			{
				$name = View::escape($subscription->getSection()->getName());
				$url = $subscription->getSection()->getURL();

				echo "
				<li><a href=\"$url\">$name</a>
					<button type=\"button\"
							class=\"unsubscribe\"
							onclick=\"document.location.href='".BASE_URL."/sections/subscriptions/unsubscribe.php?section_id={$subscription->getSection_id()};return_url=$return_url';\">
						Unsubscribe
					</button>
				</li>
				";
			}
		?>
	</ul>
</div>