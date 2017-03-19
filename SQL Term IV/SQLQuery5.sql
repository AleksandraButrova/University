
create table SupplyE(
portA  char(30) not null check(portA like '[A-Z]%[a-z]%')
,portE char(30) not null check(portE like '[A-Z]%[a-z]%')
,amount int not null
,dateE date not null
,ship char(30) not null	 check(ship like '[A-Z]%[a-z]%')
primary key(dateE, ship, portA, portE)
foreign key (ship, portA) references Ship(name, portA),
foreign key (portE) references Ship(portE),
foreign key (portA)references Ship(portA)
)
