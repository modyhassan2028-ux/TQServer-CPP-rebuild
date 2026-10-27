------------------------------------------------------------------------------------
--Name:			150706[简体征服][活动脚本]万圣节大变身（10.29-11.4）
--Purpose:		万圣节（10.29-11.4）之万圣节大变身
--Creator:		黄昕哲
--Created:		2015/07/08
------------------------------------------------------------------------------------
--前缀Halloween2015_Transform_
--复用2014年万圣节

--stc(128,63) 变身目标1-6 完成变身10-60 完成领奖100
--stc(128,64) 每次变身间隔时间，为2表示符合变身要求。
--stc(128,65) 最多两次的20修行值奖励
--stc(139,52) 防止玩家脸黑的变身错误上限,记录满次数后玩家一定变身成功
----------------------表定义-------------------------------------
local tHalloween2015_Transform_Data = {}
tHalloween2015_Transform_Data["Before"] = "2015-01-01 00:00 2015-10-28 23:59"
tHalloween2015_Transform_Data["During"] = "2015-10-29 00:00 2015-11-04 23:59"

tHalloween2015_Transform_Data["MinLev"] = 80
tHalloween2015_Transform_Data["MaxLev"] = 140
tHalloween2015_Transform_Data["MinMeto"] = 0

tHalloween2015_Transform_Data["Cult"] = 20

--玩家的状态参数nStatus,nPower,nSecs,nTimes,nunRemainTime,nunEndTime,nucRecordable,nusFrom,nunData,nUserId
--眩晕时间缩短为1秒
local tHalloween2015_Transform_Status = {}
tHalloween2015_Transform_Status["Stun"] = {}
tHalloween2015_Transform_Status["Stun"]["Status"] = 55
tHalloween2015_Transform_Status["Stun"]["Power"] = 200
tHalloween2015_Transform_Status["Stun"]["Sec"] = 1
tHalloween2015_Transform_Status["Stun"]["Times"] = 1
tHalloween2015_Transform_Status["Stun"]["RemainTime"] = 1
tHalloween2015_Transform_Status["Stun"]["EndTime"] = 1
tHalloween2015_Transform_Status["Stun"]["Recordable"] = 1

tHalloween2015_Transform_Status["Mirror"] = {}
tHalloween2015_Transform_Status["Mirror"]["Status"] = 57
tHalloween2015_Transform_Status["Mirror"]["Power"] = 0
tHalloween2015_Transform_Status["Mirror"]["Sec"] = 15
tHalloween2015_Transform_Status["Mirror"]["Times"] = 1
tHalloween2015_Transform_Status["Mirror"]["RemainTime"] = 15
tHalloween2015_Transform_Status["Mirror"]["EndTime"] = 1
tHalloween2015_Transform_Status["Mirror"]["Recordable"] = 1

local tHalloween2015_Transform_Id = {}
tHalloween2015_Transform_Id["Candy"] = 3003675
tHalloween2015_Transform_Id["Antidote"] = 3003676

local tHalloween2015_Transform_Effect = {}
tHalloween2015_Transform_Effect["GetReward"] = "zf2-e280"
tHalloween2015_Transform_Effect["TransForm"] = "BodyDisapear"

local tHalloween2015_Transform_FormId = {}
tHalloween2015_Transform_FormId[1] = 233
tHalloween2015_Transform_FormId[2] = 126
tHalloween2015_Transform_FormId[3] = 151
tHalloween2015_Transform_FormId[4] = 163
tHalloween2015_Transform_FormId[5] = 227
tHalloween2015_Transform_FormId[6] = 226

--nSkill,nSkillType,nMonsterType,nTime,nUserId
local tHalloween2015_Transform_FormMagic = {}
tHalloween2015_Transform_FormMagic["Skill"] = {}
tHalloween2015_Transform_FormMagic["Skill"]["Stone"] = {12250,12251,12252,12253,12254,12255}
tHalloween2015_Transform_FormMagic["Skill"]["Candy"] = {12180,12181,12182,12183,12184,12185}
tHalloween2015_Transform_FormMagic["MonsterLevel"] = 0
tHalloween2015_Transform_FormMagic["MonsterType"] = {}
tHalloween2015_Transform_FormMagic["MonsterType"] = {2102,2104,2478,3624,3601,3610}
tHalloween2015_Transform_FormMagic["Time"] = {}
tHalloween2015_Transform_FormMagic["Time"]["Stone"] = 15
tHalloween2015_Transform_FormMagic["Time"]["Candy"] = 3600

--自动寻路相关
local tHalloween2015_Transform_AutoFindWay = {}
	tHalloween2015_Transform_AutoFindWay["Id"] = 17054
	tHalloween2015_Transform_AutoFindWay["MapId"] = 1002
	tHalloween2015_Transform_AutoFindWay["CellX"] = 289
	tHalloween2015_Transform_AutoFindWay["CellY"] = 384

local tHalloween2015_Transform_Rate = {}
tHalloween2015_Transform_Rate["Total"] = 100
--失败,眩晕5秒
tHalloween2015_Transform_Rate["Stun"] = 15
--成功,逆向
tHalloween2015_Transform_Rate["Mirror"] = tHalloween2015_Transform_Rate["Stun"] + 15
--成功,20修行值
tHalloween2015_Transform_Rate["Cult"] = tHalloween2015_Transform_Rate["Mirror"] + 15
--成功,糖果
tHalloween2015_Transform_Rate["Candy"] = tHalloween2015_Transform_Rate["Cult"] + 15
--成功,随机变为鬼怪外形15秒
--tHalloween2015_Transform_Rate["Ghost"] = 40

local tHalloween2015_Transform_Stc = {}
tHalloween2015_Transform_Stc["Trans"] = {}
tHalloween2015_Transform_Stc["Trans"]["EventType"] = 128
tHalloween2015_Transform_Stc["Trans"]["DataType"] = 63

tHalloween2015_Transform_Stc["Times"] = {}
tHalloween2015_Transform_Stc["Times"]["EventType"] = 136
tHalloween2015_Transform_Stc["Times"]["DataType"] = 52
tHalloween2015_Transform_Stc["Times"]["Limit"] = 3

tHalloween2015_Transform_Stc["Interval"] = {}
tHalloween2015_Transform_Stc["Interval"]["EventType"] = 128
tHalloween2015_Transform_Stc["Interval"]["DataType"] = 64
tHalloween2015_Transform_Stc["Interval"]["Limit"] = 5

tHalloween2015_Transform_Stc["Cult"] = {}
tHalloween2015_Transform_Stc["Cult"]["EventType"] = 128
tHalloween2015_Transform_Stc["Cult"]["DataType"] = 65
tHalloween2015_Transform_Stc["Cult"]["Limt"] = 2

local tHalloween2015_Transform_Phase = {}
--变身前存储将要变的形态
tHalloween2015_Transform_Phase["TransMin"] = 1
tHalloween2015_Transform_Phase["TransMax"] = 6
--变身后为变身前*10
tHalloween2015_Transform_Phase["CompleteMin"] = 10
tHalloween2015_Transform_Phase["CompleteMax"] = 60
--任务完成,已收到礼包
tHalloween2015_Transform_Phase["GetReward"] = 100

local tHalloween2015_Transform_Log = {}
tHalloween2015_Transform_Log["StartTask"] = "0,0,0,0,10002305,1[1],0,0"
tHalloween2015_Transform_Log["FestivalId"] = 3456
tHalloween2015_Transform_Log["LogId"] = 10002305
tHalloween2015_Transform_Log["FestivalPack"] = "0,0,0,0,10002305,2,3003625,1"
tHalloween2015_Transform_Log["Cult"] = "0,0,0,0,10002305,2,6,20"
tHalloween2015_Transform_Log["Candy"] = "0,0,0,0,10002305,2,3004664,1"
tHalloween2015_Transform_Log["TransCorrect"] = "0,0,0,0,10002305,1[2],0,0"
tHalloween2015_Transform_Log["DropCandy"] = "0,0,3004664,1,10002305,3,0,0"

tHalloween2015_Transform_Log["Antidote"] = "0,0,3004664,1,10002305,2,3004665,1"
tHalloween2015_Transform_Log["UseAntidote"] = "0,0,3004665,1,10002305,3,0,0"

--------------------------逻辑部分------------------------
math.randomseed(os.time())
--任务隔天清理
function Halloween2015_Transform_CrossDay()
	local nTransEvent = tHalloween2015_Transform_Stc["Trans"]["EventType"]
	local nTransType = tHalloween2015_Transform_Stc["Trans"]["DataType"]
	local nTimesEvent = tHalloween2015_Transform_Stc["Times"]["EventType"]
	local nTimesType = tHalloween2015_Transform_Stc["Times"]["DataType"]
	if Task_ChkStcValue(nTransEvent,nTransType,">=",tHalloween2015_Transform_Phase["GetReward"]) and Task_StcInterval(nTransEvent,nTransType,1,4) then
		Task_SetStatistic(nTransEvent,nTransType,0,1)
		Task_SetStcTimestamp(nTransEvent,nTransType,0)
		Task_SetStatistic(nTimesEvent,nTimesType,0,1)
		Task_SetStcTimestamp(nTimesEvent,nTimesType,0)
	end
end

--选项检查	17053/17054
function Halloween2015_Transform_ChoiceChk(nNpcId)
	local nTransEvent = tHalloween2015_Transform_Stc["Trans"]["EventType"]
	local nTransType = tHalloween2015_Transform_Stc["Trans"]["DataType"]
	--mage
	if nNpcId == 17053 then
		if Task_ChkStcValue(nTransEvent,nTransType,"<",tHalloween2015_Transform_Phase["CompleteMin"]) then
			return true
		end
		if Task_ChkStcValue(nTransEvent,nTransType,">=",tHalloween2015_Transform_Phase["GetReward"]) and Task_StcInterval(nTransEvent,nTransType,1,4) then
			return true
		end
		return false
	--stone
	elseif nNpcId == 17054 then
		if Task_ChkStcValue(nTransEvent,nTransType,"==",0) or Task_ChkStcValue(nTransEvent,nTransType,">=",tHalloween2015_Transform_Phase["GetReward"]) then
			return true
		end
		return false
	end
end

--自动寻路
function Halloween2015_Transform_AutoFindWay()
	local nNpcId = tHalloween2015_Transform_AutoFindWay["Id"]
	local nMapId = tHalloween2015_Transform_AutoFindWay["MapId"]
	local nCellX = tHalloween2015_Transform_AutoFindWay["CellX"]
	local nCellY = tHalloween2015_Transform_AutoFindWay["CellY"]
	Sys_GotoSomeWhere(nCellX,nCellY,nMapId,nNpcId)
end

--来试一试
function Halloween2015_Transform_JoinAct(nNpcId)
	--检查任务条件,非任务时间则退出
	if not Sys_ChkFullTime(tHalloween2015_Transform_Data["During"]) then
		LinkNpcGossipFunc_New(nNpcId,"1-3")
		return
	end
	if not User_JudgeLevelAndMetempsychosis(tHalloween2015_Transform_Data["MinLev"],tHalloween2015_Transform_Data["MinMeto"]) then
		--等级不足
		LinkNpcGossipFunc_New(nNpcId,"2-1")
		return
	end
	local nTransEvent = tHalloween2015_Transform_Stc["Trans"]["EventType"]
	local nTransType = tHalloween2015_Transform_Stc["Trans"]["DataType"]
			--已接到任务
	if Task_ChkStcValue(nTransEvent,nTransType,">=",tHalloween2015_Transform_Phase["TransMin"]) then
		local nSaveForm = Get_UserStatisticValue(nTransEvent,nTransType)
		--变身状态正确
		if Get_UserTransformId() == nSaveForm%10 then
			Halloween2015_Transform_ApplyReward(nNpcId)
			return
		end
		--变身状态不正确
		tNpcGossip[17053]["Text231"] = string.format(tHalloween2015_Transform_Text[17053]["Text231"],tHalloween2015_Transform_Text["Form"][nSaveForm])
		LinkNpcGossipFunc_New(nNpcId,"2-3")
		return
	end
	--条件满足
	local nFormNum = math.random(#tHalloween2015_Transform_Text["Form"])
	Task_SetStatistic(nTransEvent,nTransType,nFormNum,1)
	Task_SetStcTimestamp(nTransEvent,nTransType,0)
	Sys_SaveActionFestivalLog(tHalloween2015_Transform_Log["StartTask"])
	tNpcGossip[17053]["Text222"] = string.format(tHalloween2015_Transform_Text[17053]["Text222"],tHalloween2015_Transform_Text["Form"][nFormNum])
	LinkNpcGossipFunc_New(nNpcId,"2-2")
end

--领取奖励
function Halloween2015_Transform_ApplyReward(nNpcId)
	--检查任务条件,非任务时间则退出
	if not Sys_ChkFullTime(tHalloween2015_Transform_Data["During"]) then
		LinkNpcGossipFunc_New(nNpcId,"1-3")
		return
	end
	local nTransEvent = tHalloween2015_Transform_Stc["Trans"]["EventType"]
	local nTransType = tHalloween2015_Transform_Stc["Trans"]["DataType"]
	local nSaveForm = math.ceil (Get_UserStatisticValue(nTransEvent,nTransType)/10)
	--已领过奖
	if Task_ChkStcValue(nTransEvent,nTransType,">=",tHalloween2015_Transform_Phase["GetReward"]) and not Task_StcInterval(nTransEvent,nTransType,1,4) then
		LinkNpcGossipFunc_New(nNpcId,"3-1")
		return
	end
	--未变身或变身不正确
	--修改对白
	tNpcGossip[17053]["Text322"] = string.format(tHalloween2015_Transform_Text[17053]["Text322"],tHalloween2015_Transform_Text["Form"][nSaveForm])
	if Task_ChkStcValue(nTransEvent,nTransType,"<",tHalloween2015_Transform_Phase["TransMin"]) then
		LinkNpcGossipFunc_New(nNpcId,"3-2")
		return
	end
	local nTransNum = Get_UserStatisticValue(nTransEvent,nTransType)
	if Get_UserTransformId() ~= tHalloween2015_Transform_FormId[nSaveForm] then
		Task_SetStatistic(nTransEvent,nTransType,(nTransNum/10),1)
		LinkNpcGossipFunc_New(nNpcId,"3-2")
		return
	end
	--背包满
	if not User_CheckLeftSpace(1) then
		User_TalkChannel2005(tHalloween2015_Transform_Text[17053]["FullBag"])
		return
	end
	--终于能拿礼包了
	Task_SetStatistic(nTransEvent,nTransType,tHalloween2015_Transform_Phase["GetReward"],1)
	Task_SetStcTimestamp(nTransEvent,nTransType,0)
	local nCultEvent = tHalloween2015_Transform_Stc["Cult"]["EventType"]
	local nCultType = tHalloween2015_Transform_Stc["Cult"]["DataType"]
	Task_SetStatistic(nCultEvent,nCultType,0,1)
	Task_SetStcTimestamp(nCultEvent,nCultType,0)
	User_EffectAdd("self",tHalloween2015_Transform_Effect["GetReward"])
	User_TalkChannel2005(tHalloween2015_Transform_Text[17053]["Talk1"])
	FestivalGeneralPackage_GetGift(tHalloween2015_Transform_Log["FestivalId"],tHalloween2015_Transform_Log["LogId"])
	Sys_SaveActionFestivalLog(tHalloween2015_Transform_Log["FestivalPack"])
	LinkNpcGossipFunc_New(nNpcId,"3-3")
end

--触碰魔法石
function Halloween2015_Transform_TouchStone(nNpcId)
	--时间检查/完成阶段检查
	if not Sys_ChkFullTime(tHalloween2015_Transform_Data["During"]) then
		LinkNpcGossipFunc_New(nNpcId,"1-3")
		return
	end
	--检查掩码
	local nInvEvent = tHalloween2015_Transform_Stc["Interval"]["EventType"]
	local nInvType = tHalloween2015_Transform_Stc["Interval"]["DataType"]
	local nCultEvent = tHalloween2015_Transform_Stc["Cult"]["EventType"]
	local nCultType = tHalloween2015_Transform_Stc["Cult"]["DataType"]
	--修行值相关--隔天重置
	if Task_ChkStcValue(nCultEvent,nCultType,">",0) and Task_StcInterval(nCultEvent,nCultType,1,4) then
		Task_SetStatistic(nCultEvent,nCultType,0,1)
		Task_SetStcTimestamp(nCultEvent,nCultType,0)
	end
	--变身间隔检查
	if Task_ChkStcValue(nInvEvent,nInvType,">",0) and not Task_StcInterval(nInvEvent,nInvType,tHalloween2015_Transform_Stc["Interval"]["Limit"],0) then
		User_TalkChannel2005(tHalloween2015_Transform_Text[17054]["Talk1"])
		return
	end
	--允许变身,改变掩码,重置时间戳
	Task_SetStatistic(nInvEvent,nInvType,1,1)
	Task_SetStcTimestamp(nInvEvent,nInvType,0)
	Halloween2015_Transform_PreTransform(nNpcId)
end
--变身准备
function Halloween2015_Transform_PreTransform(nNpcId)
	local nTimesEvent = tHalloween2015_Transform_Stc["Times"]["EventType"]
	local nTimesType = tHalloween2015_Transform_Stc["Times"]["DataType"]
	local nTimesLimit = tHalloween2015_Transform_Stc["Times"]["Limit"]
	local nTransExtra = math.random(tHalloween2015_Transform_Rate["Total"])
	local nUserId = Get_UserId()
	if Task_ChkStcValue(nTimesEvent,nTimesType,"<",nTimesLimit) then
		--失败,眩晕,跳出
		if nTransExtra <= tHalloween2015_Transform_Rate["Stun"] then
			local nSStatus = tHalloween2015_Transform_Status["Stun"]["Status"]
			local nSPower = tHalloween2015_Transform_Status["Stun"]["Power"]
			local nSSec = tHalloween2015_Transform_Status["Stun"]["Sec"]
			local nSTimes = tHalloween2015_Transform_Status["Stun"]["Times"]
			local nSRemainTime = tHalloween2015_Transform_Status["Stun"]["RemainTime"]
			local nSEndTime = tHalloween2015_Transform_Status["Stun"]["EndTime"]
			local nSRecordable = tHalloween2015_Transform_Status["Stun"]["Recordable"]
			User_AddRoleStatus(nSStatus,nSPower,nSSec,nSTimes,nSRemainTime,nSEndTime,nSRecordable,0,0,nUserId)
			local nFailTimes = Get_UserStatisticValue(nTimesEvent,nTimesType)
			nFailTimes = nFailTimes + 1
			Task_SetStatistic(nTimesEvent,nTimesType,nFailTimes,1,0)
			User_TalkChannel2005(tHalloween2015_Transform_Text[17054]["Talk2"])
			return
		--逆向
		elseif nTransExtra <= tHalloween2015_Transform_Rate["Mirror"] then
			local nMStatus = tHalloween2015_Transform_Status["Mirror"]["Status"]
			local nMPower = tHalloween2015_Transform_Status["Mirror"]["Power"]
			local nMSec = tHalloween2015_Transform_Status["Mirror"]["Sec"]
			local nMTimes = tHalloween2015_Transform_Status["Mirror"]["Times"]
			local nMRemainTime = tHalloween2015_Transform_Status["Mirror"]["RemainTime"]
			local nMEndTime = tHalloween2015_Transform_Status["Mirror"]["EndTime"]
			local nMRecordable = tHalloween2015_Transform_Status["Mirror"]["Recordable"]
			User_AddRoleStatus(nMStatus,nMPower,nMSec,nMTimes,nMRemainTime,nMEndTime,nMRecordable,0,0,nUserId)
			User_TalkChannel2005(tHalloween2015_Transform_Text[17054]["Talk3"])
		--修行值
		elseif nTransExtra <= tHalloween2015_Transform_Rate["Cult"] then
			local nCultEvent = tHalloween2015_Transform_Stc["Cult"]["EventType"]
			local nCultType = tHalloween2015_Transform_Stc["Cult"]["DataType"]
			local nCultTime = Get_UserStatisticValue(nCultEvent,nCultType)
			--每天只给2次
			if nCultTime < 2 then
				nCultTime = nCultTime + 1
				User_TalkChannel2005(tHalloween2015_Transform_Text[17054]["Talk4"])
				Task_SetStatistic(nCultEvent,nCultType,nCultTime,1)
				Task_SetStcTimestamp(nCultEvent,nCultType,0)
				User_AddCultivation(tHalloween2015_Transform_Data["Cult"])
				Sys_SaveActionFestivalLog(tHalloween2015_Transform_Log["Cult"])
			end
		--糖果
		elseif nTransExtra <= tHalloween2015_Transform_Rate["Candy"] then
			--检测背包
			if not User_CheckLeftSpace(1) then
				User_TalkChannel2005(tHalloween2015_Transform_Text[17054]["Talk6"])
				return
			end
			Item_AddItem(tHalloween2015_Transform_Id["Candy"])
			Sys_SaveActionFestivalLog(tHalloween2015_Transform_Log["Candy"])
			User_TalkChannel2005(tHalloween2015_Transform_Text[17054]["Talk5"])
		end
	end
	--随机变鬼怪15秒
	Halloween2015_Transform_Trans("Stone")
end
--变身逻辑
function Halloween2015_Transform_Trans(sMethod)
	local nTransEvent = tHalloween2015_Transform_Stc["Trans"]["EventType"]
	local nTransType = tHalloween2015_Transform_Stc["Trans"]["DataType"]
	local nTimesEvent = tHalloween2015_Transform_Stc["Times"]["EventType"]
	local nTimesType = tHalloween2015_Transform_Stc["Times"]["DataType"]
	local nTimesLimit = tHalloween2015_Transform_Stc["Times"]["Limit"]
	local nFormNum = math.random(#tHalloween2015_Transform_Text["Form"])
	--检测是否是使用魔法石变身.且正在进行任务=>脸黑补丁
	if sMethod == "Stone" and Task_ChkStcValue(nTransEvent,nTransType,"<=",tHalloween2015_Transform_Phase["TransMax"]) then
		--变身错误次数不足,且变身再次不正确,次数stc++
		if Task_ChkStcValue(nTimesEvent,nTimesType,"<",nTimesLimit) and not Task_ChkStcValue(nTransEvent,nTransType,"==",nFormNum) then
			local nFailTimes = Get_UserStatisticValue(nTimesEvent,nTimesType)
			nFailTimes = nFailTimes + 1
			Task_SetStatistic(nTimesEvent,nTimesType,nFailTimes,1,0)
		--变身错误次数足够
		else
			Task_SetStatistic(nTimesEvent,nTimesType,0,1,0)
			nFormNum = Get_UserStatisticValue(nTransEvent,nTransType)
		end
	end
	local sFrom = tHalloween2015_Transform_Text["Form"][nFormNum]
	local nTransTime = 0
	local nTransSkill = tHalloween2015_Transform_FormMagic["Skill"][sMethod][nFormNum]
	local nSkillLevel = tHalloween2015_Transform_FormMagic["MonsterLevel"]
	local nMonsterType = tHalloween2015_Transform_FormMagic["MonsterType"][nFormNum]
	local nTime = tHalloween2015_Transform_FormMagic["Time"][sMethod]
	User_TransForm(nTransSkill,nSkillLevel,nMonsterType,nTime)
	User_EffectAdd("self",tHalloween2015_Transform_Effect["TransForm"])
	--变身正确,完成任务
	if Task_ChkStcValue(nTransEvent,nTransType,"==",nFormNum) then
		local nTransNum = Get_UserStatisticValue(nTransEvent,nTransType)
		Task_SetStatistic(nTransEvent,nTransType,(nTransNum*10),1)
		Sys_SaveActionFestivalLog(tHalloween2015_Transform_Log["TransCorrect"])
	end
	User_TalkChannel2005(string.format(tHalloween2015_Transform_Text[17054][sMethod],sFrom))
end


--检测变身情况
function Halloween2015_Transform_ChkForm(nNpcId)
	local nTransEvent = tHalloween2015_Transform_Stc["Trans"]["EventType"]
	local nTransType = tHalloween2015_Transform_Stc["Trans"]["DataType"]
	local nTransNum = Get_UserStatisticValue(nTransEvent,nTransType)
	if Get_UserTransformId() == tHalloween2015_Transform_FormId[nTransNum] then
		Sys_MsgBox(tHalloween2015_Transform_Text[17054]["Msg1"])
	end
end

--变身糖果使用函数
function Halloween2015_Transform_Candy(nItemId)
	if Item_ChkItem(nItemId) then
		if Item_DelItem(nItemId) then
		end
	end
	--超期的情况
	if not Sys_ChkFullTime(tHalloween2015_Transform_Data["During"]) then
		Sys_SaveActionFestivalLog(tHalloween2015_Transform_Log["DropCandy"])
		User_TalkChannel2005(tHalloween2015_Transform_Text[3003675]["Talk1"])
		return
	end
	--活动期间,变身1小时,并且获得1个解药3003676(删除1个获得1个,不检测背包)
	Item_AddItem(tHalloween2015_Transform_Id["Antidote"])
	Sys_SaveActionFestivalLog(tHalloween2015_Transform_Log["Antidote"])
	Halloween2015_Transform_Trans("Candy")
end

--变身解药使用逻辑
function Halloween2015_Transform_Antidote(nItemId)
	if Item_ChkItem(nItemId) then
		if Item_DelItem(nItemId) then
		end
	end
	--时间不正确-提示,跳出
	if not Sys_ChkFullTime(tHalloween2015_Transform_Data["During"]) then
		Sys_SaveActionFestivalLog(tHalloween2015_Transform_Log["DropCandy"])
		User_TalkChannel2005(tHalloween2015_Transform_Text[3003675]["Talk1"])
		return
	end
	--玩家有变身的情况
	if Get_UserTransformId() >= 0 then
		User_SetTransform(0)
		User_TalkChannel2005(tHalloween2015_Transform_Text[3003676]["Talk1"])
	--未变身的情况
	else
		User_TalkChannel2005(tHalloween2015_Transform_Text[3003676]["Talk2"])
	end
end

---------------------------Item模板------------------------
--变身糖果
tItem[3003675] = tItem[3003675] or {}
tItem[3003675]["Function"] = function(nItemId,sItemName)
	Halloween2015_Transform_Candy(nItemId)
end

--变身解药3003676
tItem[3003676] = tItem[3003676] or {}
tItem[3003676]["Function"] = function(nItemId,sItemName)
	Halloween2015_Transform_Antidote(nItemId)
end

---------------------------Npc模板------------------------
--17053变身巫师蒙迪尔
tNpcFace[3162] = 200
tNpcGossip[17053] = tNpcGossip[17053] or DefaultNpc:new{}
tNpcGossip[17053]["OptionHidden"] = 1
--活动前
tNpcGossip[17053]["Text1-1"] = {111,112,113}
tNpcGossip[17053]["Text111"] = tHalloween2015_Transform_Text[17053]["Text111"]
tNpcGossip[17053]["Text112"] = tHalloween2015_Transform_Text[17053]["Text112"]
tNpcGossip[17053]["Text113"] = tHalloween2015_Transform_Text[17053]["Text113"]
tNpcGossip[17053]["tOption1-1"] = {1}
tNpcGossip[17053]["Option1"] = tHalloween2015_Transform_Text[17053]["Option1"]
tNpcGossip[17053]["ChkFunc1-1"] = function()
	return Sys_ChkFullTime(tHalloween2015_Transform_Data["Before"])
end
--活动中
tNpcGossip[17053]["Text1-2"] = {121,122,123}
tNpcGossip[17053]["Text121"] = tHalloween2015_Transform_Text[17053]["Text121"]
tNpcGossip[17053]["Text122"] = tHalloween2015_Transform_Text[17053]["Text122"]
tNpcGossip[17053]["Text123"] = tHalloween2015_Transform_Text[17053]["Text123"]
tNpcGossip[17053]["tOption1-2"] = {2,3,4,5}
tNpcGossip[17053]["Option2"] = tHalloween2015_Transform_Text[17053]["Option2"]
	tNpcGossip[17053]["OptionFunc2"] = "Halloween2015_Transform_JoinAct</N>17053"
	tNpcGossip[17053]["OptionChkFunc2"] = function()
		return Halloween2015_Transform_ChoiceChk(17053)
	end
tNpcGossip[17053]["Option3"] = tHalloween2015_Transform_Text[17053]["Option3"]
	tNpcGossip[17053]["OptionFunc3"] = "Halloween2015_Transform_ApplyReward</N>17053"
	tNpcGossip[17053]["OptionChkFunc3"] = function()
		return not Halloween2015_Transform_ChoiceChk(17053)
	end
tNpcGossip[17053]["Option4"] = tHalloween2015_Transform_Text[17053]["Option4"]
	tNpcGossip[17053]["OptionPoint4"] = "4-1"
tNpcGossip[17053]["Option5"] = tHalloween2015_Transform_Text[17053]["Option5"]
tNpcGossip[17053]["ChkFunc1-2"] = function()
	Halloween2015_Transform_CrossDay()
	return Sys_ChkFullTime(tHalloween2015_Transform_Data["During"])
end
--活动后
tNpcGossip[17053]["Text1-3"] = {131,132}
tNpcGossip[17053]["Text131"] = tHalloween2015_Transform_Text[17053]["Text131"]
tNpcGossip[17053]["Text132"] = tHalloween2015_Transform_Text[17053]["Text132"]
tNpcGossip[17053]["tOption1-3"] = {6}
tNpcGossip[17053]["Option6"] = tHalloween2015_Transform_Text[17053]["Option6"]

--选择2-1,条件不满足
tNpcGossip[17053]["Text2-1"] = {211}
tNpcGossip[17053]["Text211"] = tHalloween2015_Transform_Text[17053]["Text211"]
tNpcGossip[17053]["tOption2-1"] = {7}
tNpcGossip[17053]["Option7"] = tHalloween2015_Transform_Text[17053]["Option7"]
--选择2-1,条件满足
tNpcGossip[17053]["Text2-2"] = {221,222,223}
tNpcGossip[17053]["Text221"] = tHalloween2015_Transform_Text[17053]["Text221"]
tNpcGossip[17053]["Text222"] = tHalloween2015_Transform_Text[17053]["Text222"]
tNpcGossip[17053]["Text223"] = tHalloween2015_Transform_Text[17053]["Text223"]
tNpcGossip[17053]["tOption2-2"] = {8}
tNpcGossip[17053]["Option8"] = tHalloween2015_Transform_Text[17053]["Option8"]
--选择2-1,任务已接到,掩码存在
tNpcGossip[17053]["Text2-3"] = {231}
tNpcGossip[17053]["Text231"] = tHalloween2015_Transform_Text[17053]["Text231"]
tNpcGossip[17053]["tOption2-3"] = {9}
tNpcGossip[17053]["Option9"] = tHalloween2015_Transform_Text[17053]["Option9"]
	tNpcGossip[17053]["OptionFunc9"] = "Halloween2015_Transform_AutoFindWay"


--选择2-2,奖励已领过
tNpcGossip[17053]["Text3-1"] = {311}
tNpcGossip[17053]["Text311"] = tHalloween2015_Transform_Text[17053]["Text311"]
tNpcGossip[17053]["tOption3-1"] = {10}
tNpcGossip[17053]["Option10"] = tHalloween2015_Transform_Text[17053]["Option10"]
--选择2-2,未完成,不在变形状态
tNpcGossip[17053]["Text3-2"] = {321,322}
tNpcGossip[17053]["Text321"] = tHalloween2015_Transform_Text[17053]["Text321"]
tNpcGossip[17053]["Text322"] = tHalloween2015_Transform_Text[17053]["Text322"]
tNpcGossip[17053]["tOption3-2"] = {11}
tNpcGossip[17053]["Option11"] = tHalloween2015_Transform_Text[17053]["Option11"]
	tNpcGossip[17053]["OptionFunc11"] = "Halloween2015_Transform_AutoFindWay"
	
--选择2-2,领取奖励
tNpcGossip[17053]["Text3-3"] = {331,332}
tNpcGossip[17053]["Text331"] = tHalloween2015_Transform_Text[17053]["Text331"]
tNpcGossip[17053]["Text332"] = tHalloween2015_Transform_Text[17053]["Text332"]
tNpcGossip[17053]["tOption3-3"] = {12}
tNpcGossip[17053]["Option12"] = tHalloween2015_Transform_Text[17053]["Option12"]

--选择2-3,活动说明
tNpcGossip[17053]["Text4-1"] = {411,412,413}
tNpcGossip[17053]["Text411"] = tHalloween2015_Transform_Text[17053]["Text411"]
tNpcGossip[17053]["Text412"] = tHalloween2015_Transform_Text[17053]["Text412"]
tNpcGossip[17053]["Text413"] = tHalloween2015_Transform_Text[17053]["Text413"]
tNpcGossip[17053]["tOption4-1"] = {13}
tNpcGossip[17053]["Option13"] = tHalloween2015_Transform_Text[17053]["Option13"]

--17054变身魔法石
tNpcGossip[17054] = tNpcGossip[17054] or DefaultNpc:new{}
tNpcGossip[17054]["OptionHidden"] = 1
--活动前
tNpcGossip[17054]["Text1-1"] = {111}
tNpcGossip[17054]["Text111"] = tHalloween2015_Transform_Text[17054]["Text111"]
tNpcGossip[17054]["tOption1-1"] = {1}
tNpcGossip[17054]["Option1"] = tHalloween2015_Transform_Text[17054]["Option1"]
tNpcGossip[17054]["ChkFunc1-1"] = function()
	return Sys_ChkFullTime(tHalloween2015_Transform_Data["Before"])
end
--活动中
tNpcGossip[17054]["Text1-2"] = {121}
tNpcGossip[17054]["Text121"] = tHalloween2015_Transform_Text[17054]["Text121"]
tNpcGossip[17054]["tOption1-2"] = {2,3,4}
tNpcGossip[17054]["Option2"] = tHalloween2015_Transform_Text[17054]["Option2"]
	tNpcGossip[17054]["OptionPoint2"] = "2-1"
	tNpcGossip[17054]["OptionChkFunc2"] = function()
		return Halloween2015_Transform_ChoiceChk(17054)
	end
tNpcGossip[17054]["Option3"] = tHalloween2015_Transform_Text[17054]["Option3"]
	tNpcGossip[17054]["OptionFunc3"] = "Halloween2015_Transform_TouchStone</N>17054"
	tNpcGossip[17054]["OptionChkFunc3"] = function()
		return not Halloween2015_Transform_ChoiceChk(17054)
	end
tNpcGossip[17054]["Option4"] = tHalloween2015_Transform_Text[17054]["Option4"]
tNpcGossip[17054]["ChkFunc1-2"] = function()
	Halloween2015_Transform_ChkForm(17054)
	return Sys_ChkFullTime(tHalloween2015_Transform_Data["During"])
end
--活动后
tNpcGossip[17054]["Text1-3"] = {131}
tNpcGossip[17054]["Text131"] = tHalloween2015_Transform_Text[17054]["Text131"]
tNpcGossip[17054]["tOption1-3"] = {5}
tNpcGossip[17054]["Option5"] = tHalloween2015_Transform_Text[17054]["Option1"]

--2-1这是什么
tNpcGossip[17054]["Text2-1"] = {211}
tNpcGossip[17054]["Text211"] = tHalloween2015_Transform_Text[17054]["Text211"]
tNpcGossip[17054]["tOption2-1"] = {6}
tNpcGossip[17054]["Option6"] = tHalloween2015_Transform_Text[17054]["Option6"]

