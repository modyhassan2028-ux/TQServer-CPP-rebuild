# دمج بكج الريلم (Realm / Kingdom War — Cross-Server)

> المصدر: رابط MEGA من المالك. فك التشفير: AES-128-CTR
> حيث المفتاح = XOR نصفي الـ 32 بايت في الـ fragment،
> والـ nonce = kb[16:24] — صيغة مفاتيح MEGA v2. الناتج
> أرشيف RAR4 سليم → 495 ملفًا / 55MB.

## ما هو البكج
نظام الريلم الكامل (الخريطة 3935 `newborder01_new`) لنسخة
**6173**: سيرفر + قاعدة بيانات + لوا + باتش كلينت، مع أمثلة
إعداد Cross-Server (`config.ini`/`shell.ini` لربط سيرفرين).

## المحتويات (Reference/Realm_CrossServer_Package/)
- `1_Database_SQL/`: خريطة الريلم في cq_map، 33 نوع وحش +
  105 سبون، 26 NPC، 17 كوست، 23 أيتيم، 85 cq_action، وملف
  اختياري لإنشاء قاعدة realm1 منفصلة من cq.
- `2_Lua_Scripts/`: فولدر lua كامل + نسخة "الملفات المتغيرة
  فقط" (V100: TaskScript/ActiveScript/BasicData/TempLogic).
- `3_Server_Maps_and_INI/`: GameMap.ini، action_Res.ini،
  DMap الخريطة، وأمثلة إعداد الكروس سيرفر.
- `4_Client_Patch/`: DMap + scene + msk + 210 مجسم، وملفات
  INI/ANI جاهزة، ومقاطع دمج يدوي.
- `README_INSTRUCTIONS_AR.md`: تعليمات التركيب الكاملة.

## موقع المشروع منه
مرجع **بيانات** لنظام الريلم. هدفنا بورت السورس إلى
**v6159** والبكج لنسخة 6173 — الفروق بيانات لا بنية،
والجداول/الـ IDs هنا هي المرجع المعتمد عند إعادة بناء
CqCrossServer وCqMsgServer للكروس سيرفر في خريطة الطريق.
أي مطابقة سورس↔بيانات تعتمد على أسماء الجداول والأعمدة
كما هي هنا.
