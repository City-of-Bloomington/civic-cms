---------------------------------------------------------------------
-- Category tables
---------------------------------------------------------------------
create table categories (
  id int(10) unsigned not null primary key auto_increment,
  name varchar(50) not null unique
) engine=InnoDB;
insert categories values(1,'root');

create table category_parents (
  category_id int(10) unsigned not null,
  parent_id int(10) unsigned not null,
  foreign key (category_id) references categories (id),
  foreign key (parent_id) references categories (id)
) engine=InnoDB;

create table categoryIndex (
  category_id int(10) unsigned not null,
  preOrder int(10) unsigned default null,
  postOrder int(10) unsigned default null,
  foreign key (category_id) references categories (id)
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
  dateTimeCreated timestamp not null default current_timestamp
) engine=InnoDB;

create table document_categories (
  document_id int(10) unsigned not null,
  category_id int(10) unsigned not null,
  foreign key (document_id) references documents (id),
  foreign key (category_id) references categories (id)
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
  unique key (username)
) engine=InnoDB;

create table roles (
  id int(10) unsigned not null primary key auto_increment,
  role varchar(30) not null unique
) engine=InnoDB;
insert roles set role='Administrator';

create table user_roles (
  user_id int(10) unsigned not null,
  role_id int(10) unsigned not null,
  primary key  (user_id,role_id),
  foreign key (user_id) references users (id),
  foreign key (role_id) references roles (id)
) engine=InnoDB;

