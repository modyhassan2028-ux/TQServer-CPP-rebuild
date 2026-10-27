------------------------------------------------------------------------------------
-- 6173 Cross-Version Compatibility Functions for FrontierTask / Realm Scripts
------------------------------------------------------------------------------------
G_SysTempDataTable = G_SysTempDataTable or {}

if not Get_SysTempData then
	function Get_SysTempData(nType, nKey1, nKey2)
		local k1 = tonumber(nType) or 0
		local k2 = tonumber(nKey1) or 0
		local k3 = tonumber(nKey2) or 0
		if G_SysTempDataTable[k1] and G_SysTempDataTable[k1][k2] and G_SysTempDataTable[k1][k2][k3] then
			return G_SysTempDataTable[k1][k2][k3]
		end
		return 0
	end
end

if not Sys_SetTempData then
	function Sys_SetTempData(nType, nKey1, nKey2, nVal)
		local k1 = tonumber(nType) or 0
		local k2 = tonumber(nKey1) or 0
		local k3 = tonumber(nKey2) or 0
		local v = tonumber(nVal) or 0
		if v < 0 then
			v = 0
		end
		G_SysTempDataTable[k1] = G_SysTempDataTable[k1] or {}
		G_SysTempDataTable[k1][k2] = G_SysTempDataTable[k1][k2] or {}
		G_SysTempDataTable[k1][k2][k3] = v
		return true
	end
end

if not User_TransFormByMagic then
	function User_TransFormByMagic(nSkillType, nSkillLevel, nMonsterType, nTime, nUserId, nLearnMagic)
		nUserId = tonumber(nUserId) or 0
		nSkillType = tonumber(nSkillType) or 0
		nSkillLevel = tonumber(nSkillLevel) or 0
		nMonsterType = tonumber(nMonsterType) or 0
		nTime = tonumber(nTime) or 600
		nLearnMagic = tonumber(nLearnMagic) or 0
		if TransForm then
			return TransForm(nUserId, nSkillType, nSkillLevel, nMonsterType, nTime, nLearnMagic)
		end
		return false
	end
end

if not User_ChkSurplusExp then
	function User_ChkSurplusExp(nUserId)
		if Get_UserSurplusExp then
			return Get_UserSurplusExp(nUserId or 0) >= 2000000000
		end
		return false
	end
end

if not Task_AddActivityTaskSchedule then
	function Task_AddActivityTaskSchedule(nTaskType, nUserId)
		if AddActivityTaskSchedule then
			return AddActivityTaskSchedule(nUserId or 0, nTaskType or 0)
		end
		return true
	end
end

if not MapExploration_AddStc then
	function MapExploration_AddStc(nIdx, nUserId)
		return true
	end
end

------------------------------------------------------------------------------------
-- Imperial Realm dialogue tables.
-- FirstPerson and BossCopy came from serverabak18223.rar (English archive).
-- Looting Villages text is a compatibility translation for the 18280 script.
------------------------------------------------------------------------------------

if not CommonFunc_GetItemNum then
	function CommonFunc_GetItemNum(nItemId)
		return 1
	end
end

if not Item_AddNewItemAndMsg then
	function Item_AddNewItemAndMsg(nItemId, sAttr, nUserId)
		return Item_AddNewItem(nItemId, sAttr, nUserId or 0)
	end
end

if not Sys_IncNosuchStatisticCount then
	function Sys_IncNosuchStatisticCount(nId, nNum)
		return true
	end
end

if not Sys_DecNosuchStatisticCount then
	function Sys_DecNosuchStatisticCount(nId, nNum)
		return true
	end
end

if not Sys_SaveActionRewardLog then
	function Sys_SaveActionRewardLog(sLog, nUserId)
		if Sys_SaveActionTaskLog then
			return Sys_SaveActionTaskLog(sLog, nUserId or 0)
		end
		return true
	end
end

if not Sys_SaveDragonSoulLog then
	function Sys_SaveDragonSoulLog(sLog, nUserId)
		return true
	end
end

if not User_CheckTitle then
	function User_CheckTitle(nTitleType, nTitleId, nUserId)
		return false
	end
end

if not User_AwardTitle then
	function User_AwardTitle(nTitleType, nTitleId, nUserId)
		return true
	end
end

tRewardTemplate_Text = {}
tRewardTemplate_Text["Main"] = "You received %s."
tRewardTemplate_Text["Punctuat"] = ", "
tRewardTemplate_Text["RewardMoney"] = "%d Silver"
tRewardTemplate_Text["RewardEMoney"] = "%d CPs"
tRewardTemplate_Text["RewardEMoneyMono"] = "%d CPs (B)"
tRewardTemplate_Text["RewardItem"] = "%d %s"
tRewardTemplate_Text["RewardZhenQi"] = "%d Talents"
tRewardTemplate_Text["RewardCultivation"] = "%d Study Points"
tRewardTemplate_Text["RewardStrengthValue"] = "%d Chi Points"
tRewardTemplate_Text["RewardFreePractNum"] = "%d free training chances"
tRewardTemplate_Text["RewardRidingPoint"] = "%d Riding Points"
tRewardTemplate_Text["RewardRepairValue"] = "%d Potency Points"
tRewardTemplate_Text["RewardBless"] = "%d hours` Blessing"
tRewardTemplate_Text["RewardExp"] = "%d EXP"
tRewardTemplate_Text["RewardExpTime"] = "%d minutes` EXP"
tRewardTemplate_Text["RewardExpPercent"] = "%d%% EXP"
tRewardTemplate_Text["RewardBund"] = "(B)"
tRewardTemplate_Text["RewardMulExpTime"] = "%d-hour %dxEXP"

tRewardTemplate_Text["NoSpace"] = "Please clear at least %d empty space(s) in your inventory, first."
tRewardTemplate_Text["NoItem"] = "Please make sure you have this item in your inventory, first."
tRewardTemplate_Text["FreePract"] = "You`ve already accumulated 100 Free Courses and you can`t get more."
tRewardTemplate_Text["EMoneyMono"] = "You`re carrying the maximum amount of CPs (B) and you can`t get more."
tRewardTemplate_Text["EMoney"] = "You`re carrying the maximum amount of CPs and you can`t get more."
tRewardTemplate_Text["Money"] = "You`re carrying the maximum amount of Silver and you can`t get more."
tRewardTemplate_Text["ZhenQi"] = "You`ve already accumulated 5 Talents and you can`t get more."
tRewardTemplate_Text["RepairValue"] = "You`ve already accumulated lots of Potency Points and you can`t get more."
tRewardTemplate_Text["HaveReceive"] = "You`ve already claimed this reward."

-- Î´×Ô´´Îä¹¦
tRewardTemplate_Text["GongFu"] = "You haven`t joined the Jiang Hu and can`t get the reward."
-- ÒøÁ½²»×ã
tRewardTemplate_Text["CostMoney"] = "You don`t have enough Silver."
-- ÌìÊ¯²»×ã
tRewardTemplate_Text["CostEMoney"] = "You don`t have enough CPs."
-- ÔùÆ·ÌìÊ¯²»×ã
tRewardTemplate_Text["CostEMoneyMono"] = "You don`t have enough CPs (B)."
-- »Æ½ðÁªÈü»ý·Ö´ïÉÏÏÞ
tRewardTemplate_Text["GoldenLeague"] = "You have accumulated lots of Champion`s Arena points and can`t get more."
-- ÊôÐÔµã´ïµ½ÉÏÏÞ
tRewardTemplate_Text["MaxPoint"] = "Your attribute points have reached the maximum."

tRewardTemplate_Text["Currency"] = "You received %s!"
tRewardTemplate_Text["Gift"] = "(B)"
tRewardTemplate_Text["Number"] = "*"
tRewardTemplate_Text["Prescript"] = "-day"
tRewardTemplate_Text["GodBless"] = "% Blessed"
tRewardTemplate_Text["Additional"] = "+"
tRewardTemplate_Text["Hole"] = "-Soc."

tRewardTemplate_Text["TheBeat"] = "Super"
tRewardTemplate_Text["Boutique"] = "Elite"
tRewardTemplate_Text["TopGrade"] = "Unique"
tRewardTemplate_Text["GoodProduct"] = "Refined"
tRewardTemplate_Text["WhiteGoods"] = "Normal"

--³àÁ¶Ê¯ÌáÊ¾
tRewardTemplate_Text["ItemName"] = {}
tRewardTemplate_Text["ItemName"][730001] =  "+1 Stone"
tRewardTemplate_Text["ItemName"][730002] =  "+2 Stone"
tRewardTemplate_Text["ItemName"][730003] =  "+3 Stone"
tRewardTemplate_Text["ItemName"][730004] =  "+4 Stone"
tRewardTemplate_Text["ItemName"][730005] =  "+5 Stone"
tRewardTemplate_Text["ItemName"][730006] =  "+6 Stone"
tRewardTemplate_Text["ItemName"][730007] =  "+7 Stone"
tRewardTemplate_Text["ItemName"][730008] =  "+8 Stone"
tRewardTemplate_Text["ItemName"][730009] =  "+9 Stone"

----------------------------------------------------------------------------
--Name:		[Õ÷·þ][Ä£°åÂß¼­]ÂÖÅÌÄ£°å.lua
--Creator: 	À¼ÈðÃÃ
--Created:	2017/07/19
----------------------------------------------------------------------------


tFirstPerson_Text = {}
tFirstPerson_Text[17400] = {}
tFirstPerson_Text[17400]["Text1000011"] = "While in a battle against millions of enemies, striking first is the key to gain initiative. Hurry up and disable the enemy soldiers, officers, and their Kylin Chariots in the Realm!"
tFirstPerson_Text[17400]["Text1000012"] = "~When you collect 300 Strike Points, a wonderful<tip color=0xfff05050 desc=Eminent#Exploit#Pack,#Free#Training#Pill,#or#other#rewards#like#Chi#Points#&#300-min#EXP,#90#Kingdom#Deeds,#and#50#Champion#Points.>bounty</tip>"
tFirstPerson_Text[17400]["Text1000013"] = "~will be yours. You can also earn War Exploits by destroying the enemy`s Defensive Barrier, Dark Crystal, or beheading their Military Officer.\n"

tFirstPerson_Text[17400]["Option10000"] = "Claim~my~bounty."
tFirstPerson_Text[17400]["Option10014"] = "Directly~complete~it.~(10~CPs)"
tFirstPerson_Text[17400]["Option10001"] = "Claim~an~Evolution~Token."
tFirstPerson_Text[17400]["Option10002"] = "Learn~about~other~things."
tFirstPerson_Text[17400]["Option10003"] = "I`m~not~ready~yet!"

-- ½Óa£¬Ê§°Ü£¬±³°ü¿Õ¼ä²»×ã
tFirstPerson_Text[17400]["Text1000111"] = "You deserve to be rewarded for knocking down so many enemies. Please clear at least 1 empty space in your inventory for your reward."
tFirstPerson_Text[17400]["Option10004"] = "Okay."

-- ½Óa£¬Ê§°Ü£¬ÌìÊ¯ÒÑ´ïÉÏÏÞ
tFirstPerson_Text[17400]["Text1000211"] = "You must be too busy to check your pocket. It`s already full. Please deposit or spend some CPs (B), first."
tFirstPerson_Text[17400]["Option10005"] = "Okay."

-- ½Óa£¬Ê§°Ü£¬Strike Points²»×ã300
tFirstPerson_Text[17400]["Text1000311"] = "To claim a reward, you should collect 300 Strike Points, first. Fight for your home, and kill enemies in the Realm!"
tFirstPerson_Text[17400]["Option10006"] = "Go~fight!"

-- ½Óa£¬³É¹¦
tFirstPerson_Text[17400]["Text1000411"] = "Your loyalty to your kingdom is quite strong. Please accept this reward."
tFirstPerson_Text[17400]["Option10007"] = "Thanks!"

-- ½Ób£¬³ÊÇë½«¾üÁî
tFirstPerson_Text[17400]["Text1000511"] = "As long as you want to serve your kingdom, Battle Power less than 250 is not a problem. I`ll give you an Evolution Token"
tFirstPerson_Text[17400]["Text1000512"] = "~which can transform you into an invincible general in the Realm for 10 minutes."

tFirstPerson_Text[17400]["Option10008"] = "Give~me~an~Evolution~Token."
tFirstPerson_Text[17400]["Option10009"] = "Let~me~to~think~about~it."

-- ½Ó1£¬Ê§°Ü£¬±³°ü¿Õ¼ä²»×ã
tFirstPerson_Text[17400]["Text1000611"] = "Your inventory is too full to contain any things. Please clear at least 1 empty space, first."
tFirstPerson_Text[17400]["Option10010"] = "I~see."

-- ½Ó1£¬Ê§°Ü£¬ÉíÉÏÒÑÓÐ
tFirstPerson_Text[17400]["Text1000711"] = "You`ve already claimed an Evolution Token, haven`t you? Go surprise your enemies in the Realm!"
tFirstPerson_Text[17400]["Option10011"] = "I~won`t~let~you~down!"

-- ½Ó1£¬³É¹¦
tFirstPerson_Text[17400]["Text1000811"] = "The Evolution Token will be effective for 10 minutes. Hurry and go fight in the Realm!"
tFirstPerson_Text[17400]["Option10012"] = "Go!"

tFirstPerson_Text[17400]["Option10013"] = "[Realm]~Thunder~Strike."
tFirstPerson_Text[17400]["Option10013New"] = "Thunder~Strike.~(completed)"
tFirstPerson_Text[17400]["Option10016"] = "[Realm]~Crystal~Bounty."
tFirstPerson_Text[17400]["Option10016New"] = "Crystal~Bounty.~(completed)"

-- Ë®¾§êûÉÍ
tFirstPerson_Text[17400]["Text1000911"] = "The Realm has received countless threats, but this time seems different. The enemies are so manic that we`re"
tFirstPerson_Text[17400]["Text1000912"] = "~in the most urgent need of helpers. After killing a certain number of enemies, you can claim a starry"
tFirstPerson_Text[17400]["Text1000913"] = "<tip color=0xfff05050 desc=A#chance#to#get#Dragon#Ball#Piece,#Savage#Bone,#Chi#Points,#Frozen#Chi#Pill,#etc.,#once#a#day.>bounty</tip> from the Realm Crystal."
tFirstPerson_Text[17400]["Option10015"] = "Count~on~me!"

tFirstPerson_Text[3600020] = {}
tFirstPerson_Text[3600020]["UseMap"] = "This token can only be used in the Realm."
tFirstPerson_Text[3600020]["Success"] = "You`ve been transformed into a powerful general. Hurry and sweep off the enemy soldiers!"

tFirstPerson_Text[3007870] = {}
tFirstPerson_Text[3007870]["NoTask"] = "Please make sure you`ve taken the [Spirit Bead] quest, first."
tFirstPerson_Text[3007870]["Success"] = "You`ve completed the [Spirit Bead] quest by fully filling the bead with the spirits contained in the Mighty Soul Seal. Go and claim your reward."
tFirstPerson_Text[3007870]["Complete"] = "You received 360-min EXP, 48-hour Heaven Blessing, 100 Study Points and 1 Chi Token after completing the [Spirit Bead] quest."
tFirstPerson_Text[3007870]["Completed"] = "You`ve already completed today`s [Spirit Bead] quest."
tFirstPerson_Text[3007870]["LessLevel"] = "You should reach at least Level 100 before you can use the [Mighty Soul Seal]."
tFirstPerson_Text[3007870]["NoSpace"] = "Please clear at least 1 empty space in your inventory before using the Mighty Soul Seal."



tFirstPerson_Text["KillMonster"] = "The enemies retreated in a hurry, leaving %s on the ground."
tFirstPerson_Text["Crystal"] = "You`ve restored peace to the Realm by killing 50 enemy soldiers, and received a Realm Crystal Fragment."
tFirstPerson_Text["MonsterNum"] = "You`ve eliminated 50 enemies. Hurry and claim a bounty from the Realm Crystal."
tFirstPerson_Text["Reward"] = "You`ve already collected %d Strike Points. When 300 points are collected, you can claim a reward from the Kingdom Mission Envoy."
tFirstPerson_Text["HasReward"] = "You`ve completed the [Thunder Strike] mission in the realm. Report back to the Kingdom Mission Envoy to claim your reward."

tFirstPerson_Text["NoKill"] = "To claim a bounty, you should kill 50 enemies in the Realm."
tFirstPerson_Text["HaveReward"] = "You`ve already claimed a bounty today. No more to claim."
tFirstPerson_Text["NoEmoney"] = "You don`t have enough CPs to directly complete this mission."
tFirstPerson_Text["HasComplete"] = "You`ve already met the requirement to claim the reward. Don`t waste your CPs."
tFirstPerson_Text["NoSpace"] = "Your inventory is full. Please clear at least 1 empty space, first."
tFirstPerson_Text["Brush"] = "A flood of enemy soldiers emerged from the haze when their leader was killed. Go and clear them!"

tFirstPerson_Text[3008994] = {}
tFirstPerson_Text[3008994]["NoItem"] = "You don`t have enough Dragon Bloodstones to make a Dragon Ball (B)."
tFirstPerson_Text[3008994]["Success"] = "You`ve successfully made a Dragon Ball (B) with the Dragon Bloodstones!"
tFirstPerson_Text[3008994]["NoSpace"] = "Your inventory is full. Please clear at least 1 empty space before opening the pack."

tFirstPerson_Text[3600029] = {}
tFirstPerson_Text[3600029]["ThisService"] = "You can only use the Realm Crystal Fragment in your own server."
tFirstPerson_Text[3600029]["NoSpace"] = "Your inventory is full. Please clear at least 1 empty space, first."
tFirstPerson_Text[3600029]["Success"] = "You received a(n) %s!"

tFirstPerson_Text[3600030] = {}
tFirstPerson_Text[3600030]["ThisService"] = "You can only use the Valiant Exploit Pack in your own server."
tFirstPerson_Text[3600030]["NoTime"] = "You`ve already opened 20 Valiant Exploit Packs today. Please try again tomorrow."
tFirstPerson_Text[3600030]["Success"] = "You received 5 War Exploits!"

tFirstPerson_Text[3200000] = {}
tFirstPerson_Text[3200000]["NoSpace"] = "Your inventory is almost full. Please clear at least 6 empty spaces, first."
tFirstPerson_Text[3200000]["Success"] = "Your excellent performance in the battle has earned yourself a wonderful bountry!"

--------------------------------------------------------------------------------
---Name:160518[Ó¢ÎÄÕ÷·þ][»î¶¯½Å±¾]6ÔÂ³äÖµÀñ°ü
--Creator: 	ÁÖÇ¿
--Created:	2016-05-18
--------------------------------------------------------------------------------


------------------------------------------------------------------------------------
-- Imperial Realm compatibility text: Looting Villages / Burning Village.
------------------------------------------------------------------------------------
tLooting_villages_Text = {}
tLooting_villages_Text["monster"] = {}
tLooting_villages_Text["monster"][1] = "Realm Guard"
tLooting_villages_Text["monster"][2] = "Realm Captain"
tLooting_villages_Text["monster"][3] = "Realm Crystal"
tLooting_villages_Text["monster"][4] = "Village Defender"
tLooting_villages_Text["monster"][5] = "Village Commander"
tLooting_villages_Text["monster"][6] = "Village Beast"

tLooting_villages_Text[1] = "You are too far away from the explosive device."
tLooting_villages_Text[2] = "You have already ignited an explosive device for this mission."
tLooting_villages_Text[4] = "The explosive device is ready."
tLooting_villages_Text[5] = "Destroy the target and return to the Kingdom Mission Envoy."
tLooting_villages_Text[6] = "This Realm mission is no longer available today."
tLooting_villages_Text[8] = "The explosive device has been ignited. Return to the Kingdom Mission Envoy for your reward."
tLooting_villages_Text[9] = "Powerful Realm creatures have appeared!"
tLooting_villages_Text[10] = "Mission complete! You received 30 Kingdom points and a Burning Village Reward."
tLooting_villages_Text[12] = "Please make at least 1 space in your inventory."
tLooting_villages_Text[20] = "You destroyed the Realm Crystal and received its reward."
tLooting_villages_Text[21] = "You defeated the Realm boss and received its reward."

tLooting_villages_Text[17400] = {}
tLooting_villages_Text[17400]["Option600"] = "Burning~Village."
tLooting_villages_Text[17400]["Text60111"] = "Enemies are occupying a village in the Realm."
tLooting_villages_Text[17400]["Text60112"] = "~Find one of their explosive devices and ignite it to disrupt their defenses."
tLooting_villages_Text[17400]["Text60113"] = "~Return to me after the device has been ignited to claim your reward."
tLooting_villages_Text[17400]["Option601"] = "Claim~my~reward."
tLooting_villages_Text[17400]["Option602"] = "I~will~do~it."
tLooting_villages_Text[17400]["Option650"] = "Burning~Village~status."
tLooting_villages_Text[17400]["Text60211"] = "You have not ignited an explosive device in the Realm yet."
tLooting_villages_Text[17400]["Option610"] = "I~understand."
tLooting_villages_Text[17400]["Text60221"] = "You have already claimed this mission reward today."
tLooting_villages_Text[17400]["Option611"] = "Okay."
tLooting_villages_Text[17400]["Option700"] = "Realm~creatures."
tLooting_villages_Text[17400]["Text70111"] = "Dangerous creatures and crystals can appear throughout the Realm."
tLooting_villages_Text[17400]["Text70112"] = "~Defeat them to obtain temporary packs and Realm supplies."
tLooting_villages_Text[17400]["Text70113"] = "~Make sure you have enough inventory space before fighting them."
tLooting_villages_Text[17400]["Option701"] = "Thanks."

tLooting_villages_Text[3600024] = {}
tLooting_villages_Text[3600024]["Nospace"] = "Please make at least 1 space in your inventory."
tLooting_villages_Text[3600024]["Text111"] = "This fragment contains a trace of valuable power."
tLooting_villages_Text[3600024]["Text112"] = "You can cleanse one fragment for a chance at a prize, or combine 5 fragments for a guaranteed prize."
tLooting_villages_Text[3600024]["Option1"] = "Cleanse~1~fragment."
tLooting_villages_Text[3600024]["Option2"] = "Combine~5~fragments."
tLooting_villages_Text[3600024]["Text211"] = "The cleansing succeeded and produced a reward."
tLooting_villages_Text[3600024]["Option3"] = "Okay."
tLooting_villages_Text[3600024]["Text221"] = "The fragment vanished during cleansing."
tLooting_villages_Text[3600024]["Text231"] = "You need 5 fragments to combine them."
tLooting_villages_Text[3600024]["Option4"] = "I~see."
tLooting_villages_Text[3600024]["Text241"] = "The 5 fragments were combined successfully."
tLooting_villages_Text[3600024]["Option5"] = "Great."

tLooting_villages_Text[3600025] = {}
tLooting_villages_Text[3600025][1] = "You received 100 minutes of EXP."
tLooting_villages_Text[3600025][2] = "You received 50 Study Points."
tLooting_villages_Text[3600026] = {}
tLooting_villages_Text[3600026][1] = "You received 50 Golden League points."
tLooting_villages_Text[3600027] = {}
tLooting_villages_Text[3600027][1] = "You received %s."
tLooting_villages_Text[3600031] = {}
tLooting_villages_Text[3600031][1] = "Please make at least 2 spaces in your inventory."
tLooting_villages_Text[3600031][2] = "You received the Refinery Pack rewards."
tLooting_villages_Text[3600033] = {}
tLooting_villages_Text[3600033][1] = "You received 50 Strength points."
tLooting_villages_Text[3200004] = {}
tLooting_villages_Text[3200004]["Nospace"] = "Please make at least 3 spaces in your inventory."
tLooting_villages_Text[3200004][1] = "You opened the Burning Village Reward."
tLooting_villages_Text[3200004][2] = "You opened the Burning Village Reward."


tBossCopy_Text = {}

-- 22084 ¡¾Ä§Í·ÌôÕ½¡¿ÃØ¾³´«ËÍ´óÊ¹
tBossCopy_Text[22084] = {}
tBossCopy_Text[22084]["Text111"] = "There are numerous devils hiding in the Devil Realm. You may win abundant treasures if you dare to challenge!\n"
tBossCopy_Text[22084]["Text112"] = "You can challenge 3 devils that fit your strength. Each of them can be challenged once a day.\n"
tBossCopy_Text[22084]["Text113"] = "Or, you can sweep weaker devils once a day.\n"
tBossCopy_Text[22084]["Text114"] = "Requirement: Level 50\n"
tBossCopy_Text[22084]["Text115"] = "Reward: EXP, Equipment, Chi Points"
-- µÈ¼¶²»×ã
tBossCopy_Text[22084]["Option1"] = "I`ll~come~when~I`m~ready."
-- µÈ¼¶×ã¹»
tBossCopy_Text[22084]["Option2"] = "Challenge~devil~(%d/3)."
tBossCopy_Text[22084]["Option3"] = "Sweep~devils~%s."

-- ½Ó1£¬Íæ¼Ò½ñÈÕÒÑÌôÕ½ÁË3´Î
tBossCopy_Text[22084]["Text211"] = "You have challenged 3 devils today. Just come again tomorrow."
tBossCopy_Text[22084]["Option211"] = "Sure."

-- ½Ó1£¬Íæ¼Ò½ñÈÕÎ´ÌôÕ½¹ý
tBossCopy_Text[22084]["Text221"] = "Please select a level.\nChallenged Today: %s"
tBossCopy_Text[22084]["Option221"] = "Level~%d~devil~(%d/1)."
tBossCopy_Text[22084]["Option222"] = "Level~%d~devil~(%d/1)."
tBossCopy_Text[22084]["Option223"] = "Level~%d~devil~(%d/1)."
tBossCopy_Text[22084]["Option224"] = "Later."

-- Íæ¼ÒÒÑÌôÕ½¹ý±¾¼¶Ä§Í·
tBossCopy_Text[22084]["Text311"] = "You have challenged this devil today."
tBossCopy_Text[22084]["Option311"] = "Challenge~others."

-- Íæ¼ÒÎ´ÌôÕ½¹ý±¾¼¶Ä§Í·
tBossCopy_Text[22084]["Text321"] = "                          *Level %d Devil Reward*\n"
tBossCopy_Text[22084]["Text322"] = "--------------------------------------------------------------------------\n"
tBossCopy_Text[22084]["Text323"] = "Devil Level: %d\n"
tBossCopy_Text[22084]["Text324"] = "Reward: %s\n"
tBossCopy_Text[22084]["Text325"] = "Drop: %s\n"
tBossCopy_Text[22084]["Text326"] = ""
tBossCopy_Text[22084]["Text327"] = "--------------------------------------------------------------------------"
tBossCopy_Text[22084]["Option321"] = "Challenge~now."
tBossCopy_Text[22084]["Option322"] = "Not~now."

-- ½Ó2£¬Íæ¼Ò½ñÈÕÒÑÉ¨µ´¹ý
tBossCopy_Text[22084]["Text231"] = "You have swept the devils today."
tBossCopy_Text[22084]["Option231"] = "Okay"

-- ½Ó2£¬Íæ¼Ò½ñÈÕÎ´É¨µ´¹ý
tBossCopy_Text[22084]["Text241"] = "                            *Sweeping Reward*\n"
tBossCopy_Text[22084]["Text242"] = "--------------------------------------------------------------------------\n"
tBossCopy_Text[22084]["Text243"] = "Devil Level:  Level %d to Level %d\n"
tBossCopy_Text[22084]["Text2411"] = ""
tBossCopy_Text[22084]["Text2412"] = ""
tBossCopy_Text[22084]["Text2413"] = ""
tBossCopy_Text[22084]["Text2414"] = ""
tBossCopy_Text[22084]["Text2415"] = ""
tBossCopy_Text[22084]["Text2416"] = ""
tBossCopy_Text[22084]["Text2417"] = ""
tBossCopy_Text[22084]["Text2418"] = ""
tBossCopy_Text[22084]["Text2419"] = ""
tBossCopy_Text[22084]["Text2420"] = ""
tBossCopy_Text[22084]["Text2421"] = ""
tBossCopy_Text[22084]["Text2422"] = ""
tBossCopy_Text[22084]["Text244"] = "--------------------------------------------------------------------------"
tBossCopy_Text[22084]["Option241"] = "Challenge~now."
tBossCopy_Text[22084]["Option242"] = "Not~now."

-- ½Ó2-1£¬ÒøÁ½³ä×ã£¬±³°ü¿Õ¼ä²»×ã
tBossCopy_Text[22084]["Text331"] = "Please prepare %d spaces in your bag."
tBossCopy_Text[22084]["Option331"] = "Okay."

-- 22085 ¡¾Ä§Í·ÌôÕ½¡¿½±Àø±¦Ïä
tBossCopy_Text[22085] = {}

tBossCopy_Text[22085]["Text111"] = "                         *Reward Box*\n"
tBossCopy_Text[22085]["Text112"] = "--------------------------------------------------------------------------\n"
tBossCopy_Text[22085]["Text113"] = "Devil Level: %d\n"
tBossCopy_Text[22085]["Text114"] = "Reward: %s\n"
tBossCopy_Text[22085]["Text115"] = ""
tBossCopy_Text[22085]["Text116"] = ""
tBossCopy_Text[22085]["Text117"] = "--------------------------------------------------------------------------\n"
tBossCopy_Text[22085]["Text118"] = "Tips: You can pay 500000 Silver to double the reward."
tBossCopy_Text[22085]["Option111"] = "Double~reward~(500000~Silver)."
tBossCopy_Text[22085]["Option112"] = "Claim~reward."

tBossCopy_Text[22085]["Text121"] = "You`ve already claimed this reward. Do you want to go back to Twin City?"
tBossCopy_Text[22085]["Option121"] = "Yes."

-- 22096 ÃØ¾³ÊØ»¤ºÚÁú
tBossCopy_Text[22096] = {}
tBossCopy_Text[22096]["Text111"] = "Here`s a level %d devil. Would you like to challenge?"
tBossCopy_Text[22096]["Option1"] = "Yes."

tBossCopy_Text["Monster"] = {}
-- 50¼¶
tBossCopy_Text["Monster"][1] = {}
tBossCopy_Text["Monster"][1]["Pass"] = "30 minutes` EXP"
tBossCopy_Text["Monster"][1]["Drop"] = "Super Gem (B), Meteor Scroll, Level 50 Super Equipment, etc."
tBossCopy_Text["Monster"][1]["First"] = "Surprise Reward: Elite Level 50 Armor\n"
-- 60¼¶
tBossCopy_Text["Monster"][2] = {}
tBossCopy_Text["Monster"][2]["Pass"] = "40 minutes` EXP, 1 Talent"
tBossCopy_Text["Monster"][2]["Drop"] = "Super Gem (B), Meteor Scroll, Level 60 Super Equipment, etc."
tBossCopy_Text["Monster"][2]["First"] = "Surprise Reward: Elite Level 60 Ring\n"
-- 70¼¶
tBossCopy_Text["Monster"][3] = {}
tBossCopy_Text["Monster"][3]["Pass"] = "50 minutes` EXP, 2 Talents, 50 Study Points"
tBossCopy_Text["Monster"][3]["Drop"] = "Super Gem (B), Meteor Scroll, Level 70 Super Equipment, etc."
tBossCopy_Text["Monster"][3]["First"] = "Surprise Reward: Elite Level 70 Weapon\n"
-- 80¼¶
tBossCopy_Text["Monster"][4] = {}
tBossCopy_Text["Monster"][4]["Pass"] = "60 minutes` EXP, 3 Talents, 100 Study Points"
tBossCopy_Text["Monster"][4]["Drop"] = "Super Gem (B), Super Protection Pill, Level 80 Super Equipment, etc."
tBossCopy_Text["Monster"][4]["First"] = "Surprise Reward: Elite Level 80 Necklace\n"
-- 90¼¶
tBossCopy_Text["Monster"][5] = {}
tBossCopy_Text["Monster"][5]["Pass"] = "70 minutes` EXP, 4 Talents, 200 Study Points"
tBossCopy_Text["Monster"][5]["Drop"] = "Super Gem (B), Super Protection Pill, Level 90 Super Equipment, etc."
tBossCopy_Text["Monster"][5]["First"] = "Surprise Reward: Elite Level 90 Armor\n"
-- 100¼¶
tBossCopy_Text["Monster"][6] = {}
tBossCopy_Text["Monster"][6]["Pass"] = "80 minutes` EXP, 5 Talents, 300 Study Points"
tBossCopy_Text["Monster"][6]["Drop"] = "Super Gem (B), Super Protection Pill, Level 100 Super Equipment, etc."
tBossCopy_Text["Monster"][6]["First"] = "Surprise Reward: StarTower\n"
-- 110¼¶
tBossCopy_Text["Monster"][7] = {}
tBossCopy_Text["Monster"][7]["Pass"] = "90 minutes` EXP, 8 Talents, 400 Study Points"
tBossCopy_Text["Monster"][7]["Drop"] = "Super Gem (B), Super Protection Pill, Level 110 Super Equipment, etc."
tBossCopy_Text["Monster"][7]["First"] = "Surprise Reward: HeavenFan\n"
-- 115¼¶
tBossCopy_Text["Monster"][8] = {}
tBossCopy_Text["Monster"][8]["Pass"] = "100 minutes` EXP, 10 Talents, 500 Study Points"
tBossCopy_Text["Monster"][8]["Drop"] = "Super Gem (B), Free Training Pill, Level 115 Super Equipment, etc."
tBossCopy_Text["Monster"][8]["First"] = "Surprise Reward: TempestWing\n"
-- 120¼¶
tBossCopy_Text["Monster"][9] = {}
tBossCopy_Text["Monster"][9]["Pass"] = "110 minutes` EXP, 100 Chi Points, 600 Study Points"
tBossCopy_Text["Monster"][9]["Drop"] = "Super Protection Pill, 300 Chi Points, Level 120 Super Equipment, etc."
tBossCopy_Text["Monster"][9]["First"] = "Surprise Reward: Dragon Ball (B)\n"
-- 125¼¶
tBossCopy_Text["Monster"][10] = {}
tBossCopy_Text["Monster"][10]["Pass"] = "120 minutes` EXP, 200 Chi Points, 700 Study Points"
tBossCopy_Text["Monster"][10]["Drop"] = "Super Protection Pill, 300 Chi Points, Level 125 Super Equipment, etc."
tBossCopy_Text["Monster"][10]["First"] = "Surprise Reward: Dragon Ball (B)\n"
-- 130¼¶
tBossCopy_Text["Monster"][11] = {}
tBossCopy_Text["Monster"][11]["Pass"] = "130 minutes` EXP, 300 Chi Points, 800 Study Points, 5 Twilight Star Stones"
tBossCopy_Text["Monster"][11]["Drop"] = "Super Protection Pill, 300 Chi Points, Level 130 Super Equipment, etc."
tBossCopy_Text["Monster"][11]["Special"] = "Special Reward: Get a random permanent 1% blessed 3-star garment during the first 3 days after the sever opens.\n"
tBossCopy_Text["Monster"][11]["First"] = "Surprise Reward: Dragon Ball (B)\n"
-- 135¼¶
tBossCopy_Text["Monster"][12] = {}
tBossCopy_Text["Monster"][12]["Pass"] = "200 minutes` EXP, 400 Chi Points, 900 Study Points,  1 Bright Star Stone"
tBossCopy_Text["Monster"][12]["Drop"] = "Super Protection Pill, 300 Chi Points, Level 135 Super Equipment, etc."
tBossCopy_Text["Monster"][12]["Special"] = "Special Reward: Get a random permanent 1% blessed 4-star garment during the first 3 days after the sever opens.\n"
tBossCopy_Text["Monster"][12]["First"] = "Surprise Reward: Dragon Ball (B)\n"
-- 140¼¶
tBossCopy_Text["Monster"][13] = {}
tBossCopy_Text["Monster"][13]["Pass"] = "500 Chi Points, 1000 Study Points, 2 Bright Star Stones"
tBossCopy_Text["Monster"][13]["Drop"] = "Super Protection Pill, 300 Chi Points, Mystery Fruit"
tBossCopy_Text["Monster"][13]["Special"] = "Special Reward: Get a random permanent 1% blessed 5-star garment during the first 3 days after the sever opens.\n"
tBossCopy_Text["Monster"][13]["First"] = "Surprise Reward: Dragon Ball (B)\n"

tBossCopy_Text[3305071] = {}
tBossCopy_Text[3305071][1] = "Sorry, you don`t have 20 Dragon Ball Fragments."
tBossCopy_Text[3305071][2] = "Please prepare 1 space in your bag."

tBossCopy_Text[3305072] = {}
tBossCopy_Text[3305072]["Text111"] = "                                  *Gem Composing*\n"
tBossCopy_Text[3305072]["Text112"] = "*****************************************************\n"
tBossCopy_Text[3305072]["Text113"] = "Rules: 1. Compose into a Super Tortoise Gem for sure.\n"
tBossCopy_Text[3305072]["Text114"] = "             2. Compose into a random Super Gem (except Tortoise Gem).\n"
tBossCopy_Text[3305072]["Text115"] = "Cost: 15 Meteor Essences each time.\n"
tBossCopy_Text[3305072]["Text116"] = "*****************************************************\n"
tBossCopy_Text[3305072]["Option111"] = "Super~Tortoise~Gem~(15~Essences)."
tBossCopy_Text[3305072]["Option112"] = "Random~Super~Gem~(15~Essences)."

tBossCopy_Text[3305072]["NoGemsNum"] = "You don`t have enough Essences."
tBossCopy_Text[3305072]["NoSpace"] = "Please prepare some spaces in your inventory."

tBossCopy_Text[3305073] = {}
tBossCopy_Text[3305073][1] = "Sorry, you don`t have 10 Meteor Scroll Fragments."
tBossCopy_Text[3305073][2] = "Please prepare 1 space in your bag."

-- Ä§Í·ÌôÕ½ÑûÇëº¯
tBackpackLetter_Text[3305076] = {}
tBackpackLetter_Text[3305076]["Text"] = {}
tBackpackLetter_Text[3305076]["Text"]["1-1"] = {111}
tBackpackLetter_Text[3305076]["Text"]["111"] = "There are numerous devils hiding in the Devil Realm. You may win abundant treasures if you dare to challenge!"
tBackpackLetter_Text[3305076]["Text"]["Option1"] = "Talk~to~Realm~Officer."
tBackpackLetter_Text[3305076]["RewardItem"] = "You received a Devil Challenge Invitation! Check it out!"
tBackpackLetter_Text[3305076]["NoSpace"] = "Your inventory is full. Please make a space and login again to get a Devil Challenge Invitation."
tBackpackLetter_Text[3305076]["TimeOut"] = "The Devil Realm has been closed. This invitation is useless now."

tBossCopy_Text["Npc"] = {}
tBossCopy_Text["Npc"]["Name"] = {}
tBossCopy_Text["Npc"]["Name"][1] = "RealmDragon"
tBossCopy_Text["Npc"]["Name"][2] = "RewardBox"

tBossCopy_Text["Msg"] = {}
tBossCopy_Text["Msg"]["Option"] = "(Swept~Today)"
tBossCopy_Text["Msg"]["NotYet"] = ""
tBossCopy_Text["Msg"]["None"] = "None"
tBossCopy_Text["Msg"]["Comma"] = ", "
tBossCopy_Text["Msg"]["Monster"] = "Level %d Devil"
tBossCopy_Text["Msg"]["CleanUp"] = "Reward of Sweeping Level %d Devil: %s\n"
tBossCopy_Text["Msg"]["EnterInstance"] = "You have entered the realm and encountered the Level %d Devil! Win or die!"
tBossCopy_Text["Msg"]["Leave"] = "You have returned to Twin City."
tBossCopy_Text["Msg"]["MoneyNotEnough"] = "You don`t have enough Silver."
tBossCopy_Text["Msg"]["NoSpace"] = "Please prepare %d spaces in your bag."
tBossCopy_Text["Msg"]["Team"] = "You can`t enter the realm in the team status."
tBossCopy_Text["Msg"]["WannaLeave"] = "Do~you~want~to~go~back~to~Twin~City?"
tBossCopy_Text["Msg"]["JustOne"] = "Devil Level:  Level 50\n"

------------------------------------------------------------------------------------
--Name:			160810¡¾Ó¢ÎÄÕ÷·þ¡¿¡¾»î¶¯½Å±¾¡¿9ÔÂ°æ±¾´ÙÏú»î¶¯
--Creator: 		³ÂÑåºê
--Created:		2016/08/10
------------------------------------------------------------------------------------

------------------------------------------------------------------------------------
-- Imperial Realm compatibility text: Beasts of Legend (Four Symbols Bosses)
------------------------------------------------------------------------------------
tFrontier_KillBoss_Text = {}
tFrontier_KillBoss_Text[17400] = {}
tFrontier_KillBoss_Text[17400]["Option750"] = "[Realm]~Beasts~of~Legend."
tFrontier_KillBoss_Text[17400]["Option790"] = "Beasts~of~Legend.~(completed)"
tFrontier_KillBoss_Text[17400]["Text100011"] = "The Four Symbols (Azure Dragon, White Tiger, Vermilion Bird, and Black Turtle) guard the ancient altars in the Realm."
tFrontier_KillBoss_Text[17400]["Text100012"] = "~Defeat 3 Defenders around any Sacred Statue to summon the Sacred Beast itself, then slay it to prove your valor!"
tFrontier_KillBoss_Text[17400]["Text100013"] = "~Once you defeat any of the Four Symbols, return to me to claim a Supreme Gift Pack."
tFrontier_KillBoss_Text[17400]["Option760"] = "Claim~my~Supreme~Gift~Pack."
tFrontier_KillBoss_Text[17400]["Option754"] = "I~will~go~subdue~them."
tFrontier_KillBoss_Text[17400]["Option751"] = "Okay."
tFrontier_KillBoss_Text[17400]["Option752"] = "I~see."
tFrontier_KillBoss_Text[17400]["Option753"] = "Thanks."
tFrontier_KillBoss_Text[17400]["Option756"] = "Later."
tFrontier_KillBoss_Text[17400]["Text70011"] = "Please clear at least 1 empty space in your inventory first."
tFrontier_KillBoss_Text[17400]["Option755"] = "Okay."
tFrontier_KillBoss_Text[17400]["Text80011"] = "You haven`t subdued any of the Four Symbols in the Realm today. Defeat 3 Sacred Defenders around a statue to summon a Sacred Beast!"
tFrontier_KillBoss_Text[17400]["Option770"] = "I~understand."
tFrontier_KillBoss_Text[17400]["Text90011"] = "You have already claimed the Beasts of Legend reward today. Please come back tomorrow."
tFrontier_KillBoss_Text[17400]["Option771"] = "Okay."

tFrontier_KillBoss_Text["Msg"] = {}
tFrontier_KillBoss_Text["Msg"]["KillMonster"] = "You have defeated %d/3 %s. Defeat 3 to summon the Sacred Beast!"
tFrontier_KillBoss_Text["Msg"]["KillFind"] = "The Sacred Beast has been summoned near the altar! Defeat it quickly!"
tFrontier_KillBoss_Text["Msg"]["CompleteTask"] = "You subdued the Sacred Beast! Return to the Kingdom Mission Envoy to claim your reward."
tFrontier_KillBoss_Text["Msg"]["CompleteTheTask"] = "Congratulations! You received a Supreme Gift Pack for completing [Beasts of Legend]."

tFrontier_KillBoss_Text["ItemMsg"] = {}
tFrontier_KillBoss_Text["ItemMsg"]["GetRace"] = "You received 500 Riding Points!"
tFrontier_KillBoss_Text["ItemMsg"]["CompleteTask"] = "You have already completed the [Beasts of Legend] mission today."
tFrontier_KillBoss_Text["ItemMsg"]["CompleteTaskNoSpace"] = "Please clear at least 5 empty spaces in your inventory first."
tFrontier_KillBoss_Text["ItemMsg"]["CompleteTaskGetGift"] = "You opened the Supreme Gift Pack and received your Realm rewards!"
tFrontier_KillBoss_Text["ItemMsg"]["NoSpace"] = "Please clear at least 1 empty space in your inventory first."
tFrontier_KillBoss_Text["ItemMsg"]["Complete"] = "You used the Strategic Bell (Subdue) to directly complete the [Beasts of Legend] mission!"
