------------------------------------------------------------------------------------
--Name:			[征服][活动脚本]周年庆点赞、签到(4.27-5.11)
--Purpose:		周年庆活动--点赞、签到(4.27-5.11)
--Creator:		王倩娜
--Created:		2015/07/04
------------------------------------------------------------------------------------

--	命名前缀
--	Anniversary2015_SignIn_

--	掩码说明

--task_detail 6412
-- stc(122,41) 连续签到的次数
-- stc(122,42) 连签奖励的领取情况

--LOGID	10002166

--常量表配置
local tAnniversary2015_SignIn_Cont = {}
	--活动时间
	tAnniversary2015_SignIn_Cont["ActivityTime"] = "2015-05-07 00:00 2015-05-27 23:59"
	tAnniversary2015_SignIn_Cont["BeforeActivityTime"] = "2015-01-01 00:00 2015-05-06 23:59"

	--玩家等级要求
	tAnniversary2015_SignIn_Cont["Metempsychosis"] = 0
	tAnniversary2015_SignIn_Cont["Level"] = 80
	
	-- 掩码
	-- stc(122,41) 连续签到的次数
	tAnniversary2015_SignIn_Cont["SignTime"] = {}
		tAnniversary2015_SignIn_Cont["SignTime"]["Event"] = 122
		tAnniversary2015_SignIn_Cont["SignTime"]["StcType"] = 41
		tAnniversary2015_SignIn_Cont["SignTime"]["Reward"] = {}
			tAnniversary2015_SignIn_Cont["SignTime"]["Reward"][3] = 3
			tAnniversary2015_SignIn_Cont["SignTime"]["Reward"][6] = 6
			tAnniversary2015_SignIn_Cont["SignTime"]["Reward"][9] = 9
			tAnniversary2015_SignIn_Cont["SignTime"]["Reward"][12] = 12
			tAnniversary2015_SignIn_Cont["SignTime"]["Reward"][13] = 13
			tAnniversary2015_SignIn_Cont["SignTime"]["Reward"][14] = 14

	-- stc(122,42) 连签奖励的领取情况
	tAnniversary2015_SignIn_Cont["SReward"] = {}
	tAnniversary2015_SignIn_Cont["SReward"]["Event"] = 122
	tAnniversary2015_SignIn_Cont["SReward"]["StcType"] = 42
	tAnniversary2015_SignIn_Cont["SReward"]["Finish"] = {}
		tAnniversary2015_SignIn_Cont["SReward"]["Finish"][3] = 3
		tAnniversary2015_SignIn_Cont["SReward"]["Finish"][6] = 6
		tAnniversary2015_SignIn_Cont["SReward"]["Finish"][9] = 9
		tAnniversary2015_SignIn_Cont["SReward"]["Finish"][12] = 12
		tAnniversary2015_SignIn_Cont["SReward"]["Finish"][13] = 13
		tAnniversary2015_SignIn_Cont["SReward"]["Finish"][14] = 14

	--背包空间
	tAnniversary2015_SignIn_Cont["BagSpace"] = {}
		tAnniversary2015_SignIn_Cont["BagSpace"][1] = 1
		tAnniversary2015_SignIn_Cont["BagSpace"][2] = 2

	-- 奖励物品
	tAnniversary2015_SignIn_Cont["FestivalId"] = 3404
	tAnniversary2015_SignIn_Cont["LogId"] = 10002166
	tAnniversary2015_SignIn_Cont["RewardItem"] = {}
		tAnniversary2015_SignIn_Cont["RewardItem"][3] = 720828
		tAnniversary2015_SignIn_Cont["RewardItem"][6] = 3003519
		tAnniversary2015_SignIn_Cont["RewardItem"][9] = 721316
		tAnniversary2015_SignIn_Cont["RewardItem"][12] = 710214
		tAnniversary2015_SignIn_Cont["RewardItem"][13] = 3002431
		tAnniversary2015_SignIn_Cont["RewardItem"][14] = 1100003
		tAnniversary2015_SignIn_Cont["RewardItem"]["Monopoly"] = 3
	
	
-- --各种光效
	local tAnniversary2015_SignIn_Effect = {}
		tAnniversary2015_SignIn_Effect["EXP"] = "angelwing"
		tAnniversary2015_SignIn_Effect["doubleEXP"] = "accession"
	
-- --LOG 表
	local tAnniversary2015_SignIn_LOG = {}
		--获得礼包
		tAnniversary2015_SignIn_LOG["GetReward"] = "0,0,0,0,10002166,2,3007625,1"
		--额外获奖
		tAnniversary2015_SignIn_LOG["ExtraReward"] = "0,0,0,0,10002166,2,%d,1"
	


-- --------------------------------------逻辑部分-----------------------------------------

--签到
function	Anniversary2015_SignIn_SignIn(nNpcId)
	if not User_JudgeLevelAndMetempsychosis(tAnniversary2015_SignIn_Cont["Level"],tAnniversary2015_SignIn_Cont["Metempsychosis"]) then
		LinkNpcGossipFunc_New(nNpcId,"4-1")
		return
	end
	if not User_CheckLeftSpace(tAnniversary2015_SignIn_Cont["BagSpace"][2]) then
		LinkNpcGossipFunc_New(nNpcId,"4-2")
		return
	end
	-- 等于0且超过2天,第一次或断签后第一次
	local nEvent = tAnniversary2015_SignIn_Cont["SignTime"]["Event"]
	local nType = tAnniversary2015_SignIn_Cont["SignTime"]["StcType"]
	if Task_ChkStcValue(nEvent,nType,">",0) then
		if Task_StcInterval(nEvent,nType,2,4) then
			 Task_SetStatistic(nEvent,nType,0,1,0)
			 Task_SetStcTimestamp(nEvent,nType,0,0)
		 elseif not Task_StcInterval(nEvent,nType,1,4) then
			LinkNpcGossipFunc_New(nNpcId,"4-3")
			return
		end
	end
		local nTemp = Get_UserStatisticValue(nEvent,nType)
		nTemp = nTemp + 1
		Task_SetStatistic(nEvent,nType,nTemp,1,0)
		Task_SetStcTimestamp(nEvent,nType,0,0)
		local nTimes = Get_UserStatisticValue(nEvent,nType)

		--给连签奖励
		Anniversary2015_SignIn_ExtraReward(nNpcId,nTimes) 
		--给普通奖励
		Anniversary2015_SignIn_FestivalReward(nTimes)
end

--给普通奖励
function Anniversary2015_SignIn_FestivalReward(nTimes)
	local nUserLev = Get_UserLevel()
	--给节日礼包
	FestivalGeneralPackage_GetGift(tAnniversary2015_SignIn_Cont["FestivalId"],tAnniversary2015_SignIn_Cont["LogId"])
	Sys_SaveActionFestivalLog(tAnniversary2015_SignIn_LOG["GetReward"])
	User_TalkChannel2005(tAnniversary2015_SignIn_Text["GetReward"])
	-- 给经验值和修行值
	--次签到都有30%几率今天的基础经验和修行值奖励翻倍
	if Sys_Random(30,100) then
		--天数*20的战斗分钟经验和修行值
		local nTemp = nTimes * 20
		if nUserLev < 140 then 
			User_AddExp(User_CalcTimeToExp(nTemp))
		end
		User_AddCultivation(nTemp,nUserId)
		User_EffectAdd("self",tAnniversary2015_SignIn_Effect["doubleEXP"])
	else
		--天数*10的战斗分钟经验和修行值
		local nTemp = nTimes * 10
		if nUserLev < 140 then 
			User_AddExp(User_CalcTimeToExp(nTemp))
		end
		User_AddCultivation(nTemp,nUserId)
		User_EffectAdd("self",tAnniversary2015_SignIn_Effect["EXP"])
	end
end 

--给连签奖励
function Anniversary2015_SignIn_ExtraReward(nNpcId,nTimes)
	local tTable = {3,6,9,12,13,14}
	for i = 1,#tTable do
		--符合连签奖励
		if nTimes == tTable[i] then
			local nExtraEvent = tAnniversary2015_SignIn_Cont["SReward"]["Event"]
			local nExtraType = tAnniversary2015_SignIn_Cont["SReward"]["StcType"]
			-- 判断是否领取
			if Task_ChkStcValue(nExtraEvent,nExtraType,"<",nTimes) then

				-- if not User_CheckLeftSpace(tAnniversary2015_SignIn_Cont["BagSpace"][2]) then
					-- LinkNpcGossipFunc_New(nNpcId,"4-2")
					-- return
				-- end
				Task_SetStatistic(nExtraEvent,nExtraType,nTimes,1,0)
				if nTimes < 14 then 
					Item_AddItem(tAnniversary2015_SignIn_Cont["RewardItem"][nTimes],0,0,tAnniversary2015_SignIn_Cont["RewardItem"]["Monopoly"])
				else 
					Item_AddItem(tAnniversary2015_SignIn_Cont["RewardItem"][nTimes])
				end 
				local str_Log = string.format(tAnniversary2015_SignIn_LOG["ExtraReward"],tAnniversary2015_SignIn_Cont["RewardItem"][nTimes])
				Sys_SaveActionFestivalLog(str_Log)
				
				local str = string.format(tAnniversary2015_SignIn_Text[16497]["Text451"],nTimes,tAnniversary2015_SignIn_Text["RewardItem"][nTimes])
				Sys_DialogText(str)
				Sys_DialogOption(tAnniversary2015_SignIn_Text[16497]["Option19"],"</F>NULL")
				Sys_DialogFace(nNpcId)
				Sys_DialogEnd()
				return
			end
		end 
	end 
		local str = string.format(tAnniversary2015_SignIn_Text[16497]["Text441"],nTimes)
		Sys_DialogText(str)
		Sys_DialogOption(tAnniversary2015_SignIn_Text[16497]["Option19"],"</F>NULL")
		Sys_DialogFace(nNpcId)
		Sys_DialogEnd()

end 			



--查连签次数
function Anniversary2015_SignIn_CheckScore(nNpcId)
	local nEvent = tAnniversary2015_SignIn_Cont["SignTime"]["Event"]
	local nType = tAnniversary2015_SignIn_Cont["SignTime"]["StcType"]
	
	-- 不等于0且超过2天
	if Task_ChkStcValue(nEvent,nType,"~=",0) and Task_StcInterval(nEvent,nType,2,4) then
		Task_SetStatistic(nEvent,nType,0,1,0)
		Task_SetStcTimestamp(nEvent,nType,0,0)
	end

	local nTemp = Get_UserStatisticValue(nEvent,nType)
	local str = string.format(tAnniversary2015_SignIn_Text[16497]["Text311"],nTemp)
		Sys_DialogText(str)
		Sys_DialogOption(tAnniversary2015_SignIn_Text[16497]["Option15"],"</F>NULL")
		Sys_DialogFace(nNpcId)
		Sys_DialogEnd()
end 
--------------------------------------NPC模块-------------------------------------------
	--16497	签到登记使者亲亲
	tNpcFace[2937] = 157
	tNpcGossip[16497] = tNpcGossip[16497] or DefaultNpc:new{}
	tNpcGossip[16497]["OptionHidden"] = 1


	--活动时间前
	tNpcGossip[16497]["Text1-1"] = {111,112,113}
	tNpcGossip[16497]["Text111"] = tAnniversary2015_SignIn_Text[16497]["Text111"]
	tNpcGossip[16497]["Text112"] = tAnniversary2015_SignIn_Text[16497]["Text112"]
	tNpcGossip[16497]["Text113"] = tAnniversary2015_SignIn_Text[16497]["Text113"]
	tNpcGossip[16497]["tOption1-1"] = {1}
	tNpcGossip[16497]["ChkFunc1-1"] = function()
		return Sys_ChkFullTime(tAnniversary2015_SignIn_Cont["BeforeActivityTime"])
	end

	--活动时间中
	tNpcGossip[16497]["Text1-2"] = {121,122,123}
	tNpcGossip[16497]["Text121"] = tAnniversary2015_SignIn_Text[16497]["Text121"]
	tNpcGossip[16497]["Text122"] = tAnniversary2015_SignIn_Text[16497]["Text122"]
	tNpcGossip[16497]["Text123"] = tAnniversary2015_SignIn_Text[16497]["Text123"]
	tNpcGossip[16497]["tOption1-2"] = {3,4,5,6}
	tNpcGossip[16497]["ChkFunc1-2"] = function()
		return Sys_ChkFullTime(tAnniversary2015_SignIn_Cont["ActivityTime"])
	end

	--活动时间后
	tNpcGossip[16497]["Text1-3"] = {131}
	tNpcGossip[16497]["Text131"] = tAnniversary2015_SignIn_Text[16497]["Text131"]
	tNpcGossip[16497]["tOption1-3"] = {2}

	--规则
	tNpcGossip[16497]["Text2-1"] = {211,212}
	tNpcGossip[16497]["Text211"] = tAnniversary2015_SignIn_Text[16497]["Text211"]
	tNpcGossip[16497]["Text212"] = tAnniversary2015_SignIn_Text[16497]["Text212"]
	tNpcGossip[16497]["tOption2-1"] = {7,8}

	tNpcGossip[16497]["Text2-2"] = {221,222,223,224,225,226,227}
	tNpcGossip[16497]["Text221"] = tAnniversary2015_SignIn_Text[16497]["Text221"]
	tNpcGossip[16497]["Text222"] = tAnniversary2015_SignIn_Text[16497]["Text222"]
	tNpcGossip[16497]["Text223"] = tAnniversary2015_SignIn_Text[16497]["Text223"]
	tNpcGossip[16497]["Text224"] = tAnniversary2015_SignIn_Text[16497]["Text224"]
	tNpcGossip[16497]["Text225"] = tAnniversary2015_SignIn_Text[16497]["Text225"]
	tNpcGossip[16497]["Text226"] = tAnniversary2015_SignIn_Text[16497]["Text226"]
	tNpcGossip[16497]["Text227"] = tAnniversary2015_SignIn_Text[16497]["Text227"]
	tNpcGossip[16497]["tOption2-2"] = {8}

	--查询连签
	tNpcGossip[16497]["Text3-1"] = {311}
	tNpcGossip[16497]["Text311"] = tAnniversary2015_SignIn_Text[16497]["Text311"]
	tNpcGossip[16497]["tOption3-1"] = {15}

	--签到
	tNpcGossip[16497]["Text4-1"] = {411}
	tNpcGossip[16497]["Text411"] = tAnniversary2015_SignIn_Text[16497]["Text411"]
	tNpcGossip[16497]["tOption4-1"] = {16}

	tNpcGossip[16497]["Text4-2"] = {421}
	tNpcGossip[16497]["Text421"] = tAnniversary2015_SignIn_Text[16497]["Text421"]
	tNpcGossip[16497]["tOption4-2"] = {17}
	
	tNpcGossip[16497]["Text4-3"] = {431}
	tNpcGossip[16497]["Text431"] = tAnniversary2015_SignIn_Text[16497]["Text431"]
	tNpcGossip[16497]["tOption4-3"] = {18}
	
	tNpcGossip[16497]["Text4-4"] = {441}
	tNpcGossip[16497]["Text441"] = tAnniversary2015_SignIn_Text[16497]["Text441"]
	tNpcGossip[16497]["tOption4-4"] = {19}
	
	tNpcGossip[16497]["Text4-5"] = {451}
	tNpcGossip[16497]["Text451"] = tAnniversary2015_SignIn_Text[16497]["Text451"]
	tNpcGossip[16497]["tOption4-5"] = {19}
	
	
	
	--npc选项
	tNpcGossip[16497]["Option1"] = tAnniversary2015_SignIn_Text[16497]["Option1"]
	tNpcGossip[16497]["Option2"] = tAnniversary2015_SignIn_Text[16497]["Option2"]

	tNpcGossip[16497]["Option3"] = tAnniversary2015_SignIn_Text[16497]["Option3"]
	tNpcGossip[16497]["OptionFunc3"]="Anniversary2015_SignIn_SignIn</N>16497"
	tNpcGossip[16497]["OptionChkFunc3"] = function ()
		return  Sys_ChkFullTime(tAnniversary2015_SignIn_Cont["ActivityTime"])
	end
	tNpcGossip[16497]["Option4"] = tAnniversary2015_SignIn_Text[16497]["Option4"]
	tNpcGossip[16497]["OptionFunc4"]="Anniversary2015_SignIn_CheckScore</N>16497"
	tNpcGossip[16497]["OptionChkFunc4"] = function ()
		return  Sys_ChkFullTime(tAnniversary2015_SignIn_Cont["ActivityTime"])
	end

	tNpcGossip[16497]["Option5"] = tAnniversary2015_SignIn_Text[16497]["Option5"]
	tNpcGossip[16497]["OptionPoint5"]="2-1"
	tNpcGossip[16497]["Option6"] = tAnniversary2015_SignIn_Text[16497]["Option6"]
	tNpcGossip[16497]["Option7"] = tAnniversary2015_SignIn_Text[16497]["Option7"]
	tNpcGossip[16497]["OptionPoint7"]="2-2"
	tNpcGossip[16497]["Option8"] = tAnniversary2015_SignIn_Text[16497]["Option8"]
	tNpcGossip[16497]["Option9"] = tAnniversary2015_SignIn_Text[16497]["Option9"]
	tNpcGossip[16497]["Option10"] = tAnniversary2015_SignIn_Text[16497]["Option10"]
	tNpcGossip[16497]["Option11"] = tAnniversary2015_SignIn_Text[16497]["Option11"]
	tNpcGossip[16497]["Option12"] = tAnniversary2015_SignIn_Text[16497]["Option12"]
	tNpcGossip[16497]["Option13"] = tAnniversary2015_SignIn_Text[16497]["Option13"]
	tNpcGossip[16497]["Option14"] = tAnniversary2015_SignIn_Text[16497]["Option14"]
	tNpcGossip[16497]["Option15"] = tAnniversary2015_SignIn_Text[16497]["Option15"]
	tNpcGossip[16497]["Option16"] = tAnniversary2015_SignIn_Text[16497]["Option16"]
	tNpcGossip[16497]["Option17"] = tAnniversary2015_SignIn_Text[16497]["Option17"]
	tNpcGossip[16497]["Option18"] = tAnniversary2015_SignIn_Text[16497]["Option18"]
	tNpcGossip[16497]["Option19"] = tAnniversary2015_SignIn_Text[16497]["Option19"]

	