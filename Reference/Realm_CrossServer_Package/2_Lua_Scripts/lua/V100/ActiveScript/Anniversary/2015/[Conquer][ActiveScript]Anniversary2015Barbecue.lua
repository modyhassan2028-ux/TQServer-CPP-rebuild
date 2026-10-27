------------------------------------------------------------------------------------
--Name:			[征服][活动脚本]周年庆活动之篝火晚会之烧烤（4.27-5.25）
--Creator: 		陈浩文
--Created:		2015/02/27
------------------------------------------------------------------------------------
-- 命名前缀
-- Anniversary2015_Barbecue_

--活动时间
local tAnniversary2015_Barbecue_Time = {}
tAnniversary2015_Barbecue_Time["Beftime"] = "2014-01-01 00:00 2015-05-06 23:59"
tAnniversary2015_Barbecue_Time["Nowtime"] = "2015-05-07 00:00 2015-05-27 23:59"

--玩家等级要求
tAnniversary2015_Barbecue_Condition={}
tAnniversary2015_Barbecue_Condition["Metempsychosis"] = 0
tAnniversary2015_Barbecue_Condition["Level"] = 80

--活动掩码 13311	13320
--stc(133,11) 1表示成功接收任务获得鱼竿 2表示完成任务获取奖励
--stc(133,12) 0表示今天未吃烤鱼 	1表示吃了1个烤鱼 	10表示吃了10个烤鱼达到上限
--stc(133,13) 0表示今天未吃烤鸡肉 	1表示吃了1个烤鸡肉 	10表示吃了10个烤鸡肉达到上限
--stc(133,14) 0表示今天未吃蔬菜 	1表示吃了1个蔬菜 	10表示吃了10个蔬菜达到上限
local tAnniversary2015_Barbecue_Stc = {}
tAnniversary2015_Barbecue_Stc["Barbecue"]={}
tAnniversary2015_Barbecue_Stc["Barbecue"]["StcEvent"] = 133
tAnniversary2015_Barbecue_Stc["Barbecue"]["StcType"] = 11
tAnniversary2015_Barbecue_Stc["Barbecue"]["New"] = 1
tAnniversary2015_Barbecue_Stc["Barbecue"]["Complete"] = 2
--吃烤鱼
tAnniversary2015_Barbecue_Stc["EatKaoyu"]={}
tAnniversary2015_Barbecue_Stc["EatKaoyu"]["StcEvent"] = 133
tAnniversary2015_Barbecue_Stc["EatKaoyu"]["StcType"] = 12
tAnniversary2015_Barbecue_Stc["EatKaoyu"]["Complete"] = 10
--吃烤鸡肉
tAnniversary2015_Barbecue_Stc["EatKaojirou"]={}
tAnniversary2015_Barbecue_Stc["EatKaojirou"]["StcEvent"] = 133
tAnniversary2015_Barbecue_Stc["EatKaojirou"]["StcType"] = 13
tAnniversary2015_Barbecue_Stc["EatKaojirou"]["Complete"] = 10
--吃烤蔬菜
tAnniversary2015_Barbecue_Stc["EatKaoshucai"]={}
tAnniversary2015_Barbecue_Stc["EatKaoshucai"]["StcEvent"] = 133
tAnniversary2015_Barbecue_Stc["EatKaoshucai"]["StcType"] = 14
tAnniversary2015_Barbecue_Stc["EatKaoshucai"]["Complete"] = 10

-- log表
local tAnniversary2015_Barbecue_Log = {}
tAnniversary2015_Barbecue_Log["GetYugan"] = "0,0,0,0,12000038,2,3005947,1"					--获得鱼竿
tAnniversary2015_Barbecue_Log["GetYu"] = "0,0,0,0,12000038,2,3005948,1"						--获得大嘴巴鱼
tAnniversary2015_Barbecue_Log["GetJirou"] = "0,0,0,0,12000038,2,3005949,1"					--获得鲜嫩小鸡肉
tAnniversary2015_Barbecue_Log["GetShucai"] = "0,0,1,10,12000038,2,3005950,1"				--获得一份蔬菜
tAnniversary2015_Barbecue_Log["GetShucaiTen"] = "0,0,1,90,12000038,2,3005950,10"			--获得十份蔬菜
tAnniversary2015_Barbecue_Log["GetKaoyu"] = "0,0,3005948,1,12000038,2,3005951,1"			--获得烤鱼
tAnniversary2015_Barbecue_Log["GetKaojirou"] = "0,0,3005949,1,12000038,2,3005952,1"			--获得烤鸡肉
tAnniversary2015_Barbecue_Log["GetKaoshucai"] = "0,0,3005950,1,12000038,2,3005953,1"		--获得烤蔬菜
tAnniversary2015_Barbecue_Log["GetShengyu"] = "0,0,3005948,1,12000038,2,3005954,1"			--获得未熟的烤鱼
tAnniversary2015_Barbecue_Log["GetShengjirou"] = "0,0,3005949,1,12000038,2,3005955,1"		--获得未熟的烤鸡肉
tAnniversary2015_Barbecue_Log["GetShengshucai"] = "0,0,3005950,1,12000038,2,3005956,1"		--获得未熟的蔬菜
tAnniversary2015_Barbecue_Log["GetKaoyuFail"] = "0,0,3005948,1,12000038,2,0,0"				--大嘴巴鱼烤没了
tAnniversary2015_Barbecue_Log["GetKaojirouFail"] = "0,0,3005949,1,12000038,2,0,0"			--鲜嫩小鸡肉烤没了
tAnniversary2015_Barbecue_Log["GetKaoshucaiFail"] = "0,0,3005950,1,12000038,2,0,0"			--一份蔬菜烤没了
tAnniversary2015_Barbecue_Log["EatKaoyu"] = "0,0,3005951,1,12000038,2,4,5"					--吃烤鱼
tAnniversary2015_Barbecue_Log["EatKaojirou"] = "0,0,3005952,1,12000038,2,4,5"				--吃烤鸡肉
tAnniversary2015_Barbecue_Log["EatKaoshucai"] = "0,0,3005953,1,12000038,2,4,5"				--吃烤蔬菜
tAnniversary2015_Barbecue_Log["KaoShengyu"] = "0,0,3005954,1,12000038,2,3005951,1"			--未熟的烤鱼烤熟
tAnniversary2015_Barbecue_Log["KaoShengjirou"] = "0,0,3005955,1,12000038,2,3005952,1"		--未熟的鸡肉烤熟
tAnniversary2015_Barbecue_Log["KaoShengshucai"] = "0,0,3005956,1,12000038,2,3005953,1"		--未熟的蔬菜烤熟
tAnniversary2015_Barbecue_Log["YuganAfTime"] = "0,0,3005947,1,12000038,2,0,0"				--鱼竿过时
tAnniversary2015_Barbecue_Log["YuAfTime"] = "0,0,3005948,1,12000038,2,0,0"					--大嘴巴鱼过时
tAnniversary2015_Barbecue_Log["JirouAfTime"] = "0,0,3005949,1,12000038,2,0,0"				--鲜嫩小鸡肉过时
tAnniversary2015_Barbecue_Log["ShucaiAfTime"] = "0,0,3005950,1,12000038,2,0,0"				--一份蔬菜过时
tAnniversary2015_Barbecue_Log["KaoyuAfTime"] = "0,0,3005951,1,12000038,2,0,0"				--烤鱼过时
tAnniversary2015_Barbecue_Log["KaojirouAfTime"] = "0,0,3005952,1,12000038,2,0,0"			--烤鸡肉过时
tAnniversary2015_Barbecue_Log["KaoshucaiAfTime"] = "0,0,3005953,1,12000038,2,0,0"			--烤蔬菜过时
tAnniversary2015_Barbecue_Log["ShengyuAfTime"] = "0,0,3005954,1,12000038,2,0,0"				--未熟的烤鱼过时
tAnniversary2015_Barbecue_Log["ShengjirouAfTime"] = "0,0,3005955,1,12000038,2,0,0"			--未熟的烤鸡肉过时
tAnniversary2015_Barbecue_Log["ShengshucaiAfTime"] = "0,0,3005956,1,12000038,2,0,0"			--未熟的蔬菜过时

tAnniversary2015_Barbecue_Log["CompleteGet_Jierilibao"] = "0,0,3005951[3005952][3005953],3[3][1],12000038,2,3003625,1"	--1个节日礼包

-- 物品
local tAnniversary2015_Barbecue_Item = {}
tAnniversary2015_Barbecue_Item["Yugan"]={}					--鱼竿
tAnniversary2015_Barbecue_Item["Yugan"]["Id"] = 3005947
tAnniversary2015_Barbecue_Item["Yugan"]["Num"] = 1
tAnniversary2015_Barbecue_Item["Yu"]={}						--大嘴巴鱼
tAnniversary2015_Barbecue_Item["Yu"]["Id"] = 3005948
tAnniversary2015_Barbecue_Item["Yu"]["Num"] = 1
tAnniversary2015_Barbecue_Item["Jirou"]={}					--鲜嫩小鸡肉
tAnniversary2015_Barbecue_Item["Jirou"]["Id"] = 3005949
tAnniversary2015_Barbecue_Item["Jirou"]["Num"] = 1
tAnniversary2015_Barbecue_Item["Shucai"]={}					--一份蔬菜
tAnniversary2015_Barbecue_Item["Shucai"]["Id"] = 3005950
tAnniversary2015_Barbecue_Item["Shucai"]["Num"] = 1
tAnniversary2015_Barbecue_Item["Kaoyu"]={}					--烤鱼
tAnniversary2015_Barbecue_Item["Kaoyu"]["Id"] = 3005951
tAnniversary2015_Barbecue_Item["Kaoyu"]["Num"] = 1
tAnniversary2015_Barbecue_Item["Kaojirou"]={}				--烤鸡肉
tAnniversary2015_Barbecue_Item["Kaojirou"]["Id"] = 3005952
tAnniversary2015_Barbecue_Item["Kaojirou"]["Num"] = 1
tAnniversary2015_Barbecue_Item["Kaoshucai"]={}				--烤蔬菜
tAnniversary2015_Barbecue_Item["Kaoshucai"]["Id"] = 3005953
tAnniversary2015_Barbecue_Item["Kaoshucai"]["Num"] = 1
tAnniversary2015_Barbecue_Item["Shengyu"]={}				--未熟的烤鱼
tAnniversary2015_Barbecue_Item["Shengyu"]["Id"] = 3005954
tAnniversary2015_Barbecue_Item["Shengyu"]["Num"] = 3
tAnniversary2015_Barbecue_Item["Shengjirou"]={}				--未熟的烤鸡肉
tAnniversary2015_Barbecue_Item["Shengjirou"]["Id"] = 3005955
tAnniversary2015_Barbecue_Item["Shengjirou"]["Num"] = 3
tAnniversary2015_Barbecue_Item["Shengshucai"]={}			--未熟的蔬菜
tAnniversary2015_Barbecue_Item["Shengshucai"]["Id"] = 3005956
tAnniversary2015_Barbecue_Item["Shengshucai"]["Num"] = 1
tAnniversary2015_Barbecue_Item["ChkKaoyu"]={}				--检查烤鱼
tAnniversary2015_Barbecue_Item["ChkKaoyu"]["Id"] = 3005951
tAnniversary2015_Barbecue_Item["ChkKaoyu"]["Num"] = 3
tAnniversary2015_Barbecue_Item["ChkKaojirou"]={}			--检查烤鸡肉
tAnniversary2015_Barbecue_Item["ChkKaojirou"]["Id"] = 3005952
tAnniversary2015_Barbecue_Item["ChkKaojirou"]["Num"] = 3
tAnniversary2015_Barbecue_Item["ChkKaoshucai"]={}			--检查烤蔬菜
tAnniversary2015_Barbecue_Item["ChkKaoshucai"]["Id"] = 3005953
tAnniversary2015_Barbecue_Item["ChkKaoshucai"]["Num"] = 1
tAnniversary2015_Barbecue_Item["Jierilibao"]={}			--节日欢庆礼包
tAnniversary2015_Barbecue_Item["Jierilibao"]["FestivalId"] = 3404
tAnniversary2015_Barbecue_Item["Jierilibao"]["LogId"] = 12000038

tAnniversary2015_Barbecue_Item["Money"] = {}
tAnniversary2015_Barbecue_Item["Money"]['One'] = 10
tAnniversary2015_Barbecue_Item["Money"]['Ten'] = 90

--寻路坐标 (钓鱼)
local tAnniversary2015_Barbecue_Goto = {}
tAnniversary2015_Barbecue_Goto["Yugan"] = {}
tAnniversary2015_Barbecue_Goto["Yugan"]["MapId"] = 1002
tAnniversary2015_Barbecue_Goto["Yugan"]["CellX"] = 210
tAnniversary2015_Barbecue_Goto["Yugan"]["CellY"] = 353
tAnniversary2015_Barbecue_Goto["Yugan"]["NpcId"] = 0
tAnniversary2015_Barbecue_Goto["Barbecue"] = {}
tAnniversary2015_Barbecue_Goto["Barbecue"]["MapId"] = 1002
tAnniversary2015_Barbecue_Goto["Barbecue"]["CellX"] = 274
tAnniversary2015_Barbecue_Goto["Barbecue"]["CellY"] = 361
tAnniversary2015_Barbecue_Goto["Barbecue"]["NpcId"] = 0
tAnniversary2015_Barbecue_Goto["Shucai"] = {}
tAnniversary2015_Barbecue_Goto["Shucai"]["MapId"] = 1002
tAnniversary2015_Barbecue_Goto["Shucai"]["CellX"] = 289
tAnniversary2015_Barbecue_Goto["Shucai"]["CellY"] = 361
tAnniversary2015_Barbecue_Goto["Shucai"]["NpcId"] = 18294
tAnniversary2015_Barbecue_Goto["Jirou"] = {}
tAnniversary2015_Barbecue_Goto["Jirou"]["MapId"] = 1002
tAnniversary2015_Barbecue_Goto["Jirou"]["CellX"] = 360
tAnniversary2015_Barbecue_Goto["Jirou"]["CellY"] = 420
tAnniversary2015_Barbecue_Goto["Jirou"]["NpcId"] = 0

local tAnniversary2015_Barbecue_Fishing = {}
tAnniversary2015_Barbecue_Fishing["MinX"] = 209
tAnniversary2015_Barbecue_Fishing["MaxX"] = 211
tAnniversary2015_Barbecue_Fishing["MinY"] = 352
tAnniversary2015_Barbecue_Fishing["MaxY"] = 354
local tAnniversary2015_Barbecue_Barbecuing = {}
tAnniversary2015_Barbecue_Barbecuing["MinX"] = 271
tAnniversary2015_Barbecue_Barbecuing["MaxX"] = 277
tAnniversary2015_Barbecue_Barbecuing["MinY"] = 358
tAnniversary2015_Barbecue_Barbecuing["MaxY"] = 364

-- 怪物 叫天鸡
nAnniversary2015_Barbecue_Monster_Id = 1

------------------------------------------------------------------------------------
------------------------------------------
-- STC掩码隔天重置
function Anniversary2015_Barbecue_ChkStc()
	local nEvent = tAnniversary2015_Barbecue_Stc["Barbecue"]["StcEvent"]
	local nType = tAnniversary2015_Barbecue_Stc["Barbecue"]["StcType"]
	local nNew = tAnniversary2015_Barbecue_Stc["Barbecue"]["New"]
	local nComplete = tAnniversary2015_Barbecue_Stc["Barbecue"]["Complete"]
	--已经完成
	if Task_ChkStcValue(nEvent,nType,">=",nComplete) and Task_StcInterval(nEvent,nType,1,4) then
		Task_SetStatistic(nEvent,nType,0,1)
		Task_SetStcTimestamp(nEvent,nType,0)
		return
	end
	--已接受任务
	if Task_ChkStcValue(nEvent,nType,">=",nNew) and Task_StcInterval(nEvent,nType,1,4) then
		Task_SetStatistic(nEvent,nType,nNew,1)
		Task_SetStcTimestamp(nEvent,nType,0)
		return
	end
	--未接受任务
	if Task_ChkStcValue(nEvent,nType,">=",0) and Task_StcInterval(nEvent,nType,1,4) then
		Task_SetStatistic(nEvent,nType,0,1)
		Task_SetStcTimestamp(nEvent,nType,0)
		return
	end
end

------------------------------------------
-- 通过STC掩码判断当天是否已接受任务
function Anniversary2015_Barbecue_ChkNew()
	local nEvent = tAnniversary2015_Barbecue_Stc["Barbecue"]["StcEvent"]
	local nType = tAnniversary2015_Barbecue_Stc["Barbecue"]["StcType"]
	local nNew = tAnniversary2015_Barbecue_Stc["Barbecue"]["New"]
	local nComplete = tAnniversary2015_Barbecue_Stc["Barbecue"]["Complete"]
	Anniversary2015_Barbecue_ChkStc()
	return Task_ChkStcValue(nEvent,nType,"==",nNew)
end
------------------------------------------
-- 通过STC掩码判断当天是否已完成任务
function Anniversary2015_Barbecue_ChkComplete()
	local nEvent = tAnniversary2015_Barbecue_Stc["Barbecue"]["StcEvent"]
	local nType = tAnniversary2015_Barbecue_Stc["Barbecue"]["StcType"]
	local nNew = tAnniversary2015_Barbecue_Stc["Barbecue"]["New"]
	local nComplete = tAnniversary2015_Barbecue_Stc["Barbecue"]["Complete"]
	Anniversary2015_Barbecue_ChkStc()
	return Task_ChkStcValue(nEvent,nType,"==",nComplete)
end
------------------------------------------
-- 吃烧烤 STC掩码隔天重置
function Anniversary2015_Barbecue_ChkStcEat(sIndex)
	local nEvent = tAnniversary2015_Barbecue_Stc[sIndex]["StcEvent"]
	local nType = tAnniversary2015_Barbecue_Stc[sIndex]["StcType"]
	local nComplete = tAnniversary2015_Barbecue_Stc[sIndex]["Complete"]
	if Task_StcInterval(nEvent,nType,1,4) then
		Task_SetStatistic(nEvent,nType,0,1)
		Task_SetStcTimestamp(nEvent,nType,0)
		return
	end
end
------------------------------------------
-- 通过STC掩码判断当天是否已完成任务
function Anniversary2015_Barbecue_ChkCompleteEat(sIndex)
	local nEvent = tAnniversary2015_Barbecue_Stc[sIndex]["StcEvent"]
	local nType = tAnniversary2015_Barbecue_Stc[sIndex]["StcType"]
	local nComplete = tAnniversary2015_Barbecue_Stc[sIndex]["Complete"]
	Anniversary2015_Barbecue_ChkStcEat(sIndex)
	return Task_ChkStcValue(nEvent,nType,"==",nComplete)
end

------------------------------------------
--概率
function Anniversary2015_Barbecue_Possible(nNumerator,nDenominator)
	local nNum = math.random(1,nDenominator)
	if nNum <= nNumerator then
		return true
	else
		return false
	end
end
------------------------------------------
--寻路
function Anniversary2015_Barbecue_Goto(sIndex)
	Sys_GotoSomeWhere(tAnniversary2015_Barbecue_Goto[sIndex]["CellX"],tAnniversary2015_Barbecue_Goto[sIndex]["CellY"],tAnniversary2015_Barbecue_Goto[sIndex]["MapId"],tAnniversary2015_Barbecue_Goto[sIndex]["NpcId"])
end
------------------------------------------
--击杀怪物掉落
function Anniversary2015_Barbecue_Kill_Monster(nMonsterTypeId)
	local nItemId = tAnniversary2015_Barbecue_Item["Jirou"]["Id"]
	local sLogGetJirou = tAnniversary2015_Barbecue_Log["GetJirou"]
	--叫天鸡
	if nMonsterTypeId ~= nAnniversary2015_Barbecue_Monster_Id then
		return
	end
	--身上有任务，80%掉落
	if Anniversary2015_Barbecue_ChkNew() and Anniversary2015_Barbecue_Possible(8,10) then
		Monster_SysDropItem(nItemId)
	end

end
------------------------------------------
--钓鱼坐标判断
function Anniversary2015_Barbecue_Fishing()
	local nGet_UserPositionX = Get_UserPositionX()
	local nGet_UserPositionY = Get_UserPositionY()
	local nMinX = tAnniversary2015_Barbecue_Fishing["MinX"]
	local nMaxX = tAnniversary2015_Barbecue_Fishing["MaxX"]
	local nMinY = tAnniversary2015_Barbecue_Fishing["MinY"]
	local nMaxY = tAnniversary2015_Barbecue_Fishing["MaxY"]
	
	if nGet_UserPositionX >= nMinX and nGet_UserPositionX <= nMaxX and nGet_UserPositionY >= nMinY and nGet_UserPositionY <= nMaxY then
		return true
	else
		return false
	end
end
------------------------------------------
--烧烤坐标判断
function Anniversary2015_Barbecue_Barbecuing()
	local nGet_UserPositionX = Get_UserPositionX()
	local nGet_UserPositionY = Get_UserPositionY()
	local nMinX = tAnniversary2015_Barbecue_Barbecuing["MinX"]
	local nMaxX = tAnniversary2015_Barbecue_Barbecuing["MaxX"]
	local nMinY = tAnniversary2015_Barbecue_Barbecuing["MinY"]
	local nMaxY = tAnniversary2015_Barbecue_Barbecuing["MaxY"]
	
	if nGet_UserPositionX >= nMinX and nGet_UserPositionX <= nMaxX and nGet_UserPositionY >= nMinY and nGet_UserPositionY <= nMaxY then
		return true
	else
		return false
	end
end

------------------------------------------
--钓鱼成功
function Anniversary2015_Barbecue_FishingSuccess()
	local nItemId = tAnniversary2015_Barbecue_Item["Yu"]["Id"]
	local sLogGetYu = tAnniversary2015_Barbecue_Log["GetYu"]
	--背包满
	if not User_CheckLeftSpace(1) then
		User_TalkChannel2005(tAnniversary2015_Barbecue_Text["TalkChannel2005"]["YuganNoLeftSpace"])
		return
	end
	--成功
	Item_AddItem(nItemId)
	Sys_SaveActionFestivalLog(sLogGetYu)
	--Sys_MsgBox(tAnniversary2015_Barbecue_Text["MsgBox"]["YuganGetFish"])
	User_TalkChannel2005(tAnniversary2015_Barbecue_Text["MsgBox"]["YuganGetFish"])
	User_EffectAdd("self","angelwing")
end
------------------------------------------
--烤鱼成功
function Anniversary2015_Barbecue_BarbecuingYuSuccess()
	local nItemIdYu = tAnniversary2015_Barbecue_Item["Yu"]["Id"]
	local nItemIdKaoyu = tAnniversary2015_Barbecue_Item["Kaoyu"]["Id"]
	local nItemIdShengyu = tAnniversary2015_Barbecue_Item["Shengyu"]["Id"]
	local sLogGetKaoyu = tAnniversary2015_Barbecue_Log["GetKaoyu"]
	local sLogGetShengyu = tAnniversary2015_Barbecue_Log["GetShengyu"]
	local sLogGetKaoyuFail = tAnniversary2015_Barbecue_Log["GetKaoyuFail"] 
	Item_DelItem(nItemIdYu)
	--烤鱼
	if Anniversary2015_Barbecue_Possible(8,10) then
		Item_AddItem(nItemIdKaoyu)
		Sys_SaveActionFestivalLog(sLogGetKaoyu)
		User_TalkChannel2005(tAnniversary2015_Barbecue_Text["TalkChannel2005"]["YuSuccess"])
		User_EffectAdd("self","CircleUp")
		return
	end
	--未熟的烤鱼
	if Anniversary2015_Barbecue_Possible(1,2) then
		Item_AddItem(nItemIdShengyu)
		User_TalkChannel2005(tAnniversary2015_Barbecue_Text["TalkChannel2005"]["YuNotSuccess"])
		Sys_SaveActionFestivalLog(sLogGetShengyu)
		User_EffectAdd("self","BodyDisapear")
		return
	end
	
	--烤没了
	User_TalkChannel2005(tAnniversary2015_Barbecue_Text["TalkChannel2005"]["YuFail"])
	Sys_SaveActionFestivalLog(sLogGetKaoyuFail)
	User_EffectAdd("self","thunder2")
	
end
------------------------------------------
--烤鸡肉成功
function Anniversary2015_Barbecue_BarbecuingJirouSuccess()
	local nItemIdJirou = tAnniversary2015_Barbecue_Item["Jirou"]["Id"]
	local nItemIdKaojirou = tAnniversary2015_Barbecue_Item["Kaojirou"]["Id"]
	local nItemIdShengjirou = tAnniversary2015_Barbecue_Item["Shengjirou"]["Id"]
	local sLogGetKaojirou = tAnniversary2015_Barbecue_Log["GetKaojirou"]
	local sLogGetShengjirou = tAnniversary2015_Barbecue_Log["GetShengjirou"]
	local sLogGetKaojirouFail = tAnniversary2015_Barbecue_Log["GetKaojirouFail"] 
	Item_DelItem(nItemIdJirou)
	--烤鸡肉
	if Anniversary2015_Barbecue_Possible(8,10) then
		Item_AddItem(nItemIdKaojirou)
		Sys_SaveActionFestivalLog(sLogGetKaojirou)
		User_TalkChannel2005(tAnniversary2015_Barbecue_Text["TalkChannel2005"]["JirouSuccess"])
		User_EffectAdd("self","CircleUp")
		return
	end
	--未熟的鸡肉
	if Anniversary2015_Barbecue_Possible(1,2) then
		Item_AddItem(nItemIdShengjirou)
		User_TalkChannel2005(tAnniversary2015_Barbecue_Text["TalkChannel2005"]["JirouNotSuccess"])
		Sys_SaveActionFestivalLog(sLogGetShengjirou)
		User_EffectAdd("self","BodyDisapear")
		return
	end
	
	--烤没了
	User_TalkChannel2005(tAnniversary2015_Barbecue_Text["TalkChannel2005"]["JirouFail"])
	Sys_SaveActionFestivalLog(sLogGetKaojirouFail)
	User_EffectAdd("self","thunder2")
end
------------------------------------------
--烤蔬菜成功
function Anniversary2015_Barbecue_BarbecuingShucaiSuccess()
	local nItemIdShucai = tAnniversary2015_Barbecue_Item["Shucai"]["Id"]
	local nItemIdKaoshucai = tAnniversary2015_Barbecue_Item["Kaoshucai"]["Id"]
	local nItemIdShengshucai = tAnniversary2015_Barbecue_Item["Shengshucai"]["Id"]
	local sLogGetKaoshucai = tAnniversary2015_Barbecue_Log["GetKaoshucai"]
	local sLogGetShengshucai = tAnniversary2015_Barbecue_Log["GetShengshucai"]
	local sLogGetKaoshucaiFail = tAnniversary2015_Barbecue_Log["GetKaoshucaiFail"] 
	Item_DelItem(nItemIdShucai)
	--烤蔬菜
	if Anniversary2015_Barbecue_Possible(8,10) then
		Item_AddItem(nItemIdKaoshucai)
		Sys_SaveActionFestivalLog(sLogGetKaoshucai)
		User_TalkChannel2005(tAnniversary2015_Barbecue_Text["TalkChannel2005"]["ShucaiSuccess"])
		User_EffectAdd("self","CircleUp")
		return
	end
	--未熟的蔬菜
	if Anniversary2015_Barbecue_Possible(1,2) then
		Item_AddItem(nItemIdShengshucai)
		User_TalkChannel2005(tAnniversary2015_Barbecue_Text["TalkChannel2005"]["ShucaiNotSuccess"])
		Sys_SaveActionFestivalLog(sLogGetShengshucai)
		User_EffectAdd("self","BodyDisapear")
		return
	end
	
	--烤没了
	User_TalkChannel2005(tAnniversary2015_Barbecue_Text["TalkChannel2005"]["ShucaiFail"])
	Sys_SaveActionFestivalLog(sLogGetKaoshucaiFail)
	User_EffectAdd("self","thunder2")
end
------------------------------------------
--未熟的鱼烤成功
function Anniversary2015_Barbecue_BarbecuingShengyuSuccess()
	local nItemIdYu = tAnniversary2015_Barbecue_Item["Yu"]["Id"]
	local nItemIdKaoyu = tAnniversary2015_Barbecue_Item["Kaoyu"]["Id"]
	local nItemIdShengyu = tAnniversary2015_Barbecue_Item["Shengyu"]["Id"]
	local sLogKaoShengyu = tAnniversary2015_Barbecue_Log["KaoShengyu"]
	Item_DelItem(nItemIdShengyu)
	Item_AddItem(nItemIdKaoyu)
	Sys_SaveActionFestivalLog(sLogKaoShengyu)
	User_TalkChannel2005(tAnniversary2015_Barbecue_Text["TalkChannel2005"]["ShengyuSuccess"])
	User_EffectAdd("self","CircleUp")
end
------------------------------------------
--未熟的鸡肉烤成功
function Anniversary2015_Barbecue_BarbecuingShengjirouSuccess()
	local nItemIdJirou = tAnniversary2015_Barbecue_Item["Jirou"]["Id"]
	local nItemIdKaojirou = tAnniversary2015_Barbecue_Item["Kaojirou"]["Id"]
	local nItemIdShengjirou = tAnniversary2015_Barbecue_Item["Shengjirou"]["Id"]
	local sLogKaoShengjirou = tAnniversary2015_Barbecue_Log["KaoShengjirou"]
	Item_DelItem(nItemIdShengjirou)
	Item_AddItem(nItemIdKaojirou)
	Sys_SaveActionFestivalLog(sLogKaoShengjirou)
	User_TalkChannel2005(tAnniversary2015_Barbecue_Text["TalkChannel2005"]["ShengjirouSuccess"])
	User_EffectAdd("self","CircleUp")
end
------------------------------------------
--未熟的蔬菜烤成功
function Anniversary2015_Barbecue_BarbecuingShengshucaiSuccess()
	local nItemIdShucai = tAnniversary2015_Barbecue_Item["Shucai"]["Id"]
	local nItemIdKaoshucai = tAnniversary2015_Barbecue_Item["Kaoshucai"]["Id"]
	local nItemIdShengshucai = tAnniversary2015_Barbecue_Item["Shengshucai"]["Id"]
	local sLogKaoShengshucai = tAnniversary2015_Barbecue_Log["KaoShengshucai"]
	Item_DelItem(nItemIdShengshucai)
	Item_AddItem(nItemIdKaoshucai)
	Sys_SaveActionFestivalLog(sLogKaoShengshucai)
	User_TalkChannel2005(tAnniversary2015_Barbecue_Text["TalkChannel2005"]["ShengshucaiSuccess"])
	User_EffectAdd("self","CircleUp")
end
------------------------------------------
--使用鱼竿
function Anniversary2015_Barbecue_UseItem_3005947(nItemId,sItemName)
	--活动前
	if Sys_ChkFullTime(tAnniversary2015_Barbecue_Time["Beftime"]) then
		User_TalkChannel2005(tAnniversary2015_Barbecue_Text["TalkChannel2005"]["YuganBefTime"])
		return
	end
	--活动后
	if not Sys_ChkFullTime(tAnniversary2015_Barbecue_Time["Nowtime"]) then
		Item_DelItem(nItemId)
		Sys_SaveActionFestivalLog(tAnniversary2015_Barbecue_Log["YuganAfTime"])
		User_TalkChannel2005(tAnniversary2015_Barbecue_Text["TalkChannel2005"]["YuganAfTime"])
		User_EffectAdd("self","angelwing")
		return
	end
	--未接任务
	if (not Anniversary2015_Barbecue_ChkNew()) and (not Anniversary2015_Barbecue_ChkComplete()) then
		User_TalkChannel2005(tAnniversary2015_Barbecue_Text["TalkChannel2005"]["YuganNoAccept"])
		return
	end
	--完成任务
	if Anniversary2015_Barbecue_ChkComplete() then
		User_TalkChannel2005(tAnniversary2015_Barbecue_Text["TalkChannel2005"]["YuganComplete"])
		return
	end
	--已接任务 不在地图内
	if Anniversary2015_Barbecue_ChkNew() and Get_UserMapId() ~= tAnniversary2015_Barbecue_Goto["Yugan"]["MapId"] then
		User_TalkChannel2005(tAnniversary2015_Barbecue_Text["TalkChannel2005"]["YuganNotInMap"])
		return
	end
	--已接任务 在地图内 寻路去钓鱼
	if Anniversary2015_Barbecue_ChkNew() and Get_UserMapId() == tAnniversary2015_Barbecue_Goto["Yugan"]["MapId"] and not Anniversary2015_Barbecue_Fishing() then
		Sys_MsgBox(tAnniversary2015_Barbecue_Text["MsgBox"]["YuganGoto"],"Anniversary2015_Barbecue_Goto</S>Yugan")
		return
	end
	--已接任务 在地图内 钓鱼
	if Anniversary2015_Barbecue_ChkNew() and Get_UserMapId() == tAnniversary2015_Barbecue_Goto["Yugan"]["MapId"] and Anniversary2015_Barbecue_Fishing() then
		User_SetExplore(2,tAnniversary2015_Barbecue_Text["SetExplore"]["YuganFishing"],100,"Anniversary2015_Barbecue_FishingSuccess")
		return
	end
	
end
------------------------------------------
--使用大嘴巴鱼
function Anniversary2015_Barbecue_UseItem_3005948(nItemId,sItemName)
	--活动前
	if Sys_ChkFullTime(tAnniversary2015_Barbecue_Time["Beftime"]) then
		User_TalkChannel2005(tAnniversary2015_Barbecue_Text["TalkChannel2005"]["YuBefTime"])
		return
	end
	--活动后
	if not Sys_ChkFullTime(tAnniversary2015_Barbecue_Time["Nowtime"]) then
		Item_DelItem(nItemId)
		Sys_SaveActionFestivalLog(tAnniversary2015_Barbecue_Log["YuAfTime"])
		User_TalkChannel2005(tAnniversary2015_Barbecue_Text["TalkChannel2005"]["YuAfTime"])
		User_EffectAdd("self","angelwing")
		return
	end
	--未接任务
	if (not Anniversary2015_Barbecue_ChkNew()) and (not Anniversary2015_Barbecue_ChkComplete()) then
		User_TalkChannel2005(tAnniversary2015_Barbecue_Text["TalkChannel2005"]["YuNoAccept"])
		return
	end
	--完成任务
	if Anniversary2015_Barbecue_ChkComplete() then
		User_TalkChannel2005(tAnniversary2015_Barbecue_Text["TalkChannel2005"]["YuComplete"])
		return
	end
	--已接任务 不在地图内
	if Anniversary2015_Barbecue_ChkNew() and Get_UserMapId() ~= tAnniversary2015_Barbecue_Goto["Barbecue"]["MapId"] then
		User_TalkChannel2005(tAnniversary2015_Barbecue_Text["TalkChannel2005"]["YuNotInMap"])
		return
	end
	--已接任务 在地图内 寻路到篝火
	if Anniversary2015_Barbecue_ChkNew() and Get_UserMapId() == tAnniversary2015_Barbecue_Goto["Barbecue"]["MapId"] and not Anniversary2015_Barbecue_Barbecuing() then
		Sys_MsgBox(tAnniversary2015_Barbecue_Text["MsgBox"]["BarbecueGoto"],"Anniversary2015_Barbecue_Goto</S>Barbecue")
		return
	end
	--已接任务 在地图内 烤鱼坐标内 背包空间不足
	if Anniversary2015_Barbecue_ChkNew() and Get_UserMapId() == tAnniversary2015_Barbecue_Goto["Barbecue"]["MapId"] and Anniversary2015_Barbecue_Barbecuing() and (not User_CheckLeftSpace(1)) then
		User_TalkChannel2005(tAnniversary2015_Barbecue_Text["TalkChannel2005"]["YuNoLeftSpace"])
		return
	end
	
	--已接任务 在地图内 烤鱼坐标内 背包中没大嘴巴鱼
	if Anniversary2015_Barbecue_ChkNew() and Get_UserMapId() == tAnniversary2015_Barbecue_Goto["Barbecue"]["MapId"] and Anniversary2015_Barbecue_Barbecuing() and (not Item_ChkAccItem(nItemId,1)) then
		User_TalkChannel2005(tAnniversary2015_Barbecue_Text["TalkChannel2005"]["YuNotInBag"])
		return
	end
	--已接任务 在地图内 烤鱼坐标内 背包中有大嘴巴鱼 成功
	if Anniversary2015_Barbecue_ChkNew() and Get_UserMapId() == tAnniversary2015_Barbecue_Goto["Barbecue"]["MapId"] and Anniversary2015_Barbecue_Barbecuing() and Item_ChkAccItem(nItemId,1) then
		User_SetExplore(2,tAnniversary2015_Barbecue_Text["SetExplore"]["Barbecuing"],100,"Anniversary2015_Barbecue_BarbecuingYuSuccess")
		return
	end
	
end
------------------------------------------
--使用鲜嫩小鸡肉
function Anniversary2015_Barbecue_UseItem_3005949(nItemId,sItemName)
	--活动前
	if Sys_ChkFullTime(tAnniversary2015_Barbecue_Time["Beftime"]) then
		User_TalkChannel2005(tAnniversary2015_Barbecue_Text["TalkChannel2005"]["JirouBefTime"])
		return
	end
	--活动后
	if not Sys_ChkFullTime(tAnniversary2015_Barbecue_Time["Nowtime"]) then
		Item_DelItem(nItemId)
		Sys_SaveActionFestivalLog(tAnniversary2015_Barbecue_Log["JirouAfTime"])
		User_TalkChannel2005(tAnniversary2015_Barbecue_Text["TalkChannel2005"]["JirouAfTime"])
		User_EffectAdd("self","angelwing")
		return
	end
	--未接任务
	if (not Anniversary2015_Barbecue_ChkNew()) and (not Anniversary2015_Barbecue_ChkComplete()) then
		User_TalkChannel2005(tAnniversary2015_Barbecue_Text["TalkChannel2005"]["JirouNoAccept"])
		return
	end
	--完成任务
	if Anniversary2015_Barbecue_ChkComplete() then
		User_TalkChannel2005(tAnniversary2015_Barbecue_Text["TalkChannel2005"]["JirouComplete"])
		return
	end
	--已接任务 不在地图内
	if Anniversary2015_Barbecue_ChkNew() and Get_UserMapId() ~= tAnniversary2015_Barbecue_Goto["Barbecue"]["MapId"] then
		User_TalkChannel2005(tAnniversary2015_Barbecue_Text["TalkChannel2005"]["JirouNotInMap"])
		return
	end
	--已接任务 在地图内 寻路到篝火
	if Anniversary2015_Barbecue_ChkNew() and Get_UserMapId() == tAnniversary2015_Barbecue_Goto["Barbecue"]["MapId"] and not Anniversary2015_Barbecue_Barbecuing() then
		Sys_MsgBox(tAnniversary2015_Barbecue_Text["MsgBox"]["BarbecueGoto"],"Anniversary2015_Barbecue_Goto</S>Barbecue")
		return
	end
	--已接任务 在地图内 烤鸡肉坐标内 背包空间不足
	if Anniversary2015_Barbecue_ChkNew() and Get_UserMapId() == tAnniversary2015_Barbecue_Goto["Barbecue"]["MapId"] and Anniversary2015_Barbecue_Barbecuing() and (not User_CheckLeftSpace(1)) then
		User_TalkChannel2005(tAnniversary2015_Barbecue_Text["TalkChannel2005"]["JirouNoLeftSpace"])
		return
	end
	
	--已接任务 在地图内 烤鸡肉坐标内 背包中没鲜嫩小鸡肉
	if Anniversary2015_Barbecue_ChkNew() and Get_UserMapId() == tAnniversary2015_Barbecue_Goto["Barbecue"]["MapId"] and Anniversary2015_Barbecue_Barbecuing() and (not Item_ChkAccItem(nItemId,1)) then
		User_TalkChannel2005(tAnniversary2015_Barbecue_Text["TalkChannel2005"]["JirouNotInBag"])
		return
	end
	
	--已接任务 在地图内 烤鸡肉坐标内 背包中有鲜嫩小鸡肉 成功
	if Anniversary2015_Barbecue_ChkNew() and Get_UserMapId() == tAnniversary2015_Barbecue_Goto["Barbecue"]["MapId"] and Anniversary2015_Barbecue_Barbecuing() and Item_ChkAccItem(nItemId,1) then
		User_SetExplore(2,tAnniversary2015_Barbecue_Text["SetExplore"]["Barbecuing"],100,"Anniversary2015_Barbecue_BarbecuingJirouSuccess")
		return
	end
	
	
end
------------------------------------------
--使用一份蔬菜
function Anniversary2015_Barbecue_UseItem_3005950(nItemId,sItemName)
	--活动前
	if Sys_ChkFullTime(tAnniversary2015_Barbecue_Time["Beftime"]) then
		User_TalkChannel2005(tAnniversary2015_Barbecue_Text["TalkChannel2005"]["ShucaiBefTime"])
		return
	end
	--活动后
	if not Sys_ChkFullTime(tAnniversary2015_Barbecue_Time["Nowtime"]) then
		Item_DelItem(nItemId)
		Sys_SaveActionFestivalLog(tAnniversary2015_Barbecue_Log["ShucaiAfTime"])
		User_TalkChannel2005(tAnniversary2015_Barbecue_Text["TalkChannel2005"]["ShucaiAfTime"])
		User_EffectAdd("self","angelwing")
		return
	end
	--未接任务
	if (not Anniversary2015_Barbecue_ChkNew()) and (not Anniversary2015_Barbecue_ChkComplete()) then
		User_TalkChannel2005(tAnniversary2015_Barbecue_Text["TalkChannel2005"]["ShucaiNoAccept"])
		return
	end
	--完成任务
	if Anniversary2015_Barbecue_ChkComplete() then
		User_TalkChannel2005(tAnniversary2015_Barbecue_Text["TalkChannel2005"]["ShucaiComplete"])
		return
	end
	--已接任务 不在地图内
	if Anniversary2015_Barbecue_ChkNew() and Get_UserMapId() ~= tAnniversary2015_Barbecue_Goto["Barbecue"]["MapId"] then
		User_TalkChannel2005(tAnniversary2015_Barbecue_Text["TalkChannel2005"]["ShucaiNotInMap"])
		return
	end
	--已接任务 在地图内 寻路到篝火
	if Anniversary2015_Barbecue_ChkNew() and Get_UserMapId() == tAnniversary2015_Barbecue_Goto["Barbecue"]["MapId"] and not Anniversary2015_Barbecue_Barbecuing() then
		Sys_MsgBox(tAnniversary2015_Barbecue_Text["MsgBox"]["BarbecueGoto"],"Anniversary2015_Barbecue_Goto</S>Barbecue")
		return
	end
	--已接任务 在地图内 烤蔬菜坐标内 背包空间不足
	if Anniversary2015_Barbecue_ChkNew() and Get_UserMapId() == tAnniversary2015_Barbecue_Goto["Barbecue"]["MapId"] and Anniversary2015_Barbecue_Barbecuing() and (not User_CheckLeftSpace(1)) then
		User_TalkChannel2005(tAnniversary2015_Barbecue_Text["TalkChannel2005"]["ShucaiNoLeftSpace"])
		return
	end
	
	--已接任务 在地图内 烤蔬菜坐标内 背包中没一份蔬菜
	if Anniversary2015_Barbecue_ChkNew() and Get_UserMapId() == tAnniversary2015_Barbecue_Goto["Barbecue"]["MapId"] and Anniversary2015_Barbecue_Barbecuing() and (not Item_ChkAccItem(nItemId,1)) then
		User_TalkChannel2005(tAnniversary2015_Barbecue_Text["TalkChannel2005"]["ShucaiNotInBag"])
		return
	end
	--已接任务 在地图内 烤蔬菜坐标内 背包中有一份蔬菜 成功
	if Anniversary2015_Barbecue_ChkNew() and Get_UserMapId() == tAnniversary2015_Barbecue_Goto["Barbecue"]["MapId"] and Anniversary2015_Barbecue_Barbecuing() and Item_ChkAccItem(nItemId,1) then
		User_SetExplore(2,tAnniversary2015_Barbecue_Text["SetExplore"]["Barbecuing"],100,"Anniversary2015_Barbecue_BarbecuingShucaiSuccess")
		return
	end
end
------------------------------------------
--使用烤鱼
function Anniversary2015_Barbecue_UseItem_3005951(nItemId,sItemName)
	local nEvent = tAnniversary2015_Barbecue_Stc["EatKaoyu"]["StcEvent"]
	local nType = tAnniversary2015_Barbecue_Stc["EatKaoyu"]["StcType"]
	local nComplete = tAnniversary2015_Barbecue_Stc["EatKaoyu"]["Complete"]
	local nItemId = tAnniversary2015_Barbecue_Item["Kaoyu"]["Id"]
	local sLogEatKaoyu = tAnniversary2015_Barbecue_Log["EatKaoyu"]
	--活动前
	if Sys_ChkFullTime(tAnniversary2015_Barbecue_Time["Beftime"]) then
		User_TalkChannel2005(tAnniversary2015_Barbecue_Text["TalkChannel2005"]["KaoyuBefTime"])
		return
	end
	--活动后
	if not Sys_ChkFullTime(tAnniversary2015_Barbecue_Time["Nowtime"]) then
		Item_DelItem(nItemId)
		Sys_SaveActionFestivalLog(tAnniversary2015_Barbecue_Log["KaoyuAfTime"])
		User_TalkChannel2005(tAnniversary2015_Barbecue_Text["TalkChannel2005"]["KaoyuAfTime"])
		User_EffectAdd("self","angelwing")
		return
	end
	--完成任务
	if Anniversary2015_Barbecue_ChkCompleteEat("EatKaoyu") then
		User_TalkChannel2005(tAnniversary2015_Barbecue_Text["TalkChannel2005"]["KaoyuComplete"])
		return
	end
	--满级
	if Get_UserLevel() >= 140 then
		User_TalkChannel2005(tAnniversary2015_Barbecue_Text["TalkChannel2005"]["KaoyuFullLevel"])
		return
	end
	--成功
	Task_AddStatistic(nEvent,nType,1,1)
	Item_DelItem(nItemId)
	User_AddExpTime(5)
	Sys_SaveActionFestivalLog(sLogEatKaoyu)
	--Sys_MsgBox(tAnniversary2015_Barbecue_Text["MsgBox"]["Eat"])
	User_TalkChannel2005(tAnniversary2015_Barbecue_Text["MsgBox"]["Eat"])
	User_EffectAdd("self","angelwing")
end
------------------------------------------
--使用烤鸡肉
function Anniversary2015_Barbecue_UseItem_3005952(nItemId,sItemName)
	local nEvent = tAnniversary2015_Barbecue_Stc["EatKaojirou"]["StcEvent"]
	local nType = tAnniversary2015_Barbecue_Stc["EatKaojirou"]["StcType"]
	local nComplete = tAnniversary2015_Barbecue_Stc["EatKaojirou"]["Complete"]
	local nItemId = tAnniversary2015_Barbecue_Item["Kaojirou"]["Id"]
	local sLogEatKaojirou = tAnniversary2015_Barbecue_Log["EatKaojirou"]
	--活动前
	if Sys_ChkFullTime(tAnniversary2015_Barbecue_Time["Beftime"]) then
		User_TalkChannel2005(tAnniversary2015_Barbecue_Text["TalkChannel2005"]["KaojirouBefTime"])
		return
	end
	--活动后
	if not Sys_ChkFullTime(tAnniversary2015_Barbecue_Time["Nowtime"]) then
		Item_DelItem(nItemId)
		Sys_SaveActionFestivalLog(tAnniversary2015_Barbecue_Log["KaojirouAfTime"])
		User_TalkChannel2005(tAnniversary2015_Barbecue_Text["TalkChannel2005"]["KaojirouAfTime"])
		User_EffectAdd("self","angelwing")
		return
	end
	--完成任务
	if Anniversary2015_Barbecue_ChkCompleteEat("EatKaojirou") then
		User_TalkChannel2005(tAnniversary2015_Barbecue_Text["TalkChannel2005"]["KaojirouComplete"])
		return
	end
	--满级
	if Get_UserLevel() >= 140 then
		User_TalkChannel2005(tAnniversary2015_Barbecue_Text["TalkChannel2005"]["KaojirouFullLevel"])
		return
	end
	--成功
	Task_AddStatistic(nEvent,nType,1,1)
	Item_DelItem(nItemId)
	User_AddExpTime(5)
	Sys_SaveActionFestivalLog(sLogEatKaojirou)
	Sys_MsgBox(tAnniversary2015_Barbecue_Text["MsgBox"]["Eat"])
	User_EffectAdd("self","angelwing")
end
------------------------------------------
--使用烤蔬菜
function Anniversary2015_Barbecue_UseItem_3005953(nItemId,sItemName)
	local nEvent = tAnniversary2015_Barbecue_Stc["EatKaoshucai"]["StcEvent"]
	local nType = tAnniversary2015_Barbecue_Stc["EatKaoshucai"]["StcType"]
	local nComplete = tAnniversary2015_Barbecue_Stc["EatKaoshucai"]["Complete"]
	local nItemId = tAnniversary2015_Barbecue_Item["Kaoshucai"]["Id"]
	local sLogEatKaoshucai = tAnniversary2015_Barbecue_Log["EatKaoshucai"]
	--活动前
	if Sys_ChkFullTime(tAnniversary2015_Barbecue_Time["Beftime"]) then
		User_TalkChannel2005(tAnniversary2015_Barbecue_Text["TalkChannel2005"]["KaoshucaiBefTime"])
		return
	end
	--活动后
	if not Sys_ChkFullTime(tAnniversary2015_Barbecue_Time["Nowtime"]) then
		Item_DelItem(nItemId)
		Sys_SaveActionFestivalLog(tAnniversary2015_Barbecue_Log["KaoshucaiAfTime"])
		User_TalkChannel2005(tAnniversary2015_Barbecue_Text["TalkChannel2005"]["KaoshucaiAfTime"])
		User_EffectAdd("self","angelwing")
		return
	end
	--完成任务
	if Anniversary2015_Barbecue_ChkCompleteEat("EatKaoshucai") then
		User_TalkChannel2005(tAnniversary2015_Barbecue_Text["TalkChannel2005"]["KaoshucaiComplete"])
		return
	end
	--满级
	if Get_UserLevel() >= 140 then
		User_TalkChannel2005(tAnniversary2015_Barbecue_Text["TalkChannel2005"]["KaoshucaiFullLevel"])
		return
	end
	--成功
	Task_AddStatistic(nEvent,nType,1,1)
	Item_DelItem(nItemId)
	User_AddExpTime(5)
	Sys_SaveActionFestivalLog(sLogEatKaoshucai)
	Sys_MsgBox(tAnniversary2015_Barbecue_Text["MsgBox"]["Eat"])
	User_EffectAdd("self","angelwing")
end
------------------------------------------
--使用未熟的烤鱼
function Anniversary2015_Barbecue_UseItem_3005954(nItemId,sItemName)
	--活动前
	if Sys_ChkFullTime(tAnniversary2015_Barbecue_Time["Beftime"]) then
		User_TalkChannel2005(tAnniversary2015_Barbecue_Text["TalkChannel2005"]["ShengyuBefTime"])
		return
	end
	--活动后
	if not Sys_ChkFullTime(tAnniversary2015_Barbecue_Time["Nowtime"]) then
		Item_DelItem(nItemId)
		Sys_SaveActionFestivalLog(tAnniversary2015_Barbecue_Log["ShengyuAfTime"])
		User_TalkChannel2005(tAnniversary2015_Barbecue_Text["TalkChannel2005"]["ShengyuAfTime"])
		User_EffectAdd("self","angelwing")
		return
	end
	--未接任务
	if (not Anniversary2015_Barbecue_ChkNew()) and (not Anniversary2015_Barbecue_ChkComplete()) then
		User_TalkChannel2005(tAnniversary2015_Barbecue_Text["TalkChannel2005"]["ShengyuNoAccept"])
		return
	end
	--完成任务
	if Anniversary2015_Barbecue_ChkComplete() then
		User_TalkChannel2005(tAnniversary2015_Barbecue_Text["TalkChannel2005"]["ShengyuComplete"])
		return
	end
	--已接任务 不在地图内
	if Anniversary2015_Barbecue_ChkNew() and Get_UserMapId() ~= tAnniversary2015_Barbecue_Goto["Barbecue"]["MapId"] then
		User_TalkChannel2005(tAnniversary2015_Barbecue_Text["TalkChannel2005"]["ShengyuNotInMap"])
		return
	end
	--已接任务 在地图内 寻路到篝火
	if Anniversary2015_Barbecue_ChkNew() and Get_UserMapId() == tAnniversary2015_Barbecue_Goto["Barbecue"]["MapId"] and not Anniversary2015_Barbecue_Barbecuing() then
		Sys_MsgBox(tAnniversary2015_Barbecue_Text["MsgBox"]["BarbecueGoto"],"Anniversary2015_Barbecue_Goto</S>Barbecue")
		return
	end
	--已接任务 在地图内 烤鱼坐标内 背包空间不足
	if Anniversary2015_Barbecue_ChkNew() and Get_UserMapId() == tAnniversary2015_Barbecue_Goto["Barbecue"]["MapId"] and Anniversary2015_Barbecue_Barbecuing() and (not User_CheckLeftSpace(1)) then
		User_TalkChannel2005(tAnniversary2015_Barbecue_Text["TalkChannel2005"]["ShengyuNoLeftSpace"])
		return
	end
	
	--已接任务 在地图内 烤鱼坐标内 背包中没大嘴巴鱼
	if Anniversary2015_Barbecue_ChkNew() and Get_UserMapId() == tAnniversary2015_Barbecue_Goto["Barbecue"]["MapId"] and Anniversary2015_Barbecue_Barbecuing() and (not Item_ChkAccItem(nItemId,1)) then
		User_TalkChannel2005(tAnniversary2015_Barbecue_Text["TalkChannel2005"]["ShengyuNotInBag"])
		return
	end
	--已接任务 在地图内 烤鱼坐标内 背包中有大嘴巴鱼 成功
	if Anniversary2015_Barbecue_ChkNew() and Get_UserMapId() == tAnniversary2015_Barbecue_Goto["Barbecue"]["MapId"] and Anniversary2015_Barbecue_Barbecuing() and Item_ChkAccItem(nItemId,1) then
		User_SetExplore(2,tAnniversary2015_Barbecue_Text["SetExplore"]["Barbecuing"],100,"Anniversary2015_Barbecue_BarbecuingShengyuSuccess")
		return
	end
	
end
------------------------------------------
--使用未熟的烤鸡肉
function Anniversary2015_Barbecue_UseItem_3005955(nItemId,sItemName)
	--活动前
	if Sys_ChkFullTime(tAnniversary2015_Barbecue_Time["Beftime"]) then
		User_TalkChannel2005(tAnniversary2015_Barbecue_Text["TalkChannel2005"]["ShengjirouBefTime"])
		return
	end
	--活动后
	if not Sys_ChkFullTime(tAnniversary2015_Barbecue_Time["Nowtime"]) then
		Item_DelItem(nItemId)
		Sys_SaveActionFestivalLog(tAnniversary2015_Barbecue_Log["ShengjirouAfTime"])
		User_TalkChannel2005(tAnniversary2015_Barbecue_Text["TalkChannel2005"]["ShengjirouAfTime"])
		User_EffectAdd("self","angelwing")
		return
	end
	--未接任务
	if (not Anniversary2015_Barbecue_ChkNew()) and (not Anniversary2015_Barbecue_ChkComplete()) then
		User_TalkChannel2005(tAnniversary2015_Barbecue_Text["TalkChannel2005"]["ShengjirouNoAccept"])
		return
	end
	--完成任务
	if Anniversary2015_Barbecue_ChkComplete() then
		User_TalkChannel2005(tAnniversary2015_Barbecue_Text["TalkChannel2005"]["ShengjirouComplete"])
		return
	end
	--已接任务 不在地图内
	if Anniversary2015_Barbecue_ChkNew() and Get_UserMapId() ~= tAnniversary2015_Barbecue_Goto["Barbecue"]["MapId"] then
		User_TalkChannel2005(tAnniversary2015_Barbecue_Text["TalkChannel2005"]["ShengjirouNotInMap"])
		return
	end
	--已接任务 在地图内 寻路到篝火
	if Anniversary2015_Barbecue_ChkNew() and Get_UserMapId() == tAnniversary2015_Barbecue_Goto["Barbecue"]["MapId"] and not Anniversary2015_Barbecue_Barbecuing() then
		Sys_MsgBox(tAnniversary2015_Barbecue_Text["MsgBox"]["BarbecueGoto"],"Anniversary2015_Barbecue_Goto</S>Barbecue")
		return
	end
	--已接任务 在地图内 烤鱼坐标内 背包空间不足
	if Anniversary2015_Barbecue_ChkNew() and Get_UserMapId() == tAnniversary2015_Barbecue_Goto["Barbecue"]["MapId"] and Anniversary2015_Barbecue_Barbecuing() and (not User_CheckLeftSpace(1)) then
		User_TalkChannel2005(tAnniversary2015_Barbecue_Text["TalkChannel2005"]["ShengjirouNoLeftSpace"])
		return
	end
	
	--已接任务 在地图内 烤鱼坐标内 背包中没大嘴巴鱼
	if Anniversary2015_Barbecue_ChkNew() and Get_UserMapId() == tAnniversary2015_Barbecue_Goto["Barbecue"]["MapId"] and Anniversary2015_Barbecue_Barbecuing() and (not Item_ChkAccItem(nItemId,1)) then
		User_TalkChannel2005(tAnniversary2015_Barbecue_Text["TalkChannel2005"]["ShengjirouNotInBag"])
		return
	end
	--已接任务 在地图内 烤鱼坐标内 背包中有大嘴巴鱼 成功
	if Anniversary2015_Barbecue_ChkNew() and Get_UserMapId() == tAnniversary2015_Barbecue_Goto["Barbecue"]["MapId"] and Anniversary2015_Barbecue_Barbecuing() and Item_ChkAccItem(nItemId,1) then
		User_SetExplore(2,tAnniversary2015_Barbecue_Text["SetExplore"]["Barbecuing"],100,"Anniversary2015_Barbecue_BarbecuingShengjirouSuccess")
		return
	end
end
------------------------------------------
--使用未熟的蔬菜
function Anniversary2015_Barbecue_UseItem_3005956(nItemId,sItemName)
	--活动前
	if Sys_ChkFullTime(tAnniversary2015_Barbecue_Time["Beftime"]) then
		User_TalkChannel2005(tAnniversary2015_Barbecue_Text["TalkChannel2005"]["ShengshucaiBefTime"])
		return
	end
	--活动后
	if not Sys_ChkFullTime(tAnniversary2015_Barbecue_Time["Nowtime"]) then
		Item_DelItem(nItemId)
		Sys_SaveActionFestivalLog(tAnniversary2015_Barbecue_Log["ShengshucaiAfTime"])
		User_TalkChannel2005(tAnniversary2015_Barbecue_Text["TalkChannel2005"]["ShengshucaiAfTime"])
		User_EffectAdd("self","angelwing")
		return
	end
	--未接任务
	if (not Anniversary2015_Barbecue_ChkNew()) and (not Anniversary2015_Barbecue_ChkComplete()) then
		User_TalkChannel2005(tAnniversary2015_Barbecue_Text["TalkChannel2005"]["ShengshucaiNoAccept"])
		return
	end
	--完成任务
	if Anniversary2015_Barbecue_ChkComplete() then
		User_TalkChannel2005(tAnniversary2015_Barbecue_Text["TalkChannel2005"]["ShengshucaiComplete"])
		return
	end
	--已接任务 不在地图内
	if Anniversary2015_Barbecue_ChkNew() and Get_UserMapId() ~= tAnniversary2015_Barbecue_Goto["Barbecue"]["MapId"] then
		User_TalkChannel2005(tAnniversary2015_Barbecue_Text["TalkChannel2005"]["ShengshucaiNotInMap"])
		return
	end
	--已接任务 在地图内 寻路到篝火
	if Anniversary2015_Barbecue_ChkNew() and Get_UserMapId() == tAnniversary2015_Barbecue_Goto["Barbecue"]["MapId"] and not Anniversary2015_Barbecue_Barbecuing() then
		Sys_MsgBox(tAnniversary2015_Barbecue_Text["MsgBox"]["BarbecueGoto"],"Anniversary2015_Barbecue_Goto</S>Barbecue")
		return
	end
	--已接任务 在地图内 烤鱼坐标内 背包空间不足
	if Anniversary2015_Barbecue_ChkNew() and Get_UserMapId() == tAnniversary2015_Barbecue_Goto["Barbecue"]["MapId"] and Anniversary2015_Barbecue_Barbecuing() and (not User_CheckLeftSpace(1)) then
		User_TalkChannel2005(tAnniversary2015_Barbecue_Text["TalkChannel2005"]["ShengshucaiNoLeftSpace"])
		return
	end
	
	--已接任务 在地图内 烤鱼坐标内 背包中没大嘴巴鱼
	if Anniversary2015_Barbecue_ChkNew() and Get_UserMapId() == tAnniversary2015_Barbecue_Goto["Barbecue"]["MapId"] and Anniversary2015_Barbecue_Barbecuing() and (not Item_ChkAccItem(nItemId,1)) then
		User_TalkChannel2005(tAnniversary2015_Barbecue_Text["TalkChannel2005"]["ShengshucaiNotInBag"])
		return
	end
	--已接任务 在地图内 烤鱼坐标内 背包中有大嘴巴鱼 成功
	if Anniversary2015_Barbecue_ChkNew() and Get_UserMapId() == tAnniversary2015_Barbecue_Goto["Barbecue"]["MapId"] and Anniversary2015_Barbecue_Barbecuing() and Item_ChkAccItem(nItemId,1) then
		User_SetExplore(2,tAnniversary2015_Barbecue_Text["SetExplore"]["Barbecuing"],100,"Anniversary2015_Barbecue_BarbecuingShengshucaiSuccess")
		return
	end
end

------------------------------------------
--【我来帮忙吧!】
function Anniversary2015_Barbecue_Option103_18292(nNpcId)
	--未领取任务
	if (not Anniversary2015_Barbecue_ChkNew()) and (not Anniversary2015_Barbecue_ChkComplete()) then
		LinkNpcGossipFunc_New(nNpcId,"2-1")
		return
	end
	--已领取任务
	if Anniversary2015_Barbecue_ChkNew() then
		LinkNpcGossipFunc_New(nNpcId,"2-2")
		return
	end
	--已完成任务
	if Anniversary2015_Barbecue_ChkComplete() then
		LinkNpcGossipFunc_New(nNpcId,"2-3")
		return
	end
end
------------------------------------------
--【领取鱼竿】
function Anniversary2015_Barbecue_Option104_18292(nNpcId)
	local nEvent = tAnniversary2015_Barbecue_Stc["Barbecue"]["StcEvent"]
	local nType = tAnniversary2015_Barbecue_Stc["Barbecue"]["StcType"]
	local New = tAnniversary2015_Barbecue_Stc["Barbecue"]["New"]
	local nComplete = tAnniversary2015_Barbecue_Stc["Barbecue"]["Complete"]
	local nItemId = tAnniversary2015_Barbecue_Item["Yugan"]["Id"]
	local nItemNum = tAnniversary2015_Barbecue_Item["Yugan"]["Num"]
	local sLogGetYugan = tAnniversary2015_Barbecue_Log["GetYugan"]
	
	--未接受任务
	if (not Anniversary2015_Barbecue_ChkNew()) and (not Anniversary2015_Barbecue_ChkComplete()) then
		LinkNpcGossipFunc_New(nNpcId,"2-4")
		return
	end
	--已接受任务 补领失败 已有
	if Anniversary2015_Barbecue_ChkNew() and Item_ChkAccItem(nItemId,1) then
		LinkNpcGossipFunc_New(nNpcId,"2-5")
		return
	end
	
	--已接受任务 补领失败 背包满
	if Anniversary2015_Barbecue_ChkNew() and not User_CheckLeftSpace(1) then
		LinkNpcGossipFunc_New(nNpcId,"2-6")
		return
	end
	
	--已接受任务 成功补领
	if Anniversary2015_Barbecue_ChkNew() and ( User_CheckLeftSpace(1) and (not Item_ChkAccItem(nItemId,1)) ) then
		LinkNpcGossipFunc_New(nNpcId,"2-7")
		Item_AddItem(nItemId)
		Sys_SaveActionFestivalLog(sLogGetYugan)
		Sys_MsgBox(tAnniversary2015_Barbecue_Text["MsgBox"]["YuganReGet"])
		User_EffectAdd("self","angelwing")
		return
	end
	
	--已完成任务
	if Anniversary2015_Barbecue_ChkComplete() then
		LinkNpcGossipFunc_New(nNpcId,"2-8")
		return
	end
	
end
------------------------------------------
--【去买蔬菜。】
function Anniversary2015_Barbecue_Option105_18292(nNpcId)
	--自动寻路到精明的大婶
	Anniversary2015_Barbecue_Goto("Shucai")
end

------------------------------------------
--【去弄些鲜肉。】
function Anniversary2015_Barbecue_Option106_18292(nNpcId)
	--寻路打击杀叫天鸡
	Anniversary2015_Barbecue_Goto("Jirou")
	User_TalkChannel2005(tAnniversary2015_Barbecue_Text["TalkChannel2005"]["GetJirou"])
end
------------------------------------------
--【上交烧烤。】
function Anniversary2015_Barbecue_Option107_18292(nNpcId)
	local nEvent = tAnniversary2015_Barbecue_Stc["Barbecue"]["StcEvent"]
	local nType = tAnniversary2015_Barbecue_Stc["Barbecue"]["StcType"]
	local New = tAnniversary2015_Barbecue_Stc["Barbecue"]["New"]
	local nComplete = tAnniversary2015_Barbecue_Stc["Barbecue"]["Complete"]
	local nChkKaoyuItemId = tAnniversary2015_Barbecue_Item["ChkKaoyu"]["Id"]
	local nChkKaoyuItemNum = tAnniversary2015_Barbecue_Item["ChkKaoyu"]["Num"]
	local nChkKaojirouItemId = tAnniversary2015_Barbecue_Item["ChkKaojirou"]["Id"]
	local nChkKaojirouItemNum = tAnniversary2015_Barbecue_Item["ChkKaojirou"]["Num"]
	local nChkKaoshucaiItemId = tAnniversary2015_Barbecue_Item["ChkKaoshucai"]["Id"]
	local nChkKaoshucaiItemNum = tAnniversary2015_Barbecue_Item["ChkKaoshucai"]["Num"]
	local nFestivalId = tAnniversary2015_Barbecue_Item["Jierilibao"]["FestivalId"]
	local nLogId = tAnniversary2015_Barbecue_Item["Jierilibao"]["LogId"]
	local sLogCompleteGet_Jierilibao = tAnniversary2015_Barbecue_Log["CompleteGet_Jierilibao"]
	--未接受任务
	if (not Anniversary2015_Barbecue_ChkNew()) and (not Anniversary2015_Barbecue_ChkComplete()) then
		LinkNpcGossipFunc_New(nNpcId,"2-9")
		return
	end
	--已接受任务 失败 不够
	if Anniversary2015_Barbecue_ChkNew() and not (Item_ChkAccItem(nChkKaoyuItemId,nChkKaoyuItemNum) and Item_ChkAccItem(nChkKaojirouItemId,nChkKaojirouItemNum) and Item_ChkAccItem(nChkKaoshucaiItemId,nChkKaoshucaiItemNum)) then
		LinkNpcGossipFunc_New(nNpcId,"2-10")
		return
	end
	
	--已接受任务 失败 背包满
	if Anniversary2015_Barbecue_ChkNew() and not User_CheckLeftSpace(1) then
		LinkNpcGossipFunc_New(nNpcId,"2-11")
		return
	end
	
	--已接受任务 成功
	if Anniversary2015_Barbecue_ChkNew() and User_CheckLeftSpace(1)  then
		LinkNpcGossipFunc_New(nNpcId,"2-12")
		Task_SetStatistic(nEvent,nType,nComplete,1)
		Task_SetStcTimestamp(nEvent,nType,0)
		--扣除物品发奖励
		Item_DelMulItem(nChkKaoyuItemId,nChkKaoyuItemId,nChkKaoyuItemNum)
		Item_DelMulItem(nChkKaojirouItemId,nChkKaojirouItemId,nChkKaojirouItemNum)
		Item_DelMulItem(nChkKaoshucaiItemId,nChkKaoshucaiItemId,nChkKaoshucaiItemNum)
		--发节日欢庆礼包
		FestivalGeneralPackage_GetGift(nFestivalId,nLogId)
		Sys_SaveActionFestivalLog(sLogCompleteGet_Jierilibao)
		User_EffectAdd("self","angelwing")
		
		return
	end
	--已完成任务
	if Anniversary2015_Barbecue_ChkComplete() then
		LinkNpcGossipFunc_New(nNpcId,"2-13")
		return
	end
end
------------------------------------------
--【我来帮忙吧。】
function Anniversary2015_Barbecue_Option201_18292(nNpcId)
	local nLevel = tAnniversary2015_Barbecue_Condition["Level"]
	local nMetempsychosis = tAnniversary2015_Barbecue_Condition["Metempsychosis"]
	local nEvent = tAnniversary2015_Barbecue_Stc["Barbecue"]["StcEvent"]
	local nType = tAnniversary2015_Barbecue_Stc["Barbecue"]["StcType"]
	local New = tAnniversary2015_Barbecue_Stc["Barbecue"]["New"]
	local nComplete = tAnniversary2015_Barbecue_Stc["Barbecue"]["Complete"]
	local nItemId = tAnniversary2015_Barbecue_Item["Yugan"]["Id"]
	local nItemNum = tAnniversary2015_Barbecue_Item["Yugan"]["Num"]
	local sLogGetYugan = tAnniversary2015_Barbecue_Log["GetYugan"]
	Anniversary2015_Barbecue_ChkStc()
	--等级不足
	if not User_JudgeLevelAndMetempsychosis(nLevel,nMetempsychosis) then
		LinkNpcGossipFunc_New(nNpcId,"3-1")
		return
	end
	
	--当天已完成
	if Task_ChkStcValue(nEvent,nType,"==",nComplete) then
		LinkNpcGossipFunc_New(nNpcId,"3-2")
		return
	end

	--背包空间不够
	if not User_CheckLeftSpace(1) and not Item_ChkAccItem(nItemId,1) then
		LinkNpcGossipFunc_New(nNpcId,"3-3")
		return
	end
	
	--成功
	Task_SetStatistic(nEvent,nType,New,1)
	Task_SetStcTimestamp(nEvent,nType,0)
	if not Item_ChkAccItem(nItemId,1) then
		--背包中没鱼竿，成功
		Item_AddItem(nItemId)
		Sys_SaveActionFestivalLog(sLogGetYugan)
		Sys_MsgBox(tAnniversary2015_Barbecue_Text["MsgBox"]["YuganGet"])
	else 
		--背包中有鱼竿，成功
		User_TalkChannel2005(tAnniversary2015_Barbecue_Text["TalkChannel2005"]["YuganInBag"])
	end
	User_EffectAdd("self","angelwing")
end

------------------------------------------
-- 【给我来一篮吧。】
function Anniversary2015_Barbecue_Option21_18294(nNpcId)

	local nMoney = tAnniversary2015_Barbecue_Item["Money"]['One']
	local nItemId = tAnniversary2015_Barbecue_Item["Shucai"]["Id"]
	local sLogGetShucai = tAnniversary2015_Barbecue_Log["GetShucai"]
	--银子不够
	if not User_CanPutMoney2Bag(-nMoney) then
		LinkNpcGossipFunc_New(nNpcId,"3-1")
		return
	end
	--背包空间不足
	if not User_CheckLeftSpace(1) then
		LinkNpcGossipFunc_New(nNpcId,"3-2")
		return
	end
	--成功
	User_AddMoney(-1*nMoney)
	Item_AddItem(nItemId)
	Sys_SaveActionFestivalLog(sLogGetShucai)
	User_EffectAdd("self","angelwing")
end

------------------------------------------
-- 【给我来十篮！】
function Anniversary2015_Barbecue_Option22_18294(nNpcId)

	local nMoney = tAnniversary2015_Barbecue_Item["Money"]['Ten']
	local nItemId = tAnniversary2015_Barbecue_Item["Shucai"]["Id"]
	local sLogGetShucaiTen = tAnniversary2015_Barbecue_Log["GetShucaiTen"]
	--银子不够
	if not User_CanPutMoney2Bag(-nMoney) then
		LinkNpcGossipFunc_New(nNpcId,"3-3")
		return
	end
	--背包空间不足
	if not User_CheckLeftSpace(1) then
		LinkNpcGossipFunc_New(nNpcId,"3-4")
		return
	end
	--成功
	User_AddMoney(-1*nMoney)
	Item_AddItem(nItemId,0,10)
	Sys_SaveActionFestivalLog(sLogGetShucaiTen)
	User_EffectAdd("self","angelwing")
end

---------------------------------------------------对话模板部分-----------------------------------------
-- //双龙城 烧烤筹备专员老猪
tNpcFace[3579] = 191
tNpcGossip[18292] = tNpcGossip[18292] or DefaultNpc:new{}
tNpcGossip[18292]["OptionHidden"] = 1

--对白
tNpcGossip[18292]["Text1-1"] = {1011,1012,1013}					-- 活动前
tNpcGossip[18292]["Text1-2"] = {1021}							-- 活动后
tNpcGossip[18292]["Text1-3"] = {1031,1032,1033,1034}			-- 活动中（未领取任务）
tNpcGossip[18292]["Text1-4"] = {1041,1042,1043,1044}			-- 活动中（已领取任务）
tNpcGossip[18292]["Text2-1"] = {2011,2012,2013,2014}			-- 【我来帮你吧！（未领取任务）】
tNpcGossip[18292]["Text2-2"] = {2021,2022,2023,2024}			-- 【接1 我来帮你吧！（已领取任务）】
tNpcGossip[18292]["Text2-3"] = {2031,2032}						-- 【接1 我来帮你吧！（已完成任务）】
tNpcGossip[18292]["Text2-4"] = {2041,2042}						-- 【领取鱼竿。（未领取任务）】
tNpcGossip[18292]["Text2-5"] = {2051,2052}						-- 【领取鱼竿。（已领取任务 补领失败 已有）】
tNpcGossip[18292]["Text2-6"] = {2061,2062}						-- 【领取鱼竿。（已领取任务 补领失败 背包满）】
tNpcGossip[18292]["Text2-7"] = {2071,2072}						-- 【领取鱼竿。（已领取任务 补领成功）】
tNpcGossip[18292]["Text2-8"] = {2081,2082}						-- 【领取鱼竿。（已完成任务）】
tNpcGossip[18292]["Text2-9"] = {2091,2092,2093}					-- 【上交烧烤。（未领取任务）】
tNpcGossip[18292]["Text2-10"] = {2101,2102}						-- 【上交烧烤。（已领取任务 失败 不够）】
tNpcGossip[18292]["Text2-11"] = {2111,2112}						-- 【上交烧烤。（已领取任务 失败 背包满）】
tNpcGossip[18292]["Text2-12"] = {2121,2122,2123}				-- 【上交烧烤。（已领取任务 成功）】
tNpcGossip[18292]["Text2-13"] = {2131,2132}						-- 【上交烧烤。（已完成任务）】
tNpcGossip[18292]["Text2-14"] = {2141,2142,2143,2144}			-- 【要怎么帮忙？】
tNpcGossip[18292]["Text3-1"] = {3011,3012}						-- 【我来帮你吧！】 【我来帮忙吧。（失败 等级不足）】
tNpcGossip[18292]["Text3-2"] = {3021,3022}						-- 【我来帮你吧！】 【我来帮忙吧。（失败 今天已经完成过一次了）】
tNpcGossip[18292]["Text3-3"] = {3031,3032}						-- 【我来帮你吧！】 【我来帮忙吧。（失败 背包已满）】
tNpcGossip[18292]["Text1011"] = tAnniversary2015_Barbecue_Text[18292]["Text1011"]
tNpcGossip[18292]["Text1012"] = tAnniversary2015_Barbecue_Text[18292]["Text1012"]
tNpcGossip[18292]["Text1013"] = tAnniversary2015_Barbecue_Text[18292]["Text1013"]
tNpcGossip[18292]["Text1021"] = tAnniversary2015_Barbecue_Text[18292]["Text1021"]
tNpcGossip[18292]["Text1031"] = tAnniversary2015_Barbecue_Text[18292]["Text1031"]
tNpcGossip[18292]["Text1032"] = tAnniversary2015_Barbecue_Text[18292]["Text1032"]
tNpcGossip[18292]["Text1033"] = tAnniversary2015_Barbecue_Text[18292]["Text1033"]
tNpcGossip[18292]["Text1034"] = tAnniversary2015_Barbecue_Text[18292]["Text1034"]
tNpcGossip[18292]["Text1041"] = tAnniversary2015_Barbecue_Text[18292]["Text1041"]
tNpcGossip[18292]["Text1042"] = tAnniversary2015_Barbecue_Text[18292]["Text1042"]
tNpcGossip[18292]["Text1043"] = tAnniversary2015_Barbecue_Text[18292]["Text1043"]
tNpcGossip[18292]["Text1044"] = tAnniversary2015_Barbecue_Text[18292]["Text1044"]
tNpcGossip[18292]["Text2011"] = tAnniversary2015_Barbecue_Text[18292]["Text2011"]
tNpcGossip[18292]["Text2012"] = tAnniversary2015_Barbecue_Text[18292]["Text2012"]
tNpcGossip[18292]["Text2013"] = tAnniversary2015_Barbecue_Text[18292]["Text2013"]
tNpcGossip[18292]["Text2014"] = tAnniversary2015_Barbecue_Text[18292]["Text2014"]
tNpcGossip[18292]["Text2021"] = tAnniversary2015_Barbecue_Text[18292]["Text2021"]
tNpcGossip[18292]["Text2022"] = tAnniversary2015_Barbecue_Text[18292]["Text2022"]
tNpcGossip[18292]["Text2023"] = tAnniversary2015_Barbecue_Text[18292]["Text2023"]
tNpcGossip[18292]["Text2024"] = tAnniversary2015_Barbecue_Text[18292]["Text2024"]
tNpcGossip[18292]["Text2031"] = tAnniversary2015_Barbecue_Text[18292]["Text2031"]
tNpcGossip[18292]["Text2032"] = tAnniversary2015_Barbecue_Text[18292]["Text2032"]
tNpcGossip[18292]["Text2041"] = tAnniversary2015_Barbecue_Text[18292]["Text2041"]
tNpcGossip[18292]["Text2042"] = tAnniversary2015_Barbecue_Text[18292]["Text2042"]
tNpcGossip[18292]["Text2051"] = tAnniversary2015_Barbecue_Text[18292]["Text2051"]
tNpcGossip[18292]["Text2052"] = tAnniversary2015_Barbecue_Text[18292]["Text2052"]
tNpcGossip[18292]["Text2061"] = tAnniversary2015_Barbecue_Text[18292]["Text2061"]
tNpcGossip[18292]["Text2062"] = tAnniversary2015_Barbecue_Text[18292]["Text2062"]
tNpcGossip[18292]["Text2071"] = tAnniversary2015_Barbecue_Text[18292]["Text2071"]
tNpcGossip[18292]["Text2072"] = tAnniversary2015_Barbecue_Text[18292]["Text2072"]
tNpcGossip[18292]["Text2081"] = tAnniversary2015_Barbecue_Text[18292]["Text2081"]
tNpcGossip[18292]["Text2082"] = tAnniversary2015_Barbecue_Text[18292]["Text2082"]
tNpcGossip[18292]["Text2091"] = tAnniversary2015_Barbecue_Text[18292]["Text2091"]
tNpcGossip[18292]["Text2092"] = tAnniversary2015_Barbecue_Text[18292]["Text2092"]
tNpcGossip[18292]["Text2093"] = tAnniversary2015_Barbecue_Text[18292]["Text2093"]
tNpcGossip[18292]["Text2101"] = tAnniversary2015_Barbecue_Text[18292]["Text2101"]
tNpcGossip[18292]["Text2102"] = tAnniversary2015_Barbecue_Text[18292]["Text2102"]
tNpcGossip[18292]["Text2111"] = tAnniversary2015_Barbecue_Text[18292]["Text2111"]
tNpcGossip[18292]["Text2112"] = tAnniversary2015_Barbecue_Text[18292]["Text2112"]
tNpcGossip[18292]["Text2121"] = tAnniversary2015_Barbecue_Text[18292]["Text2121"]
tNpcGossip[18292]["Text2122"] = tAnniversary2015_Barbecue_Text[18292]["Text2122"]
tNpcGossip[18292]["Text2123"] = tAnniversary2015_Barbecue_Text[18292]["Text2123"]
tNpcGossip[18292]["Text2131"] = tAnniversary2015_Barbecue_Text[18292]["Text2131"]
tNpcGossip[18292]["Text2132"] = tAnniversary2015_Barbecue_Text[18292]["Text2132"]
tNpcGossip[18292]["Text2141"] = tAnniversary2015_Barbecue_Text[18292]["Text2141"]
tNpcGossip[18292]["Text2142"] = tAnniversary2015_Barbecue_Text[18292]["Text2142"]
tNpcGossip[18292]["Text2143"] = tAnniversary2015_Barbecue_Text[18292]["Text2143"]
tNpcGossip[18292]["Text2144"] = tAnniversary2015_Barbecue_Text[18292]["Text2144"]
tNpcGossip[18292]["Text3011"] = tAnniversary2015_Barbecue_Text[18292]["Text3011"]
tNpcGossip[18292]["Text3012"] = tAnniversary2015_Barbecue_Text[18292]["Text3012"]
tNpcGossip[18292]["Text3021"] = tAnniversary2015_Barbecue_Text[18292]["Text3021"]
tNpcGossip[18292]["Text3022"] = tAnniversary2015_Barbecue_Text[18292]["Text3022"]
tNpcGossip[18292]["Text3031"] = tAnniversary2015_Barbecue_Text[18292]["Text3031"]
tNpcGossip[18292]["Text3032"] = tAnniversary2015_Barbecue_Text[18292]["Text3032"]



-- 活动前
tNpcGossip[18292]["ChkFunc1-1"] = function ()
	return Sys_ChkFullTime(tAnniversary2015_Barbecue_Time["Beftime"])
end

-- 活动后
tNpcGossip[18292]["ChkFunc1-2"] = function ()
	return not Sys_ChkFullTime(tAnniversary2015_Barbecue_Time["Nowtime"])
end

-- 活动中（未领取任务）
tNpcGossip[18292]["ChkFunc1-3"] = function ()
	return Sys_ChkFullTime(tAnniversary2015_Barbecue_Time["Nowtime"]) and not (Anniversary2015_Barbecue_ChkNew() or Anniversary2015_Barbecue_ChkComplete()) 
end

-- 活动中（已领取任务）
tNpcGossip[18292]["ChkFunc1-4"] = function ()
	return Sys_ChkFullTime(tAnniversary2015_Barbecue_Time["Nowtime"]) and (Anniversary2015_Barbecue_ChkNew() or Anniversary2015_Barbecue_ChkComplete()) 
end

--选项
tNpcGossip[18292]["tOption1-1"] = {101}
tNpcGossip[18292]["tOption1-2"] = {102}
tNpcGossip[18292]["tOption1-3"] = {103,108,109}
tNpcGossip[18292]["tOption1-4"] = {103,104,105,106,107,108,109}
tNpcGossip[18292]["tOption2-1"] = {201,202}
tNpcGossip[18292]["tOption2-2"] = {203}
tNpcGossip[18292]["tOption2-3"] = {204}
tNpcGossip[18292]["tOption2-4"] = {205}
tNpcGossip[18292]["tOption2-5"] = {206}
tNpcGossip[18292]["tOption2-6"] = {207}
tNpcGossip[18292]["tOption2-7"] = {208}
tNpcGossip[18292]["tOption2-8"] = {209}
tNpcGossip[18292]["tOption2-9"] = {210}
tNpcGossip[18292]["tOption2-10"] = {211}
tNpcGossip[18292]["tOption2-11"] = {212}
tNpcGossip[18292]["tOption2-12"] = {213}
tNpcGossip[18292]["tOption2-13"] = {214}
tNpcGossip[18292]["tOption2-14"] = {215}
tNpcGossip[18292]["tOption3-1"] = {301}
tNpcGossip[18292]["tOption3-2"] = {302}
tNpcGossip[18292]["tOption3-3"] = {303}
tNpcGossip[18292]["Option101"] = tAnniversary2015_Barbecue_Text[18292]["Option101"]
tNpcGossip[18292]["Option102"] = tAnniversary2015_Barbecue_Text[18292]["Option102"]
tNpcGossip[18292]["Option103"] = tAnniversary2015_Barbecue_Text[18292]["Option103"]
tNpcGossip[18292]["Option104"] = tAnniversary2015_Barbecue_Text[18292]["Option104"]
tNpcGossip[18292]["Option105"] = tAnniversary2015_Barbecue_Text[18292]["Option105"]
tNpcGossip[18292]["Option106"] = tAnniversary2015_Barbecue_Text[18292]["Option106"]
tNpcGossip[18292]["Option107"] = tAnniversary2015_Barbecue_Text[18292]["Option107"]
tNpcGossip[18292]["Option108"] = tAnniversary2015_Barbecue_Text[18292]["Option108"]
tNpcGossip[18292]["Option109"] = tAnniversary2015_Barbecue_Text[18292]["Option109"]
tNpcGossip[18292]["Option201"] = tAnniversary2015_Barbecue_Text[18292]["Option201"]
tNpcGossip[18292]["Option202"] = tAnniversary2015_Barbecue_Text[18292]["Option202"]
tNpcGossip[18292]["Option203"] = tAnniversary2015_Barbecue_Text[18292]["Option203"]
tNpcGossip[18292]["Option204"] = tAnniversary2015_Barbecue_Text[18292]["Option204"]
tNpcGossip[18292]["Option205"] = tAnniversary2015_Barbecue_Text[18292]["Option205"]
tNpcGossip[18292]["Option206"] = tAnniversary2015_Barbecue_Text[18292]["Option206"]
tNpcGossip[18292]["Option207"] = tAnniversary2015_Barbecue_Text[18292]["Option207"]
tNpcGossip[18292]["Option208"] = tAnniversary2015_Barbecue_Text[18292]["Option208"]
tNpcGossip[18292]["Option209"] = tAnniversary2015_Barbecue_Text[18292]["Option209"]
tNpcGossip[18292]["Option210"] = tAnniversary2015_Barbecue_Text[18292]["Option210"]
tNpcGossip[18292]["Option211"] = tAnniversary2015_Barbecue_Text[18292]["Option211"]
tNpcGossip[18292]["Option212"] = tAnniversary2015_Barbecue_Text[18292]["Option212"]
tNpcGossip[18292]["Option213"] = tAnniversary2015_Barbecue_Text[18292]["Option213"]
tNpcGossip[18292]["Option214"] = tAnniversary2015_Barbecue_Text[18292]["Option214"]
tNpcGossip[18292]["Option215"] = tAnniversary2015_Barbecue_Text[18292]["Option215"]
tNpcGossip[18292]["Option301"] = tAnniversary2015_Barbecue_Text[18292]["Option301"]
tNpcGossip[18292]["Option302"] = tAnniversary2015_Barbecue_Text[18292]["Option302"]
tNpcGossip[18292]["Option303"] = tAnniversary2015_Barbecue_Text[18292]["Option303"]
tNpcGossip[18292]["OptionFunc103"]="Anniversary2015_Barbecue_Option103_18292</N>18292"
tNpcGossip[18292]["OptionFunc104"]="Anniversary2015_Barbecue_Option104_18292</N>18292"
tNpcGossip[18292]["OptionFunc105"]="Anniversary2015_Barbecue_Option105_18292</N>18292"
tNpcGossip[18292]["OptionFunc106"]="Anniversary2015_Barbecue_Option106_18292</N>18292"
tNpcGossip[18292]["OptionFunc107"]="Anniversary2015_Barbecue_Option107_18292</N>18292"
tNpcGossip[18292]["OptionPoint108"]="2-14"
tNpcGossip[18292]["OptionFunc201"]="Anniversary2015_Barbecue_Option201_18292</N>18292"



--tNpcGossip[18292]["OptionPoint13"]="2-1"
--tNpcGossip[18292]["OptionFunc21"]="Anniversary2015_Barbecue_Option201_18292</N>18292"


-------------双龙城 精明的大婶-------------
-- //双龙城 精明的大婶
tNpcFace[3581] = 2

tNpcGossip[18294] = tNpcGossip[18294] or DefaultNpc:new{}
tNpcGossip[18294]["OptionHidden"] = 1

--对白
tNpcGossip[18294]["Text1-1"] = {111}					-- 非活动时间 或者 活动时间未接任务或已完成任务
tNpcGossip[18294]["Text1-2"] = {121}					-- 活动中 且 接有任务
tNpcGossip[18294]["Text2-1"] = {211,212}				-- 【我要买菜。】
tNpcGossip[18294]["Text3-1"] = {311}					-- 【给我来一篮吧。】 （银子不够）
tNpcGossip[18294]["Text3-2"] = {321}					-- 【给我来一篮吧。】 （背包空间不足）
tNpcGossip[18294]["Text3-3"] = {331}					-- 【给我来十篮！】 （银子不够）
tNpcGossip[18294]["Text3-4"] = {341}					-- 【给我来十篮！】 （背包空间不足）
tNpcGossip[18294]["Text111"] = tAnniversary2015_Barbecue_Text[18294]["Text111"]
tNpcGossip[18294]["Text121"] = tAnniversary2015_Barbecue_Text[18294]["Text121"]
tNpcGossip[18294]["Text211"] = tAnniversary2015_Barbecue_Text[18294]["Text211"]
tNpcGossip[18294]["Text212"] = tAnniversary2015_Barbecue_Text[18294]["Text212"]
tNpcGossip[18294]["Text311"] = tAnniversary2015_Barbecue_Text[18294]["Text311"]
tNpcGossip[18294]["Text321"] = tAnniversary2015_Barbecue_Text[18294]["Text321"]
tNpcGossip[18294]["Text331"] = tAnniversary2015_Barbecue_Text[18294]["Text331"]
tNpcGossip[18294]["Text341"] = tAnniversary2015_Barbecue_Text[18294]["Text341"]


-- 非活动时间 或者 活动时间未接任务或已完成任务
tNpcGossip[18294]["ChkFunc1-1"] = function ()
	return (not Sys_ChkFullTime(tAnniversary2015_Barbecue_Time["Nowtime"])) or (not Anniversary2015_Barbecue_ChkNew())
end

-- 活动中 且 接有任务 
tNpcGossip[18294]["ChkFunc1-2"] = function ()
	return Sys_ChkFullTime(tAnniversary2015_Barbecue_Time["Nowtime"]) and Anniversary2015_Barbecue_ChkNew()
end

--选项
tNpcGossip[18294]["tOption1-1"] = {11}
tNpcGossip[18294]["tOption1-2"] = {12,13}
tNpcGossip[18294]["tOption2-1"] = {21,22}
tNpcGossip[18294]["tOption3-1"] = {31}
tNpcGossip[18294]["tOption3-2"] = {32}
tNpcGossip[18294]["tOption3-3"] = {33}
tNpcGossip[18294]["tOption3-4"] = {34}
tNpcGossip[18294]["Option11"] = tAnniversary2015_Barbecue_Text[18294]["Option11"]
tNpcGossip[18294]["Option12"] = tAnniversary2015_Barbecue_Text[18294]["Option12"]
tNpcGossip[18294]["Option13"] = tAnniversary2015_Barbecue_Text[18294]["Option13"]
tNpcGossip[18294]["Option21"] = tAnniversary2015_Barbecue_Text[18294]["Option21"]
tNpcGossip[18294]["Option22"] = tAnniversary2015_Barbecue_Text[18294]["Option22"]
tNpcGossip[18294]["Option31"] = tAnniversary2015_Barbecue_Text[18294]["Option31"]
tNpcGossip[18294]["Option32"] = tAnniversary2015_Barbecue_Text[18294]["Option32"]
tNpcGossip[18294]["Option33"] = tAnniversary2015_Barbecue_Text[18294]["Option33"]
tNpcGossip[18294]["Option34"] = tAnniversary2015_Barbecue_Text[18294]["Option34"]
tNpcGossip[18294]["OptionPoint12"]="2-1"
tNpcGossip[18294]["OptionFunc21"]="Anniversary2015_Barbecue_Option21_18294</N>18294"
tNpcGossip[18294]["OptionFunc22"]="Anniversary2015_Barbecue_Option22_18294</N>18294"

---------------------------------怪物死亡掉落--------------------------------------
-- 1,叫天鸡
--tMonster[1] = tMonster[1] or {}
--tMonster[1]["tFunction"] = tMonster[1]["tFunction"] or {}
--table.insert(tMonster[1]["tFunction"],Anniversary2015_Barbecue_Kill_Monster)



---------------------------------物品模块--------------------------------------
-- 鱼竿
tItem[3005947] = tItem[3005947] or {}
tItem[3005947]["Function"] = function(nItemId,sItemName)
	Anniversary2015_Barbecue_UseItem_3005947(nItemId,sItemName)
end

-- 大嘴巴鱼
tItem[3005948] = tItem[3005948] or {}
tItem[3005948]["Function"] = function(nItemId,sItemName)
	Anniversary2015_Barbecue_UseItem_3005948(nItemId,sItemName)
end

-- 鲜嫩小鸡肉
tItem[3005949] = tItem[3005949] or {}
tItem[3005949]["Function"] = function(nItemId,sItemName)
	Anniversary2015_Barbecue_UseItem_3005949(nItemId,sItemName)
end

-- 一份蔬菜
tItem[3005950] = tItem[3005950] or {}
tItem[3005950]["Function"] = function(nItemId,sItemName)
	Anniversary2015_Barbecue_UseItem_3005950(nItemId,sItemName)
end

-- 烤鱼
tItem[3005951] = tItem[3005951] or {}
tItem[3005951]["Function"] = function(nItemId,sItemName)
	Anniversary2015_Barbecue_UseItem_3005951(nItemId,sItemName)
end

-- 烤鸡肉
tItem[3005952] = tItem[3005952] or {}
tItem[3005952]["Function"] = function(nItemId,sItemName)
	Anniversary2015_Barbecue_UseItem_3005952(nItemId,sItemName)
end

-- 烤蔬菜
tItem[3005953] = tItem[3005953] or {}
tItem[3005953]["Function"] = function(nItemId,sItemName)
	Anniversary2015_Barbecue_UseItem_3005953(nItemId,sItemName)
end

-- 未熟的烤鱼
tItem[3005954] = tItem[3005954] or {}
tItem[3005954]["Function"] = function(nItemId,sItemName)
	Anniversary2015_Barbecue_UseItem_3005954(nItemId,sItemName)
end

-- 未熟的烤鸡肉
tItem[3005955] = tItem[3005955] or {}
tItem[3005955]["Function"] = function(nItemId,sItemName)
	Anniversary2015_Barbecue_UseItem_3005955(nItemId,sItemName)
end

-- 未熟的蔬菜
tItem[3005956] = tItem[3005956] or {}
tItem[3005956]["Function"] = function(nItemId,sItemName)
	Anniversary2015_Barbecue_UseItem_3005956(nItemId,sItemName)
end



