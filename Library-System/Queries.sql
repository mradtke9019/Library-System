DROP TABLE IF EXISTS Books;
DROP TABLE IF EXISTS Authors;
DROP TABLE IF EXISTS Members;
DROP TABLE IF EXISTS Contributors;
DROP TABLE IF EXISTS Checkouts;
-- Test comment
-- Test comment 2
Create Table IF NOT EXISTS Books(
	ISBN int,
	Copies int check(Copies > 0),
	Title varchar(50) not null,
	Summary varchar(200),
	Primary Key (ISBN)
)


Create Table IF NOT EXISTS Authors (
	Id Integer primary key AUTOINCREMENT not null,
	Name varchar(50) not null,
	Address varchar(50),
	Phone varchar(15)
)

Create Table If Not Exists Members (
	Id Integer primary key AUTOINCREMENT not null,
	Name varchar(50) not null,
	Address varchar(50),
	Email varchar (50) check(Email like '%@%'),
	Phone varchar(15)
)

Create Table Contributors(
	BookISBN int,
	AuthorId int,
	Primary key (BookISBN, AuthorId),
	Foreign Key (BookISBN) references Books,
	Foreign Key (AuthorId) references Authors
)



Create Table Checkouts(
	BookISBN int,
	MemberId int,
	Counter int,
	LoanDate DateTime,
	DueDate DateTime,
	Primary Key (BookISBN, MemberId, Counter), 
	Foreign Key (BookISBN) references Books,
	Foreign Key (MemberId) references Members
)

SELECT sql 
FROM sqlite_master 
WHERE name = 'albums'