set foreign_key_checks=0;
-- ------------------------------------------------------------------
-- Identify all the departments of the city
-- ------------------------------------------------------------------
create table departments (
	id int unsigned not null primary key auto_increment,
	name varchar(50) not null unique,
	address1 varchar(128),
	address2 varchar(128),
	city varchar(128),
	state varchar(50),
	zip varchar(15),
	phone varchar(20),
	email varchar(128),
	ldap_name varchar(128),
	document_id int unsigned,
	location_id int unsigned,
	foreign key (document_id) references documents(id),
	foreign key (location_id) references locations(id)
) engine=InnoDB;
insert departments set id=1,name='IT Department';

-- -------------------------------------------------------------------
-- User tables
-- -------------------------------------------------------------------
create table users (
  id int unsigned not null primary key auto_increment,
  username varchar(128) not null,
  password varchar(32) default null,
  authenticationMethod varchar(40) not null default 'LDAP',
  firstname varchar(128),
  lastname varchar(128),
  department_id int unsigned,
  email varchar(255) not null,
  access enum('private','public') not null default 'private',
  unique key (username),
  foreign key (department_id) references departments(id)
) engine=InnoDB;
insert users set id=1,username='administrator',password=md5('welcome'),authenticationMethod='local',
firstname='Administrator',lastname='User',department_id=1;

create table roles (
  id int unsigned not null primary key auto_increment,
  role varchar(30) not null unique
) engine=InnoDB;
insert roles set role='Administrator';
insert roles set role='Webmaster';
insert roles set role='Publisher';
insert roles set role='Content Creator';

create table user_roles (
  user_id int unsigned not null,
  role_id int unsigned not null,
  primary key  (user_id,role_id),
  foreign key (user_id) references users (id),
  foreign key (role_id) references roles (id)
) engine=InnoDB;
insert user_roles values(1,1);

create table pendingUsers (
	id int unsigned not null primary key auto_increment,
	email varchar(255) not null unique,
	password varchar(32) not null,
	date date not null
) engine=InnoDB;

-- -------------------------------------------------------------------
-- Document tables
-- -------------------------------------------------------------------
create table documentTypes (
	id int unsigned not null primary key auto_increment,
	type varchar(128) not null,
	template text not null,
	ordering varchar(50) not null default 'title',
	defaultFacetGroup_id int unsigned,
	documentInfoFields varchar(255),
	media_id int unsigned,
	seperateInSearch boolean not null default 0,
	listTemplate varchar(128) not null,
	foreign key (defaultFacetGroup_id) references facetGroups(id),
	foreign key (media_id) references media(id)
) engine=InnoDB;
insert documentTypes set type='Webpage';

create table documents (
  id int unsigned not null primary key auto_increment,
  title varchar(128) not null unique,
  wikiTitle varchar(128) not null,
  alias varchar(128),
  feature_title varchar(128),
  created timestamp not null default 0,
  createdBy int unsigned not null,
  modified timestamp default CURRENT_TIMESTAMP on update CURRENT_TIMESTAMP,
  modifiedBy int unsigned not null,
  publishDate date not null,
  retireDate date,
  department_id int unsigned not null,
  documentType_id int unsigned not null default 1,
  description varchar(255),
  lockedBy int unsigned,
  enablePHP tinyint(1) unsigned not null default 0,
  banner_media_id int unsigned,
  icon_media_id int unsigned,
  skin varchar(128),
  foreign key (createdBy) references users(id),
  foreign key (modifiedBy) references users(id),
  foreign key (department_id) references departments(id),
  foreign key (documentType_id) references documentTypes(id),
  foreign key (lockedBy) references users(id),
  foreign key (banner_media_id) references media(id),
  foreign key (icon_media_id) references media(id)
) engine=InnoDB;
insert documents set id=1,title='Welcome',department_id=1,created=now();

create table documentLinks (
	id int unsigned not null primary key auto_increment,
	document_id int unsigned not null,
	href varchar(255) not null,
	title varchar(128) not null,
	description varchar(255) not null,
	created date not null,
	unique (document_id,href),
	foreign key (document_id) references documents(id)
) engine=InnoDB;

create table document_watches (
	document_id int unsigned not null,
	user_id int unsigned not null,
	primary key (document_id,user_id),
	foreign key (document_id) references documents(id) on delete cascade,
	foreign key (user_id) references users(id) on delete cascade
) engine=InnoDB;

-- -------------------------------------------------------------------
-- Log tables.  These should not get backed up.  When restoring
-- from backup, you will need to recreate these tables by hand.
-- The easiest way is to just copy and paste from here
-- -------------------------------------------------------------------
create table search_log (
	queryString varchar(128) not null,
	access_time timestamp not null default CURRENT_TIMESTAMP
) engine=Archive;

create table file_not_found_log (
	path varchar(128) not null,
	access_time timestamp not null default CURRENT_TIMESTAMP,
	referer varchar(255)
) engine=Archive;

create table document_accesslog (
	document_id int unsigned not null,
	access_time timestamp not null default CURRENT_TIMESTAMP
) engine=Archive;

create table document_hits_yearly (
	year year(4) not null,
	document_id int unsigned not null,
	hits int unsigned not null,
	foreign key (document_id) references documents(id) on delete cascade
) engine=InnoDB;

create table document_hits_monthly (
	date date not null,
	document_id int unsigned not null,
	hits int unsigned not null,
	foreign key (document_id) references documents(id) on delete cascade
) engine=InnoDB;

create table document_hits_daily (
	date date not null,
	document_id int unsigned not null,
	hits int unsigned not null,
	key (date),
	foreign key (document_id) references documents(id) on delete cascade
) engine=InnoDB;

create table document_hits_running_totals (
	document_id int unsigned not null,
	hits int unsigned not null,
	foreign key (document_id) references documents(id) on delete cascade
) engine=InnoDB;

-- -------------------------------------------------------------------
-- Section tables
-- -------------------------------------------------------------------
create table sections (
  id int unsigned not null primary key auto_increment,
  name varchar(128) not null unique,
  nickname varchar(50),
  sectionDocument_id int unsigned,
  placement tinyint(2) unsigned,
  highlightSubscription boolean,
  foreign key (sectionDocument_id) references sectionDocuments(id) on delete set null
) engine=InnoDB;
insert sections set id=1,name='Welcome';

create table section_departments (
	section_id int unsigned not null,
	department_id int unsigned not null,
	primary key (section_id,department_id),
	foreign key (section_id) references sections(id),
	foreign key (department_id) references departments(id)
) engine=InnoDB;

create table section_parents (
	id int unsigned not null primary key auto_increment,
	section_id int unsigned not null,
	parent_id int unsigned not null,
	placement tinyint(2) unsigned not null default 99,
	foreign key (section_id) references sections (id),
	foreign key (parent_id) references sections (id),
	unique (section_id,parent_id)
) engine=InnoDB;

create table sectionIndex (
  section_id int unsigned not null,
  preOrder int unsigned default null,
  postOrder int unsigned default null,
  foreign key (section_id) references sections (id)
) engine=InnoDB;

create table sectionDocuments (
	id int unsigned not null primary key auto_increment,
	section_id int unsigned not null,
	document_id int unsigned not null,
	featured tinyint(1) unsigned not null default 0,
	unique(section_id,document_id),
	foreign key (section_id) references sections (id) on delete cascade,
	foreign key (document_id) references documents (id) on delete cascade
) engine=InnoDB;
insert sectionDocuments set id=1,section_id=1,document_id=1;
update sections set sectionDocument_id=1 where id=1;

create table section_subscriptions (
	id int unsigned not null primary key auto_increment,
	section_id int unsigned not null,
	user_id int unsigned not null,
	unique (section_id,user_id),
	foreign key (section_id) references sections(id),
	foreign key (user_id) references users(id)
) engine=InnoDB;

-- -------------------------------------------------------------------
-- Facet tables
-- -------------------------------------------------------------------
create table facetGroups (
	id int unsigned not null primary key auto_increment,
	name varchar(128) not null
) engine=InnoDB;

create table facets (
  id int unsigned not null primary key auto_increment,
  name varchar(50) not null unique,
  facetGroup_id int unsigned not null,
  description text,
  ordering tinyint(2) unsigned,
  foreign key (facetGroup_id) references facetGroups(id)
) engine=InnoDB;

create table document_facets (
  document_id int unsigned not null,
  facet_id int unsigned not null,
  primary key (document_id,facet_id),
  foreign key (document_id) references documents (id) on delete cascade,
  foreign key (facet_id) references facets (id) on delete cascade
) engine=InnoDB;

create table facetGroups_related (
	facetGroup_id int unsigned not null,
	relatedGroup_id int unsigned not null,
	primary key (facetGroup_id,relatedGroup_id),
	foreign key (facetGroup_id) references facetGroups(id),
	foreign key (relatedGroup_id) references facetGroups(id)
) engine=InnoDB;

create table facetGroup_departments (
	facetGroup_id int unsigned not null,
	department_id int unsigned not null,
	primary key (facetGroup_id,department_id),
	foreign key (facetGroup_id) references facetGroups(id),
	foreign key (department_id) references departments(id)
) engine=InnoDB;


-- -------------------------------------------------------------------
-- Widgets
-- -------------------------------------------------------------------
create table panels (
	id int unsigned not null primary key auto_increment,
	name varchar(128) not null unique
) engine=InnoDB;
insert panels set name='leftSidebar';
insert panels set name='rightSidebar';
insert panels set name='mainContent';
insert panels set name='banner';
insert panels set name='alerts';

create table widgets (
	id int unsigned not null primary key auto_increment,
	class varchar(128) not null unique,
	global_panel_id int unsigned,
	global_layout_order tinyint(2) unsigned,
	global_data text,
	default_panel_id int unsigned,
	default_layout_order tinyint(2) unsigned,
	default_data text,
	foreign key (global_panel_id) references panels(id),
	foreign key (default_panel_id) references panels(id)
) engine=InnoDB;
insert widgets set class='AdminToolsWidget',global_panel_id=1;

create table section_widgets (
	id int unsigned not null primary key auto_increment,
	section_id int unsigned not null,
	widget_id int unsigned not null,
	panel_id int unsigned not null default 1,
	layout_order tinyint(2) unsigned,
	data text,
	foreign key (section_id) references sections(id),
	foreign key (widget_id) references widgets(id),
	foreign key (panel_id) references panels(id)
) engine=InnoDB;

create table alertTypes (
	id int unsigned not null primary key auto_increment,
	name varchar(128) not null
) engine=InnoDB;
insert alertTypes set name='Custom';
insert alertTypes set name='Weather';

create table alerts (
	id int unsigned not null primary key auto_increment,
	title varchar(128) not null unique,
	alertType_id int unsigned not null default 1,
	startTime timestamp not null,
	endTime timestamp not null,
	url varchar(255),
	text text,
	foreign key (alertType_id) references alertTypes(id)
) engine=InnoDB;


-- -------------------------------------------------------------------
-- Languages
-- -------------------------------------------------------------------
create table languages (
	id int unsigned not null primary key auto_increment,
	code char(3) not null,
	english varchar(128) not null,
	native varchar(128) not null,
	direction enum('ltr','rtl') not null default 'ltr',
	unique (code)
) engine=InnoDB CHARACTER SET utf8;
insert languages (code,english,native) values ('en','English','English');
insert languages (code,english,native) values ('fr','French','Français');
insert languages (code,english,native) values ('es','Spanish','Español');
insert languages (code,english,native) values ('de','German','Deutsch');
insert languages (code,english,native) values ('it','Italian','Italiano');
insert languages (code,english,native) values ('ko','Korean','한국어');
insert languages (code,english,native) values ('ja','Japanese','日本語');
insert languages (code,english,native) values ('zh','Chinese','中文');
insert languages (code,english,native) values ('fi','Finnish','Suomi');
insert languages (code,english,native) values ('tr','Turkish','Türkçe');

-- -------------------------------------------------------------------
-- Events
-- -------------------------------------------------------------------
create table locationTypes (
	id int unsigned not null primary key auto_increment,
	type varchar(128) not null
) engine=InnoDB;
insert locationTypes set type='City';
insert locationTypes set type='Non-City';

create table locations (
	id int unsigned not null primary key auto_increment,
	name varchar(60) not null,
	locationType_id int unsigned not null default 1,
	address varchar(128) not null,
        phone varchar(15),
	description text not null,
        website varchar(255),
	content text,
	latitude float(10,6),
	longitude float(10,6),
	department_id int unsigned not null,
	handicap_accessible boolean not null default false,
	foreign key (locationType_id) references locationTypes(id),
	foreign key (department_id) references departments(id)
) engine=InnoDB;

create table locationGroups (
	id int unsigned not null primary key auto_increment,
	name varchar(128) not null,
	department_id int unsigned not null,
	description text,
	foreign key (department_id) references departments(id)
) engine=InnoDB;

create table locationGroup_locations (
	locationGroup_id int unsigned not null,
	location_id int unsigned not null,
	primary key (locationGroup_id,location_id),
	foreign key (locationGroup_id) references locationGroups(id),
	foreign key (location_id) references locations(id)
) engine=InnoDB;

create table calendars (
	id int unsigned not null primary key auto_increment,
	name varchar(128) not null,
	description varchar(255) not null,
	user_id int unsigned not null,
	foreign key (user_id) references users(id)
) engine=InnoDB;

create table calendar_departments (
	calendar_id int unsigned not null,
	department_id int unsigned not null,
	primary key (calendar_id,department_id),
	foreign key (calendar_id) references calendars(id),
	foreign key (department_id) references departments(id)
) engine=InnoDB;

create table events (
	id int unsigned not null primary key auto_increment,
	start datetime not null,
	end datetime,
	created datetime not null,
	modified datetime not null,
	title varchar(128) not null,
	description text,
	allDayEvent tinyint(1) unsigned,
	rrule_freq enum('DAILY','WEEKLY','MONTHLY'),
	rrule_until datetime,
	rrule_count tinyint unsigned,
	rrule_interval tinyint unsigned,
	rrule_byday varchar(128),
	rrule_bymonthday varchar(128),
	rrule_bysetpos tinyint,
	calendar_id int unsigned not null,
	location_id int unsigned,
	user_id int unsigned not null,
	contact_name varchar(128),
	contact_phone varchar(128),
	contact_email varchar(128),
	foreign key (calendar_id) references calendars(id),
	foreign key (location_id) references locations(id),
	foreign key (user_id) references users(id)
) engine=InnoDB;

create table event_exceptions (
	event_id int unsigned not null,
	original_start datetime not null,
	start datetime not null,
	end datetime not null,
	primary key (event_id,original_start),
	foreign key (event_id) references events(id)
) engine=InnoDB;

create table event_sections (
	event_id int unsigned not null,
	section_id int unsigned not null,
	primary key (event_id,section_id),
	foreign key (event_id) references events(id),
	foreign key (section_id) references sections(id)
) engine=InnoDB;


-- -------------------------------------------------------------------
-- Media
-- -------------------------------------------------------------------
create table media (
	id int unsigned not null primary key auto_increment,
	filename varchar(128) not null,
	mime_type varchar(128) not null,
	media_type varchar(24) not null,
	title varchar(128) not null,
	description varchar(255) not null,
	md5 varchar(32) not null unique,
	department_id int unsigned not null,
	uploaded timestamp not null default CURRENT_TIMESTAMP,
	user_id int unsigned not null,
	foreign key (department_id) references departments(id),
	foreign key (user_id) references users(id)
) engine=InnoDB;

create table media_documents (
	media_id int unsigned not null,
	document_id int unsigned not null,
	primary key (media_id,document_id),
	foreign key (media_id) references media(id) on delete cascade,
	foreign key (document_id) references documents(id) on delete cascade
) engine=InnoDB;

set foreign_key_checks=1;
