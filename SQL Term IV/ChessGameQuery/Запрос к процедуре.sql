
/*
для коня
запрос к процедуре
*/
declare @count_of_killed int
execute Knight 'knight', 0, @count_of_killed output
select @count_of_killed

/*вызов функции для коня
select *
from KnightF('knight', 0)*/