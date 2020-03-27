Create Table If Not Exists Members(
	Id Integer primary key AUTOINCREMENT not null,
	Name varchar(50) not null,
	Address varchar(50),
	Email varchar (50) check(Email like '%@%'),
	Phone varchar(15)
)