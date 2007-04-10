---------------------------------------------------------------------
-- Identify all the departments of the city
---------------------------------------------------------------------
create table departments (
	id int unsigned not null primary key auto_increment,
	name varchar(50) not null unique
) engine=InnoDB;

---------------------------------------------------------------------
-- User tables
---------------------------------------------------------------------
create table users (
  id int unsigned not null primary key auto_increment,
  username varchar(30) not null,
  password varchar(32) default null,
  authenticationMethod varchar(40) not null default 'LDAP',
  firstname varchar(128) not null,
  lastname varchar(128) not null,
  department_id int unsigned not null,
  email varchar(255) not null,
  unique key (username),
  foreign key (department_id) references departments(id)
) engine=InnoDB;

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

---------------------------------------------------------------------
-- Document tables
---------------------------------------------------------------------
create table documentTypes (
	id int unsigned not null primary key auto_increment,
	type varchar(128) not null,
	template text not null
) engine=InnoDB;
insert documentTypes set type='Webpage';

create table documents (
  id int unsigned not null primary key auto_increment,
  title varchar(128) not null,
  created timestamp not null default 0,
  createdBy int unsigned not null,
  modified timestamp default CURRENT_TIMESTAMP on update CURRENT_TIMESTAMP,
  modifiedBy int unsigned not null,
  publishDate date not null,
  retireDate date,
  department_id int unsigned not null,
  documentType_id int unsigned not null default 1,
  foreign key (createdBy) references users(id),
  foreign key (modifiedBy) references users(id),
  foreign key (department_id) references departments(id),
  foreign key (documentType_id) references documentTypes(id)
) engine=InnoDB;

create table document_watches (
	document_id int unsigned not null,
	user_id int unsigned not null,
	primary key (document_id,user_id),
	foreign key (document_id) references documents(id) on delete cascade,
	foreign key (user_id) references users(id) on delete cascade
) engine=InnoDB;
---------------------------------------------------------------------
-- Section tables
---------------------------------------------------------------------
create table sections (
  id int unsigned not null primary key auto_increment,
  name varchar(50) not null unique,
  document_id int unsigned not null,
  placement tinyint(2) unsigned,
  foreign key (document_id) references documents(id)
) engine=InnoDB;

create table section_departments (
	section_id int unsigned not null,
	department_id int unsigned not null,
	primary key (section_id,department_id),
	foreign key (section_id) references sections(id),
	foreign key (department_id) references departments(id)
) engine=InnoDB;

create table section_parents (
	node_id int unsigned not null primary key auto_increment,
	section_id int unsigned not null,
	parent_id int unsigned not null,
	placement tinyint(2) unsigned not null,
	foreign key (section_id) references sections (id),
	foreign key (parent_id) references sections (id)
) engine=InnoDB;

create table sectionIndex (
  section_id int unsigned not null,
  preOrder int unsigned default null,
  postOrder int unsigned default null,
  foreign key (section_id) references sections (id)
) engine=InnoDB;

create table document_sections (
  document_id int unsigned not null,
  section_id int unsigned not null,
  foreign key (document_id) references documents (id) on delete cascade,
  foreign key (section_id) references sections (id)
) engine=InnoDB;


---------------------------------------------------------------------
-- Facet tables
---------------------------------------------------------------------
create table facets (
  id int unsigned not null primary key auto_increment,
  name varchar(50) not null unique
) engine=InnoDB;

create table document_facets (
  document_id int unsigned not null,
  facet_id int unsigned not null,
  primary key (document_id,facet_id),
  foreign key (document_id) references documents (id) on delete cascade,
  foreign key (facet_id) references facets (id) on delete cascade
) engine=InnoDB;



---------------------------------------------------------------------
-- Widgets
---------------------------------------------------------------------
create table widgets (
	name varchar(128) not null primary key
) engine=InnoDB;

create table section_widgets (
	section_id int unsigned not null,
	widget_name varchar(128) not null,
	layout_order tinyint(2) unsigned not null,
	primary key (section_id,widget_name),
	foreign key (section_id) references sections(id),
	foreign key (widget_name) references widgets(name)
) engine=InnoDB;

---------------------------------------------------------------------
-- Languages
---------------------------------------------------------------------
create table languages (
	code char(2) not null primary key,
	english varchar(128) not null,
	native varchar(128) not null
) engine=InnoDB CHARACTER SET utf8;
insert languages values
('en','English','English'),
('fr','French','Français'),
('es','Spanish','Español'),
('de','German','Deutsch'),
('it','Italian','Italiano'),
('ko','Korean','한국어'),
('ja','Japanese','日本語'),
('zh','Chinese','中文');

---------------------------------------------------------------------
-- Events
---------------------------------------------------------------------
create table locations (
	id int unsigned not null primary key auto_increment,
	name varchar(60) not null
) engine=InnoDB;

create table calendars (
	id int unsigned not null primary key auto_increment,
	name varchar(128) not null,
	department_id int unsigned not null,
	user_id int unsigned not null,
	foreign key (department_id) references departments(id),
	foreign key (user_id) references users(id)
) engine=InnoDB;

create table events (
	id int unsigned not null primary key auto_increment,
	created timestamp not null default CURRENT_TIMESTAMP,
	start datetime not null,
	end datetime not null,
	allDayEvent tinyint(1) unsigned,
	rrule varchar(128),
	summary varchar(128) not null,
	description text,
	calendar_id int unsigned not null,
	location_id int unsigned,
	user_id int unsigned not null,
	foreign key (calendar_id) references calendars(id),
	foreign key (location_id) references locations(id),
	foreign key (user_id) references users(id)
) engine=InnoDB;

create table eventIndex (
	event_id int unsigned not null,
	datetime datetime not null,
	foreign key (event_id) references events(id)
) engine=InnoDB;

create table event_sections (
	event_id int unsigned not null,
	section_id int unsigned not null,
	primary key (event_id,section_id),
	foreign key (event_id) references events(id),
	foreign key (section_id) references sections(id)
) engine=InnoDB;

---------------------------------------------------------------------
-- Media
---------------------------------------------------------------------
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
	uploadedBy int unsigned not null,
	foreign key (department_id) references departments(id),
	foreign key (uploadedBy) references users(id)
) engine=InnoDB;

create table media_documents (
	media_id int unsigned not null,
	document_id int unsigned not null,
	primary key (media_id,document_id),
	foreign key (media_id) references media(id) on delete cascade,
	foreign key (document_id) references documents(id) on delete cascade
) engine=InnoDB;
