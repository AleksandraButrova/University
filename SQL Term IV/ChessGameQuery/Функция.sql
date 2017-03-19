create function KnightF ( 
  @type1 char(10)
, @color1 bit 
)
returns @WWE table (
 id1 int,
 idFoe int) 
 as

begin

declare @id1 int, 
@X1 int,
@Y1 char(1)

declare TypeColor
/*выбрали подходищие по цвету и типу фигуры*/
cursor for 
select Board.IdF, TypeF, ColorF, X, Y
from Board left join Figures  
on Figures.IdF=Board.IdF
where TypeF = @type1 and ColorF = @color1;

open TypeColor;

fetch TypeColor into @id1, @X1, @Y1

while (@@FETCH_STATUS=0)
begin

 insert into @WWE select @id1, Board.IdF
 from Board left join Figures
 on b.IdF=f.IdF
 where Color <> @Color1 and abs(ascii(X)-ascii(@X1))+abs(ascii(Y)-ascii(@Y1))=3

 fetch TypeColor into @id1, @X1, @Y1

end;

close TypeColor
deallocate TypeColor

return

end