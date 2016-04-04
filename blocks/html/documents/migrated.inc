<?php
/**
 * @copyright 2016 City of Bloomington, Indiana
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @param Document $this->document
 */
?>
<div class="customalert">
    <h1>Migrated</h1>
    <p> This page is available on our new
        <a href="<?=  $this->document->getMigratedUrl(); ?>">Alpha site</a>
    </p>
</div>