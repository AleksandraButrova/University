USE [master]
GO
/****** Object:  Database [ChessGame]    Script Date: 30.04.2015 22:36:38 ******/
CREATE DATABASE [ChessGame]
 CONTAINMENT = NONE
 ON  PRIMARY 
( NAME = N'ChessGame', FILENAME = N'C:\Program Files\Microsoft SQL Server\MSSQL11.SQLEXPRESS\MSSQL\DATA\ChessGame.mdf' , SIZE = 5120KB , MAXSIZE = UNLIMITED, FILEGROWTH = 1024KB )
 LOG ON 
( NAME = N'ChessGame_log', FILENAME = N'C:\Program Files\Microsoft SQL Server\MSSQL11.SQLEXPRESS\MSSQL\DATA\ChessGame_log.ldf' , SIZE = 2048KB , MAXSIZE = 2048GB , FILEGROWTH = 10%)
GO
ALTER DATABASE [ChessGame] SET COMPATIBILITY_LEVEL = 110
GO
IF (1 = FULLTEXTSERVICEPROPERTY('IsFullTextInstalled'))
begin
EXEC [ChessGame].[dbo].[sp_fulltext_database] @action = 'enable'
end
GO
ALTER DATABASE [ChessGame] SET ANSI_NULL_DEFAULT OFF 
GO
ALTER DATABASE [ChessGame] SET ANSI_NULLS OFF 
GO
ALTER DATABASE [ChessGame] SET ANSI_PADDING OFF 
GO
ALTER DATABASE [ChessGame] SET ANSI_WARNINGS OFF 
GO
ALTER DATABASE [ChessGame] SET ARITHABORT OFF 
GO
ALTER DATABASE [ChessGame] SET AUTO_CLOSE OFF 
GO
ALTER DATABASE [ChessGame] SET AUTO_SHRINK OFF 
GO
ALTER DATABASE [ChessGame] SET AUTO_UPDATE_STATISTICS ON 
GO
ALTER DATABASE [ChessGame] SET CURSOR_CLOSE_ON_COMMIT OFF 
GO
ALTER DATABASE [ChessGame] SET CURSOR_DEFAULT  GLOBAL 
GO
ALTER DATABASE [ChessGame] SET CONCAT_NULL_YIELDS_NULL OFF 
GO
ALTER DATABASE [ChessGame] SET NUMERIC_ROUNDABORT OFF 
GO
ALTER DATABASE [ChessGame] SET QUOTED_IDENTIFIER OFF 
GO
ALTER DATABASE [ChessGame] SET RECURSIVE_TRIGGERS OFF 
GO
ALTER DATABASE [ChessGame] SET  DISABLE_BROKER 
GO
ALTER DATABASE [ChessGame] SET AUTO_UPDATE_STATISTICS_ASYNC OFF 
GO
ALTER DATABASE [ChessGame] SET DATE_CORRELATION_OPTIMIZATION OFF 
GO
ALTER DATABASE [ChessGame] SET TRUSTWORTHY OFF 
GO
ALTER DATABASE [ChessGame] SET ALLOW_SNAPSHOT_ISOLATION OFF 
GO
ALTER DATABASE [ChessGame] SET PARAMETERIZATION SIMPLE 
GO
ALTER DATABASE [ChessGame] SET READ_COMMITTED_SNAPSHOT OFF 
GO
ALTER DATABASE [ChessGame] SET HONOR_BROKER_PRIORITY OFF 
GO
ALTER DATABASE [ChessGame] SET RECOVERY SIMPLE 
GO
ALTER DATABASE [ChessGame] SET  MULTI_USER 
GO
ALTER DATABASE [ChessGame] SET PAGE_VERIFY CHECKSUM  
GO
ALTER DATABASE [ChessGame] SET DB_CHAINING OFF 
GO
ALTER DATABASE [ChessGame] SET FILESTREAM( NON_TRANSACTED_ACCESS = OFF ) 
GO
ALTER DATABASE [ChessGame] SET TARGET_RECOVERY_TIME = 0 SECONDS 
GO
USE [ChessGame]
GO
/****** Object:  Table [dbo].[Board]    Script Date: 30.04.2015 22:36:38 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
SET ANSI_PADDING ON
GO
CREATE TABLE [dbo].[Board](
	[IdF] [int] NULL,
	[X] [int] NOT NULL,
	[Y] [char](1) NOT NULL,
UNIQUE NONCLUSTERED 
(
	[X] ASC,
	[Y] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY],
UNIQUE NONCLUSTERED 
(
	[IdF] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
) ON [PRIMARY]

GO
SET ANSI_PADDING OFF
GO
/****** Object:  Table [dbo].[Board2]    Script Date: 30.04.2015 22:36:38 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
SET ANSI_PADDING ON
GO
CREATE TABLE [dbo].[Board2](
	[IdF] [int] NULL,
	[X] [int] NOT NULL,
	[Y] [char](1) NOT NULL
) ON [PRIMARY]

GO
SET ANSI_PADDING OFF
GO
/****** Object:  Table [dbo].[Figures]    Script Date: 30.04.2015 22:36:38 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
SET ANSI_PADDING ON
GO
CREATE TABLE [dbo].[Figures](
	[IdF] [int] NOT NULL,
	[TypeF] [char](6) NOT NULL,
	[ColorF] [bit] NOT NULL,
PRIMARY KEY CLUSTERED 
(
	[IdF] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
) ON [PRIMARY]

GO
SET ANSI_PADDING OFF
GO
/****** Object:  Table [dbo].[History]    Script Date: 30.04.2015 22:36:38 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
SET ANSI_PADDING ON
GO
CREATE TABLE [dbo].[History](
	[IdF] [int] NULL,
	[X1] [int] NULL,
	[Y1] [char](1) NULL,
	[X2] [int] NULL,
	[Y2] [char](1) NULL
) ON [PRIMARY]

GO
SET ANSI_PADDING OFF
GO
ALTER TABLE [dbo].[Board]  WITH CHECK ADD FOREIGN KEY([IdF])
REFERENCES [dbo].[Figures] ([IdF])
GO
ALTER TABLE [dbo].[Board]  WITH CHECK ADD CHECK  (([X] like '[1-8]'))
GO
ALTER TABLE [dbo].[Board]  WITH CHECK ADD CHECK  (([Y] like '[A-H]'))
GO
ALTER TABLE [dbo].[Figures]  WITH CHECK ADD CHECK  (([TypeF]='pawn' OR [TypeF]='bishop' OR [TypeF]='knight' OR [TypeF]='castle' OR [TypeF]='queen' OR [TypeF]='king'))
GO
/****** Object:  StoredProcedure [dbo].[Knight]    Script Date: 30.04.2015 22:36:38 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
	/*
Процедура - тип и цвет фигур и один параметр внешний - количество фигур, которые могут быть съедены. 
Далее, внутри процедуры я создаю кусор в который выбираю все фигуры заданного типа и цвета.	 
Дальше перебираю по одной фигурки из курсора и определяю кого может съесть чудесная фигура.
Если она кого то может съесть, то я в табличку добавляю (кто ест - кого ест)
В конце во внешний параметр передается число, кол-во съеденный определенным типом
*/



CREATE procedure [dbo].[Knight]( 
  @type1 char(6)
, @color1 bit 
, @count_of_killed int output
)
as begin

declare @id1 int, 
@X1 int,
@Y1 char(1)

 create table #WWE
 (
 id1 int,
 idFoe int
 )

declare TypeColor
cursor for 
select Board.IdF, X, Y
from Board left join Figures  
on Figures.IdF=Board.IdF
where TypeF = @type1 and ColorF = @color1;

open TypeColor;

fetch TypeColor into @id1, @X1, @Y1

while (@@FETCH_STATUS=0)
begin

 insert into #WWE select @id1, Board.IdF
 from Board left join Figures
 on Board.IdF=Figures.IdF
 where ColorF <> @color1 and (abs(ascii(X)-ascii(@X1))+abs(ascii(Y)-ascii(@Y1)))=3

 fetch TypeColor into @id1, @X1, @Y1

end;

close TypeColor
deallocate TypeColor

select @count_of_killed =  count(idFoe)
from #WWE

end 

GO
USE [master]
GO
ALTER DATABASE [ChessGame] SET  READ_WRITE 
GO
