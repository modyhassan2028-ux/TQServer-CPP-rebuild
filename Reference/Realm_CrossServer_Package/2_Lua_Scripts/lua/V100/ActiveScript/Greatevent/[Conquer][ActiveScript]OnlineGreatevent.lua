------------------------------------------------------------------------------------
--Name:		[征服][活动脚本]线上成就榜.lua
--Purpose:	线上成就榜
--Creator: 	严振飞
--Created:	2015/08/19
------------------------------------------------------------------------------------
--掩码说明
---[1]	stc(137,62)	记录签到次数
---[2]	stc(137,63)	记录玩家积分
---[3]	stc(137,64)	记录击杀BOSS获得的10积分令牌数
---[4]	stc(137,65)	记录是否以获取禁天妖兽的10积分令牌


--LOGid 12000195
------------------------------------------------------------------------------------
--命名规范
--OnlineGreatevent_
------------------------------------------------------------------------------------
--STC掩码表
local tOnlineGreatevent_Stc = {}
----------------------------------------
---------------------记录是否已领取奖励
	tOnlineGreatevent_Stc[1] = {}
	tOnlineGreatevent_Stc[1]["EventData"] = 137
	tOnlineGreatevent_Stc[1]["TypeData"] = 62
	tOnlineGreatevent_Stc[1]["Complete"] = 1
	tOnlineGreatevent_Stc[1]["3stTime"] = 2
	tOnlineGreatevent_Stc[1]["7stTime"] = 6
	tOnlineGreatevent_Stc[1]["14stTime"] = 13
	tOnlineGreatevent_Stc[1]["30stTime"] = 29
	tOnlineGreatevent_Stc[1]["Complete"] = 30

---------------------记录每天杀真身怪个数
	tOnlineGreatevent_Stc[2] = {}
	tOnlineGreatevent_Stc[2]["EventData"] = 137
	tOnlineGreatevent_Stc[2]["TypeData"] = 63

---------------------记录击杀BOSS获得的10积分令牌数
	tOnlineGreatevent_Stc[3] = {}
	tOnlineGreatevent_Stc[3]["EventData"] = 137
	tOnlineGreatevent_Stc[3]["TypeData"] = 64
	tOnlineGreatevent_Stc[3]["Complete"] = 600
---------------------记录是否以获取禁天妖兽的10积分令牌
	tOnlineGreatevent_Stc[4] = {}
	tOnlineGreatevent_Stc[4]["EventData"] = 137
	tOnlineGreatevent_Stc[4]["TypeData"] = 65
	tOnlineGreatevent_Stc[4]["Complete"] = 1


--动态存储表
local tOnlineGreatevent_DynaGlobal = {}
	tOnlineGreatevent_DynaGlobal[1] = 50927
	
------------------------------------------------------------------------------------
--活动数据
local tOnlineGreatevent_Data = {}
	-- 活动时间
	tOnlineGreatevent_Data["Festival_BefTime"] = "2026-01-01 00:00 2026-08-20 23:59"
	tOnlineGreatevent_Data["Festival_NowTime"] = "2026-08-21 00:00 2026-09-21 23:59"

	-- 网页链接
	tOnlineGreatevent_Data["WebAddress"] = "http://197.134.251.191/www/index.php?do=Events#kingdom-achievement"

	--等级，转世设置，满级
	tOnlineGreatevent_Data["MinLevel"] = 0
	tOnlineGreatevent_Data["MinMeto"] = 2

	-- 背包空间
	tOnlineGreatevent_Data["ChkSpace"] = 1
	
	-- 输入框字符长度
	tOnlineGreatevent_Data["OptEditLen"] = 10
	
	-- 积分令牌叠加数
	tOnlineGreatevent_Data["AccumulateLimit"] = 1000
	
	-- 禁天妖兽全队执行--2：本地图
	tOnlineGreatevent_Data["Range"] = 2


-- BOSS掉落积分令牌个数
local tOnlineGreatevent_MonstDrop = {}
	tOnlineGreatevent_MonstDrop[4171] = 2
	tOnlineGreatevent_MonstDrop[4217] = 2
	tOnlineGreatevent_MonstDrop[4220] = 3
	tOnlineGreatevent_MonstDrop[4216] = 1
	
-- 积分令牌
local tOnlineGreatevent_PointId = {}
	-- 在线
	tOnlineGreatevent_PointId["Online"] = {}
	tOnlineGreatevent_PointId["Online"][10]    = 3007296
	tOnlineGreatevent_PointId["Online"][50]    = 3007297
	tOnlineGreatevent_PointId["Online"][100]   = 3007298
	-- 充值
	tOnlineGreatevent_PointId["Recharge"] = {}
	tOnlineGreatevent_PointId["Recharge"][50]    = 3007302
	tOnlineGreatevent_PointId["Recharge"][100]   = 3007303
	tOnlineGreatevent_PointId["Recharge"][500]   = 3007299
	tOnlineGreatevent_PointId["Recharge"][1000]  = 3007300
	tOnlineGreatevent_PointId["Recharge"][10000] = 3007301
	-- 杀怪
	tOnlineGreatevent_PointId["Killing"] = {}
	tOnlineGreatevent_PointId["Killing"][10] = 3007304

-- 积分令牌对应经验碎片
local tOnlineGreatevent_ExpId = {}
	tOnlineGreatevent_ExpId[10]    = 3007302
	tOnlineGreatevent_ExpId[50]    = 3007303
	tOnlineGreatevent_ExpId[100]   = 3007304
	tOnlineGreatevent_ExpId[500]   = 3007305
	tOnlineGreatevent_ExpId[1000]  = 3007306
	tOnlineGreatevent_ExpId[10000] = 3007307

-- 对应的经验时数
local tOnlineGreatevent_Exp2Exp = {}
	tOnlineGreatevent_Exp2Exp[10] = 1
	tOnlineGreatevent_Exp2Exp[50] = 5
	tOnlineGreatevent_Exp2Exp[100] = 10
	tOnlineGreatevent_Exp2Exp[500] = 50
	tOnlineGreatevent_Exp2Exp[1000] = 100
	tOnlineGreatevent_Exp2Exp[10000] = 1000
	
-- 满级对应的修行值
local tOnlineGreatevent_Exp2Cul = {}
	tOnlineGreatevent_Exp2Cul[10] = 1
	tOnlineGreatevent_Exp2Cul[50] = 3
	tOnlineGreatevent_Exp2Cul[100] = 5
	tOnlineGreatevent_Exp2Cul[500] = 25
	tOnlineGreatevent_Exp2Cul[1000] = 50
	tOnlineGreatevent_Exp2Cul[10000] = 500
	tOnlineGreatevent_Exp2Cul["Exp"] = 4
	tOnlineGreatevent_Exp2Cul["Cul"] = 6


-- 额外签到令牌个数
local tOnlineGreatevent_SignNum = {}
	tOnlineGreatevent_SignNum["Time3"]  = 2
	tOnlineGreatevent_SignNum["Time7"]  = 3
	tOnlineGreatevent_SignNum["Time14"] = 1
	tOnlineGreatevent_SignNum["Time30"] = 1

-- 额外签到令牌背包空间数
local tOnlineGreatevent_SpaceNum = {}
	tOnlineGreatevent_SignNum[3007296] = 1
	tOnlineGreatevent_SignNum[3007297] = 2
	tOnlineGreatevent_SignNum[3007298] = 2

-- 积分令牌礼包
local tOnlineGreatevent_TokenPag = {}
	-- 100*2积分令牌
	tOnlineGreatevent_TokenPag[3007312] = {}
	tOnlineGreatevent_TokenPag[3007312][1] = {}
	tOnlineGreatevent_TokenPag[3007312][1]["ItemId"] = 3007303
	tOnlineGreatevent_TokenPag[3007312][1]["ItemNum"] = 2
	-- 100*3+50*1积分令牌
	tOnlineGreatevent_TokenPag[3007313] = {}
	tOnlineGreatevent_TokenPag[3007313][1] = {}
	tOnlineGreatevent_TokenPag[3007313][1]["ItemId"] = 3007303
	tOnlineGreatevent_TokenPag[3007313][1]["ItemNum"] = 3
	tOnlineGreatevent_TokenPag[3007313][2] = {}
	tOnlineGreatevent_TokenPag[3007313][2]["ItemId"] = 3007302
	tOnlineGreatevent_TokenPag[3007313][2]["ItemNum"] = 1
	-- 500*1+50*1积分令牌
	tOnlineGreatevent_TokenPag[3007314] = {}
	tOnlineGreatevent_TokenPag[3007314][1] = {}
	tOnlineGreatevent_TokenPag[3007314][1]["ItemId"] = 3007299
	tOnlineGreatevent_TokenPag[3007314][1]["ItemNum"] = 1
	tOnlineGreatevent_TokenPag[3007314][2] = {}
	tOnlineGreatevent_TokenPag[3007314][2]["ItemId"] = 3007302
	tOnlineGreatevent_TokenPag[3007314][2]["ItemNum"] = 1
	-- 1000*2+500*1积分令牌
	tOnlineGreatevent_TokenPag[3007315] = {}
	tOnlineGreatevent_TokenPag[3007315][1] = {}
	tOnlineGreatevent_TokenPag[3007315][1]["ItemId"] = 3007300
	tOnlineGreatevent_TokenPag[3007315][1]["ItemNum"] = 2
	tOnlineGreatevent_TokenPag[3007315][2] = {}
	tOnlineGreatevent_TokenPag[3007315][2]["ItemId"] = 3007299
	tOnlineGreatevent_TokenPag[3007315][2]["ItemNum"] = 1
	-- 1000*6积分令牌
	tOnlineGreatevent_TokenPag[3007316] = {}
	tOnlineGreatevent_TokenPag[3007316][1] = {}
	tOnlineGreatevent_TokenPag[3007316][1]["ItemId"] = 3007300
	tOnlineGreatevent_TokenPag[3007316][1]["ItemNum"] = 6
	-- 10000*2+1000*3积分令牌
	tOnlineGreatevent_TokenPag[3007317] = {}
	tOnlineGreatevent_TokenPag[3007317][1] = {}
	tOnlineGreatevent_TokenPag[3007317][1]["ItemId"] = 3007301
	tOnlineGreatevent_TokenPag[3007317][1]["ItemNum"] = 2
	tOnlineGreatevent_TokenPag[3007317][2] = {}
	tOnlineGreatevent_TokenPag[3007317][2]["ItemId"] = 3007300
	tOnlineGreatevent_TokenPag[3007317][2]["ItemNum"] = 3
	-- 10000*4积分令牌
	tOnlineGreatevent_TokenPag[3007318] = {}
	tOnlineGreatevent_TokenPag[3007318][1] = {}
	tOnlineGreatevent_TokenPag[3007318][1]["ItemId"] = 3007301
	tOnlineGreatevent_TokenPag[3007318][1]["ItemNum"] = 4

------------------------------------------------------------------------------------
--活动LOG数据
local tOnlineGreatevent_Log = {}
	tOnlineGreatevent_Log["FestivalId"] = 3456
	tOnlineGreatevent_Log["LogId"] = 12000195
	-- 签到
	tOnlineGreatevent_Log["Sgin"] = "0,0,0,0,12000195,2,%d[%d],1[%d]"
	-- 上交积分令牌
	tOnlineGreatevent_Log["SubToken"] = "0,0,%d,%d,12000195,2,0,%d"
	-- 兑换经验
	tOnlineGreatevent_Log["ExpToken"] = "0,0,%d,%d,12000195,2,%d,%d"
	-- 积分令牌礼包打开
	tOnlineGreatevent_Log["TokenPag"] = "0,0,%d,1,12000195,2,%s[%s],%s[%s]"
	-- BOSS掉落
	tOnlineGreatevent_Log["Monster"] = "0,0,%d,1,12000195,2,%d,%d"
	--删除任务物品
	tOnlineGreatevent_Log["DelItem"] = "0,0,%d,1,12000195,2,0,0"
	
local tOnlineGreatevent_EmoneyBuy = {}
	-- 10积分令牌（在线）		350 20090
	-- 50积分令牌（在线）		350 20091
	-- 100积分令牌（在线）		350 20092
	-- 500积分令牌（充值）		350 20093
	-- 1000积分令牌（充值）		350 20094
	-- 10000积分令牌（充值）	350 20095
	-- 50积分令牌（充值）		350 200905
	-- 100积分令牌（充值）		350 200906
	-- 10积分令牌（杀怪）		350 200907

	tOnlineGreatevent_EmoneyBuy[3007296] = "350	20090	%d	%d	1	"
	tOnlineGreatevent_EmoneyBuy[3007297] = "350	20091	%d	%d	1	"
	tOnlineGreatevent_EmoneyBuy[3007298] = "350	20092	%d	%d	1	"
	tOnlineGreatevent_EmoneyBuy[3007299] = "350	20093	%d	%d	1	"
	tOnlineGreatevent_EmoneyBuy[3007300] = "350	20094	%d	%d	1	"
	tOnlineGreatevent_EmoneyBuy[3007301] = "350	20095	%d	%d	1	"
	
	tOnlineGreatevent_EmoneyBuy[3007302] = "350	200905	%d	%d	1	"
	tOnlineGreatevent_EmoneyBuy[3007303] = "350	200906	%d	%d	1	"
	tOnlineGreatevent_EmoneyBuy[3007304] = "350	200907	%d	%d	1	"


---------------------------------------NPC函数---------------------------------------------
--网页链接
-- Imperial live configuration bridge. Keep this block ASCII-only: the source file uses a legacy code page.
ImperialKingdomAchievementRuntime = ImperialKingdomAchievementRuntime or {generation=0,revision=""}
ImperialKingdomAchievementRuntime.generation = ImperialKingdomAchievementRuntime.generation + 1
local nImperialKingdomGeneration = ImperialKingdomAchievementRuntime.generation
local sImperialKingdomConfigPath = "lua\\V100\\ActiveScript\\ImperialScripts\\[Imperial][ActiveScript]KingdomAchievementConfig.lua"
local tImperialKingdomMilestoneReward = {}

local function ImperialKingdomAchievement_ApplyConfig()
    local cfg = tImperialKingdomAchievementConfig or {}
    if cfg.Enabled then
        if cfg.ForceOpen then
            tOnlineGreatevent_Data["Festival_NowTime"] = "2000-01-01 00:00 2099-12-31 23:59"
        else
            tOnlineGreatevent_Data["Festival_NowTime"] = tostring(cfg.StartAt or "2026-08-21 00:00").." "..tostring(cfg.EndAt or "2026-09-21 23:59")
        end
        tOnlineGreatevent_Data["Festival_BefTime"] = "2000-01-01 00:00 "..tostring(cfg.StartAt or "2026-08-21 00:00")
    else
        tOnlineGreatevent_Data["Festival_BefTime"] = "2000-01-01 00:00 2000-01-01 00:01"
        tOnlineGreatevent_Data["Festival_NowTime"] = "2000-01-01 00:00 2000-01-01 00:01"
    end
    tOnlineGreatevent_Data["WebAddress"] = tostring(cfg.WebAddress or tOnlineGreatevent_Data["WebAddress"])
    tOnlineGreatevent_Data["MinLevel"] = tonumber(cfg.MinLevel) or tOnlineGreatevent_Data["MinLevel"]
    tOnlineGreatevent_Data["MinMeto"] = tonumber(cfg.MinReborn) or tOnlineGreatevent_Data["MinMeto"]
    tOnlineGreatevent_Data["AccumulateLimit"] = tonumber(cfg.AccumulateLimit) or tOnlineGreatevent_Data["AccumulateLimit"]
    tOnlineGreatevent_Data["Range"] = tonumber(cfg.TeamRange) or tOnlineGreatevent_Data["Range"]
    tOnlineGreatevent_Stc[3]["Complete"] = tonumber(cfg.BossAwardLimit) or tOnlineGreatevent_Stc[3]["Complete"]
    for group,values in pairs(cfg.Badges or {}) do
        if tOnlineGreatevent_PointId[group] ~= nil then
            for points,itemId in pairs(values) do tOnlineGreatevent_PointId[group][tonumber(points)] = tonumber(itemId) end
        end
    end
    for points,conversion in pairs(cfg.Conversions or {}) do
        points = tonumber(points)
        if points ~= nil then
            tOnlineGreatevent_Exp2Exp[points] = tonumber(conversion.ExpMinutes) or tOnlineGreatevent_Exp2Exp[points]
            tOnlineGreatevent_Exp2Cul[points] = tonumber(conversion.StudyPoints) or tOnlineGreatevent_Exp2Cul[points]
        end
    end
    tImperialKingdomMilestoneReward = {}
    for _,reward in ipairs(cfg.Milestones or {}) do
        local day = tonumber(reward.Day)
        if day ~= nil then
            tImperialKingdomMilestoneReward[day] = {ItemId=tonumber(reward.ItemId),Amount=tonumber(reward.Amount)}
            tOnlineGreatevent_SignNum["Time"..tostring(day)] = tonumber(reward.Amount) or tOnlineGreatevent_SignNum["Time"..tostring(day)]
        end
    end
    for monsterType,badgeAmount in pairs(cfg.BossDrops or {}) do tOnlineGreatevent_MonstDrop[tonumber(monsterType)] = tonumber(badgeAmount) end
    if tonumber(cfg.DailyItemId) ~= nil then tOnlineGreatevent_PointId["Online"][10] = tonumber(cfg.DailyItemId) end
end

function ImperialKingdomAchievement_ConfigPulse(requestGeneration)
    if requestGeneration ~= ImperialKingdomAchievementRuntime.generation then return end
    local ok = pcall(dofile,sImperialKingdomConfigPath)
    if ok then
        ImperialKingdomAchievementRuntime.revision = tostring(tImperialKingdomAchievementRevision or "")
        ImperialKingdomAchievement_ApplyConfig()
    elseif Sys_SaveAbnormalLog ~= nil then
        Sys_SaveAbnormalLog("[Imperial][KingdomAchievement] live config parse failed")
    end
    if Sys_SetLuaTimer ~= nil then Sys_SetLuaTimer(5,"ImperialKingdomAchievement_ConfigPulse</N>"..tostring(requestGeneration)) end
end

pcall(dofile,sImperialKingdomConfigPath)
ImperialKingdomAchievement_ApplyConfig()
if Sys_SetLuaTimer ~= nil then Sys_SetLuaTimer(5,"ImperialKingdomAchievement_ConfigPulse</N>"..tostring(nImperialKingdomGeneration)) end

function OnlineGreatevent_WebLink()
	local sWebAddress = tOnlineGreatevent_Data["WebAddress"]
	User_SendWebPage(sWebAddress)
end

---------------------------------------【签到】
-- 签到函数
function OnlineGreatevent_SignMain(nNpcId)
	-- 活动时间
	if not Sys_ChkFullTime(tOnlineGreatevent_Data["Festival_NowTime"]) then
		LinkNpcGossipFunc_New(nNpcId,"1-2")
		return
	end
	
	local nEventData_1 = tOnlineGreatevent_Stc[1]["EventData"]
	local nTypeData_1 = tOnlineGreatevent_Stc[1]["TypeData"]
	local nComplete_1 = tOnlineGreatevent_Stc[1]["Complete"]
	
	-- 是否隔天
	if not Task_ChkStcValue(nEventData_1,nTypeData_1,"==",0) then
		if not Task_StcInterval(nEventData_1,nTypeData_1,1,4) then
			LinkNpcGossipFunc_New(nNpcId,"1-4")
			return
		end
	end
	
	local nTime_3 = tOnlineGreatevent_Stc[1]["3stTime"]
	local nTime_7 = tOnlineGreatevent_Stc[1]["7stTime"]
	local nTime_14 = tOnlineGreatevent_Stc[1]["14stTime"]
	local nTime_30 = tOnlineGreatevent_Stc[1]["30stTime"]
	local nAddItemId = 0
	local nAddItemNum = 0
	local sLogText = tOnlineGreatevent_Log["Sgin"]
	local sTalkText = tOnlineGreatevent_Text[18797]["Text151"]
	local sTalkLink = tOnlineGreatevent_Text[18797]["Text152"]
	local sSginAdd = tOnlineGreatevent_Text[18797]["Text153"]
	local sAdd2005 = ""
	
	-- 第3次签到
	if Task_ChkStcValue(nEventData_1,nTypeData_1,"==",nTime_3) then
		nAddItemId = tImperialKingdomMilestoneReward[3]["ItemId"]
		nAddItemNum = tImperialKingdomMilestoneReward[3]["Amount"]
		
	-- 第7次签到
	elseif Task_ChkStcValue(nEventData_1,nTypeData_1,"==",nTime_7) then
		nAddItemId = tImperialKingdomMilestoneReward[7]["ItemId"]
		nAddItemNum = tImperialKingdomMilestoneReward[7]["Amount"]
	
	-- 第14次签到
	elseif Task_ChkStcValue(nEventData_1,nTypeData_1,"==",nTime_14) then
		nAddItemId = tImperialKingdomMilestoneReward[14]["ItemId"]
		nAddItemNum = tImperialKingdomMilestoneReward[14]["Amount"]

	-- 第30次签到
	elseif Task_ChkStcValue(nEventData_1,nTypeData_1,"==",nTime_30) then
		nAddItemId = tImperialKingdomMilestoneReward[30]["ItemId"]
		nAddItemNum = tImperialKingdomMilestoneReward[30]["Amount"]
	end
	
	-- 背包空间
	if nAddItemId ~= 0 then
		if not User_CheckLeftSpace(tOnlineGreatevent_SignNum[nAddItemId]) then
			Sys_MsgBox(tOnlineGreatevent_Text["SpaceFull"])
			return
		end
	elseif not User_CheckLeftSpace(tOnlineGreatevent_Data["ChkSpace"]) then
		Sys_MsgBox(tOnlineGreatevent_Text["SpaceFull"])
		return
	end
	
	-- 置掩码
	Task_AddStatistic(nEventData_1,nTypeData_1,1,1)
	Task_SetStcTimestamp(nEventData_1,nTypeData_1,0)

	-- 额外奖励
	if nAddItemId ~= 0 and nAddItemNum ~= 0 then
		Item_AddItem(nAddItemId,0,nAddItemNum)
		local nSginTime = Get_UserStatisticValue(nEventData_1,nTypeData_1)
		local sItemName = Get_ItemtypeName(nAddItemId)
		sTalkLink = string.format(sSginAdd,nSginTime)
		sAdd2005 = string.format(tOnlineGreatevent_Text["SignAdd"],nAddItemNum,sItemName)
	end
	
	-- 每次签到获得
	Item_AddItem(tOnlineGreatevent_PointId["Online"][10])
	
	local sSginDay = Get_UserStatisticValue(nEventData_1,nTypeData_1)
	local sLogFormat = string.format(sLogText,tOnlineGreatevent_PointId["Online"][10],nAddItemId,nAddItemNum)
	local sText2005 = string.format(tOnlineGreatevent_Text["Sign"],sSginDay,sAdd2005)
	sLogText = string.gsub(sLogFormat,"%[0%]","")
	tNpcGossip[18797]["Text151"] = string.format(sTalkText,sTalkLink)
	Sys_SaveActionFestivalLog(sLogText)
	User_TalkChannel2005(sText2005)
	LinkNpcGossipFunc_New(nNpcId,"1-5")
end

---------------------------------------【上交令牌】
--- 上交令牌数据处理
function OnlineGreatevent_SubManage(nNpcId,sOptionNum,sTokenType,nTokenPst,nItemId,sItemName)
	-- 活动时间
	if not Sys_ChkFullTime(tOnlineGreatevent_Data["Festival_NowTime"]) then
		LinkNpcGossipFunc_New(nNpcId,"1-2")
		return
	end
	local sFuncBack = string.format("OnlineGreatevent_SubToken</N>18797</N>241</S>%s</S>%s</N>%d",sOptionNum,sTokenType,nTokenPst)
	
	-- 输入字符判断
	local nItemNum = tonumber(Get_SysAcceptStr())
	if type(nItemNum) ~= "number" or nItemNum <= 0 then
		tNpcGossip[18797]["OptionFunc261"] = sFuncBack
		LinkNpcGossipFunc_New(nNpcId,"2-6")
		return
	end
	
	-- 令牌不足
	if not Item_ChkMulItem(nItemId,nItemId,nItemNum) then
		tNpcGossip[18797]["Text251"] = string.format(tOnlineGreatevent_Text[18797]["Text251"],nItemNum,sItemName)
		LinkNpcGossipFunc_New(nNpcId,"2-5")
		return
		
	-- 令牌足够并删除成功
	elseif Item_DelMulItem(nItemId,nItemId,nItemNum) then
		local nEventData_2 = tOnlineGreatevent_Stc[2]["EventData"]
		local nTypeData_2 = tOnlineGreatevent_Stc[2]["TypeData"]
		local nAddPoint = nTokenPst * nItemNum
		
		-- 增加积分
		Task_AddStatistic(nEventData_2,nTypeData_2,nAddPoint,1)
		
		-- 打LOG
		local nPoint = Get_UserStatisticValue(nEventData_2,nTypeData_2)
		local sEmoneyBuy = string.format(tOnlineGreatevent_EmoneyBuy[nItemId],nAddPoint,nAddPoint)
		local sLogText = string.format(tOnlineGreatevent_Log["SubToken"],nItemId,nItemNum,nAddPoint)
		local sTalkText = string.format(tOnlineGreatevent_Text["GetPoint"],nAddPoint)
		tNpcGossip[18797]["Text271"] = string.format(tOnlineGreatevent_Text[18797]["Text271"],nPoint)
		tNpcGossip[18797]["OptionFunc271"] = sFuncBack
		Sys_SaveEmoneyBuy(sEmoneyBuy)
		Sys_SaveActionFestivalLog(sLogText)
		User_TalkChannel2005(sTalkText)
		LinkNpcGossipFunc_New(nNpcId,"2-7")
	end
end

---【兑换经验】
-- 兑换经验数据处理
function OnlineGreatevent_ExpManage(nNpcId,sOptionNum,sTokenType,nTokenPst,nItemId,sItemName)
	-- 活动时间
	if not Sys_ChkFullTime(tOnlineGreatevent_Data["Festival_NowTime"]) then
		LinkNpcGossipFunc_New(nNpcId,"1-2")
		return
	end
	
	local sFuncBack = string.format("OnlineGreatevent_SubToken</N>18797</N>351</S>%s</S>%s</N>%d",sOptionNum,sTokenType,nTokenPst)

	-- 输入字符判断
	local nItemNum = tonumber(Get_SysAcceptStr())
	if type(nItemNum) ~= "number" or nItemNum <= 0 then
		tNpcGossip[18797]["OptionFunc381"] = sFuncBack
		LinkNpcGossipFunc_New(nNpcId,"3-8")
		return
	end
	
	-- 令牌不足
	if not Item_ChkMulItem(nItemId,nItemId,nItemNum) then
		tNpcGossip[18797]["Text371"] = string.format(tOnlineGreatevent_Text[18797]["Text371"],nItemNum,sItemName)
		LinkNpcGossipFunc_New(nNpcId,"3-7")
		return
	
	-- 删除令牌
	elseif Item_DelMulItem(nItemId,nItemId,nItemNum) then
		local nUserLev = Get_UserLevel()
		local nAddValue = 0
		local nAddType = 0
		
		-- 非满级给经验
		if nUserLev < G_User_MaxLev then
			nAddValue = tOnlineGreatevent_Exp2Exp[nTokenPst] * nItemNum
			User_AddExpTime(nAddValue)
			nAddType = tOnlineGreatevent_Exp2Cul["Exp"]

		-- 满级给修行值
		else
			nAddValue = tOnlineGreatevent_Exp2Cul[nTokenPst] * nItemNum
			User_AddCultivation(nAddValue)
			nAddType = tOnlineGreatevent_Exp2Cul["Cul"]
		end
		
		-- 打掩码
		local sLogText = string.format(tOnlineGreatevent_Log["ExpToken"],nItemId,nItemNum,nAddType,nAddValue)
		local sTalkText = string.format(tOnlineGreatevent_Text[18797]["Text3".. nAddType .."1"],nItemNum,sItemName,nAddValue)
		local sText2005 = string.format(tOnlineGreatevent_Text["ExpToken"][nAddType],nAddValue)
		tNpcGossip[18797]["Text3".. nAddType .."1"] = sTalkText
		tNpcGossip[18797]["OptionFunc3".. nAddType .."1"] = sFuncBack
		Sys_SaveActionFestivalLog(sLogText)
		User_TalkChannel2005(sText2005)
		LinkNpcGossipFunc_New(nNpcId,"3-".. nAddType)
	end
end


--- 上交令牌初始接入
function OnlineGreatevent_SubToken(nNpcId,nTextNum,sOptionNum,sTokenType,nTokenPst)
	-- 活动时间
	if not Sys_ChkFullTime(tOnlineGreatevent_Data["Festival_NowTime"]) then
		LinkNpcGossipFunc_New(nNpcId,"1-2")
		return
	end
	
	-- 输入框跳转函数
	local tFunc = {}
		tFunc[241] = "OnlineGreatevent_SubManage</N>%d</S>%s</S>%s</N>%d</N>%d</S>%s"
		tFunc[351] = "OnlineGreatevent_ExpManage</N>%d</S>%s</S>%s</N>%d</N>%d</S>%s"

	-- 数量输入对白
	local nItemId = tOnlineGreatevent_PointId[sTokenType][nTokenPst]
	local sItemName = Get_ItemtypeName(nItemId)
	local sDialogText = string.format(tOnlineGreatevent_Text[nNpcId]["Text" .. nTextNum],sItemName)
	local sOptEditText = tOnlineGreatevent_Text[nNpcId][tostring(nTextNum)]
	local nOptEditLen = tOnlineGreatevent_Data["OptEditLen"]
	local sOptEditFunc = string.format(tFunc[nTextNum],nNpcId,sOptionNum,sTokenType,nTokenPst,nItemId,sItemName)
	local sOptionFunc = string.format("</F>LinkNpcGossipFunc_New</N>%d</S>%s",nNpcId,sOptionNum)
	-- Sys_DialogTaskClear()
	Sys_DialogText(sDialogText)
	Sys_DialogOptEdit(sOptEditText,nOptEditLen,sOptEditFunc)
	Sys_DialogOption(tOnlineGreatevent_Text[nNpcId][tostring(nTextNum+1)],sOptionFunc)
	Sys_DialogFace(nNpcId)
	Sys_DialogEnd()
end


-----------------------------------------怪物逻辑---------------------------------------------
function OnlineGreatevent_AwardTeam(nMonsterTypeId,nItemId,nItemNum)
	-- 活动时间
	if not Sys_ChkFullTime(tOnlineGreatevent_Data["Festival_NowTime"]) then
		return
	end
	
	local nEventData_3 = tOnlineGreatevent_Stc[3]["EventData"]
	local nTypeData_3  = tOnlineGreatevent_Stc[3]["TypeData"]
	local nComplete_3  = tOnlineGreatevent_Stc[3]["Complete"]

	-- 获得积分令牌数是否超过限制
	if Task_ChkStcValue(nEventData_3,nTypeData_3,">=",nComplete_3) then
		User_TalkChannel2005(tOnlineGreatevent_Text["MonsterLimit"])
		return
	end
	
	local nEventData_4 = tOnlineGreatevent_Stc[4]["EventData"]
	local nTypeData_4  = tOnlineGreatevent_Stc[4]["TypeData"]
	local nComplete_4  = tOnlineGreatevent_Stc[4]["Complete"]
	
	-- 今天是否已击杀
	if Task_ChkStcValue(nEventData_4,nTypeData_4,">=",nComplete_4) then
		-- 是否隔天
		if not Task_StcInterval(nEventData_4,nTypeData_4,1,4) then
			User_TalkChannel2005(tOnlineGreatevent_Text["ThrillingSpook"])
			return
		else
			Task_SetStatistic(nEventData_4,nTypeData_4,0,1)
			Task_SetStcTimestamp(nEventData_4,nTypeData_4,0)
		end
	end
	
	Task_AddStatistic(nEventData_3,nTypeData_3,1,1)
	Task_SetStatistic(nEventData_4,nTypeData_4,nComplete_4,1)
	Task_SetStcTimestamp(nEventData_4,nTypeData_4,0)

	Item_AddItem(nItemId,0,nItemNum)
	
	-- 打LOG
	local sItemName = Get_ItemtypeName(nItemId)
	local sLogText = string.format(tOnlineGreatevent_Log["Monster"],nMonsterTypeId,nItemId,nItemNum)
	local sTalkText = string.format(tOnlineGreatevent_Text["MonsterToken"],nItemNum,sItemName)
	Sys_SaveActionFestivalLog(sLogText)
	User_TalkChannel2005(sTalkText)
end


function OnlineGreatevent_Monster(nMonsterTypeId)
	-- 活动时间
	if not Sys_ChkFullTime(tOnlineGreatevent_Data["Festival_NowTime"]) then
		return
	end

	local nItemId = tOnlineGreatevent_PointId["Killing"][10]
	local nItemNum = tOnlineGreatevent_MonstDrop[nMonsterTypeId]
	local nLimit = tOnlineGreatevent_Data["AccumulateLimit"] - nItemNum
	
	-- 背包内是否已有10积分令牌
	if not Item_ChkItem(nItemId) or Item_ChkMulItem(nItemId,nItemId,nLimit) then
		-- 背包空间
		if not User_CheckLeftSpace(tOnlineGreatevent_Data["ChkSpace"]) then
			User_TalkChannel2005(tOnlineGreatevent_Text["SpaceMonster"])
			return
		end
	end
	
	local nEventData_3 = tOnlineGreatevent_Stc[3]["EventData"]
	local nTypeData_3  = tOnlineGreatevent_Stc[3]["TypeData"]
	local nComplete_3  = tOnlineGreatevent_Stc[3]["Complete"]
	-- 获得积分令牌数是否超过限制
	if Task_ChkStcValue(nEventData_3,nTypeData_3,">=",nComplete_3) then
		User_TalkChannel2005(tOnlineGreatevent_Text["MonsterLimit"])
		return
	end

	-- 是否为禁天妖兽
	if nMonsterTypeId == 4216 or nMonsterTypeId == 4217 then
		local nTeamNum = Get_UserTeamNumbers()
		--判断玩家是否组队
		if nTeamNum ~= 0 then
			-- 本地图全队执行
			local sFunc = "OnlineGreatevent_AwardTeam</N>".. nMonsterTypeId .."</N>".. nItemId .."</N>".. nItemNum
			User_TeamExeFuncByTeamer(tOnlineGreatevent_Data["Range"],sFunc)
			return
		end
		
		local nEventData_4 = tOnlineGreatevent_Stc[4]["EventData"]
		local nTypeData_4  = tOnlineGreatevent_Stc[4]["TypeData"]
		local nComplete_4  = tOnlineGreatevent_Stc[4]["Complete"]
		
		-- 今天是否已击杀
		if Task_ChkStcValue(nEventData_4,nTypeData_4,">=",nComplete_4) then
			-- 是否隔天
			if not Task_StcInterval(nEventData_4,nTypeData_4,1,4) then
				User_TalkChannel2005(tOnlineGreatevent_Text["ThrillingSpook"])
				return
			else
				Task_SetStatistic(nEventData_4,nTypeData_4,0,1)
				Task_SetStcTimestamp(nEventData_4,nTypeData_4,0)
			end
		end
		
		-- 设掩码
		Task_SetStatistic(nEventData_4,nTypeData_4,nComplete_4,1)
		Task_SetStcTimestamp(nEventData_4,nTypeData_4,0)
	end
	
	Task_AddStatistic(nEventData_3,nTypeData_3,1,1)
	Item_AddItem(nItemId,0,nItemNum)
	
	-- 打LOG
	local sItemName = Get_ItemtypeName(nItemId)
	local sLogText = string.format(tOnlineGreatevent_Log["Monster"],nMonsterTypeId,nItemId,nItemNum)
	local sTalkText = string.format(tOnlineGreatevent_Text["MonsterToken"],nItemNum,sItemName)
	Sys_SaveActionFestivalLog(sLogText)
	User_TalkChannel2005(sTalkText)
end

------------------------------------------NPC配置-------------------------------------------
---------------------NPC头像
tNpcFace[3788] = 101

---------------------NPC对话
------------------------------------------
-- 【国战战备官】
tNpcGossip[18797] = tNpcGossip[18797] or DefaultNpc:new{}
tNpcGossip[18797]["OptionHidden"] = 1

-- 活动前
tNpcGossip[18797]["Text1-1"] = {111,112,113,114}
tNpcGossip[18797]["tOption1-1"] = {111}
tNpcGossip[18797]["Text111"] = tOnlineGreatevent_Text[18797]["Text111"]
tNpcGossip[18797]["Text112"] = tOnlineGreatevent_Text[18797]["Text112"]
tNpcGossip[18797]["Text113"] = tOnlineGreatevent_Text[18797]["Text113"]
tNpcGossip[18797]["Text114"] = tOnlineGreatevent_Text[18797]["Text114"]
tNpcGossip[18797]["Option111"] = tOnlineGreatevent_Text[18797]["111"]
tNpcGossip[18797]["ChkFunc1-1"] = function ()
	return Sys_ChkFullTime(tOnlineGreatevent_Data["Festival_BefTime"])
end

-- 活动后
tNpcGossip[18797]["Text1-2"] = {121}
tNpcGossip[18797]["tOption1-2"] = {121}
tNpcGossip[18797]["Text121"] = tOnlineGreatevent_Text[18797]["Text121"]
tNpcGossip[18797]["Option121"] = tOnlineGreatevent_Text[18797]["121"]
tNpcGossip[18797]["ChkFunc1-2"] = function ()
	return not Sys_ChkFullTime(tOnlineGreatevent_Data["Festival_NowTime"])
end


-- 活动中
tNpcGossip[18797]["Text1-3"] = {131,132,133,134}
tNpcGossip[18797]["tOption1-3"] = {131,132,133,134,135,136}
tNpcGossip[18797]["Text131"] = tOnlineGreatevent_Text[18797]["Text131"]
tNpcGossip[18797]["Text132"] = tOnlineGreatevent_Text[18797]["Text132"]
tNpcGossip[18797]["Text133"] = tOnlineGreatevent_Text[18797]["Text133"]
tNpcGossip[18797]["Text134"] = tOnlineGreatevent_Text[18797]["Text134"]
tNpcGossip[18797]["Option131"] = tOnlineGreatevent_Text[18797]["131"]
tNpcGossip[18797]["Option132"] = tOnlineGreatevent_Text[18797]["132"]
tNpcGossip[18797]["Option133"] = tOnlineGreatevent_Text[18797]["133"]
tNpcGossip[18797]["Option134"] = tOnlineGreatevent_Text[18797]["134"]
tNpcGossip[18797]["Option135"] = tOnlineGreatevent_Text[18797]["135"]
tNpcGossip[18797]["Option136"] = tOnlineGreatevent_Text[18797]["136"]
tNpcGossip[18797]["OptionFunc131"] = "OnlineGreatevent_SignMain</N>18797"
tNpcGossip[18797]["OptionPoint132"] = "2"
tNpcGossip[18797]["OptionPoint133"] = "3"
tNpcGossip[18797]["OptionFunc134"] = "OnlineGreatevent_WebLink"
tNpcGossip[18797]["OptionPoint135"] = "4"
tNpcGossip[18797]["ChkFunc1-3"] = function ()
	local nEventData_2 = tOnlineGreatevent_Stc[2]["EventData"]
	local nTypeData_2 = tOnlineGreatevent_Stc[2]["TypeData"]
	local nPoint = Get_UserStatisticValue(nEventData_2,nTypeData_2)
	local sText = tOnlineGreatevent_Text[18797]["Text132"]
	tNpcGossip[18797]["Text132"] = string.format(sText,nPoint)
	return true
end
tNpcGossip[18797]["OptionChkFunc131"] = function ()
	-- 等级是否达到要求
	return User_JudgeLevelAndMetempsychosis(tOnlineGreatevent_Data["MinLevel"],tOnlineGreatevent_Data["MinMeto"])
end
tNpcGossip[18797]["OptionChkFunc132"] = function ()
	-- 等级是否达到要求
	return User_JudgeLevelAndMetempsychosis(tOnlineGreatevent_Data["MinLevel"],tOnlineGreatevent_Data["MinMeto"])
end

-- 当天已签到
tNpcGossip[18797]["Text1-4"] = {141}
tNpcGossip[18797]["tOption1-4"] = {141}
tNpcGossip[18797]["Text141"] = tOnlineGreatevent_Text[18797]["Text141"]
tNpcGossip[18797]["Option141"] = tOnlineGreatevent_Text[18797]["141"]

-- 签到成功
tNpcGossip[18797]["Text1-5"] = {151}
tNpcGossip[18797]["tOption1-5"] = {151}
tNpcGossip[18797]["Text151"] = tOnlineGreatevent_Text[18797]["Text151"]
tNpcGossip[18797]["Option151"] = tOnlineGreatevent_Text[18797]["151"]


-- 【上交令牌】
-- 上交类型选择对白
tNpcGossip[18797]["Text2-1"] = {211,212}
tNpcGossip[18797]["Text211"] = tOnlineGreatevent_Text[18797]["Text211"]
tNpcGossip[18797]["Text212"] = tOnlineGreatevent_Text[18797]["Text212"]
tNpcGossip[18797]["tOption2-1"] = {211,212,213,214,215}
tNpcGossip[18797]["Option211"] = tOnlineGreatevent_Text[18797]["211"]
tNpcGossip[18797]["Option212"] = tOnlineGreatevent_Text[18797]["212"]
tNpcGossip[18797]["Option213"] = tOnlineGreatevent_Text[18797]["213"]
tNpcGossip[18797]["Option214"] = tOnlineGreatevent_Text[18797]["214"]
tNpcGossip[18797]["Option215"] = tOnlineGreatevent_Text[18797]["215"]
tNpcGossip[18797]["OptionPoint211"] = "2-2"
tNpcGossip[18797]["OptionPoint212"] = "2-3"
tNpcGossip[18797]["OptionFunc213"] = "OnlineGreatevent_SubToken</N>18797</N>241</S>2-1</S>Killing</N>10"
tNpcGossip[18797]["OptionPoint214"] = "1"
tNpcGossip[18797]["ChkFunc2-1"] = function ()
	local nEventData_2 = tOnlineGreatevent_Stc[2]["EventData"]
	local nTypeData_2 = tOnlineGreatevent_Stc[2]["TypeData"]
	local nPoint = Get_UserStatisticValue(nEventData_2,nTypeData_2)
	local sText = tOnlineGreatevent_Text[18797]["Text212"]
	tNpcGossip[18797]["Text212"] = string.format(sText,nPoint)
	return true
end
-- 在线令牌(上交)
tNpcGossip[18797]["Text2-2"] = {221}
tNpcGossip[18797]["Text221"] = tOnlineGreatevent_Text[18797]["Text221"]
tNpcGossip[18797]["tOption2-2"] = {221,222,223,224}
tNpcGossip[18797]["Option221"] = tOnlineGreatevent_Text[18797]["221"]
tNpcGossip[18797]["Option222"] = tOnlineGreatevent_Text[18797]["222"]
tNpcGossip[18797]["Option223"] = tOnlineGreatevent_Text[18797]["223"]
tNpcGossip[18797]["Option224"] = tOnlineGreatevent_Text[18797]["224"]
tNpcGossip[18797]["OptionFunc221"] = "OnlineGreatevent_SubToken</N>18797</N>241</S>2-2</S>Online</N>10"
tNpcGossip[18797]["OptionFunc222"] = "OnlineGreatevent_SubToken</N>18797</N>241</S>2-2</S>Online</N>50"
tNpcGossip[18797]["OptionFunc223"] = "OnlineGreatevent_SubToken</N>18797</N>241</S>2-2</S>Online</N>100"
tNpcGossip[18797]["OptionPoint224"] = "2-1"
-- 返利令牌(上交)
tNpcGossip[18797]["Text2-3"] = {231}
tNpcGossip[18797]["Text231"] = tOnlineGreatevent_Text[18797]["Text231"]
tNpcGossip[18797]["tOption2-3"] = {231,232,233,234,235,236}
tNpcGossip[18797]["Option231"] = tOnlineGreatevent_Text[18797]["231"]
tNpcGossip[18797]["Option232"] = tOnlineGreatevent_Text[18797]["232"]
tNpcGossip[18797]["Option233"] = tOnlineGreatevent_Text[18797]["233"]
tNpcGossip[18797]["Option234"] = tOnlineGreatevent_Text[18797]["234"]
tNpcGossip[18797]["Option235"] = tOnlineGreatevent_Text[18797]["235"]
tNpcGossip[18797]["Option236"] = tOnlineGreatevent_Text[18797]["236"]
tNpcGossip[18797]["OptionFunc231"] = "OnlineGreatevent_SubToken</N>18797</N>241</S>2-3</S>Recharge</N>50"
tNpcGossip[18797]["OptionFunc232"] = "OnlineGreatevent_SubToken</N>18797</N>241</S>2-3</S>Recharge</N>100"
tNpcGossip[18797]["OptionFunc233"] = "OnlineGreatevent_SubToken</N>18797</N>241</S>2-3</S>Recharge</N>500"
tNpcGossip[18797]["OptionFunc234"] = "OnlineGreatevent_SubToken</N>18797</N>241</S>2-3</S>Recharge</N>1000"
tNpcGossip[18797]["OptionFunc235"] = "OnlineGreatevent_SubToken</N>18797</N>241</S>2-3</S>Recharge</N>10000"
tNpcGossip[18797]["OptionPoint236"] = "2-1"

-- 令牌不足
tNpcGossip[18797]["Text2-5"] = {251}
tNpcGossip[18797]["tOption2-5"] = {251}
tNpcGossip[18797]["Text251"] = tOnlineGreatevent_Text[18797]["Text251"]
tNpcGossip[18797]["Option251"] = tOnlineGreatevent_Text[18797]["251"]

-- 输入字符有误
tNpcGossip[18797]["Text2-6"] = {261}
tNpcGossip[18797]["tOption2-6"] = {261}
tNpcGossip[18797]["Text261"] = tOnlineGreatevent_Text[18797]["Text261"]
tNpcGossip[18797]["Option261"] = tOnlineGreatevent_Text[18797]["261"]
tNpcGossip[18797]["OptionFunc261"] = ""

-- 上交成功
tNpcGossip[18797]["Text2-7"] = {271}
tNpcGossip[18797]["tOption2-7"] = {271}
tNpcGossip[18797]["Text271"] = tOnlineGreatevent_Text[18797]["Text271"]
tNpcGossip[18797]["Option271"] = tOnlineGreatevent_Text[18797]["271"]
tNpcGossip[18797]["OptionFunc271"] = ""


-- 【兑换经验】
-- 兑换类型选择对白
tNpcGossip[18797]["Text3-1"] = {311}
tNpcGossip[18797]["Text311"] = tOnlineGreatevent_Text[18797]["Text311"]
tNpcGossip[18797]["tOption3-1"] = {311,312,313,314}
tNpcGossip[18797]["Option311"] = tOnlineGreatevent_Text[18797]["311"]
tNpcGossip[18797]["Option312"] = tOnlineGreatevent_Text[18797]["312"]
tNpcGossip[18797]["Option313"] = tOnlineGreatevent_Text[18797]["313"]
tNpcGossip[18797]["Option314"] = tOnlineGreatevent_Text[18797]["314"]
tNpcGossip[18797]["Option315"] = tOnlineGreatevent_Text[18797]["315"]
tNpcGossip[18797]["OptionPoint311"] = "3-2"
tNpcGossip[18797]["OptionPoint312"] = "3-3"
tNpcGossip[18797]["OptionFunc313"] = "OnlineGreatevent_SubToken</N>18797</N>351</S>3-1</S>Killing</N>10"
tNpcGossip[18797]["OptionPoint314"] = "1"
tNpcGossip[18797]["OptionChkFunc311"] = function ()
	return User_JudgeLevelAndMetempsychosis(tOnlineGreatevent_Data["MinLevel"],tOnlineGreatevent_Data["MinMeto"])
end

-- 在线令牌(经验)
tNpcGossip[18797]["Text3-2"] = {321,322,323,324}
tNpcGossip[18797]["Text321"] = tOnlineGreatevent_Text[18797]["Text321"]
tNpcGossip[18797]["Text322"] = tOnlineGreatevent_Text[18797]["Text322"]
tNpcGossip[18797]["Text323"] = tOnlineGreatevent_Text[18797]["Text323"]
tNpcGossip[18797]["Text324"] = tOnlineGreatevent_Text[18797]["Text324"]
tNpcGossip[18797]["tOption3-2"] = {321,322,323,324}
tNpcGossip[18797]["Option321"] = tOnlineGreatevent_Text[18797]["321"]
tNpcGossip[18797]["Option322"] = tOnlineGreatevent_Text[18797]["322"]
tNpcGossip[18797]["Option323"] = tOnlineGreatevent_Text[18797]["323"]
tNpcGossip[18797]["Option324"] = tOnlineGreatevent_Text[18797]["324"]
tNpcGossip[18797]["OptionFunc321"] = "OnlineGreatevent_SubToken</N>18797</N>351</S>3-2</S>Online</N>10"
tNpcGossip[18797]["OptionFunc322"] = "OnlineGreatevent_SubToken</N>18797</N>351</S>3-2</S>Online</N>50"
tNpcGossip[18797]["OptionFunc323"] = "OnlineGreatevent_SubToken</N>18797</N>351</S>3-2</S>Online</N>100"
tNpcGossip[18797]["OptionPoint324"] = "3-1"

-- 返利令牌(经验)
tNpcGossip[18797]["Text3-3"] = {331,332,333,334,335,336}
tNpcGossip[18797]["Text331"] = tOnlineGreatevent_Text[18797]["Text331"]
tNpcGossip[18797]["Text332"] = tOnlineGreatevent_Text[18797]["Text332"]
tNpcGossip[18797]["Text333"] = tOnlineGreatevent_Text[18797]["Text333"]
tNpcGossip[18797]["Text334"] = tOnlineGreatevent_Text[18797]["Text334"]
tNpcGossip[18797]["Text335"] = tOnlineGreatevent_Text[18797]["Text335"]
tNpcGossip[18797]["Text336"] = tOnlineGreatevent_Text[18797]["Text336"]
tNpcGossip[18797]["tOption3-3"] = {331,332,333,334,335,336}
tNpcGossip[18797]["Option331"] = tOnlineGreatevent_Text[18797]["331"]
tNpcGossip[18797]["Option332"] = tOnlineGreatevent_Text[18797]["332"]
tNpcGossip[18797]["Option333"] = tOnlineGreatevent_Text[18797]["333"]
tNpcGossip[18797]["Option334"] = tOnlineGreatevent_Text[18797]["334"]
tNpcGossip[18797]["Option335"] = tOnlineGreatevent_Text[18797]["335"]
tNpcGossip[18797]["Option336"] = tOnlineGreatevent_Text[18797]["336"]
tNpcGossip[18797]["OptionFunc331"] = "OnlineGreatevent_SubToken</N>18797</N>351</S>3-3</S>Recharge</N>50"
tNpcGossip[18797]["OptionFunc332"] = "OnlineGreatevent_SubToken</N>18797</N>351</S>3-3</S>Recharge</N>100"
tNpcGossip[18797]["OptionFunc333"] = "OnlineGreatevent_SubToken</N>18797</N>351</S>3-3</S>Recharge</N>500"
tNpcGossip[18797]["OptionFunc334"] = "OnlineGreatevent_SubToken</N>18797</N>351</S>3-3</S>Recharge</N>1000"
tNpcGossip[18797]["OptionFunc335"] = "OnlineGreatevent_SubToken</N>18797</N>351</S>3-3</S>Recharge</N>10000"
tNpcGossip[18797]["OptionPoint336"] = "3-1"

-- 兑换成功(经验)
tNpcGossip[18797]["Text3-4"] = {341}
tNpcGossip[18797]["tOption3-4"] = {341,342}
tNpcGossip[18797]["Text341"] = tOnlineGreatevent_Text[18797]["Text341"]
tNpcGossip[18797]["Option341"] = tOnlineGreatevent_Text[18797]["341"]
tNpcGossip[18797]["Option342"] = tOnlineGreatevent_Text[18797]["342"]
tNpcGossip[18797]["OptionFunc341"] = ""

-- 兑换成功(修行值)
tNpcGossip[18797]["Text3-6"] = {361}
tNpcGossip[18797]["tOption3-6"] = {361,362}
tNpcGossip[18797]["Text361"] = tOnlineGreatevent_Text[18797]["Text361"]
tNpcGossip[18797]["Option361"] = tOnlineGreatevent_Text[18797]["361"]
tNpcGossip[18797]["Option362"] = tOnlineGreatevent_Text[18797]["362"]
tNpcGossip[18797]["OptionFunc361"] = ""

-- 令牌不足
tNpcGossip[18797]["Text3-7"] = {371}
tNpcGossip[18797]["tOption3-7"] = {371}
tNpcGossip[18797]["Text371"] = tOnlineGreatevent_Text[18797]["Text371"]
tNpcGossip[18797]["Option371"] = tOnlineGreatevent_Text[18797]["371"]

-- 输入错误
tNpcGossip[18797]["Text3-8"] = {381}
tNpcGossip[18797]["tOption3-8"] = {381}
tNpcGossip[18797]["Text381"] = tOnlineGreatevent_Text[18797]["Text381"]
tNpcGossip[18797]["Option381"] = tOnlineGreatevent_Text[18797]["381"]
tNpcGossip[18797]["OptionFunc381"] = ""


-- 【了解活动详情】
tNpcGossip[18797]["Text4-1"] = {411,412,413,414}
tNpcGossip[18797]["tOption4-1"] = {411}
tNpcGossip[18797]["Text411"] = tOnlineGreatevent_Text[18797]["Text411"]
tNpcGossip[18797]["Text412"] = tOnlineGreatevent_Text[18797]["Text412"]
tNpcGossip[18797]["Text413"] = tOnlineGreatevent_Text[18797]["Text413"]
tNpcGossip[18797]["Text414"] = tOnlineGreatevent_Text[18797]["Text414"]
tNpcGossip[18797]["Option411"] = tOnlineGreatevent_Text[18797]["411"]
tNpcGossip[18797]["OptionPoint411"] = "4-2"

-- 贼匪魔王是哪些
tNpcGossip[18797]["Text4-2"] = {421,422,423,424,425,426}
tNpcGossip[18797]["tOption4-2"] = {421}
tNpcGossip[18797]["Text421"] = tOnlineGreatevent_Text[18797]["Text421"]
tNpcGossip[18797]["Text422"] = tOnlineGreatevent_Text[18797]["Text422"]
tNpcGossip[18797]["Text423"] = tOnlineGreatevent_Text[18797]["Text423"]
tNpcGossip[18797]["Text424"] = tOnlineGreatevent_Text[18797]["Text424"]
tNpcGossip[18797]["Text425"] = tOnlineGreatevent_Text[18797]["Text425"]
tNpcGossip[18797]["Text426"] = tOnlineGreatevent_Text[18797]["Text426"]
tNpcGossip[18797]["Option421"] = tOnlineGreatevent_Text[18797]["421"]


---------------------------------------物品配置---------------------------------------------
-------------------------------------【积分令牌】---------------------------------------
tItem[3007296] = tItem[3007296] or {}
tItem[3007297] = tItem[3007296] or {}
tItem[3007298] = tItem[3007296] or {}
tItem[3007299] = tItem[3007296] or {}
tItem[3007300] = tItem[3007296] or {}
tItem[3007301] = tItem[3007296] or {}
tItem[3007302] = tItem[3007296] or {}
tItem[3007303] = tItem[3007296] or {}
tItem[3007304] = tItem[3007296] or {}
tItem[3007296]["Function"] = function (nItemId,sItemName)
	--活动时间判断
	if not Sys_ChkFullTime(tOnlineGreatevent_Data["Festival_NowTime"]) then
		if Item_ChkItem(nItemId) and Item_DelAllItemByType(nItemId) then
			Sys_SaveActionFestivalLog(string.format(tOnlineGreatevent_Log["DelItem"],nItemId))
			User_TalkChannel2005(string.format(tOnlineGreatevent_Text["DelToken"],sItemName))
		end
		return
	end
end

-------------------------------------【100*2积分令牌】---------------------------------------
tItem[3007312] = tItem[3007312] or {}
tItem[3007313] = tItem[3007312] or {}
tItem[3007314] = tItem[3007312] or {}
tItem[3007315] = tItem[3007312] or {}
tItem[3007316] = tItem[3007312] or {}
tItem[3007317] = tItem[3007312] or {}
tItem[3007318] = tItem[3007312] or {}
tItem[3007312]["Function"] = function (nItemId,sItemName)
	-- 活动时间判断
	if not Sys_ChkFullTime(tOnlineGreatevent_Data["Festival_NowTime"]) then
		if Item_ChkItem(nItemId) and Item_DelAllItemByType(nItemId) then
			Sys_SaveActionFestivalLog(string.format(tOnlineGreatevent_Log["DelItem"],nItemId))
			User_TalkChannel2005(string.format(tOnlineGreatevent_Text["DelToken"],sItemName))
		end
		return
	end
	
	-- 背包空间
	if not User_CheckLeftSpace(#tOnlineGreatevent_TokenPag[nItemId]) then
		Sys_MsgBox(tOnlineGreatevent_Text["SpaceFull"])
		return
	end
	
	-- 删礼包给物品
	if Item_ChkItem(nItemId) and Item_DelItem(nItemId) then
		local sTalkLink = ""
		local tItemId = {}
		local tItemNum = {}
		local tItemName = {}
		for i,v in pairs (tOnlineGreatevent_TokenPag[nItemId]) do
			local nNewItemId = v["ItemId"]
			local nAddItemNum = v["ItemNum"]
			Item_AddItem(nNewItemId,0,nAddItemNum)
			tItemId[i] = nNewItemId
			tItemNum[i] = nAddItemNum
			tItemName[i] = Get_ItemtypeName(nNewItemId)
		end
		
		if tItemId[2] ~= nil then
			sTalkLink = string.format(tOnlineGreatevent_Text["TokenPagAdd"],tItemNum[2],tItemName[2])
		end
		
		local sLogFormat = string.format(tOnlineGreatevent_Log["TokenPag"],nItemId,tItemId[1],tItemId[2],tItemNum[1],tItemNum[2])
		local sLogText = string.gsub(sLogFormat,"%[nil%]","")
		local sTalkText = string.format(tOnlineGreatevent_Text["TokenPag"],tItemNum[1],tItemName[1],sTalkLink)
		Sys_SaveActionFestivalLog(sLogText)
		User_TalkChannel2005(sTalkText)
	end
end

------------------------------------------怪物配置-------------------------------------------
-- 4171	晶魄雪妖
tMonster[4171] = tMonster[4171] or {}
tMonster[4171]["tFunction"] = tMonster[4171]["tFunction"] or {}
table.insert(tMonster[4171]["tFunction"],OnlineGreatevent_Monster)

-- 4217	禁天妖兽（精英）
tMonster[4217] = tMonster[4217] or {}
tMonster[4217]["tFunction"] = tMonster[4217]["tFunction"] or {}
table.insert(tMonster[4217]["tFunction"],OnlineGreatevent_Monster)

-- 4220	啸海巨魔
tMonster[4220] = tMonster[4220] or {}
tMonster[4220]["tFunction"] = tMonster[4220]["tFunction"] or {}
table.insert(tMonster[4220]["tFunction"],OnlineGreatevent_Monster)

-- 4216	禁天妖兽（困难）
tMonster[4216] = tMonster[4216] or {}
tMonster[4216]["tFunction"] = tMonster[4216]["tFunction"] or {}
table.insert(tMonster[4216]["tFunction"],OnlineGreatevent_Monster)