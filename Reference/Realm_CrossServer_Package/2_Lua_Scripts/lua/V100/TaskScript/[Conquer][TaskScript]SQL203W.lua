------------------------------------------------------------------------------------
--Name:		[征服][任务脚本]SQL203W系统自检集中营
--Purpose:	SQL203W系统自检集中营
--Creator: 	严振飞
--Created:	2015/05/28
------------------------------------------------------------------------------------
--在后面的sql的制作中，203W的制作都用lua实现

--例子
------------------------------------------------------------------------------------
---150528[征服][活动脚本]系统自检例子
---SQL BY:严振飞
---DATE:2015-05-28
------------------------------------------------------------------------------------
---活动时间：2015-6-17 00:00 2015-7-17 23:59（方便下架）


--function FuncName_Prompet()
	--触发逻辑部分
--end
-----------------------------------------
--tSystem_Prompet_Func		实时检测
--table.insert(tSystem_Prompet_Func,FuncName_Prompet)

-----------------------------------------
--tOntimerMin_M		分钟（每小时的10分执行）
--'10-10'	
--tOntimerMin_M[10] = tOntimerMin_M[10] or {}
--table.insert(tOntimerMin_M[10],FuncName_Prompet)

-----------------------------------------
--tOntimerMin_HM	小时/分钟（每天的10点00分到10点02分执行）
--'10:00-10:02'
--tOntimerMin_HM[1000] = tOntimerMin_HM[1000] or {}
--table.insert(tOntimerMin_HM[1000],FuncName_Prompet)
--tOntimerMin_HM[1001] = tOntimerMin_HM[1001] or {}
--table.insert(tOntimerMin_HM[1001],FuncName_Prompet)
--tOntimerMin_HM[1002] = tOntimerMin_HM[1002] or {}
--table.insert(tOntimerMin_HM[1002],FuncName_Prompet)

-----------------------------------------
--tOntimerMin_wHM	周/小时/分钟（每周6的10点00分到10点02分执行）
--'6 10:00 - 6 10:02'
--tOntimerMin_wHM[61000] = tOntimerMin_M[61000] or {}
--table.insert(tOntimerMin_wHM[61000],FuncName_Prompet)
--tOntimerMin_wHM[61001] = tOntimerMin_M[61001] or {}
--table.insert(tOntimerMin_wHM[61001],FuncName_Prompet)
--tOntimerMin_wHM[61002] = tOntimerMin_M[61002] or {}
--table.insert(tOntimerMin_wHM[61002],FuncName_Prompet)

-----------------------------------------
--tOntimerMin_dHM	天/小时/分钟（每月的15号10点00分到10点02分执行）
--'15 10:00 - 15 10:02'
--tOntimerMin_dHM[151000] = tOntimerMin_M[151000] or {}
--table.insert(tOntimerMin_dHM[151000],FuncName_Prompet)
--tOntimerMin_dHM[151001] = tOntimerMin_M[151001] or {}
--table.insert(tOntimerMin_dHM[151001],FuncName_Prompet)
--tOntimerMin_dHM[151002] = tOntimerMin_M[151002] or {}
--table.insert(tOntimerMin_dHM[151002],FuncName_Prompet)














