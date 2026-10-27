------------------------------------------------------------------------------------
--Name:			[征服][活动脚本]新国境地图配套任�?-掠夺村庄
--Creator: 		魏贻�?
--Created:		2015/12/11
------------------------------------------------------------------------------------
--命名：Looting_villages
--掩码�?35024

local	tLooting_villages_Cont = {}
		tLooting_villages_Cont["task_detail"] = 35024 --烧房子掩�?
		-- The TQ Realm database places the linked explosive devices on Realm3.
		tLooting_villages_Cont["mapid"] = 3935
		tLooting_villages_Cont["time"] = {}
		tLooting_villages_Cont["time"][1] = "00 00"

local	tLooting_villages_Monster = {}
		tLooting_villages_Monster[1] = 7882
		tLooting_villages_Monster[2] = 7883
		tLooting_villages_Monster[3] = 7884
		tLooting_villages_Monster[4] = 7971
		tLooting_villages_Monster[5] = 7972
		tLooting_villages_Monster[6] = 7973

local	tLooting_villages_MapEffect = {}
		tLooting_villages_MapEffect[10948] = {}
		tLooting_villages_MapEffect[10948]["cellx"] = 378
		tLooting_villages_MapEffect[10948]["celly"] = 404

		tLooting_villages_MapEffect[10949] = {}
		tLooting_villages_MapEffect[10949]["cellx"] = 368
		tLooting_villages_MapEffect[10949]["celly"] = 355

		tLooting_villages_MapEffect[10950] = {}
		tLooting_villages_MapEffect[10950]["cellx"] = 400
		tLooting_villages_MapEffect[10950]["celly"] = 364
		
		tLooting_villages_MapEffect[10951] = {}
		tLooting_villages_MapEffect[10951]["cellx"] = 406
		tLooting_villages_MapEffect[10951]["celly"] = 401

--随机出现�?兵的坐标
--放火�?1
local	tLooting_villages_AddMonster = {}
		tLooting_villages_AddMonster[10948] = {}
		tLooting_villages_AddMonster[10948][1] = {}
		tLooting_villages_AddMonster[10948][1]["Cellx"] = 375
		tLooting_villages_AddMonster[10948][1]["Celly"] = 413

		tLooting_villages_AddMonster[10948][2] = {}
		tLooting_villages_AddMonster[10948][2]["Cellx"] = 381
		tLooting_villages_AddMonster[10948][2]["Celly"] = 412

		tLooting_villages_AddMonster[10948][3] = {}
		tLooting_villages_AddMonster[10948][3]["Cellx"] = 386
		tLooting_villages_AddMonster[10948][3]["Celly"] = 406
		
		tLooting_villages_AddMonster[10948][4] = {}
		tLooting_villages_AddMonster[10948][4]["Cellx"] = 384
		tLooting_villages_AddMonster[10948][4]["Celly"] = 398

		tLooting_villages_AddMonster[10948][5] = {}
		tLooting_villages_AddMonster[10948][5]["Cellx"] = 377
		tLooting_villages_AddMonster[10948][5]["Celly"] = 395
--放火�?2
		tLooting_villages_AddMonster[10949] = {}
		tLooting_villages_AddMonster[10949][1] = {}
		tLooting_villages_AddMonster[10949][1]["Cellx"] = 361
		tLooting_villages_AddMonster[10949][1]["Celly"] = 356

		tLooting_villages_AddMonster[10949][2] = {}
		tLooting_villages_AddMonster[10949][2]["Cellx"] = 362
		tLooting_villages_AddMonster[10949][2]["Celly"] = 364

		tLooting_villages_AddMonster[10949][3] = {}
		tLooting_villages_AddMonster[10949][3]["Cellx"] = 369
		tLooting_villages_AddMonster[10949][3]["Celly"] = 365
		
		tLooting_villages_AddMonster[10949][4] = {}
		tLooting_villages_AddMonster[10949][4]["Cellx"] = 376
		tLooting_villages_AddMonster[10949][4]["Celly"] = 363

		tLooting_villages_AddMonster[10949][5] = {}
		tLooting_villages_AddMonster[10949][5]["Cellx"] = 381
		tLooting_villages_AddMonster[10949][5]["Celly"] = 359

--放火�?3
		tLooting_villages_AddMonster[10950] = {}
		tLooting_villages_AddMonster[10950][1] = {}
		tLooting_villages_AddMonster[10950][1]["Cellx"] = 400
		tLooting_villages_AddMonster[10950][1]["Celly"] = 354

		tLooting_villages_AddMonster[10950][2] = {}
		tLooting_villages_AddMonster[10950][2]["Cellx"] = 405
		tLooting_villages_AddMonster[10950][2]["Celly"] = 362

		tLooting_villages_AddMonster[10950][3] = {}
		tLooting_villages_AddMonster[10950][3]["Cellx"] = 403
		tLooting_villages_AddMonster[10950][3]["Celly"] = 370
		
		tLooting_villages_AddMonster[10950][4] = {}
		tLooting_villages_AddMonster[10950][4]["Cellx"] = 395
		tLooting_villages_AddMonster[10950][4]["Celly"] = 368

		tLooting_villages_AddMonster[10950][5] = {}
		tLooting_villages_AddMonster[10950][5]["Cellx"] = 393
		tLooting_villages_AddMonster[10950][5]["Celly"] = 360

--放火�?4
		tLooting_villages_AddMonster[10951] = {}
		tLooting_villages_AddMonster[10951][1] = {}
		tLooting_villages_AddMonster[10951][1]["Cellx"] = 398
		tLooting_villages_AddMonster[10951][1]["Celly"] = 408

		tLooting_villages_AddMonster[10951][2] = {}
		tLooting_villages_AddMonster[10951][2]["Cellx"] = 397
		tLooting_villages_AddMonster[10951][2]["Celly"] = 402

		tLooting_villages_AddMonster[10951][3] = {}
		tLooting_villages_AddMonster[10951][3]["Cellx"] = 399
		tLooting_villages_AddMonster[10951][3]["Celly"] = 397
		
		tLooting_villages_AddMonster[10951][4] = {}
		tLooting_villages_AddMonster[10951][4]["Cellx"] = 404
		tLooting_villages_AddMonster[10951][4]["Celly"] = 395

		tLooting_villages_AddMonster[10951][5] = {}
		tLooting_villages_AddMonster[10951][5]["Cellx"] = 408
		tLooting_villages_AddMonster[10951][5]["Celly"] = 398


local	tLooting_villages_generator = {}
		tLooting_villages_generator[1] = {}
		tLooting_villages_generator[1]["MonsterId"] = 7882
		tLooting_villages_generator[1]["GenId"] = 18266
		tLooting_villages_generator[1]["Cellx"] = 379
		tLooting_villages_generator[1]["Celly"] = 335

		tLooting_villages_generator[2] = {}
		tLooting_villages_generator[2]["MonsterId"] = 7882
		tLooting_villages_generator[2]["GenId"] = 18267
		tLooting_villages_generator[2]["Cellx"] = 387
		tLooting_villages_generator[2]["Celly"] = 335

		tLooting_villages_generator[3] = {}
		tLooting_villages_generator[3]["MonsterId"] = 7882
		tLooting_villages_generator[3]["GenId"] = 18268
		tLooting_villages_generator[3]["Cellx"] = 345
		tLooting_villages_generator[3]["Celly"] = 372
		
		tLooting_villages_generator[4] = {}
		tLooting_villages_generator[4]["MonsterId"] = 7882
		tLooting_villages_generator[4]["GenId"] = 18269
		tLooting_villages_generator[4]["Cellx"] = 345
		tLooting_villages_generator[4]["Celly"] = 379
		
		tLooting_villages_generator[5] = {}
		tLooting_villages_generator[5]["MonsterId"] = 7882
		tLooting_villages_generator[5]["GenId"] = 18270
		tLooting_villages_generator[5]["Cellx"] = 378
		tLooting_villages_generator[5]["Celly"] = 437
		
		tLooting_villages_generator[6] = {}
		tLooting_villages_generator[6]["MonsterId"] = 7882
		tLooting_villages_generator[6]["GenId"] = 18271
		tLooting_villages_generator[6]["Cellx"] = 400
		tLooting_villages_generator[6]["Celly"] = 424
		
		tLooting_villages_generator[7] = {}
		tLooting_villages_generator[7]["MonsterId"] = 7882
		tLooting_villages_generator[7]["GenId"] = 18272
		tLooting_villages_generator[7]["Cellx"] = 428
		tLooting_villages_generator[7]["Celly"] = 400

		tLooting_villages_generator[8] = {}
		tLooting_villages_generator[8]["MonsterId"] = 7882
		tLooting_villages_generator[8]["GenId"] = 18273
		tLooting_villages_generator[8]["Cellx"] = 439
		tLooting_villages_generator[8]["Celly"] = 380

		tLooting_villages_generator[9] = {}
		tLooting_villages_generator[9]["MonsterId"] = 7883
		tLooting_villages_generator[9]["GenId"] = 18274
		tLooting_villages_generator[9]["Cellx"] = 387
		tLooting_villages_generator[9]["Celly"] = 386

		tLooting_villages_generator[10] = {}
		tLooting_villages_generator[10]["MonsterId"] = 7884
		tLooting_villages_generator[10]["GenId"] = 18278
		tLooting_villages_generator[10]["Cellx"] = 396
		tLooting_villages_generator[10]["Celly"] = 380
		
		tLooting_villages_generator[11] = {}
		tLooting_villages_generator[11]["MonsterId"] = 7971
		tLooting_villages_generator[11]["GenId"] = 18275
		tLooting_villages_generator[11]["Cellx"] = 379
		tLooting_villages_generator[11]["Celly"] = 393
		
		tLooting_villages_generator[12] = {}
		tLooting_villages_generator[12]["MonsterId"] = 7972
		tLooting_villages_generator[12]["GenId"] = 18276
		tLooting_villages_generator[12]["Cellx"] = 381
		tLooting_villages_generator[12]["Celly"] = 378
	
		tLooting_villages_generator[13] = {}
		tLooting_villages_generator[13]["MonsterId"] = 7973
		tLooting_villages_generator[13]["GenId"] = 18277
		tLooting_villages_generator[13]["Cellx"] = 395
		tLooting_villages_generator[13]["Celly"] = 395

--奖励�?
local	tLooting_villages_Award = {}
--放火奖励
		tLooting_villages_Award[1] = {}
		tLooting_villages_Award[1]["ItemId"] = {}
		tLooting_villages_Award[1]["ItemId"][1] = 3600033 
		tLooting_villages_Award[1]["ItemId"][2] = 1003010
		tLooting_villages_Award[1]["ItemId"][3] = 3600024
		tLooting_villages_Award[1]["ItemId"][4] = 3600025
		tLooting_villages_Award[1]["ItemId"][5] = 3600026
		tLooting_villages_Award[1]["ItemId"][6] = 3600023

		tLooting_villages_Award[1]["Attr"] = {}
		tLooting_villages_Award[1]["Attr"][1] = "0 1 0 1440 1"
		tLooting_villages_Award[1]["Attr"][2] = "0 1 3"
		tLooting_villages_Award[1]["Attr"][3] = "0 1"
		tLooting_villages_Award[1]["Attr"][4] = "0 1 0 1440 1"
		tLooting_villages_Award[1]["Attr"][5] = "0 1 0 1440 1"
		tLooting_villages_Award[1]["Attr"][6] = "0 1"

--大水晶�?�励
		tLooting_villages_Award[2] = {}
		tLooting_villages_Award[2]["ItemId"] = {}
		tLooting_villages_Award[2]["ItemId"][1] = 3600031
		tLooting_villages_Award[2]["Attr"] = {}
		tLooting_villages_Award[2]["Attr"][1] = "0 1 0 2880 1"

--�?boss奖励
		tLooting_villages_Award[3] = {}
		tLooting_villages_Award[3]["ItemId"] = {}
		tLooting_villages_Award[3]["ItemId"][1] = 3600027

		tLooting_villages_Award[3]["Attr"] = {}
		tLooting_villages_Award[3]["Attr"][1] = "0 1 0 10080 1"

--神魂礼包概率配置
		tLooting_villages_Award[4] = {}
		tLooting_villages_Award[4][1] = {}
		tLooting_villages_Award[4][1]["ItemId"] = {824020,824019,824018,823062,823061,823060,823059,823058,822072,822071,821034,821033,820076,820075,820074,820073,800917,800811,800810,800725,800618,800522,800422,800255,800215,800142,800111,800020,801004,801104,801308,827010,827011,827012,827013}
		tLooting_villages_Award[4][1]["Attr"] = "0 1 0 10080 1"
		tLooting_villages_Award[4][1]["Chance"] = 20

		tLooting_villages_Award[4][2] = {}
		tLooting_villages_Award[4][2]["ItemId"] = {822053,822055,800000,800110,800017,800320,800513,800616,800722,823055,823056,820071,820072,800421,821031,821032,824017,823057,800804,800809,800254,800916,801003,801103,801306,827009,827008,827007,827006}
		tLooting_villages_Award[4][2]["Attr"] = "0 1 0 10080 1"
		tLooting_villages_Award[4][2]["Chance"] = 30

		tLooting_villages_Award[4][3] = {}
		tLooting_villages_Award[4][3]["ItemId"] = {724404,724409,724414,724419,724424,724429,724434,724439,724444,724453,724458,724463,724472,724477,724482,724487,724492,724497,724352,724357,724362,724367,724372,724377,724384,724389,724394,724519,725196,725201,725206,725211,3006169}
		tLooting_villages_Award[4][3]["Attr"] = "0 1 0 10080 1"
		tLooting_villages_Award[4][3]["Chance"] = 20

		tLooting_villages_Award[4][4] = {}
		tLooting_villages_Award[4][4]["ItemId"] = {3004137,3004138,3004139,3004140,3004141,3004142,3004143,3004144,3004147,3004148,3004149,3004150,3004151,3004152,3004153,3004156,3004158,3004159,3004160,3004161,3004163,3004164,3004165,3004166,3004136,3004146,3004157,3004155,3004145,3004154,3004162,3006170}
		tLooting_villages_Award[4][4]["Attr"] = "0 1 0 10080 1"
		tLooting_villages_Award[4][4]["Chance"] = 30

--精炼石礼包�?�励
		tLooting_villages_Pack = {}
		tLooting_villages_Pack[3600031] = {}
		tLooting_villages_Pack[3600031]["Space"] = 2
		tLooting_villages_Pack[3600031][1] = {}
		tLooting_villages_Pack[3600031][1]["ItemId"] = 3009000
		tLooting_villages_Pack[3600031][1]["Attr"] = "0 3 0 2880 1"

		tLooting_villages_Log = {}
		tLooting_villages_Log[1] = "0,0,0,0,18000104,1[1],0,0" --完成点火任务
		tLooting_villages_Log[2] = "0,0,0,0,18000104,1[2],0,0" --�?大水�?
		tLooting_villages_Log[3] = "0,0,0,0,18000104,1[3],0,0" --�?boss
		tLooting_villages_Log[4] = "0,0,0,0,18000104,1[4],0,0" --领杀boss福利

		tLooting_villages_Log[5] = "0,0,3600024,1,18000104,2,1100003,1" --1�?合成成功
		tLooting_villages_Log[6] = "0,0,3600024,1,18000104,2,0,0" --1�?合成失败
		tLooting_villages_Log[7] = "0,0,3600024,5,18000104,2,1100003,1" --5�?合成
		
		tLooting_villages_Log[8] = "0,0,3600025,1,18000104,2,4,100" --100分钟经验
		tLooting_villages_Log[9] = "0,0,3600025,1,18000104,2,6,50" --50�?行�??
		tLooting_villages_Log[10] = "0,0,3600026,1,18000104,2,18,50" --50黄金联赛�?�?
		tLooting_villages_Log[11] = "0,0,3600027,1,18000104,2,%d,1" --获得随机神魂
		tLooting_villages_Log[13] = "0,0,3600033,1,18000104,2,12,50" --获得50气力
		tLooting_villages_Log[14] = "0,0,3200004,1,18000104,2,[729549][3600024][4][18][3600023][3303020],[1][1][100][50][1][1]" --打开国�?�犒赏�?�荒村焚妖�??
		tLooting_villages_Log[15] = "0,0,3200004,1,18000104,2,[729549][3600024][4][18][4060001][3321097],[1][1][100][50][2][1]" --打开国�?�犒赏�?�荒村焚妖�??
local tCrossServiceExpPack = {}
	tCrossServiceExpPack[1] = {}
	tCrossServiceExpPack[1]["DeleteItem"] = {}
	tCrossServiceExpPack[1]["DeleteItem"][1] = {}
	tCrossServiceExpPack[1]["DeleteItem"][1]["Id"] = 3303020
	tCrossServiceExpPack[1]["RewardExpTime"] = {}
	tCrossServiceExpPack[1]["RewardExpTime"]["Value"] = 300
	tCrossServiceExpPack[1]["Log"] = "0,0,3303020,1,10002422,2,4,300"

	tCrossServiceExpPack[2] = {}
	tCrossServiceExpPack[2]["DeleteItem"] = {}
	tCrossServiceExpPack[2]["DeleteItem"][1] = {}
	tCrossServiceExpPack[2]["DeleteItem"][1]["Id"] = 3303020
	tCrossServiceExpPack[2]["RewardExpTime"] = {}
	tCrossServiceExpPack[2]["RewardExpTime"]["Value"] = 600
	tCrossServiceExpPack[2]["Log"] = "0,0,3303020,1,10002422,2,4,600"
	
	tCrossServiceExpPack[3] = {}
	tCrossServiceExpPack[3]["DeleteItem"] = {}
	tCrossServiceExpPack[3]["DeleteItem"][1] = {}
	tCrossServiceExpPack[3]["DeleteItem"][1]["Id"] = 3303020
	tCrossServiceExpPack[3]["RewardCultivation"] = {}
	tCrossServiceExpPack[3]["RewardCultivation"]["Value"] = 150
	tCrossServiceExpPack[3]["Log"] = "0,0,3303020,1,10002422,2,6,150"
	
local tCrossServiceExpPackNoGift = {}
	tCrossServiceExpPackNoGift[1] = {}
	tCrossServiceExpPackNoGift[1]["DeleteItem"] = {}
	tCrossServiceExpPackNoGift[1]["DeleteItem"][1] = {}
	tCrossServiceExpPackNoGift[1]["DeleteItem"][1]["Id"] = 3321097
	tCrossServiceExpPackNoGift[1]["RewardExpTime"] = {}
	tCrossServiceExpPackNoGift[1]["RewardExpTime"]["Value"] = 50
	tCrossServiceExpPackNoGift[1]["Log"] = "0,0,3321097,1,10002422,2,4,50"

	tCrossServiceExpPackNoGift[2] = {}
	tCrossServiceExpPackNoGift[2]["DeleteItem"] = {}
	tCrossServiceExpPackNoGift[2]["DeleteItem"][1] = {}
	tCrossServiceExpPackNoGift[2]["DeleteItem"][1]["Id"] = 3321097
	tCrossServiceExpPackNoGift[2]["RewardExpTime"] = {}
	tCrossServiceExpPackNoGift[2]["RewardExpTime"]["Value"] = 100
	tCrossServiceExpPackNoGift[2]["Log"] = "0,0,3321097,1,10002422,2,4,100"
	
	tCrossServiceExpPackNoGift[3] = {}
	tCrossServiceExpPackNoGift[3]["DeleteItem"] = {}
	tCrossServiceExpPackNoGift[3]["DeleteItem"][1] = {}
	tCrossServiceExpPackNoGift[3]["DeleteItem"][1]["Id"] = 3321097
	tCrossServiceExpPackNoGift[3]["RewardCultivation"] = {}
	tCrossServiceExpPackNoGift[3]["RewardCultivation"]["Value"] = 25
	tCrossServiceExpPackNoGift[3]["Log"] = "0,0,3321097,1,10002422,2,6,25"

--�?�?�?
function Looting_villages_powder()
	local nNpcId = Get_NpcId()
	local nUserId = Get_UserId()
	local nTask_detail = tLooting_villages_Cont["task_detail"]
	local nTaskDetailData1 = Get_TaskDetailData1(nTask_detail)
	local nTaskDetailData2 = Get_TaskDetailData2(nTask_detail)
	local nUser_x = Get_UserPositionX()
	local nUser_y = Get_UserPositionY()
	local nNpc_x = Get_NpcPositionX()
	local nNpc_y = Get_NpcPositionY()

--判断距�??
	if math.abs(nUser_x - nNpc_x) > 10 or math.abs(nUser_y - nNpc_y) > 10 then
		User_TalkChannel2005(tLooting_villages_Text[1])
		return
	end

--判断任务�?否存�?
	if not Task_ChkTaskDetail(nTask_detail) then
		Task_AddTaskDetail(nTask_detail)
	end

--判断�?否完�?
	if Get_TaskDetailData6(nTask_detail) ~= 0 or nTaskDetailData2 >= 1 then
		User_TalkChannel2005(tLooting_villages_Text[2])
		return
	end

--接原来�?�条后的函数
	Looting_villages_powder_success(nTaskDetailData1,nNpcId,nUserId)
end


--读条成功
function Looting_villages_powder_success(nTaskDetailData1,nNpcId,nUserId)
--设置完成任务
	Task_SetTaskDetailData2(tLooting_villages_Cont["task_detail"],1,nUserId)
	local nNpcMapId = Get_NpcMapID(nNpcId)
	Map_Effect(nNpcMapId,tLooting_villages_MapEffect[nNpcId]["cellx"],tLooting_villages_MapEffect[nNpcId]["celly"],"firemagic")
	if tLooting_villages_AddMonster[nNpcId] then
		local nSpot = math.random(1,#tLooting_villages_AddMonster[nNpcId])
		local tPos = tLooting_villages_AddMonster[nNpcId][nSpot]
		Monster_AddMonster(nNpcMapId,tPos["Cellx"],tPos["Celly"],18266,7882)
	end
	User_EffectAdd("self","angelwing",nUserId)
	Sys_MsgBox(tLooting_villages_Text[8],"NULL","NULL",nUserId)

end

--跨服任务大使领取奖励
function Looting_villages_Option601(nNpcId)
	local nTask_detail = tLooting_villages_Cont["task_detail"]
	local nTaskDetailData2 = Get_TaskDetailData2(nTask_detail)
	local nTaskDetailData6 = Get_TaskDetailData6(nTask_detail)
--判断�?否已经�?�过奖励
	if nTaskDetailData6 >= 1 then
		LinkNpcGossipFunc_New(nNpcId,"602-2")
		return
	end

--判断�?否完成任�?
	if nTaskDetailData2 < 1 then
		LinkNpcGossipFunc_New(nNpcId,"602-1")
		return
	end

--判断背包空间
	if not User_CheckLeftSpace(1) then
		User_TalkChannel2005(tLooting_villages_Text[12])
		return
	end
--打完成掩�?
	Task_SetTaskDetailData2(tLooting_villages_Cont["task_detail"],0)
	Task_SetTaskDetailData6(tLooting_villages_Cont["task_detail"],1)
	Task_SetTaskDetailCompleteFlag(tLooting_villages_Cont["task_detail"],1)
	Sys_SaveActionTaskLog(tLooting_villages_Log[1])
	User_TalkChannel2005(tLooting_villages_Text[10])

--领�??
	National_War_AddIntegral(30)
	Item_AddNewItem(3200004,"0 1 0 1440 1")

end

--�?物�?�辑
--大水�?
function Looting_villages_Monster7884()
	local nUserId = Get_UserId()
	local nMonsterId = Get_MonsterType()
	local nMonsterNum = Get_SysTempData(1,tLooting_villages_Cont["mapid"],nMonsterId)
	Sys_SetTempData(1,tLooting_villages_Cont["mapid"],nMonsterId,math.max(0,(tonumber(nMonsterNum) or 1)-1))

	for i = 1,#tLooting_villages_Award[2]["ItemId"] do
		local nItemId = tLooting_villages_Award[2]["ItemId"][i]
		local sAttr = tLooting_villages_Award[2]["Attr"][i]
		Item_AddNewItem(nItemId,sAttr,nUserId)
	end
	-- Credit Realm Ore (35006 Big Magic Ore), Strike Points (+50), and Crystal Bounty (+10)
	if not Task_ChkTaskDetail(35006,nUserId) then
		Task_AddTaskDetail(35006,0,nUserId)
	end
	local nOreData = Get_TaskDetailData1(35006,nUserId) + 1
	Task_SetTaskDetailData1(35006,nOreData,nUserId)
	if tServiceTask_Crystal_Text and tServiceTask_Crystal_Text["DamageCrystal_Big"] then
		User_TalkChannel2005(tServiceTask_Crystal_Text["DamageCrystal_Big"],nUserId)
	end
	if FirstPerson_AddKillMonsterNum then
		FirstPerson_AddKillMonsterNum(nUserId,9)
	end
	if InterServeTask_Killer_TeamEnjoy then
		InterServeTask_Killer_TeamEnjoy(1,50)
	end
	Sys_SaveActionTaskLog(tLooting_villages_Log[2],nUserId)
	User_TalkChannel2005(tLooting_villages_Text[20],nUserId)
end

function Looting_villages_Monster7883()
	local nUserId = Get_UserId()
	local nMonsterId = Get_MonsterType()
	local nMonsterNum = Get_SysTempData(1,tLooting_villages_Cont["mapid"],nMonsterId)
	Sys_SetTempData(1,tLooting_villages_Cont["mapid"],nMonsterId,math.max(0,(tonumber(nMonsterNum) or 1)-1))

	for i = 1,#tLooting_villages_Award[3]["ItemId"] do
		local nItemId = tLooting_villages_Award[3]["ItemId"][i]
		local sAttr = tLooting_villages_Award[3]["Attr"][i]
		Item_AddNewItem(nItemId,sAttr,nUserId)
	end
	if FirstPerson_AddKillMonsterNum then
		FirstPerson_AddKillMonsterNum(nUserId,9)
	end
	if InterServeTask_Killer_TeamEnjoy then
		InterServeTask_Killer_TeamEnjoy(1,50)
	end
	if InterServeTask_Killer_HauntMonsterBoss then
		InterServeTask_Killer_HauntMonsterBoss(7859)
	end
	Sys_SaveActionTaskLog(tLooting_villages_Log[3],nUserId)
	User_TalkChannel2005(tLooting_villages_Text[21],nUserId)
end


function Looting_villages_Monster7881()
	local nUserId = Get_UserId()
	if FirstPerson_AddKillMonsterNum then
		FirstPerson_AddKillMonsterNum(nUserId)
	end
	if User_CheckLeftSpace(1,nUserId) then
		local nIdx = math.random(1,#tLooting_villages_Award[1]["ItemId"])
		Item_AddNewItem(tLooting_villages_Award[1]["ItemId"][nIdx],tLooting_villages_Award[1]["Attr"][nIdx],nUserId)
	end
end

--200w时间�?�?
function Looting_villages_Timechk()
--boss和水晶换�?1小时�?1�? 每小�?0点刷�?
	if not Sys_ChkMinute(tLooting_villages_Cont["time"][1]) then
		return
	end

--删除�?有�??�?
	for i= 2,6 do
		if Get_SysTempData(1,tLooting_villages_Cont["mapid"],tLooting_villages_Monster[i]) > 0 then
			Monster_DelMonster(tLooting_villages_Cont["mapid"],tLooting_villages_Monster[i])
			Sys_SetTempData(1,tLooting_villages_Cont["mapid"],tLooting_villages_Monster[i],0)
		end
	end

--创建�?�? (7883 AlluringWitch + 7884, 7971..7973 DarkCrystals)
	for i= 9,13 do
		local nMonsterNum = Get_SysTempData(1,tLooting_villages_Cont["mapid"],tLooting_villages_generator[i]["MonsterId"])
		Monster_AddMonster(tLooting_villages_Cont["mapid"],tLooting_villages_generator[i]["Cellx"],tLooting_villages_generator[i]["Celly"],tLooting_villages_generator[i]["GenId"],tLooting_villages_generator[i]["MonsterId"])
		Sys_SetTempData(1,tLooting_villages_Cont["mapid"],tLooting_villages_generator[i]["MonsterId"],nMonsterNum+1)
	end
	Sys_TalkBroadcast(tLooting_villages_Text[9])
end

--乾坤袋�?�片
function Looting_villages_Item3600024(nItemId)
	if Item_ChkItem(nItemId) then
		LinkItemGossipFunc_New(nItemId,"1-1")
	end
end

--20%概率洗�?�片
function Looting_villages_Item3600024_1(nItemId)
	if not User_CheckLeftSpace(1) then
		User_TalkChannel2005(tLooting_villages_Text[nItemId]["Nospace"])
		return
	end
	local nUserId = Get_UserId()
	if Item_ChkItem(nItemId) and Item_DelItem(nItemId) then
		if Sys_Random(2000,10000) then
			Item_AddNewItem(1100003,"0 1",nUserId)
			Sys_SaveActionTaskLog(tLooting_villages_Log[5])
			LinkItemGossipFunc_New(nItemId,"2-1")
		else
			Sys_SaveActionTaskLog(tLooting_villages_Log[6])
			LinkItemGossipFunc_New(nItemId,"2-2")
		end
	end
end

--5�?合成
function Looting_villages_Item3600024_2(nItemId)
	if not Item_ChkMulItem(nItemId,nItemId,5) then
		LinkItemGossipFunc_New(nItemId,"2-3")
		return
	end
	if not User_CheckLeftSpace(1) then
		User_TalkChannel2005(tLooting_villages_Text[nItemId]["Nospace"])
		return
	end
	local nUserId = Get_UserId()
	if Item_DelMulItem(nItemId,nItemId,5) then
		Item_AddNewItem(1100003,"0 1",nUserId)
		Sys_SaveActionTaskLog(tLooting_villages_Log[7])
		LinkItemGossipFunc_New(nItemId,"2-4")
	end
end

--100分钟经验礼包
function Looting_villages_Item3600025(nItemId)
	if Item_ChkItem(nItemId) and Item_DelItem(nItemId) then
		local nLevel = Get_UserLevel()
		local nUserId = Get_UserId()
		if nLevel < G_User_MaxLev then
			if nLevel >= 140 and User_ChkSurplusExp(nUserId) then
				User_AddCultivation(50)
				User_TalkChannel2005(tLooting_villages_Text[nItemId][2])
				Sys_SaveActionTaskLog(tLooting_villages_Log[9])
				return
			end
			User_AddExpTime(100)
			User_TalkChannel2005(tLooting_villages_Text[nItemId][1])
			Sys_SaveActionTaskLog(tLooting_villages_Log[8])
		else
			User_AddCultivation(50)
			User_TalkChannel2005(tLooting_villages_Text[nItemId][2])
			Sys_SaveActionTaskLog(tLooting_villages_Log[9])
		end
	end
end

--50点黄金联赛积分礼�?
function Looting_villages_Item3600026(nItemId)
	if Item_ChkItem(nItemId) and Item_DelItem(nItemId) then
		local nUserId = Get_UserId()
		User_AddLeaguePoint(50,nUserId)
		User_TalkChannel2005(tLooting_villages_Text[nItemId][1])
		Sys_SaveActionTaskLog(tLooting_villages_Log[10])
	end
end

-- 神魂礼包
function Looting_villages_Item3600027(nItemId)
	if Item_ChkItem(nItemId) and Item_DelItem(nItemId) then
		local nUserId = Get_UserId()
		local nChance = 100
		for i = 1,#tLooting_villages_Award[4] do
			if Sys_Random(tLooting_villages_Award[4][i]["Chance"],nChance) then
				local nNum = math.random(1,#tLooting_villages_Award[4][i]["ItemId"])
				local nAddNewItem = tLooting_villages_Award[4][i]["ItemId"][nNum]
				local sAttr = tLooting_villages_Award[4][i]["Attr"]
				local sName = Get_ItemtypeName(nAddNewItem)
				local sText = string.format(tLooting_villages_Text[nItemId][1],sName)
				local sLog = string.format(tLooting_villages_Log[11],nAddNewItem)
				Item_AddNewItem(nAddNewItem,sAttr,nUserId)
				User_TalkChannel2005(sText)
				Sys_SaveActionTaskLog(sLog)
				break
			end
			nChance = nChance - tLooting_villages_Award[4][i]["Chance"]
		end
	end
end

--精炼石礼�?
function Looting_villages_Item3600031(nItemId)
	local nUserId = Get_UserId()

	if not User_CheckLeftSpace(tLooting_villages_Pack[nItemId]["Space"]) then
		User_TalkChannel2005(tLooting_villages_Text[nItemId][1])
		return
	end

	if Item_ChkItem(nItemId) and Item_DelItem(nItemId) then
		for i = 1,#tLooting_villages_Pack[nItemId] do
			local nAddNewItem = tLooting_villages_Pack[nItemId][i]["ItemId"]
			local sAttr = tLooting_villages_Pack[nItemId][i]["Attr"]
			Item_AddNewItem(nAddNewItem,sAttr,nUserId)
			User_TalkChannel2005(tLooting_villages_Text[nItemId][2])
		end
	end
end

--50点气力礼�?
function Looting_villages_Item3600033(nItemId)
	if Item_ChkItem(nItemId) and Item_DelItem(nItemId) then
		User_AddStrengthValue(50)
		User_TalkChannel2005(tLooting_villages_Text[nItemId][1])
		Sys_SaveActionTaskLog(tLooting_villages_Log[13])
	end
end

--国�?�犒赏�?�荒村焚妖�??
function Looting_villages_Item3200004(nItemId)
	if not User_CheckLeftSpace(3) then
		User_TalkChannel2005(tLooting_villages_Text[nItemId]["Nospace"])
		return
	end

	if Item_ChkItem(nItemId) and Item_DelItem(nItemId) then
		-- User_AddStrengthValue(50) --50气力
		User_AddLeaguePoint(50) --50黄金联赛�?�?
		Item_AddNewItem(729549,"0 1 3") --�?�?
		-- Item_AddNewItem(3600024,"0 1") --乾坤袋�?�片
		-- Item_AddNewItem(3600023,"0 1") --功勋礼包
		-- Item_AddNewItem(3303020,"0 1 0 1440 1") --经验礼包
		Item_AddNewItem(3600025,"0 1 0 1440 1") --经验礼包 (EXPPack(Realm))
		Item_AddNewItem(3600024,"0 1") --乾坤袋�?�片
		Item_AddNewItem(3600023,"0 1") --功勋礼包
		Sys_SaveActionTaskLog(tLooting_villages_Log[14])
		User_TalkChannel2005(tLooting_villages_Text[nItemId][1])
		
		
	end
	--内嵌世界版图探索活动
	local nUserId = Get_UserId()
	if MapExploration_AddStc then
		MapExploration_AddStc(24,nUserId)
	end
end

-- The archived script used the newer generic RewardTemplate module, which is
-- not part of this server's Lua set. Keep these two Realm packs self-contained.
local function Looting_villages_UseExpReward(tReward,nUserId)
	local nItemId = tReward["DeleteItem"][1]["Id"]
	if not Item_ChkItem(nItemId,1,0,nUserId) or not Item_DelItem(nItemId,1,0,nUserId) then
		return
	end

	if tReward["RewardExpTime"] then
		User_AddExpTime(tReward["RewardExpTime"]["Value"],nUserId)
	elseif tReward["RewardCultivation"] then
		User_AddCultivation(tReward["RewardCultivation"]["Value"],nUserId)
	end

	Sys_SaveActionTaskLog(tReward["Log"],nUserId)
end

--新加经验礼包
function CrossServiceExpPack(nItemId)
	local nLevel = Get_UserLevel()
	local nUserId = Get_UserId()
	-- if nLevel >= 140 and User_ChkSurplusExp(nUserId) then
		-- User_TalkChannel2005(tCrossServiceExpPack_Text[1])
		-- return
	-- end

	local nNum = 1
	if nLevel < 135 then
		nNum = 1
	elseif nLevel <= G_User_MaxLev and not User_ChkSurplusExp(nUserId) then
		nNum = 2
	else
		nNum = 3
	end
	
	
	Looting_villages_UseExpReward(tCrossServiceExpPack[nNum],nUserId)
	User_EffectAdd("self","angelwing")

end

function CrossServiceExpPackNoGift(nItemId)
	local nLevel = Get_UserLevel()
	local nUserId = Get_UserId()
	-- if nLevel >= 140 and User_ChkSurplusExp(nUserId) then
		-- User_TalkChannel2005(tCrossServiceExpPack_Text[1])
		-- return
	-- end

	local nNum = 1
	if nLevel < 135 then
		nNum = 1
	elseif nLevel <= G_User_MaxLev and not User_ChkSurplusExp(nUserId) then
		nNum = 2
	else
		nNum = 3
	end
	
	Looting_villages_UseExpReward(tCrossServiceExpPackNoGift[nNum],nUserId)

	
	User_EffectAdd("self","angelwing")


end

--------------------------------------------------------------------
--荒村焚�??
tNpcGossip[17400]["Option600"]= tLooting_villages_Text[17400]["Option600"]
tNpcGossip[17400]["OptionPoint600"] = "601-1"
tNpcGossip[17400]["OptionChkFunc600"] = function ()
	if User_IsCross() then
		return false
	end
	local nTaskId = tLooting_villages_Cont["task_detail"]
	local nData = 0
	if Task_ChkTaskDetail(nTaskId) then
		nData = Get_TaskDetailData6(nTaskId)
	end
	if nData >= 1 then
		tNpcGossip[17400]["Option600"] = tLooting_villages_Text[17400]["Option650"]
		tNpcGossip[17400]["OptionPoint600"] = "602-2"
	else
		tNpcGossip[17400]["Option600"] = tLooting_villages_Text[17400]["Option600"]
		tNpcGossip[17400]["OptionPoint600"] = "601-1"
	end
	return true
end

tNpcGossip[17400]["Option650"]= tLooting_villages_Text[17400]["Option650"]
tNpcGossip[17400]["OptionPoint650"] = "602-2"
tNpcGossip[17400]["OptionChkFunc650"] = function ()
	local nTaskId = tLooting_villages_Cont["task_detail"]
	local nData = 0
	if Task_ChkTaskDetail(nTaskId) then
		nData = Get_TaskDetailData6(nTaskId)
	end
	return  not User_IsCross() and nData >= 1
end

tNpcGossip[17400]["Text601-1"] = {60111,60112,60113}
tNpcGossip[17400]["Text60111"] = tLooting_villages_Text[17400]["Text60111"]
tNpcGossip[17400]["Text60112"] = tLooting_villages_Text[17400]["Text60112"]
tNpcGossip[17400]["Text60113"] = tLooting_villages_Text[17400]["Text60113"]
tNpcGossip[17400]["tOption601-1"] = {601,602}
tNpcGossip[17400]["Option601"]= tLooting_villages_Text[17400]["Option601"]
tNpcGossip[17400]["Option602"]= tLooting_villages_Text[17400]["Option602"]
tNpcGossip[17400]["OptionFunc601"]="Looting_villages_Option601</N>17400"

--�?完成任务
tNpcGossip[17400]["Text602-1"] = {60211}
tNpcGossip[17400]["Text60211"] = tLooting_villages_Text[17400]["Text60211"]
tNpcGossip[17400]["tOption602-1"] = {610}
tNpcGossip[17400]["Option610"]= tLooting_villages_Text[17400]["Option610"]

--已�?�取过�?�励
tNpcGossip[17400]["Text602-2"] = {60221}
tNpcGossip[17400]["Text60221"] = tLooting_villages_Text[17400]["Text60221"]
tNpcGossip[17400]["tOption602-2"] = {611}
tNpcGossip[17400]["Option611"]= tLooting_villages_Text[17400]["Option611"]

--荒村除魔
tNpcGossip[17400]["Option700"]= tLooting_villages_Text[17400]["Option700"]
tNpcGossip[17400]["OptionPoint700"] = "701-1"
tNpcGossip[17400]["OptionChkFunc700"] = function ()
	return  not User_IsCross()
end

tNpcGossip[17400]["Text701-1"] = {70111,70112,70113}
tNpcGossip[17400]["Text70111"] = tLooting_villages_Text[17400]["Text70111"]
tNpcGossip[17400]["Text70112"] = tLooting_villages_Text[17400]["Text70112"]
tNpcGossip[17400]["Text70113"] = tLooting_villages_Text[17400]["Text70113"]
tNpcGossip[17400]["tOption701-1"] = {701}
tNpcGossip[17400]["Option701"]= tLooting_villages_Text[17400]["Option701"]

--------------------------------------------------------------------
tItem[3600024] = tItem[3600024] or {}
tItem[3600024]["Function"] = function (nItemId)
	Looting_villages_Item3600024(nItemId)
end
tItem[3600024]["Text1-1"] = {111,112}
tItem[3600024]["Text111"] =  tLooting_villages_Text[3600024]["Text111"]
tItem[3600024]["Text112"] =  tLooting_villages_Text[3600024]["Text112"]
tItem[3600024]["tOption1-1"] = {1,2}
tItem[3600024]["Option1"] = tLooting_villages_Text[3600024]["Option1"]
tItem[3600024]["Option2"] = tLooting_villages_Text[3600024]["Option2"]
tItem[3600024]["OptionFunc1"] = "Looting_villages_Item3600024_1</N>3600024"
tItem[3600024]["OptionFunc2"] = "Looting_villages_Item3600024_2</N>3600024"

tItem[3600024]["Text2-1"] = {211}
tItem[3600024]["Text211"] =  tLooting_villages_Text[3600024]["Text211"]
tItem[3600024]["tOption2-1"] = {3}
tItem[3600024]["Option3"] = tLooting_villages_Text[3600024]["Option3"]
tItem[3600024]["OptionFunc3"]="Looting_villages_Item3600024</N>3600024"

tItem[3600024]["Text2-2"] = {221}
tItem[3600024]["Text221"] =  tLooting_villages_Text[3600024]["Text221"]
tItem[3600024]["tOption2-2"] = {3}

tItem[3600024]["Text2-3"] = {231}
tItem[3600024]["Text231"] =  tLooting_villages_Text[3600024]["Text231"]
tItem[3600024]["tOption2-3"] = {4}
tItem[3600024]["Option4"] = tLooting_villages_Text[3600024]["Option4"]

tItem[3600024]["Text2-4"] = {241}
tItem[3600024]["Text241"] =  tLooting_villages_Text[3600024]["Text241"]
tItem[3600024]["tOption2-4"] = {5}
tItem[3600024]["Option5"] = tLooting_villages_Text[3600024]["Option5"]
tItem[3600024]["OptionFunc5"]="Looting_villages_Item3600024</N>3600024"

tItem[3600025] = tItem[3600025] or {}
tItem[3600025]["Function"] = function (nItemId)
	Looting_villages_Item3600025(nItemId)
end

tItem[3600026] = tItem[3600026] or {}
tItem[3600026]["Function"] = function (nItemId)
	Looting_villages_Item3600026(nItemId)
end

tItem[3600027] = tItem[3600027] or {}
tItem[3600027]["Function"] = function (nItemId)
	Looting_villages_Item3600027(nItemId)
end

tItem[3600031] = tItem[3600031] or {}
tItem[3600031]["Function"] = function (nItemId)
	Looting_villages_Item3600031(nItemId)
end

tItem[3600033] = tItem[3600033] or {}
tItem[3600033]["Function"] = function (nItemId)
	Looting_villages_Item3600033(nItemId)
end

tItem[3200004] = tItem[3200004] or {}
tItem[3200004]["Function"] = function (nItemId)
	Looting_villages_Item3200004(nItemId)
end

--经验礼包
tItem[3303020] = tItem[3303020] or {}
tItem[3303020]["Function"] = function (nItemId)
	CrossServiceExpPack(nItemId)
end

--�?情服经验礼包
tItem[3321097] = tItem[3321097] or {}
tItem[3321097]["Function"] = function (nItemId)
	CrossServiceExpPackNoGift(nItemId)
end

--时间�?�?
tOntimerMin_M[0] = tOntimerMin_M[0] or {}
table.insert(tOntimerMin_M[0],Looting_villages_Timechk)

tMonster[7881] = tMonster[7881] or {}
tMonster[7881]["tFunction"] = tMonster[7881]["tFunction"] or {}
table.insert(tMonster[7881]["tFunction"],Looting_villages_Monster7881)

tMonster[7882] = tMonster[7882] or {}
tMonster[7882]["tFunction"] = tMonster[7882]["tFunction"] or {}
table.insert(tMonster[7882]["tFunction"],Looting_villages_Monster7881)

tMonster[7883] = tMonster[7883] or {}
tMonster[7883]["tFunction"] = tMonster[7883]["tFunction"] or {}
table.insert(tMonster[7883]["tFunction"],Looting_villages_Monster7883)

for _, nDarkCrystalId in ipairs({7884, 7971, 7972, 7973}) do
	tMonster[nDarkCrystalId] = tMonster[nDarkCrystalId] or {}
	tMonster[nDarkCrystalId]["tFunction"] = tMonster[nDarkCrystalId]["tFunction"] or {}
	table.insert(tMonster[nDarkCrystalId]["tFunction"],Looting_villages_Monster7884)
end
