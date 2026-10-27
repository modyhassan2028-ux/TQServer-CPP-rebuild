------------------------------------------------------------------------------------
--Name:			[简体征服][节日任务]2015年春节活动之元宵（限时秒杀）
--Purpose:		2015年春节活动之元宵（限时秒杀）
--Creator: 		丁晨
--Created:		2014/12/15
------------------------------------------------------------------------------------
--任务需求：
--元宵的免费秒杀一定不能错过！2015年3月1日至3月5日元宵节期间，每天整点开始的30分钟内，等级达到80级或已转世的侠士们都可以去元宵福利美眉那儿领取免费的秒杀券获得奖品。参加每天12点整、19点整、21点整的秒杀，更可能获得超值大奖哦！ 
--任务目标：向元宵福利美眉领取秒杀券。
------------------------------------------------------------------------------------
--物品：
--- 183325 -- 浪漫骑士套装(3天使用期限) * 1
--- 711504  -- 桃源灵玉*3
--- 200499  -- 萌肥圆小羊驼(3天使用期限) *1
--- 1088000 -- 龙珠 *1
--- 730003  -- 赤炼石+3 *1
--- 3000140 -- 精装优质宝石包 *1
--- 711083  -- 乾坤九转神露 *1
------------------------------------------------------------------------------------
--掩码说明
---stc(131,94) 记录一天只能领取一次秒杀劵

--LOGid 10002409
------------------------------------------------------------------------------------
--命名规范
-- FestivalSpring2015_LanternFestival_
------------------------------------------------------------------------------------
--STC掩码
local tFestivalSpring2015_LanternFestival_Stc = {}
	--stc(131,94) 记录一天只能领取一次秒杀劵
	tFestivalSpring2015_LanternFestival_Stc["Event"] = 131
	tFestivalSpring2015_LanternFestival_Stc["Type"] = 94

-- log表
local tFestivalSpring2015_LanternFestival_Log = {}
	--记录消耗物品与获得物品log
	tFestivalSpring2015_LanternFestival_Log["CompleteLog"] = "0,0,0,0,10002409,2,3005537,1"
	tFestivalSpring2015_LanternFestival_Log["RewardLog"] = "0,0,%s,%s,10002409,2,%s,%s"
	tFestivalSpring2015_LanternFestival_Log["SecKill_GoodsLog"] = "3005537"
	tFestivalSpring2015_LanternFestival_Log["SecKill_NumLog"] = "1"
	--消耗浪漫花语武器礼包
	tFestivalSpring2015_LanternFestival_Log["Romance_GoodsLog"] = "3005571"
	tFestivalSpring2015_LanternFestival_Log["Romance_NumLog"] = "1"

--活动数据
local tFestivalSpring2015_LanternFestival_Data = {}
	--活动前、活动中、活动后时间
	tFestivalSpring2015_LanternFestival_Data["Bef_Time"]= "2014-02-11 00:00 2015-02-28 23:59"
	tFestivalSpring2015_LanternFestival_Data["Now_Time"]= "2015-03-01 00:00 2015-03-05 23:59"
	tFestivalSpring2015_LanternFestival_Data["Aft_Time"]= "2015-03-06 00:00 2020-03-06 23:59"
	--是否每个整点在30分钟之内
	tFestivalSpring2015_LanternFestival_Data["Receive_Time"] = "00 29"
	tFestivalSpring2015_LanternFestival_Data["Seckill_Time"] = {}
	--整点广播数字
	tFestivalSpring2015_LanternFestival_Data["Seckill_Get"] = {}
	tFestivalSpring2015_LanternFestival_Data["Seckill_Get"][1] = "12"
	tFestivalSpring2015_LanternFestival_Data["Seckill_Get"][2] = "19"
	tFestivalSpring2015_LanternFestival_Data["Seckill_Get"][3] = "21"
	--超值大奖秒杀领取时间
	tFestivalSpring2015_LanternFestival_Data["Seckill_Time"][1] = "12:00 12:29"
	tFestivalSpring2015_LanternFestival_Data["Seckill_Time"][2] = "19:00 19:29"
	tFestivalSpring2015_LanternFestival_Data["Seckill_Time"][3] = "21:00 21:29"  
	--超值大奖提前2分钟广播
	tFestivalSpring2015_LanternFestival_Data["Seckill_Time"][4] = "11:58 11:58"
	tFestivalSpring2015_LanternFestival_Data["Seckill_Time"][5] = "18:58 18:58"
	tFestivalSpring2015_LanternFestival_Data["Seckill_Time"][6] = "20:58 20:58"  
	--超值大奖领取1小时内打开才有可能有奖励
	tFestivalSpring2015_LanternFestival_Data["Seckill_Time"][7] = "12:00 12:59"
	tFestivalSpring2015_LanternFestival_Data["Seckill_Time"][8] = "19:00 19:59"
	tFestivalSpring2015_LanternFestival_Data["Seckill_Time"][9] = "21:00 21:59"  
	--大于等于80级 或1转以上
	tFestivalSpring2015_LanternFestival_Data["Seckill_Level"] = 80
	tFestivalSpring2015_LanternFestival_Data["MinMetempsychosis"] = 0
	--满级 给一半奖励
	tFestivalSpring2015_LanternFestival_Data["Max_Level"] = 140
	tFestivalSpring2015_LanternFestival_Data["Max_Level_Scale"] = 2
	--修行值
	tFestivalSpring2015_LanternFestival_Data["Spiritual_Values"] = "6"
	--气力值
	tFestivalSpring2015_LanternFestival_Data["Strength_Values"] = "12"
	--经验值
	tFestivalSpring2015_LanternFestival_Data["Exp_Values"] = "4"
	--转职业次数 未转
	tFestivalSpring2015_LanternFestival_Data["Transfer_Values0"] = 0
	--1转
	tFestivalSpring2015_LanternFestival_Data["Transfer_Values1"] = 1
	--2转
	tFestivalSpring2015_LanternFestival_Data["Transfer_Values1"] = 2
	--检测赠品装用
	tFestivalSpring2015_LanternFestival_Data["Check_Monopoly"] = 1
	--背包空间检测
	tFestivalSpring2015_LanternFestival_Data["Check_Bag"] = 1
	--排名专用ID 动态存储表
	tFestivalSpring2015_LanternFestival_Data["Check_Rank"] = 50683
	--全服第一名广播
	tFestivalSpring2015_LanternFestival_Data["Ranking"] = 1
	
--奖励数据 Overflow_Rewards 为超值大奖
local tFestivalSpring2015_LanternFestival_Rewards ={}
	tFestivalSpring2015_LanternFestival_Rewards["Overflow_Rewards"] = {}
	--第一名奖励 12点奖励	龙珠 
	tFestivalSpring2015_LanternFestival_Rewards["Overflow_Rewards"][1] = {}
	tFestivalSpring2015_LanternFestival_Rewards["Overflow_Rewards"][1][1] = {}
	tFestivalSpring2015_LanternFestival_Rewards["Overflow_Rewards"][1][1]["ItemId"] = 1088000 
	tFestivalSpring2015_LanternFestival_Rewards["Overflow_Rewards"][1][1]["AddAmount"] = 1 
	tFestivalSpring2015_LanternFestival_Rewards["Overflow_Rewards"][1][1]["Monopoly"] = 3 
	--第一名奖励 19点奖励   乾坤九转神露
	tFestivalSpring2015_LanternFestival_Rewards["Overflow_Rewards"][1][2] = {}
	tFestivalSpring2015_LanternFestival_Rewards["Overflow_Rewards"][1][2]["ItemId"] = 711083 
	tFestivalSpring2015_LanternFestival_Rewards["Overflow_Rewards"][1][2]["AddAmount"] = 1 
	tFestivalSpring2015_LanternFestival_Rewards["Overflow_Rewards"][1][2]["Monopoly"] = 3 
	--第一名奖励 21点奖励   气力值500点
	tFestivalSpring2015_LanternFestival_Rewards["Overflow_Rewards"][1][3] = {}
	tFestivalSpring2015_LanternFestival_Rewards["Overflow_Rewards"][1][3]["AddStrengthValue"] = 500 
	--第二名奖励 12点奖励  精装优质宝石包
	tFestivalSpring2015_LanternFestival_Rewards["Overflow_Rewards"][2] = {}
	tFestivalSpring2015_LanternFestival_Rewards["Overflow_Rewards"][2][1] = {}
	tFestivalSpring2015_LanternFestival_Rewards["Overflow_Rewards"][2][1]["ItemId"] = 3000140 
	tFestivalSpring2015_LanternFestival_Rewards["Overflow_Rewards"][2][1]["AddAmount"] = 1 
	tFestivalSpring2015_LanternFestival_Rewards["Overflow_Rewards"][2][1]["Flag"] = 1
	tFestivalSpring2015_LanternFestival_Rewards["Overflow_Rewards"][2][1]["Monopoly"] = 3 
	
	--第二名奖励 19点奖励  赤炼石+3
	tFestivalSpring2015_LanternFestival_Rewards["Overflow_Rewards"][2][2] = {}
	tFestivalSpring2015_LanternFestival_Rewards["Overflow_Rewards"][2][2]["ItemId"] = 730003 
	tFestivalSpring2015_LanternFestival_Rewards["Overflow_Rewards"][2][2]["AddAmount"] = 1 
	tFestivalSpring2015_LanternFestival_Rewards["Overflow_Rewards"][2][2]["Monopoly"] = 3 
	--第二名奖励 21点奖励  修行值1000点
	tFestivalSpring2015_LanternFestival_Rewards["Overflow_Rewards"][2][3] = {}
	tFestivalSpring2015_LanternFestival_Rewards["Overflow_Rewards"][2][3]["AddCultivation"] = 1000 
	--第三名奖励 12点奖励 坐骑外套（限时3日）
	tFestivalSpring2015_LanternFestival_Rewards["Overflow_Rewards"][3] = {}
	tFestivalSpring2015_LanternFestival_Rewards["Overflow_Rewards"][3][1] = {}
	tFestivalSpring2015_LanternFestival_Rewards["Overflow_Rewards"][3][1]["ItemId"] = 200499 
	tFestivalSpring2015_LanternFestival_Rewards["Overflow_Rewards"][3][1]["AddAmount"] = 1 
	tFestivalSpring2015_LanternFestival_Rewards["Overflow_Rewards"][3][1]["Monopoly"] = 3 
	tFestivalSpring2015_LanternFestival_Rewards["Overflow_Rewards"][3][1]["Time_Limit"] = 4320
	tFestivalSpring2015_LanternFestival_Rewards["Overflow_Rewards"][3][1]["Active"] = 1 
	tFestivalSpring2015_LanternFestival_Rewards["Overflow_Rewards"][3][1]["reduce_dmg"] = 1 
	--第三名奖励 19点奖励 节日武器外套（限时3日）
	tFestivalSpring2015_LanternFestival_Rewards["Overflow_Rewards"][3][2] = {}
	tFestivalSpring2015_LanternFestival_Rewards["Overflow_Rewards"][3][2]["ItemId"] = 3005571 
	tFestivalSpring2015_LanternFestival_Rewards["Overflow_Rewards"][3][2]["AddAmount"] = 1
	tFestivalSpring2015_LanternFestival_Rewards["Overflow_Rewards"][3][2]["Monopoly"] = 3
	tFestivalSpring2015_LanternFestival_Rewards["Overflow_Rewards"][3][2]["Time_Limit"] = 4320
	tFestivalSpring2015_LanternFestival_Rewards["Overflow_Rewards"][3][2]["Active"] = 1 
	--第三名奖励 21点奖励 桃源灵玉*3
	tFestivalSpring2015_LanternFestival_Rewards["Overflow_Rewards"][3][3] = {}
	tFestivalSpring2015_LanternFestival_Rewards["Overflow_Rewards"][3][3]["ItemId"] = 711504 
	tFestivalSpring2015_LanternFestival_Rewards["Overflow_Rewards"][3][3]["AddAmount"] = 3 
	tFestivalSpring2015_LanternFestival_Rewards["Overflow_Rewards"][3][3]["Monopoly"] = 3
	--秒杀卷
	tFestivalSpring2015_LanternFestival_Rewards["Overflow_Rewards"][4] = {}
	tFestivalSpring2015_LanternFestival_Rewards["Overflow_Rewards"][4]["ItemId"] = 3005537 
	tFestivalSpring2015_LanternFestival_Rewards["Overflow_Rewards"][4]["AddAmount"] = 1 
	tFestivalSpring2015_LanternFestival_Rewards["Overflow_Rewards"][4]["Flag"] = 1
	tFestivalSpring2015_LanternFestival_Rewards["Overflow_Rewards"][4]["Monopoly"] = 3
	--浪漫花语物品 玫瑰风暴（短武器）
	tFestivalSpring2015_LanternFestival_Rewards["Overflow_Rewards"][5] = {}
	tFestivalSpring2015_LanternFestival_Rewards["Overflow_Rewards"][5]["ItemId"] = 360149 
	tFestivalSpring2015_LanternFestival_Rewards["Overflow_Rewards"][5]["AddAmount"] = 1 
	tFestivalSpring2015_LanternFestival_Rewards["Overflow_Rewards"][5]["Flag"] = 1
	tFestivalSpring2015_LanternFestival_Rewards["Overflow_Rewards"][5]["Monopoly"] = 3
	tFestivalSpring2015_LanternFestival_Rewards["Overflow_Rewards"][5]["Time_Limit"] = 4320
	tFestivalSpring2015_LanternFestival_Rewards["Overflow_Rewards"][5]["Active"] = 1 
	tFestivalSpring2015_LanternFestival_Rewards["Overflow_Rewards"][5]["reduce_dmg"] = 1 
	--浪漫花语物品 玫瑰风暴（长武器）
	tFestivalSpring2015_LanternFestival_Rewards["Overflow_Rewards"][6] = {}
	tFestivalSpring2015_LanternFestival_Rewards["Overflow_Rewards"][6]["ItemId"] = 350079 
	tFestivalSpring2015_LanternFestival_Rewards["Overflow_Rewards"][6]["AddAmount"] = 1 
	tFestivalSpring2015_LanternFestival_Rewards["Overflow_Rewards"][6]["Flag"] = 1
	tFestivalSpring2015_LanternFestival_Rewards["Overflow_Rewards"][6]["Monopoly"] = 3
	tFestivalSpring2015_LanternFestival_Rewards["Overflow_Rewards"][6]["Time_Limit"] = 4320
	tFestivalSpring2015_LanternFestival_Rewards["Overflow_Rewards"][6]["Active"] = 1 
	tFestivalSpring2015_LanternFestival_Rewards["Overflow_Rewards"][6]["reduce_dmg"] = 1 
	--经验值满了给一半的气力值
	tFestivalSpring2015_LanternFestival_Rewards["Average_Rewards"] = {}
	--10分钟经验奖励
	tFestivalSpring2015_LanternFestival_Rewards["Average_Rewards"][1] = 10
	--30分钟经验奖励
	tFestivalSpring2015_LanternFestival_Rewards["Average_Rewards"][2] = 30 
	--90分钟经验奖励
	tFestivalSpring2015_LanternFestival_Rewards["Average_Rewards"][3] = 90 
	
--活动期间领取秒杀劵
function FestivalSpring2015_LanternFestival_Option3(nNpcId)
	--判断是否在活动期间
	if not Sys_ChkFullTime(tFestivalSpring2015_LanternFestival_Data["Now_Time"]) then
		LinkNpcGossipFunc_New(nNpcId,"1-2")
		return
	end
	
	--判断具体领取秒杀劵时间(活动期间每个整点领取一张,一天只能领一张)
	if not Sys_ChkMinute(tFestivalSpring2015_LanternFestival_Data["Receive_Time"]) then
		LinkNpcGossipFunc_New(nNpcId,"2-4")
		return
	end
	
	local nEvent = tFestivalSpring2015_LanternFestival_Stc["Event"]
	local nType = tFestivalSpring2015_LanternFestival_Stc["Type"]

	--隔天清空用户已领取的记录
	if  Task_StcInterval(nEvent,nType,1,4) then
		Task_SetStatistic(nEvent,nType,0,1)
		Task_SetStcTimestamp(nEvent,nType,0)
	end
	
	--是否今日已领过
	if not  Task_ChkStcValue(nEvent,nType,"==",0) then
	
		--今日已领取过秒杀卷
		LinkNpcGossipFunc_New(nNpcId,"2-7")
		return
	end
	
	--等级不足
	if not User_JudgeLevelAndMetempsychosis(tFestivalSpring2015_LanternFestival_Data["Seckill_Level"],tFestivalSpring2015_LanternFestival_Data["MinMetempsychosis"]) then
	
		--等级不足或未转世
		LinkNpcGossipFunc_New(nNpcId,"2-5")
		return
	end
	
	--检测背包空间
	if not User_CheckLeftSpace(tFestivalSpring2015_LanternFestival_Data["Check_Bag"]) then 
	
		--背包满
		LinkNpcGossipFunc_New(nNpcId,"2-6")
		return
	end
	
	--满足条件处理
	local nItemId = tFestivalSpring2015_LanternFestival_Rewards["Overflow_Rewards"][4]["ItemId"]
	local nNumber = tFestivalSpring2015_LanternFestival_Rewards["Overflow_Rewards"][4]["AddAmount"]
	local nFlag = tFestivalSpring2015_LanternFestival_Rewards["Overflow_Rewards"][4]["Flag"]
	local nMonopoly = tFestivalSpring2015_LanternFestival_Rewards["Overflow_Rewards"][4]["Monopoly"]
	
	--领取时检测身上已有秒杀卷事先移除
	if Item_ChkItem(nItemId,tFestivalSpring2015_LanternFestival_Data["Check_Monopoly"])  then
		Item_DelItem(nItemId,tFestivalSpring2015_LanternFestival_Data["Check_Monopoly"])
		User_TalkChannel2005(tFestivalSpring2015_LanternFestival_Text["BefPreClear"])
	end
	Item_AddItem(nItemId,nFlag,nNumber,nMonopoly)
	User_TalkChannel2005(tFestivalSpring2015_LanternFestival_Text["Success"])
	
	--记录领取时间12:00~12:29、19:00~19:29、21:00~21:29 领取的 并在整点1小时内打开才有机会获得超值大奖
	if Sys_ChkDayTime(tFestivalSpring2015_LanternFestival_Data["Seckill_Time"][1]) then
		Task_SetStatistic(nEvent,nType,tonumber(tFestivalSpring2015_LanternFestival_Data["Seckill_Get"][1]),1)
	elseif Sys_ChkDayTime(tFestivalSpring2015_LanternFestival_Data["Seckill_Time"][2]) then 
		Task_SetStatistic(nEvent,nType,tonumber(tFestivalSpring2015_LanternFestival_Data["Seckill_Get"][2]),1)
	elseif Sys_ChkDayTime(tFestivalSpring2015_LanternFestival_Data["Seckill_Time"][3]) then 
		Task_SetStatistic(nEvent,nType,tonumber(tFestivalSpring2015_LanternFestival_Data["Seckill_Get"][3]),1)
	else

		--记录其他整点领取的
		Task_SetStatistic(nEvent,nType,1,1)
	end
	Task_SetStcTimestamp(nEvent,nType,0)
	Sys_SaveActionFestivalLog(tFestivalSpring2015_LanternFestival_Log["CompleteLog"])
	
	--是否立刻使用秒杀卷
	Sys_MsgBox(tFestivalSpring2015_LanternFestival_Text["ImmediatelyUse"],"FestivalSpring2015_LanternFestival_UseItemBox</N>"..nItemId)
end	
	
--使用物品
function FestivalSpring2015_LanternFestival_UseItemBox(nItemId)
	--使用时是否有物品存在
	if not Item_ChkItem(nItemId,tFestivalSpring2015_LanternFestival_Data["Check_Monopoly"]) then
		Sys_MsgBox(tFestivalSpring2015_LanternFestival_Text["PresentClear"])
		return 
	end
	
	--检测是否在活动期间
	if not Sys_ChkFullTime(tFestivalSpring2015_LanternFestival_Data["Now_Time"]) then
		if Item_ChkItem(nItemId,tFestivalSpring2015_LanternFestival_Data["Check_Monopoly"]) and Item_DelItem(nItemId,tFestivalSpring2015_LanternFestival_Data["Check_Monopoly"])  then
			Sys_MsgBox(tFestivalSpring2015_LanternFestival_Text["FestivalFail"])
		end
		return
	end
	
	local bFlag = true
	local nEvent = tFestivalSpring2015_LanternFestival_Stc["Event"]
	local nType = tFestivalSpring2015_LanternFestival_Stc["Type"]
	
	--如果有遗留昨天 一张秒杀卷删除原来的
	if  Task_StcInterval(nEvent,nType,1,4) then
		local nItemId = tFestivalSpring2015_LanternFestival_Rewards["Overflow_Rewards"][4]["ItemId"]
		if Item_ChkItem(nItemId,tFestivalSpring2015_LanternFestival_Data["Check_Monopoly"])  then
			Item_DelItem(nItemId,tFestivalSpring2015_LanternFestival_Data["Check_Monopoly"])
			Sys_MsgBox(tFestivalSpring2015_LanternFestival_Text["BefPreClear"])
			Sys_SaveActionFestivalLog(string.format(tFestivalSpring2015_LanternFestival_Log["RewardLog"],tFestivalSpring2015_LanternFestival_Log["SecKill_GoodsLog"],tFestivalSpring2015_LanternFestival_Log["SecKill_NumLog"] ,"0","0"))
			return
		end
	end
		
	--使用后清除物品
	if Item_ChkItem(nItemId,tFestivalSpring2015_LanternFestival_Data["Check_Monopoly"])   then
		Item_DelItem(nItemId,tFestivalSpring2015_LanternFestival_Data["Check_Monopoly"])
	end
		
	--不是整点领取的 全部获得小奖(整点30分钟内领取的记录12、19、21),获得小奖写1
	if Task_ChkStcValue(nEvent,nType,"==",1)  then
		 bFlag = false
	end

	-- 不是在 12、19、21整点30分钟内领取的
	if not bFlag then
		FestivalSpring2015_LanternFestival_OrdinaryReward()
		return 
	end

	--在12点 19点 21点 至这些整点的29分之间领取的 前三名打开者 
	if Sys_ChkDayTime(tFestivalSpring2015_LanternFestival_Data["Seckill_Time"][7]) and Task_ChkStcValue(nEvent,nType,"==",tonumber(tFestivalSpring2015_LanternFestival_Data["Seckill_Get"][1]))	then
		FestivalSpring2015_LanternFestival_OverflowReward(1)
	elseif Sys_ChkDayTime(tFestivalSpring2015_LanternFestival_Data["Seckill_Time"][8]) and Task_ChkStcValue(nEvent,nType,"==",tonumber(tFestivalSpring2015_LanternFestival_Data["Seckill_Get"][2])) then
		FestivalSpring2015_LanternFestival_OverflowReward(2)
	elseif Sys_ChkDayTime(tFestivalSpring2015_LanternFestival_Data["Seckill_Time"][9]) and Task_ChkStcValue(nEvent,nType,"==",tonumber(tFestivalSpring2015_LanternFestival_Data["Seckill_Get"][3])) then
		FestivalSpring2015_LanternFestival_OverflowReward(3)
	else
	
		--未在前三名打开 获得 普通奖励
		FestivalSpring2015_LanternFestival_OrdinaryReward()
	end
end	

--普通奖励
function FestivalSpring2015_LanternFestival_OrdinaryReward()
	local nMetempsychosis = Get_UserMetempsychosis()
	local nUserLev = Get_UserLevel()
	local nTime = 0
	local sTalk =""
	local sLog  =""
	local sLogFormat = tFestivalSpring2015_LanternFestival_Log["RewardLog"]
	local nItemId = tFestivalSpring2015_LanternFestival_Log["SecKill_GoodsLog"] 
	local nNumber = tFestivalSpring2015_LanternFestival_Log["SecKill_NumLog"]
	
	-- 未转
	if nMetempsychosis == tFestivalSpring2015_LanternFestival_Data["Transfer_Values0"] then
		nTime = tFestivalSpring2015_LanternFestival_Rewards["Average_Rewards"][1] 
		
	-- 一转
	elseif  nMetempsychosis == tFestivalSpring2015_LanternFestival_Data["Transfer_Values1"] then
		nTime = tFestivalSpring2015_LanternFestival_Rewards["Average_Rewards"][2]
		
	-- 二转
	elseif  nMetempsychosis == tFestivalSpring2015_LanternFestival_Data["Transfer_Values2"] then
		nTime = tFestivalSpring2015_LanternFestival_Rewards["Average_Rewards"][3]
	else
		nTime = tFestivalSpring2015_LanternFestival_Rewards["Average_Rewards"][3]
	end
	
	--满经验给一半修行值
	if nUserLev  >= tFestivalSpring2015_LanternFestival_Data["Max_Level"] then
		User_AddCultivation(nTime/tFestivalSpring2015_LanternFestival_Data["Max_Level_Scale"]) 
		sTalk = string.format(tFestivalSpring2015_LanternFestival_Text["AddCultivation"],nTime/tFestivalSpring2015_LanternFestival_Data["Max_Level_Scale"])
		sLog = string.format(sLogFormat,nItemId,nNumber,tFestivalSpring2015_LanternFestival_Data["Spiritual_Values"],tostring(nTime/tFestivalSpring2015_LanternFestival_Data["Max_Level_Scale"]))
	else
	
		--使用后获得超值大奖或10（未转）30（一转）90（二转）分钟经验奖励
	   User_AddExpTime(nTime)
	   sTalk = string.format(tFestivalSpring2015_LanternFestival_Text["AddExp"],nTime)
	   sLog = string.format(sLogFormat,nItemId,nNumber,tFestivalSpring2015_LanternFestival_Data["Exp_Values"],tostring(nTime))
	end
	User_TalkChannel2005(sTalk)
	Sys_SaveActionFestivalLog(sLog)
end

--超值大奖 不同时间点 奖励不同
function FestivalSpring2015_LanternFestival_OverflowReward(nMoment)
	local sItemName = ""
	local nIndex = 0
	
	--第一名
	if Get_SysDynaGlobalData0(tFestivalSpring2015_LanternFestival_Data["Check_Rank"]) == 0 then 
	
		--记录获奖玩家ID
		Sys_SetSynaGlobalData0(tFestivalSpring2015_LanternFestival_Data["Check_Rank"],Get_UserId())
		nIndex = 1
	elseif Get_SysDynaGlobalData1(tFestivalSpring2015_LanternFestival_Data["Check_Rank"]) == 0 then 
		Sys_SetSynaGlobalData1(tFestivalSpring2015_LanternFestival_Data["Check_Rank"],Get_UserId())
		nIndex = 2
	elseif Get_SysDynaGlobalData2(tFestivalSpring2015_LanternFestival_Data["Check_Rank"]) == 0 then 
		Sys_SetSynaGlobalData2(tFestivalSpring2015_LanternFestival_Data["Check_Rank"],Get_UserId())
		nIndex = 3
	else
		FestivalSpring2015_LanternFestival_OrdinaryReward()
		return 
	end
	
	--物品ID
	local nItemId = tFestivalSpring2015_LanternFestival_Rewards["Overflow_Rewards"][nIndex][nMoment]["ItemId"]
	
	--是否继承
	local nFlag = tFestivalSpring2015_LanternFestival_Rewards["Overflow_Rewards"][nIndex][nMoment]["Flag"] 
	
	--物品数量
	local nNumber = tFestivalSpring2015_LanternFestival_Rewards["Overflow_Rewards"][nIndex][nMoment]["AddAmount"]
	
	-- 是否赠品
	local nMonopoly = tFestivalSpring2015_LanternFestival_Rewards["Overflow_Rewards"][nIndex][nMoment]["Monopoly"] 
	
	--是否有时限
	local nTime_Limit = tFestivalSpring2015_LanternFestival_Rewards["Overflow_Rewards"][nIndex][nMoment]["Time_Limit"] 
	
	--是否立刻激活
	local nActive = tFestivalSpring2015_LanternFestival_Rewards["Overflow_Rewards"][nIndex][nMoment]["Active"]
	
	--气力值
	local nStrengthValue = tFestivalSpring2015_LanternFestival_Rewards["Overflow_Rewards"][nIndex][nMoment]["AddStrengthValue"] 
	
	--修行值
	local nCultivation = tFestivalSpring2015_LanternFestival_Rewards["Overflow_Rewards"][nIndex][nMoment]["AddCultivation"]
	
	--1%神佑
	local nReduce_dmg = tFestivalSpring2015_LanternFestival_Rewards["Overflow_Rewards"][nIndex][nMoment]["reduce_dmg"] 
	
	--LOG内容
	local sLogContent = ""
	local slogText = tFestivalSpring2015_LanternFestival_Log["RewardLog"]
	local sRedGood = tFestivalSpring2015_LanternFestival_Log["SecKill_GoodsLog"]
	local sRedNumber = tFestivalSpring2015_LanternFestival_Log["SecKill_NumLog"]
	
	--如果是物品
	if nItemId then
		Item_AddItem(nItemId,nFlag,nNumber,nMonopoly,nTime_Limit,nActive,0,0,nReduce_dmg)
		
		sItemName = Get_ItemtypeName(nItemId)..tFestivalSpring2015_LanternFestival_Text["Present"]
		if nItemId == tFestivalSpring2015_LanternFestival_Rewards["Overflow_Rewards"][2][2]["ItemId"] then
			sItemName = Get_ItemtypeName(nItemId).."(+3)"..tFestivalSpring2015_LanternFestival_Text["Present"]
		end
		sLogContent = string.format(slogText,sRedGood,sRedNumber,tostring(nItemId),tostring(nNumber))
	end
	
	--是否是气力值奖励
	if nStrengthValue then
		User_AddStrengthValue(nStrengthValue)
		sItemName = string.format(tFestivalSpring2015_LanternFestival_Text["Average"],tostring(nStrengthValue))
		sLogContent = string.format(slogText,sRedGood,sRedNumber,tFestivalSpring2015_LanternFestival_Data["Strength_Values"],tostring(nStrengthValue))
	end
   
	--是否修行值奖励
	if nCultivation then
		User_AddCultivation(nCultivation)
		sItemName = string.format(tFestivalSpring2015_LanternFestival_Text["Cultivation"],nCultivation)
		sLogContent = string.format(slogText,sRedGood,sRedNumber,tFestivalSpring2015_LanternFestival_Data["Spiritual_Values"],tostring(nCultivation))
	end
	
	--玩家系统提示获得的物品  
	User_TalkChannel2005(string.format(tFestivalSpring2015_LanternFestival_Text["OverFlow"],sItemName))
	
	--第一名出现全服广播
	if nIndex == tFestivalSpring2015_LanternFestival_Data["Ranking"] then
		 Sys_TalkBroadcast(string.format(tFestivalSpring2015_LanternFestival_Text["Notifier"],Get_UserName(),sItemName))
	end
	User_EffectAdd("self","accession")
	Sys_SaveActionFestivalLog(sLogContent)
end

--超值提前2分钟广播(清空排名)
function FestivalSpring2015_LanternFestival_Notifi()
	if  Sys_ChkFullTime(tFestivalSpring2015_LanternFestival_Data["Now_Time"]) then
	
		--超值提前2分钟广播
		if Sys_ChkDayTime(tFestivalSpring2015_LanternFestival_Data["Seckill_Time"][4]) then
			Sys_TalkBroadcast(string.format(tFestivalSpring2015_LanternFestival_Text["Notification"],tFestivalSpring2015_LanternFestival_Data["Seckill_Get"][1]))
		elseif Sys_ChkDayTime(tFestivalSpring2015_LanternFestival_Data["Seckill_Time"][5]) then
			Sys_TalkBroadcast(string.format(tFestivalSpring2015_LanternFestival_Text["Notification"],tFestivalSpring2015_LanternFestival_Data["Seckill_Get"][2]))
		elseif  Sys_ChkDayTime(tFestivalSpring2015_LanternFestival_Data["Seckill_Time"][6]) then
			Sys_TalkBroadcast(string.format(tFestivalSpring2015_LanternFestival_Text["Notification"],tFestivalSpring2015_LanternFestival_Data["Seckill_Get"][3]))
		end
		
		--清空排名
		Sys_ResetAllSynaGlobalData(tFestivalSpring2015_LanternFestival_Data["Check_Rank"])
	end
end

--浪漫花语礼包
function FestivalSpring2015_LanternFestival_Flower(nIndex)
	if Item_ChkItem(tFestivalSpring2015_LanternFestival_Rewards["Overflow_Rewards"][3][2]["ItemId"],tFestivalSpring2015_LanternFestival_Data["Check_Monopoly"])  then
		Item_DelItem(tFestivalSpring2015_LanternFestival_Rewards["Overflow_Rewards"][3][2]["ItemId"],tFestivalSpring2015_LanternFestival_Data["Check_Monopoly"])

		local nItemId = tFestivalSpring2015_LanternFestival_Rewards["Overflow_Rewards"][nIndex]["ItemId"]
		local nFlag = tFestivalSpring2015_LanternFestival_Rewards["Overflow_Rewards"][nIndex]["Flag"]
		local nNumber = tFestivalSpring2015_LanternFestival_Rewards["Overflow_Rewards"][nIndex]["AddAmount"]
		local nMonopoly = tFestivalSpring2015_LanternFestival_Rewards["Overflow_Rewards"][nIndex]["Monopoly"] 
		local nTime_Limit = tFestivalSpring2015_LanternFestival_Rewards["Overflow_Rewards"][nIndex]["Time_Limit"]
		local nActive = tFestivalSpring2015_LanternFestival_Rewards["Overflow_Rewards"][nIndex]["Active"]
		local nReduce_Dmg =tFestivalSpring2015_LanternFestival_Rewards["Overflow_Rewards"][nIndex]["reduce_dmg"]

		Item_AddItem(nItemId,nFlag, nNumber,nMonopoly,nTime_Limit,nActive,0,0,nReduce_Dmg)
		User_TalkChannel2005(tFestivalSpring2015_LanternFestival_Text["Rose"])
		Sys_SaveActionFestivalLog(string.format(tFestivalSpring2015_LanternFestival_Log["RewardLog"],tFestivalSpring2015_LanternFestival_Log["Romance_GoodsLog"],tFestivalSpring2015_LanternFestival_Log["Romance_NumLog"],tostring(nItemid),tostring(nNumber)))
	end
end

-------------------------------------------对话模板部分-------------------------------------------
-- 元宵福利美眉
tNpcFace[3410] = 161
tNpcGossip[17425] = tNpcGossip[17425] or DefaultNpc:new{}
tNpcGossip[17425]["OptionHidden"] = 1

--活动前
tNpcGossip[17425]["Text1-1"] = {111,112,113,114}
tNpcGossip[17425]["Text111"] = tFestivalSpring2015_LanternFestival_Text[17425]["Text111"]
tNpcGossip[17425]["Text112"] = tFestivalSpring2015_LanternFestival_Text[17425]["Text112"]
tNpcGossip[17425]["Text113"] = tFestivalSpring2015_LanternFestival_Text[17425]["Text113"]
tNpcGossip[17425]["Text114"] = tFestivalSpring2015_LanternFestival_Text[17425]["Text114"]
tNpcGossip[17425]["tOption1-1"] = {1}
tNpcGossip[17425]["Option1"] = tFestivalSpring2015_LanternFestival_Text[17425]["Option11"]
tNpcGossip[17425]["ChkFunc1-1"] = function ()
	return Sys_ChkFullTime(tFestivalSpring2015_LanternFestival_Data["Bef_Time"])
end

-- 活动中
tNpcGossip[17425]["Text1-2"] = {121,122,123}
tNpcGossip[17425]["Text121"] = tFestivalSpring2015_LanternFestival_Text[17425]["Text131"] 
tNpcGossip[17425]["Text122"] = tFestivalSpring2015_LanternFestival_Text[17425]["Text132"]
tNpcGossip[17425]["Text123"] = tFestivalSpring2015_LanternFestival_Text[17425]["Text133"]

tNpcGossip[17425]["Option3"] = tFestivalSpring2015_LanternFestival_Text[17425]["Option131"]
tNpcGossip[17425]["Option4"] = tFestivalSpring2015_LanternFestival_Text[17425]["Option132"]
tNpcGossip[17425]["Option9"] = tFestivalSpring2015_LanternFestival_Text[17425]["Option133"]
tNpcGossip[17425]["Option10"] = tFestivalSpring2015_LanternFestival_Text[17425]["Option134"]

tNpcGossip[17425]["tOption1-2"] = {3,9,10,4}
tNpcGossip[17425]["ChkFunc1-2"] = function ()
	return Sys_ChkFullTime(tFestivalSpring2015_LanternFestival_Data["Now_Time"])
end

tNpcGossip[17425]["OptionFunc3"]="FestivalSpring2015_LanternFestival_Option3</N>17425"
tNpcGossip[17425]["OptionFunc9"]="LinkNpcGossipFunc_New</N>17425</S>3-4"
tNpcGossip[17425]["OptionFunc10"]="LinkNpcGossipFunc_New</N>17425</S>3-5"

-- 活动后
tNpcGossip[17425]["Text1-3"] = {131,132}
tNpcGossip[17425]["Text131"] = tFestivalSpring2015_LanternFestival_Text[17425]["Text121"] 
tNpcGossip[17425]["Text132"] = tFestivalSpring2015_LanternFestival_Text[17425]["Text122"]

tNpcGossip[17425]["Option2"] = tFestivalSpring2015_LanternFestival_Text[17425]["Option12"]
tNpcGossip[17425]["tOption1-3"] = {2}

--活动中规则说明 超值大奖是什么?
tNpcGossip[17425]["Text3-4"] = {341,342,343}
tNpcGossip[17425]["Text341"] = tFestivalSpring2015_LanternFestival_Text[17425]["Text141"] 
tNpcGossip[17425]["Text342"] = tFestivalSpring2015_LanternFestival_Text[17425]["Text142"]
tNpcGossip[17425]["Text343"] = tFestivalSpring2015_LanternFestival_Text[17425]["Text143"]

tNpcGossip[17425]["Option11"] = tFestivalSpring2015_LanternFestival_Text[17425]["Option135"]
tNpcGossip[17425]["Option12"] = tFestivalSpring2015_LanternFestival_Text[17425]["Option132"]
tNpcGossip[17425]["tOption3-4"] = {11,12}

tNpcGossip[17425]["OptionFunc11"]="LinkNpcGossipFunc_New</N>17425</S>1-2"

--秒杀规则
tNpcGossip[17425]["Text3-5"] = {351,352,353}
tNpcGossip[17425]["Text351"] = tFestivalSpring2015_LanternFestival_Text[17425]["Text151"] 
tNpcGossip[17425]["Text352"] = tFestivalSpring2015_LanternFestival_Text[17425]["Text152"]
tNpcGossip[17425]["Text353"] = tFestivalSpring2015_LanternFestival_Text[17425]["Text153"]

tNpcGossip[17425]["tOption3-5"] = {11,12}

--不在整点30分钟之内
tNpcGossip[17425]["Text2-4"] = {314}
tNpcGossip[17425]["Text314"] = tFestivalSpring2015_LanternFestival_Text[17425]["Text314"] 
tNpcGossip[17425]["Option5"] = tFestivalSpring2015_LanternFestival_Text[17425]["Option314"]
tNpcGossip[17425]["tOption2-4"] = {5}

--等级不足
tNpcGossip[17425]["Text2-5"] = {315}
tNpcGossip[17425]["Text315"] = tFestivalSpring2015_LanternFestival_Text[17425]["Text311"] 
tNpcGossip[17425]["Option6"] = tFestivalSpring2015_LanternFestival_Text[17425]["Option311"]
tNpcGossip[17425]["tOption2-5"] = {6}

--背包已满
tNpcGossip[17425]["Text2-6"] = {316}
tNpcGossip[17425]["Text316"] = tFestivalSpring2015_LanternFestival_Text["NotifiBag"]
tNpcGossip[17425]["Option7"] = tFestivalSpring2015_LanternFestival_Text[17425]["Option312"]
tNpcGossip[17425]["tOption2-6"] = {7}

--已领取过
tNpcGossip[17425]["Text2-7"] = {317}
tNpcGossip[17425]["Text317"] = tFestivalSpring2015_LanternFestival_Text[17425]["Text313"] 
tNpcGossip[17425]["Option8"] = tFestivalSpring2015_LanternFestival_Text[17425]["Option313"]
tNpcGossip[17425]["tOption2-7"] = {8}

-------------------------------------------------------物品模块-------------------------------------------------------------
-- 秒杀卷
tItem[3005537] = tItem[3005537] or {}
tItem[3005537]["Function"] = function(nItemId,sItemName)
	FestivalSpring2015_LanternFestival_UseItemBox(nItemId)
end

--浪漫花语武器外套礼包
tItem[3005571] = tItem[3005571] or {}
tItem[3005571]["Text1-1"] = {111}
tItem[3005571]["Text111"] = tFestivalSpring2015_LanternFestival_Text["RewardBag"] 
tItem[3005571]["ChkFunc1-1"] = function () return true end
tItem[3005571]["Option1"] = tFestivalSpring2015_LanternFestival_Text["ShortReward"]
tItem[3005571]["Option2"] = tFestivalSpring2015_LanternFestival_Text["LongReward"]
tItem[3005571]["Option3"] = tFestivalSpring2015_LanternFestival_Text["Think"]
tItem[3005571]["tOption1-1"] = {1,2,3}
tItem[3005571]["OptionFunc1"]="FestivalSpring2015_LanternFestival_Flower</N>5"
tItem[3005571]["OptionFunc2"]="FestivalSpring2015_LanternFestival_Flower</N>6"

--时间函数触发
--'11:58 18:58 20:58'
--tOntimerMin_HM[1158] = tOntimerMin_HM[1158] or {}
--table.insert(tOntimerMin_HM[1158],FestivalSpring2015_LanternFestival_Notifi)
--tOntimerMin_HM[1858] = tOntimerMin_HM[1858] or {}
--table.insert(tOntimerMin_HM[1858],FestivalSpring2015_LanternFestival_Notifi)
--tOntimerMin_HM[2058] = tOntimerMin_HM[2058] or {}
--table.insert(tOntimerMin_HM[2058],FestivalSpring2015_LanternFestival_Notifi)