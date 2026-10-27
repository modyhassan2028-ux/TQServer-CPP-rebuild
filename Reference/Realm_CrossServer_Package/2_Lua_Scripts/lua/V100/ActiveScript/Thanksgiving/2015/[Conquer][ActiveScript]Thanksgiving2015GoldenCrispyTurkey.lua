---Name:150817[简体征服][活动脚本]感恩节之黄金脆皮火鸡（11.24-11.30）
--Creator: 	陈莺
--Created:	2015/08/06
--------------------------------------------------------------------------------
--吮指原味火鸡坤哥  17230
--物品
-- 3007289 黄金脆皮火鸡肉
--怪物
-- 7635 黄金脆皮鸡
--掩码
--stc(130,08)	获得火鸡肉次数
--stc(130,16)	杀片区怪数量
--stc(138,90)	记录一天吃鸡肉数量
--命名规范
--Thanksgiving2015GoldenCrispyTurky_

------------------------------------------------------------------------------------------
--活动时间
local tThanksgiving2015GoldenCrispyTurky_Data= {}
	tThanksgiving2015GoldenCrispyTurky_Data["Bef_Time"]= "2014-05-18 00:00 2015-11-23 23:59"
	tThanksgiving2015GoldenCrispyTurky_Data["Now_Time"] = "2015-11-24 00:00 2015-11-30 23:59"
	tThanksgiving2015GoldenCrispyTurky_Data["Aft_Time"]= "2015-12-01 00:00 2016-10-01 23:59"

	-- tThanksgiving2015GoldenCrispyTurky_Data["Bef_Time"]= "2014-05-18 00:00 2015-08-25 23:59"
	-- tThanksgiving2015GoldenCrispyTurky_Data["Now_Time"] = "2015-08-26 00:00 2015-11-30 23:59"
	-- tThanksgiving2015GoldenCrispyTurky_Data["Aft_Time"]= "2015-12-01 00:00 2016-10-01 23:59"
--等级
	tThanksgiving2015GoldenCrispyTurky_Data["Level"] = 80
	tThanksgiving2015GoldenCrispyTurky_Data["Metempsychosis"] = 0
	
--背包空间
	tThanksgiving2015GoldenCrispyTurky_Data["Space"] = 1
--10000银两
	tThanksgiving2015GoldenCrispyTurky_Data["Money"] = 10000
--一天两次
	tThanksgiving2015GoldenCrispyTurky_Data["Time"] = 2
--杀怪100只
	tThanksgiving2015GoldenCrispyTurky_Data["Amount"] = 100
--火鸡肉
	tThanksgiving2015GoldenCrispyTurky_Data["ItemId"] = 3007289
--鸡肉获得概率
	-- tThanksgiving2015GoldenCrispyTurky_Data["GetChicken"] = 20

	-- tThanksgiving2015GoldenCrispyTurky_Data["GetChicken"] = 99
--杀火鸡掉银两概率
	tThanksgiving2015GoldenCrispyTurky_Data["GetMoney1"] = 5
	tThanksgiving2015GoldenCrispyTurky_Data["GetMoney2"] = 1
	
	-- tThanksgiving2015GoldenCrispyTurky_Data["GetMoney1"] = 99
	-- tThanksgiving2015GoldenCrispyTurky_Data["GetMoney2"] = 99

--掩码
local tThanksgiving2015GoldenCrispyTurky_Stc = {}
	tThanksgiving2015GoldenCrispyTurky_Stc["EventType"] = {}
	tThanksgiving2015GoldenCrispyTurky_Stc["DataType"] = {}
--记录获得鸡肉次数
	tThanksgiving2015GoldenCrispyTurky_Stc["EventType"]["Time"] = 130
	tThanksgiving2015GoldenCrispyTurky_Stc["DataType"]["Time"] = 08
--杀片区怪数量
	tThanksgiving2015GoldenCrispyTurky_Stc["EventType"]["Num"] = 130
	tThanksgiving2015GoldenCrispyTurky_Stc["DataType"]["Num"] = 16
--stc(138,90)	记录一天吃鸡肉数量
	tThanksgiving2015GoldenCrispyTurky_Stc["EventType"]["Turky"] = 138
	tThanksgiving2015GoldenCrispyTurky_Stc["DataType"]["Turky"] = 90

--log表
local tThanksgiving2015GoldenCrispyTurky_Log = {}

	tThanksgiving2015GoldenCrispyTurky_Log["Get"] = "0,0,0,0,10002353,2,3007289,1"
	tThanksgiving2015GoldenCrispyTurky_Log["Delete"] = "0,0,3007289,1,10002353,3,0,0"
	tThanksgiving2015GoldenCrispyTurky_Log["Appear"] = "0,0,0,0,10002353,1,0,0"
	tThanksgiving2015GoldenCrispyTurky_Log["LogId"] = 10002353
	tThanksgiving2015GoldenCrispyTurky_Log["FestivalId"] = 3330
	
-----------------------------------------逻辑部分------------------------------------------
--击杀黄金脆皮火鸡
function Thanksgiving2015GoldenCrispyTurky_KillTurky()
	local nTimeEvent = tThanksgiving2015GoldenCrispyTurky_Stc["EventType"]["Time"]
	local nTimeData = tThanksgiving2015GoldenCrispyTurky_Stc["DataType"]["Time"]
	if not Sys_ChkFullTime(tThanksgiving2015GoldenCrispyTurky_Data["Now_Time"]) then
		return
	end 
	--判断是否隔天，隔天清零
	if Task_StcInterval(nTimeEvent,nTimeData,1,4) then 
		Task_SetStatistic(nTimeEvent,nTimeData,0,1)
		Task_SetStcTimestamp(nTimeEvent,nTimeData,0)
		Thanksgiving2015GoldenCrispyTurky_GetChicken(nTimeEvent,nTimeData)
		return
	end
	if Task_ChkStcValue(nTimeEvent,nTimeData,'<',tThanksgiving2015GoldenCrispyTurky_Data["Time"]) then
		Thanksgiving2015GoldenCrispyTurky_GetChicken(nTimeEvent,nTimeData)
		return
	end

--将其击杀1%随机爆出大量银两，1万的8坨
	local nNum = math.random(1,100)
	if nNum <= tThanksgiving2015GoldenCrispyTurky_Data["GetMoney2"] then
		Thanksgiving2015GoldenCrispyTurky_DropMoney()
	end
end

--获得鸡肉
function Thanksgiving2015GoldenCrispyTurky_GetChicken(nTimeEvent,nTimeData)
--火鸡肉获得概率
	-- local nNumber = math.random(1,100)
	-- if nNumber > tThanksgiving2015GoldenCrispyTurky_Data["GetChicken"] then
		-- Sys_MsgBox(tThanksgiving2015GoldenCrispyTurky_Text["MsgBox"]["Failure"])
		-- return
	-- end
	if User_CheckLeftSpace (tThanksgiving2015GoldenCrispyTurky_Data["Space"]) then
		Task_AddStatistic(nTimeEvent,nTimeData,1,1)
		Task_SetStcTimestamp(nTimeEvent,nTimeData,0)
		Item_AddItem(tThanksgiving2015GoldenCrispyTurky_Data["ItemId"])
		Sys_SaveActionFestivalLog(tThanksgiving2015GoldenCrispyTurky_Log["Get"])
		Sys_MsgBox(tThanksgiving2015GoldenCrispyTurky_Text["MsgBox"]["Success"])
	end
--杀怪5%随机掉落银两
	local nNum = math.random(1,100)
	if nNum <= tThanksgiving2015GoldenCrispyTurky_Data["GetMoney1"] then
		Thanksgiving2015GoldenCrispyTurky_DropMoney()
	end
end
--将其击杀会爆出大量银两，1万的8坨
function Thanksgiving2015GoldenCrispyTurky_DropMoney()
	for i=0,7 do
		Monster_SysDropMoney(tThanksgiving2015GoldenCrispyTurky_Data["Money"])
	end
end

--吃黄金脆皮火鸡肉
function Thanksgiving2015GoldenCrispyTurky_EatChicken(nItemId)
	local nTurkyEvent = tThanksgiving2015GoldenCrispyTurky_Stc["EventType"]["Turky"]
	local nTurkyData = tThanksgiving2015GoldenCrispyTurky_Stc["DataType"]["Turky"]

	if not Sys_ChkFullTime(tThanksgiving2015GoldenCrispyTurky_Data["Now_Time"]) then
		if Item_DelItem(nItemId) then
		end
		Sys_SaveActionFestivalLog(tThanksgiving2015GoldenCrispyTurky_Log["Delete"])
		User_TalkChannel2007(tThanksgiving2015GoldenCrispyTurky_Text["MsgBox"]["Over"])
		return
	end 
	--隔天清零
	if Task_StcInterval(nTurkyEvent,nTurkyData,1,4) then 
		Task_SetStatistic(nTurkyEvent,nTurkyData,0,1)
		Task_SetStcTimestamp(nTurkyEvent,nTurkyData,0)
	end
	if Task_ChkStcValue(nTurkyEvent,nTurkyData,'<',tThanksgiving2015GoldenCrispyTurky_Data["Time"]) then
		if Item_DelItem(nItemId) then
			Task_AddStatistic(nTurkyEvent,nTurkyData,1,1)
			Task_SetStcTimestamp(nTurkyEvent,nTurkyData,0)
			FestivalGeneralPackage_GetGift(tThanksgiving2015GoldenCrispyTurky_Log["FestivalId"],tThanksgiving2015GoldenCrispyTurky_Log["LogId"])
		end
	else
		User_TalkChannel2005(tThanksgiving2015GoldenCrispyTurky_Text["MsgBox"]["Turky"])
	end
end
--刷出黄金脆皮火鸡
function Thanksgiving2015GoldenCrispyTurky_AppearTurky(nMonsterTypeId)
	local nNumEvent = tThanksgiving2015GoldenCrispyTurky_Stc["EventType"]["Num"]
	local nNumData = tThanksgiving2015GoldenCrispyTurky_Stc["DataType"]["Num"]
	local nTimeEvent = tThanksgiving2015GoldenCrispyTurky_Stc["EventType"]["Time"]
	local nTimeData = tThanksgiving2015GoldenCrispyTurky_Stc["DataType"]["Time"]
	local nMapId = Get_UserMapId()
	local nPosX = Get_UserPositionX()
	local nPosY = Get_UserPositionY()
--判断时间
	if not Sys_ChkFullTime(tThanksgiving2015GoldenCrispyTurky_Data["Now_Time"]) then
		return
	end 
	--判断等级
	if not User_JudgeLevelAndMetempsychosis(tThanksgiving2015GoldenCrispyTurky_Data["Level"],tThanksgiving2015GoldenCrispyTurky_Data["Metempsychosis"]) then

		return
	end
	--判断是否隔天，隔天清零
	if Task_StcInterval(nTimeEvent,nTimeData,1,4) then 
		Task_SetStatistic(nTimeEvent,nTimeData,0,1)
		Task_SetStcTimestamp(nTimeEvent,nTimeData,0)
	end

	Task_AddStatistic(nNumEvent,nNumData,1,1)
	if Task_ChkStcValue(nNumEvent,nNumData,'>=',tThanksgiving2015GoldenCrispyTurky_Data["Amount"]) then
		Task_SetStatistic(nNumEvent,nNumData,0,1)
		Monster_AddMonster(nMapId,nPosX,nPosY,17193,7635)
		Sys_SaveActionFestivalLog(tThanksgiving2015GoldenCrispyTurky_Log["Appear"])
		if Task_ChkStcValue(nTimeEvent,nTimeData,'<',tThanksgiving2015GoldenCrispyTurky_Data["Time"]) then
			Sys_MsgBox(tThanksgiving2015GoldenCrispyTurky_Text["MsgBox"]["Appear"])
		else
			User_TalkChannel2005(tThanksgiving2015GoldenCrispyTurky_Text["MsgBox"]["Appear"])
		end
	end
end 

-----------------------------------------npc模板-------------------------------------------
---NPC头像
tNpcFace[3250] = 0

---吮指原味火鸡坤哥

tNpcGossip[17230] = tNpcGossip[17230] or DefaultNpc:new{}
tNpcGossip[17230]["OptionHidden"] = 1

--活动时间前
tNpcGossip[17230]["Text1-1"] = {111,112,113}
tNpcGossip[17230]["Text111"] = tThanksgiving2015GoldenCrispyTurky_Text[17230]["Text111"]
tNpcGossip[17230]["Text112"] = tThanksgiving2015GoldenCrispyTurky_Text[17230]["Text112"]
tNpcGossip[17230]["Text113"] = tThanksgiving2015GoldenCrispyTurky_Text[17230]["Text113"]
tNpcGossip[17230]["tOption1-1"] = {1}
tNpcGossip[17230]["ChkFunc1-1"] = function()
	return Sys_ChkFullTime(tThanksgiving2015GoldenCrispyTurky_Data["Bef_Time"])
end
tNpcGossip[17230]["Option1"] = tThanksgiving2015GoldenCrispyTurky_Text[17230]["Option1"]
--活动时间中
tNpcGossip[17230]["Text1-2"] = {121,122,123}
tNpcGossip[17230]["Text121"] = tThanksgiving2015GoldenCrispyTurky_Text[17230]["Text121"]
tNpcGossip[17230]["Text122"] = tThanksgiving2015GoldenCrispyTurky_Text[17230]["Text122"]
tNpcGossip[17230]["Text123"] = tThanksgiving2015GoldenCrispyTurky_Text[17230]["Text123"]

tNpcGossip[17230]["tOption1-2"] = {2,3}
tNpcGossip[17230]["ChkFunc1-2"] = function()
	return Sys_ChkFullTime(tThanksgiving2015GoldenCrispyTurky_Data["Now_Time"])
end
tNpcGossip[17230]["Option2"] = tThanksgiving2015GoldenCrispyTurky_Text[17230]["Option2"]
tNpcGossip[17230]["OptionPoint2"]="2-1"

tNpcGossip[17230]["Option3"] = tThanksgiving2015GoldenCrispyTurky_Text[17230]["Option3"]

--活动时间后
tNpcGossip[17230]["Text1-3"] = {131}
tNpcGossip[17230]["Text131"] = tThanksgiving2015GoldenCrispyTurky_Text[17230]["Text131"]
tNpcGossip[17230]["tOption1-3"] = {4}
tNpcGossip[17230]["ChkFunc1-3"] = function ()
	return Sys_ChkFullTime(tThanksgiving2015GoldenCrispyTurky_Data["Aft_Time"])
end
tNpcGossip[17230]["Option4"] = tThanksgiving2015GoldenCrispyTurky_Text[17230]["Option4"]

--我该怎么帮你噜？
tNpcGossip[17230]["Text2-1"] = {211,212,213}
tNpcGossip[17230]["Text211"] = tThanksgiving2015GoldenCrispyTurky_Text[17230]["Text211"]
tNpcGossip[17230]["Text212"] = tThanksgiving2015GoldenCrispyTurky_Text[17230]["Text212"]
tNpcGossip[17230]["Text213"] = tThanksgiving2015GoldenCrispyTurky_Text[17230]["Text213"]
tNpcGossip[17230]["tOption2-1"] = {5}
tNpcGossip[17230]["Option5"] = tThanksgiving2015GoldenCrispyTurky_Text[17230]["Option5"]

-------------------------------------------怪物模板---------------------------------------------
--黄金脆皮鸡
tMonster[7635] = tMonster[7635] or {}
tMonster[7635]["tFunction"] = tMonster[7635]["tFunction"] or {}
table.insert(tMonster[7635]["tFunction"],Thanksgiving2015GoldenCrispyTurky_KillTurky)
--第一片区
--	1	叫天鸡	9593200
tMonster[1] = tMonster[1] or {}
tMonster[1]["tFunction"] = tMonster[1]["tFunction"] or {}
table.insert(tMonster[1]["tFunction"],Thanksgiving2015GoldenCrispyTurky_AppearTurky)

--	2	斑鸠王	9593210
tMonster[2] = tMonster[2] or {}
tMonster[2]["tFunction"] = tMonster[2]["tFunction"] or {}
table.insert(tMonster[2]["tFunction"],Thanksgiving2015GoldenCrispyTurky_AppearTurky)

--	3	罗罗鸟	9593220
tMonster[3] = tMonster[3] or {}
tMonster[3]["tFunction"] = tMonster[3]["tFunction"] or {}
table.insert(tMonster[3]["tFunction"],Thanksgiving2015GoldenCrispyTurky_AppearTurky)

--	4	幽冥鬼斧王	9593230
tMonster[4] = tMonster[4] or {}
tMonster[4]["tFunction"] = tMonster[4]["tFunction"] or {}
table.insert(tMonster[4]["tFunction"],Thanksgiving2015GoldenCrispyTurky_AppearTurky)

--	5	蹑空鬼斧王	9593240
tMonster[5] = tMonster[5] or {}
tMonster[5]["tFunction"] = tMonster[5]["tFunction"] or {}
table.insert(tMonster[5]["tFunction"],Thanksgiving2015GoldenCrispyTurky_AppearTurky)


--第二片区
--	6	翼蛇	9593250
tMonster[6] = tMonster[6] or {}
tMonster[6]["tFunction"] = tMonster[6]["tFunction"] or {}
table.insert(tMonster[6]["tFunction"],Thanksgiving2015GoldenCrispyTurky_AppearTurky)

--	7	土匪	9593260
tMonster[7] = tMonster[7] or {}
tMonster[7]["tFunction"] = tMonster[7]["tFunction"] or {}
table.insert(tMonster[7]["tFunction"],Thanksgiving2015GoldenCrispyTurky_AppearTurky)

--	8	火鼠	9593270
tMonster[8] = tMonster[8] or {}
tMonster[8]["tFunction"] = tMonster[8]["tFunction"] or {}
table.insert(tMonster[8]["tFunction"],Thanksgiving2015GoldenCrispyTurky_AppearTurky)

--	9	火精灵	9593280
tMonster[9] = tMonster[9] or {}
tMonster[9]["tFunction"] = tMonster[9]["tFunction"] or {}
table.insert(tMonster[9]["tFunction"],Thanksgiving2015GoldenCrispyTurky_AppearTurky)

--	66	精悍土匪	9593290
tMonster[66] = tMonster[66] or {}
tMonster[66]["tFunction"] = tMonster[66]["tFunction"] or {}
table.insert(tMonster[66]["tFunction"],Thanksgiving2015GoldenCrispyTurky_AppearTurky)

--	67	尖牙火鼠	9593300
tMonster[67] = tMonster[67] or {}
tMonster[67]["tFunction"] = tMonster[67]["tFunction"] or {}
table.insert(tMonster[67]["tFunction"],Thanksgiving2015GoldenCrispyTurky_AppearTurky)


--第三片区
--	10	须猕猴	9593310
tMonster[10] = tMonster[10] or {}
tMonster[10]["tFunction"] = tMonster[10]["tFunction"] or {}
table.insert(tMonster[10]["tFunction"],Thanksgiving2015GoldenCrispyTurky_AppearTurky)

--	11	巨臂猿	9593320
tMonster[11] = tMonster[11] or {}
tMonster[11]["tFunction"] = tMonster[11]["tFunction"] or {}
table.insert(tMonster[11]["tFunction"],Thanksgiving2015GoldenCrispyTurky_AppearTurky)

--	12	天雷巨猿	9593330
tMonster[12] = tMonster[12] or {}
tMonster[12]["tFunction"] = tMonster[12]["tFunction"] or {}
table.insert(tMonster[12]["tFunction"],Thanksgiving2015GoldenCrispyTurky_AppearTurky)

--	13	蛇人	9593340
tMonster[13] = tMonster[13] or {}
tMonster[13]["tFunction"] = tMonster[13]["tFunction"] or {}
table.insert(tMonster[13]["tFunction"],Thanksgiving2015GoldenCrispyTurky_AppearTurky)


--第四片区
--	14	沙怪	9593350
tMonster[14] = tMonster[14] or {}
tMonster[14]["tFunction"] = tMonster[14]["tFunction"] or {}
table.insert(tMonster[14]["tFunction"],Thanksgiving2015GoldenCrispyTurky_AppearTurky)

--	15	锤山怪	9593360
tMonster[15] = tMonster[15] or {}
tMonster[15]["tFunction"] = tMonster[15]["tFunction"] or {}
table.insert(tMonster[15]["tFunction"],Thanksgiving2015GoldenCrispyTurky_AppearTurky)

--	16	巨石怪	9593370
tMonster[16] = tMonster[16] or {}
tMonster[16]["tFunction"] = tMonster[16]["tFunction"] or {}
table.insert(tMonster[16]["tFunction"],Thanksgiving2015GoldenCrispyTurky_AppearTurky)

--	17	鬼刃	9593380
tMonster[17] = tMonster[17] or {}
tMonster[17]["tFunction"] = tMonster[17]["tFunction"] or {}
table.insert(tMonster[17]["tFunction"],Thanksgiving2015GoldenCrispyTurky_AppearTurky)

--	73	砾沙怪	9593390
tMonster[73] = tMonster[73] or {}
tMonster[73]["tFunction"] = tMonster[73]["tFunction"] or {}
table.insert(tMonster[73]["tFunction"],Thanksgiving2015GoldenCrispyTurky_AppearTurky)


--第五片区
--	18	金臂鸟人	4081200
tMonster[18] = tMonster[18] or {}
tMonster[18]["tFunction"] = tMonster[18]["tFunction"] or {}
table.insert(tMonster[18]["tFunction"],Thanksgiving2015GoldenCrispyTurky_AppearTurky)

--	19	银羽鹰王	4081254
tMonster[19] = tMonster[19] or {}
tMonster[19]["tFunction"] = tMonster[19]["tFunction"] or {}
table.insert(tMonster[19]["tFunction"],Thanksgiving2015GoldenCrispyTurky_AppearTurky)

--	55	湖岛强匪	4081258
tMonster[55] = tMonster[55] or {}
tMonster[55]["tFunction"] = tMonster[55]["tFunction"] or {}
table.insert(tMonster[55]["tFunction"],ThanksGiving2015GoldenCrispyTurky_AppearTurky)

--	78	银羽鹰魔	4081255
tMonster[78] = tMonster[78] or {}
tMonster[78]["tFunction"] = tMonster[78]["tFunction"] or {}
table.insert(tMonster[78]["tFunction"],Thanksgiving2015GoldenCrispyTurky_AppearTurky)

--	79	湖岛悍匪	4081259
tMonster[79] = tMonster[79] or {}
tMonster[79]["tFunction"] = tMonster[79]["tFunction"] or {}
table.insert(tMonster[79]["tFunction"],Thanksgiving2015GoldenCrispyTurky_AppearTurky)

--	84	匪兵	9593450
tMonster[84] = tMonster[84] or {}
tMonster[84]["tFunction"] = tMonster[84]["tFunction"] or {}
table.insert(tMonster[84]["tFunction"],Thanksgiving2015GoldenCrispyTurky_AppearTurky)

--第六片区
--	20	土墓蝠	9593460
tMonster[20] = tMonster[20] or {}
tMonster[20]["tFunction"] = tMonster[20]["tFunction"] or {}
table.insert(tMonster[20]["tFunction"],Thanksgiving2015GoldenCrispyTurky_AppearTurky)

--	56	嗜血蝙蝠	9593470
tMonster[56] = tMonster[56] or {}
tMonster[56]["tFunction"] = tMonster[56]["tFunction"] or {}
table.insert(tMonster[56]["tFunction"],Thanksgiving2015GoldenCrispyTurky_AppearTurky)

--	57	牛怪	9593480
tMonster[57] = tMonster[57] or {}
tMonster[57]["tFunction"] = tMonster[57]["tFunction"] or {}
table.insert(tMonster[57]["tFunction"],Thanksgiving2015GoldenCrispyTurky_AppearTurky)

--	58	血影红魔	9593490
tMonster[58] = tMonster[58] or {}
tMonster[58]["tFunction"] = tMonster[58]["tFunction"] or {}
table.insert(tMonster[58]["tFunction"],Thanksgiving2015GoldenCrispyTurky_AppearTurky)

-------------------------------------------物品模板---------------------------------------------
tItem[3007289] = tItem[3007289] or {}
tItem[3007289]["Function"] = function(nItemId,sItemName)
	Thanksgiving2015GoldenCrispyTurky_EatChicken(nItemId)
end







