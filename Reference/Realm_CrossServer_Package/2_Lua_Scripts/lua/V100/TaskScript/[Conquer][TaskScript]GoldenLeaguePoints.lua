------------------------------------------------------------------------------------
--Name:		[征服][任务脚本]添加黄金联赛积分
--Purpose:	添加黄金联赛积分
--Creator: 	郑鋆
--Created:	2015/08/11
------------------------------------------------------------------------------------

-- 命名前缀
-- GoldenLeaguePoints_

-- logId	18000068
-- 常量表
local tInternalTaskCheats_Count = {}
	tInternalTaskCheats_Count["MaxPoint"] = 650

local tGoldenLeaguePoints_Stc = {}
	tGoldenLeaguePoints_Stc["EventType"] = 137
	tGoldenLeaguePoints_Stc["DataType"] = 31

-- 个人竞技场礼包
local tGoldenLeaguePoints_Arenic = {}
	-- 赢场
	tGoldenLeaguePoints_Arenic["Wins"] = {}
	tGoldenLeaguePoints_Arenic["Wins"][1] = 100
	tGoldenLeaguePoints_Arenic["Wins"][2] = 150
	tGoldenLeaguePoints_Arenic["Wins"][3] = 200
	tGoldenLeaguePoints_Arenic["Wins"][4] = 250
	
	-- 参赛场
	tGoldenLeaguePoints_Arenic["Competes"] = {}
	tGoldenLeaguePoints_Arenic["Competes"][1] = 100
	tGoldenLeaguePoints_Arenic["Competes"][3] = 150
	tGoldenLeaguePoints_Arenic["Competes"][5] = 200
	tGoldenLeaguePoints_Arenic["Competes"][7] = 200

-- 组队竞技场礼包
local tGoldenLeaguePoints_TeamArenic = {}
	-- 赢场
	tGoldenLeaguePoints_TeamArenic["Wins"] = {}
	tGoldenLeaguePoints_TeamArenic["Wins"][1] = 100
	tGoldenLeaguePoints_TeamArenic["Wins"][2] = 150
	tGoldenLeaguePoints_TeamArenic["Wins"][3] = 200
	tGoldenLeaguePoints_TeamArenic["Wins"][4] = 250
	
	-- 参赛场
	tGoldenLeaguePoints_TeamArenic["Competes"] = {}
	tGoldenLeaguePoints_TeamArenic["Competes"][1] = 100
	tGoldenLeaguePoints_TeamArenic["Competes"][3] = 150
	tGoldenLeaguePoints_TeamArenic["Competes"][5] = 200
	tGoldenLeaguePoints_TeamArenic["Competes"][7] = 200

-- +3骏马可选包
local tGoldenLeaguePoints_Horse = {}
	tGoldenLeaguePoints_Horse[1] = "0 0 3 0 0 0 65430 0 255 0 3 0 0 0 0 0 0 150"
	tGoldenLeaguePoints_Horse[2] = "0 0 3 0 0 0 9830655 150 0 0 3 0 0 0 0 0 0 255"
	tGoldenLeaguePoints_Horse[3] = "0 0 3 0 0 0 16750080 255 150 0 3"
	
	tGoldenLeaguePoints_Horse[4] = "0 0 3 0 0 0 65430 0 255 0 1 0 0 0 0 0 0 150"
	tGoldenLeaguePoints_Horse[5] = "0 0 3 0 0 0 9830655 150 0 0 1 0 0 0 0 0 0 255"
	tGoldenLeaguePoints_Horse[6] = "0 0 3 0 0 0 16750080 255 150 0 1"

--------------------------------------------逻辑部分-----------------------------------------------
-- 判断是否可以加黄金联赛积分
function GoldenLeaguePoints_Chk(nPoint)
	local nEvent = tGoldenLeaguePoints_Stc["EventType"]
	local nType = tGoldenLeaguePoints_Stc["DataType"]
	
	-- 判断掩码是否隔天
	if Task_StcInterval(nEvent,nType,1,4) then
		Task_SetStatistic(nEvent,nType,0,1)
		Task_SetStcTimestamp(nEvent,nType,0,0)
	end
	
	-- 判断今天是否已达上限
	if Task_ChkStcValue(nEvent,nType,">=",tInternalTaskCheats_Count["MaxPoint"]) then
		User_TalkChannel2005(string.format(tInternalTaskCheats_Text["Top"],tInternalTaskCheats_Count["MaxPoint"]))
		return false
	end
	
	return true
end

-- 添加黄金联赛积分
function GoldenLeaguePoints_Add(nPoint,nUserId)
	local nEvent = tGoldenLeaguePoints_Stc["EventType"]
	local nType = tGoldenLeaguePoints_Stc["DataType"]
	local nUserId = nUserId or 0
	
	-- 判断掩码是否隔天
	if Task_StcInterval(nEvent,nType,1,4,nUserId) then
		Task_SetStatistic(nEvent,nType,0,1,nUserId)
		Task_SetStcTimestamp(nEvent,nType,0,nUserId)
	end
	
	-- 判断今天是否已达上限
	if Task_ChkStcValue(nEvent,nType,">=",tInternalTaskCheats_Count["MaxPoint"],nUserId) then
		User_TalkChannel2005(string.format(tInternalTaskCheats_Text["Top"],tInternalTaskCheats_Count["MaxPoint"]),nUserId)
		return false
	end
	
	local nAddPoint = nPoint
	local nData = Get_UserStatisticValue(nEvent,nType,nUserId)
	if nPoint + nData > tInternalTaskCheats_Count["MaxPoint"] then
		nAddPoint = tInternalTaskCheats_Count["MaxPoint"] - nData
	end
	
	-- 加掩码
	Task_AddStatistic(nEvent,nType,nAddPoint,1,nUserId)
	Task_SetStcTimestamp(nEvent,nType,0,nUserId)
	
	-- 加积分
	User_AddLeaguePoint(nAddPoint,nUserId)
	
	-- 打log
	Sys_SaveActionFestivalLog(string.format("0,0,3005061,1,10002361,2,21,%d",nAddPoint))
	
	-- 给提示
	User_TalkChannel2005(string.format(tInternalTaskCheats_Text["GolderLeaguePoint"],nAddPoint))
	return true
end

-- 个人排位赛 赢场
function GoldenLeaguePoints_Arenic_Wins(nUserId,nFieldNum)
	if tGoldenLeaguePoints_Arenic["Wins"][nFieldNum] == nil then
		return
	end
	
	local nAddPoint = tGoldenLeaguePoints_Arenic["Wins"][nFieldNum]
	GoldenLeaguePoints_Add(nAddPoint,nUserId)
	
	if Item_AddItem(3007309) then
		User_TalkChannel2005(tInternalTaskCheats_Text["ArenicWins"])
	end
end

-- 个人排位赛 参赛场
function GoldenLeaguePoints_Arenic_Competes(nUserId,nFieldNum)
	if tGoldenLeaguePoints_Arenic["Competes"][nFieldNum] == nil then
		return
	end
	
	local nAddPoint = tGoldenLeaguePoints_Arenic["Competes"][nFieldNum]
	GoldenLeaguePoints_Add(nAddPoint,nUserId)
	
	if Item_AddItem(3007309) then
		User_TalkChannel2005(tInternalTaskCheats_Text["ArenicCompetes"])
	end
end

-- 组队排位赛 赢场
function GoldenLeaguePoints_Arenic_TeamWins(nUserId,nFieldNum)
	if tGoldenLeaguePoints_TeamArenic["Wins"][nFieldNum] == nil then
		return
	end
	
	local nAddPoint = tGoldenLeaguePoints_TeamArenic["Wins"][nFieldNum]
	GoldenLeaguePoints_Add(nAddPoint,nUserId)
	
	if Item_AddItem(3007308) then
		User_TalkChannel2005(tInternalTaskCheats_Text["ArenicTeamWins"])
	end
end

-- 组队排位赛 参赛场
function GoldenLeaguePoints_Arenic_TeamCompetes(nUserId,nFieldNum)
	if tGoldenLeaguePoints_TeamArenic["Competes"][nFieldNum] == nil then
		return
	end
	
	local nAddPoint = tGoldenLeaguePoints_TeamArenic["Competes"][nFieldNum]
	GoldenLeaguePoints_Add(nAddPoint,nUserId)
	
	if Item_AddItem(3007308) then
		User_TalkChannel2005(tInternalTaskCheats_Text["ArenicTeamCompetes"])
	end
end

-- 骑宠，玩家冲过终点是触发
function GoldenLeaguePoints_RideArriveTerminal(nUserId)
	GoldenLeaguePoints_Add(100,nUserId)
end

-- 武功，每次修炼时触发：
function GoldenLeaguePoints_TrainGongFu(nUserId,nTrainNum)
	GoldenLeaguePoints_Add(10,nUserId)
end

-- 获得+3马匹
function GoldenLeaguePoints_RewardTheHorses(nItemId,nType)
	if Item_ChkItem(nItemId,1) and Item_DelItem(nItemId,1) then
		Item_AddNewItem(300000,tGoldenLeaguePoints_Horse[nType])
		Sys_SaveActionTaskLog(string.format("0,0,%d,1,18000068,2,300000,1",nItemId))
		User_TalkChannel2005(tInternalTaskCheats_Text[nItemId][nType])
	end
end

--------------------------------------------物品部分-----------------------------------------------
-- 豪华护心丹礼包
tItem[3007285] = tItem[3007285] or {}
tItem[3007285]["Function"] = function(nItemId,sItemName)
	-- 判断玩家是否自创武功
	local nUserId = Get_UserId()
	if not User_IsAlreadyCreateGongFu(nUserId) then
		User_TalkChannel2005(tInternalTaskCheats_Text["NoGongFu"])
		return
	end
	
	-- 判断背包空间
	if not User_CheckLeftSpace(14) then
		User_TalkChannel2005(tInternalTaskCheats_Text[nItemId]["Space"])
		return
	end
	
	if Item_ChkItem(nItemId,1) and Item_DelItem(nItemId,1) then
		Item_AddItem(3002029,0,15,0,0,1)
		
		-- 打log
		Sys_SaveActionTaskLog("0,0,3007285,1,18000068,2,3002029,1")
		
		-- 给提示
		User_TalkChannel2005(tInternalTaskCheats_Text[nItemId]["Reward"])
	end
end

-- 黄金修炼礼包
tItem[3007284] = tItem[3007284] or {}
tItem[3007284]["Function"] = function(nItemId,sItemName)
	-- 判断玩家是否自创武功
	local nUserId = Get_UserId()
	if not User_IsAlreadyCreateGongFu(nUserId) then
		User_TalkChannel2005(tInternalTaskCheats_Text["NoGongFu"])
		return
	end
	
	-- 判断玩家修炼次数是否达上限
	local nQenuineqi = Get_UserGongFureePractNum()
	local nAddNum = 100000
	
	-- 判断免费修炼次数
	if nQenuineqi > G_User_FreePractice - nAddNum then
		User_TalkChannel2005(tInternalTaskCheats_Text[nItemId]["FreePractice"])
		return
	end

	if Item_ChkItem(nItemId,1) and Item_DelItem(nItemId,1) then
		User_AddGongFuFreePractNum(nAddNum)
		
		-- 打log
		Sys_SaveActionTaskLog("0,0,3007284,1,18000068,2,17,10")
		
		-- 给提示
		User_TalkChannel2005(tInternalTaskCheats_Text[nItemId]["Reward"])
	end
end

-- 豪华七星断续礼包
tItem[3007286] = tItem[3007286] or {}
tItem[3007286]["Function"] = function(nItemId,sItemName)
	-- 判断背包空间
	if not User_CheckLeftSpace(3) then
		User_TalkChannel2005(tInternalTaskCheats_Text[nItemId]["Space"])
		return
	end
	
	if Item_ChkItem(nItemId,1) and Item_DelItem(nItemId,1) then
		Item_AddItem(1003010,0,20,3)
		
		-- 打log
		Sys_SaveActionTaskLog("0,0,3007286,1,18000068,2,1003010,20")

		-- 给提示
		User_TalkChannel2005(tInternalTaskCheats_Text[nItemId]["Reward"])
	end
end

-- +3骏马可选包
tItem[3007283] = tItem[3007283] or {}
tItem[3007283]["Text1-1"] = {111}
tItem[3007283]["Text111"] = tInternalTaskCheats_Text[3007283]["111"]
tItem[3007283]["tOption1-1"] = {1,2,3}
tItem[3007283]["Option1"] = tInternalTaskCheats_Text[3007283]["Option1"]
tItem[3007283]["OptionPoint1"]="2-1"
tItem[3007283]["Option2"] = tInternalTaskCheats_Text[3007283]["Option2"]
tItem[3007283]["OptionPoint2"]="2-2"
tItem[3007283]["Option3"] = tInternalTaskCheats_Text[3007283]["Option3"]
tItem[3007283]["OptionPoint3"]="2-3"

tItem[3007283]["Text2-1"] = {211}
tItem[3007283]["Text211"] = tInternalTaskCheats_Text[3007283]["211"]
tItem[3007283]["tOption2-1"] = {4,5}
tItem[3007283]["Option4"] = tInternalTaskCheats_Text[3007283]["Option4"]
tItem[3007283]["OptionFunc4"]="GoldenLeaguePoints_RewardTheHorses</N>3007283</N>1"
tItem[3007283]["Option5"] = tInternalTaskCheats_Text[3007283]["Option5"]

tItem[3007283]["Text2-2"] = {221}
tItem[3007283]["Text221"] = tInternalTaskCheats_Text[3007283]["221"]
tItem[3007283]["tOption2-2"] = {6,7}
tItem[3007283]["Option6"] = tInternalTaskCheats_Text[3007283]["Option6"]
tItem[3007283]["OptionFunc6"]="GoldenLeaguePoints_RewardTheHorses</N>3007283</N>2"
tItem[3007283]["Option7"] = tInternalTaskCheats_Text[3007283]["Option7"]

tItem[3007283]["Text2-3"] = {231}
tItem[3007283]["Text231"] = tInternalTaskCheats_Text[3007283]["231"]
tItem[3007283]["tOption2-3"] = {8,9}
tItem[3007283]["Option8"] = tInternalTaskCheats_Text[3007283]["Option8"]
tItem[3007283]["OptionFunc8"]="GoldenLeaguePoints_RewardTheHorses</N>3007283</N>3"
tItem[3007283]["Option9"] = tInternalTaskCheats_Text[3007283]["Option9"]

-- +1骏马可选包
tItem[3007287] = tItem[3007287] or {}
tItem[3007287]["Text1-1"] = {111}
tItem[3007287]["Text111"] = tInternalTaskCheats_Text[3007287]["111"]
tItem[3007287]["tOption1-1"] = {1,2,3}
tItem[3007287]["Option1"] = tInternalTaskCheats_Text[3007287]["Option1"]
tItem[3007287]["OptionPoint1"]="2-1"
tItem[3007287]["Option2"] = tInternalTaskCheats_Text[3007287]["Option2"]
tItem[3007287]["OptionPoint2"]="2-2"
tItem[3007287]["Option3"] = tInternalTaskCheats_Text[3007287]["Option3"]
tItem[3007287]["OptionPoint3"]="2-3"

tItem[3007287]["Text2-1"] = {211}
tItem[3007287]["Text211"] = tInternalTaskCheats_Text[3007287]["211"]
tItem[3007287]["tOption2-1"] = {4,5}
tItem[3007287]["Option4"] = tInternalTaskCheats_Text[3007287]["Option4"]
tItem[3007287]["OptionFunc4"]="GoldenLeaguePoints_RewardTheHorses</N>3007287</N>4"
tItem[3007287]["Option5"] = tInternalTaskCheats_Text[3007287]["Option5"]

tItem[3007287]["Text2-2"] = {221}
tItem[3007287]["Text221"] = tInternalTaskCheats_Text[3007287]["221"]
tItem[3007287]["tOption2-2"] = {6,7}
tItem[3007287]["Option6"] = tInternalTaskCheats_Text[3007287]["Option6"]
tItem[3007287]["OptionFunc6"]="GoldenLeaguePoints_RewardTheHorses</N>3007287</N>5"
tItem[3007287]["Option7"] = tInternalTaskCheats_Text[3007287]["Option7"]

tItem[3007287]["Text2-3"] = {231}
tItem[3007287]["Text231"] = tInternalTaskCheats_Text[3007287]["231"]
tItem[3007287]["tOption2-3"] = {8,9}
tItem[3007287]["Option8"] = tInternalTaskCheats_Text[3007287]["Option8"]
tItem[3007287]["OptionFunc8"]="GoldenLeaguePoints_RewardTheHorses</N>3007287</N>6"
tItem[3007287]["Option9"] = tInternalTaskCheats_Text[3007287]["Option9"]

-- 豪华三清回魂散礼包
tItem[3007434] = tItem[3007434] or {}
tItem[3007434]["Function"] = function(nItemId,sItemName)
	-- 判断背包空间
	if not User_CheckLeftSpace(3) then
		User_TalkChannel2005(tInternalTaskCheats_Text[nItemId]["Space"])
		return
	end
	
	if Item_ChkItem(nItemId,1) and Item_DelItem(nItemId,1) then
		Item_AddItem(1004010,0,20,3)
		User_EffectAdd("self","angelwing")
		-- 打log
		Sys_SaveActionTaskLog("0,0,3007434,1,18000068,2,1004010,20")

		-- 给提示
		User_TalkChannel2005(tInternalTaskCheats_Text[nItemId]["Reward"])
	end
end

------------------------------------------------------------------------------------------------
-- 个人排位赛：	赢场：
tArenicWins["tFunction"] = tArenicWins["tFunction"] or {}
table.insert(tArenicWins["tFunction"],GoldenLeaguePoints_Arenic_Wins)

-- 个人排位赛：	参赛场
tArenicCompetes["tFunction"] = tArenicCompetes["tFunction"] or {}
table.insert(tArenicCompetes["tFunction"],GoldenLeaguePoints_Arenic_Competes)

-- 组队排位赛：	赢场：
tTeamArenicWins["tFunction"] = tTeamArenicWins["tFunction"] or {}
table.insert(tTeamArenicWins["tFunction"],GoldenLeaguePoints_Arenic_TeamWins)

-- 组队排位赛：	参赛场
tTeamArenicCompetes["tFunction"] = tTeamArenicCompetes["tFunction"] or {}
table.insert(tTeamArenicCompetes["tFunction"],GoldenLeaguePoints_Arenic_TeamCompetes)

-- 骑宠，玩家冲过终点是触发
tRideArrive["tFunction"] = tRideArrive["tFunction"] or {}
table.insert(tRideArrive["tFunction"],GoldenLeaguePoints_RideArriveTerminal)

-- 武功，每次修炼时触发：
tTrainGongFu["tFunction"] = tTrainGongFu["tFunction"] or {}
table.insert(tTrainGongFu["tFunction"],GoldenLeaguePoints_TrainGongFu)
