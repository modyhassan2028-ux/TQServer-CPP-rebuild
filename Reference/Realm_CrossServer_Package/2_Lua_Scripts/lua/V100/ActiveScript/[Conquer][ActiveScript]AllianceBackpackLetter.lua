------------------------------------------------------------------------------------
--Name:		[征服][活动脚本]联盟功能背包信
--Purpose:	联盟功能背包信
--Creator: 	郑鋆
--Created:	2015/07/30
------------------------------------------------------------------------------------

-- 命名前缀
-- AllianceBackpackLetter_


-- 常量表
local tAllianceBackpackLetter_Count = {}
	-- 背包信物品ID
	tAllianceBackpackLetter_Count["Backpack"] = 3006952
	-- 最大的题目数
	tAllianceBackpackLetter_Count["MaxTopic"] = 7

-- stc掩码表
local tAllianceBackpackLetter_Stc = {}
	tAllianceBackpackLetter_Stc["EventType"] = 136
	tAllianceBackpackLetter_Stc["DataType"] = {}
	tAllianceBackpackLetter_Stc["DataType"][1] = 32
	tAllianceBackpackLetter_Stc["DataType"][2] = 33
	tAllianceBackpackLetter_Stc["MaxData"] = 1

-- 对白对应的索引
local tAllianceBackpackLetter_Index = {}
	tAllianceBackpackLetter_Index[1] = "3-1"
	tAllianceBackpackLetter_Index[2] = "3-2"
	tAllianceBackpackLetter_Index[3] = "3-3"
	tAllianceBackpackLetter_Index[4] = "3-4"
	tAllianceBackpackLetter_Index[5] = "3-5"
	tAllianceBackpackLetter_Index[6] = "3-6"
	tAllianceBackpackLetter_Index[7] = "3-7"

local tAllianceBackpackLetter_AnswerIndex = {}
	tAllianceBackpackLetter_AnswerIndex[1] = "4-1"
	tAllianceBackpackLetter_AnswerIndex[2] = "4-2"
	tAllianceBackpackLetter_AnswerIndex[3] = "4-3"
	tAllianceBackpackLetter_AnswerIndex[4] = "4-4"

-- 寻路数据
local tAllianceBackpackLetter_NpcData = {}
	-- 答题NPC
	tAllianceBackpackLetter_NpcData[18740] = {}
	tAllianceBackpackLetter_NpcData[18740]["MapId"] = 1002
	tAllianceBackpackLetter_NpcData[18740]["PosX"] = 309
	tAllianceBackpackLetter_NpcData[18740]["PosY"] = 348
	-- 国战战备官
	tAllianceBackpackLetter_NpcData[18797] = {}
	tAllianceBackpackLetter_NpcData[18797]["MapId"] = 1002
	tAllianceBackpackLetter_NpcData[18797]["PosX"] = 317
	tAllianceBackpackLetter_NpcData[18797]["PosY"] = 251

	
--------------------------------------逻辑部分-----------------------------------------

-- 领取背包信
function AllianceBackpackLetter_Backpack()
	local nEvent = tAllianceBackpackLetter_Stc["EventType"]
	local nType = tAllianceBackpackLetter_Stc["DataType"][1]
	
	-- 判断玩家等级是否满足
	if not User_JudgeLevelAndMetempsychosis(100,0) then
		return
	end
	
	-- 判断是否领取过了
	if Task_ChkStcValue(nEvent,nType,">=",tAllianceBackpackLetter_Stc["MaxData"]) then
		return
	end
	
	local nItemId = tAllianceBackpackLetter_Count["Backpack"]
	
	-- 判断背包是否有该物品
	if Item_ChkItem(nItemId) then
		return
	end
	
	-- 判断背包空间
	if not User_CheckLeftSpace(1) then
		User_TalkChannel2005(tAllianceBackpackLetter_Text[nItemId]["NoSpace"])
		return
	end
	
	Task_SetStatistic(nEvent,nType,tAllianceBackpackLetter_Stc["MaxData"],1)
	
	-- 添加物品
	Item_AddItem(nItemId)
	
	-- 打log
	Sys_SaveActionFestivalLog(string.format("0,0,0,0,12000138,2,%d,1",nItemId))
	
	-- 给提示
	User_TalkChannel2005(tAllianceBackpackLetter_Text[nItemId]["RewardItem"])
end

-- 答题
function AllianceBackpackLetter_OpenBackpack(nNpcId)
	-- 判断玩家等级是否满足
	if not User_JudgeLevelAndMetempsychosis(100,0) then
		LinkNpcGossipFunc_New(nNpcId,"4-5")
		return
	end
	
	local nEvent = tAllianceBackpackLetter_Stc["EventType"]
	local nType = tAllianceBackpackLetter_Stc["DataType"][2]
	local nData = Get_UserStatisticValue(nEvent,nType)
	
	-- 判断是否隔天
	if Task_StcInterval(nEvent,nType,1,4) then
		Task_SetStatistic(nEvent,nType,0,1)
		Task_SetStcTimestamp(nEvent,nType,0)
		nData = 0
		
	-- 判断今天是否答题完了
	elseif nData >= tAllianceBackpackLetter_Count["MaxTopic"] then
		Sys_MsgBox(tAllianceBackpackLetter_Text[nNpcId]["Complete"])
		return
	end
	
	
	local sIndex = tAllianceBackpackLetter_Index[nData + 1]
	
	LinkNpcGossipFunc_New(nNpcId,sIndex)
end

-- 答题正确
function AllianceBackpackLetter_AnswerSuccess(nNpcId)
	-- 答题数+1
	local nEvent = tAllianceBackpackLetter_Stc["EventType"]
	local nType = tAllianceBackpackLetter_Stc["DataType"][2]

	Task_AddStatistic(nEvent,nType,1,1)
	Task_SetStcTimestamp(nEvent,nType,0)

	-- 给奖励
	local nFlat = 0

	local nLevel = Get_UserLevel()
	
	if nLevel < 140 then
		User_AddExpTime(10)
		nFlat = 1
	else
		User_AddStrengthValue(10)
		nFlat = 2
	end

	-- 判断今天是否答题完了
	if Task_ChkStcValue(nEvent,nType,">=",tAllianceBackpackLetter_Count["MaxTopic"]) then
		User_TalkChannel2005(tAllianceBackpackLetter_Text[nNpcId]["Reward"])
		
		nFlat = nFlat + 2
	end
	
	local sIndex = tAllianceBackpackLetter_AnswerIndex[nFlat]
	LinkNpcGossipFunc_New(nNpcId,sIndex)
end

-- 答题错误
function AllianceBackpackLetter_AnswerError(nNpcId)
	local nEvent = tAllianceBackpackLetter_Stc["EventType"]
	local nType = tAllianceBackpackLetter_Stc["DataType"][2]
	local nData = Get_UserStatisticValue(nEvent,nType)
	local sIndex = tAllianceBackpackLetter_Index[nData + 1]
	
	LinkNpcGossipFunc_New(nNpcId,sIndex)
	
	Sys_MsgBox(tAllianceBackpackLetter_Text[nNpcId]["Error"])
end

-- 前往答题处（寻路）
function AllianceBackpackLetter_AutoPath(nItemId,nNpcId)
	if not Item_ChkItem(nItemId) then
		return
	end
	
	local nMapId = tAllianceBackpackLetter_NpcData[nNpcId]["MapId"]
	local nPosX = tAllianceBackpackLetter_NpcData[nNpcId]["PosX"]
	local nPosY = tAllianceBackpackLetter_NpcData[nNpcId]["PosY"]

	-- 自动寻路
	Sys_GotoSomeWhere(nPosX,nPosY,nMapId,nNpcId)
end

-------------------------------------------------NPC配置------------------------------------------------
-- 联盟国战问答官
tNpcFace[3745] = 43
tNpcGossip[18740] = tNpcGossip[18740] or DefaultNpc:new{}
tNpcGossip[18740]["OptionHidden"] = 1

tNpcGossip[18740]["Text1-1"] = {111,112}
tNpcGossip[18740]["Text111"] = tAllianceBackpackLetter_Text[18740]["111"]
tNpcGossip[18740]["Text112"] = tAllianceBackpackLetter_Text[18740]["112"]
tNpcGossip[18740]["tOption1-1"] = {1,2,21}

tNpcGossip[18740]["Option1"] = tAllianceBackpackLetter_Text[18740]["Option1"]
tNpcGossip[18740]["OptionFunc1"]="AllianceBackpackLetter_OpenBackpack</N>18740"
tNpcGossip[18740]["Option2"] = tAllianceBackpackLetter_Text[18740]["Option2"]
tNpcGossip[18740]["OptionPoint2"]="2-1"
tNpcGossip[18740]["Option21"] = tAllianceBackpackLetter_Text[18740]["Option21"]

tNpcGossip[18740]["Text2-1"] = {211,212}
tNpcGossip[18740]["Text211"] = tAllianceBackpackLetter_Text[18740]["211"]
tNpcGossip[18740]["Text212"] = tAllianceBackpackLetter_Text[18740]["212"]
tNpcGossip[18740]["tOption2-1"] = {3}
tNpcGossip[18740]["Option3"] = tAllianceBackpackLetter_Text[18740]["Option3"]
tNpcGossip[18740]["OptionPoint3"]="2-2"

tNpcGossip[18740]["Text2-2"] = {221,222,223}
tNpcGossip[18740]["Text221"] = tAllianceBackpackLetter_Text[18740]["221"]
tNpcGossip[18740]["Text222"] = tAllianceBackpackLetter_Text[18740]["222"]
tNpcGossip[18740]["Text223"] = tAllianceBackpackLetter_Text[18740]["223"]
tNpcGossip[18740]["tOption2-2"] = {4}
tNpcGossip[18740]["Option4"] = tAllianceBackpackLetter_Text[18740]["Option4"]
tNpcGossip[18740]["OptionPoint4"]="2-3"

tNpcGossip[18740]["Text2-3"] = {231,232,233}
tNpcGossip[18740]["Text231"] = tAllianceBackpackLetter_Text[18740]["231"]
tNpcGossip[18740]["Text232"] = tAllianceBackpackLetter_Text[18740]["232"]
tNpcGossip[18740]["Text233"] = tAllianceBackpackLetter_Text[18740]["233"]
tNpcGossip[18740]["tOption2-3"] = {5}
tNpcGossip[18740]["Option5"] = tAllianceBackpackLetter_Text[18740]["Option5"]
tNpcGossip[18740]["OptionPoint5"]="2-4"

tNpcGossip[18740]["Text2-4"] = {241,242,243}
tNpcGossip[18740]["Text241"] = tAllianceBackpackLetter_Text[18740]["241"]
tNpcGossip[18740]["Text242"] = tAllianceBackpackLetter_Text[18740]["242"]
tNpcGossip[18740]["Text243"] = tAllianceBackpackLetter_Text[18740]["243"]
tNpcGossip[18740]["tOption2-4"] = {6}
tNpcGossip[18740]["Option6"] = tAllianceBackpackLetter_Text[18740]["Option6"]

tNpcGossip[18740]["Text3-1"] = {311,312}
tNpcGossip[18740]["Text311"] = tAllianceBackpackLetter_Text[18740]["311"]
tNpcGossip[18740]["Text312"] = tAllianceBackpackLetter_Text[18740]["312"]
tNpcGossip[18740]["tOption3-1"] = {7,8}
tNpcGossip[18740]["Option7"] = tAllianceBackpackLetter_Text[18740]["Option7"]
tNpcGossip[18740]["OptionFunc7"]="AllianceBackpackLetter_AnswerSuccess</N>18740"
tNpcGossip[18740]["Option8"] = tAllianceBackpackLetter_Text[18740]["Option8"]
tNpcGossip[18740]["OptionFunc8"]="AllianceBackpackLetter_AnswerError</N>18740"

tNpcGossip[18740]["Text3-2"] = {321,322,323}
tNpcGossip[18740]["Text321"] = tAllianceBackpackLetter_Text[18740]["321"]
tNpcGossip[18740]["Text322"] = tAllianceBackpackLetter_Text[18740]["322"]
tNpcGossip[18740]["Text323"] = tAllianceBackpackLetter_Text[18740]["323"]
tNpcGossip[18740]["tOption3-2"] = {9,10}
tNpcGossip[18740]["Option9"] = tAllianceBackpackLetter_Text[18740]["Option9"]
tNpcGossip[18740]["OptionFunc9"]="AllianceBackpackLetter_AnswerSuccess</N>18740"
tNpcGossip[18740]["Option10"] = tAllianceBackpackLetter_Text[18740]["Option10"]
tNpcGossip[18740]["OptionFunc10"]="AllianceBackpackLetter_AnswerError</N>18740"

tNpcGossip[18740]["Text3-3"] = {331,332}
tNpcGossip[18740]["Text331"] = tAllianceBackpackLetter_Text[18740]["331"]
tNpcGossip[18740]["Text332"] = tAllianceBackpackLetter_Text[18740]["332"]
tNpcGossip[18740]["tOption3-3"] = {11,12}
tNpcGossip[18740]["Option11"] = tAllianceBackpackLetter_Text[18740]["Option11"]
tNpcGossip[18740]["OptionFunc11"]="AllianceBackpackLetter_AnswerSuccess</N>18740"
tNpcGossip[18740]["Option12"] = tAllianceBackpackLetter_Text[18740]["Option12"]
tNpcGossip[18740]["OptionFunc12"]="AllianceBackpackLetter_AnswerError</N>18740"

tNpcGossip[18740]["Text3-4"] = {341}
tNpcGossip[18740]["Text341"] = tAllianceBackpackLetter_Text[18740]["341"]
tNpcGossip[18740]["tOption3-4"] = {13,14}
tNpcGossip[18740]["Option13"] = tAllianceBackpackLetter_Text[18740]["Option13"]
tNpcGossip[18740]["OptionFunc13"]="AllianceBackpackLetter_AnswerSuccess</N>18740"
tNpcGossip[18740]["Option14"] = tAllianceBackpackLetter_Text[18740]["Option14"]
tNpcGossip[18740]["OptionFunc14"]="AllianceBackpackLetter_AnswerError</N>18740"

tNpcGossip[18740]["Text3-5"] = {351}
tNpcGossip[18740]["Text351"] = tAllianceBackpackLetter_Text[18740]["351"]
tNpcGossip[18740]["tOption3-5"] = {15,16}
tNpcGossip[18740]["Option15"] = tAllianceBackpackLetter_Text[18740]["Option15"]
tNpcGossip[18740]["OptionFunc15"]="AllianceBackpackLetter_AnswerSuccess</N>18740"
tNpcGossip[18740]["Option16"] = tAllianceBackpackLetter_Text[18740]["Option16"]
tNpcGossip[18740]["OptionFunc16"]="AllianceBackpackLetter_AnswerError</N>18740"

tNpcGossip[18740]["Text3-6"] = {361}
tNpcGossip[18740]["Text361"] = tAllianceBackpackLetter_Text[18740]["361"]
tNpcGossip[18740]["tOption3-6"] = {17,18}
tNpcGossip[18740]["Option17"] = tAllianceBackpackLetter_Text[18740]["Option17"]
tNpcGossip[18740]["OptionFunc17"]="AllianceBackpackLetter_AnswerSuccess</N>18740"
tNpcGossip[18740]["Option18"] = tAllianceBackpackLetter_Text[18740]["Option18"]
tNpcGossip[18740]["OptionFunc18"]="AllianceBackpackLetter_AnswerError</N>18740"

tNpcGossip[18740]["Text3-7"] = {371}
tNpcGossip[18740]["Text371"] = tAllianceBackpackLetter_Text[18740]["371"]
tNpcGossip[18740]["tOption3-7"] = {19,20}
tNpcGossip[18740]["Option19"] = tAllianceBackpackLetter_Text[18740]["Option19"]
tNpcGossip[18740]["OptionFunc19"]="AllianceBackpackLetter_AnswerSuccess</N>18740"
tNpcGossip[18740]["Option20"] = tAllianceBackpackLetter_Text[18740]["Option20"]
tNpcGossip[18740]["OptionFunc20"]="AllianceBackpackLetter_AnswerError</N>18740"

tNpcGossip[18740]["Text4-1"] = {411}
tNpcGossip[18740]["Text411"] = tAllianceBackpackLetter_Text[18740]["411"]
tNpcGossip[18740]["tOption4-1"] = {22}
tNpcGossip[18740]["Option22"] = tAllianceBackpackLetter_Text[18740]["Option22"]
tNpcGossip[18740]["OptionFunc22"]="AllianceBackpackLetter_OpenBackpack</N>18740"

tNpcGossip[18740]["Text4-2"] = {421}
tNpcGossip[18740]["Text421"] = tAllianceBackpackLetter_Text[18740]["421"]
tNpcGossip[18740]["tOption4-2"] = {22}

tNpcGossip[18740]["Text4-3"] = {431}
tNpcGossip[18740]["Text431"] = tAllianceBackpackLetter_Text[18740]["431"]
tNpcGossip[18740]["tOption4-3"] = {23}
tNpcGossip[18740]["Option23"] = tAllianceBackpackLetter_Text[18740]["Option23"]

tNpcGossip[18740]["Text4-4"] = {441}
tNpcGossip[18740]["Text441"] = tAllianceBackpackLetter_Text[18740]["441"]
tNpcGossip[18740]["tOption4-4"] = {23}

tNpcGossip[18740]["Text4-5"] = {451,452}
tNpcGossip[18740]["Text451"] = tAllianceBackpackLetter_Text[18740]["451"]
tNpcGossip[18740]["Text452"] = tAllianceBackpackLetter_Text[18740]["452"]
tNpcGossip[18740]["tOption4-5"] = {24}
tNpcGossip[18740]["Option24"] = tAllianceBackpackLetter_Text[18740]["Option24"]

-------------------------------------------------物品配置-----------------------------------------------
-- 联盟告示
tItem[3006952] = tItem[3006952] or {}
tItem[3006952]["Text1-1"] = {111,112}
tItem[3006952]["Text111"] = tAllianceBackpackLetter_Text[3006952]["111"]
tItem[3006952]["Text112"] = tAllianceBackpackLetter_Text[3006952]["112"]
tItem[3006952]["tOption1-1"] = {1,2,113}
tItem[3006952]["Option1"] = tAllianceBackpackLetter_Text[3006952]["Option1"]
tItem[3006952]["OptionPoint1"]="2-1"
tItem[3006952]["Option2"] = tAllianceBackpackLetter_Text[3006952]["Option2"]
tItem[3006952]["OptionFunc2"]="AllianceBackpackLetter_AutoPath</N>3006952</N>18740"
tItem[3006952]["Option113"] = tAllianceBackpackLetter_Text[3006952]["Option113"]
tItem[3006952]["OptionPoint113"]="3-1"

tItem[3006952]["Text2-1"] = {211,212}
tItem[3006952]["Text211"] = tAllianceBackpackLetter_Text[3006952]["211"]
tItem[3006952]["Text212"] = tAllianceBackpackLetter_Text[3006952]["212"]
tItem[3006952]["tOption2-1"] = {3}
tItem[3006952]["Option3"] = tAllianceBackpackLetter_Text[3006952]["Option3"]
tItem[3006952]["OptionPoint3"]="2-2"

tItem[3006952]["Text2-2"] = {221,222,223}
tItem[3006952]["Text221"] = tAllianceBackpackLetter_Text[3006952]["221"]
tItem[3006952]["Text222"] = tAllianceBackpackLetter_Text[3006952]["222"]
tItem[3006952]["Text223"] = tAllianceBackpackLetter_Text[3006952]["223"]
tItem[3006952]["tOption2-2"] = {4}
tItem[3006952]["Option4"] = tAllianceBackpackLetter_Text[3006952]["Option4"]
tItem[3006952]["OptionPoint4"]="2-3"

tItem[3006952]["Text2-3"] = {231,232,233}
tItem[3006952]["Text231"] = tAllianceBackpackLetter_Text[3006952]["231"]
tItem[3006952]["Text232"] = tAllianceBackpackLetter_Text[3006952]["232"]
tItem[3006952]["Text233"] = tAllianceBackpackLetter_Text[3006952]["233"]
tItem[3006952]["tOption2-3"] = {5}
tItem[3006952]["Option5"] = tAllianceBackpackLetter_Text[3006952]["Option5"]
tItem[3006952]["OptionPoint5"]="2-4"

tItem[3006952]["Text2-4"] = {241,242,243}
tItem[3006952]["Text241"] = tAllianceBackpackLetter_Text[3006952]["241"]
tItem[3006952]["Text242"] = tAllianceBackpackLetter_Text[3006952]["242"]
tItem[3006952]["Text243"] = tAllianceBackpackLetter_Text[3006952]["243"]
tItem[3006952]["tOption2-4"] = {6}
tItem[3006952]["Option6"] = tAllianceBackpackLetter_Text[3006952]["Option6"]

-- 荣耀令说明（10月成就榜）
tItem[3006952]["Text3-1"] = {311,312,313}
tItem[3006952]["Text311"] = tAllianceBackpackLetter_Text[3006952]["311"]
tItem[3006952]["Text312"] = tAllianceBackpackLetter_Text[3006952]["312"]
tItem[3006952]["Text313"] = tAllianceBackpackLetter_Text[3006952]["313"]
tItem[3006952]["tOption3-1"] = {311}
tItem[3006952]["Option311"] = tAllianceBackpackLetter_Text[3006952]["Option311"]
tItem[3006952]["OptionFunc311"]="AllianceBackpackLetter_AutoPath</N>3006952</N>18797"

-- tSystem_PlayLogin_Func = tSystem_PlayLogin_Func or {}
-- table.insert(tSystem_PlayLogin_Func,AllianceBackpackLetter_Backpack)