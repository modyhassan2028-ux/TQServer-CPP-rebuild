----------------------------------------------------------------------------
--Name:		[征服][公用函数]程序触发.lua
--Purpose:	程序触发
--Creator: 	郑江文
--Created:	2014/12/18

--玩家死亡触发
function Event_Kill_User(nUserid)
	local nKillerID = Get_UserId()
	--各自活动有需求死亡的逻辑封装成函数插入表中。
	if type(tUserKilled["tFunction"]) == "table" then
		for _,func in ipairs(tUserKilled["tFunction"]) do
			func(nUserid,nKillerID)
		end
	end
end