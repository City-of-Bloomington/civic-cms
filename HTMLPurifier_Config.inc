<?php
/**
 * @copyright 2007-2009 City of Bloomington, Indiana
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 *
 * Sets up the configuration to be used for cleaning content using HTMLPurifier
 */
$config = HTMLPurifier_Config::createDefault();

// configuration goes here:
$config->set('Core','Encoding', 'UTF-8'); // replace with your encoding
$config->set('HTML','Doctype', 'XHTML 1.1'); // replace with your doctype
$config->set('Output','TidyFormat',true);
$config->set('HTML','TidyLevel','heavy');
$config->set('Output','Newline',"\n");
$config->set('Cache','DefinitionImpl',null);
$config->set('Attr','EnableID',true);
#$config->set('URI','MakeAbsolute',true);
#$config->set('URI','Host','localhost');
#$config->set('URI','Base','/content_manager');
$allowedElements = array
(
	'div','p','h1', 'h2', 'h3', 'h4', 'h5', 'h6', 'br', 'hr',
	'em', 'strong', 'sub', 'sup',
	'abbr', 'acronym', 'address', 'blockquote', 'cite', 'code', 'pre', 'q',
	'dl', 'ol', 'ul', 'li', 'dt', 'dd',
	'table', 'thead','tbody','tr','th','td',
	'img'
);
$config->set('HTML','AllowedElements',$allowedElements);

/**
 * Even though we want to allow style="" as an attribute, we
 * still want to keep people from changing fonts and others.
 * This should strip those from allowed CSS definitions
 */
$valid_css = array('text-decoration');
$config->set('CSS','AllowedProperties',$valid_css);
