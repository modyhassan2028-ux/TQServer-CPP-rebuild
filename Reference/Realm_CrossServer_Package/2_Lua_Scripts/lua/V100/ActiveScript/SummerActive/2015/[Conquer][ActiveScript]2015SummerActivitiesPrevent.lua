------------------------------------------------------------------------------------
--Name:			[简体征服][活动脚本]2015暑期活动(7.9-7.22)
--Purpose:		
--Creator: 		张磊
--Created:		05/11/2015
------------------------------------------------------------------------------------

------------------------------------------------------------------------------------
--[[掩码说明
##stc(115,12):记录试用纯天然植物防晒霜的情况（==1表示正在试用中，==2表示试用失败）
##stc(115,13):记录试用水嫩防过敏防晒霜的情况（==1表示正在试用中，==2表示试用失败）
##stc(115,14):记录试用橄榄油隔离防晒霜的情况（==1表示正在试用中，==2表示试用失败）
]]--

--LOGid 12000093
--节日通用礼包taskID  3432
------------------------------------------------------------------------------------
--命名规范
--SummerActivities_Prevent_
------------------------------------------------------------------------------------------------------------------------------------------------------------------------


------------------------------------------常量表配置-------------------------------------------
local SummerActivities_Prevent_Cont = {}
	--活动时间、
	SummerActivities_Prevent_Cont["ActivityTime"] = "2015-07-09 00:00 2015-07-22 23:59"
	SummerActivities_Prevent_Cont["BeforeActivityTime"] = "2015-01-01 00:00 2015-07-08 23:59"
	
	--玩家等级以及转世要求
	SummerActivities_Prevent_Cont["Metempsychosis"] = 0
	SummerActivities_Prevent_Cont["Level"] = 80
	
	--掩码（记录玩家任务状态）
	SummerActivities_Prevent_Cont["Notask"] = 0
	SummerActivities_Prevent_Cont["Trialing"] = 1
	SummerActivities_Prevent_Cont["Failure"] = 2
	--完成
	SummerActivities_Prevent_Cont["Complete"] = 10
	--时间间隔30分钟
	SummerActivities_Prevent_Cont["Interval"] = 1800
	
	--115 15  = 0 = 1 >1
	SummerActivities_Prevent_Cont["data_0"] = 0
	SummerActivities_Prevent_Cont["data_1"] = 1
	
	SummerActivities_Prevent_Cont["Space"] = 1
	
	SummerActivities_Prevent_Cont["FestivalId"] = 3432
	
	--掩码	
local SummerActivities_Prevent_Stc = {}
	--记录成功完成任务的掩码
	SummerActivities_Prevent_Stc["Event_type"] = 115
	SummerActivities_Prevent_Stc["Data_type"] = 15

	--纯天然植物防晒霜
	SummerActivities_Prevent_Stc[11512]= {}
	SummerActivities_Prevent_Stc[11512]["Event_type"] = 115
	SummerActivities_Prevent_Stc[11512]["Data_type"] = 12

	--水嫩防过敏防晒霜
	SummerActivities_Prevent_Stc[11513]= {}
	SummerActivities_Prevent_Stc[11513]["Event_type"] = 115
	SummerActivities_Prevent_Stc[11513]["Data_type"] = 13

	--橄榄油隔离防晒霜
	SummerActivities_Prevent_Stc[11514]= {}
	SummerActivities_Prevent_Stc[11514]["Event_type"] = 115
	SummerActivities_Prevent_Stc[11514]["Data_type"] = 14

local SummerActivities_Prevent_Log = {}
	--SummerActivities_Prevent_Log["RewardItem"] = "0,0,0,0,12000093,2,3007625,1"
	SummerActivities_Prevent_Log["RewardItem"] = 12000093



--------------------------------------逻辑部分-------------------------------------------
--判断任务完成情况
function SummerActivities_Prevent_ChkComplete()
	
	local nEvent = SummerActivities_Prevent_Stc["Event_type"]
	local nType = SummerActivities_Prevent_Stc["Data_type"]
	local nComplete = SummerActivities_Prevent_Cont["Complete"]
	if Task_ChkStcValue(nEvent,nType,">=",nComplete) then
		-- 判断是否隔天
		if Task_StcInterval(nEvent,nType,1,4) then
			Task_SetStatistic(nEvent,nType,0,1,0)
			Task_SetStcTimestamp(nEvent,nType,0,0)

			local nEvent_11512 = SummerActivities_Prevent_Stc[11512]["Event_type"]
			local nType_11512 = SummerActivities_Prevent_Stc[11512]["Data_type"]

			local nEvent_11513 = SummerActivities_Prevent_Stc[11513]["Event_type"]
			local nType_11513 = SummerActivities_Prevent_Stc[11513]["Data_type"]

			local nEvent_11514 = SummerActivities_Prevent_Stc[11514]["Event_type"]
			local nType_11514 = SummerActivities_Prevent_Stc[11514]["Data_type"]

			Task_SetStatistic(nEvent_11512,nType_11512,0,1,0)			
			Task_SetStatistic(nEvent_11513,nType_11513,0,1,0)			
			Task_SetStatistic(nEvent_11514,nType_11514,0,1,0)			
			
			return false
		else
			return true
		end
	else
		return false		
	end 
end

--检测效果
function SummerActivities_Prevent_Effect(nNpcId)
	if not Sys_ChkFullTime(SummerActivities_Prevent_Cont["ActivityTime"]) then
		LinkNpcGossipFunc_New(nNpcId,"1-3")
		return
	end
	
	if not User_JudgeLevelAndMetempsychosis(SummerActivities_Prevent_Cont["Level"],SummerActivities_Prevent_Cont["Metempsychosis"]) then
		LinkNpcGossipFunc_New(nNpcId,"2-1")
		return
	end
	
	if SummerActivities_Prevent_ChkComplete() then
		LinkNpcGossipFunc_New(nNpcId,"3-1")
		return
	end
	
	--判断背包
	if not User_CheckLeftSpace(SummerActivities_Prevent_Cont["Space"]) then
		LinkNpcGossipFunc_New(nNpcId,"5-1")
		return
	end
	
	local nEvent = SummerActivities_Prevent_Stc[11512]["Event_type"]
	local nType = SummerActivities_Prevent_Stc[11512]["Data_type"]
	local nTrial = SummerActivities_Prevent_Cont["Trialing"]
	if Task_ChkStcValue(nEvent,nType,"==",nTrial) then		
		SummerActivities_Prevent_JudEffect(nNpcId,nEvent,nType,nTrial)
		return
	end
	
	local nEvent = SummerActivities_Prevent_Stc[11513]["Event_type"]
	local nType = SummerActivities_Prevent_Stc[11513]["Data_type"]
	if Task_ChkStcValue(nEvent,nType,"==",nTrial) then
		SummerActivities_Prevent_JudEffect(nNpcId,nEvent,nType,nTrial)
		return	
	end
	
	local nEvent = SummerActivities_Prevent_Stc[11514]["Event_type"]
	local nType = SummerActivities_Prevent_Stc[11514]["Data_type"]
	if Task_ChkStcValue(nEvent,nType,"==",nTrial) then
 		SummerActivities_Prevent_JudEffect(nNpcId,nEvent,nType,nTrial)
		return   
	end
	
	LinkNpcGossipFunc_New(nNpcId,"6-1")
	
end

--判断测试结果
function SummerActivities_Prevent_JudEffect(nNpcId,nEvent,nType,nTrial)
	local nTriTime = SummerActivities_Prevent_Cont["Interval"]
	
	if not Task_StcInterval(nEvent,nType,nTriTime,0) then
		LinkNpcGossipFunc_New(nNpcId,"10-1")
		return		
	end
	
	local nEvent_11515 = SummerActivities_Prevent_Stc["Event_type"]
	local nType_11515 = SummerActivities_Prevent_Stc["Data_type"]
	-- local nData_0 = SummerActivities_Prevent_Cont["data_0"]
	-- local nData_1 = SummerActivities_Prevent_Cont["data_1"]
	
	
	local nComplete = SummerActivities_Prevent_Cont["Complete"]
	
	Task_SetStatistic(nEvent_11515,nType_11515,nComplete,1,0)
	Task_SetStcTimestamp(nEvent_11515,nType_11515,0,0)
			
	--给奖励
	FestivalGeneralPackage_GetGift(SummerActivities_Prevent_Cont["FestivalId"],SummerActivities_Prevent_Log["RewardItem"])

	Sys_MsgBox(SummerActivities_Prevent_Text["Successful"])				

end
	
--判断三个选项出现的条件
function SummerActivities_Prevent_Condition(nEvent,nType,nData1)
	if not Sys_ChkFullTime(SummerActivities_Prevent_Cont["ActivityTime"]) then
		return false
		
	elseif Task_StcInterval(nEvent,nType,1,4) then
			Task_SetStatistic(nEvent,nType,0,1,0)
			--Task_SetStcTimestamp(nEvent,nType,0,0)
			return true
	elseif Task_ChkStcValue(nEvent,nType,">",nData1) then
		return false
	else
		return true
	end
	
end

--点击测试选项
function SummerActivities_Prevent_Click(nNpcId,nEvent,nType)
	if not Sys_ChkFullTime(SummerActivities_Prevent_Cont["ActivityTime"]) then
		LinkNpcGossipFunc_New(nNpcId,"1-3")
		return
	end
	
	if not User_JudgeLevelAndMetempsychosis(SummerActivities_Prevent_Cont["Level"],SummerActivities_Prevent_Cont["Metempsychosis"]) then
		LinkNpcGossipFunc_New(nNpcId,"2-1")
		return
	end
	
	if SummerActivities_Prevent_ChkComplete() then
		LinkNpcGossipFunc_New(nNpcId,"3-1")
		return
	end
	local nNothing = SummerActivities_Prevent_Cont["Notask"]
	local nTrial = SummerActivities_Prevent_Cont["Trialing"]
	
	if Task_ChkStcValue(nEvent,nType,"==",nNothing) then
		--==00
		Task_SetStatistic(nEvent,nType,nTrial,1,0)
		Task_SetStcTimestamp(nEvent,nType,0,0)
		SummerActivities_Prevent_Less(nType)
		
		return
		
	elseif Task_ChkStcValue(nEvent,nType,"==",nTrial) then
			if Task_StcInterval(nEvent,nType,1,4) then
				Task_SetStcTimestamp(nEvent,nType,0,0)	
				SummerActivities_Prevent_Less(nType)
			elseif Task_StcInterval(nEvent,nType,SummerActivities_Prevent_Cont["Interval"],0) then
				SummerActivities_Prevent_More(nType)
			else
				SummerActivities_Prevent_Less(nType)
			end
	end
	
end


--给提示函数
function SummerActivities_Prevent_Less(nType)
	if nType == SummerActivities_Prevent_Stc[11512]["Data_type"] then
		Sys_MsgBox(SummerActivities_Prevent_Text["Lessthan30minutes11512"])
			
	elseif nType == SummerActivities_Prevent_Stc[11513]["Data_type"] then
		Sys_MsgBox(SummerActivities_Prevent_Text["Lessthan30minutes11513"])
			
	elseif nType == SummerActivities_Prevent_Stc[11514]["Data_type"] then
		Sys_MsgBox(SummerActivities_Prevent_Text["Lessthan30minutes11514"])			
	end
end

function SummerActivities_Prevent_More(nType)
	if nType == SummerActivities_Prevent_Stc[11512]["Data_type"] then
		Sys_MsgBox(SummerActivities_Prevent_Text["Morethan30minutes11514"])
			
	elseif nType == SummerActivities_Prevent_Stc[11513]["Data_type"] then
		Sys_MsgBox(SummerActivities_Prevent_Text["Morethan30minutes11514"])
			
	elseif nType == SummerActivities_Prevent_Stc[11514]["Data_type"] then
		Sys_MsgBox(SummerActivities_Prevent_Text["Morethan30minutes11514"])			
	end
end

--------------------------------------NPC模块-------------------------------------------
tNpcFace[2496] = 158
tNpcGossip[15810] = tNpcGossip[15810] or DefaultNpc:new{}
tNpcGossip[15810]["OptionHidden"] = 1

--活动前
tNpcGossip[15810]["Text1-1"] = {111,112,113,114}
tNpcGossip[15810]["Text111"] = SummerActivities_Prevent_Text[15810]["Text111"]
tNpcGossip[15810]["Text112"] = SummerActivities_Prevent_Text[15810]["Text112"]
tNpcGossip[15810]["Text113"] = SummerActivities_Prevent_Text[15810]["Text113"]
tNpcGossip[15810]["Text114"] = SummerActivities_Prevent_Text[15810]["Text114"]
tNpcGossip[15810]["tOption1-1"] = {1}
tNpcGossip[15810]["ChkFunc1-1"] = function()
	return Sys_ChkFullTime(SummerActivities_Prevent_Cont["BeforeActivityTime"])
end
--活动中
tNpcGossip[15810]["Text1-2"] = {121,122,123,124,125}
tNpcGossip[15810]["Text121"] = SummerActivities_Prevent_Text[15810]["Text121"]
tNpcGossip[15810]["Text122"] = SummerActivities_Prevent_Text[15810]["Text122"]
tNpcGossip[15810]["Text123"] = SummerActivities_Prevent_Text[15810]["Text123"]
tNpcGossip[15810]["Text124"] = SummerActivities_Prevent_Text[15810]["Text124"]
tNpcGossip[15810]["Text125"] = SummerActivities_Prevent_Text[15810]["Text125"]
tNpcGossip[15810]["tOption1-2"] = {2,3,4}
tNpcGossip[15810]["ChkFunc1-2"] = function()
	return Sys_ChkFullTime(SummerActivities_Prevent_Cont["ActivityTime"])
end

--活动后	
tNpcGossip[15810]["Text1-3"] = {131,132}
tNpcGossip[15810]["Text131"] = SummerActivities_Prevent_Text[15810]["Text131"]
tNpcGossip[15810]["Text132"] = SummerActivities_Prevent_Text[15810]["Text132"]
tNpcGossip[15810]["tOption1-3"] = {5}

--等级不够提示
tNpcGossip[15810]["Text2-1"] = {211,212}
tNpcGossip[15810]["Text211"] = SummerActivities_Prevent_Text[15810]["Text211"]
tNpcGossip[15810]["Text212"] = SummerActivities_Prevent_Text[15810]["Text212"]
tNpcGossip[15810]["tOption2-1"] = {6}

--当天已经测试过了提示
tNpcGossip[15810]["Text3-1"] = {311}
tNpcGossip[15810]["Text311"] = SummerActivities_Prevent_Text[15810]["Text311"]
tNpcGossip[15810]["tOption3-1"] = {7}

--点击选择防晒霜测试，进入下一层对白
tNpcGossip[15810]["Text4-1"] = {411,412,413}
tNpcGossip[15810]["Text411"] = SummerActivities_Prevent_Text[15810]["Text411"]
tNpcGossip[15810]["Text412"] = SummerActivities_Prevent_Text[15810]["Text412"]
tNpcGossip[15810]["Text413"] = SummerActivities_Prevent_Text[15810]["Text413"]
tNpcGossip[15810]["tOption4-1"] = {8,9,10,11}

--背包空间不足
tNpcGossip[15810]["Text5-1"] = {511}
tNpcGossip[15810]["Text511"] = SummerActivities_Prevent_Text[15810]["Text511"]
tNpcGossip[15810]["tOption5-1"] = {12}

--没有测试过提示
tNpcGossip[15810]["Text6-1"] = {611}
tNpcGossip[15810]["Text611"] = SummerActivities_Prevent_Text[15810]["Text611"]
tNpcGossip[15810]["tOption6-1"] = {13}

--第一种防晒霜
--测试失败
tNpcGossip[15810]["Text7-1"] = {711}
tNpcGossip[15810]["Text711"] = SummerActivities_Prevent_Text[15810]["Text711"]
tNpcGossip[15810]["tOption7-1"] = {14}

--第二种防晒霜
--测试失败	
tNpcGossip[15810]["Text8-1"] = {811}
tNpcGossip[15810]["Text811"] = SummerActivities_Prevent_Text[15810]["Text811"]
tNpcGossip[15810]["tOption8-1"] = {14}
	
--第三种防晒霜
--测试失败
tNpcGossip[15810]["Text9-1"] = {911}
tNpcGossip[15810]["Text911"] = SummerActivities_Prevent_Text[15810]["Text911"]
tNpcGossip[15810]["tOption9-1"] = {15}

--使用防晒霜不足30分钟给提示	
tNpcGossip[15810]["Text10-1"] = {1011}
tNpcGossip[15810]["Text1011"] = SummerActivities_Prevent_Text[15810]["Text1011"]
tNpcGossip[15810]["tOption10-1"] = {16}


--选项
tNpcGossip[15810]["Option1"] = SummerActivities_Prevent_Text[15810]["Option1"]
tNpcGossip[15810]["Option2"] = SummerActivities_Prevent_Text[15810]["Option2"]
tNpcGossip[15810]["OptionPoint2"]="4-1"
tNpcGossip[15810]["OptionChkFunc2"] = function ()
	return not SummerActivities_Prevent_ChkComplete() and Sys_ChkFullTime(SummerActivities_Prevent_Cont["ActivityTime"])
end

tNpcGossip[15810]["Option3"] = SummerActivities_Prevent_Text[15810]["Option3"]
tNpcGossip[15810]["OptionFunc3"]="SummerActivities_Prevent_Effect</N>15810"
tNpcGossip[15810]["OptionChkFunc3"] = function ()
	return not SummerActivities_Prevent_ChkComplete() and Sys_ChkFullTime(SummerActivities_Prevent_Cont["ActivityTime"])
end

tNpcGossip[15810]["Option4"] = SummerActivities_Prevent_Text[15810]["Option4"]
tNpcGossip[15810]["Option5"] = SummerActivities_Prevent_Text[15810]["Option5"]
tNpcGossip[15810]["Option6"] = SummerActivities_Prevent_Text[15810]["Option6"]
tNpcGossip[15810]["Option7"] = SummerActivities_Prevent_Text[15810]["Option7"]

tNpcGossip[15810]["Option8"] = SummerActivities_Prevent_Text[15810]["Option8"]
tNpcGossip[15810]["OptionFunc8"]="SummerActivities_Prevent_Click</N>15810</N>115</N>12"
tNpcGossip[15810]["OptionChkFunc8"] = function ()
	local nEvent = SummerActivities_Prevent_Stc[11512]["Event_type"]
	local nType = SummerActivities_Prevent_Stc[11512]["Data_type"]
	local nData1 = SummerActivities_Prevent_Cont["Trialing"]
	return SummerActivities_Prevent_Condition(nEvent,nType,nData1)
end

tNpcGossip[15810]["Option9"] = SummerActivities_Prevent_Text[15810]["Option9"]
tNpcGossip[15810]["OptionFunc9"]="SummerActivities_Prevent_Click</N>15810</N>115</N>13"
tNpcGossip[15810]["OptionChkFunc9"] = function ()
	local nEvent = SummerActivities_Prevent_Stc[11513]["Event_type"]
	local nType = SummerActivities_Prevent_Stc[11513]["Data_type"]
	local nData1 = SummerActivities_Prevent_Cont["Trialing"]
	return SummerActivities_Prevent_Condition(nEvent,nType,nData1)
end

tNpcGossip[15810]["Option10"] = SummerActivities_Prevent_Text[15810]["Option10"]
tNpcGossip[15810]["OptionFunc10"]="SummerActivities_Prevent_Click</N>15810</N>115</N>14"
tNpcGossip[15810]["OptionChkFunc10"] = function ()
	local nEvent = SummerActivities_Prevent_Stc[11514]["Event_type"]
	local nType = SummerActivities_Prevent_Stc[11514]["Data_type"]
	local nData1 = SummerActivities_Prevent_Cont["Trialing"]
	return SummerActivities_Prevent_Condition(nEvent,nType,nData1)
end

tNpcGossip[15810]["Option11"] = SummerActivities_Prevent_Text[15810]["Option11"]
tNpcGossip[15810]["Option12"] = SummerActivities_Prevent_Text[15810]["Option12"]
tNpcGossip[15810]["Option13"] = SummerActivities_Prevent_Text[15810]["Option13"]
tNpcGossip[15810]["Option14"] = SummerActivities_Prevent_Text[15810]["Option14"]
tNpcGossip[15810]["Option15"] = SummerActivities_Prevent_Text[15810]["Option15"]
tNpcGossip[15810]["Option16"] = SummerActivities_Prevent_Text[15810]["Option16"]
	
