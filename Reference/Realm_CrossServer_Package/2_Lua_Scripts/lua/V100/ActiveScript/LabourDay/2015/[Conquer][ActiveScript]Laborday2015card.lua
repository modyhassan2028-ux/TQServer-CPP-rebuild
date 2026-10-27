---Name:[英文征服][活动脚本]劳工节庆典卡片(9.7-9.13)
--Creator: 	陈莺
--Created:	2015/05/05
--------------------------------------------------------------------------------
--ID号分配如下：
--npc:8045-8046
--itemtype: 711289 白色祝福卡  711286  蓝色聪敏卡  711287  红色欢乐卡  711288  紫色智慧卡
--action:7988000-7988999
--task: 7988000-7988999
--LOGid 10000237

--掩码说明
---stc(77,2) --答题掩码
---stc(77,4) --记录获得卡片时间

--命名规范
-- Laborday2015_card_

--任务：
--1、活动期间，在双龙城有一个npc大宝箱，玩家每隔一个小时就可以随机抽取4种不同的卡片，其中50%的概率抽到没用的白色祝福卡。
--2、抽到蓝色、红色、紫色卡可以到npc韩方处上交卡片，进入答题。
--3、根据卡片的类型提问相关的问题，每答对一题就可获得10分钟经验（等级要小于140）
--4、如果答对3题，就可获得一个节日礼包
--5、一天答对3题后，不能再答题
----------------------------------------------------------------------------------------------
--STC掩码
local tLaborday2015_card_stc = {}
	 tLaborday2015_card_stc[1] = {}
	 tLaborday2015_card_stc[2] = {}
	--stc(77,2) 记录答题次数
	tLaborday2015_card_stc[1]["EventType"] = 77
	tLaborday2015_card_stc[1]["DataType"] = 2
	tLaborday2015_card_stc[1]["Complete"] = 3
	tLaborday2015_card_stc[1]["day"] = 1
	--stc(77,4) 记录获得卡片时间
	tLaborday2015_card_stc[2]["EventType"] = 77
	tLaborday2015_card_stc[2]["DataType"] = 4
	tLaborday2015_card_stc[2]["time"] = 60
	
	
	-- log表
local tLaborday2015_card_log = {}
	tLaborday2015_card_log["card_log"] = "0,0,0,0,10000237,2,%d,1"
	tLaborday2015_card_log["exp_log"] = "0,0,%d,1,10000237,2,4,10"
	tLaborday2015_card_log["AddCultivation_log"] = "0,0,%d,1,10000237,2,4,5"

	tLaborday2015_card_log["DelCard_Log"] = "0,0,%d,1,10000237,2,0,0"
	tLaborday2015_card_log["LogId"] = 10000237
	tLaborday2015_card_log["FestivalId"] = 3436  
	
-- 活动时间
local tLaborday2015_card_data= {}
	tLaborday2015_card_data["Bef_Time"]= "2014-05-18 00:00 2015-09-06 23:59"
	tLaborday2015_card_data["Now_Time"] = "2015-09-07 00:00 2015-09-13 23:59"
	tLaborday2015_card_data["Aft_Time"]= "2015-09-14 00:00 2020-07-14 23:59"
	
-- 玩家等级要求
	tLaborday2015_card_data["Metempsychosis"] = 0
	tLaborday2015_card_data["Level"] = 80
	tLaborday2015_card_data["LevTop"]= 140
	
--背包空间
	tLaborday2015_card_data["space"] = 1 
	
--经验
	tLaborday2015_card_data["exp"] = 10
	
--修行值
	tLaborday2015_card_data["AddCultivation"] = 5

--卡片
	local tLaborday2015_card_ItemId ={}
	--tLaborday2015_card_ItemId[711289] = 711289
	tLaborday2015_card_ItemId[711286] = 711286
	tLaborday2015_card_ItemId[711287] = 711287
	tLaborday2015_card_ItemId[711288] = 711288

--卡片获得概率
 	local tLaborday2015_card_Get = {}
	tLaborday2015_card_Get["Reward"] = {}
	tLaborday2015_card_Get["Reward"][1] = {}
	tLaborday2015_card_Get["Reward"][1]["ItemChanceSum"] = 3

	-- tLaborday2015_card_Get["Reward"][1][1] = {}
	-- tLaborday2015_card_Get["Reward"][1][1]["RandomItemChanceType"] = 2
	-- tLaborday2015_card_Get["Reward"][1][1]["ItemChance"] = 3
	-- tLaborday2015_card_Get["Reward"][1][1]["Item_1"] = 711289
	
	tLaborday2015_card_Get["Reward"][1][1] = {}
	tLaborday2015_card_Get["Reward"][1][1]["RandomItemChanceType"] = 2
	tLaborday2015_card_Get["Reward"][1][1]["ItemChance"] = 1
	tLaborday2015_card_Get["Reward"][1][1]["Item_1"] = 711286
	
	tLaborday2015_card_Get["Reward"][1][2] = {}
	tLaborday2015_card_Get["Reward"][1][2]["RandomItemChanceType"] = 2
	tLaborday2015_card_Get["Reward"][1][2]["ItemChance"] = 1
	tLaborday2015_card_Get["Reward"][1][2]["Item_1"] = 711287
	
	tLaborday2015_card_Get["Reward"][1][3] = {}
	tLaborday2015_card_Get["Reward"][1][3]["RandomItemChanceType"] = 2
	tLaborday2015_card_Get["Reward"][1][3]["ItemChance"] = 1
	tLaborday2015_card_Get["Reward"][1][3]["Item_1"] = 711288
	
	--tLaborday2015_card_Text = {}
	--tLaborday2015_card_Text["MsgBox"] = {}

----------------------------------------逻辑部分--------------------------------------------

---庆典卡片箱 8046
function Laborday2015_card_Option3_8046(nNpcId)
--活动时间判断
	if not Sys_ChkFullTime(tLaborday2015_card_data["Now_Time"]) then
		LinkNpcGossipFunc_New(nNpcId,"1-2")
		return
	end
	---隔天掩码清零
	if Task_StcInterval(tLaborday2015_card_stc[2]["EventType"],tLaborday2015_card_stc[2]["DataType"],1,4) then 
		Task_SetStatistic(tLaborday2015_card_stc[2]["EventType"],tLaborday2015_card_stc[2]["DataType"],0,1,0)
		Task_SetStcTimestamp(tLaborday2015_card_stc[2]["EventType"],tLaborday2015_card_stc[2]["DataType"],0,0)
		
	end 
	if Task_StcInterval(tLaborday2015_card_stc[1]["EventType"],tLaborday2015_card_stc[1]["DataType"],tLaborday2015_card_stc[1]["day"],4) then
	
		Task_SetStatistic(tLaborday2015_card_stc[1]["EventType"],tLaborday2015_card_stc[1]["DataType"],0,1)
		Task_SetStcTimestamp(tLaborday2015_card_stc[1]["EventType"],tLaborday2015_card_stc[1]["DataType"],0,0)
	end
---判断是否答过3次题目
	if  Task_ChkStcValue(tLaborday2015_card_stc[1]["EventType"],tLaborday2015_card_stc[1]["DataType"],">=",3) then 
		User_TalkChannel2005(tLaborday2015_card_Text["MsgBox"]["Complete3"])
		return
	end 
--判断等级
	if User_JudgeLevelAndMetempsychosis(tLaborday2015_card_data["Level"],tLaborday2015_card_data["Metempsychosis"]) then 
		if Task_ChkStcValue(tLaborday2015_card_stc[2]["EventType"],tLaborday2015_card_stc[2]["DataType"],"==",0) then 
			Laborday2015_card_GetCard(nNpcId)
		elseif Task_StcInterval(tLaborday2015_card_stc[2]["EventType"],tLaborday2015_card_stc[2]["DataType"],tLaborday2015_card_stc[2]["time"],1) then 
			Laborday2015_card_GetCard(nNpcId)
		else
			LinkNpcGossipFunc_New(nNpcId,"3-1")
		end	
	else
		LinkNpcGossipFunc_New(nNpcId,"2-1")
	end
end

function Laborday2015_card_GetCard(nNpcId)
--判断是否有蓝卡、红卡、紫卡
	if not Item_ChkMulItem(tLaborday2015_card_ItemId[711286],tLaborday2015_card_ItemId[711288],1) then 
--检测背包
		if not User_CheckLeftSpace(tLaborday2015_card_data["space"]) then  
			User_TalkChannel2005(tLaborday2015_card_Text["MsgBox"]["bag"])
		end

--随机抽取卡片 
		local flat,tNum = Probabil_RandomAward(tLaborday2015_card_Get["Reward"],1)  
		local nItemId = tNum[1]["tAward"][1]["Item_1"]
		Task_SetStatistic(tLaborday2015_card_stc[2]["EventType"],tLaborday2015_card_stc[2]["DataType"],1,1)
		Task_SetStcTimestamp(tLaborday2015_card_stc[2]["EventType"],tLaborday2015_card_stc[2]["DataType"],0)
		Item_AddItem(nItemId)
		local slog = string.format(tLaborday2015_card_log["card_log"],tLaborday2015_card_ItemId[nItemId])
		Sys_SaveActionFestivalLog(slog)
		
		Sys_DialogText(tLaborday2015_card_Text1[8046][nItemId]["Text"])
		Sys_DialogOption(tLaborday2015_card_Text1[8046][nItemId]["Option"],"</F>NULL")
		Sys_DialogFace(nNpcId)
		Sys_DialogEnd()
	else
		User_TalkChannel2005(tLaborday2015_card_Text["MsgBox"]["GetCard"])
	end
end

---韩方

--答题，判断是否答过3次题目
function Laborday2015_card_Option3_8045(nNpcId,nItemId)
--活动时间判断
	if not Sys_ChkFullTime(tLaborday2015_card_data["Now_Time"]) then
		LinkNpcGossipFunc_New(nNpcId,"1-2")
		return
	end
---判断是否隔天
	if Task_StcInterval(tLaborday2015_card_stc[1]["EventType"],tLaborday2015_card_stc[1]["DataType"],tLaborday2015_card_stc[1]["day"],4) then
	
		Task_SetStatistic(tLaborday2015_card_stc[1]["EventType"],tLaborday2015_card_stc[1]["DataType"],0,1)
		Task_SetStcTimestamp(tLaborday2015_card_stc[1]["EventType"],tLaborday2015_card_stc[1]["DataType"],0,0)

	elseif Task_ChkStcValue(tLaborday2015_card_stc[1]["EventType"],tLaborday2015_card_stc[1]["DataType"],">=",3) then 
		LinkNpcGossipFunc_New(nNpcId,"3-1")
		
		return
	end
	Laborday2015_card_CheckCard(nNpcId,nItemId)
	
end
--检测卡片
function Laborday2015_card_CheckCard(nNpcId,nItemId)
	if Item_ChkItem(tLaborday2015_card_ItemId[nItemId]) then 
	Sys_DialogText(tLaborday2015_card_Text[8045]["Text411"])
	Sys_DialogText(tLaborday2015_card_Text[8045]["Text412"])
	Sys_DialogText(tLaborday2015_card_Text[8045]["Text413"])
	Sys_DialogOption(tLaborday2015_card_Text[8045]["Option11"],"</F>Laborday2015_card_Option11_8045</N>" .. nNpcId .. "</N>" .. nItemId)
	Sys_DialogOption(tLaborday2015_card_Text[8045]["Option12"],"</F>NULL")
	Sys_DialogFace(nNpcId)
	Sys_DialogEnd()	
	
	else 
		local sStr = string.format(tLaborday2015_card_Text1[8045]["Text"],tLaborday2015_card_Text1["name"][nItemId])
		Sys_DialogText(sStr)
		Sys_DialogOption(tLaborday2015_card_Text1[8045]["Option"],"</F>NULL")
		Sys_DialogFace(nNpcId)
		Sys_DialogEnd()
	end 
end
--抽题
function Laborday2015_card_Option11_8045(nNpcId,nItemId)
	if Item_ChkItem(tLaborday2015_card_ItemId[nItemId]) then 
		local nNum = math.random(1,20)
		Sys_DialogText(tLaborday2015_card_Question[nItemId]["Text"][nNum])
		Sys_DialogOption(tLaborday2015_card_Question[nItemId]["Option1"][nNum],"</F>Laborday2015_card_Text_Answers</N>" .. nNpcId .. "</N>" .. nItemId .."</N>" ..nNum .. "</N>" ..1)
		Sys_DialogOption(tLaborday2015_card_Question[nItemId]["Option2"][nNum],"</F>Laborday2015_card_Text_Answers</N>" .. nNpcId .. "</N>" .. nItemId .."</N>" ..nNum .. "</N>" ..2)
		Sys_DialogFace(nNpcId)
		Sys_DialogEnd()	
	end
end

--答题触发函数
function Laborday2015_card_Text_Answers(nNpcId,nItemId,nNum,nChoose)

	if nChoose == tLaborday2015_card_Question[nItemId][nNum] then
		Laborday2015_card_Text_right(nNpcId,nItemId)
	else
		Laborday2015_card_Text_wrong(nNpcId,nItemId)
	end
end

--对
function Laborday2015_card_Text_right(nNpcId,nItemId)
--检测卡
	if Item_ChkItem(tLaborday2015_card_ItemId[nItemId]) then 
		if not Item_DelItem(tLaborday2015_card_ItemId[nItemId]) then
			return
		end
		Task_AddStatistic(tLaborday2015_card_stc[1]["EventType"],tLaborday2015_card_stc[1]["DataType"],1,1)
		Task_SetStcTimestamp(tLaborday2015_card_stc[1]["EventType"],tLaborday2015_card_stc[1]["DataType"],0)
		local sLog = string.format(tLaborday2015_card_log["DelCard_Log"],tLaborday2015_card_ItemId[nItemId])
		Sys_SaveActionFestivalLog(sLog)
		local nLevel = Get_UserLevel()
---判断等级是否大于140
		if nLevel < tLaborday2015_card_data["LevTop"] then
			User_AddExpTime(tLaborday2015_card_data["exp"])
			local slog = string.format(tLaborday2015_card_log["exp_log"],tLaborday2015_card_ItemId[nItemId])
			Sys_SaveActionFestivalLog(slog)
			User_TalkChannel2005(tLaborday2015_card_Text["MsgBox"]["finish1"])
		else
			User_AddCultivation(tLaborday2015_card_data["AddCultivation"])
			local slog = string.format(tLaborday2015_card_log["AddCultivation_log"],tLaborday2015_card_ItemId[nItemId])
			Sys_SaveActionFestivalLog(slog)
			User_TalkChannel2005(tLaborday2015_card_Text["MsgBox"]["finish4"])
		end
			
---答对3题，给礼包
		if Task_ChkStcValue(tLaborday2015_card_stc[1]["EventType"],tLaborday2015_card_stc[1]["DataType"],">=",3) then

			FestivalGeneralPackage_GetGift(tLaborday2015_card_log["FestivalId"],tLaborday2015_card_log["LogId"])
			User_TalkChannel2005(tLaborday2015_card_Text["MsgBox"]["finish2"])
		else
			User_TalkChannel2005(tLaborday2015_card_Text["MsgBox"]["finish3"])
		end
		
	else
		local sStr = string.format(tLaborday2015_card_Text1[8045]["Text"],tLaborday2015_card_Text1["name"][nItemId])
		Sys_DialogText(sStr)
		Sys_DialogOption(tLaborday2015_card_Text1[8045]["Option"],"</F>NULL")
		Sys_DialogFace(nNpcId)
		Sys_DialogEnd()
	end
end



--错
function Laborday2015_card_Text_wrong(nNpcId,nItemId)
	if not Item_ChkItem(tLaborday2015_card_ItemId[nItemId]) then 
		return
	end
	if not Item_DelItem(tLaborday2015_card_ItemId[nItemId]) then 
		return
	end
	User_TalkChannel2005(tLaborday2015_card_Text["MsgBox"]["wrong"])
	local sLog = string.format(tLaborday2015_card_log["DelCard_Log"],tLaborday2015_card_ItemId[nItemId])
	Sys_SaveActionFestivalLog(sLog)
	
end




--------------------------------------对白模板-----------------------------------
---NPC头像

tNpcFace[173] = 0


---庆典卡片箱
	tNpcGossip[8046] = tNpcGossip[8046] or DefaultNpc:new{}
	tNpcGossip[8046]["OptionHidden"] = 1
	
-- 活动前
tNpcGossip[8046]["Text1-1"] = {111,112}
tNpcGossip[8046]["Text111"] = tLaborday2015_card_Text[8046]["Text111"]
tNpcGossip[8046]["Text112"] = tLaborday2015_card_Text[8046]["Text112"]
tNpcGossip[8046]["tOption1-1"] = {1}
tNpcGossip[8046]["Option1"] = tLaborday2015_card_Text[8046]["Option1"]
tNpcGossip[8046]["ChkFunc1-1"] = function ()
	return Sys_ChkFullTime(tLaborday2015_card_data["Bef_Time"])
end
-- 活动后
tNpcGossip[8046]["Text1-2"] = {121}
tNpcGossip[8046]["Text121"] = tLaborday2015_card_Text[8046]["Text121"]
tNpcGossip[8046]["tOption1-2"] = {2}
tNpcGossip[8046]["Option2"] = tLaborday2015_card_Text[8046]["Option2"]
tNpcGossip[8046]["ChkFunc1-2"] = function ()
	return Sys_ChkFullTime(tLaborday2015_card_data["Aft_Time"])
end
--活动中
tNpcGossip[8046]["Text1-3"] = {131,132,133}
tNpcGossip[8046]["Text131"] = tLaborday2015_card_Text[8046]["Text131"]
tNpcGossip[8046]["Text132"] = tLaborday2015_card_Text[8046]["Text132"]
tNpcGossip[8046]["Text133"] = tLaborday2015_card_Text[8046]["Text133"]
tNpcGossip[8046]["tOption1-3"] = {3,4}
tNpcGossip[8046]["Option3"] = tLaborday2015_card_Text[8046]["Option3"]
tNpcGossip[8046]["Option4"] = tLaborday2015_card_Text[8046]["Option4"]
tNpcGossip[8046]["ChkFunc1-3"] = function ()
	return Sys_ChkFullTime(tLaborday2015_card_data["Now_Time"])
end
tNpcGossip[8046]["OptionFunc3"]="Laborday2015_card_Option3_8046</N>8046"
--等级不足
tNpcGossip[8046]["Text2-1"] = {211}
tNpcGossip[8046]["Text211"] = tLaborday2015_card_Text[8046]["Text211"]
tNpcGossip[8046]["tOption2-1"] = {5}
tNpcGossip[8046]["Option5"] = tLaborday2015_card_Text[8046]["Option5"]
--时间间隔不足1小时
tNpcGossip[8046]["Text3-1"] = {311}
tNpcGossip[8046]["Text311"] = tLaborday2015_card_Text[8046]["Text311"]
tNpcGossip[8046]["tOption3-1"] = {6}
tNpcGossip[8046]["Option6"] = tLaborday2015_card_Text[8046]["Option6"]


---NPC头像

tNpcFace[172] = 56
---韩方
	tNpcGossip[8045] = tNpcGossip[8045] or DefaultNpc:new{}
	tNpcGossip[8045]["OptionHidden"] = 1
-- 活动前
tNpcGossip[8045]["Text1-1"] = {111,112}
tNpcGossip[8045]["Text111"] = tLaborday2015_card_Text[8045]["Text111"]
tNpcGossip[8045]["Text112"] = tLaborday2015_card_Text[8045]["Text112"]
tNpcGossip[8045]["tOption1-1"] = {1}
tNpcGossip[8045]["Option1"] = tLaborday2015_card_Text[8045]["Option1"]
tNpcGossip[8045]["ChkFunc1-1"] = function ()
	return Sys_ChkFullTime(tLaborday2015_card_data["Bef_Time"])
end
-- 活动后
tNpcGossip[8045]["Text1-2"] = {121,122}
tNpcGossip[8045]["Text121"] = tLaborday2015_card_Text[8045]["Text121"]
tNpcGossip[8045]["Text122"] = tLaborday2015_card_Text[8045]["Text122"]
tNpcGossip[8045]["tOption1-2"] = {2}
tNpcGossip[8045]["Option2"] = tLaborday2015_card_Text[8045]["Option2"]
tNpcGossip[8045]["ChkFunc1-2"] = function ()
	return Sys_ChkFullTime(tLaborday2015_card_data["Aft_Time"])
end
-- 活动中
tNpcGossip[8045]["Text1-3"] = {131,132,133,134}
tNpcGossip[8045]["Text131"] = tLaborday2015_card_Text[8045]["Text131"]
tNpcGossip[8045]["Text132"] = tLaborday2015_card_Text[8045]["Text132"]
tNpcGossip[8045]["Text133"] = tLaborday2015_card_Text[8045]["Text133"]
tNpcGossip[8045]["Text134"] = tLaborday2015_card_Text[8045]["Text134"]
tNpcGossip[8045]["tOption1-3"] = {3,4,5,6,7}
tNpcGossip[8045]["Option3"] = tLaborday2015_card_Text[8045]["Option3"]
tNpcGossip[8045]["Option4"] = tLaborday2015_card_Text[8045]["Option4"]
tNpcGossip[8045]["Option5"] = tLaborday2015_card_Text[8045]["Option5"]
tNpcGossip[8045]["Option6"] = tLaborday2015_card_Text[8045]["Option6"]
tNpcGossip[8045]["Option7"] = tLaborday2015_card_Text[8045]["Option7"]
tNpcGossip[8045]["ChkFunc1-3"] = function ()
	return Sys_ChkFullTime(tLaborday2015_card_data["Now_Time"])
end
tNpcGossip[8045]["OptionFunc3"]="Laborday2015_card_Option3_8045</N>8045</N>711286"
tNpcGossip[8045]["OptionFunc4"]="Laborday2015_card_Option3_8045</N>8045</N>711287"
tNpcGossip[8045]["OptionFunc5"]="Laborday2015_card_Option3_8045</N>8045</N>711288"
tNpcGossip[8045]["OptionPoint6"]="2"
--如何得到庆典卡片
tNpcGossip[8045]["Text2-1"] = {211,212}
tNpcGossip[8045]["Text211"] = tLaborday2015_card_Text[8045]["Text211"]
tNpcGossip[8045]["Text212"] = tLaborday2015_card_Text[8045]["Text212"]
tNpcGossip[8045]["tOption2-1"] = {8}
tNpcGossip[8045]["Option8"] = tLaborday2015_card_Text[8045]["Option8"]
--一天答过3次
tNpcGossip[8045]["Text3-1"] = {311}
tNpcGossip[8045]["Text311"] = tLaborday2015_card_Text[8045]["Text311"]
tNpcGossip[8045]["tOption3-1"] = {9}
tNpcGossip[8045]["Option9"] = tLaborday2015_card_Text[8045]["Option9"]
















		
		
		
		