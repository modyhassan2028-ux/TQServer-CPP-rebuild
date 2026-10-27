------------------------------------------------------------------------------------
--Name:			[征服][活动脚本]周年庆活动之篝火晚会之喝酒唱歌（4.27-5.25）
--Creator: 		陈浩文
--Created:		2015/02/27
------------------------------------------------------------------------------------
-- 命名前缀
-- Anniversary2015_Sing_

--活动时间
local tAnniversary2015_Sing_Time = {}
tAnniversary2015_Sing_Time["Beftime"] = "2014-01-01 00:00 2015-05-06 23:59"
tAnniversary2015_Sing_Time["Nowtime"] = "2015-05-07 00:00 2015-05-27 23:59"

--玩家等级要求
tAnniversary2015_Sing_Condition={}
tAnniversary2015_Sing_Condition["Metempsychosis"] = 0
tAnniversary2015_Sing_Condition["Level"] = 80

--活动掩码 13326	13335
--stc(133,26) 1表示成功接受任务获得美酒音符 2表示完成任务获取奖励
--stc(133,27) 演奏阶段		1表示完成了1次 	7表示完成了7	8表示完成
--stc(133,28) 演奏音符		1-7表示
--1 Do1（成功光效：dispel1）
--2 Re2（成功光效：dispel2）
--3 Mi3（成功光效：dispel3）
--4 Fa4（成功光效：dispel4）
--5 So5（成功光效：dispel5）
--6 La6（成功光效：dispel6）
--7 Ti7（成功光效：dispel7）
--stc(133,29) 演奏结果 0正确 大等1错误

local tAnniversary2015_Sing_Stc = {}
tAnniversary2015_Sing_Stc["Sing"]={}
tAnniversary2015_Sing_Stc["Sing"]["StcEvent"] = 133
tAnniversary2015_Sing_Stc["Sing"]["StcType"] = 26
tAnniversary2015_Sing_Stc["Sing"]["New"] = 1
tAnniversary2015_Sing_Stc["Sing"]["Complete"] = 2
tAnniversary2015_Sing_Stc["Play"]={}
tAnniversary2015_Sing_Stc["Play"]["StcEvent"] = 133
tAnniversary2015_Sing_Stc["Play"]["StcType"] = 27
tAnniversary2015_Sing_Stc["Play"]["One"] = 1
tAnniversary2015_Sing_Stc["Play"]["Two"] = 2
tAnniversary2015_Sing_Stc["Play"]["Three"] = 3
tAnniversary2015_Sing_Stc["Play"]["Four"] = 4
tAnniversary2015_Sing_Stc["Play"]["Five"] = 5
tAnniversary2015_Sing_Stc["Play"]["Six"] = 6
tAnniversary2015_Sing_Stc["Play"]["Seven"] = 7
tAnniversary2015_Sing_Stc["Play"]["Complete"] = 8
tAnniversary2015_Sing_Stc["Yinfu"]={}
tAnniversary2015_Sing_Stc["Yinfu"]["StcEvent"] = 133
tAnniversary2015_Sing_Stc["Yinfu"]["StcType"] = 28
tAnniversary2015_Sing_Stc["Yinfu"]["Do1"] = 1
tAnniversary2015_Sing_Stc["Yinfu"]["Re2"] = 2
tAnniversary2015_Sing_Stc["Yinfu"]["Mi3"] = 3
tAnniversary2015_Sing_Stc["Yinfu"]["Fa4"] = 4
tAnniversary2015_Sing_Stc["Yinfu"]["So5"] = 5
tAnniversary2015_Sing_Stc["Yinfu"]["La6"] = 6
tAnniversary2015_Sing_Stc["Yinfu"]["Ti7"] = 7
tAnniversary2015_Sing_Stc["Drink"]={}
tAnniversary2015_Sing_Stc["Drink"]["StcEvent"] = 133
tAnniversary2015_Sing_Stc["Drink"]["StcType"] = 29
tAnniversary2015_Sing_Stc["Drink"]["Error"] = 1
-- log表
local tAnniversary2015_Sing_Log = {}
tAnniversary2015_Sing_Log["GetWine"] = "0,0,0,0,12000040,2,3005981,1"						--获得美酒
tAnniversary2015_Sing_Log["GetDo1"] = "0,0,0,0,12000040,2,3005982,1"						--获得Do1音符
tAnniversary2015_Sing_Log["GetRe2"] = "0,0,0,0,12000040,2,3005983,1"						--获得Re2音符
tAnniversary2015_Sing_Log["GetMi3"] = "0,0,0,0,12000040,2,3005984,1"						--获得Mi3音符
tAnniversary2015_Sing_Log["GetFa4"] = "0,0,0,0,12000040,2,3005985,1"						--获得Fa4音符
tAnniversary2015_Sing_Log["GetSo5"] = "0,0,0,0,12000040,2,3005986,1"						--获得So5音符
tAnniversary2015_Sing_Log["GetLa6"] = "0,0,0,0,12000040,2,3005987,1"						--获得La6音符
tAnniversary2015_Sing_Log["GetTi7"] = "0,0,0,0,12000040,2,3005988,1"						--获得Ti7音符
tAnniversary2015_Sing_Log["DelWine"] = "0,0,3005981,1,12000040,2,0,0"						--删除美酒
tAnniversary2015_Sing_Log["DelDo1"] = "0,0,3005982,1,12000040,2,0,0"						--删除Do1音符
tAnniversary2015_Sing_Log["DelRe2"] = "0,0,3005983,1,12000040,2,0,0"						--删除Re2音符
tAnniversary2015_Sing_Log["DelMi3"] = "0,0,3005984,1,12000040,2,0,0"						--删除Mi3音符
tAnniversary2015_Sing_Log["DelFa4"] = "0,0,3005985,1,12000040,2,0,0"						--删除Fa4音符
tAnniversary2015_Sing_Log["DelSo5"] = "0,0,3005986,1,12000040,2,0,0"						--删除So5音符
tAnniversary2015_Sing_Log["DelLa6"] = "0,0,3005987,1,12000040,2,0,0"						--删除La6音符
tAnniversary2015_Sing_Log["DelTi7"] = "0,0,3005988,1,12000040,2,0,0"						--删除Ti7音符
tAnniversary2015_Sing_Log["DelAllAndGetAll"] = "0,0,3005981[3005982][3005983][3005984][3005985][3005986][3005987][3005988],1[1][1][1][1][1][1][1],12000040,2,3005981[3005982][3005983][3005984][3005985][3005986][3005987][3005988],1[1][1][1][1][1][1][1]"		--批量删除领取
tAnniversary2015_Sing_Log["DelAll"] = "0,0,3005981[3005982][3005983][3005984][3005985][3005986][3005987][3005988],1[1][1][1][1][1][1][1],12000040,2,0,0"		--批量删除


-- 物品
local tAnniversary2015_Sing_Item = {}
tAnniversary2015_Sing_Item["WineId"]=3005981					--美酒
tAnniversary2015_Sing_Item["Do1Id"]=3005982						--Do1音符
tAnniversary2015_Sing_Item["Re2Id"]=3005983						--Re2音符
tAnniversary2015_Sing_Item["Mi3Id"]=3005984						--Mi3音符
tAnniversary2015_Sing_Item["Fa4Id"]=3005985						--Fa4音符
tAnniversary2015_Sing_Item["So5Id"]=3005986						--So5音符
tAnniversary2015_Sing_Item["La6Id"]=3005987						--La6音符
tAnniversary2015_Sing_Item["Ti7Id"]=3005988						--Ti7音符

tAnniversary2015_Sing_Item[3005982] = {}
tAnniversary2015_Sing_Item[3005982]["Id"] = 3005982
tAnniversary2015_Sing_Item[3005982]["Yinfu"] = "Do1"
tAnniversary2015_Sing_Item[3005982]["Effect"] = "dispel1"
tAnniversary2015_Sing_Item[3005982]["Media"] = "sound/Piano_do.mp3"
tAnniversary2015_Sing_Item[3005983] = {}
tAnniversary2015_Sing_Item[3005983]["Id"] = 3005983
tAnniversary2015_Sing_Item[3005983]["Yinfu"] = "Re2"
tAnniversary2015_Sing_Item[3005983]["Effect"] = "dispel2"
tAnniversary2015_Sing_Item[3005983]["Media"] = "sound/Piano_rui.mp3"
tAnniversary2015_Sing_Item[3005984] = {}
tAnniversary2015_Sing_Item[3005984]["Id"] = 3005984
tAnniversary2015_Sing_Item[3005984]["Yinfu"] = "Mi3"
tAnniversary2015_Sing_Item[3005984]["Effect"] = "dispel3"
tAnniversary2015_Sing_Item[3005984]["Media"] = "sound/Piano_Mi.mp3"
tAnniversary2015_Sing_Item[3005985] = {}
tAnniversary2015_Sing_Item[3005985]["Id"] = 3005985
tAnniversary2015_Sing_Item[3005985]["Yinfu"] = "Fa4"
tAnniversary2015_Sing_Item[3005985]["Effect"] = "dispel4"
tAnniversary2015_Sing_Item[3005985]["Media"] = "sound/Piano_Fa.mp3"
tAnniversary2015_Sing_Item[3005986] = {}
tAnniversary2015_Sing_Item[3005986]["Id"] = 3005986
tAnniversary2015_Sing_Item[3005986]["Yinfu"] = "So5"
tAnniversary2015_Sing_Item[3005986]["Effect"] = "dispel5"
tAnniversary2015_Sing_Item[3005986]["Media"] = "sound/Piano_So.mp3"
tAnniversary2015_Sing_Item[3005987] = {}
tAnniversary2015_Sing_Item[3005987]["Id"] = 3005987
tAnniversary2015_Sing_Item[3005987]["Yinfu"] = "La6"
tAnniversary2015_Sing_Item[3005987]["Effect"] = "dispel6"
tAnniversary2015_Sing_Item[3005987]["Media"] = "sound/Piano_La.mp3"
tAnniversary2015_Sing_Item[3005988] = {}
tAnniversary2015_Sing_Item[3005988]["Id"] = 3005988
tAnniversary2015_Sing_Item[3005988]["Yinfu"] = "Ti7"
tAnniversary2015_Sing_Item[3005988]["Effect"] = "dispel7"
tAnniversary2015_Sing_Item[3005988]["Media"] = "sound/Piano_Si.mp3"

--选择 DO1  DO1  Mi3  Ti7  So5  Fa4  Re2
--选择 Mi3  Ti7  So5  Do1  La6  La6  Re2
--选择 Re2  Do1  Fa4  Fa4  So5  La6  Ti7
--选择 So5  So5  Fa4  Mi3  Do1  Ti7  Re2
--选择 Ti7  La6  So5  Fa4  Mi3  Mi3  Re2
--准备5套音乐
tAnniversary2015_Sing_Item["Music"] = {}
tAnniversary2015_Sing_Item["Music"]["One"] = {}
tAnniversary2015_Sing_Item["Music"]["One"]["Num"] = {1,1,3,7,5,4,2}
tAnniversary2015_Sing_Item["Music"]["One"]["Str"] = {"Do1","Do1","Mi3","Ti7","So5","Fa4","Re2"}
tAnniversary2015_Sing_Item["Music"]["Two"] = {}
tAnniversary2015_Sing_Item["Music"]["Two"]["Num"] = {3,7,5,1,6,6,2}
tAnniversary2015_Sing_Item["Music"]["Two"]["Str"] = {"Mi3","Ti7","So5","Do1","La6","La6","Re2"}
tAnniversary2015_Sing_Item["Music"]["Three"] = {}
tAnniversary2015_Sing_Item["Music"]["Three"]["Num"] = {2,1,4,4,5,6,7}
tAnniversary2015_Sing_Item["Music"]["Three"]["Str"] = {"Re2","Do1","Fa4","Fa4","So5","La6","Ti7"}
tAnniversary2015_Sing_Item["Music"]["Four"] = {}
tAnniversary2015_Sing_Item["Music"]["Four"]["Num"] = {5,5,4,3,1,7,2}
tAnniversary2015_Sing_Item["Music"]["Four"]["Str"] = {"So5","So5","Fa4","Mi3","Do1","Ti7","Re2"}
tAnniversary2015_Sing_Item["Music"]["Five"] = {}
tAnniversary2015_Sing_Item["Music"]["Five"]["Num"] = {7,6,5,4,3,3,2}
tAnniversary2015_Sing_Item["Music"]["Five"]["Str"] = {"Ti7","La6","So5","Fa4","Mi3","Mi3","Re2"}
tAnniversary2015_Sing_Item["Jierilibao"]={}			--节日欢庆礼包
tAnniversary2015_Sing_Item["Jierilibao"]["FestivalId"] = 3404
tAnniversary2015_Sing_Item["Jierilibao"]["LogId"] = 12000040
local tAnniversary2015_Sing_Item_Music


------------------------------------------------------------------------------------
------------------------------------------
-- STC掩码隔天重置
function Anniversary2015_Sing_ChkStc()
	local nEvent = tAnniversary2015_Sing_Stc["Sing"]["StcEvent"]
	local nType = tAnniversary2015_Sing_Stc["Sing"]["StcType"]
	local nNew = tAnniversary2015_Sing_Stc["Sing"]["New"]
	local nComplete = tAnniversary2015_Sing_Stc["Sing"]["Complete"]
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
function Anniversary2015_Sing_ChkNew()
	local nEvent = tAnniversary2015_Sing_Stc["Sing"]["StcEvent"]
	local nType = tAnniversary2015_Sing_Stc["Sing"]["StcType"]
	local nNew = tAnniversary2015_Sing_Stc["Sing"]["New"]
	local nComplete = tAnniversary2015_Sing_Stc["Sing"]["Complete"]
	Anniversary2015_Sing_ChkStc()
	return Task_ChkStcValue(nEvent,nType,"==",nNew)
end
------------------------------------------
-- 通过STC掩码判断当天是否已完成任务
function Anniversary2015_Sing_ChkComplete()
	local nEvent = tAnniversary2015_Sing_Stc["Sing"]["StcEvent"]
	local nType = tAnniversary2015_Sing_Stc["Sing"]["StcType"]
	local nNew = tAnniversary2015_Sing_Stc["Sing"]["New"]
	local nComplete = tAnniversary2015_Sing_Stc["Sing"]["Complete"]
	Anniversary2015_Sing_ChkStc()
	return Task_ChkStcValue(nEvent,nType,"==",nComplete)
end
------------------------------------------
-- 演奏阶段 掩码隔天重置
function Anniversary2015_Sing_ChkStcPlay()
	local nEvent = tAnniversary2015_Sing_Stc["Play"]["StcEvent"] 
	local nType = tAnniversary2015_Sing_Stc["Play"]["StcType"]
	if Task_StcInterval(nEvent,nType,1,4) then
		Task_SetStatistic(nEvent,nType,0,1)
		Task_SetStcTimestamp(nEvent,nType,0)
	end
end
------------------------------------------
-- 演奏阶段 完成挑战
function Anniversary2015_Sing_ChkStcPlayComplete()
	local nEvent = tAnniversary2015_Sing_Stc["Play"]["StcEvent"] 
	local nType = tAnniversary2015_Sing_Stc["Play"]["StcType"]
	local nComplete = tAnniversary2015_Sing_Stc["Play"]["Complete"]
	--Anniversary2015_Sing_ChkStcPlay()
	return Task_ChkStcValue(nEvent,nType,"==",nComplete)
end

------------------------------------------
-- 罚酒阶段 掩码隔天重置
function Anniversary2015_Sing_ChkStcDrink()
	local nEvent = tAnniversary2015_Sing_Stc["Drink"]["StcEvent"] 
	local nType = tAnniversary2015_Sing_Stc["Drink"]["StcType"]
	if Task_StcInterval(nEvent,nType,1,4) then
		Task_SetStatistic(nEvent,nType,0,1)
		Task_SetStcTimestamp(nEvent,nType,0)
	end
end
------------------------------------------
-- 罚酒阶段 是否需要罚酒
function Anniversary2015_Sing_ChkStcNeedDrink()
	local nEvent = tAnniversary2015_Sing_Stc["Drink"]["StcEvent"] 
	local nType = tAnniversary2015_Sing_Stc["Drink"]["StcType"]
	local nError = tAnniversary2015_Sing_Stc["Drink"]["Error"]
	--已接受任务
	Anniversary2015_Sing_ChkStcDrink()
	return Task_ChkStcValue(nEvent,nType,">=",nError)
	
end
------------------------------------------
--概率
function Anniversary2015_Sing_Possible(nNumerator,nDenominator)
	local nNum = math.random(1,nDenominator)
	if nNum <= nNumerator then
		return true
	else
		return false
	end
end

------------------------------------------
--选择一套音乐
function Anniversary2015_Sing_Music()
	local tMusic = {}
	if Anniversary2015_Sing_Possible(1,5) then
		tMusic = tAnniversary2015_Sing_Item["Music"]["One"]
		return tMusic
	end
	if Anniversary2015_Sing_Possible(1,4) then
		tMusic = tAnniversary2015_Sing_Item["Music"]["Two"]
		return tMusic
	end
	if Anniversary2015_Sing_Possible(1,3) then
		tMusic = tAnniversary2015_Sing_Item["Music"]["Three"]
		return tMusic
	end
	if Anniversary2015_Sing_Possible(1,2) then
		tMusic = tAnniversary2015_Sing_Item["Music"]["Four"]
		return tMusic
	end
	if Anniversary2015_Sing_Possible(1,1) then
		tMusic = tAnniversary2015_Sing_Item["Music"]["Five"]
		return tMusic
	end
end

------------------------------------------
--演奏阶段
function Anniversary2015_Sing_Play_Jieduan()
	local nEvent = tAnniversary2015_Sing_Stc["Play"]["StcEvent"] 
	local nType = tAnniversary2015_Sing_Stc["Play"]["StcType"]
	local nOne = tAnniversary2015_Sing_Stc["Play"]["One"]
	local nTwo = tAnniversary2015_Sing_Stc["Play"]["Two"]
	local nThree = tAnniversary2015_Sing_Stc["Play"]["Three"]
	local nFour = tAnniversary2015_Sing_Stc["Play"]["Four"]
	local nFive = tAnniversary2015_Sing_Stc["Play"]["Five"]
	local nSix = tAnniversary2015_Sing_Stc["Play"]["Six"]
	local nSeven = tAnniversary2015_Sing_Stc["Play"]["Seven"]
	local nComplete = tAnniversary2015_Sing_Stc["Play"]["Complete"]
	local nReturn = 0
	--Anniversary2015_Sing_ChkStcPlay()
	if Task_ChkStcValue(nEvent,nType,"==",nOne) then
		nReturn = nOne 
	end
	if Task_ChkStcValue(nEvent,nType,"==",nTwo) then
		nReturn = nTwo 
	end
	if Task_ChkStcValue(nEvent,nType,"==",nThree) then
		nReturn = nThree 
	end
	if Task_ChkStcValue(nEvent,nType,"==",nFour) then
		nReturn = nFour 
	end
	if Task_ChkStcValue(nEvent,nType,"==",nFive) then
		nReturn = nFive 
	end
	if Task_ChkStcValue(nEvent,nType,"==",nSix) then
		nReturn = nSix 
	end
	if Task_ChkStcValue(nEvent,nType,"==",nSeven) then
		nReturn = nSeven 
	end
	if Task_ChkStcValue(nEvent,nType,"==",nComplete) then
		nReturn = nComplete 
	end
	return nReturn
end
------------------------------------------
--领取音符和美酒。还需要的空间数量
function Anniversary2015_Sing_NeedSpace()
	local nItemWineId = tAnniversary2015_Sing_Item["WineId"]
	local nItemDo1Id = tAnniversary2015_Sing_Item[3005982]["Id"]
	local nItemRe2Id = tAnniversary2015_Sing_Item[3005983]["Id"]
	local nItemMi3Id = tAnniversary2015_Sing_Item[3005984]["Id"]
	local nItemFa4Id = tAnniversary2015_Sing_Item[3005985]["Id"]
	local nItemSo5Id = tAnniversary2015_Sing_Item[3005986]["Id"]
	local nItemLa6Id = tAnniversary2015_Sing_Item[3005987]["Id"]
	local nItemTi7Id = tAnniversary2015_Sing_Item[3005988]["Id"]
	local nSpace = 8
	--背包中有美酒
	if Item_ChkItem(nItemWineId) then
		nSpace = nSpace - 1
	end
	--背包中有Do1
	if Item_ChkItem(nItemDo1Id) then
		nSpace = nSpace - 1
	end
	--背包中有Re2
	if Item_ChkItem(nItemRe2Id) then
		nSpace = nSpace - 1
	end
	--背包中有Mi3
	if Item_ChkItem(nItemMi3Id) then
		nSpace = nSpace - 1
	end
	--背包中有Fa4
	if Item_ChkItem(nItemFa4Id) then
		nSpace = nSpace - 1
	end
	--背包中有So5
	if Item_ChkItem(nItemSo5Id) then
		nSpace = nSpace - 1
	end
	--背包中有La6
	if Item_ChkItem(nItemLa6Id) then
		nSpace = nSpace - 1
	end
	--背包中有Ti7
	if Item_ChkItem(nItemTi7Id) then
		nSpace = nSpace - 1
	end
	return nSpace
	
end 
------------------------------------------
--领取音符和美酒。空间是否不足
function Anniversary2015_Sing_CheckLeftSpace()
	local nSpace = Anniversary2015_Sing_NeedSpace()
	if nSpace <= 0 then
		return false
	end
	if not User_CheckLeftSpace(nSpace) then
		return true
	end
	return false
end 
------------------------------------------
--领取音符和美酒。物品是否都有
function Anniversary2015_Sing_CheckAllItem()
	local nSpace = Anniversary2015_Sing_NeedSpace()
	if nSpace == 0 then
		return true
	end
	return false
end 
------------------------------------------
--演奏开始时1010提醒
function Anniversary2015_Sing_Play_PlayBegin(sYinfu)
	User_TalkChannel2005(string.format(tAnniversary2015_Sing_Text["MsgBox"]["PlayBegin"],sYinfu))
end
------------------------------------------
--演奏过程中1010提醒
function Anniversary2015_Sing_Play_PlayNow(sYinfu)
	User_TalkChannel2005(string.format(tAnniversary2015_Sing_Text["MsgBox"]["PlayNow"],sYinfu))
end
------------------------------------------
--演奏
function Anniversary2015_Sing_Play()
	tAnniversary2015_Sing_Item_Music = Anniversary2015_Sing_Music()
	local tMusic = tAnniversary2015_Sing_Item_Music
	local nEventYinfu = tAnniversary2015_Sing_Stc["Yinfu"]["StcEvent"] 
	local nTypeYinfu = tAnniversary2015_Sing_Stc["Yinfu"]["StcType"]
	local nEventPlay = tAnniversary2015_Sing_Stc["Play"]["StcEvent"] 
	local nTypePlay = tAnniversary2015_Sing_Stc["Play"]["StcType"]
	local nOnePlay = tAnniversary2015_Sing_Stc["Play"]["One"]
	
	--Anniversary2015_Sing_ChkStcPlay()
	Task_SetStatistic(nEventPlay,nTypePlay,nOnePlay,1)
	Task_SetStcTimestamp(nEventPlay,nTypePlay,0)
	Task_SetStatistic(nEventYinfu,nTypeYinfu,tMusic["Num"][1],1)
	Task_SetStcTimestamp(nEventYinfu,nTypeYinfu,0)
	Sys_MsgBox(string.format(tAnniversary2015_Sing_Text["MsgBox"]["PlayBegin"],tMusic["Str"][1]),"Anniversary2015_Sing_Play_PlayBegin</S>"..tMusic["Str"][1] )
	--Sys_SetLuaTimer(15,"</F>Anniversary2015_Sing_Play_Delay")
	--这里执行倒计时显示
	User_SetTimer(15,'Anniversary2015_Sing_Play_Error',1)
end 
------------------------------------------
--演奏15秒
function Anniversary2015_Sing_Play_Delay()
	local tMusic = tAnniversary2015_Sing_Item_Music
	local nJieduan = Anniversary2015_Sing_Play_Jieduan()
	local nEventSing = tAnniversary2015_Sing_Stc["Sing"]["StcEvent"] 
	local nTypeSing = tAnniversary2015_Sing_Stc["Sing"]["StcType"]
	local nEventPlay = tAnniversary2015_Sing_Stc["Play"]["StcEvent"] 
	local nTypePlay = tAnniversary2015_Sing_Stc["Play"]["StcType"]
	local nOnePlay = tAnniversary2015_Sing_Stc["Play"]["One"]
	local nTwoPlay = tAnniversary2015_Sing_Stc["Play"]["Two"]
	local nThreePlay = tAnniversary2015_Sing_Stc["Play"]["Three"]
	local nFourPlay = tAnniversary2015_Sing_Stc["Play"]["Four"]
	local nFivePlay = tAnniversary2015_Sing_Stc["Play"]["Five"]
	local nSixPlay = tAnniversary2015_Sing_Stc["Play"]["Six"]
	local nSevenPlay = tAnniversary2015_Sing_Stc["Play"]["Seven"]
	local nCompletePlay = tAnniversary2015_Sing_Stc["Play"]["Complete"]
	local nEventYinfu = tAnniversary2015_Sing_Stc["Yinfu"]["StcEvent"] 
	local nTypeYinfu = tAnniversary2015_Sing_Stc["Yinfu"]["StcType"]
	local nEventDrink = tAnniversary2015_Sing_Stc["Drink"]["StcEvent"] 
	local nTypeDrink = tAnniversary2015_Sing_Stc["Drink"]["StcType"]

	--罚酒未罚完超时 
	if Anniversary2015_Sing_ChkStcNeedDrink() then
		--各掩码重置 重头开始
		Task_SetStatistic(nEventSing,nTypeSing,0,1)
		Task_SetStcTimestamp(nEventSing,nTypeSing,0)
		Task_SetStatistic(nEventPlay,nTypePlay,0,1)
		Task_SetStcTimestamp(nEventPlay,nTypePlay,0)
		Task_SetStatistic(nEventYinfu,nTypeYinfu,0,1)
		Task_SetStcTimestamp(nEventYinfu,nTypeYinfu,0)
		Task_SetStatistic(nEventDrink,nTypeDrink,0,1)
		Task_SetStcTimestamp(nEventDrink,nTypeDrink,0)
		User_TalkChannel2005(tAnniversary2015_Sing_Text["TalkChannel2005"]["PlayOverTimeDrink"])
		return
	end
	--未输入正确答案超时
	if Task_StcInterval(nEventYinfu,nTypeYinfu,15,0) then
		--各掩码重置 重头开始
		Task_SetStatistic(nEventSing,nTypeSing,0,1)
		Task_SetStcTimestamp(nEventSing,nTypeSing,0)
		Task_SetStatistic(nEventPlay,nTypePlay,0,1)
		Task_SetStcTimestamp(nEventPlay,nTypePlay,0)
		Task_SetStatistic(nEventYinfu,nTypeYinfu,0,1)
		Task_SetStcTimestamp(nEventYinfu,nTypeYinfu,0)
		Task_SetStatistic(nEventDrink,nTypeDrink,0,1)
		Task_SetStcTimestamp(nEventDrink,nTypeDrink,0)
		User_TalkChannel2005(tAnniversary2015_Sing_Text["TalkChannel2005"]["PlayOverTimePlay"])
		return
	end
		
	--成功
	Task_AddStatistic(nEventPlay,nTypePlay,1,1)
	--最后一个阶段
	if Task_ChkStcValue(nEventPlay,nTypePlay,"==",nCompletePlay) then
		Task_AddStatistic(nEventYinfu,nTypeYinfu,1,1)
		Sys_MsgBox(tAnniversary2015_Sing_Text["MsgBox"]["PlayEnd"] )
		return
	end
	Task_SetStatistic(nEventYinfu,nTypeYinfu,tMusic["Num"][nJieduan],1)
	Task_SetStcTimestamp(nEventYinfu,nTypeYinfu,0)
	Sys_MsgBox(string.format(tAnniversary2015_Sing_Text["MsgBox"]["PlayNow"],tMusic["Str"][nJieduan]),"Anniversary2015_Sing_Play_PlayNow</S>"..tMusic["Str"][nJieduan] )
	--Sys_SetLuaTimer(15,"</F>Anniversary2015_Sing_Play_Delay")
	--这里执行倒计时显示
	User_SetTimer(15,'Anniversary2015_Sing_Play_Error',1)
end 
------------------------------------------
--超时给提示
function Anniversary2015_Sing_Play_Error()
	local nEventSing = tAnniversary2015_Sing_Stc["Sing"]["StcEvent"] 
	local nTypeSing = tAnniversary2015_Sing_Stc["Sing"]["StcType"]
	local nEventPlay = tAnniversary2015_Sing_Stc["Play"]["StcEvent"] 
	local nTypePlay = tAnniversary2015_Sing_Stc["Play"]["StcType"]
	local nEventYinfu = tAnniversary2015_Sing_Stc["Yinfu"]["StcEvent"] 
	local nTypeYinfu = tAnniversary2015_Sing_Stc["Yinfu"]["StcType"]
	local nEventDrink = tAnniversary2015_Sing_Stc["Drink"]["StcEvent"] 
	local nTypeDrink = tAnniversary2015_Sing_Stc["Drink"]["StcType"]
	local nErrorDrink = tAnniversary2015_Sing_Stc["Drink"]["Error"]

	--未输入正确答案超时
	if Task_StcInterval(nEventYinfu,nTypeYinfu,15,0) then
		--各掩码重置 重头开始
		Task_SetStatistic(nEventSing,nTypeSing,0,1)
		Task_SetStcTimestamp(nEventSing,nTypeSing,0)
		Task_SetStatistic(nEventPlay,nTypePlay,0,1)
		Task_SetStcTimestamp(nEventPlay,nTypePlay,0)
		Task_SetStatistic(nEventYinfu,nTypeYinfu,0,1)
		Task_SetStcTimestamp(nEventYinfu,nTypeYinfu,0)
		Task_SetStatistic(nEventDrink,nTypeDrink,0,1)
		Task_SetStcTimestamp(nEventDrink,nTypeDrink,0)
		User_TalkChannel2005(tAnniversary2015_Sing_Text["TalkChannel2005"]["PlayOverTimePlay"])
		return
	end
end
------------------------------------------
--使用美酒
function Anniversary2015_Sing_UseItem_3005981(nItemId,sItemName)
	local nEvent = tAnniversary2015_Sing_Stc["Drink"]["StcEvent"] 
	local nType = tAnniversary2015_Sing_Stc["Drink"]["StcType"]

	--活动前
	if Sys_ChkFullTime(tAnniversary2015_Sing_Time["Beftime"]) then
		User_TalkChannel2005(tAnniversary2015_Sing_Text["TalkChannel2005"]["WineBefTime"])
		return
	end
	--活动后
	if not Sys_ChkFullTime(tAnniversary2015_Sing_Time["Nowtime"]) then
		Item_DelItem(nItemId)
		Sys_SaveActionFestivalLog(tAnniversary2015_Sing_Log["DelWine"])
		User_TalkChannel2005(tAnniversary2015_Sing_Text["TalkChannel2005"]["WineAfTime"])
		User_EffectAdd("self","angelwing")
		return
	end
	Anniversary2015_Sing_ChkStcDrink()
	--无需罚酒
	if not Anniversary2015_Sing_ChkStcNeedDrink() then
		User_TalkChannel2005(tAnniversary2015_Sing_Text["TalkChannel2005"]["PlayNoNeedDrink"])
		return
	end
	--罚酒成功
	Task_SetStatistic(nEvent,nType,0,1)
	Task_SetStcTimestamp(nEvent,nType,0)
	User_TalkChannel2005(tAnniversary2015_Sing_Text["TalkChannel2005"]["PlayDrink"])
end

------------------------------------------
--使用音符
function Anniversary2015_Sing_UseItem(nItemId,sItemName)
	local nEventSing = tAnniversary2015_Sing_Stc["Sing"]["StcEvent"] 
	local nTypeSing = tAnniversary2015_Sing_Stc["Sing"]["StcType"]
	local nEventPlay = tAnniversary2015_Sing_Stc["Play"]["StcEvent"] 
	local nTypePlay = tAnniversary2015_Sing_Stc["Play"]["StcType"]
	local nEventYinfu = tAnniversary2015_Sing_Stc["Yinfu"]["StcEvent"] 
	local nTypeYinfu = tAnniversary2015_Sing_Stc["Yinfu"]["StcType"]
	local nEventDrink = tAnniversary2015_Sing_Stc["Drink"]["StcEvent"] 
	local nTypeDrink = tAnniversary2015_Sing_Stc["Drink"]["StcType"]
	local nErrorDrink = tAnniversary2015_Sing_Stc["Drink"]["Error"]
	local sYinfu = tAnniversary2015_Sing_Item[nItemId]["Yinfu"]
	local sEffect = tAnniversary2015_Sing_Item[nItemId]["Effect"]
	local sMedia = tAnniversary2015_Sing_Item[nItemId]["Media"]
	local nCompletePlay = tAnniversary2015_Sing_Stc["Play"]["Complete"]
	
	local nYinfu = tAnniversary2015_Sing_Stc["Yinfu"][sYinfu]
	-- 玩家弹奏的音符
	--活动前
	if Sys_ChkFullTime(tAnniversary2015_Sing_Time["Beftime"]) then
		User_TalkChannel2005(tAnniversary2015_Sing_Text["TalkChannel2005"][sYinfu.."BefTime"])
		return
	end
	--活动后
	if not Sys_ChkFullTime(tAnniversary2015_Sing_Time["Nowtime"]) then
		Item_DelItem(nItemId)
		Sys_SaveActionFestivalLog(tAnniversary2015_Sing_Log["Del"..sYinfu])
		User_TalkChannel2005(tAnniversary2015_Sing_Text["TalkChannel2005"][sYinfu.."AfTime"])
		User_EffectAdd("self","angelwing")
		return
	end
	--未接任务 
	if not Anniversary2015_Sing_ChkNew() and not Anniversary2015_Sing_ChkComplete() then
		--User_EffectAdd("self",sEffect)
		--播放音乐
		--User_MediaPlay(sMedia)
		User_TalkChannel2005(tAnniversary2015_Sing_Text["TalkChannel2005"]["PlayOverTimePlay"])
		return
	end
	--完成任务
	if Anniversary2015_Sing_ChkComplete() then
		--播放音乐
		User_EffectAdd("self",sEffect)
		User_MediaPlay(sMedia)
		return
	end
	--完成挑战
	if Task_ChkStcValue(nEventPlay,nTypePlay,"==",nCompletePlay) then
		User_TalkChannel2005(tAnniversary2015_Sing_Text["MsgBox"]["PlayEnd"] )
		return
	end
	--未输入正确答案超时
	if Task_StcInterval(nEventYinfu,nTypeYinfu,15,0) then
		--各掩码重置 重头开始
		Task_SetStatistic(nEventSing,nTypeSing,0,1)
		Task_SetStcTimestamp(nEventSing,nTypeSing,0)
		Task_SetStatistic(nEventPlay,nTypePlay,0,1)
		Task_SetStcTimestamp(nEventPlay,nTypePlay,0)
		Task_SetStatistic(nEventYinfu,nTypeYinfu,0,1)
		Task_SetStcTimestamp(nEventYinfu,nTypeYinfu,0)
		Task_SetStatistic(nEventDrink,nTypeDrink,0,1)
		Task_SetStcTimestamp(nEventDrink,nTypeDrink,0)
		User_TalkChannel2005(tAnniversary2015_Sing_Text["TalkChannel2005"]["PlayOverTimePlay"])
		return
	end
	--有罚酒未喝 或 不正确
	if Anniversary2015_Sing_ChkStcNeedDrink() or not Task_ChkStcValue(nEventYinfu,nTypeYinfu,"==",nYinfu) then
		Task_SetStatistic(nEventDrink,nTypeDrink,nErrorDrink,1)
		Task_SetStcTimestamp(nEventDrink,nTypeDrink,0)
		User_TalkChannel2005(tAnniversary2015_Sing_Text["TalkChannel2005"]["PlayError"])
		return
	end
	--正确
	Task_SetStatistic(nEventDrink,nTypeDrink,0,1)
	Task_SetStcTimestamp(nEventDrink,nTypeDrink,0)
	Task_SetStcTimestamp(nEventYinfu,nTypeYinfu,0)
	User_EffectAdd("self",sEffect)
	--播放音乐
	User_MediaPlay(sMedia)
	Anniversary2015_Sing_Play_Delay()
end
------------------------------------------
--【我来挑战琴谱。】
function Anniversary2015_Sing_Option103_18298(nNpcId)
	local nLevel = tAnniversary2015_Sing_Condition["Level"]
	local nMetempsychosis = tAnniversary2015_Sing_Condition["Metempsychosis"]
	local nEvent = tAnniversary2015_Sing_Stc["Sing"]["StcEvent"]
	local nType = tAnniversary2015_Sing_Stc["Sing"]["StcType"]
	local nNew = tAnniversary2015_Sing_Stc["Sing"]["New"]
	local nComplete = tAnniversary2015_Sing_Stc["Sing"]["Complete"]
	
	Anniversary2015_Sing_ChkStc()
	--已经完成
	if Task_ChkStcValue(nEvent,nType,">=",nComplete) then
		LinkNpcGossipFunc_New(nNpcId,"2-1")
		return
	end
	--已接受任务
	if Task_ChkStcValue(nEvent,nType,">=",nNew) then
		LinkNpcGossipFunc_New(nNpcId,"2-11")
		return
	end
	--等级不足
	if not User_JudgeLevelAndMetempsychosis(nLevel,nMetempsychosis) then
		LinkNpcGossipFunc_New(nNpcId,"2-2")
		return
	end
	--成功
	LinkNpcGossipFunc_New(nNpcId,"2-3")
end
------------------------------------------
--【领取音符和美酒。】
function Anniversary2015_Sing_Option104_18298(nNpcId)
	local nLevel = tAnniversary2015_Sing_Condition["Level"]
	local nMetempsychosis = tAnniversary2015_Sing_Condition["Metempsychosis"]
	local nEvent = tAnniversary2015_Sing_Stc["Sing"]["StcEvent"]
	local nType = tAnniversary2015_Sing_Stc["Sing"]["StcType"]
	local nNew = tAnniversary2015_Sing_Stc["Sing"]["New"]
	local nComplete = tAnniversary2015_Sing_Stc["Sing"]["Complete"]
	local nItemWineId = tAnniversary2015_Sing_Item["WineId"]
	local nItemDo1Id = tAnniversary2015_Sing_Item[3005982]["Id"]
	local nItemRe2Id = tAnniversary2015_Sing_Item[3005983]["Id"]
	local nItemMi3Id = tAnniversary2015_Sing_Item[3005984]["Id"]
	local nItemFa4Id = tAnniversary2015_Sing_Item[3005985]["Id"]
	local nItemSo5Id = tAnniversary2015_Sing_Item[3005986]["Id"]
	local nItemLa6Id = tAnniversary2015_Sing_Item[3005987]["Id"]
	local nItemTi7Id = tAnniversary2015_Sing_Item[3005988]["Id"]
	--未接任务
	if not Task_ChkStcValue(nEvent,nType,">=",nComplete) and not Task_ChkStcValue(nEvent,nType,">=",nNew) then
		LinkNpcGossipFunc_New(nNpcId,"2-11")
		return
	end
	--已经完成
	if Task_ChkStcValue(nEvent,nType,">=",nComplete) then
		LinkNpcGossipFunc_New(nNpcId,"2-4")
		return
	end
	--等级不足
	if not User_JudgeLevelAndMetempsychosis(nLevel,nMetempsychosis) then
		LinkNpcGossipFunc_New(nNpcId,"2-2")
		return
	end
	--背包不足
	if Anniversary2015_Sing_CheckLeftSpace() then
		LinkNpcGossipFunc_New(nNpcId,"2-5")
		return
	end
	--都有
	if Anniversary2015_Sing_CheckAllItem() then
		LinkNpcGossipFunc_New(nNpcId,"2-6")
		return
	end
	--成功
	if Item_ChkItem(nItemWineId) then
		Item_DelAllItemByType(nItemWineId)
	end
	if Item_ChkItem(nItemDo1Id) then
		Item_DelAllItemByType(nItemDo1Id)
	end
	if Item_ChkItem(nItemRe2Id) then
		Item_DelAllItemByType(nItemRe2Id)
	end
	if Item_ChkItem(nItemMi3Id) then
		Item_DelAllItemByType(nItemMi3Id)
	end
	if Item_ChkItem(nItemFa4Id) then
		Item_DelAllItemByType(nItemFa4Id)
	end
	if Item_ChkItem(nItemSo5Id) then
		Item_DelAllItemByType(nItemSo5Id)
	end
	if Item_ChkItem(nItemLa6Id) then
		Item_DelAllItemByType(nItemLa6Id)
	end
	if Item_ChkItem(nItemTi7Id) then
		Item_DelAllItemByType(nItemTi7Id)
	end
	Item_AddItem(nItemWineId)
	Item_AddItem(nItemDo1Id)
	Item_AddItem(nItemRe2Id)
	Item_AddItem(nItemMi3Id)
	Item_AddItem(nItemFa4Id)
	Item_AddItem(nItemSo5Id)
	Item_AddItem(nItemLa6Id)
	Item_AddItem(nItemTi7Id)
	Sys_SaveActionFestivalLog(tAnniversary2015_Sing_Log["DelAllAndGetAll"])
	Sys_MsgBox(tAnniversary2015_Sing_Text["MsgBox"]["GetItem"])
	User_EffectAdd("self","angelwing")
end

------------------------------------------
--【领取奖励。】
function Anniversary2015_Sing_Option105_18298(nNpcId)
	local nLevel = tAnniversary2015_Sing_Condition["Level"]
	local nMetempsychosis = tAnniversary2015_Sing_Condition["Metempsychosis"]
	local nEvent = tAnniversary2015_Sing_Stc["Sing"]["StcEvent"]
	local nType = tAnniversary2015_Sing_Stc["Sing"]["StcType"]
	local nNew = tAnniversary2015_Sing_Stc["Sing"]["New"]
	local nComplete = tAnniversary2015_Sing_Stc["Sing"]["Complete"]
	local nItemWineId = tAnniversary2015_Sing_Item["WineId"]
	local nItemDo1Id = tAnniversary2015_Sing_Item[3005982]["Id"]
	local nItemRe2Id = tAnniversary2015_Sing_Item[3005983]["Id"]
	local nItemMi3Id = tAnniversary2015_Sing_Item[3005984]["Id"]
	local nItemFa4Id = tAnniversary2015_Sing_Item[3005985]["Id"]
	local nItemSo5Id = tAnniversary2015_Sing_Item[3005986]["Id"]
	local nItemLa6Id = tAnniversary2015_Sing_Item[3005987]["Id"]
	local nItemTi7Id = tAnniversary2015_Sing_Item[3005988]["Id"]
	local nFestivalId = tAnniversary2015_Sing_Item["Jierilibao"]["FestivalId"]
	local nLogId = tAnniversary2015_Sing_Item["Jierilibao"]["LogId"]
	--未接任务
	if not Anniversary2015_Sing_ChkNew() and not Anniversary2015_Sing_ChkComplete() then
		LinkNpcGossipFunc_New(nNpcId,"2-11")
		return
	end
	--已经完成
	if Anniversary2015_Sing_ChkComplete() then
		LinkNpcGossipFunc_New(nNpcId,"2-1")
		return
	end
	--未挑战
	if not Anniversary2015_Sing_ChkStcPlayComplete() then
		LinkNpcGossipFunc_New(nNpcId,"2-8")
		return
	end
	--背包不足
	if not User_CheckLeftSpace(1) then
		LinkNpcGossipFunc_New(nNpcId,"2-9")
		return
	end
	--成功
	Task_SetStatistic(nEvent,nType,nComplete,1)
	Task_SetStcTimestamp(nEvent,nType,0)
	
	if Item_ChkItem(nItemWineId) then
		Item_DelAllItemByType(nItemWineId)
	end
	if Item_ChkItem(nItemDo1Id) then
		Item_DelAllItemByType(nItemDo1Id)
	end
	if Item_ChkItem(nItemRe2Id) then
		Item_DelAllItemByType(nItemRe2Id)
	end
	if Item_ChkItem(nItemMi3Id) then
		Item_DelAllItemByType(nItemMi3Id)
	end
	if Item_ChkItem(nItemFa4Id) then
		Item_DelAllItemByType(nItemFa4Id)
	end
	if Item_ChkItem(nItemSo5Id) then
		Item_DelAllItemByType(nItemSo5Id)
	end
	if Item_ChkItem(nItemLa6Id) then
		Item_DelAllItemByType(nItemLa6Id)
	end
	if Item_ChkItem(nItemTi7Id) then
		Item_DelAllItemByType(nItemTi7Id)
	end
	Sys_SaveActionFestivalLog(tAnniversary2015_Sing_Log["DelAll"])
	--发节日欢庆礼包
	FestivalGeneralPackage_GetGift(nFestivalId,nLogId)
	User_EffectAdd("self","angelwing")
	LinkNpcGossipFunc_New(nNpcId,"2-10")
	
end
------------------------------------------
--【我来挑战琴谱。】 【我要挑战。】
function Anniversary2015_Sing_Option203_18298(nNpcId)
	local nEvent = tAnniversary2015_Sing_Stc["Sing"]["StcEvent"]
	local nType = tAnniversary2015_Sing_Stc["Sing"]["StcType"]
	local nNew = tAnniversary2015_Sing_Stc["Sing"]["New"]
	local nComplete = tAnniversary2015_Sing_Stc["Sing"]["Complete"]
	local nItemWineId = tAnniversary2015_Sing_Item["WineId"]
	local nItemDo1Id = tAnniversary2015_Sing_Item[3005982]["Id"]
	local nItemRe2Id = tAnniversary2015_Sing_Item[3005983]["Id"]
	local nItemMi3Id = tAnniversary2015_Sing_Item[3005984]["Id"]
	local nItemFa4Id = tAnniversary2015_Sing_Item[3005985]["Id"]
	local nItemSo5Id = tAnniversary2015_Sing_Item[3005986]["Id"]
	local nItemLa6Id = tAnniversary2015_Sing_Item[3005987]["Id"]
	local nItemTi7Id = tAnniversary2015_Sing_Item[3005988]["Id"]
	--直接删除所有任务物品
	if Item_ChkItem(nItemWineId) then
		Item_DelAllItemByType(nItemWineId)
	end
	if Item_ChkItem(nItemDo1Id) then
		Item_DelAllItemByType(nItemDo1Id)
	end
	if Item_ChkItem(nItemRe2Id) then
		Item_DelAllItemByType(nItemRe2Id)
	end
	if Item_ChkItem(nItemMi3Id) then
		Item_DelAllItemByType(nItemMi3Id)
	end
	if Item_ChkItem(nItemFa4Id) then
		Item_DelAllItemByType(nItemFa4Id)
	end
	if Item_ChkItem(nItemSo5Id) then
		Item_DelAllItemByType(nItemSo5Id)
	end
	if Item_ChkItem(nItemLa6Id) then
		Item_DelAllItemByType(nItemLa6Id)
	end
	if Item_ChkItem(nItemTi7Id) then
		Item_DelAllItemByType(nItemTi7Id)
	end
	
	--背包不足
	if not User_CheckLeftSpace(8) then
		LinkNpcGossipFunc_New(nNpcId,"3-1")
		return
	end
	--成功
	Task_SetStatistic(nEvent,nType,nNew,1)
	Task_SetStcTimestamp(nEvent,nType,0)
	Item_AddItem(nItemWineId)
	Item_AddItem(nItemDo1Id)
	Item_AddItem(nItemRe2Id)
	Item_AddItem(nItemMi3Id)
	Item_AddItem(nItemFa4Id)
	Item_AddItem(nItemSo5Id)
	Item_AddItem(nItemLa6Id)
	Item_AddItem(nItemTi7Id)
	Sys_SaveActionFestivalLog(tAnniversary2015_Sing_Log["DelAllAndGetAll"])
	--挑战开始
	Anniversary2015_Sing_Play()
end
---------------------------------------------------对话模板部分-----------------------------------------

-- //双龙城 欢乐音乐大师
tNpcFace[3585] = 185
tNpcGossip[18298] = tNpcGossip[18298] or DefaultNpc:new{}
tNpcGossip[18298]["OptionHidden"] = 1

--对白
tNpcGossip[18298]["Text1-1"] = {1011,1012,1013}					-- 活动前
tNpcGossip[18298]["Text1-2"] = {1021}							-- 活动后
tNpcGossip[18298]["Text1-3"] = {1031,1032,1033,1034}			-- 活动中（未领取任务）
tNpcGossip[18298]["Text1-4"] = {1041,1042,1043,1044}			-- 活动中（已领取任务）
tNpcGossip[18298]["Text2-1"] = {2011,2012}						-- 【我来挑战琴谱。（今日已完成）】
tNpcGossip[18298]["Text2-2"] = {2021,2022}						-- 【我来挑战琴谱。（失败 等级不足）】
tNpcGossip[18298]["Text2-3"] = {2031,2032,2033,2034}			-- 【我来挑战琴谱。（成功）】
tNpcGossip[18298]["Text2-4"] = {2041,2042}						-- 【领取音符和美酒。（失败 今日任务已完成】
tNpcGossip[18298]["Text2-5"] = {2051,2052,2053}					-- 【领取音符和美酒。（失败 背包空间不足）】
tNpcGossip[18298]["Text2-6"] = {2061,2062,2063}					-- 【领取音符和美酒。（失败 都有）】
tNpcGossip[18298]["Text2-7"] = {2071,2072}						-- 【领取奖励。（失败-已领取）】
tNpcGossip[18298]["Text2-8"] = {2081,2082}						-- 【领取奖励。（失败-未挑战）】
tNpcGossip[18298]["Text2-9"] = {2091,2092}						-- 【领取奖励。（失败-背包满）】
tNpcGossip[18298]["Text2-10"] = {2101,2102,2103}				-- 【领取奖励。（成功）】
tNpcGossip[18298]["Text2-11"] = {2111,2112,2113}				-- 【要怎么挑战？】
tNpcGossip[18298]["Text3-1"] = {3011,3012}						-- 【我来挑战琴谱。】 【我要挑战。（背包空间不足）】

tNpcGossip[18298]["Text1011"] = tAnniversary2015_Sing_Text[18298]["Text1011"]
tNpcGossip[18298]["Text1012"] = tAnniversary2015_Sing_Text[18298]["Text1012"]
tNpcGossip[18298]["Text1013"] = tAnniversary2015_Sing_Text[18298]["Text1013"]
tNpcGossip[18298]["Text1021"] = tAnniversary2015_Sing_Text[18298]["Text1021"]
tNpcGossip[18298]["Text1031"] = tAnniversary2015_Sing_Text[18298]["Text1031"]
tNpcGossip[18298]["Text1032"] = tAnniversary2015_Sing_Text[18298]["Text1032"]
tNpcGossip[18298]["Text1033"] = tAnniversary2015_Sing_Text[18298]["Text1033"]
tNpcGossip[18298]["Text1034"] = tAnniversary2015_Sing_Text[18298]["Text1034"]
tNpcGossip[18298]["Text1041"] = tAnniversary2015_Sing_Text[18298]["Text1041"]
tNpcGossip[18298]["Text1042"] = tAnniversary2015_Sing_Text[18298]["Text1042"]
tNpcGossip[18298]["Text1043"] = tAnniversary2015_Sing_Text[18298]["Text1043"]
tNpcGossip[18298]["Text1044"] = tAnniversary2015_Sing_Text[18298]["Text1044"]
tNpcGossip[18298]["Text2011"] = tAnniversary2015_Sing_Text[18298]["Text2011"]
tNpcGossip[18298]["Text2012"] = tAnniversary2015_Sing_Text[18298]["Text2012"]
tNpcGossip[18298]["Text2021"] = tAnniversary2015_Sing_Text[18298]["Text2021"]
tNpcGossip[18298]["Text2022"] = tAnniversary2015_Sing_Text[18298]["Text2022"]
tNpcGossip[18298]["Text2031"] = tAnniversary2015_Sing_Text[18298]["Text2031"]
tNpcGossip[18298]["Text2032"] = tAnniversary2015_Sing_Text[18298]["Text2032"]
tNpcGossip[18298]["Text2033"] = tAnniversary2015_Sing_Text[18298]["Text2033"]
tNpcGossip[18298]["Text2034"] = tAnniversary2015_Sing_Text[18298]["Text2034"]
tNpcGossip[18298]["Text2041"] = tAnniversary2015_Sing_Text[18298]["Text2041"]
tNpcGossip[18298]["Text2042"] = tAnniversary2015_Sing_Text[18298]["Text2042"]
tNpcGossip[18298]["Text2051"] = tAnniversary2015_Sing_Text[18298]["Text2051"]
tNpcGossip[18298]["Text2052"] = tAnniversary2015_Sing_Text[18298]["Text2052"]
tNpcGossip[18298]["Text2053"] = tAnniversary2015_Sing_Text[18298]["Text2053"]
tNpcGossip[18298]["Text2061"] = tAnniversary2015_Sing_Text[18298]["Text2061"]
tNpcGossip[18298]["Text2062"] = tAnniversary2015_Sing_Text[18298]["Text2062"]
tNpcGossip[18298]["Text2063"] = tAnniversary2015_Sing_Text[18298]["Text2063"]
tNpcGossip[18298]["Text2071"] = tAnniversary2015_Sing_Text[18298]["Text2071"]
tNpcGossip[18298]["Text2072"] = tAnniversary2015_Sing_Text[18298]["Text2072"]
tNpcGossip[18298]["Text2081"] = tAnniversary2015_Sing_Text[18298]["Text2081"]
tNpcGossip[18298]["Text2082"] = tAnniversary2015_Sing_Text[18298]["Text2082"]
tNpcGossip[18298]["Text2091"] = tAnniversary2015_Sing_Text[18298]["Text2091"]
tNpcGossip[18298]["Text2092"] = tAnniversary2015_Sing_Text[18298]["Text2092"]
tNpcGossip[18298]["Text2101"] = tAnniversary2015_Sing_Text[18298]["Text2101"]
tNpcGossip[18298]["Text2102"] = tAnniversary2015_Sing_Text[18298]["Text2102"]
tNpcGossip[18298]["Text2103"] = tAnniversary2015_Sing_Text[18298]["Text2103"]
tNpcGossip[18298]["Text2111"] = tAnniversary2015_Sing_Text[18298]["Text2111"]
tNpcGossip[18298]["Text2112"] = tAnniversary2015_Sing_Text[18298]["Text2112"]
tNpcGossip[18298]["Text2113"] = tAnniversary2015_Sing_Text[18298]["Text2113"]
tNpcGossip[18298]["Text3011"] = tAnniversary2015_Sing_Text[18298]["Text3011"]
tNpcGossip[18298]["Text3012"] = tAnniversary2015_Sing_Text[18298]["Text3012"]


-- 活动前
tNpcGossip[18298]["ChkFunc1-1"] = function ()
	return Sys_ChkFullTime(tAnniversary2015_Sing_Time["Beftime"])
end

-- 活动后
tNpcGossip[18298]["ChkFunc1-2"] = function ()
	return not Sys_ChkFullTime(tAnniversary2015_Sing_Time["Nowtime"])
end

-- 活动中（未领取任务）
tNpcGossip[18298]["ChkFunc1-3"] = function ()
	return Sys_ChkFullTime(tAnniversary2015_Sing_Time["Nowtime"]) and not (Anniversary2015_Sing_ChkNew() or Anniversary2015_Sing_ChkComplete()) 
end

-- 活动中（已领取任务）
tNpcGossip[18298]["ChkFunc1-4"] = function ()
	return Sys_ChkFullTime(tAnniversary2015_Sing_Time["Nowtime"]) and (Anniversary2015_Sing_ChkNew() or Anniversary2015_Sing_ChkComplete()) 
end

--选项
tNpcGossip[18298]["tOption1-1"] = {101}
tNpcGossip[18298]["tOption1-2"] = {102}
tNpcGossip[18298]["tOption1-3"] = {103,106,107}
tNpcGossip[18298]["tOption1-4"] = {103,104,105,106,107}
tNpcGossip[18298]["tOption2-1"] = {201}
tNpcGossip[18298]["tOption2-2"] = {202}
tNpcGossip[18298]["tOption2-3"] = {203,204}
tNpcGossip[18298]["tOption2-4"] = {205}
tNpcGossip[18298]["tOption2-5"] = {206}
tNpcGossip[18298]["tOption2-6"] = {207}
tNpcGossip[18298]["tOption2-7"] = {208}
tNpcGossip[18298]["tOption2-8"] = {209}
tNpcGossip[18298]["tOption2-9"] = {210}
tNpcGossip[18298]["tOption2-10"] = {211}
tNpcGossip[18298]["tOption2-11"] = {212}
tNpcGossip[18298]["tOption3-1"] = {301}
tNpcGossip[18298]["Option101"] = tAnniversary2015_Sing_Text[18298]["Option101"]
tNpcGossip[18298]["Option102"] = tAnniversary2015_Sing_Text[18298]["Option102"]
tNpcGossip[18298]["Option103"] = tAnniversary2015_Sing_Text[18298]["Option103"]
tNpcGossip[18298]["Option104"] = tAnniversary2015_Sing_Text[18298]["Option104"]
tNpcGossip[18298]["Option105"] = tAnniversary2015_Sing_Text[18298]["Option105"]
tNpcGossip[18298]["Option106"] = tAnniversary2015_Sing_Text[18298]["Option106"]
tNpcGossip[18298]["Option107"] = tAnniversary2015_Sing_Text[18298]["Option107"]
tNpcGossip[18298]["Option201"] = tAnniversary2015_Sing_Text[18298]["Option201"]
tNpcGossip[18298]["Option202"] = tAnniversary2015_Sing_Text[18298]["Option202"]
tNpcGossip[18298]["Option203"] = tAnniversary2015_Sing_Text[18298]["Option203"]
tNpcGossip[18298]["Option204"] = tAnniversary2015_Sing_Text[18298]["Option204"]
tNpcGossip[18298]["Option205"] = tAnniversary2015_Sing_Text[18298]["Option205"]
tNpcGossip[18298]["Option206"] = tAnniversary2015_Sing_Text[18298]["Option206"]
tNpcGossip[18298]["Option207"] = tAnniversary2015_Sing_Text[18298]["Option207"]
tNpcGossip[18298]["Option208"] = tAnniversary2015_Sing_Text[18298]["Option208"]
tNpcGossip[18298]["Option209"] = tAnniversary2015_Sing_Text[18298]["Option209"]
tNpcGossip[18298]["Option210"] = tAnniversary2015_Sing_Text[18298]["Option210"]
tNpcGossip[18298]["Option211"] = tAnniversary2015_Sing_Text[18298]["Option211"]
tNpcGossip[18298]["Option212"] = tAnniversary2015_Sing_Text[18298]["Option212"]
tNpcGossip[18298]["Option301"] = tAnniversary2015_Sing_Text[18298]["Option301"]
tNpcGossip[18298]["OptionFunc103"]="Anniversary2015_Sing_Option103_18298</N>18298"
tNpcGossip[18298]["OptionFunc104"]="Anniversary2015_Sing_Option104_18298</N>18298"
tNpcGossip[18298]["OptionFunc105"]="Anniversary2015_Sing_Option105_18298</N>18298"
tNpcGossip[18298]["OptionPoint106"]="2-11"
tNpcGossip[18298]["OptionFunc203"]="Anniversary2015_Sing_Option203_18298</N>18298"

---------------------------------物品模块--------------------------------------
-- 美酒
tItem[3005981] = tItem[3005981] or {}
tItem[3005981]["Function"] = function(nItemId,sItemName)
	Anniversary2015_Sing_UseItem_3005981(nItemId,sItemName)
end

-- Do1音符
tItem[3005982] = tItem[3005982] or {}
tItem[3005982]["Function"] = function(nItemId,sItemName)
	Anniversary2015_Sing_UseItem(nItemId,sItemName)
end
-- Re2音符
tItem[3005983] = tItem[3005983] or {}
tItem[3005983]["Function"] = function(nItemId,sItemName)
	Anniversary2015_Sing_UseItem(nItemId,sItemName)
end
-- Mi3音符
tItem[3005984] = tItem[3005984] or {}
tItem[3005984]["Function"] = function(nItemId,sItemName)
	Anniversary2015_Sing_UseItem(nItemId,sItemName)
end
-- Fa4音符
tItem[3005985] = tItem[3005985] or {}
tItem[3005985]["Function"] = function(nItemId,sItemName)
	Anniversary2015_Sing_UseItem(nItemId,sItemName)
end
-- So5音符
tItem[3005986] = tItem[3005986] or {}
tItem[3005986]["Function"] = function(nItemId,sItemName)
	Anniversary2015_Sing_UseItem(nItemId,sItemName)
end
-- La6音符
tItem[3005987] = tItem[3005987] or {}
tItem[3005987]["Function"] = function(nItemId,sItemName)
	Anniversary2015_Sing_UseItem(nItemId,sItemName)
end

-- Ti7音符
tItem[3005988] = tItem[3005988] or {}
tItem[3005988]["Function"] = function(nItemId,sItemName)
	Anniversary2015_Sing_UseItem(nItemId,sItemName)
end
