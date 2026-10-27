--Name:			[征服][活动脚本]2015年暑期活动无影盗贼团
--Creator: 		魏贻逵
--Created:		2015/05/04
------------------------------------------------------------------------------------
--掩码说明：
--115,18 领取奖励
--115,19 使用面粉让小偷现形的次数
--115,20 找到道具
--
--动态存储表说明：
--50263 无影盗贼团团长出现

-- 活动时间
local tSummeractivities_thief_Cont = {}
tSummeractivities_thief_Cont["Beftime"] = "2015-01-01 00:00 2015-07-08 23:59"
tSummeractivities_thief_Cont["Nowtime"] = "2015-07-09 00:00 2015-07-22 23:59"
tSummeractivities_thief_Cont["Aftime"]  = "2015-07-23 00:00 2020-01-01 23:59"

-- 玩家等级要求
tSummeractivities_thief_Cont["Metempsychosis"] = 1
tSummeractivities_thief_Cont["Level"] = 80
tSummeractivities_thief_Cont["Levellimit"] = 140

--背包空间
tSummeractivities_thief_Cont["Space"] = 1

--相关奖励
tSummeractivities_thief_Cont["AddExpTime"] = 10
tSummeractivities_thief_Cont["AddCultivation"] = 5

--任务物品
tSummeractivities_thief_Cont["Item"] = 3001520
tSummeractivities_thief_Cont["Item1"] = 1090010

--相关地图
tSummeractivities_thief_Cont["Map"] = 1002
tSummeractivities_thief_Cont["Cellx"] = 288
tSummeractivities_thief_Cont["Celly"] = 383
tSummeractivities_thief_Cont["NpcId"] = 10301

--地图怪物数量限制
tSummeractivities_thief_Cont["Limit"] = 9
tSummeractivities_thief_Cont["Limit1"] = 15

--状态配置
tSummeractivities_thief_Cont["Status"] = 55
tSummeractivities_thief_Cont["Status1"] = 57
tSummeractivities_thief_Cont["Power"] = 200
tSummeractivities_thief_Cont["Secs"] = 5
tSummeractivities_thief_Cont["Secs1"] = 10
tSummeractivities_thief_Cont["Times"] = 1
tSummeractivities_thief_Cont["RemainTime"] = 5
tSummeractivities_thief_Cont["RemainTime1"] = 10
tSummeractivities_thief_Cont["EndTime"] = 1
tSummeractivities_thief_Cont["Recordable"] = 1

--团长掉落物品
tSummeractivities_thief_Cont["prize"] = 3003627
tSummeractivities_thief_Cont["Active"] = 1440
tSummeractivities_thief_Cont["Num1"] = 3
tSummeractivities_thief_Cont["Num2"] = 4
tSummeractivities_thief_Cont["Num3"] = 5

--怪物id
local tSummeractivities_thief_monster = {}
tSummeractivities_thief_monster["Id"] = 7239
tSummeractivities_thief_monster["Id1"] = 7240
tSummeractivities_thief_monster["Genid"] = 17457

--掉落物品
local tSummeractivities_thief_Item = {}
tSummeractivities_thief_Item[1] = 3001521
tSummeractivities_thief_Item[2] = 3001522
tSummeractivities_thief_Item[3] = 3001523

--活动掩码
--领奖
local tSummeractivities_thief_stc = {}
tSummeractivities_thief_stc[1] = {} 
tSummeractivities_thief_stc[1]["EventType"] = 115
tSummeractivities_thief_stc[1]["DataType"] = 18
tSummeractivities_thief_stc[1]["Complete"] = 1  

--使用面粉让小偷现形的次数
tSummeractivities_thief_stc[2] = {} 
tSummeractivities_thief_stc[2]["EventType"] = 115
tSummeractivities_thief_stc[2]["DataType"] = 19
tSummeractivities_thief_stc[2]["New"] = 0 
tSummeractivities_thief_stc[2]["Add"] = 1 
tSummeractivities_thief_stc[2]["Complete"] = 5 

--杀怪掉落物品
tSummeractivities_thief_stc[3] = {} 
tSummeractivities_thief_stc[3]["EventType"] = 115
tSummeractivities_thief_stc[3]["DataType"] = 20
tSummeractivities_thief_stc[3]["Item0"] = 0
tSummeractivities_thief_stc[3]["Item1"] = 1 
tSummeractivities_thief_stc[3]["Item2"] = 2 
tSummeractivities_thief_stc[3]["Item3"] = 3 

--动态存储表
local tSummeractivities_thief_dyna = {}
tSummeractivities_thief_dyna["Id"] = 50263
tSummeractivities_thief_dyna["Complete"] = 1

--影子的坐标
local tSummeractivities_thief_npc = {}
tSummeractivities_thief_npc[10302] = {} 
tSummeractivities_thief_npc[10302]["Mapid"] = 1002
tSummeractivities_thief_npc[10302]["Cellx1"] = 242
tSummeractivities_thief_npc[10302]["Celly1"] = 225

tSummeractivities_thief_npc[10302]["Cellx2"] = 280
tSummeractivities_thief_npc[10302]["Celly2"] = 140

tSummeractivities_thief_npc[10302]["Cellx3"] = 321
tSummeractivities_thief_npc[10302]["Celly3"] = 129

tSummeractivities_thief_npc[10303] = {} 
tSummeractivities_thief_npc[10303]["Mapid"] = 1002
tSummeractivities_thief_npc[10303]["Cellx1"] = 265
tSummeractivities_thief_npc[10303]["Celly1"] = 196

tSummeractivities_thief_npc[10303]["Cellx2"] = 352
tSummeractivities_thief_npc[10303]["Celly2"] = 233

tSummeractivities_thief_npc[10303]["Cellx3"] = 261
tSummeractivities_thief_npc[10303]["Celly3"] = 212

tSummeractivities_thief_npc[10304] = {} 
tSummeractivities_thief_npc[10304]["Mapid"] = 1002
tSummeractivities_thief_npc[10304]["Cellx1"] = 344
tSummeractivities_thief_npc[10304]["Celly1"] = 209

tSummeractivities_thief_npc[10304]["Cellx2"] = 352
tSummeractivities_thief_npc[10304]["Celly2"] = 300

tSummeractivities_thief_npc[10304]["Cellx3"] = 248
tSummeractivities_thief_npc[10304]["Celly3"] = 304

tSummeractivities_thief_npc[10305] = {} 
tSummeractivities_thief_npc[10305]["Mapid"] = 1002
tSummeractivities_thief_npc[10305]["Cellx1"] = 265
tSummeractivities_thief_npc[10305]["Celly1"] = 298

tSummeractivities_thief_npc[10305]["Cellx2"] = 266
tSummeractivities_thief_npc[10305]["Celly2"] = 235

tSummeractivities_thief_npc[10305]["Cellx3"] = 338
tSummeractivities_thief_npc[10305]["Celly3"] = 182

tSummeractivities_thief_npc[10306] = {} 
tSummeractivities_thief_npc[10306]["Mapid"] = 1002
tSummeractivities_thief_npc[10306]["Cellx1"] = 272
tSummeractivities_thief_npc[10306]["Celly1"] = 188

tSummeractivities_thief_npc[10306]["Cellx2"] = 280
tSummeractivities_thief_npc[10306]["Celly2"] = 158

tSummeractivities_thief_npc[10306]["Cellx3"] = 319
tSummeractivities_thief_npc[10306]["Celly3"] = 154

tSummeractivities_thief_npc[10307] = {} 
tSummeractivities_thief_npc[10307]["Mapid"] = 1011
tSummeractivities_thief_npc[10307]["Cellx1"] = 184
tSummeractivities_thief_npc[10307]["Celly1"] = 266

tSummeractivities_thief_npc[10307]["Cellx2"] = 169
tSummeractivities_thief_npc[10307]["Celly2"] = 270

tSummeractivities_thief_npc[10307]["Cellx3"] = 165
tSummeractivities_thief_npc[10307]["Celly3"] = 251

tSummeractivities_thief_npc[10308] = {} 
tSummeractivities_thief_npc[10308]["Mapid"] = 1011
tSummeractivities_thief_npc[10308]["Cellx1"] = 153
tSummeractivities_thief_npc[10308]["Celly1"] = 244

tSummeractivities_thief_npc[10308]["Cellx2"] = 181
tSummeractivities_thief_npc[10308]["Celly2"] = 246

tSummeractivities_thief_npc[10308]["Cellx3"] = 205
tSummeractivities_thief_npc[10308]["Celly3"] = 259

tSummeractivities_thief_npc[10309] = {} 
tSummeractivities_thief_npc[10309]["Mapid"] = 1011
tSummeractivities_thief_npc[10309]["Cellx1"] = 229
tSummeractivities_thief_npc[10309]["Celly1"] = 263

tSummeractivities_thief_npc[10309]["Cellx2"] = 236
tSummeractivities_thief_npc[10309]["Celly2"] = 283

tSummeractivities_thief_npc[10309]["Cellx3"] = 217
tSummeractivities_thief_npc[10309]["Celly3"] = 210

tSummeractivities_thief_npc[10310] = {} 
tSummeractivities_thief_npc[10310]["Mapid"] = 1020
tSummeractivities_thief_npc[10310]["Cellx1"] = 553
tSummeractivities_thief_npc[10310]["Celly1"] = 563

tSummeractivities_thief_npc[10310]["Cellx2"] = 554
tSummeractivities_thief_npc[10310]["Celly2"] = 582

tSummeractivities_thief_npc[10310]["Cellx3"] = 541
tSummeractivities_thief_npc[10310]["Celly3"] = 596

tSummeractivities_thief_npc[10311] = {} 
tSummeractivities_thief_npc[10311]["Mapid"] = 1020
tSummeractivities_thief_npc[10311]["Cellx1"] = 555
tSummeractivities_thief_npc[10311]["Celly1"] = 601

tSummeractivities_thief_npc[10311]["Cellx2"] = 578
tSummeractivities_thief_npc[10311]["Celly2"] = 598

tSummeractivities_thief_npc[10311]["Cellx3"] = 578
tSummeractivities_thief_npc[10311]["Celly3"] = 569

tSummeractivities_thief_npc[10312] = {} 
tSummeractivities_thief_npc[10312]["Mapid"] = 1020
tSummeractivities_thief_npc[10312]["Cellx1"] = 570
tSummeractivities_thief_npc[10312]["Celly1"] = 545

tSummeractivities_thief_npc[10312]["Cellx2"] = 552
tSummeractivities_thief_npc[10312]["Celly2"] = 530

tSummeractivities_thief_npc[10312]["Cellx3"] = 544
tSummeractivities_thief_npc[10312]["Celly3"] = 511

tSummeractivities_thief_npc[10313] = {} 
tSummeractivities_thief_npc[10313]["Mapid"] = 1000
tSummeractivities_thief_npc[10313]["Cellx1"] = 471
tSummeractivities_thief_npc[10313]["Celly1"] = 654

tSummeractivities_thief_npc[10313]["Cellx2"] = 472
tSummeractivities_thief_npc[10313]["Celly2"] = 676

tSummeractivities_thief_npc[10313]["Cellx3"] = 508
tSummeractivities_thief_npc[10313]["Celly3"] = 667

tSummeractivities_thief_npc[10314] = {} 
tSummeractivities_thief_npc[10314]["Mapid"] = 1000
tSummeractivities_thief_npc[10314]["Cellx1"] = 502
tSummeractivities_thief_npc[10314]["Celly1"] = 640

tSummeractivities_thief_npc[10314]["Cellx2"] = 520
tSummeractivities_thief_npc[10314]["Celly2"] = 629

tSummeractivities_thief_npc[10314]["Cellx3"] = 498
tSummeractivities_thief_npc[10314]["Celly3"] = 603

tSummeractivities_thief_npc[10315] = {} 
tSummeractivities_thief_npc[10315]["Mapid"] = 1000
tSummeractivities_thief_npc[10315]["Cellx1"] = 472
tSummeractivities_thief_npc[10315]["Celly1"] = 591

tSummeractivities_thief_npc[10315]["Cellx2"] = 488
tSummeractivities_thief_npc[10315]["Celly2"] = 578

tSummeractivities_thief_npc[10315]["Cellx3"] = 502
tSummeractivities_thief_npc[10315]["Celly3"] = 576

tSummeractivities_thief_npc[10316] = {} 
tSummeractivities_thief_npc[10316]["Mapid"] = 1015
tSummeractivities_thief_npc[10316]["Cellx1"] = 717
tSummeractivities_thief_npc[10316]["Celly1"] = 567

tSummeractivities_thief_npc[10316]["Cellx2"] = 728
tSummeractivities_thief_npc[10316]["Celly2"] = 549

tSummeractivities_thief_npc[10316]["Cellx3"] = 700
tSummeractivities_thief_npc[10316]["Celly3"] = 548

tSummeractivities_thief_npc[10317] = {} 
tSummeractivities_thief_npc[10317]["Mapid"] = 1015
tSummeractivities_thief_npc[10317]["Cellx1"] = 687
tSummeractivities_thief_npc[10317]["Celly1"] = 558

tSummeractivities_thief_npc[10317]["Cellx2"] = 696
tSummeractivities_thief_npc[10317]["Celly2"] = 583

tSummeractivities_thief_npc[10317]["Cellx3"] = 718
tSummeractivities_thief_npc[10317]["Celly3"] = 600

tSummeractivities_thief_npc[10318] = {} 
tSummeractivities_thief_npc[10318]["Mapid"] = 1015
tSummeractivities_thief_npc[10318]["Cellx1"] = 706
tSummeractivities_thief_npc[10318]["Celly1"] = 520

tSummeractivities_thief_npc[10318]["Cellx2"] = 744
tSummeractivities_thief_npc[10318]["Celly2"] = 519

tSummeractivities_thief_npc[10318]["Cellx3"] = 760
tSummeractivities_thief_npc[10318]["Celly3"] = 547

--相关log
local tSummeractivities_thief_log = {}
tSummeractivities_thief_log["New"] = "0,0,0,0,10001937,2,3001520,1" --领面粉
tSummeractivities_thief_log["Complete"] = "0,0,0,0,10001937,1,0,0" --使用面粉
tSummeractivities_thief_log["Dropitem1"] = "0,0,0,0,10001937,2,3001521,1" --获得手帕
tSummeractivities_thief_log["Dropitem2"] = "0,0,0,0,10001937,2,3001522,1" --获得袜子
tSummeractivities_thief_log["Dropitem3"] = "0,0,0,0,10001937,2,3001523,1" --获得裤子
tSummeractivities_thief_log["Dropitem4"] = "0,0,0,0,10001937,2,3003627,3" --杀团长获得3个礼包
tSummeractivities_thief_log["Dropitem5"] = "0,0,0,0,10001937,2,3003627,4" --杀团长获得4个礼包
tSummeractivities_thief_log["Dropitem6"] = "0,0,0,0,10001937,2,3003627,5" --杀团长获得5个礼包

--tSummeractivities_thief_log["RewardLog"] = "0,0,0,0,10001937,2,3001526,1" --获得礼包奖励
tSummeractivities_thief_log["LogId"] = 10001937
tSummeractivities_thief_log["FestivalId"] = 3432

-------------------------------------------------------------------逻辑部分------------------------------------------------------------
--常用逻辑
--等级判断
function Summeractivities_thief_level()
	local nMetempsychosis = Get_UserMetempsychosis()
	local nUserLev = Get_UserLevel()
	local bPlayerLev = false
	if nMetempsychosis < tSummeractivities_thief_Cont["Metempsychosis"] then
		if nUserLev < tSummeractivities_thief_Cont["Level"] then
			bPlayerLev = true
		else
			bPlayerLev = false
		end 
	end
	return bPlayerLev
end

--隔天清领奖掩码
function Summeractivities_thief_nextday()
	if Task_StcInterval(tSummeractivities_thief_stc[1]["EventType"],tSummeractivities_thief_stc[1]["DataType"],1,4) then
		Task_SetStatistic(tSummeractivities_thief_stc[1]["EventType"], tSummeractivities_thief_stc[1]["DataType"],0,1,0)
		Task_SetStcTimestamp(tSummeractivities_thief_stc[1]["EventType"],tSummeractivities_thief_stc[1]["DataType"],0,0)
	end
		
end

--缉盗总兵钱形
--领取面粉。
function Summeractivities_thief_Option3_10301(nNpcId)
--判断活动时间
	if not Sys_ChkFullTime(tSummeractivities_thief_Cont["Nowtime"]) then
		LinkNpcGossipFunc_New(nNpcId,"1-2")
		return
	end

--判断玩家等级
	if Summeractivities_thief_level() then
		LinkNpcGossipFunc_New(nNpcId,"4-1")
		return
	end	
	
--判断是否有面粉	
	if Item_ChkItem(tSummeractivities_thief_Cont["Item"]) then
		LinkNpcGossipFunc_New(nNpcId,"4-2")
		return		
	end
				
--判断背包空间
	if not User_CheckLeftSpace(tSummeractivities_thief_Cont["Space"]) then		
		LinkNpcGossipFunc_New(nNpcId,"4-3")
		return		
	end		
			
	Item_AddItem(tSummeractivities_thief_Cont["Item"])	
	Sys_SaveActionFestivalLog(tSummeractivities_thief_log["New"])
	LinkNpcGossipFunc_New(nNpcId,"4-4")
							
end

--领取缉盗悬赏。
function Summeractivities_thief_Option4_10301(nNpcId)
	local nMetempsychosis = Get_UserMetempsychosis()
--判断活动时间
	if not Sys_ChkFullTime(tSummeractivities_thief_Cont["Nowtime"]) then
		LinkNpcGossipFunc_New(nNpcId,"1-2")
		return
	end

--隔天清领奖掩码
	Summeractivities_thief_nextday()

--已领奖	
	if Task_ChkStcValue(tSummeractivities_thief_stc[1]["EventType"],tSummeractivities_thief_stc[1]["DataType"],">=",tSummeractivities_thief_stc[1]["Complete"]) then
		LinkNpcGossipFunc_New(nNpcId,"5-1")	
		return
	end	
	
--还没完成任务
	if not Task_ChkStcValue(tSummeractivities_thief_stc[2]["EventType"],tSummeractivities_thief_stc[2]["DataType"],">=",tSummeractivities_thief_stc[2]["Complete"]) then
		LinkNpcGossipFunc_New(nNpcId,"5-2")	
		return
	end	
	
--背包空间
	if not User_CheckLeftSpace(tSummeractivities_thief_Cont["Space"]) then		
		LinkNpcGossipFunc_New(nNpcId,"4-3")
		return		
	end	  

--领奖
	Task_SetStatistic(tSummeractivities_thief_stc[1]["EventType"], tSummeractivities_thief_stc[1]["DataType"],tSummeractivities_thief_stc[1]["Complete"],1,0)						
	Task_SetStcTimestamp(tSummeractivities_thief_stc[1]["EventType"],tSummeractivities_thief_stc[1]["DataType"],0,0)	
	Task_SetStatistic(tSummeractivities_thief_stc[2]["EventType"], tSummeractivities_thief_stc[2]["DataType"],tSummeractivities_thief_stc[2]["New"],1,0)	
	FestivalGeneralPackage_GetGift(tSummeractivities_thief_log["FestivalId"],tSummeractivities_thief_log["LogId"])
--	User_TalkChannel2005(tSummeractivities_thief_Text["Reward"])	
--	Sys_SaveActionFestivalLog(tSummeractivities_thief_log["RewardLog"])
	
end

--归还缴获的赃物。
function Summeractivities_thief_Option5_10301(nNpcId)
--判断活动时间
	if not Sys_ChkFullTime(tSummeractivities_thief_Cont["Nowtime"]) then
		LinkNpcGossipFunc_New(nNpcId,"1-2")
		return
	end
	
	local nUserLev = Get_UserLevel()
	for i = 1,3 do
		if Item_ChkItem(tSummeractivities_thief_Item[i]) then
			Item_DelItem(tSummeractivities_thief_Item[i])				
			User_EffectAdd("self","angelwing")			
			if	nUserLev < tSummeractivities_thief_Cont["Levellimit"] then			
				User_AddExpTime(tSummeractivities_thief_Cont["AddExpTime"])
				LinkNpcGossipFunc_New(nNpcId,"6-1")
			else	
				User_AddCultivation(tSummeractivities_thief_Cont["AddCultivation"])
				LinkNpcGossipFunc_New(nNpcId,"6-2")				
			end	 
			
			if	i == 1 then			
				User_EffectDel("self","flying")				
			end  
			return
			
		end 
	end	
	LinkNpcGossipFunc_New(nNpcId,"6-3")	
		
end	

--奇怪的影子
function Summeractivities_thief_shadow(nNpcid,nNpc_m,nNpc_x,nNpc_y,SysDynaGlobalData1)
	local nNpcid = Get_NpcId()
	local nNpc_m = Get_NpcMapID()
	local nNpc_x = Get_NpcPositionX()
	local nNpc_y = Get_NpcPositionY()
	local SysDynaGlobalData1 = Get_SysDynaGlobalData1(tSummeractivities_thief_dyna["Id"])
--判断活动时间
	if not Sys_ChkFullTime(tSummeractivities_thief_Cont["Nowtime"]) then
		return
	end
	
	if not Item_ChkItem(tSummeractivities_thief_Cont["Item"]) then
		   Summeractivities_thief_lose(nNpcid,nNpc_m,nNpc_x,nNpc_y,SysDynaGlobalData1)
		   		
	else	
		User_SetExplore(2,tSummeractivities_thief_Text["Throw"],905,"Summeractivities_thief_success</N>"..nNpcid.."</N>"..nNpc_m.."</N>"..nNpc_x.."</N>"..nNpc_y.."</N>"..SysDynaGlobalData1,"Summeractivities_thief_lose</N>"..nNpcid.."</N>"..nNpc_m.."</N>"..nNpc_x.."</N>"..nNpc_y.."</N>"..SysDynaGlobalData1)
	
			
	end
	
end	


--影子移动
function Summeractivities_thief_move(nNpcid,nNpc_m,nNpc_x,nNpc_y,SysDynaGlobalData1)
	if nNpc_m == tSummeractivities_thief_npc[nNpcid]["Mapid"] and nNpc_x == tSummeractivities_thief_npc[nNpcid]["Cellx1"] and nNpc_y == tSummeractivities_thief_npc[nNpcid]["Celly1"] then
		if Sys_Random(1,2) then
			Npc_MoveNpcPos(nNpcid,tSummeractivities_thief_npc[nNpcid]["Mapid"],tSummeractivities_thief_npc[nNpcid]["Cellx2"],tSummeractivities_thief_npc[nNpcid]["Celly2"])				
		else
			Npc_MoveNpcPos(nNpcid,tSummeractivities_thief_npc[nNpcid]["Mapid"],tSummeractivities_thief_npc[nNpcid]["Cellx3"],tSummeractivities_thief_npc[nNpcid]["Celly3"])	
		end
			return
	end	
			
	if nNpc_m == tSummeractivities_thief_npc[nNpcid]["Mapid"] and nNpc_x == tSummeractivities_thief_npc[nNpcid]["Cellx2"] and nNpc_y == tSummeractivities_thief_npc[nNpcid]["Celly2"] then
		if Sys_Random(1,2) then
			Npc_MoveNpcPos(nNpcid,tSummeractivities_thief_npc[nNpcid]["Mapid"],tSummeractivities_thief_npc[nNpcid]["Cellx1"],tSummeractivities_thief_npc[nNpcid]["Celly1"])				
		else
			Npc_MoveNpcPos(nNpcid,tSummeractivities_thief_npc[nNpcid]["Mapid"],tSummeractivities_thief_npc[nNpcid]["Cellx3"],tSummeractivities_thief_npc[nNpcid]["Celly3"])			
		end
			return
	end	
		
	if nNpc_m == tSummeractivities_thief_npc[nNpcid]["Mapid"] and nNpc_x == tSummeractivities_thief_npc[nNpcid]["Cellx3"] and nNpc_y == tSummeractivities_thief_npc[nNpcid]["Celly3"] then
		if Sys_Random(1,2) then
			Npc_MoveNpcPos(nNpcid,tSummeractivities_thief_npc[nNpcid]["Mapid"],tSummeractivities_thief_npc[nNpcid]["Cellx1"],tSummeractivities_thief_npc[nNpcid]["Celly1"])				
		else
			Npc_MoveNpcPos(nNpcid,tSummeractivities_thief_npc[nNpcid]["Mapid"],tSummeractivities_thief_npc[nNpcid]["Cellx2"],tSummeractivities_thief_npc[nNpcid]["Celly2"])			
		end		
			
	end	
end	

--影子随机对话
function Summeractivities_thief_talk()
	if Sys_Random(1,3) then
		Sys_DialogText(tSummeractivities_thief_Text["Text1"])
		Sys_DialogOption(tSummeractivities_thief_Text["Option1"],"</F>NULL")
		Sys_DialogOption(tSummeractivities_thief_Text["Option4"],"</F>Summeractivities_thief_talk1")
		Sys_DialogEnd()
			return
		end		
		
	if Sys_Random(1,2) then
		Sys_DialogText(tSummeractivities_thief_Text["Text2"])
		Sys_DialogOption(tSummeractivities_thief_Text["Option2"],"</F>NULL")
		Sys_DialogOption(tSummeractivities_thief_Text["Option4"],"</F>Summeractivities_thief_talk1")
		Sys_DialogEnd()
			
	else	
		Sys_DialogText(tSummeractivities_thief_Text["Text3"])
		Sys_DialogOption(tSummeractivities_thief_Text["Option3"],"</F>NULL")
		Sys_DialogOption(tSummeractivities_thief_Text["Option4"],"</F>Summeractivities_thief_talk1")
		Sys_DialogEnd()					
	end	

end

function Summeractivities_thief_talk1()

Sys_GotoSomeWhere(tSummeractivities_thief_Cont["Cellx"],tSummeractivities_thief_Cont["Celly"],tSummeractivities_thief_Cont["Map"],tSummeractivities_thief_Cont["NpcId"])

end

--读条失败
function Summeractivities_thief_lose(nNpcid,nNpc_m,nNpc_x,nNpc_y,SysDynaGlobalData1)
	Summeractivities_thief_move(nNpcid,nNpc_m,nNpc_x,nNpc_y,SysDynaGlobalData1)		
	Map_DropMultiItems(nNpc_m,tSummeractivities_thief_Cont["Item1"],nNpc_x,nNpc_y,1,1,1,30)	
	User_TalkChannel2005(tSummeractivities_thief_Text["Drop"])	
	Summeractivities_thief_talk()

end

--刷普通盗贼
function Summeractivities_thief_AddMonster(nNpcid,nNpc_m,nNpc_x,nNpc_y,SysDynaGlobalData1)
	if nNpc_m == tSummeractivities_thief_Cont["Map"] then	
		if Monster_GetMonsterByName(nNpc_m,tSummeractivities_thief_Text["Monster"]) > tSummeractivities_thief_Cont["Limit1"] then
				Monster_DelMonster(nNpc_m,tSummeractivities_thief_monster["Id1"])
		end			
	else
		if Monster_GetMonsterByName(nNpc_m,tSummeractivities_thief_Text["Monster"]) > tSummeractivities_thief_Cont["Limit"] then
				Monster_DelMonster(nNpc_m,tSummeractivities_thief_monster["Id1"])
		end	
	end					
		Monster_AddMonster(nNpc_m,nNpc_x,nNpc_y,tSummeractivities_thief_monster["Genid"],tSummeractivities_thief_monster["Id1"])
		User_TalkChannel2005(tSummeractivities_thief_Text["Grow"])
		
end


--读条成功
function Summeractivities_thief_success(nNpcid,nNpc_m,nNpc_x,nNpc_y,SysDynaGlobalData1)
	Summeractivities_thief_move(nNpcid,nNpc_m,nNpc_x,nNpc_y,SysDynaGlobalData1)
	Map_Effect(nNpc_m,nNpc_x,nNpc_y,"zf2-e185")
	Task_AddStatistic(tSummeractivities_thief_stc[2]["EventType"],tSummeractivities_thief_stc[2]["DataType"],tSummeractivities_thief_stc[2]["Add"],1,0)
	Sys_SaveActionFestivalLog(tSummeractivities_thief_log["Complete"])

	if Task_ChkStcValue(tSummeractivities_thief_stc[2]["EventType"],tSummeractivities_thief_stc[2]["DataType"],"==",tSummeractivities_thief_stc[2]["Complete"]) then
		User_TalkChannel2005(tSummeractivities_thief_Text["Complete"])	
	end
	
	if Sys_Random(99,100) then
		Summeractivities_thief_AddMonster(nNpcid,nNpc_m,nNpc_x,nNpc_y,SysDynaGlobalData1)
		
	else	
		if SysDynaGlobalData1 >= tSummeractivities_thief_dyna["Complete"] then
			Summeractivities_thief_AddMonster(nNpcid,nNpc_m,nNpc_x,nNpc_y,SysDynaGlobalData1)		
		else
			Sys_SetSynaGlobalData1(tSummeractivities_thief_dyna["Id"],tSummeractivities_thief_dyna["Complete"])
			Monster_AddMonster(nNpc_m,nNpc_x,nNpc_y,tSummeractivities_thief_monster["Genid"],tSummeractivities_thief_monster["Id"])
			User_TalkChannel2005(tSummeractivities_thief_Text["Grow1"])
			
		end	
	
	end
		
end

--普通盗贼掉落
function Summeractivities_thief_drop()
--背包空间判断
--	if not User_CheckLeftSpace(tSummeractivities_thief_Cont["Space"]) then		
--		User_TalkChannel2005(tSummeractivities_thief_Text["Full"])
--		return		
--	end	  
--清掉落掩码
	if Task_StcInterval(tSummeractivities_thief_stc[3]["EventType"],tSummeractivities_thief_stc[3]["DataType"],1,4) then
		Task_SetStatistic(tSummeractivities_thief_stc[3]["EventType"], tSummeractivities_thief_stc[3]["DataType"],0,1,0)
		Task_SetStcTimestamp(tSummeractivities_thief_stc[3]["EventType"],tSummeractivities_thief_stc[3]["DataType"],0,0)
	end	
--70%概率掉落
	if Sys_Random(70,100) then
		local nStc = Get_UserStatisticValue(tSummeractivities_thief_stc[3]["EventType"], tSummeractivities_thief_stc[3]["DataType"])
		if nStc == tSummeractivities_thief_stc[3]["Item0"] then 
			Summeractivities_thief_dropitem1()	
		end
				
		if nStc == tSummeractivities_thief_stc[3]["Item1"] then 
			Summeractivities_thief_dropitem2()	
		end				
				
		if nStc == tSummeractivities_thief_stc[3]["Item2"] then 
			Summeractivities_thief_dropitem3()	
		end		

	end
		
end	


--掉手帕
function Summeractivities_thief_dropitem1()
	Task_SetStatistic(tSummeractivities_thief_stc[3]["EventType"],tSummeractivities_thief_stc[3]["DataType"],tSummeractivities_thief_stc[3]["Item1"],1,0)
	Task_SetStcTimestamp(tSummeractivities_thief_stc[3]["EventType"],tSummeractivities_thief_stc[3]["DataType"],0,0)	
	Item_AddItem(tSummeractivities_thief_Item[1])	
	User_EffectAdd("self","flying")
	User_TalkChannel2005(tSummeractivities_thief_Text["Item1"])
	Sys_SaveActionFestivalLog(tSummeractivities_thief_log["Dropitem1"])
	
end

--掉袜子
function Summeractivities_thief_dropitem2()
	local nUserId = Get_UserId()
	Task_SetStatistic(tSummeractivities_thief_stc[3]["EventType"],tSummeractivities_thief_stc[3]["DataType"],tSummeractivities_thief_stc[3]["Item2"],1,0)
	Task_SetStcTimestamp(tSummeractivities_thief_stc[3]["EventType"],tSummeractivities_thief_stc[3]["DataType"],0,0)	
	Item_AddItem(tSummeractivities_thief_Item[2])	
	User_TalkChannel2005(tSummeractivities_thief_Text["Item2"])
	User_AddRoleStatus(tSummeractivities_thief_Cont["Status"],tSummeractivities_thief_Cont["Power"],tSummeractivities_thief_Cont["Secs"],tSummeractivities_thief_Cont["Times"],tSummeractivities_thief_Cont["RemainTime"],tSummeractivities_thief_Cont["EndTime"],tSummeractivities_thief_Cont["Recordable"],0,0,nUserId)
	Sys_SaveActionFestivalLog(tSummeractivities_thief_log["Dropitem2"])
	
end


--掉裤子
function Summeractivities_thief_dropitem3()
	local nUserId = Get_UserId()
	Task_SetStatistic(tSummeractivities_thief_stc[3]["EventType"],tSummeractivities_thief_stc[3]["DataType"],tSummeractivities_thief_stc[3]["Item3"],1,0)
	Task_SetStcTimestamp(tSummeractivities_thief_stc[3]["EventType"],tSummeractivities_thief_stc[3]["DataType"],0,0)	
	Item_AddItem(tSummeractivities_thief_Item[3])	
	User_TalkChannel2005(tSummeractivities_thief_Text["Item3"])	
	User_AddRoleStatus(tSummeractivities_thief_Cont["Status1"],tSummeractivities_thief_Cont["Power"],tSummeractivities_thief_Cont["Secs1"],tSummeractivities_thief_Cont["Times"],tSummeractivities_thief_Cont["RemainTime1"],tSummeractivities_thief_Cont["EndTime"],tSummeractivities_thief_Cont["Recordable"],0,0,nUserId)
	Sys_SaveActionFestivalLog(tSummeractivities_thief_log["Dropitem3"])	
	
end

--团长掉落
function Summeractivities_thief_drop1()
	if Sys_Random(50,100) then
		Item_AddItem(tSummeractivities_thief_Cont["prize"],0,tSummeractivities_thief_Cont["Num1"],0,tSummeractivities_thief_Cont["Active"],1)
		Sys_SaveActionFestivalLog(tSummeractivities_thief_log["Dropitem4"])
		User_TalkChannel2005(tSummeractivities_thief_Text["Drop1"])
			return Summeractivities_thief_drop()
		end	

	if Sys_Random(35,50) then
		Item_AddItem(tSummeractivities_thief_Cont["prize"],0,tSummeractivities_thief_Cont["Num2"],0,tSummeractivities_thief_Cont["Active"],1)
		Sys_SaveActionFestivalLog(tSummeractivities_thief_log["Dropitem5"])
		User_TalkChannel2005(tSummeractivities_thief_Text["Drop1"])
			return Summeractivities_thief_drop()
	else
		Item_AddItem(tSummeractivities_thief_Cont["prize"],0,tSummeractivities_thief_Cont["Num3"],0,tSummeractivities_thief_Cont["Active"],1)
		Sys_SaveActionFestivalLog(tSummeractivities_thief_log["Dropitem6"])
		User_TalkChannel2005(tSummeractivities_thief_Text["Drop1"])
		return Summeractivities_thief_drop()

	end

end

--清动态存储表
function Summeractivities_thief_clearsysdyna()
	if	Sys_ChkFullTime(tSummeractivities_thief_Cont["Nowtime"]) then
		Sys_ResetAllSynaGlobalData(tSummeractivities_thief_dyna["Id"])			
		
	end	
end

--200W
-- tOntimerMin_HM[0000] = tOntimerMin_HM[0000] or {}
-- table.insert(tOntimerMin_HM[0000],Summeractivities_thief_clearsysdyna)

---------------------------------------------------对话模板部分-----------------------------------------
--缉盗总兵钱形
tNpcFace[2502] = 37
tNpcGossip[10301] = tNpcGossip[10301] or DefaultNpc:new{}
tNpcGossip[10301]["OptionHidden"] = 1

-- 活动前
tNpcGossip[10301]["Text1-1"] = {111,112}
tNpcGossip[10301]["Text111"] = tSummeractivities_thief_Text[10301]["Text111"]
tNpcGossip[10301]["Text112"] = tSummeractivities_thief_Text[10301]["Text112"]
tNpcGossip[10301]["tOption1-1"] = {1}
tNpcGossip[10301]["Option1"] = tSummeractivities_thief_Text[10301]["Option1"]
tNpcGossip[10301]["ChkFunc1-1"] = function ()
	return Sys_ChkFullTime(tSummeractivities_thief_Cont["Beftime"])
end

-- 活动后
tNpcGossip[10301]["Text1-2"] = {121}
tNpcGossip[10301]["Text121"] = tSummeractivities_thief_Text[10301]["Text121"]
tNpcGossip[10301]["tOption1-2"] = {1}
tNpcGossip[10301]["Option2"] = tSummeractivities_thief_Text[10301]["Option2"]
tNpcGossip[10301]["ChkFunc1-2"] = function ()
	return Sys_ChkFullTime(tSummeractivities_thief_Cont["Aftime"])
end

-- 活动中
tNpcGossip[10301]["Text1-3"] = {131,132}
tNpcGossip[10301]["Text131"] = tSummeractivities_thief_Text[10301]["Text131"]
tNpcGossip[10301]["Text132"] = tSummeractivities_thief_Text[10301]["Text132"] 
tNpcGossip[10301]["tOption1-3"] = {3,4,5,6}
tNpcGossip[10301]["Option3"] = tSummeractivities_thief_Text[10301]["Option3"]
tNpcGossip[10301]["Option4"] = tSummeractivities_thief_Text[10301]["Option4"]
tNpcGossip[10301]["Option5"] = tSummeractivities_thief_Text[10301]["Option5"]
tNpcGossip[10301]["Option6"] = tSummeractivities_thief_Text[10301]["Option6"]
tNpcGossip[10301]["ChkFunc1-3"] = function ()
	return Sys_ChkFullTime(tSummeractivities_thief_Cont["Nowtime"])
end

tNpcGossip[10301]["OptionFunc3"]="Summeractivities_thief_Option3_10301</N>10301"
tNpcGossip[10301]["OptionFunc4"]="Summeractivities_thief_Option4_10301</N>10301"
tNpcGossip[10301]["OptionFunc5"]="Summeractivities_thief_Option5_10301</N>10301"
tNpcGossip[10301]["OptionPoint6"]="2"

tNpcGossip[10301]["Text2-1"] = {211,212}
tNpcGossip[10301]["Text211"] = tSummeractivities_thief_Text[10301]["Text211"]
tNpcGossip[10301]["Text212"] = tSummeractivities_thief_Text[10301]["Text212"]
tNpcGossip[10301]["tOption2-1"] = {7,8}
tNpcGossip[10301]["Option7"] = tSummeractivities_thief_Text[10301]["Option7"]
tNpcGossip[10301]["Option8"] = tSummeractivities_thief_Text[10301]["Option8"]
tNpcGossip[10301]["OptionPoint7"]="3"

tNpcGossip[10301]["Text3-1"] = {311,312}
tNpcGossip[10301]["Text311"] = tSummeractivities_thief_Text[10301]["Text311"]
tNpcGossip[10301]["Text312"] = tSummeractivities_thief_Text[10301]["Text312"]
tNpcGossip[10301]["tOption3-1"] = {9}
tNpcGossip[10301]["Option9"] = tSummeractivities_thief_Text[10301]["Option9"]

tNpcGossip[10301]["Text4-1"] = {411}
tNpcGossip[10301]["Text411"] = tSummeractivities_thief_Text[10301]["Text411"]
tNpcGossip[10301]["tOption4-1"] = {10}
tNpcGossip[10301]["Option10"] = tSummeractivities_thief_Text[10301]["Option10"]

tNpcGossip[10301]["Text4-2"] = {421}
tNpcGossip[10301]["Text421"] = tSummeractivities_thief_Text[10301]["Text421"]
tNpcGossip[10301]["tOption4-2"] = {11}
tNpcGossip[10301]["Option11"] = tSummeractivities_thief_Text[10301]["Option11"]

tNpcGossip[10301]["Text4-3"] = {431}
tNpcGossip[10301]["Text431"] = tSummeractivities_thief_Text[10301]["Text431"]
tNpcGossip[10301]["tOption4-3"] = {12}
tNpcGossip[10301]["Option12"] = tSummeractivities_thief_Text[10301]["Option12"]

tNpcGossip[10301]["Text4-4"] = {441}
tNpcGossip[10301]["Text441"] = tSummeractivities_thief_Text[10301]["Text441"]
tNpcGossip[10301]["tOption4-4"] = {13}
tNpcGossip[10301]["Option13"] = tSummeractivities_thief_Text[10301]["Option13"]

tNpcGossip[10301]["Text5-1"] = {511}
tNpcGossip[10301]["Text511"] = tSummeractivities_thief_Text[10301]["Text511"]
tNpcGossip[10301]["tOption5-1"] = {14}
tNpcGossip[10301]["Option14"] = tSummeractivities_thief_Text[10301]["Option14"]

tNpcGossip[10301]["Text5-2"] = {521}
tNpcGossip[10301]["Text521"] = tSummeractivities_thief_Text[10301]["Text521"]
tNpcGossip[10301]["tOption5-1"] = {15}
tNpcGossip[10301]["Option15"] = tSummeractivities_thief_Text[10301]["Option15"]

tNpcGossip[10301]["Text6-1"] = {611}
tNpcGossip[10301]["Text611"] = tSummeractivities_thief_Text[10301]["Text611"]
tNpcGossip[10301]["tOption6-1"] = {16}
tNpcGossip[10301]["Option16"] = tSummeractivities_thief_Text[10301]["Option16"]

tNpcGossip[10301]["Text6-2"] = {621}
tNpcGossip[10301]["Text621"] = tSummeractivities_thief_Text[10301]["Text621"]
tNpcGossip[10301]["tOption6-2"] = {17}
tNpcGossip[10301]["Option17"] = tSummeractivities_thief_Text[10301]["Option17"]

tNpcGossip[10301]["Text6-3"] = {631}
tNpcGossip[10301]["Text631"] = tSummeractivities_thief_Text[10301]["Text631"]
tNpcGossip[10301]["tOption6-3"] = {18}
tNpcGossip[10301]["Option18"] = tSummeractivities_thief_Text[10301]["Option18"]





