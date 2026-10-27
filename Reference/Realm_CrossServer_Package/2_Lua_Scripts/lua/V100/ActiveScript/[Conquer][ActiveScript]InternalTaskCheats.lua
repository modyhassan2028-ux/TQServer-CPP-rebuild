------------------------------------------------------------------------------------
--Name:		[征服][活动脚本]内功秘籍任务制作
--Purpose:	内功秘籍任务制作
--Creator: 	郑鋆
--Created:	2015/08/07
------------------------------------------------------------------------------------

-- 命名前缀
-- InternalTaskCheats
-- LOGid	12000185

-- 常量表
local tInternalTaskCheats_Constant = {}
	-- 玩家等级要求
	tInternalTaskCheats_Constant["Metempsychosis"] = 2
	tInternalTaskCheats_Constant["Level"] = 15
	
	tInternalTaskCheats_Constant["Log"] = "0,0,0,0,12000185,2,%d,1"
	tInternalTaskCheats_Constant["TaskId"] = 3460

local tInternalTaskCheats_Stc = {}
	tInternalTaskCheats_Stc["EventType"] = 137
	tInternalTaskCheats_Stc["DataType"] = 46
	tInternalTaskCheats_Stc["MaxData"] = 2		--开放的最高的秘籍

-- stc掩码对应的秘籍
local tInternalTaskCheats_Item = {}
	-- "混元功·上篇"
	tInternalTaskCheats_Item[1] = {}
	tInternalTaskCheats_Item[1]["RewardItemId"] = 3005365
	tInternalTaskCheats_Item[1]["InnerStrengthType"] = 1
	tInternalTaskCheats_Item[1]["RequireType"] = 0
	tInternalTaskCheats_Item[1]["RequireLevel"] = 0
	tInternalTaskCheats_Item[1]["Log"] = "0,0,0,0,12000185,2,3005365,1"
	
	-- "混元功·下篇"		流星*1
	tInternalTaskCheats_Item[2] = {}
	tInternalTaskCheats_Item[2]["RewardItemId"] = 3005366
	tInternalTaskCheats_Item[2]["InnerStrengthType"] = 2
	tInternalTaskCheats_Item[2]["RequireType"] = 1
	tInternalTaskCheats_Item[2]["RequireLevel"] = 5
	tInternalTaskCheats_Item[2]["ReqItemId"] = 1088001
	tInternalTaskCheats_Item[2]["ReqItemNum"] = 1
	tInternalTaskCheats_Item[2]["Log"] = "0,0,1088001,1,12000185,2,3005366,1"
	
	-- "天罡气诀·上篇"		赤练石+1*1
	tInternalTaskCheats_Item[3] = {}
	tInternalTaskCheats_Item[3]["RewardItemId"] = 3005395
	tInternalTaskCheats_Item[3]["InnerStrengthType"] = 3
	tInternalTaskCheats_Item[3]["RequireType"] = 2
	tInternalTaskCheats_Item[3]["RequireLevel"] = 5
	tInternalTaskCheats_Item[3]["ReqItemId"] = 730001
	tInternalTaskCheats_Item[3]["ReqItemNum"] = 1
	tInternalTaskCheats_Item[3]["Log"] = "0,0,730001,1,12000185,2,3005395,1"
	
	-- "天罡气诀·下篇"		赤练石+1*1
	tInternalTaskCheats_Item[4] = {}
	tInternalTaskCheats_Item[4]["RewardItemId"] = 3005396
	tInternalTaskCheats_Item[4]["InnerStrengthType"] = 4
	tInternalTaskCheats_Item[4]["RequireType"] = 3
	tInternalTaskCheats_Item[4]["RequireLevel"] = 5
	tInternalTaskCheats_Item[4]["ReqItemId"] = 730001
	tInternalTaskCheats_Item[4]["ReqItemNum"] = 1
	tInternalTaskCheats_Item[4]["Log"] = "0,0,730001,1,12000185,2,3005396,1"
	
	-- "罗刹决·上篇"		火舞精丹*3
	tInternalTaskCheats_Item[5] = {}
	tInternalTaskCheats_Item[5]["RewardItemId"] = 3007113
	tInternalTaskCheats_Item[5]["InnerStrengthType"] = 5
	tInternalTaskCheats_Item[5]["RequireType"] = 4
	tInternalTaskCheats_Item[5]["RequireLevel"] = 5
	tInternalTaskCheats_Item[5]["ReqItemId"] = 720598
	tInternalTaskCheats_Item[5]["ReqItemNum"] = 3
	tInternalTaskCheats_Item[5]["ReqSpace"] = 1
	tInternalTaskCheats_Item[5]["Log"] = "0,0,720598,3,12000185,2,3007113,1"
	
	-- "罗刹决·下篇"		火舞精丹*3
	tInternalTaskCheats_Item[6] = {}
	tInternalTaskCheats_Item[6]["RewardItemId"] = 3007114
	tInternalTaskCheats_Item[6]["InnerStrengthType"] = 6
	tInternalTaskCheats_Item[6]["RequireType"] = 5
	tInternalTaskCheats_Item[6]["RequireLevel"] = 7
	tInternalTaskCheats_Item[6]["ReqItemId"] = 720598
	tInternalTaskCheats_Item[6]["ReqItemNum"] = 3
	tInternalTaskCheats_Item[6]["ReqSpace"] = 1
	tInternalTaskCheats_Item[6]["Log"] = "0,0,720598,3,12000185,2,3007114,1"
	
	-- "龙象般若功·上篇"	良品玄元宝石*1
	tInternalTaskCheats_Item[7] = {}
	tInternalTaskCheats_Item[7]["RewardItemId"] = 3005397
	tInternalTaskCheats_Item[7]["InnerStrengthType"] = 7
	tInternalTaskCheats_Item[7]["RequireType"] = 6
	tInternalTaskCheats_Item[7]["RequireLevel"] = 7
	tInternalTaskCheats_Item[7]["ReqItemId"] = 700072
	tInternalTaskCheats_Item[7]["ReqItemNum"] = 1
	tInternalTaskCheats_Item[7]["Log"] = "0,0,700072,1,12000185,2,3005397,1"
	
	-- "龙象般若功·下篇"	良品玄元宝石*1
	tInternalTaskCheats_Item[8] = {}
	tInternalTaskCheats_Item[8]["RewardItemId"] = 3005398
	tInternalTaskCheats_Item[8]["InnerStrengthType"] = 8
	tInternalTaskCheats_Item[8]["RequireType"] = 7
	tInternalTaskCheats_Item[8]["RequireLevel"] = 7
	tInternalTaskCheats_Item[8]["ReqItemId"] = 700072
	tInternalTaskCheats_Item[8]["ReqItemNum"] = 1
	tInternalTaskCheats_Item[8]["Log"] = "0,0,700072,1,12000185,2,3005398,1"
	
	-- "无量心经·上篇"		万年寒冰*300
	tInternalTaskCheats_Item[9] = {}
	tInternalTaskCheats_Item[9]["RewardItemId"] = 3007115
	tInternalTaskCheats_Item[9]["InnerStrengthType"] = 9
	tInternalTaskCheats_Item[9]["RequireType"] = 8
	tInternalTaskCheats_Item[9]["RequireLevel"] = 7
	tInternalTaskCheats_Item[9]["ReqItemId"] = 729102
	tInternalTaskCheats_Item[9]["ReqItemNum"] = 300
	tInternalTaskCheats_Item[9]["Log"] = "0,0,729102,300,12000185,2,3007115,1"
	
	-- "无量心经·中篇"		万年寒冰*400
	tInternalTaskCheats_Item[10] = {}
	tInternalTaskCheats_Item[10]["RewardItemId"] = 3007116
	tInternalTaskCheats_Item[10]["InnerStrengthType"] = 10
	tInternalTaskCheats_Item[10]["RequireType"] = 9
	tInternalTaskCheats_Item[10]["RequireLevel"] = 7
	tInternalTaskCheats_Item[10]["ReqItemId"] = 729102
	tInternalTaskCheats_Item[10]["ReqItemNum"] = 400
	tInternalTaskCheats_Item[10]["Log"] = "0,0,729102,400,12000185,2,3007116,1"
	
	-- "无量心经·下篇"		万年寒冰*500
	tInternalTaskCheats_Item[11] = {}
	tInternalTaskCheats_Item[11]["RewardItemId"] = 3007117
	tInternalTaskCheats_Item[11]["InnerStrengthType"] = 11
	tInternalTaskCheats_Item[11]["RequireType"] = 10
	tInternalTaskCheats_Item[11]["RequireLevel"] = 7
	tInternalTaskCheats_Item[11]["ReqItemId"] = 729102
	tInternalTaskCheats_Item[11]["ReqItemNum"] = 500
	tInternalTaskCheats_Item[11]["Log"] = "0,0,729102,500,12000185,2,3007117,1"
	
	-- "太乙神功·上篇"		流星卷*7
	tInternalTaskCheats_Item[12] = {}
	tInternalTaskCheats_Item[12]["RewardItemId"] = 3005399
	tInternalTaskCheats_Item[12]["InnerStrengthType"] = 12
	tInternalTaskCheats_Item[12]["RequireType"] = 11
	tInternalTaskCheats_Item[12]["RequireLevel"] = 7
	tInternalTaskCheats_Item[12]["ReqItemId"] = 720027
	tInternalTaskCheats_Item[12]["ReqItemNum"] = 7
	tInternalTaskCheats_Item[12]["Log"] = "0,0,720027,7,12000185,2,3005399,1"
	
	-- "太乙神功·中篇"		流星卷*8
	tInternalTaskCheats_Item[13] = {}
	tInternalTaskCheats_Item[13]["RewardItemId"] = 3005400
	tInternalTaskCheats_Item[13]["InnerStrengthType"] = 13
	tInternalTaskCheats_Item[13]["RequireType"] = 12
	tInternalTaskCheats_Item[13]["RequireLevel"] = 7
	tInternalTaskCheats_Item[13]["ReqItemId"] = 720027
	tInternalTaskCheats_Item[13]["ReqItemNum"] = 8
	tInternalTaskCheats_Item[13]["Log"] = "0,0,720027,8,12000185,2,3005400,1"
	
	-- "太乙神功·下篇"		流星卷*9
	tInternalTaskCheats_Item[14] = {}
	tInternalTaskCheats_Item[14]["RewardItemId"] = 3005401
	tInternalTaskCheats_Item[14]["InnerStrengthType"] = 14
	tInternalTaskCheats_Item[14]["RequireType"] = 13
	tInternalTaskCheats_Item[14]["RequireLevel"] = 7
	tInternalTaskCheats_Item[14]["ReqItemId"] = 720027
	tInternalTaskCheats_Item[14]["ReqItemNum"] = 9
	tInternalTaskCheats_Item[14]["Log"] = "0,0,720027,9,12000185,2,3005401,1"
	
	-- "枯荣禅功·上篇"		涅槃灵石*3
	tInternalTaskCheats_Item[15] = {}
	tInternalTaskCheats_Item[15]["RewardItemId"] = 3007230
	tInternalTaskCheats_Item[15]["InnerStrengthType"] = 15
	tInternalTaskCheats_Item[15]["RequireType"] = 14
	tInternalTaskCheats_Item[15]["RequireLevel"] = 7
	tInternalTaskCheats_Item[15]["ReqItemId"] = 721259
	tInternalTaskCheats_Item[15]["ReqItemNum"] = 3
	tInternalTaskCheats_Item[15]["ReqSpace"] = 1
	tInternalTaskCheats_Item[15]["Log"] = "0,0,721259,3,12000185,2,3007230,1"
	
	-- "枯荣禅功·中篇"		涅槃灵石*4
	tInternalTaskCheats_Item[16] = {}
	tInternalTaskCheats_Item[16]["RewardItemId"] = 3007231
	tInternalTaskCheats_Item[16]["InnerStrengthType"] = 16
	tInternalTaskCheats_Item[16]["RequireType"] = 15
	tInternalTaskCheats_Item[16]["RequireLevel"] = 7
	tInternalTaskCheats_Item[16]["ReqItemId"] = 721259
	tInternalTaskCheats_Item[16]["ReqItemNum"] = 4
	tInternalTaskCheats_Item[16]["ReqSpace"] = 1
	tInternalTaskCheats_Item[16]["Log"] = "0,0,721259,4,12000185,2,3007231,1"
	
	-- "枯荣禅功·下篇"		涅槃灵石*5
	tInternalTaskCheats_Item[17] = {}
	tInternalTaskCheats_Item[17]["RewardItemId"] = 3007232
	tInternalTaskCheats_Item[17]["InnerStrengthType"] = 17
	tInternalTaskCheats_Item[17]["RequireType"] = 16
	tInternalTaskCheats_Item[17]["RequireLevel"] = 7
	tInternalTaskCheats_Item[17]["ReqItemId"] = 721259
	tInternalTaskCheats_Item[17]["ReqItemNum"] = 5
	tInternalTaskCheats_Item[17]["ReqSpace"] = 1
	tInternalTaskCheats_Item[17]["Log"] = "0,0,721259,5,12000185,2,3007232,1"

--------------------------------------逻辑部分-------------------------------------------
-- 第一次免费给秘籍
function InternalTaskCheats_GiveFree(nNpcId)
	-- 判断玩家等级
	if not User_JudgeLevelAndMetempsychosis(tInternalTaskCheats_Constant["Level"],tInternalTaskCheats_Constant["Metempsychosis"]) then
		LinkNpcGossipFunc_New(nNpcId,"1-1")
		return
	end

	if Task_ChkStcValue(tInternalTaskCheats_Stc["EventType"],tInternalTaskCheats_Stc["DataType"],">",0) then
		return
	end

	-- 判断背包空间
	if not User_CheckLeftSpace(1) then
		LinkNpcGossipFunc_New(nNpcId,"2-3")
		return
	end

	-- 设掩码值
	Task_SetStatistic(tInternalTaskCheats_Stc["EventType"],tInternalTaskCheats_Stc["DataType"],1,1)
	
	-- 完成任务
	local nTaskId = tInternalTaskCheats_Constant["TaskId"]
	
	if not Task_ChkTaskDetail(nTaskId) then
		if Task_AddTaskDetail(nTaskId) then
			Task_SetTaskDetailCompleteFlag(nTaskId,1)
		end
	end
	
	InternalTaskCheats_RewardItem()
end

-- 给秘籍的接口
function InternalTaskCheats_RewardItem(sLog)
	local nEvent = tInternalTaskCheats_Stc["EventType"]
	local nType = tInternalTaskCheats_Stc["DataType"]
	local nData = Get_UserStatisticValue(nEvent,nType)
	
	-- 判断该掩码值是否有配置相应的数据
	if tInternalTaskCheats_Item[nData] == nil then
		return
	end
	
	local nItemId = tInternalTaskCheats_Item[nData]["RewardItemId"]
	
	-- 判断身上是否有该物品
	if Item_ChkItem(nItemId) then
		return
	end
	
	-- 判断是否学习过该物品对应的内功
	if User_IsLearnInnerStrengthType(tInternalTaskCheats_Item[nData]["InnerStrengthType"]) then
		return
	end
	
	-- 给物品
	Item_AddItem(nItemId)
	
	-- 打log
	sLog = sLog or tInternalTaskCheats_Item[nData]["Log"]
	Sys_SaveActionFestivalLog(sLog)
	
	User_EffectAdd("self","zf2-e300")
	
	-- 给提示
	local sItemName = Get_ItemtypeName(nItemId)
	User_TalkChannel2005(string.format(tInternalTaskCheats_Text["RewardItem"],sItemName))
end

-- 补领秘籍
function InternalTaskCheats_Replacement(nNpcId)
	local nEvent = tInternalTaskCheats_Stc["EventType"]
	local nType = tInternalTaskCheats_Stc["DataType"]
	local nData = Get_UserStatisticValue(nEvent,nType)
	
	-- 判断该掩码值是否有配置相应的数据
	if tInternalTaskCheats_Item[nData] == nil then
		return
	end
	
	local nItemId = tInternalTaskCheats_Item[nData]["RewardItemId"]
	
	-- 判断身上是否有该物品
	if Item_ChkItem(nItemId) then
		LinkNpcGossipFunc_New(nNpcId,"4-2")
		return
	end
	
	-- 判断背包空间
	if not User_CheckLeftSpace(1) then
		LinkNpcGossipFunc_New(nNpcId,"4-3")
		return
	end
	
	local sLog = string.format(tInternalTaskCheats_Constant["Log"],nItemId)
	InternalTaskCheats_RewardItem(sLog)
end

-- 领取下一本秘籍
function InternalTaskCheats_Reward(nNpcId)
	local nEvent = tInternalTaskCheats_Stc["EventType"]
	local nType = tInternalTaskCheats_Stc["DataType"]

	-- 判断是否还有领取的秘籍
	if Task_ChkStcValue(nEvent,nType,">=",tInternalTaskCheats_Stc["MaxData"]) then
		LinkNpcGossipFunc_New(nNpcId,"3-2")
		return
	end

	local nData = Get_UserStatisticValue(nEvent,nType) + 1
	-- 判断该掩码值是否有配置相应的数据
	if tInternalTaskCheats_Item[nData] == nil then
		return
	end
	
	-- 判断前置内功是否满足
	if tInternalTaskCheats_Item[nData]["RequireType"] > 0 then
		local nRequireType = tInternalTaskCheats_Item[nData]["RequireType"]
		
		if not User_IsLearnInnerStrengthType(nRequireType) then
			LinkNpcGossipFunc_New(nNpcId,"3-1")
			return
		end

		local nRequireLevel = Get_InnerStrengthLevByType(nRequireType)

		if nRequireLevel < tInternalTaskCheats_Item[nData]["RequireLevel"] then
			LinkNpcGossipFunc_New(nNpcId,"3-1")
			return
		end
	end

	LinkNpcGossipFunc_New(nNpcId,"3-3")
end

-- 上交材料，领取秘籍
function InternalTaskCheats_UpperMaterial(nNpcId)
	local nEvent = tInternalTaskCheats_Stc["EventType"]
	local nType = tInternalTaskCheats_Stc["DataType"]
	local nData = Get_UserStatisticValue(nEvent,nType) + 1
	
	-- 判断该掩码值是否有配置相应的数据
	if tInternalTaskCheats_Item[nData] == nil then
		return
	end
	
	local nReqItemId = tInternalTaskCheats_Item[nData]["ReqItemId"]
	local nReqItemNum = tInternalTaskCheats_Item[nData]["ReqItemNum"]
	
	-- 判断材料是否满足
	if not Item_ChkMulItem(nReqItemId,nReqItemId,nReqItemNum,1) then
		LinkNpcGossipFunc_New(nNpcId,"3-5")
		return
	end
	
	-- 判断背包空间
	local nSpace = tInternalTaskCheats_Item[nData]["ReqSpace"]
	if nSpace ~= nil and (not User_CheckLeftSpace(nSpace)) then
		LinkNpcGossipFunc_New(nNpcId,"3-4")
		return
	end
	
	-- 删除材料
	if not Item_DelMulItem(nReqItemId,nReqItemId,nReqItemNum,1) then
		return
	end
	
	-- 设置掩码值
	Task_AddStatistic(nEvent,nType,1,1)

	InternalTaskCheats_RewardItem()
	LinkNpcGossipFunc_New(nNpcId,"3-6")
end

-- 背包信使用
function InternalTaskCheats_UseItem(nItemId)
	if Item_ChkItem(nItemId) and Item_DelItem(nItemId) then
		-- 给经验或者修行值
		local nLevel = Get_UserLevel()
		
		if nLevel >= G_User_MaxLev then
			User_AddCultivation(15)
			User_TalkChannel2005(tInternalTaskCheats_Text[nItemId]["Cultivation"])
		else
			User_AddExpTime(30)
			User_TalkChannel2005(tInternalTaskCheats_Text[nItemId]["ExpTime"])
		end
		
		Sys_GotoSomeWhere(178,209,1036,18786)
	end
end

-- 玩家内功转换
function InternalTaskCheats_Change(nUserId,nChangeUserId)

	local nUserNum = Get_UserStatisticValue(tInternalTaskCheats_Stc["EventType"],tInternalTaskCheats_Stc["DataType"],nUserId)
	local nChangeUserNum = Get_UserStatisticValue(tInternalTaskCheats_Stc["EventType"],tInternalTaskCheats_Stc["DataType"],nChangeUserId)

	Task_SetStatistic(tInternalTaskCheats_Stc["EventType"],tInternalTaskCheats_Stc["DataType"],nChangeUserNum,1,nUserId)
	Task_SetStatistic(tInternalTaskCheats_Stc["EventType"],tInternalTaskCheats_Stc["DataType"],nUserNum,1,nChangeUserId)
end

--------------------------------------NPC模块-------------------------------------------
-- 神机老人
tNpcFace[3781] = 6
tNpcGossip[18786] = tNpcGossip[18786] or DefaultNpc:new{}
tNpcGossip[18786]["OptionHidden"] = 1

-- 【玩家等级不足，无法接受任务】
tNpcGossip[18786]["Text1-1"] = {111,112}
tNpcGossip[18786]["Text111"] = tInternalTaskCheats_Text[18786]["111"]
tNpcGossip[18786]["Text112"] = tInternalTaskCheats_Text[18786]["112"]
tNpcGossip[18786]["tOption1-1"] = {1}
tNpcGossip[18786]["ChkFunc1-1"] = function ()
	return not User_JudgeLevelAndMetempsychosis(tInternalTaskCheats_Constant["Level"],tInternalTaskCheats_Constant["Metempsychosis"])
end	

tNpcGossip[18786]["Option1"] = tInternalTaskCheats_Text[18786]["Option1"]

-- 第一次对白（脚本注意：领取秘籍后不再显示）
tNpcGossip[18786]["Text1-2"] = {121}
tNpcGossip[18786]["Text121"] = tInternalTaskCheats_Text[18786]["121"]
tNpcGossip[18786]["tOption1-2"] = {2,3}
tNpcGossip[18786]["ChkFunc1-2"] = function ()
	return Task_ChkStcValue(tInternalTaskCheats_Stc["EventType"],tInternalTaskCheats_Stc["DataType"],"==",0)
end	
tNpcGossip[18786]["Option2"] = tInternalTaskCheats_Text[18786]["Option2"]
tNpcGossip[18786]["OptionPoint2"]="2-1"
tNpcGossip[18786]["Option3"] = tInternalTaskCheats_Text[18786]["Option3"]

-- 【领取秘籍后对白】
tNpcGossip[18786]["Text1-3"] = {131}
tNpcGossip[18786]["Text131"] = tInternalTaskCheats_Text[18786]["131"]
tNpcGossip[18786]["tOption1-3"] = {7,8,9}
tNpcGossip[18786]["Option7"] = tInternalTaskCheats_Text[18786]["Option7"]
tNpcGossip[18786]["OptionFunc7"]="InternalTaskCheats_Reward</N>18786"
tNpcGossip[18786]["Option8"] = tInternalTaskCheats_Text[18786]["Option8"]
tNpcGossip[18786]["OptionPoint8"]="4-1"
tNpcGossip[18786]["OptionChkFunc8"] = function ()
	local nEvent = tInternalTaskCheats_Stc["EventType"]
	local nType = tInternalTaskCheats_Stc["DataType"]
	local nData = Get_UserStatisticValue(nEvent,nType)
	
	if tInternalTaskCheats_Item[nData] == nil then
		return false
	end

	return not User_IsLearnInnerStrengthType(tInternalTaskCheats_Item[nData]["InnerStrengthType"])
end

tNpcGossip[18786]["Option9"] = tInternalTaskCheats_Text[18786]["Option9"]

-- 【玩家选1，了解内功修炼法门】（脚本注意：领取秘籍后不再显示）
tNpcGossip[18786]["Text2-1"] = {211,212}
tNpcGossip[18786]["Text211"] = tInternalTaskCheats_Text[18786]["211"]
tNpcGossip[18786]["Text212"] = tInternalTaskCheats_Text[18786]["212"]
tNpcGossip[18786]["tOption2-1"] = {4}
tNpcGossip[18786]["Option4"] = tInternalTaskCheats_Text[18786]["Option4"]
tNpcGossip[18786]["OptionPoint4"]="2-2"

-- 【玩家选1.1，了解如何获取内功秘籍】（脚本注意：领取秘籍后不再显示）
tNpcGossip[18786]["Text2-2"] = {221,222}
tNpcGossip[18786]["Text221"] = tInternalTaskCheats_Text[18786]["221"]
tNpcGossip[18786]["Text222"] = tInternalTaskCheats_Text[18786]["222"]
tNpcGossip[18786]["tOption2-2"] = {5}
tNpcGossip[18786]["Option5"] = tInternalTaskCheats_Text[18786]["Option5"]
tNpcGossip[18786]["OptionFunc5"]="InternalTaskCheats_GiveFree</N>18786"

-- 【玩家选1.1.1，失败，背包空间不足】
tNpcGossip[18786]["Text2-3"] = {231}
tNpcGossip[18786]["Text231"] = tInternalTaskCheats_Text[18786]["231"]
tNpcGossip[18786]["tOption2-3"] = {6}
tNpcGossip[18786]["Option6"] = tInternalTaskCheats_Text[18786]["Option6"]

-- 玩家选1，失败，上一本秘籍还未圆功
tNpcGossip[18786]["Text3-1"] = {311,312}
tNpcGossip[18786]["Text311"] = tInternalTaskCheats_Text[18786]["311"]
tNpcGossip[18786]["Text312"] = tInternalTaskCheats_Text[18786]["312"]
tNpcGossip[18786]["tOption3-1"] = {10}
tNpcGossip[18786]["Option10"] = tInternalTaskCheats_Text[18786]["Option10"]
tNpcGossip[18786]["ChkFunc3-1"] = function ()
	local nEvent = tInternalTaskCheats_Stc["EventType"]
	local nType = tInternalTaskCheats_Stc["DataType"]
	local nData = Get_UserStatisticValue(nEvent,nType)
	local nInnerStrengthType = tInternalTaskCheats_Item[nData]["InnerStrengthType"]
	
	tNpcGossip[18786]["Text311"] = string.format(tInternalTaskCheats_Text[18786]["311"],tInternalSystem_InnerName[nInnerStrengthType])
	return true
end

-- 玩家选1，失败，暂时没有更多的秘籍了
tNpcGossip[18786]["Text3-2"] = {321,322}
tNpcGossip[18786]["Text321"] = tInternalTaskCheats_Text[18786]["321"]
tNpcGossip[18786]["Text322"] = tInternalTaskCheats_Text[18786]["322"]
tNpcGossip[18786]["tOption3-2"] = {11}
tNpcGossip[18786]["Option11"] = tInternalTaskCheats_Text[18786]["Option11"]

-- 玩家选1，成功，提示领取秘籍所需的材料
tNpcGossip[18786]["Text3-3"] = {331,332}
tNpcGossip[18786]["Text331"] = tInternalTaskCheats_Text[18786]["331"]
tNpcGossip[18786]["Text332"] = tInternalTaskCheats_Text[18786]["332"]
tNpcGossip[18786]["tOption3-3"] = {12,13}
tNpcGossip[18786]["Option12"] = tInternalTaskCheats_Text[18786]["Option12"]
tNpcGossip[18786]["OptionFunc12"]="InternalTaskCheats_UpperMaterial</N>18786"
tNpcGossip[18786]["Option13"] = tInternalTaskCheats_Text[18786]["Option13"]
tNpcGossip[18786]["ChkFunc3-3"] = function ()
	local nEvent = tInternalTaskCheats_Stc["EventType"]
	local nType = tInternalTaskCheats_Stc["DataType"]
	local nData = Get_UserStatisticValue(nEvent,nType) + 1
	local nItemId = tInternalTaskCheats_Item[nData]["RewardItemId"]
	local sItemName = Get_ItemtypeName(nItemId)
	local sDemand = tInternalTaskCheats_Text["Demand"][nData]
	
	tNpcGossip[18786]["Text331"] = string.format(tInternalTaskCheats_Text[18786]["331"],sItemName,sDemand)
	return true
end

-- 玩家选1.1，失败，背包空间不足
tNpcGossip[18786]["Text3-4"] = {341}
tNpcGossip[18786]["Text341"] = tInternalTaskCheats_Text[18786]["341"]
tNpcGossip[18786]["tOption3-4"] = {14}
tNpcGossip[18786]["Option14"] = tInternalTaskCheats_Text[18786]["Option14"]

-- 玩家选1.1，失败，材料不足
tNpcGossip[18786]["Text3-5"] = {351,352}
tNpcGossip[18786]["Text351"] = tInternalTaskCheats_Text[18786]["351"]
tNpcGossip[18786]["Text352"] = tInternalTaskCheats_Text[18786]["352"]
tNpcGossip[18786]["tOption3-5"] = {15}
tNpcGossip[18786]["Option15"] = tInternalTaskCheats_Text[18786]["Option15"]

-- 玩家选1.1，成功，获得秘籍
tNpcGossip[18786]["Text3-6"] = {361}
tNpcGossip[18786]["Text361"] = tInternalTaskCheats_Text[18786]["361"]
tNpcGossip[18786]["tOption3-6"] = {16}
tNpcGossip[18786]["Option16"] = tInternalTaskCheats_Text[18786]["Option16"]
tNpcGossip[18786]["ChkFunc3-6"] = function ()
	local nEvent = tInternalTaskCheats_Stc["EventType"]
	local nType = tInternalTaskCheats_Stc["DataType"]
	local nData = Get_UserStatisticValue(nEvent,nType)
	local nItemId = tInternalTaskCheats_Item[nData]["RewardItemId"]
	local sItemName = Get_ItemtypeName(nItemId)
	
	tNpcGossip[18786]["Text361"] = string.format(tInternalTaskCheats_Text[18786]["361"],sItemName)
	return true
end	

-- 玩家选2，补领秘籍
tNpcGossip[18786]["Text4-1"] = {411}
tNpcGossip[18786]["Text411"] = tInternalTaskCheats_Text[18786]["411"]
tNpcGossip[18786]["tOption4-1"] = {17}
tNpcGossip[18786]["Option17"] = tInternalTaskCheats_Text[18786]["Option17"]
tNpcGossip[18786]["OptionFunc17"]="InternalTaskCheats_Replacement</N>18786"

-- 玩家选2.1，失败，已有该秘籍
tNpcGossip[18786]["Text4-2"] = {421}
tNpcGossip[18786]["Text421"] = tInternalTaskCheats_Text[18786]["421"]
tNpcGossip[18786]["tOption4-2"] = {18}
tNpcGossip[18786]["Option18"] = tInternalTaskCheats_Text[18786]["Option18"]
tNpcGossip[18786]["ChkFunc4-2"] = function ()
	local nEvent = tInternalTaskCheats_Stc["EventType"]
	local nType = tInternalTaskCheats_Stc["DataType"]
	local nData = Get_UserStatisticValue(nEvent,nType)
	local nItemId = tInternalTaskCheats_Item[nData]["RewardItemId"]
	local sItemName = Get_ItemtypeName(nItemId)
	
	tNpcGossip[18786]["Text421"] = string.format(tInternalTaskCheats_Text[18786]["421"],sItemName)
	return true
end	
	
-- 玩家选2.1，失败，背包空间不足
tNpcGossip[18786]["Text4-3"] = {431}
tNpcGossip[18786]["Text431"] = tInternalTaskCheats_Text[18786]["431"]
tNpcGossip[18786]["tOption4-3"] = {19}
tNpcGossip[18786]["Option19"] = tInternalTaskCheats_Text[18786]["Option19"]

--------------------------------------物品配置-------------------------------------------
tItem[3007294] = tItem[3007294] or {}
tItem[3007294]["Text1-1"] = {111,112}
tItem[3007294]["Text111"] = tInternalTaskCheats_Text[3007294]["111"]
tItem[3007294]["Text112"] = tInternalTaskCheats_Text[3007294]["112"]
tItem[3007294]["tOption1-1"] = {1}
tItem[3007294]["Option1"] = tInternalTaskCheats_Text[3007294]["Option1"]
tItem[3007294]["OptionFunc1"]="InternalTaskCheats_UseItem</N>3007294"


---- 玩家内功转换
tStrengthExchange["tFunction"] = tStrengthExchange["tFunction"] or {}
table.insert(tStrengthExchange["tFunction"],InternalTaskCheats_Change)