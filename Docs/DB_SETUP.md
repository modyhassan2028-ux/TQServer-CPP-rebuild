# إعداد قاعدة البيانات — DB Setup (2026-10-24)

> **مهم:** الداتابيز الأصلية (cq.sql الأصلي من الديمو) **ناقصة** صف
> `cq_config type=149883` (أوقات حرب السلب). بدون الصف ده
> CQCrossServer الأصلي نفسه بيرفض الإقلاع في Init
> (`LoadPlunderTimeConfig` @ FUN_1400165d0: لو SELECT رجع صفر صفوف أو
> data1/100 خارج [2,22] → لوج "data1 must be >1 and <23" + فشل).

## النسخة الكاملة الجاهزة (موصى بها)
`sql/original_full/cq_with_plunder_war.sql.gz` — الدمب الكامل
الأصلي (267 جدول) + صف 149883 مضاف ومتحمّل ومختبر
(296 صف في cq_config، السطر الجديد id=296):
```bash
gunzip -c sql/original_full/cq_with_plunder_war.sql.gz | mysql -u root
# ثم: CREATE DATABASE cq; USE cq; ... أو الدمب ينشئ الجداول مباشرة على القاعدة المحددة
```

## الترقيع على قاعدة موجودة
```bash
mysql -u root cq < sql/patches/cq_config_plunder_war_149883.sql
```

## قيم الصف (حرفية من الديكمبايل)
| العمود | القيمة | المعنى |
|---|---|---|
| type | 149883 | مفتاح LoadPlunderTimeConfig |
| data1 | 1900 | HHMM إغلاق التسجيل (19:00) |
| data2 | 2000 | HHMM بداية الحرب (20:00) |
| data3 | 2100 | HHMM نهاية الحرب (21:00) |
| data4/data5 | 0 | غير مستخدمين في FUN_1400165d0 |
