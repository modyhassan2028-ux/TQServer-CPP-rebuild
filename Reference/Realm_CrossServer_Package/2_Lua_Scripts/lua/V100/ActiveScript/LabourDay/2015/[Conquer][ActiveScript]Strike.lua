--Name:			[征服][活动脚本]劳工节大罢工(9.7-9.13)
--Creator: 		魏贻逵
--Created:		2015/05/20
------------------------------------------------------------------------------------
--命名前? Laborday2015_Strike
local	tLaborday2015_Strike_Time = {}
		tLaborday2015_Strike_Time["Beftime"] = "2015-01-01 00:00 2015-09-06 23:59"
		tLaborday2015_Strike_Time["Nowtime"] = "2015-09-07 00:00 2015-09-13 23:59"
		tLaborday2015_Strike_Time["Aftime"] = "2015-09-14 00:00 2020-01-01 23:59"

		tLaborday2015_Strike_Time[1] = "2015-09-07 00:00 2015-09-08 23:59"
		tLaborday2015_Strike_Time[2] = "2015-09-09 00:00 2015-09-11 23:59"
		tLaborday2015_Strike_Time[3] = "2015-09-12 00:00 2015-09-12 23:59"
		tLaborday2015_Strike_Time[4] = "2015-09-13 00:00 2015-09-13 23:59"

local	tLaborday2015_Strike_Cont = {}
		tLaborday2015_Strike_Cont["Level"] = 80
		tLaborday2015_Strike_Cont["Metempsychosis"] = 0
		tLaborday2015_Strike_Cont["Space"] = 1
		tLaborday2015_Strike_Cont["Space1"] = 2
		tLaborday2015_Strike_Cont["Percent"] = 200
		tLaborday2015_Strike_Cont["PercentTime"] = 3600

		tLaborday2015_Strike_Cont["NpcId"] = {}
		tLaborday2015_Strike_Cont["NpcId"]["Bef"] = {}
		tLaborday2015_Strike_Cont["NpcId"]["Aft"] = {}
		
		tLaborday2015_Strike_Cont["NpcId"]["Bef"][1] = 8165
		tLaborday2015_Strike_Cont["NpcId"]["Aft"][1] = 8170
		
		tLaborday2015_Strike_Cont["NpcId"]["Bef"][2] = 8171
		tLaborday2015_Strike_Cont["NpcId"]["Aft"][2] = 8176
		
		tLaborday2015_Strike_Cont["NpcId"]["Bef"][3] = 8177
		tLaborday2015_Strike_Cont["NpcId"]["Aft"][3] = 8182
		
		tLaborday2015_Strike_Cont["NpcId"]["Bef"][4] = 8183
		tLaborday2015_Strike_Cont["NpcId"]["Aft"][4] = 8188

--头像配置
local	tLaborday2015_Strike_LookFace = {}
		tLaborday2015_Strike_LookFace[309] = 66
		tLaborday2015_Strike_LookFace[310] = 75
		tLaborday2015_Strike_LookFace[311] = 18
		tLaborday2015_Strike_LookFace[312] = 48
		tLaborday2015_Strike_LookFace[313] = 97

local	tLaborday2015_Strike_Item = {}
--第1阶段任务物品
		tLaborday2015_Strike_Item[1] = {}
		tLaborday2015_Strike_Item[1][8153] = {}
		tLaborday2015_Strike_Item[1][8153][1] = 720780
		tLaborday2015_Strike_Item[1][8153][2] = 720781
		tLaborday2015_Strike_Item[1][8153][3] = 711290

		tLaborday2015_Strike_Item[1][8154] = {}
		tLaborday2015_Strike_Item[1][8154][1] = 720782
		tLaborday2015_Strike_Item[1][8154][2] = 720783
		tLaborday2015_Strike_Item[1][8154][3] = 711291

		tLaborday2015_Strike_Item[1][8155] = {}
		tLaborday2015_Strike_Item[1][8155][1] = 720784
		tLaborday2015_Strike_Item[1][8155][2] = 720785
		tLaborday2015_Strike_Item[1][8155][3] = 711292

		tLaborday2015_Strike_Item[1][8156] = {}
		tLaborday2015_Strike_Item[1][8156][1] = 720786

--第2?段任?物品
		tLaborday2015_Strike_Item[2] = {}
		tLaborday2015_Strike_Item[2][1] = 711293
		
		tLaborday2015_Strike_Item[2][8153] = 720787
		tLaborday2015_Strike_Item[2][8154] = 711294
		tLaborday2015_Strike_Item[2][8155] = 711295
		tLaborday2015_Strike_Item[2][8156] = 720788

--第4?段任?物品
		tLaborday2015_Strike_Item[4] = {}
		tLaborday2015_Strike_Item[4][8165] = 711296
		tLaborday2015_Strike_Item[4][8171] = 711297
		tLaborday2015_Strike_Item[4][8177] = 711298
		tLaborday2015_Strike_Item[4][8183] = 711299

		tLaborday2015_Strike_Item[4][8153] = {}
		tLaborday2015_Strike_Item[4][8153][1] = 500301
		tLaborday2015_Strike_Item[4][8153][2] = 421301
		tLaborday2015_Strike_Item[4][8153][3] = 601003
		tLaborday2015_Strike_Item[4][8153][4] = 410301
		tLaborday2015_Strike_Item[4][8153][5] = 711296
		tLaborday2015_Strike_Item[4][8153][6] = 720789

		tLaborday2015_Strike_Item[4][8154] = {}
		tLaborday2015_Strike_Item[4][8154][1] = 1060040
		tLaborday2015_Strike_Item[4][8154][2] = 1060050
		tLaborday2015_Strike_Item[4][8154][3] = 1060060
		tLaborday2015_Strike_Item[4][8154][4] = 1060070
		tLaborday2015_Strike_Item[4][8154][5] = 711297
		tLaborday2015_Strike_Item[4][8154][6] = 720812
		
		tLaborday2015_Strike_Item[4][8155] = {}
		tLaborday2015_Strike_Item[4][8155][1] = 117015
		tLaborday2015_Strike_Item[4][8155][2] = 150015
		tLaborday2015_Strike_Item[4][8155][3] = 152015
		tLaborday2015_Strike_Item[4][8155][4] = 120045
		tLaborday2015_Strike_Item[4][8155][5] = 711298
		tLaborday2015_Strike_Item[4][8155][6] = 720813

		tLaborday2015_Strike_Item[4][8156] = {}
		tLaborday2015_Strike_Item[4][8156][1] = 123013
		tLaborday2015_Strike_Item[4][8156][2] = 112013
		tLaborday2015_Strike_Item[4][8156][3] = 141013
		tLaborday2015_Strike_Item[4][8156][4] = 111013
		tLaborday2015_Strike_Item[4][8156][5] = 711299
		tLaborday2015_Strike_Item[4][8156][6] = 720814


local	tLaborday2015_Strike_Stc = {}
--第1阶段掩码
--4个npc 4个任务
		tLaborday2015_Strike_Stc[1] = {}
		tLaborday2015_Strike_Stc[1][8153] = {}
		tLaborday2015_Strike_Stc[1][8153]["EventType"] = 71
		tLaborday2015_Strike_Stc[1][8153]["DataType"] = 6
		tLaborday2015_Strike_Stc[1][8153]["Data"] = 1

		tLaborday2015_Strike_Stc[1][8154] = {}
		tLaborday2015_Strike_Stc[1][8154]["EventType"] = 71
		tLaborday2015_Strike_Stc[1][8154]["DataType"] = 8
		tLaborday2015_Strike_Stc[1][8154]["Data"] = 1

		tLaborday2015_Strike_Stc[1][8155] = {}
		tLaborday2015_Strike_Stc[1][8155]["EventType"] = 71
		tLaborday2015_Strike_Stc[1][8155]["DataType"] = 10
		tLaborday2015_Strike_Stc[1][8155]["Data"] = 1

		tLaborday2015_Strike_Stc[1][8156] = {}
		tLaborday2015_Strike_Stc[1][8156]["EventType"] = 71
		tLaborday2015_Strike_Stc[1][8156]["DataType"] = 13
		tLaborday2015_Strike_Stc[1][8156]["Data"] = 1

		tLaborday2015_Strike_Stc[1][8156]["EventType1"] = 71
		tLaborday2015_Strike_Stc[1][8156]["DataType1"] = 12
		tLaborday2015_Strike_Stc[1][8156]["Data1"] = 1

--第2阶段掩码
--EventType签名任务 72,6-72,9(4个npc单独完成掩码) 72,10(完成所有签名任务)
--EventType1表示4个npc单独的任务 1表示接任务，2表示完成
		tLaborday2015_Strike_Stc[2] = {}
		tLaborday2015_Strike_Stc[2][1] = {}
		tLaborday2015_Strike_Stc[2][1]["EventType"] = 72
		tLaborday2015_Strike_Stc[2][1]["DataType"] = 10
		tLaborday2015_Strike_Stc[2][1]["Data"] = 1

		tLaborday2015_Strike_Stc[2][8153] = {}
		tLaborday2015_Strike_Stc[2][8153]["EventType"] = 72
		tLaborday2015_Strike_Stc[2][8153]["DataType"] = 6
		tLaborday2015_Strike_Stc[2][8153]["Data"] = 1
		
		tLaborday2015_Strike_Stc[2][8153]["EventType1"] = 72
		tLaborday2015_Strike_Stc[2][8153]["DataType1"] = 11
		tLaborday2015_Strike_Stc[2][8153]["Data1"] = 1
		tLaborday2015_Strike_Stc[2][8153]["Data2"] = 2

		tLaborday2015_Strike_Stc[2][8154] = {}
		tLaborday2015_Strike_Stc[2][8154]["EventType"] = 72
		tLaborday2015_Strike_Stc[2][8154]["DataType"] = 7
		tLaborday2015_Strike_Stc[2][8154]["Data"] = 1

		tLaborday2015_Strike_Stc[2][8154]["EventType1"] = 72
		tLaborday2015_Strike_Stc[2][8154]["DataType1"] = 13
		tLaborday2015_Strike_Stc[2][8154]["Data1"] = 1
		tLaborday2015_Strike_Stc[2][8154]["Data2"] = 2

		tLaborday2015_Strike_Stc[2][8155] = {}
		tLaborday2015_Strike_Stc[2][8155]["EventType"] = 72
		tLaborday2015_Strike_Stc[2][8155]["DataType"] = 8
		tLaborday2015_Strike_Stc[2][8155]["Data"] = 1
		
		tLaborday2015_Strike_Stc[2][8155]["EventType1"] = 72
		tLaborday2015_Strike_Stc[2][8155]["DataType1"] = 15
		tLaborday2015_Strike_Stc[2][8155]["Data1"] = 1
		tLaborday2015_Strike_Stc[2][8155]["Data2"] = 2

		tLaborday2015_Strike_Stc[2][8156] = {}
		tLaborday2015_Strike_Stc[2][8156]["EventType"] = 72
		tLaborday2015_Strike_Stc[2][8156]["DataType"] = 9
		tLaborday2015_Strike_Stc[2][8156]["Data"] = 1
		
		tLaborday2015_Strike_Stc[2][8156]["EventType1"] = 72
		tLaborday2015_Strike_Stc[2][8156]["DataType1"] = 17
		tLaborday2015_Strike_Stc[2][8156]["Data1"] = 1
		tLaborday2015_Strike_Stc[2][8156]["Data2"] = 2

--第3阶段掩码
--对话任务4个npc4个掩码 1接任务，2完成与官员对话 3领取礼包
		tLaborday2015_Strike_Stc[3] = {}
		tLaborday2015_Strike_Stc[3][8153] = {}
		tLaborday2015_Strike_Stc[3][8153]["EventType"] = 72
		tLaborday2015_Strike_Stc[3][8153]["DataType"] = 19
		tLaborday2015_Strike_Stc[3][8153]["New"] = 1
		tLaborday2015_Strike_Stc[3][8153]["Data"] = 2
		tLaborday2015_Strike_Stc[3][8153]["Complete"] = 3

		tLaborday2015_Strike_Stc[3][8154] = {}
		tLaborday2015_Strike_Stc[3][8154]["EventType"] = 72
		tLaborday2015_Strike_Stc[3][8154]["DataType"] = 20
		tLaborday2015_Strike_Stc[3][8154]["New"] = 1
		tLaborday2015_Strike_Stc[3][8154]["Data"] = 2
		tLaborday2015_Strike_Stc[3][8154]["Complete"] = 3

		tLaborday2015_Strike_Stc[3][8155] = {}
		tLaborday2015_Strike_Stc[3][8155]["EventType"] = 72
		tLaborday2015_Strike_Stc[3][8155]["DataType"] = 22
		tLaborday2015_Strike_Stc[3][8155]["New"] = 1
		tLaborday2015_Strike_Stc[3][8155]["Data"] = 2
		tLaborday2015_Strike_Stc[3][8155]["Complete"] = 3

		tLaborday2015_Strike_Stc[3][8156] = {}
		tLaborday2015_Strike_Stc[3][8156]["EventType"] = 72
		tLaborday2015_Strike_Stc[3][8156]["DataType"] = 24
		tLaborday2015_Strike_Stc[3][8156]["New"] = 1
		tLaborday2015_Strike_Stc[3][8156]["Data"] = 2
		tLaborday2015_Strike_Stc[3][8156]["Complete"] = 3

--第4阶段掩码
--慰问劳工npc
		tLaborday2015_Strike_Stc[4] = {}
		tLaborday2015_Strike_Stc[4][8165] = {}
		tLaborday2015_Strike_Stc[4][8165]["EventType"] = 72
		tLaborday2015_Strike_Stc[4][8165]["DataType"] = 27
		tLaborday2015_Strike_Stc[4][8165]["Data6"] = 6

		tLaborday2015_Strike_Stc[4][8171] = {}
		tLaborday2015_Strike_Stc[4][8171]["EventType"] = 72
		tLaborday2015_Strike_Stc[4][8171]["DataType"] = 28
		tLaborday2015_Strike_Stc[4][8171]["Data6"] = 6

		tLaborday2015_Strike_Stc[4][8177] = {}
		tLaborday2015_Strike_Stc[4][8177]["EventType"] = 72
		tLaborday2015_Strike_Stc[4][8177]["DataType"] = 29
		tLaborday2015_Strike_Stc[4][8177]["Data6"] = 6

		tLaborday2015_Strike_Stc[4][8183] = {}
		tLaborday2015_Strike_Stc[4][8183]["EventType"] = 72
		tLaborday2015_Strike_Stc[4][8183]["DataType"] = 30
		tLaborday2015_Strike_Stc[4][8183]["Data6"] = 6

--礼花
		tLaborday2015_Strike_Stc[4][720789] = {}
		tLaborday2015_Strike_Stc[4][720789]["EventType"] = 72
		tLaborday2015_Strike_Stc[4][720789]["DataType"] = 27
		tLaborday2015_Strike_Stc[4][720789]["Data8"] = 8

		tLaborday2015_Strike_Stc[4][720812] = {}
		tLaborday2015_Strike_Stc[4][720812]["EventType"] = 72
		tLaborday2015_Strike_Stc[4][720812]["DataType"] = 28
		tLaborday2015_Strike_Stc[4][720812]["Data8"] = 8

		tLaborday2015_Strike_Stc[4][720813] = {}
		tLaborday2015_Strike_Stc[4][720813]["EventType"] = 72
		tLaborday2015_Strike_Stc[4][720813]["DataType"] = 29
		tLaborday2015_Strike_Stc[4][720813]["Data8"] = 8

		tLaborday2015_Strike_Stc[4][720814] = {}
		tLaborday2015_Strike_Stc[4][720814]["EventType"] = 72
		tLaborday2015_Strike_Stc[4][720814]["DataType"] = 30
		tLaborday2015_Strike_Stc[4][720814]["Data8"] = 8

--任务NPC 1-5 随机买物品任务 6-7慰问劳工任务 8-9燃放礼花
		tLaborday2015_Strike_Stc[4][8153] = {}
		tLaborday2015_Strike_Stc[4][8153]["EventType"] = 72
		tLaborday2015_Strike_Stc[4][8153]["DataType"] = 27
		tLaborday2015_Strike_Stc[4][8153]["Data1"] = 1
		tLaborday2015_Strike_Stc[4][8153]["Data4"] = 4
		tLaborday2015_Strike_Stc[4][8153]["Data5"] = 5
		tLaborday2015_Strike_Stc[4][8153]["Data6"] = 6
		tLaborday2015_Strike_Stc[4][8153]["Data7"] = 7
		tLaborday2015_Strike_Stc[4][8153]["Data8"] = 8
		tLaborday2015_Strike_Stc[4][8153]["Data9"] = 9

		tLaborday2015_Strike_Stc[4][8154] = {}
		tLaborday2015_Strike_Stc[4][8154]["EventType"] = 72
		tLaborday2015_Strike_Stc[4][8154]["DataType"] = 28
		tLaborday2015_Strike_Stc[4][8154]["Data1"] = 1
		tLaborday2015_Strike_Stc[4][8154]["Data4"] = 4
		tLaborday2015_Strike_Stc[4][8154]["Data5"] = 5
		tLaborday2015_Strike_Stc[4][8154]["Data6"] = 6
		tLaborday2015_Strike_Stc[4][8154]["Data7"] = 7
		tLaborday2015_Strike_Stc[4][8154]["Data8"] = 8
		tLaborday2015_Strike_Stc[4][8154]["Data9"] = 9

		tLaborday2015_Strike_Stc[4][8155] = {}
		tLaborday2015_Strike_Stc[4][8155]["EventType"] = 72
		tLaborday2015_Strike_Stc[4][8155]["DataType"] = 29
		tLaborday2015_Strike_Stc[4][8155]["Data1"] = 1
		tLaborday2015_Strike_Stc[4][8155]["Data4"] = 4
		tLaborday2015_Strike_Stc[4][8155]["Data5"] = 5
		tLaborday2015_Strike_Stc[4][8155]["Data6"] = 6
		tLaborday2015_Strike_Stc[4][8155]["Data7"] = 7
		tLaborday2015_Strike_Stc[4][8155]["Data8"] = 8
		tLaborday2015_Strike_Stc[4][8155]["Data9"] = 9

		tLaborday2015_Strike_Stc[4][8156] = {}
		tLaborday2015_Strike_Stc[4][8156]["EventType"] = 72
		tLaborday2015_Strike_Stc[4][8156]["DataType"] = 30
		tLaborday2015_Strike_Stc[4][8156]["Data1"] = 1
		tLaborday2015_Strike_Stc[4][8156]["Data4"] = 4
		tLaborday2015_Strike_Stc[4][8156]["Data5"] = 5
		tLaborday2015_Strike_Stc[4][8156]["Data6"] = 6
		tLaborday2015_Strike_Stc[4][8156]["Data7"] = 7
		tLaborday2015_Strike_Stc[4][8156]["Data8"] = 8
		tLaborday2015_Strike_Stc[4][8156]["Data9"] = 9

--领取双倍经验
		tLaborday2015_Strike_Stc[4][1] = {}
		tLaborday2015_Strike_Stc[4][1]["EventType"] = 72
		tLaborday2015_Strike_Stc[4][1]["DataType"] = 26
		tLaborday2015_Strike_Stc[4][1]["Data"] = 1

--?路地?
local	tLaborday2015_Strike_Pathfinding = {}
		tLaborday2015_Strike_Pathfinding[1] = {}
		tLaborday2015_Strike_Pathfinding[1]["MapId"] = 1002
		tLaborday2015_Strike_Pathfinding[1]["PosX"] = 295
		tLaborday2015_Strike_Pathfinding[1]["PosY"] = 385
		tLaborday2015_Strike_Pathfinding[1]["NpcId"] = 8152

		tLaborday2015_Strike_Pathfinding[2] = {}
		tLaborday2015_Strike_Pathfinding[2]["MapId"] = 1002
		tLaborday2015_Strike_Pathfinding[2]["PosX"] = 280
		tLaborday2015_Strike_Pathfinding[2]["PosY"] = 385
		tLaborday2015_Strike_Pathfinding[2]["NpcId"] = 8045

		tLaborday2015_Strike_Pathfinding[3] = {}
		tLaborday2015_Strike_Pathfinding[3]["MapId"] = 1002
		tLaborday2015_Strike_Pathfinding[3]["PosX"] = 290
		tLaborday2015_Strike_Pathfinding[3]["PosY"] = 385
		tLaborday2015_Strike_Pathfinding[3]["NpcId"] = 8047

--??投放地?
		tLaborday2015_Strike_Pathfinding[720787] = {}
		tLaborday2015_Strike_Pathfinding[720787]["MapId"] = 1002
		tLaborday2015_Strike_Pathfinding[720787]["PosX1"] = 300
		tLaborday2015_Strike_Pathfinding[720787]["PosX2"] = 320
		tLaborday2015_Strike_Pathfinding[720787]["PosY1"] = 270
		tLaborday2015_Strike_Pathfinding[720787]["PosY2"] = 290

--草料投放地?
		tLaborday2015_Strike_Pathfinding[720788] = {}
		tLaborday2015_Strike_Pathfinding[720788]["MapId"] = 1002
		tLaborday2015_Strike_Pathfinding[720788]["PosX1"] = 245
		tLaborday2015_Strike_Pathfinding[720788]["PosX2"] = 255
		tLaborday2015_Strike_Pathfinding[720788]["PosY1"] = 375
		tLaborday2015_Strike_Pathfinding[720788]["PosY2"] = 385

--礼花燃放位置
		tLaborday2015_Strike_Pathfinding[5] = {}
		tLaborday2015_Strike_Pathfinding[5]["MapId"] = 1002
		tLaborday2015_Strike_Pathfinding[5]["PosX1"] = 300
		tLaborday2015_Strike_Pathfinding[5]["PosX2"] = 320
		tLaborday2015_Strike_Pathfinding[5]["PosY1"] = 280
		tLaborday2015_Strike_Pathfinding[5]["PosY2"] = 300

		tLaborday2015_Strike_Pathfinding[8153] = {}
		tLaborday2015_Strike_Pathfinding[8153]["MapId"] = 1002
		tLaborday2015_Strike_Pathfinding[8153]["PosX"] = 310
		tLaborday2015_Strike_Pathfinding[8153]["PosY"] = 290
		
		tLaborday2015_Strike_Pathfinding[8154] = {}
		tLaborday2015_Strike_Pathfinding[8154]["MapId"] = 1002
		tLaborday2015_Strike_Pathfinding[8154]["PosX"] = 340
		tLaborday2015_Strike_Pathfinding[8154]["PosY"] = 380

		tLaborday2015_Strike_Pathfinding[8155] = {}
		tLaborday2015_Strike_Pathfinding[8155]["MapId"] = 1002
		tLaborday2015_Strike_Pathfinding[8155]["PosX"] = 340
		tLaborday2015_Strike_Pathfinding[8155]["PosY"] = 380

		tLaborday2015_Strike_Pathfinding[8156] = {}
		tLaborday2015_Strike_Pathfinding[8156]["MapId"] = 1006
		tLaborday2015_Strike_Pathfinding[8156]["PosX"] = 30
		tLaborday2015_Strike_Pathfinding[8156]["PosY"] = 30



local	tLaborday2015_Strike_log = {}
		tLaborday2015_Strike_log["FestivalId"] = 3436
		tLaborday2015_Strike_log["LogId"] = 10000241
		tLaborday2015_Strike_log[1] = "0,0,%d[%d],1[1],10000241,2,%d,1"
		tLaborday2015_Strike_log[2] = "0,0,720786,1,10000241,2,0,0"
		tLaborday2015_Strike_log[3] = "0,0,0,0,10000241,2,711293,1"
		tLaborday2015_Strike_log[4] = "0,0,0,0,10000241,2,720787,1"
		tLaborday2015_Strike_log[5] = "0,0,0,0,10000241,2,720788,1"
		tLaborday2015_Strike_log[6] = "0,0,%d,1,10000241,2,0,0"
		tLaborday2015_Strike_log[7] = "0,0,0,0,10000241,2,%d,1"



-------------------------------------------------??部分-------------------------------------------------

-------------------------------------------Npc-------------------------------------------
--常用??封?
--已完成
function Laborday2015_Strike_Text1(nNpcId)
	Sys_DialogText(tLaborday2015_Strike_Text["Text"][1])
	Sys_DialogOption(tLaborday2015_Strike_Text["Option"][1],"</F>NULL")
	Sys_DialogFace(nNpcId)
	Sys_DialogEnd()

end

--等???到
function Laborday2015_Strike_Text2(nNpcId)
	Sys_DialogText(tLaborday2015_Strike_Text["Text"][2])
	Sys_DialogOption(tLaborday2015_Strike_Text["Option"][2],"</F>NULL")
	Sys_DialogFace(nNpcId)
	Sys_DialogEnd()
	
end

--背包空??
function Laborday2015_Strike_Text3(nNpcId)
	Sys_DialogText(tLaborday2015_Strike_Text["Text"][3])
	Sys_DialogOption(tLaborday2015_Strike_Text["Option"][3],"</F>NULL")
	Sys_DialogFace(nNpcId)
	Sys_DialogEnd()
	
end

--工会的铁匠 工会的裁缝 工会的厨师 工会的马夫
function Laborday2015_Strike_Labor(nNpcId)
	local nNpcId = Get_NpcId()
	if not Sys_ChkFullTime(tLaborday2015_Strike_Time[4]) then
		local nNum = math.random(1,4)
		Sys_DialogText(tLaborday2015_Strike_Labor_Text["Text1"][nNum])
		Sys_DialogOption(tLaborday2015_Strike_Labor_Text["Option1"],"</F>NULL")
		Sys_DialogFace(nNpcId)
		Sys_DialogEnd()
	else
		Sys_DialogText(tLaborday2015_Strike_Labor_Text["Text2"])
		Sys_DialogOption(tLaborday2015_Strike_Labor_Text["Option2"],"</F>Laborday2015_Strike_Labor_Condolences</N>"..nNpcId)
		Sys_DialogOption(tLaborday2015_Strike_Labor_Text["Option3"],"</F>NULL")
		Sys_DialogFace(nNpcId)
		Sys_DialogEnd()
	end
end

--我来慰问大家了。
function Laborday2015_Strike_Labor_Condolences(nNpcId)
	for i = 1,4 do
		if nNpcId >=tLaborday2015_Strike_Cont["NpcId"]["Bef"][i] and nNpcId <= tLaborday2015_Strike_Cont["NpcId"]["Aft"][i] then
			nNpcId = tLaborday2015_Strike_Cont["NpcId"]["Bef"][i]
		end	
	end
	local sLog = string.format(tLaborday2015_Strike_log[6],tLaborday2015_Strike_Item[4][nNpcId])
	if Item_ChkItem(tLaborday2015_Strike_Item[4][nNpcId]) and Item_DelItem(tLaborday2015_Strike_Item[4][nNpcId]) then 
		Task_SetStatistic(tLaborday2015_Strike_Stc[4][nNpcId]["EventType"],tLaborday2015_Strike_Stc[4][nNpcId]["DataType"],tLaborday2015_Strike_Stc[4][nNpcId]["Data6"],1,0)
		Sys_SaveActionFestivalLog(tLaborday2015_Strike_log[6])
		User_TalkChannel2005(tLaborday2015_Strike_Labor_Text[nNpcId])
		return
	end

	Sys_DialogText(tLaborday2015_Strike_Labor_Text["Text3"])
	Sys_DialogOption(tLaborday2015_Strike_Labor_Text["Option4"],"</F>NULL")
	Sys_DialogFace(nNpcId)
	Sys_DialogEnd()

end

--官兵
function Laborday2015_Strike_Labor_Soldier(nNpcId)
	local nNpcId = Get_NpcId()
	local nNum = math.random(1,2)
	Sys_DialogText(tLaborday2015_Strike_Soldier_Text[nNum]["Text"])
	Sys_DialogOption(tLaborday2015_Strike_Soldier_Text[nNum]["Option"],"</F>NULL")
	Sys_DialogFace(nNpcId)
	Sys_DialogEnd()

end

--工会宣传大使
--接?路
function Laborday2015_Strike_Option6_8151(nNpcId,nOption)
	local nPosX = tLaborday2015_Strike_Pathfinding[nOption]["PosX"]
	local nPosY = tLaborday2015_Strike_Pathfinding[nOption]["PosY"]
	local nMapId = tLaborday2015_Strike_Pathfinding[nOption]["MapId"]
	local nTarget = tLaborday2015_Strike_Pathfinding[nOption]["NpcId"]
	Sys_GotoSomeWhere(nPosX,nPosY,nMapId,nTarget)
end

--会长何辛
function Laborday2015_Strike_Option2_8152(nNpcId)
	if Sys_ChkFullTime(tLaborday2015_Strike_Time["Beftime"]) then
		LinkNpcGossipFunc_New(nNpcId,"2-1")
		return
	end
	
	if Sys_ChkFullTime(tLaborday2015_Strike_Time[1]) then
		LinkNpcGossipFunc_New(nNpcId,"2-2")
		return
	end
	

	if Sys_ChkFullTime(tLaborday2015_Strike_Time[2]) then
		if not Task_ChkStcValue(tLaborday2015_Strike_Stc[2][1]["EventType"],tLaborday2015_Strike_Stc[2][1]["DataType"],">=",tLaborday2015_Strike_Stc[2][1]["Data"]) then
			LinkNpcGossipFunc_New(nNpcId,"3-1")
			return
		else
			LinkNpcGossipFunc_New(nNpcId,"3-8")
		
		end
	end
	
	if Sys_ChkFullTime(tLaborday2015_Strike_Time[3]) then
		LinkNpcGossipFunc_New(nNpcId,"4-1")
		return
	end

	if Sys_ChkFullTime(tLaborday2015_Strike_Time[4]) then
		LinkNpcGossipFunc_New(nNpcId,"6-1")
		return
	end
	
	if Sys_ChkFullTime(tLaborday2015_Strike_Time["Aftime"]) then
		LinkNpcGossipFunc_New(nNpcId,"8-1")
		return
	end

end

--交给我吧。
function Laborday2015_Strike_Option5_8152(nNpcId)
	if not User_JudgeLevelAndMetempsychosis(tLaborday2015_Strike_Cont["Level"],tLaborday2015_Strike_Cont["Metempsychosis"]) then
		LinkNpcGossipFunc_New(nNpcId,"3-2")
		return
	end
	
	if Item_ChkItem(tLaborday2015_Strike_Item[2][1]) then
		LinkNpcGossipFunc_New(nNpcId,"3-3")
		return
	end
	
	if not User_CheckLeftSpace(tLaborday2015_Strike_Cont["Space"]) then
		LinkNpcGossipFunc_New(nNpcId,"3-4")
		return
	end

	Item_AddItem(tLaborday2015_Strike_Item[2][1])
	Sys_SaveActionFestivalLog(tLaborday2015_Strike_log[3])
	User_TalkChannel2005(tLaborday2015_Strike_Text[1])

end

--上交签名表。
function Laborday2015_Strike_Option6_8152(nNpcId)
	if not Item_ChkItem(tLaborday2015_Strike_Item[2][1]) then
		LinkNpcGossipFunc_New(nNpcId,"3-5")
		return
	end

	if not Laborday2015_Strike_ChkattendanceSheet() then
		LinkNpcGossipFunc_New(nNpcId,"3-6")
		return
	end
	
	if Item_DelItem(tLaborday2015_Strike_Item[2][1]) then
		Task_SetStatistic(tLaborday2015_Strike_Stc[2][1]["EventType"],tLaborday2015_Strike_Stc[2][1]["DataType"],tLaborday2015_Strike_Stc[2][1]["Data"],1,0)
		LinkNpcGossipFunc_New(nNpcId,"3-7")
	end
end

--判??到表是否都?了
function Laborday2015_Strike_ChkattendanceSheet()
	for i = 8153,8156 do
		if not Task_ChkStcValue(tLaborday2015_Strike_Stc[2][i]["EventType"],tLaborday2015_Strike_Stc[2][i]["DataType"],">=",tLaborday2015_Strike_Stc[2][i]["Data"]) then
			return false
		end
	end
		return true
end

--?取?倍??
function Laborday2015_Strike_Option12_8152(nNpcId)
	if not User_JudgeLevelAndMetempsychosis(tLaborday2015_Strike_Cont["Level"],tLaborday2015_Strike_Cont["Metempsychosis"]) then
		LinkNpcGossipFunc_New(nNpcId,"3-2")
		return
	end

	if Task_ChkStcValue(tLaborday2015_Strike_Stc[4][1]["EventType"],tLaborday2015_Strike_Stc[4][1]["DataType"],">=",tLaborday2015_Strike_Stc[4][1]["Data"]) then
		LinkNpcGossipFunc_New(nNpcId,"8-3")
		return
	end

	Task_SetStatistic(tLaborday2015_Strike_Stc[4][1]["EventType"],tLaborday2015_Strike_Stc[4][1]["DataType"],tLaborday2015_Strike_Stc[4][1]["Data"],1,0)
	User_SetExpControl(tLaborday2015_Strike_Cont["Percent"],tLaborday2015_Strike_Cont["PercentTime"])
	User_TalkChannel2005(tLaborday2015_Strike_Text[2])

end

--官府老爷
function Laborday2015_Strike_Option2_8164(nNpcId)
	if not Sys_ChkFullTime(tLaborday2015_Strike_Time[3]) then
		LinkNpcGossipFunc_New(nNpcId,"1-1")
		return
	end

	for i=8153,8156 do
		if Task_ChkStcValue(tLaborday2015_Strike_Stc[3][i]["EventType"],tLaborday2015_Strike_Stc[3][i]["DataType"],"==",1) then
			Task_SetStatistic(tLaborday2015_Strike_Stc[3][i]["EventType"],tLaborday2015_Strike_Stc[3][i]["DataType"],tLaborday2015_Strike_Stc[3][i]["Data"],1,0)
			LinkNpcGossipFunc_New(nNpcId,"2-1")
			return
		end
	end
	
	LinkNpcGossipFunc_New(nNpcId,"1-1")
	
end

--壹堆草料
function Laborday2015_Strike_Grass()
	if not Sys_ChkFullTime(tLaborday2015_Strike_Time[2]) then
		return
	end

	if Item_ChkItem (tLaborday2015_Strike_Item[2][8156]) then
		User_TalkChannel2005(tLaborday2015_Strike_Text[3])
		return
	end

	if Task_StcInterval(tLaborday2015_Strike_Stc[2][8156]["EventType1"],tLaborday2015_Strike_Stc[2][8156]["DataType1"],1,4) then
		Task_SetStatistic(tLaborday2015_Strike_Stc[2][8156]["EventType1"],tLaborday2015_Strike_Stc[2][8156]["DataType1"],0,1,0)
		Task_SetStcTimestamp(tLaborday2015_Strike_Stc[2][8156]["EventType1"],tLaborday2015_Strike_Stc[2][8156]["DataType1"],0,0)
	end

	if Task_ChkStcValue(tLaborday2015_Strike_Stc[2][8156]["EventType1"],tLaborday2015_Strike_Stc[2][8156]["DataType1"],"==",tLaborday2015_Strike_Stc[2][8156]["Data1"]) then
		User_SetExplore(10,tLaborday2015_Strike_Text[5],100,"</F>Laborday2015_Strike_Grass1")
	end
	
end

function Laborday2015_Strike_Grass1()
	if not User_CheckLeftSpace(tLaborday2015_Strike_Cont["Space"]) then
		User_TalkChannel2005(tLaborday2015_Strike_Text[4])
		return
	end

	Item_AddItem(tLaborday2015_Strike_Item[2][8156])
	Sys_SaveActionFestivalLog(tLaborday2015_Strike_log[5])
	User_TalkChannel2005(tLaborday2015_Strike_Text[3])

end

--第1?段 
--有什么需要帮忙的？ 铁匠赵刚 裁缝惠娘 厨师冯善 马夫王宝(通用)
function Laborday2015_Strike_Option2_8153(nNpcId)
	if Task_StcInterval(tLaborday2015_Strike_Stc[1][nNpcId]["EventType"],tLaborday2015_Strike_Stc[1][nNpcId]["DataType"],1,4) then
		Task_SetStatistic(tLaborday2015_Strike_Stc[1][nNpcId]["EventType"],tLaborday2015_Strike_Stc[1][nNpcId]["DataType"],0,1,0)
		Task_SetStcTimestamp(tLaborday2015_Strike_Stc[1][nNpcId]["EventType"],tLaborday2015_Strike_Stc[1][nNpcId]["DataType"],0,0)
	end

	if Task_ChkStcValue(tLaborday2015_Strike_Stc[1][nNpcId]["EventType"],tLaborday2015_Strike_Stc[1][nNpcId]["DataType"],">=",tLaborday2015_Strike_Stc[1][nNpcId]["Data"]) then
		Laborday2015_Strike_Text1(nNpcId)
		return
	end

	if not User_JudgeLevelAndMetempsychosis(tLaborday2015_Strike_Cont["Level"],tLaborday2015_Strike_Cont["Metempsychosis"]) then
		Laborday2015_Strike_Text2(nNpcId)
		return
	end

	LinkNpcGossipFunc_New(nNpcId,"2-3")
end

--没问题。 铁匠赵刚 裁缝惠娘 厨师冯善(通用)
function Laborday2015_Strike_Option7_8153(nNpcId)
	if Item_ChkItem(tLaborday2015_Strike_Item[1][nNpcId][3]) then
		User_TalkChannel2005(tLaborday2015_Strike_Npc_Text[1][nNpcId][1])
		return
	end
	
	if not User_CheckLeftSpace(tLaborday2015_Strike_Cont["Space1"]) then
		Laborday2015_Strike_Text3(nNpcId)
		return
	end
	
	if not Item_ChkItem (tLaborday2015_Strike_Item[1][nNpcId][1]) then
		Item_AddItem(tLaborday2015_Strike_Item[1][nNpcId][1])
	end
	
	if not Item_ChkItem (tLaborday2015_Strike_Item[1][nNpcId][2]) then
		Item_AddItem(tLaborday2015_Strike_Item[1][nNpcId][2])
	end

	User_TalkChannel2005(tLaborday2015_Strike_Npc_Text[1][nNpcId][2])

end

--没问题。 马夫王宝
function Laborday2015_Strike_Option7_8156(nNpcId)
	if Task_ChkStcValue(tLaborday2015_Strike_Stc[1][nNpcId]["EventType1"],tLaborday2015_Strike_Stc[1][nNpcId]["DataType1"],">=",tLaborday2015_Strike_Stc[1][nNpcId]["Data1"]) then
		Laborday2015_Strike_Text1(nNpcId)
		return
	end

	if Item_ChkItem(tLaborday2015_Strike_Item[1][nNpcId][1]) then
		User_TalkChannel2005(tLaborday2015_Strike_Npc_Text[1][nNpcId][1])
		return
	end

	if not User_CheckLeftSpace(tLaborday2015_Strike_Cont["Space"]) then
		Laborday2015_Strike_Text3(nNpcId)
		return
	end

	Item_AddItem(tLaborday2015_Strike_Item[1][nNpcId][1])
	User_TalkChannel2005(tLaborday2015_Strike_Npc_Text[1][nNpcId][2])
	Sys_GotoSomeWhere(tLaborday2015_Strike_Pathfinding[8156]["PosX"],tLaborday2015_Strike_Pathfinding[8156]["PosY"],tLaborday2015_Strike_Pathfinding[8156]["MapId"])

end

--上交物品 铁匠赵刚 裁缝惠娘 厨师冯善(通用)
function Laborday2015_Strike_Option3_8153(nNpcId)
	if Task_StcInterval(tLaborday2015_Strike_Stc[1][nNpcId]["EventType"],tLaborday2015_Strike_Stc[1][nNpcId]["DataType"],1,4) then
		Task_SetStatistic(tLaborday2015_Strike_Stc[1][nNpcId]["EventType"],tLaborday2015_Strike_Stc[1][nNpcId]["DataType"],0,1,0)
		Task_SetStcTimestamp(tLaborday2015_Strike_Stc[1][nNpcId]["EventType"],tLaborday2015_Strike_Stc[1][nNpcId]["DataType"],0,0)
	end
	
	if Task_ChkStcValue(tLaborday2015_Strike_Stc[1][nNpcId]["EventType"],tLaborday2015_Strike_Stc[1][nNpcId]["DataType"],">=",tLaborday2015_Strike_Stc[1][nNpcId]["Data"]) then
		Laborday2015_Strike_Text1(nNpcId)
		return
	end

	if not Item_ChkItem (tLaborday2015_Strike_Item[1][nNpcId][3]) then
		LinkNpcGossipFunc_New(nNpcId,"2-5")
		return
	end

	if Item_DelItem(tLaborday2015_Strike_Item[1][nNpcId][3]) then
		Task_SetStatistic(tLaborday2015_Strike_Stc[1][nNpcId]["EventType"],tLaborday2015_Strike_Stc[1][nNpcId]["DataType"],tLaborday2015_Strike_Stc[1][nNpcId]["Data"],1,0)
		Task_SetStcTimestamp(tLaborday2015_Strike_Stc[1][nNpcId]["EventType"],tLaborday2015_Strike_Stc[1][nNpcId]["DataType"],0,0)
		FestivalGeneralPackage_GetGift(tLaborday2015_Strike_log["FestivalId"],tLaborday2015_Strike_log["LogId"])
		LinkNpcGossipFunc_New(nNpcId,"2-6")
	end
end

--上交物品 马夫王宝 (非通用)
function Laborday2015_Strike_Option3_8156(nNpcId)
	if Task_StcInterval(tLaborday2015_Strike_Stc[1][nNpcId]["EventType"],tLaborday2015_Strike_Stc[1][nNpcId]["DataType"],1,4) then
		Task_SetStatistic(tLaborday2015_Strike_Stc[1][nNpcId]["EventType"],tLaborday2015_Strike_Stc[1][nNpcId]["DataType"],0,1,0)
		Task_SetStcTimestamp(tLaborday2015_Strike_Stc[1][nNpcId]["EventType"],tLaborday2015_Strike_Stc[1][nNpcId]["DataType"],0,0)
	end

	if Task_ChkStcValue(tLaborday2015_Strike_Stc[1][nNpcId]["EventType"],tLaborday2015_Strike_Stc[1][nNpcId]["DataType"],">=",tLaborday2015_Strike_Stc[1][nNpcId]["Data"]) then
		Laborday2015_Strike_Text1(nNpcId)
		return
	end
	
	if not Task_ChkStcValue(tLaborday2015_Strike_Stc[1][nNpcId]["EventType1"],tLaborday2015_Strike_Stc[1][nNpcId]["DataType1"],">=",tLaborday2015_Strike_Stc[1][nNpcId]["Data1"]) then
		LinkNpcGossipFunc_New(nNpcId,"2-5")
		return
	end
	
	if not User_CheckLeftSpace(tLaborday2015_Strike_Cont["Space"]) then
		Laborday2015_Strike_Text3(nNpcId)
		return
	end

	Task_SetStatistic(tLaborday2015_Strike_Stc[1][nNpcId]["EventType"],tLaborday2015_Strike_Stc[1][nNpcId]["DataType"],tLaborday2015_Strike_Stc[1][nNpcId]["Data"],1,0)
	Task_SetStcTimestamp(tLaborday2015_Strike_Stc[1][nNpcId]["EventType"],tLaborday2015_Strike_Stc[1][nNpcId]["DataType"],0,0)
	Task_SetStatistic(tLaborday2015_Strike_Stc[1][nNpcId]["EventType1"],tLaborday2015_Strike_Stc[1][nNpcId]["DataType1"],0,1,0)
	FestivalGeneralPackage_GetGift(tLaborday2015_Strike_log["FestivalId"],tLaborday2015_Strike_log["LogId"])
	LinkNpcGossipFunc_New(nNpcId,"2-6")

end

--第2?段 
--会长让你在这表上签名。 (通用)
function Laborday2015_Strike_Option11_8153(nNpcId)
	if not Item_ChkItem (tLaborday2015_Strike_Item[2][1]) then
		LinkNpcGossipFunc_New(nNpcId,"3-5")
		return
	end
	Task_SetStatistic(tLaborday2015_Strike_Stc[2][nNpcId]["EventType"],tLaborday2015_Strike_Stc[2][nNpcId]["DataType"],tLaborday2015_Strike_Stc[2][nNpcId]["Data"],1,0)
	User_TalkChannel2005(tLaborday2015_Strike_Npc_Text[2][nNpcId][1])

end

--没问题。 铁匠赵刚 (非通用)
function Laborday2015_Strike_Option14_8153(nNpcId)
	if not User_JudgeLevelAndMetempsychosis(tLaborday2015_Strike_Cont["Level"],tLaborday2015_Strike_Cont["Metempsychosis"]) then
		Laborday2015_Strike_Text2(nNpcId)
		return
	end

	if Task_StcInterval(tLaborday2015_Strike_Stc[2][nNpcId]["EventType1"],tLaborday2015_Strike_Stc[2][nNpcId]["DataType1"],1,4) then
		Task_SetStatistic(tLaborday2015_Strike_Stc[2][nNpcId]["EventType1"],tLaborday2015_Strike_Stc[2][nNpcId]["DataType1"],0,1,0)
		Task_SetStcTimestamp(tLaborday2015_Strike_Stc[2][nNpcId]["EventType1"],tLaborday2015_Strike_Stc[2][nNpcId]["DataType1"],0,0)
	end

	if Task_ChkStcValue(tLaborday2015_Strike_Stc[2][nNpcId]["EventType1"],tLaborday2015_Strike_Stc[2][nNpcId]["DataType1"],">=",tLaborday2015_Strike_Stc[2][nNpcId]["Data2"]) then
		Laborday2015_Strike_Text1(nNpcId)
		return
	end

	if Item_ChkItem (tLaborday2015_Strike_Item[2][nNpcId]) then
		LinkNpcGossipFunc_New(nNpcId,"3-6")
		return
	end
	
	if not User_CheckLeftSpace(tLaborday2015_Strike_Cont["Space"]) then
		Laborday2015_Strike_Text3(nNpcId)
		return
	end

	Task_SetStatistic(tLaborday2015_Strike_Stc[2][nNpcId]["EventType1"],tLaborday2015_Strike_Stc[2][nNpcId]["DataType1"],tLaborday2015_Strike_Stc[2][nNpcId]["Data1"],1,0)
	Task_SetStcTimestamp(tLaborday2015_Strike_Stc[2][nNpcId]["EventType1"],tLaborday2015_Strike_Stc[2][nNpcId]["DataType1"],0,0)
	Item_AddItem(tLaborday2015_Strike_Item[2][nNpcId])
	Sys_SaveActionFestivalLog(tLaborday2015_Strike_log[4])
	User_TalkChannel2005(tLaborday2015_Strike_Npc_Text[2][nNpcId][2])
	Sys_GotoSomeWhere(tLaborday2015_Strike_Pathfinding[nNpcId]["PosX"],tLaborday2015_Strike_Pathfinding[nNpcId]["PosY"],tLaborday2015_Strike_Pathfinding[nNpcId]["MapId"])

end


--没问题。 裁缝惠娘 厨师冯善 马夫王宝(通用)
function Laborday2015_Strike_Option14_8154(nNpcId)
	if not User_JudgeLevelAndMetempsychosis(tLaborday2015_Strike_Cont["Level"],tLaborday2015_Strike_Cont["Metempsychosis"]) then
		Laborday2015_Strike_Text2(nNpcId)
		return
	end

	if Task_StcInterval(tLaborday2015_Strike_Stc[2][nNpcId]["EventType1"],tLaborday2015_Strike_Stc[2][nNpcId]["DataType1"],1,4) then
		Task_SetStatistic(tLaborday2015_Strike_Stc[2][nNpcId]["EventType1"],tLaborday2015_Strike_Stc[2][nNpcId]["DataType1"],0,1,0)
		Task_SetStcTimestamp(tLaborday2015_Strike_Stc[2][nNpcId]["EventType1"],tLaborday2015_Strike_Stc[2][nNpcId]["DataType1"],0,0)
	end

	if Task_ChkStcValue(tLaborday2015_Strike_Stc[2][nNpcId]["EventType1"],tLaborday2015_Strike_Stc[2][nNpcId]["DataType1"],">=",tLaborday2015_Strike_Stc[2][nNpcId]["Data2"]) then
		Laborday2015_Strike_Text1(nNpcId)
		return
	end

	if (nNpcId == 8154 or nNpcId == 8155) and Item_ChkItem(tLaborday2015_Strike_Item[2][nNpcId]) then
		Laborday2015_Strike_Option5_8154(nNpcId)
		return
	end
	
	if nNpcId == 8156 and (Item_ChkItem(tLaborday2015_Strike_Item[2][nNpcId]) or Task_ChkStcValue(tLaborday2015_Strike_Stc[2][nNpcId]["EventType1"],tLaborday2015_Strike_Stc[2][nNpcId]["DataType1"],">=",tLaborday2015_Strike_Stc[2][nNpcId]["Data2"])) then
		Laborday2015_Strike_Text1(nNpcId)
		return
	end
	
	Task_SetStatistic(tLaborday2015_Strike_Stc[2][nNpcId]["EventType1"],tLaborday2015_Strike_Stc[2][nNpcId]["DataType1"],tLaborday2015_Strike_Stc[2][nNpcId]["Data1"],1,0)
	Task_SetStcTimestamp(tLaborday2015_Strike_Stc[2][nNpcId]["EventType1"],tLaborday2015_Strike_Stc[2][nNpcId]["DataType1"],0,0)
	Sys_GotoSomeWhere(tLaborday2015_Strike_Pathfinding[nNpcId]["PosX"],tLaborday2015_Strike_Pathfinding[nNpcId]["PosY"],tLaborday2015_Strike_Pathfinding[nNpcId]["MapId"])
	
end

--上交布料 裁缝惠娘 厨师冯善(通用)
function Laborday2015_Strike_Option5_8154(nNpcId)
	if Task_StcInterval(tLaborday2015_Strike_Stc[2][nNpcId]["EventType1"],tLaborday2015_Strike_Stc[2][nNpcId]["DataType1"],1,4) then
		Task_SetStatistic(tLaborday2015_Strike_Stc[2][nNpcId]["EventType1"],tLaborday2015_Strike_Stc[2][nNpcId]["DataType1"],0,1,0)
		Task_SetStcTimestamp(tLaborday2015_Strike_Stc[2][nNpcId]["EventType1"],tLaborday2015_Strike_Stc[2][nNpcId]["DataType1"],0,0)
	end

	if Task_ChkStcValue(tLaborday2015_Strike_Stc[2][nNpcId]["EventType1"],tLaborday2015_Strike_Stc[2][nNpcId]["DataType1"],">=",tLaborday2015_Strike_Stc[2][nNpcId]["Data2"]) then
		Laborday2015_Strike_Text1(nNpcId)
		return
	end

	if not Item_ChkItem (tLaborday2015_Strike_Item[2][nNpcId]) then
		LinkNpcGossipFunc_New(nNpcId,"3-6")
		return
	end

	if Item_DelItem(tLaborday2015_Strike_Item[2][nNpcId]) then
		Task_SetStatistic(tLaborday2015_Strike_Stc[2][nNpcId]["EventType1"],tLaborday2015_Strike_Stc[2][nNpcId]["DataType1"],tLaborday2015_Strike_Stc[2][nNpcId]["Data2"],1,0)
		Task_SetStcTimestamp(tLaborday2015_Strike_Stc[2][nNpcId]["EventType1"],tLaborday2015_Strike_Stc[2][nNpcId]["DataType1"],0,0)
		FestivalGeneralPackage_GetGift(tLaborday2015_Strike_log["FestivalId"],tLaborday2015_Strike_log["LogId"])
	end

end

--第3?段
--需要我帮忙吗？(通用)
function Laborday2015_Strike_Option22_8153(nNpcId)
	if not User_JudgeLevelAndMetempsychosis(tLaborday2015_Strike_Cont["Level"],tLaborday2015_Strike_Cont["Metempsychosis"]) then
		Laborday2015_Strike_Text2(nNpcId)
		return
	end

	if Task_ChkStcValue(tLaborday2015_Strike_Stc[3][nNpcId]["EventType"],tLaborday2015_Strike_Stc[3][nNpcId]["DataType"],">=",tLaborday2015_Strike_Stc[3][nNpcId]["Complete"]) then
		Laborday2015_Strike_Text1(nNpcId)
		return
	end

	if Task_ChkStcValue(tLaborday2015_Strike_Stc[3][nNpcId]["EventType"],tLaborday2015_Strike_Stc[3][nNpcId]["DataType"],">=",tLaborday2015_Strike_Stc[3][nNpcId]["Data"]) then
		LinkNpcGossipFunc_New(nNpcId,"5-1")
		return
	end

	if Task_ChkStcValue(tLaborday2015_Strike_Stc[3][nNpcId]["EventType"],tLaborday2015_Strike_Stc[3][nNpcId]["DataType"],"==",tLaborday2015_Strike_Stc[3][nNpcId]["New"]) then
		LinkNpcGossipFunc_New(nNpcId,"4-2")
		return
	end
	
	local nTask = 0
	for i= 8153,8156 do
		if Task_ChkStcValue(tLaborday2015_Strike_Stc[3][i]["EventType"],tLaborday2015_Strike_Stc[3][i]["DataType"],"==",tLaborday2015_Strike_Stc[3][i]["New"]) or 
			Task_ChkStcValue(tLaborday2015_Strike_Stc[3][i]["EventType"],tLaborday2015_Strike_Stc[3][i]["DataType"],"==",tLaborday2015_Strike_Stc[3][i]["Data"]) then
			nTask = nTask + 1
		end
		if nTask >= 1 then 
			LinkNpcGossipFunc_New(nNpcId,"4-3")
			return
		end

	end

	local nNum = math.random(1,12)
		Sys_DialogText(tLaborday2015_Strike_Npc_Text[3][nNpcId]["Text1"][nNum])
		Sys_DialogText(tLaborday2015_Strike_Npc_Text[3][nNpcId]["Text2"][nNum])
		Sys_DialogOption(tLaborday2015_Strike_Npc_Text[3]["Option1"],"</F>Laborday2015_Strike_Npc_Text_Option1</N>"..nNpcId)
		Sys_DialogFace(nNpcId)
		Sys_DialogEnd()

end

--我帮你去提这要求。 (通用)
function Laborday2015_Strike_Npc_Text_Option1(nNpcId)

	Task_SetStatistic(tLaborday2015_Strike_Stc[3][nNpcId]["EventType"],tLaborday2015_Strike_Stc[3][nNpcId]["DataType"],tLaborday2015_Strike_Stc[3][nNpcId]["New"],1,0)
	
end

--你们的要求我已经告诉了官府。 (通用)
function Laborday2015_Strike_Option23_8153(nNpcId)
	if Task_ChkStcValue(tLaborday2015_Strike_Stc[3][nNpcId]["EventType"],tLaborday2015_Strike_Stc[3][nNpcId]["DataType"],"==",tLaborday2015_Strike_Stc[3][nNpcId]["Complete"]) then
		Laborday2015_Strike_Text1(nNpcId)
		return
	end

	if not Task_ChkStcValue(tLaborday2015_Strike_Stc[3][nNpcId]["EventType"],tLaborday2015_Strike_Stc[3][nNpcId]["DataType"],"==",tLaborday2015_Strike_Stc[3][nNpcId]["Data"]) then
		LinkNpcGossipFunc_New(nNpcId,"4-4")
		return
	end
		LinkNpcGossipFunc_New(nNpcId,"5-1")
end

--不必客气。 (通用)
function Laborday2015_Strike_Option28_8153(nNpcId)
	if not User_CheckLeftSpace(tLaborday2015_Strike_Cont["Space"]) then
		Laborday2015_Strike_Text3(nNpcId)
		return
	end

	Task_SetStatistic(tLaborday2015_Strike_Stc[3][nNpcId]["EventType"],tLaborday2015_Strike_Stc[3][nNpcId]["DataType"],tLaborday2015_Strike_Stc[3][nNpcId]["Complete"],1,0)
	FestivalGeneralPackage_GetGift(tLaborday2015_Strike_log["FestivalId"],tLaborday2015_Strike_log["LogId"])

end

--第4?段
--我还能为你做点什么？(通用)
function Laborday2015_Strike_Option30_8153(nNpcId)
	if not User_JudgeLevelAndMetempsychosis(tLaborday2015_Strike_Cont["Level"],tLaborday2015_Strike_Cont["Metempsychosis"]) then
		Laborday2015_Strike_Text2(nNpcId)
		return
	end
	
	if Task_ChkStcValue(tLaborday2015_Strike_Stc[4][nNpcId]["EventType"],tLaborday2015_Strike_Stc[4][nNpcId]["DataType"],"==",0) then
		LinkNpcGossipFunc_New(nNpcId,"5-2")
		return
	end
	
	if Task_ChkStcValue(tLaborday2015_Strike_Stc[4][nNpcId]["EventType"],tLaborday2015_Strike_Stc[4][nNpcId]["DataType"],">=",tLaborday2015_Strike_Stc[4][nNpcId]["Data1"]) and 
		Task_ChkStcValue(tLaborday2015_Strike_Stc[4][nNpcId]["EventType"],tLaborday2015_Strike_Stc[4][nNpcId]["DataType"],"<=",tLaborday2015_Strike_Stc[4][nNpcId]["Data4"]) then
		LinkNpcGossipFunc_New(nNpcId,"5-3")
		return
	end

	if Task_ChkStcValue(tLaborday2015_Strike_Stc[4][nNpcId]["EventType"],tLaborday2015_Strike_Stc[4][nNpcId]["DataType"],">=",tLaborday2015_Strike_Stc[4][nNpcId]["Data5"]) and 
		Task_ChkStcValue(tLaborday2015_Strike_Stc[4][nNpcId]["EventType"],tLaborday2015_Strike_Stc[4][nNpcId]["DataType"],"<=",tLaborday2015_Strike_Stc[4][nNpcId]["Data6"]) then
		LinkNpcGossipFunc_New(nNpcId,"5-4")
		return
	end
	
	if Task_ChkStcValue(tLaborday2015_Strike_Stc[4][nNpcId]["EventType"],tLaborday2015_Strike_Stc[4][nNpcId]["DataType"],">=",tLaborday2015_Strike_Stc[4][nNpcId]["Data7"]) and 
		Task_ChkStcValue(tLaborday2015_Strike_Stc[4][nNpcId]["EventType"],tLaborday2015_Strike_Stc[4][nNpcId]["DataType"],"<=",tLaborday2015_Strike_Stc[4][nNpcId]["Data8"]) then
		LinkNpcGossipFunc_New(nNpcId,"5-5")
		return
	end

	if Task_ChkStcValue(tLaborday2015_Strike_Stc[4][nNpcId]["EventType"],tLaborday2015_Strike_Stc[4][nNpcId]["DataType"],"==",tLaborday2015_Strike_Stc[4][nNpcId]["Data9"]) then
		Laborday2015_Strike_Text1(nNpcId)
	end

end

--没问题。?物品 (通用)
function Laborday2015_Strike_Option31_8153(nNpcId)
	local nNum = math.random(1,4)
		Task_SetStatistic(tLaborday2015_Strike_Stc[4][nNpcId]["EventType"],tLaborday2015_Strike_Stc[4][nNpcId]["DataType"],nNum,1,0)
		Sys_DialogText(tLaborday2015_Strike_Npc_Text[4][nNpcId]["Text1"][nNum])
		Sys_DialogOption(tLaborday2015_Strike_Npc_Text[4]["Option1"],"</F>NULL")
		Sys_DialogFace(nNpcId)
		Sys_DialogEnd()

end

--我把武器带来了。 (通用)
function Laborday2015_Strike_Option33_8153(nNpcId)
	local nStc = Get_UserStatisticValue(tLaborday2015_Strike_Stc[4][nNpcId]["EventType"],tLaborday2015_Strike_Stc[4][nNpcId]["DataType"])
	if not Item_ChkItem (tLaborday2015_Strike_Item[4][nNpcId][nStc]) then
		Sys_DialogText(tLaborday2015_Strike_Npc_Text[4][nNpcId]["Text2"][nStc])
		Sys_DialogOption(tLaborday2015_Strike_Npc_Text[4]["Option1"],"</F>NULL")
		Sys_DialogFace(nNpcId)
		Sys_DialogEnd()
		return
	end

	local sLog = string.format(tLaborday2015_Strike_log[6],tLaborday2015_Strike_Item[4][nNpcId][nStc])
	if Item_DelItem(tLaborday2015_Strike_Item[4][nNpcId][nStc]) then
		Task_SetStatistic(tLaborday2015_Strike_Stc[4][nNpcId]["EventType"],tLaborday2015_Strike_Stc[4][nNpcId]["DataType"],tLaborday2015_Strike_Stc[4][nNpcId]["Data5"],1,0)
		Sys_SaveActionFestivalLog(tLaborday2015_Strike_log[6])
		Sys_DialogText(tLaborday2015_Strike_Npc_Text[4][nNpcId]["Text7"])
		Sys_DialogOption(tLaborday2015_Strike_Npc_Text[4]["Option2"],"</F>Laborday2015_Strike_Option33_8153_1</N>"..nNpcId)
		Sys_DialogFace(nNpcId)
		Sys_DialogEnd()
	end

end

function Laborday2015_Strike_Option33_8153_1(nNpcId)
	LinkNpcGossipFunc_New(nNpcId,"5-4")
end

--没问题。慰??工 (通用)
function Laborday2015_Strike_Option35_8153(nNpcId)
	if not Item_ChkItem (tLaborday2015_Strike_Item[4][nNpcId][5]) then
		if not User_CheckLeftSpace(tLaborday2015_Strike_Cont["Space"]) then
			Laborday2015_Strike_Text3(nNpcId)
			return
		end
		Item_AddItem(tLaborday2015_Strike_Item[4][nNpcId][5])
	end
		User_TalkChannel2005(tLaborday2015_Strike_Npc_Text[4][nNpcId]["Text3"])

end

--我已经送到了。 (通用)
function Laborday2015_Strike_Option36_8153(nNpcId)
	if not Task_ChkStcValue(tLaborday2015_Strike_Stc[4][nNpcId]["EventType"],tLaborday2015_Strike_Stc[4][nNpcId]["DataType"],"==",tLaborday2015_Strike_Stc[4][nNpcId]["Data6"]) then
		Sys_DialogText(tLaborday2015_Strike_Npc_Text[4][nNpcId]["Text4"])
		Sys_DialogOption(tLaborday2015_Strike_Npc_Text[4]["Option1"],"</F>NULL")
		Sys_DialogFace(nNpcId)
		Sys_DialogEnd()
		return
	end
	
	if not User_CheckLeftSpace(tLaborday2015_Strike_Cont["Space"]) then
		Laborday2015_Strike_Text3(nNpcId)
		return
	end

	Task_SetStatistic(tLaborday2015_Strike_Stc[4][nNpcId]["EventType"],tLaborday2015_Strike_Stc[4][nNpcId]["DataType"],tLaborday2015_Strike_Stc[4][nNpcId]["Data7"],1,0)
	LinkNpcGossipFunc_New(nNpcId,"5-5")

end

--好，把礼花给我吧。 (通用)
function Laborday2015_Strike_Option38_8153(nNpcId)
	if not Item_ChkItem (tLaborday2015_Strike_Item[4][nNpcId][6]) then
		if not User_CheckLeftSpace(tLaborday2015_Strike_Cont["Space"]) then
			Laborday2015_Strike_Text3(nNpcId)
			return
		end
		local sLog = string.format(tLaborday2015_Strike_log[7],tLaborday2015_Strike_Item[4][nNpcId][6])
		Item_AddItem(tLaborday2015_Strike_Item[4][nNpcId][6])
		Sys_SaveActionFestivalLog(tLaborday2015_Strike_log[7])
	end
		User_TalkChannel2005(tLaborday2015_Strike_Npc_Text[4][nNpcId]["Text5"])
		Sys_GotoSomeWhere(tLaborday2015_Strike_Pathfinding[8153]["PosX"],tLaborday2015_Strike_Pathfinding[8153]["PosY"],tLaborday2015_Strike_Pathfinding[8153]["MapId"])

end

--我已经燃放了。 (通用)
function Laborday2015_Strike_Option39_8153(nNpcId)
	if not Task_ChkStcValue(tLaborday2015_Strike_Stc[4][nNpcId]["EventType"],tLaborday2015_Strike_Stc[4][nNpcId]["DataType"],"==",tLaborday2015_Strike_Stc[4][nNpcId]["Data8"]) then
		Sys_DialogText(tLaborday2015_Strike_Npc_Text[4][nNpcId]["Text6"])
		Sys_DialogOption(tLaborday2015_Strike_Npc_Text[4]["Option1"],"</F>NULL")
		Sys_DialogFace(nNpcId)
		Sys_DialogEnd()
		return
	end
	
	if not User_CheckLeftSpace(tLaborday2015_Strike_Cont["Space"]) then
		Laborday2015_Strike_Text3(nNpcId)
		return
	end
	
	Task_SetStatistic(tLaborday2015_Strike_Stc[4][nNpcId]["EventType"],tLaborday2015_Strike_Stc[4][nNpcId]["DataType"],tLaborday2015_Strike_Stc[4][nNpcId]["Data9"],1,0)
	FestivalGeneralPackage_GetGift(tLaborday2015_Strike_log["FestivalId"],tLaborday2015_Strike_log["LogId"])

end

-------------------------------------------物品-------------------------------------------

--钝掉的钢刀，磨刀石，裁剪好的衣服，云石扣子，米酒，果酒
function Laborday2015_Strike_TaskItem1(nItemId)
	local nItemId = Get_ItemType()
		User_SetExplore(10,tLaborday2015_Strike_Npc_Text[1][nItemId],100,"</F>Laborday2015_Strike_TaskItem1_1</N>"..nItemId)
end

--??成功
function Laborday2015_Strike_TaskItem1_1(nItemId)
	for i = 8153,8155 do
		if nItemId == tLaborday2015_Strike_Item[1][i][1] or nItemId == tLaborday2015_Strike_Item[1][i][2] then
			if not Item_ChkItem (tLaborday2015_Strike_Item[1][i][1]) then
				User_TalkChannel2005(tLaborday2015_Strike_Npc_Text[1][i][3])
				return
			end

			if not Item_ChkItem (tLaborday2015_Strike_Item[1][i][2]) then
				User_TalkChannel2005(tLaborday2015_Strike_Npc_Text[1][i][4])
				return
			end

			local sLog = string.format(tLaborday2015_Strike_log[1],tLaborday2015_Strike_Item[1][i][1],tLaborday2015_Strike_Item[1][i][2],tLaborday2015_Strike_Item[1][i][3])
			if Item_DelItem(tLaborday2015_Strike_Item[1][i][1]) and Item_DelItem(tLaborday2015_Strike_Item[1][i][2]) then
				Item_AddItem(tLaborday2015_Strike_Item[1][i][3])
				Sys_SaveActionFestivalLog(sLog)
				User_TalkChannel2005(tLaborday2015_Strike_Npc_Text[1][i][5])
				return
			end
		end	
	end

end

--壹份草料
function Laborday2015_Strike_TaskItem2()
	local nMapId = Get_UserMapId()
	if nMapId ~= tLaborday2015_Strike_Pathfinding[8156]["MapId"] then
		Sys_GotoSomeWhere(tLaborday2015_Strike_Pathfinding[8156]["PosX"],tLaborday2015_Strike_Pathfinding[8156]["PosY"],tLaborday2015_Strike_Pathfinding[8156]["MapId"])
		return
	end

	User_SetExplore(10,tLaborday2015_Strike_Npc_Text[1][720786],100,"</F>Laborday2015_Strike_TaskItem2_1")

end

function Laborday2015_Strike_TaskItem2_1()
	if not Item_ChkItem (tLaborday2015_Strike_Item[1][8156][1]) then
		User_TalkChannel2005(tLaborday2015_Strike_Npc_Text[1][8156][3])
		return
	end
	
	if Item_DelItem(tLaborday2015_Strike_Item[1][8156][1]) then
		Task_SetStatistic(tLaborday2015_Strike_Stc[1][8156]["EventType1"],tLaborday2015_Strike_Stc[1][8156]["DataType1"],tLaborday2015_Strike_Stc[1][8156]["Data1"],1,0)
		Sys_SaveActionFestivalLog(tLaborday2015_Strike_log[2])
		User_TalkChannel2005(tLaborday2015_Strike_Npc_Text[1][8156][4])
		return
	end

end

--壹叠传单 壹袋草料
function Laborday2015_Strike_TaskItem3(nItemId)
	local nMapId = Get_UserMapId()
	local nUser_X = Get_UserPositionX()
	local nUser_Y = Get_UserPositionY()
	local nItemId = Get_ItemType()

	if nMapId ~= tLaborday2015_Strike_Pathfinding[nItemId]["MapId"] or 
		(nUser_X < tLaborday2015_Strike_Pathfinding[nItemId]["PosX1"] or nUser_X > tLaborday2015_Strike_Pathfinding[nItemId]["PosX2"]) or 
		(nUser_Y < tLaborday2015_Strike_Pathfinding[nItemId]["PosY1"] or nUser_Y > tLaborday2015_Strike_Pathfinding[nItemId]["PosY2"]) then
		User_TalkChannel2005(tLaborday2015_Strike_Npc_Text[2][nItemId][1])
		return
	end
	User_SetExplore(10,tLaborday2015_Strike_Npc_Text[2][nItemId][2],100,"</F>Laborday2015_Strike_TaskItem3_1</N>"..nItemId)

end

function Laborday2015_Strike_TaskItem3_1(nItemId)
	local nNpcId = nItemId

	if nNpcId == tLaborday2015_Strike_Item[2][8153] then 
		nNpcId = 8153
	end

	if nNpcId == tLaborday2015_Strike_Item[2][8156] then 
		nNpcId = 8156
	end

	if Task_StcInterval(tLaborday2015_Strike_Stc[2][nNpcId]["EventType1"],tLaborday2015_Strike_Stc[2][nNpcId]["DataType1"],1,4) then
		Task_SetStatistic(tLaborday2015_Strike_Stc[2][nNpcId]["EventType1"],tLaborday2015_Strike_Stc[2][nNpcId]["DataType1"],0,1,0)
		Task_SetStcTimestamp(tLaborday2015_Strike_Stc[2][nNpcId]["EventType1"],tLaborday2015_Strike_Stc[2][nNpcId]["DataType1"],0,0)
	end

	if Task_ChkStcValue(tLaborday2015_Strike_Stc[2][nNpcId]["EventType1"],tLaborday2015_Strike_Stc[2][nNpcId]["DataType1"],">=",tLaborday2015_Strike_Stc[2][nNpcId]["Data2"]) then
		User_TalkChannel2005(tLaborday2015_Strike_Npc_Text[2][nItemId][4])
		return
	end

	if not Item_ChkItem (tLaborday2015_Strike_Item[2][nNpcId]) then
		User_TalkChannel2005(tLaborday2015_Strike_Npc_Text[2][nItemId][3])
		return
	end

	if Item_DelItem(tLaborday2015_Strike_Item[2][nNpcId]) then
		Task_SetStatistic(tLaborday2015_Strike_Stc[2][nNpcId]["EventType1"],tLaborday2015_Strike_Stc[2][nNpcId]["DataType1"],tLaborday2015_Strike_Stc[2][nNpcId]["Data2"],1,0)
		Task_SetStcTimestamp(tLaborday2015_Strike_Stc[2][nNpcId]["EventType1"],tLaborday2015_Strike_Stc[2][nNpcId]["DataType1"],0,0)
		FestivalGeneralPackage_GetGift(tLaborday2015_Strike_log["FestivalId"],tLaborday2015_Strike_log["LogId"])
		return
	end

end

--团结礼花 友谊礼花 多彩礼花 幸福礼花
function Laborday2015_Strike_TaskItem4()
	local nItemId = Get_ItemType()
	local nMapId = Get_UserMapId()
	local nUser_X = Get_UserPositionX()
	local nUser_Y = Get_UserPositionY()
	if nMapId ~= tLaborday2015_Strike_Pathfinding[5]["MapId"] or 
		(nUser_X < tLaborday2015_Strike_Pathfinding[5]["PosX1"] or nUser_X > tLaborday2015_Strike_Pathfinding[5]["PosX2"]) or 
		(nUser_Y < tLaborday2015_Strike_Pathfinding[5]["PosY1"] or nUser_Y > tLaborday2015_Strike_Pathfinding[5]["PosY2"]) then
		User_TalkChannel2005(tLaborday2015_Strike_Text[6])
		return
	end

	if Item_ChkItem(nItemId) and Item_DelItem(nItemId) then
		Map_FireWorks()
		Task_SetStatistic(tLaborday2015_Strike_Stc[4][nItemId]["EventType"],tLaborday2015_Strike_Stc[4][nItemId]["DataType"],tLaborday2015_Strike_Stc[4][nItemId]["Data8"],1,0)
		User_TalkChannel2005(tLaborday2015_Strike_Text[7])
	end

end


function tLaborday2015_Strike_Monster()
	if Sys_ChkFullTime(tLaborday2015_Strike_Time[2]) then
		for i = 8154,8155 do
			if Task_ChkStcValue(tLaborday2015_Strike_Stc[2][i]["EventType1"],tLaborday2015_Strike_Stc[2][i]["DataType1"],"==",tLaborday2015_Strike_Stc[2][i]["Data1"]) then
				if not Item_ChkItem(tLaborday2015_Strike_Item[2][i]) then
					if not User_CheckLeftSpace(tLaborday2015_Strike_Cont["Space"]) then
						User_TalkChannel2005(tLaborday2015_Strike_Npc_Text[2][i][2])
						return
					else
						Item_AddItem(tLaborday2015_Strike_Item[2][i])
						User_TalkChannel2005(tLaborday2015_Strike_Npc_Text[2][i][3])
					end	
				end
			end	
		end	
	end	
end	

-------------------------------------------------NPC模板部分-------------------------------------------------
--其他NPC
tNpcFace[309] = 66
tNpcFace[310] = 178
tNpcFace[311] = 18
tNpcFace[312] = 48
tNpcFace[313] = 97

--工会宣传大使
tNpcFace[210] = 26
tNpcGossip[8151] = tNpcGossip[8151] or DefaultNpc:new{}
tNpcGossip[8151]["OptionHidden"] = 1

--活?前后
tNpcGossip[8151]["Text1-1"] = {111,112,113}
tNpcGossip[8151]["Text111"] = tLaborday2015_Strike_Text[8151]["Text111"]
tNpcGossip[8151]["Text112"] = tLaborday2015_Strike_Text[8151]["Text112"]
tNpcGossip[8151]["Text113"] = tLaborday2015_Strike_Text[8151]["Text113"]
tNpcGossip[8151]["tOption1-1"] = {1}
tNpcGossip[8151]["Option1"] = tLaborday2015_Strike_Text[8151]["Option1"]
tNpcGossip[8151]["ChkFunc1-1"] = function ()
	if Sys_ChkFullTime(tLaborday2015_Strike_Time["Beftime"]) or Sys_ChkFullTime(tLaborday2015_Strike_Time["Aftime"]) then
		return true
	end
		return false
end 

--活?中
tNpcGossip[8151]["Text1-2"] = {111,112,113}
tNpcGossip[8151]["tOption1-2"] = {2,3,4,5}
tNpcGossip[8151]["Option2"] = tLaborday2015_Strike_Text[8151]["Option2"]
tNpcGossip[8151]["Option3"] = tLaborday2015_Strike_Text[8151]["Option3"]
tNpcGossip[8151]["Option4"] = tLaborday2015_Strike_Text[8151]["Option4"]
tNpcGossip[8151]["Option5"] = tLaborday2015_Strike_Text[8151]["Option5"]
tNpcGossip[8151]["ChkFunc1-2"] = function ()
	return Sys_ChkFullTime(tLaborday2015_Strike_Time["Nowtime"])
end
tNpcGossip[8151]["OptionPoint2"]="2"
tNpcGossip[8151]["OptionPoint3"]="3"
tNpcGossip[8151]["OptionPoint4"]="4"

--了解劳工大罢工活动。
tNpcGossip[8151]["Text2-1"] = {211,212,213}
tNpcGossip[8151]["tOption2-1"] = {6,7}
tNpcGossip[8151]["Text211"] = tLaborday2015_Strike_Text[8151]["Text211"]
tNpcGossip[8151]["Text212"] = tLaborday2015_Strike_Text[8151]["Text212"]
tNpcGossip[8151]["Text213"] = tLaborday2015_Strike_Text[8151]["Text213"]
tNpcGossip[8151]["Option6"] = tLaborday2015_Strike_Text[8151]["Option6"]
tNpcGossip[8151]["Option7"] = tLaborday2015_Strike_Text[8151]["Option7"]
tNpcGossip[8151]["OptionFunc6"]="Laborday2015_Strike_Option6_8151</N>8151</N>1"
tNpcGossip[8151]["OptionPoint7"]="1"

tNpcGossip[8151]["Text3-1"] = {311,312}
tNpcGossip[8151]["tOption3-1"] = {8,7}
tNpcGossip[8151]["Text311"] = tLaborday2015_Strike_Text[8151]["Text311"]
tNpcGossip[8151]["Text312"] = tLaborday2015_Strike_Text[8151]["Text312"]
tNpcGossip[8151]["Option8"] = tLaborday2015_Strike_Text[8151]["Option8"]
tNpcGossip[8151]["OptionFunc8"]="Laborday2015_Strike_Option6_8151</N>8151</N>2"

tNpcGossip[8151]["Text4-1"] = {411,412}
tNpcGossip[8151]["tOption4-1"] = {9,7}
tNpcGossip[8151]["Text411"] = tLaborday2015_Strike_Text[8151]["Text411"]
tNpcGossip[8151]["Text412"] = tLaborday2015_Strike_Text[8151]["Text412"]
tNpcGossip[8151]["Option9"] = tLaborday2015_Strike_Text[8151]["Option9"]
tNpcGossip[8151]["OptionFunc9"]="Laborday2015_Strike_Option6_8151</N>8151</N>3"

--会长何辛
tNpcFace[211] = 27
tNpcGossip[8152] = tNpcGossip[8152] or DefaultNpc:new{}
tNpcGossip[8152]["OptionHidden"] = 1

tNpcGossip[8152]["Text1-1"] = {111,112}
tNpcGossip[8152]["Text111"] = tLaborday2015_Strike_Text[8152]["Text111"]
tNpcGossip[8152]["Text112"] = tLaborday2015_Strike_Text[8152]["Text112"]
tNpcGossip[8152]["tOption1-1"] = {1,2}
tNpcGossip[8152]["Option1"] = tLaborday2015_Strike_Text[8152]["Option1"]
tNpcGossip[8152]["Option2"] = tLaborday2015_Strike_Text[8152]["Option2"]
tNpcGossip[8152]["OptionFunc1"]="Laborday2015_Strike_Option2_8152</N>8152"

tNpcGossip[8152]["Text2-1"] = {211,212}
tNpcGossip[8152]["Text211"] = tLaborday2015_Strike_Text[8152]["Text211"]
tNpcGossip[8152]["Text212"] = tLaborday2015_Strike_Text[8152]["Text212"]
tNpcGossip[8152]["tOption2-1"] = {3}
tNpcGossip[8152]["Option3"] = tLaborday2015_Strike_Text[8152]["Option3"]

tNpcGossip[8152]["Text2-2"] = {221,222}
tNpcGossip[8152]["Text221"] = tLaborday2015_Strike_Text[8152]["Text221"]
tNpcGossip[8152]["Text222"] = tLaborday2015_Strike_Text[8152]["Text222"]
tNpcGossip[8152]["tOption2-2"] = {4}
tNpcGossip[8152]["Option4"] = tLaborday2015_Strike_Text[8152]["Option4"] 

tNpcGossip[8152]["Text3-1"] = {311,312}
tNpcGossip[8152]["Text311"] = tLaborday2015_Strike_Text[8152]["Text311"]
tNpcGossip[8152]["Text312"] = tLaborday2015_Strike_Text[8152]["Text312"]
tNpcGossip[8152]["tOption3-1"] = {5,6,7}
tNpcGossip[8152]["Option5"] = tLaborday2015_Strike_Text[8152]["Option5"]
tNpcGossip[8152]["Option6"] = tLaborday2015_Strike_Text[8152]["Option6"]
tNpcGossip[8152]["Option7"] = tLaborday2015_Strike_Text[8152]["Option7"]
tNpcGossip[8152]["OptionFunc5"]="Laborday2015_Strike_Option5_8152</N>8152"
tNpcGossip[8152]["OptionFunc6"]="Laborday2015_Strike_Option6_8152</N>8152"

tNpcGossip[8152]["Text3-2"] = {321}
tNpcGossip[8152]["Text321"] = tLaborday2015_Strike_Text[8152]["Text321"]
tNpcGossip[8152]["tOption3-2"] = {20}
tNpcGossip[8152]["Option20"] = tLaborday2015_Strike_Text[8152]["Option20"]

tNpcGossip[8152]["Text3-3"] = {331}
tNpcGossip[8152]["Text331"] = tLaborday2015_Strike_Text[8152]["Text331"]
tNpcGossip[8152]["tOption3-3"] = {21}
tNpcGossip[8152]["Option21"] = tLaborday2015_Strike_Text[8152]["Option21"]

tNpcGossip[8152]["Text3-4"] = {341}
tNpcGossip[8152]["Text341"] = tLaborday2015_Strike_Text[8152]["Text341"]
tNpcGossip[8152]["tOption3-4"] = {22}
tNpcGossip[8152]["Option22"] = tLaborday2015_Strike_Text[8152]["Option22"]

tNpcGossip[8152]["Text3-5"] = {351}
tNpcGossip[8152]["Text351"] = tLaborday2015_Strike_Text[8152]["Text351"]
tNpcGossip[8152]["tOption3-5"] = {23}
tNpcGossip[8152]["Option23"] = tLaborday2015_Strike_Text[8152]["Option23"]

tNpcGossip[8152]["Text3-6"] = {361,362}
tNpcGossip[8152]["Text361"] = tLaborday2015_Strike_Text[8152]["Text361"]
tNpcGossip[8152]["Text362"] = tLaborday2015_Strike_Text[8152]["Text362"]
tNpcGossip[8152]["tOption3-6"] = {24}
tNpcGossip[8152]["Option24"] = tLaborday2015_Strike_Text[8152]["Option24"]

tNpcGossip[8152]["Text3-7"] = {371,372}
tNpcGossip[8152]["Text371"] = tLaborday2015_Strike_Text[8152]["Text371"]
tNpcGossip[8152]["Text372"] = tLaborday2015_Strike_Text[8152]["Text372"]
tNpcGossip[8152]["tOption3-7"] = {25}
tNpcGossip[8152]["Option25"] = tLaborday2015_Strike_Text[8152]["Option25"]

tNpcGossip[8152]["Text3-8"] = {381,382}
tNpcGossip[8152]["Text381"] = tLaborday2015_Strike_Text[8152]["Text381"]
tNpcGossip[8152]["Text382"] = tLaborday2015_Strike_Text[8152]["Text382"]
tNpcGossip[8152]["tOption3-8"] = {26}
tNpcGossip[8152]["Option26"] = tLaborday2015_Strike_Text[8152]["Option26"]


tNpcGossip[8152]["Text4-1"] = {411,412}
tNpcGossip[8152]["Text411"] = tLaborday2015_Strike_Text[8152]["Text411"]
tNpcGossip[8152]["Text412"] = tLaborday2015_Strike_Text[8152]["Text412"]
tNpcGossip[8152]["tOption4-1"] = {8,9}
tNpcGossip[8152]["Option8"] = tLaborday2015_Strike_Text[8152]["Option8"]
tNpcGossip[8152]["Option9"] = tLaborday2015_Strike_Text[8152]["Option9"]
tNpcGossip[8152]["OptionPoint8"]="5"

tNpcGossip[8152]["Text5-1"] = {511,512}
tNpcGossip[8152]["Text511"] = tLaborday2015_Strike_Text[8152]["Text511"]
tNpcGossip[8152]["Text512"] = tLaborday2015_Strike_Text[8152]["Text512"]
tNpcGossip[8152]["tOption5-1"] = {10}
tNpcGossip[8152]["Option10"] = tLaborday2015_Strike_Text[8152]["Option10"]

tNpcGossip[8152]["Text6-1"] = {611,612}
tNpcGossip[8152]["Text611"] = tLaborday2015_Strike_Text[8152]["Text611"]
tNpcGossip[8152]["Text612"] = tLaborday2015_Strike_Text[8152]["Text612"]
tNpcGossip[8152]["tOption6-1"] = {11,12,13}
tNpcGossip[8152]["Option11"] = tLaborday2015_Strike_Text[8152]["Option11"]
tNpcGossip[8152]["Option12"] = tLaborday2015_Strike_Text[8152]["Option12"]
tNpcGossip[8152]["Option13"] = tLaborday2015_Strike_Text[8152]["Option13"]
tNpcGossip[8152]["OptionPoint11"]="7"
tNpcGossip[8152]["OptionFunc12"]="Laborday2015_Strike_Option12_8152</N>8152"

tNpcGossip[8152]["Text7-1"] = {711,712}
tNpcGossip[8152]["Text711"] = tLaborday2015_Strike_Text[8152]["Text711"]
tNpcGossip[8152]["Text712"] = tLaborday2015_Strike_Text[8152]["Text712"]
tNpcGossip[8152]["tOption7-1"] = {14}
tNpcGossip[8152]["Option14"] = tLaborday2015_Strike_Text[8152]["Option14"]

tNpcGossip[8152]["Text8-1"] = {811}
tNpcGossip[8152]["Text811"] = tLaborday2015_Strike_Text[8152]["Text811"]
tNpcGossip[8152]["tOption8-1"] = {15}
tNpcGossip[8152]["Option15"] = tLaborday2015_Strike_Text[8152]["Option15"]

tNpcGossip[8152]["Text8-3"] = {831}
tNpcGossip[8152]["Text831"] = tLaborday2015_Strike_Text[8152]["Text831"]
tNpcGossip[8152]["tOption8-3"] = {31}
tNpcGossip[8152]["Option30"] = tLaborday2015_Strike_Text[8152]["Option30"]

--官府老爷
tNpcFace[314] = 96
tNpcGossip[8164] = tNpcGossip[8164] or DefaultNpc:new{}
tNpcGossip[8164]["OptionHidden"] = 1

tNpcGossip[8164]["Text1-1"] = {111,112}
tNpcGossip[8164]["Text111"] = tLaborday2015_Strike_Text[8164]["Text111"]
tNpcGossip[8164]["Text112"] = tLaborday2015_Strike_Text[8164]["Text112"]
tNpcGossip[8164]["tOption1-1"] = {1}
tNpcGossip[8164]["Option1"] = tLaborday2015_Strike_Text[8164]["Option1"]
tNpcGossip[8164]["ChkFunc1-1"] = function ()
	if not Sys_ChkFullTime(tLaborday2015_Strike_Time[3]) then
		return true
	end

	for i=8153,8156 do
		if Task_ChkStcValue(tLaborday2015_Strike_Stc[3][i]["EventType"],tLaborday2015_Strike_Stc[3][i]["DataType"],"==",1) then
			return false
		end
	end
		return true
end 

tNpcGossip[8164]["Text1-2"] = {121,122}
tNpcGossip[8164]["Text121"] = tLaborday2015_Strike_Text[8164]["Text121"]
tNpcGossip[8164]["tOption1-2"] = {2}
tNpcGossip[8164]["Option2"] = tLaborday2015_Strike_Text[8164]["Option2"]
tNpcGossip[8164]["OptionFunc2"]="Laborday2015_Strike_Option2_8164</N>8164"
tNpcGossip[8164]["ChkFunc1-2"] = function ()
	if not Sys_ChkFullTime(tLaborday2015_Strike_Time[3]) then
		return false
	end

	for i=8153,8156 do
		if Task_ChkStcValue(tLaborday2015_Strike_Stc[3][i]["EventType"],tLaborday2015_Strike_Stc[3][i]["DataType"],"==",1) then
			return true
		end
	end
		return false
end

tNpcGossip[8164]["Text2-1"] = {211,212}
tNpcGossip[8164]["Text211"] = tLaborday2015_Strike_Text[8164]["Text211"]
tNpcGossip[8164]["Text212"] = tLaborday2015_Strike_Text[8164]["Text212"]
tNpcGossip[8164]["tOption2-1"] = {3}
tNpcGossip[8164]["Option3"] = tLaborday2015_Strike_Text[8164]["Option3"]


--铁匠赵刚
tNpcFace[212] = 66
tNpcGossip[8153] = tNpcGossip[8153] or DefaultNpc:new{}
tNpcGossip[8153]["OptionHidden"] = 1

--1?段
tNpcGossip[8153]["Text1-1"] = {111}
tNpcGossip[8153]["Text111"] = tLaborday2015_Strike_Text[8153]["Text111"]
tNpcGossip[8153]["tOption1-1"] = {1}
tNpcGossip[8153]["Option1"] = tLaborday2015_Strike_Text[8153]["Option1"]
tNpcGossip[8153]["ChkFunc1-1"] = function ()
	return Sys_ChkFullTime(tLaborday2015_Strike_Time["Beftime"])
end

tNpcGossip[8153]["Text1-2"] = {121}
tNpcGossip[8153]["Text121"] = tLaborday2015_Strike_Text[8153]["Text121"]
tNpcGossip[8153]["tOption1-2"] = {2,3,4}
tNpcGossip[8153]["Option2"] = tLaborday2015_Strike_Text[8153]["Option2"]
tNpcGossip[8153]["Option3"] = tLaborday2015_Strike_Text[8153]["Option3"]
tNpcGossip[8153]["Option4"] = tLaborday2015_Strike_Text[8153]["Option4"]
tNpcGossip[8153]["OptionFunc2"]="Laborday2015_Strike_Option2_8153</N>8153"
tNpcGossip[8153]["OptionFunc3"]="Laborday2015_Strike_Option3_8153</N>8153"
tNpcGossip[8153]["ChkFunc1-2"] = function ()
	return Sys_ChkFullTime(tLaborday2015_Strike_Time[1])
end

tNpcGossip[8153]["Text2-3"] = {231,232}
tNpcGossip[8153]["Text231"] = tLaborday2015_Strike_Text[8153]["Text231"]
tNpcGossip[8153]["Text232"] = tLaborday2015_Strike_Text[8153]["Text232"]
tNpcGossip[8153]["tOption2-3"] = {7}
tNpcGossip[8153]["Option7"] = tLaborday2015_Strike_Text[8153]["Option7"]
tNpcGossip[8153]["OptionFunc7"]="Laborday2015_Strike_Option7_8153</N>8153"

tNpcGossip[8153]["Text2-5"] = {251}
tNpcGossip[8153]["Text251"] = tLaborday2015_Strike_Text[8153]["Text251"]
tNpcGossip[8153]["tOption2-5"] = {9}
tNpcGossip[8153]["Option9"] = tLaborday2015_Strike_Text[8153]["Option9"]

tNpcGossip[8153]["Text2-6"] = {261}
tNpcGossip[8153]["Text261"] = tLaborday2015_Strike_Text[8153]["Text261"]
tNpcGossip[8153]["tOption2-6"] = {10}
tNpcGossip[8153]["Option10"] = tLaborday2015_Strike_Text[8153]["Option10"]

--2?段
tNpcGossip[8153]["Text1-3"] = {131}
tNpcGossip[8153]["Text131"] = tLaborday2015_Strike_Text[8153]["Text131"]
tNpcGossip[8153]["tOption1-3"] = {11,12}
tNpcGossip[8153]["Option11"] = tLaborday2015_Strike_Text[8153]["Option11"]
tNpcGossip[8153]["Option12"] = tLaborday2015_Strike_Text[8153]["Option12"]
tNpcGossip[8153]["OptionFunc11"]="Laborday2015_Strike_Option11_8153</N>8153"
tNpcGossip[8153]["ChkFunc1-3"] = function ()
	if Sys_ChkFullTime(tLaborday2015_Strike_Time[2]) and 
		Task_ChkStcValue(tLaborday2015_Strike_Stc[2][1]["EventType"],tLaborday2015_Strike_Stc[2][1]["DataType"],"==",0) and 
		Task_ChkStcValue(tLaborday2015_Strike_Stc[2][8153]["EventType"],tLaborday2015_Strike_Stc[2][8153]["DataType"],"==",0) then
		return true
	end
		return false
end

tNpcGossip[8153]["Text1-7"] = {321,322}
tNpcGossip[8153]["Text321"] = tLaborday2015_Strike_Text[8153]["Text321"]
tNpcGossip[8153]["Text322"] = tLaborday2015_Strike_Text[8153]["Text322"]
tNpcGossip[8153]["tOption1-7"] = {13}
tNpcGossip[8153]["Option13"] = tLaborday2015_Strike_Text[8153]["Option13"]
tNpcGossip[8153]["ChkFunc1-7"] = function ()
	if Sys_ChkFullTime(tLaborday2015_Strike_Time[2]) and 
		Task_ChkStcValue(tLaborday2015_Strike_Stc[2][1]["EventType"],tLaborday2015_Strike_Stc[2][1]["DataType"],"==",0) and
		Laborday2015_Strike_ChkattendanceSheet() then
		return true
	end
		return false
end

tNpcGossip[8153]["Text1-8"] = {331,332}
tNpcGossip[8153]["Text331"] = tLaborday2015_Strike_Text[8153]["Text331"]
tNpcGossip[8153]["Text332"] = tLaborday2015_Strike_Text[8153]["Text332"]
tNpcGossip[8153]["tOption1-8"] = {14,15}
tNpcGossip[8153]["Option14"] = tLaborday2015_Strike_Text[8153]["Option14"]
tNpcGossip[8153]["Option15"] = tLaborday2015_Strike_Text[8153]["Option15"]
tNpcGossip[8153]["OptionFunc14"]="Laborday2015_Strike_Option14_8153</N>8153"
tNpcGossip[8153]["ChkFunc1-8"] = function ()
	if Sys_ChkFullTime(tLaborday2015_Strike_Time[2]) and 
		Task_ChkStcValue(tLaborday2015_Strike_Stc[2][1]["EventType"],tLaborday2015_Strike_Stc[2][1]["DataType"],">=",tLaborday2015_Strike_Stc[2][1]["Data"]) then
		return true
	end
		return false
end

tNpcGossip[8153]["Text1-9"] = {341,342}
tNpcGossip[8153]["Text341"] = tLaborday2015_Strike_Text[8153]["Text341"]
tNpcGossip[8153]["tOption1-9"] = {16}
tNpcGossip[8153]["Option16"] = tLaborday2015_Strike_Text[8153]["Option16"]
tNpcGossip[8153]["ChkFunc1-9"] = function ()
	if Sys_ChkFullTime(tLaborday2015_Strike_Time[2]) and 
		Task_ChkStcValue(tLaborday2015_Strike_Stc[2][1]["EventType"],tLaborday2015_Strike_Stc[2][1]["DataType"],"==",0) and 
		Task_ChkStcValue(tLaborday2015_Strike_Stc[2][8153]["EventType"],tLaborday2015_Strike_Stc[2][8153]["DataType"],">=",tLaborday2015_Strike_Stc[2][8153]["Data"]) and
		not Laborday2015_Strike_ChkattendanceSheet() then
		return true
	end

end

tNpcGossip[8153]["Text3-5"] = {351}
tNpcGossip[8153]["Text351"] = tLaborday2015_Strike_Text[8153]["Text351"]
tNpcGossip[8153]["tOption3-5"] = {17}
tNpcGossip[8153]["Option17"] = tLaborday2015_Strike_Text[8153]["Option17"]

tNpcGossip[8153]["Text3-6"] = {361}
tNpcGossip[8153]["Text361"] = tLaborday2015_Strike_Text[8153]["Text361"]
tNpcGossip[8153]["tOption3-6"] = {18}
tNpcGossip[8153]["Option18"] = tLaborday2015_Strike_Text[8153]["Option18"]

--3?段
tNpcGossip[8153]["Text1-4"] = {411}
tNpcGossip[8153]["Text411"] = tLaborday2015_Strike_Text[8153]["Text411"]
tNpcGossip[8153]["tOption1-4"] = {22,23,24}
tNpcGossip[8153]["Option22"] = tLaborday2015_Strike_Text[8153]["Option22"]
tNpcGossip[8153]["Option23"] = tLaborday2015_Strike_Text[8153]["Option23"]
tNpcGossip[8153]["Option24"] = tLaborday2015_Strike_Text[8153]["Option24"]
tNpcGossip[8153]["OptionFunc22"]="Laborday2015_Strike_Option22_8153</N>8153"
tNpcGossip[8153]["OptionFunc23"]="Laborday2015_Strike_Option23_8153</N>8153"
tNpcGossip[8153]["ChkFunc1-4"] = function ()
	return Sys_ChkFullTime(tLaborday2015_Strike_Time[3])
end

tNpcGossip[8153]["Text4-2"] = {421}
tNpcGossip[8153]["Text421"] = tLaborday2015_Strike_Text[8153]["Text421"] 
tNpcGossip[8153]["tOption4-2"] = {25}
tNpcGossip[8153]["Option25"] = tLaborday2015_Strike_Text[8153]["Option25"]

tNpcGossip[8153]["Text4-3"] = {431}
tNpcGossip[8153]["Text431"] = tLaborday2015_Strike_Text[8153]["Text431"]
tNpcGossip[8153]["tOption4-3"] = {26}
tNpcGossip[8153]["Option26"] = tLaborday2015_Strike_Text[8153]["Option26"]

tNpcGossip[8153]["Text4-4"] = {441}
tNpcGossip[8153]["Text441"] = tLaborday2015_Strike_Text[8153]["Text441"]
tNpcGossip[8153]["tOption4-4"] = {27}
tNpcGossip[8153]["Option27"] = tLaborday2015_Strike_Text[8153]["Option27"]

tNpcGossip[8153]["Text5-1"] = {511}
tNpcGossip[8153]["Text511"] = tLaborday2015_Strike_Text[8153]["Text511"]
tNpcGossip[8153]["tOption5-1"] = {28}
tNpcGossip[8153]["Option28"] = tLaborday2015_Strike_Text[8153]["Option28"]
tNpcGossip[8153]["OptionFunc28"]="Laborday2015_Strike_Option28_8153</N>8153"

--4?段
tNpcGossip[8153]["Text1-5"] = {151}
tNpcGossip[8153]["Text151"] = tLaborday2015_Strike_Text[8153]["Text151"]
tNpcGossip[8153]["tOption1-5"] = {30}
tNpcGossip[8153]["Option30"] = tLaborday2015_Strike_Text[8153]["Option30"]
tNpcGossip[8153]["OptionFunc30"]="Laborday2015_Strike_Option30_8153</N>8153"
tNpcGossip[8153]["ChkFunc1-5"] = function ()
	return Sys_ChkFullTime(tLaborday2015_Strike_Time[4])
end

tNpcGossip[8153]["Text5-2"] = {521,522}
tNpcGossip[8153]["Text521"] = tLaborday2015_Strike_Text[8153]["Text521"]
tNpcGossip[8153]["Text522"] = tLaborday2015_Strike_Text[8153]["Text522"]
tNpcGossip[8153]["tOption5-2"] = {31,32}
tNpcGossip[8153]["Option31"] = tLaborday2015_Strike_Text[8153]["Option31"]
tNpcGossip[8153]["Option32"] = tLaborday2015_Strike_Text[8153]["Option32"]
tNpcGossip[8153]["OptionFunc31"]="Laborday2015_Strike_Option31_8153</N>8153"

tNpcGossip[8153]["Text5-3"] = {531,532}
tNpcGossip[8153]["Text531"] = tLaborday2015_Strike_Text[8153]["Text531"]
tNpcGossip[8153]["Text532"] = tLaborday2015_Strike_Text[8153]["Text532"]
tNpcGossip[8153]["tOption5-3"] = {33,34}
tNpcGossip[8153]["Option33"] = tLaborday2015_Strike_Text[8153]["Option33"]
tNpcGossip[8153]["Option34"] = tLaborday2015_Strike_Text[8153]["Option34"]
tNpcGossip[8153]["OptionFunc33"]="Laborday2015_Strike_Option33_8153</N>8153"

tNpcGossip[8153]["Text5-4"] = {541,542}
tNpcGossip[8153]["Text541"] = tLaborday2015_Strike_Text[8153]["Text541"]
tNpcGossip[8153]["Text542"] = tLaborday2015_Strike_Text[8153]["Text542"]
tNpcGossip[8153]["tOption5-4"] = {35,36,37}
tNpcGossip[8153]["Option35"] = tLaborday2015_Strike_Text[8153]["Option35"]
tNpcGossip[8153]["Option36"] = tLaborday2015_Strike_Text[8153]["Option36"]
tNpcGossip[8153]["Option37"] = tLaborday2015_Strike_Text[8153]["Option37"]
tNpcGossip[8153]["OptionFunc35"]="Laborday2015_Strike_Option35_8153</N>8153"
tNpcGossip[8153]["OptionFunc36"]="Laborday2015_Strike_Option36_8153</N>8153"
tNpcGossip[8153]["OptionChkFunc35"] = function ()
	return Task_ChkStcValue(tLaborday2015_Strike_Stc[4][8153]["EventType"],tLaborday2015_Strike_Stc[4][8153]["DataType"],"==",tLaborday2015_Strike_Stc[4][8153]["Data5"])
end
tNpcGossip[8153]["OptionChkFunc36"] = function ()
	return Task_ChkStcValue(tLaborday2015_Strike_Stc[4][8153]["EventType"],tLaborday2015_Strike_Stc[4][8153]["DataType"],"==",tLaborday2015_Strike_Stc[4][8153]["Data6"])
end

tNpcGossip[8153]["Text5-5"] = {551,552}
tNpcGossip[8153]["Text551"] = tLaborday2015_Strike_Text[8153]["Text551"]
tNpcGossip[8153]["Text552"] = tLaborday2015_Strike_Text[8153]["Text552"]
tNpcGossip[8153]["tOption5-5"] = {38,39,40}
tNpcGossip[8153]["Option38"] = tLaborday2015_Strike_Text[8153]["Option38"]
tNpcGossip[8153]["Option39"] = tLaborday2015_Strike_Text[8153]["Option39"]
tNpcGossip[8153]["Option40"] = tLaborday2015_Strike_Text[8153]["Option40"]
tNpcGossip[8153]["OptionFunc38"]="Laborday2015_Strike_Option38_8153</N>8153"
tNpcGossip[8153]["OptionFunc39"]="Laborday2015_Strike_Option39_8153</N>8153"
tNpcGossip[8153]["OptionChkFunc38"] = function ()
	return Task_ChkStcValue(tLaborday2015_Strike_Stc[4][8153]["EventType"],tLaborday2015_Strike_Stc[4][8153]["DataType"],"==",tLaborday2015_Strike_Stc[4][8153]["Data7"])
end
tNpcGossip[8153]["OptionChkFunc39"] = function ()
	return Task_ChkStcValue(tLaborday2015_Strike_Stc[4][8153]["EventType"],tLaborday2015_Strike_Stc[4][8153]["DataType"],"==",tLaborday2015_Strike_Stc[4][8153]["Data8"])
end

tNpcGossip[8153]["Text1-6"] = {611}
tNpcGossip[8153]["Text611"] = tLaborday2015_Strike_Text[8153]["Text611"]
tNpcGossip[8153]["tOption1-6"] = {41}
tNpcGossip[8153]["Option41"] = tLaborday2015_Strike_Text[8153]["Option41"]
tNpcGossip[8153]["ChkFunc1-6"] = function ()
	return Sys_ChkFullTime(tLaborday2015_Strike_Time["Aftime"])
end

--裁缝惠娘
tNpcFace[213] = 178
tNpcGossip[8154] = tNpcGossip[8154] or DefaultNpc:new{}
tNpcGossip[8154]["OptionHidden"] = 1

--1?段
tNpcGossip[8154]["Text1-1"] = {111}
tNpcGossip[8154]["Text111"] = tLaborday2015_Strike_Text[8154]["Text111"]
tNpcGossip[8154]["tOption1-1"] = {1}
tNpcGossip[8154]["Option1"] = tLaborday2015_Strike_Text[8154]["Option1"]
tNpcGossip[8154]["ChkFunc1-1"] = function ()
	return Sys_ChkFullTime(tLaborday2015_Strike_Time["Beftime"])
end

tNpcGossip[8154]["Text1-2"] = {121}
tNpcGossip[8154]["Text121"] = tLaborday2015_Strike_Text[8154]["Text121"]
tNpcGossip[8154]["tOption1-2"] = {2,3,4}
tNpcGossip[8154]["Option2"] = tLaborday2015_Strike_Text[8154]["Option2"]
tNpcGossip[8154]["Option3"] = tLaborday2015_Strike_Text[8154]["Option3"]
tNpcGossip[8154]["Option4"] = tLaborday2015_Strike_Text[8154]["Option4"]
tNpcGossip[8154]["OptionFunc2"]="Laborday2015_Strike_Option2_8153</N>8154"
tNpcGossip[8154]["OptionFunc3"]="Laborday2015_Strike_Option3_8153</N>8154"
tNpcGossip[8154]["ChkFunc1-2"] = function ()
	return Sys_ChkFullTime(tLaborday2015_Strike_Time[1])
end

tNpcGossip[8154]["Text2-3"] = {231}
tNpcGossip[8154]["Text231"] = tLaborday2015_Strike_Text[8154]["Text231"]
tNpcGossip[8154]["Text232"] = tLaborday2015_Strike_Text[8154]["Text232"]
tNpcGossip[8154]["tOption2-3"] = {7}
tNpcGossip[8154]["Option7"] = tLaborday2015_Strike_Text[8154]["Option7"]
tNpcGossip[8154]["OptionFunc7"]="Laborday2015_Strike_Option7_8153</N>8154"

tNpcGossip[8154]["Text2-5"] = {251}
tNpcGossip[8154]["Text251"] = tLaborday2015_Strike_Text[8154]["Text251"]
tNpcGossip[8154]["tOption2-5"] = {9}
tNpcGossip[8154]["Option9"] = tLaborday2015_Strike_Text[8154]["Option9"]

tNpcGossip[8154]["Text2-6"] = {261}
tNpcGossip[8154]["Text261"] = tLaborday2015_Strike_Text[8154]["Text261"]
tNpcGossip[8154]["tOption2-6"] = {10}
tNpcGossip[8154]["Option10"] = tLaborday2015_Strike_Text[8154]["Option10"]

--2?段
tNpcGossip[8154]["Text1-3"] = {131}
tNpcGossip[8154]["Text131"] = tLaborday2015_Strike_Text[8154]["Text131"]
tNpcGossip[8154]["tOption1-3"] = {11,12}
tNpcGossip[8154]["Option11"] = tLaborday2015_Strike_Text[8154]["Option11"]
tNpcGossip[8154]["Option12"] = tLaborday2015_Strike_Text[8154]["Option12"]
tNpcGossip[8154]["OptionFunc11"]="Laborday2015_Strike_Option11_8153</N>8154"
tNpcGossip[8154]["ChkFunc1-3"] = function ()
	if Sys_ChkFullTime(tLaborday2015_Strike_Time[2]) and 
		Task_ChkStcValue(tLaborday2015_Strike_Stc[2][1]["EventType"],tLaborday2015_Strike_Stc[2][1]["DataType"],"==",0) and 
		Task_ChkStcValue(tLaborday2015_Strike_Stc[2][8154]["EventType"],tLaborday2015_Strike_Stc[2][8154]["DataType"],"==",0) then
		return true
	end
		return false
end

tNpcGossip[8154]["Text1-7"] = {321,322}
tNpcGossip[8154]["Text321"] = tLaborday2015_Strike_Text[8154]["Text321"]
tNpcGossip[8154]["Text322"] = tLaborday2015_Strike_Text[8154]["Text322"]
tNpcGossip[8154]["tOption1-7"] = {13}
tNpcGossip[8154]["Option13"] = tLaborday2015_Strike_Text[8154]["Option13"]
tNpcGossip[8154]["ChkFunc1-7"] = function ()
	if Sys_ChkFullTime(tLaborday2015_Strike_Time[2]) and 
		Task_ChkStcValue(tLaborday2015_Strike_Stc[2][1]["EventType"],tLaborday2015_Strike_Stc[2][1]["DataType"],"==",0) and
		Laborday2015_Strike_ChkattendanceSheet() then
		return true
	end
		return false
end

tNpcGossip[8154]["Text1-8"] = {331,332}
tNpcGossip[8154]["Text331"] = tLaborday2015_Strike_Text[8154]["Text331"]
tNpcGossip[8154]["Text332"] = tLaborday2015_Strike_Text[8154]["Text332"]
tNpcGossip[8154]["tOption1-8"] = {14,5,15}
tNpcGossip[8154]["Option14"] = tLaborday2015_Strike_Text[8154]["Option14"]
tNpcGossip[8154]["Option5"] = tLaborday2015_Strike_Text[8154]["Option5"]
tNpcGossip[8154]["Option15"] = tLaborday2015_Strike_Text[8154]["Option15"]
tNpcGossip[8154]["OptionFunc14"]="Laborday2015_Strike_Option14_8154</N>8154"
tNpcGossip[8154]["OptionFunc5"]="Laborday2015_Strike_Option5_8154</N>8154"
tNpcGossip[8154]["ChkFunc1-8"] = function ()
	if Sys_ChkFullTime(tLaborday2015_Strike_Time[2]) and 
		Task_ChkStcValue(tLaborday2015_Strike_Stc[2][1]["EventType"],tLaborday2015_Strike_Stc[2][1]["DataType"],">=",tLaborday2015_Strike_Stc[2][1]["Data"]) then
		return true
	end
		return false
end

tNpcGossip[8154]["Text1-9"] = {341,342}
tNpcGossip[8154]["Text341"] = tLaborday2015_Strike_Text[8154]["Text341"]
tNpcGossip[8154]["tOption1-9"] = {16}
tNpcGossip[8154]["Option16"] = tLaborday2015_Strike_Text[8154]["Option16"]
tNpcGossip[8154]["ChkFunc1-9"] = function ()
	if Sys_ChkFullTime(tLaborday2015_Strike_Time[2]) and 
		Task_ChkStcValue(tLaborday2015_Strike_Stc[2][1]["EventType"],tLaborday2015_Strike_Stc[2][1]["DataType"],"==",0) and 
		Task_ChkStcValue(tLaborday2015_Strike_Stc[2][8154]["EventType"],tLaborday2015_Strike_Stc[2][8154]["DataType"],">=",tLaborday2015_Strike_Stc[2][8154]["Data"]) and
		not Laborday2015_Strike_ChkattendanceSheet() then
		return true
	end

end

tNpcGossip[8154]["Text3-5"] = {351}
tNpcGossip[8154]["Text351"] = tLaborday2015_Strike_Text[8154]["Text351"]
tNpcGossip[8154]["tOption3-5"] = {17}
tNpcGossip[8154]["Option17"] = tLaborday2015_Strike_Text[8154]["Option17"]

tNpcGossip[8154]["Text3-6"] = {361}
tNpcGossip[8154]["Text361"] = tLaborday2015_Strike_Text[8154]["Text361"]
tNpcGossip[8154]["tOption3-6"] = {17}
tNpcGossip[8154]["Option18"] = tLaborday2015_Strike_Text[8154]["Option18"]


--3?段
tNpcGossip[8154]["Text1-4"] = {411}
tNpcGossip[8154]["Text411"] = tLaborday2015_Strike_Text[8154]["Text411"]
tNpcGossip[8154]["tOption1-4"] = {22,23,24}
tNpcGossip[8154]["Option22"] = tLaborday2015_Strike_Text[8154]["Option22"]
tNpcGossip[8154]["Option23"] = tLaborday2015_Strike_Text[8154]["Option23"]
tNpcGossip[8154]["Option24"] = tLaborday2015_Strike_Text[8154]["Option24"]
tNpcGossip[8154]["OptionFunc22"]="Laborday2015_Strike_Option22_8153</N>8154"
tNpcGossip[8154]["OptionFunc23"]="Laborday2015_Strike_Option23_8153</N>8154"
tNpcGossip[8154]["ChkFunc1-4"] = function ()
	return Sys_ChkFullTime(tLaborday2015_Strike_Time[3])
end

tNpcGossip[8154]["Text4-2"] = {421}
tNpcGossip[8154]["Text421"] = tLaborday2015_Strike_Text[8154]["Text421"]
tNpcGossip[8154]["tOption4-2"] = {25}
tNpcGossip[8154]["Option25"] = tLaborday2015_Strike_Text[8154]["Option25"]

tNpcGossip[8154]["Text4-3"] = {431}
tNpcGossip[8154]["Text431"] = tLaborday2015_Strike_Text[8154]["Text431"]
tNpcGossip[8154]["tOption4-3"] = {26}
tNpcGossip[8154]["Option26"] = tLaborday2015_Strike_Text[8154]["Option26"]

tNpcGossip[8154]["Text4-4"] = {441}
tNpcGossip[8154]["Text441"] = tLaborday2015_Strike_Text[8154]["Text441"]
tNpcGossip[8154]["tOption4-4"] = {27}
tNpcGossip[8154]["Option27"] = tLaborday2015_Strike_Text[8154]["Option27"]

tNpcGossip[8154]["Text5-1"] = {511}
tNpcGossip[8154]["Text511"] = tLaborday2015_Strike_Text[8154]["Text511"]
tNpcGossip[8154]["tOption5-1"] = {28}
tNpcGossip[8154]["Option28"] = tLaborday2015_Strike_Text[8154]["Option28"]
tNpcGossip[8154]["OptionFunc28"]="Laborday2015_Strike_Option28_8153</N>8154"

--4?段
tNpcGossip[8154]["Text1-5"] = {151}
tNpcGossip[8154]["Text151"] = tLaborday2015_Strike_Text[8154]["Text151"]
tNpcGossip[8154]["tOption1-5"] = {30}
tNpcGossip[8154]["Option30"] = tLaborday2015_Strike_Text[8154]["Option30"]
tNpcGossip[8154]["OptionFunc30"]="Laborday2015_Strike_Option30_8153</N>8154"
tNpcGossip[8154]["ChkFunc1-5"] = function ()
	return Sys_ChkFullTime(tLaborday2015_Strike_Time[4])
end

tNpcGossip[8154]["Text5-2"] = {521,522}
tNpcGossip[8154]["Text521"] = tLaborday2015_Strike_Text[8154]["Text521"]
tNpcGossip[8154]["Text522"] = tLaborday2015_Strike_Text[8154]["Text522"]
tNpcGossip[8154]["tOption5-2"] = {31,32}
tNpcGossip[8154]["Option31"] = tLaborday2015_Strike_Text[8154]["Option31"]
tNpcGossip[8154]["Option32"] = tLaborday2015_Strike_Text[8154]["Option32"]
tNpcGossip[8154]["OptionFunc31"]="Laborday2015_Strike_Option31_8153</N>8154"

tNpcGossip[8154]["Text5-3"] = {531,532}
tNpcGossip[8154]["Text531"] = tLaborday2015_Strike_Text[8154]["Text531"]
tNpcGossip[8154]["Text532"] = tLaborday2015_Strike_Text[8154]["Text532"]
tNpcGossip[8154]["tOption5-3"] = {33,34}
tNpcGossip[8154]["Option33"] = tLaborday2015_Strike_Text[8154]["Option33"]
tNpcGossip[8154]["Option34"] = tLaborday2015_Strike_Text[8154]["Option34"]
tNpcGossip[8154]["OptionFunc33"]="Laborday2015_Strike_Option33_8153</N>8154"

tNpcGossip[8154]["Text5-4"] = {541,542}
tNpcGossip[8154]["Text541"] = tLaborday2015_Strike_Text[8154]["Text541"]
tNpcGossip[8154]["Text542"] = tLaborday2015_Strike_Text[8154]["Text542"]
tNpcGossip[8154]["tOption5-4"] = {35,36,37}
tNpcGossip[8154]["Option35"] = tLaborday2015_Strike_Text[8154]["Option35"]
tNpcGossip[8154]["Option36"] = tLaborday2015_Strike_Text[8154]["Option36"]
tNpcGossip[8154]["Option37"] = tLaborday2015_Strike_Text[8154]["Option37"]
tNpcGossip[8154]["OptionFunc35"]="Laborday2015_Strike_Option35_8153</N>8154"
tNpcGossip[8154]["OptionFunc36"]="Laborday2015_Strike_Option36_8153</N>8154"
tNpcGossip[8154]["OptionChkFunc35"] = function ()
	return Task_ChkStcValue(tLaborday2015_Strike_Stc[4][8154]["EventType"],tLaborday2015_Strike_Stc[4][8154]["DataType"],"==",tLaborday2015_Strike_Stc[4][8154]["Data5"])
end
tNpcGossip[8154]["OptionChkFunc36"] = function ()
	return Task_ChkStcValue(tLaborday2015_Strike_Stc[4][8154]["EventType"],tLaborday2015_Strike_Stc[4][8154]["DataType"],"==",tLaborday2015_Strike_Stc[4][8154]["Data6"])
end

tNpcGossip[8154]["Text5-5"] = {551,552}
tNpcGossip[8154]["Text551"] = tLaborday2015_Strike_Text[8154]["Text551"]
tNpcGossip[8154]["Text552"] = tLaborday2015_Strike_Text[8154]["Text552"]
tNpcGossip[8154]["tOption5-5"] = {38,39,40}
tNpcGossip[8154]["Option38"] = tLaborday2015_Strike_Text[8154]["Option38"]
tNpcGossip[8154]["Option39"] = tLaborday2015_Strike_Text[8154]["Option39"]
tNpcGossip[8154]["Option40"] = tLaborday2015_Strike_Text[8154]["Option40"]
tNpcGossip[8154]["OptionFunc38"]="Laborday2015_Strike_Option38_8153</N>8154"
tNpcGossip[8154]["OptionFunc39"]="Laborday2015_Strike_Option39_8153</N>8154"
tNpcGossip[8154]["OptionChkFunc38"] = function ()
	return Task_ChkStcValue(tLaborday2015_Strike_Stc[4][8154]["EventType"],tLaborday2015_Strike_Stc[4][8154]["DataType"],"==",tLaborday2015_Strike_Stc[4][8154]["Data7"])
end
tNpcGossip[8154]["OptionChkFunc39"] = function ()
	return Task_ChkStcValue(tLaborday2015_Strike_Stc[4][8154]["EventType"],tLaborday2015_Strike_Stc[4][8154]["DataType"],"==",tLaborday2015_Strike_Stc[4][8154]["Data8"])
end

tNpcGossip[8154]["Text1-6"] = {611}
tNpcGossip[8154]["Text611"] = tLaborday2015_Strike_Text[8154]["Text611"]
tNpcGossip[8154]["tOption1-6"] = {41}
tNpcGossip[8154]["Option41"] = tLaborday2015_Strike_Text[8154]["Option41"]
tNpcGossip[8154]["ChkFunc1-6"] = function ()
	return Sys_ChkFullTime(tLaborday2015_Strike_Time["Aftime"])
end

--厨师冯善
tNpcFace[214] = 18
tNpcGossip[8155] = tNpcGossip[8155] or DefaultNpc:new{}
tNpcGossip[8155]["OptionHidden"] = 1

--1?段
tNpcGossip[8155]["Text1-1"] = {111}
tNpcGossip[8155]["Text111"] = tLaborday2015_Strike_Text[8155]["Text111"]
tNpcGossip[8155]["tOption1-1"] = {1}
tNpcGossip[8155]["Option1"] = tLaborday2015_Strike_Text[8155]["Option1"]
tNpcGossip[8155]["ChkFunc1-1"] = function ()
	return Sys_ChkFullTime(tLaborday2015_Strike_Time["Beftime"])
end

tNpcGossip[8155]["Text1-2"] = {121}
tNpcGossip[8155]["Text121"] = tLaborday2015_Strike_Text[8155]["Text121"]
tNpcGossip[8155]["tOption1-2"] = {2,3,4}
tNpcGossip[8155]["Option2"] = tLaborday2015_Strike_Text[8155]["Option2"]
tNpcGossip[8155]["Option3"] = tLaborday2015_Strike_Text[8155]["Option3"]
tNpcGossip[8155]["Option4"] = tLaborday2015_Strike_Text[8155]["Option4"]
tNpcGossip[8155]["OptionFunc2"]="Laborday2015_Strike_Option2_8153</N>8155"
tNpcGossip[8155]["OptionFunc3"]="Laborday2015_Strike_Option3_8153</N>8155"
tNpcGossip[8155]["ChkFunc1-2"] = function ()
	return Sys_ChkFullTime(tLaborday2015_Strike_Time[1])
end

tNpcGossip[8155]["Text2-3"] = {231,232}
tNpcGossip[8155]["Text231"] = tLaborday2015_Strike_Text[8155]["Text231"]
tNpcGossip[8155]["Text232"] = tLaborday2015_Strike_Text[8155]["Text232"]
tNpcGossip[8155]["tOption2-3"] = {7}
tNpcGossip[8155]["Option7"] = tLaborday2015_Strike_Text[8155]["Option7"]
tNpcGossip[8155]["OptionFunc7"]="Laborday2015_Strike_Option7_8153</N>8155"

tNpcGossip[8155]["Text2-5"] = {251}
tNpcGossip[8155]["Text251"] = tLaborday2015_Strike_Text[8155]["Text251"]
tNpcGossip[8155]["tOption2-5"] = {9}
tNpcGossip[8155]["Option9"] = tLaborday2015_Strike_Text[8155]["Option9"]

tNpcGossip[8155]["Text2-6"] = {261}
tNpcGossip[8155]["Text261"] = tLaborday2015_Strike_Text[8155]["Text261"]
tNpcGossip[8155]["tOption2-6"] = {10}
tNpcGossip[8155]["Option10"] = tLaborday2015_Strike_Text[8155]["Option10"]

--2?段
tNpcGossip[8155]["Text1-3"] = {131}
tNpcGossip[8155]["Text131"] = tLaborday2015_Strike_Text[8155]["Text131"]
tNpcGossip[8155]["tOption1-3"] = {11,12}
tNpcGossip[8155]["Option11"] = tLaborday2015_Strike_Text[8155]["Option11"]
tNpcGossip[8155]["Option12"] = tLaborday2015_Strike_Text[8155]["Option12"]
tNpcGossip[8155]["OptionFunc11"]="Laborday2015_Strike_Option11_8153</N>8155"
tNpcGossip[8155]["ChkFunc1-3"] = function ()
	if Sys_ChkFullTime(tLaborday2015_Strike_Time[2]) and 
		Task_ChkStcValue(tLaborday2015_Strike_Stc[2][1]["EventType"],tLaborday2015_Strike_Stc[2][1]["DataType"],"==",0) and 
		Task_ChkStcValue(tLaborday2015_Strike_Stc[2][8155]["EventType"],tLaborday2015_Strike_Stc[2][8155]["DataType"],"==",0) then
		return true
	end
		return false
end

tNpcGossip[8155]["Text1-7"] = {321,322}
tNpcGossip[8155]["Text321"] = tLaborday2015_Strike_Text[8155]["Text321"]
tNpcGossip[8155]["Text322"] = tLaborday2015_Strike_Text[8155]["Text322"]
tNpcGossip[8155]["tOption1-7"] = {13}
tNpcGossip[8155]["Option13"] = tLaborday2015_Strike_Text[8155]["Option13"]
tNpcGossip[8155]["ChkFunc1-7"] = function ()
	if Sys_ChkFullTime(tLaborday2015_Strike_Time[2]) and 
		Task_ChkStcValue(tLaborday2015_Strike_Stc[2][1]["EventType"],tLaborday2015_Strike_Stc[2][1]["DataType"],"==",0) and
		Laborday2015_Strike_ChkattendanceSheet() then
		return true
	end
		return false
end

tNpcGossip[8155]["Text1-8"] = {331,332}
tNpcGossip[8155]["Text331"] = tLaborday2015_Strike_Text[8155]["Text331"]
tNpcGossip[8155]["Text332"] = tLaborday2015_Strike_Text[8155]["Text332"]
tNpcGossip[8155]["tOption1-8"] = {14,5,15}
tNpcGossip[8155]["Option14"] = tLaborday2015_Strike_Text[8155]["Option14"]
tNpcGossip[8155]["Option5"] = tLaborday2015_Strike_Text[8155]["Option5"]
tNpcGossip[8155]["Option15"] = tLaborday2015_Strike_Text[8155]["Option15"]
tNpcGossip[8155]["OptionFunc14"]="Laborday2015_Strike_Option14_8154</N>8155"
tNpcGossip[8155]["OptionFunc5"]="Laborday2015_Strike_Option5_8154</N>8155"
tNpcGossip[8155]["ChkFunc1-8"] = function ()
	if Sys_ChkFullTime(tLaborday2015_Strike_Time[2]) and 
		Task_ChkStcValue(tLaborday2015_Strike_Stc[2][1]["EventType"],tLaborday2015_Strike_Stc[2][1]["DataType"],">=",tLaborday2015_Strike_Stc[2][1]["Data"]) then
		return true
	end
		return false
end

tNpcGossip[8155]["Text1-9"] = {341,342}
tNpcGossip[8155]["Text341"] = tLaborday2015_Strike_Text[8155]["Text341"]
tNpcGossip[8155]["tOption1-9"] = {16}
tNpcGossip[8155]["Option16"] = tLaborday2015_Strike_Text[8155]["Option16"]
tNpcGossip[8155]["ChkFunc1-9"] = function ()
	if Sys_ChkFullTime(tLaborday2015_Strike_Time[2]) and 
		Task_ChkStcValue(tLaborday2015_Strike_Stc[2][1]["EventType"],tLaborday2015_Strike_Stc[2][1]["DataType"],"==",0) and 
		Task_ChkStcValue(tLaborday2015_Strike_Stc[2][8155]["EventType"],tLaborday2015_Strike_Stc[2][8155]["DataType"],">=",tLaborday2015_Strike_Stc[2][8155]["Data"]) and
		not Laborday2015_Strike_ChkattendanceSheet() then
		return true
	end

end

tNpcGossip[8155]["Text3-5"] = {351}
tNpcGossip[8155]["Text351"] = tLaborday2015_Strike_Text[8155]["Text351"]
tNpcGossip[8155]["tOption3-5"] = {17}
tNpcGossip[8155]["Option17"] = tLaborday2015_Strike_Text[8155]["Option17"]

tNpcGossip[8155]["Text3-6"] = {361}
tNpcGossip[8155]["Text361"] = tLaborday2015_Strike_Text[8155]["Text361"]
tNpcGossip[8155]["tOption3-6"] = {17}
tNpcGossip[8155]["Option18"] = tLaborday2015_Strike_Text[8155]["Option18"]

--3?段
tNpcGossip[8155]["Text1-4"] = {411}
tNpcGossip[8155]["Text411"] = tLaborday2015_Strike_Text[8155]["Text411"]
tNpcGossip[8155]["tOption1-4"] = {22,23,24}
tNpcGossip[8155]["Option22"] = tLaborday2015_Strike_Text[8155]["Option22"]
tNpcGossip[8155]["Option23"] = tLaborday2015_Strike_Text[8155]["Option23"]
tNpcGossip[8155]["Option24"] = tLaborday2015_Strike_Text[8155]["Option24"]
tNpcGossip[8155]["OptionFunc22"]="Laborday2015_Strike_Option22_8153</N>8155"
tNpcGossip[8155]["OptionFunc23"]="Laborday2015_Strike_Option23_8153</N>8155"
tNpcGossip[8155]["ChkFunc1-4"] = function ()
	return Sys_ChkFullTime(tLaborday2015_Strike_Time[3])
end

tNpcGossip[8155]["Text4-2"] = {421}
tNpcGossip[8155]["Text421"] = tLaborday2015_Strike_Text[8155]["Text421"]
tNpcGossip[8155]["tOption4-2"] = {25}
tNpcGossip[8155]["Option25"] = tLaborday2015_Strike_Text[8155]["Option25"]

tNpcGossip[8155]["Text4-3"] = {431}
tNpcGossip[8155]["Text431"] = tLaborday2015_Strike_Text[8155]["Text431"]
tNpcGossip[8155]["tOption4-3"] = {26}
tNpcGossip[8155]["Option26"] = tLaborday2015_Strike_Text[8155]["Option26"]

tNpcGossip[8155]["Text4-4"] = {441}
tNpcGossip[8155]["Text441"] = tLaborday2015_Strike_Text[8155]["Text441"]
tNpcGossip[8155]["tOption4-4"] = {27}
tNpcGossip[8155]["Option27"] = tLaborday2015_Strike_Text[8155]["Option27"]

tNpcGossip[8155]["Text5-1"] = {511}
tNpcGossip[8155]["Text511"] = tLaborday2015_Strike_Text[8155]["Text511"]
tNpcGossip[8155]["tOption5-1"] = {28}
tNpcGossip[8155]["Option28"] = tLaborday2015_Strike_Text[8155]["Option28"]
tNpcGossip[8155]["OptionFunc28"]="Laborday2015_Strike_Option28_8153</N>8155"

--4?段
tNpcGossip[8155]["Text1-5"] = {151}
tNpcGossip[8155]["Text151"] = tLaborday2015_Strike_Text[8155]["Text151"]
tNpcGossip[8155]["tOption1-5"] = {30}
tNpcGossip[8155]["Option30"] = tLaborday2015_Strike_Text[8155]["Option30"]
tNpcGossip[8155]["OptionFunc30"]="Laborday2015_Strike_Option30_8153</N>8155"
tNpcGossip[8155]["ChkFunc1-5"] = function ()
	return Sys_ChkFullTime(tLaborday2015_Strike_Time[4])
end

tNpcGossip[8155]["Text5-2"] = {521,522}
tNpcGossip[8155]["Text521"] = tLaborday2015_Strike_Text[8155]["Text521"]
tNpcGossip[8155]["Text522"] = tLaborday2015_Strike_Text[8155]["Text522"]
tNpcGossip[8155]["tOption5-2"] = {31,32}
tNpcGossip[8155]["Option31"] = tLaborday2015_Strike_Text[8155]["Option31"]
tNpcGossip[8155]["Option32"] = tLaborday2015_Strike_Text[8155]["Option32"]
tNpcGossip[8155]["OptionFunc31"]="Laborday2015_Strike_Option31_8153</N>8155"

tNpcGossip[8155]["Text5-3"] = {531,532}
tNpcGossip[8155]["Text531"] = tLaborday2015_Strike_Text[8155]["Text531"]
tNpcGossip[8155]["Text532"] = tLaborday2015_Strike_Text[8155]["Text532"]
tNpcGossip[8155]["tOption5-3"] = {33,34}
tNpcGossip[8155]["Option33"] = tLaborday2015_Strike_Text[8155]["Option33"]
tNpcGossip[8155]["Option34"] = tLaborday2015_Strike_Text[8155]["Option34"]
tNpcGossip[8155]["OptionFunc33"]="Laborday2015_Strike_Option33_8153</N>8155"

tNpcGossip[8155]["Text5-4"] = {541,542}
tNpcGossip[8155]["Text541"] = tLaborday2015_Strike_Text[8155]["Text541"]
tNpcGossip[8155]["Text542"] = tLaborday2015_Strike_Text[8155]["Text542"]
tNpcGossip[8155]["tOption5-4"] = {35,36,37}
tNpcGossip[8155]["Option35"] = tLaborday2015_Strike_Text[8155]["Option35"]
tNpcGossip[8155]["Option36"] = tLaborday2015_Strike_Text[8155]["Option36"]
tNpcGossip[8155]["Option37"] = tLaborday2015_Strike_Text[8155]["Option37"]
tNpcGossip[8155]["OptionFunc35"]="Laborday2015_Strike_Option35_8153</N>8155"
tNpcGossip[8155]["OptionFunc36"]="Laborday2015_Strike_Option36_8153</N>8155"
tNpcGossip[8155]["OptionChkFunc35"] = function ()
	return Task_ChkStcValue(tLaborday2015_Strike_Stc[4][8155]["EventType"],tLaborday2015_Strike_Stc[4][8155]["DataType"],"==",tLaborday2015_Strike_Stc[4][8155]["Data5"])
end
tNpcGossip[8155]["OptionChkFunc36"] = function ()
	return Task_ChkStcValue(tLaborday2015_Strike_Stc[4][8155]["EventType"],tLaborday2015_Strike_Stc[4][8155]["DataType"],"==",tLaborday2015_Strike_Stc[4][8155]["Data6"])
end

tNpcGossip[8155]["Text5-5"] = {551,552}
tNpcGossip[8155]["Text551"] = tLaborday2015_Strike_Text[8155]["Text551"]
tNpcGossip[8155]["Text552"] = tLaborday2015_Strike_Text[8155]["Text552"]
tNpcGossip[8155]["tOption5-5"] = {38,39,40}
tNpcGossip[8155]["Option38"] = tLaborday2015_Strike_Text[8155]["Option38"]
tNpcGossip[8155]["Option39"] = tLaborday2015_Strike_Text[8155]["Option39"]
tNpcGossip[8155]["Option40"] = tLaborday2015_Strike_Text[8155]["Option40"]
tNpcGossip[8155]["OptionFunc38"]="Laborday2015_Strike_Option38_8153</N>8155"
tNpcGossip[8155]["OptionFunc39"]="Laborday2015_Strike_Option39_8153</N>8155"
tNpcGossip[8155]["OptionChkFunc38"] = function ()
	return Task_ChkStcValue(tLaborday2015_Strike_Stc[4][8155]["EventType"],tLaborday2015_Strike_Stc[4][8155]["DataType"],"==",tLaborday2015_Strike_Stc[4][8155]["Data7"])
end
tNpcGossip[8155]["OptionChkFunc39"] = function ()
	return Task_ChkStcValue(tLaborday2015_Strike_Stc[4][8155]["EventType"],tLaborday2015_Strike_Stc[4][8155]["DataType"],"==",tLaborday2015_Strike_Stc[4][8155]["Data8"])
end

tNpcGossip[8155]["Text1-6"] = {611}
tNpcGossip[8155]["Text611"] = tLaborday2015_Strike_Text[8155]["Text611"]
tNpcGossip[8155]["tOption1-6"] = {41}
tNpcGossip[8155]["Option41"] = tLaborday2015_Strike_Text[8155]["Option41"]
tNpcGossip[8155]["ChkFunc1-6"] = function ()
	return Sys_ChkFullTime(tLaborday2015_Strike_Time["Aftime"])
end

--马夫王宝
tNpcFace[215] = 48
tNpcGossip[8156] = tNpcGossip[8156] or DefaultNpc:new{}
tNpcGossip[8156]["OptionHidden"] = 1

--1?段
tNpcGossip[8156]["Text1-1"] = {111}
tNpcGossip[8156]["Text111"] = tLaborday2015_Strike_Text[8156]["Text111"]
tNpcGossip[8156]["tOption1-1"] = {1}
tNpcGossip[8156]["Option1"] = tLaborday2015_Strike_Text[8156]["Option1"]
tNpcGossip[8156]["ChkFunc1-1"] = function ()
	return Sys_ChkFullTime(tLaborday2015_Strike_Time["Beftime"])
end

tNpcGossip[8156]["Text1-2"] = {121}
tNpcGossip[8156]["Text121"] = tLaborday2015_Strike_Text[8156]["Text121"]
tNpcGossip[8156]["tOption1-2"] = {2,3,4}
tNpcGossip[8156]["Option2"] = tLaborday2015_Strike_Text[8156]["Option2"]
tNpcGossip[8156]["Option3"] = tLaborday2015_Strike_Text[8156]["Option3"]
tNpcGossip[8156]["Option4"] = tLaborday2015_Strike_Text[8156]["Option4"]
tNpcGossip[8156]["OptionFunc2"]="Laborday2015_Strike_Option2_8153</N>8156"
tNpcGossip[8156]["OptionFunc3"]="Laborday2015_Strike_Option3_8156</N>8156"
tNpcGossip[8156]["ChkFunc1-2"] = function ()
	return Sys_ChkFullTime(tLaborday2015_Strike_Time[1])
end

tNpcGossip[8156]["Text2-3"] = {231,232}
tNpcGossip[8156]["Text231"] = tLaborday2015_Strike_Text[8156]["Text231"]
tNpcGossip[8156]["Text232"] = tLaborday2015_Strike_Text[8156]["Text232"]
tNpcGossip[8156]["tOption2-3"] = {7}
tNpcGossip[8156]["Option7"] = tLaborday2015_Strike_Text[8156]["Option7"]
tNpcGossip[8156]["OptionFunc7"]="Laborday2015_Strike_Option7_8156</N>8156"

tNpcGossip[8156]["Text2-5"] = {251}
tNpcGossip[8156]["Text251"] = tLaborday2015_Strike_Text[8156]["Text251"]
tNpcGossip[8156]["tOption2-5"] = {9}
tNpcGossip[8156]["Option9"] = tLaborday2015_Strike_Text[8156]["Option9"]

tNpcGossip[8156]["Text2-6"] = {261}
tNpcGossip[8156]["Text261"] = tLaborday2015_Strike_Text[8156]["Text261"]
tNpcGossip[8156]["tOption2-6"] = {10}
tNpcGossip[8156]["Option10"] = tLaborday2015_Strike_Text[8156]["Option10"]

--2?段
tNpcGossip[8156]["Text1-3"] = {131}
tNpcGossip[8156]["Text131"] = tLaborday2015_Strike_Text[8156]["Text131"]
tNpcGossip[8156]["tOption1-3"] = {11,12}
tNpcGossip[8156]["Option11"] = tLaborday2015_Strike_Text[8156]["Option11"]
tNpcGossip[8156]["Option12"] = tLaborday2015_Strike_Text[8156]["Option12"]
tNpcGossip[8156]["OptionFunc11"]="Laborday2015_Strike_Option11_8153</N>8156"
tNpcGossip[8156]["ChkFunc1-3"] = function ()
	if Sys_ChkFullTime(tLaborday2015_Strike_Time[2]) and 
		Task_ChkStcValue(tLaborday2015_Strike_Stc[2][1]["EventType"],tLaborday2015_Strike_Stc[2][1]["DataType"],"==",0) and 
		Task_ChkStcValue(tLaborday2015_Strike_Stc[2][8156]["EventType"],tLaborday2015_Strike_Stc[2][8156]["DataType"],"==",0) then
		return true
	end
		return false
end

tNpcGossip[8156]["Text1-7"] = {321,322}
tNpcGossip[8156]["Text321"] = tLaborday2015_Strike_Text[8156]["Text321"]
tNpcGossip[8156]["Text322"] = tLaborday2015_Strike_Text[8156]["Text322"]
tNpcGossip[8156]["tOption1-7"] = {13}
tNpcGossip[8156]["Option13"] = tLaborday2015_Strike_Text[8156]["Option13"]
tNpcGossip[8156]["ChkFunc1-7"] = function ()
	if Sys_ChkFullTime(tLaborday2015_Strike_Time[2]) and 
		Task_ChkStcValue(tLaborday2015_Strike_Stc[2][1]["EventType"],tLaborday2015_Strike_Stc[2][1]["DataType"],"==",0) and
		Laborday2015_Strike_ChkattendanceSheet() then
		return true
	end
		return false
end

tNpcGossip[8156]["Text1-8"] = {331,332}
tNpcGossip[8156]["Text331"] = tLaborday2015_Strike_Text[8156]["Text331"]
tNpcGossip[8156]["Text332"] = tLaborday2015_Strike_Text[8156]["Text332"]
tNpcGossip[8156]["tOption1-8"] = {14,15}
tNpcGossip[8156]["Option14"] = tLaborday2015_Strike_Text[8156]["Option14"]
tNpcGossip[8156]["Option15"] = tLaborday2015_Strike_Text[8156]["Option15"]
tNpcGossip[8156]["OptionFunc14"]="Laborday2015_Strike_Option14_8154</N>8156"
tNpcGossip[8156]["ChkFunc1-8"] = function ()
	if Sys_ChkFullTime(tLaborday2015_Strike_Time[2]) and 
		Task_ChkStcValue(tLaborday2015_Strike_Stc[2][1]["EventType"],tLaborday2015_Strike_Stc[2][1]["DataType"],">=",tLaborday2015_Strike_Stc[2][1]["Data"]) then
		return true
	end
		return false
end

tNpcGossip[8156]["Text1-9"] = {341,342}
tNpcGossip[8156]["Text341"] = tLaborday2015_Strike_Text[8156]["Text341"]
tNpcGossip[8156]["tOption1-9"] = {16}
tNpcGossip[8156]["Option16"] = tLaborday2015_Strike_Text[8156]["Option16"]
tNpcGossip[8156]["ChkFunc1-9"] = function ()
	if Sys_ChkFullTime(tLaborday2015_Strike_Time[2]) and 
		Task_ChkStcValue(tLaborday2015_Strike_Stc[2][1]["EventType"],tLaborday2015_Strike_Stc[2][1]["DataType"],"==",0) and 
		Task_ChkStcValue(tLaborday2015_Strike_Stc[2][8156]["EventType"],tLaborday2015_Strike_Stc[2][8156]["DataType"],">=",tLaborday2015_Strike_Stc[2][8156]["Data"]) and
		not Laborday2015_Strike_ChkattendanceSheet() then
		return true
	end

end

tNpcGossip[8156]["Text3-5"] = {351}
tNpcGossip[8156]["Text351"] = tLaborday2015_Strike_Text[8156]["Text351"]
tNpcGossip[8156]["tOption3-5"] = {17}
tNpcGossip[8156]["Option17"] = tLaborday2015_Strike_Text[8156]["Option17"]

--3?段
tNpcGossip[8156]["Text1-4"] = {411}
tNpcGossip[8156]["Text411"] = tLaborday2015_Strike_Text[8156]["Text411"]
tNpcGossip[8156]["tOption1-4"] = {22,23,24}
tNpcGossip[8156]["Option22"] = tLaborday2015_Strike_Text[8156]["Option22"]
tNpcGossip[8156]["Option23"] = tLaborday2015_Strike_Text[8156]["Option23"]
tNpcGossip[8156]["Option24"] = tLaborday2015_Strike_Text[8156]["Option24"]
tNpcGossip[8156]["OptionFunc22"]="Laborday2015_Strike_Option22_8153</N>8156"
tNpcGossip[8156]["OptionFunc23"]="Laborday2015_Strike_Option23_8153</N>8156"
tNpcGossip[8156]["ChkFunc1-4"] = function ()
	return Sys_ChkFullTime(tLaborday2015_Strike_Time[3])
end

tNpcGossip[8156]["Text4-2"] = {421}
tNpcGossip[8156]["Text421"] = tLaborday2015_Strike_Text[8156]["Text421"]
tNpcGossip[8156]["tOption4-2"] = {25}
tNpcGossip[8156]["Option25"] = tLaborday2015_Strike_Text[8156]["Option25"]

tNpcGossip[8156]["Text4-3"] = {431}
tNpcGossip[8156]["Text431"] = tLaborday2015_Strike_Text[8156]["Text431"]
tNpcGossip[8156]["tOption4-3"] = {26}
tNpcGossip[8156]["Option26"] = tLaborday2015_Strike_Text[8156]["Option26"]

tNpcGossip[8156]["Text4-4"] = {441}
tNpcGossip[8156]["Text441"] = tLaborday2015_Strike_Text[8156]["Text441"]
tNpcGossip[8156]["tOption4-4"] = {27}
tNpcGossip[8156]["Option27"] = tLaborday2015_Strike_Text[8156]["Option27"]

tNpcGossip[8156]["Text5-1"] = {511}
tNpcGossip[8156]["Text511"] = tLaborday2015_Strike_Text[8156]["Text511"]
tNpcGossip[8156]["tOption5-1"] = {28}
tNpcGossip[8156]["Option28"] = tLaborday2015_Strike_Text[8156]["Option28"]
tNpcGossip[8156]["OptionFunc28"]="Laborday2015_Strike_Option28_8153</N>8156"

--4?段
tNpcGossip[8156]["Text1-5"] = {151}
tNpcGossip[8156]["Text151"] = tLaborday2015_Strike_Text[8156]["Text151"]
tNpcGossip[8156]["tOption1-5"] = {30}
tNpcGossip[8156]["Option30"] = tLaborday2015_Strike_Text[8156]["Option30"]
tNpcGossip[8156]["OptionFunc30"]="Laborday2015_Strike_Option30_8153</N>8156"
tNpcGossip[8156]["ChkFunc1-5"] = function ()
	return Sys_ChkFullTime(tLaborday2015_Strike_Time[4])
end

tNpcGossip[8156]["Text5-2"] = {521,522}
tNpcGossip[8156]["Text521"] = tLaborday2015_Strike_Text[8156]["Text521"]
tNpcGossip[8156]["Text522"] = tLaborday2015_Strike_Text[8156]["Text522"]
tNpcGossip[8156]["tOption5-2"] = {31,32}
tNpcGossip[8156]["Option31"] = tLaborday2015_Strike_Text[8156]["Option31"]
tNpcGossip[8156]["Option32"] = tLaborday2015_Strike_Text[8156]["Option32"]
tNpcGossip[8156]["OptionFunc31"]="Laborday2015_Strike_Option31_8153</N>8156"

tNpcGossip[8156]["Text5-3"] = {531,532}
tNpcGossip[8156]["Text531"] = tLaborday2015_Strike_Text[8156]["Text531"]
tNpcGossip[8156]["Text532"] = tLaborday2015_Strike_Text[8156]["Text532"]
tNpcGossip[8156]["tOption5-3"] = {33,34}
tNpcGossip[8156]["Option33"] = tLaborday2015_Strike_Text[8156]["Option33"]
tNpcGossip[8156]["Option34"] = tLaborday2015_Strike_Text[8156]["Option34"]
tNpcGossip[8156]["OptionFunc33"]="Laborday2015_Strike_Option33_8153</N>8156"

tNpcGossip[8156]["Text5-4"] = {541,542}
tNpcGossip[8156]["Text541"] = tLaborday2015_Strike_Text[8156]["Text541"]
tNpcGossip[8156]["Text542"] = tLaborday2015_Strike_Text[8156]["Text542"]
tNpcGossip[8156]["tOption5-4"] = {35,36,37}
tNpcGossip[8156]["Option35"] = tLaborday2015_Strike_Text[8156]["Option35"]
tNpcGossip[8156]["Option36"] = tLaborday2015_Strike_Text[8156]["Option36"]
tNpcGossip[8156]["Option37"] = tLaborday2015_Strike_Text[8156]["Option37"]
tNpcGossip[8156]["OptionFunc35"]="Laborday2015_Strike_Option35_8153</N>8156"
tNpcGossip[8156]["OptionFunc36"]="Laborday2015_Strike_Option36_8153</N>8156"
tNpcGossip[8156]["OptionChkFunc35"] = function ()
	return Task_ChkStcValue(tLaborday2015_Strike_Stc[4][8156]["EventType"],tLaborday2015_Strike_Stc[4][8156]["DataType"],"==",tLaborday2015_Strike_Stc[4][8156]["Data5"])
end
tNpcGossip[8156]["OptionChkFunc36"] = function ()
	return Task_ChkStcValue(tLaborday2015_Strike_Stc[4][8156]["EventType"],tLaborday2015_Strike_Stc[4][8156]["DataType"],"==",tLaborday2015_Strike_Stc[4][8156]["Data6"])
end

tNpcGossip[8156]["Text5-5"] = {551,552}
tNpcGossip[8156]["Text551"] = tLaborday2015_Strike_Text[8156]["Text551"]
tNpcGossip[8156]["Text552"] = tLaborday2015_Strike_Text[8156]["Text552"]
tNpcGossip[8156]["tOption5-5"] = {38,39,40}
tNpcGossip[8156]["Option38"] = tLaborday2015_Strike_Text[8156]["Option38"]
tNpcGossip[8156]["Option39"] = tLaborday2015_Strike_Text[8156]["Option39"]
tNpcGossip[8156]["Option40"] = tLaborday2015_Strike_Text[8156]["Option40"]
tNpcGossip[8156]["OptionFunc38"]="Laborday2015_Strike_Option38_8153</N>8156"
tNpcGossip[8156]["OptionFunc39"]="Laborday2015_Strike_Option39_8153</N>8156"
tNpcGossip[8156]["OptionChkFunc38"] = function ()
	return Task_ChkStcValue(tLaborday2015_Strike_Stc[4][8156]["EventType"],tLaborday2015_Strike_Stc[4][8156]["DataType"],"==",tLaborday2015_Strike_Stc[4][8156]["Data7"])
end
tNpcGossip[8156]["OptionChkFunc39"] = function ()
	return Task_ChkStcValue(tLaborday2015_Strike_Stc[4][8156]["EventType"],tLaborday2015_Strike_Stc[4][8156]["DataType"],"==",tLaborday2015_Strike_Stc[4][8156]["Data8"])
end

tNpcGossip[8156]["Text1-6"] = {611}
tNpcGossip[8156]["Text611"] = tLaborday2015_Strike_Text[8156]["Text611"]
tNpcGossip[8156]["tOption1-6"] = {41}
tNpcGossip[8156]["Option41"] = tLaborday2015_Strike_Text[8156]["Option41"]
tNpcGossip[8156]["ChkFunc1-6"] = function ()
	return Sys_ChkFullTime(tLaborday2015_Strike_Time["Aftime"])
end

--怪物掉落
-- 第一片区
	-- 1	叫天鸡	9593200
-- tMonster[1] = tMonster[1] or {}
-- tMonster[1]["tFunction"] = tMonster[1]["tFunction"] or {}
-- table.insert(tMonster[1]["tFunction"],tLaborday2015_Strike_Monster)










