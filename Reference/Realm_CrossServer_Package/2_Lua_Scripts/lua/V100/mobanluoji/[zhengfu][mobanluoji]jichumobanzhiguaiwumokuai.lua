----------------------------------------------------------------------------
--Name:		[征服][模板逻辑]基础模板之怪物模块.lua
--Purpose:	基础模板之怪物模块
--Creator: 	郑江文
--Created:	2014/12/10
----------------------------------------------------------------------------

--任务怪物触发Action接口函数(action.id=94416550)，实时触发。（适合用来做怪物掉落）
function LinkMonsterMain()
	local nMonsterTypeId = Get_MonsterType()
	--怪物表是否有值
	if nMonsterTypeId == 0 or nMonsterTypeId == nil or tMonster[nMonsterTypeId] == nil then
		return
	end
	--功能怪
	if type(tMonster[nMonsterTypeId]["tFunction"]) == "table" then
		for _,func in ipairs(tMonster[nMonsterTypeId]["tFunction"]) do
			func(nMonsterTypeId)
		end
	end	
end
--例：
--tMonster[5830] = tMonster[5830] or {}
--tMonster[5830]["tFunction"] = tMonster[5830]["tFunction"] or {}
--table.insert(tMonster[5830]["tFunction"],RandMission_55136_Monster_Killed)