------------------------------------------------------------------------------------
--Name:		[征服][活动脚本]情人节活动之神父的祝福
--Purpose:	情人节活动之神父的祝福
--Creator: 	严振飞
--Created:	2014/11/07
------------------------------------------------------------------------------------
--[[
任务需求：
******************************************************************
*王语萱(任务部剧情策划处)在2014-11-05 10:58修改任务(任务号：5067324)时补充了如下需求：
******************************************************************
1、4天活动时间，6个活动。
2、任务说明及设计：
神父的祝福（总NPC）--wyx（1）
同心锁、比翼双飞鸟、甜蜜约会之非诚勿扰--hyx（3）
美女与野兽--xyn（1）
共修玉女剑--yjl（1）
******************************************************************
*王语萱(任务部剧情策划处)在2014-11-05 14:47修改任务(任务号：5067324)时补充了如下需求：
******************************************************************
细化案中的“爱情玫瑰换取外套”从6朵玫瑰换武器外套和8朵玫瑰换时装修改成6朵玫瑰换武器外套和6朵玫瑰换时装，就是时装的8朵玫瑰换成跟武器套一样的6朵了 
]]--
------------------------------------------------------------------------------------
--掩码说明
---stc(131,75) 记录【上线给长梗玫瑰】
---stc(131,76) 记录【长梗玫瑰祝福】和【长梗玫瑰节日礼包】
---stc(131,78) 记录【签到祝福】和【全活动完成节日礼包】
---stc(131,79) 记录【送上长梗玫瑰】完成

--LOGid 10002397
------------------------------------------------------------------------------------
--命名规范
--ValentinesDay2015_Priest_
------------------------------------------------------------------------------------
--STC掩码表
local tValentinesDay2015_Priest_Stc = {}
----------------------------------------
--情人节其他活动掩码表
--stc(131,59)--比翼双飞。
	tValentinesDay2015_Priest_Stc[1] = {}
	tValentinesDay2015_Priest_Stc[1]["Event"] = 131
	tValentinesDay2015_Priest_Stc[1]["Type"] = 59
	tValentinesDay2015_Priest_Stc[1]["Finish"] = 300
--stc(131,46)--美女与野兽。
	tValentinesDay2015_Priest_Stc[2] = {}
	tValentinesDay2015_Priest_Stc[2]["Event"] = 131
	tValentinesDay2015_Priest_Stc[2]["Type"] = 46
	tValentinesDay2015_Priest_Stc[2]["Finish"] = 4
--stc(131,53)--悬挂同心锁。
	tValentinesDay2015_Priest_Stc[3] = {}
	tValentinesDay2015_Priest_Stc[3]["Event"] = 131
	tValentinesDay2015_Priest_Stc[3]["Type"] = 53
	tValentinesDay2015_Priest_Stc[3]["Finish"] = 20
--stc(131,22)--眉来眼去传真情。
	tValentinesDay2015_Priest_Stc[4] = {}
	tValentinesDay2015_Priest_Stc[4]["Event"] = 131
	tValentinesDay2015_Priest_Stc[4]["Type"] = 22
	tValentinesDay2015_Priest_Stc[4]["Finish"] = 5
--stc(131,80)--甜蜜约会之非诚勿扰。
	tValentinesDay2015_Priest_Stc[5] = {}
	tValentinesDay2015_Priest_Stc[5]["Event"] = 131
	tValentinesDay2015_Priest_Stc[5]["Type"] = 80
	tValentinesDay2015_Priest_Stc[5]["Finish"] = 2


----------------------------------------
--神父的祝福掩码表
---stc(131,76) 记录【长梗玫瑰祝福】和【长梗玫瑰节日礼包】
	tValentinesDay2015_Priest_Stc[11] = {}
	tValentinesDay2015_Priest_Stc[11]["Event"] = 131
	tValentinesDay2015_Priest_Stc[11]["Type"] = 76
	--不同祝福掩码存储位置
	tValentinesDay2015_Priest_Stc[11]["Place"] = {}
	tValentinesDay2015_Priest_Stc[11]["Place"][1] = 1 --【长梗玫瑰祝福】
	tValentinesDay2015_Priest_Stc[11]["Place"][2] = 10 --【长梗玫瑰节日礼包】


--stc(131,78) 记录【签到祝福】和【全活动完成节日礼包】
	tValentinesDay2015_Priest_Stc[12] = {}
	tValentinesDay2015_Priest_Stc[12]["Event"] = 131
	tValentinesDay2015_Priest_Stc[12]["Type"] = 78
	--不同奖励掩码存储位置
	tValentinesDay2015_Priest_Stc[12]["Place"] = {}
	tValentinesDay2015_Priest_Stc[12]["Place"][1] = 1 --【签到祝福】
	tValentinesDay2015_Priest_Stc[12]["Place"][2] = 10 --【全活动完成节日礼包】


--stc(131,79) 记录【送上长梗玫瑰】完成
	tValentinesDay2015_Priest_Stc[13] = {}
	tValentinesDay2015_Priest_Stc[13]["Event"] = 131
	tValentinesDay2015_Priest_Stc[13]["Type"] = 79
	tValentinesDay2015_Priest_Stc[13]["Finish"] = 111111
	--各活动掩码存储位置
	tValentinesDay2015_Priest_Stc[13]["Place"] = {}
	tValentinesDay2015_Priest_Stc[13]["Place"][1] = 1 --苏巧儿
	tValentinesDay2015_Priest_Stc[13]["Place"][2] = 10 --美女贝儿
	tValentinesDay2015_Priest_Stc[13]["Place"][3] = 100 --红娘娇燕燕
	tValentinesDay2015_Priest_Stc[13]["Place"][4] = 1000 --药师师兄
	tValentinesDay2015_Priest_Stc[13]["Place"][5] = 10000 --素秋师妹
	tValentinesDay2015_Priest_Stc[13]["Place"][6] = 100000 --男媒婆姚大痣


------------------------------------------------------------------------------------
--情人节其他活动NPC数据表
local tValentinesDay2015_Priest_Npc = {}

	--比翼双飞--NPC信息
	tValentinesDay2015_Priest_Npc[1] = {}
	tValentinesDay2015_Priest_Npc[1]["Npc_NpcId"] = 17302
	tValentinesDay2015_Priest_Npc[1]["Npc_MapId"] = 1002
	tValentinesDay2015_Priest_Npc[1]["Npc_PosX"] = 286
	tValentinesDay2015_Priest_Npc[1]["Npc_PosY"] = 385

	--美女与野兽--NPC信息
	tValentinesDay2015_Priest_Npc[2] = {}
	tValentinesDay2015_Priest_Npc[2]["Npc_NpcId"] = 17287
	tValentinesDay2015_Priest_Npc[2]["Npc_MapId"] = 1002
	tValentinesDay2015_Priest_Npc[2]["Npc_PosX"] = 298
	tValentinesDay2015_Priest_Npc[2]["Npc_PosY"] = 359

	--悬挂同心锁--NPC信息
	tValentinesDay2015_Priest_Npc[3] = {}
	tValentinesDay2015_Priest_Npc[3]["Npc_NpcId"] = 17276 
	tValentinesDay2015_Priest_Npc[3]["Npc_MapId"] = 1002
	tValentinesDay2015_Priest_Npc[3]["Npc_PosX"] = 298
	tValentinesDay2015_Priest_Npc[3]["Npc_PosY"] = 385

	--眉来眼去传真情--NPC信息
	tValentinesDay2015_Priest_Npc[4] = {}
	-----男角色
	tValentinesDay2015_Priest_Npc[4][1] = {}
	tValentinesDay2015_Priest_Npc[4][1]["Npc_NpcId"]= 10079
	tValentinesDay2015_Priest_Npc[4][1]["Npc_MapId"] = 1002
	tValentinesDay2015_Priest_Npc[4][1]["Npc_PosX"] = 287
	tValentinesDay2015_Priest_Npc[4][1]["Npc_PosY"] = 359
	-----女角色
	tValentinesDay2015_Priest_Npc[4][2] = {}
	tValentinesDay2015_Priest_Npc[4][2]["Npc_NpcId"]= 10078
	tValentinesDay2015_Priest_Npc[4][2]["Npc_MapId"] = 1002
	tValentinesDay2015_Priest_Npc[4][2]["Npc_PosX"] = 284
	tValentinesDay2015_Priest_Npc[4][2]["Npc_PosY"] = 359
	
	--甜蜜约会之非诚勿扰--NPC信息
	tValentinesDay2015_Priest_Npc[6] = {}
	tValentinesDay2015_Priest_Npc[6]["Npc_NpcId"] = 17321 
	tValentinesDay2015_Priest_Npc[6]["Npc_MapId"] = 1002
	tValentinesDay2015_Priest_Npc[6]["Npc_PosX"] = 274
	tValentinesDay2015_Priest_Npc[6]["Npc_PosY"] = 385

	--神父的祝福
	tValentinesDay2015_Priest_Npc[7] = {}
	tValentinesDay2015_Priest_Npc[7]["Npc_NpcId"] = 17285 
	tValentinesDay2015_Priest_Npc[7]["Npc_MapId"] = 1002
	tValentinesDay2015_Priest_Npc[7]["Npc_PosX"] = 292
	tValentinesDay2015_Priest_Npc[7]["Npc_PosY"] = 369

------------------------------------------------------------------------------------
--活动数据
local tValentinesDay2015_Priest_Data = {}
	--活动时间
	tValentinesDay2015_Priest_Data["Festival_BefTime"] = "2014-01-01 00:00 2015-02-10 23:59"
	tValentinesDay2015_Priest_Data["Festival_NowTime"] = "2015-02-11 00:00 2015-02-14 23:59"
	--活动物品
	tValentinesDay2015_Priest_Data["Item_LoveRose"] = 3005410
	tValentinesDay2015_Priest_Data["Item_LongRose"] = 3005411
	--上线给长梗玫瑰数
	tValentinesDay2015_Priest_Data["LongRose_Num"] = 6
	--等级，转世设置
	tValentinesDay2015_Priest_Data["MinLevel"] = 80
	tValentinesDay2015_Priest_Data["MinMeto"] = 1
	--背包空间
	tValentinesDay2015_Priest_Data["ChkSpace"] = 1
	--祝福奖励时间
	tValentinesDay2015_Priest_Data["AddBlessTime"] = {}
	tValentinesDay2015_Priest_Data["AddBlessTime"][11] = 24 --长梗玫瑰使用1天
	tValentinesDay2015_Priest_Data["AddBlessTime"][12] = 3 --签到3小时
	--领取祝福光效
	tValentinesDay2015_Priest_Data["Effect"] = {}
		--长梗玫瑰祝福
	tValentinesDay2015_Priest_Data["Effect"][11] = "red-flower-charm1"
		--签到祝福
	tValentinesDay2015_Priest_Data["Effect"][12] = "red-flower-charm3"
	tValentinesDay2015_Priest_Data["EffectObj"] = "self"
	--送长梗玫瑰给NPC光效
	tValentinesDay2015_Priest_Data["MapEffect"] = "red-flower-charm2"
	--通用礼包ID
	tValentinesDay2015_Priest_Data["GeneralPagId"] = 3353
	tValentinesDay2015_Priest_Data["LogId"] = 10002397


------------------------------------------------------------------------------------
--换取时装数据表
local tValentinesDay2015_Priest_Garment = {}
	--换取--3小时玫瑰风暴武器外套礼盒
	tValentinesDay2015_Priest_Garment[1] = {}
	tValentinesDay2015_Priest_Garment[1]["Garment"] = 3005577
	tValentinesDay2015_Priest_Garment[1]["Garment_SaveTime"] = 0
	tValentinesDay2015_Priest_Garment[1]["RoseNum"] = 5
	tValentinesDay2015_Priest_Garment[1]["Garment_Reducedmg"] = 0
	
	--换取--3小时神佑1%情人之泪外套
	tValentinesDay2015_Priest_Garment[2] = {}
	tValentinesDay2015_Priest_Garment[2]["Garment"] = 192565
	tValentinesDay2015_Priest_Garment[2]["Garment_SaveTime"] = 180
	tValentinesDay2015_Priest_Garment[2]["RoseNum"] = 5
	tValentinesDay2015_Priest_Garment[2]["Garment_Reducedmg"] = 1

	--换取--3小时神佑1%玫瑰风暴武器外套（短武器）
	tValentinesDay2015_Priest_Garment[3] = {}
	tValentinesDay2015_Priest_Garment[3]["Garment"] = 360149
	tValentinesDay2015_Priest_Garment[3]["Garment_SaveTime"] = 180
	tValentinesDay2015_Priest_Garment[3]["Garment_Reducedmg"] = 1

	--换取--3小时神佑1%玫瑰风暴武器外套（长武器）
	tValentinesDay2015_Priest_Garment[4] = {}
	tValentinesDay2015_Priest_Garment[4]["Garment"] = 350079
	tValentinesDay2015_Priest_Garment[4]["Garment_SaveTime"] = 180
	tValentinesDay2015_Priest_Garment[4]["Garment_Reducedmg"] = 1

------------------------------------------------------------------------------------
--活动LOG数据表
local tValentinesDay2015_Priest_Log = {}
	--长梗玫瑰
	tValentinesDay2015_Priest_Log["Get_LongRose"] = "0,0,0,0,10002397,2,3005411,6"
	tValentinesDay2015_Priest_Log["Del_LongRose"] = "0,0,3005411,1,10002397,2,0,0"

	--爱情玫瑰换取外套
	tValentinesDay2015_Priest_Log["Garment"] = {}
	tValentinesDay2015_Priest_Log["Garment"][1] = "0,0,3005410,5,10002397,2,3005577,1"
	tValentinesDay2015_Priest_Log["Garment"][2] = "0,0,3005410,5,10002397,2,192565,1"
	--礼盒换外套
	tValentinesDay2015_Priest_Log["Garment"][3] = "0,0,3005577,1,10002397,2,360149,1"
	tValentinesDay2015_Priest_Log["Garment"][4] = "0,0,3005577,1,10002397,2,350079,1"
	--获得祝福
	tValentinesDay2015_Priest_Log["Get_AddBless"] = {}
	tValentinesDay2015_Priest_Log["Get_AddBless"][11] = "0,0,0,0,10002397,2,5,24"
	tValentinesDay2015_Priest_Log["Get_AddBless"][12] = "0,0,0,0,10002397,2,5,3"


------------------------------------------逻辑部分-------------------------------------------
--- 活动时间判断函数
function ValentinesDay2015_Priest_FestivalTime(sPhase)

	--判断是否活动前
	if sPhase == "Before" then
		if Sys_ChkFullTime(tValentinesDay2015_Priest_Data["Festival_BefTime"]) then
			return true
		else
			return false
		end

	--判断是否活动期间
	elseif sPhase == "Now" then
		if Sys_ChkFullTime(tValentinesDay2015_Priest_Data["Festival_NowTime"]) then
			return true
		else
			return false
		end
	end
end


-----------------------------------------
--- 玩家等级判断函数
function ValentinesDay2015_Priest_PlayerLev()
	local nMetempsychosis = Get_UserMetempsychosis()
	local nUserLev = Get_UserLevel()
	if nMetempsychosis < tValentinesDay2015_Priest_Data["MinMeto"] then
		--等级是否为80级（含）以上
		if nUserLev < tValentinesDay2015_Priest_Data["MinLevel"] then
			return true
		else
			return false
		end 
	end
end

------------------------------------------
--- 单用STC掩码逻辑
function ValentinesDay2015_Priest_ChkStc(nStcNum)
--//函数返回true表示出相应对白
--//函数返回false表示不出相应对白
	local nEvent = tValentinesDay2015_Priest_Stc[nStcNum]["Event"]
	local nType = tValentinesDay2015_Priest_Stc[nStcNum]["Type"]
	local nFinish = tValentinesDay2015_Priest_Stc[nStcNum]["Finish"]
	
	--判断是否已完成任务
	if not Task_ChkStcValue(nEvent,nType,"==",nFinish) then
		return false
	end
	
	--判断是否隔天
	if Task_StcInterval(nEvent,nType,1,4) then
			Task_SetStatistic(nEvent,nType,0,1)
			Task_SetStcTimestamp(nEvent,nType,0)
		return false
	end
	
	return true
end

------------------------------------------
--- 多用STC掩码判断
function ValentinesDay2015_Priest_MultiStc(nStcNum,nPlaceNum)
	local nEvent = tValentinesDay2015_Priest_Stc[nStcNum]["Event"]
	local nType = tValentinesDay2015_Priest_Stc[nStcNum]["Type"]
	local nStcValue = Get_UserStatisticValue(nEvent,nType)
	local nMathValue = math.floor(nStcValue / tValentinesDay2015_Priest_Stc[nStcNum]["Place"][nPlaceNum]) % 10
	
	--是否完成
	if nMathValue == 0 then
		return true
	
	--nStcNum == 12，为领取全活动完成活动，隔天需重置
	--nStcNum == 11或13，为长梗玫瑰活动，无需隔天重置
	elseif nStcNum == 12 then
		if Task_StcInterval(nEvent,nType,1,4) then
			Task_SetStatistic(nEvent,nType,0,1)
			Task_SetStcTimestamp(nEvent,nType,0)
			return true
		else
			return false
		end
	else
		return false
	end
end


------------------------------------------
---自动寻路逻辑
function ValentinesDay2015_Priest_FindNpc(nNpcNum,nType)
	local nNpcId = tValentinesDay2015_Priest_Npc[nNpcNum]["Npc_NpcId"]
	local nMapId = tValentinesDay2015_Priest_Npc[nNpcNum]["Npc_MapId"]
	local nPosX = tValentinesDay2015_Priest_Npc[nNpcNum]["Npc_PosX"]
	local nPosY = tValentinesDay2015_Priest_Npc[nNpcNum]["Npc_PosY"]
	
	--眉来眼去传真情NPC寻路(有男女之分)
	if nNpcNum == 4 then
		local nSex = Get_UserSex()
		
		--是否为长梗玫瑰寻路
		if nType ~= 0 then
			nSex = nType
		end
		nNpcId = tValentinesDay2015_Priest_Npc[nNpcNum][nSex]["Npc_NpcId"]
		nMapId = tValentinesDay2015_Priest_Npc[nNpcNum][nSex]["Npc_MapId"]
		nPosX = tValentinesDay2015_Priest_Npc[nNpcNum][nSex]["Npc_PosX"]
		nPosY = tValentinesDay2015_Priest_Npc[nNpcNum][nSex]["Npc_PosY"]
	end
	
	Sys_GotoSomeWhere(nPosX,nPosY,nMapId,nNpcId)
end


------------------------------------------
--- 全活动完成逻辑
function ValentinesDay2015_Priest_AllFinish()
	for nStcNum=1,5 do
		local nEvent = tValentinesDay2015_Priest_Stc[nStcNum]["Event"]
		local nType = tValentinesDay2015_Priest_Stc[nStcNum]["Type"]
		local nFinish = tValentinesDay2015_Priest_Stc[nStcNum]["Finish"]
		
		--判断各个活动是否完成
		if not Task_ChkStcValue(nEvent,nType,"==",nFinish) then
			return true
		end
		
		--判断是否隔天
		if Task_StcInterval(nEvent,nType,1,4) then
				Task_SetStatistic(nEvent,nType,0,1)
				Task_SetStcTimestamp(nEvent,nType,0)
			return true
		end
	end
	return false
end


------------------------------------------
-- 获得奖励逻辑
function ValentinesDay2015_Priest_GetAward(nStcNum,nPlaceNum)
	local nEvent = tValentinesDay2015_Priest_Stc[nStcNum]["Event"]
	local nType = tValentinesDay2015_Priest_Stc[nStcNum]["Type"]
	local nAddValue = tValentinesDay2015_Priest_Stc[nStcNum]["Place"][nPlaceNum]
	
	--删除多余长梗玫瑰
	if nStcNum == 11 then
		if Item_ChkItem(tValentinesDay2015_Priest_Data["Item_LongRose"]) then
			Item_DelAllItemByType(tValentinesDay2015_Priest_Data["Item_LongRose"])
		end
	end
	
	--领取祝福奖励
	if nPlaceNum == 1 then
		Task_AddStatistic(nEvent,nType,nAddValue,0)
		Task_SetStcTimestamp(nEvent,nType,0)
		User_AddBless(tValentinesDay2015_Priest_Data["AddBlessTime"][nStcNum])
		User_EffectAdd(tValentinesDay2015_Priest_Data["EffectObj"],tValentinesDay2015_Priest_Data["Effect"][nStcNum])
		Sys_SaveActionFestivalLog(tValentinesDay2015_Priest_Log["Get_AddBless"][nStcNum])
		User_TalkChannel2005(tValentinesDay2015_Priest_Text["AddBless_SysTip"][nStcNum])
		
	--领取节日礼包
	elseif nPlaceNum == 2 then
		Task_AddStatistic(nEvent,nType,nAddValue,0)
		Task_SetStcTimestamp(nEvent,nType,0)
		FestivalGeneralPackage_GetGift(tValentinesDay2015_Priest_Data["GeneralPagId"],tValentinesDay2015_Priest_Data["LogId"])
	end
	
	return true
end


------------------------------------------
--- 其他活动NPC的【送上长梗玫瑰。】选项
function ValentinesDay2015_Priest_LongRose(nPlaceNum)
	local nEvent = tValentinesDay2015_Priest_Stc[13]["Event"]
	local nType = tValentinesDay2015_Priest_Stc[13]["Type"]
	local nMapId = tValentinesDay2015_Priest_Npc[nPlaceNum]["Npc_MapId"]
	local nPosX = tValentinesDay2015_Priest_Npc[nPlaceNum]["Npc_PosX"]
	local nPosY = tValentinesDay2015_Priest_Npc[nPlaceNum]["Npc_PosY"]
	local sEffect = tValentinesDay2015_Priest_Data["MapEffect"]
	local nItemId = tValentinesDay2015_Priest_Data["Item_LongRose"]
	
	--删除长梗玫瑰-置掩码
	if Item_ChkItem(nItemId) and Item_DelItem(nItemId) then
		Task_AddStatistic(nEvent,nType,tValentinesDay2015_Priest_Stc[13]["Place"][nPlaceNum],0)
		Task_SetStcTimestamp(nEvent,nType,0)
		Map_Effect(nMapId,nPosX,nPosY,sEffect)
		Sys_SaveActionFestivalLog(tValentinesDay2015_Priest_Log["Del_LongRose"])
	end
	
	--送完6朵出提示
	if not ValentinesDay2015_Priest_LongRoseFinish() then
		Sys_MsgBox(tValentinesDay2015_Priest_Text["Flower_Finish"],"ValentinesDay2015_Priest_FindNpc</N>7</N>0")
	end
	
	return true
end


------------------------------------------
--长梗玫瑰是否送完6朵
function ValentinesDay2015_Priest_LongRoseFinish()
	local nEvent = tValentinesDay2015_Priest_Stc[13]["Event"]
	local nType = tValentinesDay2015_Priest_Stc[13]["Type"]
	local nTemp = Get_UserStatisticValue(tValentinesDay2015_Priest_Stc[13]["Event"],tValentinesDay2015_Priest_Stc[13]["Type"])

	--送完6朵长梗玫瑰
	if nTemp == tValentinesDay2015_Priest_Stc[13]["Finish"] then
		return false
	else
		--未送完
		return true
	end
end


------------------------------------------
---换取时装逻辑
function ValentinesDay2015_Priest_GetGarment(nItemNum,nTextNum)

	--nTextNum用来区别对话判断函数
	--nTextNum == 4 表示对白中第4段对白的判断
	--nTextNum == 5 表示对白中第5段对白的判断
	local nRoseId = tValentinesDay2015_Priest_Data["Item_LoveRose"]
	local nRoseNum = tValentinesDay2015_Priest_Garment[nItemNum]["RoseNum"]
	if nTextNum == 4 then
		
		--判断是否有5个爱情梗玫瑰
		if Item_ChkMulItem(nRoseId,nRoseId,nRoseNum) then
			return false
		else
			return true
		end
		
	elseif nTextNum == 5 then
		local nItemId = tValentinesDay2015_Priest_Garment[nItemNum]["Garment"]
		local nSaveTime = tValentinesDay2015_Priest_Garment[nItemNum]["Garment_SaveTime"]
		local nReducedmg = tValentinesDay2015_Priest_Garment[nItemNum]["Garment_Reducedmg"]
		
		--删除爱情玫瑰--获得外套奖励
		if Item_ChkMulItem(nRoseId,nRoseId,nRoseNum) and Item_DelMulItem(nRoseId,nRoseId,nRoseNum) then
			Item_AddItem(nItemId,0,0,0,nSaveTime,0,0,0,nReducedmg)
			Sys_SaveActionFestivalLog(tValentinesDay2015_Priest_Log["Garment"][nItemNum])
			return true
		end
	end
end


------------------------------------------
---上线触发函数
function ValentinesDay2015_Priest_Login()

	--活动时间
	if not ValentinesDay2015_Priest_FestivalTime("Now") then

		--删除礼包
		if Item_ChkItem(tValentinesDay2015_Priest_Data["Item_LongRose"]) then
			Item_DelAllItemByType(tValentinesDay2015_Priest_Data["Item_LongRose"])
			User_TalkChannel2005(tValentinesDay2015_Priest_Text["Del_LongRose"])
		end
		return
	end
	
	--是否已完成长梗玫瑰任务
	if not ValentinesDay2015_Priest_MultiStc(11,2) then
		return
	end
	
	--背包内是否有长梗玫瑰
	if Item_ChkItem(tValentinesDay2015_Priest_Data["Item_LongRose"]) then
		return
	end
	
	--判断背包空间
	if not User_CheckLeftSpace(tValentinesDay2015_Priest_Data["ChkSpace"]) then
		User_TalkChannel2005(tValentinesDay2015_Priest_Text["Login_BagFull"])
		return
	end
	
	--判断玩家等级转世
	if ValentinesDay2015_Priest_PlayerLev() then 
		return
	end
	
	--获得长梗玫瑰
	Item_AddItem(tValentinesDay2015_Priest_Data["Item_LongRose"],0,tValentinesDay2015_Priest_Data["LongRose_Num"])
	Sys_SaveActionFestivalLog(tValentinesDay2015_Priest_Log["Get_LongRose"])
	User_TalkChannel2005(tValentinesDay2015_Priest_Text["Login_Success"])
end


------------------------------------------物品逻辑-------------------------------------------
-- //长梗玫瑰接入逻辑
function ValentinesDay2015_Priest_LongRoseMain()
	if not Sys_ChkFullTime(tValentinesDay2015_Priest_Data["Festival_NowTime"]) then

		--活动时间外删除全部同类物品
		if Item_ChkItem(tValentinesDay2015_Priest_Data["Item_LongRose"]) then
			Item_DelAllItemByType(tValentinesDay2015_Priest_Data["Item_LongRose"])
			User_TalkChannel2005(tValentinesDay2015_Priest_Text["Del_LongRose"])
		end
		return
	end

	--出对白
	LinkItemMain()
end


-- //3小时玫瑰风暴武器外套礼盒
function ValentinesDay2015_Priest_ChgCoat(nItemNum)
	local nGiftBox = tValentinesDay2015_Priest_Garment[1]["Garment"]
	local nItemId = tValentinesDay2015_Priest_Garment[nItemNum]["Garment"]
	local nSaveTime = tValentinesDay2015_Priest_Garment[nItemNum]["Garment_SaveTime"]
	local nReducedmg = tValentinesDay2015_Priest_Garment[nItemNum]["Garment_Reducedmg"]
		
	--删除礼盒--获得外套奖励
	if Item_ChkItem(nGiftBox) and Item_DelItem(nGiftBox) then
		Item_AddItem(nItemId,0,0,0,nSaveTime,0,0,0,nReducedmg)
		Sys_SaveActionFestivalLog(tValentinesDay2015_Priest_Log["Garment"][nItemNum])
		User_TalkChannel2005(tValentinesDay2015_Priest_ItemText["ChgCoat_Success"][nItemNum])
	end
end


------------------------------------------其他活动逻辑-------------------------------------------
-- //美女贝儿 -《美女与野兽》
function ValentinesDay2015_beauty_LongRose()
	LinkNpcGossipFunc_New(17287,"40")
end


------------------------------------------物品配置-------------------------------------------
 --爱情玫瑰
tItem[3005410] = tItem[3005410] or {}
tItem[3005410]["Function"] = function (nItemId,sItemName)
	if not Sys_ChkFullTime(tValentinesDay2015_Priest_Data["Festival_NowTime"]) then
	
		--活动时间外删除全部同类物品
		if Item_ChkItem(tValentinesDay2015_Priest_Data["Item_LoveRose"]) then
			Item_DelAllItemByType(tValentinesDay2015_Priest_Data["Item_LoveRose"])
			User_TalkChannel2005(tValentinesDay2015_Priest_Text["Del_LoveRose"])
		end
		return
	end
	
	User_TalkChannel2005(tValentinesDay2015_Priest_Text["Item_LoveRose"])
end


------------------------------------------物品对话配置-------------------------------------------
--长梗玫瑰
tItem[3005411] = tItem[3005411] or {}

tItem[3005411]["Text1-1"] = {111}
tItem[3005411]["Text111"] = tValentinesDay2015_Priest_ItemText[3005411]["Text111"]
tItem[3005411]["tOption1-1"] = {11,12}
tItem[3005411]["Option11"] = tValentinesDay2015_Priest_ItemText[3005411]["Option11"]
tItem[3005411]["OptionFunc11"] = "ValentinesDay2015_Priest_FindNpc</N>7</N>0"
tItem[3005411]["Option12"] = tValentinesDay2015_Priest_ItemText[3005411]["Option12"]


------------------------------------------
--3小时玫瑰风暴武器外套礼盒
tItem[3005577] = tItem[3005577] or {}

tItem[3005577]["Text1-1"] = {111}
tItem[3005577]["Text111"] = tValentinesDay2015_Priest_ItemText[3005577]["Text111"]
tItem[3005577]["tOption1-1"] = {11,12}
tItem[3005577]["Option11"] = tValentinesDay2015_Priest_ItemText[3005577]["Option11"]
tItem[3005577]["OptionPoint11"] = "2"
tItem[3005577]["Option12"] = tValentinesDay2015_Priest_ItemText[3005577]["Option12"]
tItem[3005577]["OptionPoint12"] = "3"

--【玫瑰风暴（短武器）。】
tItem[3005577]["Text2-1"] = {211}
tItem[3005577]["Text211"] = tValentinesDay2015_Priest_ItemText[3005577]["Text211"]
tItem[3005577]["tOption2-1"] = {21,22}
tItem[3005577]["Option21"] = tValentinesDay2015_Priest_ItemText[3005577]["Option21"]
tItem[3005577]["OptionFunc21"] = "ValentinesDay2015_Priest_ChgCoat</N>3"
tItem[3005577]["Option22"] = tValentinesDay2015_Priest_ItemText[3005577]["Option22"]

--【玫瑰风暴（长武器）。】
tItem[3005577]["Text3-1"] = {311}
tItem[3005577]["Text311"] = tValentinesDay2015_Priest_ItemText[3005577]["Text311"]
tItem[3005577]["tOption3-1"] = {31,32}
tItem[3005577]["Option31"] = tValentinesDay2015_Priest_ItemText[3005577]["Option31"]
tItem[3005577]["OptionFunc31"] = "ValentinesDay2015_Priest_ChgCoat</N>4"
tItem[3005577]["Option32"] = tValentinesDay2015_Priest_ItemText[3005577]["Option32"]


------------------------------------------NPC对话配置-------------------------------------------
-- 头像
tNpcFace[3331] = 35
tNpcFace[3332] = 119

------------------------------------------
-- //查理神父
tNpcGossip[17285] = tNpcGossip[17285] or DefaultNpc:new{}
tNpcGossip[17285]["OptionHidden"] = 1

--【第一层】--对白
tNpcGossip[17285]["Text1-1"] = {111,112,113} 	--活动时间前
tNpcGossip[17285]["Text1-2"] = {121,122,123} 	--活动时间中
tNpcGossip[17285]["Text1-3"] = {131,132} 		--活动时间后
--活动时间前
tNpcGossip[17285]["Text111"] = tValentinesDay2015_Priest_Text[17285]["Text111"]
tNpcGossip[17285]["Text112"] = tValentinesDay2015_Priest_Text[17285]["Text112"]
tNpcGossip[17285]["Text113"] = tValentinesDay2015_Priest_Text[17285]["Text113"]
tNpcGossip[17285]["ChkFunc1-1"] = function ()
	return ValentinesDay2015_Priest_FestivalTime("Before")
end
--活动时间中
tNpcGossip[17285]["Text121"] = tValentinesDay2015_Priest_Text[17285]["Text121"]
tNpcGossip[17285]["Text122"] = tValentinesDay2015_Priest_Text[17285]["Text122"]
tNpcGossip[17285]["Text123"] = tValentinesDay2015_Priest_Text[17285]["Text123"]
tNpcGossip[17285]["ChkFunc1-2"] = function ()
	return ValentinesDay2015_Priest_FestivalTime("Now")
end
--活动时间后
tNpcGossip[17285]["Text131"] = tValentinesDay2015_Priest_Text[17285]["Text131"]
tNpcGossip[17285]["Text132"] = tValentinesDay2015_Priest_Text[17285]["Text132"]
--选项
tNpcGossip[17285]["tOption1-1"] = {11}
tNpcGossip[17285]["tOption1-2"] = {12,13,14,15,16,17}
tNpcGossip[17285]["tOption1-3"] = {18}
tNpcGossip[17285]["Option11"] = tValentinesDay2015_Priest_Text[17285]["Option11"]
tNpcGossip[17285]["Option12"] = tValentinesDay2015_Priest_Text[17285]["Option12"]
tNpcGossip[17285]["OptionPoint12"] = "17"
tNpcGossip[17285]["Option13"] = tValentinesDay2015_Priest_Text[17285]["Option13"]
tNpcGossip[17285]["OptionPoint13"] = "2"
tNpcGossip[17285]["Option14"] = tValentinesDay2015_Priest_Text[17285]["Option14"]
tNpcGossip[17285]["OptionChkFunc14"] = function ()
	return ValentinesDay2015_Priest_MultiStc(11,2)
end
tNpcGossip[17285]["OptionPoint14"] = "18"
tNpcGossip[17285]["Option15"] = tValentinesDay2015_Priest_Text[17285]["Option15"]
tNpcGossip[17285]["OptionPoint15"] = "11"
tNpcGossip[17285]["Option16"] = tValentinesDay2015_Priest_Text[17285]["Option16"]
tNpcGossip[17285]["OptionPoint16"] = "12"
tNpcGossip[17285]["Option17"] = tValentinesDay2015_Priest_Text[17285]["Option17"]
tNpcGossip[17285]["Option18"] = tValentinesDay2015_Priest_Text[17285]["Option18"]


-- 【我想了解活动详情。】
tNpcGossip[17285]["Text2-1"] = {211}
tNpcGossip[17285]["Text211"] = tValentinesDay2015_Priest_Text[17285]["Text211"]
tNpcGossip[17285]["ChkFunc2-1"] = function ()
	return ValentinesDay2015_Priest_FestivalTime("Now")
end
tNpcGossip[17285]["tOption2-1"] = {21,22,23,24}
tNpcGossip[17285]["Option21"] = tValentinesDay2015_Priest_Text[17285]["Option21"]
tNpcGossip[17285]["OptionPoint21"] = "3"
tNpcGossip[17285]["Option22"] = tValentinesDay2015_Priest_Text[17285]["Option22"]
tNpcGossip[17285]["OptionPoint22"] = "10"
tNpcGossip[17285]["Option23"] = tValentinesDay2015_Priest_Text[17285]["Option23"]
tNpcGossip[17285]["OptionPoint23"] = "9"
tNpcGossip[17285]["Option24"] = tValentinesDay2015_Priest_Text[17285]["Option24"]



-- 【我想了解活动详情。】--> 我想知道情人节有什么活动。
tNpcGossip[17285]["Text3-1"] = {311,312,313}
tNpcGossip[17285]["Text311"] = tValentinesDay2015_Priest_Text[17285]["Text311"]
tNpcGossip[17285]["Text312"] = tValentinesDay2015_Priest_Text[17285]["Text312"]
tNpcGossip[17285]["Text312"] = tValentinesDay2015_Priest_Text[17285]["Text313"]
tNpcGossip[17285]["ChkFunc3-1"] = function ()
	return ValentinesDay2015_Priest_FestivalTime("Now")
end
tNpcGossip[17285]["tOption3-1"] = {31,32,33,34,35,36,37,38,39}
tNpcGossip[17285]["Option31"] = tValentinesDay2015_Priest_Text[17285]["Option31"]
tNpcGossip[17285]["OptionPoint31"] = "4"
tNpcGossip[17285]["Option32"] = tValentinesDay2015_Priest_Text[17285]["Option32"]
tNpcGossip[17285]["OptionPoint32"] = "5"
tNpcGossip[17285]["Option33"] = tValentinesDay2015_Priest_Text[17285]["Option33"]
tNpcGossip[17285]["OptionPoint33"] = "6"
tNpcGossip[17285]["Option34"] = tValentinesDay2015_Priest_Text[17285]["Option34"]
tNpcGossip[17285]["OptionPoint34"] = "7"
tNpcGossip[17285]["Option35"] = tValentinesDay2015_Priest_Text[17285]["Option35"]
tNpcGossip[17285]["OptionPoint35"] = "8"
tNpcGossip[17285]["Option36"] = tValentinesDay2015_Priest_Text[17285]["Option36"]


-- 【我想了解活动详情。】--> 我想知道情人节有什么活动。--> 比翼双飞。
tNpcGossip[17285]["Text4-1"] = {411,412,413}
tNpcGossip[17285]["Text411"] = tValentinesDay2015_Priest_Text[17285]["Text411"]
tNpcGossip[17285]["Text412"] = tValentinesDay2015_Priest_Text[17285]["Text412"]
tNpcGossip[17285]["Text413"] = tValentinesDay2015_Priest_Text[17285]["Text413"]
tNpcGossip[17285]["ChkFunc4-1"] = function ()
	return ValentinesDay2015_Priest_FestivalTime("Now")
end
tNpcGossip[17285]["tOption4-1"] = {41,42}
tNpcGossip[17285]["Option41"] = tValentinesDay2015_Priest_Text[17285]["Option41"]
tNpcGossip[17285]["OptionFunc41"] = "ValentinesDay2015_Priest_FindNpc</N>1</N>0"
tNpcGossip[17285]["Option42"] = tValentinesDay2015_Priest_Text[17285]["Option42"]
tNpcGossip[17285]["OptionPoint42"] = "3"


-- 【我想了解活动详情。】--> 我想知道情人节有什么活动。--> 美女与野兽。
tNpcGossip[17285]["Text5-1"] = {511,512,513}
tNpcGossip[17285]["Text511"] = tValentinesDay2015_Priest_Text[17285]["Text511"]
tNpcGossip[17285]["Text512"] = tValentinesDay2015_Priest_Text[17285]["Text512"]
tNpcGossip[17285]["Text513"] = tValentinesDay2015_Priest_Text[17285]["Text513"]
tNpcGossip[17285]["ChkFunc5-1"] = function ()
	return ValentinesDay2015_Priest_FestivalTime("Now")
end
tNpcGossip[17285]["tOption5-1"] = {51,52}
tNpcGossip[17285]["Option51"] = tValentinesDay2015_Priest_Text[17285]["Option51"]
tNpcGossip[17285]["OptionFunc51"] ="ValentinesDay2015_Priest_FindNpc</N>2</N>0"
tNpcGossip[17285]["Option52"] = tValentinesDay2015_Priest_Text[17285]["Option52"]
tNpcGossip[17285]["OptionPoint52"] = "3"


-- 【我想了解活动详情。】--> 我想知道情人节有什么活动。--> 悬挂同心锁。
tNpcGossip[17285]["Text6-1"] = {611,612,613}
tNpcGossip[17285]["Text611"] = tValentinesDay2015_Priest_Text[17285]["Text611"]
tNpcGossip[17285]["Text612"] = tValentinesDay2015_Priest_Text[17285]["Text612"]
tNpcGossip[17285]["Text613"] = tValentinesDay2015_Priest_Text[17285]["Text613"]
tNpcGossip[17285]["ChkFunc6-1"] = function ()
	return ValentinesDay2015_Priest_FestivalTime("Now")
end
tNpcGossip[17285]["tOption6-1"] = {61,62}
tNpcGossip[17285]["Option61"] = tValentinesDay2015_Priest_Text[17285]["Option61"]
tNpcGossip[17285]["OptionFunc61"] ="ValentinesDay2015_Priest_FindNpc</N>3</N>0"
tNpcGossip[17285]["Option62"] = tValentinesDay2015_Priest_Text[17285]["Option62"]
tNpcGossip[17285]["OptionPoint62"] = "3"


-- 【我想了解活动详情。】--> 我想知道情人节有什么活动。--> 眉来眼去传真情。
tNpcGossip[17285]["Text7-1"] = {711,712}
tNpcGossip[17285]["Text711"] = tValentinesDay2015_Priest_Text[17285]["Text711"]
tNpcGossip[17285]["Text712"] = tValentinesDay2015_Priest_Text[17285]["Text712"]
tNpcGossip[17285]["ChkFunc7-1"] = function ()
	return ValentinesDay2015_Priest_FestivalTime("Now")
end
tNpcGossip[17285]["tOption7-1"] = {71,72}
tNpcGossip[17285]["Option71"] = tValentinesDay2015_Priest_Text[17285]["Option71"]
tNpcGossip[17285]["OptionFunc71"] ="ValentinesDay2015_Priest_FindNpc</N>4</N>0"
tNpcGossip[17285]["Option72"] = tValentinesDay2015_Priest_Text[17285]["Option72"]
tNpcGossip[17285]["OptionPoint72"] = "3"


-- 【我想了解活动详情。】--> 我想知道情人节有什么活动。--> 甜蜜约会之非诚勿扰。
tNpcGossip[17285]["Text8-1"] = {811,812,813}
tNpcGossip[17285]["Text811"] = tValentinesDay2015_Priest_Text[17285]["Text811"]
tNpcGossip[17285]["Text812"] = tValentinesDay2015_Priest_Text[17285]["Text812"]
tNpcGossip[17285]["Text813"] = tValentinesDay2015_Priest_Text[17285]["Text813"]
tNpcGossip[17285]["ChkFunc8-1"] = function ()
	return ValentinesDay2015_Priest_FestivalTime("Now")
end
tNpcGossip[17285]["tOption8-1"] = {81,82}
tNpcGossip[17285]["Option81"] = tValentinesDay2015_Priest_Text[17285]["Option81"]
tNpcGossip[17285]["OptionFunc81"] ="ValentinesDay2015_Priest_FindNpc</N>6</N>0"
tNpcGossip[17285]["Option82"] = tValentinesDay2015_Priest_Text[17285]["Option82"]
tNpcGossip[17285]["OptionPoint82"] = "3"


-- 【我想了解活动详情。】--> 爱情玫瑰要怎么换取外套呢？
tNpcGossip[17285]["Text9-1"] = {911,912,913}
tNpcGossip[17285]["Text911"] = tValentinesDay2015_Priest_Text[17285]["Text911"]
tNpcGossip[17285]["Text912"] = tValentinesDay2015_Priest_Text[17285]["Text912"]
tNpcGossip[17285]["Text913"] = tValentinesDay2015_Priest_Text[17285]["Text913"]
tNpcGossip[17285]["ChkFunc9-1"] = function ()
	return ValentinesDay2015_Priest_FestivalTime("Now") 
end
tNpcGossip[17285]["tOption9-1"] = {91,92}
tNpcGossip[17285]["Option91"] = tValentinesDay2015_Priest_Text[17285]["Option91"]
tNpcGossip[17285]["OptionPoint91"] = "12"
tNpcGossip[17285]["Option92"] = tValentinesDay2015_Priest_Text[17285]["Option92"]


-- 【我想了解活动详情。】--> 我想知道送长梗玫瑰的事情。
tNpcGossip[17285]["Text10-1"] = {1011,1012,1013}
tNpcGossip[17285]["Text1011"] = tValentinesDay2015_Priest_Text[17285]["Text1011"]
tNpcGossip[17285]["Text1012"] = tValentinesDay2015_Priest_Text[17285]["Text1012"]
tNpcGossip[17285]["Text1013"] = tValentinesDay2015_Priest_Text[17285]["Text1013"]
tNpcGossip[17285]["tOption10-1"] = {101}
tNpcGossip[17285]["Option101"] = tValentinesDay2015_Priest_Text[17285]["Option101"]


-- 【我要领取全活动完成奖励。】
tNpcGossip[17285]["Text11-1"] = {1111} 			--活动时间外
tNpcGossip[17285]["Text11-2"] = {1121,1122} 	--等级不足
tNpcGossip[17285]["Text11-3"] = {1131} 			--背包空间不足
tNpcGossip[17285]["Text11-4"] = {1141} 			--领取过奖励
tNpcGossip[17285]["Text11-5"] = {1151} 			--未完成全活动任务
tNpcGossip[17285]["Text11-6"] = {1161} 			--成功领取奖励
--活动时间外
tNpcGossip[17285]["Text1111"] = tValentinesDay2015_Priest_Text[17285]["Text1111"]
tNpcGossip[17285]["ChkFunc11-1"] = function ()
	return not ValentinesDay2015_Priest_FestivalTime("Now")
end
--等级不足
tNpcGossip[17285]["Text1121"] = tValentinesDay2015_Priest_Text[17285]["Text1121"]
tNpcGossip[17285]["Text1122"] = tValentinesDay2015_Priest_Text[17285]["Text1122"]
tNpcGossip[17285]["ChkFunc11-2"] = function ()
	return ValentinesDay2015_Priest_PlayerLev()
end
--背包空间不足
tNpcGossip[17285]["Text1131"] = tValentinesDay2015_Priest_Text[17285]["Text1131"]
tNpcGossip[17285]["ChkFunc11-3"] = function ()
	return not User_CheckLeftSpace(tValentinesDay2015_Priest_Data["ChkSpace"])
end
--领取过奖励
tNpcGossip[17285]["Text1141"] = tValentinesDay2015_Priest_Text[17285]["Text1141"]
tNpcGossip[17285]["ChkFunc11-4"] = function ()
	return not ValentinesDay2015_Priest_MultiStc(12,2)
end
--未完成全活动任务
tNpcGossip[17285]["Text1151"] = tValentinesDay2015_Priest_Text[17285]["Text1151"]
tNpcGossip[17285]["ChkFunc11-5"] = function ()
	return ValentinesDay2015_Priest_AllFinish()
end
--成功领取奖励
tNpcGossip[17285]["Text1161"] = tValentinesDay2015_Priest_Text[17285]["Text1161"]
tNpcGossip[17285]["ChkFunc11-6"] = function ()
	return ValentinesDay2015_Priest_GetAward(12,2)
end
--选项
tNpcGossip[17285]["tOption11-1"] = {111}
tNpcGossip[17285]["Option111"] = tValentinesDay2015_Priest_Text[17285]["Option111"]
tNpcGossip[17285]["tOption11-2"] = {112}
tNpcGossip[17285]["Option112"] = tValentinesDay2015_Priest_Text[17285]["Option112"]
tNpcGossip[17285]["tOption11-3"] = {113}
tNpcGossip[17285]["Option113"] = tValentinesDay2015_Priest_Text[17285]["Option113"]
tNpcGossip[17285]["tOption11-4"] = {114}
tNpcGossip[17285]["Option114"] = tValentinesDay2015_Priest_Text[17285]["Option114"]
tNpcGossip[17285]["tOption11-5"] = {11501,11502,11503,11504,11505,11506,11507}
tNpcGossip[17285]["Option11501"] = tValentinesDay2015_Priest_Text[17285]["Option11501"]

--我这就去找苏巧儿！
tNpcGossip[17285]["OptionChkFunc11501"] = function ()
	return not ValentinesDay2015_Priest_ChkStc(1)
end
tNpcGossip[17285]["OptionFunc11501"] ="ValentinesDay2015_Priest_FindNpc</N>1</N>0"

--我这就去找美女贝儿！
tNpcGossip[17285]["Option11502"] = tValentinesDay2015_Priest_Text[17285]["Option11502"]
tNpcGossip[17285]["OptionChkFunc11502"] = function ()
	return not ValentinesDay2015_Priest_ChkStc(2)
end
tNpcGossip[17285]["OptionFunc11502"] ="ValentinesDay2015_Priest_FindNpc</N>2</N>0"

--我这就去找红娘娇燕燕！
tNpcGossip[17285]["Option11503"] = tValentinesDay2015_Priest_Text[17285]["Option11503"]
tNpcGossip[17285]["OptionChkFunc11503"] = function ()
	return not ValentinesDay2015_Priest_ChkStc(3)
end
tNpcGossip[17285]["OptionFunc11503"] ="ValentinesDay2015_Priest_FindNpc</N>3</N>0"

--我这就去找药师师兄！
tNpcGossip[17285]["Option11504"] = tValentinesDay2015_Priest_Text[17285]["Option11504"]
tNpcGossip[17285]["OptionChkFunc11504"] = function ()
	local nSex = Get_UserSex()

	--男角色
	if nSex == 1 then
		return not ValentinesDay2015_Priest_ChkStc(4)

	--女角色
	elseif nSex == 2 then
		return false
	end
end
tNpcGossip[17285]["OptionFunc11504"] ="ValentinesDay2015_Priest_FindNpc</N>4</N>0"

--我这就去找素秋师妹！
tNpcGossip[17285]["Option11505"] = tValentinesDay2015_Priest_Text[17285]["Option11505"]
tNpcGossip[17285]["OptionChkFunc11505"] = function ()
	local nSex = Get_UserSex()

	--男角色
	if nSex == 1 then
		return false

	--女角色
	elseif nSex == 2 then
		return not ValentinesDay2015_Priest_ChkStc(4)
	end
end
tNpcGossip[17285]["OptionFunc11505"] ="ValentinesDay2015_Priest_FindNpc</N>4</N>0"

--我这就去找男媒婆姚大痣！
tNpcGossip[17285]["Option11506"] = tValentinesDay2015_Priest_Text[17285]["Option11506"]
tNpcGossip[17285]["OptionChkFunc11506"] = function ()
	return not ValentinesDay2015_Priest_ChkStc(5)
end
tNpcGossip[17285]["OptionFunc11506"] ="ValentinesDay2015_Priest_FindNpc</N>6</N>0"
--退出
tNpcGossip[17285]["Option11507"] = tValentinesDay2015_Priest_Text[17285]["Option11507"]
--完成
tNpcGossip[17285]["tOption11-6"] = {116} 
tNpcGossip[17285]["Option116"] = tValentinesDay2015_Priest_Text[17285]["Option116"]


-- 【我要换取情人节外套。】
tNpcGossip[17285]["Text12-1"] = {1211,1212,1213}
tNpcGossip[17285]["Text1211"] = tValentinesDay2015_Priest_Text[17285]["Text1211"]
tNpcGossip[17285]["Text1212"] = tValentinesDay2015_Priest_Text[17285]["Text1212"]
tNpcGossip[17285]["Text1213"] = tValentinesDay2015_Priest_Text[17285]["Text1213"]
tNpcGossip[17285]["ChkFunc12-1"] = function ()
	return ValentinesDay2015_Priest_FestivalTime("Now")
end
tNpcGossip[17285]["tOption12-1"] = {121,122,123}
tNpcGossip[17285]["Option121"] = tValentinesDay2015_Priest_Text[17285]["Option121"]
tNpcGossip[17285]["OptionPoint121"] = "15"
tNpcGossip[17285]["Option122"] = tValentinesDay2015_Priest_Text[17285]["Option122"]
tNpcGossip[17285]["OptionPoint122"] = "16"
tNpcGossip[17285]["Option123"] = tValentinesDay2015_Priest_Text[17285]["Option123"]


-- 【我要换取情人节外套。】--> 我要换取玫瑰风暴武器外套。
tNpcGossip[17285]["Text13-1"] = {1311}
tNpcGossip[17285]["Text1311"] = tValentinesDay2015_Priest_Text[17285]["Text1311"]
tNpcGossip[17285]["ChkFunc13-1"] = function ()
	return ValentinesDay2015_Priest_GetGarment(1,5)
end
tNpcGossip[17285]["tOption13-1"] = {131}
tNpcGossip[17285]["Option131"] = tValentinesDay2015_Priest_Text[17285]["Option131"]


-- 【我要换取情人节外套。】--> 我要换取情人之泪外套。
tNpcGossip[17285]["Text14-1"] = {1411}
tNpcGossip[17285]["Text1411"] = tValentinesDay2015_Priest_Text[17285]["Text1411"]
tNpcGossip[17285]["ChkFunc14-1"] = function ()
	return ValentinesDay2015_Priest_GetGarment(2,5)
end
tNpcGossip[17285]["tOption14-1"] = {141,142}
tNpcGossip[17285]["Option141"] = tValentinesDay2015_Priest_Text[17285]["Option141"]


-- 【我要换取情人节外套。】--> 我要换取玫瑰风暴武器外套。--> 确定。
tNpcGossip[17285]["Text15-1"] = {1511} 			--活动时间外
tNpcGossip[17285]["Text15-2"] = {1521,1522} 	--等级不足
tNpcGossip[17285]["Text15-3"] = {1531} 			--背包空间不足
tNpcGossip[17285]["Text15-4"] = {1541} 			--爱情玫瑰不足
tNpcGossip[17285]["Text15-5"] = {1551} 			--符合条件
--活动时间外
tNpcGossip[17285]["Text1511"] = tValentinesDay2015_Priest_Text[17285]["Text1511"]
tNpcGossip[17285]["ChkFunc15-1"] = function ()
	return not ValentinesDay2015_Priest_FestivalTime("Now")
end
--等级不足
tNpcGossip[17285]["Text1521"] = tValentinesDay2015_Priest_Text[17285]["Text1521"]
tNpcGossip[17285]["Text1522"] = tValentinesDay2015_Priest_Text[17285]["Text1522"]
tNpcGossip[17285]["ChkFunc15-2"] = function ()
	return ValentinesDay2015_Priest_PlayerLev()
end
--背包空间不足
tNpcGossip[17285]["Text1531"] = tValentinesDay2015_Priest_Text[17285]["Text1531"]
tNpcGossip[17285]["ChkFunc15-3"] = function ()
	return not User_CheckLeftSpace(tValentinesDay2015_Priest_Data["ChkSpace"])
end
--爱情玫瑰不足
tNpcGossip[17285]["Text1541"] = tValentinesDay2015_Priest_Text[17285]["Text1541"]
tNpcGossip[17285]["ChkFunc15-4"] = function ()
	return ValentinesDay2015_Priest_GetGarment(1,4)
end
--条件符合
tNpcGossip[17285]["Text1551"] = tValentinesDay2015_Priest_Text[17285]["Text1551"]
--选项
tNpcGossip[17285]["tOption15-1"] = {151}
tNpcGossip[17285]["tOption15-2"] = {152}
tNpcGossip[17285]["tOption15-3"] = {153}
tNpcGossip[17285]["tOption15-4"] = {154}
tNpcGossip[17285]["tOption15-5"] = {155,156}
tNpcGossip[17285]["Option151"] = tValentinesDay2015_Priest_Text[17285]["Option151"]
tNpcGossip[17285]["Option152"] = tValentinesDay2015_Priest_Text[17285]["Option152"]
tNpcGossip[17285]["Option153"] = tValentinesDay2015_Priest_Text[17285]["Option153"]
tNpcGossip[17285]["Option154"] = tValentinesDay2015_Priest_Text[17285]["Option154"]
tNpcGossip[17285]["Option155"] = tValentinesDay2015_Priest_Text[17285]["Option155"]
tNpcGossip[17285]["OptionPoint155"] = "13"
tNpcGossip[17285]["Option156"] = tValentinesDay2015_Priest_Text[17285]["Option156"]


-- 【我要换取情人节外套。】--> 我要换取情人之泪外套。--> 确定。
tNpcGossip[17285]["Text16-1"] = {1611} 			--活动时间外
tNpcGossip[17285]["Text16-2"] = {1621,1622} 	--等级不足
tNpcGossip[17285]["Text16-3"] = {1631} 			--背包空间不足
tNpcGossip[17285]["Text16-4"] = {1641} 			--爱情玫瑰不足
tNpcGossip[17285]["Text16-5"] = {1651} 			--成功换取外套
--活动时间外
tNpcGossip[17285]["Text1611"] = tValentinesDay2015_Priest_Text[17285]["Text1611"]
tNpcGossip[17285]["ChkFunc16-1"] = function ()
	return not ValentinesDay2015_Priest_FestivalTime("Now")
end
--等级不足
tNpcGossip[17285]["Text1621"] = tValentinesDay2015_Priest_Text[17285]["Text1621"]
tNpcGossip[17285]["Text1622"] = tValentinesDay2015_Priest_Text[17285]["Text1622"]
tNpcGossip[17285]["ChkFunc16-2"] = function ()
	return ValentinesDay2015_Priest_PlayerLev()
end
--背包空间不足
tNpcGossip[17285]["Text1631"] = tValentinesDay2015_Priest_Text[17285]["Text1631"]
tNpcGossip[17285]["ChkFunc16-3"] = function ()
	return not User_CheckLeftSpace(tValentinesDay2015_Priest_Data["ChkSpace"])
end
--爱情玫瑰不足
tNpcGossip[17285]["Text1641"] = tValentinesDay2015_Priest_Text[17285]["Text1641"]
tNpcGossip[17285]["ChkFunc16-4"] = function ()
	return ValentinesDay2015_Priest_GetGarment(2,4)
end
--成功换取外套
--条件符合
tNpcGossip[17285]["Text1651"] = tValentinesDay2015_Priest_Text[17285]["Text1651"]
--选项
tNpcGossip[17285]["tOption16-1"] = {161}
tNpcGossip[17285]["tOption16-2"] = {162}
tNpcGossip[17285]["tOption16-3"] = {163}
tNpcGossip[17285]["tOption16-4"] = {164}
tNpcGossip[17285]["tOption16-5"] = {165,166}
tNpcGossip[17285]["Option161"] = tValentinesDay2015_Priest_Text[17285]["Option161"]
tNpcGossip[17285]["Option162"] = tValentinesDay2015_Priest_Text[17285]["Option162"]
tNpcGossip[17285]["Option163"] = tValentinesDay2015_Priest_Text[17285]["Option163"]
tNpcGossip[17285]["Option164"] = tValentinesDay2015_Priest_Text[17285]["Option164"]
tNpcGossip[17285]["Option165"] = tValentinesDay2015_Priest_Text[17285]["Option165"]
tNpcGossip[17285]["OptionPoint165"] = "14"
tNpcGossip[17285]["Option166"] = tValentinesDay2015_Priest_Text[17285]["Option166"]


-- 【我要签到领祝福。】
tNpcGossip[17285]["Text17-1"] = {1711} 	--活动时间外
tNpcGossip[17285]["Text17-2"] = {1721} 	--等级不足
tNpcGossip[17285]["Text17-3"] = {1731} 	--已领过祝福
tNpcGossip[17285]["Text17-4"] = {1741} 	--成功领取祝福
--活动时间外
tNpcGossip[17285]["Text1711"] = tValentinesDay2015_Priest_Text[17285]["Text1711"]
tNpcGossip[17285]["ChkFunc17-1"] = function ()
	return not ValentinesDay2015_Priest_FestivalTime("Now")
end
--等级不足
tNpcGossip[17285]["Text1721"] = tValentinesDay2015_Priest_Text[17285]["Text1721"]
tNpcGossip[17285]["ChkFunc17-2"] = function ()
	return ValentinesDay2015_Priest_PlayerLev()
end
--已领过祝福
tNpcGossip[17285]["Text1731"] = tValentinesDay2015_Priest_Text[17285]["Text1731"]
tNpcGossip[17285]["ChkFunc17-3"] = function ()
	return not ValentinesDay2015_Priest_MultiStc(12,1)
end
--成功领取祝福
tNpcGossip[17285]["Text1741"] = tValentinesDay2015_Priest_Text[17285]["Text1741"]
tNpcGossip[17285]["ChkFunc17-4"] = function ()
	return ValentinesDay2015_Priest_GetAward(12,1)
end
--选项
tNpcGossip[17285]["tOption17-1"] = {171}
tNpcGossip[17285]["tOption17-2"] = {172}
tNpcGossip[17285]["tOption17-3"] = {173}
tNpcGossip[17285]["tOption17-4"] = {174}
tNpcGossip[17285]["Option171"] = tValentinesDay2015_Priest_Text[17285]["Option171"]
tNpcGossip[17285]["Option172"] = tValentinesDay2015_Priest_Text[17285]["Option172"]
tNpcGossip[17285]["Option173"] = tValentinesDay2015_Priest_Text[17285]["Option173"]
tNpcGossip[17285]["Option174"] = tValentinesDay2015_Priest_Text[17285]["Option174"]


-- 【我要领取送长梗玫瑰奖励。】（领取礼包后选项消失）
tNpcGossip[17285]["Text18-1"] = {1811} 	--长梗玫瑰未送完
tNpcGossip[17285]["Text18-2"] = {1821} 	--成功领取奖励
--长梗玫瑰未送完
tNpcGossip[17285]["Text1811"] = tValentinesDay2015_Priest_Text[17285]["Text1811"]
tNpcGossip[17285]["ChkFunc18-1"] = function ()
	return ValentinesDay2015_Priest_LongRoseFinish()
end
--成功领取奖励
tNpcGossip[17285]["Text1821"] = tValentinesDay2015_Priest_Text[17285]["Text1821"]
tNpcGossip[17285]["ChkFunc18-2"] = function ()
	return ValentinesDay2015_Priest_GetAward(11,2)
end
--选项
tNpcGossip[17285]["tOption18-1"] = {181,182,183,184,185,186,187}
tNpcGossip[17285]["Option181"] = tValentinesDay2015_Priest_Text[17285]["Option181"]

--我这就去找苏巧儿！
tNpcGossip[17285]["OptionChkFunc181"] = function ()
	return ValentinesDay2015_Priest_MultiStc(13,1)
end
tNpcGossip[17285]["OptionFunc181"] ="ValentinesDay2015_Priest_FindNpc</N>1</N>0"

--我这就去找美女贝儿！
tNpcGossip[17285]["Option182"] = tValentinesDay2015_Priest_Text[17285]["Option182"]
tNpcGossip[17285]["OptionChkFunc182"] = function ()
	return ValentinesDay2015_Priest_MultiStc(13,2)
end
tNpcGossip[17285]["OptionFunc182"] ="ValentinesDay2015_Priest_FindNpc</N>2</N>0"

--我这就去找红娘娇燕燕！
tNpcGossip[17285]["Option183"] = tValentinesDay2015_Priest_Text[17285]["Option183"]
tNpcGossip[17285]["OptionChkFunc183"] = function ()
	return ValentinesDay2015_Priest_MultiStc(13,3)
end
tNpcGossip[17285]["OptionFunc183"] ="ValentinesDay2015_Priest_FindNpc</N>3</N>0"

--我这就去找药师师兄！
tNpcGossip[17285]["Option184"] = tValentinesDay2015_Priest_Text[17285]["Option184"]
tNpcGossip[17285]["OptionChkFunc184"] = function ()
	return ValentinesDay2015_Priest_MultiStc(13,4)
end
tNpcGossip[17285]["OptionFunc184"] ="ValentinesDay2015_Priest_FindNpc</N>4</N>1"

--我这就去找素秋师妹！
tNpcGossip[17285]["Option185"] = tValentinesDay2015_Priest_Text[17285]["Option185"]
tNpcGossip[17285]["OptionChkFunc185"] = function ()
	return ValentinesDay2015_Priest_MultiStc(13,5)
end
tNpcGossip[17285]["OptionFunc185"] ="ValentinesDay2015_Priest_FindNpc</N>4</N>2"

--我这就去找男媒婆姚大痣！
tNpcGossip[17285]["Option186"] = tValentinesDay2015_Priest_Text[17285]["Option186"]
tNpcGossip[17285]["OptionChkFunc186"] = function ()
	return ValentinesDay2015_Priest_MultiStc(13,6)
end
tNpcGossip[17285]["OptionFunc186"] ="ValentinesDay2015_Priest_FindNpc</N>6</N>0"
--退出
tNpcGossip[17285]["Option187"] = tValentinesDay2015_Priest_Text[17285]["Option187"]
--完成
tNpcGossip[17285]["tOption18-2"] = {188}
tNpcGossip[17285]["Option188"] = tValentinesDay2015_Priest_Text[17285]["Option188"]

------------------------------------------其他活动NPC------------------------------------------

--为情人节其他活动提供的公用选项【送上长梗玫瑰。】
--《眉来眼去传真情》活动未提供

------------------------------------------
-- //苏巧儿 --《比翼双飞》
tNpcGossip[17302] = tNpcGossip[17302] or DefaultNpc:new{}
tNpcGossip[17302]["OptionHidden"] = 1

--【选项】-1000
tNpcGossip[17302]["Option1000"] = tValentinesDay2015_Priest_Text["LongRose_Option"]
tNpcGossip[17302]["OptionChkFunc1000"] = function ()
	return ValentinesDay2015_Priest_MultiStc(13,1)
end
tNpcGossip[17302]["OptionPoint1000"] = "40"

--【送上长梗玫瑰。】
tNpcGossip[17302]["Text40-1"] = {4011} --没有长梗玫瑰
tNpcGossip[17302]["Text40-2"] = {4021} --成功
--没有长梗玫瑰
tNpcGossip[17302]["Text4011"] = tValentinesDay2015_Priest_Text["NoLongRose_Text"]
tNpcGossip[17302]["ChkFunc40-1"] = function ()
	return not Item_ChkItem(tValentinesDay2015_Priest_Data["Item_LongRose"])
end
--成功
tNpcGossip[17302]["Text4021"] = tValentinesDay2015_Priest_Text[17302]["Text4011"]
tNpcGossip[17302]["ChkFunc40-2"] = function ()
	return ValentinesDay2015_Priest_LongRose(1)
end
tNpcGossip[17302]["tOption40-1"] = {401}
tNpcGossip[17302]["tOption40-2"] = {402}
tNpcGossip[17302]["Option401"] = tValentinesDay2015_Priest_Text["NoLongRose_Option"]
tNpcGossip[17302]["Option402"] = tValentinesDay2015_Priest_Text[17302]["Option402"]


------------------------------------------
-- //美女贝儿 -《美女与野兽》
tNpcGossip[17287] = tNpcGossip[17287] or DefaultNpc:new{}
tNpcGossip[17287]["OptionHidden"] = 1

--【选项】-1000
tNpcGossip[17287]["Option1000"] = tValentinesDay2015_Priest_Text["LongRose_Option"]
tNpcGossip[17287]["OptionChkFunc1000"] = function ()
	return ValentinesDay2015_Priest_MultiStc(13,2)
end
tNpcGossip[17287]["OptionPoint1000"] = "40"

--【送上长梗玫瑰。】
tNpcGossip[17287]["Text40-1"] = {4011} --没有长梗玫瑰
tNpcGossip[17287]["Text40-2"] = {4021} --成功
--没有长梗玫瑰
tNpcGossip[17287]["Text4011"] = tValentinesDay2015_Priest_Text["NoLongRose_Text"]
tNpcGossip[17287]["ChkFunc40-1"] = function ()
	return not Item_ChkItem(tValentinesDay2015_Priest_Data["Item_LongRose"])
end
--成功
tNpcGossip[17287]["Text4021"] = tValentinesDay2015_Priest_Text[17287]["Text4011"]
tNpcGossip[17287]["ChkFunc40-2"] = function ()
	return ValentinesDay2015_Priest_LongRose(2)
end
tNpcGossip[17287]["tOption40-1"] = {401}
tNpcGossip[17287]["tOption40-2"] = {402}
tNpcGossip[17287]["Option401"] = tValentinesDay2015_Priest_Text["NoLongRose_Option"]
tNpcGossip[17287]["Option402"] = tValentinesDay2015_Priest_Text[17287]["Option402"]


------------------------------------------
-- //红娘娇燕燕 -《悬挂同心锁》
tNpcGossip[17276] = tNpcGossip[17276] or DefaultNpc:new{}
tNpcGossip[17276]["OptionHidden"] = 1

--【选项】-1000
tNpcGossip[17276]["Option1000"] = tValentinesDay2015_Priest_Text["LongRose_Option"]
tNpcGossip[17276]["OptionChkFunc1000"] = function ()
	return ValentinesDay2015_Priest_MultiStc(13,3)
end
tNpcGossip[17276]["OptionPoint1000"] = "40"

--【送上长梗玫瑰。】
tNpcGossip[17276]["Text40-1"] = {4011} --没有长梗玫瑰
tNpcGossip[17276]["Text40-2"] = {4021} --成功
--没有长梗玫瑰
tNpcGossip[17276]["Text4011"] = tValentinesDay2015_Priest_Text["NoLongRose_Text"]
tNpcGossip[17276]["ChkFunc40-1"] = function ()
	return not Item_ChkItem(tValentinesDay2015_Priest_Data["Item_LongRose"])
end
--成功
tNpcGossip[17276]["Text4021"] = tValentinesDay2015_Priest_Text[17276]["Text4011"]
tNpcGossip[17276]["ChkFunc40-2"] = function ()
	return ValentinesDay2015_Priest_LongRose(3)
end
tNpcGossip[17276]["tOption40-1"] = {401}
tNpcGossip[17276]["tOption40-2"] = {402}
tNpcGossip[17276]["Option401"] = tValentinesDay2015_Priest_Text["NoLongRose_Option"]
tNpcGossip[17276]["Option402"] = tValentinesDay2015_Priest_Text[17276]["Option402"]


------------------------------------------
-- //男媒婆姚大痣 -甜蜜约会之非诚勿扰
tNpcGossip[17321] = tNpcGossip[17321] or DefaultNpc:new{}
tNpcGossip[17321]["OptionHidden"] = 1

--【选项】-1000
tNpcGossip[17321]["Option1000"] = tValentinesDay2015_Priest_Text["LongRose_Option"]
tNpcGossip[17321]["OptionChkFunc1000"] = function ()
	return ValentinesDay2015_Priest_MultiStc(13,6)
end
tNpcGossip[17321]["OptionPoint1000"] = "40"

--【送上长梗玫瑰。】
tNpcGossip[17321]["Text40-1"] = {4011} --没有长梗玫瑰
tNpcGossip[17321]["Text40-2"] = {4021} --成功
--没有长梗玫瑰
tNpcGossip[17321]["Text4011"] = tValentinesDay2015_Priest_Text["NoLongRose_Text"]
tNpcGossip[17321]["ChkFunc40-1"] = function ()
	return not Item_ChkItem(tValentinesDay2015_Priest_Data["Item_LongRose"])
end
--成功
tNpcGossip[17321]["Text4021"] = tValentinesDay2015_Priest_Text[17321]["Text4011"]
tNpcGossip[17321]["ChkFunc40-2"] = function ()
	return ValentinesDay2015_Priest_LongRose(6)
end
tNpcGossip[17321]["tOption40-1"] = {401}
tNpcGossip[17321]["tOption40-2"] = {402}
tNpcGossip[17321]["Option401"] = tValentinesDay2015_Priest_Text["NoLongRose_Option"]
tNpcGossip[17321]["Option402"] = tValentinesDay2015_Priest_Text[17321]["Option402"]



------------------------------------------------------------------------------------
--上线触发
table.insert(tSystem_PlayLogin_Func,ValentinesDay2015_Priest_Login)





