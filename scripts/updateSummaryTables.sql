-- @copyright Copyright (C) 2008 City of Bloomington, Indiana. All rights reserved.
-- @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
-- @author Cliff Ingham <inghamn@bloomington.in.gov>
delete from document_hits_yearly;
delete from document_hits_monthly;
delete from document_hits_daily;

-- Insert data from the log file for documents that have not been deleted
-- We join on the documents table, and anything that's null should be ignored
insert document_hits_yearly
select year(access_time) as year,document_id,count(*) from document_accesslog
left join documents on document_id=id where id is not null
group by year,document_id;


insert document_hits_monthly
select concat_ws('-',year(access_time),month(access_time),1) as date,document_id,count(*) from document_accesslog
left join documents on document_id=id where id is not null
group by date,document_id;


insert document_hits_daily
select date(access_time) as date,document_id,count(*) from document_accesslog
left join documents on document_id=id where id is not null
group by date,document_id;
