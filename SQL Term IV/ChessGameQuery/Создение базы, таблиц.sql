create database Chess

create table Figures (
IdF int primary key,
TypeF char(6) not null check(TypeF IN ('king', 'queen', 'castle', 'knight', 'bishop', 'pawn')),
ColorF bit not null ) 

create table Board (
IdF int primary key references Figures(IdF),
X int not null check (X like '[1-8]'),
Y char(1) not null check(Y like '[A-H]'),
unique(X, Y)
)