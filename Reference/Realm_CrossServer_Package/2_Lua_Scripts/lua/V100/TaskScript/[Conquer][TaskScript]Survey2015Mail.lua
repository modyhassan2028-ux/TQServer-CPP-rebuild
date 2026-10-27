---Name:150616[英文征服][任务脚本]八阵图调查(7.2-7.16)
--Creator: 	陈莺
--Created:	2015/06/16
--------------------------------------------------------------------------------
--命名：   Survery2015_Mail_

--掩码  sct（135,27） 表示领过物品
--log 18000057

local Survery2015_Mail_Cont = {}
	Survery2015_Mail_Cont[3006797] = {}
	Survery2015_Mail_Cont[3006797]["MaxLevel"] = 140
	Survery2015_Mail_Cont[3006797]["Cultivation"] = 15
	Survery2015_Mail_Cont[3006797]["Exp"] = 30
	Survery2015_Mail_Cont[3006797]["ActivityTime"] = "2015-07-02 00:00 2015-07-16 23:59"
	
	
local tSurvery2015_Mail_Log = {}
	tSurvery2015_Mail_Log["Exp"] = "0,0,3006797,1,18000057,2,4,30"
	tSurvery2015_Mail_Log["Cultivation"] = "0,0,3006797,1,18000057,2,6,15"

--------------------------------逻辑部分--------------------------
--物品使用
function Survery2015_Mail_UseMail()
	local nItemId = Get_ItemType()
	if not Sys_ChkFullTime( Survery2015_Mail_Cont[3006797]["ActivityTime"])  then 
		if Item_ChkItem(nItemId) and  Item_DelItem(nItemId)then
			
			Sys_MsgBox(tBackpackLetter_Text[3006797]["OverTime"])
			return
		end
	end 
	Sys_DialogText(tBackpackLetter_Text[3006797]["Text111"])
	Sys_DialogText(tBackpackLetter_Text[3006797]["Text112"])
	Sys_DialogText(tBackpackLetter_Text[3006797]["Text113"])
	Sys_DialogText(tBackpackLetter_Text[3006797]["Text114"])
	Sys_DialogText(tBackpackLetter_Text[3006797]["Text115"])
	Sys_DialogOption(tBackpackLetter_Text[3006797]["Option1"],"</F>Survery2015_Mail_Answer</N>3006797")
	Sys_DialogOption(tBackpackLetter_Text[3006797]["Option2"],"</F>Survery2015_Mail_Burn</N>3006797")
	Sys_DialogEnd()

end

function Survery2015_Mail_Answer(nItemId)

	-- WebDialog(tBackpackLetter_Text[3006797]["WebDialog"])
	User_SendWebPage(tBackpackLetter_Text[3006797]["WebDialog"])

end
function Survery2015_Mail_Burn(nItemId)
	local nLevel = Get_UserLevel()
	local nMaxLwvel = Survery2015_Mail_Cont[3006797]["MaxLevel"]
	local nAddCultivation = Survery2015_Mail_Cont[3006797]["Cultivation"]
	local nTime = Survery2015_Mail_Cont[3006797]["Exp"]
	if  Item_ChkItem(nItemId)  and Item_DelItem(nItemId) then 
	
		if nLevel >= nMaxLwvel  then 
		
			User_AddCultivation(nAddCultivation)
			Sys_SaveActionLog(tSurvery2015_Mail_Log["Cultivation"])
			Sys_MsgBox(tBackpackLetter_Text[3006797]["Cultivation"])
		
		else 
		
			User_AddExpTime(nTime)
			Sys_SaveActionLog(tSurvery2015_Mail_Log["Exp"])
			Sys_MsgBox(tBackpackLetter_Text[3006797]["RewardExp"])
		end 
	end
end
