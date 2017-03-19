USE [master]
GO
/****** Object:  Database [MyCafe]    Script Date: 30.04.2015 22:38:07 ******/
CREATE DATABASE [MyCafe]
 CONTAINMENT = NONE
 ON  PRIMARY 
( NAME = N'MyCafe', FILENAME = N'C:\Program Files\Microsoft SQL Server\MSSQL11.SQLEXPRESS\MSSQL\DATA\MyCafe.mdf' , SIZE = 5120KB , MAXSIZE = UNLIMITED, FILEGROWTH = 1024KB )
 LOG ON 
( NAME = N'MyCafe_log', FILENAME = N'C:\Program Files\Microsoft SQL Server\MSSQL11.SQLEXPRESS\MSSQL\DATA\MyCafe_log.ldf' , SIZE = 2048KB , MAXSIZE = 2048GB , FILEGROWTH = 10%)
GO
ALTER DATABASE [MyCafe] SET COMPATIBILITY_LEVEL = 110
GO
IF (1 = FULLTEXTSERVICEPROPERTY('IsFullTextInstalled'))
begin
EXEC [MyCafe].[dbo].[sp_fulltext_database] @action = 'enable'
end
GO
ALTER DATABASE [MyCafe] SET ANSI_NULL_DEFAULT OFF 
GO
ALTER DATABASE [MyCafe] SET ANSI_NULLS OFF 
GO
ALTER DATABASE [MyCafe] SET ANSI_PADDING OFF 
GO
ALTER DATABASE [MyCafe] SET ANSI_WARNINGS OFF 
GO
ALTER DATABASE [MyCafe] SET ARITHABORT OFF 
GO
ALTER DATABASE [MyCafe] SET AUTO_CLOSE OFF 
GO
ALTER DATABASE [MyCafe] SET AUTO_SHRINK OFF 
GO
ALTER DATABASE [MyCafe] SET AUTO_UPDATE_STATISTICS ON 
GO
ALTER DATABASE [MyCafe] SET CURSOR_CLOSE_ON_COMMIT OFF 
GO
ALTER DATABASE [MyCafe] SET CURSOR_DEFAULT  GLOBAL 
GO
ALTER DATABASE [MyCafe] SET CONCAT_NULL_YIELDS_NULL OFF 
GO
ALTER DATABASE [MyCafe] SET NUMERIC_ROUNDABORT OFF 
GO
ALTER DATABASE [MyCafe] SET QUOTED_IDENTIFIER OFF 
GO
ALTER DATABASE [MyCafe] SET RECURSIVE_TRIGGERS OFF 
GO
ALTER DATABASE [MyCafe] SET  DISABLE_BROKER 
GO
ALTER DATABASE [MyCafe] SET AUTO_UPDATE_STATISTICS_ASYNC OFF 
GO
ALTER DATABASE [MyCafe] SET DATE_CORRELATION_OPTIMIZATION OFF 
GO
ALTER DATABASE [MyCafe] SET TRUSTWORTHY OFF 
GO
ALTER DATABASE [MyCafe] SET ALLOW_SNAPSHOT_ISOLATION OFF 
GO
ALTER DATABASE [MyCafe] SET PARAMETERIZATION SIMPLE 
GO
ALTER DATABASE [MyCafe] SET READ_COMMITTED_SNAPSHOT OFF 
GO
ALTER DATABASE [MyCafe] SET HONOR_BROKER_PRIORITY OFF 
GO
ALTER DATABASE [MyCafe] SET RECOVERY SIMPLE 
GO
ALTER DATABASE [MyCafe] SET  MULTI_USER 
GO
ALTER DATABASE [MyCafe] SET PAGE_VERIFY CHECKSUM  
GO
ALTER DATABASE [MyCafe] SET DB_CHAINING OFF 
GO
ALTER DATABASE [MyCafe] SET FILESTREAM( NON_TRANSACTED_ACCESS = OFF ) 
GO
ALTER DATABASE [MyCafe] SET TARGET_RECOVERY_TIME = 0 SECONDS 
GO
USE [MyCafe]
GO
/****** Object:  Table [dbo].[Bookkeeping]    Script Date: 30.04.2015 22:38:07 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
SET ANSI_PADDING ON
GO
CREATE TABLE [dbo].[Bookkeeping](
	[customer] [char](30) NOT NULL,
	[amount] [int] NOT NULL,
	[dateE] [date] NOT NULL,
	[ship] [char](30) NOT NULL,
PRIMARY KEY CLUSTERED 
(
	[customer] ASC,
	[dateE] ASC,
	[ship] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
) ON [PRIMARY]

GO
SET ANSI_PADDING OFF
GO
/****** Object:  Table [dbo].[Customer]    Script Date: 30.04.2015 22:38:07 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
SET ANSI_PADDING ON
GO
CREATE TABLE [dbo].[Customer](
	[name] [char](30) NOT NULL,
	[price] [int] NOT NULL,
PRIMARY KEY CLUSTERED 
(
	[name] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
) ON [PRIMARY]

GO
SET ANSI_PADDING OFF
GO
/****** Object:  Table [dbo].[Plantation]    Script Date: 30.04.2015 22:38:07 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
SET ANSI_PADDING ON
GO
CREATE TABLE [dbo].[Plantation](
	[id] [int] NOT NULL,
	[сountry] [char](30) NOT NULL,
	[manager] [char](30) NOT NULL,
	[portA] [char](30) NOT NULL,
PRIMARY KEY CLUSTERED 
(
	[id] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
) ON [PRIMARY]

GO
SET ANSI_PADDING OFF
GO
/****** Object:  Table [dbo].[PortA]    Script Date: 30.04.2015 22:38:07 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
SET ANSI_PADDING ON
GO
CREATE TABLE [dbo].[PortA](
	[name] [char](30) NOT NULL,
PRIMARY KEY CLUSTERED 
(
	[name] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
) ON [PRIMARY]

GO
SET ANSI_PADDING OFF
GO
/****** Object:  Table [dbo].[PortE]    Script Date: 30.04.2015 22:38:07 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
SET ANSI_PADDING ON
GO
CREATE TABLE [dbo].[PortE](
	[name] [char](30) NOT NULL,
PRIMARY KEY CLUSTERED 
(
	[name] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
) ON [PRIMARY]

GO
SET ANSI_PADDING OFF
GO
/****** Object:  Table [dbo].[Ship]    Script Date: 30.04.2015 22:38:07 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
SET ANSI_PADDING ON
GO
CREATE TABLE [dbo].[Ship](
	[name] [char](30) NOT NULL,
	[capacity] [int] NOT NULL,
	[portA] [char](30) NOT NULL,
	[portE] [char](30) NOT NULL,
	[cost] [int] NOT NULL,
PRIMARY KEY CLUSTERED 
(
	[name] ASC,
	[portA] ASC,
	[portE] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
) ON [PRIMARY]

GO
SET ANSI_PADDING OFF
GO
/****** Object:  Table [dbo].[SupplyA]    Script Date: 30.04.2015 22:38:07 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
SET ANSI_PADDING ON
GO
CREATE TABLE [dbo].[SupplyA](
	[plantation] [int] NOT NULL,
	[portA] [char](30) NOT NULL,
	[amount] [int] NOT NULL,
	[dateA] [date] NOT NULL
) ON [PRIMARY]

GO
SET ANSI_PADDING OFF
GO
/****** Object:  Table [dbo].[SupplyE]    Script Date: 30.04.2015 22:38:07 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
SET ANSI_PADDING ON
GO
CREATE TABLE [dbo].[SupplyE](
	[portA] [char](30) NOT NULL,
	[portE] [char](30) NOT NULL,
	[amount] [int] NOT NULL,
	[dateE] [date] NOT NULL,
	[ship] [char](30) NOT NULL,
PRIMARY KEY CLUSTERED 
(
	[dateE] ASC,
	[ship] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
) ON [PRIMARY]

GO
SET ANSI_PADDING OFF
GO
/****** Object:  View [dbo].[CommodityTurnover]    Script Date: 30.04.2015 22:38:07 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
/*Представления
1. Аналитикам хочется знать "товарооборот" между каждой парой европейских и южноамериканских портов. 
   Товарооборот -- это суммарный вес перевезенного кофе между двумя портами.
   Напишите им простенькое представление, показывающее эти цифры.

2. Тем же аналитикам для каждого европейского порта хочется знать распределение доставленного в него кофе по покупателям.
   Что-то в духе "50% кофе, доставленного в Гамбург, покупает "Чибо", 25% "Нескафе" и 25% "Якобс". 
   В Марселе 70% покупает "Нескафе", а "Чибо" и "Якобс" по 15%.
*/

CREATE view [dbo].[CommodityTurnover]
as select portA, portE, sum(amount) as CommodityTurnover
from SupplyE
group by portA, portE


GO
/****** Object:  View [dbo].[Вistribution]    Script Date: 30.04.2015 22:38:07 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
/*Представления
1. Аналитикам хочется знать "товарооборот" между каждой парой европейских и южноамериканских портов. 
   Товарооборот -- это суммарный вес перевезенного кофе между двумя портами.
   Напишите им простенькое представление, показывающее эти цифры.

2. Тем же аналитикам для каждого европейского порта хочется знать распределение доставленного в него кофе по покупателям.
   Что-то в духе "50% кофе, доставленного в Гамбург, покупает "Чибо", 25% "Нескафе" и 25% "Якобс". 
   В Марселе 70% покупает "Нескафе", а "Чибо" и "Якобс" по 15%.
*/
create view [dbo].[Вistribution]
as select portE, customer, cast(sum(Bookkeeping.amount)as float)*100/sum(SupplyE.amount)   as Вistribution
from Bookkeeping full join SupplyE
on Bookkeeping.ship=SupplyE.ship and Bookkeeping.dateE=SupplyE.dateE
group by portE, customer
GO
ALTER TABLE [dbo].[Bookkeeping]  WITH CHECK ADD CHECK  (([customer] like '[A-Z]%[a-z]%'))
GO
ALTER TABLE [dbo].[Bookkeeping]  WITH CHECK ADD CHECK  (([ship] like '[A-Z]%[a-z]%'))
GO
ALTER TABLE [dbo].[Plantation]  WITH CHECK ADD CHECK  (([manager] like '[A-Z]%[a-z]%'))
GO
ALTER TABLE [dbo].[Plantation]  WITH CHECK ADD CHECK  (([portA] like '[A-Z]%[a-z]%'))
GO
ALTER TABLE [dbo].[Plantation]  WITH CHECK ADD CHECK  (([сountry] like '[A-Z]%[a-z]%'))
GO
ALTER TABLE [dbo].[PortA]  WITH CHECK ADD CHECK  (([name] like '[A-Z]%[a-z]%'))
GO
ALTER TABLE [dbo].[PortE]  WITH CHECK ADD CHECK  (([name] like '[A-Z]%[a-z]%'))
GO
ALTER TABLE [dbo].[Ship]  WITH CHECK ADD CHECK  (([name] like '[A-Z]%[a-z]%'))
GO
ALTER TABLE [dbo].[Ship]  WITH CHECK ADD CHECK  (([portA] like '[A-Z]%[a-z]%'))
GO
ALTER TABLE [dbo].[Ship]  WITH CHECK ADD CHECK  (([portE] like '[A-Z]%[a-z]%'))
GO
ALTER TABLE [dbo].[SupplyA]  WITH CHECK ADD CHECK  (([portA] like '[A-Z]%[a-z]%'))
GO
ALTER TABLE [dbo].[SupplyE]  WITH CHECK ADD CHECK  (([portA] like '[A-Z]%[a-z]%'))
GO
ALTER TABLE [dbo].[SupplyE]  WITH CHECK ADD CHECK  (([portE] like '[A-Z]%[a-z]%'))
GO
/****** Object:  StoredProcedure [dbo].[ChooseCust]    Script Date: 30.04.2015 22:38:07 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO

CREATE procedure [dbo].[ChooseCust](
  @portK char(30)
, @amountX int
, @customerA char(30)
, @customerB char(30)
, @portL char(30)
, @portM char(30)
, @choosenCustomer char(30) output
, @choosenShip char(30) output
)

as begin

create table #SuitableShip(
  name char(30)
, cost int
, portE char(30)
)

insert into #SuitableShip
select name, cost, portE
from Ship
where portA=@portK
and capacity>=@amountX
and (portE=@portL
or portE=@portM)

select @choosenShip = name
from #SuitableShip
where cost=(select min(cost) from #SuitableShip)

if (@portL=(select portE
from #SuitableShip
where cost=(select min(cost) from #SuitableShip))) set  @choosenCustomer=@customerA
else set  @choosenCustomer=@customerA

end
GO
/****** Object:  StoredProcedure [dbo].[ChooseCustomer]    Script Date: 30.04.2015 22:38:07 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
/*Хранимая процедура.

У вас в неком южноамериканском порту K лежит некий груз кофе -- X тонн.
У вас есть два покупателя A и B. 
Покупатель A согласен приехать за кофе в европейский порт L,
а покупатель B согласен приехать в порт M. 
Посчитайте, кому из них выгоднее везти ваш кофе и на каком корабле.*/

CREATE procedure [dbo].[ChooseCustomer](
  @portK char(30)
, @amountX int
, @customerA char(30)
, @customerB char(30)
, @portL char(30)
, @portM char(30)
, @choosenCustomer char(30) output
, @choosenShip char(30) output
)

as begin

declare SuitableShip
cursor for 
select name, cost, portE
from Ship
where portA=@portK
and capacity>=@amountX
and (portE=@portL
or portE=@portM)

declare @ship char(30)
, @cost int
, @portE char(30)
, @min int

open SuitableShip

fetch SuitableShip into @ship, @cost, @portE

set @min=@cost
set @choosenShip=@ship
if (@portE=@portL) set @choosenCustomer=@customerA
else set @choosenCustomer=@customerB

while (@@FETCH_STATUS=0)
begin

if(@min>@cost) 
begin
set @min=@cost
set @choosenShip=@ship
if(@portE=@portL) set @choosenCustomer=@customerA
else set @choosenCustomer=@customerB
end

fetch SuitableShip into @ship, @cost, @portE

end;

close SuitableShip
deallocate SuitableShip

end
GO
USE [master]
GO
ALTER DATABASE [MyCafe] SET  READ_WRITE 
GO
