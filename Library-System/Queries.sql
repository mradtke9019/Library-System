Create Table IF NOT EXISTS Books(
	ISBN int,
	Copies int check(Copies > 0),
	Title varchar(50) not null,
	Summary varchar(200),
	Primary Key (ISBN)
);


Create Table IF NOT EXISTS Authors (
	Id Integer primary key AUTOINCREMENT not null,
	Name varchar(50) not null,
	Address varchar(50),
	Phone varchar(15)
);

Create Table If Not Exists Members (
	Id Integer primary key AUTOINCREMENT not null,
	Name varchar(50) not null,
	Address varchar(50),
	Email varchar (50) check(Email like '%@%') unique,
	Phone varchar(15)
);

Create Table If Not Exists Contributors(
	BookISBN int,
	AuthorId int,
	Primary key (BookISBN, AuthorId),
	Foreign Key (BookISBN) references Books,
	Foreign Key (AuthorId) references Authors
);



Create Table If Not Exists Checkouts(
	BookISBN int,
	MemberId int,
	LoanDate DateTime not null,
	DueDate DateTime not null,
	Primary Key (BookISBN, MemberId), 
	Foreign Key (BookISBN) references Books,
	Foreign Key (MemberId) references Members
);