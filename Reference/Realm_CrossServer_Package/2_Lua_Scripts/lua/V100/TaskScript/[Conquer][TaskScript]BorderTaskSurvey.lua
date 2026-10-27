----------------------------------------------------------------------------------------
--Name:		151104[英文征服][任务脚本]国境任务调查问卷
--Purpose:		国境任务调查问卷
--Creator:		林辉山
--Created:		2015/11/04
----------------------------------------------------------------------------------------

--前缀
--BorderTaskSurvey_

function BorderTaskSurvey_OpenTheWeb()
	local sWebSite = tBorderTaskSurvey_Text["WebSite"]
	User_SendWebPage(sWebSite)
end



-------------------------------------------NPC模块-----------------------------------------------
tNpcFace[3863] = 166
tNpcGossip[18888] = tNpcGossip[18888] or DefaultNpc:new{}
tNpcGossip[18888]["OptionHidden"] = 1

--活动时间前
tNpcGossip[18888]["Text1-1"] = {111}
tNpcGossip[18888]["Text111"] = tBorderTaskSurvey_Text["Survey"]["Text111"]
tNpcGossip[18888]["tOption1-1"] = {1}
tNpcGossip[18888]["ChkFunc1-1"] = function()
	return true
end

tNpcGossip[18888]["Option1"] = tBorderTaskSurvey_Text["Survey"]["Option1"]
tNpcGossip[18888]["OptionFunc1"]="BorderTaskSurvey_OpenTheWeb"





tNpcGossip[18889] = tNpcGossip[18888]
tNpcGossip[18890] = tNpcGossip[18888]
tNpcGossip[18891] = tNpcGossip[18888]
tNpcGossip[18892] = tNpcGossip[18888]
tNpcGossip[18893] = tNpcGossip[18888]
tNpcGossip[18894] = tNpcGossip[18888]
tNpcGossip[18895] = tNpcGossip[18888]
tNpcGossip[18896] = tNpcGossip[18888]
tNpcGossip[18897] = tNpcGossip[18888]
tNpcGossip[18898] = tNpcGossip[18888]
