/*
Процедура - тип и цвет фигур и один параметр внешний - количество фигур, которые могут быть съедены. 
Далее, внутри процедуры я создаю кусор в который выбираю все фигуры заданного типа и цвета.	 
Дальше перебираю по одной фигурки из курсора и определяю кого может съесть чудесная фигура.
Если она кого то может съесть, то я в табличку добавляю (кто ест - кого ест)
В конце во внешний параметр передается число, кол-во съеденный определенным типом
*/



alter procedure Knight( 
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
