------------------------------------------------------------------------------------
--Name:			150731[简体征服][活动脚本]2015万圣节(签到有好礼)(10.29-11.4)
--Purpose:		签到有好礼
--Creator:		王倩娜
--Created:		2015/07/31
------------------------------------------------------------------------------------

--命名前缀
--Halloween2015_SignInGift_

--掩码说明
--log	12000163	
--stc(137,04) 签到状态 ，1为签过
--stc(137,05) 格外奖励 ，1为领过



------------------------------数据表-----------------------------
local tHalloween2015_SignInGift_Cont = {}
		--活动时间
	tHalloween2015_SignInGift_Cont["ActivityTime"] = "2015-10-29 00:00 2015-11-04 23:59"
	tHalloween2015_SignInGift_Cont["BeforeActivityTime"] = "2015-01-01 00:00 2015-10-28 23:59"
	
	--玩家等级要求
	tHalloween2015_SignInGift_Cont["Metempsychosis"] = 0
	tHalloween2015_SignInGift_Cont["Level"] = 80

	-- 掩码
	--stc(137,04) 签到状态 ，1为签过
	tHalloween2015_SignInGift_Cont["SignIn"] = {}
		tHalloween2015_SignInGift_Cont["SignIn"]["Event"] = 137
		tHalloween2015_SignInGift_Cont["SignIn"]["StcType"] = 04
		tHalloween2015_SignInGift_Cont["SignIn"]["nRewardData"] = 1
	--stc(137,05) 格外奖励 ，1为领过
	tHalloween2015_SignInGift_Cont["Reward"] = {}
		tHalloween2015_SignInGift_Cont["Reward"]["Event"] = 137
		tHalloween2015_SignInGift_Cont["Reward"]["StcType"] = 05
		tHalloween2015_SignInGift_Cont["Reward"]["nRewardData"] = 1

	--背包
	tHalloween2015_SignInGift_Cont["BagSpace"] = 1
	-- 奖励物品
	tHalloween2015_SignInGift_Cont["FestivalId"] = 3456
	tHalloween2015_SignInGift_Cont["LogId"] = 12000163
	--给经验 
	tHalloween2015_SignInGift_Cont["RondomStart"] = 9
	tHalloween2015_SignInGift_Cont["RondomEnd"] = 10

	tHalloween2015_SignInGift_Cont["UserLevel"] = 140
	tHalloween2015_SignInGift_Cont["Exp"] = 60
	tHalloween2015_SignInGift_Cont["Cultivation"] = 50
	tHalloween2015_SignInGift_Cont["Bless"] = 24
		
	--各种光效
	tHalloween2015_SignInGift_Cont["SignEffect"] = "WarFlagEscortBegin"
	tHalloween2015_SignInGift_Cont["ExtraEffect"] = "zf2-e280"

	local tHalloween2015_SignInGift_Log = {}
		tHalloween2015_SignInGift_Log["FestivalPack"] = "0,0,0,0,12000163,2,3003625,1"
		tHalloween2015_SignInGift_Log["Exp"] = "0,0,0,0,12000163,2,4[5],60[24]"
		tHalloween2015_SignInGift_Log["Cultivation"] = "0,0,0,0,12000163,2[5],6,50[24]"
		tHalloween2015_SignInGift_Log["Bless"] = "0,0,0,0,12000163,2,5,25"
		
	 local tHalloween2015_SignInGift_NpcDetail= {}
	 	-- 南瓜大赛	17058	军方蔬菜供应商大瓜	1002	273,364		(128,73) 	1
		tHalloween2015_SignInGift_NpcDetail[1] = {}
		tHalloween2015_SignInGift_NpcDetail[1]["NpcId"] = 17058
		tHalloween2015_SignInGift_NpcDetail[1]["Event"] = 128
		tHalloween2015_SignInGift_NpcDetail[1]["StcType"] = 73
		tHalloween2015_SignInGift_NpcDetail[1]["Finsh"] = 1
		tHalloween2015_SignInGift_NpcDetail[1]["MapId"] = 1002
		tHalloween2015_SignInGift_NpcDetail[1]["CellX"] = 273
		tHalloween2015_SignInGift_NpcDetail[1]["CellY"] = 360
		-- 双龙游园	17080	游园大使小兔	1002	281,373		(128,75)	6
		tHalloween2015_SignInGift_NpcDetail[2] = {}
		tHalloween2015_SignInGift_NpcDetail[2]["NpcId"] = 17080
		tHalloween2015_SignInGift_NpcDetail[2]["Event"] = 128
		tHalloween2015_SignInGift_NpcDetail[2]["StcType"] = 75
		tHalloween2015_SignInGift_NpcDetail[2]["Finsh"] = 6
		tHalloween2015_SignInGift_NpcDetail[2]["MapId"] = 1002
		tHalloween2015_SignInGift_NpcDetail[2]["CellX"] = 284
		tHalloween2015_SignInGift_NpcDetail[2]["CellY"] = 360
		--杰克的游戏		17057	杰克  	1002	287,384		(128,67)	1
		tHalloween2015_SignInGift_NpcDetail[3] = {}
		tHalloween2015_SignInGift_NpcDetail[3]["NpcId"] = 17057
		tHalloween2015_SignInGift_NpcDetail[3]["Event"] = 128
		tHalloween2015_SignInGift_NpcDetail[3]["StcType"] = 67
		tHalloween2015_SignInGift_NpcDetail[3]["Finsh"] = 1
		tHalloween2015_SignInGift_NpcDetail[3]["MapId"] = 1002
		tHalloween2015_SignInGift_NpcDetail[3]["CellX"] = 273
		tHalloween2015_SignInGift_NpcDetail[3]["CellY"] = 384
		--女巫的南瓜	17055	女巫桑德拉	1002	272,373		(128,66)	1
		tHalloween2015_SignInGift_NpcDetail[4] = {}
		tHalloween2015_SignInGift_NpcDetail[4]["NpcId"] = 17055
		tHalloween2015_SignInGift_NpcDetail[4]["Event"] = 128
		tHalloween2015_SignInGift_NpcDetail[4]["StcType"] = 66
		tHalloween2015_SignInGift_NpcDetail[4]["Finsh"] = 1
		tHalloween2015_SignInGift_NpcDetail[4]["MapId"] = 1002
		tHalloween2015_SignInGift_NpcDetail[4]["CellX"] = 273
		tHalloween2015_SignInGift_NpcDetail[4]["CellY"] = 369
	-- 万圣节大变身	17053	变身巫师蒙迪尔	1002	285,384		(128,63)	100
		tHalloween2015_SignInGift_NpcDetail[5] = {}
		tHalloween2015_SignInGift_NpcDetail[5]["NpcId"] = 17053
		tHalloween2015_SignInGift_NpcDetail[5]["Event"] = 128
		tHalloween2015_SignInGift_NpcDetail[5]["StcType"] = 63
		tHalloween2015_SignInGift_NpcDetail[5]["Finsh"] = 100
		tHalloween2015_SignInGift_NpcDetail[5]["MapId"] = 1002
		tHalloween2015_SignInGift_NpcDetail[5]["CellX"] = 285
		tHalloween2015_SignInGift_NpcDetail[5]["CellY"] = 384
	-- 南瓜大战僵尸	17144	南瓜园园丁大叔	1002	300,367		(129,39)	2
		tHalloween2015_SignInGift_NpcDetail[6] = {}
		tHalloween2015_SignInGift_NpcDetail[6]["NpcId"] = 17144
		tHalloween2015_SignInGift_NpcDetail[6]["Event"] = 129
		tHalloween2015_SignInGift_NpcDetail[6]["StcType"] = 39
		tHalloween2015_SignInGift_NpcDetail[6]["Finsh"] = 2
		tHalloween2015_SignInGift_NpcDetail[6]["MapId"] = 1002
		tHalloween2015_SignInGift_NpcDetail[6]["CellX"] = 297
		tHalloween2015_SignInGift_NpcDetail[6]["CellY"] = 360
	-- 不给糖果就捣乱	17150	豆子熊	1002	299,379		(137,2)	2
		tHalloween2015_SignInGift_NpcDetail[7] = {}
		tHalloween2015_SignInGift_NpcDetail[7]["NpcId"] = 17150
		tHalloween2015_SignInGift_NpcDetail[7]["Event"] = 137
		tHalloween2015_SignInGift_NpcDetail[7]["StcType"] = 2
		tHalloween2015_SignInGift_NpcDetail[7]["Finsh"] = 2
		tHalloween2015_SignInGift_NpcDetail[7]["MapId"] = 1002
		tHalloween2015_SignInGift_NpcDetail[7]["CellX"] = 296
		tHalloween2015_SignInGift_NpcDetail[7]["CellY"] = 379
		
------------------------------逻辑-----------------------------
--每日签到
function Halloween2015_SignInGift_SignInAction(nNpcId)
	-- 判断活动时间
	if not Sys_ChkFullTime(tHalloween2015_SignInGift_Cont["ActivityTime"]) then
		LinkNpcGossipFunc_New(nNpcId,"1-3")
		return
	end
	
	-- 判断玩家等级
	if not User_JudgeLevelAndMetempsychosis(tHalloween2015_SignInGift_Cont["Level"],tHalloween2015_SignInGift_Cont["Metempsychosis"]) then
		Sys_MsgBox(tHalloween2015_SignInGift_Text["Msg"]["UnderLevel"])
		return
	end

	--一天只能签到
	local nEvent = tHalloween2015_SignInGift_Cont["SignIn"]["Event"]
	local nType = tHalloween2015_SignInGift_Cont["SignIn"]["StcType"]
	local nRewardData = tHalloween2015_SignInGift_Cont["SignIn"]["nRewardData"]
	
	if Task_ChkStcValue(nEvent,nType,">=",nRewardData) then
		-- 判断是否隔天
		if not Task_StcInterval(nEvent,nType,1,4) then
			Sys_MsgBox(tHalloween2015_SignInGift_Text["Msg"]["OnlyOnce"])
			return
		end
	end
	
	--赋值掩码
	Task_SetStatistic(nEvent,nType,nRewardData,1,0)
	Task_SetStcTimestamp(nEvent,nType,0,0)
	--给祝福
	User_AddBless(tHalloween2015_SignInGift_Cont["Bless"])
	
	local nStartNum = tHalloween2015_SignInGift_Cont["RondomStart"]
	local nEndNum = tHalloween2015_SignInGift_Cont["RondomEnd"]
	if not Sys_Random(nStartNum,nEndNum) then
		
		local nUserLev = Get_UserLevel()
		if nUserLev < tHalloween2015_SignInGift_Cont["UserLevel"] then
			local nExpTime = tHalloween2015_SignInGift_Cont["Exp"]
			User_AddExpTime(nExpTime)
			Sys_SaveActionFestivalLog(tHalloween2015_SignInGift_Log["Exp"])
			Sys_MsgBox(tHalloween2015_SignInGift_Text["Msg"]["Exp"])
		else
			local nCultivation = tHalloween2015_SignInGift_Cont["Cultivation"]
			User_AddCultivation(nCultivation)
			Sys_SaveActionFestivalLog(tHalloween2015_SignInGift_Log["Cultivation"])
			Sys_MsgBox(tHalloween2015_SignInGift_Text["Msg"]["Cultivation"])
		end
		
	else
		Sys_SaveActionFestivalLog(tHalloween2015_SignInGift_Log["Bless"])
		Sys_MsgBox(tHalloween2015_SignInGift_Text["Msg"]["Bless"])

	end
	User_EffectAdd("self",tHalloween2015_SignInGift_Cont["SignEffect"])
end
--寻路
function Halloween2015_SignInGift_GotoTheNpc(nNpcIndex)
	local nMapId = tHalloween2015_SignInGift_NpcDetail[nNpcIndex]["MapId"]
	local nPosX = tHalloween2015_SignInGift_NpcDetail[nNpcIndex]["CellX"]
	local nPosY = tHalloween2015_SignInGift_NpcDetail[nNpcIndex]["CellY"]
	local nNpcId = tHalloween2015_SignInGift_NpcDetail[nNpcIndex]["NpcId"]
	
	Sys_GotoSomeWhere(nPosX,nPosY,nMapId,nNpcId)
end
--额外奖励
function Halloween2015_SignInGift_CheakExtraReward(nNpcId)
	-- 判断活动时间
	if not Sys_ChkFullTime(tHalloween2015_SignInGift_Cont["ActivityTime"]) then
		LinkNpcGossipFunc_New(nNpcId,"1-3")
		return
	end
		--一天只能领奖1次
	local nRewEvent = tHalloween2015_SignInGift_Cont["Reward"]["Event"]
	local nRewType = tHalloween2015_SignInGift_Cont["Reward"]["StcType"]
	local nFinsh = tHalloween2015_SignInGift_Cont["Reward"]["nRewardData"]
	
	if Task_ChkStcValue(nRewEvent,nRewType,">=",nFinsh) then
		-- 判断是否隔天
		if not Task_StcInterval(nRewEvent,nRewType,1,4) then
			Sys_MsgBox(tHalloween2015_SignInGift_Text["Msg"]["HavedReward"])
			return
		else
			--隔天清理掩码
			Task_SetStatistic(nRewEvent,nRewType,0,1,0)
			Task_SetStcTimestamp(nRewEvent,nRewType,0,0)
		end
	end

	if not User_CheckLeftSpace(tHalloween2015_SignInGift_Cont["BagSpace"]) then
		Sys_MsgBox(tHalloween2015_SignInGift_Text["Msg"]["NoSpace"])
		return
	end
	
	if not Halloween2015_SignInGift_CheakAllEventFinsh() then
		Sys_MsgBox(tHalloween2015_SignInGift_Text["Msg"]["LessThan"])
		return
	end
	
	Task_SetStatistic(nRewEvent,nRewType,nFinsh,1,0)
	Task_SetStcTimestamp(nRewEvent,nRewType,0,0)
	FestivalGeneralPackage_GetGift(tHalloween2015_SignInGift_Cont["FestivalId"],tHalloween2015_SignInGift_Cont["LogId"])

	
	User_EffectAdd("self",tHalloween2015_SignInGift_Cont["ExtraEffect"])
	Sys_MsgBox(tHalloween2015_SignInGift_Text["Msg"]["GetFestivalID"])

end
--检测所有任务都完成了。且是当天完成，隔天就不能领取了
function Halloween2015_SignInGift_CheakAllEventFinsh()
	for k,v in ipairs(tHalloween2015_SignInGift_NpcDetail)  do
		local nEachEvent = v["Event"]
		local nEachType = v["StcType"]
		local nEachData = v["Finsh"]
		--未完成
		if not Task_ChkStcValue(nEachEvent,nEachType,">=",nEachData) then
			return false
		end
		--完成，隔天
		if Task_StcInterval(nEachEvent,nEachType,1,4) then
			return false
		end
	end
	--不存在未完成和隔天
	return true
end


------------------------------模板-----------------------------
--18781	中秋特使文青瑜
	tNpcFace[3161] = 216
	tNpcGossip[18781] = tNpcGossip[18781] or DefaultNpc:new{}
	tNpcGossip[18781]["OptionHidden"] = 1

	--活动时间前
	tNpcGossip[18781]["Text1-1"] = {111,112,113}
	tNpcGossip[18781]["Text111"] = tHalloween2015_SignInGift_Text[18781]["Text111"]
	tNpcGossip[18781]["Text112"] = tHalloween2015_SignInGift_Text[18781]["Text112"]
	tNpcGossip[18781]["Text113"] = tHalloween2015_SignInGift_Text[18781]["Text113"]
	tNpcGossip[18781]["tOption1-1"] = {1}
	tNpcGossip[18781]["ChkFunc1-1"] = function()
		return Sys_ChkFullTime(tHalloween2015_SignInGift_Cont["BeforeActivityTime"])
	end

	--活动时间中
	tNpcGossip[18781]["Text1-2"] = {121,122,123}
	tNpcGossip[18781]["Text121"] = tHalloween2015_SignInGift_Text[18781]["Text121"]
	tNpcGossip[18781]["Text122"] = tHalloween2015_SignInGift_Text[18781]["Text122"]
	tNpcGossip[18781]["Text123"] = tHalloween2015_SignInGift_Text[18781]["Text123"]
	tNpcGossip[18781]["tOption1-2"] = {2,3,4,5}
	tNpcGossip[18781]["ChkFunc1-2"] = function()
		return Sys_ChkFullTime(tHalloween2015_SignInGift_Cont["ActivityTime"])
	end
	
	-- 活动后
	tNpcGossip[18781]["Text1-3"] = {131}
	tNpcGossip[18781]["Text131"] = tHalloween2015_SignInGift_Text[18781]["Text131"]
	tNpcGossip[18781]["tOption1-3"] = {6}

	-- 介绍活动
	tNpcGossip[18781]["Text2-1"] = {211}
	tNpcGossip[18781]["Text211"] = tHalloween2015_SignInGift_Text[18781]["Text211"]
	tNpcGossip[18781]["tOption2-1"] = {7,8,9,10,11,12,13,14}

	tNpcGossip[18781]["Text3-1"] = {311,312}
	tNpcGossip[18781]["Text311"] = tHalloween2015_SignInGift_Text[18781]["Text311"]
	tNpcGossip[18781]["Text312"] = tHalloween2015_SignInGift_Text[18781]["Text312"]
	tNpcGossip[18781]["tOption3-1"] = {16,15,14}

	tNpcGossip[18781]["Text3-2"] = {321,322}
	tNpcGossip[18781]["Text321"] = tHalloween2015_SignInGift_Text[18781]["Text321"]
	tNpcGossip[18781]["Text322"] = tHalloween2015_SignInGift_Text[18781]["Text322"]
	tNpcGossip[18781]["tOption3-2"] = {17,15,14}

	tNpcGossip[18781]["Text3-3"] = {331,332}
	tNpcGossip[18781]["Text331"] = tHalloween2015_SignInGift_Text[18781]["Text331"]
	tNpcGossip[18781]["Text332"] = tHalloween2015_SignInGift_Text[18781]["Text332"]
	tNpcGossip[18781]["tOption3-3"] = {18,15,14}

	tNpcGossip[18781]["Text3-4"] = {341,342}
	tNpcGossip[18781]["Text341"] = tHalloween2015_SignInGift_Text[18781]["Text341"]
	tNpcGossip[18781]["Text342"] = tHalloween2015_SignInGift_Text[18781]["Text342"]
	tNpcGossip[18781]["tOption3-4"] = {19,15,14}

	tNpcGossip[18781]["Text3-5"] = {351,352}
	tNpcGossip[18781]["Text351"] = tHalloween2015_SignInGift_Text[18781]["Text351"]
	tNpcGossip[18781]["Text352"] = tHalloween2015_SignInGift_Text[18781]["Text352"]
	tNpcGossip[18781]["tOption3-5"] = {20,15,14}

	tNpcGossip[18781]["Text3-6"] = {361,362}
	tNpcGossip[18781]["Text361"] = tHalloween2015_SignInGift_Text[18781]["Text361"]
	tNpcGossip[18781]["Text362"] = tHalloween2015_SignInGift_Text[18781]["Text362"]
	tNpcGossip[18781]["tOption3-6"] = {21,15,14}

	tNpcGossip[18781]["Text3-7"] = {371,372}
	tNpcGossip[18781]["Text371"] = tHalloween2015_SignInGift_Text[18781]["Text371"]
	tNpcGossip[18781]["Text372"] = tHalloween2015_SignInGift_Text[18781]["Text372"]
	tNpcGossip[18781]["tOption3-7"] = {22,15,14}

	-- 选项
	tNpcGossip[18781]["Option1"] = tHalloween2015_SignInGift_Text[18781]["Option1"]
	--活动介绍
	tNpcGossip[18781]["Option2"] = tHalloween2015_SignInGift_Text[18781]["Option2"]
	tNpcGossip[18781]["OptionPoint2"] = "2-1"
	--签到
	tNpcGossip[18781]["Option3"] = tHalloween2015_SignInGift_Text[18781]["Option3"]
	tNpcGossip[18781]["OptionFunc3"] = "Halloween2015_SignInGift_SignInAction</N>18781"
	--额外奖励
	tNpcGossip[18781]["Option4"] = tHalloween2015_SignInGift_Text[18781]["Option4"]
	tNpcGossip[18781]["OptionFunc4"] = "Halloween2015_SignInGift_CheakExtraReward</N>18781"
	
	tNpcGossip[18781]["Option5"] = tHalloween2015_SignInGift_Text[18781]["Option5"]
	tNpcGossip[18781]["Option6"] = tHalloween2015_SignInGift_Text[18781]["Option6"]
	--各个活动
	tNpcGossip[18781]["Option7"] = tHalloween2015_SignInGift_Text[18781]["Option7"]
	tNpcGossip[18781]["OptionPoint7"] = "3-1"
	tNpcGossip[18781]["Option8"] = tHalloween2015_SignInGift_Text[18781]["Option8"]
	tNpcGossip[18781]["OptionPoint8"] = "3-2"
	tNpcGossip[18781]["Option9"] = tHalloween2015_SignInGift_Text[18781]["Option9"]
	tNpcGossip[18781]["OptionPoint9"] = "3-3"
	tNpcGossip[18781]["Option10"] = tHalloween2015_SignInGift_Text[18781]["Option10"]
	tNpcGossip[18781]["OptionPoint10"] = "3-4"
	tNpcGossip[18781]["Option11"] = tHalloween2015_SignInGift_Text[18781]["Option11"]
	tNpcGossip[18781]["OptionPoint11"] = "3-5"
	tNpcGossip[18781]["Option12"] = tHalloween2015_SignInGift_Text[18781]["Option12"]
	tNpcGossip[18781]["OptionPoint12"] = "3-6"
	tNpcGossip[18781]["Option13"] = tHalloween2015_SignInGift_Text[18781]["Option13"]
	tNpcGossip[18781]["OptionPoint13"] = "3-7"
	tNpcGossip[18781]["Option14"] = tHalloween2015_SignInGift_Text[18781]["Option14"]

	--返回上一页
	tNpcGossip[18781]["Option15"] = tHalloween2015_SignInGift_Text[18781]["Option15"]
	tNpcGossip[18781]["OptionPoint15"] = "2-1"

	tNpcGossip[18781]["Option16"] = tHalloween2015_SignInGift_Text[18781]["Option16"]
	tNpcGossip[18781]["Option17"] = tHalloween2015_SignInGift_Text[18781]["Option17"]
	tNpcGossip[18781]["Option18"] = tHalloween2015_SignInGift_Text[18781]["Option18"]
	tNpcGossip[18781]["Option19"] = tHalloween2015_SignInGift_Text[18781]["Option19"]
	tNpcGossip[18781]["Option20"] = tHalloween2015_SignInGift_Text[18781]["Option20"]
	tNpcGossip[18781]["Option21"] = tHalloween2015_SignInGift_Text[18781]["Option21"]
	tNpcGossip[18781]["Option22"] = tHalloween2015_SignInGift_Text[18781]["Option22"]
	tNpcGossip[18781]["OptionFunc16"] = "Halloween2015_SignInGift_GotoTheNpc</N>1"
	tNpcGossip[18781]["OptionFunc17"] = "Halloween2015_SignInGift_GotoTheNpc</N>2"
	tNpcGossip[18781]["OptionFunc18"] = "Halloween2015_SignInGift_GotoTheNpc</N>3"
	tNpcGossip[18781]["OptionFunc19"] = "Halloween2015_SignInGift_GotoTheNpc</N>4"
	tNpcGossip[18781]["OptionFunc20"] = "Halloween2015_SignInGift_GotoTheNpc</N>5"
	tNpcGossip[18781]["OptionFunc21"] = "Halloween2015_SignInGift_GotoTheNpc</N>6"
	tNpcGossip[18781]["OptionFunc22"] = "Halloween2015_SignInGift_GotoTheNpc</N>7"
