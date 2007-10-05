<?php
define('COPYRIGHT',"/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 */");
	/**
	 * Used to keep sessions on the same webserver seperate;
	 */
	define('APPLICATION_NAME','content_manager');

	/**
	 * Where on the filesystem the framework is installed.
	 */
	define('FRAMEWORK','/home/inghamn/Desktop/working/framework/branches/devel');

	/**
	 * This needs to point to the library directory inside your
	 * installation of the ZendFramework
	 */
	define('ZEND','/var/www/libraries/ZendFramework/library');
	/**
	 * These control search index performance.  If indexing seems slow
	 * or PHP runs out of memory, you might try adjusting these to suit
	 * Documentation is available at:
	 * http://framework.zend.com/manual/en/zend.search.lucene.best-practice.html
	 */
	define('ZEND_SEARCH_MAX_BUFFERED_DOCS',1);
	define('ZEND_SEARCH_MAX_MERGE_DOCS',10000);
	define('ZEND_SEARCH_MERGE_FACTOR',10);

	/**
	 * Optional Content cleaning - Uncomment this is you want
	 * extra cleaning to be done on content submitted from the WYSIWYG editor
	 *
	 * This should point to the library directory inside your
	 * installation of the HTMLPurifier
	 * http://htmlpurifier.org
	 */
	#define('HTMLPURIFIER','/var/www/libraries/htmlpurifier/library');

	/**
	 * Where on the filesystem this application is installed
	 */
	define('APPLICATION_HOME','/home/inghamn/Desktop/working/content_manager/trunk');

	/**
	 * The URL to get to this site
	 * Do NOT use a trailing slash
	 */
	define('BASE_URL','http://aoi.bloomington.in.gov/test');

	/**
	 * Used when there's an error on the site.  The Framework will
	 * print out a nice error message, encouraging users to report any problems
	 * See: FRAMEWORK/ITSFunctions.inc
	 */
	define('ADMINISTRATOR_NAME','Cliff');
	define('ADMINISTRATOR_EMAIL','inghamn@bloomington.in.gov');


	/**
	 * Database Setup
	 */
	define('DB_NAME','test');
	define('DB_USER','test');
	define('DB_PASS','test');

	# This application calls mysql and mysqldump from the command line through
	# exec() and needs the path to the binaries
	define('MYSQL_PATH','/usr/local/mysql');

	/**
	 * LDAP Configuration
	 * This is required in order to use the LDAP authentication
	 * If you do not want to use LDAP authentication, you can comment this out
	 */
	define('LDAP_DOMAIN','city.bloomington.in.us');
	define('LDAP_DN','ou=people,o='.LDAP_DOMAIN);
	define('LDAP_USERNAME_ATTRIBUTE','uid');
	define('LDAP_ADMIN_USER','username');
	define('LDAP_ADMIN_PASS','password');
	define('LDAP_SERVER','ldap.bloomington.in.gov');
	define('LDAP_PASSWORD_ATTRIBUTE','userpassword');

	/**
	 * Subversion setup
	 * This is required in order to use Subversion to version documents
	 * If you do not want to use Subversion, you can comment this out
	 */
	 define('SVN','/usr/bin/svn');

	/**
	 * WYSIWYG Editor
	 * Choose from: FCKeditor, tiny_mce
	 */
	#define('EDITOR','FCKeditor');
	define('EDITOR','tiny_mce');

	/**
	 * Image handling library
	 * Set the path to the ImageMagick binaries
	 */
	define('IMAGEMAGICK','/usr/bin');

	/**
	 * Import global functions that we use for many applications we write
	 */
	include(FRAMEWORK.'/ITSFunctions.inc');

	/**
	 * Session Startup
	 */
	session_start();

	/**
	 * Language Negotiation
	 * Order of precedence: GET,SESSION, HTTP_ACCEPT_LANGUAGE, en
	 */
	 define('DEFAULT_LANGUAGE','en');
	 if (isset($_GET['lang'])) { $_SESSION['LANGUAGE'] = strtolower(substr($_GET['lang'],0,2)); }
	 if (!isset($_SESSION['LANGUAGE']))
	 {
	 	if (isset($_SERVER['HTTP_ACCEPT_LANGUAGE'])) { $_SESSION['LANGUAGE'] = strtolower(substr($_SERVER['HTTP_ACCEPT_LANGUAGE'],0,2)); }
	 	else { $_SESSION['LANGUAGE'] = DEFAULT_LANGUAGE; }
	 }

	/**
	 * Skin Negotiation
	 * Order of precedence: GET, SESSION, default
	 */
	if (isset($_GET['skin'])) { $_SESSION['skin'] = $_GET['skin']; }
	if (!isset($_SESSION['skin'])) { $_SESSION['skin'] = 'default'; }

	/**
	 * External Web Services
	 */
	define('DIRECTORY_WEBSERVICE','http://isotope.bloomington.in.gov/directory');

	/**
	 * Bad URL Definitions
	 * Regular expressions defining what bad links would look like
	 * URLs that match these regular expressions will be treated as bad
	 * links by the WikiMarkup parser
	 * Each of these must be a regular expression in Perl syntax
	 */
	 $BAD_LINK_EXPRESSIONS = array(
		'/http:\/\/bloomington\.in\.gov/',
		'/http:\/\/www\.bloomington\.in\.gov/'
	 );
?>