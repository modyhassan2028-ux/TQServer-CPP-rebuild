-----------------------------------------------------------------------------------------------------
--Name:			150803[简体征服][活动脚本]万圣节之南瓜大战僵尸(10.29-11.04)
--Purpose:		万圣节之南瓜大战僵尸
--Creator: 		许乐
--Created:		2015/08/03
------------------------------------------------------------------------------------------------------
-- 命名前缀
--Halloween2015_PumpkinVSZombie_

------------------------------------------------------------------------------------------------------
-- 【简体征服】万圣节（10.29-11.4）
-- 复用去年
-- 脚本提交：8.11
-- 注意节日气氛的渲染，以及需要针对去年不足的部分进行优化。
-- 活动时间：10.29-11.4

-- 万圣节之南瓜大战僵尸
-- 任务参与的时间：2014年10月27日至11月3日
-- 参与任务的要求与次数：80级以上或者已转世的玩家，1天完成一次

-- 1.活动期间，玩家在南瓜园园丁大叔处进行接取任务，
-- 进入地图后，会获得一个百宝盒，
-- 百宝盒打开获得5种道具，其中三种可以对僵尸产生伤害，另外两种给提示。
-- 2.当玩家使用道具成功杀死三个僵尸后，给领取奖励的提示，玩家进行领取奖励，
-----------------------------------------------------------------------------------------------------------
-- mapid:				3872
-- npcId:				17144-17145
-- npctype:			3194-3195
-- itemtype:		3007244-3007250
-- monstertype:	7618
-- stc:					12939  12941  12942
-- lua.ini				40087
-- logID:				12000175
--FestivalId: 		3456

-- 掩码说明          
-- stc掩码：
-- stc(129,39)   ==0表示未接受任务，==1表示接受了任务，==2表示完成任务
-- stc(129,41)   表示杀死僵尸（吸血鬼）的数量

-----------------------------------------常量表配置-----------------------------------------------
local tHalloween2015_PumpkinVSZombie_Cont = {}
	--节日活动时间
	tHalloween2015_PumpkinVSZombie_Cont["BeforeActivityTime"] = "2014-10-01 00:00 2015-10-28 23:59"
	tHalloween2015_PumpkinVSZombie_Cont["ActivityTime"] = "2015-10-29 00:00 2015-11-04 23:59"

	--玩家等级要求
	tHalloween2015_PumpkinVSZombie_Cont["Metempsychosis"] = 0
	tHalloween2015_PumpkinVSZombie_Cont["Level"] = 80
	
	tHalloween2015_PumpkinVSZombie_Cont["BagSpace_1"] = 1
	tHalloween2015_PumpkinVSZombie_Cont["BagSpace_2"] = 4

--NPC坐标
local tHalloween2015_PumpkinVSZombie_Npc = {}
	-- 17144 南瓜园园丁大叔
	tHalloween2015_PumpkinVSZombie_Npc[17144] = {}
	tHalloween2015_PumpkinVSZombie_Npc[17144]["CellX"] = 297
	tHalloween2015_PumpkinVSZombie_Npc[17144]["CellY"] = 360
	tHalloween2015_PumpkinVSZombie_Npc[17144]["Mapid"] = 1002
	tHalloween2015_PumpkinVSZombie_Npc[17144]["NpcId"] = 17144

	-- 17145 南瓜宝宝
	tHalloween2015_PumpkinVSZombie_Npc[17145] = {}
	tHalloween2015_PumpkinVSZombie_Npc[17145]["CellX"] =75
	tHalloween2015_PumpkinVSZombie_Npc[17145]["CellY"] = 55
	tHalloween2015_PumpkinVSZombie_Npc[17145]["Mapid"] =3872 
	tHalloween2015_PumpkinVSZombie_Npc[17145]["NpcId"] = 17145

	tHalloween2015_PumpkinVSZombie_Npc["BoundCX"] = 5
	tHalloween2015_PumpkinVSZombie_Npc["BoundCY"] = 5
	
--掩码
local tHalloween2015_PumpkinVSZombie_Stc = {}
	-- stc(129,39)   ==0表示未接受任务，==1表示接受了任务，==2表示完成任务
	tHalloween2015_PumpkinVSZombie_Stc[1] = {}
	tHalloween2015_PumpkinVSZombie_Stc[1]["EventType"] = 129
	tHalloween2015_PumpkinVSZombie_Stc[1]["DataType"] = 39
	tHalloween2015_PumpkinVSZombie_Stc[1]["GetTask"] = 1
	tHalloween2015_PumpkinVSZombie_Stc[1]["Complete"] = 2
	
	-- stc(129,41)   表示杀死僵尸（吸血鬼）的数量
	tHalloween2015_PumpkinVSZombie_Stc[2] = {}
	tHalloween2015_PumpkinVSZombie_Stc[2]["EventType"] = 129
	tHalloween2015_PumpkinVSZombie_Stc[2]["DataType"] = 41
	tHalloween2015_PumpkinVSZombie_Stc[2]["Complete"] = 3

	--物品
local tHalloween2015_PumpkinVSZombie_Item = {}	
	tHalloween2015_PumpkinVSZombie_Item["Item"] = {}
	--百宝盒
	tHalloween2015_PumpkinVSZombie_Item["Item"][1] = 3007244
	--食人花
	tHalloween2015_PumpkinVSZombie_Item["Item"][2] = 3007246
	--大南瓜
	tHalloween2015_PumpkinVSZombie_Item["Item"][3] = 3007247
	--红辣椒
	tHalloween2015_PumpkinVSZombie_Item["Item"][4] = 3007248
	--郁金香
	tHalloween2015_PumpkinVSZombie_Item["Item"][5] = 3007249
	--万圣节糖果
	tHalloween2015_PumpkinVSZombie_Item["Item"][6] = 3007250
	
--获得礼包的特效
local tHalloween2015_PumpkinVSZombie_Effect = {}
	tHalloween2015_PumpkinVSZombie_Effect[1] = "self"
	tHalloween2015_PumpkinVSZombie_Effect[2] = "angelwing"
	tHalloween2015_PumpkinVSZombie_Effect[3] = "angelwing6" --成功消灭僵尸光效
	
--LOG
local tHalloween2015_PumpkinVSZombie_Log = {}
	tHalloween2015_PumpkinVSZombie_Log["GetBigBox"] = "0,0,0,0,12000175,2,3007244,1"
	tHalloween2015_PumpkinVSZombie_Log["OpenBigBox"] = "0,0,3007244,1,12000175,2,3007246[3007247][3007248][3007249][3007250],1[1][1][1][1]"
	tHalloween2015_PumpkinVSZombie_Log["DelItem"] = "0,0,%s,1,12000175,2,0,0"
	tHalloween2015_PumpkinVSZombie_Log["UseItem"] = "0,0,%s,1,12000175,2,0,0"
	tHalloween2015_PumpkinVSZombie_Log["FinishTask"] = "0,0,0,0,12000175,3,0,2"
	tHalloween2015_PumpkinVSZombie_Log["FestivalId"] = 3456
	tHalloween2015_PumpkinVSZombie_Log["LogId"] = 12000175

------------------------------------------------逻辑部分-------------------------------------------------
--统一判断掩码 
-- stc(129,39)   ==0表示未接受任务，==1表示接受了任务，==2表示完成任务 nStcNum = 1
-- stc(129,41)   表示杀死僵尸（吸血鬼）的数量 	nStcNum = 2
function Halloween2015_PumpkinVSZombie_ChkStcComplete(nStcNum)
	local nEvent = tHalloween2015_PumpkinVSZombie_Stc[nStcNum]["EventType"]
	local nType = tHalloween2015_PumpkinVSZombie_Stc[nStcNum]["DataType"]
	local nComplete = tHalloween2015_PumpkinVSZombie_Stc[nStcNum]["Complete"]

	if Task_ChkStcValue(nEvent,nType,">=",nComplete) then
		-- 判断是否隔天
		if Task_StcInterval(nEvent,nType,1,4) then
			Task_SetStatistic(nEvent,nType,0,1,0)
			Task_SetStcTimestamp(nEvent,nType,0,0)	
			return false
		else
			return true
		end
	else
		return false
	end
end

--传送地图逻辑
function Halloween2015_PumpkinVSZombie_ChgMap(nNpcId)
	local nMapId = tHalloween2015_PumpkinVSZombie_Npc[nNpcId]["Mapid"]
	local nBoundX = tHalloween2015_PumpkinVSZombie_Npc[nNpcId]["CellX"]
	local nBoundY = tHalloween2015_PumpkinVSZombie_Npc[nNpcId]["CellY"]
	local nBoundCX = tHalloween2015_PumpkinVSZombie_Npc["BoundCX"]
	local nBoundCY = tHalloween2015_PumpkinVSZombie_Npc["BoundCY"]
	User_UserRandBoundTrans(nMapId,nBoundX,nBoundY,nBoundCX,nBoundCY,0,0)
end

--接Option2：我要大战僵尸！
function Halloween2015_PumpkinVSZombie_VSZombies(nNpcId)
	-- 判断活动时间
	if not Sys_ChkFullTime(tHalloween2015_PumpkinVSZombie_Cont["ActivityTime"]) then
		--不在活动时间，活动后
		LinkNpcGossipFunc_New(nNpcId,"1-3")
		return
	end
	
	-- 判断玩家等级
	local nLevel = tHalloween2015_PumpkinVSZombie_Cont["Level"]
	local nMete = tHalloween2015_PumpkinVSZombie_Cont["Metempsychosis"]
	if not User_JudgeLevelAndMetempsychosis(nLevel,nMete) then
		LinkNpcGossipFunc_New(nNpcId,"2-1")
		return
	end
	
	--判断是否完成任务 stc(129,39) == 2
	if Halloween2015_PumpkinVSZombie_ChkStcComplete(1) then
		LinkNpcGossipFunc_New(nNpcId,"2-2")
		return
	end
	
	local nEvent = tHalloween2015_PumpkinVSZombie_Stc[1]["EventType"]
	local nType = tHalloween2015_PumpkinVSZombie_Stc[1]["DataType"]
	local nData = tHalloween2015_PumpkinVSZombie_Stc[1]["GetTask"]
	
	--stc(129,39) == 1 接了任务
	if Task_ChkStcValue(nEvent,nType,"==",nData) then
		--stc(129,41) == 3 杀满3只僵尸
		if Halloween2015_PumpkinVSZombie_ChkStcComplete(2) then
			LinkNpcGossipFunc_New(nNpcId,"2-3")
			return 
		end
	end

	-- 判断背包空间
	if not User_CheckLeftSpace(tHalloween2015_PumpkinVSZombie_Cont["BagSpace_1"]) then
		LinkNpcGossipFunc_New(nNpcId,"2-4")
		return
	end
	
	-- 检查是否有任务物品，删除
	local nId = {}
	local nCounter = 0
	for _,v in pairs(tHalloween2015_PumpkinVSZombie_Item["Item"]) do
		if Item_ChkItem(v) then
			nCounter = nCounter + 1
			table.insert(nId,v)
		end
	end
	if nCounter ~= 0 then
		for _,k in pairs(nId) do
			Item_DelAllItemByType(k)
		end
	end

	--设置掩码,接受任务
	Task_SetStatistic(nEvent,nType,nData,1,0)

	--给百宝盒，打log
	local nItemId = tHalloween2015_PumpkinVSZombie_Item["Item"][1]
	Item_AddItem(nItemId)
	Sys_SaveActionFestivalLog(tHalloween2015_PumpkinVSZombie_Log["GetBigBox"])	
	LinkNpcGossipFunc_New(nNpcId,"2-5")
end

--没问题
function Halloween2015_PumpkinVSZombie_SendInMap(nNpcId)
	Halloween2015_PumpkinVSZombie_ChgMap(tHalloween2015_PumpkinVSZombie_Npc[17145]["NpcId"])
	User_EffectAdd(tHalloween2015_PumpkinVSZombie_Effect[1],tHalloween2015_PumpkinVSZombie_Effect[3])
	Sys_MsgBox(tHalloween2015_PumpkinVSZombie_Text["UseBox"])
end

--接Option3：领取战胜僵尸的奖励
function Halloween2015_PumpkinVSZombie_GetReward(nNpcId)
	-- 判断活动时间
	if not Sys_ChkFullTime(tHalloween2015_PumpkinVSZombie_Cont["ActivityTime"]) then
		--不在活动时间，活动后
		LinkNpcGossipFunc_New(nNpcId,"1-3")
		return
	end
	
	-- 判断玩家等级
	local nLevel = tHalloween2015_PumpkinVSZombie_Cont["Level"]
	local nMete = tHalloween2015_PumpkinVSZombie_Cont["Metempsychosis"]
	if not User_JudgeLevelAndMetempsychosis(nLevel,nMete) then
		LinkNpcGossipFunc_New(nNpcId,"3-1")
		return
	end
	
	local nEvent1 = tHalloween2015_PumpkinVSZombie_Stc[1]["EventType"]
	local nType1 = tHalloween2015_PumpkinVSZombie_Stc[1]["DataType"]
	local nData1 = tHalloween2015_PumpkinVSZombie_Stc[1]["GetTask"]
	local nComplete1 = tHalloween2015_PumpkinVSZombie_Stc[1]["Complete"]
	
	local nEvent2 = tHalloween2015_PumpkinVSZombie_Stc[2]["EventType"]
	local nType2 = tHalloween2015_PumpkinVSZombie_Stc[2]["DataType"]
	local nComplete2 = tHalloween2015_PumpkinVSZombie_Stc[2]["Complete"]
	
	--stc(129,39) == 0 未接任务
	if Task_ChkStcValue(nEvent1,nType1,"==",0) then
		LinkNpcGossipFunc_New(nNpcId,"3-2")
		return
	end
	
	--stc(129,39) == 2  完成任务
	if Halloween2015_PumpkinVSZombie_ChkStcComplete(1) then
		LinkNpcGossipFunc_New(nNpcId,"3-3")
		return
	end
	
	--stc(129,39) == 1 接了任务
	if Task_ChkStcValue(nEvent1,nType1,"==",nData1) then
		--stc(129,41) < 3 僵尸数不足
		if Task_ChkStcValue(nEvent2,nType2,"<",nComplete2) then
			LinkNpcGossipFunc_New(nNpcId,"3-4")
			return
		end		
		--stc(129,41) == 3 杀满3只僵尸
		if Halloween2015_PumpkinVSZombie_ChkStcComplete(2) then
			-- 判断背包空间
			if not User_CheckLeftSpace(tHalloween2015_PumpkinVSZombie_Cont["BagSpace_1"]) then
				LinkNpcGossipFunc_New(nNpcId,"3-5")
				return
			end
			-- 检查是否有任务物品，删除
			local nId = {}
			local nCounter = 0
			for _,v in pairs(tHalloween2015_PumpkinVSZombie_Item["Item"]) do
				if Item_ChkItem(v) then
					nCounter = nCounter + 1
					table.insert(nId,v)
				end
			end
			if nCounter ~= 0 then
				for _,k in pairs(nId) do
					Item_DelAllItemByType(k)
				end
			end
			
			--设置掩码 stc(129,39) = 2 完成任务
			Task_SetStatistic(nEvent1,nType1,nComplete1,1,0)
			Task_SetStcTimestamp(nEvent1,nType1,0,0)
			FestivalGeneralPackage_GetGift(tHalloween2015_PumpkinVSZombie_Log["FestivalId"],tHalloween2015_PumpkinVSZombie_Log["LogId"])
			User_EffectAdd(tHalloween2015_PumpkinVSZombie_Effect[1],tHalloween2015_PumpkinVSZombie_Effect[2])
			Sys_SaveActionFestivalLog(tHalloween2015_PumpkinVSZombie_Log["FinishTask"])
		end
	end
end

--17145 南瓜宝宝 
--Option1 带我离开南瓜园
function Halloween2015_PumpkinVSZombie_LeaveMap(nNpcId)
	-- 判断活动时间
	if not Sys_ChkFullTime(tHalloween2015_PumpkinVSZombie_Cont["ActivityTime"]) then
		--不在活动时间，活动后
		LinkNpcGossipFunc_New(nNpcId,"1-3")
		return
	end
	
	Halloween2015_PumpkinVSZombie_ChgMap(tHalloween2015_PumpkinVSZombie_Npc[17144]["NpcId"])
	--stc(129,41) == 3 杀满3只僵尸
	if Halloween2015_PumpkinVSZombie_ChkStcComplete(2) then
		User_TalkChannel2005(tHalloween2015_PumpkinVSZombie_Text["BackToMap"])
	end
	
	local nEvent = tHalloween2015_PumpkinVSZombie_Stc[2]["EventType"]
	local nType = tHalloween2015_PumpkinVSZombie_Stc[2]["DataType"]
	local nComplete = tHalloween2015_PumpkinVSZombie_Stc[2]["Complete"]
	--stc(129,41) < 3 僵尸数不足
	if Task_ChkStcValue(nEvent,nType,"<",nComplete) then
		User_TalkChannel2005(tHalloween2015_PumpkinVSZombie_Text["BackToMapWithTask"])
	end
end

-------------------------------------------使用物品逻辑----------------------------------------------------------
--百宝盒
function Halloween2015_PumpkinVSZombie_UseBigBox(nItemId)
	-- 判断活动时间
	if Sys_ChkFullTime(tHalloween2015_PumpkinVSZombie_Cont["BeforeActivityTime"]) then
		--活动前，提示在活动时间使用
		User_TalkChannel2005(tHalloween2015_PumpkinVSZombie_Text["UseInTime"])
		return
	elseif not Sys_ChkFullTime(tHalloween2015_PumpkinVSZombie_Cont["ActivityTime"]) then
		--活动后，删除物品
		if Item_ChkItem(nItemId) and Item_DelItem(nItemId) then
			local str = string.format(tHalloween2015_PumpkinVSZombie_Log["DelItem"],tostring(nItemId))
			Sys_SaveActionFestivalLog(str)
			User_TalkChannel2005(tHalloween2015_PumpkinVSZombie_Text["DelItem"])
			return
		end
	end
	
	--判断背包空间
	if not User_CheckLeftSpace(tHalloween2015_PumpkinVSZombie_Cont["BagSpace_2"]) then
		User_TalkChannel2005(tHalloween2015_PumpkinVSZombie_Text["FullBag"])
		return
	end
	
	--打开获得5个小魔盒
	if Item_ChkItem(nItemId) and Item_DelItem(nItemId) then
		Item_AddItem(tHalloween2015_PumpkinVSZombie_Item["Item"][2])
		Item_AddItem(tHalloween2015_PumpkinVSZombie_Item["Item"][3])
		Item_AddItem(tHalloween2015_PumpkinVSZombie_Item["Item"][4])
		Item_AddItem(tHalloween2015_PumpkinVSZombie_Item["Item"][5])
		Item_AddItem(tHalloween2015_PumpkinVSZombie_Item["Item"][6])

		Sys_SaveActionFestivalLog(tHalloween2015_PumpkinVSZombie_Log["OpenBigBox"])
		User_TalkChannel2005(tHalloween2015_PumpkinVSZombie_Text["OpenBox"])
	end
end

--道具
function Halloween2015_PumpkinVSZombie_UseTools(nItemId)
	-- 判断活动时间
	if Sys_ChkFullTime(tHalloween2015_PumpkinVSZombie_Cont["BeforeActivityTime"]) then
		--活动前，提示在活动时间使用
		User_TalkChannel2005(tHalloween2015_PumpkinVSZombie_Text["UseInTime"])
		return
	elseif not Sys_ChkFullTime(tHalloween2015_PumpkinVSZombie_Cont["ActivityTime"]) then
		--活动后，删除物品
		if Item_ChkItem(nItemId) and Item_DelItem(nItemId) then
			local str = string.format(tHalloween2015_PumpkinVSZombie_Log["DelItem"],tostring(nItemId))
			Sys_SaveActionFestivalLog(str)
			User_TalkChannel2005(tHalloween2015_PumpkinVSZombie_Text["DelItem"])
			return
		end
	end
	
	-- 判断玩家等级
	local nLevel = tHalloween2015_PumpkinVSZombie_Cont["Level"]
	local nMete = tHalloween2015_PumpkinVSZombie_Cont["Metempsychosis"]
	if not User_JudgeLevelAndMetempsychosis(nLevel,nMete) then
		User_TalkChannel2005(tHalloween2015_PumpkinVSZombie_Text["Level"])
		return
	end
	
	--判断是否在活动地图中
	local nMapId = tHalloween2015_PumpkinVSZombie_Npc[17145]["Mapid"]
	if Get_UserMapId() ~= nMapId then
		User_TalkChannel2005(tHalloween2015_PumpkinVSZombie_Text["UseInMap"])
		return
	end

	--判断是否完成任务
	local nEvent1 = tHalloween2015_PumpkinVSZombie_Stc[1]["EventType"]
	local nType1 = tHalloween2015_PumpkinVSZombie_Stc[1]["DataType"]
	local nData1 = tHalloween2015_PumpkinVSZombie_Stc[1]["GetTask"]
	local nComplete1 = tHalloween2015_PumpkinVSZombie_Stc[1]["Complete"]
	
	local nEvent2 = tHalloween2015_PumpkinVSZombie_Stc[2]["EventType"]
	local nType2 = tHalloween2015_PumpkinVSZombie_Stc[2]["DataType"]
	local nComplete2 = tHalloween2015_PumpkinVSZombie_Stc[2]["Complete"]
	
	--stc(129,39) == 0 未接任务
	if Task_ChkStcValue(nEvent1,nType1,"==",0) then
		User_TalkChannel2005(tHalloween2015_PumpkinVSZombie_Text["UseWithTask"])
		return
	end
	
	--stc(129,39) == 2  完成任务
	if Halloween2015_PumpkinVSZombie_ChkStcComplete(1) then
		User_TalkChannel2005(tHalloween2015_PumpkinVSZombie_Text["CompleteTask"])
		return
	end
	
	--stc(129,39) == 1 接了任务
	if Task_ChkStcValue(nEvent1,nType1,"==",nData1) then
		--stc(129,41) == 3 杀满3只僵尸
		if Halloween2015_PumpkinVSZombie_ChkStcComplete(2) then
			User_TalkChannel2005(tHalloween2015_PumpkinVSZombie_Text["GoGetReward"])
			return
		end	
		--stc(129,41) < 3 僵尸数不足
		if Task_ChkStcValue(nEvent2,nType2,"<",nComplete2) then			
			--	食人花，大南瓜，红辣椒 可以杀掉僵尸
			-- 郁金香，万圣节糖果 不能杀掉僵尸
			if Item_ChkItem(nItemId) then		
				--使用道具 
				Sys_MouseWaitClick(4,"</F>Halloween2015_PumpkinVSZombie_MouseClick</N>"..nItemId)
			end
		end	
	end
end

function Halloween2015_PumpkinVSZombie_MouseClick(nItemId)
	if Sys_MonsterMouseType(tostring(7618)) then
		local nId1 = tHalloween2015_PumpkinVSZombie_Item["Item"][2]
		local nId2 = tHalloween2015_PumpkinVSZombie_Item["Item"][3]
		local nId3 = tHalloween2015_PumpkinVSZombie_Item["Item"][4]
		if nItemId == nId1 or nItemId == nId2 or nItemId == nId3 then
			--删除选中的怪物
			Sys_MouseDeleteChosen()
			User_EffectAdd(tHalloween2015_PumpkinVSZombie_Effect[1],tHalloween2015_PumpkinVSZombie_Effect[3])
			local nEvent = tHalloween2015_PumpkinVSZombie_Stc[2]["EventType"]
			local nType = tHalloween2015_PumpkinVSZombie_Stc[2]["DataType"]
			Task_AddStatistic(nEvent,nType,1,1,0)
			
			if Halloween2015_PumpkinVSZombie_ChkStcComplete(2) then
				Sys_MsgBox(tHalloween2015_PumpkinVSZombie_Text["Successful"],"</F>Halloween2015_PumpkinVSZombie_GuideWay")
			end
		end
		--清除当前指针状态
		Sys_MouseClearStatus()
		Item_DelItem(nItemId)
		
		local str = string.format(tHalloween2015_PumpkinVSZombie_Log["UseItem"],tostring(nItemId))
		Sys_SaveActionFestivalLog(str)
		User_TalkChannel2005(tHalloween2015_PumpkinVSZombie_Text[nItemId])
	end
end

--寻路到npc处
function Halloween2015_PumpkinVSZombie_GuideWay()
	local nPosX = tHalloween2015_PumpkinVSZombie_Npc[17145]["CellX"]
	local nPosY = tHalloween2015_PumpkinVSZombie_Npc[17145]["CellY"]
	local nMapId = tHalloween2015_PumpkinVSZombie_Npc[17145]["Mapid"]
	local nNpcId = tHalloween2015_PumpkinVSZombie_Npc[17145]["NpcId"]
	Sys_GotoSomeWhere(nPosX,nPosY,nMapId,nNpcId)
end

-----------------------------------------杀怪逻辑-------------------------------------------------------------
function Halloween2015_PumpkinVSZombie_KillMonster_7618(nMonsterId)
	-- 判断活动时间
	if not Sys_ChkFullTime(tHalloween2015_PumpkinVSZombie_Cont["ActivityTime"]) then
		return
	end
	--提示玩家使用道具杀怪
	Sys_MsgBox(tHalloween2015_PumpkinVSZombie_Text["UseItem"])
	if Halloween2015_PumpkinVSZombie_ChkStcComplete(2) then
		Sys_MsgBox(tHalloween2015_PumpkinVSZombie_Text["Successful"])
		return
	end
end

------------------------------------------------NPC模块--------------------------------------------------
-- 17144 南瓜园园丁大叔
tNpcFace[3194] = 15 
tNpcGossip[17144] = tNpcGossip[17144] or DefaultNpc:new{}
tNpcGossip[17144]["OptionHidden"] = 1

--活动前对白
tNpcGossip[17144]["Text1-1"] = {111,112,113}
tNpcGossip[17144]["Text111"] = tHalloween2015_PumpkinVSZombie_Text[17144]["Text111"]
tNpcGossip[17144]["Text112"] = tHalloween2015_PumpkinVSZombie_Text[17144]["Text112"]
tNpcGossip[17144]["Text113"] = tHalloween2015_PumpkinVSZombie_Text[17144]["Text113"]
tNpcGossip[17144]["tOption1-1"] = {1}
tNpcGossip[17144]["ChkFunc1-1"] = function ()
	return Sys_ChkFullTime(tHalloween2015_PumpkinVSZombie_Cont["BeforeActivityTime"])
end

--活动中对白
tNpcGossip[17144]["Text1-2"] = {121,122,123}
tNpcGossip[17144]["Text121"] = tHalloween2015_PumpkinVSZombie_Text[17144]["Text121"]
tNpcGossip[17144]["Text122"] = tHalloween2015_PumpkinVSZombie_Text[17144]["Text122"]
tNpcGossip[17144]["Text123"] = tHalloween2015_PumpkinVSZombie_Text[17144]["Text123"]
tNpcGossip[17144]["tOption1-2"] = {2,3,4,5}
tNpcGossip[17144]["ChkFunc1-2"] = function ()
	return Sys_ChkFullTime(tHalloween2015_PumpkinVSZombie_Cont["ActivityTime"])
end

--活动后对白
tNpcGossip[17144]["Text1-3"] = {131}
tNpcGossip[17144]["Text131"] = tHalloween2015_PumpkinVSZombie_Text[17144]["Text131"]
tNpcGossip[17144]["tOption1-3"] = {8}

--接Option2：我要大战僵尸！
--失败、判断等级不足
tNpcGossip[17144]["Text2-1"] = {211,212}
tNpcGossip[17144]["Text211"] = tHalloween2015_PumpkinVSZombie_Text[17144]["Text211"]
tNpcGossip[17144]["Text212"] = tHalloween2015_PumpkinVSZombie_Text[17144]["Text212"]
tNpcGossip[17144]["tOption2-1"] = {9}
--在活动时间内，stc(129,39) >= 2
tNpcGossip[17144]["Text2-2"] = {221,222}
tNpcGossip[17144]["Text221"] = tHalloween2015_PumpkinVSZombie_Text[17144]["Text221"]
tNpcGossip[17144]["Text222"] = tHalloween2015_PumpkinVSZombie_Text[17144]["Text222"]
tNpcGossip[17144]["tOption2-2"] = {10}
--在活动时间内，杀完3只 stc(129,41) >= 3
tNpcGossip[17144]["Text2-3"] = {231}
tNpcGossip[17144]["Text231"] = tHalloween2015_PumpkinVSZombie_Text[17144]["Text231"]
tNpcGossip[17144]["tOption2-3"] = {11}
--接受了任务，但是没有杀完3只，删除相关道具，给魔盒，背包满提示
tNpcGossip[17144]["Text2-4"] = {241}
tNpcGossip[17144]["Text241"] = tHalloween2015_PumpkinVSZombie_Text[17144]["Text241"]
tNpcGossip[17144]["tOption2-4"] = {12}
--传送进地图
tNpcGossip[17144]["Text2-5"] = {251,252,253}
tNpcGossip[17144]["Text251"] = tHalloween2015_PumpkinVSZombie_Text[17144]["Text251"]
tNpcGossip[17144]["Text252"] = tHalloween2015_PumpkinVSZombie_Text[17144]["Text252"]
tNpcGossip[17144]["Text253"] = tHalloween2015_PumpkinVSZombie_Text[17144]["Text253"]
tNpcGossip[17144]["tOption2-5"] = {13}
	
--接Option3：领取战胜僵尸的奖励。
--等级不足
tNpcGossip[17144]["Text3-1"] = {311}
tNpcGossip[17144]["Text311"] = tHalloween2015_PumpkinVSZombie_Text[17144]["Text311"]
tNpcGossip[17144]["tOption3-1"] = {14}
--没有进入过地图，没有奖励
tNpcGossip[17144]["Text3-2"] = {321}
tNpcGossip[17144]["Text321"] = tHalloween2015_PumpkinVSZombie_Text[17144]["Text321"]
tNpcGossip[17144]["tOption3-2"] = {15}
--已领取过奖励
tNpcGossip[17144]["Text3-3"] = {331}
tNpcGossip[17144]["Text331"] = tHalloween2015_PumpkinVSZombie_Text[17144]["Text331"]
tNpcGossip[17144]["tOption3-3"] = {15}
--未完成任务，不可领取
tNpcGossip[17144]["Text3-4"] = {341}
tNpcGossip[17144]["Text341"] = tHalloween2015_PumpkinVSZombie_Text[17144]["Text341"]
tNpcGossip[17144]["tOption3-4"] = {16}
--背包满提示
tNpcGossip[17144]["Text3-5"] = {351}
tNpcGossip[17144]["Text351"] = tHalloween2015_PumpkinVSZombie_Text[17144]["Text351"]
tNpcGossip[17144]["tOption3-5"] = {12}

--接Option4：我该如何战胜僵尸？
tNpcGossip[17144]["Text4-1"] = {411,412}
tNpcGossip[17144]["Text411"] = tHalloween2015_PumpkinVSZombie_Text[17144]["Text411"]
tNpcGossip[17144]["Text412"] = tHalloween2015_PumpkinVSZombie_Text[17144]["Text412"]
tNpcGossip[17144]["tOption4-1"] = {6}

--接Option6：都是哪些法宝呢？
tNpcGossip[17144]["Text6-1"] = {611,612}
tNpcGossip[17144]["Text611"] = tHalloween2015_PumpkinVSZombie_Text[17144]["Text611"]
tNpcGossip[17144]["Text612"] = tHalloween2015_PumpkinVSZombie_Text[17144]["Text612"]
tNpcGossip[17144]["tOption6-1"] = {7}

--选项
tNpcGossip[17144]["Option1"] = tHalloween2015_PumpkinVSZombie_Text[17144]["Option1"]
tNpcGossip[17144]["Option2"] = tHalloween2015_PumpkinVSZombie_Text[17144]["Option2"]
tNpcGossip[17144]["OptionFunc2"]="Halloween2015_PumpkinVSZombie_VSZombies</N>17144"
tNpcGossip[17144]["Option3"] = tHalloween2015_PumpkinVSZombie_Text[17144]["Option3"]
tNpcGossip[17144]["OptionFunc3"]="Halloween2015_PumpkinVSZombie_GetReward</N>17144"
tNpcGossip[17144]["Option4"] = tHalloween2015_PumpkinVSZombie_Text[17144]["Option4"]
tNpcGossip[17144]["OptionPoint4"]="4-1"
tNpcGossip[17144]["Option5"] = tHalloween2015_PumpkinVSZombie_Text[17144]["Option5"]
tNpcGossip[17144]["Option6"] = tHalloween2015_PumpkinVSZombie_Text[17144]["Option6"]
tNpcGossip[17144]["OptionPoint6"]="6-1"
tNpcGossip[17144]["Option7"] = tHalloween2015_PumpkinVSZombie_Text[17144]["Option7"]
tNpcGossip[17144]["Option8"] = tHalloween2015_PumpkinVSZombie_Text[17144]["Option8"]
tNpcGossip[17144]["Option9"] = tHalloween2015_PumpkinVSZombie_Text[17144]["Option9"]
tNpcGossip[17144]["Option10"] = tHalloween2015_PumpkinVSZombie_Text[17144]["Option10"]
tNpcGossip[17144]["Option11"] = tHalloween2015_PumpkinVSZombie_Text[17144]["Option11"]
tNpcGossip[17144]["OptionPoint11"]="1-2"
tNpcGossip[17144]["Option12"] = tHalloween2015_PumpkinVSZombie_Text[17144]["Option12"]
tNpcGossip[17144]["Option13"] = tHalloween2015_PumpkinVSZombie_Text[17144]["Option13"]
tNpcGossip[17144]["OptionFunc13"]="Halloween2015_PumpkinVSZombie_SendInMap</N>17144"
tNpcGossip[17144]["Option14"] = tHalloween2015_PumpkinVSZombie_Text[17144]["Option14"]
tNpcGossip[17144]["Option15"] = tHalloween2015_PumpkinVSZombie_Text[17144]["Option15"]
tNpcGossip[17144]["Option16"] = tHalloween2015_PumpkinVSZombie_Text[17144]["Option16"]

-- 17145 南瓜宝宝
tNpcFace[3195] = 196
tNpcGossip[17145] = tNpcGossip[17145] or DefaultNpc:new{}
tNpcGossip[17145]["OptionHidden"] = 1

--活动中对白
tNpcGossip[17145]["Text1-1"] = {111,112}
tNpcGossip[17145]["Text111"] = tHalloween2015_PumpkinVSZombie_Text[17145]["Text111"]
tNpcGossip[17145]["Text112"] = tHalloween2015_PumpkinVSZombie_Text[17145]["Text112"]
tNpcGossip[17145]["tOption1-1"] = {1,2}
tNpcGossip[17145]["ChkFunc1-1"] = function ()
	return Sys_ChkFullTime(tHalloween2015_PumpkinVSZombie_Cont["ActivityTime"])
end

--选项
tNpcGossip[17145]["Option1"] = tHalloween2015_PumpkinVSZombie_Text[17145]["Option1"]
tNpcGossip[17145]["OptionFunc1"]="Halloween2015_PumpkinVSZombie_LeaveMap</N>17145"
tNpcGossip[17145]["Option2"] = tHalloween2015_PumpkinVSZombie_Text[17145]["Option2"]

------------------------------------------------itemtype模块--------------------------------------------------
--百宝盒
tItem[3007244] = tItem[3007244] or {}
tItem[3007244]["Function"] = function(nItemId,sItemName)
	local nItemId = tHalloween2015_PumpkinVSZombie_Item["Item"][1]
	Halloween2015_PumpkinVSZombie_UseBigBox(nItemId)
end

--食人花
tItem[3007246] = tItem[3007246] or {}
tItem[3007246]["Function"] = function(nItemId,sItemName)
	local nItemId = tHalloween2015_PumpkinVSZombie_Item["Item"][2]
	Halloween2015_PumpkinVSZombie_UseTools(nItemId)
end

--大南瓜
tItem[3007247] = tItem[3007247] or {}
tItem[3007247]["Function"] = function(nItemId,sItemName)
	local nItemId = tHalloween2015_PumpkinVSZombie_Item["Item"][3]
	Halloween2015_PumpkinVSZombie_UseTools(nItemId)
end

--红辣椒
tItem[3007248] = tItem[3007248] or {}
tItem[3007248]["Function"] = function(nItemId,sItemName)
	local nItemId = tHalloween2015_PumpkinVSZombie_Item["Item"][4]
	Halloween2015_PumpkinVSZombie_UseTools(nItemId)
end

--郁金香
tItem[3007249] = tItem[3007249] or {}
tItem[3007249]["Function"] = function(nItemId,sItemName)
	local nItemId = tHalloween2015_PumpkinVSZombie_Item["Item"][5]
	Halloween2015_PumpkinVSZombie_UseTools(nItemId)
end

--万圣节糖果
tItem[3007250] = tItem[3007250] or {}
tItem[3007250]["Function"] = function(nItemId,sItemName)
	local nItemId = tHalloween2015_PumpkinVSZombie_Item["Item"][6]
	Halloween2015_PumpkinVSZombie_UseTools(nItemId)
end

------------------------------------------------Monster模块--------------------------------------------------
--7618  吸血鬼
tMonster[7618] = tMonster[7618] or {}
tMonster[7618]["tFunction"] = tMonster[7618]["tFunction"] or {}
table.insert(tMonster[7618]["tFunction"],Halloween2015_PumpkinVSZombie_KillMonster_7618)
