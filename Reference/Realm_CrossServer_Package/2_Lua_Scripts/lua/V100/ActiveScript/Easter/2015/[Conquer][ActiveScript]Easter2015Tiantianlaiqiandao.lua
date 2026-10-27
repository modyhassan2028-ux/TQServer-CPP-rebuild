------------------------------------------------------------------------------------
--Name:			[征服][活动脚本]复活节天天来签到（4.2-4.8）
--Creator: 		陈浩文
--Created:		2015/01/29
------------------------------------------------------------------------------------
-- 命名前缀
-- Easter2015_Tiantianlaiqiandao_

--活动时间
local tEaster2015_Tiantianlaiqiandao_Time = {}
tEaster2015_Tiantianlaiqiandao_Time["Beftime"]= "2014-01-01 00:00 2015-04-01 23:59"
tEaster2015_Tiantianlaiqiandao_Time["Nowtime"] = "2015-04-02 00:00 2015-04-08 23:59"

--玩家等级要求
tEaster2015_Tiantianlaiqiandao_Condition={}
tEaster2015_Tiantianlaiqiandao_Condition["Metempsychosis"] = 0
tEaster2015_Tiantianlaiqiandao_Condition["Level"] = 80

--活动掩码 13269	13273
--stc(132,69) 1表示完成任务获取奖励
local tEaster2015_Tiantianlaiqiandao_Stc = {}
tEaster2015_Tiantianlaiqiandao_Stc["Tiantianlaiqiandao"]={}
tEaster2015_Tiantianlaiqiandao_Stc["Tiantianlaiqiandao"]["StcEvent"] = 132
tEaster2015_Tiantianlaiqiandao_Stc["Tiantianlaiqiandao"]["StcType"] = 74
tEaster2015_Tiantianlaiqiandao_Stc["Tiantianlaiqiandao"]["Complete"] = 1

-- log表
local tEaster2015_Tiantianlaiqiandao_Log = {}
tEaster2015_Tiantianlaiqiandao_Log["CompleteGetItem"] = "0,0,0,0,12000026,2,%d,1"

-- 光效
tEaster2015_Tiantianlaiqiandao_Effect = {}
tEaster2015_Tiantianlaiqiandao_Effect["Effect"] = "relive"
tEaster2015_Tiantianlaiqiandao_Effect["EffectObj"] = "self"

-- 背包空间
local nUser_CheckLeftSpace = 1

-- 物品
local tEaster2015_Tiantianlaiqiandao_Item = {}
-- 0转
tEaster2015_Tiantianlaiqiandao_Item["Zero"] = {}
tEaster2015_Tiantianlaiqiandao_Item["Zero"][1] = {}
tEaster2015_Tiantianlaiqiandao_Item["Zero"][1]["ItemId"] = 723017 			--昆仑雪水（赠）
tEaster2015_Tiantianlaiqiandao_Item["Zero"][1]["ItemName"] = tEaster2015_Tiantianlaiqiandao_Text["Zero"][1]["ItemName"]
tEaster2015_Tiantianlaiqiandao_Item["Zero"][1]["Monopoly"] = 3
tEaster2015_Tiantianlaiqiandao_Item["Zero"][1]["Chance"] = 20
tEaster2015_Tiantianlaiqiandao_Item["Zero"][2] = {}
tEaster2015_Tiantianlaiqiandao_Item["Zero"][2]["ItemId"] = 723700 			--聚神丹（赠）
tEaster2015_Tiantianlaiqiandao_Item["Zero"][2]["ItemName"] = tEaster2015_Tiantianlaiqiandao_Text["Zero"][2]["ItemName"]
tEaster2015_Tiantianlaiqiandao_Item["Zero"][2]["Monopoly"] = 3
tEaster2015_Tiantianlaiqiandao_Item["Zero"][2]["Chance"] = 20
tEaster2015_Tiantianlaiqiandao_Item["Zero"][3] = {}
tEaster2015_Tiantianlaiqiandao_Item["Zero"][3]["ItemId"] = 1200000 			--小祈愿石（赠）
tEaster2015_Tiantianlaiqiandao_Item["Zero"][3]["ItemName"] = tEaster2015_Tiantianlaiqiandao_Text["Zero"][3]["ItemName"]
tEaster2015_Tiantianlaiqiandao_Item["Zero"][3]["Monopoly"] = 3
tEaster2015_Tiantianlaiqiandao_Item["Zero"][3]["Chance"] = 20
tEaster2015_Tiantianlaiqiandao_Item["Zero"][4] = {}
tEaster2015_Tiantianlaiqiandao_Item["Zero"][4]["ItemId"] = 723341 			--玄灵秘录（赠）
tEaster2015_Tiantianlaiqiandao_Item["Zero"][4]["ItemName"] = tEaster2015_Tiantianlaiqiandao_Text["Zero"][4]["ItemName"]
tEaster2015_Tiantianlaiqiandao_Item["Zero"][4]["Monopoly"] = 3
tEaster2015_Tiantianlaiqiandao_Item["Zero"][4]["Chance"] = 20
tEaster2015_Tiantianlaiqiandao_Item["Zero"][5] = {}
tEaster2015_Tiantianlaiqiandao_Item["Zero"][5]["ItemId"] = 720828 			--记忆宝珠（赠）
tEaster2015_Tiantianlaiqiandao_Item["Zero"][5]["ItemName"] = tEaster2015_Tiantianlaiqiandao_Text["Zero"][5]["ItemName"]
tEaster2015_Tiantianlaiqiandao_Item["Zero"][5]["Monopoly"] = 3
tEaster2015_Tiantianlaiqiandao_Item["Zero"][5]["Chance"] = 2 
tEaster2015_Tiantianlaiqiandao_Item["Zero"][6] = {}
tEaster2015_Tiantianlaiqiandao_Item["Zero"][6]["ItemId"] = 3001265 			--一级神魂礼包（赠）
tEaster2015_Tiantianlaiqiandao_Item["Zero"][6]["ItemName"] = tEaster2015_Tiantianlaiqiandao_Text["Zero"][6]["ItemName"]
tEaster2015_Tiantianlaiqiandao_Item["Zero"][6]["Monopoly"] = 3
tEaster2015_Tiantianlaiqiandao_Item["Zero"][6]["Chance"] = 8 
tEaster2015_Tiantianlaiqiandao_Item["Zero"][7] = {}
tEaster2015_Tiantianlaiqiandao_Item["Zero"][7]["ItemId"] = 3003629 			--1级淬炼礼包（赠）
tEaster2015_Tiantianlaiqiandao_Item["Zero"][7]["ItemName"] = tEaster2015_Tiantianlaiqiandao_Text["Zero"][7]["ItemName"]
tEaster2015_Tiantianlaiqiandao_Item["Zero"][7]["Monopoly"] = 3
tEaster2015_Tiantianlaiqiandao_Item["Zero"][7]["Chance"] = 8 
tEaster2015_Tiantianlaiqiandao_Item["Zero"][8] = {}
tEaster2015_Tiantianlaiqiandao_Item["Zero"][8]["ItemId"] = 710214 			--万商名典（赠）
tEaster2015_Tiantianlaiqiandao_Item["Zero"][8]["ItemName"] = tEaster2015_Tiantianlaiqiandao_Text["Zero"][8]["ItemName"]
tEaster2015_Tiantianlaiqiandao_Item["Zero"][8]["Monopoly"] = 3
tEaster2015_Tiantianlaiqiandao_Item["Zero"][8]["Chance"] = 2 
-- 1转
tEaster2015_Tiantianlaiqiandao_Item["One"] = {}
tEaster2015_Tiantianlaiqiandao_Item["One"][1] = {}
tEaster2015_Tiantianlaiqiandao_Item["One"][1]["ItemId"] = 723017 			--昆仑雪水（赠）
tEaster2015_Tiantianlaiqiandao_Item["One"][1]["ItemName"] = tEaster2015_Tiantianlaiqiandao_Text["One"][1]["ItemName"]
tEaster2015_Tiantianlaiqiandao_Item["One"][1]["Monopoly"] = 3
tEaster2015_Tiantianlaiqiandao_Item["One"][1]["Chance"] = 20
tEaster2015_Tiantianlaiqiandao_Item["One"][2] = {}
tEaster2015_Tiantianlaiqiandao_Item["One"][2]["ItemId"] = 723700 			--聚神丹（赠）
tEaster2015_Tiantianlaiqiandao_Item["One"][2]["ItemName"] = tEaster2015_Tiantianlaiqiandao_Text["One"][2]["ItemName"]
tEaster2015_Tiantianlaiqiandao_Item["One"][2]["Monopoly"] = 3
tEaster2015_Tiantianlaiqiandao_Item["One"][2]["Chance"] = 20
tEaster2015_Tiantianlaiqiandao_Item["One"][3] = {}
tEaster2015_Tiantianlaiqiandao_Item["One"][3]["ItemId"] = 1200000 			--小祈愿石（赠）
tEaster2015_Tiantianlaiqiandao_Item["One"][3]["ItemName"] = tEaster2015_Tiantianlaiqiandao_Text["One"][3]["ItemName"]
tEaster2015_Tiantianlaiqiandao_Item["One"][3]["Monopoly"] = 3
tEaster2015_Tiantianlaiqiandao_Item["One"][3]["Chance"] = 20
tEaster2015_Tiantianlaiqiandao_Item["One"][4] = {}
tEaster2015_Tiantianlaiqiandao_Item["One"][4]["ItemId"] = 723341 			--玄灵秘录（赠）
tEaster2015_Tiantianlaiqiandao_Item["One"][4]["ItemName"] = tEaster2015_Tiantianlaiqiandao_Text["One"][4]["ItemName"]
tEaster2015_Tiantianlaiqiandao_Item["One"][4]["Monopoly"] = 3
tEaster2015_Tiantianlaiqiandao_Item["One"][4]["Chance"] = 20
tEaster2015_Tiantianlaiqiandao_Item["One"][5] = {}
tEaster2015_Tiantianlaiqiandao_Item["One"][5]["ItemId"] = 720828 			--记忆宝珠（赠）
tEaster2015_Tiantianlaiqiandao_Item["One"][5]["ItemName"] = tEaster2015_Tiantianlaiqiandao_Text["One"][5]["ItemName"]
tEaster2015_Tiantianlaiqiandao_Item["One"][5]["Monopoly"] = 3
tEaster2015_Tiantianlaiqiandao_Item["One"][5]["Chance"] = 2 
tEaster2015_Tiantianlaiqiandao_Item["One"][6] = {}
tEaster2015_Tiantianlaiqiandao_Item["One"][6]["ItemId"] = 3000107 			--精致神魂礼包（赠）
tEaster2015_Tiantianlaiqiandao_Item["One"][6]["ItemName"] = tEaster2015_Tiantianlaiqiandao_Text["One"][6]["ItemName"]
tEaster2015_Tiantianlaiqiandao_Item["One"][6]["Monopoly"] = 3
tEaster2015_Tiantianlaiqiandao_Item["One"][6]["Chance"] = 8 
tEaster2015_Tiantianlaiqiandao_Item["One"][7] = {}
tEaster2015_Tiantianlaiqiandao_Item["One"][7]["ItemId"] = 720399 			--高级淬炼礼包（赠）
tEaster2015_Tiantianlaiqiandao_Item["One"][7]["ItemName"] = tEaster2015_Tiantianlaiqiandao_Text["One"][7]["ItemName"]
tEaster2015_Tiantianlaiqiandao_Item["One"][7]["Monopoly"] = 3
tEaster2015_Tiantianlaiqiandao_Item["One"][7]["Chance"] = 8 
tEaster2015_Tiantianlaiqiandao_Item["One"][8] = {}
tEaster2015_Tiantianlaiqiandao_Item["One"][8]["ItemId"] = 710214 			--万商名典（赠）
tEaster2015_Tiantianlaiqiandao_Item["One"][8]["ItemName"] = tEaster2015_Tiantianlaiqiandao_Text["One"][8]["ItemName"]
tEaster2015_Tiantianlaiqiandao_Item["One"][8]["Monopoly"] = 3
tEaster2015_Tiantianlaiqiandao_Item["One"][8]["Chance"] = 2 
-- 2转
tEaster2015_Tiantianlaiqiandao_Item["Two"] = {}
tEaster2015_Tiantianlaiqiandao_Item["Two"][1] = {}
tEaster2015_Tiantianlaiqiandao_Item["Two"][1]["ItemId"] = 723017 			--昆仑雪水（赠）
tEaster2015_Tiantianlaiqiandao_Item["Two"][1]["ItemName"] = tEaster2015_Tiantianlaiqiandao_Text["Two"][1]["ItemName"]
tEaster2015_Tiantianlaiqiandao_Item["Two"][1]["Monopoly"] = 3
tEaster2015_Tiantianlaiqiandao_Item["Two"][1]["Chance"] = 20
tEaster2015_Tiantianlaiqiandao_Item["Two"][2] = {}
tEaster2015_Tiantianlaiqiandao_Item["Two"][2]["ItemId"] = 723700 			--聚神丹（赠）
tEaster2015_Tiantianlaiqiandao_Item["Two"][2]["ItemName"] = tEaster2015_Tiantianlaiqiandao_Text["Two"][2]["ItemName"]
tEaster2015_Tiantianlaiqiandao_Item["Two"][2]["Monopoly"] = 3
tEaster2015_Tiantianlaiqiandao_Item["Two"][2]["Chance"] = 20
tEaster2015_Tiantianlaiqiandao_Item["Two"][3] = {}
tEaster2015_Tiantianlaiqiandao_Item["Two"][3]["ItemId"] = 1200001 			--大祈愿石（赠）
tEaster2015_Tiantianlaiqiandao_Item["Two"][3]["ItemName"] = tEaster2015_Tiantianlaiqiandao_Text["Two"][3]["ItemName"]
tEaster2015_Tiantianlaiqiandao_Item["Two"][3]["Monopoly"] = 3
tEaster2015_Tiantianlaiqiandao_Item["Two"][3]["Chance"] = 20
tEaster2015_Tiantianlaiqiandao_Item["Two"][4] = {}
tEaster2015_Tiantianlaiqiandao_Item["Two"][4]["ItemId"] = 723341 			--玄灵秘录（赠）
tEaster2015_Tiantianlaiqiandao_Item["Two"][4]["ItemName"] = tEaster2015_Tiantianlaiqiandao_Text["Two"][4]["ItemName"]
tEaster2015_Tiantianlaiqiandao_Item["Two"][4]["Monopoly"] = 3
tEaster2015_Tiantianlaiqiandao_Item["Two"][4]["Chance"] = 20
tEaster2015_Tiantianlaiqiandao_Item["Two"][5] = {}
tEaster2015_Tiantianlaiqiandao_Item["Two"][5]["ItemId"] = 720828 			--记忆宝珠（赠）
tEaster2015_Tiantianlaiqiandao_Item["Two"][5]["ItemName"] = tEaster2015_Tiantianlaiqiandao_Text["Two"][5]["ItemName"]
tEaster2015_Tiantianlaiqiandao_Item["Two"][5]["Monopoly"] = 3
tEaster2015_Tiantianlaiqiandao_Item["Two"][5]["Chance"] = 3
tEaster2015_Tiantianlaiqiandao_Item["Two"][6] = {}
tEaster2015_Tiantianlaiqiandao_Item["Two"][6]["ItemId"] = 3000107 			--精致神魂礼包（赠）
tEaster2015_Tiantianlaiqiandao_Item["Two"][6]["ItemName"] = tEaster2015_Tiantianlaiqiandao_Text["Two"][6]["ItemName"]
tEaster2015_Tiantianlaiqiandao_Item["Two"][6]["Monopoly"] = 3
tEaster2015_Tiantianlaiqiandao_Item["Two"][6]["Chance"] = 8
tEaster2015_Tiantianlaiqiandao_Item["Two"][7] = {}
tEaster2015_Tiantianlaiqiandao_Item["Two"][7]["ItemId"] = 720399 			--高级淬炼礼包（赠）
tEaster2015_Tiantianlaiqiandao_Item["Two"][7]["ItemName"] = tEaster2015_Tiantianlaiqiandao_Text["Two"][7]["ItemName"]
tEaster2015_Tiantianlaiqiandao_Item["Two"][7]["Monopoly"] = 3
tEaster2015_Tiantianlaiqiandao_Item["Two"][7]["Chance"] = 8
tEaster2015_Tiantianlaiqiandao_Item["Two"][8] = {}
tEaster2015_Tiantianlaiqiandao_Item["Two"][8]["ItemId"] = 1100003 			--小乾坤袋（赠）
tEaster2015_Tiantianlaiqiandao_Item["Two"][8]["ItemName"] = tEaster2015_Tiantianlaiqiandao_Text["Two"][8]["ItemName"]
tEaster2015_Tiantianlaiqiandao_Item["Two"][8]["Monopoly"] = 3
tEaster2015_Tiantianlaiqiandao_Item["Two"][8]["Chance"] = 1

------------------------------------------------------------------------------------
------------------------------------------
-- STC掩码隔天重置
function Easter2015_Tiantianlaiqiandao_ChkStc()
	local nEvent = tEaster2015_Tiantianlaiqiandao_Stc["Tiantianlaiqiandao"]["StcEvent"]
	local nType = tEaster2015_Tiantianlaiqiandao_Stc["Tiantianlaiqiandao"]["StcType"]
	if Task_StcInterval(nEvent,nType,1,4) then
		Task_SetStatistic(nEvent,nType,0,1)
		Task_SetStcTimestamp(nEvent,nType,0)
	end
end

------------------------------------------
-- 通过STC掩码判断当天是否完成签到
function Easter2015_Tiantianlaiqiandao_ChkComplete()
	local nEvent = tEaster2015_Tiantianlaiqiandao_Stc["Tiantianlaiqiandao"]["StcEvent"]
	local nType = tEaster2015_Tiantianlaiqiandao_Stc["Tiantianlaiqiandao"]["StcType"]
	local nComplete = tEaster2015_Tiantianlaiqiandao_Stc["Tiantianlaiqiandao"]["Complete"]
	Easter2015_Tiantianlaiqiandao_ChkStc()
	return Task_ChkStcValue(nEvent,nType,"==",nComplete)
end

------------------------------------------
--根据转世情况得到奖励
function Easter2015_Tiantianlaiqiandao_GetItem()
	local nEvent = tEaster2015_Tiantianlaiqiandao_Stc["Tiantianlaiqiandao"]["StcEvent"]
	local nType = tEaster2015_Tiantianlaiqiandao_Stc["Tiantianlaiqiandao"]["StcType"]
	local nComplete = tEaster2015_Tiantianlaiqiandao_Stc["Tiantianlaiqiandao"]["Complete"]
	local nMetempsychosis = Get_UserMetempsychosis()
	local nItemId 
	local nItemName
	local nMonopoly
	local nCompleteGetItem
	local nNum = math.random(1,100)
	local nSum = 0
	local sIndex
	if nMetempsychosis == 0 then 
		sIndex = "Zero"
	elseif nMetempsychosis == 1 then 
		sIndex = "One"
	elseif nMetempsychosis >= 2 then 
		sIndex = "Two"
	end
	
	for nIndex =1 , 8 do 
		nSum = nSum + tEaster2015_Tiantianlaiqiandao_Item[sIndex][nIndex]["Chance"]
		if nNum <= nSum then
			Task_SetStatistic(nEvent,nType,nComplete,1)
			Task_SetStcTimestamp(nEvent,nType,0)
			nItemId = tEaster2015_Tiantianlaiqiandao_Item[sIndex][nIndex]["ItemId"]
			nItemName = tEaster2015_Tiantianlaiqiandao_Item[sIndex][nIndex]["ItemName"]
			nMonopoly = tEaster2015_Tiantianlaiqiandao_Item[sIndex][nIndex]["Monopoly"]
			Item_AddItem(nItemId,0,1,nMonopoly)
			Sys_SaveActionFestivalLog(string.format(tEaster2015_Tiantianlaiqiandao_Log["CompleteGetItem"],nItemId))
			User_TalkChannel2005(string.format(tEaster2015_Tiantianlaiqiandao_Text["TalkChannel2005"]["Get"],nItemName) )
			User_EffectAdd(tEaster2015_Tiantianlaiqiandao_Effect["EffectObj"],tEaster2015_Tiantianlaiqiandao_Effect["Effect"])
			return
		end
	end
end

------------------------------------------
--我要签到抽奖
function Easter2015_Tiantianlaiqiandao_Option14_10826(nNpcId)
	
	local nLevel = tEaster2015_Tiantianlaiqiandao_Condition["Level"]
	local nMetempsychosis = tEaster2015_Tiantianlaiqiandao_Condition["Metempsychosis"]
	local nEvent = tEaster2015_Tiantianlaiqiandao_Stc["Tiantianlaiqiandao"]["StcEvent"]
	local nType = tEaster2015_Tiantianlaiqiandao_Stc["Tiantianlaiqiandao"]["StcType"]
	local nComplete = tEaster2015_Tiantianlaiqiandao_Stc["Tiantianlaiqiandao"]["Complete"]
	
	Easter2015_Tiantianlaiqiandao_ChkStc()
	--等级不足
	if not User_JudgeLevelAndMetempsychosis(nLevel,nMetempsychosis) then
		LinkNpcGossipFunc_New(nNpcId,"2-1")
		return
	end
	--今日已签到
	if Task_ChkStcValue(nEvent,nType,"==",nComplete) then
		LinkNpcGossipFunc_New(nNpcId,"1-3")
		return
	end
	--背包空间不足
	if not User_CheckLeftSpace(nUser_CheckLeftSpace) then
		User_TalkChannel2005(tEaster2015_Tiantianlaiqiandao_Text["TalkChannel2005"]["NoLeftSpace"])
		return
	end
	
	--成功得到奖励
	Easter2015_Tiantianlaiqiandao_GetItem()
	
end

---------------------------------------------------对话模板部分-----------------------------------------
-- //双龙城 签到使天天
tNpcFace[3542] = 170
tNpcGossip[10826] = tNpcGossip[10826] or DefaultNpc:new{}
tNpcGossip[10826]["OptionHidden"] = 1

--对白
tNpcGossip[10826]["Text1-1"] = {111,112}				-- 活动前
tNpcGossip[10826]["Text1-2"] = {121,122}				-- 活动后
tNpcGossip[10826]["Text1-3"] = {131}					-- 活动中 已签到抽奖
tNpcGossip[10826]["Text1-4"] = {141,142,143}			-- 活动中 没有签到抽奖
tNpcGossip[10826]["Text2-1"] = {211}					-- 当天已获得过礼包
tNpcGossip[10826]["Text111"] = tEaster2015_Tiantianlaiqiandao_Text[10826]["Text111"]
tNpcGossip[10826]["Text112"] = tEaster2015_Tiantianlaiqiandao_Text[10826]["Text112"]
tNpcGossip[10826]["Text121"] = tEaster2015_Tiantianlaiqiandao_Text[10826]["Text121"]
tNpcGossip[10826]["Text122"] = tEaster2015_Tiantianlaiqiandao_Text[10826]["Text122"]
tNpcGossip[10826]["Text131"] = tEaster2015_Tiantianlaiqiandao_Text[10826]["Text131"]
tNpcGossip[10826]["Text141"] = tEaster2015_Tiantianlaiqiandao_Text[10826]["Text141"]
tNpcGossip[10826]["Text142"] = tEaster2015_Tiantianlaiqiandao_Text[10826]["Text142"]
tNpcGossip[10826]["Text143"] = tEaster2015_Tiantianlaiqiandao_Text[10826]["Text143"]
tNpcGossip[10826]["Text211"] = tEaster2015_Tiantianlaiqiandao_Text[10826]["Text211"]

-- 活动前
tNpcGossip[10826]["ChkFunc1-1"] = function ()
	return Sys_ChkFullTime(tEaster2015_Tiantianlaiqiandao_Time["Beftime"])
end

-- 活动后
tNpcGossip[10826]["ChkFunc1-2"] = function ()
	return not Sys_ChkFullTime(tEaster2015_Tiantianlaiqiandao_Time["Nowtime"])
end

-- 活动中 已签到抽奖
tNpcGossip[10826]["ChkFunc1-3"] = function ()
	return Sys_ChkFullTime(tEaster2015_Tiantianlaiqiandao_Time["Nowtime"]) and Easter2015_Tiantianlaiqiandao_ChkComplete()
end

-- 活动中 没有签到抽奖
tNpcGossip[10826]["ChkFunc1-4"] = function ()
	return Sys_ChkFullTime(tEaster2015_Tiantianlaiqiandao_Time["Nowtime"]) and (not Easter2015_Tiantianlaiqiandao_ChkComplete())
end

--选项
tNpcGossip[10826]["tOption1-1"] = {11}
tNpcGossip[10826]["tOption1-2"] = {12}
tNpcGossip[10826]["tOption1-3"] = {13}
tNpcGossip[10826]["tOption1-4"] = {14,15}
tNpcGossip[10826]["tOption2-1"] = {21}
tNpcGossip[10826]["Option11"] = tEaster2015_Tiantianlaiqiandao_Text[10826]["Option11"]
tNpcGossip[10826]["Option12"] = tEaster2015_Tiantianlaiqiandao_Text[10826]["Option12"]
tNpcGossip[10826]["Option13"] = tEaster2015_Tiantianlaiqiandao_Text[10826]["Option13"]
tNpcGossip[10826]["Option14"] = tEaster2015_Tiantianlaiqiandao_Text[10826]["Option14"]
tNpcGossip[10826]["Option15"] = tEaster2015_Tiantianlaiqiandao_Text[10826]["Option15"]
tNpcGossip[10826]["Option21"] = tEaster2015_Tiantianlaiqiandao_Text[10826]["Option21"]
tNpcGossip[10826]["OptionFunc14"]="Easter2015_Tiantianlaiqiandao_Option14_10826</N>10826"

