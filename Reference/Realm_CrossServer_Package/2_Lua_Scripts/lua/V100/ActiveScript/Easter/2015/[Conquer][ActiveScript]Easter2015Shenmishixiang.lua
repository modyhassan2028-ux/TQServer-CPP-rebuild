------------------------------------------------------------------------------------
--Name:			[征服][活动脚本]复活节活动之神秘的宝藏（4.2-4.8）
--Creator: 		陈浩文
--Created:		2015/01/23
------------------------------------------------------------------------------------
-- 命名前缀
-- Easter2015_Shenmishixiang_

--活动时间
local tEaster2015_Shenmishixiang_Time = {}
tEaster2015_Shenmishixiang_Time["Beftime"]= "2014-01-01 00:00 2015-04-01 23:59"
tEaster2015_Shenmishixiang_Time["Nowtime"] = "2015-04-02 00:00 2015-04-08 23:59"

--玩家等级要求
tEaster2015_Shenmishixiang_Condition={}
tEaster2015_Shenmishixiang_Condition["Metempsychosis"] = 0
tEaster2015_Shenmishixiang_Condition["Level"] = 80

--返回双龙城、复活节岛坐标
tEaster2015_Shenmishixiang_Position={}
tEaster2015_Shenmishixiang_Position["Zero"]={}
tEaster2015_Shenmishixiang_Position["Zero"]["MapId"] = 1002
tEaster2015_Shenmishixiang_Position["Zero"]["CellX"] = 297
tEaster2015_Shenmishixiang_Position["Zero"]["CellY"] = 361
tEaster2015_Shenmishixiang_Position["One"]={}
tEaster2015_Shenmishixiang_Position["One"]["MapId"] = 3930
tEaster2015_Shenmishixiang_Position["One"]["CellX"] = 31
tEaster2015_Shenmishixiang_Position["One"]["CellY"] = 36

--活动掩码 13269	13273
--stc(132,69) 1表示完成任务获取奖励
--stc(132,70) 1表示当天第一次成功进入复活节岛
--stc(132,73) 复活节 节日欢庆礼包使用掩码
local tEaster2015_Shenmishixiang_Stc = {}
tEaster2015_Shenmishixiang_Stc["Shenmishixiang"]={}
tEaster2015_Shenmishixiang_Stc["Shenmishixiang"]["StcEvent"] = 132
tEaster2015_Shenmishixiang_Stc["Shenmishixiang"]["StcType"] = 69
tEaster2015_Shenmishixiang_Stc["Shenmishixiang"]["Complete"] = 1
tEaster2015_Shenmishixiang_Stc["EnterOne"]={}
tEaster2015_Shenmishixiang_Stc["EnterOne"]["StcEvent"] = 132
tEaster2015_Shenmishixiang_Stc["EnterOne"]["StcType"] = 70
tEaster2015_Shenmishixiang_Stc["EnterOne"]["Complete"] = 1

-- log表
local tEaster2015_Shenmishixiang_Log = {}
tEaster2015_Shenmishixiang_Log["New"] = "0,0,0,0,12000025,1[1],0,0"
tEaster2015_Shenmishixiang_Log["Complete"] = "0,0,0,0,12000025,1[2],0,0"
tEaster2015_Shenmishixiang_Log["CompleteGet_Xingyunshijing"] = "0,0,0,0,12000025,2,3002951,1"			--1个幸运石晶
tEaster2015_Shenmishixiang_Log["CompleteGet_Jierilibao"] = "0,0,3002951,7,12000025,2,3003625,1"			--1个节日礼包

-- 物品
local tEaster2015_Shenmishixiang_Item = {}
tEaster2015_Shenmishixiang_Item["Xingyunshijing"]={}		--幸运石晶
tEaster2015_Shenmishixiang_Item["Xingyunshijing"]["Id"] = 3002951
tEaster2015_Shenmishixiang_Item["Xingyunshijing"]["Num"] = 7
tEaster2015_Shenmishixiang_Item["Jierilibao"]={}			--节日欢庆礼包
tEaster2015_Shenmishixiang_Item["Jierilibao"]["FestivalId"] = 3381
tEaster2015_Shenmishixiang_Item["Jierilibao"]["LogId"] = 12000025

-- 怪物
tEaster2015_Shenmishixiang_Monster = {}
tEaster2015_Shenmishixiang_Monster["Normal"] = 7670
tEaster2015_Shenmishixiang_Monster["Large"] = 7671
------------------------------------------------------------------------------------

------------------------------------------
-- STC掩码逻辑隔天重置
function Easter2015_Shenmishixiang_ChkStc(sIndex)
	local nEvent = tEaster2015_Shenmishixiang_Stc[sIndex]["StcEvent"]
	local nType = tEaster2015_Shenmishixiang_Stc[sIndex]["StcType"]
	if Task_StcInterval(nEvent,nType,1,4) then
		Task_SetStatistic(nEvent,nType,0,1)
		Task_SetStcTimestamp(nEvent,nType,0)
	end
end

------------------------------------------
--概率
function Easter2015_Shenmishixiang_Possible(nNumerator,nDenominator)
	local nNum = math.random(1,nDenominator)
	if nNum <= nNumerator then
		return true
	else
		return false
	end
end

------------------------------------------
--传送逻辑
function Easter2015_Shenmishixiang_User_ChgMap(sWay)
	local nMapId = tEaster2015_Shenmishixiang_Position[sWay]["MapId"]
	local nCellX = tEaster2015_Shenmishixiang_Position[sWay]["CellX"]
	local nCellY = tEaster2015_Shenmishixiang_Position[sWay]["CellY"]
	User_ChgMap(nMapId,nCellX,nCellY)
end

------------------------------------------
-- 使用幸运石晶
function Easter2015_Shenmishixiang_UseItem(nItemId,sItemName)
	local nItemId = tEaster2015_Shenmishixiang_Item["Xingyunshijing"]["Id"]
	local nItemNum = tEaster2015_Shenmishixiang_Item["Xingyunshijing"]["Num"]
	
	if not Sys_ChkFullTime(tEaster2015_Shenmishixiang_Time["Nowtime"]) then
		User_TalkChannel2005(tEaster2015_Shenmishixiang_Text["TalkChannel2005"]["Aftime"])
		Item_DelAllItemByType(nItemId)
	elseif Item_ChkAccItem(nItemId,nItemNum)  then
		Sys_MsgBox(tEaster2015_Shenmishixiang_Text["MsgBox"]["GetSevenConfirm"],"Easter2015_Shenmishixiang_UseItemSetExplore")
		
	else
		Sys_MsgBox(tEaster2015_Shenmishixiang_Text["MsgBox"]["NoSeven"])
	end
end

------------------------------------------
-- 读条
function Easter2015_Shenmishixiang_UseItemSetExplore()
	User_SetExplore(2,tEaster2015_Shenmishixiang_Text["SetExplore"]["Use"],100,"Easter2015_Shenmishixiang_GetJierilibao")
end

------------------------------------------
--七个幸运石晶换取一个节日礼包
function Easter2015_Shenmishixiang_GetJierilibao()
	local nMapId = Get_UserMapId()
	local nItemId = tEaster2015_Shenmishixiang_Item["Xingyunshijing"]["Id"]
	local nItemNum = tEaster2015_Shenmishixiang_Item["Xingyunshijing"]["Num"]
	local nFestivalId = tEaster2015_Shenmishixiang_Item["Jierilibao"]["FestivalId"]
	local nLogId = tEaster2015_Shenmishixiang_Item["Jierilibao"]["LogId"]
	local nEvent = tEaster2015_Shenmishixiang_Stc["Shenmishixiang"]["StcEvent"]
	local nType = tEaster2015_Shenmishixiang_Stc["Shenmishixiang"]["StcType"]
	local nComplete = tEaster2015_Shenmishixiang_Stc["Shenmishixiang"]["Complete"]
	local sLogCompleteGet_Jierilibao = tEaster2015_Shenmishixiang_Log["CompleteGet_Jierilibao"]
	Easter2015_Shenmishixiang_ChkStc("Shenmishixiang")
	
	--当天已获得礼包
	if Task_ChkStcValue(nEvent,nType,"==",nComplete) then
		if nMapId == tEaster2015_Shenmishixiang_Position["One"]["MapId"] then
			Easter2015_Shenmishixiang_User_ChgMap("Zero")
		end
		return
	end
	
	if Item_ChkAccItem(nItemId,nItemNum)  then
		Item_DelAllItemByType(nItemId)
		FestivalGeneralPackage_GetGift(nFestivalId,nLogId)
		Sys_SaveActionFestivalLog(sLogCompleteGet_Jierilibao)
		User_EffectAdd("self","angelwing")
		Task_SetStatistic(nEvent,nType,nComplete,1)
		Task_SetStcTimestamp(nEvent,nType,0)
		if nMapId == tEaster2015_Shenmishixiang_Position["One"]["MapId"] then
			Easter2015_Shenmishixiang_User_ChgMap("Zero")
		end
		--User_TalkChannel2005(tEaster2015_Shenmishixiang_Text["TalkChannel2005"]["JoinZero"])
		Sys_MsgBox(tEaster2015_Shenmishixiang_Text["MsgBox"]["Jierilibao"])
	end
end

------------------------------------------
--击杀怪物
function Easter2015_Shenmishixiang_Add_Kill_Monster(nMonsterTypeId)
	local bIsGetItem = false
	local nItemId = tEaster2015_Shenmishixiang_Item["Xingyunshijing"]["Id"]
	local nItemNum = tEaster2015_Shenmishixiang_Item["Xingyunshijing"]["Num"]
	local sLogCompleteGet_Xingyunshijing = tEaster2015_Shenmishixiang_Log["CompleteGet_Xingyunshijing"]
	--石像怪人
	if nMonsterTypeId == tEaster2015_Shenmishixiang_Monster["Normal"] then
		bIsGetItem = Easter2015_Shenmishixiang_Possible(1,5)
	end
	--巨大的石像怪人
	if nMonsterTypeId == tEaster2015_Shenmishixiang_Monster["Large"] then
		bIsGetItem = Easter2015_Shenmishixiang_Possible(1,1)
	end
	
	if Item_ChkAccItem(nItemId,nItemNum)  then
		Sys_MsgBox(tEaster2015_Shenmishixiang_Text["MsgBox"]["GetSeven"],"Easter2015_Shenmishixiang_UseItemSetExplore")
	elseif Item_ChkAccItem(nItemId,1) or User_CheckLeftSpace(1) then
		--背包中已经有1个幸运石晶 或者 背包中有1个空格
		if bIsGetItem then
			Item_AddItem(nItemId,0,1)
			Sys_SaveActionFestivalLog(sLogCompleteGet_Xingyunshijing)
			User_TalkChannel2005(tEaster2015_Shenmishixiang_Text["TalkChannel2005"]["GetOne"])
		end
		if Item_ChkAccItem(nItemId,nItemNum)  then
			Sys_MsgBox(tEaster2015_Shenmishixiang_Text["MsgBox"]["GetSeven"],"Easter2015_Shenmishixiang_UseItemSetExplore")
		end
	else
		--您的背包已满，得不到任务物品。
		User_TalkChannel2005(tEaster2015_Shenmishixiang_Text["TalkChannel2005"]["NoLeftSpace"])
	end
end

------------------------------------------
--进入复活节岛
function Easter2015_Shenmishixiang_Option13_10821(nNpcId)
	local nLevel = tEaster2015_Shenmishixiang_Condition["Level"]
	local nMetempsychosis = tEaster2015_Shenmishixiang_Condition["Metempsychosis"]
	local nEvent = tEaster2015_Shenmishixiang_Stc["Shenmishixiang"]["StcEvent"]
	local nType = tEaster2015_Shenmishixiang_Stc["Shenmishixiang"]["StcType"]
	local nComplete = tEaster2015_Shenmishixiang_Stc["Shenmishixiang"]["Complete"]
	local nEvent2 = tEaster2015_Shenmishixiang_Stc["EnterOne"]["StcEvent"]
	local nType2 = tEaster2015_Shenmishixiang_Stc["EnterOne"]["StcType"]
	local nComplete2 = tEaster2015_Shenmishixiang_Stc["EnterOne"]["Complete"]
	Easter2015_Shenmishixiang_ChkStc("Shenmishixiang")
	Easter2015_Shenmishixiang_ChkStc("EnterOne")
	
	--等级不足
	if not User_JudgeLevelAndMetempsychosis(nLevel,nMetempsychosis) then
		LinkNpcGossipFunc_New(nNpcId,"2-1")
		return
	end
	
	--当天已获得礼包
	if Task_ChkStcValue(nEvent,nType,"==",nComplete) then
		LinkNpcGossipFunc_New(nNpcId,"2-2")
		return
	end
	
	--当天第一次进岛
	if Task_ChkStcValue(nEvent2,nType2,"<",nComplete2) then
		Task_SetStatistic(nEvent2,nType2,nComplete2,1)
		Task_SetStcTimestamp(nEvent2,nType2,0)
		Sys_SaveActionFestivalLog(tEaster2015_Shenmishixiang_Log["New"])
	end
	
	Easter2015_Shenmishixiang_User_ChgMap("One")
	Sys_MsgBox(tEaster2015_Shenmishixiang_Text["MsgBox"]["ChgMap"])
	User_TalkChannel2005(tEaster2015_Shenmishixiang_Text["TalkChannel2005"]["JoinOne"])
end

--返回双龙城
function Easter2015_Shenmishixiang_Option13_10822(nNpcId)
	Easter2015_Shenmishixiang_User_ChgMap("Zero")
	User_TalkChannel2005(tEaster2015_Shenmishixiang_Text["TalkChannel2005"]["JoinZero"])
end

---------------------------------------------------对话模板部分-----------------------------------------
-- //双龙城 探险者乔治
tNpcFace[3534] = 218
tNpcGossip[10821] = tNpcGossip[10821] or DefaultNpc:new{}
tNpcGossip[10821]["OptionHidden"] = 1

--对白
tNpcGossip[10821]["Text1-1"] = {111,112,113}			-- 活动前
tNpcGossip[10821]["Text1-2"] = {121,122}				-- 活动后
tNpcGossip[10821]["Text1-3"] = {131,132,133}			-- 活动中
tNpcGossip[10821]["Text2-1"] = {211,212}				-- 等级不足
tNpcGossip[10821]["Text2-2"] = {221,222}				-- 当天已获得过礼包
tNpcGossip[10821]["Text2-3"] = {231,232,233,234}		-- 了解详情
tNpcGossip[10821]["Text111"] = tEaster2015_Shenmishixiang_Text[10821]["Text111"]
tNpcGossip[10821]["Text112"] = tEaster2015_Shenmishixiang_Text[10821]["Text112"]
tNpcGossip[10821]["Text113"] = tEaster2015_Shenmishixiang_Text[10821]["Text113"]
tNpcGossip[10821]["Text121"] = tEaster2015_Shenmishixiang_Text[10821]["Text121"]
tNpcGossip[10821]["Text122"] = tEaster2015_Shenmishixiang_Text[10821]["Text122"]
tNpcGossip[10821]["Text131"] = tEaster2015_Shenmishixiang_Text[10821]["Text131"]
tNpcGossip[10821]["Text132"] = tEaster2015_Shenmishixiang_Text[10821]["Text132"]
tNpcGossip[10821]["Text133"] = tEaster2015_Shenmishixiang_Text[10821]["Text133"]
tNpcGossip[10821]["Text211"] = tEaster2015_Shenmishixiang_Text[10821]["Text211"]
tNpcGossip[10821]["Text212"] = tEaster2015_Shenmishixiang_Text[10821]["Text212"]
tNpcGossip[10821]["Text221"] = tEaster2015_Shenmishixiang_Text[10821]["Text221"]
tNpcGossip[10821]["Text222"] = tEaster2015_Shenmishixiang_Text[10821]["Text222"]
tNpcGossip[10821]["Text231"] = tEaster2015_Shenmishixiang_Text[10821]["Text231"]
tNpcGossip[10821]["Text232"] = tEaster2015_Shenmishixiang_Text[10821]["Text232"]
tNpcGossip[10821]["Text233"] = tEaster2015_Shenmishixiang_Text[10821]["Text233"]
tNpcGossip[10821]["Text234"] = tEaster2015_Shenmishixiang_Text[10821]["Text234"]

-- 活动前
tNpcGossip[10821]["ChkFunc1-1"] = function ()
	return Sys_ChkFullTime(tEaster2015_Shenmishixiang_Time["Beftime"])
end

-- 活动后
tNpcGossip[10821]["ChkFunc1-2"] = function ()
	return not Sys_ChkFullTime(tEaster2015_Shenmishixiang_Time["Nowtime"])
end

-- 活动中
tNpcGossip[10821]["ChkFunc1-3"] = function ()
	return Sys_ChkFullTime(tEaster2015_Shenmishixiang_Time["Nowtime"])
end

--选项
tNpcGossip[10821]["tOption1-1"] = {11}
tNpcGossip[10821]["tOption1-2"] = {12}
tNpcGossip[10821]["tOption1-3"] = {13,14,15}
tNpcGossip[10821]["tOption2-1"] = {21}
tNpcGossip[10821]["tOption2-2"] = {22}
tNpcGossip[10821]["tOption2-3"] = {23}
tNpcGossip[10821]["Option11"] = tEaster2015_Shenmishixiang_Text[10821]["Option11"]
tNpcGossip[10821]["Option12"] = tEaster2015_Shenmishixiang_Text[10821]["Option12"]
tNpcGossip[10821]["Option13"] = tEaster2015_Shenmishixiang_Text[10821]["Option13"]
tNpcGossip[10821]["Option14"] = tEaster2015_Shenmishixiang_Text[10821]["Option14"]
tNpcGossip[10821]["Option15"] = tEaster2015_Shenmishixiang_Text[10821]["Option15"]
tNpcGossip[10821]["Option21"] = tEaster2015_Shenmishixiang_Text[10821]["Option21"]
tNpcGossip[10821]["Option22"] = tEaster2015_Shenmishixiang_Text[10821]["Option22"]
tNpcGossip[10821]["Option23"] = tEaster2015_Shenmishixiang_Text[10821]["Option23"]
tNpcGossip[10821]["OptionFunc13"]="Easter2015_Shenmishixiang_Option13_10821</N>10821"
tNpcGossip[10821]["OptionPoint14"]="2-3"
tNpcGossip[10821]["OptionPoint23"]="1-3"

----------------------------------------------------------------------------------------------
-- //复活节岛 探险者乔治
tNpcFace[3535] = 218
tNpcGossip[10822] = tNpcGossip[10822] or DefaultNpc:new{}
tNpcGossip[10822]["OptionHidden"] = 1

--对白
tNpcGossip[10822]["Text1-1"] = {111,112,113}			-- 活动前
tNpcGossip[10822]["Text1-2"] = {121,122}				-- 活动后
tNpcGossip[10822]["Text1-3"] = {131,132,133}			-- 活动中
tNpcGossip[10822]["Text2-1"] = {211}					-- 返回双龙城
tNpcGossip[10822]["Text2-2"] = {221,222,223}			-- 了解详情
tNpcGossip[10822]["Text111"] = tEaster2015_Shenmishixiang_Text[10822]["Text111"]
tNpcGossip[10822]["Text112"] = tEaster2015_Shenmishixiang_Text[10822]["Text112"]
tNpcGossip[10822]["Text113"] = tEaster2015_Shenmishixiang_Text[10822]["Text113"]
tNpcGossip[10822]["Text121"] = tEaster2015_Shenmishixiang_Text[10822]["Text121"]
tNpcGossip[10822]["Text122"] = tEaster2015_Shenmishixiang_Text[10822]["Text122"]
tNpcGossip[10822]["Text131"] = tEaster2015_Shenmishixiang_Text[10822]["Text131"]
tNpcGossip[10822]["Text132"] = tEaster2015_Shenmishixiang_Text[10822]["Text132"]
tNpcGossip[10822]["Text133"] = tEaster2015_Shenmishixiang_Text[10822]["Text133"]
tNpcGossip[10822]["Text211"] = tEaster2015_Shenmishixiang_Text[10822]["Text211"]
tNpcGossip[10822]["Text221"] = tEaster2015_Shenmishixiang_Text[10822]["Text221"]
tNpcGossip[10822]["Text222"] = tEaster2015_Shenmishixiang_Text[10822]["Text222"]
tNpcGossip[10822]["Text223"] = tEaster2015_Shenmishixiang_Text[10822]["Text223"]

-- 活动前
tNpcGossip[10822]["ChkFunc1-1"] = function ()
	return Sys_ChkFullTime(tEaster2015_Shenmishixiang_Time["Beftime"])
end

-- 活动后
tNpcGossip[10822]["ChkFunc1-2"] = function ()
	if Sys_ChkFullTime(tEaster2015_Shenmishixiang_Time["Nowtime"]) then
		return not Sys_ChkFullTime(tEaster2015_Shenmishixiang_Time["Nowtime"])
	end
	Easter2015_Shenmishixiang_User_ChgMap("Zero")
	User_TalkChannel2005(tEaster2015_Shenmishixiang_Text["TalkChannel2005"]["LeaveIsland"])
	return not Sys_ChkFullTime(tEaster2015_Shenmishixiang_Time["Nowtime"])
end

-- 活动中
tNpcGossip[10822]["ChkFunc1-3"] = function ()
	return Sys_ChkFullTime(tEaster2015_Shenmishixiang_Time["Nowtime"])
end

--选项
tNpcGossip[10822]["tOption1-1"] = {11}
tNpcGossip[10822]["tOption1-2"] = {12}
tNpcGossip[10822]["tOption1-3"] = {13,14,15}
tNpcGossip[10822]["tOption2-1"] = {21}
tNpcGossip[10822]["tOption2-2"] = {22}
tNpcGossip[10822]["Option11"] = tEaster2015_Shenmishixiang_Text[10822]["Option11"]
tNpcGossip[10822]["Option12"] = tEaster2015_Shenmishixiang_Text[10822]["Option12"]
tNpcGossip[10822]["Option13"] = tEaster2015_Shenmishixiang_Text[10822]["Option13"]
tNpcGossip[10822]["Option14"] = tEaster2015_Shenmishixiang_Text[10822]["Option14"]
tNpcGossip[10822]["Option15"] = tEaster2015_Shenmishixiang_Text[10822]["Option15"]
tNpcGossip[10822]["Option21"] = tEaster2015_Shenmishixiang_Text[10822]["Option21"]
tNpcGossip[10822]["Option22"] = tEaster2015_Shenmishixiang_Text[10822]["Option22"]
tNpcGossip[10822]["OptionFunc13"]="Easter2015_Shenmishixiang_Option13_10822</N>10822"
tNpcGossip[10822]["OptionPoint14"]="2-2"
---------------------------------怪物死亡掉落--------------------------------------
-- 7670,石像怪人
tMonster[7670] = tMonster[7670] or {}
tMonster[7670]["tFunction"] = tMonster[7670]["tFunction"] or {}
table.insert(tMonster[7670]["tFunction"],Easter2015_Shenmishixiang_Add_Kill_Monster)
-- 7671,巨大的石像怪人
tMonster[7671] = tMonster[7671] or {}
tMonster[7671]["tFunction"] = tMonster[7671]["tFunction"] or {}
table.insert(tMonster[7671]["tFunction"],Easter2015_Shenmishixiang_Add_Kill_Monster)

---------------------------------物品模块--------------------------------------
-- 幸运石晶
tItem[3002951] = tItem[3002951] or {}
tItem[3002951]["Function"] = function(nItemId,sItemName)
	Easter2015_Shenmishixiang_UseItem(nItemId,sItemName)
end
