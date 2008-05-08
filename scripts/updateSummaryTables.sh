#!/bin/sh
# @copyright Copyright (C) 2008 City of Bloomington, Indiana. All rights reserved.
# @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
# @author Cliff Ingham <inghamn@bloomington.in.gov>
#
# Updates the Summary tables in the database for the content manager.
#
# The content manager keeps a full access_log as a table.  However, reading
# real-time statistics from this table is very slow.  We created Summary tables
# in the content manager, but they need to be updated periodically.
# Add this CRON script to your system however often you want to update
# the summary tables.  We recommend daily updates
MYSQL=/usr/local/mysql/bin/mysql
MYSQL_DATABASE=database_name
MYSQL_USER=username
MYSQL_PASS=password
CONTENT_MANAGER=/var/www/sites/content_manager

$MYSQL --user="$MYSQL_USER" --password="$MYSQL_PASS" $MYSQL_DATABASE < $CONTENT_MANAGER/scripts/updateSummaryTables.sql
