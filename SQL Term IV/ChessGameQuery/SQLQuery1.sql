	/*
��������� - ��� � ���� ����� � ���� �������� ������� - ���������� �����, ������� ����� ���� �������. 
�����, ������ ��������� � ������ ����� � ������� ������� ��� ������ ��������� ���� � �����.	 
������ ��������� �� ����� ������� �� ������� � ��������� ���� ����� ������ �������� ������.
���� ��� ���� �� ����� ������, �� � � �������� �������� (��� ��� - ���� ���)
� ����� �� ������� �������� ���������� �����, ���-�� ��������� ������������ �����
*/



create procedure Horse( 
  @typeF char(10)
, @colorF bit 
, @cok int output
)
as begin

declare @idFig int, 
@FigType char(10),
@FigColor bit,
@FigX int,
@FigY char(1)

 create table #WWE
 (
 idFig int,
 idFoe int
 )

declare TypeColor
/*������� ���������� �� ����� � ���� ������*/
cursor for 
select ChessFigures.Id, FigureType, FigureColor, RowIs, ColumnIs
from ChessBoard left join ChessFigures  
on ChessFigures.Id=ChessBoard.Id
where FigureType = @typeF and FigureColor = @colorF;

open TypeColor;

fetch TypeColor into @idFig, @FigType, @FigColor, @FigX, @FigY

while (@@FETCH_STATUS=0)
begin

 insert into #WWE select @idFig, cb.Id 
 from ChessBoard as cb left join ChessFigures as cf
 on cb.Id=cf.Id
 where FigureColor <> @FigColor and abs(ascii(RowIs)-ascii(@FigX))+abs(ascii(ColumnIs)-ascii(@FigY))=3

 fetch TypeColor into @idFig, @FigType, @FigColor, @FigX, @FigY

end;

close TypeColor
deallocate TypeColor

select @cok =  count(idFoe)
from #WWE

end 
