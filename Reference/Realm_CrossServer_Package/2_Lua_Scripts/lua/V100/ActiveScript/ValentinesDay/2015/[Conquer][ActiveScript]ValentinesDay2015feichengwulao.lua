------------------------------------------------------------------------------------
--Name:			[征服][活动脚本]2015年情人节之甜蜜约会之非诚勿扰（2.11-2.14）
--Creator: 		魏贻逵
--Created:		2014/12/03
------------------------------------------------------------------------------------
-- 命名前缀
-- ValentinesDay2015_feichengwulao

-- 活动时间
local tValentinesDay2015_feichengwulao_Cont = {}
tValentinesDay2015_feichengwulao_Cont["Beftime"]= "2014-02-11 00:00 2015-02-10 23:59"
tValentinesDay2015_feichengwulao_Cont["Nowtime"] = "2015-02-11 00:00 2015-02-14 23:59"
--tValentinesDay2015_feichengwulao_Cont["Nowdaytime"] = "19:00 22:59"
tValentinesDay2015_feichengwulao_Cont["Aftime"] = "2015-02-15 00:00 2020-02-10 23:59"

-- 玩家等级要求
tValentinesDay2015_feichengwulao_Cont["Metempsychosis"] = 1
tValentinesDay2015_feichengwulao_Cont["Level"] = 80

--传送地点
--活动地图坐标
tValentinesDay2015_feichengwulao_Cont["MapId"] = 3897
tValentinesDay2015_feichengwulao_Cont["CellX"] = 77
tValentinesDay2015_feichengwulao_Cont["CellY"] = 71
tValentinesDay2015_feichengwulao_Cont["BoundCX"] = 5
tValentinesDay2015_feichengwulao_Cont["BoundCY"] = 5

--返回双龙城坐标
tValentinesDay2015_feichengwulao_Cont["MapId1"] = 1002
tValentinesDay2015_feichengwulao_Cont["CellX1"] = 275
tValentinesDay2015_feichengwulao_Cont["CellY1"] = 380

--奖励背包空间和物品
tValentinesDay2015_feichengwulao_Cont["Space"] = 2
tValentinesDay2015_feichengwulao_Cont["RewardItem"] = 3005410

--寻路NPC
local tValentinesDay2015_feichengwulao_npc = {}
tValentinesDay2015_feichengwulao_npc["NpcId"] = 17322
tValentinesDay2015_feichengwulao_npc["MapId"] = 3897
tValentinesDay2015_feichengwulao_npc["CellX"] = 92
tValentinesDay2015_feichengwulao_npc["CellY"] = 69

-- log表
local tValentinesDay2015_feichengwulao_Log = {}
tValentinesDay2015_feichengwulao_Log["New"] = "0,0,0,0,10002402,1[1],0,0"
tValentinesDay2015_feichengwulao_Log["Complete"] = "0,0,0,0,10002402,1[2],0,0"
tValentinesDay2015_feichengwulao_Log["RewardLog"] = "0,0,0,0,10002402,2,3005410,1"
tValentinesDay2015_feichengwulao_Log["FestivalId"] = 3353
tValentinesDay2015_feichengwulao_Log["LogId"] = 10002402

-- 奖励掩码 1表示接任务 2表示领取奖励
local tValentinesDay2015_feichengwulao_stc = {}
tValentinesDay2015_feichengwulao_stc[1] = {}
tValentinesDay2015_feichengwulao_stc[1]["StcEvent"] = 131
tValentinesDay2015_feichengwulao_stc[1]["StcType"] = 80
tValentinesDay2015_feichengwulao_stc[1]["New"] = 1
tValentinesDay2015_feichengwulao_stc[1]["Complete"] = 2

 --完成次数掩码
tValentinesDay2015_feichengwulao_stc[2] = {}
tValentinesDay2015_feichengwulao_stc[2]["StcEvent"] = 131
tValentinesDay2015_feichengwulao_stc[2]["StcType"] = 81
tValentinesDay2015_feichengwulao_stc[2]["Complete"] = 3

 --家具npc对话掩码
tValentinesDay2015_feichengwulao_stc[17409] = {}
tValentinesDay2015_feichengwulao_stc[17409]["StcEvent"] = 131
tValentinesDay2015_feichengwulao_stc[17409]["StcType"] = 82
tValentinesDay2015_feichengwulao_stc[17409]["Complete"] = 1

tValentinesDay2015_feichengwulao_stc[17410] = {}
tValentinesDay2015_feichengwulao_stc[17410]["StcEvent"] = 131
tValentinesDay2015_feichengwulao_stc[17410]["StcType"] = 83
tValentinesDay2015_feichengwulao_stc[17410]["Complete"] = 1

tValentinesDay2015_feichengwulao_stc[17411] = {}
tValentinesDay2015_feichengwulao_stc[17411]["StcEvent"] = 131
tValentinesDay2015_feichengwulao_stc[17411]["StcType"] = 84
tValentinesDay2015_feichengwulao_stc[17411]["Complete"] = 1

tValentinesDay2015_feichengwulao_stc[17412] = {}
tValentinesDay2015_feichengwulao_stc[17412]["StcEvent"] = 131
tValentinesDay2015_feichengwulao_stc[17412]["StcType"] = 85
tValentinesDay2015_feichengwulao_stc[17412]["Complete"] = 1

tValentinesDay2015_feichengwulao_stc[17413] = {}
tValentinesDay2015_feichengwulao_stc[17413]["StcEvent"] = 131
tValentinesDay2015_feichengwulao_stc[17413]["StcType"] = 86
tValentinesDay2015_feichengwulao_stc[17413]["Complete"] = 1

---------------------------------------------------对话模板部分-----------------------------------------
-- 男媒婆姚大痣
tNpcFace[3378] = 7
tNpcGossip[17321] = tNpcGossip[17321] or DefaultNpc:new{}
tNpcGossip[17321]["OptionHidden"] = 1

-- 活动前
tNpcGossip[17321]["Text1-1"] = {111,112,113}
tNpcGossip[17321]["Text111"] = tValentinesDay2015_feichengwulao_Text[17321]["Text111"]
tNpcGossip[17321]["Text112"] = tValentinesDay2015_feichengwulao_Text[17321]["Text112"]
tNpcGossip[17321]["Text113"] = tValentinesDay2015_feichengwulao_Text[17321]["Text113"]
tNpcGossip[17321]["tOption1-1"] = {1}
tNpcGossip[17321]["Option1"] = tValentinesDay2015_feichengwulao_Text[17321]["Option1"]
tNpcGossip[17321]["ChkFunc1-1"] = function ()
	return Sys_ChkFullTime(tValentinesDay2015_feichengwulao_Cont["Beftime"])
end

-- 活动后
tNpcGossip[17321]["Text1-2"] = {121,122}
tNpcGossip[17321]["Text121"] = tValentinesDay2015_feichengwulao_Text[17321]["Text121"] 
tNpcGossip[17321]["Text122"] = tValentinesDay2015_feichengwulao_Text[17321]["Text122"]
tNpcGossip[17321]["tOption1-2"] = {2}
tNpcGossip[17321]["Option2"] = tValentinesDay2015_feichengwulao_Text[17321]["Option2"]
tNpcGossip[17321]["ChkFunc1-2"] = function ()
	return Sys_ChkFullTime(tValentinesDay2015_feichengwulao_Cont["Aftime"])
end

-- 活动中
tNpcGossip[17321]["Text1-3"] = {131,132,133,134}
tNpcGossip[17321]["Text131"] = tValentinesDay2015_feichengwulao_Text[17321]["Text131"] 
tNpcGossip[17321]["Text132"] = tValentinesDay2015_feichengwulao_Text[17321]["Text132"]
tNpcGossip[17321]["Text133"] = tValentinesDay2015_feichengwulao_Text[17321]["Text133"]
tNpcGossip[17321]["Text134"] = tValentinesDay2015_feichengwulao_Text[17321]["Text134"]
tNpcGossip[17321]["tOption1-3"] = {3,4,5,1000,6}
tNpcGossip[17321]["Option3"] = tValentinesDay2015_feichengwulao_Text[17321]["Option3"]
tNpcGossip[17321]["Option4"] = tValentinesDay2015_feichengwulao_Text[17321]["Option4"]
tNpcGossip[17321]["Option5"] = tValentinesDay2015_feichengwulao_Text[17321]["Option5"]
tNpcGossip[17321]["Option6"] = tValentinesDay2015_feichengwulao_Text[17321]["Option6"]
tNpcGossip[17321]["ChkFunc1-3"] = function ()
	return Sys_ChkFullTime(tValentinesDay2015_feichengwulao_Cont["Nowtime"])
end
tNpcGossip[17321]["OptionFunc3"]="ValentinesDay2015_feichengwulao_Option3_17321</N>17321"
tNpcGossip[17321]["OptionFunc4"]="ValentinesDay2015_feichengwulao_Option4_17321</N>17321"
tNpcGossip[17321]["OptionPoint5"]="5"

--"我要帮忙，带我去后花园！"
--tNpcGossip[17321]["Text3-1"] = {311,312}
--tNpcGossip[17321]["Text311"] = tValentinesDay2015_feichengwulao_Text[17321]["Text311"]
--tNpcGossip[17321]["Text312"] = tValentinesDay2015_feichengwulao_Text[17321]["Text312"]
--tNpcGossip[17321]["tOption3-1"] = {7}
--tNpcGossip[17321]["Option7"] = tValentinesDay2015_feichengwulao_Text[17321]["Option7"]

tNpcGossip[17321]["Text3-2"] = {321,322}
tNpcGossip[17321]["Text321"] = tValentinesDay2015_feichengwulao_Text[17321]["Text321"]
tNpcGossip[17321]["Text322"] = tValentinesDay2015_feichengwulao_Text[17321]["Text322"]
tNpcGossip[17321]["tOption3-2"] = {8}
tNpcGossip[17321]["Option8"] = tValentinesDay2015_feichengwulao_Text[17321]["Option8"]

tNpcGossip[17321]["Text3-3"] = {331,332}
tNpcGossip[17321]["Text331"] = tValentinesDay2015_feichengwulao_Text[17321]["Text331"]
tNpcGossip[17321]["Text332"] = tValentinesDay2015_feichengwulao_Text[17321]["Text332"]
tNpcGossip[17321]["tOption3-3"] = {9}
tNpcGossip[17321]["Option9"] = tValentinesDay2015_feichengwulao_Text[17321]["Option9"]

tNpcGossip[17321]["Text3-4"] = {341,342}
tNpcGossip[17321]["Text341"] = tValentinesDay2015_feichengwulao_Text[17321]["Text341"]
tNpcGossip[17321]["Text342"] = tValentinesDay2015_feichengwulao_Text[17321]["Text342"]
tNpcGossip[17321]["tOption3-4"] = {10}
tNpcGossip[17321]["Option10"] = tValentinesDay2015_feichengwulao_Text[17321]["Option10"]

--"领取报酬。"
tNpcGossip[17321]["Text4-1"] = {411,412}
tNpcGossip[17321]["Text411"] = tValentinesDay2015_feichengwulao_Text[17321]["Text411"] 
tNpcGossip[17321]["Text412"] = tValentinesDay2015_feichengwulao_Text[17321]["Text412"] 
tNpcGossip[17321]["tOption4-1"] = {11}
tNpcGossip[17321]["Option11"] = tValentinesDay2015_feichengwulao_Text[17321]["Option11"]

tNpcGossip[17321]["Text4-2"] = {421}
tNpcGossip[17321]["Text421"] = tValentinesDay2015_feichengwulao_Text[17321]["Text421"]
tNpcGossip[17321]["tOption4-2"] = {12}
tNpcGossip[17321]["Option12"] = tValentinesDay2015_feichengwulao_Text[17321]["Option12"]

tNpcGossip[17321]["Text4-3"] = {431}
tNpcGossip[17321]["Text431"] = tValentinesDay2015_feichengwulao_Text[17321]["Text431"]
tNpcGossip[17321]["tOption4-3"] = {13}
tNpcGossip[17321]["Option13"] = tValentinesDay2015_feichengwulao_Text[17321]["Option13"]

tNpcGossip[17321]["Text4-4"] = {441,442}
tNpcGossip[17321]["Text441"] = tValentinesDay2015_feichengwulao_Text[17321]["Text441"]
tNpcGossip[17321]["Text442"] = tValentinesDay2015_feichengwulao_Text[17321]["Text442"]
tNpcGossip[17321]["tOption4-4"] = {14}
tNpcGossip[17321]["Option14"] = tValentinesDay2015_feichengwulao_Text[17321]["Option14"]

tNpcGossip[17321]["Text5-1"] = {511,512,513,514}
tNpcGossip[17321]["Text511"] = tValentinesDay2015_feichengwulao_Text[17321]["Text511"]
tNpcGossip[17321]["Text512"] = tValentinesDay2015_feichengwulao_Text[17321]["Text512"]
tNpcGossip[17321]["Text513"] = tValentinesDay2015_feichengwulao_Text[17321]["Text513"]
tNpcGossip[17321]["Text514"] = tValentinesDay2015_feichengwulao_Text[17321]["Text514"]
tNpcGossip[17321]["tOption5-1"] = {15}
tNpcGossip[17321]["Option15"] = tValentinesDay2015_feichengwulao_Text[17321]["Option15"]

--伙计姚前树
tNpcFace[3379] = 22
tNpcGossip[17322] = tNpcGossip[17322] or DefaultNpc:new{}
tNpcGossip[17322]["OptionHidden"] = 1

tNpcGossip[17322]["Text1-1"] = {111,112,113}
tNpcGossip[17322]["Text111"] = tValentinesDay2015_feichengwulao_Text[17322]["Text111"]
tNpcGossip[17322]["Text112"] = tValentinesDay2015_feichengwulao_Text[17322]["Text112"]
tNpcGossip[17322]["Text113"] = tValentinesDay2015_feichengwulao_Text[17322]["Text113"]
tNpcGossip[17322]["tOption1-1"] = {1,2,3}
tNpcGossip[17322]["Option1"] = tValentinesDay2015_feichengwulao_Text[17322]["Option1"]
tNpcGossip[17322]["Option2"] = tValentinesDay2015_feichengwulao_Text[17322]["Option2"] 
tNpcGossip[17322]["Option3"] = tValentinesDay2015_feichengwulao_Text[17322]["Option3"]
tNpcGossip[17322]["OptionFunc1"]="ValentinesDay2015_feichengwulao_Option1_17322</N>17322"
tNpcGossip[17322]["OptionPoint2"]="2"

tNpcGossip[17322]["Text1-2"] = {121}
tNpcGossip[17322]["Text121"] = tValentinesDay2015_feichengwulao_Text[17322]["Text121"]
tNpcGossip[17322]["tOption1-2"] = {4,5}
tNpcGossip[17322]["Option4"] = tValentinesDay2015_feichengwulao_Text[17322]["Option4"] 
tNpcGossip[17322]["Option5"] = tValentinesDay2015_feichengwulao_Text[17322]["Option5"]
tNpcGossip[17322]["OptionFunc4"]="ValentinesDay2015_feichengwulao_Option4_17322</N>17322"

tNpcGossip[17322]["Text2-1"] = {211,212,213,214}
tNpcGossip[17322]["Text211"] = tValentinesDay2015_feichengwulao_Text[17322]["Text211"]
tNpcGossip[17322]["Text212"] = tValentinesDay2015_feichengwulao_Text[17322]["Text212"]
tNpcGossip[17322]["Text213"] = tValentinesDay2015_feichengwulao_Text[17322]["Text213"]
tNpcGossip[17322]["Text214"] = tValentinesDay2015_feichengwulao_Text[17322]["Text214"]
tNpcGossip[17322]["tOption2-1"] = {6}
tNpcGossip[17322]["Option6"] = tValentinesDay2015_feichengwulao_Text[17322]["Option6"]

----情侣对白
--留声机旁的女NPC
tNpcFace[3380] = 119
tNpcGossip[17323] = tNpcGossip[17323] or DefaultNpc:new{}
tNpcGossip[17323]["OptionHidden"] = 1

tNpcGossip[17323]["Text1-1"] = {111}
tNpcGossip[17323]["Text111"] = tValentinesDay2015_feichengwulao_Text[17323]["Text111"]
tNpcGossip[17323]["tOption1-1"] = {1}
tNpcGossip[17323]["Option1"] = tValentinesDay2015_feichengwulao_Text[17323]["Option1"] 
tNpcGossip[17323]["ChkFunc1-1"] = function ()
	return Task_ChkStcValue(tValentinesDay2015_feichengwulao_stc[17409]["StcEvent"],tValentinesDay2015_feichengwulao_stc[17409]["StcType"],"==",0)
end

tNpcGossip[17323]["Text1-2"] = {121}
tNpcGossip[17323]["Text121"] = tValentinesDay2015_feichengwulao_Text[17323]["Text121"]
tNpcGossip[17323]["tOption1-2"] = {2}
tNpcGossip[17323]["Option2"] = tValentinesDay2015_feichengwulao_Text[17323]["Option2"]
tNpcGossip[17323]["ChkFunc1-2"] = function ()
	return Task_ChkStcValue(tValentinesDay2015_feichengwulao_stc[17409]["StcEvent"],tValentinesDay2015_feichengwulao_stc[17409]["StcType"],"==",1)
end

--留声机旁的男NPC
tNpcFace[3381] = 47
tNpcGossip[17324] = tNpcGossip[17324] or DefaultNpc:new{}
tNpcGossip[17324]["OptionHidden"] = 1

tNpcGossip[17324]["Text1-1"] = {111}
tNpcGossip[17324]["Text111"] = tValentinesDay2015_feichengwulao_Text[17324]["Text111"]
tNpcGossip[17324]["tOption1-1"] = {1}
tNpcGossip[17324]["Option1"] = tValentinesDay2015_feichengwulao_Text[17324]["Option1"]
tNpcGossip[17324]["ChkFunc1-1"] = function ()
	return Task_ChkStcValue(tValentinesDay2015_feichengwulao_stc[17409]["StcEvent"],tValentinesDay2015_feichengwulao_stc[17409]["StcType"],"==",0)
end

tNpcGossip[17324]["Text1-2"] = {121}
tNpcGossip[17324]["Text121"] = tValentinesDay2015_feichengwulao_Text[17324]["Text121"]
tNpcGossip[17324]["tOption1-2"] = {2}
tNpcGossip[17324]["Option2"] = tValentinesDay2015_feichengwulao_Text[17324]["Option2"]
tNpcGossip[17324]["ChkFunc1-2"] = function ()
	return Task_ChkStcValue(tValentinesDay2015_feichengwulao_stc[17409]["StcEvent"],tValentinesDay2015_feichengwulao_stc[17409]["StcType"],"==",1)
end

--古筝的女NPC
tNpcFace[3382] = 134
tNpcGossip[17325] = tNpcGossip[17325] or DefaultNpc:new{}
tNpcGossip[17325]["OptionHidden"] = 1

tNpcGossip[17325]["Text1-1"] = {111}
tNpcGossip[17325]["Text111"] = tValentinesDay2015_feichengwulao_Text[17325]["Text111"]
tNpcGossip[17325]["tOption1-1"] = {1}
tNpcGossip[17325]["Option1"] = tValentinesDay2015_feichengwulao_Text[17325]["Option1"]
tNpcGossip[17325]["ChkFunc1-1"] = function ()
	return Task_ChkStcValue(tValentinesDay2015_feichengwulao_stc[17410]["StcEvent"],tValentinesDay2015_feichengwulao_stc[17410]["StcType"],"==",0)
end

tNpcGossip[17325]["Text1-2"] = {121}
tNpcGossip[17325]["Text121"] = tValentinesDay2015_feichengwulao_Text[17325]["Text121"]
tNpcGossip[17325]["tOption1-2"] = {2}
tNpcGossip[17325]["Option2"] = tValentinesDay2015_feichengwulao_Text[17325]["Option2"]
tNpcGossip[17325]["ChkFunc1-2"] = function ()
	return Task_ChkStcValue(tValentinesDay2015_feichengwulao_stc[17410]["StcEvent"],tValentinesDay2015_feichengwulao_stc[17410]["StcType"],"==",1)
end

--古筝的男NPC
tNpcFace[3383] = 81
tNpcGossip[17326] = tNpcGossip[17326] or DefaultNpc:new{}
tNpcGossip[17326]["OptionHidden"] = 1

tNpcGossip[17326]["Text1-1"] = {111}
tNpcGossip[17326]["Text111"] = tValentinesDay2015_feichengwulao_Text[17326]["Text111"]
tNpcGossip[17326]["tOption1-1"] = {1}
tNpcGossip[17326]["Option1"] = tValentinesDay2015_feichengwulao_Text[17326]["Option1"]
tNpcGossip[17326]["ChkFunc1-1"] = function ()
	return Task_ChkStcValue(tValentinesDay2015_feichengwulao_stc[17410]["StcEvent"],tValentinesDay2015_feichengwulao_stc[17410]["StcType"],"==",0)
end

tNpcGossip[17326]["Text1-2"] = {121}
tNpcGossip[17326]["Text121"] = tValentinesDay2015_feichengwulao_Text[17326]["Text121"]
tNpcGossip[17326]["tOption1-2"] = {2}
tNpcGossip[17326]["Option2"] = tValentinesDay2015_feichengwulao_Text[17326]["Option2"]
tNpcGossip[17326]["ChkFunc1-2"] = function ()
	return Task_ChkStcValue(tValentinesDay2015_feichengwulao_stc[17410]["StcEvent"],tValentinesDay2015_feichengwulao_stc[17410]["StcType"],"==",1)
end

--书画案几旁的女NPC
tNpcFace[3384] = 158
tNpcGossip[17327] = tNpcGossip[17327] or DefaultNpc:new{}
tNpcGossip[17327]["OptionHidden"] = 1

tNpcGossip[17327]["Text1-1"] = {111}
tNpcGossip[17327]["Text111"] = tValentinesDay2015_feichengwulao_Text[17327]["Text111"]
tNpcGossip[17327]["tOption1-1"] = {1}
tNpcGossip[17327]["Option1"] = tValentinesDay2015_feichengwulao_Text[17327]["Option1"]
tNpcGossip[17327]["ChkFunc1-1"] = function ()
	return Task_ChkStcValue(tValentinesDay2015_feichengwulao_stc[17411]["StcEvent"],tValentinesDay2015_feichengwulao_stc[17411]["StcType"],"==",0)
end

tNpcGossip[17327]["Text1-2"] = {121}
tNpcGossip[17327]["Text121"] = tValentinesDay2015_feichengwulao_Text[17327]["Text121"]
tNpcGossip[17327]["tOption1-2"] = {2}
tNpcGossip[17327]["Option2"] = tValentinesDay2015_feichengwulao_Text[17327]["Option2"]
tNpcGossip[17327]["ChkFunc1-2"] = function ()
	return Task_ChkStcValue(tValentinesDay2015_feichengwulao_stc[17411]["StcEvent"],tValentinesDay2015_feichengwulao_stc[17411]["StcType"],"==",1)
end

--书画案几旁的男NPC
tNpcFace[3385] = 64
tNpcGossip[17328] = tNpcGossip[17328] or DefaultNpc:new{}
tNpcGossip[17328]["OptionHidden"] = 1

tNpcGossip[17328]["Text1-1"] = {111}
tNpcGossip[17328]["Text111"] = tValentinesDay2015_feichengwulao_Text[17328]["Text111"]
tNpcGossip[17328]["tOption1-1"] = {1}
tNpcGossip[17328]["Option1"] = tValentinesDay2015_feichengwulao_Text[17328]["Option1"]
tNpcGossip[17328]["ChkFunc1-1"] = function ()
	return Task_ChkStcValue(tValentinesDay2015_feichengwulao_stc[17411]["StcEvent"],tValentinesDay2015_feichengwulao_stc[17411]["StcType"],"==",0)
end

tNpcGossip[17328]["Text1-2"] = {121}
tNpcGossip[17328]["Text121"] = tValentinesDay2015_feichengwulao_Text[17328]["Text121"] 
tNpcGossip[17328]["tOption1-2"] = {2}
tNpcGossip[17328]["Option2"] = tValentinesDay2015_feichengwulao_Text[17328]["Option2"]
tNpcGossip[17328]["ChkFunc1-2"] = function ()
	return Task_ChkStcValue(tValentinesDay2015_feichengwulao_stc[17411]["StcEvent"],tValentinesDay2015_feichengwulao_stc[17411]["StcType"],"==",1)
end

--干花罐旁的女NPC
tNpcFace[3386] = 158
tNpcGossip[17329] = tNpcGossip[17329] or DefaultNpc:new{}
tNpcGossip[17329]["OptionHidden"] = 1

tNpcGossip[17329]["Text1-1"] = {111}
tNpcGossip[17329]["Text111"] = tValentinesDay2015_feichengwulao_Text[17329]["Text111"]
tNpcGossip[17329]["tOption1-1"] = {1}
tNpcGossip[17329]["Option1"] = tValentinesDay2015_feichengwulao_Text[17329]["Option1"]
tNpcGossip[17329]["ChkFunc1-1"] = function ()
	return Task_ChkStcValue(tValentinesDay2015_feichengwulao_stc[17412]["StcEvent"],tValentinesDay2015_feichengwulao_stc[17412]["StcType"] ,"==",0)
end

tNpcGossip[17329]["Text1-2"] = {121}
tNpcGossip[17329]["Text121"] = tValentinesDay2015_feichengwulao_Text[17329]["Text121"]
tNpcGossip[17329]["tOption1-2"] = {2}
tNpcGossip[17329]["Option2"] = tValentinesDay2015_feichengwulao_Text[17329]["Option2"]
tNpcGossip[17329]["ChkFunc1-2"] = function ()
	return Task_ChkStcValue(tValentinesDay2015_feichengwulao_stc[17412]["StcEvent"],tValentinesDay2015_feichengwulao_stc[17412]["StcType"] ,"==",1)
end

--干花罐旁的男NPC
tNpcFace[3387] = 56
tNpcGossip[17330] = tNpcGossip[17330] or DefaultNpc:new{}
tNpcGossip[17330]["OptionHidden"] = 1

tNpcGossip[17330]["Text1-1"] = {111}
tNpcGossip[17330]["Text111"] = tValentinesDay2015_feichengwulao_Text[17330]["Text111"]
tNpcGossip[17330]["tOption1-1"] = {1}
tNpcGossip[17330]["Option1"] = tValentinesDay2015_feichengwulao_Text[17330]["Option1"] 
tNpcGossip[17330]["ChkFunc1-1"] = function ()
	return Task_ChkStcValue(tValentinesDay2015_feichengwulao_stc[17412]["StcEvent"],tValentinesDay2015_feichengwulao_stc[17412]["StcType"] ,"==",0)
end

tNpcGossip[17330]["Text1-2"] = {121}
tNpcGossip[17330]["Text121"] = tValentinesDay2015_feichengwulao_Text[17330]["Text121"]
tNpcGossip[17330]["tOption1-2"] = {2}
tNpcGossip[17330]["Option2"] = tValentinesDay2015_feichengwulao_Text[17330]["Option2"]
tNpcGossip[17330]["ChkFunc1-2"] = function ()
	return Task_ChkStcValue(tValentinesDay2015_feichengwulao_stc[17412]["StcEvent"],tValentinesDay2015_feichengwulao_stc[17412]["StcType"] ,"==",1)
end

--蜡烛旁的女NPC
tNpcFace[3388] = 133
tNpcGossip[17331] = tNpcGossip[17331] or DefaultNpc:new{}
tNpcGossip[17331]["OptionHidden"] = 1

tNpcGossip[17331]["Text1-1"] = {111}
tNpcGossip[17331]["Text111"] = tValentinesDay2015_feichengwulao_Text[17331]["Text111"]
tNpcGossip[17331]["tOption1-1"] = {1}
tNpcGossip[17331]["Option1"] = tValentinesDay2015_feichengwulao_Text[17331]["Option1"]
tNpcGossip[17331]["ChkFunc1-1"] = function ()
	return Task_ChkStcValue(tValentinesDay2015_feichengwulao_stc[17413]["StcEvent"],tValentinesDay2015_feichengwulao_stc[17413]["StcType"],"==",0)
end

tNpcGossip[17331]["Text1-2"] = {121}
tNpcGossip[17331]["Text121"] = tValentinesDay2015_feichengwulao_Text[17331]["Text121"] 
tNpcGossip[17331]["tOption1-2"] = {2}
tNpcGossip[17331]["Option2"] = tValentinesDay2015_feichengwulao_Text[17331]["Option2"]
tNpcGossip[17331]["ChkFunc1-2"] = function ()
	return Task_ChkStcValue(tValentinesDay2015_feichengwulao_stc[17413]["StcEvent"],tValentinesDay2015_feichengwulao_stc[17413]["StcType"],"==",1)
end

--蜡烛旁的男NPC
tNpcFace[3389] = 94
tNpcGossip[17332] = tNpcGossip[17332] or DefaultNpc:new{}
tNpcGossip[17332]["OptionHidden"] = 1

tNpcGossip[17332]["Text1-1"] = {111}
tNpcGossip[17332]["Text111"] = tValentinesDay2015_feichengwulao_Text[17332]["Text111"]
tNpcGossip[17332]["tOption1-1"] = {1}
tNpcGossip[17332]["Option1"] = tValentinesDay2015_feichengwulao_Text[17332]["Option1"]
tNpcGossip[17332]["ChkFunc1-1"] = function ()
	return Task_ChkStcValue(tValentinesDay2015_feichengwulao_stc[17413]["StcEvent"],tValentinesDay2015_feichengwulao_stc[17413]["StcType"],"==",0)
end

tNpcGossip[17332]["Text1-2"] = {121}
tNpcGossip[17332]["Text121"] = tValentinesDay2015_feichengwulao_Text[17332]["Text121"]
tNpcGossip[17332]["tOption1-2"] = {2}
tNpcGossip[17332]["Option2"] = tValentinesDay2015_feichengwulao_Text[17332]["Option2"]
tNpcGossip[17332]["ChkFunc1-2"] = function ()
	return Task_ChkStcValue(tValentinesDay2015_feichengwulao_stc[17413]["StcEvent"],tValentinesDay2015_feichengwulao_stc[17413]["StcType"],"==",1)
end

--家具对白
--留声机
tNpcGossip[17409] = tNpcGossip[17409] or DefaultNpc:new{}
tNpcGossip[17409]["OptionHidden"] = 1

tNpcGossip[17409]["Text1-1"] = {111}
tNpcGossip[17409]["Text111"] = tValentinesDay2015_feichengwulao_Text[17409]["Text111"]
tNpcGossip[17409]["tOption1-1"] = {1,2}
tNpcGossip[17409]["Option1"] = tValentinesDay2015_feichengwulao_Text[17409]["Option1"]
tNpcGossip[17409]["Option2"] = tValentinesDay2015_feichengwulao_Text[17409]["Option2"] 
tNpcGossip[17409]["OptionFunc1"]="ValentinesDay2015_feichengwulao_Option1_17409</N>17409"

tNpcGossip[17409]["Text1-2"] = {121}
tNpcGossip[17409]["Text121"] = tValentinesDay2015_feichengwulao_Text[17409]["Text121"] 
tNpcGossip[17409]["tOption1-2"] = {3}
tNpcGossip[17409]["Option3"] = tValentinesDay2015_feichengwulao_Text[17409]["Option3"]

--古筝
tNpcGossip[17410] = tNpcGossip[17410] or DefaultNpc:new{}
tNpcGossip[17410]["OptionHidden"] = 1

tNpcGossip[17410]["Text1-1"] = {111}
tNpcGossip[17410]["Text111"] = tValentinesDay2015_feichengwulao_Text[17410]["Text111"]
tNpcGossip[17410]["tOption1-1"] = {1,2}
tNpcGossip[17410]["Option1"] = tValentinesDay2015_feichengwulao_Text[17410]["Option1"]
tNpcGossip[17410]["Option2"] = tValentinesDay2015_feichengwulao_Text[17410]["Option2"]
tNpcGossip[17410]["OptionFunc1"]="ValentinesDay2015_feichengwulao_Option1_17409</N>17410"

tNpcGossip[17410]["Text1-2"] = {121}
tNpcGossip[17410]["Text121"] = tValentinesDay2015_feichengwulao_Text[17410]["Text121"]
tNpcGossip[17410]["tOption1-2"] = {3}
tNpcGossip[17410]["Option3"] = tValentinesDay2015_feichengwulao_Text[17410]["Option3"]

--书画案几
tNpcGossip[17411] = tNpcGossip[17411] or DefaultNpc:new{}
tNpcGossip[17411]["OptionHidden"] = 1

tNpcGossip[17411]["Text1-1"] = {111}
tNpcGossip[17411]["Text111"] = tValentinesDay2015_feichengwulao_Text[17411]["Text111"]
tNpcGossip[17411]["tOption1-1"] = {1,2}
tNpcGossip[17411]["Option1"] = tValentinesDay2015_feichengwulao_Text[17411]["Option1"]
tNpcGossip[17411]["Option2"] = tValentinesDay2015_feichengwulao_Text[17411]["Option2"]
tNpcGossip[17411]["OptionFunc1"]="ValentinesDay2015_feichengwulao_Option1_17409</N>17411"

tNpcGossip[17411]["Text1-2"] = {121}
tNpcGossip[17411]["Text121"] = tValentinesDay2015_feichengwulao_Text[17411]["Text121"]
tNpcGossip[17411]["tOption1-2"] = {3}
tNpcGossip[17411]["Option3"] = tValentinesDay2015_feichengwulao_Text[17411]["Option3"]

--干花罐
tNpcGossip[17412] = tNpcGossip[17412] or DefaultNpc:new{}
tNpcGossip[17412]["OptionHidden"] = 1

tNpcGossip[17412]["Text1-1"] = {111}
tNpcGossip[17412]["Text111"] = tValentinesDay2015_feichengwulao_Text[17412]["Text111"]
tNpcGossip[17412]["tOption1-1"] = {1,2}
tNpcGossip[17412]["Option1"] = tValentinesDay2015_feichengwulao_Text[17412]["Option1"]
tNpcGossip[17412]["Option2"] = tValentinesDay2015_feichengwulao_Text[17412]["Option2"]
tNpcGossip[17412]["OptionFunc1"]="ValentinesDay2015_feichengwulao_Option1_17409</N>17412"

tNpcGossip[17412]["Text1-2"] = {121}
tNpcGossip[17412]["Text121"] = tValentinesDay2015_feichengwulao_Text[17412]["Text121"]
tNpcGossip[17412]["tOption1-2"] = {3}
tNpcGossip[17412]["Option3"] = tValentinesDay2015_feichengwulao_Text[17412]["Option3"]

--蜡烛
tNpcGossip[17413] = tNpcGossip[17413] or DefaultNpc:new{}
tNpcGossip[17413]["OptionHidden"] = 1

tNpcGossip[17413]["Text1-1"] = {111}
tNpcGossip[17413]["Text111"] = tValentinesDay2015_feichengwulao_Text[17413]["Text111"]
tNpcGossip[17413]["tOption1-1"] = {1,2}
tNpcGossip[17413]["Option1"] = tValentinesDay2015_feichengwulao_Text[17413]["Option1"]
tNpcGossip[17413]["Option2"] = tValentinesDay2015_feichengwulao_Text[17413]["Option2"]
tNpcGossip[17413]["OptionFunc1"]="ValentinesDay2015_feichengwulao_Option1_17409</N>17413"

tNpcGossip[17413]["Text1-2"] = {121}
tNpcGossip[17413]["Text121"] = tValentinesDay2015_feichengwulao_Text[17413]["Text121"] 
tNpcGossip[17413]["tOption1-2"] = {3}
tNpcGossip[17413]["Option3"] = tValentinesDay2015_feichengwulao_Text[17413]["Option3"]

-------------------------------------------------------------------逻辑部分------------------------------------------------------------

--等级判断
function ValentinesDay2015_feichengwulao_level()
	local nMetempsychosis = Get_UserMetempsychosis()
	local nUserLev = Get_UserLevel()
	local bPlayerLev = false
	if nMetempsychosis < tValentinesDay2015_feichengwulao_Cont["Metempsychosis"] then

		if nUserLev < tValentinesDay2015_feichengwulao_Cont["Level"] then
			bPlayerLev = true
		else
			bPlayerLev = false
		end 
	end
	return bPlayerLev
end

--隔天清0
function ValentinesDay2015_feichengwulao_nextday()
	if Task_StcInterval(tValentinesDay2015_feichengwulao_stc[1]["StcEvent"],tValentinesDay2015_feichengwulao_stc[1]["StcType"],1,4) then
		Task_SetStatistic(tValentinesDay2015_feichengwulao_stc[1]["StcEvent"], tValentinesDay2015_feichengwulao_stc[1]["StcType"],0,1,0)
		Task_SetStcTimestamp(tValentinesDay2015_feichengwulao_stc[1]["StcEvent"],tValentinesDay2015_feichengwulao_stc[1]["StcType"],0,0)
--		Task_SetStatistic(tValentinesDay2015_feichengwulao_stc[2]["StcEvent"],tValentinesDay2015_feichengwulao_stc[2]["StcType"],0,1,0)
--		Task_SetStatistic(tValentinesDay2015_feichengwulao_stc[17409]["StcEvent"],tValentinesDay2015_feichengwulao_stc[17409]["StcType"],0,1,0)
--		Task_SetStatistic(tValentinesDay2015_feichengwulao_stc[17410]["StcEvent"],tValentinesDay2015_feichengwulao_stc[17410]["StcType"],0,1,0)
--		Task_SetStatistic(tValentinesDay2015_feichengwulao_stc[17411]["StcEvent"],tValentinesDay2015_feichengwulao_stc[17411]["StcType"],0,1,0)
--		Task_SetStatistic(tValentinesDay2015_feichengwulao_stc[17412]["StcEvent"],tValentinesDay2015_feichengwulao_stc[17412]["StcType"] ,0,1,0)
--		Task_SetStatistic(tValentinesDay2015_feichengwulao_stc[17413]["StcEvent"],tValentinesDay2015_feichengwulao_stc[17413]["StcType"],0,1,0)
	end
end

---17321,'男媒婆姚大痣'
--我要帮忙，带我去后花园！
function ValentinesDay2015_feichengwulao_Option3_17321(nNpcId)
	-- 判断活动时间
	if not Sys_ChkFullTime(tValentinesDay2015_feichengwulao_Cont["Nowtime"]) then
		LinkNpcGossipFunc_New(nNpcId,"1-2")
		return
	end
	
	-- 判断具体活动时间
--	if not Sys_ChkDayTime(tValentinesDay2015_feichengwulao_Cont["Nowdaytime"]) then
--		LinkNpcGossipFunc_New(nNpcId,"3-1")
--		return
--	end
	
	-- 判断玩家等级
	if ValentinesDay2015_feichengwulao_level() then
		LinkNpcGossipFunc_New(nNpcId,"3-2")
		return
	end
	
	--隔天清0操作
	ValentinesDay2015_feichengwulao_nextday()
	
	--判断是否领奖
	if Task_ChkStcValue(tValentinesDay2015_feichengwulao_stc[1]["StcEvent"],tValentinesDay2015_feichengwulao_stc[1]["StcType"],">=",tValentinesDay2015_feichengwulao_stc[1]["Complete"]) then
		LinkNpcGossipFunc_New(nNpcId,"3-3")
		return
	end
	
	--判断是否已完成任务
	if Task_ChkStcValue(tValentinesDay2015_feichengwulao_stc[2]["StcEvent"],tValentinesDay2015_feichengwulao_stc[2]["StcType"],">=",tValentinesDay2015_feichengwulao_stc[2]["Complete"]) then
		LinkNpcGossipFunc_New(nNpcId,"3-4")
		return
	end
	
	-- 打接任务掩码，传送到活动地图
	Task_SetStatistic(tValentinesDay2015_feichengwulao_stc[1]["StcEvent"],tValentinesDay2015_feichengwulao_stc[1]["StcType"],tValentinesDay2015_feichengwulao_stc[1]["New"],1,0)
	Task_SetStcTimestamp(tValentinesDay2015_feichengwulao_stc[1]["StcEvent"],tValentinesDay2015_feichengwulao_stc[1]["StcType"],0,0)
	User_UserRandBoundTrans(tValentinesDay2015_feichengwulao_Cont["MapId"],tValentinesDay2015_feichengwulao_Cont["CellX"],tValentinesDay2015_feichengwulao_Cont["CellY"],tValentinesDay2015_feichengwulao_Cont["BoundCX"],tValentinesDay2015_feichengwulao_Cont["BoundCY"],1,0)
	Sys_MsgBox(tValentinesDay2015_feichengwulao_Text["MsgBox"]["chgmap"])
    Sys_SaveActionFestivalLog(tValentinesDay2015_feichengwulao_Log["New"])
	
end

--领取报酬。
function ValentinesDay2015_feichengwulao_Option4_17321(nNpcId)
	-- 判断活动时间
	if not Sys_ChkFullTime(tValentinesDay2015_feichengwulao_Cont["Nowtime"]) then
		LinkNpcGossipFunc_New(nNpcId,"1-2")
		return
	end
		
	--隔天清0操作
	ValentinesDay2015_feichengwulao_nextday()

	--判断是否领奖
	if Task_ChkStcValue(tValentinesDay2015_feichengwulao_stc[1]["StcEvent"],tValentinesDay2015_feichengwulao_stc[1]["StcType"],">=",tValentinesDay2015_feichengwulao_stc[1]["Complete"]) then
		LinkNpcGossipFunc_New(nNpcId,"4-1")
		return
	end
	
	--判断是否完成任务
	if not Task_ChkStcValue(tValentinesDay2015_feichengwulao_stc[2]["StcEvent"] , tValentinesDay2015_feichengwulao_stc[2]["StcType"],">=",tValentinesDay2015_feichengwulao_stc[2]["Complete"]) then
		LinkNpcGossipFunc_New(nNpcId,"4-2")
		return
	end
	
	-- 判断玩家背包空间
	if not User_CheckLeftSpace(tValentinesDay2015_feichengwulao_Cont["Space"]) then
		LinkNpcGossipFunc_New(nNpcId,"4-3")
		return
	end
	
	--打领奖掩码获得礼包
	Task_SetStatistic(tValentinesDay2015_feichengwulao_stc[1]["StcEvent"],tValentinesDay2015_feichengwulao_stc[1]["StcType"],tValentinesDay2015_feichengwulao_stc[1]["Complete"],1,0)
	Task_SetStcTimestamp(tValentinesDay2015_feichengwulao_stc[1]["StcEvent"],tValentinesDay2015_feichengwulao_stc[1]["StcType"],0,0)
	Task_SetStatistic(tValentinesDay2015_feichengwulao_stc[2]["StcEvent"],tValentinesDay2015_feichengwulao_stc[2]["StcType"],0,1,0)
	Task_SetStatistic(tValentinesDay2015_feichengwulao_stc[17409]["StcEvent"],tValentinesDay2015_feichengwulao_stc[17409]["StcType"],0,1,0)
	Task_SetStatistic(tValentinesDay2015_feichengwulao_stc[17410]["StcEvent"],tValentinesDay2015_feichengwulao_stc[17410]["StcType"],0,1,0)
	Task_SetStatistic(tValentinesDay2015_feichengwulao_stc[17411]["StcEvent"],tValentinesDay2015_feichengwulao_stc[17411]["StcType"],0,1,0)
	Task_SetStatistic(tValentinesDay2015_feichengwulao_stc[17412]["StcEvent"],tValentinesDay2015_feichengwulao_stc[17412]["StcType"] ,0,1,0)
	Task_SetStatistic(tValentinesDay2015_feichengwulao_stc[17413]["StcEvent"],tValentinesDay2015_feichengwulao_stc[17413]["StcType"],0,1,0)
	FestivalGeneralPackage_GetGift(tValentinesDay2015_feichengwulao_Log["FestivalId"],tValentinesDay2015_feichengwulao_Log["LogId"])
	Item_AddItem(tValentinesDay2015_feichengwulao_Cont["RewardItem"])
	Sys_SaveActionFestivalLog(tValentinesDay2015_feichengwulao_Log["RewardLog"])
--	Sys_SaveActionFestivalLog(tValentinesDay2015_feichengwulao_Log["Complete"])
	LinkNpcGossipFunc_New(nNpcId,"4-4")
	
end

--17322,'伙计姚前树'
--请带我离开后花园。
function ValentinesDay2015_feichengwulao_Option1_17322(nNpcId)
   --判断是否完成任务
	if not Task_ChkStcValue(tValentinesDay2015_feichengwulao_stc[2]["StcEvent"] , tValentinesDay2015_feichengwulao_stc[2]["StcType"],">=",tValentinesDay2015_feichengwulao_stc[2]["Complete"]) then
		LinkNpcGossipFunc_New(nNpcId,"1-2")
		return
	end	
	
    ValentinesDay2015_feichengwulao_Option4_17322()
	Sys_MsgBox(tValentinesDay2015_feichengwulao_Text["MsgBox"]["chgmap1"])

end

--离开后花园。
function ValentinesDay2015_feichengwulao_Option4_17322()

	User_UserRandBoundTrans(tValentinesDay2015_feichengwulao_Cont["MapId1"],tValentinesDay2015_feichengwulao_Cont["CellX1"],tValentinesDay2015_feichengwulao_Cont["CellY1"],tValentinesDay2015_feichengwulao_Cont["BoundCX"],tValentinesDay2015_feichengwulao_Cont["BoundCY"],1,0)

end

--家具NPC
function ValentinesDay2015_feichengwulao_Option1_17409(nNpcid)
--	local nNpcid = Get_NpcId()
	local nComplete = tValentinesDay2015_feichengwulao_Log["Complete"]

	if Task_ChkStcValue(tValentinesDay2015_feichengwulao_stc[nNpcid]["StcEvent"],tValentinesDay2015_feichengwulao_stc[nNpcid]["StcType"],">=",tValentinesDay2015_feichengwulao_stc[nNpcid]["Complete"]) then
		Sys_MsgBox(tValentinesDay2015_feichengwulao_Text["MsgBox"]["Complete"])
		return
	else	
	   Task_SetStatistic(tValentinesDay2015_feichengwulao_stc[nNpcid]["StcEvent"],tValentinesDay2015_feichengwulao_stc[nNpcid]["StcType"],tValentinesDay2015_feichengwulao_stc[nNpcid]["Complete"],1,0)
	   Task_AddStatistic(tValentinesDay2015_feichengwulao_stc[2]["StcEvent"],tValentinesDay2015_feichengwulao_stc[2]["StcType"],1,1,0)
	   Sys_SaveActionFestivalLog(nComplete)
	   LinkNpcGossipFunc_New(nNpcid,"1-2")
	end
	
	if Task_ChkStcValue(tValentinesDay2015_feichengwulao_stc[2]["StcEvent"],tValentinesDay2015_feichengwulao_stc[2]["StcType"],"==",tValentinesDay2015_feichengwulao_stc[2]["Complete"]) then
		Sys_MsgBox(tValentinesDay2015_feichengwulao_Text["MsgBox"]["Complete1"],"ValentinesDay2015_feichengwulao_Goto")
	end
   
end

--点确定寻路到传送npc旁边
function ValentinesDay2015_feichengwulao_Goto()

	Sys_GotoSomeWhere(tValentinesDay2015_feichengwulao_npc["CellX"],tValentinesDay2015_feichengwulao_npc["CellY"],tValentinesDay2015_feichengwulao_npc["MapId"],tValentinesDay2015_feichengwulao_npc["NpcId"])
end


--清场
--function ValentinesDay2015_feichengwulao_clear()
	-- 判断活动时间
--	if not Sys_ChkFullTime(tValentinesDay2015_feichengwulao_Cont["Nowtime"]) then
--		return
		
--	elseif	Map_GetUserNum(tValentinesDay2015_feichengwulao_Cont["MapId"],1) >= 1 then
--			Map_SendBroadcastMsg(tValentinesDay2015_feichengwulao_Cont["MapId"],tValentinesDay2015_feichengwulao_Text["MsgBox"]["clear"])
--			Map_UserExeFunc(tValentinesDay2015_feichengwulao_Cont["MapId"],-1,"ValentinesDay2015_feichengwulao_Option4_17322")

--	end
--end


--时间函数触发
--'22:00 22:02'
--tOntimerMin_HM[2300] = tOntimerMin_HM[2300] or {}
--table.insert(tOntimerMin_HM[2300],ValentinesDay2015_feichengwulao_clear)
--tOntimerMin_HM[2301] = tOntimerMin_HM[2301] or {}
--table.insert(tOntimerMin_HM[2301],ValentinesDay2015_feichengwulao_clear)
--tOntimerMin_HM[2302] = tOntimerMin_HM[2302] or {}
--table.insert(tOntimerMin_HM[2302],ValentinesDay2015_feichengwulao_clear)











