<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 *
 * Sets up the configuration to be used for cleaning content using HTMLPurifier
 */

	$config = HTMLPurifier_Config::createDefault();
	$config->set('HTML', 'Doctype', 'XHTML 1.1');
	$config->set('HTML','TidyLevel','heavy');
	$config->set('Output','TidyFormat',true);
	$config->set('Output','Newline',"\n");
	$config->set('Cache','DefinitionImpl',null);
	#$config->set('URI','MakeAbsolute',true);
	#$config->set('URI','Host','localhost');
	#$config->set('URI','Base','/content_manager');


	#$allowedElements = array
	#(
	#	'div','p','h1', 'h2', 'h3', 'h4', 'h5', 'h6', 'br', 'hr',
	#	'em', 'strong', 'u', 'sub', 'sup',
	#	'abbr', 'acronym', 'address', 'blockquote', 'cite', 'code', 'pre', 'q',
	#	'dl', 'ol', 'ul', 'li', 'dt', 'dd',
	#	'a', 'img',
	#	'table', 'thead','tbody','tr','th','td'
	#);
	#$config->set('HTML','AllowedElements',$allowedElements);
