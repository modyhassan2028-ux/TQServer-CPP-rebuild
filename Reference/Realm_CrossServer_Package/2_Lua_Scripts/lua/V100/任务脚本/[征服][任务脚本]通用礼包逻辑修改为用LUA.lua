------------------------------------------------------------------------------------
--Name:		[征服][任务脚本]通用礼包逻辑修改为用LUA
--Purpose:	通用礼包逻辑修改为用LUA
--Creator: 	严振飞
--Created:	2014/10/28
------------------------------------------------------------------------------------
--任务需求：
---将通用礼包逻辑修改为用lua编写，避免麻烦的update 并防止出错
------------------------------------------------------------------------------------
--物品：
---3003625--节日欢庆礼包--没有转世
---3003626--节日欢庆礼包--1转
---3003627--节日欢庆礼包--2转
------------------------------------------------------------------------------------
--掩码说明
---stc(131,74) 记录领取奖励次数--2015年情人节活动

--LOGid说明
---10002397 --2015年情人节活动
------------------------------------------------------------------------------------
--命名规范
--FestivalGeneralPackage_
---------------------------------------活动数据---------------------------------------------
--活动数据
local tFestivalGeneralPackage_Data = {}
------------------------------------------------------------------------------------
	--【SQL调用例子】：
	--//传入的参数为    nFestivalId
	--(94999999,0,0,20002,0,'FestivalGeneralPackage_GetGift 1');


	--tFestivalGeneralPackage_Data[nFestivalId] = {}
	--tFestivalGeneralPackage_Data[nFestivalId]["Stc"] = {}
	--....
	--nFestivalId 表示：相应任务的唯一任务ID
-----------------------------------
	--活动1
	--[[
	tFestivalGeneralPackage_Data[1] = {}
	tFestivalGeneralPackage_Data[1]["Stc"] = {}
	tFestivalGeneralPackage_Data[1]["Stc"]["Event"] = 124
	tFestivalGeneralPackage_Data[1]["Stc"]["Type"] = 30
	tFestivalGeneralPackage_Data[1]["Festival_Time"] = '2014-11-23 00:00 2014-11-29 23:59'
	tFestivalGeneralPackage_Data[1]["GetGift_Limit"] = 8
	tFestivalGeneralPackage_Data[1]["CheckLeftSpace"] = 1
	]]--
-----------------------------------
	--2015年情人节活动
	tFestivalGeneralPackage_Data[3353] = {}
	tFestivalGeneralPackage_Data[3353]["Stc"] = {}
	tFestivalGeneralPackage_Data[3353]["Stc"]["Event"] = 131
	tFestivalGeneralPackage_Data[3353]["Stc"]["Type"] = 74
	tFestivalGeneralPackage_Data[3353]["Festival_Time"] = '2015-02-11 00:00 2015-02-14 23:59'
	tFestivalGeneralPackage_Data[3353]["GetGift_Limit"] = 7
	tFestivalGeneralPackage_Data[3353]["CheckLeftSpace"] = 1
	
------------------------------------------------------------------------------------
--额外物品数据（可添加多个额外物品）
local tFestivalGeneralPackage_AdditionalGift = {}
-----------------------------------
	--活动1新增物品
	--tFestivalGeneralPackage_AdditionalGift[1] = {}
	--未转世增加额外物品
	--[[
	tFestivalGeneralPackage_AdditionalGift[1][3003625] = {}
	tFestivalGeneralPackage_AdditionalGift[1][3003625]["Add_Num"] = 2

	tFestivalGeneralPackage_AdditionalGift[1][3003625][1] = {}
	tFestivalGeneralPackage_AdditionalGift[1][3003625][1]["Add_ItemId"] = nil
	tFestivalGeneralPackage_AdditionalGift[1][3003625][1]["Add_Num"] = 1

	tFestivalGeneralPackage_AdditionalGift[1][3003625][2] = {}
	tFestivalGeneralPackage_AdditionalGift[1][3003625][2]["Add_ItemId"] = nil
	tFestivalGeneralPackage_AdditionalGift[1][3003625][2]["Add_Num"] = 1

	--1转增加额外物品
	tFestivalGeneralPackage_AdditionalGift[1][3003626] = {}
	tFestivalGeneralPackage_AdditionalGift[1][3003626]["Add_Num"] = 2

	tFestivalGeneralPackage_AdditionalGift[1][3003626][1] = {}
	tFestivalGeneralPackage_AdditionalGift[1][3003626][1]["Add_ItemId"] = nil
	tFestivalGeneralPackage_AdditionalGift[1][3003626][1]["Add_Num"] = 1

	tFestivalGeneralPackage_AdditionalGift[1][3003626][2] = {}
	tFestivalGeneralPackage_AdditionalGift[1][3003626][2]["Add_ItemId"] = nil
	tFestivalGeneralPackage_AdditionalGift[1][3003626][2]["Add_Num"] = 1

	--2转以上增加额外物品
	tFestivalGeneralPackage_AdditionalGift[1][3003627] = {}
	tFestivalGeneralPackage_AdditionalGift[1][3003627]["Add_Num"] = 2
	
	tFestivalGeneralPackage_AdditionalGift[1][3003627][1] = {}
	tFestivalGeneralPackage_AdditionalGift[1][3003627][1]["Add_ItemId"] = nil
	tFestivalGeneralPackage_AdditionalGift[1][3003627][1]["Add_Num"] = 1

	tFestivalGeneralPackage_AdditionalGift[1][3003627][2] = {}
	tFestivalGeneralPackage_AdditionalGift[1][3003627][2]["Add_ItemId"] = nil
	tFestivalGeneralPackage_AdditionalGift[1][3003627][2]["Add_Num"] = 1
-----------------------------------
	--活动XXX新增物品
	....
	]]--


------------------------------------------固定数据------------------------------------------
--玩家转世
local tFestivalGeneralPackage_Metempsychosis = {}
	tFestivalGeneralPackage_Metempsychosis["Max"] = 2

--礼包种类
local tFestivalGeneralPackage_GfitType = {}
	tFestivalGeneralPackage_GfitType[1] = 3003625 --没有转世
	tFestivalGeneralPackage_GfitType[2] = 3003626 --1转
	tFestivalGeneralPackage_GfitType[3] = 3003627 --2转
	
	tFestivalGeneralPackage_GfitType["Log"] = {}
	tFestivalGeneralPackage_GfitType["Log"][1] = "3003625,1"
	tFestivalGeneralPackage_GfitType["Log"][2] = "3003626,1"
	tFestivalGeneralPackage_GfitType["Log"][3] = "3003627,1"
--动态存储表
local tFestivalGeneralPackage_DynaGlobalData = {}
	tFestivalGeneralPackage_DynaGlobalData[1] = 80114
	tFestivalGeneralPackage_DynaGlobalData[2] = 80115
	tFestivalGeneralPackage_DynaGlobalData[3] = 80116
--LOG数据
local tFestivalGeneralPackage_LogMain = {}
	tFestivalGeneralPackage_LogMain["Log_Text"] = "0,0,0,0,%d,2,%s"
------------------------------------------逻辑部分------------------------------------------
function FestivalGeneralPackage_GetGift(nFestivalId,nLogId)

	---活动时间
	if not Sys_ChkFullTime(tFestivalGeneralPackage_Data[nFestivalId]["Festival_Time"]) then
		return
	end

	---是否隔1天
	if Task_StcInterval(tFestivalGeneralPackage_Data[nFestivalId]["Stc"]["Event"],tFestivalGeneralPackage_Data[nFestivalId]["Stc"]["Type"],1,4) then
		Task_SetStatistic(tFestivalGeneralPackage_Data[nFestivalId]["Stc"]["Event"],tFestivalGeneralPackage_Data[nFestivalId]["Stc"]["Type"],0,0)
		Task_SetStcTimestamp(tFestivalGeneralPackage_Data[nFestivalId]["Stc"]["Event"],tFestivalGeneralPackage_Data[nFestivalId]["Stc"]["Type"],0)
	end

	---礼包领取次数是否超过限制
	if Task_ChkStcValue(tFestivalGeneralPackage_Data[nFestivalId]["Stc"]["Event"],tFestivalGeneralPackage_Data[nFestivalId]["Stc"]["Type"],">=",tFestivalGeneralPackage_Data[nFestivalId]["GetGift_Limit"]) then
		Sys_MsgBox(string.format(tFestivalGeneralPackage["OverLimit_Msg"],tFestivalGeneralPackage_Data[nFestivalId]["GetGift_Limit"]))
		return
	end

	--背包空格检测
	if not User_CheckLeftSpace(tFestivalGeneralPackage_Data[nFestivalId]["CheckLeftSpace"]) then
		Sys_MsgBox(tFestivalGeneralPackage["Bag_Full"])
		return
	end
	
	--STC掩码设置
	Task_AddStatistic(tFestivalGeneralPackage_Data[nFestivalId]["Stc"]["Event"],tFestivalGeneralPackage_Data[nFestivalId]["Stc"]["Type"],1,0)
	Task_SetStcTimestamp(tFestivalGeneralPackage_Data[nFestivalId]["Stc"]["Event"],tFestivalGeneralPackage_Data[nFestivalId]["Stc"]["Type"],0)

	--玩家转世判断,给礼包
	local nItemId = 0
	local sLog_Table = ""
	local nMetempsychosis = Get_UserMetempsychosis()
	if nMetempsychosis >= tFestivalGeneralPackage_Metempsychosis["Max"] then
		nItemId = tFestivalGeneralPackage_GfitType[3]
		sLog_Table = tFestivalGeneralPackage_GfitType["Log"][3]
	else
		nItemId = tFestivalGeneralPackage_GfitType[nMetempsychosis + 1]
		sLog_Table = tFestivalGeneralPackage_GfitType["Log"][nMetempsychosis + 1]
	end
	Item_AddItem(nItemId)

	---额外礼包
	local tLog = {}
	local nIndex = 1
	local sItemId = tostring(nItemId)
	local sAdd_Num = "1"
	if tFestivalGeneralPackage_AdditionalGift[nFestivalId] ~= nil then
		for i=1,tFestivalGeneralPackage_AdditionalGift[nFestivalId][nItemId]["Add_Num"] do
			if tFestivalGeneralPackage_AdditionalGift[nFestivalId][nItemId][i]["Add_ItemId"] ~= nil then
				Item_AddItem(tFestivalGeneralPackage_AdditionalGift[nFestivalId][nItemId][i]["Add_ItemId"])
				tLog["ItemId"] = tFestivalGeneralPackage_AdditionalGift[nFestivalId][nItemId][i]["Add_ItemId"]
				tLog["Add_Num"] = tFestivalGeneralPackage_AdditionalGift[nFestivalId][nItemId][i]["Add_Num"]
				
				--log内容组合
				sItemId = sItemId .."[".. tLog["ItemId"] .."]"
				sAdd_Num = sAdd_Num .."[".. tLog["Add_Num"] .."]"
				sLog_Table = sItemId..","..sAdd_Num
			end
		end
	end
	--提示
	local sText = string.format(tFestivalGeneralPackage_LogMain["Log_Text"],nLogId,sLog_Table)
	User_TalkChannel2005(tFestivalGeneralPackage["Get_Gift"])
	Sys_SaveActionFestivalLog(sText)
end



---------------------------------------系统自检逻辑部分------------------------------------------
--// 关闭重置限制
function FestivalGeneralPackag_ResetLimit()
	Sys_SetSynaGlobalData0(tFestivalGeneralPackage_DynaGlobalData[1],0)
end

--// 活动列表循环检测
function FestivalGeneralPackag_ResetDataTable()
	for nFestivalId,v in pairs(tFestivalGeneralPackage_Data) do
		FestivalGeneralPackag_Reset(nFestivalId)
	end
end

--// 系统自检重置动态存储表
function FestivalGeneralPackag_Reset(nFestivalId)

	---活动时间
	if not Sys_ChkFullTime(tFestivalGeneralPackage_Data[nFestivalId]["Festival_Time"]) then
		return
	end
	
	--判断重置限制是否打开
	local nDynaGlobalData0 = Get_SysDynaGlobalData0(tFestivalGeneralPackage_DynaGlobalData[1])
	if nDynaGlobalData0 == 1 then
		return
	end

	--判断时间段，执行动态存储表清零
	if Sys_ChkDayTime("02:00 02:01") or Sys_ChkDayTime("10:00 10:01") or Sys_ChkDayTime("18:00 18:01") then
		Sys_ResetAllSynaGlobalData(tFestivalGeneralPackage_DynaGlobalData[1])
		Sys_ResetAllSynaGlobalData(tFestivalGeneralPackage_DynaGlobalData[2])
		Sys_ResetAllSynaGlobalData(tFestivalGeneralPackage_DynaGlobalData[3])
		
		Sys_SetSynaGlobalData0(tFestivalGeneralPackage_DynaGlobalData[1],1)
	elseif Sys_ChkDayTime("06:00 06:01") or Sys_ChkDayTime("14:00 14:01") or Sys_ChkDayTime("22:00 22:01") then
		Sys_SetSynaGlobalData2(tFestivalGeneralPackage_DynaGlobalData[1],0)
		Sys_SetSynaGlobalData3(tFestivalGeneralPackage_DynaGlobalData[1],0)
		Sys_SetSynaGlobalData4(tFestivalGeneralPackage_DynaGlobalData[1],0)
		
		Sys_SetSynaGlobalData1(tFestivalGeneralPackage_DynaGlobalData[2],0)
		Sys_SetSynaGlobalData3(tFestivalGeneralPackage_DynaGlobalData[2],0)
		Sys_SetSynaGlobalData5(tFestivalGeneralPackage_DynaGlobalData[2],0)
		
		Sys_SetSynaGlobalData0(tFestivalGeneralPackage_DynaGlobalData[1],1)
	end
end

------------------------------------------配置数据------------------------------------------
--时间函数触发
--'02:00 02:03'
tOntimerMin_HM[0200] = tOntimerMin_HM[0200] or {}
table.insert(tOntimerMin_HM[0200],FestivalGeneralPackag_ResetDataTable)
tOntimerMin_HM[0201] = tOntimerMin_HM[0201] or {}
table.insert(tOntimerMin_HM[0201],FestivalGeneralPackag_ResetDataTable)
tOntimerMin_HM[0202] = tOntimerMin_HM[0202] or {}
table.insert(tOntimerMin_HM[0202],FestivalGeneralPackag_ResetLimit)
tOntimerMin_HM[0203] = tOntimerMin_HM[0203] or {}
table.insert(tOntimerMin_HM[0203],FestivalGeneralPackag_ResetLimit)


--'06:00 06:03'
tOntimerMin_HM[0600] = tOntimerMin_HM[0600] or {}
table.insert(tOntimerMin_HM[0600],FestivalGeneralPackag_ResetDataTable)
tOntimerMin_HM[0601] = tOntimerMin_HM[0601] or {}
table.insert(tOntimerMin_HM[0601],FestivalGeneralPackag_ResetDataTable)
tOntimerMin_HM[0602] = tOntimerMin_HM[0602] or {}
table.insert(tOntimerMin_HM[0602],FestivalGeneralPackag_ResetLimit)
tOntimerMin_HM[0603] = tOntimerMin_HM[0603] or {}
table.insert(tOntimerMin_HM[0603],FestivalGeneralPackag_ResetLimit)


--'10:00 10:03'
tOntimerMin_HM[1000] = tOntimerMin_HM[1000] or {}
table.insert(tOntimerMin_HM[1000],FestivalGeneralPackag_ResetDataTable)
tOntimerMin_HM[1001] = tOntimerMin_HM[1001] or {}
table.insert(tOntimerMin_HM[1001],FestivalGeneralPackag_ResetDataTable)
tOntimerMin_HM[1002] = tOntimerMin_HM[1002] or {}
table.insert(tOntimerMin_HM[1002],FestivalGeneralPackag_ResetLimit)
tOntimerMin_HM[1003] = tOntimerMin_HM[1003] or {}
table.insert(tOntimerMin_HM[1003],FestivalGeneralPackag_ResetLimit)


--'14:00 14:03'
tOntimerMin_HM[1400] = tOntimerMin_HM[1400] or {}
table.insert(tOntimerMin_HM[1400],FestivalGeneralPackag_ResetDataTable)
tOntimerMin_HM[1401] = tOntimerMin_HM[1401] or {}
table.insert(tOntimerMin_HM[1401],FestivalGeneralPackag_ResetDataTable)
tOntimerMin_HM[1402] = tOntimerMin_HM[1402] or {}
table.insert(tOntimerMin_HM[1402],FestivalGeneralPackag_ResetLimit)
tOntimerMin_HM[1403] = tOntimerMin_HM[1403] or {}
table.insert(tOntimerMin_HM[1403],FestivalGeneralPackag_ResetLimit)


--'18:00 18:03'
tOntimerMin_HM[1800] = tOntimerMin_HM[1800] or {}
table.insert(tOntimerMin_HM[1800],FestivalGeneralPackag_ResetDataTable)
tOntimerMin_HM[1801] = tOntimerMin_HM[1801] or {}
table.insert(tOntimerMin_HM[1801],FestivalGeneralPackag_ResetDataTable)
tOntimerMin_HM[1802] = tOntimerMin_HM[1802] or {}
table.insert(tOntimerMin_HM[1802],FestivalGeneralPackag_ResetLimit)
tOntimerMin_HM[1803] = tOntimerMin_HM[1803] or {}
table.insert(tOntimerMin_HM[1803],FestivalGeneralPackag_ResetLimit)












