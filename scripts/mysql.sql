---------------------------------------------------------------------
-- Category tables
---------------------------------------------------------------------
create table categories (
  id int(10) unsigned not null primary key auto_increment,
  name varchar(50) not null
) engine=InnoDB;
insert categories set name='Home';

create table category_parents (
  category_id int(10) unsigned not null,
  parent_id int(10) unsigned not null,
  foreign key (category_id) references categories (id),
  foreign key (parent_id) references categories (id)
) engine=InnoDB;

create table categoryIndex (
  category_id int(10) unsigned not null,
  preorder int(10) unsigned default null,
  postorder int(10) unsigned default null,
  top int(10) unsigned default null,
  foreign key (category_id) references categories (id)
) engine=InnoDB;


---------------------------------------------------------------------
-- Facet tables
---------------------------------------------------------------------
create table facets (
  id int(10) unsigned not null primary key auto_increment,
  name varchar(50) not null
) engine=InnoDB default;
insert facets set name='root';

create table facet_parents (
  facet_id int(10) unsigned not null,
  parent_id int(10) unsigned not null,
  foreign key (facet_id) references facets (id),
  foreign key (parent_id) references facets (id)
) engine=InnoDB;

create table facetIndex (
  facet_id int(10) unsigned not null,
  preorder int(10) unsigned not null,
  postorder int(10) unsigned not null,
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
  authenticationmethod varchar(40) not null default 'LDAP',
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


---------------------------------------------------------------------
-- Stored procedure for updating the category index.
-- This should be run whenever the category_parents table is touched
---------------------------------------------------------------------
delimiter $
create procedure rebuildCategoryIndex()
begin
	declare maxrightedge, rows smallint default 0;
	declare current smallint default 1;
	declare nextedge smallint default 2;
	create temporary table tree like category_parents;
	insert tree select * from category_parents;
	delete from categoryindex;
	set maxrightedge = 2 * (1 + (select count(*) from tree));
	insert categoryindex values(1,1,maxrightedge,1);
	while nextedge < maxrightedge do
		select * from categoryindex s inner join tree t on s.category_id=t.parent_id and s.top=current;
		set rows = found_rows();
		if rows > 0 then
			begin
				insert categoryindex
				select min(t.category_id),nextedge,null,current+1
				from categoryindex s inner join tree t on s.category_id=t.parent_id and s.top=current;
				delete from tree where category_id=(select category_id from categoryindex where top=(current+1));
				set nextedge = nextedge + 1;
				set current = current + 1;
			end;
		else
			begin
				update categoryindex set postorder=nextedge,top=-top where top=current;
				set nextedge=nextedge+1;
				set current=current-1;
			end;
		end if;
	end while;
end$
delimiter ;
