---------------------------------------------------------------------
-- Identify all the departments of the city
---------------------------------------------------------------------
create table departments (
	id int unsigned not null primary key auto_increment,
	name varchar(50) not null unique
) engine=InnoDB;
insert departments set name='City Clerk';
insert departments set name='Community and Family Resources (CFRD)';
insert departments set name='Controller';
insert departments set name='Council Office';
insert departments set name='Employee Services';
insert departments set name='Housing and Neighborhood Development (HAND)';
insert departments set name='Information & Technology Services (ITS)';
insert departments set name='Legal';
insert departments set name='Office of the Mayor (OOTM)';
insert departments set name='Parks and Recreation';
insert departments set name='Planning';
insert departments set name='Public Works';
insert departments set name='Fire';
insert departments set name='Police';
insert departments set name='Utilities';

---------------------------------------------------------------------
-- Section tables
---------------------------------------------------------------------
create table sections (
  id int(10) unsigned not null primary key auto_increment,
  name varchar(50) not null unique,
  department_id int unsigned not null,
  foreign key (department_id) references departments(id)
) engine=InnoDB;
insert sections values(1,'root',(select id from departments where name="Information & Technology Services (ITS)"));

create table section_parents (
  section_id int(10) unsigned not null,
  parent_id int(10) unsigned not null,
  foreign key (section_id) references sections (id),
  foreign key (parent_id) references sections (id)
) engine=InnoDB;

create table sectionIndex (
  section_id int(10) unsigned not null,
  preOrder int(10) unsigned default null,
  postOrder int(10) unsigned default null,
  foreign key (section_id) references sections (id)
) engine=InnoDB;

---------------------------------------------------------------------
-- Facet tables
---------------------------------------------------------------------
create table facets (
  id int(10) unsigned not null primary key auto_increment,
  name varchar(50) not null
) engine=InnoDB;
insert facets set name='root';

create table facet_parents (
  facet_id int(10) unsigned not null,
  parent_id int(10) unsigned not null,
  foreign key (facet_id) references facets (id),
  foreign key (parent_id) references facets (id)
) engine=InnoDB;

create table facetIndex (
  facet_id int(10) unsigned not null,
  preOrder int(10) unsigned not null,
  postOrder int(10) unsigned not null,
  foreign key (facet_id) references facets (id)
) engine=InnoDB;


---------------------------------------------------------------------
-- Document tables
---------------------------------------------------------------------
create table documents (
  id int(10) unsigned not null primary key auto_increment,
  dateTimeCreated timestamp not null default current_timestamp,
  department_id int unsigned not null,
  foreign key (department_id) references departments(id)
) engine=InnoDB;

create table document_sections (
  document_id int(10) unsigned not null,
  section_id int(10) unsigned not null,
  foreign key (document_id) references documents (id),
  foreign key (section_id) references sections (id)
) engine=InnoDB;

create table document_facets (
  document_id int(10) unsigned not null,
  facet_id int(10) unsigned not null,
  foreign key (document_id) references documents (id),
  foreign key (facet_id) references facets (id)
) engine=InnoDB;


---------------------------------------------------------------------
-- User tables
---------------------------------------------------------------------
create table users (
  id int(10) unsigned not null primary key auto_increment,
  username varchar(30) not null,
  password varchar(32) default null,
  authenticationMethod varchar(40) not null default 'LDAP',
  firstname varchar(128) not null,
  lastname varchar(128) not null,
  department_id int unsigned not null,
  unique key (username),
  foreign key (department_id) references departments(id)
) engine=InnoDB;

create table roles (
  id int(10) unsigned not null primary key auto_increment,
  role varchar(30) not null unique
) engine=InnoDB;
insert roles set role='Administrator';
insert roles set role='Webmaster';
insert roles set role='Publisher';
insert roles set role='Content Creator';

create table user_roles (
  user_id int(10) unsigned not null,
  role_id int(10) unsigned not null,
  primary key  (user_id,role_id),
  foreign key (user_id) references users (id),
  foreign key (role_id) references roles (id)
) engine=InnoDB;
