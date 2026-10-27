----------------------------------------------------------------------------
--Name:		[征服][功能脚本]性别转换服务专员.lua
--Purpose:	性别转换服务专员
--Creator: 	郑鋆
--Created:	2015/07/27
----------------------------------------------------------------------------

-- 命名前缀
-- GenderTransitionService_

local tGenderTransitionService_Constant = {}
	-- 花费的天石
	tGenderTransitionService_Constant["Emoney"] = 1075
	
	tGenderTransitionService_Constant["Log"] = "0,0,0,0,10001930,2,sex,0"

	tGenderTransitionService_Constant["EmoneyLog"] = "350	4226	1075	1075	1	"
	


--------------------------------------逻辑部分-----------------------------------------	
-- 公共判断
function GenderTransitionService_PublicJudgment(nNpcId)
	-- 判断玩家是否有婚姻
	local nMateId = Get_UserMateId()
	
	if nMateId > 0 then
		LinkNpcGossipFunc_New(nNpcId,"3-1")
		return false
	end
	
	-- 判断玩家身上天石
	local nEmoney = Get_UserEMoney()
	
	if nEmoney < tGenderTransitionService_Constant["Emoney"] then
		LinkNpcGossipFunc_New(nNpcId,"3-2")
		return false
	end
	
	-- 判断是否是嫔妃
	if User_IsConcubines() then
		LinkNpcGossipFunc_New(nNpcId,"4-3")
		return false
	-- 是否有嫔妃
	elseif User_HaveConcubines() then
		LinkNpcGossipFunc_New(nNpcId,"4-2")
		return false
	end
	
	return true
end

-- 出二次确认对白
function GenderTransitionService_RecognitionConversionSex(nNpcId)
	-- 判断是否满足转换条件
	if not GenderTransitionService_PublicJudgment(nNpcId) then
		return
	end
	
	LinkNpcGossipFunc_New(nNpcId,"3-3")
end

-- 确认转换性别
function GenderTransitionService_ConversionSex(nNpcId)
	-- 判断是否满足转换条件
	if not GenderTransitionService_PublicJudgment(nNpcId) then
		return
	end
	
	-- 判断背包空间
	if not User_CheckLeftSpace(2) then
		LinkNpcGossipFunc_New(nNpcId,"4-1")
		return
	end
	
	local nEmoney = Get_UserEMoney()
	
	if not User_AddEMoney(-tGenderTransitionService_Constant["Emoney"]) then
		return
	end
	
	Sys_SaveActionFestivalLog(tGenderTransitionService_Constant["Log"])
	Sys_SaveEmoneyBuy(tGenderTransitionService_Constant["EmoneyLog"])
	
	-- 播光效
	User_EffectAdd("self","angelwing")
	
	local nUserId = Get_UserId()
	local nSex = Get_UserSex(nUserId)
	local sUserName = Get_UserName(nUserId)
	
	if nSex == 1 then
		User_SetSex(2)
	else
		User_SetSex(1)
	end
	
	if User_ChkRoleStatus(166,nUserId) then
		User_DelRoleStatus(166,nUserId)
	end
	
	if User_ChkRoleStatus(167,nUserId) then
		User_DelRoleStatus(167,nUserId)
	end
	
	Sys_SystemBroadcast(string.format(tGenderTransitionService_Text["Success"][nSex],sUserName))
end

--------------------------------------NPC模块-------------------------------------------
-- 性别转换服务专员
tNpcFace[2490] = 218
tNpcGossip[15805] = tNpcGossip[15805] or DefaultNpc:new{}
tNpcGossip[15805]["OptionHidden"] = 1

tNpcGossip[15805]["Text1-1"] = {111,112,113}
tNpcGossip[15805]["Text111"] = tGenderTransitionService_Text[15805]["111"]
tNpcGossip[15805]["Text112"] = tGenderTransitionService_Text[15805]["112"]
tNpcGossip[15805]["Text113"] = tGenderTransitionService_Text[15805]["113"]
tNpcGossip[15805]["tOption1-1"] = {1,2,3}

tNpcGossip[15805]["Option1"] = tGenderTransitionService_Text[15805]["Option1"]
tNpcGossip[15805]["OptionFunc1"]="GenderTransitionService_RecognitionConversionSex</N>15805"
tNpcGossip[15805]["Option2"] = tGenderTransitionService_Text[15805]["Option2"]
tNpcGossip[15805]["OptionPoint2"]="2-1"
tNpcGossip[15805]["Option3"] = tGenderTransitionService_Text[15805]["Option3"]

-- 咨询注意事项。
tNpcGossip[15805]["Text2-1"] = {211,212,213}
tNpcGossip[15805]["Text211"] = tGenderTransitionService_Text[15805]["211"]
tNpcGossip[15805]["Text212"] = tGenderTransitionService_Text[15805]["212"]
tNpcGossip[15805]["Text213"] = tGenderTransitionService_Text[15805]["213"]
tNpcGossip[15805]["tOption2-1"] = {4,5}

tNpcGossip[15805]["Option4"] = tGenderTransitionService_Text[15805]["Option4"]
tNpcGossip[15805]["OptionPoint4"]="1"
tNpcGossip[15805]["Option5"] = tGenderTransitionService_Text[15805]["Option5"]

-- 已婚状态
tNpcGossip[15805]["Text3-1"] = {311}
tNpcGossip[15805]["Text311"] = tGenderTransitionService_Text[15805]["311"]
tNpcGossip[15805]["tOption3-1"] = {6}

tNpcGossip[15805]["Option6"] = tGenderTransitionService_Text[15805]["Option6"]

-- 1075天石
tNpcGossip[15805]["Text3-2"] = {321,322}
tNpcGossip[15805]["Text321"] = tGenderTransitionService_Text[15805]["321"]
tNpcGossip[15805]["Text322"] = tGenderTransitionService_Text[15805]["322"]
tNpcGossip[15805]["tOption3-2"] = {7}

tNpcGossip[15805]["Option7"] = tGenderTransitionService_Text[15805]["Option7"]

-- 二次确认
tNpcGossip[15805]["Text3-3"] = {331,332}
tNpcGossip[15805]["Text331"] = tGenderTransitionService_Text[15805]["331"]
tNpcGossip[15805]["Text332"] = tGenderTransitionService_Text[15805]["332"]
tNpcGossip[15805]["tOption3-3"] = {8,9}

tNpcGossip[15805]["Option8"] = tGenderTransitionService_Text[15805]["Option8"]
tNpcGossip[15805]["OptionFunc8"]="GenderTransitionService_ConversionSex</N>15805"
tNpcGossip[15805]["Option9"] = tGenderTransitionService_Text[15805]["Option9"]

tNpcGossip[15805]["Text4-1"] = {411}
tNpcGossip[15805]["Text411"] = tGenderTransitionService_Text[15805]["411"]
tNpcGossip[15805]["tOption4-1"] = {10}
tNpcGossip[15805]["Option10"] = tGenderTransitionService_Text[15805]["Option10"]

tNpcGossip[15805]["Text4-2"] = {421}
tNpcGossip[15805]["Text421"] = tGenderTransitionService_Text[15805]["421"]
tNpcGossip[15805]["tOption4-2"] = {11}
tNpcGossip[15805]["Option11"] = tGenderTransitionService_Text[15805]["Option11"]

tNpcGossip[15805]["Text4-3"] = {431}
tNpcGossip[15805]["Text431"] = tGenderTransitionService_Text[15805]["431"]
tNpcGossip[15805]["tOption4-3"] = {12}
tNpcGossip[15805]["ChkFunc4-3"] = function ()
	local sOffice = Get_Harem()
	
	tNpcGossip[15805]["Text431"] = string.format(tGenderTransitionService_Text[15805]["431"],sOffice)
	return true
end



tNpcGossip[15805]["Option12"] = tGenderTransitionService_Text[15805]["Option12"]