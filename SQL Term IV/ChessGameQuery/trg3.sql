create trigger trg3 on Board
after insert, update, delete 
as
begin 
insert into History1
select coalesce(inserted.IdF, deleted.IdF),coalesce(deleted.X,inserted.X) , coalesce(deleted.Y, inserted.Y)
from inserted full join deleted
on inserted.IdF=deleted.IdF
end 
