<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 *
 * Sets up the configuration to be used for cleaning content using HTMLPurifier
 */
$config = HTMLPurifier_Config::createDefault();

// configuration goes here:
$config->set('Core', 'Encoding', 'UTF-8'); // replace with your encoding
$config->set('HTML', 'Doctype', 'XHTML 1.1'); // replace with your doctype
$config->set('Output','TidyFormat',true);
$config->set('HTML','TidyLevel','heavy');
$config->set('Output','Newline',"\n");
$config->set('Cache','DefinitionImpl',null);
#$config->set('URI','MakeAbsolute',true);
#$config->set('URI','Host','localhost');
#$config->set('URI','Base','/content_manager');
$allowedElements = array
(
	'div','p','h1', 'h2', 'h3', 'h4', 'h5', 'h6', 'br', 'hr',
	'em', 'strong', 'u', 'sub', 'sup',
	'abbr', 'acronym', 'address', 'blockquote', 'cite', 'code', 'pre', 'q',
	'dl', 'ol', 'ul', 'li', 'dt', 'dd',
	'table', 'thead','tbody','tr','th','td'
);
$config->set('HTML','AllowedElements',$allowedElements);


/*
$config->set('HTML', 'DefinitionID', 'content_manager');
$config->set('HTML', 'DefinitionRev', 1);
$config->set('Core', 'DefinitionCache', null); // remove this later!
$def =& $config->getHTMLDefinition(true);

$form =& $def->addElement(
  'form',   // name
  'Block',  // content set
  'Flow|Optional: fieldset', // allowed children
  'Common', // attribute collection
  array( // attributes
	'action*' => 'URI',
	'method' => 'Enum#get|post'
  )
);
$form->excludes = array('form' => true);

$def->addElement( 'fieldset','Block','Optional: legend|Flow','',array() );
$def->addElement( 'legend','Inline','Flow','',array() );

$def->addElement('label','Inline','Flow','',array('for'=>'NMTOKENS'));
$def->addElement('select','Inline','Flow','',array('name'=>'ID','id'=>'ID'));
$def->addElement('option','Inline','Flow','',array('value'=>'CDATA','selected'=>'Enum#selected'));
$def->addElement('textarea','Inline','Empty','',array('name'=>'ID','id'=>'ID','rows'=>'Number','cols'=>'Number'));
$def->addElement('input','Inline','Flow','',array('type'=>'CDATA',
											   'name'=>'ID',
											   'id'=>'ID',
											   'value'=>'CDATA',
											   'size'=>'Number',
											   'maxlength'=>'Number',
											   'checked'=>'Enum#checked'));
*/
