------------------------------------------------------------------------------------
--Name:		[征服][任务脚本]战力锦标赛
--Purpose:	战力锦标赛
--Creator: 	丁晨
--Created:	2015/06/20
------------------------------------------------------------------------------------
--任务需求：
---选择战力段进入赛场，互相PK直至场内仅自己一人胜出
------------------------------------------------------------------------------------
--命名规范
--PowerChampionships_Match

--美服 欧服 区分掩码 你懂的
local tPowerChampionships_Match_DynaData ={}
	tPowerChampionships_Match_DynaData["DynaId"] = 50920
	tPowerChampionships_Match_DynaData["DynaValue"] = 0

--美服
local tPowerChampionships_Match_Activity ={}
	tPowerChampionships_Match_Activity["BefTime"] = "2015-02-25 00:00 2015-07-11 23:59"
	
	
	tPowerChampionships_Match_Activity["JoinTime"] ={}
	tPowerChampionships_Match_Activity["JoinTime"][1] ="2015-07-12 19:45 2015-07-12 19:59"
	tPowerChampionships_Match_Activity["JoinTime"][2] ="2015-07-19 19:45 2015-07-19 19:59"
	tPowerChampionships_Match_Activity["JoinTime"][3] ="2015-07-26 19:45 2015-07-26 19:59"
	tPowerChampionships_Match_Activity["JoinTime"][4] ="2015-08-02 19:45 2015-08-02 19:59"
	
	tPowerChampionships_Match_Activity["ActTime"] ={}
	tPowerChampionships_Match_Activity["ActTime"][1] ="2015-07-12 20:00 2015-07-12 20:59"
	tPowerChampionships_Match_Activity["ActTime"][2] ="2015-07-19 20:00 2015-07-19 20:59"
	tPowerChampionships_Match_Activity["ActTime"][3] ="2015-07-26 20:00 2015-07-26 20:59"
	tPowerChampionships_Match_Activity["ActTime"][4] ="2015-08-02 20:00 2015-08-02 20:59"
	
	tPowerChampionships_Match_Activity["KickTime"] ={}
	tPowerChampionships_Match_Activity["KickTime"][1] ="2015-07-12 21:00 2015-07-12 21:05"
	tPowerChampionships_Match_Activity["KickTime"][2] ="2015-07-19 21:00 2015-07-19 21:05"
	tPowerChampionships_Match_Activity["KickTime"][3] ="2015-07-26 21:00 2015-07-26 21:05"
	tPowerChampionships_Match_Activity["KickTime"][4] ="2015-08-02 21:00 2015-08-02 21:05"
	
	tPowerChampionships_Match_Activity["AftTime"] = "2015-08-02 21:00 2016-12-11 23:59"

--欧服
local tPowerChampionships_Match_ActivityEurope = {}

	tPowerChampionships_Match_ActivityEurope["BefTime"] = "2015-02-25 00:00 2015-07-11 23:59"
	
	
	tPowerChampionships_Match_ActivityEurope["JoinTime"] ={}
	tPowerChampionships_Match_ActivityEurope["JoinTime"][1] ="2015-07-12 21:45 2015-07-12 21:59"
	tPowerChampionships_Match_ActivityEurope["JoinTime"][2] ="2015-07-19 21:45 2015-07-19 21:59"
	tPowerChampionships_Match_ActivityEurope["JoinTime"][3] ="2015-07-26 21:45 2015-07-26 21:59"
	tPowerChampionships_Match_ActivityEurope["JoinTime"][4] ="2015-08-02 21:45 2015-08-02 21:59"
	
	tPowerChampionships_Match_ActivityEurope["ActTime"] ={}
	tPowerChampionships_Match_ActivityEurope["ActTime"][1] ="2015-07-12 22:00 2015-07-12 22:59"
	tPowerChampionships_Match_ActivityEurope["ActTime"][2] ="2015-07-19 22:00 2015-07-19 22:59"
	tPowerChampionships_Match_ActivityEurope["ActTime"][3] ="2015-07-26 22:00 2015-07-26 22:59"
	tPowerChampionships_Match_ActivityEurope["ActTime"][4] ="2015-08-02 22:00 2015-08-02 22:59"
	
	tPowerChampionships_Match_ActivityEurope["KickTime"] ={}
	tPowerChampionships_Match_ActivityEurope["KickTime"][1] ="2015-07-12 23:00 2015-07-12 23:05"
	tPowerChampionships_Match_ActivityEurope["KickTime"][2] ="2015-07-19 23:00 2015-07-19 23:05"
	tPowerChampionships_Match_ActivityEurope["KickTime"][3] ="2015-07-26 23:00 2015-07-26 23:05"
	tPowerChampionships_Match_ActivityEurope["KickTime"][4] ="2015-08-02 23:00 2015-08-02 23:05"
	
	tPowerChampionships_Match_ActivityEurope["AftTime"] = "2015-08-02 23:00 2016-12-11 23:59"

--地图存活限制
local tPowerChampionships_Match_Alive = {}
	tPowerChampionships_Match_Alive["AliveLimit"] = 1
	tPowerChampionships_Match_Alive["IsAlive"] = 1
	
--战力奖励配置表
local tPowerChampionships_Match_Power = {}

	--传送进地图后点 
	tPowerChampionships_Match_Power["PosX"] = 36
	tPowerChampionships_Match_Power["PosY"] = 19
	tPowerChampionships_Match_Power["Bound"] = 20
	
	--战力范围
	tPowerChampionships_Match_Power[1]={}
	tPowerChampionships_Match_Power[1]["UpPower"] = 250
	tPowerChampionships_Match_Power[1]["DownPower"] = 300
	tPowerChampionships_Match_Power[1]["MapId"] = 3950
	tPowerChampionships_Match_Power[1]["ItemId"] = 3006840
	
	--蝉联冠军
	tPowerChampionships_Match_Power[1]["ClPower"]={}
	tPowerChampionships_Match_Power[1]["ClPower"][1] = 5000
	tPowerChampionships_Match_Power[1]["ClPower"][2] = 10000
	tPowerChampionships_Match_Power[1]["ClPower"][3] = 20000
	
	tPowerChampionships_Match_Power[2]={}
	tPowerChampionships_Match_Power[2]["UpPower"] = 301
	tPowerChampionships_Match_Power[2]["DownPower"] = 350
	tPowerChampionships_Match_Power[2]["MapId"] = 3951
	tPowerChampionships_Match_Power[2]["ItemId"] = 3006841
	
	
	tPowerChampionships_Match_Power[2]["ClPower"]={}
	tPowerChampionships_Match_Power[2]["ClPower"][1] = 10000
	tPowerChampionships_Match_Power[2]["ClPower"][2] = 20000
	tPowerChampionships_Match_Power[2]["ClPower"][3] = 30000
	
	tPowerChampionships_Match_Power[3]={}
	tPowerChampionships_Match_Power[3]["UpPower"] = 351
	tPowerChampionships_Match_Power[3]["DownPower"] = 5000
	tPowerChampionships_Match_Power[3]["MapId"] = 3952
	tPowerChampionships_Match_Power[3]["ItemId"] = 3006842
	
	tPowerChampionships_Match_Power[3]["ClPower"]={}
	tPowerChampionships_Match_Power[3]["ClPower"][1] = 20000
	tPowerChampionships_Match_Power[3]["ClPower"][2] = 30000
	tPowerChampionships_Match_Power[3]["ClPower"][3] = 50000
	
--返回双龙城
local tPowerChampionships_Match_BackCity = {}
	tPowerChampionships_Match_BackCity["MapId"] = 1002
	tPowerChampionships_Match_BackCity["PosX"] = 304
	tPowerChampionships_Match_BackCity["PosY"] = 262
	tPowerChampionships_Match_BackCity["Bound"] = 10
	
--地图检测
local tPowerChampionships_Match_MapChk = {}
	tPowerChampionships_Match_MapChk["MapId"] = {}
	tPowerChampionships_Match_MapChk["MapId"][1] = 3950
	tPowerChampionships_Match_MapChk["MapId"][2] = 3951
	tPowerChampionships_Match_MapChk["MapId"][3] = 3952
	
	
--NPC领奖员奖励配置
local tPowerChampionships_Match_GjReward = {}
	--冠军
	tPowerChampionships_Match_GjReward[3950] = {}
	--天石
	tPowerChampionships_Match_GjReward[3950]["Cp"] = 300
	--气力值
	tPowerChampionships_Match_GjReward[3950]["Power"] = 5000
	--普通战力令牌
	tPowerChampionships_Match_GjReward[3950]["ItemId"] = 3006840
	
	
	--冠军
	tPowerChampionships_Match_GjReward[3951] = {}
	--天石
	tPowerChampionships_Match_GjReward[3951]["Cp"] = 500
	--气力值
	tPowerChampionships_Match_GjReward[3951]["Power"] = 10000
	--中级战力令牌
	tPowerChampionships_Match_GjReward[3951]["ItemId"] = 3006841
	
	
	--冠军
	tPowerChampionships_Match_GjReward[3952] = {}
	--天石
	tPowerChampionships_Match_GjReward[3952]["Cp"] = 1000
	--气力值
	tPowerChampionships_Match_GjReward[3952]["Power"] = 15000
	--高级战力令牌
	tPowerChampionships_Match_GjReward[3952]["ItemId"] = 3006842
	

	
--冠军光环配置
local tPowerChampionships_Match_GjEffect ={}
	tPowerChampionships_Match_GjEffect["Status"] = 45
	tPowerChampionships_Match_GjEffect["Power"] = 200
	tPowerChampionships_Match_GjEffect["Secs"] = 604800
	tPowerChampionships_Match_GjEffect["Times"] = 1
	tPowerChampionships_Match_GjEffect["RemainTime"] = 2
	tPowerChampionships_Match_GjEffect["EndTime"] = 1
	tPowerChampionships_Match_GjEffect["Recordable"] = 1
	
--背包信
local tPowerChampionships_Match_Letter = {}
	tPowerChampionships_Match_Letter["ItemId"] = 3006839
	tPowerChampionships_Match_Letter["Exp"]	= 30
	tPowerChampionships_Match_Letter["Cul"]	=15
	
--各种限制
local tPowerChampionships_Match_Limit = {}
	tPowerChampionships_Match_Limit["CpTop"] = 999999999
	tPowerChampionships_Match_Limit["Bag"] = 1
	tPowerChampionships_Match_Limit["Level"] = 140
	
--全服邀请设置
local tPowerChampionships_Match_Invite ={}
	tPowerChampionships_Match_Invite["MapId"] = 1002
	tPowerChampionships_Match_Invite["Activity_Invite"] = "battlelev >= 250"
	tPowerChampionships_Match_Invite["Activity_InviteId"] = 1
	--全服邀请任意8个点
	tPowerChampionships_Match_Invite["Invite_Pos"] ={}
	tPowerChampionships_Match_Invite["Invite_Pos"][1] = {}
	tPowerChampionships_Match_Invite["Invite_Pos"][1]["X"] = 289
	tPowerChampionships_Match_Invite["Invite_Pos"][1]["Y"] = 151
	
	tPowerChampionships_Match_Invite["Invite_Pos"][2] = {}
	tPowerChampionships_Match_Invite["Invite_Pos"][2]["X"] = 296
	tPowerChampionships_Match_Invite["Invite_Pos"][2]["Y"] = 150
	
	tPowerChampionships_Match_Invite["Invite_Pos"][3] = {}
	tPowerChampionships_Match_Invite["Invite_Pos"][3]["X"] = 300
	tPowerChampionships_Match_Invite["Invite_Pos"][3]["Y"] = 148
	
	tPowerChampionships_Match_Invite["Invite_Pos"][4] = {}
	tPowerChampionships_Match_Invite["Invite_Pos"][4]["X"] = 303
	tPowerChampionships_Match_Invite["Invite_Pos"][4]["Y"] = 147
	
	tPowerChampionships_Match_Invite["Invite_Pos"][5] = {}
	tPowerChampionships_Match_Invite["Invite_Pos"][5]["X"] = 299
	tPowerChampionships_Match_Invite["Invite_Pos"][5]["Y"] = 153
	
	tPowerChampionships_Match_Invite["Invite_Pos"][6] = {}
	tPowerChampionships_Match_Invite["Invite_Pos"][6]["X"] = 293
	tPowerChampionships_Match_Invite["Invite_Pos"][6]["Y"] = 152
	
	tPowerChampionships_Match_Invite["Invite_Pos"][7] = {}
	tPowerChampionships_Match_Invite["Invite_Pos"][7]["X"] = 292
	tPowerChampionships_Match_Invite["Invite_Pos"][7]["Y"] = 146
	
	tPowerChampionships_Match_Invite["Invite_Pos"][8] = {}
	tPowerChampionships_Match_Invite["Invite_Pos"][8]["X"] = 302
	tPowerChampionships_Match_Invite["Invite_Pos"][8]["Y"] = 145
	
	--全服邀请对白
	tPowerChampionships_Match_Invite["InviteSendId"] = 10517
	tPowerChampionships_Match_Invite["InviteSendOkId"] = 10518
	
	--全服邀请倒计时
	tPowerChampionships_Match_Invite["InviteCountDown"] = 30

--Stc掩码 背包信
local tPowerChampionships_Match_Stc={}
	tPowerChampionships_Match_Stc["EventType"] = 135
	tPowerChampionships_Match_Stc["DataType"] = 41
	
--自动寻路
local tPowerChampionships_Match_FindWay={}
	tPowerChampionships_Match_FindWay["MapId"] = 1002
	tPowerChampionships_Match_FindWay["PosX"] = 295
	tPowerChampionships_Match_FindWay["PosY"] = 141
	tPowerChampionships_Match_FindWay["NpcId"] = 18662

	
--全服冠军掩码
local tPowerChampionships_Match_dynaData={}
	tPowerChampionships_Match_dynaData["global_Id"] = 50916
	
--各种光效
local tPowerChampionships_Match_Effect={}
	tPowerChampionships_Match_Effect["Effect"] ="SuperXp-6"
	tPowerChampionships_Match_Effect["ScrEffect"] =4
	
--log
local tPowerChampionships_Match_Log = {}
	--光环LOG
	tPowerChampionships_Match_Log["EMap_File"] = "bat_jbs"
	tPowerChampionships_Match_Log["EMap_Text"] = tPowerChampionships_Match_Text["BattleEffect"]
	
	--进地图
	tPowerChampionships_Match_Log["EMap_Site"] = "0,0,0,0,18000058,1,%s,0"
	
	--奖励
	tPowerChampionships_Match_Log["EMap_Reward"]= "0,0,0,0,18000059,1,%s,%s"
	
	tPowerChampionships_Match_Log["EMap_Reward1"]= "0,0,0,0,18000060,1,%s,%s"

--自动寻路
function PowerChampionships_Match_FindWay()
	local nMapId = tPowerChampionships_Match_FindWay["MapId"] 
	local nPosX = tPowerChampionships_Match_FindWay["PosX"] 
	local nPosY = tPowerChampionships_Match_FindWay["PosY"] 
	local nNpcId = tPowerChampionships_Match_FindWay["NpcId"] 
	
	Sys_GotoSomeWhere(nPosX,nPosY,nMapId,nNpcId)
end

--返回双龙城
function PowerChampionships_Match_BackCity(sTalk)
	
	--发送变蓝 记数条
	local nMapId = tPowerChampionships_Match_BackCity["MapId"]
	local nPosX = tPowerChampionships_Match_BackCity["PosX"]
	local nPosY = tPowerChampionships_Match_BackCity["PosY"]
	local nBound = tPowerChampionships_Match_BackCity["Bound"]
	
	User_SendNetWorkMsg(0)
	
	if type(sTalk)== "string" then
		User_TalkChannel2005(sTalk)
	end
		
	User_UserRandBoundTrans(nMapId,nPosX,nPosY,nBound,nBound)
end

--参赛战力
function PowerChampionships_Match_Join(nNpcId,nIndex)
	--判断是否在非报名期间
	local bFlag = false
	local tTableData = tPowerChampionships_Match_DynaData["DynaValue"]  == 2  and tPowerChampionships_Match_ActivityEurope or tPowerChampionships_Match_Activity
	
	for k, v in pairs(tTableData["JoinTime"])do
		if Sys_ChkFullTime(v) then
			bFlag = true
		end
	end
	
	if not bFlag then
		LinkNpcGossipFunc_New(nNpcId,"100-1")
		return
	end
	
	--战力检测 
	local nPower =Get_UserBattleLevel()
	
	if nPower >=tPowerChampionships_Match_Power[nIndex]["UpPower"] and nPower <= tPowerChampionships_Match_Power[nIndex]["DownPower"] then
		
		--满足条件进入指定地图
		local nMapId = tPowerChampionships_Match_Power[nIndex]["MapId"]
		local nPosX = tPowerChampionships_Match_Power["PosX"]
		local nPosY = tPowerChampionships_Match_Power["PosY"]
		local nBound = tPowerChampionships_Match_Power["Bound"]
		
		--发送变红杀人 记数条
		User_SendNetWorkMsg(1)
		
		User_UserRandBoundTrans(nMapId,nPosX,nPosY,nBound,nBound)
		Sys_SaveActionTaskLog(string.format(tPowerChampionships_Match_Log["EMap_Site"],nIndex))
		
	else
		LinkNpcGossipFunc_New(nNpcId,"100-2")
		return
	end
end

--领取蝉联奖励
function PowerChampionships_Match_GetReward(nNpcId,nIndex)
	local nPower =Get_UserBattleLevel()
	
	local nIndexv = 0
	for i=1, 3 do
		if nPower >=tPowerChampionships_Match_Power[i]["UpPower"] and nPower <= tPowerChampionships_Match_Power[i]["DownPower"] then
			nIndexv =i
		end
	end
	
    if nIndexv == 0 then
		LinkNpcGossipFunc_New(nNpcId,"100-3")
		return 
	end
	
	local nItemId = tPowerChampionships_Match_Power[nIndexv]["ItemId"]
	if Item_ChkMulItem(nItemId,nItemId,nIndex+1) then
	
		tNpcGossip[18662]["Text122"] = string.format(tPowerChampionships_Match_Text[18662]["Text122"],tPowerChampionships_Match_Power[nIndexv]["ClPower"][nIndex]) 
		--蝉联冠军
		LinkNpcGossipFunc_New(nNpcId,"100-4")
		--增加气力值
		User_AddStrengthValue(tPowerChampionships_Match_Power[nIndexv]["ClPower"][nIndex])
		Sys_SaveActionTaskLog(string.format(tPowerChampionships_Match_Log["EMap_Reward1"],"12",tPowerChampionships_Match_Power[nIndexv]["ClPower"][nIndex]))
		--删除多个物品
		Item_DelMulItem(nItemId,nItemId,nIndex+1)
	else
		LinkNpcGossipFunc_New(nNpcId,"100-3")
	end
end


--NPC领奖员 领取奖励
function PowerChampionships_Match_GetInnerReward(nNpcId)
	local nMapId = Get_UserMapId()
	local nIndex = nMapId % 10
	
	if  Get_SysDynaGlobalData(tPowerChampionships_Match_dynaData["global_Id"],nIndex) ~= 0 then
		return
	end

	--背包空间判断
	if not User_CheckLeftSpace(tPowerChampionships_Match_Limit["Bag"]) then 
		LinkNpcGossipFunc_New(nNpcId,"100-1")
		return 
	end
	
	--有光环
	if User_IsExistHalo() then
		LinkNpcGossipFunc_New(nNpcId,"100-3")
		return
	end
	
	
	for k,v in pairs(tPowerChampionships_Match_MapChk["MapId"])do
		if nMapId == v then
			
			local nPower = tPowerChampionships_Match_GjReward[nMapId]["Power"]
			local nCpNum = tPowerChampionships_Match_GjReward[nMapId]["Cp"]
			local nItemId = tPowerChampionships_Match_GjReward[nMapId]["ItemId"] 
			--local sLevel = tPowerChampionships_Match_GjReward[nMapId]["PowerPhase"]
			
			--判断天石上限
			if Get_UserEMoney() > tPowerChampionships_Match_Limit["CpTop"] - nCpNum then
				LinkNpcGossipFunc_New(nNpcId,"100-2")
				return 
			end
			
			Sys_SetSynaGlobalData(tPowerChampionships_Match_dynaData["global_Id"],nIndex,Get_UserId())
			
			--增加气力值
			User_AddStrengthValue(nPower)
			--增加天石
			User_AddEMoney(nCpNum)
			
			--判定玩家身上是否有光环
			local nStatus = tPowerChampionships_Match_GjEffect["Status"]
			local nVPower = tPowerChampionships_Match_GjEffect["Power"]
			local nSecs  = tPowerChampionships_Match_GjEffect["Secs"]
			local nTimes = tPowerChampionships_Match_GjEffect["Times"]
			local nEndTime = tPowerChampionships_Match_GjEffect["EndTime"]
			local nRecordable = tPowerChampionships_Match_GjEffect["Recordable"]
			local nRemainTime = tPowerChampionships_Match_GjEffect["RemainTime"]
			
			if User_IsExistHalo() then
				--删除光环
				User_DelHalo()
			end
			
			local nUserId = Get_UserId()
			User_AddRoleStatus(nStatus,nVPower,nSecs,nTimes,nRemainTime,nEndTime,nRecordable,0,0,nUserId)
			
			local sLogFile = tPowerChampionships_Match_Log["EMap_File"]
			local sLogText = tPowerChampionships_Match_Log["EMap_Text"]
			
			--光环log
			Sys_SaveActionParamLog(sLogFile,sLogText)
			
			--令牌
			Item_AddItem(nItemId)
			User_TalkChannel2005(string.format(tPowerChampionships_Match_Text["Text200511"],tPowerChampionships_Match_Text["TextPower"..nMapId],tostring(nCpNum),tostring(nPower),Get_ItemtypeName(nItemId)))
			
			Sys_SaveActionTaskLog(string.format(tPowerChampionships_Match_Log["EMap_Reward"],"["..nItemId.."][12][2]","[1]["..nPower.."]["..nCpNum.."]"))
			
		
			
			--返回双龙城
			PowerChampionships_Match_BackCity()
			
			User_Screffect(tPowerChampionships_Match_Effect["ScrEffect"],nUserId)
			User_EffectAdd("self",tPowerChampionships_Match_Effect["Effect"],nUserId)
			
			return
		end
	end
	--地图错误
	User_TalkChannel2005(tPowerChampionships_Match_Text["Text20053"])
end

--全服邀请
function PowerChampionships_Match_SystemBroadcast()
	local bFlag = false
	local tTableData = tPowerChampionships_Match_DynaData["DynaValue"]  == 2  and tPowerChampionships_Match_ActivityEurope or tPowerChampionships_Match_Activity
	for k, v in pairs(tTableData["JoinTime"])do
		if Sys_ChkFullTime(v)  then
			bFlag = true
		end
	end
	
	if bFlag then
	
		--左上角广播提示
		Sys_SystemBroadcast(tPowerChampionships_Match_Text["Text20054"])
		
		--全服邀请
		Sys_InviteFilter(tPowerChampionships_Match_Invite["Activity_InviteId"],tPowerChampionships_Match_Invite["Activity_Invite"])
		Sys_InviteTrans(tPowerChampionships_Match_Invite["MapId"],tPowerChampionships_Match_Invite["Invite_Pos"],tPowerChampionships_Match_Invite["InviteSendId"],tPowerChampionships_Match_Invite["InviteSendOkId"],tPowerChampionships_Match_Invite["Activity_InviteId"],tPowerChampionships_Match_Invite["InviteCountDown"])
		
		Sys_ResetAllSynaGlobalData(tPowerChampionships_Match_dynaData["global_Id"])
	end
	
end

--踢出所有玩家
function PowerChampionships_Match_KickPlayer()
	local bFlag = false
	local tTableData = tPowerChampionships_Match_DynaData["DynaValue"]  == 2  and tPowerChampionships_Match_ActivityEurope or tPowerChampionships_Match_Activity
	for z,l in pairs(tTableData["KickTime"])do
		if Sys_ChkFullTime(l) then
			bFlag = true
		end
	end
	
	if bFlag then
		for k,v in pairs (tPowerChampionships_Match_GjReward)do
			Map_UserExeFunc(k,-1,"PowerChampionships_Match_BackCity</S>"..tPowerChampionships_Match_Text["Text20055"])
		end
	end
end

--通知各地图通知比赛开始
function PowerChampionships_Match_GameStart()
	local bFlag = false
	local tTableData = tPowerChampionships_Match_DynaData["DynaValue"]  == 2  and tPowerChampionships_Match_ActivityEurope or tPowerChampionships_Match_Activity
	for z,l in pairs(tTableData["ActTime"])do
		if Sys_ChkFullTime(l) then
			bFlag = true
		end
	end
	
	if bFlag then
		for k,v in pairs (tPowerChampionships_Match_GjReward)do
			Map_SendBroadcastMsg(k,tPowerChampionships_Match_Text["Text20056"])
		end
	end
end

--背包信加入
function PowerChampionships_Match_Login()
		--取值美服还是欧服
	if tPowerChampionships_Match_DynaData["DynaValue"] == 0 then
		tPowerChampionships_Match_DynaData["DynaValue"] = Get_SysDynaGlobalData(tPowerChampionships_Match_DynaData["DynaId"],0)
	end
	
	local tTableData = tPowerChampionships_Match_DynaData["DynaValue"]  == 2  and tPowerChampionships_Match_ActivityEurope or tPowerChampionships_Match_Activity
	--活动期间
	if Sys_ChkFullTime(tTableData["BefTime"])  or Sys_ChkFullTime(tTableData["AftTime"]) then
		return 
	end
	
	local nEvent = tPowerChampionships_Match_Stc["EventType"] 
	local nType = tPowerChampionships_Match_Stc["DataType"]
	if Task_ChkStcValue(nEvent,nType,"==",0) then
		if not Item_ChkItem(tPowerChampionships_Match_Letter["ItemId"]) then
		
			--背包空间判断
			if not User_CheckLeftSpace(tPowerChampionships_Match_Limit["Bag"]) then 
				User_TalkChannel2005(tPowerChampionships_Match_Text["Text20057"]) 
			else
				User_TalkChannel2005(tPowerChampionships_Match_Text["Text20058"]) 
			end
			Task_SetStatistic(nEvent,nType,1,1)
			Task_SetStcTimestamp(nEvent,nType,0)
			Item_AddItem(tPowerChampionships_Match_Letter["ItemId"])
		end
	end
end

--背包信销毁
function PowerChampionships_Match_Read(nItemId,nNpcId)
	if Item_ChkItem(nItemId) then
		Item_DelItem(nItemId)
		
		if Get_UserLevel() < tPowerChampionships_Match_Limit["Level"] then
			User_AddExpTime(tPowerChampionships_Match_Letter["Exp"])
			User_TalkChannel2005(tPowerChampionships_Match_Text["Text20059"]) 
		else
			User_AddCultivation(tPowerChampionships_Match_Letter["Cul"])
			User_TalkChannel2005(tPowerChampionships_Match_Text["Text200510"]) 
		end
	end
end

--更换光环
function PowerChampionships_Match_ChangeEffect(sFlag,nNpcId)

	local nMapId = Get_UserMapId()
	local nUserId = Get_UserId()
	
	--背包空间判断
	if not User_CheckLeftSpace(tPowerChampionships_Match_Limit["Bag"]) then 
		LinkNpcGossipFunc_New(nNpcId,"100-1")
		return 
	end
	
	
	for k,v in pairs(tPowerChampionships_Match_MapChk["MapId"])do
		if nMapId == v then
			local nPower = tPowerChampionships_Match_GjReward[nMapId]["Power"]
			local nCpNum = tPowerChampionships_Match_GjReward[nMapId]["Cp"]
			local nItemId = tPowerChampionships_Match_GjReward[nMapId]["ItemId"] 
			--local sLevel = tPowerChampionships_Match_GjReward[nMapId]["PowerPhase"]
			
			--判断天石上限
			if Get_UserEMoney() > tPowerChampionships_Match_Limit["CpTop"] - nCpNum then
				LinkNpcGossipFunc_New(nNpcId,"100-2")
				return 
			end
			
			if sFlag == "T" then
				--判定玩家身上是否有光环
				local nStatus = tPowerChampionships_Match_GjEffect["Status"]
				local nVPower = tPowerChampionships_Match_GjEffect["Power"]
				local nSecs  = tPowerChampionships_Match_GjEffect["Secs"]
				local nTimes = tPowerChampionships_Match_GjEffect["Times"]
				local nEndTime = tPowerChampionships_Match_GjEffect["EndTime"]
				local nRecordable = tPowerChampionships_Match_GjEffect["Recordable"]
				local nRemainTime = tPowerChampionships_Match_GjEffect["RemainTime"]
				
				if User_IsExistHalo() then
					--删除光环
					User_DelHalo()
				end
				
				
				User_AddRoleStatus(nStatus,nVPower,nSecs,nTimes,nRemainTime,nEndTime,nRecordable,0,0,nUserId)
				local sLogFile = tPowerChampionships_Match_Log["EMap_File"]
				local sLogText = tPowerChampionships_Match_Log["EMap_Text"]
			
				--光环log
				Sys_SaveActionParamLog(sLogFile,sLogText)
			end
			
			local nIndex = nMapId % 10
			
			Sys_SetSynaGlobalData(tPowerChampionships_Match_dynaData["global_Id"],nIndex,nUserId)
			
			--令牌
			Item_AddItem(nItemId)
		
			--增加气力值
			User_AddStrengthValue(nPower)
			--增加天石
			User_AddEMoney(nCpNum)
			
			Sys_SaveActionTaskLog(string.format(tPowerChampionships_Match_Log["EMap_Reward"],"["..nItemId.."][12][2]","[1]["..nPower.."]["..nCpNum.."]"))
			
		
			--返货双龙城
			PowerChampionships_Match_BackCity()
			
			User_Screffect(tPowerChampionships_Match_Effect["ScrEffect"],nUserId)
			User_EffectAdd("self",tPowerChampionships_Match_Effect["Effect"],nUserId)
			
			User_TalkChannel2005(string.format(tPowerChampionships_Match_Text["Text200511"],tPowerChampionships_Match_Text["TextPower"..nMapId],tostring(nCpNum),tostring(nPower),Get_ItemtypeName(nItemId)))
			return
		end
	end

	--地图错误
	User_TalkChannel2005(tPowerChampionships_Match_Text["Text20053"])
end

--锦标赛入场员
tNpcFace[3727] = 32
tNpcGossip[18662] = tNpcGossip[18662] or DefaultNpc:new{}
tNpcGossip[18662]["OptionHidden"] = 1

--活动前对白
tNpcGossip[18662]["Text1-1"] = {111,112,113}
tNpcGossip[18662]["Text111"] = tPowerChampionships_Match_Text[18662]["Text111"]
tNpcGossip[18662]["Text112"] = tPowerChampionships_Match_Text[18662]["Text112"]
tNpcGossip[18662]["Text113"] = tPowerChampionships_Match_Text[18662]["Text113"]
tNpcGossip[18662]["Option1"] = tPowerChampionships_Match_Text[18662]["Option1"]
tNpcGossip[18662]["tOption1-1"] = {1}
tNpcGossip[18662]["ChkFunc1-1"] = function ()
	local tTableData = tPowerChampionships_Match_DynaData["DynaValue"]  == 2  and tPowerChampionships_Match_ActivityEurope or tPowerChampionships_Match_Activity
	
	if tPowerChampionships_Match_DynaData["DynaValue"]  == 2 then
		tNpcGossip[18662]["Text111"] = tPowerChampionships_Match_Text[18662]["Text151"]
	end
	
	if Sys_ChkFullTime(tTableData["BefTime"]) then
		return true
	end
	
	
	
	local bFlag = true
	for k , v in pairs(tTableData["JoinTime"]) do
		if  Sys_ChkFullTime(v) then
			bFlag = false
		end
	end

	if bFlag and not  Sys_ChkFullTime(tTableData["AftTime"]) then
		return true
	end
end

--活动中对白
tNpcGossip[18662]["Text1-2"] = {115,116,117}
tNpcGossip[18662]["Text115"] = tPowerChampionships_Match_Text[18662]["Text115"]
tNpcGossip[18662]["Text116"] = tPowerChampionships_Match_Text[18662]["Text116"]
tNpcGossip[18662]["Text117"] = tPowerChampionships_Match_Text[18662]["Text117"]
tNpcGossip[18662]["Option3"] = tPowerChampionships_Match_Text[18662]["Option3"]
tNpcGossip[18662]["Option4"] = tPowerChampionships_Match_Text[18662]["Option4"]
tNpcGossip[18662]["Option5"] = tPowerChampionships_Match_Text[18662]["Option5"]
tNpcGossip[18662]["Option9"] = tPowerChampionships_Match_Text[18662]["Option9"]

tNpcGossip[18662]["Option10"] = tPowerChampionships_Match_Text[18662]["Option10"]
tNpcGossip[18662]["tOption1-2"] = {3,4,5,9,10}
tNpcGossip[18662]["OptionFunc3"]="PowerChampionships_Match_Join</N>18662</N>1"
tNpcGossip[18662]["OptionFunc4"]="PowerChampionships_Match_Join</N>18662</N>2"
tNpcGossip[18662]["OptionFunc5"]="PowerChampionships_Match_Join</N>18662</N>3"

tNpcGossip[18662]["OptionFunc9"]="LinkNpcGossipFunc_New</N>18662</S>100-5"
tNpcGossip[18662]["ChkFunc1-2"] = function ()
	local tTableData = tPowerChampionships_Match_DynaData["DynaValue"]  == 2  and tPowerChampionships_Match_ActivityEurope or tPowerChampionships_Match_Activity
	if tPowerChampionships_Match_DynaData["DynaValue"]  == 2 then
		tNpcGossip[18662]["Text115"] = tPowerChampionships_Match_Text[18662]["Text152"]
	end
	for k, v in pairs(tTableData["JoinTime"])do
		if Sys_ChkFullTime(v) then
			return true
		end  
	end
	return false
end

--活动后
tNpcGossip[18662]["Text1-3"] = {114}
tNpcGossip[18662]["Text114"] = tPowerChampionships_Match_Text[18662]["Text114"]
tNpcGossip[18662]["Option2"] = tPowerChampionships_Match_Text[18662]["Option2"]

tNpcGossip[18662]["Option6"] = tPowerChampionships_Match_Text[18662]["Option6"]
tNpcGossip[18662]["Option7"] = tPowerChampionships_Match_Text[18662]["Option7"]
tNpcGossip[18662]["Option8"] = tPowerChampionships_Match_Text[18662]["Option8"]

tNpcGossip[18662]["OptionFunc6"]="PowerChampionships_Match_GetReward</N>18662</N>1"
tNpcGossip[18662]["OptionFunc7"]="PowerChampionships_Match_GetReward</N>18662</N>2"
tNpcGossip[18662]["OptionFunc8"]="PowerChampionships_Match_GetReward</N>18662</N>3"

tNpcGossip[18662]["tOption1-3"] = {6,7,8,2}


--非活动期间
tNpcGossip[18662]["Text100-1"] = {118,119}
tNpcGossip[18662]["Text118"] =  tPowerChampionships_Match_DynaData["DynaValue"] == 2 and  tPowerChampionships_Match_Text[18662]["Text153"] or   tPowerChampionships_Match_Text[18662]["Text118"] 
tNpcGossip[18662]["Text119"] = tPowerChampionships_Match_Text[18662]["Text119"]
tNpcGossip[18662]["Option11"] = tPowerChampionships_Match_Text[18662]["Option11"]
tNpcGossip[18662]["tOption100-1"] = {11}


--战力不足
tNpcGossip[18662]["Text100-2"] = {120}
tNpcGossip[18662]["Text120"] = tPowerChampionships_Match_Text[18662]["Text120"]
tNpcGossip[18662]["Option12"] = tPowerChampionships_Match_Text[18662]["Option12"]
tNpcGossip[18662]["tOption100-2"] = {12}

--玩家并非蝉联冠军
tNpcGossip[18662]["Text100-3"] = {121}
tNpcGossip[18662]["Text121"] = tPowerChampionships_Match_Text[18662]["Text121"]
tNpcGossip[18662]["Option13"] = tPowerChampionships_Match_Text[18662]["Option13"]
tNpcGossip[18662]["tOption100-3"] = {13}

--领取蝉联冠军
tNpcGossip[18662]["Text100-4"] = {122}
tNpcGossip[18662]["Text122"] = tPowerChampionships_Match_Text[18662]["Text122"]
tNpcGossip[18662]["Option14"] = tPowerChampionships_Match_Text[18662]["Option14"]
tNpcGossip[18662]["tOption100-4"] = {14}

--了解战力锦标赛活动
tNpcGossip[18662]["Text100-5"] = {123,124,125,126}
tNpcGossip[18662]["Text123"] = tPowerChampionships_Match_Text[18662]["Text123"]
tNpcGossip[18662]["Text124"] = tPowerChampionships_Match_Text[18662]["Text124"]
tNpcGossip[18662]["Text125"] = tPowerChampionships_Match_Text[18662]["Text125"]
tNpcGossip[18662]["Text126"] = tPowerChampionships_Match_Text[18662]["Text126"]
tNpcGossip[18662]["Option15"] = tPowerChampionships_Match_Text[18662]["Option15"]
tNpcGossip[18662]["Option16"] = tPowerChampionships_Match_Text[18662]["Option16"]
tNpcGossip[18662]["OptionFunc15"]="LinkNpcGossipFunc_New</N>18662</S>100-6"
tNpcGossip[18662]["OptionFunc16"]="LinkNpcGossipFunc_New</N>18662</S>100-7"
tNpcGossip[18662]["tOption100-5"] = {15,16}

--了解不同战力段的奖励。
tNpcGossip[18662]["Text100-6"] = {127,128,129}
tNpcGossip[18662]["Text127"] = tPowerChampionships_Match_Text[18662]["Text127"]
tNpcGossip[18662]["Text128"] = tPowerChampionships_Match_Text[18662]["Text128"]
tNpcGossip[18662]["Text129"] = tPowerChampionships_Match_Text[18662]["Text129"]
tNpcGossip[18662]["Option17"] = tPowerChampionships_Match_Text[18662]["Option17"]
tNpcGossip[18662]["tOption100-6"] = {17}

--了解蝉联冠军奖励。
tNpcGossip[18662]["Text100-7"] = {130,131,132,133,134}
tNpcGossip[18662]["Text130"] = tPowerChampionships_Match_Text[18662]["Text130"]
tNpcGossip[18662]["Text131"] = tPowerChampionships_Match_Text[18662]["Text131"]
tNpcGossip[18662]["Text132"] = tPowerChampionships_Match_Text[18662]["Text132"]
tNpcGossip[18662]["Text133"] = tPowerChampionships_Match_Text[18662]["Text133"]
tNpcGossip[18662]["Text134"] = tPowerChampionships_Match_Text[18662]["Text134"]
tNpcGossip[18662]["Option18"] = tPowerChampionships_Match_Text[18662]["Option18"]
tNpcGossip[18662]["OptionFunc18"]="LinkNpcGossipFunc_New</N>18662</S>100-8"
tNpcGossip[18662]["tOption100-7"] = {18}

--了解蝉联冠军奖励。(下一页)
tNpcGossip[18662]["Text100-8"] = {135,136,137,138,139,140}
tNpcGossip[18662]["Text135"] = tPowerChampionships_Match_Text[18662]["Text135"]
tNpcGossip[18662]["Text136"] = tPowerChampionships_Match_Text[18662]["Text136"]
tNpcGossip[18662]["Text137"] = tPowerChampionships_Match_Text[18662]["Text137"]
tNpcGossip[18662]["Text138"] = tPowerChampionships_Match_Text[18662]["Text138"]
tNpcGossip[18662]["Text139"] = tPowerChampionships_Match_Text[18662]["Text139"]
tNpcGossip[18662]["Text140"] = tPowerChampionships_Match_Text[18662]["Text140"]
tNpcGossip[18662]["Option19"] = tPowerChampionships_Match_Text[18662]["Option19"]
tNpcGossip[18662]["tOption100-8"] = {19}


--NPC--赛场颁奖员
tNpcFace[3728] = 4
tNpcGossip[18663] = tNpcGossip[18663] or DefaultNpc:new{}
tNpcGossip[18663]["OptionHidden"] = 1

tNpcGossip[18663]["Text1-1"] = {141,142}
tNpcGossip[18663]["Text141"] = tPowerChampionships_Match_Text[18663]["Text141"]
tNpcGossip[18663]["Text142"] = tPowerChampionships_Match_Text[18663]["Text142"]
tNpcGossip[18663]["Option20"] = tPowerChampionships_Match_Text[18663]["Option20"]
tNpcGossip[18663]["Option21"] = tPowerChampionships_Match_Text[18663]["Option21"]
tNpcGossip[18663]["Option22"] = tPowerChampionships_Match_Text[18663]["Option22"]

tNpcGossip[18663]["tOption1-1"] = {20,21,22}
tNpcGossip[18663]["OptionFunc20"]="PowerChampionships_Match_GetInnerReward</N>18663"
tNpcGossip[18663]["OptionFunc21"]="PowerChampionships_Match_BackCity</N>18663"
tNpcGossip[18663]["ChkFunc1-1"] = function ()
	local tTableData = tPowerChampionships_Match_DynaData["DynaValue"]  == 2  and tPowerChampionships_Match_ActivityEurope or tPowerChampionships_Match_Activity
	--在比赛期间
	local nNpcId = Get_NpcId()
	for k, v in pairs(tTableData["ActTime"])do
		local nNpcMapId =  Get_NpcMapID(nNpcId)
		if Sys_ChkFullTime(v) and Map_GetUserNum(nNpcMapId,tPowerChampionships_Match_Alive["IsAlive"]) == tPowerChampionships_Match_Alive["AliveLimit"] then
			return true
		end
		 
	end
	
	return false
end

--比赛还没开始
tNpcGossip[18663]["Text1-2"] = {146,147}
tNpcGossip[18663]["Text146"] = tPowerChampionships_Match_Text[18663]["Text146"]
tNpcGossip[18663]["Text147"] = tPowerChampionships_Match_Text[18663]["Text147"]
tNpcGossip[18663]["Option26"] = tPowerChampionships_Match_Text[18663]["Option26"]
tNpcGossip[18663]["Option27"] = tPowerChampionships_Match_Text[18663]["Option27"]
tNpcGossip[18663]["OptionFunc26"]="PowerChampionships_Match_BackCity</S>"..tPowerChampionships_Match_Text["Text20051"]
tNpcGossip[18663]["tOption1-2"] = {26,27}
tNpcGossip[18663]["ChkFunc1-2"] = function ()
	 local tTableData = tPowerChampionships_Match_DynaData["DynaValue"]  == 2  and tPowerChampionships_Match_ActivityEurope or tPowerChampionships_Match_Activity
	 --不在比赛期间
	local nIndex =  true
	for k, v in pairs(tTableData["ActTime"])do
		if  Sys_ChkFullTime(v) then
			nIndex = false
		end
	end
	return nIndex
end

--比赛进行中
tNpcGossip[18663]["Text1-3"] = {148}
tNpcGossip[18663]["Text148"] = tPowerChampionships_Match_Text[18663]["Text148"]
tNpcGossip[18663]["Option28"] = tPowerChampionships_Match_Text[18663]["Option26"]
tNpcGossip[18663]["Option29"] = tPowerChampionships_Match_Text[18663]["Option27"]
tNpcGossip[18663]["OptionFunc28"]="PowerChampionships_Match_BackCity</S>"..tPowerChampionships_Match_Text["Text20052"]
tNpcGossip[18663]["tOption1-3"] = {28,29}
tNpcGossip[18663]["ChkFunc1-3"] = function ()
	local tTableData = tPowerChampionships_Match_DynaData["DynaValue"]  == 2  and tPowerChampionships_Match_ActivityEurope or tPowerChampionships_Match_Activity
	--在比赛期间
	local nNpcId = Get_NpcId()
	for k, v in pairs(tTableData["ActTime"])do
		local nNpcMapId =  Get_NpcMapID(nNpcId)
		if Sys_ChkFullTime(v) and Map_GetUserNum(nNpcMapId,tPowerChampionships_Match_Alive["IsAlive"]) ~= tPowerChampionships_Match_Alive["AliveLimit"] then
			return true
		end
	end
	return false
end

--背包空间不足
tNpcGossip[18663]["Text100-1"] = {149}
tNpcGossip[18663]["Text149"] = tPowerChampionships_Match_Text[18663]["Text149"]
tNpcGossip[18663]["Option30"] = tPowerChampionships_Match_Text[18663]["Option30"]
tNpcGossip[18663]["tOption100-1"] = {30}


--背包天石不足
tNpcGossip[18663]["Text100-2"] = {150}
tNpcGossip[18663]["Text150"] = tPowerChampionships_Match_Text[18663]["Text150"]
tNpcGossip[18663]["Option31"] = tPowerChampionships_Match_Text[18663]["Option31"]
tNpcGossip[18663]["tOption100-2"] = {31}

--已有光环是否更换
tNpcGossip[18663]["Text100-3"] = {151}
tNpcGossip[18663]["Text151"] = tPowerChampionships_Match_Text[18663]["Text151"]
tNpcGossip[18663]["Option32"] = tPowerChampionships_Match_Text[18663]["Option32"]
tNpcGossip[18663]["Option33"] = tPowerChampionships_Match_Text[18663]["Option33"]
tNpcGossip[18663]["OptionFunc32"]="PowerChampionships_Match_ChangeEffect</S>T</N>18663"
tNpcGossip[18663]["OptionFunc33"]="PowerChampionships_Match_ChangeEffect</S>F</N>18663"
tNpcGossip[18663]["tOption100-3"] = {32,33}

tNpcGossip[18664] = tNpcGossip[18663]
tNpcGossip[18665] = tNpcGossip[18663]



-----------背包信使用
tItem[3006839] = tItem[3006839] or {}
tItem[3006839]["Text1-1"] = {111}
tItem[3006839]["Text111"] = tPowerChampionships_Match_Text["Letter"]
tItem[3006839]["ChkFunc1-1"] = function () 
	local tTableData = tPowerChampionships_Match_DynaData["DynaValue"]  == 2  and tPowerChampionships_Match_ActivityEurope or tPowerChampionships_Match_Activity
	if tPowerChampionships_Match_DynaData["DynaValue"]  == 2 then
		tItem[3006839]["Text111"] = tPowerChampionships_Match_Text["Letter1"]
	end
	
	if  Sys_ChkFullTime(tTableData["AftTime"]) then
		Item_DelItem(3006839)
		tItem[3006839]["Text111"] = tPowerChampionships_Match_Text["LetterOver"]
		tItem[3006839]["Option1"] = tPowerChampionships_Match_Text["LetterOver1"]
		tItem[3006839]["tOption1-1"] ={1}
		tItem[3006839]["OptionFunc1"] = ""
	end
	return true
end

tItem[3006839]["Option1"] = tPowerChampionships_Match_Text["Option32"]
tItem[3006839]["Option2"] = tPowerChampionships_Match_Text["Option33"]
tItem[3006839]["tOption1-1"] = {1,2}
tItem[3006839]["OptionFunc1"]="PowerChampionships_Match_FindWay"
tItem[3006839]["OptionFunc2"]="PowerChampionships_Match_Read</N>3006839"


--全服邀请  左上角通知
tOntimerMin_HM[1945] = tOntimerMin_HM[1945] or {}
table.insert(tOntimerMin_HM[1945],PowerChampionships_Match_SystemBroadcast)

--欧服
tOntimerMin_HM[2145] = tOntimerMin_HM[2145] or {}
table.insert(tOntimerMin_HM[2145],PowerChampionships_Match_SystemBroadcast)

--比赛结束踢出所有玩家
tOntimerMin_HM[2100] = tOntimerMin_HM[2100] or {}
table.insert(tOntimerMin_HM[2100],PowerChampionships_Match_KickPlayer)

--欧服
tOntimerMin_HM[2300] = tOntimerMin_HM[2300] or {}
table.insert(tOntimerMin_HM[2300],PowerChampionships_Match_KickPlayer)

--各地图通知比赛开始
tOntimerMin_HM[2000] = tOntimerMin_HM[2000] or {}
table.insert(tOntimerMin_HM[2000],PowerChampionships_Match_GameStart)

--欧服
tOntimerMin_HM[2200] = tOntimerMin_HM[2200] or {}
table.insert(tOntimerMin_HM[2200],PowerChampionships_Match_GameStart)

--上线触发
table.insert(tSystem_PlayLogin_Func,PowerChampionships_Match_Login)
