------------------------------------------------------------------------------------
--Name:		[征服][活动脚本]元宵节之热热闹闹舞龙灯
--Purpose:	元宵节之热热闹闹舞龙灯
--Creator: 	严振飞
--Created:	2014/12/09
------------------------------------------------------------------------------------
--[[
任务需求：


]]--
------------------------------------------------------------------------------------
--掩码说明
---stc(132,20) =1表示是完成任务，=2表示已领取奖励
---stc(132,21) （队长）记录队伍人数
---stc(132,23) （队长）记录符合条件人数

--LOGid 10002414
------------------------------------------------------------------------------------
--命名规范
--FestivalSpring2015_DragonLight_
------------------------------------------------------------------------------------
--STC掩码表
local tFestivalSpring2015_DragonLight_Stc = {}
----------------------------------------
--stc(132,20)--记录是否完成任务
	tFestivalSpring2015_DragonLight_Stc[1] = {}
	tFestivalSpring2015_DragonLight_Stc[1]["Event"] = 132
	tFestivalSpring2015_DragonLight_Stc[1]["Type"] = 20
	
--stc(132,21)--（队长）记录队伍人数
	tFestivalSpring2015_DragonLight_Stc[2] = {}
	tFestivalSpring2015_DragonLight_Stc[2]["Event"] = 132
	tFestivalSpring2015_DragonLight_Stc[2]["Type"] = 21

--stc(132,23)--（队长）记录符合条件人数
	tFestivalSpring2015_DragonLight_Stc[3] = {}
	tFestivalSpring2015_DragonLight_Stc[3]["Event"] = 132
	tFestivalSpring2015_DragonLight_Stc[3]["Type"] = 23

------------------------------------------------------------------------------------
--活动数据
local tFestivalSpring2015_DragonLight_Data = {}
	--活动时间
	tFestivalSpring2015_DragonLight_Data["Festival_BefTime"] = "2014-01-01 00:00 2015-02-28 23:59"
	tFestivalSpring2015_DragonLight_Data["Festival_NowTime"] = "2015-03-01 00:00 2015-03-05 23:59"
	
	--等级，转世设置
	tFestivalSpring2015_DragonLight_Data["LevTop"] = 140
	tFestivalSpring2015_DragonLight_Data["MinLevel"] = 80
	tFestivalSpring2015_DragonLight_Data["MinMeto"] = 0

	--背包空间
	tFestivalSpring2015_DragonLight_Data["ChkSpace"] = 1
	
	--舞龙队伍范围--3：所有地图
	tFestivalSpring2015_DragonLight_Data["Range"] = 3
	
	--延时时间
	tFestivalSpring2015_DragonLight_Data["DelayTime"] = 2
	
	--舞龙光效
	tFestivalSpring2015_DragonLight_Data["EffectObj"] = "self"
	tFestivalSpring2015_DragonLight_Data["Effect"] = "cyclonecyc"
	tFestivalSpring2015_DragonLight_Data["EffectTime"] = 5
	
	--通用礼包ID
	tFestivalSpring2015_DragonLight_Data["FestivalId"] = 3370
	tFestivalSpring2015_DragonLight_Data["LogId"] = 10002414
	
------------------------------------------------------------------------------------
--活动LOG数据
local tFestivalSpring2015_DragonLight_Log = {}
	--任务阶段
	tFestivalSpring2015_DragonLight_Log["Phase_1"] = "0,0,0,0,10002414,1[1],0,0"
	tFestivalSpring2015_DragonLight_Log["Phase_2"] = "0,0,0,0,10002414,1[2],0,0"
	
------------------------------------------------------------------------------------


------------------------------------------逻辑部分-------------------------------------------
--单用STC掩码判断
function FestivalSpring2015_DragonLight_ChkStc(nStcNum)
	local nEvent = tFestivalSpring2015_DragonLight_Stc[1]["Event"]
	local nType = tFestivalSpring2015_DragonLight_Stc[1]["Type"]
	
	--判断掩码是否为0
	if Task_ChkStcValue(nEvent,nType,"==",0) then
		return false
	end
	
	--判断是否隔天
	if Task_StcInterval(nEvent,nType,1,4) then
		Task_SetStatistic(nEvent,nType,0,1)
		Task_SetStcTimestamp(nEvent,nType,0)
		return false
	end
	
	--不等0，未隔天
	if Task_ChkStcValue(nEvent,nType,">=",nStcNum) then
		return true
	end
end

--- 多用STC掩码判断
function FestivalSpring2015_DragonLight_MultiStc(nStcNum,nPlaceNum)
	local nEvent = tFestivalSpring2015_DragonLight_Stc[nStcNum]["Event"]
	local nType = tFestivalSpring2015_DragonLight_Stc[nStcNum]["Type"]
	local nStcValue = Get_UserStatisticValue(nEvent,nType)
	local nMathValue = math.floor(nStcValue / tFestivalSpring2015_DragonLight_Stc[nStcNum]["Place"][nPlaceNum]) % 10
	
	--是否满足条件
	if nMathValue == 0 then
		return true
	else
		return false
	end
end



--队里是有人不满足条件--全队执行
function FestivalSpring2015_DragonLight_TeamFuncFail(nNpcId)
	LinkNpcGossipFunc_New(nNpcId,"2-4")
end



--队伍满足条件
function FestivalSpring2015_DragonLight_TeamFuncSuccess(nNpcId)
	local sEffectObj = tFestivalSpring2015_DragonLight_Data["EffectObj"]
	local sEffect = tFestivalSpring2015_DragonLight_Data["Effect"]
	
	--成功，置掩码，播放光效
	Task_SetStatistic(tFestivalSpring2015_DragonLight_Stc[1]["Event"],tFestivalSpring2015_DragonLight_Stc[1]["Type"],1,1)
	Task_SetStcTimestamp(tFestivalSpring2015_DragonLight_Stc[1]["Event"],tFestivalSpring2015_DragonLight_Stc[1]["Type"],0)
	Sys_MsgBox(tFestivalSpring2015_DragonLight_Text["Finish"])
	Sys_SaveActionFestivalLog(tFestivalSpring2015_DragonLight_Log["Phase_1"])
	User_EffectAdd(sEffectObj,sEffect)
	Sys_SetLuaTimer(tFestivalSpring2015_DragonLight_Data["EffectTime"],string.format("User_EffectDel</S>%s</S>%s",sEffectObj,sEffect))
end



--计算队伍是否满足条件
function FestivalSpring2015_DragonLight_ChkTeamFunc(nNpcId,nTeamNum)
	local nEvent = tFestivalSpring2015_DragonLight_Stc[3]["Event"]
	local nType = tFestivalSpring2015_DragonLight_Stc[3]["Type"]
	local nValue = Get_UserStatisticValue(nEvent,nType)
	
	--判断队伍是否满足条件
	if nTeamNum == nValue then
		User_TeamExeFuncByTeamer(tFestivalSpring2015_DragonLight_Data["Range"],string.format("FestivalSpring2015_DragonLight_TeamFuncSuccess</N>%d",nNpcId))
	else
		User_TeamExeFuncByTeamer(tFestivalSpring2015_DragonLight_Data["Range"],string.format("FestivalSpring2015_DragonLight_TeamFuncFail</N>%d",nNpcId))
	end
end



--第二次全队执行
function FestivalSpring2015_DragonLight_TeamFunc2(nNpcId,nTeamNum)

	--判断是否队长
	if User_IsTeamLeader() then
		Task_AddStatistic(tFestivalSpring2015_DragonLight_Stc[3]["Event"],tFestivalSpring2015_DragonLight_Stc[3]["Type"],1,0)
		
		--倒计时2秒后执行函数
		Sys_SetLuaTimer(tFestivalSpring2015_DragonLight_Data["DelayTime"],string.format("FestivalSpring2015_DragonLight_ChkTeamFunc</N>%d</N>%d",nNpcId,nTeamNum))
	end
end



--第一次全队执行
function FestivalSpring2015_DragonLight_TeamFunc1(nNpcId)

	--判断队里是否有人等级不足
	if not User_JudgeLevelAndMetempsychosis(tFestivalSpring2015_DragonLight_Data["MinLevel"],tFestivalSpring2015_DragonLight_Data["MinMeto"]) then
		return
	end

	--判断是否有人已完成任务
	if FestivalSpring2015_DragonLight_ChkStc(1) then
		return
	end
	
	--取队伍人数
	local nTeamNum = Get_UserTeamNumbers()
	
	--判断玩家是否队长
	if User_IsTeamLeader() then
		--清掩码
		Task_SetStatistic(tFestivalSpring2015_DragonLight_Stc[2]["Event"],tFestivalSpring2015_DragonLight_Stc[2]["Type"],0,1)
		Task_SetStatistic(tFestivalSpring2015_DragonLight_Stc[3]["Event"],tFestivalSpring2015_DragonLight_Stc[3]["Type"],0,1)
		
		--记录队伍人数
		Task_SetStatistic(tFestivalSpring2015_DragonLight_Stc[2]["Event"],tFestivalSpring2015_DragonLight_Stc[2]["Type"],nTeamNum,1)
		Task_SetStcTimestamp(tFestivalSpring2015_DragonLight_Stc[2]["Event"],tFestivalSpring2015_DragonLight_Stc[2]["Type"],0)
		Task_SetStcTimestamp(tFestivalSpring2015_DragonLight_Stc[3]["Event"],tFestivalSpring2015_DragonLight_Stc[3]["Type"],0)
	end
	
	--满足条件执行
	User_TeamExeFuncByTeamer(tFestivalSpring2015_DragonLight_Data["Range"],string.format("FestivalSpring2015_DragonLight_TeamFunc2</N>%d</N>%d",nNpcId,nTeamNum))
end


--参加舞龙灯逻辑
function FestivalSpring2015_DragonLight_Join(nNpcId)
	--活动时间判断
	if not Sys_ChkFullTime(tFestivalSpring2015_DragonLight_Data["Festival_NowTime"]) then
		LinkNpcGossipFunc_New(nNpcId,"1-2")
		return
	end
	
	--判断是否等级不足
	if not User_JudgeLevelAndMetempsychosis(tFestivalSpring2015_DragonLight_Data["MinLevel"],tFestivalSpring2015_DragonLight_Data["MinMeto"]) then
		LinkNpcGossipFunc_New(nNpcId,"2-5")
		return
	end
	
	--判断玩家是否已完成任务
	if FestivalSpring2015_DragonLight_ChkStc(1) then
		User_TeamExeFuncByTeamer(tFestivalSpring2015_DragonLight_Data["Range"],string.format("FestivalSpring2015_DragonLight_TeamFuncDone</N>%d",nNpcId))
		return
	end
	
	local nTeamNum = Get_UserTeamNumbers()
	--判断玩家是否组队
	if nTeamNum == 0 then
		LinkNpcGossipFunc_New(nNpcId,"2-1")
		return
	end
	
	--判断玩家组队却只有1个人
	if nTeamNum == 1 then
		LinkNpcGossipFunc_New(nNpcId,"2-2")
		return
	end
	
	--判断玩家是否队长
	if not User_IsTeamLeader() then
		LinkNpcGossipFunc_New(nNpcId,"2-3")
		return
	end
	
	--全队执行
	User_TeamExeFuncByTeamer(tFestivalSpring2015_DragonLight_Data["Range"],string.format("FestivalSpring2015_DragonLight_TeamFunc1</N>%d",nNpcId))
end



--领取奖赏
function FestivalSpring2015_DragonLight_Reward(nNpcId)

	--活动时间判断
	if not Sys_ChkFullTime(tFestivalSpring2015_DragonLight_Data["Festival_NowTime"]) then
		LinkNpcGossipFunc_New(nNpcId,"1-2")
		return
	end

	local nEvent = tFestivalSpring2015_DragonLight_Stc[1]["Event"]
	local nType = tFestivalSpring2015_DragonLight_Stc[1]["Type"]

	--判断是否完成任务
	if not FestivalSpring2015_DragonLight_ChkStc(1) then 
		LinkNpcGossipFunc_New(nNpcId,"3-1")
		return
	end

	--判断是否已领取奖励
	if FestivalSpring2015_DragonLight_ChkStc(2) then 
		LinkNpcGossipFunc_New(nNpcId,"3-2")
		return
	end
	
	--判断背包空间
	if not User_CheckLeftSpace(tFestivalSpring2015_DragonLight_Data["ChkSpace"]) then
		LinkNpcGossipFunc_New(nNpcId,"3-3")
		return
	end
	
	--获得节日礼包
	Task_SetStatistic(tFestivalSpring2015_DragonLight_Stc[1]["Event"],tFestivalSpring2015_DragonLight_Stc[1]["Type"],2,1)
	Task_SetStcTimestamp(tFestivalSpring2015_DragonLight_Stc[1]["Event"],tFestivalSpring2015_DragonLight_Stc[1]["Type"],0)
	FestivalGeneralPackage_GetGift(tFestivalSpring2015_DragonLight_Data["FestivalId"],tFestivalSpring2015_DragonLight_Data["LogId"])
	Sys_SaveActionFestivalLog(tFestivalSpring2015_DragonLight_Log["Phase_2"])
	LinkNpcGossipFunc_New(nNpcId,"3-4")
end

--愿闻其详
function FestivalSpring2015_DragonLight_Introduction(nNpcId)
	--活动时间判断
	if not Sys_ChkFullTime(tFestivalSpring2015_DragonLight_Data["Festival_NowTime"]) then
		LinkNpcGossipFunc_New(nNpcId,"1-3")
		return
	end
	
	--活动时间内出对白
	LinkNpcGossipFunc_New(nNpcId,"4-1")
end

------------------------------------------NPC头像-------------------------------------------
tNpcFace[3432] = 156
------------------------------------------NPC对话-------------------------------------------

-- //舞者小丸子
tNpcGossip[17436] = tNpcGossip[17436] or DefaultNpc:new{}
tNpcGossip[17436]["OptionHidden"] = 1

-- 【起始对白】
tNpcGossip[17436]["Text1-1"] = {111,112} 		-- 活动时间前
tNpcGossip[17436]["Text1-2"] = {121} 			-- 活动时间后
tNpcGossip[17436]["Text1-3"] = {131,132,133} 		-- 活动时间后
-- 活动前
tNpcGossip[17436]["Text111"] = tFestivalSpring2015_DragonLight_Text[17436]["Text111"]
tNpcGossip[17436]["Text112"] = tFestivalSpring2015_DragonLight_Text[17436]["Text112"]
tNpcGossip[17436]["ChkFunc1-1"] = function ()
	return Sys_ChkFullTime(tFestivalSpring2015_DragonLight_Data["Festival_BefTime"])
end
-- 活动后
tNpcGossip[17436]["Text121"] = tFestivalSpring2015_DragonLight_Text[17436]["Text121"]
tNpcGossip[17436]["ChkFunc1-2"] = function ()
	return not Sys_ChkFullTime(tFestivalSpring2015_DragonLight_Data["Festival_NowTime"])
end
-- 活动中
tNpcGossip[17436]["Text131"] = tFestivalSpring2015_DragonLight_Text[17436]["Text131"]
tNpcGossip[17436]["Text132"] = tFestivalSpring2015_DragonLight_Text[17436]["Text132"]
tNpcGossip[17436]["Text133"] = tFestivalSpring2015_DragonLight_Text[17436]["Text133"]
--选项
tNpcGossip[17436]["tOption1-1"] = {11}				-- 活动时间前
tNpcGossip[17436]["tOption1-2"] = {12}				-- 活动时间后
tNpcGossip[17436]["tOption1-3"] = {13,14,15,16}		-- 活动时间中
tNpcGossip[17436]["Option11"] = tFestivalSpring2015_DragonLight_Text[17436]["Option11"]
tNpcGossip[17436]["Option12"] = tFestivalSpring2015_DragonLight_Text[17436]["Option12"]
tNpcGossip[17436]["Option13"] = tFestivalSpring2015_DragonLight_Text[17436]["Option13"]
tNpcGossip[17436]["OptionChkFunc13"] = function ()
	return not FestivalSpring2015_DragonLight_ChkStc(1)
end
tNpcGossip[17436]["OptionFunc13"] = "FestivalSpring2015_DragonLight_Join</N>17436"
tNpcGossip[17436]["Option14"] = tFestivalSpring2015_DragonLight_Text[17436]["Option14"]
tNpcGossip[17436]["OptionFunc14"] = "FestivalSpring2015_DragonLight_Reward</N>17436"
tNpcGossip[17436]["Option15"] = tFestivalSpring2015_DragonLight_Text[17436]["Option15"]
tNpcGossip[17436]["OptionFunc15"] = "FestivalSpring2015_DragonLight_Introduction</N>17436"
tNpcGossip[17436]["Option16"] = tFestivalSpring2015_DragonLight_Text[17436]["Option16"]


-- 【弟兄们来舞龙喽！】
tNpcGossip[17436]["Text2-1"] = {211,212} --未组队
tNpcGossip[17436]["Text2-2"] = {221,222} --组队却只有1个人
tNpcGossip[17436]["Text2-3"] = {231,232} --不是队长
tNpcGossip[17436]["Text2-4"] = {241,242,243} --队伍里有人等级不足
tNpcGossip[17436]["Text2-5"] = {251} --等级不足提示
tNpcGossip[17436]["Text211"] = tFestivalSpring2015_DragonLight_Text[17436]["Text211"]
tNpcGossip[17436]["Text212"] = tFestivalSpring2015_DragonLight_Text[17436]["Text212"]
tNpcGossip[17436]["Text221"] = tFestivalSpring2015_DragonLight_Text[17436]["Text221"]
tNpcGossip[17436]["Text222"] = tFestivalSpring2015_DragonLight_Text[17436]["Text222"]
tNpcGossip[17436]["Text231"] = tFestivalSpring2015_DragonLight_Text[17436]["Text231"]
tNpcGossip[17436]["Text232"] = tFestivalSpring2015_DragonLight_Text[17436]["Text232"]
tNpcGossip[17436]["Text241"] = tFestivalSpring2015_DragonLight_Text[17436]["Text241"]
tNpcGossip[17436]["Text242"] = tFestivalSpring2015_DragonLight_Text[17436]["Text242"]
tNpcGossip[17436]["Text243"] = tFestivalSpring2015_DragonLight_Text[17436]["Text243"]
tNpcGossip[17436]["Text251"] = tFestivalSpring2015_DragonLight_Text[17436]["Text251"]
tNpcGossip[17436]["tOption2-1"] = {21}
tNpcGossip[17436]["tOption2-2"] = {22}
tNpcGossip[17436]["tOption2-3"] = {23}
tNpcGossip[17436]["tOption2-4"] = {24}
tNpcGossip[17436]["tOption2-5"] = {25}
tNpcGossip[17436]["Option21"] = tFestivalSpring2015_DragonLight_Text[17436]["Option21"]
tNpcGossip[17436]["Option22"] = tFestivalSpring2015_DragonLight_Text[17436]["Option22"]
tNpcGossip[17436]["Option23"] = tFestivalSpring2015_DragonLight_Text[17436]["Option23"]
tNpcGossip[17436]["Option24"] = tFestivalSpring2015_DragonLight_Text[17436]["Option24"]
tNpcGossip[17436]["Option25"] = tFestivalSpring2015_DragonLight_Text[17436]["Option25"]


-- 【领取奖赏。】
tNpcGossip[17436]["Text3-1"] = {311} 		--未完成任务
tNpcGossip[17436]["Text3-2"] = {321} 		--已领取奖励
tNpcGossip[17436]["Text3-3"] = {331} 		--背包空间不足
tNpcGossip[17436]["Text3-4"] = {341,342} 	--领取成功
tNpcGossip[17436]["Text311"] = tFestivalSpring2015_DragonLight_Text[17436]["Text311"]
tNpcGossip[17436]["Text321"] = tFestivalSpring2015_DragonLight_Text[17436]["Text321"]
tNpcGossip[17436]["Text331"] = tFestivalSpring2015_DragonLight_Text[17436]["Text331"]
tNpcGossip[17436]["Text341"] = tFestivalSpring2015_DragonLight_Text[17436]["Text341"]
tNpcGossip[17436]["Text342"] = tFestivalSpring2015_DragonLight_Text[17436]["Text342"]
tNpcGossip[17436]["tOption3-1"] = {31}
tNpcGossip[17436]["tOption3-2"] = {32}
tNpcGossip[17436]["tOption3-3"] = {33}
tNpcGossip[17436]["tOption3-4"] = {34}
tNpcGossip[17436]["Option31"] = tFestivalSpring2015_DragonLight_Text[17436]["Option31"]
tNpcGossip[17436]["Option32"] = tFestivalSpring2015_DragonLight_Text[17436]["Option32"]
tNpcGossip[17436]["Option33"] = tFestivalSpring2015_DragonLight_Text[17436]["Option33"]
tNpcGossip[17436]["Option34"] = tFestivalSpring2015_DragonLight_Text[17436]["Option34"]


-- 【我该怎么舞龙？】
tNpcGossip[17436]["Text4-1"] = {411,412} 	--内容
tNpcGossip[17436]["Text411"] = tFestivalSpring2015_DragonLight_Text[17436]["Text411"]
tNpcGossip[17436]["Text412"] = tFestivalSpring2015_DragonLight_Text[17436]["Text412"]
tNpcGossip[17436]["tOption4-1"] = {41}
tNpcGossip[17436]["Option41"] = tFestivalSpring2015_DragonLight_Text[17436]["Option41"]







