/*1. Сколько фигур стоит на доске? Вывести количество.*/
select COUNT(X)
from Board

/*2. Вывести id фигур, чьи названия начинаются на букву k.*/
select IdF
from Figures
where TypeF like 'k%'

/*3. Какие типы фигур бывают и по сколько штук? 
Вывести тип и количество.*/
select distinct TypeF, count(TypeF) as counts
from Figures
group by TypeF

/*4. Вывести id белых пешек , стоящих на доске?*/
select Board.IdF
from Board full join Figures
on Board.IdF=Figures.IdF
where ColorF=0 and X is not null

/*5. Какие фигуры стоят на главной диагонали? Вывести их тип и цвет.*/
select TypeF, ColorF
from Board full join Figures
on Board.IdF=Figures.IdF
where ASCII(X)+64=ASCII(Y)+48

/*6. Найдите общее количество фигур, оставшихся у каждого игрока. 
Вывести цвет и количество.*/
select ColorF, count(ColorF) as Counts
from Figures full join Board
on Figures.IdF=Board.IdF
where X is not null
group by ColorF

/*7. Какие фигуры черных имеются на доске? Вывести тип.*/
select distinct TypeF
from Figures full join Board
on Figures.IdF=Board.IdF
where ColorF=1 and X is not null

/*8. Какие фигуры черных имеются на доске? Вывести тип и количество.*/
select distinct TypeF, count(X) as Counts
from Figures full join Board
on Figures.IdF=Board.IdF
where ColorF=1 and X is not null
group by TypeF

/*9. Найдите типы фигур (любого цвета), которых осталось, 
по крайней мере, не меньше двух на доске.*/
select TypeF
from Figures full join Board
on Figures.IdF=Board.IdF
group by TypeF
having count(TypeF)>1

/*10. Вывести цвет фигур, которых на доске больше.*/
select ColorF
from Figures full join Board
on Figures.IdF=Board.IdF

/*11. Найдите фигуры, которые стоят на возможном пути движения ладьи (rock) (Любой ладьи любого цвета)*/
select b.IdF
from Board as a full join Board as b
on a.X=b.X or a.Y=b.Y
where a.IdF in (select IdF
from Figures
where TypeF='castle') and b.IdF <> a.IdF

/*12. У каких игроков (цвета) еще остались ВСЕ пешки (pawn)?*/
select ColorF, count(ColorF) as Count_Of_Figure
from Figures full join Board
on Figures.IdF=Board.IdF
group by ColorF
having count(TypeF)=8

/*13. Пусть отношения board1 и board2 представляют собой два последовательных состояние игры (Chessboard). 
Какие фигуры (cid) изменили свою позицию (за один ход это может быть передвигаемая фигура и возможно еще фигура, 
которая была “съедена”)?*/

/*select * into Board2 from Board  создаст копию таблицы Board*/

select b1.IdF, b1.X, b1.Y, b2.X, b2.Y
from Board as b1 left join Board2 as b2
on b1.IdF=b2.IdF
where not exists(
select IdF
from Board2
where IdF=b1.IdF)
or b1.X <> b2.X 
or b2.IdF<>b1.IdF

/*14. Вывести id фигуры, если она стоит в «опасной близости» от черного короля? 
«опасной близостью» будем считать квадрат 5х5 с королем в центре.*/

/*15. Найти фигуру, ближе всех стоящую к белому королю 
(расстояние считаем по метрике L1 – разница координат по X + разница координат по Y.*/