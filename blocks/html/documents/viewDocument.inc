<?php
/**
 * @copyright 2006-2016 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @param Document $this->document
 * @param Section $this->section (optional)
 * Some documents are not in sections, and will not produce a section obejct
 */
if ($this->document->getDrupalNodeId()) {

    $sql = "select body_format, body_value
            from drupal.field_data_body
            where entity_type='node' and entity_id=?";
    $pdo = Database::getConnection();
    $query = $pdo->prepare($sql);
    $query->execute([$this->document->getDrupalNodeId()]);
    $result = $query->fetchAll();
    if (count($result)) {
        $row = $result[0];
        if ($row['body_format'] === 'markdown') {
            require_once MARKDOWN.'/Markdown.inc.php';
            $content = \Michelf\Markdown::defaultTransform($row['body_value']);
        }
        else { $content = $row['body_value']; }
    }
}

if (isset($content) && $content) {
    echo $content;
}
else {

    # We want to render PHP code harmless in the markup, unless
    # it's specifically enabled by some Webmaster
    if ($this->document->getContent($_SESSION['LANGUAGE'])) {
        $lang = $_SESSION['LANGUAGE'];
    }
    else {
        # Try and find a language we do have, English first
        if ($this->document->getContent('en')) { $lang = 'en'; }
        else {
            foreach($this->document->getContent() as $l=>$content) {
                if ($content) {
                    $lang = $l;
                    break;
                }
            }
        }
    }
    # If we still couldn't find a language, then somehow, this document
    # has no content.  Just display a blank page in English
    if (!isset($lang)) { $lang = 'en'; }


    if ($this->document->PHPIsEnabled()) {
        include $this->document->getContentFilename($lang);
    }
    else {
        echo WikiMarkup::parse($this->document->getContent($lang),$this->template);
    }
}
