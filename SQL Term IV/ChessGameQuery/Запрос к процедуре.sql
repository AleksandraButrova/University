
/*
��� ����
������ � ���������
*/
declare @count_of_killed int
execute Knight 'knight', 0, @count_of_killed output
select @count_of_killed

/*����� ������� ��� ����
select *
from KnightF('knight', 0)*/