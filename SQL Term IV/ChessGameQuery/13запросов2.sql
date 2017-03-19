/*1. ������� ����� ����� �� �����? ������� ����������.*/
select COUNT(X)
from Board

/*2. ������� id �����, ��� �������� ���������� �� ����� k.*/
select IdF
from Figures
where TypeF like 'k%'

/*3. ����� ���� ����� ������ � �� ������� ����? 
������� ��� � ����������.*/
select distinct TypeF, count(TypeF) as counts
from Figures
group by TypeF

/*4. ������� id ����� ����� , ������� �� �����?*/
select Board.IdF
from Board full join Figures
on Board.IdF=Figures.IdF
where ColorF=0 and X is not null

/*5. ����� ������ ����� �� ������� ���������? ������� �� ��� � ����.*/
select TypeF, ColorF
from Board full join Figures
on Board.IdF=Figures.IdF
where ASCII(X)+64=ASCII(Y)+48

/*6. ������� ����� ���������� �����, ���������� � ������� ������. 
������� ���� � ����������.*/
select ColorF, count(ColorF) as Counts
from Figures full join Board
on Figures.IdF=Board.IdF
where X is not null
group by ColorF

/*7. ����� ������ ������ ������� �� �����? ������� ���.*/
select distinct TypeF
from Figures full join Board
on Figures.IdF=Board.IdF
where ColorF=1 and X is not null

/*8. ����� ������ ������ ������� �� �����? ������� ��� � ����������.*/
select distinct TypeF, count(X) as Counts
from Figures full join Board
on Figures.IdF=Board.IdF
where ColorF=1 and X is not null
group by TypeF

/*9. ������� ���� ����� (������ �����), ������� ��������, 
�� ������� ����, �� ������ ���� �� �����.*/
select TypeF
from Figures full join Board
on Figures.IdF=Board.IdF
group by TypeF
having count(TypeF)>1

/*10. ������� ���� �����, ������� �� ����� ������.*/
select ColorF
from Figures full join Board
on Figures.IdF=Board.IdF

/*11. ������� ������, ������� ����� �� ��������� ���� �������� ����� (rock) (����� ����� ������ �����)*/
select b.IdF
from Board as a full join Board as b
on a.X=b.X or a.Y=b.Y
where a.IdF in (select IdF
from Figures
where TypeF='castle') and b.IdF <> a.IdF

/*12. � ����� ������� (�����) ��� �������� ��� ����� (pawn)?*/
select ColorF, count(ColorF) as Count_Of_Figure
from Figures full join Board
on Figures.IdF=Board.IdF
group by ColorF
having count(TypeF)=8

/*13. ����� ��������� board1 � board2 ������������ ����� ��� ���������������� ��������� ���� (Chessboard). 
����� ������ (cid) �������� ���� ������� (�� ���� ��� ��� ����� ���� ������������� ������ � �������� ��� ������, 
������� ���� ���������)?*/

/*select * into Board2 from Board  ������� ����� ������� Board*/

select b1.IdF, b1.X, b1.Y, b2.X, b2.Y
from Board as b1 left join Board2 as b2
on b1.IdF=b2.IdF
where not exists(
select IdF
from Board2
where IdF=b1.IdF)
or b1.X <> b2.X 
or b2.IdF<>b1.IdF

/*14. ������� id ������, ���� ��� ����� � �������� �������� �� ������� ������? 
�������� ���������� ����� ������� ������� 5�5 � ������� � ������.*/

/*15. ����� ������, ����� ���� ������� � ������ ������ 
(���������� ������� �� ������� L1 � ������� ��������� �� X + ������� ��������� �� Y.*/