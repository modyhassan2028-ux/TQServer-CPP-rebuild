------------------------------------------------------------------------------------
--Name:		151010[英文征服][任务脚本]付费移服判断增加
--Purpose:		付费移服判断增加
--Creator:		许乐
--Created:		2015/10/10
------------------------------------------------------------------------------------
-- #任务需求 
-- #1、付费移服npc申请移服之前；判断玩家是否有联盟，有的话不让转服；
-- #2、听剑鸣说；联盟判断需要用lua写；
-- #3、转服npc后面内容弄成LUA
-- #4、BreathFocus
-- #DragonPunch
-- #DragonRoar
-- #Royalty_EU_o (欧服）
-- #Liberty_o（美服）
-- #以上5个服价格判断改成1999
-- #
-- #5、新接口对应链接
-- #http://forum.nderp.99.com/Forum/TopicList-D8C592E066A21417-1.aspx#2305397
-- #任务来自：http://nderp.99.com/Forum/TopicList-233187.aspx

-- 前缀
-- ServerTransferOfficer_
-----------------------------------------常量表配置-----------------------------------------------
local tServerTransferOfficer_Cont = {}
	--时间限制
	tServerTransferOfficer_Cont["Time1"] = "07:00 09:30"
	tServerTransferOfficer_Cont["Time2"] = "15:00 17:30"
	
	tServerTransferOfficer_Cont["Emoney1"] = 3999
	tServerTransferOfficer_Cont["Emoney2"] = 1999

--掩码
local tServerTransferOfficer_Stc = {}
	--30天转服1次
	tServerTransferOfficer_Stc[1]={}
	tServerTransferOfficer_Stc[1]["EventType"] = 114
	tServerTransferOfficer_Stc[1]["DataType"] = 53
	tServerTransferOfficer_Stc[1]["Complete"] = 30

------------------------------------------逻辑部分-------------------------------------------------
function ServerTransferOfficer_JudgeStc(nNpcId)
	local nEvent = tServerTransferOfficer_Stc[1]["EventType"]
	local nType =  tServerTransferOfficer_Stc[1]["DataType"]
	local nComplete = tServerTransferOfficer_Stc[1]["Complete"]
	if not Task_StcInterval(nEvent,nType,nComplete,3) then
		if not Task_ChkStcValue(nEvent,nType,"==",0) then
			Sys_MsgBox(tServerTransferOfficer_Text[105]["30Days"])
			return
		else
			LinkNpcGossipFunc_New(nNpcId,"3-1")
		end
	else
		LinkNpcGossipFunc_New(nNpcId,"3-1")
	end
end

--服务器名称
function ServerTransferOfficer_IsConnectServer(nChoose)
	local sServerName = tServerTransferOfficer_Text["ServerName"][nChoose]
	local str = string.format(tServerTransferOfficer_Text[105]["SureToTrans"],sServerName)
	Sys_MsgBox(str,"ServerTransferOfficer_ConnectJudgement</N>"..nChoose)
end

--转服判断
function ServerTransferOfficer_ConnectJudgement(nChoose)
	if Sys_ChkDayTime(tServerTransferOfficer_Cont["Time1"]) or Sys_ChkDayTime(tServerTransferOfficer_Cont["Time2"]) then
		Sys_MsgBox(tServerTransferOfficer_Text[105]["NotRightTime"])
		return
	end
	
	-- 判断是否打开二级密码 1053
	if not Sys_IsOpenSecondPWD() then
		Sys_MsgBox(tServerTransferOfficer_Text[105]["PasswordTip"])
		return
	end
	
	-- 判断帐号服务器是否正常连接 1215
	if not Sys_IsAccountServerNormal() then
		Sys_MsgBox(tServerTransferOfficer_Text[105]["FailConnect"])
		return
	end
	
	local sServerName = tostring(tServerTransferOfficer_Text["ServerName"][nChoose])
	-- 判断当前是否在该服务器 1213
	if Sys_CheckServerName(sServerName) then
		Sys_MsgBox(tServerTransferOfficer_Text[105]["InSameServer"])
		return
	end
	
	-- 判断转服服务器是否连接上 1205
	if not Sys_IsChangeServerEnable() then
		Sys_MsgBox(tServerTransferOfficer_Text[105]["FailServer"])
		return
	end
	
	-- 判断转服服务器是否空闲 1214
	if not Sys_IsChangeServerIdle() then
		Sys_MsgBox(tServerTransferOfficer_Text[105]["BusyServer"])
		return
	end

	--天石数量判断
	local nEmoney = Get_UserEMoney()
	local nNeedEM = tServerTransferOfficer_Cont["Emoney1"]
	for _,v in pairs(tServerTransferOfficer_Text["EMoney"]) do	
		if Sys_CheckServerName(v) then
			nNeedEM = tServerTransferOfficer_Cont["Emoney2"]
		end
	end
	if nEmoney < nNeedEM then
		Sys_MsgBox(string.format(tServerTransferOfficer_Text[105]["NoEnoughEmoney"],nNeedEM))
		return
	end

	--取玩家伴侣名字
	local nMateId = Get_UserMateId()
	if nMateId ~= 0 then
		Sys_MsgBox(tServerTransferOfficer_Text[105]["Marriage"])
		return
	end
	
	--取玩家帮派ID
	local nGuildId = Get_UserGuildId()
	if nGuildId ~= 0 then
		Sys_MsgBox(tServerTransferOfficer_Text[105]["Guild"])
		return
	end
	
	--取玩家家族ID
	local nFamilyId = Get_UserFamilyId()
	if nFamilyId ~= 0 then
		Sys_MsgBox(tServerTransferOfficer_Text[105]["Family"])
		return
	end
	
	-- 判断是否有联盟
	if User_IsInLeague() then
		Sys_MsgBox(tServerTransferOfficer_Text[105]["League"])
		return
	end
	
	--检测玩家是否存在师徒关系 1206
	if User_CheckGuide() then
		Sys_MsgBox(tServerTransferOfficer_Text[105]["Mentor"])
		return
	end
	
	-- 检测玩家是否存在商业伙伴关系 1207
	if User_CheckTradeBuddy() then
		Sys_MsgBox(tServerTransferOfficer_Text[105]["TradePartner"])
		return
	end
	
	-- -- 检测玩家是否存在拍卖行物品  1210
	-- if User_HasAuctionItem() then
		-- Sys_MsgBox(tServerTransferOfficer_Text[105]["Auction"])
		-- return
	-- end
	
	-- 检测玩家是否存在邮件 1211
	if User_HasMail() then
		Sys_MsgBox(tServerTransferOfficer_Text[105]["Email"])
		return
	end
	
	-- 对cq_pk_item表的检查 2205
	if User_CheckPkItem(0) then
		Sys_MsgBox(tServerTransferOfficer_Text[105]["TargetPKItem"])
		return
	elseif User_CheckPkItem(1) then
		Sys_MsgBox(tServerTransferOfficer_Text[105]["HunterPKItem"])
		return
	end
	
	-- 检测玩家是否存在未领天石卡，一定要同步查表，放在最后面 1209
	if User_CheckCard() then
		Sys_MsgBox(tServerTransferOfficer_Text[105]["ClaimEmoney"])
		return
	end
	
	-- 游服发起转服要求 1212
	User_ChangeServer(sServerName)
end

-------------------------------------------NPC模块--------------------------------------------------
--15702 ServerTransferOfficer
tNpcFace[2415] = 186 
tNpcGossip[15702] = tNpcGossip[15702] or DefaultNpc:new{}
tNpcGossip[15702]["OptionHidden"] = 1

tNpcGossip[15702]["Text1-1"] = {111,112}
tNpcGossip[15702]["Text111"] = tServerTransferOfficer_Text[15702]["Text111"]
tNpcGossip[15702]["Text112"] = tServerTransferOfficer_Text[15702]["Text112"]
tNpcGossip[15702]["tOption1-1"] = {1,2,3}
tNpcGossip[15702]["Option1"] = tServerTransferOfficer_Text[15702]["Option1"]
tNpcGossip[15702]["OptionPoint1"]="2-1"
tNpcGossip[15702]["Option2"] = tServerTransferOfficer_Text[15702]["Option2"]
tNpcGossip[15702]["OptionFunc2"]="ServerTransferOfficer_JudgeStc</N>15702"
tNpcGossip[15702]["Option3"] = tServerTransferOfficer_Text[15702]["Option3"]

tNpcGossip[15702]["Text2-1"] = {211,212,213,214,215,216}
tNpcGossip[15702]["Text211"] = tServerTransferOfficer_Text[15702]["Text211"]
tNpcGossip[15702]["Text212"] = tServerTransferOfficer_Text[15702]["Text212"]
tNpcGossip[15702]["Text213"] = tServerTransferOfficer_Text[15702]["Text213"]
tNpcGossip[15702]["Text214"] = tServerTransferOfficer_Text[15702]["Text214"]
tNpcGossip[15702]["Text215"] = tServerTransferOfficer_Text[15702]["Text215"]
tNpcGossip[15702]["Text216"] = tServerTransferOfficer_Text[15702]["Text216"]
tNpcGossip[15702]["tOption2-1"] = {4}
tNpcGossip[15702]["Option4"] = tServerTransferOfficer_Text[15702]["Option4"]

tNpcGossip[15702]["Text3-1"] = {311}
tNpcGossip[15702]["Text311"] = tServerTransferOfficer_Text[15702]["Text311"]
tNpcGossip[15702]["tOption3-1"] = {5,6,7,8,9,10,11,3}
tNpcGossip[15702]["Option5"] = tServerTransferOfficer_Text[15702]["Option5"]
tNpcGossip[15702]["OptionPoint5"]="5-1"
tNpcGossip[15702]["Option6"] = tServerTransferOfficer_Text[15702]["Option6"]
tNpcGossip[15702]["OptionPoint6"]="6-1"
tNpcGossip[15702]["Option7"] = tServerTransferOfficer_Text[15702]["Option7"]
tNpcGossip[15702]["OptionPoint7"]="7-1"
tNpcGossip[15702]["Option8"] = tServerTransferOfficer_Text[15702]["Option8"]
tNpcGossip[15702]["OptionPoint8"]="8-1"
tNpcGossip[15702]["Option9"] = tServerTransferOfficer_Text[15702]["Option9"]
tNpcGossip[15702]["OptionPoint9"]="9-1"
tNpcGossip[15702]["Option10"] = tServerTransferOfficer_Text[15702]["Option10"]
tNpcGossip[15702]["OptionPoint10"]="10-1"
tNpcGossip[15702]["Option11"] = tServerTransferOfficer_Text[15702]["Option11"]
tNpcGossip[15702]["OptionPoint11"]="3-2"

tNpcGossip[15702]["Text3-2"] = {321}
tNpcGossip[15702]["Text321"] = tServerTransferOfficer_Text[15702]["Text321"]
tNpcGossip[15702]["tOption3-2"] = {12,13,14,15,16,17,21,3}
tNpcGossip[15702]["Option12"] = tServerTransferOfficer_Text[15702]["Option12"]
tNpcGossip[15702]["OptionPoint12"]="12-1"
tNpcGossip[15702]["Option13"] = tServerTransferOfficer_Text[15702]["Option13"]
tNpcGossip[15702]["OptionPoint13"]="13-1"
tNpcGossip[15702]["Option14"] = tServerTransferOfficer_Text[15702]["Option14"]
tNpcGossip[15702]["OptionPoint14"]="14-1"
tNpcGossip[15702]["Option15"] = tServerTransferOfficer_Text[15702]["Option15"]
tNpcGossip[15702]["OptionPoint15"]="15-1"
tNpcGossip[15702]["Option16"] = tServerTransferOfficer_Text[15702]["Option16"]
tNpcGossip[15702]["OptionPoint16"]="16-1"
tNpcGossip[15702]["Option17"] = tServerTransferOfficer_Text[15702]["Option17"]
tNpcGossip[15702]["OptionPoint17"]="17-1"
tNpcGossip[15702]["Option21"] = tServerTransferOfficer_Text[15702]["Option21"]
tNpcGossip[15702]["OptionPoint21"]="3-3"

tNpcGossip[15702]["Text3-3"] = {331}
tNpcGossip[15702]["Text331"] = tServerTransferOfficer_Text[15702]["Text331"]
tNpcGossip[15702]["tOption3-3"] = {18,19,20,22,3}
tNpcGossip[15702]["Option18"] = tServerTransferOfficer_Text[15702]["Option18"]
tNpcGossip[15702]["OptionPoint18"]="18-1"
tNpcGossip[15702]["Option19"] = tServerTransferOfficer_Text[15702]["Option19"]
tNpcGossip[15702]["OptionPoint19"]="19-1"
tNpcGossip[15702]["Option20"] = tServerTransferOfficer_Text[15702]["Option20"]
tNpcGossip[15702]["OptionPoint20"]="20-1"
tNpcGossip[15702]["Option22"] = tServerTransferOfficer_Text[15702]["Option22"]
tNpcGossip[15702]["OptionPoint22"]="22-1"

tNpcGossip[15702]["Text5-1"] = {511}
tNpcGossip[15702]["Text511"] = tServerTransferOfficer_Text[15702]["Text511"]
tNpcGossip[15702]["tOption5-1"] = {511,512,513,514,515,3}
tNpcGossip[15702]["Option511"] = tServerTransferOfficer_Text[15702]["Option511"]
tNpcGossip[15702]["OptionFunc511"]="ServerTransferOfficer_IsConnectServer</N>1"
tNpcGossip[15702]["Option512"] = tServerTransferOfficer_Text[15702]["Option512"]
tNpcGossip[15702]["OptionFunc512"]="ServerTransferOfficer_IsConnectServer</N>2"
tNpcGossip[15702]["Option513"] = tServerTransferOfficer_Text[15702]["Option513"]
tNpcGossip[15702]["OptionFunc513"]="ServerTransferOfficer_IsConnectServer</N>3"
tNpcGossip[15702]["Option514"] = tServerTransferOfficer_Text[15702]["Option514"]
tNpcGossip[15702]["OptionFunc514"]="ServerTransferOfficer_IsConnectServer</N>4"
tNpcGossip[15702]["Option515"] = tServerTransferOfficer_Text[15702]["Option515"]
tNpcGossip[15702]["OptionFunc515"]="ServerTransferOfficer_IsConnectServer</N>5"

tNpcGossip[15702]["Text6-1"] = {611}
tNpcGossip[15702]["Text611"] = tServerTransferOfficer_Text[15702]["Text511"]
tNpcGossip[15702]["tOption6-1"] = {611,612,613,3}
tNpcGossip[15702]["Option611"] = tServerTransferOfficer_Text[15702]["Option611"]
tNpcGossip[15702]["OptionFunc611"]="ServerTransferOfficer_IsConnectServer</N>6"
tNpcGossip[15702]["Option612"] = tServerTransferOfficer_Text[15702]["Option612"]
tNpcGossip[15702]["OptionFunc612"]="ServerTransferOfficer_IsConnectServer</N>7"
tNpcGossip[15702]["Option613"] = tServerTransferOfficer_Text[15702]["Option613"]
tNpcGossip[15702]["OptionFunc613"]="ServerTransferOfficer_IsConnectServer</N>8"

tNpcGossip[15702]["Text7-1"] = {711}
tNpcGossip[15702]["Text711"] = tServerTransferOfficer_Text[15702]["Text511"]
tNpcGossip[15702]["tOption7-1"] = {711,712,713,714,715,3}
tNpcGossip[15702]["Option711"] = tServerTransferOfficer_Text[15702]["Option711"]
tNpcGossip[15702]["OptionFunc711"]="ServerTransferOfficer_IsConnectServer</N>9"
tNpcGossip[15702]["Option712"] = tServerTransferOfficer_Text[15702]["Option712"]
tNpcGossip[15702]["OptionFunc712"]="ServerTransferOfficer_IsConnectServer</N>10"
tNpcGossip[15702]["Option713"] = tServerTransferOfficer_Text[15702]["Option713"]
tNpcGossip[15702]["OptionFunc713"]="ServerTransferOfficer_IsConnectServer</N>11"
tNpcGossip[15702]["Option714"] = tServerTransferOfficer_Text[15702]["Option714"]
tNpcGossip[15702]["OptionFunc714"]="ServerTransferOfficer_IsConnectServer</N>12"
tNpcGossip[15702]["Option715"] = tServerTransferOfficer_Text[15702]["Option715"]
tNpcGossip[15702]["OptionFunc715"]="ServerTransferOfficer_IsConnectServer</N>13"

tNpcGossip[15702]["Text8-1"] = {811}
tNpcGossip[15702]["Text811"] = tServerTransferOfficer_Text[15702]["Text511"]
tNpcGossip[15702]["tOption8-1"] = {811,812,813,814,815,3}
tNpcGossip[15702]["Option811"] = tServerTransferOfficer_Text[15702]["Option811"]
tNpcGossip[15702]["OptionFunc811"]="ServerTransferOfficer_IsConnectServer</N>14"
tNpcGossip[15702]["Option812"] = tServerTransferOfficer_Text[15702]["Option812"]
tNpcGossip[15702]["OptionFunc812"]="ServerTransferOfficer_IsConnectServer</N>15"
tNpcGossip[15702]["Option813"] = tServerTransferOfficer_Text[15702]["Option813"]
tNpcGossip[15702]["OptionFunc813"]="ServerTransferOfficer_IsConnectServer</N>16"
tNpcGossip[15702]["Option814"] = tServerTransferOfficer_Text[15702]["Option814"]
tNpcGossip[15702]["OptionFunc814"]="ServerTransferOfficer_IsConnectServer</N>17"
tNpcGossip[15702]["Option815"] = tServerTransferOfficer_Text[15702]["Option815"]
tNpcGossip[15702]["OptionFunc815"]="ServerTransferOfficer_IsConnectServer</N>18"

tNpcGossip[15702]["Text9-1"] = {611}
tNpcGossip[15702]["Text911"] = tServerTransferOfficer_Text[15702]["Text511"]
tNpcGossip[15702]["tOption9-1"] = {911,912,913,914,3}
tNpcGossip[15702]["Option911"] = tServerTransferOfficer_Text[15702]["Option911"]
tNpcGossip[15702]["OptionFunc911"]="ServerTransferOfficer_IsConnectServer</N>19"
tNpcGossip[15702]["Option912"] = tServerTransferOfficer_Text[15702]["Option912"]
tNpcGossip[15702]["OptionFunc912"]="ServerTransferOfficer_IsConnectServer</N>20"
tNpcGossip[15702]["Option913"] = tServerTransferOfficer_Text[15702]["Option913"]
tNpcGossip[15702]["OptionFunc913"]="ServerTransferOfficer_IsConnectServer</N>21"
tNpcGossip[15702]["Option914"] = tServerTransferOfficer_Text[15702]["Option914"]
tNpcGossip[15702]["OptionFunc914"]="ServerTransferOfficer_IsConnectServer</N>22"

tNpcGossip[15702]["Text10-1"] = {1011}
tNpcGossip[15702]["Text1011"] = tServerTransferOfficer_Text[15702]["Text511"]
tNpcGossip[15702]["tOption10-1"] = {1011,1012,1013,3}
tNpcGossip[15702]["Option1011"] = tServerTransferOfficer_Text[15702]["Option1011"]
tNpcGossip[15702]["OptionFunc1011"]="ServerTransferOfficer_IsConnectServer</N>23"
tNpcGossip[15702]["Option1012"] = tServerTransferOfficer_Text[15702]["Option1012"]
tNpcGossip[15702]["OptionFunc1012"]="ServerTransferOfficer_IsConnectServer</N>24"
tNpcGossip[15702]["Option1013"] = tServerTransferOfficer_Text[15702]["Option1013"]
tNpcGossip[15702]["OptionFunc1013"]="ServerTransferOfficer_IsConnectServer</N>25"
-- tNpcGossip[15702]["Option1014"] = tServerTransferOfficer_Text[15702]["Option1014"]
-- tNpcGossip[15702]["OptionFunc1014"]="ServerTransferOfficer_IsConnectServer</N>26"

tNpcGossip[15702]["Text12-1"] = {1211}
tNpcGossip[15702]["Text1211"] = tServerTransferOfficer_Text[15702]["Text511"]
tNpcGossip[15702]["tOption12-1"] = {1211,1212,3}
tNpcGossip[15702]["Option1211"] = tServerTransferOfficer_Text[15702]["Option1211"]
tNpcGossip[15702]["OptionFunc1211"]="ServerTransferOfficer_IsConnectServer</N>27"
tNpcGossip[15702]["Option1212"] = tServerTransferOfficer_Text[15702]["Option1212"]
tNpcGossip[15702]["OptionFunc1212"]="ServerTransferOfficer_IsConnectServer</N>28"

tNpcGossip[15702]["Text13-1"] = {1311}
tNpcGossip[15702]["Text1311"] = tServerTransferOfficer_Text[15702]["Text511"]
tNpcGossip[15702]["tOption13-1"] = {1311,1312,1313,1314,1315,3}
tNpcGossip[15702]["Option1311"] = tServerTransferOfficer_Text[15702]["Option1311"]
tNpcGossip[15702]["OptionFunc1311"]="ServerTransferOfficer_IsConnectServer</N>29"
tNpcGossip[15702]["Option1312"] = tServerTransferOfficer_Text[15702]["Option1312"]
tNpcGossip[15702]["OptionFunc1312"]="ServerTransferOfficer_IsConnectServer</N>30"
tNpcGossip[15702]["Option1313"] = tServerTransferOfficer_Text[15702]["Option1313"]
tNpcGossip[15702]["OptionFunc1313"]="ServerTransferOfficer_IsConnectServer</N>31"
tNpcGossip[15702]["Option1314"] = tServerTransferOfficer_Text[15702]["Option1314"]
tNpcGossip[15702]["OptionFunc1314"]="ServerTransferOfficer_IsConnectServer</N>32"
tNpcGossip[15702]["Option1315"] = tServerTransferOfficer_Text[15702]["Option1315"]
tNpcGossip[15702]["OptionFunc1315"]="ServerTransferOfficer_IsConnectServer</N>33"

tNpcGossip[15702]["Text14-1"] = {1411}
tNpcGossip[15702]["Text1411"] = tServerTransferOfficer_Text[15702]["Text511"]
tNpcGossip[15702]["tOption14-1"] = {1411,1412,3}
tNpcGossip[15702]["Option1411"] = tServerTransferOfficer_Text[15702]["Option1411"]
tNpcGossip[15702]["OptionFunc1411"]="ServerTransferOfficer_IsConnectServer</N>34"
tNpcGossip[15702]["Option1412"] = tServerTransferOfficer_Text[15702]["Option1412"]
tNpcGossip[15702]["OptionFunc1412"]="ServerTransferOfficer_IsConnectServer</N>35"

tNpcGossip[15702]["Text15-1"] = {1511}
tNpcGossip[15702]["Text1511"] = tServerTransferOfficer_Text[15702]["Text511"]
tNpcGossip[15702]["tOption15-1"] = {1511,1512,1513,3}
tNpcGossip[15702]["Option1511"] = tServerTransferOfficer_Text[15702]["Option1511"]
tNpcGossip[15702]["OptionFunc1511"]="ServerTransferOfficer_IsConnectServer</N>36"
tNpcGossip[15702]["Option1512"] = tServerTransferOfficer_Text[15702]["Option1512"]
tNpcGossip[15702]["OptionFunc1512"]="ServerTransferOfficer_IsConnectServer</N>37"
tNpcGossip[15702]["Option1513"] = tServerTransferOfficer_Text[15702]["Option1513"]
tNpcGossip[15702]["OptionFunc1513"]="ServerTransferOfficer_IsConnectServer</N>38"

tNpcGossip[15702]["Text16-1"] = {1611}
tNpcGossip[15702]["Text1611"] = tServerTransferOfficer_Text[15702]["Text511"]
tNpcGossip[15702]["tOption16-1"] = {1611,1612,1613,1614,3}
tNpcGossip[15702]["Option1611"] = tServerTransferOfficer_Text[15702]["Option1611"]
tNpcGossip[15702]["OptionFunc1611"]="ServerTransferOfficer_IsConnectServer</N>39"
tNpcGossip[15702]["Option1612"] = tServerTransferOfficer_Text[15702]["Option1612"]
tNpcGossip[15702]["OptionFunc1612"]="ServerTransferOfficer_IsConnectServer</N>40"
tNpcGossip[15702]["Option1613"] = tServerTransferOfficer_Text[15702]["Option1613"]
tNpcGossip[15702]["OptionFunc1613"]="ServerTransferOfficer_IsConnectServer</N>41"
tNpcGossip[15702]["Option1614"] = tServerTransferOfficer_Text[15702]["Option1614"]
tNpcGossip[15702]["OptionFunc1614"]="ServerTransferOfficer_IsConnectServer</N>42"

tNpcGossip[15702]["Text17-1"] = {1711}
tNpcGossip[15702]["Text1711"] = tServerTransferOfficer_Text[15702]["Text511"]
tNpcGossip[15702]["tOption17-1"] = {1711,1712,3}
tNpcGossip[15702]["Option1711"] = tServerTransferOfficer_Text[15702]["Option1711"]
tNpcGossip[15702]["OptionFunc1711"]="ServerTransferOfficer_IsConnectServer</N>43"
tNpcGossip[15702]["Option1712"] = tServerTransferOfficer_Text[15702]["Option1712"]
tNpcGossip[15702]["OptionFunc1712"]="ServerTransferOfficer_IsConnectServer</N>44"

tNpcGossip[15702]["Text18-1"] = {1811}
tNpcGossip[15702]["Text1811"] = tServerTransferOfficer_Text[15702]["Text511"]
tNpcGossip[15702]["tOption18-1"] = {1811,1812,1813,3}
tNpcGossip[15702]["Option1811"] = tServerTransferOfficer_Text[15702]["Option1811"]
tNpcGossip[15702]["OptionFunc1811"]="ServerTransferOfficer_IsConnectServer</N>45"
tNpcGossip[15702]["Option1812"] = tServerTransferOfficer_Text[15702]["Option1812"]
tNpcGossip[15702]["OptionFunc1812"]="ServerTransferOfficer_IsConnectServer</N>46"
tNpcGossip[15702]["Option1813"] = tServerTransferOfficer_Text[15702]["Option1813"]
tNpcGossip[15702]["OptionFunc1813"]="ServerTransferOfficer_IsConnectServer</N>47"
tNpcGossip[15702]["Option1814"] = tServerTransferOfficer_Text[15702]["Option1814"]
tNpcGossip[15702]["OptionFunc1814"]="ServerTransferOfficer_IsConnectServer</N>48"
tNpcGossip[15702]["Option1815"] = tServerTransferOfficer_Text[15702]["Option1815"]
tNpcGossip[15702]["OptionFunc1815"]="ServerTransferOfficer_IsConnectServer</N>49"

tNpcGossip[15702]["Text19-1"] = {1911}
tNpcGossip[15702]["Text1911"] = tServerTransferOfficer_Text[15702]["Text511"]
tNpcGossip[15702]["tOption19-1"] = {1912,3}
tNpcGossip[15702]["Option1911"] = tServerTransferOfficer_Text[15702]["Option1911"]
tNpcGossip[15702]["OptionFunc1911"]="ServerTransferOfficer_IsConnectServer</N>50"
tNpcGossip[15702]["Option1912"] = tServerTransferOfficer_Text[15702]["Option1912"]
tNpcGossip[15702]["OptionFunc1912"]="ServerTransferOfficer_IsConnectServer</N>54"

tNpcGossip[15702]["Text20-1"] = {2011}
tNpcGossip[15702]["Text2011"] = tServerTransferOfficer_Text[15702]["Text511"]
tNpcGossip[15702]["tOption20-1"] = {2011,2012,3}
tNpcGossip[15702]["Option2011"] = tServerTransferOfficer_Text[15702]["Option2011"]
tNpcGossip[15702]["OptionFunc2011"]="ServerTransferOfficer_IsConnectServer</N>51"
tNpcGossip[15702]["OptionChkFunc2011"] = function ()
	if Sys_CheckServerName(tServerTransferOfficer_Text["ServerName"][52]) then
		return true
	else
		return false
	end
end
tNpcGossip[15702]["Option2012"] = tServerTransferOfficer_Text[15702]["Option2012"]
tNpcGossip[15702]["OptionFunc2012"]="ServerTransferOfficer_IsConnectServer</N>52"
tNpcGossip[15702]["OptionChkFunc2012"] = function ()
	if Sys_CheckServerName(tServerTransferOfficer_Text["ServerName"][51]) then
		return true
	else
		return false
	end
end

tNpcGossip[15702]["Text22-1"] = {2211,2212}
tNpcGossip[15702]["Text2211"] = tServerTransferOfficer_Text[15702]["Text2211"]
tNpcGossip[15702]["Text2212"] = tServerTransferOfficer_Text[15702]["Text2212"]
tNpcGossip[15702]["tOption22-1"] = {23,24}
tNpcGossip[15702]["Option23"] = tServerTransferOfficer_Text[15702]["Option23"]
tNpcGossip[15702]["OptionFunc23"]="ServerTransferOfficer_IsConnectServer</N>53"
tNpcGossip[15702]["Option24"] = tServerTransferOfficer_Text[15702]["Option24"]

--18873 ServerTransferOfficer  1002,284,289
tNpcFace[2415] = 186 
tNpcGossip[18873] = tNpcGossip[18873] or DefaultNpc:new{}
tNpcGossip[18873]["OptionHidden"] = 1

tNpcGossip[18873]["Text1-1"] = {111}
tNpcGossip[18873]["Text111"] = tServerTransferOfficer_Text[18873]["Text111"]
tNpcGossip[18873]["tOption1-1"] = {1}
tNpcGossip[18873]["Option1"] = tServerTransferOfficer_Text[18873]["Option1"]
