USE [ChessGame]
GO
/****** Object:  Trigger [dbo].[trg1]    Script Date: 14.04.2015 17:54:00 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
ALTER trigger [dbo].[trg1] on [dbo].[Board]
after insert, update, delete 
as
begin 
insert into History
select coalesce(inserted.IdF, deleted.IdF), deleted.X, deleted.Y, inserted.X, inserted.Y
from inserted full join deleted
on inserted.IdF=deleted.IdF

end 