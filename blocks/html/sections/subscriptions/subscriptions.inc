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
	<h2><?php echo View::escape($this->title); ?></h2>
	<ul><?php
			$return_url = new URL($_SERVER['SERVER_NAME'].$_SERVER['REQUEST_URI']);
			foreach($this->subscriptionList as $subscription)
			{
				$name = View::escape($subscription->getSection()->getName());
				$url = $subscription->getSection()->getURL();

				echo "
				<li><a href=\"$url\">$name</a>
					<a class=\"unsubscribe button\"
						href=\"".BASE_URL."/sections/subscriptions/unsubscribe.php?section_id={$subscription->getSection_id()};return_url=$return_url\"
						onmouseover=\"FRAMEWORK.popupTooltip('Unsubscribe to this section.');\"
						onmouseout=\"FRAMEWORK.hideTooltip();\">
						Unsubscribe
					</a>
				</li>
				";
			}
		?>
	</ul>
</div>
