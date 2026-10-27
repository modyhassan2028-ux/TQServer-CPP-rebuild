--Name:			[征服][活动脚本]2015年暑期活动无畏勇者
--Creator: 		魏贻逵
--Created:		2015/04/21
------------------------------------------------------------------------------------
--掩码说明：
--115,09
--每隔3分钟领取兑奖令牌 
--1代表 18:00-18:02领取 
--2代表 18:03-18:05领取
--3代表 18:06-18:08领取
--4代表 18:09-18:11领取
--5代表 18:12-18:14领取

--115,10
--当天领取牌子的数量
--2000 代表领取礼包

--动态存储表说明：
--50262 全服领取牌子数量

-- 活动时间
local tSummeractivities_brave_Cont = {}
tSummeractivities_brave_Cont["Beftime"] = "2015-01-01 00:00 2015-07-08 23:59"
tSummeractivities_brave_Cont["Nowtime"] = "2015-07-09 00:00 2015-07-22 23:59"
tSummeractivities_brave_Cont["Aftime"]  = "2015-07-23 00:00 2020-01-01 23:59"
tSummeractivities_brave_Cont["Nowdaytime"] = "18:00 18:14"


-- 玩家等级要求
tSummeractivities_brave_Cont["Metempsychosis"] = 1
tSummeractivities_brave_Cont["Level"] = 80

--传送地点
tSummeractivities_brave_Cont["MapId"] = 9966
tSummeractivities_brave_Cont["BoundCX"] = 5
tSummeractivities_brave_Cont["BoundCY"] = 5

tSummeractivities_brave_Cont["CellX1"] = 76
tSummeractivities_brave_Cont["CellY1"] = 56

tSummeractivities_brave_Cont["CellX2"] = 65
tSummeractivities_brave_Cont["CellY2"] = 71

tSummeractivities_brave_Cont["CellX3"] = 23
tSummeractivities_brave_Cont["CellY3"] = 39

tSummeractivities_brave_Cont["CellX4"] = 38
tSummeractivities_brave_Cont["CellY4"] = 23

--返回地点
tSummeractivities_brave_Cont["MapId1"] = 1002
tSummeractivities_brave_Cont["CellX5"] = 280
tSummeractivities_brave_Cont["CellY5"] = 370

--相关物品
tSummeractivities_brave_Cont["Item"] = 3001502

--领取牌子数量
tSummeractivities_brave_Cont["Addamount"] = 30

--背包空间
tSummeractivities_brave_Cont["Space"] = 2

--相关NPC
tSummeractivities_brave_Cont["Npc"] = 10297

--间隔距离
tSummeractivities_brave_Cont["CXInterval"] = 15
tSummeractivities_brave_Cont["CYInterval"] = 15

--存活人数
tSummeractivities_brave_Cont["UserNum"] = 1

--活动掩码
--每隔3分钟领取兑奖令牌 
local tSummeractivities_brave_stc = {}
tSummeractivities_brave_stc[1] = {}
tSummeractivities_brave_stc[1]["EventType"] = 115
tSummeractivities_brave_stc[1]["DataType"] = 09

--当天领取牌子的数量
tSummeractivities_brave_stc[2] = {}
tSummeractivities_brave_stc[2]["EventType"] = 115
tSummeractivities_brave_stc[2]["DataType"] = 10
tSummeractivities_brave_stc[2]["Add"] = 1
tSummeractivities_brave_stc[2]["Complete"] = 5
tSummeractivities_brave_stc[2]["Complete1"] = 2000 --领取礼包奖励

--动态存储表-记录牌子领取情况
local tSummeractivities_brave_dyna = {}
tSummeractivities_brave_dyna["Id"] = 50262
tSummeractivities_brave_dyna["Add"] = 1
tSummeractivities_brave_dyna["Limit"] = 1000
tSummeractivities_brave_dyna["Limit1"] = 1030

--活动阶段时间-每阶段可领1个牌子
local tSummeractivities_brave_time = {}
tSummeractivities_brave_time[1] = "18:00 18:02"
tSummeractivities_brave_time[2] = "18:03 18:05"
tSummeractivities_brave_time[3] = "18:06 18:08"
tSummeractivities_brave_time[4] = "18:09 18:11"
tSummeractivities_brave_time[5] = "18:12 18:14"

--奖励配置-3个炉子经验，修行值和气力值
local tSummeractivities_brave_Reward = {}
tSummeractivities_brave_Reward[10297] = {}
tSummeractivities_brave_Reward[10297]["Limitlevel"] = 140 
tSummeractivities_brave_Reward[10297]["AddExpTime"] = 12 

tSummeractivities_brave_Reward[10298] = {}
tSummeractivities_brave_Reward[10298]["AddCultivation"] = 10 

tSummeractivities_brave_Reward[10299] = {}
tSummeractivities_brave_Reward[10299]["Addstrengthvalue"] = 5 

--相关log
local tSummeractivities_brave_log = {}
tSummeractivities_brave_log["AddExpTime"] = "0,0,3001502,1,10001941,2,4,12" --获得经验
tSummeractivities_brave_log["AddCultivation"] = "0,0,3001502,1,10001941,2,6,10" --获得修行值
tSummeractivities_brave_log["Addstrengthvalue"] = "0,0,3001502,1,10001941,2,12,5" --获得气力值
tSummeractivities_brave_log["Reward"] = "0,0,0,0,10001941,2,3001502,1" --获得牌子
tSummeractivities_brave_log["Reward1"] = "0,0,0,0,10001941,2,3001502,30" --获得牌子
--tSummeractivities_brave_log["RewardLog"] = "0,0,0,0,10001941,2,3001526,1" --获得礼包奖励
tSummeractivities_brave_log["LogId"] = 10001941
tSummeractivities_brave_log["FestivalId"] = 3432


--[[
--相关提示
local tSummeractivities_brave_Text = {}
tSummeractivities_brave_Text["NoItem"] = "你身上并没有携带无畏令牌，不能获得奖励！"
tSummeractivities_brave_Text["Limitlevel"] = "你的等级已达到上限，无法获得经验。"
tSummeractivities_brave_Text["AddExpTime"] = "你投入了1个无畏令牌，获得了12分钟经验！"
tSummeractivities_brave_Text["AddCultivation"] = "你投入了1个无畏令牌，获得了10点修行值！"
tSummeractivities_brave_Text["Addstrengthvalue"] = "你投入了1个无畏令牌，获得了5点气力值！"
tSummeractivities_brave_Text["Far"] = "你距离我那么远，我是无法发给你令牌的，请靠近一些吧。"
tSummeractivities_brave_Text["Complete"] = "还未到领取无畏令牌的时候，每隔3分钟才能领取1次，还请稍候再来吧。"
tSummeractivities_brave_Text["Space"] = "阁下的背包空间不足，请先整理一下背包吧。"
tSummeractivities_brave_Text["Reward"] = "恭喜你成功领取了1枚无畏令牌！"
tSummeractivities_brave_Text["Lead"] = "牌子已经都被领取完了。"
tSummeractivities_brave_Text["Lastpoint"] = "尽情杀戮吧！剩余的令牌只有场中唯一的存活者才能领取。"
tSummeractivities_brave_Text["Reward1"] = "恭喜你获得了节日欢庆礼包！"
tSummeractivities_brave_Text["Win"] = "你是最后留在场地上的勇者，恭喜你获得了剩下的全部无畏令牌。"
tSummeractivities_brave_Text["Broadcast"] = "热血竞技场已经开放！快找竞技冠军凌云入场吧！"

tSummeractivities_brave_Text["Text1"] = "热血竞技场已经开放！快找竞技冠军凌云入场吧！"
tSummeractivities_brave_Text["Option1"] = "确定"
tSummeractivities_brave_Text["Option2"] = "取消"

tSummeractivities_brave_Text[10296] = {}
tSummeractivities_brave_Text[10296]["Text111"] ="    真正的勇者，需要有着坚忍不拔的毅力，勇往直前的气魄和战胜一切阻碍的信念。你到底是不是一名真正的勇士呢？7月9日至7月22日，我会给你一个证明自己的机会！"
tSummeractivities_brave_Text[10296]["Text112"] = "来吧，来到我们的热血竞技场，让大家都为你的实力惊叹吧！"
tSummeractivities_brave_Text[10296]["Option1"] = "我一定参加！"

tSummeractivities_brave_Text[10296]["Text121"] ="    诸位侠士勇往直前的精神真是让在下敬佩不已。"
tSummeractivities_brave_Text[10296]["Option2"] = "过奖了。"

tSummeractivities_brave_Text[10296]["Text131"] ="     7月9日到7月22日，每天的18:00-18:15，只要你的等级达到80级，就可以参与到我们热火朝天的热血竞技场活动中了。进入竞技场后，侠士们就开始不受限制的比武。怎"
tSummeractivities_brave_Text[10296]["Text132"] ="么尽可能地坚持到最后，就要看你的本事了！每隔3分钟可以找我弟弟凌霄领取1个无畏令牌。如果你能成为最后留在场地的勇者，还有特别的惊喜等着你！"
tSummeractivities_brave_Text[10296]["Option3"] = "我要参加！"
tSummeractivities_brave_Text[10296]["Option4"] = "我还要了解更多。"
tSummeractivities_brave_Text[10296]["Option5"] = "我就是路过看看。"

tSummeractivities_brave_Text[10296]["Text411"] = "    这无畏令牌可是个好东西，把它投入我身后的香炉，就可以获得奖励了。阁下可以在12分钟经验、10点修行值和5点气力值中任意选择一种。另外，如果阁下实力非凡，拿到"
tSummeractivities_brave_Text[10296]["Text412"] = "5个以上的令牌，我将额外赠送给阁下1个暑假欢笑大礼包，不过这个礼包1天只能领取1次哦。"
tSummeractivities_brave_Text[10296]["Option6"] = "还有呢？"
tSummeractivities_brave_Text[10296]["Option7"] = "我要参加！"
tSummeractivities_brave_Text[10296]["Option8"] = "我就路过看看。"

tSummeractivities_brave_Text[10296]["Text611"] = "    热血竞技场每天18:00到18:15入场，期间侠士们可以任意进出。19:00时，所有还在竞技场内的侠士都将被送回双龙城。另外，我弟弟凌霄总共携带了1000个无畏令牌，如果"
tSummeractivities_brave_Text[10296]["Text612"] = "你能够成为最后留在场上的侠士， 就可以获得30枚令牌作为奖励了！这可需要你有着超乎常人的勇气和绝佳的武艺哦！"
tSummeractivities_brave_Text[10296]["Option9"] = "太诱人了，我要参加！"
tSummeractivities_brave_Text[10296]["Option10"] = "我还有别的事情要忙。"

tSummeractivities_brave_Text[10296]["Text211"] = "    很抱歉，今天的竞技场还没有开放，请在18:00以后再来吧。"
tSummeractivities_brave_Text[10296]["Option11"] = "离开。"

tSummeractivities_brave_Text[10296]["Text221"] = "    你的等级不到80级，这种挑战对你来说太危险了，请升级到80级以后再来吧。"
tSummeractivities_brave_Text[10296]["Option12"] = "离开。"

--]]

-------------------------------------------------------------------逻辑部分------------------------------------------------------------
--常用逻辑
--等级判断
function Summeractivities_brave_level()
	local nMetempsychosis = Get_UserMetempsychosis()
	local nUserLev = Get_UserLevel()
	local bPlayerLev = false
	if nMetempsychosis < tSummeractivities_brave_Cont["Metempsychosis"] then
		if nUserLev < tSummeractivities_brave_Cont["Level"] then
			bPlayerLev = true
		else
			bPlayerLev = false
		end 
	end
	return bPlayerLev
end

--隔天清0
function Summeractivities_brave_nextday()
	if Task_StcInterval(tSummeractivities_brave_stc[1]["EventType"],tSummeractivities_brave_stc[1]["DataType"],1,4) then
		Task_SetStatistic(tSummeractivities_brave_stc[1]["EventType"], tSummeractivities_brave_stc[1]["DataType"],0,1,0)
		Task_SetStcTimestamp(tSummeractivities_brave_stc[1]["EventType"],tSummeractivities_brave_stc[1]["DataType"],0,0)
	end
	
	if Task_StcInterval(tSummeractivities_brave_stc[2]["EventType"],tSummeractivities_brave_stc[2]["DataType"],1,4) then
		Task_SetStatistic(tSummeractivities_brave_stc[2]["EventType"], tSummeractivities_brave_stc[2]["DataType"],0,1,0)
		Task_SetStcTimestamp(tSummeractivities_brave_stc[2]["EventType"],tSummeractivities_brave_stc[2]["DataType"],0,0)
	end
		
end

--活动礼包奖励
function Summeractivities_brave_prize()
	local nMetempsychosis = Get_UserMetempsychosis()
	Task_SetStatistic(tSummeractivities_brave_stc[2]["EventType"], tSummeractivities_brave_stc[2]["DataType"],tSummeractivities_brave_stc[2]["Complete1"],1,0)						
	Task_SetStcTimestamp(tSummeractivities_brave_stc[2]["EventType"],tSummeractivities_brave_stc[2]["DataType"],0,0)	
	FestivalGeneralPackage_GetGift(tSummeractivities_brave_log["FestivalId"],tSummeractivities_brave_log["LogId"])
--	Sys_SaveActionFestivalLog(tSummeractivities_brave_log["RewardLog"])
	
end


--传送到双龙城
function Summeractivities_brave_chgmap()

User_UserRandBoundTrans(tSummeractivities_brave_Cont["MapId1"],tSummeractivities_brave_Cont["CellX5"],tSummeractivities_brave_Cont["CellY5"],tSummeractivities_brave_Cont["BoundCX"],tSummeractivities_brave_Cont["BoundCY"],0,0)

end

--清动态存储表
function Summeractivities_brave_clearsysdyna()
	if	Sys_ChkFullTime(tSummeractivities_brave_Cont["Nowtime"]) then
		Sys_ResetAllSynaGlobalData(tSummeractivities_brave_dyna["Id"])				
		
	end	
end

--全服公告
function Summeractivities_brave_broadcast()
	if	Sys_ChkFullTime(tSummeractivities_brave_Cont["Nowtime"]) then
		Sys_TalkBroadcast(tSummeractivities_brave_Text["Broadcast"])		
		
	end	
end

--清场
function Summeractivities_brave_clearuser()
	if Sys_ChkFullTime(tSummeractivities_brave_Cont["Nowtime"]) then	
		if Map_GetUserNum(tSummeractivities_brave_Cont["MapId"],1) >= tSummeractivities_brave_Cont["UserNum"] then	
           Map_UserExeFunc(tSummeractivities_brave_Cont["MapId"],-1,"Summeractivities_brave_chgmap")
		   
		end		
	end	
	
end


--竞技冠军凌云
--我要参加！
function Summeractivities_brave_Option3_10296(nNpcId)
--判断活动时间
	if not Sys_ChkFullTime(tSummeractivities_brave_Cont["Nowtime"]) then
		LinkNpcGossipFunc_New(nNpcId,"1-2")
		return
	end
	
--判断具体活动时间
	if not Sys_ChkDayTime(tSummeractivities_brave_Cont["Nowdaytime"]) then
		LinkNpcGossipFunc_New(nNpcId,"2-1")
		return
	end	

--判断玩家等级
	if Summeractivities_brave_level() then
		LinkNpcGossipFunc_New(nNpcId,"2-2")
		return
	end

--随机传送	
	if Sys_Random(1,4) then
		User_UserRandBoundTrans(tSummeractivities_brave_Cont["MapId"],tSummeractivities_brave_Cont["CellX1"],tSummeractivities_brave_Cont["CellY1"],tSummeractivities_brave_Cont["BoundCX"],tSummeractivities_brave_Cont["BoundCY"],1,0)	
		return
	end
		
	if Sys_Random(1,3) then
		User_UserRandBoundTrans(tSummeractivities_brave_Cont["MapId"],tSummeractivities_brave_Cont["CellX2"],tSummeractivities_brave_Cont["CellY2"],tSummeractivities_brave_Cont["BoundCX"],tSummeractivities_brave_Cont["BoundCY"],1,0)	
		return
	end
		
	if Sys_Random(1,2) then
		User_UserRandBoundTrans(tSummeractivities_brave_Cont["MapId"],tSummeractivities_brave_Cont["CellX3"],tSummeractivities_brave_Cont["CellY3"],tSummeractivities_brave_Cont["BoundCX"],tSummeractivities_brave_Cont["BoundCY"],1,0)	
		
	else	
		User_UserRandBoundTrans(tSummeractivities_brave_Cont["MapId"],tSummeractivities_brave_Cont["CellX4"],tSummeractivities_brave_Cont["CellY4"],tSummeractivities_brave_Cont["BoundCX"],tSummeractivities_brave_Cont["BoundCY"],1,0)	
				
	end
		
end

--香炉
function Summeractivities_brave_censer(nNpcid)
	local nNpcid = Get_NpcId()
	Sys_DialogText(tSummeractivities_brave_Text[nNpcid]["Text111"])
	Sys_DialogOption(tSummeractivities_brave_Text["Option1"],"</F>Summeractivities_brave_censer1</N>"..nNpcid)
	Sys_DialogOption(tSummeractivities_brave_Text["Option2"],"</F>NULL")
	Sys_DialogEnd()

end

function Summeractivities_brave_censer1(nNpcid)
	local nUserLev = Get_UserLevel()
	if not Item_ChkItem(tSummeractivities_brave_Cont["Item"]) then
		User_TalkChannel2005(tSummeractivities_brave_Text["NoItem"])
		return
	end 

	if nNpcid == tSummeractivities_brave_Cont["Npc"] then
		if nUserLev >= tSummeractivities_brave_Reward[10297]["Limitlevel"] then
			User_TalkChannel2005(tSummeractivities_brave_Text["Limitlevel"])
			return
		end	
	end 	
	
	if Item_DelItem(tSummeractivities_brave_Cont["Item"]) then
		if tSummeractivities_brave_Reward[nNpcid]["AddExpTime"] ~= nil then
			User_AddExpTime(tSummeractivities_brave_Reward[nNpcid]["AddExpTime"])
			User_TalkChannel2005(tSummeractivities_brave_Text["AddExpTime"])
			Sys_SaveActionFestivalLog(tSummeractivities_brave_log["AddExpTime"])
		end
		
		if tSummeractivities_brave_Reward[nNpcid]["AddCultivation"] ~= nil then
			User_AddCultivation(tSummeractivities_brave_Reward[nNpcid]["AddCultivation"])
			User_TalkChannel2005(tSummeractivities_brave_Text["AddCultivation"])
			Sys_SaveActionFestivalLog(tSummeractivities_brave_log["AddCultivation"])
		end
		
		if tSummeractivities_brave_Reward[nNpcid]["Addstrengthvalue"] ~= nil then
			User_AddStrengthValue(tSummeractivities_brave_Reward[nNpcid]["Addstrengthvalue"])
			User_TalkChannel2005(tSummeractivities_brave_Text["Addstrengthvalue"])
			Sys_SaveActionFestivalLog(tSummeractivities_brave_log["Addstrengthvalue"])		
			
		end
	end
	return	Summeractivities_brave_censer(nNpcid)
end	

--凌霄
function Summeractivities_brave_linxiao()
	--判断距离	
	local nUser_x = Get_UserPositionX()
	local nUser_y = Get_UserPositionY()
	local nNpc_x = Get_NpcPositionX()
	local nNpc_y = Get_NpcPositionY()
	if (nUser_x + tSummeractivities_brave_Cont["CXInterval"] <= nNpc_x) or (nUser_x - tSummeractivities_brave_Cont["CXInterval"] >= nNpc_x) or (nUser_y + tSummeractivities_brave_Cont["CYInterval"] <= nNpc_y) or (nUser_y - tSummeractivities_brave_Cont["CYInterval"] >= nNpc_y) then
		User_TalkChannel2005(tSummeractivities_brave_Text["Far"])	
		return
	end	
	--隔天清0
	Summeractivities_brave_nextday() 	
	local SysDynaGlobalData1 = Get_SysDynaGlobalData1(tSummeractivities_brave_dyna["Id"])		
	
	--18:00-18:14
	if Sys_ChkDayTime(tSummeractivities_brave_Cont["Nowdaytime"]) then	
		for i = 1,5 do
			if Sys_ChkDayTime(tSummeractivities_brave_time[i]) then	
				if SysDynaGlobalData1 < tSummeractivities_brave_dyna["Limit"] then				
					if Task_ChkStcValue(tSummeractivities_brave_stc[2]["EventType"],tSummeractivities_brave_stc[2]["DataType"],">=",tSummeractivities_brave_stc[2]["Complete1"]) then
						User_TalkChannel2005(tSummeractivities_brave_Text["Lastpoint"])	
						return
					end					
								
					if Task_ChkStcValue(tSummeractivities_brave_stc[1]["EventType"], tSummeractivities_brave_stc[1]["DataType"],"==",i) then			
						User_TalkChannel2005(tSummeractivities_brave_Text["Complete"])	
						return
					end	
																						
					if not User_CheckLeftSpace(tSummeractivities_brave_Cont["Space"]) then
						User_TalkChannel2005(tSummeractivities_brave_Text["Space"])
						return
					end
						SysDynaGlobalData1 = SysDynaGlobalData1 +1
						Task_SetStatistic(tSummeractivities_brave_stc[1]["EventType"], tSummeractivities_brave_stc[1]["DataType"],i,1,0)
						Task_SetStcTimestamp(tSummeractivities_brave_stc[1]["EventType"],tSummeractivities_brave_stc[1]["DataType"],0,0)
						Task_AddStatistic(tSummeractivities_brave_stc[2]["EventType"],tSummeractivities_brave_stc[2]["DataType"],tSummeractivities_brave_stc[2]["Add"],1,0)
						Task_SetStcTimestamp(tSummeractivities_brave_stc[2]["EventType"],tSummeractivities_brave_stc[2]["DataType"],0,0)						
						Sys_SetSynaGlobalData1(tSummeractivities_brave_dyna["Id"],SysDynaGlobalData1)
						Item_AddItem(tSummeractivities_brave_Cont["Item"])						
						User_TalkChannel2005(tSummeractivities_brave_Text["Reward"])
						Sys_SaveActionFestivalLog(tSummeractivities_brave_log["Reward"])						
						
					if  Task_ChkStcValue(tSummeractivities_brave_stc[2]["EventType"], tSummeractivities_brave_stc[2]["DataType"],">=",tSummeractivities_brave_stc[2]["Complete"]) then	
						Summeractivities_brave_prize()		
						return
					end	
										
				else
					User_TalkChannel2005(tSummeractivities_brave_Text["Lead"])							
				end	
			end			
		end	
		
	--18:15之后
	else 
		if SysDynaGlobalData1 < tSummeractivities_brave_dyna["Limit1"] then
			if Map_GetUserNum(tSummeractivities_brave_Cont["MapId"],1) > tSummeractivities_brave_Cont["UserNum"] then
				User_TalkChannel2005(tSummeractivities_brave_Text["Lastpoint"])	
				return
			end
			
			if not User_CheckLeftSpace(tSummeractivities_brave_Cont["Space"]) then
				User_TalkChannel2005(tSummeractivities_brave_Text["Space"])
				return
			end				
			
			Sys_SetSynaGlobalData1(tSummeractivities_brave_dyna["Id"],tSummeractivities_brave_dyna["Limit1"])
			Item_AddItem(tSummeractivities_brave_Cont["Item"],0,tSummeractivities_brave_Cont["Addamount"])
			Sys_SaveActionFestivalLog(tSummeractivities_brave_log["Reward1"])
						
			if Task_ChkStcValue(tSummeractivities_brave_stc[2]["EventType"],tSummeractivities_brave_stc[2]["DataType"],"<",tSummeractivities_brave_stc[2]["Complete1"]) then
				Summeractivities_brave_prize()																
			end				
				
			Summeractivities_brave_chgmap()
			User_TalkChannel2005(tSummeractivities_brave_Text["Win"])		
			
		else
			User_TalkChannel2005(tSummeractivities_brave_Text["Lead"])	
		end	
		
	end
end

--双龙城传送石
function Summeractivities_brave_stone()
	if Sys_ChkDayTime(tSummeractivities_brave_Cont["Nowdaytime"]) then	
		Summeractivities_brave_chgmap()
				
	else
		Sys_DialogText(tSummeractivities_brave_Text["Text1"])
		Sys_DialogOption(tSummeractivities_brave_Text["Option1"],"</F>Summeractivities_brave_chgmap")
		Sys_DialogOption(tSummeractivities_brave_Text["Option2"],"</F>NULL")
		Sys_DialogEnd()
	end	
		
end


--200W
--清动态存储表
-- tOntimerMin_HM[1755] = tOntimerMin_HM[1755] or {}
-- table.insert(tOntimerMin_HM[1755],Summeractivities_brave_clearsysdyna)
-- tOntimerMin_HM[1756] = tOntimerMin_HM[1756] or {}
-- table.insert(tOntimerMin_HM[1756],Summeractivities_brave_clearsysdyna)
-- tOntimerMin_HM[1757] = tOntimerMin_HM[1757] or {}
-- table.insert(tOntimerMin_HM[1757],Summeractivities_brave_clearsysdyna)
-- tOntimerMin_HM[1758] = tOntimerMin_HM[1758] or {}
-- table.insert(tOntimerMin_HM[1758],Summeractivities_brave_clearsysdyna)
-- tOntimerMin_HM[1759] = tOntimerMin_HM[1759] or {}
-- table.insert(tOntimerMin_HM[1759],Summeractivities_brave_clearsysdyna)

--全服公告
-- tOntimerMin_HM[1800] = tOntimerMin_HM[1800] or {}
-- table.insert(tOntimerMin_HM[1800],Summeractivities_brave_broadcast)
-- tOntimerMin_HM[1801] = tOntimerMin_HM[1801] or {}
-- table.insert(tOntimerMin_HM[1801],Summeractivities_brave_broadcast)

--清场
-- tOntimerMin_HM[1900] = tOntimerMin_HM[1900] or {}
-- table.insert(tOntimerMin_HM[1900],Summeractivities_brave_clearuser)
-- tOntimerMin_HM[1901] = tOntimerMin_HM[1901] or {}
-- table.insert(tOntimerMin_HM[1901],Summeractivities_brave_clearuser)
-- tOntimerMin_HM[1902] = tOntimerMin_HM[1902] or {}
-- table.insert(tOntimerMin_HM[1902],Summeractivities_brave_clearuser)
-- tOntimerMin_HM[1903] = tOntimerMin_HM[1903] or {}
-- table.insert(tOntimerMin_HM[1903],Summeractivities_brave_clearuser)
-- tOntimerMin_HM[1904] = tOntimerMin_HM[1904] or {}
-- table.insert(tOntimerMin_HM[1904],Summeractivities_brave_clearuser)

---------------------------------------------------对话模板部分-----------------------------------------
-- 竞技冠军凌云
tNpcFace[2497] = 18
tNpcGossip[10296] = tNpcGossip[10296] or DefaultNpc:new{}
tNpcGossip[10296]["OptionHidden"] = 1

-- 活动前
tNpcGossip[10296]["Text1-1"] = {111,112}
tNpcGossip[10296]["Text111"] = tSummeractivities_brave_Text[10296]["Text111"]
tNpcGossip[10296]["Text112"] = tSummeractivities_brave_Text[10296]["Text112"]
tNpcGossip[10296]["tOption1-1"] = {1}
tNpcGossip[10296]["Option1"] = tSummeractivities_brave_Text[10296]["Option1"]
tNpcGossip[10296]["ChkFunc1-1"] = function ()
	return Sys_ChkFullTime(tSummeractivities_brave_Cont["Beftime"])
end

-- 活动后
tNpcGossip[10296]["Text1-2"] = {121}
tNpcGossip[10296]["Text121"] = tSummeractivities_brave_Text[10296]["Text121"]
tNpcGossip[10296]["tOption1-2"] = {2}
tNpcGossip[10296]["Option2"] = tSummeractivities_brave_Text[10296]["Option2"]
tNpcGossip[10296]["ChkFunc1-2"] = function ()
	return Sys_ChkFullTime(tSummeractivities_brave_Cont["Aftime"])
end

-- 活动中
tNpcGossip[10296]["Text1-3"] = {131,132}
tNpcGossip[10296]["Text131"] = tSummeractivities_brave_Text[10296]["Text131"]
tNpcGossip[10296]["Text132"] = tSummeractivities_brave_Text[10296]["Text132"]
tNpcGossip[10296]["tOption1-3"] = {3,4,5}
tNpcGossip[10296]["Option3"] = tSummeractivities_brave_Text[10296]["Option3"]
tNpcGossip[10296]["Option4"] = tSummeractivities_brave_Text[10296]["Option4"]
tNpcGossip[10296]["Option5"] = tSummeractivities_brave_Text[10296]["Option5"]
tNpcGossip[10296]["ChkFunc1-3"] = function ()
	return Sys_ChkFullTime(tSummeractivities_brave_Cont["Nowtime"])
end
tNpcGossip[10296]["OptionFunc3"]="Summeractivities_brave_Option3_10296</N>10296"
tNpcGossip[10296]["OptionPoint4"]="4"

tNpcGossip[10296]["Text4-1"] = {411,412}
tNpcGossip[10296]["Text411"] = tSummeractivities_brave_Text[10296]["Text411"]
tNpcGossip[10296]["Text412"] = tSummeractivities_brave_Text[10296]["Text412"]
tNpcGossip[10296]["tOption4-1"] = {6,7,8}
tNpcGossip[10296]["Option6"] = tSummeractivities_brave_Text[10296]["Option6"]
tNpcGossip[10296]["Option7"] = tSummeractivities_brave_Text[10296]["Option7"]
tNpcGossip[10296]["Option8"] = tSummeractivities_brave_Text[10296]["Option8"]

tNpcGossip[10296]["OptionPoint6"]="6"
tNpcGossip[10296]["OptionFunc7"]="Summeractivities_brave_Option3_10296</N>10296"

tNpcGossip[10296]["Text6-1"] = {611,612}
tNpcGossip[10296]["Text611"] = tSummeractivities_brave_Text[10296]["Text611"]
tNpcGossip[10296]["Text612"] = tSummeractivities_brave_Text[10296]["Text612"]
tNpcGossip[10296]["tOption6-1"] = {9,10}
tNpcGossip[10296]["Option9"] = tSummeractivities_brave_Text[10296]["Option9"]
tNpcGossip[10296]["Option10"] = tSummeractivities_brave_Text[10296]["Option10"]
tNpcGossip[10296]["OptionFunc9"]="Summeractivities_brave_Option3_10296</N>10296"

tNpcGossip[10296]["Text2-1"] = {211}
tNpcGossip[10296]["tOption2-1"] = {11}
tNpcGossip[10296]["Text211"] = tSummeractivities_brave_Text[10296]["Text211"]
tNpcGossip[10296]["Option11"] = tSummeractivities_brave_Text[10296]["Option11"]

tNpcGossip[10296]["Text2-2"] = {221}
tNpcGossip[10296]["tOption2-2"] = {12}
tNpcGossip[10296]["Text221"] = tSummeractivities_brave_Text[10296]["Text221"]
tNpcGossip[10296]["Option12"] = tSummeractivities_brave_Text[10296]["Option12"]



