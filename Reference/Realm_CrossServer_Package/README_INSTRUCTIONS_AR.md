# 📦 بكج نظام الريلم الكامل (Realm / Kingdom War - Map 3935) لنسخة 6173

هذا الفولدر يحتوي على **كل شيء يخص الريلم (الخريطة 3935)** جاهز للتركيب 100% (سيرفر + قاعدة بيانات + لوا + باتش كلينت كامل)، مع حل جميع مشاكل اللوا وحساب نقاط البلورات (Crystals) وجميع الكوستات.

---

## 📁 محتويات البكج

### 1️⃣ فولدر `1_Database_SQL` (قاعدة البيانات)
يحتوي على ملفات الـ SQL مقسمة ومنظمة + ملف شامل ينفذ كل شيء بضغطة واحدة:
- **`00_INSTALL_ALL_REALM_IN_ONE.sql`** *(مُوصى به)*: يحتوي على كل شيء مدمج في ملف واحد (الخرائط + الوحوش + السبون + الـ NPCs + الكوستات + الأيتيمات).
- **`01_Realm_Maps_And_ClientConfig.sql`**: يضيف خريطة الريلم `3935` (`newborder01_new`) في `cq_map`، وإعدادات البوابات في `cq_client_config` و `cq_config`.
- **`02_Realm_Monsters_And_Generators.sql`**: يضيف **33 نوع وحش وبلورة وحارس** في `cq_monstertype` + **105 سبون (Generators)** في `cq_generator` داخل خريطة الريلم `3935`.
- **`03_Realm_NPCs_Quests_And_Items.sql`**: يضيف **26 NPC** في `cq_npc`، و **17 مهمة/عداد كوست** في `cq_taskdetail`، و **23 جائزة/صندوق/توكن ريلم** في `cq_itemtype`، و **85 سطر `cq_action`** لتوصيل الشبيحة والبلورات بملفات اللوا.
- **`04_Optional_Create_Realm1_DB_From_CQ.sql`**: (اختياري) لو عايز تشغل الريلم كسيرفر Cross-Server منفصل (`realm1`) بينسخ الجداول المطلوبة تلقائياً من قاعدة `cq`.

> ⚠️ **ملاحظة**: جميع ملفات الـ SQL مكتوبة بنظام `DELETE` للـ IDs الخاصة بالريلم فقط ثم `INSERT`، يعني **آمنة تماماً** ومش هتمسح أي حاجة تخص سيرفرك، وتقدر تشغلها أكثر من مرة بدون أي تعارض (Duplicate Key).

---

### 2️⃣ فولدر `2_Lua_Scripts` (ملفات اللوا كاملة ومُصلحة 100%)
يحتوي على خيارين حسب حالة السيرفر عندك:
1. **`lua/` (الفولدر الكامل الجاهز - مُوصى به)**:
   - يحتوي على `lua.ini` + `cnlua.txt` + فولدر `V100/PublicFunc` كامل + `V100/TempLogic` كامل + `V100/BasicData` كامل + كل ملفات كوستات الريلم في `V100/TaskScript` و `V100/ActiveScript`.
   - **طريقة التركيب**: انسخ فولدر `lua` بالكامل وحطه جنب `MsgServer.exe` و `NPC.exe` (ووافق على الاستبدال).
2. **`Only_Realm_Changed_Files_V100/` (للي عنده فولدر lua معدل ومش عايز يستبدله كله)**:
   - يحتوي فقط على ملفات الريلم + الـ 4 ملفات الأساسية اللي اتضاف فيها دوال الريلم (`FuncPlayer.lua`, `FuncTask.lua`, `FuncGetValue.lua`, `[Imperial][BasicData]RealmText.lua`).
   - وتأكد إن `V100/BasicData/[Imperial][BasicData]RealmText.lua` والملفات المضافة موجودة في `lua/lua.ini` عندك.

---

### 3️⃣ فولدر `3_Server_Maps_and_INI` (خرائط وملفات السيرفر)
- **`ini/GameMap.ini`** و **`ini/action_Res.ini`**: ضعهم داخل فولدر `ini` الخاص بالسيرفر.
- **`map/map/newborder01_new.DMap`** و **`newborder01_new.7z`**: ضعهم داخل `map/map` في السيرفر.
- **`CrossServer_Config_Examples/`**: أمثلة جاهزة لملفات `config.ini` و `shell.ini` لو حبيت تربط سيرفرين ببعض (Cross-Server).

---

### 4️⃣ فولدر `4_Client_Patch` (باتش الكلينت الكامل لمنع اختفاء أي وحش أو بلورة أو خريطة)
عشان مفيش أي حاجة تكون مخفية في الكلينت (سواء الخريطة 3935 أو البلورات `Lookface 916` أو الشبيحة `Lookface 981` أو حراس الريلم `852/853/854` أو المباني أو أيقونات الجوائز):
1. **`1_Direct_Copy_To_Client_Map_And_Assets/`**:
   - انسخ محتوياته مباشرة داخل فولدر الكلينت (`ani`, `data`, `ini`, `map`).
   - يحتوي على خريطة `newborder01_new.DMap`، ملفات المشهد `newborder01_new.scene` و `.msk`، و **210 ملف مجسمات ومباني الريلم الرسمية** (`data/map/mapobj/border/...` و `ani/mapscene-new.ani`).
2. **`2_Ready_Full_Client_INI_And_ANI/`**:
   - يحتوي على ملفات الكلينت الجاهزة بالكامل لنسخة 6173 (`GameMap.dat`, `npc.ini`, `Monster.ini`, `3DObj.ini`, `3DEffect.ini`, `itemtype.dat`, `StrRes.ini`, `ItemMinIcon.Ani`, `MapItemIcon.Ani`).
   - انسخها داخل الكلينت (ولو عندك تعديلات خاصة في الكلينت خذ Backup من ملفاتك أولاً وراجع `3_Manual_Merge_Snippets_If_Custom_Client`).

---

## 🛠️ المشاكل التي تم حلها في هذا البكج (Troubleshooting)

### ✅ المشكلة الأولى: أخطاء `ERROR: Break link file=.../lua/V100/...` أو `attempt to call a nil value` عند فتح السيرفر
- **السبب**: السيرفر كان يبحث عن دوال مساعدة (`Get_SysTempData`, `Sys_SetTempData`, `User_ChkSurplusExp`, `User_TransFormByMagic`, `Task_AddActivityTaskSchedule`, `MapExploration_AddStc`) أو كان يفتقد ملفات `PublicFunc` / `lua.ini`.
- **الحل المدمج في البكج**:
  - تم تعريف جميع هذه الدوال رسمياً في `FuncPlayer.lua` و `FuncTask.lua` و `FuncGetValue.lua`، وكمان تم وضع نسخة احتياطية تلقائية منها داخل `[Imperial][BasicData]RealmText.lua` بحيث تشتغل على أي سورس 6173 بدون أي خطأ `nil value`.

### ✅ المشكلة الثانية: "لما بكسر البلورة في الريلم مش بيحسبلي نقطة"
- **السبب**:
  1. السكربت الأصلي `InterServeTaskCrystal.lua` كان بيشترط `User_IsCross()` (فلو بتجرب الريلم على نفس السيرفر المحلي كان بيخرج فوراً ومش بيحسب حاجة) وكان بيشترط إن المهمة `35006` تكون متسجلة مسبقاً وإلا مبيحسبش نقاط.
  2. البلورات الـ 4 الكبيرة في الخريطة (`DarkCrystal` أرقام `7884, 7971, 7972, 7973`) واخدة نفس شكل البلورة (`Lookface 916`) لكن مربوطة بسكربت `Looting_villages_Monster7884` اللي كان بيدي شنطة بس ومش بيزود نقاط البلورة أو نقاط المهمة.
- **الحل المدمج في البكج**:
  - الآن عند تكسير **أي بلورة في خريطة الريلم 3935** (سواء `BigCrystal 7860` أو `SmallCrystal 7861` أو `DarkCrystal 7884/7971/7972/7973`، وسواء كنت داخل Cross-Server أو على السيرفر العادي):
    1. بيتم تفعيل عداد الكوست تلقائياً لو مش متفعل.
    2. بتاخد نقاط **Magic Ore** (`35006` لكوست `Mine Battle` عند `KingdomMissionEnvoy 17400`).
    3. بتاخد نقاط **Strike Points** (`+50` للبلورة الكبيرة و `+10` للبلورة الصغيرة في كوست `35007`).
    4. بتاخد نقاط **Crystal Bounty** (`+10` للبلورة الكبيرة و `+2` للبلورة الصغيرة في كوست `35028` اللي بتستلم جائزته من الـ 5 بلورات `Crystal NPCs 19121..19125` لما توصل 50 نقطة، ولو ضغطت عليها قبل الـ 50 نقطة هتعرضلك نقاطك الحالية `X/50`).
    5. وكمان بتظهرلك رسالة فورية في الشات بالنقاط اللي اتحسبتلك.
