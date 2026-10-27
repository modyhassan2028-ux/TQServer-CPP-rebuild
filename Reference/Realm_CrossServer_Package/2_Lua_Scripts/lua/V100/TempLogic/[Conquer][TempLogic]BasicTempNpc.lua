----------------------------------------------------------------------------
--Name:		[Õ÷·þ][Ä£°åÂß¼­]»ù´¡Ä£°åÖ®npcÄ£¿é.lua
--Purpose:	»ù´¡Ä£°åÖ®npcÄ£¿é
--Creator: 	Ö£½­ÎÄ
--Created:	2014/08/28
----------------------------------------------------------------------------

--//¶¨Òå»ù´¡NPCÀà
DefaultNpc	=	{
Text=tLuaRes[10001], --Ä¬ÈÏ¶Ô°×
Option=tLuaRes[10002]	 --Ä¬ÈÏÑ¡Ïî
}

function DefaultNpc:new(o)
	o =  o or {}
	setmetatable(o,self)
	self.__index = self
	return o
end

--//cq_NPC½Ó¿Úº¯Êý(Action_id=94418000)
function  LinkNpcMain(...)
	local nNpcId = Get_NpcId()
	local arg = {...}

	if tNpcGossip[nNpcId] ~= nil then
		tNpcGossip[nNpcId]:NpcProcess(nNpcId,arg[1],arg[2],arg[3],arg[4])
	else
		--ÏÐÁÄ±í tNpcGossip Î´ÅäÖÃ ¶Ô°×
		Sys_DialogText(tLuaRes[10001])
		Sys_DialogOption(tLuaRes[10002],"</F>NULL")
		Sys_DialogFace(nNpcId)
		Sys_DialogEnd()
	end
end

--//»ù´¡NPCÀàµÄ³ÉÔ±º¯Êý_Á÷³Ìº¯Êý
function DefaultNpc:NpcProcess(nNpcId,...)
	--¹¦ÄÜ NPC´¦Àí
	local arg = {...}
	---print(111111)
	if type(tNpcGossip[nNpcId]["Function"]) == "function" then
		tNpcGossip[nNpcId]["Function"](arg[1],arg[2],arg[3],arg[4])
	else
		--ÏÈ×ßÈëµÚ¶þÌ×Ä£°å£¬¼ì²â["Text1"]×Ö¶ÎÊÇ·ñÓÐÅäÖÃ£¬ÓÐÔò×ßµÚ¶þÌ×£¬ÎÞÔò×ßµÚÈýÌ×¡£
		tNpcGossip[nNpcId]:AIFunc_New(nNpcId, nil, 0, tNpcGossip[nNpcId]["nPageNum"])
	end

	--NPC¶Ô»°¿ªÊ¼Ñ¡Ïî
	if type(tNpcGossip[nNpcId]["OptionStarFunc"]) == "function" then
		tNpcGossip[nNpcId]["OptionStarFunc"](nNpcId,arg[1],arg[2],arg[3],arg[4])
	end

	--NPCÈÎÎñ½áÊø±íÅÐ¶Ï
	--local i = 1
	--if tNpcQuestEnd[nNpcId] ~= nil then
	--	while tNpcQuestEnd[nNpcId][i] ~= nil do
	--		local QuestId=tNpcQuestEnd[nNpcId][i]
	--		if PlayerInQuest(QuestId) then
	--			Sys_DialogOption("£¿"..tQuestTemplate[QuestId].Title,"</F>LinkQuestFinishDialog</N>"..QuestId)
	--		end
	--		i = i+1
	--	end
	--end

	--NPCÈÎÎñÖÐ¼ä±íÅÐ¶Ï
	--local m = 1
	--if tNpcQuestMid[nNpcId] ~= nil then
	--	while tNpcQuestMid[nNpcId][m] ~= nil do
	--		local QuestId=tNpcQuestMid[nNpcId][m]
	--		if PlayerInQuest(QuestId) and type(tQuestTemplate[QuestId]["QuestMidNPC"]) == "function" then
	--			tQuestTemplate[QuestId]:QuestMidNPC(QuestId)
	--		end
	--		m = m+1
	--	end
	--end

	--NPCÈÎÎñÆðÊ¼±íÅÐ¶Ï
	--local j = 1
	--if tNpcQuestStar[nNpcId] ~= nil then
	--	while tNpcQuestStar[nNpcId][j] ~= nil and type(tNpcQuestStar[nNpcId][j]) == "number" do
	--		local QuestId=tNpcQuestStar[nNpcId][j]
	--		if not PlayerChkTask(QuestId) then
	--			if tQuestTemplate[QuestId]:IsQuestAvailable(QuestId) then
	--				Sys_DialogOption("£¡"..tQuestTemplate[QuestId].Title,"</F>LinkQuestAcceptDialog</N>"..QuestId)--½ÓÊÜÈÎÎñÏÔÊ¾Ñ¡Ïî
	--			end
 	--		end
	--		j = j+1
	--	end
	--end

	--NPC¶Ô»°½áÊøÑ¡Ïî
	if type(tNpcGossip[nNpcId]["OptionEndFunc"]) == "function" then
		tNpcGossip[nNpcId]["OptionEndFunc"](nNpcId,arg[1],arg[2],arg[3],arg[4])
	end

	if not(tNpcGossip[nNpcId]["OptionHidden"] == 1) then
		if tNpcGossip[nNpcId]["Option"] ~= nil and tNpcGossip[nNpcId]["Option"] ~= "" then
			Sys_DialogOption(tNpcGossip[nNpcId]["Option"],"</F>NULL")
		else
			Sys_DialogOption(tLuaRes[10003],"</F>NULL")
		end
	end
	Sys_DialogFace(nNpcId)
	Sys_DialogEnd()
end

--[[
@param
nNpcId:´«Èë¸ÃNPCµÄID
sIndex:´ÓÉÏÒ»²ã´«ÈëµÄË÷ÒýID£¬µÚÒ»²ãÎªnil´«Èë
nPage:µ±Ç°µÚ¼¸Ò³Ñ¡Ïî£¬0ÎªµÚÒ»Ò³
nPageNum:Ã¿Ò³ÏÔÊ¾µÄÑ¡ÏîÊý£¬Ä¬ÈÏÎª5
--]]
function DefaultNpc:AIFunc_New(nNpcId, sIndex, nPage, nPageNum)
	local bFirst = false				--ÊÇ·ñµÚÒ»´Î×ßÈë´Ëº¯Êý£¬¼´ÊÇ·ñÔÚNpcProcessËùµ÷ÓÃµÄ¡£
	local nPage = nPage or 0			--µ±Ç°Ò³Âë£¬0ÎªµÚÒ»Ò³
	local nPageNum = nPageNum or 8		--Ã¿Ò³ÏÔÊ¾µÄÑ¡ÏîÊý
	local nCount = 1					--µ±Ç°Ó¦¸ÃÏÔÊ¾µÚ¼¸Ïî
	local nFlag = 0						--Îª0´ú±íÃ»³ö¶Ô°×£¬1´ú±í·ÇÖ¸¶¨¶Ô°×£¬2´ú±íÖ¸¶¨¶Ô°×
	local n = 1							--´æ´¢ÏÔÊ¾µÄText±íÐòºÅ

	--µÚÒ»²ã¶Ô°×£¬Ö§³ÖÌõ¼þÑ¡Ôñ
	if sIndex == nil then
		sIndex = "1"
		bFirst = true --µÚÒ»²ã£¬ÒòÎªÖ´ÐÐÍêºóÒª»Øµ÷µ½NPCÄ£°åÖÐ£¬ËùÒÔ²»ÄÜ³öÏÖ¶Ô»°¿ò½áÊøµÄÓï¾ä
	else
		if string.find(sIndex, "-") == nil then
			nFlag = 0
		else
			nFlag = 2
		end
		bFirst = false
	end

	--¶ÔText½øÐÐ´¦Àí£¬Çø·ÖÏÔÊ¾Ö¸¶¨¶Ô°×ºÍ·ÇÖ¸¶¨¶Ô°×
	if nFlag == 2 then
		if tNpcGossip[nNpcId]["Text"..sIndex] == nil or  tNpcGossip[nNpcId]["Text"..sIndex] == {} then
			return
		end

		if tNpcGossip[nNpcId]["ChkFunc"..sIndex] == nil or (type(tNpcGossip[nNpcId]["ChkFunc"..sIndex]) == "function" and tNpcGossip[nNpcId]["ChkFunc"..sIndex]() == true) then
			for _,v in ipairs(tNpcGossip[nNpcId]["Text"..sIndex]) do
				if tNpcGossip[nNpcId]["Text"..v] ~= nil and tNpcGossip[nNpcId]["Text"..v] ~= "" then
					Sys_DialogText(tNpcGossip[nNpcId]["Text"..v])
				end
			end
		else
			return
		end
	else
		for i = 1, 50 do
			if tNpcGossip[nNpcId]["Text"..sIndex.."-"..i] ~= nil and tNpcGossip[nNpcId]["Text"..sIndex.."-"..i] ~= "" then
				--¹¦ÄÜ¶Ô°×³öÏÖ¼ì²éº¯Êý
				if tNpcGossip[nNpcId]["ChkFunc"..sIndex.."-"..i] == nil or (type(tNpcGossip[nNpcId]["ChkFunc"..sIndex.."-"..i]) == "function" and tNpcGossip[nNpcId]["ChkFunc"..sIndex.."-"..i]() == true) then
					
					--³ö¶Ô°×,×î¶à¿ÉÒÔÅäÖÃ5Ìõ
					for _,v in ipairs(tNpcGossip[nNpcId]["Text"..sIndex.."-"..i]) do
						if tNpcGossip[nNpcId]["Text"..v] ~= nil and tNpcGossip[nNpcId]["Text"..v] ~= "" then
							Sys_DialogText(tNpcGossip[nNpcId]["Text"..v])
						end
					end
					
					--¶Ô°×ÒÑ³ö£¬²»ÔÙ¼ì²â±íÖÐÖµ
					nFlag = 1
					n = i
					break
				end
			else
				break
			end
		end
	end

	--¶Ô´«ÈëµÄsIndex½øÐÐ´¦Àí£¬Ê¹Ö¸¶¨ºÍ·ÇÖ¸¶¨¶Ô°×Ò»ÖÂ£¬·½±ãÏÂÃæµÄ´¦Àí
	if nFlag == 2 then
		n = string.sub(sIndex, string.find(sIndex,"-") + 1)
		sIndex = string.sub(sIndex, 1, string.find(sIndex,"-") - 1)
	elseif nFlag == 0 then --Ã»ÓÐ¿ÉÒÔÏÔÊ¾µÄ¶Ô°×
		if bFirst then --µÚÒ»´Î½øÈëÔòÏÔÊ¾Ä¬ÈÏ¶Ô°×·ñÔòÖ±½ÓÖÐ¶Ï
			Sys_DialogText(tNpcGossip[nNpcId]["Text"])
			return
		else
			return
		end
	end

	--Ñ¡ÏîÏÔÊ¾²¿·Ö
	if nFlag ~= 0 then
	--Ñ¡Ïî´æÔÚ¼ì²é
		if type(tNpcGossip[nNpcId]["tOption"..sIndex.."-"..n]) == "table" and tNpcGossip[nNpcId]["tOption"..sIndex.."-"..n] ~= {} then
			for _, v in ipairs(tNpcGossip[nNpcId]["tOption"..sIndex.."-"..n]) do --¼ìË÷Ñ¡Ïî±í
				
				if nCount <= nPageNum and ((_ > nPage * nPageNum and nPage == 0) or (_ > nPage * nPageNum - (2 * nPage - 1) and nPage >= 1)) then --Î´³¬¹ýÃ¿Ò³Ñ¡ÏîÊý
					if tNpcGossip[nNpcId]["Option"..v] ~= nil and tNpcGossip[nNpcId]["Option"..v] ~= "" then --´æÔÚ¸ÃÑ¡Ïî
						if tNpcGossip[nNpcId]["OptionChkFunc"..v] == nil or (type(tNpcGossip[nNpcId]["OptionChkFunc"..v]) == "function" and tNpcGossip[nNpcId]["OptionChkFunc"..v]()) then --ChkFuncÅÐ¶¨Í¨¹ý
							local sTemp = ""
							local sFunc = ""
							if tNpcGossip[nNpcId]["OptionPoint"..v] ~= nil and tNpcGossip[nNpcId]["OptionPoint"..v] ~= "" then
								sTemp = tNpcGossip[nNpcId]["OptionPoint"..v]
							else
								sTemp = nil
							end

							if tNpcGossip[nNpcId]["OptionFunc"..v] ~= nil and tNpcGossip[nNpcId]["OptionFunc"..v] ~= "" and type(tNpcGossip[nNpcId]["OptionFunc"..v]) == "string" then
								sFunc = "</F>"..tNpcGossip[nNpcId]["OptionFunc"..v]
							elseif sTemp ~= nil then
								sFunc = "</F>LinkNpcGossipFunc_New</N>"..nNpcId.."</S>"..sTemp.."</N>0</N>"..nPageNum
							else
								sFunc = "</F>NULL"
							end
							
							Sys_DialogOption(tNpcGossip[nNpcId]["Option"..v], sFunc)
							nCount = nCount + 1
							--if nCount < nPageNum then
							--	nCount = nCount + 1
							--end
							
							if nCount == nPageNum and #tNpcGossip[nNpcId]["tOption"..sIndex.."-"..n] > nPageNum and nPage == 0  then
								local sTemp = sIndex.."-"..n
								Sys_DialogOption(tLuaRes[10006] , "</F>LinkNpcGossipFunc_New</N>"..nNpcId.."</S>"..sTemp.."</N>"..(nPage + 1).."</N>"..nPageNum)
								break
							elseif nCount == nPageNum - 1 and #tNpcGossip[nNpcId]["tOption"..sIndex.."-"..n] > nPageNum * (nPage + 1) - 2 * nPage and nPage > 0 then
								local sTemp = sIndex.."-"..n
								Sys_DialogOption(tLuaRes[10006] , "</F>LinkNpcGossipFunc_New</N>"..nNpcId.."</S>"..sTemp.."</N>"..(nPage + 1).."</N>"..nPageNum)
								break
							end
						end
						
					end
				--elseif nCount ==  nPageNum and #tNpcGossip[nNpcId]["tOption"..sIndex.."-"..n] > nPageNum then
				--	local sTemp = sIndex.."-"..n
				--	Sys_DialogOption("ÏÂÒ»Ò³", "</F>LinkNpcGossipFunc_New</N>"..nNpcId.."</S>"..sTemp.."</N>"..(nPage + 1).."</N>"..nPageNum)
				--	break
				end
			end

			if nPage > 0 then
				local sTemp = sIndex.."-"..n
				Sys_DialogOption(tLuaRes[10005], "</F>LinkNpcGossipFunc_New</N>"..nNpcId.."</S>"..sTemp.."</N>"..(nPage - 1).."</N>"..nPageNum)
			end
		end
	end
	
	--ºó²¿´¦Àí£¬Çø·ÖÊÇ·ñNpcProcess×ßÈëµÄº¯Êý
	if not bFirst then
		--Sys_SystemBroadcast("nCount is "..nCount)
		if nCount == 1 then
			Sys_DialogOption(tNpcGossip[nNpcId]["Option"] or tLuaRes[10002], "</F>NULL")
		end
		Sys_DialogFace(nNpcId)
		Sys_DialogEnd()
	end
end

function LinkNpcGossipFunc_New(nNpcId, sIndex, nPage, nPageNum)
	return tNpcGossip[nNpcId]:AIFunc_New(nNpcId, sIndex, nPage, nPageNum)
end

--½ÓÈÎÎñ º¯Êý
-- function LinkQuestAcceptDialog(QuestId)
	-- return tQuestTemplate[QuestId]:QuestAcceptDialog(QuestId)
-- end

--½»ÈÎÎñ º¯Êý
-- function LinkQuestFinishDialog(QuestId)
	-- return tQuestTemplate[QuestId]:QuestFinishDialog(QuestId)
-- end

-------------------------NPC·ÇÈÎÎñ¶Ô°×Ä£¿éÊ¾Àý-------------------------------

