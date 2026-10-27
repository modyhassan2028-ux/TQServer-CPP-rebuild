------------------------------------------------------------------------------------
--Name:			150729[简体征服][活动脚本]万圣节不给糖就捣乱
--Purpose:		万圣节不给糖就捣乱
--Creator:		张磊
--Created:		2015/07/29
------------------------------------------------------------------------------------


-- ##########################################修改##################################

-- #掩码替换：
-- #stc(137,2)		>=100 表示已经完成任务
-- #
-- #			包含1 表示已经破坏了衣柜
-- #			包含2 表示已经破坏了案几
-- #			包含4 表示已经破坏了书架
-- #			包含8 表示已经破坏了镜子
-- #			包含16表示已经破坏了浴盆
-- #			
-- #			==31 表示全部家具都已经破坏了

-- #LOGID替换
-- #10002332	替换为	12000162

-- #################################################################################




---------常量表配置
local tHalloween2015_RockTheBoat_Cont = {}
	-- 活动时间
	tHalloween2015_RockTheBoat_Cont["BeforeActivityTime"] = "2015-01-01 00:00 2015-10-28 23:59"
	tHalloween2015_RockTheBoat_Cont["ActivityTime"] = "2015-10-29 00:00 2015-11-04 23:59"

	-- 玩家等级要求
	tHalloween2015_RockTheBoat_Cont["Metempsychosis"] = 0
	tHalloween2015_RockTheBoat_Cont["Level"] = 80
	
	-- 读条配置
	---- 读条时间
	tHalloween2015_RockTheBoat_Cont["Time"] = 3
	---- 读条动作
	tHalloween2015_RockTheBoat_Cont["Action"] = 200
	
	-- 接受任务
	tHalloween2015_RockTheBoat_Cont["Accpect"] = 1
	
	--完成掩码
	tHalloween2015_RockTheBoat_Cont["Complete"] = 2
	
	--背包空间
	tHalloween2015_RockTheBoat_Cont["Space"] = 1
	
	--节日礼包ＩＤ
	tHalloween2015_RockTheBoat_Cont["FestivalId"] = 3456
	
	-- 破坏的掩码值
	tHalloween2015_RockTheBoat_Cont[17151] = 1
	tHalloween2015_RockTheBoat_Cont[17152] = 2
	tHalloween2015_RockTheBoat_Cont[17153] = 4
	tHalloween2015_RockTheBoat_Cont[17154] = 8
	tHalloween2015_RockTheBoat_Cont[17155] = 16
	
	
	tHalloween2015_RockTheBoat_Cont["DamageAll"] = 31
	
local tHalloween2015_RockTheBoat_Stc = {}
	
	tHalloween2015_RockTheBoat_Stc["Event_type"] = 137
	-- 任务掩码	
	tHalloween2015_RockTheBoat_Stc["Data_type_Task"] = 2
	-- 破坏掩码
	tHalloween2015_RockTheBoat_Stc["Data_type_Damage"] = 19
	
local tHalloween2015_RockTheBoat_Position = {}

	tHalloween2015_RockTheBoat_Position["Size"] = 5
	tHalloween2015_RockTheBoat_Position["Flag"] = 1
	-- 离开土豪磊的家，坐标	
	tHalloween2015_RockTheBoat_Position["Map_1002"] = 1002
	tHalloween2015_RockTheBoat_Position["PosX_1002"] = 299
	tHalloween2015_RockTheBoat_Position["PosY_1002"] = 383
	
	-- 进入土豪磊的家，坐标	
	tHalloween2015_RockTheBoat_Position["Map_3871"] = 3871
	tHalloween2015_RockTheBoat_Position["PosX_3871"] = 74
	tHalloween2015_RockTheBoat_Position["PosY_3871"] = 55
	
local tHalloween2015_RockTheBoat_Npc = {}
	tHalloween2015_RockTheBoat_Npc["MapId"] = 3871
	tHalloween2015_RockTheBoat_Npc["NpcId"] = 17149
	tHalloween2015_RockTheBoat_Npc["NpcX"] = 074
	tHalloween2015_RockTheBoat_Npc["NpcY"] = 060

local tHalloween2015_RockTheBoat_Log = {}

	tHalloween2015_RockTheBoat_Log["RewardItem"] = 12000162
	
local tHalloween2015_RockTheBoat_Effect = {}
	tHalloween2015_RockTheBoat_Effect["Self"] = "self"
	tHalloween2015_RockTheBoat_Effect["Effect"] = "angelwing6"
	
	tHalloween2015_RockTheBoat_Effect["EffectReward"] = "angelwing"
		
------------------------------------------逻辑部分---------------------------------------
--判断任务完成掩码情况
function Halloween2015_RockTheBoat_StcComplete()
	
	local nEvent = tHalloween2015_RockTheBoat_Stc["Event_type"]
	local nType = tHalloween2015_RockTheBoat_Stc["Data_type_Task"]
	local nData = tHalloween2015_RockTheBoat_Cont["Complete"]
	
	if Task_StcInterval(nEvent,nType,1,4) then
		Task_SetStatistic(nEvent,nType,0,1)
		Task_SetStcTimestamp(nEvent,nType,0)
		return false
	elseif Task_ChkStcValue(nEvent,nType,">=",nData) then
		return true
	else
		return false
	end	
end

--判断破坏掩码的情况
function Halloween2015_RockTheBoat_StcDamage()
	local nEvent = tHalloween2015_RockTheBoat_Stc["Event_type"]
	local nType = tHalloween2015_RockTheBoat_Stc["Data_type_Damage"]
	local nData = tHalloween2015_RockTheBoat_Cont["DamageAll"]
	
	if Task_StcInterval(nEvent,nType,1,4) then
		Task_SetStatistic(nEvent,nType,0,1)
		Task_SetStcTimestamp(nEvent,nType,0)
		return true
	elseif Task_ChkStcValue(nEvent,nType,"<",nData) then
		return true
	else
		return false
	end
end

--偷偷逃离土豪家。
function Halloween2015_RockTheBoat_Leave()
	local nMapId = tHalloween2015_RockTheBoat_Position["Map_1002"]
	local nBoundX = tHalloween2015_RockTheBoat_Position["PosX_1002"]
	local nBoundY = tHalloween2015_RockTheBoat_Position["PosY_1002"]
	local nBoundCX = tHalloween2015_RockTheBoat_Position["Size"]
	local nBoundCY = tHalloween2015_RockTheBoat_Position["Size"]
	local nCheck = tHalloween2015_RockTheBoat_Position["Flag"]
	
	if not User_UserRandBoundTrans(nMapId,nBoundX,nBoundY,nBoundCX,nBoundCY,nCheck) then
		return
	end
	
	local nEvent = tHalloween2015_RockTheBoat_Stc["Event_type"]
	local nType = tHalloween2015_RockTheBoat_Stc["Data_type_Task"]
		
	--检查掩码情况(完成情况)
	if Halloween2015_RockTheBoat_StcComplete() then
		User_TalkChannel2005(tHalloween2015_RockTheBoat_Text["GetGift"])
		return	
	end
	
	if Task_ChkStcValue(nEvent,nType,"==",0) then
		User_TalkChannel2005(tHalloween2015_RockTheBoat_Text["NoTask"])
		return
	end
	
	--检查掩码情况(破坏情况)
	if Halloween2015_RockTheBoat_StcDamage() then
		User_TalkChannel2005(tHalloween2015_RockTheBoat_Text["NotDamageAll"])
	else
		User_TalkChannel2005(tHalloween2015_RockTheBoat_Text["DamageAll"])
	end
end

--我要去土豪磊家捣乱
function Halloween2015_RockTheBoat_GoIn(nNpcId)
	-- 判断活动时间
	if not Sys_ChkFullTime(tHalloween2015_RockTheBoat_Cont["ActivityTime"]) then
		LinkNpcGossipFunc_New(nNpcId,"1-3")
		return
	end
	
	-- 判断等级
	if not User_JudgeLevelAndMetempsychosis(tHalloween2015_RockTheBoat_Cont["Level"],tHalloween2015_RockTheBoat_Cont["Metempsychosis"]) then
		LinkNpcGossipFunc_New(nNpcId,"2-1")
		return
	end
	
	-- 判断今天是否完成了
	---- 已经完成
	if Halloween2015_RockTheBoat_StcComplete() then
		LinkNpcGossipFunc_New(nNpcId,"3-1")
		return
	end
	
	---- 未完成，判断有没有接任务
	local nEvent = tHalloween2015_RockTheBoat_Stc["Event_type"]
	local nType = tHalloween2015_RockTheBoat_Stc["Data_type_Task"]
	
	local nMapId = tHalloween2015_RockTheBoat_Position["Map_3871"]
	local nBoundX = tHalloween2015_RockTheBoat_Position["PosX_3871"]
	local nBoundY = tHalloween2015_RockTheBoat_Position["PosY_3871"]
	local nBoundCX = tHalloween2015_RockTheBoat_Position["Size"]
	local nBoundCY = tHalloween2015_RockTheBoat_Position["Size"]
	local nCheck = tHalloween2015_RockTheBoat_Position["Flag"]
	
	
	if Task_ChkStcValue(nEvent,nType,"==",0) then
		Task_SetStatistic(nEvent,nType,tHalloween2015_RockTheBoat_Cont["Accpect"],1)
		Task_SetStcTimestamp(nEvent,nType,0)
	elseif not Halloween2015_RockTheBoat_StcDamage() then
		LinkNpcGossipFunc_New(nNpcId,"4-1")
		return
	end
	
	User_UserRandBoundTrans(nMapId,nBoundX,nBoundY,nBoundCX,nBoundCY,nCheck)
	LinkNpcGossipFunc_New(nNpcId,"5-1")
end

-- 完成任务
function Halloween2015_RockTheBoat_Complete(nNpcId)
		-- 判断活动时间
	if not Sys_ChkFullTime(tHalloween2015_RockTheBoat_Cont["ActivityTime"]) then
		LinkNpcGossipFunc_New(nNpcId,"1-3")
		return
	end
	
	-- 判断等级
	if not User_JudgeLevelAndMetempsychosis(tHalloween2015_RockTheBoat_Cont["Level"],tHalloween2015_RockTheBoat_Cont["Metempsychosis"]) then
		LinkNpcGossipFunc_New(nNpcId,"2-1")
		return
	end
	
	-- 是否已经领取过了
	---- 已经完成
	if Halloween2015_RockTheBoat_StcComplete() then
		LinkNpcGossipFunc_New(nNpcId,"7-1")
		return
	end
	
	---- 未完成，判断有没有任务
	local nEvent = tHalloween2015_RockTheBoat_Stc["Event_type"]
	local nType = tHalloween2015_RockTheBoat_Stc["Data_type_Task"]
	
	if Task_ChkStcValue(nEvent,nType,"==",0) then
		LinkNpcGossipFunc_New(nNpcId,"9-1")
		return
	end
	
	--有任务，判断是否已经破坏完成了
	---- 还未破坏完
	if Halloween2015_RockTheBoat_StcDamage() then
		LinkNpcGossipFunc_New(nNpcId,"8-1")
		return
	end
	
	---- 已经破坏完，判断有没有背包空间
	local nSpace = tHalloween2015_RockTheBoat_Cont["Space"]
	if not User_CheckLeftSpace(nSpace) then
		User_TalkChannel2005(tHalloween2015_RockTheBoat_Text["NoSpace"])
		return
	end
	
	---- 破坏完且有背包空间
	---- 打掩码 和 给奖励
	local nCompleteFlag = tHalloween2015_RockTheBoat_Cont["Complete"]
	Task_SetStatistic(nEvent,nType,nCompleteFlag,1)
	Task_SetStcTimestamp(nEvent,nType,0)
	
	FestivalGeneralPackage_GetGift(tHalloween2015_RockTheBoat_Cont["FestivalId"],tHalloween2015_RockTheBoat_Log["RewardItem"])
	LinkNpcGossipFunc_New(nNpcId,"10-1")
	User_EffectAdd(tHalloween2015_RockTheBoat_Effect["Self"],tHalloween2015_RockTheBoat_Effect["EffectReward"])
end

-- 点击破坏选项
function Halloween2015_RockTheBoat_DamgeItem(nNpcId)
	-- 判断活动时间
	if not Sys_ChkFullTime(tHalloween2015_RockTheBoat_Cont["ActivityTime"]) then
		LinkNpcGossipFunc_New(nNpcId,"2-1")
		return
	end
	
	-- 判断等级
	if not User_JudgeLevelAndMetempsychosis(tHalloween2015_RockTheBoat_Cont["Level"],tHalloween2015_RockTheBoat_Cont["Metempsychosis"]) then
		LinkNpcGossipFunc_New(nNpcId,"3-1")
		return
	end

	-- 是判断当天否完成任务了
	if Halloween2015_RockTheBoat_StcComplete() then
		User_TalkChannel2005(tHalloween2015_RockTheBoat_Text["SysMsg"][nNpcId][2])
		return
	end
	
	local nEvent = tHalloween2015_RockTheBoat_Stc["Event_type"]
	local nType = tHalloween2015_RockTheBoat_Stc["Data_type_Task"]
	
	if Task_ChkStcValue(nEvent,nType,"==",0) then
		LinkNpcGossipFunc_New(nNpcId,"4-1")
		return
	end
	
	-- 已接取任务，判断破坏状态
	if not Halloween2015_RockTheBoat_StcDamage() then
		User_TalkChannel2005(tHalloween2015_RockTheBoat_Text["SysMsg_DamageAll"])
		return
	end
	
	-- 没有全部破坏完，判断掩码值是否为0   ==0 表示还未开始破坏
	local nEvent_damage = tHalloween2015_RockTheBoat_Stc["Event_type"]
	local nType_damage = tHalloween2015_RockTheBoat_Stc["Data_type_Damage"]
	 
	if Task_ChkStcValue(nEvent_damage,nType_damage,"==",0) or (not Sys_ParseNumbersContain(tHalloween2015_RockTheBoat_Cont[nNpcId],Get_UserStatisticValue(nEvent_damage,nType_damage))) then
		-- 读条
		local nSecs = tHalloween2015_RockTheBoat_Cont["Time"]
		local sContent = tHalloween2015_RockTheBoat_Str[nNpcId]
		local nActionId = tHalloween2015_RockTheBoat_Cont["Action"]
		User_SetExplore(nSecs,sContent,nActionId,"Halloween2015_RockTheBoat_AddDamageStc</N>" .. nNpcId)
	else
		User_TalkChannel2005(tHalloween2015_RockTheBoat_Text["SysMsg"][nNpcId][2])
	end	
	
end


-- 读条后操作破坏加掩码
function Halloween2015_RockTheBoat_AddDamageStc(nNpcId)
-- 判断活动时间
	if not Sys_ChkFullTime(tHalloween2015_RockTheBoat_Cont["ActivityTime"]) then
		LinkNpcGossipFunc_New(nNpcId,"2-1")
		return
	end
	
	-- 判断等级
	if not User_JudgeLevelAndMetempsychosis(tHalloween2015_RockTheBoat_Cont["Level"],tHalloween2015_RockTheBoat_Cont["Metempsychosis"]) then
		LinkNpcGossipFunc_New(nNpcId,"3-1")
		return
	end

	-- 是判断当天否完成任务了
	if Halloween2015_RockTheBoat_StcComplete() then
		User_TalkChannel2005(tHalloween2015_RockTheBoat_Text["SysMsg"][nNpcId][2])
		return
	end
	
	local nEvent = tHalloween2015_RockTheBoat_Stc["Event_type"]
	local nType = tHalloween2015_RockTheBoat_Stc["Data_type_Task"]
	
	if Task_ChkStcValue(nEvent,nType,"==",0) then
		LinkNpcGossipFunc_New(nNpcId,"4-1")
		return
	end
	
	-- 已接取任务，判断破坏状态
	if not Halloween2015_RockTheBoat_StcDamage() then
		User_TalkChannel2005(tHalloween2015_RockTheBoat_Text["SysMsg_DamageAll"])
		return
	end
	
	-- 没有全部破坏完，判断掩码值是否为0   ==0 表示还未开始破坏
	local nEvent_damage = tHalloween2015_RockTheBoat_Stc["Event_type"]
	local nType_damage = tHalloween2015_RockTheBoat_Stc["Data_type_Damage"]
	
	if Task_ChkStcValue(nEvent_damage,nType_damage,"==",0) or (not Sys_ParseNumbersContain(tHalloween2015_RockTheBoat_Cont[nNpcId],Get_UserStatisticValue(nEvent_damage,nType_damage))) then
		Task_AddStatistic(nEvent_damage,nType_damage,tHalloween2015_RockTheBoat_Cont[nNpcId],1)
		Task_SetStcTimestamp(nEvent_damage,nType_damage,0)
		User_TalkChannel2005(tHalloween2015_RockTheBoat_Text["SysMsg"][nNpcId][3])
		User_EffectAdd(tHalloween2015_RockTheBoat_Effect["Self"],tHalloween2015_RockTheBoat_Effect["Effect"])
	else
		User_TalkChannel2005(tHalloween2015_RockTheBoat_Text["SysMsg"][nNpcId][2])
	end	
	
	if Task_ChkStcValue(nEvent_damage,nType_damage,">=",tHalloween2015_RockTheBoat_Cont["DamageAll"]) then
		Sys_MsgBox(tHalloween2015_RockTheBoat_Text["SysMsg_DamageAll"],"Halloween2015_RockTheBoat_FindNpc")
	end
end

function Halloween2015_RockTheBoat_SysMsg(nNpcId)
	User_TalkChannel2005(tHalloween2015_RockTheBoat_Text["SysMsg"][nNpcId][1])
end

-- 破坏完后点击寻路到 土豪磊处
function Halloween2015_RockTheBoat_FindNpc()

	Sys_GotoSomeWhere(tHalloween2015_RockTheBoat_Npc["NpcX"],tHalloween2015_RockTheBoat_Npc["NpcY"],tHalloween2015_RockTheBoat_Npc["MapId"],tHalloween2015_RockTheBoat_Npc["NpcId"])
end


------------------------------NPC模版配置-------------------------------------------------
-- 土豪磊
tNpcFace[3204] = 42
tNpcGossip[17149] = tNpcGossip[17149] or DefaultNpc:new{}
tNpcGossip[17149]["OptionHidden"] = 1

tNpcGossip[17149]["Text1-1"] = {111,112,113}
tNpcGossip[17149]["Text111"] = tHalloween2015_RockTheBoat_Text[17149]["Text111"]
tNpcGossip[17149]["Text112"] = tHalloween2015_RockTheBoat_Text[17149]["Text112"]
tNpcGossip[17149]["Text113"] = tHalloween2015_RockTheBoat_Text[17149]["Text113"]
tNpcGossip[17149]["tOption1-1"] = {1,2}

tNpcGossip[17149]["Option1"] = tHalloween2015_RockTheBoat_Text[17149]["Option1"]
tNpcGossip[17149]["OptionFunc1"]="Halloween2015_RockTheBoat_Leave"

tNpcGossip[17149]["Option2"] = tHalloween2015_RockTheBoat_Text[17149]["Option2"]


--豆子熊
tNpcFace[3205] = 68
tNpcGossip[17150] = tNpcGossip[17150] or DefaultNpc:new{}
tNpcGossip[17150]["OptionHidden"] = 1

tNpcGossip[17150]["Text1-1"] = {111,112,113}
tNpcGossip[17150]["Text111"] = tHalloween2015_RockTheBoat_Text[17150]["Text111"]
tNpcGossip[17150]["Text112"] = tHalloween2015_RockTheBoat_Text[17150]["Text112"]
tNpcGossip[17150]["Text113"] = tHalloween2015_RockTheBoat_Text[17150]["Text113"]
tNpcGossip[17150]["tOption1-1"] = {1}
tNpcGossip[17150]["ChkFunc1-1"] = function()
	return Sys_ChkFullTime(tHalloween2015_RockTheBoat_Cont["BeforeActivityTime"])
end

tNpcGossip[17150]["Text1-2"] = {121,122,123}
tNpcGossip[17150]["Text121"] = tHalloween2015_RockTheBoat_Text[17150]["Text121"]
tNpcGossip[17150]["Text122"] = tHalloween2015_RockTheBoat_Text[17150]["Text122"]
tNpcGossip[17150]["Text123"] = tHalloween2015_RockTheBoat_Text[17150]["Text123"]
tNpcGossip[17150]["tOption1-2"] = {2,3,4,5}
tNpcGossip[17150]["ChkFunc1-2"] = function()
	return Sys_ChkFullTime(tHalloween2015_RockTheBoat_Cont["ActivityTime"])
end

tNpcGossip[17150]["Option1"] = tHalloween2015_RockTheBoat_Text[17150]["Option1"]


-- 我要去土豪家捣乱！
tNpcGossip[17150]["Option2"] = tHalloween2015_RockTheBoat_Text[17150]["Option2"]
tNpcGossip[17150]["OptionFunc2"]="Halloween2015_RockTheBoat_GoIn</N>17150"
tNpcGossip[17150]["OptionChkFunc2"] = function()
	return Sys_ChkFullTime(tHalloween2015_RockTheBoat_Cont["ActivityTime"]) and (not Halloween2015_RockTheBoat_StcComplete())
end

--领取捣乱礼物。
tNpcGossip[17150]["Option3"] = tHalloween2015_RockTheBoat_Text[17150]["Option3"]
tNpcGossip[17150]["OptionFunc3"]="Halloween2015_RockTheBoat_Complete</N>17150"
tNpcGossip[17150]["OptionChkFunc3"] = function()
	return Sys_ChkFullTime(tHalloween2015_RockTheBoat_Cont["ActivityTime"]) and (not Halloween2015_RockTheBoat_StcComplete())
end
--请教我怎么捣乱！
tNpcGossip[17150]["Option4"] = tHalloween2015_RockTheBoat_Text[17150]["Option4"]
tNpcGossip[17150]["OptionPoint4"]="6-1"

--怕在土豪家迷路，算了。
tNpcGossip[17150]["Option5"] = tHalloween2015_RockTheBoat_Text[17150]["Option5"]


tNpcGossip[17150]["Text1-3"] = {131}
tNpcGossip[17150]["Text131"] = tHalloween2015_RockTheBoat_Text[17150]["Text131"]
tNpcGossip[17150]["tOption1-3"] = {6}

tNpcGossip[17150]["Option6"] = tHalloween2015_RockTheBoat_Text[17150]["Option6"]


--接任务，等级不足
tNpcGossip[17150]["Text2-1"] = {211}
tNpcGossip[17150]["Text211"] = tHalloween2015_RockTheBoat_Text[17150]["Text211"]
tNpcGossip[17150]["tOption2-1"] = {7}

tNpcGossip[17150]["Option7"] = tHalloween2015_RockTheBoat_Text[17150]["Option7"]

--当天已经完成
tNpcGossip[17150]["Text3-1"] = {311}
tNpcGossip[17150]["Text311"] = tHalloween2015_RockTheBoat_Text[17150]["Text311"]
tNpcGossip[17150]["tOption3-1"] = {8}

tNpcGossip[17150]["Option8"] = tHalloween2015_RockTheBoat_Text[17150]["Option8"]

--完成了，但是还未领取奖励
tNpcGossip[17150]["Text4-1"] = {411}
tNpcGossip[17150]["Text411"] = tHalloween2015_RockTheBoat_Text[17150]["Text411"]
tNpcGossip[17150]["tOption4-1"] = {9}

tNpcGossip[17150]["Option9"] = tHalloween2015_RockTheBoat_Text[17150]["Option9"]
tNpcGossip[17150]["OptionPoint9"]="1"

--成功接取任务，传送进地图
tNpcGossip[17150]["Text5-1"] = {511,512,513}
tNpcGossip[17150]["Text511"] = tHalloween2015_RockTheBoat_Text[17150]["Text511"]
tNpcGossip[17150]["Text512"] = tHalloween2015_RockTheBoat_Text[17150]["Text512"]
tNpcGossip[17150]["Text513"] = tHalloween2015_RockTheBoat_Text[17150]["Text513"]
tNpcGossip[17150]["tOption5-1"] = {10}

tNpcGossip[17150]["Option10"] = tHalloween2015_RockTheBoat_Text[17150]["Option10"]

--请教我怎么捣乱！
tNpcGossip[17150]["Text6-1"] = {611,612,613,614}
tNpcGossip[17150]["Text611"] = tHalloween2015_RockTheBoat_Text[17150]["Text611"]
tNpcGossip[17150]["Text612"] = tHalloween2015_RockTheBoat_Text[17150]["Text612"]
tNpcGossip[17150]["Text613"] = tHalloween2015_RockTheBoat_Text[17150]["Text613"]
tNpcGossip[17150]["Text614"] = tHalloween2015_RockTheBoat_Text[17150]["Text614"]
tNpcGossip[17150]["tOption6-1"] = {11}

tNpcGossip[17150]["Option11"] = tHalloween2015_RockTheBoat_Text[17150]["Option11"]


--领奖部分提示
--已经领取过了奖励
tNpcGossip[17150]["Text7-1"] = {711}
tNpcGossip[17150]["Text711"] = tHalloween2015_RockTheBoat_Text[17150]["Text711"]
tNpcGossip[17150]["tOption7-1"] = {12}

tNpcGossip[17150]["Option12"] = tHalloween2015_RockTheBoat_Text[17150]["Option12"]

--有任务但是还未完成
tNpcGossip[17150]["Text8-1"] = {811,812}
tNpcGossip[17150]["Text811"] = tHalloween2015_RockTheBoat_Text[17150]["Text811"]
tNpcGossip[17150]["Text812"] = tHalloween2015_RockTheBoat_Text[17150]["Text812"]
tNpcGossip[17150]["tOption8-1"] = {13,14}

tNpcGossip[17150]["Option13"] = tHalloween2015_RockTheBoat_Text[17150]["Option13"]
tNpcGossip[17150]["OptionFunc13"]="Halloween2015_RockTheBoat_GoIn</N>17150"
tNpcGossip[17150]["OptionChkFunc13"] = function()
	return Sys_ChkFullTime(tHalloween2015_RockTheBoat_Cont["ActivityTime"]) and (not Halloween2015_RockTheBoat_StcComplete())
end

tNpcGossip[17150]["Option14"] = tHalloween2015_RockTheBoat_Text[17150]["Option14"]

--没接任务
tNpcGossip[17150]["Text9-1"] = {911,912}
tNpcGossip[17150]["Text911"] = tHalloween2015_RockTheBoat_Text[17150]["Text911"]
tNpcGossip[17150]["Text912"] = tHalloween2015_RockTheBoat_Text[17150]["Text912"]
tNpcGossip[17150]["tOption9-1"] = {15}

tNpcGossip[17150]["Option15"] = tHalloween2015_RockTheBoat_Text[17150]["Option15"]

--成功领取奖励，完成任务
tNpcGossip[17150]["Text10-1"] = {1011,1012}
tNpcGossip[17150]["Text1011"] = tHalloween2015_RockTheBoat_Text[17150]["Text1011"]
tNpcGossip[17150]["Text1012"] = tHalloween2015_RockTheBoat_Text[17150]["Text1012"]
tNpcGossip[17150]["tOption10-1"] = {16}

tNpcGossip[17150]["Option16"] = tHalloween2015_RockTheBoat_Text[17150]["Option16"]

--衣柜
tNpcGossip[17151] = tNpcGossip[17151] or DefaultNpc:new{}
tNpcGossip[17151]["OptionHidden"] = 1

tNpcGossip[17151]["Text1-1"] = {111,112}
tNpcGossip[17151]["Text111"] = tHalloween2015_RockTheBoat_Text[17151]["Text111"]
tNpcGossip[17151]["Text112"] = tHalloween2015_RockTheBoat_Text[17151]["Text112"]
tNpcGossip[17151]["tOption1-1"] = {1,2,3}


-- 通用函数，参数区分
tNpcGossip[17151]["Option1"] = tHalloween2015_RockTheBoat_Text[17151]["Option1"]
tNpcGossip[17151]["OptionFunc1"]="Halloween2015_RockTheBoat_DamgeItem</N>17151"
tNpcGossip[17151]["OptionChkFunc1"] = function()
	return Sys_ChkFullTime(tHalloween2015_RockTheBoat_Cont["ActivityTime"]) and (not Halloween2015_RockTheBoat_StcComplete())
end

tNpcGossip[17151]["Option2"] = tHalloween2015_RockTheBoat_Text[17151]["Option2"]
tNpcGossip[17151]["OptionFunc2"]="Halloween2015_RockTheBoat_SysMsg</N>17151"

tNpcGossip[17151]["Option3"] = tHalloween2015_RockTheBoat_Text[17151]["Option3"]


--犯强迫症了，帮他整理吧！
----非活动时间内
tNpcGossip[17151]["Text2-1"] = {211}
tNpcGossip[17151]["Text211"] = tHalloween2015_RockTheBoat_Text[17151]["Text211"]
tNpcGossip[17151]["tOption2-1"] = {4}

tNpcGossip[17151]["Option4"] = tHalloween2015_RockTheBoat_Text[17151]["Option4"]

----等级不够
tNpcGossip[17151]["Text3-1"] = {311}
tNpcGossip[17151]["Text311"] = tHalloween2015_RockTheBoat_Text[17151]["Text311"]
tNpcGossip[17151]["tOption3-1"] = {4}

--弄乱所有的衣服，哼！
--超过1天了，任务重置
tNpcGossip[17151]["Text4-1"] = {411}
tNpcGossip[17151]["Text411"] = tHalloween2015_RockTheBoat_Text[17151]["Text411"]
tNpcGossip[17151]["tOption4-1"] = {4}

--案几
tNpcGossip[17152] = tNpcGossip[17152] or DefaultNpc:new{}
tNpcGossip[17152]["OptionHidden"] = 1

tNpcGossip[17152]["Text1-1"] = {111,112}
tNpcGossip[17152]["Text111"] = tHalloween2015_RockTheBoat_Text[17152]["Text111"]
tNpcGossip[17152]["Text112"] = tHalloween2015_RockTheBoat_Text[17152]["Text112"]
tNpcGossip[17152]["tOption1-1"] = {1,2,3}

-- 通用函数，参数区分
tNpcGossip[17152]["Option1"] = tHalloween2015_RockTheBoat_Text[17152]["Option1"]
tNpcGossip[17152]["OptionFunc1"]="Halloween2015_RockTheBoat_DamgeItem</N>17152"
tNpcGossip[17152]["OptionChkFunc1"] = function()
	return Sys_ChkFullTime(tHalloween2015_RockTheBoat_Cont["ActivityTime"]) and (not Halloween2015_RockTheBoat_StcComplete())
end

tNpcGossip[17152]["Option2"] = tHalloween2015_RockTheBoat_Text[17152]["Option2"]
tNpcGossip[17152]["OptionFunc2"]="Halloween2015_RockTheBoat_SysMsg</N>17152"


tNpcGossip[17152]["Option3"] = tHalloween2015_RockTheBoat_Text[17152]["Option3"]

--这么乱，帮他归类放好吧！
----非活动时间内
tNpcGossip[17152]["Text2-1"] = {211}
tNpcGossip[17152]["Text211"] = tHalloween2015_RockTheBoat_Text[17152]["Text211"]
tNpcGossip[17152]["tOption2-1"] = {4}

tNpcGossip[17152]["Option4"] = tHalloween2015_RockTheBoat_Text[17152]["Option4"]

----等级不够
tNpcGossip[17152]["Text3-1"] = {311}
tNpcGossip[17152]["Text311"] = tHalloween2015_RockTheBoat_Text[17152]["Text311"]
tNpcGossip[17152]["tOption3-1"] = {4}

--吹乱所有书稿账本页，哼！
--超过1天了，任务重置
tNpcGossip[17152]["Text4-1"] = {411}
tNpcGossip[17152]["Text411"] = tHalloween2015_RockTheBoat_Text[17152]["Text411"]
tNpcGossip[17152]["tOption4-1"] = {4}

--书架
tNpcGossip[17153] = tNpcGossip[17153] or DefaultNpc:new{}
tNpcGossip[17153]["OptionHidden"] = 1

tNpcGossip[17153]["Text1-1"] = {111,112}
tNpcGossip[17153]["Text111"] = tHalloween2015_RockTheBoat_Text[17153]["Text111"]
tNpcGossip[17153]["Text112"] = tHalloween2015_RockTheBoat_Text[17153]["Text112"]
tNpcGossip[17153]["tOption1-1"] = {1,2,3}

-- 通用函数，参数区分
tNpcGossip[17153]["Option1"] = tHalloween2015_RockTheBoat_Text[17153]["Option1"]
tNpcGossip[17153]["OptionFunc1"]="Halloween2015_RockTheBoat_DamgeItem</N>17153"
tNpcGossip[17153]["OptionChkFunc1"] = function()
	return Sys_ChkFullTime(tHalloween2015_RockTheBoat_Cont["ActivityTime"]) and (not Halloween2015_RockTheBoat_StcComplete())
end

tNpcGossip[17153]["Option2"] = tHalloween2015_RockTheBoat_Text[17153]["Option2"]
tNpcGossip[17153]["OptionFunc2"]="Halloween2015_RockTheBoat_SysMsg</N>17153"

tNpcGossip[17153]["Option3"] = tHalloween2015_RockTheBoat_Text[17153]["Option3"]

--好心帮他擦擦书的灰尘吧！
----非活动时间内
tNpcGossip[17153]["Text2-1"] = {211}
tNpcGossip[17153]["Text211"] = tHalloween2015_RockTheBoat_Text[17153]["Text211"]
tNpcGossip[17153]["tOption2-1"] = {4}

tNpcGossip[17153]["Option4"] = tHalloween2015_RockTheBoat_Text[17153]["Option4"]

----等级不够
tNpcGossip[17153]["Text3-1"] = {311}
tNpcGossip[17153]["Text311"] = tHalloween2015_RockTheBoat_Text[17153]["Text311"]
tNpcGossip[17153]["tOption3-1"] = {4}

--把所有的书都倒着放，哼！
--超过1天了，任务重置
tNpcGossip[17153]["Text4-1"] = {411}
tNpcGossip[17153]["Text411"] = tHalloween2015_RockTheBoat_Text[17153]["Text411"]
tNpcGossip[17153]["tOption4-1"] = {4}

--镜子
tNpcGossip[17154] = tNpcGossip[17154] or DefaultNpc:new{}
tNpcGossip[17154]["OptionHidden"] = 1

tNpcGossip[17154]["Text1-1"] = {111,112}
tNpcGossip[17154]["Text111"] = tHalloween2015_RockTheBoat_Text[17154]["Text111"]
tNpcGossip[17154]["Text112"] = tHalloween2015_RockTheBoat_Text[17154]["Text112"]
tNpcGossip[17154]["tOption1-1"] = {1,2,3}

-- 通用函数，参数区分
tNpcGossip[17154]["Option1"] = tHalloween2015_RockTheBoat_Text[17154]["Option1"]
tNpcGossip[17154]["OptionFunc1"]="Halloween2015_RockTheBoat_DamgeItem</N>17154"
tNpcGossip[17154]["OptionChkFunc1"] = function()
	return Sys_ChkFullTime(tHalloween2015_RockTheBoat_Cont["ActivityTime"]) and (not Halloween2015_RockTheBoat_StcComplete())
end

tNpcGossip[17154]["Option2"] = tHalloween2015_RockTheBoat_Text[17154]["Option2"]
tNpcGossip[17154]["OptionFunc3"]="Halloween2015_RockTheBoat_SysMsg</N>17154"

tNpcGossip[17154]["Option3"] = tHalloween2015_RockTheBoat_Text[17154]["Option3"]


--哇，我要把镜面擦得透亮！
----非活动时间内
tNpcGossip[17154]["Text2-1"] = {211}
tNpcGossip[17154]["Text211"] = tHalloween2015_RockTheBoat_Text[17154]["Text211"]
tNpcGossip[17154]["tOption2-1"] = {4}

tNpcGossip[17154]["Option4"] = tHalloween2015_RockTheBoat_Text[17154]["Option4"]

----等级不够
tNpcGossip[17154]["Text3-1"] = {311}
tNpcGossip[17154]["Text311"] = tHalloween2015_RockTheBoat_Text[17154]["Text311"]
tNpcGossip[17154]["tOption3-1"] = {4}

--用毛笔把镜面画花，哼！
--超过1天了，任务重置
tNpcGossip[17154]["Text4-1"] = {411}
tNpcGossip[17154]["Text411"] = tHalloween2015_RockTheBoat_Text[17154]["Text411"]
tNpcGossip[17154]["tOption4-1"] = {4}

--浴盆
tNpcGossip[17155] = tNpcGossip[17155] or DefaultNpc:new{}
tNpcGossip[17155]["OptionHidden"] = 1

tNpcGossip[17155]["Text1-1"] = {111,112}
tNpcGossip[17155]["Text111"] = tHalloween2015_RockTheBoat_Text[17155]["Text111"]
tNpcGossip[17155]["Text112"] = tHalloween2015_RockTheBoat_Text[17155]["Text112"]
tNpcGossip[17155]["tOption1-1"] = {1,2,3}

-- 通用函数，参数区分
tNpcGossip[17155]["Option1"] = tHalloween2015_RockTheBoat_Text[17155]["Option1"]
tNpcGossip[17155]["OptionFunc1"]="Halloween2015_RockTheBoat_DamgeItem</N>17155"
tNpcGossip[17155]["OptionChkFunc1"] = function()
	return Sys_ChkFullTime(tHalloween2015_RockTheBoat_Cont["ActivityTime"]) and (not Halloween2015_RockTheBoat_StcComplete())
end

tNpcGossip[17155]["Option2"] = tHalloween2015_RockTheBoat_Text[17155]["Option2"]
tNpcGossip[17155]["OptionFunc2"]="Halloween2015_RockTheBoat_SysMsg</N>17155"

tNpcGossip[17155]["Option3"] = tHalloween2015_RockTheBoat_Text[17155]["Option3"]


--帮他把地上的肥皂捡起！
----非活动时间内
tNpcGossip[17155]["Text2-1"] = {211}
tNpcGossip[17155]["Text211"] = tHalloween2015_RockTheBoat_Text[17155]["Text211"]
tNpcGossip[17155]["tOption2-1"] = {4}

tNpcGossip[17155]["Option4"] = tHalloween2015_RockTheBoat_Text[17155]["Option4"]

----等级不够
tNpcGossip[17155]["Text3-1"] = {311}
tNpcGossip[17155]["Text311"] = tHalloween2015_RockTheBoat_Text[17155]["Text311"]
tNpcGossip[17155]["tOption3-1"] = {4}

--往里面加冰水，哼！
--超过1天了，任务重置
tNpcGossip[17155]["Text4-1"] = {411}
tNpcGossip[17155]["Text411"] = tHalloween2015_RockTheBoat_Text[17155]["Text411"]
tNpcGossip[17155]["tOption4-1"] = {4}


