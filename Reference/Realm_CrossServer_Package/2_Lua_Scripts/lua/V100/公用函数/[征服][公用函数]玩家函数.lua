----------------------------------------------------------------------------
--Name:		[征服][公用函数]玩家函数.lua
--Purpose:	玩家函数接口
--Creator: 	林锦
--Created:	2014/06/26
----------------------------------------------------------------------------
---------------------------------命名规范----------------------------------
------------------------------actiontype的分类------------------------------
--Sys  玩家所有
--Send 消息发送
--Get  获得属性
--Set  修改属性
--Chk  检查属性
--Del  删除属性
--Add  添加属性
------------------------------------------------------------------------------
-- 玩家函数命名前缀词：User_
--例子：
--(fn_CheckLeftSpace, "CheckLeftSpace");//检查玩家空格子数，参1:玩家ID, 参2:空格数量


--function User_ChkBagSpace(nUserId,nNum)
--
--end

------------------------------------------------------------------------------

--检查玩家空格子数 
--(fn_CheckLeftSpace, "CheckLeftSpace");		
--参数说明：参1:玩家ID, 参2:空格数量
--返回：有空间 ture 没空间false
function User_CheckLeftSpace(nSpaceNum,nUserId)
	if nUserId == nil then
		nUserId = 0
	elseif type(nUserId) ~= "number" or nUserId%1 ~= 0 or nUserId < 0 then
		Sys_SaveAbnormalLog("函数 User_CheckLeftSpace 第二个参数nUserId 为整型并且大于等于0")
		return
	end	
	
	if type(nSpaceNum) ~= "number" or nSpaceNum%1 ~= 0 or nSpaceNum <= 0 then
		Sys_SaveAbnormalLog("函数 User_CheckLeftSpace 中 nSpaceNum 只能传大于0的整数")
		return
	end

	return CheckLeftSpace(nUserId,nSpaceNum)
end


--玩家变身
--TransformByItem		
--参数说明：参1:玩家ID, 参2:技能类型ID, 参3:技能等级, 参4:怪物类型ID, 参5:持续时间
--返回
function User_TransForm(nSkill,nSkillType,nMonsterType,nTime,nUserId)
	if nUserId == nil then
		nUserId = 0
	elseif type(nUserId) ~= "number" or nUserId%1 ~= 0 or nUserId < 0 then
		Sys_SaveAbnormalLog("函数 User_TransForm 中 nUserId 为整型并且大于等于0")
		return
	end	
	
	if type(nSkill) ~= "number" or nSkill%1 ~= 0 or nSkill <= 0 then
		Sys_SaveAbnormalLog("函数 User_TransForm 中 nSkill 只能传大于0的整数")
		return
	end
	
	if type(nSkillType) ~= "number" or nSkillType%1 ~= 0 or nSkillType < 0 then
		Sys_SaveAbnormalLog("函数 User_TransForm 中 nSkillType 只能传大于等于0的整数")
		return
	end
	
	if type(nMonsterType) ~= "number" or nMonsterType%1 ~= 0 or nMonsterType <= 0 then
		Sys_SaveAbnormalLog("函数 User_TransForm 中 nMonsterType 只能传大于0的整数")
		return
	end
		
	if type(nTime) ~= "number" or nTime%1 ~= 0 or nTime <= 0 then
		Sys_SaveAbnormalLog("函数 User_TransForm 中 nTime 只能传大于0的整数")
		return
	end	

	return TransformByItem(nUserId,nSkill,nSkillType,nMonsterType,nTime)
end


--玩家切地图
--(fn_ChgMap, "ChgMap");			
--参数说明：参1:玩家ID, 参2:地图ID, 参3:坐标X, 参4:坐标Y, 参5:是否可以出监狱 	参照 ACTION_USER_CHGMAP = 1003
--返回玩家切地图的坐标点
function User_ChgMap(nMapId,nCellx,nCelly,nIsOutPrison,nUserId)
	if nUserId == nil then
		nUserId = 0
	elseif type(nUserId) ~= "number" or nUserId%1 ~= 0 or nUserId < 0 then
		Sys_SaveAbnormalLog("函数 User_ChgMap  中 nUserId 为整型并且大于等于0")
		return
	end	
	
	if type(nMapId) ~= "number" or nMapId%1 ~= 0 or nMapId <= 0 then
		Sys_SaveAbnormalLog("函数 User_ChgMap 中 nMapId 只能传大于0的整数")
		return
	end
	
	if type(nCellx) ~= "number" or nCellx%1 ~= 0 or nCellx <= 0 then
		Sys_SaveAbnormalLog("函数 User_ChgMap 中 nCellx 只能传大于0的整数")
		return
	end
	
	if type(nCelly) ~= "number" or nCelly%1 ~= 0 or nCelly <= 0 then
		Sys_SaveAbnormalLog("函数 User_ChgMap 中 nCelly 只能传大于0的整数")
		return
	end
	
	if nIsOutPrison == nil then
		nIsOutPrison = 0
	elseif type(nIsOutPrison) ~= "number" or nIsOutPrison%1 ~= 0 or nIsOutPrison < 0 or nIsOutPrison > 1  then
		Sys_SaveAbnormalLog("函数 User_ChgMap 中 nIsOutPrison 只能传（0，1）的整数")
		return
	end	

	return ChgMap(nUserId,nMapId,nCellx,nCelly,nIsOutPrison)
end


--记录玩家坐标	
--(fn_RecordPoint, "RecordPoint");	
--参数说明：参1:玩家ID, 参2:地图ID, 参3:坐标X, 参4:坐标Y 			参照 ACTION_USER_RECORDPOINT = 1004 
----返回记录玩家坐标
function User_RecordPoint(nMapId,nCellx,nCelly,nUserId)
	if nUserId == nil then
		nUserId = 0
	elseif type(nUserId) ~= "number" or nUserId%1 ~= 0 or nUserId < 0 then
		Sys_SaveAbnormalLog("函数 User_RecordPoint  中 nUserId 为整型并且大于等于0")
		return
	end
	
	if type(nMapId) ~= "number" or nMapId%1 ~= 0 or nMapId <= 0 then
		Sys_SaveAbnormalLog("函数 User_RecordPoint 中 nMapId 只能传大于0的整数")
		return
	end
	
	if type(nCellx) ~= "number" or nCellx%1 ~= 0 or nCellx <= 0 then
		Sys_SaveAbnormalLog("函数 User_RecordPoint 中 nCellx 只能传大于0的整数")
		return
	end
	
	if type(nCelly) ~= "number" or nCelly%1 ~= 0 or nCelly <= 0 then
		Sys_SaveAbnormalLog("函数 User_RecordPoint 中 nCelly 只能传大于0的整数")
		return
	end
	
	return RecordPoint(nUserId,nMapId,nCellx,nCelly)
end


--玩家发言之2002动作频道	
--(fn_Talk, "Talk");
--参数说明：参1:玩家ID, 参2:频道, 参3:内容  						参照 ACTION_USER_TALK = 1010
--频道=2002;	 	动作
--返回2002动作频道	
function User_TalkChannel2002(sContent,nUserId)
	if nUserId == nil then
		nUserId = 0
	elseif type(nUserId) ~= "number" or nUserId%1 ~= 0 or nUserId < 0 then
		Sys_SaveAbnormalLog("函数 User_TalkChannel2002  中 nUserId 为整型并且大于等于0")
		return
	end
	
	if type(sContent) ~= "string" then
		Sys_SaveAbnormalLog("函数 User_TalkChannel2002 中 sContent 只能传字符串")
		return
	end	
	
	return Talk(nUserId,2002,sContent)
end



--玩家发言之2003队伍频道	
--(fn_Talk, "Talk");				
--参数说明：参1:玩家ID, 参2:频道, 参3:内容  						参照 ACTION_USER_TALK = 1010
--频道=2003;	 	动作
--返回2003队伍频道的对白
function User_TalkChannel2003(sContent,nUserId)
	if nUserId == nil then
		nUserId = 0
	elseif type(nUserId) ~= "number" or nUserId%1 ~= 0 or nUserId < 0 then
		Sys_SaveAbnormalLog("函数 User_TalkChannel2003  中 nUserId 为整型并且大于等于0")
		return
	end
	
	if type(sContent) ~= "string" then
		Sys_SaveAbnormalLog("函数 User_TalkChannel2003 中 sContent 只能传字符串")
		return
	end	

	return Talk(nUserId,2003,sContent)
end


--玩家发言之2005系统频道	
--(fn_Talk, "Talk");				
--参数说明：参1:玩家ID, 参2:频道, 参3:内容  						参照 ACTION_USER_TALK = 1010
--频道=2005;	 	系统
--返回2005系统频道
function User_TalkChannel2005(sContent,nUserId)
	if nUserId == nil then
		nUserId = 0
	elseif type(nUserId) ~= "number" or nUserId%1 ~= 0 or nUserId < 0 then
		Sys_SaveAbnormalLog("函数 User_TalkChannel2005  中 nUserId 为整型并且大于等于0")
		return
	end
	
	if type(sContent) ~= "string" then
		Sys_SaveAbnormalLog("函数 User_TalkChannel2005 中 sContent 只能传字符串")
		return
	end	
	
	return Talk(nUserId,2005,sContent)
end



--玩家发言之2007交谈频道	
--(fn_Talk, "Talk");			
--参数说明：参1:玩家ID, 参2:频道, 参3:内容  						参照 ACTION_USER_TALK = 1010
--频道=2007;	 	交谈
--返回2007交谈频道
function User_TalkChannel2007(sContent,nUserId)
	if nUserId == nil then
		nUserId = 0
	elseif type(nUserId) ~= "number" or nUserId%1 ~= 0 or nUserId < 0 then
		Sys_SaveAbnormalLog("函数 User_TalkChannel2007  中 nUserId 为整型并且大于等于0")
		return
	end
	
	if type(sContent) ~= "string" then
		Sys_SaveAbnormalLog("函数 User_TalkChannel2007 中 sContent 只能传字符串")
		return
	end	
	
	return Talk(nUserId,2007,sContent)
end



--玩家发言之2011GM频道	
--(fn_Talk, "Talk");		
--参数说明：参1:玩家ID, 参2:频道, 参3:内容  						参照 ACTION_USER_TALK = 1010
--频道=2011;	 	GM频道
--返回2011GM频道
function User_TalkChannel2011(sContent,nUserId)
	if nUserId == nil then
		nUserId = 0
	elseif type(nUserId) ~= "number" or nUserId%1 ~= 0 or nUserId < 0 then
		Sys_SaveAbnormalLog("函数 User_TalkChannel2011  中 nUserId 为整型并且大于等于0")
		return
	end
	
	if type(sContent) ~= "string" then
		Sys_SaveAbnormalLog("函数 User_TalkChannel2011 中 sContent 只能传字符串")
		return
	end		

	return Talk(nUserId,2011,sContent)
end



--玩家添加特效
--(fn_Effect, "Effect");	
--参数说明：参1:玩家ID, 参2:szObj, 参3:szEffect, 参4:szOpt   		参照 ACTION_USER_EFFECT = 1027,
--szObj支持"self", "couple", "team", szEffect为特效名称, szOpt支持"add", "del"
--返回玩家添加特效
function User_EffectAdd(nSzObj,sEffect,nUserId)
	if nUserId == nil then
		nUserId = 0
	elseif type(nUserId) ~= "number" or nUserId%1 ~= 0 or nUserId < 0 then
		Sys_SaveAbnormalLog("函数 User_EffectAdd  中 nUserId 为整型并且大于等于0")
		return
	end
	
	if type(sEffect) ~= "string" then
		Sys_SaveAbnormalLog("函数 User_EffectAdd 中 sEffect 只能传字符串")
		return
	end
	
	if type(nSzObj) ~= "string" then
		Sys_SaveAbnormalLog("函数 User_EffectAdd 中 nSzObj 只能传字符串")
		return
	end		
	
	if nSzObj == "self" then
		return Effect(nUserId,"self",sEffect,"add")
	elseif 	nSzObj == "couple" then 
		return Effect(nUserId,"couple",sEffect,"add")
	elseif 	nSzObj == "team"	then
		return Effect(nUserId,"team",sEffect,"add")
	end

end



--玩家删除特效
--(fn_Effect, "Effect");	
--参数说明：参1:玩家ID, 参2:szObj, 参3:szEffect, 参4:szOpt   		参照 ACTION_USER_EFFECT = 1027,
--szObj支持"self", "couple", "team", szEffect为特效名称, szOpt支持"add", "del"
--返回玩家删除特效
function User_EffectDel(nSzObj,sEffect,nUserId)
	if nUserId == nil then
		nUserId = 0
	elseif type(nUserId) ~= "number" or nUserId%1 ~= 0 or nUserId < 0 then
		Sys_SaveAbnormalLog("函数 User_EffectDel  中 nUserId 为整型并且大于等于0")
		return
	end
	
	if type(sEffect) ~= "string" then
		Sys_SaveAbnormalLog("函数 User_EffectDel 中 sEffect 只能传字符串")
		return
	end
	
	if type(nSzObj) ~= "string" then
		Sys_SaveAbnormalLog("函数 User_EffectDel 中 nSzObj 只能传字符串")
		return
	end		
	
	if nSzObj == "self" then
		return Effect(nUserId,"self",sEffect,"del")
	elseif 	nSzObj == "couple" then 
		return Effect(nUserId,"couple",sEffect,"del")
	elseif 	nSzObj == "team"	then
		return Effect(nUserId,"team",sEffect,"del")
	end
end



--玩家修正战斗最终所获经验值
--SetExpControl	
--参数说明：参1:玩家ID, 参2:加成百分比, 参3:时间, 					参照 ACTION_USER_PLUSEXP = 1048
--返回玩家修正战斗最终所获经验值(X倍经验)
function User_SetExpControl(nPercent,nTime,nUserId)
	if nUserId == nil then
		nUserId = 0
	elseif type(nUserId) ~= "number" or nUserId%1 ~= 0 or nUserId < 0 then
		Sys_SaveAbnormalLog("函数 User_SetExpControl  中 nUserId 为整型并且大于等于0")
		return
	end
	
	if type(nPercent) ~= "number" or nPercent%1 ~= 0 or nPercent <= 0 then
		Sys_SaveAbnormalLog("函数 User_SetExpControl 中 nPercent 只能传大于0的整数")
		return
	end
	
	if type(nTime) ~= "number" or nTime%1 ~= 0 or nTime <= 0 then
		Sys_SaveAbnormalLog("函数 User_SetExpControl 中 nTime 只能传大于0的整数")
		return
	end	

	return SetExpControl(nUserId,nPercent,nTime)
end



--向在队伍频道中广播一条消息
--(fn_BroadcastTeamMsg, "BroadcastTeamMsg");	
--参数说明：参1:玩家ID, 参2:内容			参照 ACTION_TEAM_BROADCAST = 1101,
--返回队伍频道中广播一条消息
function User_BroadcastTeamMsg(nContent,nUserId)
	if nUserId == nil then
		nUserId = 0
	elseif type(nUserId) ~= "number" or nUserId%1 ~= 0 or nUserId < 0 then
		Sys_SaveAbnormalLog("函数 User_BroadcastTeamMsg  中 nUserId 为整型并且大于等于0")
		return
	end
	
	if type(nContent) ~= "string" then
		Sys_SaveAbnormalLog("函数 User_BroadcastTeamMsg 中 nContent 只能传字符串")
		return
	end			
	
	return BroadcastTeamMsg(nUserId,nContent)
end

--组队切屏
--(fn_TeamChgMap, "TeamChgMap");		
--参数说明：参1:玩家ID, 参2:地图ID，参3:X坐标, 参4:Y坐标				参照 ACTION_TEAM_CHGMAP        = 1107
--返回组队切屏（必须队长触发）
function User_TeamChgMap(nMapId,nCellx,nCelly,nUserId)
	if nUserId == nil then
		nUserId = 0
	elseif type(nUserId) ~= "number" or nUserId%1 ~= 0 or nUserId < 0 then
		Sys_SaveAbnormalLog("函数 User_TeamChgMap  中 nUserId 为整型并且大于等于0")
		return
	end
	
	if type(nMapId) ~= "number" or nMapId%1 ~= 0 or nMapId <= 0 then
		Sys_SaveAbnormalLog("函数 User_TeamChgMap 中 nMapId 只能传大于0的整数")
		return
	end
	
	if type(nCellx) ~= "number" or nCellx%1 ~= 0 or nCellx <= 0 then
		Sys_SaveAbnormalLog("函数 User_TeamChgMap 中 nCellx 只能传大于0的整数")
		return
	end
	
	if type(nCelly) ~= "number" or nCelly%1 ~= 0 or nCelly <= 0 then
		Sys_SaveAbnormalLog("函数 User_TeamChgMap 中 nCelly 只能传大于0的整数")
		return
	end	
	
	return TeamChgMap(nUserId,nMapId,nCellx,nCelly)
end

--玩家是否队长
--(fn_IsTeamLeader, "IsTeamLeader");		
--参数说明：参1:玩家ID
--返回玩家是否队长
function User_IsTeamLeader(nUserId)
	if nUserId == nil then
		nUserId = 0
	elseif type(nUserId) ~= "number" or nUserId%1 ~= 0 or nUserId < 0 then
		Sys_SaveAbnormalLog("函数 User_IsTeamLeader  中 nUserId 为整型并且大于等于0")
		return
	end	
	
	return IsTeamLeader(nUserId)
end

--全队执行某个LUA函数(只有队长可以触发)	
--TeamExeFuncByLeader	
--参数说明：参1:玩家ID  参2:范围(1:触发者附近 2:本地图 3:所有地图)  参3:LUA函数     失败返回false，否则返回true
--返回全队执行某个LUA函数(只有队长可以触发)	
function User_TeamExeFuncByLeader(nRange,sFunc,nUserId)
	if nUserId == nil then
		nUserId = 0
	elseif type(nUserId) ~= "number" or nUserId%1 ~= 0 or nUserId < 0 then
		Sys_SaveAbnormalLog("函数 User_TeamExeFuncByLeader  中 nUserId 为整型并且大于等于0")
		return
	end
	
	if type(nRange) ~= "number" or nRange%1 ~= 0 or nRange <= 0 or nRange > 3 then
		Sys_SaveAbnormalLog("函数 User_TeamExeFuncByLeader 中 nRange 只能传(1,2,3)的整数")
		return
	end
	
	if type(sFunc) ~= "string" then
		Sys_SaveAbnormalLog("函数 User_TeamExeFuncByLeader 中 sFunc 只能传字符串")
		return
	end		
	
	return TeamExeFuncByLeader(nUserId,nRange,string.format("</F>%s",sFunc))
end

--全队执行某个LUA函数(队员可以触发)	
--TeamExeFuncByTeamer			
--参数说明：参1:玩家ID  参2:范围(1:触发者附近 2:本地图 3:所有地图)  参3:LUA函数     失败返回false，否则返回true
--返回全队执行某个LUA函数(队员可以触发)	
function User_TeamExeFuncByTeamer(nRange,sFunc,nUserId)
	if nUserId == nil then
		nUserId = 0
	elseif type(nUserId) ~= "number" or nUserId%1 ~= 0 or nUserId < 0 then
		Sys_SaveAbnormalLog("函数 User_TeamExeFuncByTeamer  中 nUserId 为整型并且大于等于0")
		return
	end
	
	if type(nRange) ~= "number" or nRange%1 ~= 0 or nRange <= 0 or nRange > 3 then
		Sys_SaveAbnormalLog("函数 User_TeamExeFuncByTeamer 中 nUserId 只能传(1,2,3)的整数")
		return
	end
	
	if type(sFunc) ~= "string" then
		Sys_SaveAbnormalLog("函数 User_TeamExeFuncByTeamer 中 sFunc 只能传字符串")
		return
	end		
	
	return TeamExeFuncByTeamer(nUserId,nRange,string.format("</F>%s",sFunc))
end



--将玩家传送到地图的随机点
--ACTION_USER_RAND_TRANS   = 1509,     
--bool UserRandTrans(int idUser, int idMap, int nCheck);            
--参数说明: idUser表示指定玩家, 填0表示当前玩家, idMap表示指定的地图, 为0时表示玩家当前所在地图, nCheck表示检查地图属性, 非0表示要检查. 如果失败返回false, 成功返回true.
--返回将玩家传送到地图的随机点
function User_UserRandTrans(nMapId,nCheck,nUserId)
	if nUserId == nil then
		nUserId = 0
	elseif type(nUserId) ~= "number" or nUserId%1 ~= 0 or nUserId < 0 then
		Sys_SaveAbnormalLog("函数 User_UserRandTrans  中 nUserId 为整型并且大于等于0")
		return
	end
	
	if type(nMapId) ~= "number" or nMapId%1 ~= 0 or nMapId < 0 then
		Sys_SaveAbnormalLog("函数 User_UserRandTrans 中 nMapId 只能传大于等于0的整数")
		return
	end
	
	if nCheck == nil then
		nCheck = 0
	elseif type(nCheck) ~= "number" or nCheck%1 ~= 0 or nCheck < 0 then
		Sys_SaveAbnormalLog("函数 User_UserRandTrans 中 nCheck 只能传大于0的整数")
		return
	end	

	return UserRandTrans(nUserId,nMapId,nCheck)
end

--将玩家传送到地图的指定区域.
--bool UserRandBoundTrans(int idUser, int idMap, int nCheck， int nBoundX, int nBoundY, int nBoundCX, int nBoundCY);
--参数说明: idUser表示指定玩家, 填0表示当前玩家, idMap表示指定的地图, 为0时表示玩家当前所在地图, nCheck表示检查地图属性，非0表示要检查;
--nBoundX, nBoundY表示这个区域的左上角的坐标, nBoundCX, nBoundCY表示这个区域的范围. 如果失败返回false, 成功返回true.
--返回将玩家传送到地图的指定区域.
function User_UserRandBoundTrans(nMapId,nBoundX,nBoundY,nBoundCX,nBoundCY,nCheck,nUserId)
	if nUserId == nil then
		nUserId = 0
	elseif type(nUserId) ~= "number" or nUserId%1 ~= 0 or nUserId < 0 then
		Sys_SaveAbnormalLog("函数 User_UserRandBoundTrans  中 nUserId 为整型并且大于等于0")
		return
	end
	
	if type(nMapId) ~= "number" or nMapId%1 ~= 0 or nMapId < 0 then
		Sys_SaveAbnormalLog("函数 User_UserRandBoundTrans 中 nMapId 只能传大于等于0的整数")
		return
	end
	
	if nCheck == nil then
		nCheck = 0
	elseif type(nCheck) ~= "number" or nCheck%1 ~= 0 or nCheck < 0 then
		Sys_SaveAbnormalLog("函数 User_UserRandBoundTrans 中 nCheck 只能传大于0的整数")
		return
	end	
	
	if type(nBoundX) ~= "number" or nBoundX%1 ~= 0 or nBoundX <= 0 then
		Sys_SaveAbnormalLog("函数 User_UserRandBoundTrans 中 nBoundX 只能传大于0的整数")
		return
	end
	
	if type(nBoundY) ~= "number" or nBoundY%1 ~= 0 or nBoundY <= 0 then
		Sys_SaveAbnormalLog("函数 User_UserRandBoundTrans 中 nBoundY 只能传大于0的整数")
		return
	end
	
	if type(nBoundCX) ~= "number" or nBoundCX%1 ~= 0 or nBoundCX <= 0 then
		Sys_SaveAbnormalLog("函数 User_UserRandBoundTrans 中 nBoundCX 只能传大于0的整数")
		return
	end
	
	if type(nBoundCY) ~= "number" or nBoundCY%1 ~= 0 or nBoundCY <= 0 then
		Sys_SaveAbnormalLog("函数 User_UserRandBoundTrans 中 nBoundCY 只能传大于0的整数")
		return
	end	
	
	return UserRandBoundTrans(nUserId,nMapId,nCheck,nBoundX,nBoundY,nBoundCX,nBoundCY)
end

-- 4. 设置寄存器变量值接口：void  SetUserVarData(int UserId, int nInx, int nData);
-- 参数1：玩家id，参数2：索引;3.寄存器变量值
-- 返回值：无
function User_SetVarData(nInx,nData,nUserId)
	if type(nInx) ~= "number" or nInx > 7 or nInx < 0 or nInx%1 ~= 0 then
		Sys_SaveAbnormalLog("函数 User_SetVarData 参数 nInx 必须为整型并且在0-7之间")
		return
	end
	
	if type(nData) ~= "number" or nData < 0 or nData%1 ~= 0 then
		Sys_SaveAbnormalLog("函数 User_SetVarData 参数 nData 必须为整型并且大于等于0")
		return
	end
	
	if nUserId == nil then
		nUserId = 0
	elseif type(nUserId) ~= "number" or nUserId < 0 or nUserId%1 ~= 0 then
		Sys_SaveAbnormalLog("函数 User_SetVarData 参数 nUserId 必须为整型并且大于等于0")
		return
	end
	
	return SetUserVarData(nUserId,nInx,nData)
end


-- 6. 设置寄存器变量值字符串类型）接口：void  SetUserVarStr(int UserId, int nInx, char* pData);
-- 参数1：玩家id，参数2：索引;3.寄存器变量值
-- 返回值：无
function User_SetVarStr(nInx,sDataStr,nUserId)
	if type(nInx) ~= "number" or nInx > 7 or nInx < 0 or nInx%1 ~= 0 then
		Sys_SaveAbnormalLog("函数 User_SetVarStr 参数 nInx 必须为整型并且在0-7之间")
		return
	end
	
	if type(sDataStr) ~= "string" then
		Sys_SaveAbnormalLog("函数 User_SetVarStr 参数 sDataStr 必须为字符串")
		return
	end
	
	if nUserId == nil then
		nUserId = 0
	elseif type(nUserId) ~= "number" or nUserId < 0 or nUserId%1 ~= 0 then
		Sys_SaveAbnormalLog("函数 User_SetVarStr 参数 nUserId 必须为整型并且大于等于0")
		return
	end
	
	return SetUserVarStr(nUserId,nInx,sDataStr)
end

-- //ACTION_USER_CAL_EXP 1084  ACTION_USER_TIME_TO_EXP	1086
-- bool CalcUserExp(OBJID idUser, __int64 n64ExpAdd, DWORD dwIdxLev, DWORD dwIdxPercent);
-- bool CalcUserTimeToExp(OBJID idUser, DWORD dwTime, DWORD idx);
--1084	计算指定数值的exp对当前用户的影响, 输出目标级别和百分比数值到指定的寄存器变量
--// param为"exp_add idx_lev idx_percent"
--// exp_add为添加的exp值, idx_lev为目标级别输出的寄存器变量索引, idx_percent为目标百分比输出的寄存器变量索引,
--// 寄存器变量索引为 0-7
-- bool CalcUserExp(OBJID idUser, __int64 n64ExpAdd, DWORD dwIdxLev, DWORD dwIdxPercent);
function User_CalcExp(nExpAdd,nUserId)
	if type(nExpAdd) ~= "number" or nExpAdd < 0 or nExpAdd%1 ~= 0 then
		Sys_SaveAbnormalLog("函数 User_CalcExp 参数 nExpAdd 必须为整型并且大于等于0")
		return
	end

	if nUserId == nil then
		nUserId = 0
	elseif type(nUserId) ~= "number" or nUserId < 0 or nUserId%1 ~= 0 then
		Sys_SaveAbnormalLog("函数 User_CalcExp 参数 nUserId 必须为整型并且大于等于0")
		return
	end

	return Sys_Split(CalcUserExp(nUserId,nExpAdd)," ")
end


-- 1086 // 折算一定的升级时间到当前用户的经验数字, 输出到指定的寄存器变量                                       
-- // param为"time idx_exp", time为升级时间，单位和cq_levexp表中的uplevtime相同，idx_exp为寄存器变量索引， 
-- // 寄存器变量索引为 0-7                                                                                 
-- bool CalcUserTimeToExp(OBJID idUser, DWORD dwTime, DWORD idx);
function User_CalcTimeToExp(nTime,nUserId)
	if type(nTime) ~= "number" or nTime < 0 or nTime%1 ~= 0 then
		Sys_SaveAbnormalLog("函数 User_CalcTimeToExp 参数 nTime 必须为整型并且大于等于0")
		return
	end

	if nUserId == nil then
		nUserId = 0
	elseif type(nUserId) ~= "number" or nUserId < 0 or nUserId%1 ~= 0 then
		Sys_SaveAbnormalLog("函数 User_CalcTimeToExp 参数 nUserId 必须为整型并且大于等于0")
		return
	end
	
	return CalcUserTimeToExp(nUserId,nTime)
end


-- //user status
-- //ACTION_USER_STATUS 1082

--AddRoleStatus(objid idRole,int nType,int nPower,int nInterval,int ucLeaveTimes,int unRemainTime,int unEndTime,int ucRecordable,int usFrom,int unData)
--idRole 角色ID  nType 状态类型 nInterval 状态持续时间 ucLeaveTimes 状态次数 unRemainTime 剩余时间 unEndTime 有效时长 ucRecordable 是否入库 usFrom 数据来源 unData 其它内容(action传0)

-- bool DelRoleStatus(OBJID idUser, DWORD dwStatus);
-- bool ChkRoleStatus(OBJID idUser, DWORD dwStatus);
-- bool AddUserTeamStatus(OBJID idUser, DWORD dwStatus, int nPower , int nSecs, int nTimes);
-- bool DelUserTeamStatus(OBJID idUser, DWORD dwStatus);
-- bool ChkUserTeamStatus(OBJID idUser, DWORD dwStatus);
-- 1082,			// 附加或删除指定的状态，param为"obj opr status power seconds times", 
-- // obj支持"self", "mate", "couple", "team", 注意team不包含自己, 如果没有队伍，返回失败
-- //		另外，"mate"选项如果对方不在线，返回失败
-- // opr支持"add", "del", "chk"
-- // power为状态力度参数，
-- // seconds为状态延续的秒数
-- // times为状态激发的次数, 只激发一次的填0


--1000007--你把idRole改为 用户id,直接调用接口不行
function User_AddRoleStatus(nStatus,nPower,nSecs,nTimes,nunRemainTime,nunEndTime,nucRecordable,nusFrom,nunData,nUserId)
	if type(nStatus) ~= "number" or nStatus <= 0 or nStatus%1 ~= 0 then
		Sys_SaveAbnormalLog("函数 User_AddRoleStatus 参数 nStatus 必须为整型并且大于0")
		return
	end
	
	if type(nPower) ~= "number" or nPower < 0 or nPower%1 ~= 0 then
		Sys_SaveAbnormalLog("函数 User_AddRoleStatus 参数 nPower 必须为整型并且大于等于0")
		return
	end

	if type(nSecs) ~= "number" or nSecs < 0 or nSecs%1 ~= 0 then
		Sys_SaveAbnormalLog("函数 User_AddRoleStatus 参数 nSecs 必须为整型并且大于等于0")
		return
	end

	if type(nTimes) ~= "number" or nTimes < 0 or nTimes%1 ~= 0 then
		Sys_SaveAbnormalLog("函数 User_AddRoleStatus 参数 nTimes 必须为整型并且大于等于0")
		return
	end
	
	if type(nunRemainTime) ~= "number" or nunRemainTime < 0 or nunRemainTime%1 ~= 0 then
		Sys_SaveAbnormalLog("函数 User_AddRoleStatus 参数 nunRemainTime 必须为整型并且大于等于0")
		return
	end

	if type(nunEndTime) ~= "number" or nunEndTime < 0 or nunEndTime%1 ~= 0 then
		Sys_SaveAbnormalLog("函数 User_AddRoleStatus 参数 nunEndTime 必须为整型并且大于等于0")
		return
	end

	if type(nucRecordable) ~= "number" or nucRecordable < 0 or nucRecordable%1 ~= 0 then
		Sys_SaveAbnormalLog("函数 User_AddRoleStatus 参数 nucRecordable 必须为整型并且大于等于0")
		return
	end

	if type(nusFrom) ~= "number" or nusFrom < 0  or nusFrom%1 ~= 0 then
		Sys_SaveAbnormalLog("函数 User_AddRoleStatus 参数 nusFrom 必须为整型并且大于等于0")
		return
	end

	if type(nunData) ~= "number" or nunData < 0  or nunData%1 ~= 0 then
		Sys_SaveAbnormalLog("函数 User_AddRoleStatus 参数 nunData 必须为整型并且大于等于0")
		return
	end

	if type(nUserId) ~= "number" or nUserId <= 0 or nUserId%1 ~= 0 then
		Sys_SaveAbnormalLog("函数 User_AddRoleStatus 参数 nUserId 必须为整型并且大于等于0")
		return
	end
	
	return AddRoleStatus(nUserId,nStatus,nPower,nSecs,nTimes,nunRemainTime,nunEndTime,nucRecordable,nusFrom,nunData)
end

function User_DelRoleStatus(nStatus,nUserId)
	if type(nStatus) ~= "number" or nStatus <= 0 or nStatus%1 ~= 0 then
		Sys_SaveAbnormalLog("函数 User_DelRoleStatus 参数 nStatus 必须为整型并且大于0")
		return
	end
	
	if type(nUserId) ~= "number" or nUserId <= 0 or nUserId%1 ~= 0 then
		Sys_SaveAbnormalLog("函数 User_DelRoleStatus 参数 nUserId 必须为整型并且大于等于0")
		return
	end

	return DelRoleStatus(nUserId,nStatus)
end

function User_ChkRoleStatus(nStatus,nUserId)
	if type(nStatus) ~= "number" or nStatus <= 0 or nStatus%1 ~= 0 then
		Sys_SaveAbnormalLog("函数 User_ChkRoleStatus 参数 nStatus 必须为整型并且大于0")
		return
	end

	if type(nUserId) ~= "number" or nUserId <= 0 or nUserId%1 ~= 0 then
		Sys_SaveAbnormalLog("函数 User_ChkRoleStatus 参数 nUserId 必须为整型并且大于等于0")
		return
	end

	return ChkRoleStatus(nUserId,nStatus)
end

-- bool AddUserTeamStatus(OBJID idUser, DWORD dwStatus, int nPower , int nSecs, int nTimes);
function User_AddTeamStatus(nStatus,nPower,nSecs,nTimes,nUserId)
	if type(nStatus) ~= "number" or nStatus <= 0 or nStatus%1 ~= 0 then
		Sys_SaveAbnormalLog("函数 User_AddTeamStatus 参数 nStatus 必须为整型并且大于0")
		return
	end

	if type(nPower) ~= "number" or nPower < 0 or nPower%1 ~= 0 then
		Sys_SaveAbnormalLog("函数 User_AddTeamStatus 参数 nPower 必须为整型并且大于等于0")
		return
	end

	if type(nSecs) ~= "number" or nSecs < 0 or nSecs%1 ~= 0 then
		Sys_SaveAbnormalLog("函数 User_AddTeamStatus 参数 nSecs 必须为整型并且大于等于0")
		return
	end
	
	if type(nTimes) ~= "number" or nTimes < 0 or nTimes%1 ~= 0 then
		Sys_SaveAbnormalLog("函数 User_AddTeamStatus 参数 nTimes 必须为整型并且大于等于0")
		return
	end

	if type(nUserId) ~= "number" or nUserId <= 0 or nUserId%1 ~= 0 then
		Sys_SaveAbnormalLog("函数 User_AddTeamStatus 参数 nUserId 必须为整型并且大于等于0")
		return
	end

	return AddUserTeamStatus(nUserId,nStatus,nPower,nSecs,nTimes)
end

-- bool DelUserTeamStatus(OBJID idUser, DWORD dwStatus);
function User_DelTeamStatus(nStatus,nUserId)
	if type(nStatus) ~= "number" or nStatus <= 0 or nStatus%1 ~= 0 then
		Sys_SaveAbnormalLog("函数 User_DelTeamStatus 参数 nStatus 必须为整型并且大于0")
		return
	end

	if type(nUserId) ~= "number" or nUserId <= 0 or nUserId%1 ~= 0 then
		Sys_SaveAbnormalLog("函数 User_DelTeamStatus 参数 nUserId 必须为整型并且大于等于0")
		return
	end

	return DelUserTeamStatus(nUserId,nStatus)
end

-- bool ChkUserTeamStatus(OBJID idUser, DWORD dwStatus);
function User_ChkTeamStatus(nStatus,nUserId)
	if type(nStatus) ~= "number" or nStatus <= 0 or nStatus%1 ~= 0 then
		Sys_SaveAbnormalLog("函数 User_ChkTeamStatus 参数 nStatus 必须为整型并且大于0")
		return
	end

	if type(nUserId) ~= "number" or nUserId <= 0 or nUserId%1 ~= 0 then
		Sys_SaveAbnormalLog("函数 User_ChkTeamStatus 参数 nUserId 必须为整型并且大于0")
		return
	end

	return ChkUserTeamStatus(nUserId,nStatus)
end


-----------20140822---------
--// 记录玩家练气和武功日志. 参数说明: idUser表示玩家ID. 如果失败返回false, 成功返回true.
--LUA_FUNC(GongfuAndFateValueLog)
--	OBJID idUser = Lua_GetParamUInt(1);
--生成文件在gmlog/syn_templog
function User_GongfuAndFateValueLog(nUserId)
	if nUserId == nil then
		nUserId = 0
	elseif type(nUserId) ~= "number" or nUserId < 0 or nUserId%1 ~= 0 then
		Sys_SaveAbnormalLog("函数 User_GongfuAndFateValueLog 中 nUserId 只能传大于等于0的整数")
		return
	end

	return GongfuAndFateValueLog(nUserId)
end




-- //检查背包剩余空间是否有data数量大小   	参1:玩家ID，参2:格子数量，	有队员空间小于nData就返回false，否则返回true
-- LUA_FUNC(TeamLeaveSpace)
	-- OBJID idUser		= Lua_GetParamUInt(1);
	-- int nData			= Lua_GetParamUInt(2);
--只能队长触发，所有队员触发都返回false
function User_ChkTeamSpace(nSpace,nUserId)
	if type(nSpace) ~= "number" or nSpace <= 0 or nSpace%1 ~= 0 then
		Sys_SaveAbnormalLog("函数 User_ChkTeamSpace 中 nSpace 只能传大于0的整数")
		return
	end

	if nUserId == nil then
		nUserId = 0
	elseif type(nUserId) ~= "number" or nUserId < 0 or nUserId%1 ~= 0 then
		Sys_SaveAbnormalLog("函数 User_ChkTeamSpace 中 nUserId 只能传大于等于0的整数")
		return
	end

	return TeamLeaveSpace(nUserId,nSpace)
end


-- //队伍成员添加物品(在调用此接口的时候必须先调用TeamLeaveSpace来判断背包空间)   	参1:玩家ID，参2:物品类型ID，		失败返回false，否则返回true
-- LUA_FUNC(TeamAddItem)
	-- OBJID idUser		= Lua_GetParamUInt(1);
	-- OBJID idItemType	= Lua_GetParamUInt(2);

function User_AddTeamItem(nItemtype,nUserId)
	if type(nItemtype) ~= "number" or nItemtype <= 0 or nItemtype%1 ~= 0 then
		Sys_SaveAbnormalLog("函数 User_AddTeamItem 中 nItemtype 只能传大于0的整数")
		return
	end

	if nUserId == nil then
		nUserId = 0
	elseif type(nUserId) ~= "number" or nUserId < 0 or nUserId%1 ~= 0 then
		Sys_SaveAbnormalLog("函数 User_AddTeamItem 中 nUserId 只能传大于等于0的整数")
		return
	end

	if Item_ChkTeamSpace(1) then
		return TeamAddItem(nUserId,nItemtype)
	else 
		Sys_SaveAbnormalLog("队伍中有玩家的背包空间不足，请提醒队员整理背包。")
		return
	end

end



-- //队伍成员删除物品(在调用此接口之前必须先调用TeamCheckItem接口判断是否有物品)   	参1:玩家ID，参2:物品类型ID，		失败返回false，否则返回true
-- LUA_FUNC(TeamDelItem)
	-- OBJID idUser		= Lua_GetParamUInt(1);
	-- OBJID idItemType	= Lua_GetParamUInt(2);
-- //队伍成员检查是否有某物品   	参1:玩家ID，参2:物品类型ID，		失败返回false，否则返回true

function User_DelTeamItem(nItemtype,nUserId)

	if type(nItemtype) ~= "number" or nItemtype <= 0 or nItemtype%1 ~= 0 then
		Sys_SaveAbnormalLog("函数 User_DelTeamItem 中 nItemtype 只能传大于0的整数")
		return
	end

	if nUserId == nil then
		nUserId = 0
	elseif type(nUserId) ~= "number" or nUserId < 0 or nUserId%1 ~= 0 then
		Sys_SaveAbnormalLog("函数 User_DelTeamItem 中 nUserId 只能传大于等于0的整数")
		return
	end

	if Item_ChkTeamItem(nItemtype) then
		return TeamDelItem(nUserId,nItemtype)
	else 
		Sys_SaveAbnormalLog("队伍中有玩家没有该物品，请提醒队员检查是否有该物品。")
		return
	end

end



-- LUA_FUNC(TeamCheckItem)
	-- OBJID idUser		= Lua_GetParamUInt(1);
	-- OBJID idItemType	= Lua_GetParamUInt(2);
--所有成员都有才ture，否则返回false
function User_ChkTeamItem(nItemtype,nUserId)
	if type(nItemtype) ~= "number" or nItemtype <= 0 or nItemtype%1 ~= 0 then
		Sys_SaveAbnormalLog("函数 User_ChkTeamItem 中 nItemtype 只能传大于0的整数")
		return
	end

	if nUserId == nil then
		nUserId = 0
	elseif type(nUserId) ~= "number" or nUserId < 0 or nUserId%1 ~= 0 then
		Sys_SaveAbnormalLog("函数 User_ChkTeamItem 中 nUserId 只能传大于等于0的整数")
		return
	end

	return TeamCheckItem(nUserId,nItemtype)
end

-- //脱下装备   	参1:玩家ID，		失败返回false，否则返回true
-- LUA_FUNC(UnequipItem)
	-- OBJID idUser	= Lua_GetParamUInt(1);
	-- int nPosition	= Lua_GetParamUInt(2);

function User_UnequipItem(nPos,nUserId)
	if type(nPos) ~= "number" or nPos < 0 or nPos > 8 or nPos%1 ~= 0 then
		Sys_SaveAbnormalLog("函数 User_UnequipItem 中 nPos 只能传1~8的整数")
		return
	end

	if nUserId == nil then
		nUserId = 0
	elseif type(nUserId) ~= "number" or nUserId < 0 or nUserId%1 ~= 0 then
		Sys_SaveAbnormalLog("函数 User_UnequipItem 中 nUserId 只能传大于等于0的整数")
		return
	end

	return UnequipItem(nUserId,nPos)
end

-- //武器技能等级检查		参1: 玩家ID，参2:技能类型ID，参3：等级	小于nLev返回false，否则返回true
-- LUA_FUNC(SkillCheckLev)
	-- OBJID idUser	= Lua_GetParamInt(1);
	-- OBJID idType	= Lua_GetParamInt(2);
	-- int	  nLev		= Lua_GetParamInt(3);

function User_SkillChkLev(nSkillType,nLev,nUserId)
	if type(nSkillType) ~= "number" or nSkillType <= 0 or nSkillType%1 ~= 0 then
		Sys_SaveAbnormalLog("函数 User_SkillChkLev 中 nSkillType 只能传大于0的整数")
		return
	end

	if type(nLev) ~= "number" or nLev <= 0 or nLev%1 ~= 0 then
		Sys_SaveAbnormalLog("函数 User_SkillChkLev 中 nTime 只能传大于0的整数")
		return
	end

	if nUserId == nil then
		nUserId = 0
	elseif type(nUserId) ~= "number" or nUserId < 0 or nUserId%1 ~= 0 then
		Sys_SaveAbnormalLog("函数 User_SkillChkLev 中 nUserId 只能传大于等于0的整数")
		return
	end

	return SkillCheckLev(nUserId,nSkillType,nLev)
end


-- //学习武器技能		参1: 玩家ID，参2:技能类型ID，参3：等级	失败返回false，否则返回true
-- LUA_FUNC(LearnSkill)
	-- OBJID idUser	= Lua_GetParamInt(1);
	-- OBJID idType	= Lua_GetParamInt(2);
	-- int	  nLev		= Lua_GetParamInt(3);
--可增可减，只要武器技能编号存在就可以设置。
--执行成功后，level字段等于nlev参数。
function User_SkillLearn(nSkillType,nLev,nUserId)
	if type(nSkillType) ~= "number" or nSkillType <= 0 or nSkillType%1 ~= 0 then
		Sys_SaveAbnormalLog("函数 User_SkillLearn 中 nSkillType 只能传大于0的整数")
		return
	end

	if type(nLev) ~= "number" or nLev <= 0 or nLev%1 ~= 0 then
		Sys_SaveAbnormalLog("函数 User_SkillLearn 中 nTime 只能传大于0的整数")
		return
	end

	if nUserId == nil then
		nUserId = 0
	elseif type(nUserId) ~= "number" or nUserId < 0 or nUserId%1 ~= 0 then
		Sys_SaveAbnormalLog("函数 User_SkillLearn 中 nUserId 只能传大于等于0的整数")
		return
	end

	return LearnSkill(nUserId,nSkillType,nLev)
end

-- //增加武器技能经验		参1: 玩家ID，参2:技能类型ID，参3：经验。	失败返回false，否则返回true
-- LUA_FUNC(SkillAddExp)
	-- OBJID idUser	= Lua_GetParamInt(1);
	-- OBJID idType	= Lua_GetParamInt(2);
	-- int	  nExp		= Lua_GetParamInt(3);
--客户端会立刻显示，但数据库不会时时保存。
--未学过的武器熟练度，数据库会新建数据，但客户端看不到。
function User_SkillAddExp(nSkillType,nExp,nUserId)
	if type(nSkillType) ~= "number" or nSkillType <= 0 or nSkillType%1 ~= 0 then
		Sys_SaveAbnormalLog("函数 User_SkillAddExp 中 nSkillType 只能传大于0的整数")
		return
	end

	if type(nExp) ~= "number" or nExp <= 0 or nExp%1 ~= 0 then
		Sys_SaveAbnormalLog("函数 User_SkillAddExp 中 nExp 只能传大于0的整数")
		return
	end

	if nUserId == nil then
		nUserId = 0
	elseif type(nUserId) ~= "number" or nUserId < 0 or nUserId%1 ~= 0 then
		Sys_SaveAbnormalLog("函数 User_SkillAddExp 中 nUserId 只能传大于等于0的整数")
		return
	end

	return SkillAddExp(nUserId,nSkillType,nExp)
end


-- //增加武器技能经验		参1: 玩家ID，参2:技能类型ID，参3：时间(程序将换算成经验)。	失败返回false，否则返回true
-- LUA_FUNC(SkillAddLevTime)
	-- OBJID idUser	= Lua_GetParamInt(1);
	-- OBJID idType	= Lua_GetParamInt(2);
	-- int	  nTime		= Lua_GetParamInt(3);
--客户端会立刻显示，但数据库不会时时保存。
--未学过的武器熟练度，数据库会新建数据，但客户端看不到。
function User_SkillAddExpByTime(nSkillType,nTime,nUserId)
	if type(nSkillType) ~= "number" or nSkillType <= 0 or nSkillType%1 ~= 0 then
		Sys_SaveAbnormalLog("函数 User_SkillAddExpByTime 中 nSkillType 只能传大于0的整数")
		return
	end

	if type(nTime) ~= "number" or nTime <= 0 or nTime%1 ~= 0 then
		Sys_SaveAbnormalLog("函数 User_SkillAddExpByTime 中 nTime 只能传大于0的整数")
		return
	end

	if nUserId == nil then
		nUserId = 0
	elseif type(nUserId) ~= "number" or nUserId < 0 or nUserId%1 ~= 0 then
		Sys_SaveAbnormalLog("函数 User_SkillAddExpByTime 中 nUserId 只能传大于等于0的整数")
		return
	end

	return SkillAddExp(nUserId,nSkillType,nTime)
end


-- //掷骰子分配物品		参1:玩家ID，参2:物品类型ID，参3：分配类型(目前只有0这一种)		失败返回false，否则返回true
-- LUA_FUNC(TeamDice)
	-- OBJID	idUser		= Lua_GetParamUInt(1);
	-- OBJID	idItemType	= Lua_GetParamUInt(2);
	-- int		nType		= Lua_GetParamUInt(3);
--队员队长都可以触发。
function User_TeamDice(nItemtype,nUserId)
	if type(nItemtype) ~= "number" or nItemtype <= 0 or nItemtype%1 ~= 0 then
		Sys_SaveAbnormalLog("函数 User_TeamDice 中 nItemtype 只能传大于0的整数")
		return
	end

	if nUserId == nil then
		nUserId = 0
	elseif type(nUserId) ~= "number" or nUserId < 0 or nUserId%1 ~= 0 then
		Sys_SaveAbnormalLog("函数 User_TeamDice 中 nUserId 只能传大于等于0的整数")
		return
	end

	return TeamDice(nUserId,nItemtype,0)
end


-- //玩家最后一次离线时间相关操作		参1:玩家ID，参2:操作方式，参3：存取		失败返回false，否则返回true
-- LUA_FUNC(UserLastLoginOperator)
	-- OBJID	idUser		= Lua_GetParamUInt(1);
	-- OBJID	nType		= Lua_GetParamUInt(2);
	-- UINT	unParam		= Lua_GetParamUInt(3);

--nTime的格式为"yyyymmdd"，例如："20070405"
--如果最后一次离线时间，比输入的时间参数早，则返回false。
--反之，返回ture。
function User_LastLoginOperatorByTime(nTime,nUserId)
	if nTime == nil then
		nTime = os.date("%Y%m%d")
	elseif type(nTime) ~= "number" or nTime <= 0 or nTime%1 ~= 0 then
		Sys_SaveAbnormalLog("函数 User_LastLoginOperatorByTime 中 nTime 只能传大于0的整数")
		return
	end

	if nUserId == nil then
		nUserId = 0
	elseif type(nUserId) ~= "number" or nUserId < 0 or nUserId%1 ~= 0 then
		Sys_SaveAbnormalLog("函数 User_LastLoginOperatorByTime 中 nUserId 只能传大于等于0的整数")
		return
	end
	BrocastMsg(2011,tostring(UserLastLoginOperator(nUserId,0,nTime)))
	return UserLastLoginOperator(nUserId,0,nTime)
end




-- //判定玩家身上是否有光环，参数说明： idUser玩家ID ,有光环返回真，无光环返回假
-- LUA_FUNC(IsExistHalo)
	-- OBJID idUser = Lua_GetParamUInt(1);

function User_IsExistHalo(nUserId)
	if nUserId == nil then
		nUserId = 0
	elseif type(nUserId) ~= "number" or nUserId < 0 or nUserId%1 ~= 0 then
		Sys_SaveAbnormalLog("函数 User_IsExistHalo 中 nUserId 只能传大于等于0的整数")
		return
	end

	return IsExistHalo(nUserId)
end


-- // 删除玩家身上的光环，参数说明： idUser玩家ID
-- LUA_FUNC(ClsHalo)
	-- OBJID idUser = Lua_GetParamUInt(1);
--不论是否有无光环，删除玩家身上所有光环，且永远返回ture。
function User_DelHalo(nUserId)
	if nUserId == nil then
		nUserId = 0
	elseif type(nUserId) ~= "number" or nUserId < 0 or nUserId%1 ~= 0 then
		Sys_SaveAbnormalLog("函数 User_DelHalo 中 nUserId 只能传大于等于0的整数")
		return
	end

	return ClsHalo(nUserId)
end

-- //玩家保存指定信息到gm log	参数说明：szParam 指定要保存的信息
-- LUA_FUNC(MsgToGMLog)
	-- const char* szParam= Lua_GetParamString(1);
--生成的log在gmlog/月份/action.log下
function User_GmLog(sLogParam)
	if type(sLogParam) ~= "string" then
		Sys_SaveAbnormalLog("函数 User_GmLog 中 sLogParam 只能传字符串类型的参数")
		return
	end

	return MsgToGMLog(sLogParam)
end

--SCRIPT_PARAM_PLAYER_LookFace,	1003	//玩家头像编号	get 	set	
--玩家外形会直接改变
function User_SetLookFace(nFace,nUserId)
	if type(nFace) ~= "number" or nFace <= 0 or nFace%1 ~= 0 then
		Sys_SaveAbnormalLog("函数 User_SetLookFace 中 nFace 只能传大于0的整数")
		return
	end

	if nUserId == nil then
		nUserId = 0
	elseif type(nUserId) ~= "number" or nUserId < 0 or nUserId%1 ~= 0 then
		Sys_SaveAbnormalLog("函数 User_SetLookFace 中 nUserId 只能传大于等于0的整数")
		return
	end

	return SetUserInt(nUserId,G_PLAYER_LookFace,nFace,0)
end

--SCRIPT_PARAM_PLAYER_Profession,	1005	//玩家的职业	get 	set	
--若职业编号不存在，能执行成功，但是人物面板的职业描述会出现？？
function User_SetProfession(nProfession,nUserId)
	if type(nProfession) ~= "number" or nProfession <= 0 or nProfession%1 ~= 0 then
		Sys_SaveAbnormalLog("函数 User_SetProfession 中 nProfession 只能传大于0的整数")
		return
	end

	if nUserId == nil then
		nUserId = 0
	elseif type(nUserId) ~= "number" or nUserId < 0 or nUserId%1 ~= 0 then
		Sys_SaveAbnormalLog("函数 User_SetProfession 中 nUserId 只能传大于等于0的整数")
		return
	end

	return SetUserInt(nUserId,G_PLAYER_Profession,nProfession,0)
end

--只能传0，变成成初始状态。
--SCRIPT_PARAM_PLAYER_Transfrom,	1024	//变身ID	get	set	
function User_SetTransform(nUserId)
	if nUserId == nil then
		nUserId = 0
	elseif type(nUserId) ~= "number" or nUserId < 0 or nUserId%1 ~= 0 then
		Sys_SaveAbnormalLog("函数 User_SetTransform 中 nUserId 只能传大于等于0的整数")
		return
	end

	return SetUserInt(nUserId,G_PLAYER_Transfrom,0,0)
end

--SCRIPT_PARAM_PLAYER_Crime,	1038	//犯罪时间	get	set	
--设置不为0，玩家进入pk后的蓝名闪烁状态
function User_SetCrime(nCrime,nUserId)
	if type(nCrime) ~= "number" or nCrime <= 0 or nCrime%1 ~= 0 then
		Sys_SaveAbnormalLog("函数 User_SetCrime 中 nCrime 只能传大于0的整数")
		return
	end

	if nUserId == nil then
		nUserId = 0
	elseif type(nUserId) ~= "number" or nUserId < 0 or nUserId%1 ~= 0 then
		Sys_SaveAbnormalLog("函数 User_SetCrime 中 nUserId 只能传大于等于0的整数")
		return
	end

	return SetUserInt(nUserId,G_PLAYER_Crime,nCrime,0)
end

--SCRIPT_PARAM_PLAYER_XP,	1041	//当前XP值	get	set	add
function User_SetXp(nXp,nUserId)
	if type(nXp) ~= "number" or nXp < 0 or nXp%1 ~= 0 then
		Sys_SaveAbnormalLog("函数 User_SetXp 中 nXp 只能传大于等于0的整数")
		return
	end

	if nUserId == nil then
		nUserId = 0
	elseif type(nUserId) ~= "number" or nUserId < 0 or nUserId%1 ~= 0 then
		Sys_SaveAbnormalLog("函数 User_SetXp 中 nUserId 只能传大于等于0的整数")
		return
	end

	return SetUserInt(nUserId,G_PLAYER_XP,nXp,0)
end

--SCRIPT_PARAM_PLAYER_EP,	1042	//体力值	get	set	add
function User_SetEp(nEp,nUserId)
	if type(nEp) ~= "number" or nEp < 0 or nEp%1 ~= 0 then
		Sys_SaveAbnormalLog("函数 User_SetEp 中 nEp 只能传大于等于0的整数")
		return
	end

	if nUserId == nil then
		nUserId = 0
	elseif type(nUserId) ~= "number" or nUserId < 0 or nUserId%1 ~= 0 then
		Sys_SaveAbnormalLog("函数 User_SetEp 中 nUserId 只能传大于等于0的整数")
		return
	end

	return SetUserInt(nUserId,G_PLAYER_EP,nEp,0)
end

--SCRIPT_PARAM_PLAYER_AddPoint,	1043	//玩家属性点	get	set	add
function User_SetAddPoint(nAddPoint,nUserId)
	if type(nAddPoint) ~= "number" or nAddPoint < 0 or nAddPoint%1 ~= 0 then
		Sys_SaveAbnormalLog("函数 User_SetAddPoint 中 nAddPoint 只能传大于等于0的整数")
		return
	end

	if nUserId == nil then
		nUserId = 0
	elseif type(nUserId) ~= "number" or nUserId < 0 or nUserId%1 ~= 0 then
		Sys_SaveAbnormalLog("函数 User_SetAddPoint 中 nUserId 只能传大于等于0的整数")
		return
	end

	return SetUserInt(nUserId,G_PLAYER_AddPoint,nAddPoint,0)
end

--SCRIPT_PARAM_PLAYER_PKProtocol,	1054	//PK模式	get	set	
--修改cq_user表的PKProtocol字段
--重新登录才有效。
function User_SetPkProtocol(nPkProtocol,nUserId)
	if  nPkProtocol == 0 or nPkProtocol == 1 or nPkProtocol == 2 then
		Sys_SaveAbnormalLog("函数 User_SetPkProtocol 中 nPkProtocol 只能传0,1,2.")
		return
	end

	if nUserId == nil then
		nUserId = 0
	elseif type(nUserId) ~= "number" or nUserId < 0 or nUserId%1 ~= 0 then
		Sys_SaveAbnormalLog("函数 User_SetPkProtocol 中 nUserId 只能传大于等于0的整数")
		return
	end

	return SetUserInt(nUserId,G_PLAYER_PKProtocol,nPkProtocol,0)
end

--SCRIPT_PARAM_PLAYER_Level,	1006	//玩家等级	get		add
function User_AddLevel(nAddLevel,nUserId)
	if type(nAddLevel) ~= "number" or nAddLevel <= 0 or nAddLevel%1 ~= 0 then
		Sys_SaveAbnormalLog("函数 User_AddLevel 中 nAddLevel 只能传大于0的整数")
		return
	end

	if nUserId == nil then
		nUserId = 0
	elseif type(nUserId) ~= "number" or nUserId < 0 or nUserId%1 ~= 0 then
		Sys_SaveAbnormalLog("函数 User_AddLevel 中 nUserId 只能传大于等于0的整数")
		return
	end

	return AddUserInt(nUserId,G_PLAYER_Level,nAddLevel,0)
end

--SCRIPT_PARAM_PLAYER_Life,	1019	//玩家生命值	get		add
function User_AddLife(nAddLife,nUserId)
	if type(nAddLife) ~= "number" or nAddLife%1 ~= 0 then
		Sys_SaveAbnormalLog("函数 User_AddLife 中 nAddLife 只能传整数")
		return
	end

	if nUserId == nil then
		nUserId = 0
	elseif type(nUserId) ~= "number" or nUserId < 0 or nUserId%1 ~= 0 then
		Sys_SaveAbnormalLog("函数 User_AddLife 中 nUserId 只能传大于等于0的整数")
		return
	end

	return AddUserInt(nUserId,G_PLAYER_Life,nAddLife,0)
end

--SCRIPT_PARAM_PLAYER_Mana,	1021	//玩家法力值	get		add
function User_AddMana(nAddMana,nUserId)
	if type(nAddMana) ~= "number" or nAddMana%1 ~= 0 then
		Sys_SaveAbnormalLog("函数 User_AddMana 中 nAddMana 只能传整数")
		return
	end

	if nUserId == nil then
		nUserId = 0
	elseif type(nUserId) ~= "number" or nUserId < 0 or nUserId%1 ~= 0 then
		Sys_SaveAbnormalLog("函数 User_AddMana 中 nUserId 只能传大于等于0的整数")
		return
	end

	return AddUserInt(nUserId,G_PLAYER_Mana,nAddMana,0)
end

--SCRIPT_PARAM_PLAYER_Mentor,	1023	//玩家点化机会	get		add
--100点=1次点化机会
function User_AddMentor(nAddMentor,nUserId)
	if type(nAddMentor) ~= "number" or nAddMentor <= 0 or nAddMentor%1 ~= 0 then
		Sys_SaveAbnormalLog("函数 User_AddMentor 中 nAddMentor 只能传大于0的整数")
		return
	end

	if nUserId == nil then
		nUserId = 0
	elseif type(nUserId) ~= "number" or nUserId < 0 or nUserId%1 ~= 0 then
		Sys_SaveAbnormalLog("函数 User_AddMentor 中 nUserId 只能传大于等于0的整数")
		return
	end

	return AddUserInt(nUserId,G_PLAYER_Mentor,nAddMentor,0)
end

--SCRIPT_PARAM_PLAYER_Money,	1025	//玩家游戏币	get		add
function User_AddMoney(nAddMoney,nUserId)
	if type(nAddMoney) ~= "number" or nAddMoney%1 ~= 0 then
		Sys_SaveAbnormalLog("函数 User_AddMoney 中 nAddMoney 只能传整数")
		return
	end

	if math.abs(nAddMoney) > 2000000000 then
		Sys_SaveAbnormalLog("User_AddMoney blocked: money delta exceeds safe 32-bit operation limit")
		return
	end

	if nUserId == nil then
		nUserId = 0
	elseif type(nUserId) ~= "number" or nUserId < 0 or nUserId%1 ~= 0 then
		Sys_SaveAbnormalLog("函数 User_AddMoney 中 nUserId 只能传大于等于0的整数")
		return
	end

	return AddUserInt(nUserId,G_PLAYER_Money,nAddMoney,0)
end

--SCRIPT_PARAM_PLAYER_EMoney,	1027	//玩家天石	get		add
function User_AddEMoney(nAddEMoney,nUserId)
	if type(nAddEMoney) ~= "number" or nAddEMoney%1 ~= 0 then
		Sys_SaveAbnormalLog("函数 User_AddEMoney 中 nAddEMoney 只能传整数")
		return
	end

	if nUserId == nil then
		nUserId = 0
	elseif type(nUserId) ~= "number" or nUserId < 0 or nUserId%1 ~= 0 then
		Sys_SaveAbnormalLog("函数 User_AddEMoney 中 nUserId 只能传大于等于0的整数")
		return
	end

	return AddUserInt(nUserId,G_PLAYER_EMoney,nAddEMoney,0)
end

--SCRIPT_PARAM_PLAYER_EMoneyMono,	1028	//玩家赠点	get		add
function User_AddEMoneyMono(nAddEMoneyMono,nUserId)
	if type(nAddEMoneyMono) ~= "number" or nAddEMoneyMono%1 ~= 0 then
		Sys_SaveAbnormalLog("函数 User_AddEMoneyMono 中 nAddEMoneyMono 只能传整数")
		return
	end

	if nUserId == nil then
		nUserId = 0
	elseif type(nUserId) ~= "number" or nUserId < 0 or nUserId%1 ~= 0 then
		Sys_SaveAbnormalLog("函数 User_AddEMoneyMono 中 nUserId 只能传大于等于0的整数")
		return
	end

	return AddUserInt(nUserId,G_PLAYER_EMoneyMono,nAddEMoneyMono,0)
end

--SCRIPT_PARAM_PLAYER_Exp,	1029	//玩家经验(add操作不增加贡献)	get		add
function User_AddExp(nAddExp,nUserId)
	if type(nAddExp) ~= "number" or nAddExp <= 0 or nAddExp%1 ~= 0 then
		Sys_SaveAbnormalLog("函数 User_AddExp 中 nAddExp 只能传大于0的整数")
		return
	end

	if nUserId == nil then
		nUserId = 0
	elseif type(nUserId) ~= "number" or nUserId < 0 or nUserId%1 ~= 0 then
		Sys_SaveAbnormalLog("函数 User_AddExp 中 nUserId 只能传大于等于0的整数")
		return
	end

	return AddUserInt(nUserId,G_PLAYER_Exp,nAddExp,0)
end

--SCRIPT_PARAM_PLAYER_ExpContribute,	1030	//玩家经验(add操作增加贡献)			add
function User_AddExpContribute(nAddExpContribute,nUserId)
	if type(nAddExpContribute) ~= "number" or nAddExpContribute <= 0 or nAddExpContribute%1 ~= 0 then
		Sys_SaveAbnormalLog("函数 User_AddExpContribute 中 nAddExpContribute 只能传大于0的整数")
		return
	end

	if nUserId == nil then
		nUserId = 0
	elseif type(nUserId) ~= "number" or nUserId < 0 or nUserId%1 ~= 0 then
		Sys_SaveAbnormalLog("函数 User_AddExpContribute 中 nUserId 只能传大于等于0的整数")
		return
	end

	return AddUserInt(nUserId,G_PLAYER_ExpContribute,nAddExpContribute,0)
end


-- SCRIP_PARAM_PLAYER_ExpPercent	1065 //按百分比增加经验(不增加贡献)。
function User_AddExpPercent(nAddPercent,nUserId)
	if type(nAddPercent) ~= "number" or nAddPercent < 0 or nAddPercent > 100 or nAddPercent%1 ~= 0 then
		Sys_SaveAbnormalLog("函数 User_AddExpPercent 中 nAddPercent 只能传0-100的整数")
		return
	end
	
	if nUserId == nil then
		nUserId = 0
	elseif type(nUserId) ~= "number" or nUserId < 0 or nUserId%1 ~= 0 then
		Sys_SaveAbnormalLog("函数 User_AddExpPercent 中 nUserId 只能传大于等于0的整数")
		return
	end

	return AddUserInt(nUserId,G_PLAYER_ExpPercent,nAddPercent,0)
end


-- SCRIP_PARAM_PLAYER_ExpPercentContribute	1066 //按百分比增加经验(增加贡献)
function User_AddExpPercentContribute(nAddPercentContribute,nUserId)
	if type(nAddPercentContribute) ~= "number" or nAddPercentContribute < 0 or nAddPercentContribute > 100 or nAddPercentContribute%1 ~= 0 then
		Sys_SaveAbnormalLog("函数 User_AddExpPercentContribute 中 nAddPercentContribute 只能传0-100的整数")
		return
	end
	
	if nUserId == nil then
		nUserId = 0
	elseif type(nUserId) ~= "number" or nUserId < 0 or nUserId%1 ~= 0 then
		Sys_SaveAbnormalLog("函数 User_AddExpPercentContribute 中 nUserId 只能传大于等于0的整数")
		return
	end

	return AddUserInt(nUserId,G_PLAYER_ExpPercentContribute,nAddPercentContribute,0)
end


-- //增加玩家的经验时间（折算一定的升级时间到当前用户的经验）
-- //注意：nTime为增加经验的时间。单位是分钟，
-- //用到的接口：	User_CalcTimeToExp(nTime,nUserId)	--折算一定的升级时间到当前用户的经验数字（直接返回经验数值）
--					User_AddExp(nAddExp,nUserId)		--增加玩家经验
-- //User_AddExpTime(30)表示增加当前玩家30分钟经验。
function User_AddExpTime(nTime,nUserId)
	if type(nTime) ~= "number" or nTime < 0 or nTime%1 ~= 0 then
		Sys_SaveAbnormalLog("函数 User_AddExpTime 参数 nTime 必须为整型并且大于等于0")
		return
	end

	if nUserId == nil then
		nUserId = 0
	elseif type(nUserId) ~= "number" or nUserId < 0 or nUserId%1 ~= 0 then
		Sys_SaveAbnormalLog("函数 User_AddExpTime 参数 nUserId 必须为整型并且大于等于0")
		return
	end
	
	local nAddTime = nTime * 10
	local nAddExp = User_CalcTimeToExp(nAddTime,nUserId)
	return User_AddExp(nAddExp,nUserId)
end




--SCRIPT_PARAM_PLAYER_PK,	1031	//玩家PK值	get		add
--30变红，100变黑
function User_AddPk(nAddPk,nUserId)
	if type(nAddPk) ~= "number" or nAddPk%1 ~= 0 then
		Sys_SaveAbnormalLog("函数 User_AddPk 中 nAddPk 只能传整数")
		return
	end

	if nUserId == nil then
		nUserId = 0
	elseif type(nUserId) ~= "number" or nUserId < 0 or nUserId%1 ~= 0 then
		Sys_SaveAbnormalLog("函数 User_AddPk 中 nUserId 只能传大于等于0的整数")
		return
	end

	return AddUserInt(nUserId,G_PLAYER_PK,nAddPk,0)
end

--SCRIPT_PARAM_PLAYER_Strength,	1032	//玩家力量值	get		add
--建议不要使用，原因是，执行完后，面板上剩余点数显示很奇怪。
--当加数值时，如果面板在打开状态，不会直接加在力量值，而是剩余点数显示出加上的点数，且不会出现加点按钮。面板切换后，显示正常。
--当减数值时，情况同加法，只是在剩余数值部分会显示负数。
function User_AddStrength(nAddStrength,nUserId)
	if type(nAddStrength) ~= "number" or nAddStrength <= 0 or nAddStrength%1 ~= 0 then
		Sys_SaveAbnormalLog("函数 User_AddStrength 中 nAddStrength 只能传大于0的整数")
		return
	end

	if nUserId == nil then
		nUserId = 0
	elseif type(nUserId) ~= "number" or nUserId < 0 or nUserId%1 ~= 0 then
		Sys_SaveAbnormalLog("函数 User_AddStrength 中 nUserId 只能传大于等于0的整数")
		return
	end

	return AddUserInt(nUserId,G_PLAYER_Strength,nAddStrength,0)
end

--SCRIPT_PARAM_PLAYER_Speed,	1033	//玩家灵巧值	get		add
function User_AddSpeed(nAddSpeed,nUserId)
	if type(nAddSpeed) ~= "number" or nAddSpeed <= 0 or nAddSpeed%1 ~= 0 then
		Sys_SaveAbnormalLog("函数 User_AddSpeed 中 nAddSpeed 只能传大于0的整数")
		return
	end

	if nUserId == nil then
		nUserId = 0
	elseif type(nUserId) ~= "number" or nUserId < 0 or nUserId%1 ~= 0 then
		Sys_SaveAbnormalLog("函数 User_AddSpeed 中 nUserId 只能传大于等于0的整数")
		return
	end

	return AddUserInt(nUserId,G_PLAYER_Speed,nAddSpeed,0)
end

--SCRIPT_PARAM_PLAYER_Health,	1034	//玩家体力值	get		add
function User_AddHealth(nAddHealth,nUserId)
	if type(nAddHealth) ~= "number" or nAddHealth <= 0 or nAddHealth%1 ~= 0 then
		Sys_SaveAbnormalLog("函数 User_AddHealth 中 nAddHealth 只能传大于0的整数")
		return
	end

	if nUserId == nil then
		nUserId = 0
	elseif type(nUserId) ~= "number" or nUserId < 0 or nUserId%1 ~= 0 then
		Sys_SaveAbnormalLog("函数 User_AddHealth 中 nUserId 只能传大于等于0的整数")
		return
	end

	return AddUserInt(nUserId,G_PLAYER_Health,nAddHealth,0)
end

--SCRIPT_PARAM_PLAYER_Soul,	1035	//玩家精神值	get		add
function User_AddSoul(nAddSoul,nUserId)
	if type(nAddSoul) ~= "number" or nAddSoul <= 0 or nAddSoul%1 ~= 0 then
		Sys_SaveAbnormalLog("函数 User_AddSoul 中 nAddSoul 只能传大于0的整数")
		return
	end

	if nUserId == nil then
		nUserId = 0
	elseif type(nUserId) ~= "number" or nUserId < 0 or nUserId%1 ~= 0 then
		Sys_SaveAbnormalLog("函数 User_AddSoul 中 nUserId 只能传大于等于0的整数")
		return
	end

	return AddUserInt(nUserId,G_PLAYER_Soul,nAddSoul,0)
end

--SCRIPT_PARAM_PLAYER_XP,	1041	//当前XP值	get	set	add
--传入负数无效
function User_AddXp(nAddXp,nUserId)
	if type(nAddXp) ~= "number" or nAddXp <= 0 or nAddXp%1 ~= 0 then
		Sys_SaveAbnormalLog("函数 User_AddXp 中 nAddXp 只能传大于0的整数")
		return
	end

	if nUserId == nil then
		nUserId = 0
	elseif type(nUserId) ~= "number" or nUserId < 0 or nUserId%1 ~= 0 then
		Sys_SaveAbnormalLog("函数 User_AddXp 中 nUserId 只能传大于等于0的整数")
		return
	end

	return AddUserInt(nUserId,G_PLAYER_XP,nAddXp,0)
end

--SCRIPT_PARAM_PLAYER_EP,	1042	//体力值	get	set	add
function User_AddEp(nAddEp,nUserId)
	if type(nAddEp) ~= "number" or nAddEp%1 ~= 0 then
		Sys_SaveAbnormalLog("函数 User_AddEp 中 nAddEp 只能传整数")
		return
	end

	if nUserId == nil then
		nUserId = 0
	elseif type(nUserId) ~= "number" or nUserId < 0 or nUserId%1 ~= 0 then
		Sys_SaveAbnormalLog("函数 User_AddEp 中 nUserId 只能传大于等于0的整数")
		return
	end

	return AddUserInt(nUserId,G_PLAYER_EP,nAddEp,0)
end

--SCRIPT_PARAM_PLAYER_AddPoint,	1043	//玩家属性点	get	set	add
--当传入负数，若超出玩家当前剩余点数，会出现错误，剩余点数变成65535-扣太多的点数。
--所以，干脆把负数禁掉。
function User_AddAddPoint(nAddAddPoint,nUserId)
	if type(nAddAddPoint) ~= "number" or nAddAddPoint <=0 or nAddAddPoint%1 ~= 0 then
		Sys_SaveAbnormalLog("函数 User_AddAddPoint 中 nAddAddPoint 只能传大于0的整数")
		return
	end

	if nUserId == nil then
		nUserId = 0
	elseif type(nUserId) ~= "number" or nUserId < 0 or nUserId%1 ~= 0 then
		Sys_SaveAbnormalLog("函数 User_AddAddPoint 中 nUserId 只能传大于等于0的整数")
		return
	end

	return AddUserInt(nUserId,G_PLAYER_AddPoint,nAddAddPoint,0)
end

--SCRIPT_PARAM_PLAYER_StorageMoney,	1049	//玩家存储的钱	get		add
--当扣掉的钱大于玩家当前仓库的钱的时，不执行。
function User_AddStorageMoney(nAddStorageMoney,nUserId)
	if type(nAddStorageMoney) ~= "number" or nAddStorageMoney%1 ~= 0 then
		Sys_SaveAbnormalLog("函数 User_AddStorageMoney 中 nAddStorageMoney 只能传整数")
		return
	end

	if math.abs(nAddStorageMoney) > 2000000000 then
		Sys_SaveAbnormalLog("User_AddStorageMoney blocked: storage money delta exceeds safe 32-bit operation limit")
		return
	end

	if nUserId == nil then
		nUserId = 0
	elseif type(nUserId) ~= "number" or nUserId < 0 or nUserId%1 ~= 0 then
		Sys_SaveAbnormalLog("函数 User_AddStorageMoney 中 nUserId 只能传大于等于0的整数")
		return
	end

	return AddUserInt(nUserId,G_PLAYER_StorageMoney,nAddStorageMoney,0)
end

--SCRIPT_PARAM_PLAYER_AddMount,	1052	//坐骑移动力			add
--输入负数无效
function User_AddMount(nAddMount,nUserId)
	if type(nAddMount) ~= "number" or nAddMount <= 0 or nAddMount%1 ~= 0 then
		Sys_SaveAbnormalLog("函数 User_AddMount 中 nAddMount 只能传大于0的整数")
		return
	end

	if nUserId == nil then
		nUserId = 0
	elseif type(nUserId) ~= "number" or nUserId < 0 or nUserId%1 ~= 0 then
		Sys_SaveAbnormalLog("函数 User_AddMount 中 nUserId 只能传大于等于0的整数")
		return
	end

	return AddUserInt(nUserId,G_PLAYER_AddMount,nAddMount,0)
end

--SCRIPT_PARAM_PLAYER_Cultivation,	1053	//修行值	get		add
function User_AddCultivation(nAddCultivation,nUserId)
	if type(nAddCultivation) ~= "number" or nAddCultivation <= 0 or nAddCultivation%1 ~= 0 then
		Sys_SaveAbnormalLog("函数 User_AddCultivation 中 nAddCultivation 只能传大于0的整数")
		return
	end

	if nUserId == nil then
		nUserId = 0
	elseif type(nUserId) ~= "number" or nUserId < 0 or nUserId%1 ~= 0 then
		Sys_SaveAbnormalLog("函数 User_AddCultivation 中 nUserId 只能传大于等于0的整数")
		return
	end

	return AddUserInt(nUserId,G_PLAYER_Cultivation,nAddCultivation,0)
end

--SCRIPT_PARAM_PLAYER_StrengthValue,	1055	//气力值	get		add
function User_AddStrengthValue(nAddStrengthValue,nUserId)
	if type(nAddStrengthValue) ~= "number" or nAddStrengthValue <= 0 or nAddStrengthValue%1 ~= 0 then
		Sys_SaveAbnormalLog("函数 User_AddStrengthValue 中 nAddStrengthValue 只能传大于0的整数")
		return
	end

	if nUserId == nil then
		nUserId = 0
	elseif type(nUserId) ~= "number" or nUserId < 0 or nUserId%1 ~= 0 then
		Sys_SaveAbnormalLog("函数 User_AddStrengthValue 中 nUserId 只能传大于等于0的整数")
		return
	end

	return AddUserInt(nUserId,G_PLAYER_StrengthValue,nAddStrengthValue,0)
end

--SCRIPT_PARAM_PLAYER_GodBless,	1060	//获得祝福剩余时间	get		add
--单位小时，负数无效，所以禁掉。
function User_AddBless(nAddBless,nUserId)
	if type(nAddBless) ~= "number" or nAddBless <=0 or nAddBless%1 ~= 0 then
		Sys_SaveAbnormalLog("函数 User_AddBless 中 nAddBless 只能传大于0的整数")
		return
	end

	if nUserId == nil then
		nUserId = 0
	elseif type(nUserId) ~= "number" or nUserId < 0 or nUserId%1 ~= 0 then
		Sys_SaveAbnormalLog("函数 User_AddBless 中 nUserId 只能传大于等于0的整数")
		return
	end

	return AddUserInt(nUserId,G_PLAYER_GodBless,nAddBless,0)
end

-- /玩家添加道具状态，参数说明： idUser玩家ID , idProp状态类型ID, unRemainTime 剩余时间
-- LUA_FUNC(AddPropStatus)
	-- OBJID idUser		   = Lua_GetParamUInt(1);
	-- infoProps.idProp	   = Lua_GetParamULong(2);
	-- infoProps.unRemainTime = Lua_GetParamUInt(3);
function User_AddPropStatus(nPropId,nUnRemainTime,nUserId)
	if type(nPropId) ~= "number" or nPropId < 0 or nPropId%1 ~= 0 then
		Sys_SaveAbnormalLog("函数 User_AddPropStatus 第1个参数nPropId必须为整型并且大于等于0")
		return
	end

	if type(nUnRemainTime) ~= "number" or nUnRemainTime < 0 or nUnRemainTime%1 ~= 0 then
		Sys_SaveAbnormalLog("函数 User_AddPropStatus 第2个参数nUnRemainTime必须为整型并且大于等于0")
		return
	end

	if type(nUserId) ~= "number" or nUserId < 0 or nUserId%1 ~= 0 then
		Sys_SaveAbnormalLog("函数 User_AddPropStatus 第3个参数nUserId必须为整型并且大于等于0")
		return
	end
	
	return AddPropStatus(nUserId,nPropId,nUnRemainTime)
end


-- //删除玩家所有的物暴、法暴等特殊属性状态，参数说明： idUser玩家ID
-- LUA_FUNC(DelAllAttribStatus)
	-- OBJID idUser = Lua_GetParamUInt(1);
function User_DelAllAttribStatus(nUserId)
	if type(nUserId) ~= "number" or nUserId < 0 or nUserId%1 ~= 0 then
		Sys_SaveAbnormalLog("函数 User_DelAllAttribStatus 第1个参数nUserId必须为整型并且大于等于0")
		return
	end
	
	return DelAllAttribStatus(nUserId)
end

-- // 设置玩家死亡，并指定重生地图地点. 参数说明: idUser表示玩家ID; idRebornMap表示重生地图ID; nPosX, nPosY表示坐标. 如果失败返回false, 成功返回true.
-- LUA_FUNC(UserDie)
	-- OBJID idUser = Lua_GetParamUInt(1);
	-- OBJID idRebornMap = Lua_GetParamUInt(2);
	-- int nPosX = Lua_GetParamInt(3);
	-- int nPosY = Lua_GetParamInt(4);
function User_Die(nRebornMap,nPosX,nPosY,nUserId)
	if type(nRebornMap) ~= "number" or nRebornMap < 0 or nRebornMap%1 ~= 0 then
		Sys_SaveAbnormalLog("函数 User_Die 第1个参数nRebornMap必须为整型并且大于等于0")
		return
	end

	if type(nPosX) ~= "number" or nPosX < 0 or nPosX%1 ~= 0 then
		Sys_SaveAbnormalLog("函数 User_Die 第2个参数nPosX必须为整型并且大于等于0")
		return
	end

	if type(nPosY) ~= "number" or nPosY < 0 or nPosY%1 ~= 0 then
		Sys_SaveAbnormalLog("函数 User_Die 第3个参数nPosY必须为整型并且大于等于0")
		return
	end
	
	if type(nUserId) ~= "number" or nUserId < 0 or nUserId%1 ~= 0 then
		Sys_SaveAbnormalLog("函数 User_Die 第4个参数nUserId必须为整型并且大于等于0")
		return
	end

	return UserDie(nUserId,nRebornMap,nPosX,nPosY)
end

-- //设置玩家功夫属性的整型属性，参数说明：idUser指要操作的USERID, nIdx指SCRIPT_PARAM_GONGFU_ATTR_BEGIN-SCRIPT_PARAM_GONGFU_ATTR_END的枚举值，nData表示要设置的值，无返回值。
-- LUA_FUNC(SetGongFuInt)
	-- int idUser	= Lua_GetParamInt(1);
	-- int nIdx	= Lua_GetParamInt(2);
	-- int nData	= Lua_GetParamInt(3);
function User_SetGongFuInt(nIdx,nData,nUserId)
	if type(nIdx) ~= "number" or nIdx < 0 or nIdx%1 ~= 0 then
		Sys_SaveAbnormalLog("函数 User_SetGongFuInt 第1个参数nIdx必须为整型并且大于等于0")
		return
	end

	if type(nData) ~= "number" or nData < 0 or nData%1 ~= 0 then
		Sys_SaveAbnormalLog("函数 User_SetGongFuInt 第2个参数nData必须为整型并且大于等于0")
		return
	end

	if type(nUserId) ~= "number" or nUserId < 0 or nUserId%1 ~= 0 then
		Sys_SaveAbnormalLog("函数 User_SetGongFuInt 第3个参数nUserId必须为整型并且大于等于0")
		return
	end

	return SetGongFuInt(nUserId,nIdx,nData)
end

-- //增加玩家功夫属性的整型属性值，参数说明：idUser指要操作的USERID, nIdx指SCRIPT_PARAM_GONGFU_ATTR_BEGIN-SCRIPT_PARAM_GONGFU_ATTR_END的枚举值，nData表示要设置的值，无返回值。
-- LUA_FUNC(AddGongFuInt)
	-- int idUser	= Lua_GetParamInt(1);
	-- int nIdx	= Lua_GetParamInt(2);
	-- int nData	= Lua_GetParamInt(3);
function User_AddGongFuInt(nIdx,nData,nUserId)
	if type(nIdx) ~= "number" or nIdx < 0 or nIdx%1 ~= 0 then
		Sys_SaveAbnormalLog("函数 User_AddGongFuInt 第1个参数nIdx必须为整型并且大于等于0")
		return
	end

	if type(nData) ~= "number" or nData < 0 or nData%1 ~= 0 then
		Sys_SaveAbnormalLog("函数 User_AddGongFuInt 第2个参数nData必须为整型并且大于等于0")
		return
	end

	if type(nUserId) ~= "number" or nUserId < 0 or nUserId%1 ~= 0 then
		Sys_SaveAbnormalLog("函数 User_AddGongFuInt 第3个参数nUserId必须为整型并且大于等于0")
		return
	end

	return AddGongFuInt(nUserId,nIdx,nData)
end

-- //判断是否已经创建过功夫，参数说明：idUser用户ID， 返回值：已经创建返回true，否则返回false
-- LUA_FUNC(IsUserAlreadyCreateGongFu)
	-- OBJID idUser			= Lua_GetParamULong(1);
function User_IsAlreadyCreateGongFu(nUserId)
	if type(nUserId) ~= "number" or nUserId < 0 or nUserId%1 ~= 0 then
		Sys_SaveAbnormalLog("函数 User_IsAlreadyCreateGongFu 第1个参数nUserId必须为整型并且大于等于0")
		return
	end

	return IsUserAlreadyCreateGongFu(nUserId)
end

-- //队长添加周围成员状态，参数说明：idUser角色ID	nType 状态类型, nPower  状态效果，nInterval 状态持续时间，ucLeaveTimes状态次数, unRemainTime 剩余时间, unEndTime 有效时长 , ucRecordable 是否入库, usFrom 数据来源 , unData 其它内容（action传0）
-- LUA_FUNC(AddUserAroundTeamerStatus)
	-- OBJID idUser			= Lua_GetParamULong(1);
	-- statusInfo.nType		= Lua_GetParamInt(2);
	-- statusInfo.nPower	    = Lua_GetParamInt(3);
	-- statusInfo.nInterval	= Lua_GetParamInt(4);
	-- statusInfo.ucLeaveTimes = (UCHAR)Lua_GetParamUInt(5);
	-- statusInfo.unRemainTime = Lua_GetParamUInt(6);
	-- statusInfo.unEndTime 	= Lua_GetParamUInt(7);
	-- statusInfo.ucRecordable = (UCHAR) Lua_GetParamUInt(8);
	-- USHORT usFrom		    = Lua_GetParamUInt(9);
	-- statusInfo.unData		= Lua_GetParamUInt(10);

function User_AddAroundTeamerStatus(nType,nPower,nInterval,nLeaveTimes,nRemainTime,nEndTime,nRecordable,nFrom,nUserId)
	if type(nType) ~= "number" or nType%1 ~= 0 or nType <= 0 then
		Sys_SaveAbnormalLog("函数 User_AddAroundTeamerStatus 中 nMagicType 只能传大于0的整数")
		return
	end
	
	if type(nPower) ~= "number" or nPower%1 ~= 0 or nPower < 0 then
		Sys_SaveAbnormalLog("函数 User_AddAroundTeamerStatus 中 nPower 只能传大于等于0的整数")
		return
	end
	
	if type(nInterval) ~= "number" or nInterval%1 ~= 0 or nInterval <= 0 then
		Sys_SaveAbnormalLog("函数 User_AddAroundTeamerStatus 中 nInterval 只能传大于0的整数")
		return
	end
		
	if type(nLeaveTimes) ~= "number" or nLeaveTimes%1 ~= 0 or nLeaveTimes <= 0 then
		Sys_SaveAbnormalLog("函数 User_AddAroundTeamerStatus 中 nLeaveTimes 只能传大于0的整数")
		return
	end	

	if type(nRemainTime) ~= "number" or nRemainTime%1 ~= 0 or nRemainTime <= 0 then
		Sys_SaveAbnormalLog("函数 User_AddAroundTeamerStatus 中 nRemainTime 只能传大于0的整数")
		return
	end	

	if type(nEndTime) ~= "number" or nEndTime%1 ~= 0 or nEndTime <= 0 then
		Sys_SaveAbnormalLog("函数 User_AddAroundTeamerStatus 中 nEndTime 只能传大于0的整数")
		return
	end	

	if type(nRecordable) ~= "number" or nRecordable%1 ~= 0 or nRecordable <= 0 then
		Sys_SaveAbnormalLog("函数 User_AddAroundTeamerStatus 中 nRecordable 只能传大于0的整数")
		return
	end	

	if type(nFrom) ~= "number" or nFrom%1 ~= 0 or nFrom <= 0 then
		Sys_SaveAbnormalLog("函数 User_AddAroundTeamerStatus 中 nFrom 只能传大于0的整数")
		return
	end	

	if type(nUserId) ~= "number" or nUserId < 0 or nUserId%1 ~= 0 then
		Sys_SaveAbnormalLog("函数 User_AddAroundTeamerStatus 中nUserId必须为整型并且大于等于0")
		return
	end

	return AddUserAroundTeamerStatus(nUserId,nType,nPower,nInterval,nLeaveTimes,nRemainTime,nEndTime,nRecordable,nFrom)
end

	
-- //队长删除周围队伍成员状态，参数说明：idUser用户ID，szParam为状态类型参数字符串 最多输入15个状态类型数据
-- LUA_FUNC(DelUserAroundTeamerStatus)
	-- OBJID idUser   = Lua_GetParamULong(1);
	-- const char* szParam = Lua_GetParamString(2);
function User_DelAroundTeamerStatus(sParam,nUserId)
	if type(sParam) ~= "string"  then
		Sys_SaveAbnormalLog("函数 User_DelAroundTeamerStatus 中 sParam 只能传大于0的整数")
		return
	end
	
	if type(nUserId) ~= "number" or nUserId < 0 or nUserId%1 ~= 0 then
		Sys_SaveAbnormalLog("函数 User_DelAroundTeamerStatus 中nUserId必须为整型并且大于等于0")
		return
	end

	return DelUserAroundTeamerStatus(nUserId,sParam)
end

	
-- //队长检查周围队伍成员状态，参数说明：idUser用户ID，szParam为状态类型参数字符串 最多输入15个状态类型数据
-- LUA_FUNC(ChkUserAroundTeamerStatus)
	-- OBJID idUser   = Lua_GetParamULong(1);
	-- const char* szParam = Lua_GetParamString(2);
function User_ChkAroundTeamerStatus(sParam,nUserId)
	if type(sParam) ~= "string"  then
		Sys_SaveAbnormalLog("函数 User_ChkAroundTeamerStatus 中 sParam 只能传大于0的整数")
		return
	end
	
	if type(nUserId) ~= "number" or nUserId < 0 or nUserId%1 ~= 0 then
		Sys_SaveAbnormalLog("函数 User_ChkAroundTeamerStatus 中nUserId必须为整型并且大于等于0")
		return
	end
	return ChkUserAroundTeamerStatus(nUserId,sParam)
end

--任务轮盘抽奖界面. 
--参数说明: idUser表示玩家ID; idTask表示任务ID. 如果失败返回false, 成功返回true.
--LUA_FUNC(UserTaskReward)
--OBJID idUser = Lua_GetParamUInt(1);
--OBJID idTask = Lua_GetParamUInt(2);
--返回

function User_TaskReward(nTask,nUserId)
	if nUserId == nil then
		nUserId = 0
	elseif type(nUserId) ~= "number" or nUserId%1 ~= 0 or nUserId < 0 then
		Sys_SaveAbnormalLog("函数 User_TaskReward 中 nUserId 只能传大于等于0的整数")
		return
	end		
	if type(nTask) ~= "number" or nTask%1 ~= 0 or nTask < 0 then
		Sys_SaveAbnormalLog("函数 User_TaskReward 中 nTask 只能传大于等于0的整数")
		return
	end	
	
	return UserTaskReward(nUserId,nTask)

end

--通知客户端打开网页
--参数说明: idUser表示玩家ID, pszParam表示网址. 如果失败返回false, 成功返回true.
--LUA_FUNC(SendWebPage)
--OBJID idUser = Lua_GetParamUInt(1);
--const char* pszParam = Lua_GetParamString(2);
--返回通知客户端打开网页
function User_SendWebPage(nPszParam,nUserId)
	if nUserId == nil then
		nUserId = 0
	elseif type(nUserId) ~= "number" or nUserId%1 ~= 0 or nUserId < 0 then
		Sys_SaveAbnormalLog("函数 User_SendWebPage 中 nUserId 只能传大于等于0的整数")
		return
	end		
	if type(nPszParam) ~= "string" then
		Sys_SaveAbnormalLog("函数 User_SendWebPage 中 nPszParam 只能传字符串")
		return
	end		
	return SendWebPage(nUserId,nPszParam)
end

--通知客户端打开界面
--参数说明: idUser表示玩家ID, dwDialog表示界面ID. 如果失败返回false, 成功返回true.
--LUA_FUNC(OpenDialog)
--OBJID idUser = Lua_GetParamUInt(1);
--DWORD dwDialog = Lua_GetParamUInt(2);
--返回通知客户端打开界面
function User_OpenDialog(ndwDialog,nUserId)
	if nUserId == nil then
		nUserId = 0
	elseif type(nUserId) ~= "number" or nUserId%1 ~= 0 or nUserId < 0 then
		Sys_SaveAbnormalLog("函数 User_OpenDialog 中 nUserId 只能传大于等于0的整数")
		return
	end		
	if type(ndwDialog) ~= "number" or ndwDialog%1 ~= 0 or ndwDialog < 0 then
		Sys_SaveAbnormalLog("函数 User_OpenDialog 中 ndwDialog 只能传大于等于0的整数")
		return
	end	
	return OpenDialog(nUserId,ndwDialog)
end


--屏幕效果,包括震动1,缩放2,变暗变亮4,由DATA来指定,可以叠加. 
--参数说明: idUser表示玩家ID, nData表示效果. 如果失败返回false, 成功返回true.
--LUA_FUNC(Screffect)
--OBJID idUser = Lua_GetParamUInt(1);
--int nData = Lua_GetParamInt(2);
--返回屏幕效果
function User_Screffect(nData,nUserId)
	if nUserId == nil then
		nUserId = 0
	elseif type(nUserId) ~= "number" or nUserId%1 ~= 0 or nUserId < 0 then
		Sys_SaveAbnormalLog("函数 User_Screffect 中 nUserId 只能传大于等于0的整数")
		return
	end		
	if type(nData) ~= "number" or nData%1 ~= 0 or nData < 0 then
		Sys_SaveAbnormalLog("函数 User_Screffect 中 nData 只能传大于等于0的整数")
		return
	end	
	return Screffect(nUserId,nData)
end


--玩家进入副本
--参数说明： idUser玩家ID ,idInstanceType 副本类型, nNumLimit副本数量限制 0为不限制数量. bIsInvite是否邀请队友进入, nTimeLimit设置队友进入时间 bIsInvite为真时此值有用
--LUA_FUNC(EnterInstance)
--OBJID idUser = Lua_GetParamUInt(1);
--OBJID idInstanceType = Lua_GetParamUInt(2);
--int   nNumLimit = Lua_GetParamInt(3);
--int   nIsInvite = Lua_GetParamBool(4);
--int   nTimeLimit = Lua_GetParamInt(5);
--返回玩家进入副本
function User_EnterInstance(nInstanceType,nNumLimit,nIsInvite,nTimeLimit,nUserId)
	if nUserId == nil then
		nUserId = 0
	elseif type(nUserId) ~= "number" or nUserId%1 ~= 0 or nUserId < 0 then
		Sys_SaveAbnormalLog("函数 User_EnterInstance 中 nUserId 只能传大于等于0的整数")
		return
	end		
	if type(nInstanceType) ~= "number" or nInstanceType%1 ~= 0 or nInstanceType < 0 then
		Sys_SaveAbnormalLog("函数 User_EnterInstance 中 nInstanceType 只能传大于等于0的整数")
		return
	end	
	if nNumLimit == nil then
		nNumLimit = 0
	elseif  type(nNumLimit) ~= "number" or nNumLimit%1 ~= 0 or nNumLimit < 0 then
		Sys_SaveAbnormalLog("函数 User_EnterInstance 中 nNumLimit 只能传大于等于0的整数")
		return
	end		
	if nIsInvite == nil then
		nIsInvite = 0
	elseif type(nIsInvite) ~= "number" or nIsInvite%1 ~= 0 or nIsInvite < 0 then
		Sys_SaveAbnormalLog("函数 User_EnterInstance 中 nIsInvite 只能传大于等于0的整数")
		return
	end	
	if nIsInvite == nil or nIsInvite == 0 then
		nTimeLimit = 0
	elseif type(nTimeLimit) ~= "number" or nTimeLimit%1 ~= 0 or nTimeLimit < 0 then
		Sys_SaveAbnormalLog("函数 User_EnterInstance 中 nTimeLimit 只能传大于等于0的整数")
		return
	end	
	return EnterInstance(nUserId,nInstanceType,nNumLimit,nIsInvite,nTimeLimit)
end



--发送文字花. 
--参数说明: idUser表示玩家ID, nFlowerType为1:红色,2:黄色,3:玫瑰色 ,4:三色花 ,5三色花; pszWords表示发送的话. 如果失败返回false, 成功返回true.
--LUA_FUNC(WordsFlower)
--OBJID idUser = Lua_GetParamUInt(1);
--int nFlowerType = Lua_GetParamInt(2);
--const char* pszWords = Lua_GetParamString(3);
--返回文字花（只有4:三色花 可以播）
function User_WordsFlower(nFlowerType,nPszWords,nUserId)
	if nUserId == nil then
		nUserId = 0
	elseif type(nUserId) ~= "number" or nUserId%1 ~= 0 or nUserId < 0 then
		Sys_SaveAbnormalLog("函数 User_WordsFlower 中 nUserId 只能传大于等于0的整数")
		return
	end		
	if type(nFlowerType) ~= "number" or nFlowerType%1 ~= 0 or nFlowerType < 0 or nFlowerType > 5 then
		Sys_SaveAbnormalLog("函数 User_WordsFlower 中 nFlowerType 只能传(1,2,3,4,5)的整数")
		return
	end	
	if type(nPszWords) ~= "string" then
		Sys_SaveAbnormalLog("函数 User_WordsFlower 中 nPszWords 只能传字符串")
		return
	end		
	return WordsFlower(nUserId,nFlowerType,nPszWords)
end


--执行指定的sql语句, 取回指定的一个数据字段值, 以字符串形式存入到指定的寄存器变量. 
--参数说明: idUser表示玩家ID; nIdx表示寄存器索引; pszSQL表示SQL语句. 如果失败返回false, 成功返回true.
--LUA_FUNC(UserDbField)
--OBJID idUser = Lua_GetParamUInt(1);
--int nIdx = Lua_GetParamInt(2);
--const char* pszSQL = Lua_GetParamString(3);
--返回
function User_DbField(nPszSQL,nUserId)
	if nUserId == nil then
		nUserId = 0
	elseif type(nUserId) ~= "number" or nUserId%1 ~= 0 or nUserId < 0 then
		Sys_SaveAbnormalLog("函数 User_DbField 中 nUserId 只能传大于等于0的整数")
		return
	end		
	
	if type(nPszSQL) ~= "string" then
		Sys_SaveAbnormalLog("函数 User_DbField 中 nPszSQL 只能传字符串")
		return
	end		
	
	return UserDbField(nUserId,nPszSQL)
end

-- 玩家等级及转世次数判断
function User_JudgeLevelAndMetempsychosis(nLevel,nMetempsychosis)
	if type(nLevel) ~= "number" or nLevel%1 ~= 0 or nLevel < 0 then
		Sys_SaveAbnormalLog("函数 User_JudgeLevelAndMetempsychosis 中 nLevel 只能传大于等于0的整数")
		return
	end
	
	if type(nMetempsychosis) ~= "number" or nMetempsychosis%1 ~= 0 or nMetempsychosis < 0 then
		Sys_SaveAbnormalLog("函数 User_JudgeLevelAndMetempsychosis 中 nMetempsychosis 只能传大于等于0的整数")
		return
	end
	
	local nUserId = Get_UserId()
	local nUserMetempsychosis = Get_UserMetempsychosis(nUserId)
	local nUserLev = Get_UserLevel(nUserId)
	
	if nUserMetempsychosis < nMetempsychosis then
		return false
	end
	
	if nUserMetempsychosis > nMetempsychosis then
		return true
	end
	
	if nUserLev < nLevel then
		return false
	else
		return true
	end
end

-- actionType 3701 读条封装
-- nSecs 读条的秒数
-- sContent 读条内显示的文字
-- nActionId 读条时执行的动作
-- sFunc 读条成功时执行的函数
-- sFileFunc 读条失败时执行的函数
function User_SetExplore(nSecs,sContent,nActionId,sFunc,sFileFunc,nUserId)
	if type(nSecs) ~= "number" or nSecs%1 ~= 0 or nSecs <= 0 then
		Sys_SaveAbnormalLog("函数 User_SetExplore 中 nSecs 只能传大于0的整数")
		return
	end 
	
	if type(sContent) ~= "string" then
		Sys_SaveAbnormalLog("函数 User_SetExplore 中 sContent 只能传字符串类型的参数")
		return
	end
	
	if type(nActionId) ~= "number" or nActionId%1 ~= 0 or nActionId < 0 then
		Sys_SaveAbnormalLog("函数 User_SetExplore 中 nActionId 只能传大于等于0的整数")
		return
	end
	
	if sFunc == nil then
		sFunc = "NULL"
	elseif type(sFunc) ~= "string" then
		Sys_SaveAbnormalLog("函数 User_SetExplore 中 sFunc 只能传字符")
		return
	end
	
	if sFileFunc == nil then
		sFileFunc = "NULL"
	elseif type(sFileFunc) ~= "string" then
		Sys_SaveAbnormalLog("函数 User_SetExplore 中 sFileFunc 只能传字符")
		return
	end
	
	if nUserId == nil then
		nUserId = 0
	elseif type(nUserId) ~= "number" or nUserId < 0 or nUserId%1 ~= 0 then
		Sys_SaveAbnormalLog("函数 User_SetExplore 中 nUserId 只能传大于0的整数")
		return
	end
	
	return UserSetExplore(nUserId,nSecs,sContent,nActionId,string.format("</F>%s",sFunc),string.format("</F>%s",sFileFunc))
end

------------------------------------2014.12.5
-- 检测玩家是否学习指定类型的内功、
-- 参数说明：参1：idUser玩家ID； 返回值：已经学习返回true，否则返回false
function User_IsLearnInnerStrengthType(nType,nUserId)
	if type(nType) ~= "number" or nType%1 ~= 0 or nType <= 0 or nType > 14 then
		Sys_SaveAbnormalLog("函数 User_IsLearnInnerStrengthType 中 nType 只能传大于0小于14的整数")
		return
	end
	
	if nUserId == nil then
		nUserId = 0
	elseif type(nUserId) ~= "number" or nUserId%1 ~= 0 or nUserId < 0 then
		Sys_SaveAbnormalLog("函数 User_IsLearnInnerStrengthType 中 nUserId 只能传大于等于0的整数")
		return
	end

	return IsLearnedInnerStrengthType(nUserId,nType)
end

-- 玩家学习指定类型的内功
-- 参数说明：参1：玩家ID，参2：内功类型；返回值：成功返回true，否则返回false
function User_LearningInnerStrength(nType,nUserId)
	if type(nType) ~= "number" or nType%1 ~= 0 or nType <= 0 or nType > 14 then
		Sys_SaveAbnormalLog("函数 User_LearningInnerStrength 中 nType 只能传大于0小于14的整数")
		return
	end
	
	if nUserId == nil then
		nUserId = 0
	elseif type(nUserId) ~= "number" or nUserId%1 ~= 0 or nUserId < 0 then
		Sys_SaveAbnormalLog("函数 User_LearningInnerStrength 中 nUserId 只能传大于等于0的整数")
		return
	end

	return LearningInnerStrength(nUserId,nType)
end

-- 玩家添加修为值
function User_AddCultureValue(nValue,nUserId)
	if type(nValue) ~= "number" or nValue%1 ~= 0 then
		Sys_SaveAbnormalLog("函数 User_AddCultureValue 中 nValue 只能传整数")
		return
	end

	if nUserId == nil then
		nUserId = 0
	elseif type(nUserId) ~= "number" or nUserId < 0 or nUserId%1 ~= 0 then
		Sys_SaveAbnormalLog("函数 User_AddCultureValue 中 nUserId 只能传大于等于0的整数")
		return
	end

	return AddUserInt(nUserId,G_PLAYER_CultureValue,nValue)
end