------------------------------------------------------------------------------------
--Name:		[征服][活动脚本]复活节限量特卖（4.2-4.8）
--Purpose:	复活节限量特卖（4.2-4.8）
--Creator: 	严振飞
--Created:	2015/02/02
------------------------------------------------------------------------------------

--掩码说明
---stc(132,82) 记录玩家已购礼包个数

--LOGid 12000029
------------------------------------------------------------------------------------
--命名规范
--Easter2015_Sale_
------------------------------------------------------------------------------------
--STC掩码表
local tEaster2015_Sale_Stc = {}
	tEaster2015_Sale_Stc[1] = {}
	tEaster2015_Sale_Stc[1]["Event"] = 132
	tEaster2015_Sale_Stc[1]["Type"] = 82
	tEaster2015_Sale_Stc[1]["AddValue"] = 1
	tEaster2015_Sale_Stc[1]["Complete"] = 3

--活动数据
local tEaster2015_Sale_Data = {}
	--活动总时间
	tEaster2015_Sale_Data["Festival_BefTime"] = "2015-01-01 00:00 2015-04-01 23:59"
	tEaster2015_Sale_Data["Festival_MidTime"] = "2015-04-02 00:00 2015-04-08 23:59"
	--特卖时间
	tEaster2015_Sale_Data["Sale_Time1"] = "08:00 9:59"
	tEaster2015_Sale_Data["Sale_Time2"] = "12:00 13:59"
	tEaster2015_Sale_Data["Sale_Time3"] = "18:00 21:59"
	--玩家等级要求
	tEaster2015_Sale_Data["Metempsychosis"] = 0
	tEaster2015_Sale_Data["Level"] = 80
	--背包空间判断
	tEaster2015_Sale_Data["CheckLeftSpace"] = 1
	--礼包价值
	tEaster2015_Sale_Data["BoxValue"] = 20000
	--传进特卖场数据
	tEaster2015_Sale_Data["SaleMap"] = {}
	tEaster2015_Sale_Data["SaleMap"]["MapId"] = 3931
	tEaster2015_Sale_Data["SaleMap"]["PosX"] = 40
	tEaster2015_Sale_Data["SaleMap"]["PosY"] = 40
	tEaster2015_Sale_Data["SaleMap"]["BoundX"] = 5
	tEaster2015_Sale_Data["SaleMap"]["BoundY"] = 5
	--回双龙成数据
	tEaster2015_Sale_Data["DragonCity"] = {}
	tEaster2015_Sale_Data["DragonCity"]["MapId"] = 1002
	tEaster2015_Sale_Data["DragonCity"]["PosX"] = 287
	tEaster2015_Sale_Data["DragonCity"]["PosY"] = 377
	tEaster2015_Sale_Data["DragonCity"]["BoundX"] = 5
	tEaster2015_Sale_Data["DragonCity"]["BoundY"] = 5
	--玩家与宝箱的距离
	tEaster2015_Sale_Data["Range"] = 6
	--活动结束群体传送数据
	tEaster2015_Sale_Data["MapId"] = 3931
	tEaster2015_Sale_Data["TargetMapId"] = 1002
	tEaster2015_Sale_Data["PosX"] = 287
	tEaster2015_Sale_Data["PosY"] = 377
	--活动结束宝箱NPC移回5000地图
	tEaster2015_Sale_Data["MoveMapId"] = 5000
	tEaster2015_Sale_Data["MovePosX"] = 100
	tEaster2015_Sale_Data["MovePosY"] = 100
	tEaster2015_Sale_Data["MoveBoxStart"] = 18227
	tEaster2015_Sale_Data["MoveBoxNum"] = 30
	--获得礼包光效
	tEaster2015_Sale_Data["EffectObj"] = "self"
	tEaster2015_Sale_Data["Effect_1"] = "money"
------------------------------------------------------------------------------------
--宝箱数据
local tEaster2015_Sale_BoxData = {}
	tEaster2015_Sale_BoxData["StartPosX"] = 34
	tEaster2015_Sale_BoxData["StartPosY"] = 34
	tEaster2015_Sale_BoxData["BoxNum_X"] = 6
	tEaster2015_Sale_BoxData["BoxNum_Y"] = 5
	tEaster2015_Sale_BoxData["AddValue1"] = 7
	tEaster2015_Sale_BoxData["AddValue2"] = 8

--动态存储表
local tEaster2015_Sale_DynaGlobalData = {}
	tEaster2015_Sale_DynaGlobalData["Id"] = 50853
	tEaster2015_Sale_DynaGlobalData["CreatBox"] = 1
	tEaster2015_Sale_DynaGlobalData["DeleteBox"] = 0

--活动LOG数据
local tEaster2015_Sale_Log = {}
	--LogId
	tEaster2015_Sale_Log["LogId"] = 12000029
	tEaster2015_Sale_Log["FestivalId"] = 3381
	--任务阶段
	tEaster2015_Sale_Log["GetPackage"] = "0,0,1,20000,12000029,2,3003625,1"


------------------------------------------------------------------------------------
--传送逻辑
function Easter2015_Sale_ChgMap(sWay)
	local nMapId = tEaster2015_Sale_Data[sWay]["MapId"]
	local nPosX = tEaster2015_Sale_Data[sWay]["PosX"]
	local nPosY = tEaster2015_Sale_Data[sWay]["PosY"]
	local nBoundX = tEaster2015_Sale_Data[sWay]["BoundX"]
	local nBoundY = tEaster2015_Sale_Data[sWay]["BoundY"]
	
	--将玩家传送到地图的指定区域
	User_UserRandBoundTrans(nMapId,nPosX,nPosY,nBoundX,nBoundY)
	User_TalkChannel2005(tEaster2015_Sale_Text[sWay])
end



--【如何进入特卖场？】+【怎么抢购礼包？】
function Easter2015_Sale_HowPlay(nNpcId,sCont)
	--活动时间判断
	if not Sys_ChkFullTime(tEaster2015_Sale_Data["Festival_MidTime"]) then
		LinkNpcGossipFunc_New(nNpcId,"1-2")
		return
	end
	
	--显示内容
	LinkNpcGossipFunc_New(nNpcId,sCont)
end



--【我要进入特卖场。】
function Easter2015_Sale_EnterMap(nNpcId)
	--活动总时间判断
	if not Sys_ChkFullTime(tEaster2015_Sale_Data["Festival_MidTime"]) then
		LinkNpcGossipFunc_New(nNpcId,"1-2")
		return
	end

	--特卖时间判断
	if not Sys_ChkDayTime(tEaster2015_Sale_Data["Sale_Time1"]) and not Sys_ChkDayTime(tEaster2015_Sale_Data["Sale_Time2"]) and not Sys_ChkDayTime(tEaster2015_Sale_Data["Sale_Time3"]) then
		LinkNpcGossipFunc_New(nNpcId,"4-1")
		return
	end
	
	--玩家等级判断
	if not User_JudgeLevelAndMetempsychosis(tEaster2015_Sale_Data["Level"],tEaster2015_Sale_Data["Metempsychosis"]) then
		LinkNpcGossipFunc_New(nNpcId,"4-2")
		return
	end
	
	--传送到特卖场
	Easter2015_Sale_ChgMap("SaleMap")
end



--宝箱移入特卖场
function Easter2015_Sale_CreateBox()
	
	--活动总时间判断
	if not Sys_ChkFullTime(tEaster2015_Sale_Data["Festival_MidTime"]) then
		return
	end
	
	--判断是否已创建NPC
	local nDynaValue = Get_SysDynaGlobalData0(tEaster2015_Sale_DynaGlobalData["Id"])
	if nDynaValue ~= 0 then
		return
	end
	
	--移出宝箱
	local nNpcId = tEaster2015_Sale_Data["MoveBoxStart"] - 1
	
	for nBoxNum_X=0,tEaster2015_Sale_BoxData["BoxNum_X"] - 1 do
		for nBoxNum_Y=0,tEaster2015_Sale_BoxData["BoxNum_Y"] - 1 do
			local nMapId = tEaster2015_Sale_Data["MapId"]
			local nPosX = nBoxNum_X * tEaster2015_Sale_BoxData["AddValue1"] + tEaster2015_Sale_BoxData["StartPosX"]
			local nPosY = nBoxNum_Y * tEaster2015_Sale_BoxData["AddValue2"] + tEaster2015_Sale_BoxData["StartPosY"]
			nNpcId = nNpcId + 1
			Npc_MoveNpcPos(nNpcId,nMapId,nPosX,nPosY)
		end
	end
	
	--完成置掩码
	Sys_SetSynaGlobalData0(tEaster2015_Sale_DynaGlobalData["Id"],tEaster2015_Sale_DynaGlobalData["CreatBox"])
end



--抢购宝箱
function Easter2015_Sale_BuyBox(nNpcId)

	--活动总时间判断
	if not Sys_ChkFullTime(tEaster2015_Sale_Data["Festival_MidTime"]) then
		return
	end
	
	--特卖时间判断
	if not Sys_ChkDayTime(tEaster2015_Sale_Data["Sale_Time1"]) and not Sys_ChkDayTime(tEaster2015_Sale_Data["Sale_Time2"]) and not Sys_ChkDayTime(tEaster2015_Sale_Data["Sale_Time3"]) then
		return
	end
	
	--判断是否隔天
	local nEvent = tEaster2015_Sale_Stc[1]["Event"]
	local nType = tEaster2015_Sale_Stc[1]["Type"]
	local nComplete = tEaster2015_Sale_Stc[1]["Complete"]
	if Task_StcInterval(nEvent,nType,1,4) then
		Task_SetStatistic(nEvent,nType,0,1)
		Task_SetStcTimestamp(nEvent,nType,0)
	end
	
	--判断是否超过抢购限制
	if Task_ChkStcValue(nEvent,nType,">=",nComplete) then
		LinkNpcGossipFunc_New(nNpcId,"2-2")
		return
	end
	
	--判断是否在特卖场+宝箱是否存在
	local nUserMapId = Get_UserMapId()
	local nUserPosX = Get_UserPositionX()
	local nUserPosY = Get_UserPositionY()
	local nBoxPosX = Get_NpcPositionX()
	local nBoxPosY = Get_NpcPositionY()
	local nRange = tEaster2015_Sale_Data["Range"]
	

	--是否在特卖场
	if nUserMapId ~= tEaster2015_Sale_Data["MapId"] then
		Sys_MsgBox(tEaster2015_Sale_Text["LeaveMap"])
		return
	end
	
	--宝箱是否在距离内
	if nUserPosX < nBoxPosX - nRange or nUserPosX > nBoxPosX + nRange or nUserPosY < nBoxPosY - nRange or nUserPosY > nBoxPosY + nRange then
		Sys_MsgBox(tEaster2015_Sale_Text["TooFar"])
		return
	end

	--背包空间判断
	if not User_CheckLeftSpace(tEaster2015_Sale_Data["CheckLeftSpace"]) then
		LinkNpcGossipFunc_New(nNpcId,"2-1")
		return
	end
	
	--判断金币是否足够
	local nMoney = Get_UserMoney()
	local nAddMoney = tEaster2015_Sale_Data["BoxValue"]
	if nMoney <= nAddMoney then
		LinkNpcGossipFunc_New(nNpcId,"2-4")
		return
	end
	
	--减少玩家金币
	User_AddMoney(-nAddMoney)
	
	--置掩码
	local nBoxNpcId = Get_NpcId()
	local nBoxMoveMapId = tEaster2015_Sale_Data["MoveMapId"]
	local nBoxMovePosX = tEaster2015_Sale_Data["MovePosX"]
	local nBoxMovePosY = tEaster2015_Sale_Data["MovePosY"]
	Task_AddStatistic(tEaster2015_Sale_Stc[1]["Event"],tEaster2015_Sale_Stc[1]["Type"],tEaster2015_Sale_Stc[1]["AddValue"],1)
	Task_SetStcTimestamp(tEaster2015_Sale_Stc[1]["Event"],tEaster2015_Sale_Stc[1]["Type"],0)
	
	--给通用礼包+打LOG
	FestivalGeneralPackage_GetGift(tEaster2015_Sale_Log["FestivalId"],tEaster2015_Sale_Log["LogId"])
	Sys_SaveActionFestivalLog(tEaster2015_Sale_Log["GetPackage"])
	
	--移走宝箱+播放光效+出对白
	Npc_MoveNpcPos(nBoxNpcId,nBoxMoveMapId,nBoxMovePosX,nBoxMovePosY)
	User_EffectAdd(tEaster2015_Sale_Data["EffectObj"],tEaster2015_Sale_Data["Effect_1"])
	LinkNpcGossipFunc_New(nNpcId,"2-3")
end



--活动时间结束玩家传出地图+删除残留宝箱
function Easter2015_Sale_TimeEnd()

	--活动总时间判断
	if not Sys_ChkFullTime(tEaster2015_Sale_Data["Festival_MidTime"]) then
		return
	end

	--判断是否已传送玩家+移除NPC
	--local nDynaValue = Get_SysDynaGlobalData0(tEaster2015_Sale_DynaGlobalData["Id"])
	--if nDynaValue == 0 then
	--	return
	--end
	
	--全体玩家传送出地图
	local nMapId = tEaster2015_Sale_Data["MapId"]
	local nTargetMapId = tEaster2015_Sale_Data["TargetMapId"]
	local nPosX = tEaster2015_Sale_Data["PosX"]
	local nPosY = tEaster2015_Sale_Data["PosY"]
	Map_ChgUserPos(nMapId,nTargetMapId,nPosX,nPosY)
	
	--宝箱移到5000地图
	local nBoxMapId = tEaster2015_Sale_Data["MoveMapId"]
	local nBoxPosX = tEaster2015_Sale_Data["MovePosX"]
	local nBoxPosY = tEaster2015_Sale_Data["MovePosY"]
	for nStart=0,tEaster2015_Sale_Data["MoveBoxNum"]-1 do
		local nBoxNpcId = tEaster2015_Sale_Data["MoveBoxStart"] + nStart
		Npc_MoveNpcPos(nBoxNpcId,nBoxMapId,nBoxPosX,nBoxPosY)
	end

	--置掩码
	Sys_SetSynaGlobalData0(tEaster2015_Sale_DynaGlobalData["Id"],tEaster2015_Sale_DynaGlobalData["DeleteBox"])
end




------------------------------------------NPC对话配置-------------------------------------------
-- 头像
tNpcFace[3558] = 172

------------------------------------------
-- //========划算姐========\\
tNpcGossip[18221] = tNpcGossip[18221] or DefaultNpc:new{}
tNpcGossip[18226] = tNpcGossip[18221] or DefaultNpc:new{}
tNpcGossip[18221]["OptionHidden"] = 1

--【第一层】
tNpcGossip[18221]["Text1-1"] = {111,112} 	--活动前
tNpcGossip[18221]["Text1-2"] = {121} 		--活动后
tNpcGossip[18221]["Text1-3"] = {131,132} 	--活动中
--活动前
tNpcGossip[18221]["Text111"] = tEaster2015_Sale_Text[18221]["Text111"]
tNpcGossip[18221]["Text112"] = tEaster2015_Sale_Text[18221]["Text112"]
tNpcGossip[18221]["ChkFunc1-1"] = function ()
	return Sys_ChkFullTime(tEaster2015_Sale_Data["Festival_BefTime"])
end
--活动后
tNpcGossip[18221]["Text121"] = tEaster2015_Sale_Text[18221]["Text121"]
tNpcGossip[18221]["ChkFunc1-2"] = function ()
	return not Sys_ChkFullTime(tEaster2015_Sale_Data["Festival_MidTime"])
end
--活动中
tNpcGossip[18221]["Text131"] = tEaster2015_Sale_Text[18221]["Text131"]
tNpcGossip[18221]["Text132"] = tEaster2015_Sale_Text[18221]["Text132"]

--------------选项
tNpcGossip[18221]["tOption1-1"] = {11}
tNpcGossip[18221]["tOption1-2"] = {12}
tNpcGossip[18221]["tOption1-3"] = {14,15,13,16}
tNpcGossip[18221]["Option11"] = tEaster2015_Sale_Text[18221]["Option11"]
tNpcGossip[18221]["Option12"] = tEaster2015_Sale_Text[18221]["Option12"]
tNpcGossip[18221]["Option13"] = tEaster2015_Sale_Text[18221]["Option13"]
tNpcGossip[18221]["OptionFunc13"] = "Easter2015_Sale_HowPlay</N>18221</S>2-1"
tNpcGossip[18221]["Option14"] = tEaster2015_Sale_Text[18221]["Option14"]
tNpcGossip[18221]["OptionChkFunc14"] = function ()
	local nNpcId = Get_NpcId()
	--为进场NPC
	if nNpcId == 18221 then
		return true
	else
		return false
	end
end
tNpcGossip[18221]["OptionFunc14"] = "Easter2015_Sale_EnterMap</N>18221"
tNpcGossip[18221]["Option15"] = tEaster2015_Sale_Text[18221]["Option15"]
tNpcGossip[18221]["OptionChkFunc15"] = function ()
	local nNpcId = Get_NpcId()
	--为离场NPC
	if nNpcId == 18226 then
		return true
	else
		return false
	end
end
tNpcGossip[18221]["OptionFunc15"] = "Easter2015_Sale_ChgMap</S>DragonCity"
tNpcGossip[18221]["Option16"] = tEaster2015_Sale_Text[18221]["Option16"]



--【如何进入特卖场？】
tNpcGossip[18221]["Text2-1"] = {211,212} 	--内容
tNpcGossip[18221]["Text211"] = tEaster2015_Sale_Text[18221]["Text211"]
tNpcGossip[18221]["Text212"] = tEaster2015_Sale_Text[18221]["Text212"]
tNpcGossip[18221]["tOption2-1"] = {21,22}
tNpcGossip[18221]["Option21"] = tEaster2015_Sale_Text[18221]["Option21"]
tNpcGossip[18221]["OptionFunc21"] = "Easter2015_Sale_HowPlay</N>18221</S>3-1"
tNpcGossip[18221]["Option22"] = tEaster2015_Sale_Text[18221]["Option22"]
tNpcGossip[18221]["OptionPoint22"] = "1"

--【怎么抢购礼包？】
tNpcGossip[18221]["Text3-1"] = {311,312,313} 	--内容
tNpcGossip[18221]["Text311"] = tEaster2015_Sale_Text[18221]["Text311"]
tNpcGossip[18221]["Text312"] = tEaster2015_Sale_Text[18221]["Text312"]
tNpcGossip[18221]["Text313"] = tEaster2015_Sale_Text[18221]["Text313"]
tNpcGossip[18221]["tOption3-1"] = {32,31}
tNpcGossip[18221]["Option31"] = tEaster2015_Sale_Text[18221]["Option31"]
tNpcGossip[18221]["Option32"] = tEaster2015_Sale_Text[18221]["Option32"]
tNpcGossip[18221]["OptionPoint32"] = "1"

--【我要进入特卖场。】
tNpcGossip[18221]["Text4-1"] = {411,412} 	--特卖时间外
tNpcGossip[18221]["Text4-2"] = {421,422} 	--等级不足
tNpcGossip[18221]["Text411"] = tEaster2015_Sale_Text[18221]["Text411"]
tNpcGossip[18221]["Text412"] = tEaster2015_Sale_Text[18221]["Text412"]
tNpcGossip[18221]["Text421"] = tEaster2015_Sale_Text[18221]["Text421"]
tNpcGossip[18221]["Text422"] = tEaster2015_Sale_Text[18221]["Text422"]
tNpcGossip[18221]["tOption4-1"] = {41}
tNpcGossip[18221]["tOption4-2"] = {42}
tNpcGossip[18221]["Option41"] = tEaster2015_Sale_Text[18221]["Option41"]
tNpcGossip[18221]["Option42"] = tEaster2015_Sale_Text[18221]["Option42"]



-- //========宝箱========\\
tNpcGossip[18227] = tNpcGossip[18227] or DefaultNpc:new{}
tNpcGossip[18228] = tNpcGossip[18227] or DefaultNpc:new{}
tNpcGossip[18229] = tNpcGossip[18227] or DefaultNpc:new{}
tNpcGossip[18230] = tNpcGossip[18227] or DefaultNpc:new{}
tNpcGossip[18231] = tNpcGossip[18227] or DefaultNpc:new{}
tNpcGossip[18232] = tNpcGossip[18227] or DefaultNpc:new{}
tNpcGossip[18233] = tNpcGossip[18227] or DefaultNpc:new{}
tNpcGossip[18234] = tNpcGossip[18227] or DefaultNpc:new{}
tNpcGossip[18235] = tNpcGossip[18227] or DefaultNpc:new{}
tNpcGossip[18236] = tNpcGossip[18227] or DefaultNpc:new{}
tNpcGossip[18237] = tNpcGossip[18227] or DefaultNpc:new{}
tNpcGossip[18238] = tNpcGossip[18227] or DefaultNpc:new{}
tNpcGossip[18239] = tNpcGossip[18227] or DefaultNpc:new{}
tNpcGossip[18240] = tNpcGossip[18227] or DefaultNpc:new{}
tNpcGossip[18241] = tNpcGossip[18227] or DefaultNpc:new{}
tNpcGossip[18242] = tNpcGossip[18227] or DefaultNpc:new{}
tNpcGossip[18243] = tNpcGossip[18227] or DefaultNpc:new{}
tNpcGossip[18244] = tNpcGossip[18227] or DefaultNpc:new{}
tNpcGossip[18245] = tNpcGossip[18227] or DefaultNpc:new{}
tNpcGossip[18246] = tNpcGossip[18227] or DefaultNpc:new{}
tNpcGossip[18247] = tNpcGossip[18227] or DefaultNpc:new{}
tNpcGossip[18248] = tNpcGossip[18227] or DefaultNpc:new{}
tNpcGossip[18249] = tNpcGossip[18227] or DefaultNpc:new{}
tNpcGossip[18250] = tNpcGossip[18227] or DefaultNpc:new{}
tNpcGossip[18251] = tNpcGossip[18227] or DefaultNpc:new{}
tNpcGossip[18252] = tNpcGossip[18227] or DefaultNpc:new{}
tNpcGossip[18253] = tNpcGossip[18227] or DefaultNpc:new{}
tNpcGossip[18254] = tNpcGossip[18227] or DefaultNpc:new{}
tNpcGossip[18255] = tNpcGossip[18227] or DefaultNpc:new{}
tNpcGossip[18256] = tNpcGossip[18227] or DefaultNpc:new{}
tNpcGossip[18227]["OptionHidden"] = 1


--【第一层】
tNpcGossip[18227]["Text1-1"] = {111} --对白内容
tNpcGossip[18227]["Text111"] = tEaster2015_Sale_Text[18227]["Text111"]
tNpcGossip[18227]["tOption1-1"] = {11,12}
tNpcGossip[18227]["Option11"] = tEaster2015_Sale_Text[18227]["Option11"]
tNpcGossip[18227]["OptionFunc11"] = "Easter2015_Sale_BuyBox</N>18227"
tNpcGossip[18227]["Option12"] = tEaster2015_Sale_Text[18227]["Option12"]


--【我要抢购你。】
tNpcGossip[18227]["Text2-1"] = {211} --背包空间不足
tNpcGossip[18227]["Text2-2"] = {221} --超出抢购数量限制
tNpcGossip[18227]["Text2-3"] = {231} --成功
tNpcGossip[18227]["Text2-4"] = {241} --金钱不足
tNpcGossip[18227]["Text211"] = tEaster2015_Sale_Text[18227]["Text211"]
tNpcGossip[18227]["Text221"] = tEaster2015_Sale_Text[18227]["Text221"]
tNpcGossip[18227]["Text231"] = tEaster2015_Sale_Text[18227]["Text231"]
tNpcGossip[18227]["Text241"] = tEaster2015_Sale_Text[18227]["Text241"]
tNpcGossip[18227]["tOption2-1"] = {21}
tNpcGossip[18227]["tOption2-2"] = {22}
tNpcGossip[18227]["tOption2-3"] = {23}
tNpcGossip[18227]["tOption2-4"] = {24}
tNpcGossip[18227]["Option21"] = tEaster2015_Sale_Text[18227]["Option21"]
tNpcGossip[18227]["Option22"] = tEaster2015_Sale_Text[18227]["Option22"]
tNpcGossip[18227]["Option23"] = tEaster2015_Sale_Text[18227]["Option23"]
tNpcGossip[18227]["Option24"] = tEaster2015_Sale_Text[18227]["Option24"]



------------------------------------------配置数据------------------------------------------
--时间函数触发
--'07:57 07:59'--创建宝箱
--tOntimerMin_HM[0757] = tOntimerMin_HM[0757] or {}
--table.insert(tOntimerMin_HM[0757],Easter2015_Sale_CreateBox)
--tOntimerMin_HM[0758] = tOntimerMin_HM[0758] or {}
--table.insert(tOntimerMin_HM[0758],Easter2015_Sale_CreateBox)
--tOntimerMin_HM[0759] = tOntimerMin_HM[0759] or {}
--table.insert(tOntimerMin_HM[0759],Easter2015_Sale_CreateBox)

--'10:00 10:02'--移除宝箱
--tOntimerMin_HM[1000] = tOntimerMin_HM[1000] or {}
--table.insert(tOntimerMin_HM[1000],Easter2015_Sale_TimeEnd)
--tOntimerMin_HM[1001] = tOntimerMin_HM[1001] or {}
--table.insert(tOntimerMin_HM[1001],Easter2015_Sale_TimeEnd)
--tOntimerMin_HM[1002] = tOntimerMin_HM[1002] or {}
--table.insert(tOntimerMin_HM[1002],Easter2015_Sale_TimeEnd)

--'11:57 11:59'--创建宝箱
--tOntimerMin_HM[1157] = tOntimerMin_HM[1157] or {}
--table.insert(tOntimerMin_HM[1157],Easter2015_Sale_CreateBox)
--tOntimerMin_HM[1158] = tOntimerMin_HM[1158] or {}
--table.insert(tOntimerMin_HM[1158],Easter2015_Sale_CreateBox)
--tOntimerMin_HM[1159] = tOntimerMin_HM[1159] or {}
--table.insert(tOntimerMin_HM[1159],Easter2015_Sale_CreateBox)

--'14:00 14:02'--移除宝箱
--tOntimerMin_HM[1400] = tOntimerMin_HM[1400] or {}
--table.insert(tOntimerMin_HM[1400],Easter2015_Sale_TimeEnd)
--tOntimerMin_HM[1401] = tOntimerMin_HM[1401] or {}
--table.insert(tOntimerMin_HM[1401],Easter2015_Sale_TimeEnd)
--tOntimerMin_HM[1402] = tOntimerMin_HM[1402] or {}
--table.insert(tOntimerMin_HM[1402],Easter2015_Sale_TimeEnd)

--'17:57 17:59'--创建宝箱
--tOntimerMin_HM[1757] = tOntimerMin_HM[1757] or {}
--table.insert(tOntimerMin_HM[1757],Easter2015_Sale_CreateBox)
--tOntimerMin_HM[1758] = tOntimerMin_HM[1758] or {}
--table.insert(tOntimerMin_HM[1758],Easter2015_Sale_CreateBox)
--tOntimerMin_HM[1759] = tOntimerMin_HM[1759] or {}
--table.insert(tOntimerMin_HM[1759],Easter2015_Sale_CreateBox)

--'10:00 10:03'--移除宝箱
--tOntimerMin_HM[2200] = tOntimerMin_HM[2200] or {}
--table.insert(tOntimerMin_HM[2200],Easter2015_Sale_TimeEnd)
--tOntimerMin_HM[2201] = tOntimerMin_HM[2201] or {}
--table.insert(tOntimerMin_HM[2201],Easter2015_Sale_TimeEnd)
--tOntimerMin_HM[2202] = tOntimerMin_HM[2202] or {}
--table.insert(tOntimerMin_HM[2202],Easter2015_Sale_TimeEnd)















