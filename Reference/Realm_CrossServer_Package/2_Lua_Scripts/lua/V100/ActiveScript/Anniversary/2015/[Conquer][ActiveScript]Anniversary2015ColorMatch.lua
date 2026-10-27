------------------------------------------------------------------------------------
--Name:		[征服][活动脚本]调色大比拼（4.27-5.11）
--Purpose:	调色大比拼
--Creator: 	严振飞
--Created:	2015/02/13
------------------------------------------------------------------------------------
--[[
任务需求：


]]--
------------------------------------------------------------------------------------
--掩码说明
---stc(116,34) 记录是否请假
---stc(122,43) 判断是否接受任务 0为未接受任务 1为接受任务 2为完成任务
---stc(122,44) 判断是否领取奖励 0为未领取 1为已领取
---stc(122,45) 记录第一种使用过的颜料颜色
---0为未使用过颜料 1为红 2为黄 3为蓝 4为橙 5为紫 6为绿

--动态存储表
--cq_dyna_global_data 50468
--data0  = 1 tAnniversary2015_ColorMatch_Text["Orange"]
--       = 2 tAnniversary2015_ColorMatch_Text["Violet"]
--       = 3 tAnniversary2015_ColorMatch_Text["Green"]
--       = 4 黑色
--data1  = 0 当天未置掩码
--       = 1 当天已置掩码 


--LOGid 10002169
------------------------------------------------------------------------------------
--命名规范
--Anniversary2015_ColorMatch_
------------------------------------------------------------------------------------
--STC掩码表
local tAnniversary2015_ColorMatch_Stc = {}
---stc(122,43) 判断是否接受任务 0为未接受任务 1为接受任务 2为完成任务
	tAnniversary2015_ColorMatch_Stc[1] = {}
	tAnniversary2015_ColorMatch_Stc[1]["Event"] = 122
	tAnniversary2015_ColorMatch_Stc[1]["Type"] = 43
	tAnniversary2015_ColorMatch_Stc[1]["Begin"] = 0
	tAnniversary2015_ColorMatch_Stc[1]["Accept"] = 1
	tAnniversary2015_ColorMatch_Stc[1]["Complete"] = 2

---stc(122,44) 判断是否领取奖励 0为未领取 1为已领取
	tAnniversary2015_ColorMatch_Stc[2] = {}
	tAnniversary2015_ColorMatch_Stc[2]["Event"] = 122
	tAnniversary2015_ColorMatch_Stc[2]["Type"] = 44
	tAnniversary2015_ColorMatch_Stc[2]["Begin"] = 0
	tAnniversary2015_ColorMatch_Stc[2]["Complete"] = 1

---stc(122,45) 记录第一种使用过的颜料颜色
	tAnniversary2015_ColorMatch_Stc[3] = {}
	tAnniversary2015_ColorMatch_Stc[3]["Event"] = 122
	tAnniversary2015_ColorMatch_Stc[3]["Type"] = 45
	tAnniversary2015_ColorMatch_Stc[3]["Begin"] = 0
	--颜料ID对应的stc值
	tAnniversary2015_ColorMatch_Stc[3][3003507] =1
	tAnniversary2015_ColorMatch_Stc[3][3003508] =2
	tAnniversary2015_ColorMatch_Stc[3][3003509] =3
	tAnniversary2015_ColorMatch_Stc[3][3003510] =4
	tAnniversary2015_ColorMatch_Stc[3][3003511] =5
	tAnniversary2015_ColorMatch_Stc[3][3003512] =6
	
--颜料对应的ID
local tAnniversary2015_ColorMatch_ColorId = {}
	tAnniversary2015_ColorMatch_ColorId["Red"] =3003507
	tAnniversary2015_ColorMatch_ColorId["Yellow"] =3003508
	tAnniversary2015_ColorMatch_ColorId["Blue"] =3003509
	tAnniversary2015_ColorMatch_ColorId["Orange"] =3003510
	tAnniversary2015_ColorMatch_ColorId["Violet"] =3003511
	tAnniversary2015_ColorMatch_ColorId["Green"] =3003512
	tAnniversary2015_ColorMatch_ColorId["Black"] = 3003513


--活动数据
local tAnniversary2015_ColorMatch_Data = {}
	--活动时间
	tAnniversary2015_ColorMatch_Data["Festival_BefTime"] = "2015-01-01 00:00 2015-05-06 23:59"
	tAnniversary2015_ColorMatch_Data["Festival_MidTime"] = "2015-05-07 00:00 2015-05-27 23:59"
	--等级限制
	tAnniversary2015_ColorMatch_Data["MinLevel"] = 80
	tAnniversary2015_ColorMatch_Data["MinMeto"] = 0
	--背包空间
	tAnniversary2015_ColorMatch_Data["ChkSpace"] = 1
	--调色盘ID
	tAnniversary2015_ColorMatch_Data["ColorDisc"] = 3003506
	--读条数据
	tAnniversary2015_ColorMatch_Data["ExploreTime"] = 5
	tAnniversary2015_ColorMatch_Data["ExploreActionId"] = 220
	--光效
	tAnniversary2015_ColorMatch_Data["EffectObj"] = "self"
	tAnniversary2015_ColorMatch_Data["Effect"] = {}
	tAnniversary2015_ColorMatch_Data["Effect"]["GetReward"] = "angelwing"
	tAnniversary2015_ColorMatch_Data["Effect"]["Orange"] = "accession"
	tAnniversary2015_ColorMatch_Data["Effect"]["Violet"] = "accession4"
	tAnniversary2015_ColorMatch_Data["Effect"]["Green"] = "accession1"
	tAnniversary2015_ColorMatch_Data["Effect"]["Black"] = "accession6"
	tAnniversary2015_ColorMatch_Data["Effect"]["FailColor"] = "BodyDisapear"
	
	--颜料保存时间等数据
	tAnniversary2015_ColorMatch_Data["SaveTime"] = 10
	tAnniversary2015_ColorMatch_Data["Active"] = 1
	--颜料不对错误颜料检测起始+结束
	tAnniversary2015_ColorMatch_Data["TestBegin"] = 1
	tAnniversary2015_ColorMatch_Data["TestEnd"] = 5

	--随机任务颜色几率
	tAnniversary2015_ColorMatch_Data["RandomBegin"] = 25
	tAnniversary2015_ColorMatch_Data["RandomEnd1"] = 4
	tAnniversary2015_ColorMatch_Data["RandomEnd2"] = 3
	tAnniversary2015_ColorMatch_Data["RandomEnd3"] = 2


-- 动态存储表
local tAnniversary2015_ColorMatch_DynaGlobal = {}
	tAnniversary2015_ColorMatch_DynaGlobal["GlobalId"] = 50468
	tAnniversary2015_ColorMatch_DynaGlobal["Data0"] = {}
	tAnniversary2015_ColorMatch_DynaGlobal["Data0"]["Orange"] = 1
	tAnniversary2015_ColorMatch_DynaGlobal["Data0"]["Violet"] = 2
	tAnniversary2015_ColorMatch_DynaGlobal["Data0"]["Green"] = 3
	tAnniversary2015_ColorMatch_DynaGlobal["Data0"]["Black"] = 4
	tAnniversary2015_ColorMatch_DynaGlobal["Data1_Begin"] = 0
	tAnniversary2015_ColorMatch_DynaGlobal["Data1_End"] = 1



--颜色材料
local tAnniversary2015_ColorMatch_Num2Id = {}
	tAnniversary2015_ColorMatch_Num2Id[1] = 3003510
	tAnniversary2015_ColorMatch_Num2Id[2] = 3003511
	tAnniversary2015_ColorMatch_Num2Id[3] = 3003512
	tAnniversary2015_ColorMatch_Num2Id[4] = 3003513


--LOG数据
local tAnniversary2015_ColorMatch_Log = {}
	--通用礼包数据
	tAnniversary2015_ColorMatch_Log["FestivalId"] = 3404
	tAnniversary2015_ColorMatch_Log["LogId"] = 10002169
	--获得调色盘
	tAnniversary2015_ColorMatch_Log["GetColorDisc"] = "0,0,0,0,10002169,2,3003506,1"
	--获得颜料
	tAnniversary2015_ColorMatch_Log["GetColor"] = "0,0,0,0,10002169,2,%s,1"
	--上交配好的颜色
	tAnniversary2015_ColorMatch_Log["GiveColor"] = "0,0,%s[3003506],1[1],10002169,2,3003625,1"
	--删除调色板
	tAnniversary2015_ColorMatch_Log["DelColorDisc"] = "0,0,3003506,1,10002169,1,0,0"
	--删除颜料
	tAnniversary2015_ColorMatch_Log["DelColor"] = "0,0,%s,1,10002169,1,0,0"
	--调色成功
	tAnniversary2015_ColorMatch_Log["SuccessColor"] = "0,0,%s[%s],1[1],10002169,2,%s,1"
	--调色失败删除颜料
	tAnniversary2015_ColorMatch_Log["FailColor"] = "0,0,%s[%s],1[1],10002169,1,0,0"


-- 概率配置表参考
-- tAnniversary2015_ColorMatch_Probabil = {}
-- tAnniversary2015_ColorMatch_Probabil[711897] = {}
-- tAnniversary2015_ColorMatch_Probabil[711897][1] = {}
-- tAnniversary2015_ColorMatch_Probabil[711897][1]["ItemChanceSum"] = 100						--------------相同概率基数的总数

-- tAnniversary2015_ColorMatch_Probabil[711897][1][1] = {}
-- tAnniversary2015_ColorMatch_Probabil[711897][1][1]["RandomItemChanceType"] = 2				--------------概率的类型（1为绝对概率触发，2为相同概率基数，3为各自概率基数）
-- tAnniversary2015_ColorMatch_Probabil[711897][1][1]["ItemChance"] = 25						--------------概率
-- tAnniversary2015_ColorMatch_Probabil[711897][1][1]["Item_1"] = 1								--------------对应的物品ID或者其它自己定义的数字用来概率测试函数的分组

--随机刷出当天任务需要的颜色1/4概率
local tAnniversary2015_ColorMatch_Probabil = {}
	tAnniversary2015_ColorMatch_Probabil[1] = {}
	tAnniversary2015_ColorMatch_Probabil[1][1] = {}
	tAnniversary2015_ColorMatch_Probabil[1][1]["ItemChanceSum"] = 100
	
	tAnniversary2015_ColorMatch_Probabil[1][1][1] = {}
	tAnniversary2015_ColorMatch_Probabil[1][1][1]["RandomItemChanceType"] = 2
	tAnniversary2015_ColorMatch_Probabil[1][1][1]["ItemChance"] = 25
	tAnniversary2015_ColorMatch_Probabil[1][1][1]["Item_1"] = "Orange"

	tAnniversary2015_ColorMatch_Probabil[1][1][2] = {}
	tAnniversary2015_ColorMatch_Probabil[1][1][2]["RandomItemChanceType"] = 2
	tAnniversary2015_ColorMatch_Probabil[1][1][2]["ItemChance"] = 25
	tAnniversary2015_ColorMatch_Probabil[1][1][2]["Item_1"] = "Violet"
	
	tAnniversary2015_ColorMatch_Probabil[1][1][3] = {}
	tAnniversary2015_ColorMatch_Probabil[1][1][3]["RandomItemChanceType"] = 2
	tAnniversary2015_ColorMatch_Probabil[1][1][3]["ItemChance"] = 25
	tAnniversary2015_ColorMatch_Probabil[1][1][3]["Item_1"] = "Green"
	
	tAnniversary2015_ColorMatch_Probabil[1][1][4] = {}
	tAnniversary2015_ColorMatch_Probabil[1][1][4]["RandomItemChanceType"] = 2
	tAnniversary2015_ColorMatch_Probabil[1][1][4]["ItemChance"] = 25
	tAnniversary2015_ColorMatch_Probabil[1][1][4]["Item_1"] = "Black"


------------------------------------------逻辑部分-------------------------------------------
---【我要调色。】
function Anniversary2015_ColorMatch_JoinFestival(nNpcId)
	--活动时间判断
	if not Sys_ChkFullTime(tAnniversary2015_ColorMatch_Data["Festival_MidTime"]) then
		LinkNpcGossipFunc_New(nNpcId,"1-2")
		return
	end

	--玩家等级判断
	if not User_JudgeLevelAndMetempsychosis(tAnniversary2015_ColorMatch_Data["MinLevel"],tAnniversary2015_ColorMatch_Data["MinMeto"]) then
		LinkNpcGossipFunc_New(nNpcId,"2-1")
		return
	end 
	
	--是否有调色盘
	if not Item_ChkItem(tAnniversary2015_ColorMatch_Data["ColorDisc"]) then
	
		--判断背包空间
		if not User_CheckLeftSpace(tAnniversary2015_ColorMatch_Data["ChkSpace"]) then
			LinkNpcGossipFunc_New(nNpcId,"2-2")
			return
		end
		
		--成功接收任务
		Task_SetStatistic(tAnniversary2015_ColorMatch_Stc[1]["Event"],tAnniversary2015_ColorMatch_Stc[1]["Type"],tAnniversary2015_ColorMatch_Stc[1]["Accept"],1)
		Task_SetStcTimestamp(tAnniversary2015_ColorMatch_Stc[1]["Event"],tAnniversary2015_ColorMatch_Stc[1]["Type"],0)
		Item_AddItem(tAnniversary2015_ColorMatch_Data["ColorDisc"])
		Sys_SaveActionFestivalLog(tAnniversary2015_ColorMatch_Log["GetColorDisc"])
	else
		--不给调色板接收任务
		Task_SetStatistic(tAnniversary2015_ColorMatch_Stc[1]["Event"],tAnniversary2015_ColorMatch_Stc[1]["Type"],tAnniversary2015_ColorMatch_Stc[1]["Accept"],1)
		Task_SetStcTimestamp(tAnniversary2015_ColorMatch_Stc[1]["Event"],tAnniversary2015_ColorMatch_Stc[1]["Type"],0)
	end
	
	--出对白
	local sColor = Get_SysDynaGlobalDataStr0(tAnniversary2015_ColorMatch_DynaGlobal["GlobalId"])
	local sText231 = string.format(tAnniversary2015_ColorMatch_Text[nNpcId]["Text231"],sColor)
	Sys_DialogText(sText231)
	Sys_DialogText(tAnniversary2015_ColorMatch_Text[16499]["Text232"])
	Sys_DialogText(tAnniversary2015_ColorMatch_Text[16499]["Text233"])
	Sys_DialogText(tAnniversary2015_ColorMatch_Text[16499]["Text234"])
	Sys_DialogOption(tAnniversary2015_ColorMatch_Text[16499]["Option23"],"</F>NULL")
	Sys_DialogFace(nNpcId)
	Sys_DialogEnd()
end



--【补领调色盘。】
function Anniversary2015_ColorMatch_RewardColorDisc(nNpcId)
	--活动时间判断
	if not Sys_ChkFullTime(tAnniversary2015_ColorMatch_Data["Festival_MidTime"]) then
		LinkNpcGossipFunc_New(nNpcId,"1-2")
		return
	end

	--是否已接收任务
	if Task_ChkStcValue(tAnniversary2015_ColorMatch_Stc[1]["Event"],tAnniversary2015_ColorMatch_Stc[1]["Type"],"==",tAnniversary2015_ColorMatch_Stc[1]["Begin"]) then
		LinkNpcGossipFunc_New(nNpcId,"1-3")
		return
	end

	
	--是否隔天
	if Task_StcInterval(tAnniversary2015_ColorMatch_Stc[1]["Event"],tAnniversary2015_ColorMatch_Stc[1]["Type"],1,4) then
		Task_SetStatistic(tAnniversary2015_ColorMatch_Stc[1]["Event"],tAnniversary2015_ColorMatch_Stc[1]["Type"],0,1)
		Task_SetStcTimestamp(tAnniversary2015_ColorMatch_Stc[1]["Event"],tAnniversary2015_ColorMatch_Stc[1]["Type"],0)
		LinkNpcGossipFunc_New(nNpcId,"1-3")
		return
	end

	--是否未完成任务
	if not Task_ChkStcValue(tAnniversary2015_ColorMatch_Stc[1]["Event"],tAnniversary2015_ColorMatch_Stc[1]["Type"],"==",tAnniversary2015_ColorMatch_Stc[1]["Accept"]) then
		LinkNpcGossipFunc_New(nNpcId,"1-3")
		return
	end

	--是否有调色板
	if Item_ChkItem(tAnniversary2015_ColorMatch_Data["ColorDisc"]) then
		Sys_MsgBox(tAnniversary2015_ColorMatch_Text["HaveColorDisc"])
		return
	end
	
	--判断背包空间
	if not User_CheckLeftSpace(tAnniversary2015_ColorMatch_Data["ChkSpace"]) then
		LinkNpcGossipFunc_New(nNpcId,"2-2")
		return
	end
	
	--成功补领
	Item_AddItem(tAnniversary2015_ColorMatch_Data["ColorDisc"])
	Sys_SaveActionFestivalLog(tAnniversary2015_ColorMatch_Log["GetColorDisc"])
	Sys_MsgBox(tAnniversary2015_ColorMatch_Text["RewardSuccess"])
end



--【上交调配好的颜色。】
function Anniversary2015_ColorMatch_GiveColor(nNpcId)
	--活动时间判断
	if not Sys_ChkFullTime(tAnniversary2015_ColorMatch_Data["Festival_MidTime"]) then
		LinkNpcGossipFunc_New(nNpcId,"1-2")
		return
	end
	
	--是否已接收任务
	if Task_ChkStcValue(tAnniversary2015_ColorMatch_Stc[1]["Event"],tAnniversary2015_ColorMatch_Stc[1]["Type"],"==",tAnniversary2015_ColorMatch_Stc[1]["Begin"]) then
		LinkNpcGossipFunc_New(nNpcId,"1-3")
		return
	end
	
	--是否隔天
	if Task_StcInterval(tAnniversary2015_ColorMatch_Stc[1]["Event"],tAnniversary2015_ColorMatch_Stc[1]["Type"],1,4) then
		Task_SetStatistic(tAnniversary2015_ColorMatch_Stc[1]["Event"],tAnniversary2015_ColorMatch_Stc[1]["Type"],0,1)
		Task_SetStcTimestamp(tAnniversary2015_ColorMatch_Stc[1]["Event"],tAnniversary2015_ColorMatch_Stc[1]["Type"],0)
		LinkNpcGossipFunc_New(nNpcId,"1-3")
		return
	end
	
	--是否未完成任务
	if not Task_ChkStcValue(tAnniversary2015_ColorMatch_Stc[1]["Event"],tAnniversary2015_ColorMatch_Stc[1]["Type"],"==",tAnniversary2015_ColorMatch_Stc[1]["Accept"]) then
		LinkNpcGossipFunc_New(nNpcId,"3-1")
		return
	end
	
	--是否未领奖
	if not Task_ChkStcValue(tAnniversary2015_ColorMatch_Stc[2]["Event"],tAnniversary2015_ColorMatch_Stc[2]["Type"],"==",tAnniversary2015_ColorMatch_Stc[2]["Begin"]) then
		
		--是否隔天
		if not Task_StcInterval(tAnniversary2015_ColorMatch_Stc[2]["Event"],tAnniversary2015_ColorMatch_Stc[2]["Type"],1,4) then
			LinkNpcGossipFunc_New(nNpcId,"3-1")
			return
		end
		
		--重置领奖掩码
		Task_SetStatistic(tAnniversary2015_ColorMatch_Stc[2]["Event"],tAnniversary2015_ColorMatch_Stc[2]["Type"],0,1)
		Task_SetStcTimestamp(tAnniversary2015_ColorMatch_Stc[2]["Event"],tAnniversary2015_ColorMatch_Stc[2]["Type"],0)
	end

	--判断完成任务需要的颜色是否存在
	local nColorNum = Get_SysDynaGlobalData0(tAnniversary2015_ColorMatch_DynaGlobal["GlobalId"])
	local nColorId = tAnniversary2015_ColorMatch_Num2Id[nColorNum]
	local sColor = tAnniversary2015_ColorMatch_Text[nColorId]
	
	if not Item_ChkItem(nColorId) then
		local sText332 = string.format(tAnniversary2015_ColorMatch_Text[nNpcId]["Text332"],sColor)
			Sys_DialogText(tAnniversary2015_ColorMatch_Text[16499]["Text331"])
			Sys_DialogText(sText332)
			Sys_DialogOption(tAnniversary2015_ColorMatch_Text[16499]["Option23"],"</F>NULL")
			Sys_DialogFace(nNpcId)
			Sys_DialogEnd()
		return
	else
		--删除颜料
		Item_DelItem(nColorId)
	end
	
	--是否有调色板
	if Item_ChkItem(tAnniversary2015_ColorMatch_Data["ColorDisc"]) then
		Item_DelItem(tAnniversary2015_ColorMatch_Data["ColorDisc"])
	end

	--置掩码
	Task_SetStatistic(tAnniversary2015_ColorMatch_Stc[1]["Event"],tAnniversary2015_ColorMatch_Stc[1]["Type"],tAnniversary2015_ColorMatch_Stc[1]["Complete"],1)
	Task_SetStcTimestamp(tAnniversary2015_ColorMatch_Stc[1]["Event"],tAnniversary2015_ColorMatch_Stc[1]["Type"],0)
	Task_SetStatistic(tAnniversary2015_ColorMatch_Stc[2]["Event"],tAnniversary2015_ColorMatch_Stc[2]["Type"],tAnniversary2015_ColorMatch_Stc[2]["Complete"],1)
	Task_SetStcTimestamp(tAnniversary2015_ColorMatch_Stc[2]["Event"],tAnniversary2015_ColorMatch_Stc[2]["Type"],0)

	--给礼包+打LOG+播光效+出对白
	FestivalGeneralPackage_GetGift(tAnniversary2015_ColorMatch_Log["FestivalId"],tAnniversary2015_ColorMatch_Log["LogId"])
	local sLog_GiveColor = string.format(tAnniversary2015_ColorMatch_Log["GiveColor"],nColorId)
	Sys_SaveActionFestivalLog(sLog_GiveColor)
	User_EffectAdd(tAnniversary2015_ColorMatch_Data["EffectObj"],tAnniversary2015_ColorMatch_Data["Effect"]["GetReward"])
	LinkNpcGossipFunc_New(nNpcId,"3-2")
end



--【我该怎么做？】
function Anniversary2015_ColorMatch_Introduction(nNpcId)
	--活动时间判断
	if not Sys_ChkFullTime(tAnniversary2015_ColorMatch_Data["Festival_MidTime"]) then
		LinkNpcGossipFunc_New(nNpcId,"1-2")
		return
	end
	
	--介绍内容
	LinkNpcGossipFunc_New(nNpcId,"4-1")
end



--【具体配色规则】
function Anniversary2015_ColorMatch_ColorRule(nNpcId)
	--活动时间判断
	if not Sys_ChkFullTime(tAnniversary2015_ColorMatch_Data["Festival_MidTime"]) then
		LinkNpcGossipFunc_New(nNpcId,"1-2")
		return
	end
	
	--规则内容
	LinkNpcGossipFunc_New(nNpcId,"5-1")
end



---------------------------------------颜料箱逻辑函数-----------------------------------------
--【颜料箱选项判断函数】
function Anniversary2015_ColorMatch_ChkOption()
	--活动时间判断
	if not Sys_ChkFullTime(tAnniversary2015_ColorMatch_Data["Festival_MidTime"]) then
		return false
	end
	
	local nEvent = tAnniversary2015_ColorMatch_Stc[1]["Event"]
	local nType = tAnniversary2015_ColorMatch_Stc[1]["Type"]
	
	--是否已接收任务
	if Task_ChkStcValue(nEvent,nType,"==",tAnniversary2015_ColorMatch_Stc[1]["Begin"]) then
		return false
	end
	
	--是否隔天
	if Task_StcInterval(nEvent,nType,1,4) then
		Task_SetStatistic(nEvent,nType,0,1)
		Task_SetStcTimestamp(nEvent,nType,0)
		return false
	end
	
	--是否未完成任务
	if not Task_ChkStcValue(nEvent,nType,"==",tAnniversary2015_ColorMatch_Stc[1]["Accept"]) then
		return false
	end
	
	return true
end




--【读条成功】
function Anniversary2015_ColorMatch_ExploreSuccess(nNpcId,sColor,nColorId)

	--获得颜料
	local nSaveTime = tAnniversary2015_ColorMatch_Data["SaveTime"]
	local nActive = tAnniversary2015_ColorMatch_Data["Active"]
	local sLogText = string.format(tAnniversary2015_ColorMatch_Log["GetColor"],nColorId)
	local sText = string.format(tAnniversary2015_ColorMatch_Text["GetColor"],sColor)
	Item_AddItem(nColorId,0,0,0,nSaveTime,nActive)
	Sys_SaveActionFestivalLog(sLogText)
	User_TalkChannel2005(sText)
end



--【取用颜料】
function Anniversary2015_ColorMatch_GetColor(nNpcId,nColorId)
	local sColor = tAnniversary2015_ColorMatch_Text[nColorId]

	--活动时间判断
	if not Sys_ChkFullTime(tAnniversary2015_ColorMatch_Data["Festival_MidTime"]) then
		LinkNpcGossipFunc_New(nNpcId,"1-1")
		return
	end
	
	--判断背包空间
	if not User_CheckLeftSpace(tAnniversary2015_ColorMatch_Data["ChkSpace"]) then
		User_TalkChannel2005(tAnniversary2015_ColorMatch_Text["BagFull"])
		return
	end
	
	local nSecs = tAnniversary2015_ColorMatch_Data["ExploreTime"]
	local sContent = tAnniversary2015_ColorMatch_Text["ExploreText"]
	local nActionId = tAnniversary2015_ColorMatch_Data["ExploreActionId"]
	local sFunc = string.format("Anniversary2015_ColorMatch_ExploreSuccess</N>%d</S>%s</N>%d",nNpcId,sColor,nColorId)
	User_SetExplore(nSecs,sContent,nActionId,sFunc)
end

--关闭调色板提示
function Anniversary2015_ColorMatch_CloseColorDisc()
	User_TalkChannel2005(tAnniversary2015_ColorMatch_Text["CloseColorDisc"])
end



---------------------------------------颜料逻辑函数-----------------------------------------
--颜料初始判断函数
function Anniversary2015_ColorMatch_AddColorBegin(nItemId)
	local sColor = tAnniversary2015_ColorMatch_Text[nItemId]
	
	--活动时间判断
	if not Sys_ChkFullTime(tAnniversary2015_ColorMatch_Data["Festival_MidTime"]) then
		--删除颜料
		if Item_ChkItem(nItemId) then
			Item_DelAllItemByType(nItemId)
			local sLogText = string.format(tAnniversary2015_ColorMatch_Log["DelColor"],nItemId)
			local sTalkText = string.format(tAnniversary2015_ColorMatch_Text["DelColor"],sColor)
			Sys_SaveActionFestivalLog(sLogText)
			User_TalkChannel2005(sTalkText)
		end
		return false
	end

	--判断是否存在调色板
	if not Item_ChkItem(tAnniversary2015_ColorMatch_Data["ColorDisc"]) then
		User_TalkChannel2005(tAnniversary2015_ColorMatch_Text["NoColorDisc"])
		return false
	end
	
	--判断是否使用
	if Task_ChkStcValue(tAnniversary2015_ColorMatch_Stc[3]["Event"],tAnniversary2015_ColorMatch_Stc[3]["Type"],"==",tAnniversary2015_ColorMatch_Stc[3]["Begin"]) then
		Task_SetStatistic(tAnniversary2015_ColorMatch_Stc[3]["Event"],tAnniversary2015_ColorMatch_Stc[3]["Type"],tAnniversary2015_ColorMatch_Stc[3][nItemId],1)
		local sUseColorText = string.format(tAnniversary2015_ColorMatch_Text["UseColor"],sColor)
		Sys_MsgBox(sUseColorText)
		User_TalkChannel2005(sUseColorText)
		return false
	end

	--满足条件返回真
	return true
end




--颜料合成函数
function Anniversary2015_ColorMatch_ColorForm(sColorObj,sColor1,sColor2)
	local nColorObjId = tAnniversary2015_ColorMatch_ColorId[sColorObj]
	local nColor1Id = tAnniversary2015_ColorMatch_ColorId[sColor1]
	local nColor2Id = tAnniversary2015_ColorMatch_ColorId[sColor2]

	--调色板上是否有颜料2（sColor2）
	if Task_ChkStcValue(tAnniversary2015_ColorMatch_Stc[3]["Event"],tAnniversary2015_ColorMatch_Stc[3]["Type"],"==",tAnniversary2015_ColorMatch_Stc[3][nColor2Id]) then
		--重置使用的颜料
		Task_SetStatistic(tAnniversary2015_ColorMatch_Stc[3]["Event"],tAnniversary2015_ColorMatch_Stc[3]["Type"],tAnniversary2015_ColorMatch_Stc[3]["Begin"],1)

		--是否存在颜料（sColor2）
		if not Item_ChkItem(tAnniversary2015_ColorMatch_ColorId[sColor2]) then
			User_TalkChannel2005(tAnniversary2015_ColorMatch_Text["ErrorColor"])
			return false
		end

		--删除基础颜料
		Item_DelItem(tAnniversary2015_ColorMatch_ColorId[sColor1])
		Item_DelItem(tAnniversary2015_ColorMatch_ColorId[sColor2])
		
		--活动调成的颜料
		Item_AddItem(tAnniversary2015_ColorMatch_ColorId[sColorObj])
		
		--打LOG+播光效+出对白
		local sColorName = tAnniversary2015_ColorMatch_Text[nColorObjId]
		local sLog_SucessColor = string.format(tAnniversary2015_ColorMatch_Log["SuccessColor"],nColor1Id,nColor2Id,nColorObjId)
		local sText_SucessColor = string.format(tAnniversary2015_ColorMatch_Text["SuccessColor"],sColorName)
		Sys_SaveActionFestivalLog(sLog_SucessColor)
		User_EffectAdd(tAnniversary2015_ColorMatch_Data["EffectObj"],tAnniversary2015_ColorMatch_Data["Effect"][sColorObj])
		User_TalkChannel2005(sText_SucessColor)
		return true
	end
	
	--返回错误
	return false
end




--颜色不对调色失败
function Anniversary2015_ColorMatch_AddColorFail(nItemId,sErrorColor1,sErrorColor2,sErrorColor3,sErrorColor4,sErrorColor5)
	local nEvent_4 = tAnniversary2015_ColorMatch_Stc[3]["Event"]
	local nType_4 = tAnniversary2015_ColorMatch_Stc[3]["Type"]
	local nTestBegin = tAnniversary2015_ColorMatch_Data["TestBegin"]
	local nTestEnd = tAnniversary2015_ColorMatch_Data["TestEnd"]
	
	local tColorTable = {}
		tColorTable[1] = sErrorColor1
		tColorTable[2] = sErrorColor2
		tColorTable[3] = sErrorColor3
		tColorTable[4] = sErrorColor4
		tColorTable[5] = sErrorColor5

	for nColorNum = nTestBegin, nTestEnd do
		--确定是哪种错误颜料
		local sColorName = tColorTable[nColorNum]
		
		--是否为空判断
		if sColorName == nil then
			return
		end

		local nColorId = tAnniversary2015_ColorMatch_ColorId[sColorName]
		--确认是否是该错误颜料
		if Task_ChkStcValue(nEvent_4,nType_4,"==",tAnniversary2015_ColorMatch_Stc[3][nColorId]) then

			--重置使用的颜料
			Task_SetStatistic(nEvent_4,nType_4,tAnniversary2015_ColorMatch_Stc[3]["Begin"],1)
			
			--删除两种错误颜料
			Item_DelItem(nItemId)
			if Item_ChkItem(nColorId) then
				Item_DelItem(nColorId)
			end
			
			--LOG+光效+提示
			local sLog_FailColor = string.format(tAnniversary2015_ColorMatch_Log["FailColor"],nItemId,nColorId)
			Sys_SaveActionFestivalLog(sLog_FailColor)
			User_EffectAdd(tAnniversary2015_ColorMatch_Data["EffectObj"],tAnniversary2015_ColorMatch_Data["Effect"]["FailColor"])
			User_TalkChannel2005(tAnniversary2015_ColorMatch_Text["FailColor"])
			return
		end
	end
end




---------------------------------------自检逻辑函数-----------------------------------------
function Anniversary2015_ColorMatch_PrompetFunc()
	local nGlobalId = tAnniversary2015_ColorMatch_DynaGlobal["GlobalId"]
	
	--活动时间判断
	if not Sys_ChkFullTime(tAnniversary2015_ColorMatch_Data["Festival_MidTime"]) then
		return
	end

	--判断重置限制是否打开
	local nDynaGlobalData1 = Get_SysDynaGlobalData1(nGlobalId)

	if nDynaGlobalData1 == 1 then
		return
	end

	--1/4几率
	local flat,tItem = Probabil_RandomAward(tAnniversary2015_ColorMatch_Probabil[1],1)
	local sColorName = tItem[1]["tAward"][1]["Item_1"]
	Sys_SetSynaGlobalData0(nGlobalId,tAnniversary2015_ColorMatch_DynaGlobal["Data0"][sColorName])
	Sys_SetSynaGlobalDataStr0(nGlobalId,tAnniversary2015_ColorMatch_Text[sColorName])

	--打开限制
	Sys_SetSynaGlobalData1(nGlobalId,tAnniversary2015_ColorMatch_DynaGlobal["Data1_End"])
end


--关闭限制函数
function Anniversary2015_ColorMatch_PrompetColose()
	local nGlobalId = tAnniversary2015_ColorMatch_DynaGlobal["GlobalId"]
	Sys_SetSynaGlobalData1(nGlobalId,tAnniversary2015_ColorMatch_DynaGlobal["Data1_Begin"])
end


------------------------------------------NPC配置-------------------------------------------
---------------------NPC头像
tNpcFace[2939] = 158
---------------------NPC对话
------------------------------------------
-- // ==调色大师王芝芝== \\
tNpcGossip[16499] = tNpcGossip[16499] or DefaultNpc:new{}
tNpcGossip[16503] = tNpcGossip[16499] or DefaultNpc:new{}
tNpcGossip[16499]["OptionHidden"] = 1

---【起始对白】
tNpcGossip[16499]["Text1-1"] = {111,112,113,114} 	-- 活动时间前
tNpcGossip[16499]["Text1-2"] = {121} 				-- 活动时间后
tNpcGossip[16499]["Text1-3"] = {131,132,133} 		-- 活动时间中

---活动前
tNpcGossip[16499]["Text111"] = tAnniversary2015_ColorMatch_Text[16499]["Text111"]
tNpcGossip[16499]["Text112"] = tAnniversary2015_ColorMatch_Text[16499]["Text112"]
tNpcGossip[16499]["Text113"] = tAnniversary2015_ColorMatch_Text[16499]["Text113"]
tNpcGossip[16499]["Text114"] = tAnniversary2015_ColorMatch_Text[16499]["Text114"]
tNpcGossip[16499]["ChkFunc1-1"] = function ()
	return Sys_ChkFullTime(tAnniversary2015_ColorMatch_Data["Festival_BefTime"])
end

---活动后
tNpcGossip[16499]["Text121"] = tAnniversary2015_ColorMatch_Text[16499]["Text121"]
tNpcGossip[16499]["ChkFunc1-2"] = function ()
	return not Sys_ChkFullTime(tAnniversary2015_ColorMatch_Data["Festival_MidTime"])
end

---活动中
tNpcGossip[16499]["Text131"] = tAnniversary2015_ColorMatch_Text[16499]["Text131"]
tNpcGossip[16499]["Text132"] = tAnniversary2015_ColorMatch_Text[16499]["Text132"]
tNpcGossip[16499]["Text133"] = tAnniversary2015_ColorMatch_Text[16499]["Text133"]
--选项
tNpcGossip[16499]["tOption1-1"] = {11}				-- 活动时间前
tNpcGossip[16499]["tOption1-2"] = {12}				-- 活动时间后
tNpcGossip[16499]["tOption1-3"] = {13,14,16,15,17}	-- 活动时间中
tNpcGossip[16499]["Option11"] = tAnniversary2015_ColorMatch_Text[16499]["Option11"]
tNpcGossip[16499]["Option12"] = tAnniversary2015_ColorMatch_Text[16499]["Option12"]
tNpcGossip[16499]["Option13"] = tAnniversary2015_ColorMatch_Text[16499]["Option13"]
tNpcGossip[16499]["OptionChkFunc13"] = function ()
	--接受任务掩码是否为0
	if Task_ChkStcValue(tAnniversary2015_ColorMatch_Stc[1]["Event"],tAnniversary2015_ColorMatch_Stc[1]["Type"],"==",tAnniversary2015_ColorMatch_Stc[1]["Begin"]) then
		return true
	end

	--是否隔天
	if Task_StcInterval(tAnniversary2015_ColorMatch_Stc[1]["Event"],tAnniversary2015_ColorMatch_Stc[1]["Type"],1,4) then
		Task_SetStatistic(tAnniversary2015_ColorMatch_Stc[1]["Event"],tAnniversary2015_ColorMatch_Stc[1]["Type"],0,1)
		Task_SetStcTimestamp(tAnniversary2015_ColorMatch_Stc[1]["Event"],tAnniversary2015_ColorMatch_Stc[1]["Type"],0)
		return true
	end
end
tNpcGossip[16499]["OptionFunc13"] = "Anniversary2015_ColorMatch_JoinFestival</N>16499"
tNpcGossip[16499]["Option14"] = tAnniversary2015_ColorMatch_Text[16499]["Option14"]
tNpcGossip[16499]["OptionChkFunc14"] = function ()
	--判断是否接受任务
	if Task_ChkStcValue(tAnniversary2015_ColorMatch_Stc[1]["Event"],tAnniversary2015_ColorMatch_Stc[1]["Type"],"==",tAnniversary2015_ColorMatch_Stc[1]["Accept"]) then
		return true
	end
end
tNpcGossip[16499]["OptionFunc14"] = "Anniversary2015_ColorMatch_RewardColorDisc</N>16499"
tNpcGossip[16499]["Option15"] = tAnniversary2015_ColorMatch_Text[16499]["Option15"]
tNpcGossip[16499]["OptionChkFunc15"] = function ()
	--判断是否接受任务
	if Task_ChkStcValue(tAnniversary2015_ColorMatch_Stc[1]["Event"],tAnniversary2015_ColorMatch_Stc[1]["Type"],"==",tAnniversary2015_ColorMatch_Stc[1]["Accept"]) then
		return true
	end
end
tNpcGossip[16499]["OptionFunc15"] = "Anniversary2015_ColorMatch_GiveColor</N>16499"
tNpcGossip[16499]["Option16"] = tAnniversary2015_ColorMatch_Text[16499]["Option16"]
tNpcGossip[16499]["OptionFunc16"] = "Anniversary2015_ColorMatch_Introduction</N>16499"
tNpcGossip[16499]["Option17"] = tAnniversary2015_ColorMatch_Text[16499]["Option17"]



---【我要调色。】
tNpcGossip[16499]["Text2-1"] = {211} 				--等级不足
tNpcGossip[16499]["Text2-2"] = {221}				--背包空间不足
tNpcGossip[16499]["Text211"] = tAnniversary2015_ColorMatch_Text[16499]["Text211"]
tNpcGossip[16499]["Text221"] = tAnniversary2015_ColorMatch_Text[16499]["Text221"]
--选项
tNpcGossip[16499]["tOption2-1"] = {21}				-- 等级不足
tNpcGossip[16499]["tOption2-2"] = {22}				--背包空间不足
tNpcGossip[16499]["Option21"] = tAnniversary2015_ColorMatch_Text[16499]["Option21"]
tNpcGossip[16499]["Option22"] = tAnniversary2015_ColorMatch_Text[16499]["Option22"]



--【上交调配好的颜色。】
tNpcGossip[16499]["Text3-1"] = {311} 				--已完成任务
tNpcGossip[16499]["Text3-2"] = {321}				--成功上交
tNpcGossip[16499]["Text311"] = tAnniversary2015_ColorMatch_Text[16499]["Text311"]
tNpcGossip[16499]["Text321"] = tAnniversary2015_ColorMatch_Text[16499]["Text321"]
--选项
tNpcGossip[16499]["tOption3-1"] = {31}			--已完成任务
tNpcGossip[16499]["tOption3-2"] = {32}			--成功上交
tNpcGossip[16499]["Option31"] = tAnniversary2015_ColorMatch_Text[16499]["Option31"]
tNpcGossip[16499]["Option32"] = tAnniversary2015_ColorMatch_Text[16499]["Option32"]



--【我该怎么做？】
tNpcGossip[16499]["Text4-1"] = {411,412,413,414} 		--活动内容介绍
tNpcGossip[16499]["Text411"] = tAnniversary2015_ColorMatch_Text[16499]["Text411"]
tNpcGossip[16499]["Text412"] = tAnniversary2015_ColorMatch_Text[16499]["Text412"]
tNpcGossip[16499]["Text413"] = tAnniversary2015_ColorMatch_Text[16499]["Text413"]
tNpcGossip[16499]["Text414"] = tAnniversary2015_ColorMatch_Text[16499]["Text414"]
--选项
tNpcGossip[16499]["tOption4-1"] = {41}			--活动内容介绍
tNpcGossip[16499]["Option41"] = tAnniversary2015_ColorMatch_Text[16499]["Option41"]
tNpcGossip[16499]["OptionFunc41"] = "Anniversary2015_ColorMatch_ColorRule</N>16499"


--【配色规则】
tNpcGossip[16499]["Text5-1"] = {511,512,513,514,515}	--配色规则
tNpcGossip[16499]["Text511"] = tAnniversary2015_ColorMatch_Text[16499]["Text511"]
tNpcGossip[16499]["Text512"] = tAnniversary2015_ColorMatch_Text[16499]["Text512"]
tNpcGossip[16499]["Text513"] = tAnniversary2015_ColorMatch_Text[16499]["Text513"]
tNpcGossip[16499]["Text514"] = tAnniversary2015_ColorMatch_Text[16499]["Text514"]
tNpcGossip[16499]["Text515"] = tAnniversary2015_ColorMatch_Text[16499]["Text515"]
--选项
tNpcGossip[16499]["tOption5-1"] = {51}			--配色规则
tNpcGossip[16499]["Option51"] = tAnniversary2015_ColorMatch_Text[16499]["Option51"]



------------------------------------------------------------------------------------
-- // ==红色颜料箱== \\
tNpcGossip[16500] = tNpcGossip[16500] or DefaultNpc:new{}
tNpcGossip[16500]["OptionHidden"] = 1
---【起始对白】
tNpcGossip[16500]["Text1-1"] = {111} 	-- 活动中对白
tNpcGossip[16500]["Text111"] = tAnniversary2015_ColorMatch_Text[16500]["Text111"]
--选项
tNpcGossip[16500]["tOption1-1"] = {11,12}		--活动中对白
tNpcGossip[16500]["Option11"] = tAnniversary2015_ColorMatch_Text[16500]["Option11"]
tNpcGossip[16500]["OptionChkFunc11"] = function ()
	return Anniversary2015_ColorMatch_ChkOption()
end
tNpcGossip[16500]["OptionFunc11"] = "Anniversary2015_ColorMatch_GetColor</N>16499</N>3003507"
tNpcGossip[16500]["Option12"] = tAnniversary2015_ColorMatch_Text[16500]["Option12"]




------------------------------------------
-- // ==黄色颜料箱== \\
tNpcGossip[16501] = tNpcGossip[16501] or DefaultNpc:new{}
tNpcGossip[16501]["OptionHidden"] = 1
---【起始对白】
tNpcGossip[16501]["Text1-1"] = {111} 	-- 活动中对白
tNpcGossip[16501]["Text111"] = tAnniversary2015_ColorMatch_Text[16501]["Text111"]
--选项
tNpcGossip[16501]["tOption1-1"] = {11,12}		--活动中对白
tNpcGossip[16501]["Option11"] = tAnniversary2015_ColorMatch_Text[16501]["Option11"]
tNpcGossip[16501]["OptionChkFunc11"] = function ()
	return Anniversary2015_ColorMatch_ChkOption()
end
tNpcGossip[16501]["OptionFunc11"] = "Anniversary2015_ColorMatch_GetColor</N>16501</N>3003508"
tNpcGossip[16501]["Option12"] = tAnniversary2015_ColorMatch_Text[16501]["Option12"]



------------------------------------------
-- // ==蓝色颜料箱== \\
tNpcGossip[16502] = tNpcGossip[16502] or DefaultNpc:new{}
tNpcGossip[16502]["OptionHidden"] = 1
---【起始对白】
tNpcGossip[16502]["Text1-1"] = {111} 	-- 活动中对白
tNpcGossip[16502]["Text111"] = tAnniversary2015_ColorMatch_Text[16502]["Text111"]
--选项
tNpcGossip[16502]["tOption1-1"] = {11,12}		--活动中对白
tNpcGossip[16502]["Option11"] = tAnniversary2015_ColorMatch_Text[16502]["Option11"]
tNpcGossip[16502]["OptionChkFunc11"] = function ()
	return Anniversary2015_ColorMatch_ChkOption()
end
tNpcGossip[16502]["OptionFunc11"] = "Anniversary2015_ColorMatch_GetColor</N>16502</N>3003509"
tNpcGossip[16502]["Option12"] = tAnniversary2015_ColorMatch_Text[16502]["Option12"]



------------------------------------------物品配置-------------------------------------------
------------------------------------------
-- // ==调色板== \\
tItem[3003506] = tItem[3003506] or {} --调色板
tItem[3003506]["Function"] = function (nItemId,sItemName)
	--活动时间前
	if Sys_ChkFullTime(tAnniversary2015_ColorMatch_Data["Festival_BefTime"]) then
		return
	end

	--活动时间外
	if not Sys_ChkFullTime(tAnniversary2015_ColorMatch_Data["Festival_MidTime"]) then
		if Item_ChkItem(tAnniversary2015_ColorMatch_Data["ColorDisc"]) then
			Item_DelItem(tAnniversary2015_ColorMatch_Data["ColorDisc"])
			Sys_SaveActionFestivalLog(tAnniversary2015_ColorMatch_Log["DelColorDisc"])
			User_TalkChannel2005(tAnniversary2015_ColorMatch_Text["DelColorDisc"])
			return
		end
	end
	local sTaskColor = Get_SysDynaGlobalDataStr0(tAnniversary2015_ColorMatch_DynaGlobal["GlobalId"])
	local sText1 = string.format(tAnniversary2015_ColorMatch_Text["ColorDsic"]["Text1"],sTaskColor)
	
	--出对白
	Sys_DialogText(sText1)
	Sys_DialogText(tAnniversary2015_ColorMatch_Text["ColorDsic"]["Text2"])
	Sys_DialogText(tAnniversary2015_ColorMatch_Text["ColorDsic"]["Text3"])
	Sys_DialogText(tAnniversary2015_ColorMatch_Text["ColorDsic"]["Text4"])
	Sys_DialogText(tAnniversary2015_ColorMatch_Text["ColorDsic"]["Text5"])
	Sys_DialogText(tAnniversary2015_ColorMatch_Text["ColorDsic"]["Text6"])
	Sys_DialogOption(tAnniversary2015_ColorMatch_Text["ColorDsic"]["Option1"],"</F>Anniversary2015_ColorMatch_CloseColorDisc")
	Sys_DialogEnd()
end


------------------------------------------
-- // ==红色== \\
tItem[3003507] = tItem[3003507] or {}
tItem[3003507]["Function"] = function (nItemId,sItemName)
	--颜料初始判断函数
	if not Anniversary2015_ColorMatch_AddColorBegin(nItemId) then
		return
	end

	--橙=红+黄
	if Anniversary2015_ColorMatch_ColorForm("Orange","Red","Yellow") then
		return
		
	--紫=红+蓝
	elseif Anniversary2015_ColorMatch_ColorForm("Violet","Red","Blue") then
		return
		
	--黑=红+绿
	elseif Anniversary2015_ColorMatch_ColorForm("Black","Red","Green") then
		return
	
	--颜色不对
	else
		Anniversary2015_ColorMatch_AddColorFail(nItemId,"Red","Orange","Violet")
	end
end

-- // ==黄色== \\
tItem[3003508] = tItem[3003508] or {}
tItem[3003508]["Function"] = function (nItemId,sItemName)
	--颜料初始判断函数
	if not Anniversary2015_ColorMatch_AddColorBegin(nItemId) then
		return
	end

	--橙=红+黄
	if Anniversary2015_ColorMatch_ColorForm("Orange","Yellow","Red") then
		return
		
	--绿=黄+蓝
	elseif Anniversary2015_ColorMatch_ColorForm("Green","Yellow","Blue") then
		return
	
	--黑=紫+黄
	elseif Anniversary2015_ColorMatch_ColorForm("Black","Yellow","Violet") then
	
	--颜色不对
	else
		Anniversary2015_ColorMatch_AddColorFail(nItemId,"Yellow","Orange","Green")
	end
end



-- // ==蓝色== \\
tItem[3003509] = tItem[3003509] or {}
tItem[3003509]["Function"] = function (nItemId,sItemName)
	--颜料初始判断函数
	if not Anniversary2015_ColorMatch_AddColorBegin(nItemId) then
		return
	end

	--紫=蓝+红
	if Anniversary2015_ColorMatch_ColorForm("Violet","Blue","Red") then
		return
		
	--绿=蓝+黄
	elseif Anniversary2015_ColorMatch_ColorForm("Green","Blue","Yellow") then
		return
		
	--黑=蓝+橙
	elseif Anniversary2015_ColorMatch_ColorForm("Black","Blue","Orange") then
	
	--颜色不对
	else
		Anniversary2015_ColorMatch_AddColorFail(nItemId,"Blue","Violet","Green")
	end
end



-- // ==橙色== \\
tItem[3003510] = tItem[3003510] or {}
tItem[3003510]["Function"] = function (nItemId,sItemName)
	--颜料初始判断函数
	if not Anniversary2015_ColorMatch_AddColorBegin(nItemId) then
		return
	end

	--黑=橙+蓝
	if Anniversary2015_ColorMatch_ColorForm("Black","Orange","Blue") then
		return
	
	--颜色不对
	else
		Anniversary2015_ColorMatch_AddColorFail(nItemId,"Red","Yellow","Orange","Violet","Green")
	end
end



-- // ==紫色== \\
tItem[3003511] = tItem[3003511] or {}
tItem[3003511]["Function"] = function (nItemId,sItemName)
	--颜料初始判断函数
	if not Anniversary2015_ColorMatch_AddColorBegin(nItemId) then
		return
	end

	--黑=紫+黄
	if Anniversary2015_ColorMatch_ColorForm("Black","Violet","Yellow") then
		return
	
	--颜色不对
	else
		Anniversary2015_ColorMatch_AddColorFail(nItemId,"Red","Blue","Orange","Violet","Green")
	end
end



-- // ==绿色== \\
tItem[3003512] = tItem[3003512] or {}
tItem[3003512]["Function"] = function (nItemId,sItemName)
	--颜料初始判断函数
	if not Anniversary2015_ColorMatch_AddColorBegin(nItemId) then
		return
	end

	--黑=绿+红
	if Anniversary2015_ColorMatch_ColorForm("Black","Green","Red") then
		return
	
	--颜色不对
	else
		Anniversary2015_ColorMatch_AddColorFail(nItemId,"Yellow","Blue","Orange","Violet","Green")
	end
end



-- // ==黑色== \\
tItem[3003513] = tItem[3003513] or {}
tItem[3003513]["Function"] = function (nItemId,sItemName)
	local sColor = tAnniversary2015_ColorMatch_Text[nItemId]
	--活动时间判断
	if not Sys_ChkFullTime(tAnniversary2015_ColorMatch_Data["Festival_MidTime"]) then
		--删除颜料
		if Item_ChkItem(nItemId) then
			Item_DelAllItemByType(nItemId)
			local sLogText = string.format(tAnniversary2015_ColorMatch_Log["DelColor"],nItemId)
			local sTalkText = string.format(tAnniversary2015_ColorMatch_Text["DelColor"],sColor)
			Sys_SaveActionFestivalLog(sLogText)
			User_TalkChannel2005(sTalkText)
		end
		return false
	end
end


------------------------------------------配置数据------------------------------------------
--时间函数触发
--'00:00 00:05'
--tOntimerMin_HM[0000] = tOntimerMin_HM[0000] or {}
--table.insert(tOntimerMin_HM[0000],Anniversary2015_ColorMatch_PrompetFunc)
--tOntimerMin_HM[0001] = tOntimerMin_HM[0001] or {}
--table.insert(tOntimerMin_HM[0001],Anniversary2015_ColorMatch_PrompetFunc)
--tOntimerMin_HM[0002] = tOntimerMin_HM[0002] or {}
--table.insert(tOntimerMin_HM[0002],Anniversary2015_ColorMatch_PrompetFunc)
--tOntimerMin_HM[0003] = tOntimerMin_HM[0003] or {}
--table.insert(tOntimerMin_HM[0003],Anniversary2015_ColorMatch_PrompetColose)
--tOntimerMin_HM[0004] = tOntimerMin_HM[0004] or {}
--table.insert(tOntimerMin_HM[0004],Anniversary2015_ColorMatch_PrompetColose)
--tOntimerMin_HM[0005] = tOntimerMin_HM[0005] or {}
--table.insert(tOntimerMin_HM[0005],Anniversary2015_ColorMatch_PrompetColose)
