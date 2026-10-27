----------------------------------------------------------------------------
--Name:		[征服][基础数据]中文索引表.lua
--Purpose:	中文索引表
--Creator: 	郑江文
--Created:	2014/08/28
----------------------------------------------------------------------------
--key为10000~99999
--10000-29999 公用函数、模板逻辑
--30000-59999 功能脚本
--60000-99999 任务脚本
tLuaRes = {}
tLuaRes[10001] = "Eh..."
tLuaRes[10002] = "See~you."
tLuaRes[10003] = "Leave."

------------------------------------------------------------------------------------
--Name:			[征服][节日任务]悬挂同心锁（2.11-2.14）
--Purpose:		2015年情人节悬挂同心锁（2.11-2.14）
--Creator: 		郑鋆
--Created:		2014/11/28
------------------------------------------------------------------------------------
-- 文字对白
tValentinesDay2015_ConcentricLock_Text = {}
tValentinesDay2015_ConcentricLock_Text[17276] = {}
-- 活动前
tValentinesDay2015_ConcentricLock_Text[17276]["Text111"] = "Have you ever heard about that? If lovers leave the Heart Lock on a romantic place, their love"
tValentinesDay2015_ConcentricLock_Text[17276]["Text112"] = "~will be everlasting. If you`re interested, come and claim a Heart Lock from Feb. 11th to 14th."
tValentinesDay2015_ConcentricLock_Text[17276]["Text113"] = ""
-- 活动后
tValentinesDay2015_ConcentricLock_Text[17276]["Text121"] = "People believe that leaving the Heart Lock on the bridge symbolizes their eternal love."
tValentinesDay2015_ConcentricLock_Text[17276]["Text122"] = ""
-- 活动中
tValentinesDay2015_ConcentricLock_Text[17276]["Text131"] = "People believe that leaving the Heart Lock on the bridge symbolizes their eternal love. If you`ve"
tValentinesDay2015_ConcentricLock_Text[17276]["Text132"] = "~reached Level 80 or get reborn and you want to pray for everlasting love, come and claim your"
tValentinesDay2015_ConcentricLock_Text[17276]["Text133"] = "~Heart Lock from Feb. 11th to 14th."

-- 玩家等级不足
tValentinesDay2015_ConcentricLock_Text[17276]["Text311"] = "Sorry, the Heart Locks are only for heroes who have reached Level 80 or got reborn."
tValentinesDay2015_ConcentricLock_Text[17276]["Text312"] = "~You need to make yourself stronger, first."

-- 玩家选1、失败、当日已完成该任务
tValentinesDay2015_ConcentricLock_Text[17276]["Text321"] = "Come on, you`ve already hung a Heart Lock, today. For a good prayer, you only need to do it once."

-- 玩家选1、失败、玩家处于异性组队状态
tValentinesDay2015_ConcentricLock_Text[17276]["Text331"] = "Well, you have a partner in a team, now. If you want to pray for your own love, you need to be alone first."
tValentinesDay2015_ConcentricLock_Text[17276]["Text332"] = "~If it`s the love between you and your partner you would like to pray for, you need to hang the Heart Lock for both of you."

-- 玩家选1、失败、玩家背包满
tValentinesDay2015_ConcentricLock_Text[17276]["Text341"] = "Come on, I can`t put anything into a full bag. You need to make some room in your inventory, first."

-- 玩家选1、成功、给玩家道具、并导航到第一座桥
tValentinesDay2015_ConcentricLock_Text[17276]["Text351"] = "Please take the Heart Lock and the Heart Key. You`ll need to hang the lock on the bridge (589,355) in the southeast of Wind Plain,"
tValentinesDay2015_ConcentricLock_Text[17276]["Text352"] = "~and then throw the key from the bridge (132,345) in the northwest of Wind Plain. Good luck!"
tValentinesDay2015_ConcentricLock_Text[17276]["Text353"] = ""

-- 玩家选1、补领失败、玩家已完成任务提醒领取奖励
tValentinesDay2015_ConcentricLock_Text[17276]["Text411"] = "It seems you`ve done the love prayer with Heart Lock and Heart Key. Actually, you can claim a reward from me."

-- 玩家选1、补领失败、玩家背包满
tValentinesDay2015_ConcentricLock_Text[17276]["Text421"] = "Your inventory is too full to contain anything. Please make some room, first."

-- 玩家选1、补领失败、玩家身上已有道具或已使用道具
tValentinesDay2015_ConcentricLock_Text[17276]["Text431"] = "You`ve claimed a Heart Lock and a Heart Key, haven`t you? I guess they`re still in your inventory, or maybe you`ve already used them for the love prayer."

-- 玩家选1、补领成功
tValentinesDay2015_ConcentricLock_Text[17276]["Text441"] = "Okay. Now, you`re ready to do the love prayer.  Go hang the lock on the bridge (589,355) in the southeast of Wind Plain,"
tValentinesDay2015_ConcentricLock_Text[17276]["Text442"] = "~and then throw the key from the bridge (132,345) in the northwest of Wind Plain. Remember to be sincere while praying."
tValentinesDay2015_ConcentricLock_Text[17276]["Text443"] = ""

-- 玩家选2、失败、已领取当天奖励
tValentinesDay2015_ConcentricLock_Text[17276]["Text511"] = "You`ve already claimed the reward, today. See, I have no more for you."

-- 玩家选2、失败、玩家未完该活动
tValentinesDay2015_ConcentricLock_Text[17276]["Text521"] = "You haven`t finished the love prayer with the Heart Lock and Heart Key. If so, you can`t claim the reward."

-- 玩家选2、失败、背包满
tValentinesDay2015_ConcentricLock_Text[17276]["Text531"] = "Your inventory is too full! I can`t put anything into it. Why not tidy it up, first?"

-- 玩家选2、成功、领取活动奖励
tValentinesDay2015_ConcentricLock_Text[17276]["Text541"] = "Trust me, your love prayer will be heard. Here is a reward for you."

-- 玩家选3、活动介绍
tValentinesDay2015_ConcentricLock_Text[17276]["Text611"] = "During the event, all qualified heroes can claim a Heart Lock and a Heart Key to pray for eternal love."
tValentinesDay2015_ConcentricLock_Text[17276]["Text612"] = "~First, go to the bridge (589,355) on the southeast of Wind Plain, and right click to hang the Heart Lock."
tValentinesDay2015_ConcentricLock_Text[17276]["Text613"] = "~Then, throw the Heart Key over the bridge (132,345) in the northeast. Don`t forget to claim a reward"
tValentinesDay2015_ConcentricLock_Text[17276]["Text614"] = "~from me after finishing these things."

-- 选项文字
tValentinesDay2015_ConcentricLock_Text[17276]["Option1"] = "Sounds~romantic."
tValentinesDay2015_ConcentricLock_Text[17276]["Option2"] = "I~believe~it~so."
tValentinesDay2015_ConcentricLock_Text[17276]["Option3"] = "I~want~to~hang~the~lock."
tValentinesDay2015_ConcentricLock_Text[17276]["Option4"] = "I~lost~the~lock~and~key."
tValentinesDay2015_ConcentricLock_Text[17276]["Option5"] = "Claim~my~reward."
tValentinesDay2015_ConcentricLock_Text[17276]["Option6"] = "How~to~use~the~lock?"
tValentinesDay2015_ConcentricLock_Text[17276]["Option7"] = "I~have~no~Valentine`s~Day."
tValentinesDay2015_ConcentricLock_Text[17276]["Option9"] = "You`re~right."
tValentinesDay2015_ConcentricLock_Text[17276]["Option10"] = "Okay."
tValentinesDay2015_ConcentricLock_Text[17276]["Option11"] = "Sorry..."
tValentinesDay2015_ConcentricLock_Text[17276]["Option12"] = "Okay."
tValentinesDay2015_ConcentricLock_Text[17276]["Option13"] = "I~need~your~guidance."
tValentinesDay2015_ConcentricLock_Text[17276]["Option14"] = "Great."
tValentinesDay2015_ConcentricLock_Text[17276]["Option15"] = "Sorry..."
tValentinesDay2015_ConcentricLock_Text[17276]["Option16"] = "Okay."
tValentinesDay2015_ConcentricLock_Text[17276]["Option17"] = "I~really~want~it."
tValentinesDay2015_ConcentricLock_Text[17276]["Option18"] = "Go~to~the~bridge~in~southeast."

-- 物品使用提示
tValentinesDay2015_ConcentricLock_Text[3005388] = {}
tValentinesDay2015_ConcentricLock_Text[3005388]["NoPosition"] = "You can`t leave the Heart Lock here. Go to the bridge (589,355) in the southeast of Wind Plain."
tValentinesDay2015_ConcentricLock_Text[3005388]["Complete"] = "The Heart Locks on the bridge are symbols of everlasting love. Go find another bridge, and throw the Heart Key."
tValentinesDay2015_ConcentricLock_Text[3005388]["Content"] = "Hanging"

tValentinesDay2015_ConcentricLock_Text[3005389] = {}
tValentinesDay2015_ConcentricLock_Text[3005389]["NoPosition"] = "You can`t throw the Heart Key here. Go to the bridge (132,345) in the northwest of Wind Plain."
tValentinesDay2015_ConcentricLock_Text[3005389]["Complete"] = "The Heart Key has been thrown into the lake, symbolizing unbreakable love. Go claim your reward from Matchmaker Kiu."
tValentinesDay2015_ConcentricLock_Text[3005389]["Content"] = "Discarding"

tValentinesDay2015_ConcentricLock_Text["BeOverdue"] = "Valentine`s Day is over, and the item is useless now."
tValentinesDay2015_ConcentricLock_Text["ExtraProps"] = "You`ve already used the item and completed this step."
tValentinesDay2015_ConcentricLock_Text["Step"] = "You need to hang the Heart Lock on the bridge first, and then throw the Heart Key into the lake."
tValentinesDay2015_ConcentricLock_Text["Excess"] = "You just need to hang one Heart Lock, while other relevant items have been discarded."
tValentinesDay2015_ConcentricLock_Text["NextDay"] = "The expired item has been discarded by you. You can claim a new Heart Lock from Matchmaker Kiu, today."

-- 陷阱提示
tValentinesDay2015_ConcentricLock_Text[992303] = "Right click the Heart Lock to hang it on the bridge."
tValentinesDay2015_ConcentricLock_Text[992304] = "Right click the Heart Key to throw it into the lake."

------------------------------------------------------------------------------------
--Name:			[征服][节日任务]比翼双飞鸟（2.11-2.14）
--Purpose:		2015年情人节比翼双飞鸟（2.11-2.14）
--Creator: 		郑鋆
--Created:		2014/11/28
------------------------------------------------------------------------------------
-- 中文提示	
tValentinesDay2015_BiyiBirds_Text = {}
tValentinesDay2015_BiyiBirds_Text[17302] = {}
-- 活动前对白
tValentinesDay2015_BiyiBirds_Text[17302]["Text111"] = "Love is the most beautiful thing that everyone desires for. However, there are some monsters with"
tValentinesDay2015_BiyiBirds_Text[17302]["Text112"] = "~a disgusting hobby trying to separate the love birds from Feb. 11th to 14th. If you`re free at that"
tValentinesDay2015_BiyiBirds_Text[17302]["Text113"] = "~time, come and give me a hand."
-- 活动后对白
tValentinesDay2015_BiyiBirds_Text[17302]["Text121"] = "See, there are birds in couples on the trees. Where is my love?"
tValentinesDay2015_BiyiBirds_Text[17302]["Text122"] = ""
-- 活动中对白
tValentinesDay2015_BiyiBirds_Text[17302]["Text131"] = "I don`t really understand those monsters. They must be sick to separate the couples of love birds."
tValentinesDay2015_BiyiBirds_Text[17302]["Text132"] = "~We have to do something to save them from the monsters. If you`ve reached Level 80 or got reborn,"
tValentinesDay2015_BiyiBirds_Text[17302]["Text133"] = "~come and give me a hand from Feb. 11th to 14th. You know, I`m always generous to those who help me."
tValentinesDay2015_BiyiBirds_Text[17302]["Text134"] = ""

-- 接1?姑娘莫急，交给在下?等级不够
tValentinesDay2015_BiyiBirds_Text[17302]["Text311"] = "Thanks for your kindness, but it`s too dangerous for you to face off those disgusting monsters."
tValentinesDay2015_BiyiBirds_Text[17302]["Text312"] = "~Only when you reach Level 80 or get reborn, you may become strong enough."

-- 接1?姑娘莫急，交给在下?今天已完成过
tValentinesDay2015_BiyiBirds_Text[17302]["Text321"] = "You`ve already rescued a couple of love birds. They looks so sweet, right?"
tValentinesDay2015_BiyiBirds_Text[17302]["Text322"] = ""

-- 接1?姑娘莫急，交给在下?今天已完成并未领取奖励
tValentinesDay2015_BiyiBirds_Text[17302]["Text331"] = "You`ve already rescued a couple of love birds. Don`t forget to claim your reward."

-- 接1?姑娘莫急，交给在下?成功
tValentinesDay2015_BiyiBirds_Text[17302]["Text341"] = "Good. The couple of love birds were separately locked up in the Winged Cage and the Couple Cage."
tValentinesDay2015_BiyiBirds_Text[17302]["Text342"] = "~Some monsters on Wind Plain have the Winged Box or Couple Box with corresponding cage inside,"
tValentinesDay2015_BiyiBirds_Text[17302]["Text343"] = "~while some don`t. When you have the Winged Cage and the Couple Cage together, you can open"
tValentinesDay2015_BiyiBirds_Text[17302]["Text344"] = "~them at the same time on the city wall (TwinCity 248,292) and set the love birds free."

-- 【接1、姑娘莫急、玩家接任务但未完成任务】
tValentinesDay2015_BiyiBirds_Text[17302]["Text351"] = "Have you found the Winged Cage and the Couple Cage? The love birds were separately locked up in the two cages. Hurry and rescue them!"

-- 接2?领取奖励?已领取过
tValentinesDay2015_BiyiBirds_Text[17302]["Text411"] = "You`ve claimed the reward, haven`t you? I hope you like it. Thanks!"
tValentinesDay2015_BiyiBirds_Text[17302]["Text412"] = ""

-- 接2?领取奖励?任务未完成
tValentinesDay2015_BiyiBirds_Text[17302]["Text421"] = "It`s not time for rewards. Remember, the love birds are still in distress. You should help them out, first!"
tValentinesDay2015_BiyiBirds_Text[17302]["Text422"] = ""

-- 接2?领取奖励?玩家背包满
tValentinesDay2015_BiyiBirds_Text[17302]["Text431"] = "Hey, I can`t put anything into your full inventory. Why not make some room, first?"

-- 接2?领取奖励?成功领取
tValentinesDay2015_BiyiBirds_Text[17302]["Text441"] = "Thanks for rescuing the love birds. Well, here`s a reward for you as I promised."
tValentinesDay2015_BiyiBirds_Text[17302]["Text442"] = ""

-- 接3?可否请姑娘详细一说
tValentinesDay2015_BiyiBirds_Text[17302]["Text511"] = "Some monsters captured couples of love birds, and separately locked up them in Winged Cage and"
tValentinesDay2015_BiyiBirds_Text[17302]["Text512"] = "~Couple Cage. While hunting monsters on Wind Plain, you`ll have a chance to receive Winged Box or Couple Box"
tValentinesDay2015_BiyiBirds_Text[17302]["Text513"] = "~with corresponding cage inside. You may also get empty boxes. When you collect a Winged Cage and a"
tValentinesDay2015_BiyiBirds_Text[17302]["Text514"] = "~Couple Cage, open them at the same time on the city wall (TwinCity 248,292) and set the love birds free."

-- 选项
tValentinesDay2015_BiyiBirds_Text[17302]["Option1"] = "I`ll~help."
tValentinesDay2015_BiyiBirds_Text[17302]["Option2"] = "You`ll~find~your~true~love."
tValentinesDay2015_BiyiBirds_Text[17302]["Option3"] = "Count~on~me!"
tValentinesDay2015_BiyiBirds_Text[17302]["Option4"] = "Claim~my~reward."
tValentinesDay2015_BiyiBirds_Text[17302]["Option5"] = "Tell~me~more."
tValentinesDay2015_BiyiBirds_Text[17302]["Option6"] = "I`ll~talk~to~you~later."
tValentinesDay2015_BiyiBirds_Text[17302]["Option7"] = "You`re~right."
tValentinesDay2015_BiyiBirds_Text[17302]["Option8"] = "Love~is~love."
tValentinesDay2015_BiyiBirds_Text[17302]["Option9"] = "You`re~right."
tValentinesDay2015_BiyiBirds_Text[17302]["Option10"] = "Don`t~worry."
tValentinesDay2015_BiyiBirds_Text[17302]["Option11"] = "You`re~welcome."
tValentinesDay2015_BiyiBirds_Text[17302]["Option12"] = "I`m~on~the~way."
tValentinesDay2015_BiyiBirds_Text[17302]["Option13"] = "Okay."
tValentinesDay2015_BiyiBirds_Text[17302]["Option14"] = "You~can~count~on~me."

tValentinesDay2015_BiyiBirds_Text[3005441] = {}
tValentinesDay2015_BiyiBirds_Text[3005441]["NoItem"] = "You opened the Winged Box, and found nothing inside."
tValentinesDay2015_BiyiBirds_Text[3005441]["RewardItem"] = "You opened the Winged Box, and received a Winged Cage."
tValentinesDay2015_BiyiBirds_Text[3005441]["Reward"] = "You killed monsters without mercy, and found a Winged Box on the ground. Hurry and check it."

tValentinesDay2015_BiyiBirds_Text[3005442] = {}
tValentinesDay2015_BiyiBirds_Text[3005442]["NoItem"] = "You opened the Couple Box, and found nothing inside."
tValentinesDay2015_BiyiBirds_Text[3005442]["RewardItem"] = "You opened the Couple Box, and received a Couple Cage."
tValentinesDay2015_BiyiBirds_Text[3005442]["Reward"] = "The monster fell down and dropped a Couple Box. Hurry and check it."

tValentinesDay2015_BiyiBirds_Text["BeOverdue"] = "Valentine`s Day has ended. The item became useless, and you threw it away."
tValentinesDay2015_BiyiBirds_Text["BagFull"] = "Your inventory is full. Please make some room, first."
tValentinesDay2015_BiyiBirds_Text["NotAllItem"] = "You`re unable to open the cage. The bird in the cage is crying for its lover."
tValentinesDay2015_BiyiBirds_Text["UseItemNavigat"] = "You can`t open the cage, here. Please walk onto the city wall (TwinCity 248,292), and set the love birds free."
tValentinesDay2015_BiyiBirds_Text["AllItem"] = "You`ve collected the Winged Cage and the Couple Cage. Go and set the birds free on the city wall (TwinCity 248,292)."
tValentinesDay2015_BiyiBirds_Text["NextDay"] = "There is nothing in the cage."
tValentinesDay2015_BiyiBirds_Text["HaveComplete"] = "You`ve already set the love birds free from the cage."
tValentinesDay2015_BiyiBirds_Text["Complete"] = "You unlocked the cages, and set the love birds free!"

tValentinesDay2015_BiyiBirds_Text[992310] = {}
tValentinesDay2015_BiyiBirds_Text[992310][1] = "This is the right place to set the love birds free."
tValentinesDay2015_BiyiBirds_Text[992310][2] = "This is the right place to set the love birds free."
tValentinesDay2015_BiyiBirds_Text[992311] = "Go collect the Winged Box and the Couple Box from monsters on Wind Plain."


------------------------------------------------------------------------------------
--Name:		[征服][任务脚本]通用礼包逻辑修改为用LUA
--Purpose:	通用礼包逻辑修改为用LUA
--Creator: 	严振飞
--Created:	2014/10/28
------------------------------------------------------------------------------------
tFestivalGeneralPackage = {}
tFestivalGeneralPackage["Bag_Full"] = "Your inventory is full. Please make some room first, and then login again to receive a gift."
tFestivalGeneralPackage["Get_Gift"] = "You received a Festival Joy Pack!"
tFestivalGeneralPackage["OverLimit_Msg"] = "You can`t claimed more than %s Festival Joy Packs in a day."


------------------------------------------------------------------------------------
--Name:		[征服][活动脚本]情人节活动之神父的祝福
--Purpose:	情人节活动之神父的祝福
--Creator: 	严振飞
--Created:	2014/11/07
------------------------------------------------------------------------------------
-------------NPC对白
-- //查理神父
tValentinesDay2015_Priest_Text = {}
tValentinesDay2015_Priest_Text[17285] = {}

-- 活动前对白
tValentinesDay2015_Priest_Text[17285]["Text111"] = "Every year when Valentine`s Day comes, I`ll travel around and deliver blessing to lovers. If you`re looking for true"
tValentinesDay2015_Priest_Text[17285]["Text112"] = "~love and seeking for happiness, come and find me on Feb. 11th - 14th."
tValentinesDay2015_Priest_Text[17285]["Text113"] = ""

-- 活动中对白
tValentinesDay2015_Priest_Text[17285]["Text121"] = "Happy Valentine`s Day! As called by goddess of love, I`m delivering blessing to lovers in Twin City. If you`re looking for true"
tValentinesDay2015_Priest_Text[17285]["Text122"] = "~love and seeking for happiness, come and find me on Feb. 11th - 14th. I`ll do a prayer for you."
tValentinesDay2015_Priest_Text[17285]["Text123"] = ""

-- 活动后对白
tValentinesDay2015_Priest_Text[17285]["Text131"] = "What a romantic festival! Thanks for giving me an unforgettable memory of love."
tValentinesDay2015_Priest_Text[17285]["Text132"] = ""

-- 【我想了解活动详情。】
tValentinesDay2015_Priest_Text[17285]["Text211"] = "Of course, you`re interested in the events. So, what would you like to learn more?"

-- 【我想了解活动详情。】--> 我想知道情人节有什么活动。
tValentinesDay2015_Priest_Text[17285]["Text311"] = "I`m responsible for delivering blessing and explaining the events of Valentine Days. During the festival, you can claim blessing"
tValentinesDay2015_Priest_Text[17285]["Text312"] = "~from me every day, and sign up for wonderful quests with my friends around the flower bed in Twin City. After completing all the events, you can"
tValentinesDay2015_Priest_Text[17285]["Text313"] = "~also claim a special gift pack from me, once in a day. So, which quest are you interested?"

-- 【我想了解活动详情。】--> 我想知道情人节有什么活动。--> 比翼双飞。
tValentinesDay2015_Priest_Text[17285]["Text411"] = "In the season of love, people are immersed in sweetness, but Smart Sue looks worried. Some disgusting monsters captured"
tValentinesDay2015_Priest_Text[17285]["Text412"] = "~couples of love birds and separated them in cages. Sue is calling heroes above Level 80 or reborn to rescue the love birds"
tValentinesDay2015_Priest_Text[17285]["Text413"] = "~from monsters on Wind Plain from Feb. 11th to 14th."

-- 【我想了解活动详情。】--> 我想知道情人节有什么活动。--> 美女与野兽。
tValentinesDay2015_Priest_Text[17285]["Text511"] = "Siegfride was cursed to be a beast since he refused to put up an old woman. It`s said only when he learns to be kind to people"
tValentinesDay2015_Priest_Text[17285]["Text512"] = "~and receives 99 Lover`s Roses from Feb. 11th to 14th, the curse can be dispelled. Siegfride`s lover, Bella, is asking help from the"
tValentinesDay2015_Priest_Text[17285]["Text513"] = "~heroes who`ve reached Level 80 or got reborn."

-- 【我想了解活动详情。】--> 我想知道情人节有什么活动。--> 悬挂同心锁。
tValentinesDay2015_Priest_Text[17285]["Text611"] = "It`s an old story. Lovers who hang the Heart Lock on a spiritual bridge will never apart. Matchmaker Kiu just happened"
tValentinesDay2015_Priest_Text[17285]["Text612"] = "~to have some Heart Locks. If you`ve reached Level 80 or got reborn and you`re interested, go claim one from Matchmaker"
tValentinesDay2015_Priest_Text[17285]["Text613"] = "~Kiu on Feb. 11th - 14th for a love prayer."

-- 【我想了解活动详情。】--> 我想知道情人节有什么活动。--> 眉来眼去传真情。
tValentinesDay2015_Priest_Text[17285]["Text711"] = "From Feb. 11th to 14th, Lady Autumn and Master Hwang will appear at (TwinCity 285,359) and share a legendary"
tValentinesDay2015_Priest_Text[17285]["Text712"] = "~scripture of martial arts, True Love Manual, with Level 80+ or reborn heroes as a Valentine`s Day gift."

-- 【我想了解活动详情。】--> 我想知道情人节有什么活动。--> 甜蜜约会之非诚勿扰。
tValentinesDay2015_Priest_Text[17285]["Text811"] = "Matchmaker Yiu is incredibly busy. His assistant, Fat, disappeared. There are many single men and women waiting for a match"
tValentinesDay2015_Priest_Text[17285]["Text812"] = "~in his office. All in all, Yiu is seriously short of hands. If you`ve reached Level 80 or got reborn, go and do him a favor."
tValentinesDay2015_Priest_Text[17285]["Text813"] = ""

-- 【我想了解活动详情。】--> 爱情玫瑰要怎么换取外套呢？
tValentinesDay2015_Priest_Text[17285]["Text911"] = "The Love Rose with delicate petals and mysterious scent is a blessing to Valentine`s Day. From Feb. 11th to 14th, every time"
tValentinesDay2015_Priest_Text[17285]["Text912"] = "~when you complete a quest of Valentine`s Day, you`ll be rewarded with a Love Rose. When you have 5 Love Roses, you can"
tValentinesDay2015_Priest_Text[17285]["Text913"] = "~sweep them for a 3-hour 1%% Blessed weapon accessory, Rod of Rose, with me."

-- 【我想了解活动详情。】--> 我想知道送长梗玫瑰的事情。
tValentinesDay2015_Priest_Text[17285]["Text1011"] = "To celebrate the romantic festival, heroes are presented with the Roses of Everlasting. I want you to share that with those friends"
tValentinesDay2015_Priest_Text[17285]["Text1012"] = "~working for Valentine`s Day events. Good things will become better when you share. After that, you can claim a Festival Joy Pack from me."
tValentinesDay2015_Priest_Text[17285]["Text1013"] = "~By the way, if you lost the Roses of Everlasting before finishing the job, you can login again to reclaim another bunch."

-- 【我要领取全活动完成奖励。】
tValentinesDay2015_Priest_Text[17285]["Text1111"] = "Valentine`s Day has passed, and you can`t claim a reward for completing all the quest."
tValentinesDay2015_Priest_Text[17285]["Text1121"] = "Thanks for coming, but you`re still too green for the quests of Valentine`s Day."
tValentinesDay2015_Priest_Text[17285]["Text1122"] = "~Keep practicing, and come back when you`re qualified."
tValentinesDay2015_Priest_Text[17285]["Text1131"] = "Come on, I can`t put anything into your full inventory. You need to make some room, first."
tValentinesDay2015_Priest_Text[17285]["Text1141"] = "It seems you`ve already claimed a gift pack. You must be too excited to check it well."
tValentinesDay2015_Priest_Text[17285]["Text1151"] = "Buddy, you haven`t completed all the quests of Valentine`s Day. You`ll find more interesting things in Valentine`s Day celebration."
tValentinesDay2015_Priest_Text[17285]["Text1161"] = "Here`s a Festival Joy Pack for you. Wish you a happy life!"

-- 【我要换取情人节外套。】
tValentinesDay2015_Priest_Text[17285]["Text1211"] = "Let me see... Wow, you really have 5 Love Roses! Look, you can swap them for a 3-hour 1%% Blessed weapon accessory or garment."
tValentinesDay2015_Priest_Text[17285]["Text1212"] = "~So, which one do you want, the Rod of Roses or the Cogs of the Heart?"
tValentinesDay2015_Priest_Text[17285]["Text1213"] = ""

-- 【我要换取情人节外套。】--> 我要换取玫瑰风暴武器外套。
tValentinesDay2015_Priest_Text[17285]["Text1311"] = "The Rod of Rose belongs to you, now. Happy Valentine`s Day!"

-- 【我要换取情人节外套。】--> 我要换取情人之泪外套。
tValentinesDay2015_Priest_Text[17285]["Text1411"] = "The Cogs of the Heart belong to you, now. Happy Valentine`s Day!"

-- 【我要换取情人节外套。】--> 我要换取玫瑰风暴武器外套。
tValentinesDay2015_Priest_Text[17285]["Text1511"] = "The event is over, and you can`t swap for Rod of Roses now."
tValentinesDay2015_Priest_Text[17285]["Text1521"] = "Buddy, I know you really want the beautiful weapon accessory, but you should train yourself strong enough first."
tValentinesDay2015_Priest_Text[17285]["Text1522"] = "~When you reach Level 80 or get reborn, you`ll be able to take the quests for winning a Rod of Roses."
tValentinesDay2015_Priest_Text[17285]["Text1531"] = "Why are you carrying a full bag? You need to make some room in the inventory for the reward, first."
tValentinesDay2015_Priest_Text[17285]["Text1541"] = "Buddy, I know you really want the beautiful weapon accessory, but you should have 5 Love Roses to swap for it. Go collect the roses from Valentine`s Day quests."
tValentinesDay2015_Priest_Text[17285]["Text1551"] = "Are you sure you want to swap the 5 Love Roses for a Rod of Roses weapon accessory?"

-- 【我要换取情人节外套。】--> 我要换取情人之泪外套。
tValentinesDay2015_Priest_Text[17285]["Text1611"] = "The event is over, and you can`t swap for Cogs of the Heart now."
tValentinesDay2015_Priest_Text[17285]["Text1621"] = "Buddy, I know you really want the delicate garment, but you should train yourself strong enough first."
tValentinesDay2015_Priest_Text[17285]["Text1622"] = "~When you reach Level 80 or get reborn, you`ll be able to take the quests for winning the Cogs of the Heart."
tValentinesDay2015_Priest_Text[17285]["Text1631"] = "Why are you carrying a full bag? You need to make some room in the inventory for the reward, first."
tValentinesDay2015_Priest_Text[17285]["Text1641"] = "Buddy, I know you really want the delicate garment, but you should have 5 Love Roses to swap for it. Go collect the roses from Valentine`s Day quests."
tValentinesDay2015_Priest_Text[17285]["Text1651"] = "Are you sure you want to swap the 5 Love Roses for Cogs of the Heart garment?"

-- 【我要签到领祝福。】
tValentinesDay2015_Priest_Text[17285]["Text1711"] = "The event is over, and you can`t claim the sign-up blessing now."
tValentinesDay2015_Priest_Text[17285]["Text1721"] = "You`re not qualified for the blessing reward. Keep practicing."
tValentinesDay2015_Priest_Text[17285]["Text1731"] = "You`ve already claimed the blessing. Come and try again tomorrow."
tValentinesDay2015_Priest_Text[17285]["Text1741"] = "The priest`s smile makes you happy and warm, and you received 3 hours of Heaven Blessing."

-- 【我要领取送长梗玫瑰奖励。】（领取礼包后选项消失）
tValentinesDay2015_Priest_Text[17285]["Text1811"] = "It seems someone hasn`t received your Rose of Everlasting. You need to finish the job, first."
tValentinesDay2015_Priest_Text[17285]["Text1821"] = "Thanks for delivering the Roses of Everlasting to my friends. Here`s a Festival Joy Pack for you."

-------------选项
tValentinesDay2015_Priest_Text[17285]["Option11"] = "Great."
tValentinesDay2015_Priest_Text[17285]["Option12"] = "Sign~up~for~blessing."
tValentinesDay2015_Priest_Text[17285]["Option13"] = "Tell~me~more~about~the~event."
tValentinesDay2015_Priest_Text[17285]["Option14"] = "I`ve~completed~rose~delivery."
tValentinesDay2015_Priest_Text[17285]["Option15"] = "I`ve~completed~all~the~quests."
tValentinesDay2015_Priest_Text[17285]["Option16"] = "Swap~Love~Roses."
tValentinesDay2015_Priest_Text[17285]["Option17"] = "What~a~good~priest."
tValentinesDay2015_Priest_Text[17285]["Option18"] = "Good~luck~for~you."
tValentinesDay2015_Priest_Text[17285]["Option21"] = "What~for~Valentine`s~Day?"
tValentinesDay2015_Priest_Text[17285]["Option22"] = "Roses~of~Everlasting~delivery."
tValentinesDay2015_Priest_Text[17285]["Option23"] = "How~to~swap~the~Love~Roses?"
tValentinesDay2015_Priest_Text[17285]["Option24"] = "I`m~just~passing~by."
tValentinesDay2015_Priest_Text[17285]["Option31"] = "Love~Birds."
tValentinesDay2015_Priest_Text[17285]["Option32"] = "Beauty~and~the~Beast."
tValentinesDay2015_Priest_Text[17285]["Option33"] = "The~Heart~Lock."
tValentinesDay2015_Priest_Text[17285]["Option34"] = "True~Love~Manual."
tValentinesDay2015_Priest_Text[17285]["Option35"] = "Sweet~Date."
tValentinesDay2015_Priest_Text[17285]["Option36"] = "Sounds~interesting."
tValentinesDay2015_Priest_Text[17285]["Option41"] = "I`m~on~the~way."
tValentinesDay2015_Priest_Text[17285]["Option42"] = "Learn~about~other~things."
tValentinesDay2015_Priest_Text[17285]["Option51"] = "I`m~on~the~way."
tValentinesDay2015_Priest_Text[17285]["Option52"] = "Learn~about~other~things."
tValentinesDay2015_Priest_Text[17285]["Option61"] = "I`m~on~the~way."
tValentinesDay2015_Priest_Text[17285]["Option62"] = "Learn~about~other~things."
tValentinesDay2015_Priest_Text[17285]["Option71"] = "I`m~on~the~way."
tValentinesDay2015_Priest_Text[17285]["Option72"] = "Learn~about~other~things."
tValentinesDay2015_Priest_Text[17285]["Option81"] = "I`m~on~the~way."
tValentinesDay2015_Priest_Text[17285]["Option82"] = "Learn~about~other~things."
tValentinesDay2015_Priest_Text[17285]["Option91"] = "Swap~the~Love~Roses."
tValentinesDay2015_Priest_Text[17285]["Option92"] = "I`ll~go~collect~Love~Roses."
tValentinesDay2015_Priest_Text[17285]["Option101"] = "I~see."
tValentinesDay2015_Priest_Text[17285]["Option111"] = "I~see."
tValentinesDay2015_Priest_Text[17285]["Option112"] = "I`ll~come~back."
tValentinesDay2015_Priest_Text[17285]["Option113"] = "I`ll~do~it~now."
tValentinesDay2015_Priest_Text[17285]["Option114"] = "Sorry,~I~forgot."
tValentinesDay2015_Priest_Text[17285]["Option11501"] = "I`ll~go~find~Smart~Sue."
tValentinesDay2015_Priest_Text[17285]["Option11502"] = "I`ll~go~find~Bella."
tValentinesDay2015_Priest_Text[17285]["Option11503"] = "I`ll~go~find~Matchmaker~Kiu."
tValentinesDay2015_Priest_Text[17285]["Option11504"] = "I`ll~go~find~Master~Hwang."
tValentinesDay2015_Priest_Text[17285]["Option11505"] = "I`ll~go~find~Lady~Autumn."
tValentinesDay2015_Priest_Text[17285]["Option11506"] = "I`ll~go~find~Matchmaker~Yiu."
tValentinesDay2015_Priest_Text[17285]["Option11507"] = "I~need~to~take~a~rest."
tValentinesDay2015_Priest_Text[17285]["Option116"] = "Happy~Valentine`s~Day!"
tValentinesDay2015_Priest_Text[17285]["Option121"] = "Swap~for~Rod~of~Roses."
tValentinesDay2015_Priest_Text[17285]["Option122"] = "Swap~for~Cogs~of~the~Heart."
tValentinesDay2015_Priest_Text[17285]["Option123"] = "I`ll~think~about~it."
tValentinesDay2015_Priest_Text[17285]["Option131"] = "Happy~Valentine`s~Day!"
tValentinesDay2015_Priest_Text[17285]["Option141"] = "Happy~Valentine`s~Day!"
tValentinesDay2015_Priest_Text[17285]["Option151"] = "I~see."
tValentinesDay2015_Priest_Text[17285]["Option152"] = "Alright."
tValentinesDay2015_Priest_Text[17285]["Option153"] = "I`ll~do~it~now."
tValentinesDay2015_Priest_Text[17285]["Option154"] = "What~a~pity."
tValentinesDay2015_Priest_Text[17285]["Option155"] = "Yes."
tValentinesDay2015_Priest_Text[17285]["Option156"] = "No."
tValentinesDay2015_Priest_Text[17285]["Option161"] = "I~see."
tValentinesDay2015_Priest_Text[17285]["Option162"] = "Alright."
tValentinesDay2015_Priest_Text[17285]["Option163"] = "I`ll~do~it~now."
tValentinesDay2015_Priest_Text[17285]["Option164"] = "What~a~pity."
tValentinesDay2015_Priest_Text[17285]["Option165"] = "Yes."
tValentinesDay2015_Priest_Text[17285]["Option166"] = "No."

tValentinesDay2015_Priest_Text[17285]["Option171"] = "Okay."
tValentinesDay2015_Priest_Text[17285]["Option172"] = "Alright."
tValentinesDay2015_Priest_Text[17285]["Option173"] = "I~see."
tValentinesDay2015_Priest_Text[17285]["Option174"] = "Good!"
tValentinesDay2015_Priest_Text[17285]["Option181"] = "I`ll~go~find~Smart~Sue."
tValentinesDay2015_Priest_Text[17285]["Option182"] = "I`ll~go~find~Bella."
tValentinesDay2015_Priest_Text[17285]["Option183"] = "I`ll~go~find~Matchmaker~Kiu."
tValentinesDay2015_Priest_Text[17285]["Option184"] = "I`ll~go~find~Master~Hwang."
tValentinesDay2015_Priest_Text[17285]["Option185"] = "I`ll~go~find~Lady~Autumn."
tValentinesDay2015_Priest_Text[17285]["Option186"] = "I`ll~go~find~Matchmaker~Yiu."
tValentinesDay2015_Priest_Text[17285]["Option187"] = "I~need~to~take~a~rest."
tValentinesDay2015_Priest_Text[17285]["Option188"] = "Happy~Valentine`s~Day!"

-------------其他NPC对白
-- //苏巧儿
tValentinesDay2015_Priest_Text[17302] = {}
tValentinesDay2015_Priest_Text[17302]["Text4011"] = "Thanks! I really love roses. They look more beautiful on Valentine`s Day, don`t they?"
tValentinesDay2015_Priest_Text[17302]["Option402"] = "Indeed."

-- //美女贝儿
tValentinesDay2015_Priest_Text[17287] = {}
tValentinesDay2015_Priest_Text[17287]["Text4011"] = "Wow, this is my favorite flower! Thanks!"
tValentinesDay2015_Priest_Text[17287]["Option402"] = "You`re~welcome."

-- //红娘娇燕燕
tValentinesDay2015_Priest_Text[17276] = {}
tValentinesDay2015_Priest_Text[17276]["Text4011"] = "Ha, it`s the first time I received roses as a matchmaker. I guess, my love is not far away."
tValentinesDay2015_Priest_Text[17276]["Option402"] = "Good~luck!"

-- //男媒婆姚大痣
tValentinesDay2015_Priest_Text[17321] = {}
tValentinesDay2015_Priest_Text[17321]["Text4011"] = "Are you sure the roses are for me? I`m really surprised. Thank you very much!"
tValentinesDay2015_Priest_Text[17321]["Option402"] = "Happy~Valentine`s~Day!"

-------------其他对白
tValentinesDay2015_Priest_Text["Login_Success"] = "You received Roses of Everlasting. Go and present them to the people working for Valentine`s Day celebration. After that, you can claim a reward from Priest Charlie."
tValentinesDay2015_Priest_Text["Login_BagFull"] = "Your inventory is full. Please make some room first, and then login again to receive the Roses of Everlasting."
tValentinesDay2015_Priest_Text["Item_LoveRose"] = "You can collect Love Roses by participating Valentine`s Day events. When you have 5 Love Roses, swap them for a weapon accessory or garment with Charlie."
tValentinesDay2015_Priest_Text["Item_LongRose"] = "You`ve smelt the roses, and received 1-day Heaven Blessing. Hurry and deliver the roses to the people working for Valentine`s Day celebration."
tValentinesDay2015_Priest_Text["Del_LoveRose"] = "Valentine`s Day has passed, and the Love Roses withered."
tValentinesDay2015_Priest_Text["Del_LongRose"] = "Valentine`s Day has passed, and the Roses of Everlasting disappeared."
tValentinesDay2015_Priest_Text["Flower_Finish"] = "You`ve delivered all the roses. Go and claim your reward from Priest Charlie."
tValentinesDay2015_Priest_Text["NoLongRose_Text"] = "Where is the rose you mentioned?"
tValentinesDay2015_Priest_Text["NoLongRose_Option"] = "I`ll~check~it~again."
tValentinesDay2015_Priest_Text["LongRose_Option"] = "Present~the~rose."

--祝福奖励（数字表示STC掩码编号）
tValentinesDay2015_Priest_Text["AddBless_SysTip"] = {}
tValentinesDay2015_Priest_Text["AddBless_SysTip"][11] = "You smelt the roses, and received 1 day of Heaven Blessing!"
tValentinesDay2015_Priest_Text["AddBless_SysTip"][12] = "Priest Charlie gave you a warm smile, and you received 3 hours of Heaven Blessing!"

-------------物品对白
tValentinesDay2015_Priest_ItemText = {}
--长梗玫瑰
tValentinesDay2015_Priest_ItemText[3005411] = {}
tValentinesDay2015_Priest_ItemText[3005411]["Text111"] = "Are you sure you want to find Priest Charlie for Valentine`s Day events?"

-------------选项
tValentinesDay2015_Priest_ItemText[3005411]["Option11"] = "Yes."
tValentinesDay2015_Priest_ItemText[3005411]["Option12"] = "No."


--3小时玫瑰风暴武器外套礼盒
tValentinesDay2015_Priest_ItemText[3005577] = {}
tValentinesDay2015_Priest_ItemText[3005577]["Text111"] = "Which one do you want to claim?"
--【玫瑰风暴（短武器）。】
tValentinesDay2015_Priest_ItemText[3005577]["Text211"] = "Are you sure you want the 3-hour 1%% Blessed 1-handed weapon accessory, Rod of Rose?"
--【玫瑰风暴（长武器）。】
tValentinesDay2015_Priest_ItemText[3005577]["Text311"] = "Are you sure you want the 3-hour 1%% Blessed 2-handed weapon accessory, Rod of Rose?"

-------------选项
tValentinesDay2015_Priest_ItemText[3005577]["Option11"] = "Rod~of~Roses~(1-handed)."
tValentinesDay2015_Priest_ItemText[3005577]["Option12"] = "Rod~of~Roses~(2-handed)."
tValentinesDay2015_Priest_ItemText[3005577]["Option21"] = "Yes."
tValentinesDay2015_Priest_ItemText[3005577]["Option22"] = "No."
tValentinesDay2015_Priest_ItemText[3005577]["Option31"] = "Yes."
tValentinesDay2015_Priest_ItemText[3005577]["Option32"] = "No."

-------------其他对白
--获得玫瑰风暴外套
tValentinesDay2015_Priest_ItemText["ChgCoat_Success"] = {}
tValentinesDay2015_Priest_ItemText["ChgCoat_Success"][3] = "You received a 3-hour 1%% Blessed 1-handed weapon accessory, Rod of Rose!"
tValentinesDay2015_Priest_ItemText["ChgCoat_Success"][4] = "You received a 3-hour 1%% Blessed 2-handed weapon accessory, Rod of Rose!"



------------------------------------------------------------------------------------
--Name:			[征服][节日任务]眉来眼去传真情（2.11-2.14）
--Purpose:		2015年情人眉来眼去传真情（2.11-2.14）
--Creator: 		陈麟泉
--Created:		2014/11/05
------------------------------------------------------------------------------------

tValentinesDay2015_Flirt_NpcGossip = {}

--素秋师妹
tValentinesDay2015_Flirt_NpcGossip[10078] = {}
tValentinesDay2015_Flirt_NpcGossip[10078]["BeforeEvent"] = {}
tValentinesDay2015_Flirt_NpcGossip[10078]["BeforeEvent"]["Text1"] = "It`s been a long time since Master Hwang and I started training martial arts on the mountain. Boring...ing..., you know."
tValentinesDay2015_Flirt_NpcGossip[10078]["BeforeEvent"]["Text2"] = "~Anyway, we`re going to celebrate Valentine`s Day in Twin City, and share the `True Love Manual` with heroes above Level 80 or reborn from Feb. 11th to 14th."
tValentinesDay2015_Flirt_NpcGossip[10078]["BeforeEvent"]["Option1"] = "I~can`t~wait~to~see~it."

tValentinesDay2015_Flirt_NpcGossip[10078]["AfterEvent"] = {}
tValentinesDay2015_Flirt_NpcGossip[10078]["AfterEvent"]["Text1"] = "It`s good to see lovers being together. Master Hwang and I have to return to the mountain. Wish you everlasting love!"
tValentinesDay2015_Flirt_NpcGossip[10078]["AfterEvent"]["Option1"] = "See~you."

tValentinesDay2015_Flirt_NpcGossip[10078]["AtEvent"] = {}
tValentinesDay2015_Flirt_NpcGossip[10078]["AtEvent"]["Text1"] = "Happy Valentine`s Day! No matter you`re man or woman, take the chance to confess your love. Come and study the True Love Manual with your beloved, and let him/her understand your heart."
tValentinesDay2015_Flirt_NpcGossip[10078]["AtEvent"]["Option1"] = "Gimme~the~manual."
tValentinesDay2015_Flirt_NpcGossip[10078]["AtEvent"]["Option2"] = "I~lost~the~manual."
tValentinesDay2015_Flirt_NpcGossip[10078]["AtEvent"]["Option3"] = "Tell~me~more."
tValentinesDay2015_Flirt_NpcGossip[10078]["AtEvent"]["Option4"] = "Roses~of~Everlasting~for~you."
tValentinesDay2015_Flirt_NpcGossip[10078]["AtEvent"]["Option5"] = "I`ll~talk~to~you~later."

tValentinesDay2015_Flirt_NpcGossip[10078]["IntroduceEvent"] = {}
tValentinesDay2015_Flirt_NpcGossip[10078]["IntroduceEvent"]["Text1"] = "True Love Manual is a martial art book divided into 3 stages: Love Glance, Lingering Sense, and Forever Love. When you train the proficiency to a certain level, your stage will increase. Girls, come"
tValentinesDay2015_Flirt_NpcGossip[10078]["IntroduceEvent"]["Text2"] = "~and claim True Love Manual (B) from me. Boys, go find Master Hwang for True Love Manual (A). The boy and the girl with the manuals can make a team and hunt monsters together to rise the proficiency."
tValentinesDay2015_Flirt_NpcGossip[10078]["IntroduceEvent"]["Option1"] = "What`re~the~stages~for?"
tValentinesDay2015_Flirt_NpcGossip[10078]["IntroduceEvent"]["Option2"] = "Learn~about~other~things."
tValentinesDay2015_Flirt_NpcGossip[10078]["IntroduceEvent"]["Option3"] = "Got~it."

tValentinesDay2015_Flirt_NpcGossip[10078]["IntroduceReward"] = {}
tValentinesDay2015_Flirt_NpcGossip[10078]["IntroduceReward"]["Text1"] = "For rewards. When you kill a monster, you`ll earn 1 proficiency point. 10 points to reach Love Glance stage, and get 20-minute EXP; 60 points for Lingering Sense, and get 40-minute EXP;"
tValentinesDay2015_Flirt_NpcGossip[10078]["IntroduceReward"]["Text2"] = "~and 160 points for Forever Love, and get a Festival Joy Pack. You can also train it alone, but you`ll miss some EXP reward."
tValentinesDay2015_Flirt_NpcGossip[10078]["IntroduceReward"]["Option1"] = "Learn~about~other~things."
tValentinesDay2015_Flirt_NpcGossip[10078]["IntroduceReward"]["Option2"] = "I~see."

tValentinesDay2015_Flirt_NpcGossip[10078]["GiveLongStemRose"] = {}
tValentinesDay2015_Flirt_NpcGossip[10078]["GiveLongStemRose"]["Text1"] = "Rose? Is it from Master Hwang? Alright. I really hope he could be a little more romantic sometimes."
tValentinesDay2015_Flirt_NpcGossip[10078]["GiveLongStemRose"]["Option1"] = "He~will~understand."

tValentinesDay2015_Flirt_NpcGossip[10078]["SysMsg"] = {}
tValentinesDay2015_Flirt_NpcGossip[10078]["SysMsg"]["WrongSex"] = "Sorry, you got the wrong person. Master Hwang has True Love Manual (A) for boys."
tValentinesDay2015_Flirt_NpcGossip[10078]["SysMsg"]["ItemGet"] = "You`ve got True Love Manual (B). I suggest you to team up with a boy who has True Love Manual (A), and study the manual by hunting monsters together."

--药师师兄
tValentinesDay2015_Flirt_NpcGossip[10079] = {}
tValentinesDay2015_Flirt_NpcGossip[10079]["BeforeEvent"] = {}
tValentinesDay2015_Flirt_NpcGossip[10079]["BeforeEvent"]["Text1"] = "Valentine`s Day is coming, and my lady, Autumn, wants to celebrate it in Twin City. From Feb. 11th to 14th, we`ll also share the `True Love Manual` with heroes above Level 80 or reborn."
tValentinesDay2015_Flirt_NpcGossip[10079]["BeforeEvent"]["Option1"] = "I~can`t~wait~to~see~it."

tValentinesDay2015_Flirt_NpcGossip[10079]["AfterEvent"] = {}
tValentinesDay2015_Flirt_NpcGossip[10079]["AfterEvent"]["Text1"] = "I don`t care what others think. I just want Autumn to be happy. Time to say goodbye."
tValentinesDay2015_Flirt_NpcGossip[10079]["AfterEvent"]["Option1"] = "Good~bye."

tValentinesDay2015_Flirt_NpcGossip[10079]["AtEvent"] = {}
tValentinesDay2015_Flirt_NpcGossip[10079]["AtEvent"]["Text1"] = "Happy Valentine`s Day! It`s really a good chance to confess your love, isn`t it? Come and study the True Love Manual with your beloved. I bet your love will be eternal after that."
tValentinesDay2015_Flirt_NpcGossip[10079]["AtEvent"]["Option1"] = "Gimme~the~manual."
tValentinesDay2015_Flirt_NpcGossip[10079]["AtEvent"]["Option2"] = "I~lost~the~manual."
tValentinesDay2015_Flirt_NpcGossip[10079]["AtEvent"]["Option3"] = "Tell~me~more."
tValentinesDay2015_Flirt_NpcGossip[10079]["AtEvent"]["Option4"] = "Roses~of~Everlasting~for~you."
tValentinesDay2015_Flirt_NpcGossip[10079]["AtEvent"]["Option5"] = "I`ll~talk~to~you~later."

tValentinesDay2015_Flirt_NpcGossip[10079]["IntroduceEvent"] = {}
tValentinesDay2015_Flirt_NpcGossip[10079]["IntroduceEvent"]["Text1"] = "Actually, the True Love Manual is a martial art book in 3 stages: Love Glance, Lingering Sense, and Forever Love. When you train the proficiency to a certain level, your stage will increase. I have"
tValentinesDay2015_Flirt_NpcGossip[10079]["IntroduceEvent"]["Text2"] = "~True Love Manual (A) for boys, while Lady Autumn has True Love Manual (B) for girls. The boy and the girl with the manuals can make a team and hunt monsters together to rise the proficiency."
tValentinesDay2015_Flirt_NpcGossip[10079]["IntroduceEvent"]["Option1"] = "What`re~the~stages~for?"
tValentinesDay2015_Flirt_NpcGossip[10079]["IntroduceEvent"]["Option2"] = "Learn~about~other~things."
tValentinesDay2015_Flirt_NpcGossip[10079]["IntroduceEvent"]["Option3"] = "Got~it."

tValentinesDay2015_Flirt_NpcGossip[10079]["IntroduceReward"] = {}
tValentinesDay2015_Flirt_NpcGossip[10079]["IntroduceReward"]["Text1"] = "For rewards. Killing each monster will earn yourself 1 proficiency point. 10 points to reach Love Glance stage, and get 20-minute EXP; 60 points for Lingering Sense, and get 40-minute EXP;"
tValentinesDay2015_Flirt_NpcGossip[10079]["IntroduceReward"]["Text2"] = "~and 160 points for Forever Love, and get a Festival Joy Pack. You can also train it alone, but you`ll miss some EXP reward."
tValentinesDay2015_Flirt_NpcGossip[10079]["IntroduceReward"]["Option1"] = "Learn~about~other~things."
tValentinesDay2015_Flirt_NpcGossip[10079]["IntroduceReward"]["Option2"] = "I~see."

tValentinesDay2015_Flirt_NpcGossip[10079]["GiveLongStemRose"] = {}
tValentinesDay2015_Flirt_NpcGossip[10079]["GiveLongStemRose"]["Text1"] = "What? Rose? Oh, no! Lady Autumn must have seen it, and she would misunderstand. Autumn? Come on, I can explain!"
tValentinesDay2015_Flirt_NpcGossip[10079]["GiveLongStemRose"]["Option1"] = "Sorry..."

tValentinesDay2015_Flirt_NpcGossip[10079]["SysMsg"] = {}
tValentinesDay2015_Flirt_NpcGossip[10079]["SysMsg"]["WrongSex"] = "Sorry, you got the wrong person. Master Hwang has True Love Manual (B) for girls."
tValentinesDay2015_Flirt_NpcGossip[10079]["SysMsg"]["ItemGet"] = "You`ve got True Love Manual (A). I suggest you to team up with a girl who has True Love Manual (B), and study the manual by hunting monsters together."

--心法
tValentinesDay2015_Flirt_ItemDialog = {}

tValentinesDay2015_Flirt_ItemDialog[1] = {}
tValentinesDay2015_Flirt_ItemDialog[1]["Text"] = "You`ve trained the proficiency of True Love Manual to %d point(s). You need to get 10 points to reach Love Glance stage."
tValentinesDay2015_Flirt_ItemDialog[1]["Option1"] = "I~see."

tValentinesDay2015_Flirt_ItemDialog[2] = {}
tValentinesDay2015_Flirt_ItemDialog[2]["Text"] = "You`ve trained the proficiency of True Love Manual to %d point(s). You need to get 60 points to reach Lingering Sense stage."
tValentinesDay2015_Flirt_ItemDialog[2]["Option1"] = "I~see."

tValentinesDay2015_Flirt_ItemDialog[3] = {}
tValentinesDay2015_Flirt_ItemDialog[3]["Text"] = "You`ve trained the proficiency of True Love Manual to %d point(s). You need to get 160 points to reach Forever Love stage."
tValentinesDay2015_Flirt_ItemDialog[3]["Option1"] = "I~see."

tValentinesDay2015_Flirt_ItemDialog[4] = {}
tValentinesDay2015_Flirt_ItemDialog[4]["Text"] = "You`ve acquired the essence of True Love. You can claim a reward, now."
tValentinesDay2015_Flirt_ItemDialog[4]["Option1"] = "Claim~my~reward."
tValentinesDay2015_Flirt_ItemDialog[4]["Option2"] = "I~see."

--系统提示内容
tValentinesDay2015_Flirt_SysMsgContent = {}
tValentinesDay2015_Flirt_SysMsgContent["ItemNotFoundMal"] = "You`ve discarded True Love Manual (A). If you want to continue the study, go claim another piece from Master Hwang (TwinCity 287,359)."
tValentinesDay2015_Flirt_SysMsgContent["ItemNotFoundFem"] = "You`ve discarded True Love Manual (B). If you want to continue the study, go claim another piece from Lady Autumn (TwinCity 284,359)."
tValentinesDay2015_Flirt_SysMsgContent["TaskComplete"] = "You`ve trained the True Love Manual to Forever Love stage. Go and claim your reward."
tValentinesDay2015_Flirt_SysMsgContent["ItemExpired"] = "Valentine`s Day has passed, and the magic of the True Love Manual has vanished."
tValentinesDay2015_Flirt_SysMsgContent["WrongTeam"] = "You can`t study True Love Manual in current team.  Group training of True Love Manual should be a team of a boy and a girl."
tValentinesDay2015_Flirt_SysMsgContent["TaskFinished"] = "You seem quite happy. You must have trained the True Love Manual to Forever Love stage."
tValentinesDay2015_Flirt_SysMsgContent["BagFullItem"] = "Your inventory is full. You need to make some room, first."
tValentinesDay2015_Flirt_SysMsgContent["BagFullReward"] = "Your inventory is full. You need to make some room for the reward, first."
tValentinesDay2015_Flirt_SysMsgContent["ItemExist"] = "You`ve already claimed a True Love Manual. Go and study it with your beloved who also has a True Love Manual."
tValentinesDay2015_Flirt_SysMsgContent["LevelNotEnough"] = "You`re still too green to understand the meaning of True Love Manual. You should reach at least Level 80, first."
tValentinesDay2015_Flirt_SysMsgContent["RewardGet"] = "Congrats! You and your partner have trained the True Love Manual to Forever Love stage, and received a Festival Joy Pack and a Love Rose."

--奖励表
tValentinesDay2015_Flirt_Reward = {}
tValentinesDay2015_Flirt_Reward[1] = {}
tValentinesDay2015_Flirt_Reward[1]["SysMsg1"] = "You and your partner have trained the True Love Manual to Love Glance stage, and received 20 minutes of EXP!"
tValentinesDay2015_Flirt_Reward[1]["SysMsg2"] = "You and your partner have trained the True Love Manual to Love Glance stage, and received 10 Study Points!"
tValentinesDay2015_Flirt_Reward[2] = {}
tValentinesDay2015_Flirt_Reward[2]["SysMsg1"] = "You and your partner have trained the True Love Manual to Lingering Sense stage, and received 40 minutes of EXP!"
tValentinesDay2015_Flirt_Reward[2]["SysMsg2"] = "You and your partner have trained the True Love Manual to Lingering Sense stage, and received 20 Study Points!"

------------------------------------------------------------------------------------
--Name:			[征服][节日任务]2015年情人节之甜蜜约会之非诚勿扰（2.11-2.14）
--Creator: 		魏贻逵
--Created:		2014/12/03
------------------------------------------------------------------------------------

--提示
tValentinesDay2015_feichengwulao_Text = {}
tValentinesDay2015_feichengwulao_Text["MsgBox"] = {}
tValentinesDay2015_feichengwulao_Text["MsgBox"]["chgmap"] = "You entered Matchmaker Yiu`s office, and got impressed by the luxury decoration."
tValentinesDay2015_feichengwulao_Text["MsgBox"]["chgmap1"] = "Thanks for your help! Don`t forget to claim your reward from my boss."
tValentinesDay2015_feichengwulao_Text["MsgBox"]["Complete"] = "You`ve already successfully brought the two persons together. Go and make another match."
tValentinesDay2015_feichengwulao_Text["MsgBox"]["Complete1"] = "You`ve successfully made 3 matches. Go and claim a reward from Matchmaker Yiu."
tValentinesDay2015_feichengwulao_Text["MsgBox"]["clear"] = "It`s late. You were teleported out."


--对白
tValentinesDay2015_feichengwulao_Text[17321] = {}
tValentinesDay2015_feichengwulao_Text[17321]["Text111"] = "It`s hard to be a good matchmaker, and even harder to be a good male matchmaker."
tValentinesDay2015_feichengwulao_Text[17321]["Text112"] = "~To make perfect matches, I`ve racked my brains. Hey, are you free on Feb. 11th - 14th?"
tValentinesDay2015_feichengwulao_Text[17321]["Text113"] = "~It`s always busy on Valentine`s Day, and I`ll need your help."
tValentinesDay2015_feichengwulao_Text[17321]["Option1"] = "Sounds~funny."

tValentinesDay2015_feichengwulao_Text[17321]["Text121"] = "Thanks for your help! I`ve successfully brought many couples together on Valentine`s Day,"
tValentinesDay2015_feichengwulao_Text[17321]["Text122"] = "~and I felt so good."
tValentinesDay2015_feichengwulao_Text[17321]["Option2"] = "You`re~a~good~matchmaker."

tValentinesDay2015_feichengwulao_Text[17321]["Text131"] = "Did you see my assistant, Fat? Come on! If nobody helps me, I`ll die. There are so many single"
tValentinesDay2015_feichengwulao_Text[17321]["Text132"] = "~men and women waiting for a match in my office! Have you reached Level 80 or got reborn? If so,"
tValentinesDay2015_feichengwulao_Text[17321]["Text133"] = "~come and give me a hand from Feb. 11th to 14th. I really, really, really need help!"
tValentinesDay2015_feichengwulao_Text[17321]["Text134"] = ""
tValentinesDay2015_feichengwulao_Text[17321]["Option3"] = "I~can~help."
tValentinesDay2015_feichengwulao_Text[17321]["Option4"] = "Claim~my~reward."
tValentinesDay2015_feichengwulao_Text[17321]["Option5"] = "How~to~make~a~match?"
tValentinesDay2015_feichengwulao_Text[17321]["Option6"] = "I`m~also~waiting~for~love."

--tValentinesDay2015_feichengwulao_Text[17321]["Text311"] = "Um... It`s not time for the work, now. Look, I want you to work in my office"
--tValentinesDay2015_feichengwulao_Text[17321]["Text312"] = "~from 19:00 to 23:00, everyday during the celebration. You know, shyness goes when night comes."
--tValentinesDay2015_feichengwulao_Text[17321]["Option7"] = "You`re~right."

tValentinesDay2015_feichengwulao_Text[17321]["Text321"] = "Wait, you haven`t reached Level 80 nor got reborn. Come on, you`re still too green"
tValentinesDay2015_feichengwulao_Text[17321]["Text322"] = "~to deal with such a profound thing. Keep practicing."
tValentinesDay2015_feichengwulao_Text[17321]["Option8"] = "Alright."

tValentinesDay2015_feichengwulao_Text[17321]["Text331"] = "Hey, I knew you. You`ve already helped me, today. I just can`t bother you any more."
tValentinesDay2015_feichengwulao_Text[17321]["Text332"] = "~You should accompany your beloved for a wonderful festival."
tValentinesDay2015_feichengwulao_Text[17321]["Option9"] = "You`re~right."

tValentinesDay2015_feichengwulao_Text[17321]["Text341"] = "Buddy, you`ve helped make some matches today. Thank you very much! You deserve a nice reward."
tValentinesDay2015_feichengwulao_Text[17321]["Text342"] = "~Hey, don`t forget to say love to the people you love."
tValentinesDay2015_feichengwulao_Text[17321]["Option10"] = "Okay."

tValentinesDay2015_feichengwulao_Text[17321]["Text411"] = "Eh? You`ve already claimed the reward, today."
tValentinesDay2015_feichengwulao_Text[17321]["Text412"] = ""
tValentinesDay2015_feichengwulao_Text[17321]["Option11"] = "Sorry,~I~forgot."

tValentinesDay2015_feichengwulao_Text[17321]["Text421"] = "Wait, you haven`t made 3 matches for me in the office. Finish the job first, and you can claim a reward from me."
tValentinesDay2015_feichengwulao_Text[17321]["Option12"] = "I~see."

tValentinesDay2015_feichengwulao_Text[17321]["Text431"] = "Your inventory is full. You need to make some room, first."
tValentinesDay2015_feichengwulao_Text[17321]["Option13"] = "I`ll~do~it~now."

tValentinesDay2015_feichengwulao_Text[17321]["Text441"] = "Ah, you do have a gift for making matches! Thanks for your help. Here`s a reward for you."
tValentinesDay2015_feichengwulao_Text[17321]["Text442"] = ""
tValentinesDay2015_feichengwulao_Text[17321]["Option14"] = "Thanks."

tValentinesDay2015_feichengwulao_Text[17321]["Text511"] = "In my office, you`ll see many lovers-to-be dating. I want you to do something to enhance the"
tValentinesDay2015_feichengwulao_Text[17321]["Text512"] = "~atmosphere of love around them, such as playing Guzheng, turning on the Gramophone, painting"
tValentinesDay2015_feichengwulao_Text[17321]["Text513"] = "~for them on the table, dimming the candle light, taking flowers from the Dried Flower Vase..."
tValentinesDay2015_feichengwulao_Text[17321]["Text514"] = "~If you successfully make 3 matches, you can claim a reward from me."
tValentinesDay2015_feichengwulao_Text[17321]["Option15"] = "It`s~quite~interesting."

tValentinesDay2015_feichengwulao_Text[17322] = {}
tValentinesDay2015_feichengwulao_Text[17322]["Text111"] = "Assistant Fat often gets lazy, leaving me working alone like a dog. The boss is also looking for him."
tValentinesDay2015_feichengwulao_Text[17322]["Text112"] = "~Thanks for your assistance."
tValentinesDay2015_feichengwulao_Text[17322]["Text113"] = ""
tValentinesDay2015_feichengwulao_Text[17322]["Option1"] = "I~want~to~leave~the~office."
tValentinesDay2015_feichengwulao_Text[17322]["Option2"] = "How~to~make~a~match?"
tValentinesDay2015_feichengwulao_Text[17322]["Option3"] = "You`re~welcome."

tValentinesDay2015_feichengwulao_Text[17322]["Text121"] = "It seems you haven`t made 3 matches in the office. Are you sure you want to leave now?"
tValentinesDay2015_feichengwulao_Text[17322]["Option4"] = "Yes,~I`ve~decided."
tValentinesDay2015_feichengwulao_Text[17322]["Option5"] = "No,~not~now."

tValentinesDay2015_feichengwulao_Text[17322]["Text211"] = "As you can see, there are single men and women here. You need to do something to enhance the"
tValentinesDay2015_feichengwulao_Text[17322]["Text212"] = "~atmosphere of love around them, such as playing Guzheng, turning on the Gramophone, painting"
tValentinesDay2015_feichengwulao_Text[17322]["Text213"] = "~for them on the table, dimming the candle light, taking flowers from the Dried Flower Vase..."
tValentinesDay2015_feichengwulao_Text[17322]["Text214"] = "~If you successfully make 3 matches, you can claim a reward from Matchmaker Yiu. Got it?"
tValentinesDay2015_feichengwulao_Text[17322]["Option6"] = "Yeah."

tValentinesDay2015_feichengwulao_Text[17323] = {}
tValentinesDay2015_feichengwulao_Text[17323]["Text111"] = "If there is western music here, we can dance together."
tValentinesDay2015_feichengwulao_Text[17323]["Option1"] = "Got~it!"
tValentinesDay2015_feichengwulao_Text[17323]["Text121"] = "Wow, you`re the best dancer I`ve ever seen."
tValentinesDay2015_feichengwulao_Text[17323]["Option2"] = "Good!~I~made~it!"

tValentinesDay2015_feichengwulao_Text[17324] = {}
tValentinesDay2015_feichengwulao_Text[17324]["Text111"] = "I just happened to learn some western dance. It`ll be nice if we have a chance to dance together."
tValentinesDay2015_feichengwulao_Text[17324]["Option1"] = "Got~it!"
tValentinesDay2015_feichengwulao_Text[17324]["Text121"] = "My lady, you`re a very good dancer. You don`t know how beautiful you are."
tValentinesDay2015_feichengwulao_Text[17324]["Option2"] = "Good!~I~made~it!"

tValentinesDay2015_feichengwulao_Text[17325] = {}
tValentinesDay2015_feichengwulao_Text[17325]["Text111"] = "The moon is beautiful, isn`t it?"
tValentinesDay2015_feichengwulao_Text[17325]["Option1"] = "Boring..."
tValentinesDay2015_feichengwulao_Text[17325]["Text121"] = "I really love the music played with Guzheng. It has beautiful sound and rich meaning."
tValentinesDay2015_feichengwulao_Text[17325]["Option2"] = "Good!~I~made~it!"

tValentinesDay2015_feichengwulao_Text[17326] = {}
tValentinesDay2015_feichengwulao_Text[17326]["Text111"] = "What a beautiful night!"
tValentinesDay2015_feichengwulao_Text[17326]["Option1"] = "Got~it!"
tValentinesDay2015_feichengwulao_Text[17326]["Text121"] = "Ha, I love Guzheng too. See, we share the same hobby."
tValentinesDay2015_feichengwulao_Text[17326]["Option2"] = "Good!~I~made~it!"

tValentinesDay2015_feichengwulao_Text[17327] = {}
tValentinesDay2015_feichengwulao_Text[17327]["Text111"] = "Hey... Why are you staring at me? Come on... I`ll be shy."
tValentinesDay2015_feichengwulao_Text[17327]["Option1"] = "Got~it!"
tValentinesDay2015_feichengwulao_Text[17327]["Text121"] = "We look like a perfect match in the picture, don`t we?"
tValentinesDay2015_feichengwulao_Text[17327]["Option2"] = "Good!~I~made~it!"

tValentinesDay2015_feichengwulao_Text[17328] = {}
tValentinesDay2015_feichengwulao_Text[17328]["Text111"] = "For a pretty girl like you, I wish this moment could be forever."
tValentinesDay2015_feichengwulao_Text[17328]["Option1"] = "Got~it!"
tValentinesDay2015_feichengwulao_Text[17328]["Text121"] = "If we can be together... Yeah, we`ll be together forever."
tValentinesDay2015_feichengwulao_Text[17328]["Option2"] = "Good!~I~made~it!"

tValentinesDay2015_feichengwulao_Text[17329] = {}
tValentinesDay2015_feichengwulao_Text[17329]["Text111"] = "Did you smell the flower? It`s good."
tValentinesDay2015_feichengwulao_Text[17329]["Option1"] = "Boring..."
tValentinesDay2015_feichengwulao_Text[17329]["Text121"] = "Ha, you`re really a dull boy. Why do you take my hand till now..."
tValentinesDay2015_feichengwulao_Text[17329]["Option2"] = "Good!~I~made~it!"

tValentinesDay2015_feichengwulao_Text[17330] = {}
tValentinesDay2015_feichengwulao_Text[17330]["Text111"] = "Eh... Why do you keep your hands behind your backs?"
tValentinesDay2015_feichengwulao_Text[17330]["Option1"] = "Boring..."
tValentinesDay2015_feichengwulao_Text[17330]["Text121"] = "Ha, I finally took your hand, my love."
tValentinesDay2015_feichengwulao_Text[17330]["Option2"] = "Good!~I~made~it!"

tValentinesDay2015_feichengwulao_Text[17331] = {}
tValentinesDay2015_feichengwulao_Text[17331]["Text111"] = "The candle light is too bright, isn`t it?"
tValentinesDay2015_feichengwulao_Text[17331]["Option1"] = "Got~it!"
tValentinesDay2015_feichengwulao_Text[17331]["Text121"] = "The light is just good. You look more beautiful, now."
tValentinesDay2015_feichengwulao_Text[17331]["Option2"] = "Good!~I~made~it!"

tValentinesDay2015_feichengwulao_Text[17332] = {}
tValentinesDay2015_feichengwulao_Text[17332]["Text111"] = "What does Matchmaker Yiu really think? The candle light is so bright that I feel uncomfortable."
tValentinesDay2015_feichengwulao_Text[17332]["Option1"] = "Boring..."
tValentinesDay2015_feichengwulao_Text[17332]["Text121"] = "Now, I feel better with the candle light."
tValentinesDay2015_feichengwulao_Text[17332]["Option2"] = "Good!~I~made~it!"

tValentinesDay2015_feichengwulao_Text[17409] = {}
tValentinesDay2015_feichengwulao_Text[17409]["Text111"] = "It seems the man and the woman want to be together. Hurry and create an opportunity for them to dance together."
tValentinesDay2015_feichengwulao_Text[17409]["Option1"] = "Turn~on~the~Gramophone."
tValentinesDay2015_feichengwulao_Text[17409]["Option2"] = "They~should~not~be~together."
tValentinesDay2015_feichengwulao_Text[17409]["Text121"] = "As the music started, the man and the woman embraced together and danced. You successfully made a match!"
tValentinesDay2015_feichengwulao_Text[17409]["Option3"] = "It`s~so~good."

tValentinesDay2015_feichengwulao_Text[17410] = {}
tValentinesDay2015_feichengwulao_Text[17410]["Text111"] = "The man the woman are so quiet. Hurry and create an opportunity for them to chat."
tValentinesDay2015_feichengwulao_Text[17410]["Option1"] = "Play~Guzheng."
tValentinesDay2015_feichengwulao_Text[17410]["Option2"] = "They~should~not~be~together."
tValentinesDay2015_feichengwulao_Text[17410]["Text121"] = "With the beautiful melody and moonlight, the man the woman found they shared the same hobby and started chatting. You successfully made a match!"
tValentinesDay2015_feichengwulao_Text[17410]["Option3"] = "It`s~so~good."

tValentinesDay2015_feichengwulao_Text[17411] = {}
tValentinesDay2015_feichengwulao_Text[17411]["Text111"] = "The date between the man and the woman goes well. Draw a picture for them to enhance the atmosphere of love."
tValentinesDay2015_feichengwulao_Text[17411]["Option1"] = "Draw~them~a~picture."
tValentinesDay2015_feichengwulao_Text[17411]["Option2"] = "They~should~not~be~together."
tValentinesDay2015_feichengwulao_Text[17411]["Text121"] = "The man and the woman got impressed by the picture you drew for them, and decided to be together. You successfully made a match!"
tValentinesDay2015_feichengwulao_Text[17411]["Option3"] = "It`s~so~good."

tValentinesDay2015_feichengwulao_Text[17412] = {}
tValentinesDay2015_feichengwulao_Text[17412]["Text111"] = "It seems both the man and the woman are willing to be hand in hand. Take some flowers from the vase, and throw them into the air."
tValentinesDay2015_feichengwulao_Text[17412]["Option1"] = "Throw~flowers."
tValentinesDay2015_feichengwulao_Text[17412]["Option2"] = "They~should~not~be~together."
tValentinesDay2015_feichengwulao_Text[17412]["Text121"] = "The man and the woman smelt the flower petals in the air, and uncontrollably took each other`s hand. You successfully made a match!"
tValentinesDay2015_feichengwulao_Text[17412]["Option3"] = "It`s~so~good."

tValentinesDay2015_feichengwulao_Text[17413] = {}
tValentinesDay2015_feichengwulao_Text[17413]["Text111"] = "The bright candle light makes the man and the woman feel shy and anxious."
tValentinesDay2015_feichengwulao_Text[17413]["Option1"] = "Dim~the~candle~light."
tValentinesDay2015_feichengwulao_Text[17413]["Option2"] = "They~should~not~be~together."
tValentinesDay2015_feichengwulao_Text[17413]["Text121"] = "In the dimness of the light, the man kissed the woman. You successfully made a match!"
tValentinesDay2015_feichengwulao_Text[17413]["Option3"] = "It`s~so~good."




------------------------------------------------------------------------------------
--Name:		[征服][活动脚本]春节活动（元宵）之张灯结彩贺元宵（3.1—3.5）
--Purpose:	春节活动（元宵）之张灯结彩贺元宵（3.1—3.5）
--Creator: 	陈浩文
--Created:	2014/12/17
------------------------------------------------------------------------------------
-- 命名前缀
-- FestivalSpring2015_Zhangdengjiecai_
-------------采莲姑娘NPC对白-------------
-- //采莲姑娘
tFestivalSpring2015_Zhangdengjiecai_Text = {}
tFestivalSpring2015_Zhangdengjiecai_Text[10753] = {}

-- 活动前对白
tFestivalSpring2015_Zhangdengjiecai_Text[10753]["Text111"] = "Spring has come, and we`re going to celebrate the Lantern Festival on March 1st to 5th."
tFestivalSpring2015_Zhangdengjiecai_Text[10753]["Text112"] = "~Guess what we are going to do on the festival? If you`ve reached Level 80 or got reborn,"
tFestivalSpring2015_Zhangdengjiecai_Text[10753]["Text113"] = "~come and claim a Wish Lantern from me. Each one who lights up the lantern will receive blessing and a gift from me."

-- 活动中对白
tFestivalSpring2015_Zhangdengjiecai_Text[10753]["Text121"] = "During the Lantern Festival, people will go out at night, and carry paper lanterns. See, I`ve prepared"
tFestivalSpring2015_Zhangdengjiecai_Text[10753]["Text122"] = "~some Wish Lanterns for heroes above Level 80 or reborn. If you`re qualified, you can light the"
tFestivalSpring2015_Zhangdengjiecai_Text[10753]["Text123"] = "~lantern one time in a day, and receive blessing and a gift from me."
tFestivalSpring2015_Zhangdengjiecai_Text[10753]["Text124"] = ""


-- 活动后对白
tFestivalSpring2015_Zhangdengjiecai_Text[10753]["Text131"] = "Happy Lantern Festival! May you a happy life in the New Year!"
tFestivalSpring2015_Zhangdengjiecai_Text[10753]["Text132"] = ""

-- 等级不足
tFestivalSpring2015_Zhangdengjiecai_Text[10753]["Text211"] = "Sorry, only the heroes who`ve reached Level 80 or got reborn are able to light the Wish Lantern."

-- 已完成点灯对白 
tFestivalSpring2015_Zhangdengjiecai_Text[10753]["Text221"] = "You`ve already lighted the lantern, today. If you`re still interested, please come and retry tomorrow."

--选项
tFestivalSpring2015_Zhangdengjiecai_Text[10753]["Option11"] = "Great!"
tFestivalSpring2015_Zhangdengjiecai_Text[10753]["Option12"] = "Light~the~Wish~Lantern."
tFestivalSpring2015_Zhangdengjiecai_Text[10753]["Option13"] = "I`ll~talk~to~you~later."
tFestivalSpring2015_Zhangdengjiecai_Text[10753]["Option14"] = "Thanks!"
tFestivalSpring2015_Zhangdengjiecai_Text[10753]["Option21"] = "Alright."
tFestivalSpring2015_Zhangdengjiecai_Text[10753]["Option22"] = "Alright."
-------------祝福灯笼NPC对白-------------

-- //祝福灯笼
tFestivalSpring2015_Zhangdengjiecai_Text[10754] = {}

-- 未活动中对白
tFestivalSpring2015_Zhangdengjiecai_Text[10754]["Text111"] = "This is a beautiful lantern. Wish you a colorful life in the New Year!"

-- 接受任务对白
tFestivalSpring2015_Zhangdengjiecai_Text[10754]["Text121"] = "This is a beautiful lantern. Wish you a colorful life in the New Year!"

-- 已完成点灯对白 
tFestivalSpring2015_Zhangdengjiecai_Text[10754]["Text131"] = "You`ve already lighted the lantern, today. If you`re still interested, please come and retry tomorrow."

--【点灯。】
tFestivalSpring2015_Zhangdengjiecai_Text[10754]["Text211"] = "Sorry, only the heroes who`ve reached Level 80 or got reborn are able to light the Wish Lantern."
tFestivalSpring2015_Zhangdengjiecai_Text[10754]["Text221"] = "Your inventory is full. You need to make some room, first."
tFestivalSpring2015_Zhangdengjiecai_Text[10754]["Text231"] = "Wish you dream come true! The Wish Lantern blessed you with a Festival Joy Pack and 60 minutes of EXP!"
tFestivalSpring2015_Zhangdengjiecai_Text[10754]["Text241"] = "Wish you a harvest in the New Year! The Wish Lantern blessed you with a Festival Joy Pack and 1 day of Heaven Blessing!"
tFestivalSpring2015_Zhangdengjiecai_Text[10754]["Text251"] = "Wish you a splendid life! The Wish Lantern blessed you with a Festival Joy Pack and 30 Study Points!"
tFestivalSpring2015_Zhangdengjiecai_Text[10754]["Text261"] = "Wish you a happy life! The Wish Lantern blessed you with a Festival Joy Pack and 20 Chi Points!"

--选项
tFestivalSpring2015_Zhangdengjiecai_Text[10754]["Option11"] = "I~see."
tFestivalSpring2015_Zhangdengjiecai_Text[10754]["Option12"] = "Light~the~lantern."
tFestivalSpring2015_Zhangdengjiecai_Text[10754]["Option13"] = "Alright."
tFestivalSpring2015_Zhangdengjiecai_Text[10754]["Option14"] = "I~see."
tFestivalSpring2015_Zhangdengjiecai_Text[10754]["Option21"] = "Okay."
tFestivalSpring2015_Zhangdengjiecai_Text[10754]["Option22"] = "Good!"
----------------特效文字--------------------
--烟花特效文字
tFestivalSpring2015_Zhangdengjiecai_Effect={}
tFestivalSpring2015_Zhangdengjiecai_Effect["Effect"]="Happy~Lantern~Festival!"
------------------------------------------------------------------------------------



------------------------------------------------------------------------------------
--Name:		[简体征服][节日任务]元宵节之横扫八方战元宵
--Purpose:	元宵节之横扫八方战元宵
--Creator: 	严振飞
--Created:	2014/12/09
------------------------------------------------------------------------------------

------------------------------------------NPC对白-------------------------------------------
-- //大将军卫无敌

tFestivalSpring2015_FestivalWar_Text = {}
tFestivalSpring2015_FestivalWar_Text[17432] = {}
-- 活动前对白
tFestivalSpring2015_FestivalWar_Text[17432]["Text111"] = "You must have heard about the Lantern Festival celebration from March 1st to 5th. The more the people,"
tFestivalSpring2015_FestivalWar_Text[17432]["Text112"] = "~the more the danger. I just worry something bad may happen during the celebration. If you`ve reached Level 80"
tFestivalSpring2015_FestivalWar_Text[17432]["Text113"] = "~or got reborn, come and give me a hand at that time."
-- 活动中对白
tFestivalSpring2015_FestivalWar_Text[17432]["Text121"] = "What a busy festival! People are everywhere in the city. What`s worse, the noise has attracted monsters"
tFestivalSpring2015_FestivalWar_Text[17432]["Text122"] = "~all around the land. Look, I`ve dispatched a team to block the monsters in the Evil Field. However, it`s not"
tFestivalSpring2015_FestivalWar_Text[17432]["Text123"] = "~enough. From March 1st to 5th, I need helps from Level 80+ or reborn heroes. I`ll give a nice pay for that."
-- 活动后对白（通用）
tFestivalSpring2015_FestivalWar_Text[17432]["Text131"] = "We finally drove away the monsters. Thanks to everyone who had ever lent me a hand."


-- 【前往妖魔战场。】
tFestivalSpring2015_FestivalWar_Text[17432]["Text211"] = "Come on, you should reach at least Level 80 or get reborn to deal with those monsters. They`re much more fierce than you imagined."
tFestivalSpring2015_FestivalWar_Text[17432]["Text221"] = "Hey, you`ve already given a help in the Evil Field, today. Why not take a rest, and join the fight again tomorrow?"
tFestivalSpring2015_FestivalWar_Text[17432]["Text231"] = "I just found that you`ve successfully defeated the monsters in the Evil Field. You can claim the reward, now."

-- 【返回双龙城。】
tFestivalSpring2015_FestivalWar_Text[17432]["Text311"] = "Are you sure you want to return to Twin City? You haven`t smashed the monsters` attack."
tFestivalSpring2015_FestivalWar_Text[17432]["Text321"] = "Thanks for smashing the monsters` attack! I`ll send you to Twin City, right now."

-- 【兑换皮毛。】
tFestivalSpring2015_FestivalWar_Text[17432]["Text411"] = "Eh? You`ve already claimed today`s reward, haven`t you?"
tFestivalSpring2015_FestivalWar_Text[17432]["Text421"] = "Buddy, you should break down the monsters` attack before you can claim a reward from me."
tFestivalSpring2015_FestivalWar_Text[17432]["Text431"] = "Your inventory is too full to contain anything. You need to make some room, first."
tFestivalSpring2015_FestivalWar_Text[17432]["Text441"] = "You`ve showed your courage to me. Look, I have a Festival Joy Pack for you. Just take it."


-- 【愿闻其详。】
tFestivalSpring2015_FestivalWar_Text[17432]["Text521"] = "If you can help, I`ll send you to the Evil Field one time in a day. Defeat the monsters in the field, and you can"
tFestivalSpring2015_FestivalWar_Text[17432]["Text522"] = "~claim a Festival Joy Pack from me. Listen, those monsters are different. They know how to fight in a formation."
tFestivalSpring2015_FestivalWar_Text[17432]["Text523"] = "~I want you to do what I tell you during the fight. If you did something wrong, you need to start over. "



------------------------------------------大将军卫无敌--选项-------------------------------------------
tFestivalSpring2015_FestivalWar_Text[17432]["Option11"] = "Sure."
tFestivalSpring2015_FestivalWar_Text[17432]["Option12"] = "Enter~the~Evil~Field."
tFestivalSpring2015_FestivalWar_Text[17432]["Option13"] = "Return~to~Twin~City."
tFestivalSpring2015_FestivalWar_Text[17432]["Option14"] = "Claim~my~reward."
tFestivalSpring2015_FestivalWar_Text[17432]["Option15"] = "Tell~me~more."
tFestivalSpring2015_FestivalWar_Text[17432]["Option16"] = "I`ll~talk~to~you~later."
tFestivalSpring2015_FestivalWar_Text[17432]["Option17"] = "Great!"
tFestivalSpring2015_FestivalWar_Text[17432]["Option21"] = "Alright."
tFestivalSpring2015_FestivalWar_Text[17432]["Option22"] = "Yeah."
tFestivalSpring2015_FestivalWar_Text[17432]["Option23"] = "Okay."
tFestivalSpring2015_FestivalWar_Text[17432]["Option31"] = "I~have~to~leave."
tFestivalSpring2015_FestivalWar_Text[17432]["Option32"] = "I~changed~my~mind."
tFestivalSpring2015_FestivalWar_Text[17432]["Option33"] = "See~you."
tFestivalSpring2015_FestivalWar_Text[17432]["Option41"] = "Sorry,~I~forgot."
tFestivalSpring2015_FestivalWar_Text[17432]["Option42"] = "I~see."
tFestivalSpring2015_FestivalWar_Text[17432]["Option43"] = "I`ll~do~it~now."
tFestivalSpring2015_FestivalWar_Text[17432]["Option44"] = "Thanks!"
tFestivalSpring2015_FestivalWar_Text[17432]["Option51"] = "Learn~about~something~else."
tFestivalSpring2015_FestivalWar_Text[17432]["Option52"] = "Got~it."


-------------其他对白
tFestivalSpring2015_FestivalWar_Text["Join"] = "You`ve entered the Evil Field. Get yourself ready for combat!"
tFestivalSpring2015_FestivalWar_Text["Leave"] = "You`ve left the Evil Field, and returned to Twin City."
tFestivalSpring2015_FestivalWar_Text["KillError"] = "Oops! You messed up the fighting pace. Make sure you kill the correct monster in a correct order."
tFestivalSpring2015_FestivalWar_Text["Finish"] = "You`ve destroyed the formation formed by the monsters in the Evil Field. Go and claim a reward from General Wai!"
--怪物提示
tFestivalSpring2015_FestivalWar_Text["Monster"] = {}
tFestivalSpring2015_FestivalWar_Text["Monster"][1] = "Currently, the Flame Leopard is the key of the monster formation. Hurry and kill 1 Flame Leopard!"
tFestivalSpring2015_FestivalWar_Text["Monster"][2] = "Currently, the Jade Snake is the key of the monster formation. Hurry and kill 1 Jade Snake!"
tFestivalSpring2015_FestivalWar_Text["Monster"][3] = "Currently, the Lava Devil is the key of the monster formation. Hurry and kill 1 Lava Devil!"
tFestivalSpring2015_FestivalWar_Text["Monster"][4] = "Currently, the Water Ghost is the key of the monster formation. Hurry and kill 1 Water Ghost!"
tFestivalSpring2015_FestivalWar_Text["Monster"][5] = "Currently, the Infernal Lord is the key of the monster formation. Hurry and kill 1 Infernal Lord!"


------------------------------------------------------------------------------------
--Name:		[简体征服][节日任务]元宵节之热热闹闹舞龙灯
--Purpose:	元宵节之热热闹闹舞龙灯
--Creator: 	严振飞
--Created:	2014/12/09
------------------------------------------------------------------------------------

------------------------------------------NPC对白-------------------------------------------
-- //舞者小丸子

tFestivalSpring2015_DragonLight_Text = {}
tFestivalSpring2015_DragonLight_Text[17436] = {}
-- 活动前对白
tFestivalSpring2015_DragonLight_Text[17436]["Text111"] = "The Lantern Festival will be celebrated from March 1st to 5th. If you`re above Level 80 or reborn,"
tFestivalSpring2015_DragonLight_Text[17436]["Text112"] = "~you should never miss the dragon dance performance on the festival. Come and pray for a harvest!"
-- 活动后对白
tFestivalSpring2015_DragonLight_Text[17436]["Text121"] = "Many people have revealed a talent for the dragon dance. Should I make a dragon dance contest?"
-- 活动中对白
tFestivalSpring2015_DragonLight_Text[17436]["Text131"] = "Happy Lantern Festival! If you`re above Level 80 or reborn and you`re longing for good luck in the New Year,"
tFestivalSpring2015_DragonLight_Text[17436]["Text132"] = "~make a team with your friends and give us a dragon dance! I`m looking forward to your performance"
tFestivalSpring2015_DragonLight_Text[17436]["Text133"] = "~between March 1st and 5th."


-- 【弟兄们来舞龙喽！】
tFestivalSpring2015_DragonLight_Text[17436]["Text211"] = "Make sure you`re in a team, first. The dragon dance requires teamwork, and you can`t do it alone."
tFestivalSpring2015_DragonLight_Text[17436]["Text212"] = "It`s impossible to wield the dragon lantern by yourself alone. It`s quite a big thing."
tFestivalSpring2015_DragonLight_Text[17436]["Text221"] = "Hey, where are your teammates? The dragon dance requires teamwork. Go and team up with your friends!"
tFestivalSpring2015_DragonLight_Text[17436]["Text222"] = ""
tFestivalSpring2015_DragonLight_Text[17436]["Text231"] = "Sorry, you`re not the team leader. If you`re interested in the dragon dance, go and ask your team leader"
tFestivalSpring2015_DragonLight_Text[17436]["Text232"] = "~to sign up for the show."
tFestivalSpring2015_DragonLight_Text[17436]["Text241"] = "I`m afraid you can`t sign up for the dragon lion show. Make sure each one in your team has reached Level 80 or got reborn,"
tFestivalSpring2015_DragonLight_Text[17436]["Text242"] = "~and none of them has joined the event today."
tFestivalSpring2015_DragonLight_Text[17436]["Text243"] = ""
tFestivalSpring2015_DragonLight_Text[17436]["Text251"] = "You`re still too green to wield the dragon lantern. I await your return when you reach Level 80 or get reborn."

-- 【领取奖赏。】
tFestivalSpring2015_DragonLight_Text[17436]["Text311"] = "Sorry, I didn`t see you in the dragon dance show."
tFestivalSpring2015_DragonLight_Text[17436]["Text321"] = "You`ve already claimed the reward today, haven`t you?"
tFestivalSpring2015_DragonLight_Text[17436]["Text331"] = "Buddy, you`re carrying a full bag. Why not make some room in your inventory, first?"
tFestivalSpring2015_DragonLight_Text[17436]["Text341"] = "Wow, you guys really impressed me with such a wonderful dance! You deserve to be rewarded."
tFestivalSpring2015_DragonLight_Text[17436]["Text342"] = ""


-- 【我该怎么舞龙？】
tFestivalSpring2015_DragonLight_Text[17436]["Text411"] = "It`s easy. Just team up with at least one of your friends who`ve reached Level 80 or got reborn."
tFestivalSpring2015_DragonLight_Text[17436]["Text412"] = "~Then, ask the team leader to sign up with me. After the show, each one in the team can claim a reward from me."




------------------------------------------舞者小丸子--选项-------------------------------------------
tFestivalSpring2015_DragonLight_Text[17436]["Option11"] = "Sounds~good."
tFestivalSpring2015_DragonLight_Text[17436]["Option12"] = "Good~idea!"
tFestivalSpring2015_DragonLight_Text[17436]["Option13"] = "Dance!~It`s~my~stage."
tFestivalSpring2015_DragonLight_Text[17436]["Option14"] = "Claim~my~reward."
tFestivalSpring2015_DragonLight_Text[17436]["Option15"] = "How~to~dance?"
tFestivalSpring2015_DragonLight_Text[17436]["Option16"] = "I`m~just~passing~by."
tFestivalSpring2015_DragonLight_Text[17436]["Option21"] = "Okay."
tFestivalSpring2015_DragonLight_Text[17436]["Option22"] = "Okay."
tFestivalSpring2015_DragonLight_Text[17436]["Option23"] = "I~see."
tFestivalSpring2015_DragonLight_Text[17436]["Option24"] = "I~see."
tFestivalSpring2015_DragonLight_Text[17436]["Option25"] = "I`ll~talk~to~you~later."
tFestivalSpring2015_DragonLight_Text[17436]["Option31"] = "Maybe,~I~got~it~wrong."
tFestivalSpring2015_DragonLight_Text[17436]["Option32"] = "Sorry,~I~forgot."
tFestivalSpring2015_DragonLight_Text[17436]["Option33"] = "I`ll~do~it~now."
tFestivalSpring2015_DragonLight_Text[17436]["Option34"] = "Thanks!"
tFestivalSpring2015_DragonLight_Text[17436]["Option41"] = "I~see."
-------------其他对白
tFestivalSpring2015_DragonLight_Text["Finish"] = "The dragon dance is impressive! Go and claim a reward from Dancer Bella!"




------------------------------------------------------------------------------------
--Name:		[简体征服][节日任务]元宵节之砰砰啪啪拆爆竹
--Purpose:	元宵节之砰砰啪啪拆爆竹
--Creator: 	严振飞
--Created:	2014/12/09
------------------------------------------------------------------------------------

------------------------------------------NPC对白-------------------------------------------
-- //爆竹大师张巧手

tFestivalSpring2015_RemoveFireks_Text = {}
tFestivalSpring2015_RemoveFireks_Text[17416] = {}
-- 活动前对白
tFestivalSpring2015_RemoveFireks_Text[17416]["Text111"] = "I got a bad news. The Predator stole a box of firecrackers when it fled away. I know the monster."
tFestivalSpring2015_RemoveFireks_Text[17416]["Text112"] = "~It wouldn`t let things go easily. I`m afraid it`ll come back to revenge during the Lantern Festival"
tFestivalSpring2015_RemoveFireks_Text[17416]["Text113"] = "~celebration from March 1st to 5th. If you`re above Level 80 or reborn, pay me a visit at that time."
-- 活动中对白
tFestivalSpring2015_RemoveFireks_Text[17416]["Text121"] = "Emergency! The Predator stole a box of firecrackers, and threw them everywhere on Wind Plain."
tFestivalSpring2015_RemoveFireks_Text[17416]["Text122"] = "~If you`re above Level 80 or reborn, come and clear these explosives between March 1st and 5th."
tFestivalSpring2015_RemoveFireks_Text[17416]["Text123"] = "~Your help will get paid. By the way, if you happen to collect Predator`s Tooth, give it to me for a gift."
-- 活动后对白（通用）
tFestivalSpring2015_RemoveFireks_Text[17416]["Text131"] = "Thanks for clearing the Risky Firecrackers! We can finally enjoy the festival, now."


-- 【我也来帮忙！】
tFestivalSpring2015_RemoveFireks_Text[17416]["Text211"] = "It`s too dangerous for you to clear the explosives. Keep practicing, and come back when you reach Level 80 or get reborn."
tFestivalSpring2015_RemoveFireks_Text[17416]["Text221"] = "You`ve already cleared 10 Risky Firecrackers for me, today. It`s enough. Don`t push yourself too hard."
tFestivalSpring2015_RemoveFireks_Text[17416]["Text231"] = "Um? The Disassemble Device is just in your inventory. You don`t need to claim another one."
tFestivalSpring2015_RemoveFireks_Text[17416]["Text241"] = "Buddy, your inventory is full! I have a Disassemble Device for you. Please make some room, first."
tFestivalSpring2015_RemoveFireks_Text[17416]["Text251"] = "Master Zhang gave you a Disassemble Device. Go and clear the Risky Firecrackers on Wind Plain."

-- 【领取奖励。】
tFestivalSpring2015_RemoveFireks_Text[17416]["Text311"] = "You look quite familiar. Oh, you helped me clear 10 Risky Firecrackers today. It`s enough. Please take a rest."
tFestivalSpring2015_RemoveFireks_Text[17416]["Text321"] = "Have you cleared 10 Risky Firecrackers? It seems the answer is `NO`. Then, finish your job, first."
tFestivalSpring2015_RemoveFireks_Text[17416]["Text331"] = "Your inventory is full, you know? Please make some room for the reward, first."
tFestivalSpring2015_RemoveFireks_Text[17416]["Text341"] = "Well done! Thanks for your help. See, here is a Festival Joy Pack for you."
tFestivalSpring2015_RemoveFireks_Text[17416]["Text342"] = ""

-- 【兑换牙齿。】
tFestivalSpring2015_RemoveFireks_Text[17416]["Text411"] = "Where is the tooth you mentioned? I can`t find it in your inventory."
tFestivalSpring2015_RemoveFireks_Text[17416]["Text421"] = "Ah, it`s exactly what I want. You can have the reward, now."


-- 【怎么回事？】
tFestivalSpring2015_RemoveFireks_Text[17416]["Text511"] = "I`ve spent days and nights, and finally made this Disassemble Device. Since limited time, the device hasn`t not been improved."
tFestivalSpring2015_RemoveFireks_Text[17416]["Text512"] = "~When you use it to disassemble the Risky Firecrackers, it may carelessly set off the firecracker. Anyway, if you`re able to"
tFestivalSpring2015_RemoveFireks_Text[17416]["Text513"] = "~clear 10 Risky Firecrackers, you can claim a Festival Joy Pack from me."


-- 【怎么回事？】--爆竹拆解器怎么用？
tFestivalSpring2015_RemoveFireks_Text[17416]["Text611"] = "When you locate a Risky Firecracker, turn on the Disassemble Device. It`ll automatically clear the risk, while it may"
tFestivalSpring2015_RemoveFireks_Text[17416]["Text612"] = "~fail sometimes and set off the firecracker. Don`t worry, you`ll just fall into faint for a while if it fails. When"
tFestivalSpring2015_RemoveFireks_Text[17416]["Text613"] = "~you clear 10 Risky Fireworks, report back to me and claim your reward."


-- 【怎么回事？】--怎么找年兽牙齿？
tFestivalSpring2015_RemoveFireks_Text[17416]["Text711"] = "While disassembling the Risky Firework, you may find Predator`s Tooth."
tFestivalSpring2015_RemoveFireks_Text[17416]["Text712"] = "~If so, bring it to me. I`ll give a good price for it."


------------------------------------------爆竹大师张巧手--选项-------------------------------------------
tFestivalSpring2015_RemoveFireks_Text[17416]["Option11"] = "Got~it."
tFestivalSpring2015_RemoveFireks_Text[17416]["Option12"] = "I~can~help."
tFestivalSpring2015_RemoveFireks_Text[17416]["Option13"] = "Claim~my~reward."
tFestivalSpring2015_RemoveFireks_Text[17416]["Option14"] = "I~got~Predator`s~Tooth."
tFestivalSpring2015_RemoveFireks_Text[17416]["Option15"] = "Tell~me~more."
tFestivalSpring2015_RemoveFireks_Text[17416]["Option16"] = "I`m~just~passing~by."
tFestivalSpring2015_RemoveFireks_Text[17416]["Option17"] = "Good."
tFestivalSpring2015_RemoveFireks_Text[17416]["Option21"] = "Alright."
tFestivalSpring2015_RemoveFireks_Text[17416]["Option22"] = "You`re~right."
tFestivalSpring2015_RemoveFireks_Text[17416]["Option23"] = "Okay."
tFestivalSpring2015_RemoveFireks_Text[17416]["Option24"] = "I`ll~do~it~now."
tFestivalSpring2015_RemoveFireks_Text[17416]["Option25"] = "I`m~on~the~way."
tFestivalSpring2015_RemoveFireks_Text[17416]["Option31"] = "Alright."
tFestivalSpring2015_RemoveFireks_Text[17416]["Option32"] = "Alright."
tFestivalSpring2015_RemoveFireks_Text[17416]["Option33"] = "Okay."
tFestivalSpring2015_RemoveFireks_Text[17416]["Option34"] = "Thanks!"
tFestivalSpring2015_RemoveFireks_Text[17416]["Option41"] = "Really?~I~must~lose~it~somewhere."
tFestivalSpring2015_RemoveFireks_Text[17416]["Option42"] = "Thanks!"
tFestivalSpring2015_RemoveFireks_Text[17416]["Option51"] = "How~to~use~the~device."
tFestivalSpring2015_RemoveFireks_Text[17416]["Option52"] = "How~to~collect~Predator`s~Tooth."
tFestivalSpring2015_RemoveFireks_Text[17416]["Option53"] = "Learn~about~something~else."
tFestivalSpring2015_RemoveFireks_Text[17416]["Option54"] = "I~see."
tFestivalSpring2015_RemoveFireks_Text[17416]["Option61"] = "Learn~about~something~else."
tFestivalSpring2015_RemoveFireks_Text[17416]["Option62"] = "I~see."
tFestivalSpring2015_RemoveFireks_Text[17416]["Option71"] = "Learn~about~something~else."
tFestivalSpring2015_RemoveFireks_Text[17416]["Option72"] = "I~see."




----------------------------------------------------------------------------------------
-- //危险的爆竹
tFestivalSpring2015_RemoveFireks_Text[17417] = {}
-- 活动前对白
tFestivalSpring2015_RemoveFireks_Text[17417]["Text111"] = "Someone dropped the firecracker here. It seems dangerous."
-- 活动后对白
tFestivalSpring2015_RemoveFireks_Text[17417]["Text121"] = "The Predator dropped some firecrackers here. Fortunately, a heavy rain made them wet and erased the danger."
-- 活动中对白（无任务）
tFestivalSpring2015_RemoveFireks_Text[17417]["Text131"] = "The Predator dropped some firecrackers here for a revenge. It may explode at any time. Hurry and talk to Master Zhang for a solution."
-- 活动中对白（有任务，已领取奖励）
tFestivalSpring2015_RemoveFireks_Text[17417]["Text141"] = "You`ve cleared enough amount of Risky Firecrackers. Take a rest."
-- 活动中对白（有任务,爆炸）
tFestivalSpring2015_RemoveFireks_Text[17417]["Text151"] = "The Disassemble Device falsely set off the firecracker, and you dropped into a faint. So far, you`ve cleared %s Risky Firecracker(s)."
-- 活动中对白（有任务,出选项）
tFestivalSpring2015_RemoveFireks_Text[17417]["Text161"] = "The Predator dropped some firecrackers here for a revenge. It may explode at any time. Do you want to clear it?"


-- 【尝试拆除。】
tFestivalSpring2015_RemoveFireks_Text[17417]["Text211"] = "There is no Disassemble Device in your inventory. Go claim another one from Master Zhang."
tFestivalSpring2015_RemoveFireks_Text[17417]["Text221"] = "You should get closer to the Risky Firecracker to disassemble it."
tFestivalSpring2015_RemoveFireks_Text[17417]["Text231"] = "Your inventory is full. You need to make some room, first."
tFestivalSpring2015_RemoveFireks_Text[17417]["Text241"] = "The Disassemble Device falsely set off the firecracker, and you dropped into a faint. Till now, you`ve cleared %s Risky Firecracker(s)."
tFestivalSpring2015_RemoveFireks_Text[17417]["Text251"] = "You successfully disassembled the Risky Firecracker. So far, you`ve cleared %s Risky Firecracker(s)."
tFestivalSpring2015_RemoveFireks_Text[17417]["Text261"] = "You successfully disassembled the Risky Firecracker and received Predator`s Tooth. So far, you`ve cleared %s Risky Firecracker(s)."


------------------------------------------危险的爆竹--选项-------------------------------------------
-- //危险的爆竹
tFestivalSpring2015_RemoveFireks_Text[17417]["Option11"] = "Indeed."
tFestivalSpring2015_RemoveFireks_Text[17417]["Option12"] = "Good."
tFestivalSpring2015_RemoveFireks_Text[17417]["Option13"] = "Okay."
tFestivalSpring2015_RemoveFireks_Text[17417]["Option14"] = "Alright."
tFestivalSpring2015_RemoveFireks_Text[17417]["Option15"] = "I~see."
tFestivalSpring2015_RemoveFireks_Text[17417]["Option16"] = "I~want~to~clear~it."
tFestivalSpring2015_RemoveFireks_Text[17417]["Option17"] = "I`m~not~ready,~yet."
tFestivalSpring2015_RemoveFireks_Text[17417]["Option21"] = "Okay."
tFestivalSpring2015_RemoveFireks_Text[17417]["Option22"] = "Okay."
tFestivalSpring2015_RemoveFireks_Text[17417]["Option23"] = "Okay."
tFestivalSpring2015_RemoveFireks_Text[17417]["Option24"] = "Okay."
tFestivalSpring2015_RemoveFireks_Text[17417]["Option25"] = "Okay."
tFestivalSpring2015_RemoveFireks_Text[17417]["Option26"] = "Okay."


-------------其他对白
tFestivalSpring2015_RemoveFireks_Text["Succee"] = "You`ve successfully cleared 10 Risky Fireworks. Hurry and claim your reward from Master Zhang."
tFestivalSpring2015_RemoveFireks_Text["GetGeneralPag"] = "Master Zhang gave you a Festival Joy Pack. Hurry and check it!"
tFestivalSpring2015_RemoveFireks_Text["Item_TimeOut"] = "The Lantern Festival has passed, and the item became useless, so you threw it away."
tFestivalSpring2015_RemoveFireks_Text["Item_MonsterCoat"] = "Master Zhang is looking for the Predator`s Teeth. You can swap it for a gift from Master Zhang."
tFestivalSpring2015_RemoveFireks_Text["AddExp"] = "You received 30 minutes of EXP!"
tFestivalSpring2015_RemoveFireks_Text["AddCultivation"] = "You received 20 Study Points!"
tFestivalSpring2015_RemoveFireks_Text["ExploreText"] = "Disassembling"


------------------------------------------------------------------------------------
--Name:		[简体征服][活动任务]2015年春节活动之元宵
--Purpose:	2015年春节活动之元宵
--Creator: 	丁晨
--Created:	2014/12/15
------------------------------------------------------------------------------------

------------------------------------------NPC对白------------------------------------
-- //元宵福利美眉
-- 活动前
tFestivalSpring2015_LanternFestival_Text = {}
tFestivalSpring2015_LanternFestival_Text[17425] = {}
tFestivalSpring2015_LanternFestival_Text[17425]["Text111"] = "From March 1st to 5th, the Quick Luck event will be held in Twin City. For heroes above Level 80 or reborn,"
tFestivalSpring2015_LanternFestival_Text[17425]["Text112"] = "~you can also claim a Spring Coupon from me during the first 30 minutes of every hour at that time. Shh,"
tFestivalSpring2015_LanternFestival_Text[17425]["Text113"] = "~it`s a secret. The first three heroes who claim the coupon at 12:00, 19:00 and 21:00 will be able to swap"
tFestivalSpring2015_LanternFestival_Text[17425]["Text114"] = "~for a super prize."

--活动后
tFestivalSpring2015_LanternFestival_Text[17425]["Text121"] ="Though I nearly crashed on the busy days, I really enjoyed myself. There were so many people showing interest"
tFestivalSpring2015_LanternFestival_Text[17425]["Text122"] ="~in me. Each of them tried very hard to touch me for the coupons."

--活动中
tFestivalSpring2015_LanternFestival_Text[17425]["Text131"] ="Happy Lantern Festival! The Quick Luck event is heating up from March 1st to 5th! If you`re above Level 80"
tFestivalSpring2015_LanternFestival_Text[17425]["Text132"] ="~or reborn, you can claim a Spring Coupon from me during the first 30 minutes of every hour. Shh,"
tFestivalSpring2015_LanternFestival_Text[17425]["Text133"] ="~it`s a secret. The first three heroes who claim and activate the coupon at 12:00, 19:00 and 21:00 will be able to swap for a super prize."

--活动规则
tFestivalSpring2015_LanternFestival_Text[17425]["Text141"] ="For 12:00, it`s a Dragon Ball (B) for the 1st place, a Super Gem (B) for the 2nd place, and a 3-day Fancy Alpaca (B) for the 3rd place.\n"
tFestivalSpring2015_LanternFestival_Text[17425]["Text142"] ="~For 19:00, it`s a bottle of Oblivion Dew (B) for the 1st place, a +3 Stone (B) for the 2nd place, and a 3-day Rod of Roses Bag (B) for the 3rd place.\n"
tFestivalSpring2015_LanternFestival_Text[17425]["Text143"] ="~For 21:00, it`s 500 Chi Points for the 1st place, 1000 Study Points for the 2nd place, and 3 Small Lottery Tickets (B) for the 3rd place."


tFestivalSpring2015_LanternFestival_Text[17425]["Text151"] ="As long as you`ve reached Level 80 or got reborn, you can claim a Spring Coupon from me, everyday from March 1st to 5th."
tFestivalSpring2015_LanternFestival_Text[17425]["Text152"] ="~But remember, you should within the first 30 minutes of every hour. What`s more, I`ve prepared a super prize for the first three heroes"
tFestivalSpring2015_LanternFestival_Text[17425]["Text153"] ="~who claim and activate the coupon at 12:00, 19:00 and 21:00."


--领取失败
--失败、等级不足
tFestivalSpring2015_LanternFestival_Text[17425]["Text311"] ="Sorry, the Spring Coupons are only for heroes who`ve reached Level 80 or reborn."
--失败、背包满
tFestivalSpring2015_LanternFestival_Text[17425]["Text312"] ="Your inventory is too full to contain anything. You need to make some room, first."
--失败、已领取
tFestivalSpring2015_LanternFestival_Text[17425]["Text313"] ="Hey, you`ve already claimed a Spring Coupon from me, haven`t you? I have no more for you, today."
--失败、时间范围外
tFestivalSpring2015_LanternFestival_Text[17425]["Text314"] ="Sorry, you came at the wrong time. The Spring Coupon is available during the first 30 minutes of every hour."

--选项卡
tFestivalSpring2015_LanternFestival_Text[17425]["Option11"] = "Sounds~wonderful."
tFestivalSpring2015_LanternFestival_Text[17425]["Option12"] = "Yeah,~just~for~the~coupons."
tFestivalSpring2015_LanternFestival_Text[17425]["Option131"] = "Give~me~the~coupon."
tFestivalSpring2015_LanternFestival_Text[17425]["Option132"] = "I`ll~talk~to~you~later."
tFestivalSpring2015_LanternFestival_Text[17425]["Option133"] = "What`s~the~super~prize?"
tFestivalSpring2015_LanternFestival_Text[17425]["Option134"] = "What`re~the~rules?"
tFestivalSpring2015_LanternFestival_Text[17425]["Option135"] = "Learn~about~something~else."
tFestivalSpring2015_LanternFestival_Text[17425]["Option311"] = "Alright."
tFestivalSpring2015_LanternFestival_Text[17425]["Option312"] = "I`ll~come~back~soon."
tFestivalSpring2015_LanternFestival_Text[17425]["Option313"] = "Okay."
tFestivalSpring2015_LanternFestival_Text[17425]["Option314"] = "Okay."


--系统提示seckill

--领取成功
tFestivalSpring2015_LanternFestival_Text["Success"] ="Lady Fancy gave you a Spring Coupon. Hurry and activate it."

tFestivalSpring2015_LanternFestival_Text["Notification"] ="The Quick Luck at %s:00 is about to start in 2 minutes. Hurry and try your luck at Lady Fancy."

tFestivalSpring2015_LanternFestival_Text["Notifier"] ="The 1st place of the Quick Luck event has come out. Congratulations to %s! The prize is %s!"

tFestivalSpring2015_LanternFestival_Text["NotifiBag"] ="Your inventory is full. You need to make some room, first."

tFestivalSpring2015_LanternFestival_Text["FestivalFail"] ="The celebration has ended, and the item became useless, so you threw it away."

tFestivalSpring2015_LanternFestival_Text["AddExp"] ="You received %s minutes of EXP!"

tFestivalSpring2015_LanternFestival_Text["OverFlow"] ="You successfully taken the 1st place of this round`s Quick Luck, and received %s!"

tFestivalSpring2015_LanternFestival_Text["AddCultivation"] = "You received %s Study Points!"

tFestivalSpring2015_LanternFestival_Text["Cultivation"] = "%s Study Points"

tFestivalSpring2015_LanternFestival_Text["Average"] =  "%s Chi Points"

tFestivalSpring2015_LanternFestival_Text["Present"] = "(B)"
tFestivalSpring2015_LanternFestival_Text["PresentClear"] = "The item has disappeared."

tFestivalSpring2015_LanternFestival_Text["RewardBag"] = "Which one do you want to claim?"
tFestivalSpring2015_LanternFestival_Text["ShortReward"] = "1-handed~Rod~of~Roses."
tFestivalSpring2015_LanternFestival_Text["LongReward"] = "2-handed~Rod~of~Roses."
tFestivalSpring2015_LanternFestival_Text["Think"] = "I`ll~think~about~it."
tFestivalSpring2015_LanternFestival_Text["BefPreClear"] = "Clear yesterday`s Spring Coupon."
tFestivalSpring2015_LanternFestival_Text["ImmediatelyUse"] ="Activate the Spring Coupon, now?"
tFestivalSpring2015_LanternFestival_Text["Rose"]= "You received a 3-day weapon accessory, Rod of Roses (B)!"