----------------------------------------------------------------------------
--Name:		[征服][模板逻辑]奖励模板.lua
--Purpose:	奖励模板
--Creator: 	郑鋆
--Created:	2016/03/28
----------------------------------------------------------------------------

-- 命名前缀
-- RewardTemplate_


-- 例子
-- local tReward = {}
	-- tReward["Log"] = "0,0,0,0,10002354,2,728596,3"	--具体的LOG格式
	-- tReward["LogId"] = 10002354	--LogId
	-- tReward["LogStep"] = "1[1]"	--记录的log步骤
	
	-- 通用的字段
	-- tReward["xxxxxxxx"] = {}
	-- tReward["xxxxxxxx"]["Value"] = 1	--具体获得的值，物品的话就是物品ID
	
	-- 添加物品的特殊字段
	-- tReward["RewardItem"] = {}				--物品属性
	-- tReward["RewardItem"][1] = {}				--物品属性
	-- tReward["RewardItem"][1]["Id"] = "0 1"		--物品Id
	-- tReward["RewardItem"][1]["Attr"] = "0 1"		--物品属性
	
	-- 添加光效的特殊字段
	-- tReward["RewardEffect"]["SzObj"] = "self" --添加光效时的对象，默认为self
	-- tReward["RewardEffect"]["Effect"] = "self" --添加光效名字
	
	-- 添加需要职业要求的物品特殊字段
	-- tReward["RewardProItem"] = {}
	-- tReward["RewardProItem"][1] = {}
	-- tReward["RewardProItem"][1]["Pro"] = {{10,15},{20,25}}
	-- tReward["RewardProItem"][1]["Item"] = {}
	-- tReward["RewardProItem"][1]["Item"][1] = {}
	-- tReward["RewardProItem"][1]["Item"][1]["Id"] = 1			---物品ID
	-- tReward["RewardProItem"][1]["Item"][1]["Attr"] = "0 1"	---物品属性
	
	-- 添加天石或者天石赠，需要打的EmoneyBuylog
	-- tReward["RewardEMoney"]["EmoneyLog"] = "250	4033	0	0	1	"
	
	-- 给经验的情况
	-- tReward["RewardExp"] = {}
	-- tReward["RewardExp"]["FullIndex"] = "RewardCultivation"	---满级给其它奖励
	-- tReward["RewardExp"]["FullValue"] = 11					---满级给其它奖励的具体值
	-- tReward["RewardExp"]["FullLog"] = "0,0,0,0,10002354,2,728596,3"	---满级的LOG格式
	
	-- 删除物品
	
	-- 学习技能
	-- tReward["RewardMagic"] = {}
	-- tReward["RewardMagic"]["MagicType"] = 12345			技能ID
	-- tReward["RewardMagic"]["MagicUp"] = 1				是否是升级技能（如果只是学习技能这个字段就不用配置）
	-- tReward["RewardMagic"]["LearnMagic"] = "12"			学习技能成功后的提示
	-- tReward["RewardMagic"]["UpMagic"] = "12"				升级技能成功后的提示
	
	-- 提示
	-- tReward["Talk"] = "12312"			获得奖励的配置提示
	-- tReward["NoItem"] = "12312"			删除物品时，物品不存在的提示
	-- tReward["FreePract"] = "12312"		免费修炼次数达到上限
	-- tReward["EMoneyMono"] = "12312"		赠点天石达到上限
	-- tReward["EMoney"] = "12312"			赠点达到上限
	-- tReward["Money"] = "12312"			银两达到上限
	-- tReward["ZhenQi"] = "12312"			真气达到上限
	-- tReward["RepairValue"] = "12312"		修为值达到上限
	-- tReward["HaveReceive"] = "12312"		已经领取过奖励

-- 变量表
local tRewardTemplate_TypeLog = {}
local tRewardTemplate_NumLog = {}
local tRewardTemplate_DelItemTypeLog = {}
local tRewardTemplate_DelItemNumLog = {}
local tRewardTemplate_IsReward = {}
local tRewardTemplate_NewRewardItem = {}
local tRewardTemplate_NewItemMsg = {}
local bFullLevel = false
local tRewardTemplate_Type = {}

---------------------------------------------上限判断函数-------------------------------------------------
-- 真气上限
function RewardTemplate_ZhenQiLimit(tZhenQi,nUserId)
	local nZhenQi = Get_UserGongFuQiLev(nUserId)
	local nAddZhenQi = tZhenQi["Value"]
	
	if nZhenQi + nAddZhenQi > G_User_MaxZhenQi then
		RewardTemplate_NotSatisfyCondition(tZhenQi,"ZhenQi",nUserId)
		return false
	end
	
	return true
end

-- 银两上限判断
function RewardTemplate_MoneyLimit(tMoney,nUserId)
	local nBagMoneyNum = tMoney["Value"]
	
	if not User_CanPutMoney2Bag(nBagMoneyNum,nUserId) then
		RewardTemplate_NotSatisfyCondition(tMoney,"Money",nUserId)
		return false
	end
	
	return true
end

-- 天石上限
function RewardTemplate_EMoneyLimit(tEMoney,nUserId)
	local nEmoney = Get_UserEMoney(nUserId)
	local nAddEmoney = tEMoney["Value"]
	
	if nEmoney + nAddEmoney > G_User_MaxEmoney then
		RewardTemplate_NotSatisfyCondition(tEMoney,"EMoney",nUserId)
		return false
	end
	
	return true
end

-- 赠点天石上限
function RewardTemplate_EMoneyMonoLimit(tEMoneyMono,nUserId)
	local nEmoney = Get_UserMonoEMoney(nUserId)
	local nAddEmoney = tEMoneyMono["Value"]
	
	if nEmoney + nAddEmoney > G_User_MaxEmoneyMono then
		RewardTemplate_NotSatisfyCondition(tEMoneyMono,"EMoneyMono",nUserId)
		return false
	end
	
	return true
end

-- 免费修炼次数上限
function RewardTemplate_FreePractNumLimit(tFreePractNum,nUserId)
	local nFreePractNum = Get_UserGongFureePractNum(nUserId)
	local nAddFreePractNum = tFreePractNum["Value"]*10000
	
	if nFreePractNum + nAddFreePractNum > G_User_FreePractice then
		RewardTemplate_NotSatisfyCondition(tFreePractNum,"FreePract",nUserId)
		return false
	end
	
	return true
end

-- 修为值达上限
function RewardTemplate_RepairValueLimit(tRepairValue,nUserId)
	local nRepairValue = Get_UserCultureValue(nUserId)
	local nAddRepairValue = tRepairValue["Value"]
	
	if nRepairValue + nAddRepairValue > G_User_RepairValue then
		RewardTemplate_NotSatisfyCondition(tRepairValue,"RepairValue",nUserId)
		return false
	end
	
	return true
end

function RewardTemplate_GetSpace(tAward)
	local nItemtypeId = tAward["Id"]
	local nNum = CommonFunc_GetItemNum(tAward["Attr"]) or 1
	local nLimit = Get_ItemtypeAccumulateLimit(nItemtypeId) 
	nLimit = (nLimit == 0 and 1 ) or nLimit
	return math.ceil(nNum/nLimit)
end

function RewardTemplate_DelSpace(tAward)
	local nItemtypeId = tAward["Id"]
	local nNum = tAward["ItemNum"] or 1
	local nLimit = Get_ItemtypeAccumulateLimit(nItemtypeId)
	nLimit = (nLimit == 0 and 1 ) or nLimit
	return math.floor(nNum/nLimit)
end

-- 掩码判断
function RewardTemplate_JudgmentStc(tReward,nUserId)
	local nEvent = tReward["EventType"]
	local nType = tReward["DataType"]
	
	if nEvent == nil or nType == nil then
		return false
	end
	
	local nSingleData = tReward["RewardData"] or 1
	local nTotalData = tReward["RewardTotalData"]
	local nDelay = tReward["RewardDelay"]
	local nTimeType = tReward["RewardTimeType"]
	local nData = Get_UserStatisticValue(nEvent,nType,nUserId)
	
	-- 对掩码值进行分解，取出总的次数跟今天的次数
	local nNowSingleData = nData%10000
	local nNowTotalData = (nData - nNowSingleData)/10000

	if (nTotalData ~= nil) and (nNowTotalData >= nTotalData) then
		return false
	end
	
	-- 判断是否需要清除掩码的操作
	if (nDelay ~= nil) and (nTimeType ~= nil) and Task_StcInterval(nEvent,nType,nDelay,nTimeType,nUserId) then
		nNowSingleData = 0
		nData = nNowTotalData*10000 + nNowSingleData
		Task_SetStatistic(nEvent,nType,nData,1,nUserId)
		Task_SetStcTimestamp(nEvent,nType,0,nUserId)
	end

	-- 判断今天是否领取过奖励
	if nNowSingleData >= nSingleData then
		-- tReward["HaveReceiveNoTip"] 有设置，则不需要提示"阁下已经领取过这项奖励了。" --by zzs
		if tReward["HaveReceiveNoTip"] ==nil then
			RewardTemplate_NotSatisfyCondition(tReward,"HaveReceive",nUserId)
		end
		return false
	end
	
	return true
end

-- 设置掩码值
function RewardTemplate_SetStc(tReward,nUserId)
	local nEvent = tReward["EventType"]
	local nType = tReward["DataType"]
	local nData = Get_UserStatisticValue(nEvent,nType,nUserId)
	local nNowSingleData = nData%10000
	local nNowTotalData = (nData - nNowSingleData)/10000
	
	nNowSingleData = nNowSingleData + 1
	nNowTotalData = nNowTotalData + 1
	local nNewData = nNowTotalData*10000 + nNowSingleData
	
	Task_SetStatistic(nEvent,nType,nNewData,1,nUserId)
	Task_SetStcTimestamp(nEvent,nType,0,nUserId)
	return true
end

-- 打开多次后删除物品
function RewardTemplate_ManyTimeDelItem(tReward,nUserId)
	local nEvent = tReward["EventType"]
	local nType = tReward["DataType"]
	local nTotalData = tReward["RewardTotalData"]
	
	if nEvent == nil or nType == nil or nTotalData == nil then
		return true
	end
	
	local nData = Get_UserStatisticValue(nEvent,nType,nUserId)

	-- 对掩码值进行分解，取出总的次数跟今天的次数
	local nNowSingleData = nData%10000
	local nNowTotalData = (nData - nNowSingleData)/10000
	
	if nNowTotalData + 1 >= nTotalData then
		return true
	end
	
	return false
end

-- 删除物品
function RewardTemplate_DelItem(tReward,nUserId)
	local tDelItem = tReward["DeleteItem"]
	
	if tDelItem == nil or (not RewardTemplate_ManyTimeDelItem(tReward,nUserId)) then
		return true
	end

	for i,v in pairs(tDelItem) do
		local nItemId = v["Id"]
		local nMonopoly = v["Monopoly"] or 1
		local nSash = v["Sash"] or 0
		local nItemNum = v["ItemNum"] or 1
		local nSaveTime = v["SaveTime"] or 1
		
		if not Item_ChkMulItem(nItemId,nItemId,nItemNum,nMonopoly,nSash,nUserId,nSaveTime) then
			RewardTemplate_NotSatisfyCondition(v,"NoItem",nUserId)
			return false
		end
	end
	
	for i,v in pairs(tDelItem) do
		local nItemId = v["Id"]
		local nMonopoly = v["Monopoly"] or 1
		local nSash = v["Sash"] or 0
		local nItemNum = v["ItemNum"] or 1
		local nSaveTime = v["SaveTime"] or 1

		if not Item_DelMulItem(nItemId,nItemId,nItemNum,nMonopoly,nSash,nUserId,nSaveTime) then
			return false
		else
			if tRewardTemplate_DelItemTypeLog[nUserId] == "" or tRewardTemplate_DelItemTypeLog[nUserId] == nil then
				tRewardTemplate_DelItemTypeLog[nUserId] = tostring(nItemId)
				tRewardTemplate_DelItemNumLog[nUserId] = tostring(nItemNum)
			else
				tRewardTemplate_DelItemTypeLog[nUserId] = tRewardTemplate_DelItemTypeLog[nUserId] .. "[" .. nItemId .. "]"
				tRewardTemplate_DelItemNumLog[nUserId] = tRewardTemplate_DelItemNumLog[nUserId] .. "[" .. nItemNum .. "]"
			end

			-- 判断是否贵重物品
			if v["PreciousType"] ~= nil then
				Sys_DecNosuchStatisticCount(v["PreciousType"],nItemId,nItemNum)
			end
		end
	end
	
	return true
end

-- 不满足条件的提示
function RewardTemplate_NotSatisfyCondition(tReward,sIndex,nUserId)
	local sCoent = tReward[sIndex]
	if sCoent == nil then
		sCoent = tRewardTemplate_Text[sIndex]
	end

	User_TalkChannel2005(sCoent,nUserId)
end

----------------------------------------------------------------------------------------------------------

local tRewardTemplate_List = {}
	-- 获得真气
	tRewardTemplate_List["RewardZhenQi"] = {}
	tRewardTemplate_List["RewardZhenQi"]["Func"] = User_AddGongFuQiLeve
	tRewardTemplate_List["RewardZhenQi"]["Index"] = 16
	tRewardTemplate_List["RewardZhenQi"]["LimitFunc"] = RewardTemplate_ZhenQiLimit

	-- 获得修行值
	tRewardTemplate_List["RewardCultivation"] = {}
	tRewardTemplate_List["RewardCultivation"]["Func"] = User_AddCultivation
	tRewardTemplate_List["RewardCultivation"]["Index"] = 6

	-- 获得银两
	tRewardTemplate_List["RewardMoney"] = {}
	tRewardTemplate_List["RewardMoney"]["Func"] = User_AddMoney
	tRewardTemplate_List["RewardMoney"]["Index"] = 1
	tRewardTemplate_List["RewardMoney"]["LimitFunc"] = RewardTemplate_MoneyLimit

	-- 获得天石
	tRewardTemplate_List["RewardEMoney"] = {}
	tRewardTemplate_List["RewardEMoney"]["Func"] = User_AddEMoney
	tRewardTemplate_List["RewardEMoney"]["Index"] = 2
	tRewardTemplate_List["RewardEMoney"]["LimitFunc"] = RewardTemplate_EMoneyLimit

	-- 获得赠品天石
	tRewardTemplate_List["RewardEMoneyMono"] = {}
	tRewardTemplate_List["RewardEMoneyMono"]["Func"] = User_AddEMoneyMono
	tRewardTemplate_List["RewardEMoneyMono"]["Index"] = 3
	tRewardTemplate_List["RewardEMoneyMono"]["LimitFunc"] = RewardTemplate_EMoneyMonoLimit

	-- 获得气力值
	tRewardTemplate_List["RewardStrengthValue"] = {}
	tRewardTemplate_List["RewardStrengthValue"]["Func"] = User_AddStrengthValue
	tRewardTemplate_List["RewardStrengthValue"]["Index"] = 12

	-- 获得经验点经验
	tRewardTemplate_List["RewardExp"] = {}
	tRewardTemplate_List["RewardExp"]["Func"] = User_AddExp
	tRewardTemplate_List["RewardExp"]["Index"] = 4

	-- 获得经验时间经验
	tRewardTemplate_List["RewardExpTime"] = {}
	tRewardTemplate_List["RewardExpTime"]["Func"] = User_AddExpTime
	tRewardTemplate_List["RewardExpTime"]["Index"] = 4

	-- 获得经验百分比经验
	tRewardTemplate_List["RewardExpPercent"] = {}
	tRewardTemplate_List["RewardExpPercent"]["Func"] = User_AddExpPercent
	tRewardTemplate_List["RewardExpPercent"]["Index"] = 4
	-- X倍经验 
	tRewardTemplate_List["RewardMulExpTime"] = {}
	tRewardTemplate_List["RewardMulExpTime"]["Func"] = User_SetExpControl
	tRewardTemplate_List["RewardMulExpTime"]["Index"] = 7

	-- 给物品
	tRewardTemplate_List["RewardItem"] = {}
	tRewardTemplate_List["RewardItem"]["Func"] = Item_AddNewItem

	-- 给光效
	tRewardTemplate_List["RewardEffect"] = {}
	tRewardTemplate_List["RewardEffect"]["Func"] = User_EffectAdd
	

	-- 给祝福时间
	tRewardTemplate_List["RewardBless"] = {}
	tRewardTemplate_List["RewardBless"]["Func"] = User_AddBless
	tRewardTemplate_List["RewardBless"]["Index"] = 5

	-- 给免费修炼次数
	tRewardTemplate_List["RewardFreePractNum"] = {}
	tRewardTemplate_List["RewardFreePractNum"]["Func"] = User_AddGongFuFreePractNum
	tRewardTemplate_List["RewardFreePractNum"]["Index"] = 17
	tRewardTemplate_List["RewardFreePractNum"]["LimitFunc"] = RewardTemplate_FreePractNumLimit

	-- 给骑马积分
	tRewardTemplate_List["RewardRidingPoint"] = {}
	tRewardTemplate_List["RewardRidingPoint"]["Func"] = User_AddRidingPoints
	tRewardTemplate_List["RewardRidingPoint"]["Index"] = 14

	-- 给修为值
	tRewardTemplate_List["RewardRepairValue"] = {}
	tRewardTemplate_List["RewardRepairValue"]["Func"] = User_AddCultureValue
	tRewardTemplate_List["RewardRepairValue"]["Index"] = 19
	tRewardTemplate_List["RewardRepairValue"]["LimitFunc"] = RewardTemplate_RepairValueLimit

	-- 给黄金联赛积分
	tRewardTemplate_List["RewardGoldenLeague"] = {}
	tRewardTemplate_List["RewardGoldenLeague"]["Func"] = GoldenLeaguePoints_Add
	
	-- 跨服功勋值
	tRewardTemplate_List["RewardExploitValue"] = {}
	tRewardTemplate_List["RewardExploitValue"]["Func"] = National_War_AddIntegral
	
	-- 获得称号
	tRewardTemplate_List["RewardTitle"] = {}
	tRewardTemplate_List["RewardTitle"]["Func"] = User_AwardTitle

	-- 获得翅膀
	tRewardTemplate_List["RewardWing"] = {}
	tRewardTemplate_List["RewardWing"]["Func"] = User_AwardTitle	
	
	-- 获得技能
	tRewardTemplate_List["RewardMagic"] = {}
	tRewardTemplate_List["RewardMagic"]["Func"] = Magic_Learn
	
	-- 获得特殊经验时间经验
	tRewardTemplate_List["RewardExpTimeSpecial"] = {}
	tRewardTemplate_List["RewardExpTimeSpecial"]["Func"] = User_AddSpecialExpTime
	tRewardTemplate_List["RewardExpTimeSpecial"]["Index"] = 4

	-- 获得特殊经验百分比经验
	tRewardTemplate_List["RewardExpPercentSpecial"] = {}
	tRewardTemplate_List["RewardExpPercentSpecial"]["Func"] = User_AddSpecialExpPercent
	tRewardTemplate_List["RewardExpPercentSpecial"]["Index"] = 4

----------------------------------------------------------------------------------

function RewardTemplate_Reward(tReward,nNowUserId)
	if tReward == nil or type(tReward) ~= "table" then
		return
	end
	
	local nUserId = nNowUserId or Get_UserId()
	local sRewardStr = ""
	tRewardTemplate_Text[nUserId] = {}
	tRewardTemplate_NewItemMsg[nUserId] = {}
	tRewardTemplate_TypeLog[nUserId] = ""
	tRewardTemplate_NumLog[nUserId] = ""
	tRewardTemplate_IsReward[nUserId] = false
	tRewardTemplate_Type[nUserId] = {}
	bFullLevel = false

	for i,v in pairs(tReward) do
		local sTemp = RewardTemplate_Give(i,v,nUserId)
		if sTemp then
			sRewardStr = sTemp
		end
	end
	
	if tRewardTemplate_IsReward[nUserId] then
		-- 默认log
		RewardTemplate_OutputLog(tReward,nUserId)
	
		-- 默认提示
		local str = RewardTemplate_Talk(tReward,nUserId)
		if str ~= "" then
			sRewardStr = str
		end
		
		--全服广播
		RewardTemplate_BroadCast(tReward,nUserId)
	end
	
	return sRewardStr
end

function RewardTemplate_BroadCast(tReward,nUserId)
	local sText = tReward["RewardBroadCast"]
	if sText ~= nil then
		local sUserName = Get_UserName(nUserId)
		Sys_SystemBroadcast(string.format(sText,sUserName))
	end
end

function RewardTemplate_Give(i,v,nUserId)
	local sIndex = i
	local bIsItem = false
	local bIsEffect = false
	local bIsProItem = false
	local bIsTitle = false
	local bIsWing = false 
	local bIsMagic = false
	local bMulExpTime = false
	local tAward = {}

	if string.find(i,"RewardItem") then
		bIsItem = true
		tAward = v
	elseif string.find(i,"RewardEffect") then
		bIsEffect = true
		tAward = v
	elseif string.find(i,"RewardProItem") then
		local nPro = Get_UserProfession(nUserId)

		for nIndex,tValue in pairs (v) do
			local tPro = tValue["Pro"]

			if RewardTemplate_ChkPro(tPro,nPro) then
				sIndex = "RewardItem"
				bIsProItem = true
				tAward = tValue
			end
		end
	elseif string.find(i,"RewardExp") then
		local nLev = Get_UserLevel(nUserId)

		if nLev >= G_User_MaxLev then
			bFullLevel = true
			sIndex = v["FullIndex"]
			tAward["Value"] = v["FullValue"]
		else
			tAward = v
		end
	elseif string.find(i,"RewardTitle") then
		bIsTitle = true
		tAward = v
	elseif string.find(i,"RewardWing") then
		bIsTitle = true
		tAward = v
	elseif string.find(i,"RewardMagic") then
		bIsMagic = true
		tAward = v
	elseif string.find(i,"RewardMulExpTime") then
		bMulExpTime = true
		tAward = v
	else
		tAward = v
	end

	-- 判断是否有对应的封装函数
	if tRewardTemplate_List[sIndex] == nil then
		return
	end
	
	local sFunc = tRewardTemplate_List[sIndex]["Func"]
	local nType = tRewardTemplate_List[sIndex]["Index"]

	if sFunc == nil and type(sFunc) ~= "function" then
		return
	end

	-- 给奖励
	local sRewardStr = ""
	if bIsItem then
		for m,n in pairs (tAward) do
			local sTemp = RewardTemplate_RewardItem(n,sIndex,nUserId)
			if sTemp then
				sRewardStr = sTemp
			end
		end
		
		tRewardTemplate_IsReward[nUserId] = true
	-- 给光效
	elseif bIsEffect then
		local sSzobj = tAward["SzObj"] or "self"
		sFunc(sSzobj,tAward["Effect"],nUserId)
	-- 给职业要求物品
	elseif bIsProItem then
		for m,n in pairs (tAward["Item"]) do
			local sTemp = RewardTemplate_RewardItem(n,sIndex,nUserId)
			if sTemp then
				sRewardStr = sTemp
			end
		end
		
		tRewardTemplate_IsReward[nUserId] = true
	-- 给称号
	elseif bIsTitle then
		local nTitleType = tAward["TitleType"]
		local nTitleId = tAward["TitleId"]
		local nSaveTime = tAward["SaveTime"]
		-- 判断是否有称号
		if not User_CheckTitle(nTitleType,nTitleId,nUserId) then
			User_AwardTitle(nTitleType,nTitleId,nSaveTime,nUserId)
		end
	-- 给翅膀
	elseif bIsWing then
		local nTitleType = tAward["TitleType"]
		local nTitleId = tAward["TitleId"]
		local nSaveTime = tAward["SaveTime"]
		-- 判断是否有称号
		if not User_CheckTitle(nTitleType,nTitleId,nUserId) then
			User_AwardTitle(nTitleType,nTitleId,nSaveTime,nUserId)
		end
	-- 学技能
	elseif bIsMagic then
		if tAward["MagicUp"] ~= nil then
			RewardTemplate_UpMagic(tAward,nUserId)
		else
			RewardTemplate_Magic(tAward,nUserId)
		end
		--多倍经验
	elseif bMulExpTime then
		sFunc(tAward["Percent"],tAward["Time"]*3600,nUserId)
		RewardTemplate_MulExpTimeText(sIndex,tAward,nUserId)
		RewardTemplate_Log(nType,tAward["Time"],nUserId)
		tRewardTemplate_IsReward[nUserId] = true
	elseif tAward["Value"] ~= nil then
		sFunc(tAward["Value"],nUserId)
		-- 拼接log
		RewardTemplate_Log(nType,tAward["Value"],nUserId)
		-- 拼接提示
		RewardTemplate_SetText(sIndex,tAward["Value"],nUserId)
		
		if (sIndex == "RewardEMoney" or sIndex == "RewardEMoneyMono") and tAward["EmoneyLog"] ~= nil then
			Sys_SaveEmoneyBuy(tAward["EmoneyLog"])
		end
		
		tRewardTemplate_IsReward[nUserId] = true
	end

	return sRewardStr
end

-- 玩家学习技能
function RewardTemplate_Magic(tAward,nUserId)
	local nMagicType = tAward["MagicType"]
	
	if nMagicType == nil then
		return
	end
	
	-- 检测玩家是否学习过技能
	if Magic_ChkType(nMagicType,nUserId) then
		return
	end
		
	if Magic_Learn(nMagicType,nUserId) then
		-- 技能学习成功给予的提示
		if tAward["LearnMagic"] ~= nil then
			User_TalkChannel2005(tAward["LearnMagic"],nUserId)
		end
		return
	end
end

-- 玩家升级技能
function RewardTemplate_UpMagic(tAward,nUserId)
	local nMagicType = tAward["MagicType"]
	local nUpTimes = tAward["Times"] or 1
	
	if nMagicType == nil then
		return false
	end
	
	-- 检测玩家是否学习过技能
	if not Magic_ChkType(nMagicType,nUserId) then
		-- 玩家学习技能
		if not Magic_Learn(nMagicType,nUserId) then
			return false
		end

	end
	
	for i = 1,nUpTimes do
		if Magic_UpLev(nMagicType,nUserId) then
			if i == nUpTimes then
				-- 技能升级提示
				if tAward["UpMagic"] ~= nil then
					User_TalkChannel2005(tAward["UpMagic"],nUserId)
				end
				return true
			end
		end
	end
	
	return false
end

-- 检测是否满足职业要求
function RewardTemplate_ChkPro(tPro,nPro)
	for m,n in pairs(tPro) do
		if nPro >= n[1] and nPro <= n[2] then	
			return true
		end
	end
	
	return false
end

-- 给物品
function RewardTemplate_RewardItem(tAward,sIndex,nUserId)
	local nItemId = tAward["Id"]
	local nNum = CommonFunc_GetItemNum(tAward["Attr"])
	local str = ""

	if tRewardTemplate_NewRewardItem[nUserId] ~= nil then
		local sReward = Item_AddNewItemAndMsg(nItemId,tAward["Attr"],nUserId)
		tRewardTemplate_NewItemMsg[nUserId] = tRewardTemplate_NewItemMsg[nUserId] or {}
		str = tRewardTemplate_NewItemMsg[nUserId][sIndex] or ""
		
		if str == nil or str == "" then
			str = str .. sReward
		else
			str = str .. tRewardTemplate_Text["Punctuat"] .. sReward
		end
		
		tRewardTemplate_NewItemMsg[nUserId][sIndex] = str
		
		
	else
		Item_AddNewItem(nItemId,tAward["Attr"],nUserId)
		
		tRewardTemplate_Text[nUserId] = tRewardTemplate_Text[nUserId] or {}
		local sItemName = tRewardTemplate_Text["ItemName"][nItemId] or Get_ItemtypeName(nItemId)
		str = tRewardTemplate_Text[nUserId][sIndex] or ""
		local sReward = string.format(tRewardTemplate_Text[sIndex],nNum,sItemName)
		
		if str == nil or str == "" then
			str = str .. sReward
		else
			str = str .. tRewardTemplate_Text["Punctuat"] .. sReward
		end
		
		tRewardTemplate_Text[nUserId][sIndex] = str
	end
	
	-- 判断是否贵重物品
	if tAward["PreciousType"] ~= nil then
		Sys_IncNosuchStatisticCount(tAward["PreciousType"],nItemId,tonumber(nNum))
	end
	
	RewardTemplate_Log(nItemId,nNum,nUserId)
	return str
end

function RewardTemplate_Sort(a,b)
	return a.Type < b.Type
end

-- log
function RewardTemplate_OutputLog(tReward,nUserId)
	local sLog = tReward["Log"]
	local sDelItemLog = tReward["DelItemLog"]
	local sDelItemNumLog = tReward["DelItemNumLog"]
	
	if bFullLevel == true then
		sLog = tReward["FullLog"]
	end
	
	if sDelItemLog == nil then
		if tRewardTemplate_DelItemTypeLog[nUserId] == "" or tRewardTemplate_DelItemTypeLog[nUserId] == nil then
			sDelItemLog = "0"
			sDelItemNumLog = "0"
		else
			sDelItemLog = tRewardTemplate_DelItemTypeLog[nUserId]
			sDelItemNumLog = tRewardTemplate_DelItemNumLog[nUserId]
		end
	end
	
	-- 对获得奖励按照数字大小进行排序，从小到大排序
	table.sort(tRewardTemplate_Type[nUserId],RewardTemplate_Sort)
	
	for i = 1,#tRewardTemplate_Type[nUserId] do
		local nType = tRewardTemplate_Type[nUserId][i]["Type"]
		local nNum = tRewardTemplate_Type[nUserId][i]["Num"]
	
		if tRewardTemplate_TypeLog[nUserId] == "" then
			tRewardTemplate_TypeLog[nUserId] = tostring(nType)
			tRewardTemplate_NumLog[nUserId] = tostring(nNum)
		else
			tRewardTemplate_TypeLog[nUserId] = tRewardTemplate_TypeLog[nUserId] .. "[" .. nType .. "]"
			tRewardTemplate_NumLog[nUserId] = tRewardTemplate_NumLog[nUserId] .. "[" .. nNum .. "]"
		end
	end

	if sLog == nil then
		local nLogId = tReward["LogId"] or 12000400
		local sStep = tReward["LogStep"] or "2"
		sLog = string.format("0,0,%s,%s,%d,%s,%s,%s",sDelItemLog,sDelItemNumLog,nLogId,sStep,tRewardTemplate_TypeLog[nUserId],tRewardTemplate_NumLog[nUserId])
	end

	if tReward["LogFile"] ~= nil then
		if tReward["LogFile"] == "DragonSoul" then
			Sys_SaveDragonSoulLog(sLog,nUserId)
		end
	else
		Sys_SaveActionRewardLog(sLog,nUserId)
	end
	
	tRewardTemplate_TypeLog[nUserId] = ""
	tRewardTemplate_NumLog[nUserId] = ""
	tRewardTemplate_DelItemTypeLog[nUserId] = ""
	tRewardTemplate_DelItemNumLog[nUserId] = ""
	tRewardTemplate_Type[nUserId] = {}
end

function RewardTemplate_Log(nType,nNum,nUserId)
	if nType == nil or nNum == nil then
		return
	end
	
	local tLog = {["Type"] = nType,["Num"] = nNum}
	
	table.insert(tRewardTemplate_Type[nUserId],tLog)
	
	-- if tRewardTemplate_TypeLog[nUserId] == "" then
		-- tRewardTemplate_TypeLog[nUserId] = tostring(nType)
		-- tRewardTemplate_NumLog[nUserId] = tostring(nNum)
	-- else
		-- tRewardTemplate_TypeLog[nUserId] = tRewardTemplate_TypeLog[nUserId] .. "[" .. nType .. "]"
		-- tRewardTemplate_NumLog[nUserId] = tRewardTemplate_NumLog[nUserId] .. "[" .. nNum .. "]"
	-- end
end

-- 给提示
function RewardTemplate_Talk(tReward,nUserId)
	local sTalk = tReward["Talk"]
	local str = ""

	if sTalk == nil then
		
		for i,v in pairs(tRewardTemplate_Text[nUserId]) do
			if str == "" then
				str = str .. v
			else
				str = str .. tRewardTemplate_Text["Punctuat"] .. v
			end
		end
		
		if str == "" then
			return str
		end
		
		sTalk = string.format(tRewardTemplate_Text["Main"],str)
	end

	-- 不需要通用提示
	if tReward["RewardNoNeedTip"] ~= nil then
		return str
	end
	
	User_TalkChannel2005(sTalk,nUserId)
	return str
end

function RewardTemplate_SetText(sIndex,nValue,nUserId)
	tRewardTemplate_Text[nUserId] = tRewardTemplate_Text[nUserId] or {}
	tRewardTemplate_Text[nUserId][sIndex] = string.format(tRewardTemplate_Text[sIndex],nValue)
end

function RewardTemplate_MulExpTimeText(sIndex,tAward,nUserId)
	tRewardTemplate_Text[nUserId] = tRewardTemplate_Text[nUserId] or {}
	local nMul = tAward["Percent"]/100
	local nTime = tAward["Time"]
	tRewardTemplate_Text[nUserId][sIndex] = string.format(tRewardTemplate_Text[sIndex],nTime,nMul)
end
-- 随机概率获得物品
function RewardTemplate_Random(tTable,nIndex,nNowUserId)
	local nFlag,tReward = Probabil_RandomAward(tTable,nIndex)
	local sRewardStr = ""
	for i = 1,#tReward do
		-- 随机获得物品
		local tAward = tReward[i]["tAward"]
		
		if tAward ~= nil and next(tAward) ~= nil then
			for j,v in pairs (tAward) do
				local sTemp = RewardTemplate_Reward(v,nNowUserId)
				if sTemp then
					sRewardStr = sTemp
				end
			end
		end
		
		-- 必定获得物品
		local tAbsolute = tReward[i]["tAbsoluteAward"]
		if tAbsolute ~= nil and next(tAbsolute) ~= nil then
			for j,v in pairs (tAbsolute) do
				local sTemp = RewardTemplate_Reward(v,nNowUserId)
				if sTemp then
					sRewardStr = sTemp
				end
			end
		end
		
		-- 有概率获得物品
		local tSelfItemChanceAward = tReward[i]["tSelfItemChanceAward"]
		if tSelfItemChanceAward ~= nil and next(tSelfItemChanceAward) ~= nil then
			for j,v in pairs (tSelfItemChanceAward) do
				local sTemp = RewardTemplate_Reward(v,nNowUserId)
				if sTemp then
					sRewardStr = sTemp
				end
			end
		end
	end
	
	return tReward,sRewardStr
end

-- 上限的判断
function RewardTemplate_UpperLimit(tReward,nNowUserId)
	local nUserId = nNowUserId or Get_UserId()
	local nSpace = 0
	local nSubSpace = 0
	
	for i,v in pairs(tReward) do
		if tRewardTemplate_List[i] ~= nil and tRewardTemplate_List[i]["LimitFunc"] ~= nil and type(tRewardTemplate_List[i]["LimitFunc"]) == "function" then
			if not tRewardTemplate_List[i]["LimitFunc"](v,nUserId) then
				return false
			end
		-- 判断普通物品需要的背包空间
		elseif string.find(i,"RewardItem") then
			for m,n in pairs (v) do
				nSpace = nSpace + RewardTemplate_GetSpace(n)
			end
		-- 获取职业要求需要的背包空间
		elseif string.find(i,"RewardProItem") then
			local nPro = Get_UserProfession(nUserId)

			for nIndex,tValue in pairs (v) do
				local tPro = tValue["Pro"]
	
				if RewardTemplate_ChkPro(tPro,nPro) then
					for m,n in pairs (tValue["Item"]) do
						nSpace = nSpace + RewardTemplate_GetSpace(n)
					end
				end
			end
		-- 获取删除物品的背包空间
		elseif string.find(i,"DeleteItem") then
			for m,n in pairs (v) do
				nSubSpace = nSubSpace + RewardTemplate_DelSpace(n)
			end
		end
	end

	nSpace = nSpace - nSubSpace

	if nSpace > 0 and (not User_CheckLeftSpace(nSpace,nUserId)) then
		local sCoent = tReward["NoSpace"]
		
		if sCoent == nil then
			sCoent = string.format(tRewardTemplate_Text["NoSpace"],nSpace)
		end
		
		User_TalkChannel2005(sCoent,nUserId)
		return false
	end

	return true
end

-- 奖励接口的外层封装
-- bJudge:该参数的值为通过TermsOfUse_Main返回的值。
function RewardTemplate_OuterPckage(tReward,nNowUserId,bJudge)
	local nUserId = nNowUserId or Get_UserId()
	tRewardTemplate_DelItemTypeLog[nUserId] = ""
	tRewardTemplate_DelItemNumLog[nUserId] = ""
	tRewardTemplate_NewRewardItem[nUserId] = 1
	
	if (bJudge ~= nil) and (not bJudge) then
		return false
	end
	
	if bJudge == nil then
		-- 掩码判断
		if not RewardTemplate_JudgmentStc(tReward,nUserId) then
			return false
		end
		
		-- 上限判断
		if not RewardTemplate_UpperLimit(tReward,nUserId) then
			return false
		end
	end
	
	-- 是否要删除物品
	if not RewardTemplate_DelItem(tReward,nUserId) then
		return false
	end
	
	-- 设置掩码
	if RewardTemplate_SetStc(tReward,nUserId) then
		-- 给奖励
			local sRewardStr = RewardTemplate_Reward(tReward,nUserId)
	end
	
	return true,sRewardStr
end

-- 简单物品使用
-- bJudge:该参数的值为通过TermsOfUse_Main返回的值。
function RewardTemplate_UseItem(tReward,nNowUserId,bJudge)
	local nUserId = nNowUserId or Get_UserId()
	tRewardTemplate_DelItemTypeLog[nUserId] = ""
	tRewardTemplate_DelItemNumLog[nUserId] = ""
	tRewardTemplate_NewRewardItem[nUserId] = nil
	
	-- 掩码判断
	local nEvent = tReward["EventType"]
	local nType = tReward["DataType"]
	
	if (bJudge ~= nil) and (not bJudge) then
		return false
	end
	
	if bJudge == nil then
		if (nEvent ~= nil or nType ~= nil) and not RewardTemplate_JudgmentStc(tReward,nUserId) then
			return false
		end
		
		-- 上限判断
		if not RewardTemplate_UpperLimit(tReward,nUserId) then
			return false
		end
	end
	
	-- 是否要删除物品
	if not RewardTemplate_DelItem(tReward,nUserId) then
		return false
	end
	
	-- 设置掩码
	if (nEvent ~= nil or nType ~= nil) then
		RewardTemplate_SetStc(tReward,nUserId)
	end
	
	-- 给奖励
	local sRewardStr = RewardTemplate_Reward(tReward,nUserId)
	
	if tReward["EmoneyLog"] ~= nil then
		Sys_SaveEmoneyBuy(tReward["EmoneyLog"])
	end
	
	return true,sRewardStr
end

-- 简单物品使用(获得物品时给予相应的提示)
-- bJudge:该参数的值为通过TermsOfUse_Main返回的值。
function RewardTemplate_UseItemAndMsg(tReward,nNowUserId,bJudge)
	local nUserId = nNowUserId or Get_UserId()
	tRewardTemplate_DelItemTypeLog[nUserId] = ""
	tRewardTemplate_DelItemNumLog[nUserId] = ""
	tRewardTemplate_NewRewardItem[nUserId] = 1
	
	-- 掩码判断
	local nEvent = tReward["EventType"]
	local nType = tReward["DataType"]
	
	if (bJudge ~= nil) and (not bJudge) then
		return false
	end
	
	if bJudge == nil then
		if (nEvent ~= nil or nType ~= nil) and not RewardTemplate_JudgmentStc(tReward,nUserId) then
			return false
		end
		
		-- 上限判断
		if not RewardTemplate_UpperLimit(tReward,nUserId) then
			return false
		end
	end
	
	-- 是否要删除物品
	if not RewardTemplate_DelItem(tReward,nUserId) then
		return false
	end
	
	-- 设置掩码
	if (nEvent ~= nil or nType ~= nil) then
		RewardTemplate_SetStc(tReward,nUserId)
	end
	
	-- 给奖励
	local sRewardStr = RewardTemplate_Reward(tReward,nUserId)
	
	if tReward["EmoneyLog"] ~= nil then
		Sys_SaveEmoneyBuy(tReward["EmoneyLog"])
	end
	
	return true,sRewardStr
end

-- 新的随机概率获得物品（增加上限限制，达到上限后给另外物品）
function RewardTemplate_GiveRandom(tAward,tReward,nNowUserId)
	local nUserId = nNowUserId or Get_UserId()
	local nUpperLog = tReward["LogId"]
	local sUpperStep = tReward["LogStep"]
	
	if tAward["LogId"] == nil and nUpperLog ~= nil then
		tAward["LogId"] = nUpperLog
	end
	
	if tAward["LogStep"] == nil and sUpperStep ~= nil then
		tAward["LogStep"] = sUpperStep
	end
	
	if tAward["RewardNoNeedTip"] == nil and tReward["RewardNoNeedTip"] ~= nil then
		tAward["RewardNoNeedTip"] = tReward["RewardNoNeedTip"]
	end 
	
	-- 判断是否有领取上限
	local nEvent = tAward["EventType"]
	local nType = tAward["DataType"]
	local nSingleData = tAward["RewardData"]
	local nDelay = tAward["RewardDelay"]
	local nTimeType = tAward["RewardTimeType"]
	local sRewardStr = ""
	
	if nEvent ~= nil or nType ~= nil then
		if (nDelay ~= nil) and (nTimeType ~= nil) and Task_StcInterval(nEvent,nType,nDelay,nTimeType,nUserId) then
			Task_SetStatistic(nEvent,nType,0,1,nUserId)
			Task_SetStcTimestamp(nEvent,nType,0,nUserId)
		else
			local nData = Get_UserStatisticValue(nEvent,nType,nUserId)
			
			if nData >= nSingleData then
				local nIndex = tAward["FullIndex"]
				
				if nIndex ~= nil then
					if tReward[nIndex]["LogId"] == nil and nUpperLog ~= nil then
						tReward[nIndex]["LogId"] = nUpperLog
					end
					
					if tReward[nIndex]["LogStep"] == nil and sUpperStep ~= nil then
						tReward[nIndex]["LogStep"] = sUpperStep
					end
					
					sRewardStr = RewardTemplate_Reward(tReward[nIndex],nUserId)
				end
				
				return sRewardStr,tReward[nIndex]
			end
		end
		
		Task_AddStatistic(nEvent,nType,1,1,nUserId)
		Task_SetStcTimestamp(nEvent,nType,0,nUserId)
	end
	
	-- 动态存储表限制
	local nGlobalId = tAward["GlobalId"]
	
	if nGlobalId ~= nil then
		local nPos = tAward["Pos"]
		local nMaxData = tAward["MaxData"]
		local nData = Get_SysDynaGlobalData(nGlobalId,nPos)
		
		if nData >= nMaxData then
			local nIndex = tAward["FullIndex"]
			
			if nIndex ~= nil then
				if tReward[nIndex]["LogId"] == nil and nUpperLog ~= nil then
					tReward[nIndex]["LogId"] = nUpperLog
				end
				
				if tReward[nIndex]["LogStep"] == nil and sUpperStep ~= nil then
					tReward[nIndex]["LogStep"] = sUpperStep
				end
				sRewardStr = RewardTemplate_Reward(tReward[nIndex],nUserId)
			end
			
			return sRewardStr,tReward[nIndex]
		end
		
		Sys_SetSynaGlobalData(nGlobalId,nPos,nData + 1)
	end

	sRewardStr = RewardTemplate_Reward(tAward,nUserId)
	return sRewardStr,tAward
end

function RewardTemplate_NewRandom(tTable,nIndex,nNowUserId)
	local nUserId = nNowUserId or Get_UserId()
	local nFlag,tReward = Probabil_RandomAward(tTable,nIndex)
	local tChar = {"tAward","tAbsoluteAward","tSelfItemChanceAward"}
	local sRewardStr = ""
	local tNewReward = {}
	tRewardTemplate_DelItemTypeLog[nUserId] = ""
	tRewardTemplate_DelItemNumLog[nUserId] = ""
	tRewardTemplate_NewRewardItem[nUserId] = 1

	for i = 1,#tReward do
		tNewReward[i] = {}
		for j,v in pairs(tChar) do
			local tAward = tReward[i][v]
				tNewReward[i][v] = {}

			if tAward ~= nil and next(tAward) ~= nil then
				for m,n in pairs (tAward) do
						local sTemp,tNewAward  = RewardTemplate_GiveRandom(n,tTable[nIndex],nUserId)
						table.insert(tNewReward[i][v],tNewAward)
						if sTemp then
							sRewardStr = sTemp
					end
				end
			end
		end
	end
	
	return tNewReward,sRewardStr
end
--新的随机概率获得物品,没有默认提示
function RewardTemplate_NewRandomNoTip(tTable,nIndex,nNowUserId)
	local nUserId = nNowUserId or Get_UserId()
	local nFlag,tReward = Probabil_RandomAward(tTable,nIndex)
	local tChar = {"tAward","tAbsoluteAward","tSelfItemChanceAward"}
	local sRewardStr = ""
	local tNewReward = {}
	tRewardTemplate_DelItemTypeLog[nUserId] = ""
	tRewardTemplate_DelItemNumLog[nUserId] = ""
	tRewardTemplate_NewRewardItem[nUserId] = nil
	for i = 1,#tReward do
		tNewReward[i] = {}
		for j,v in pairs(tChar) do
			local tAward = tReward[i][v]
			tNewReward[i][v] = {}
			if tAward ~= nil and next(tAward) ~= nil then
				for m,n in pairs (tAward) do
						local sTemp,tNewAward = RewardTemplate_GiveRandom(n,tTable[nIndex],nUserId)
					table.insert(tNewReward[i][v],tNewAward)			
					if sTemp then
						sRewardStr = sTemp
					end
				end
			end
		end
	end
	return tNewReward,sRewardStr
end
-- 自动判断背包空间
function RewardTemplate_CheckSpace(tReward,nNowUserId)
	-- 判断参数是否正确
	if tReward == nil or type(tReward) ~= "table" then
		return false
	end
	
	local nUserId = nNowUserId or Get_UserId()
	local nSpace = 0
	local nSubSpace = 0
	
	-- 判断删除物品所需的背包空间
	for i, v in pairs(tReward) do
		-- 判断普通物品需要的背包空间
		if string.find(i,"RewardItem") then
			for m,n in pairs (v) do
				nSpace = nSpace + RewardTemplate_GetSpace(n)
			end
		-- 获取职业要求需要的背包空间
		elseif string.find(i,"RewardProItem") then
			local nPro = Get_UserProfession(nUserId)

			for nIndex,tValue in pairs (v) do
				local tPro = tValue["Pro"]
	
				if RewardTemplate_ChkPro(tPro,nPro) then
					for m,n in pairs (tValue["Item"]) do
						nSpace = nSpace + RewardTemplate_GetSpace(n)
					end
				end
			end
		-- 获取删除物品的背包空间
		elseif string.find(i,"DeleteItem") then
			for m,n in pairs (v) do
				nSubSpace = nSubSpace + RewardTemplate_DelSpace(n)
			end
		end
	end
	
	nSpace = nSpace - nSubSpace

	if nSpace > 0 and (not User_CheckLeftSpace(nSpace,nUserId)) then
		local sCoent = tReward["NoSpace"]
		
		if sCoent == nil then
			sCoent = string.format(tRewardTemplate_Text["NoSpace"],nSpace)
		end
		
		User_TalkChannel2005(sCoent,nUserId)
		return false
	end

	return true
end

-- 获取奖励所需的背包空间
function RewardTemplate_GetRewardSpace(tReward,nNowUserId)
	-- 判断参数是否正确
	if tReward == nil or type(tReward) ~= "table" then
		return false
	end

	local nUserId = nNowUserId or Get_UserId()
	local nSpace = 0
	
	for i, v in pairs(tReward) do
		-- 判断普通物品需要的背包空间
		if string.find(i,"RewardItem") then
			for m,n in pairs (v) do
				nSpace = nSpace + RewardTemplate_GetSpace(n)
			end
		-- 获取职业要求需要的背包空间
		elseif string.find(i,"RewardProItem") then
			local nPro = Get_UserProfession(nUserId)

			for nIndex,tValue in pairs (v) do
				local tPro = tValue["Pro"]
	
				if RewardTemplate_ChkPro(tPro,nPro) then
					for m,n in pairs (tValue["Item"]) do
						nSpace = nSpace + RewardTemplate_GetSpace(n)
					end
				end
			end
		end
	end
	
	return nSpace
end

-- 获取删除物品所需的背包空间
function RewardTemplate_GetDelSpace(tReward,nNowUserId)
	-- 判断参数是否正确
	if tReward == nil or type(tReward) ~= "table" then
		return false
	end

	local nUserId = nNowUserId or Get_UserId()
	local nSubSpace = 0
	
	-- 判断删除物品所需的背包空间
	for i, v in pairs(tReward) do
		-- 获取删除物品的背包空间
		if string.find(i,"DeleteItem") then
			for m,n in pairs (v) do
				nSubSpace = nSubSpace + RewardTemplate_DelSpace(n)
			end
		end
	end
	
	return nSubSpace
end

-- 获取随机奖励所需的背包空间
function RewardTemplate_GetRandomSpace(tTable,nIndex,nNowUserId)
	local nUserId = nNowUserId or Get_UserId()
	local tAwardChart = tTable[nIndex]
	local nSpace = 0
	local nAwardSpace = 0
	local nAbsoluteSpace = 0
	local nSelfSpace = 0
	
	-- 判断奖励是否是表数据
	if type(tAwardChart) ~= "table" then
		return false
	end
	
	-- 构造一个奖励源表，用于存放相同概率基数的数据
	local tAwardSource = {}
	-- 构造一个奖励源表，用于存放拥有各自概率的数据
	local tSelfItemChanceAwardSource = {}
	-- 构造一个奖励源表，用于存放绝对触发的数据
	local tAbsoluteSource = {}
	
	for i,v in pairs(tAwardChart) do
		if type(v) == "table" then
			local randomItemChanceType = v.RandomItemChanceType or 0
			if randomItemChanceType == 1 then
				table.insert(tAbsoluteSource, v)
			elseif randomItemChanceType == 2 then
				table.insert(tAwardSource, v)
			elseif randomItemChanceType == 3 then
				table.insert(tSelfItemChanceAwardSource, v)
			end
		end
	end
	
	-- 获取相同概率基数所需的背包空间
	for i,v in pairs (tAwardSource) do
		local nNowSpace = RewardTemplate_GetRewardSpace(v,nUserId)
		
		if nNowSpace > nAwardSpace then
			nAwardSpace = nNowSpace
		end
	end
	
	-- 获取相同各自概率所需的背包空间
	for i,v in pairs (tSelfItemChanceAwardSource) do
		local nNowSpace = RewardTemplate_GetRewardSpace(v,nUserId)
		nSelfSpace = nSelfSpace + nNowSpace
	end

	-- 获取绝对触发所需的背包空间
	for i,v in pairs (tAbsoluteSource) do
		local nNowSpace = RewardTemplate_GetRewardSpace(v,nUserId)
		nAbsoluteSpace = nAbsoluteSpace + nNowSpace
	end

	nSpace = nAwardSpace + nSelfSpace + nAbsoluteSpace

	return nSpace
end

-- 检测随机所需的背包空间
function RewardTemplate_ChkRandomSpace(tTable,nIndex,nNowUserId)
	local nUserId = nNowUserId or Get_UserId()
	local tAwardChart = tTable[nIndex]
	local nSpace = 0
	local nSubSpace = 0
	
	-- 判断奖励是否是表数据
	if type(tAwardChart) ~= "table" then
		return false
	end
	
	-- 获取奖励所需的背包空间
	nSpace = RewardTemplate_GetRandomSpace(tTable,nIndex,nUserId)
	-- 获取删除的物品所需的背包空间
	nSubSpace = RewardTemplate_GetDelSpace(tAwardChart,nNowUserId)
	
	nSpace = nSpace - nSubSpace
	
	if nSpace > 0 and (not User_CheckLeftSpace(nSpace,nUserId)) then
		return false,nSpace
	end

	return true
end