#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
port_progress.py — مقياس تقدم البورت الحرفي لكل ملفات
الديكمبايل مقابل المنقول فعلياً في Exe/*/.
يستخدمه كل الوكلاء لقياس "وصلنا لحد فين" بأرقام.
"""
import re, os, glob, sys

DECOMP_DIR = "/app/co_repo/Native-Decompiled"
REPO = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
PORT_DIRS = glob.glob(os.path.join(REPO, "Exe", "*", "Port")) + \
            [os.path.join(REPO, "Exe", "CQCrossServer"),
             os.path.join(REPO, "Exe", "NpcServer"),
             os.path.join(REPO, "Exe", "MsgServer")]

def count_functions(path):
    n = 0
    with open(path, "r", errors="ignore") as f:
        for line in f:
            if line.startswith("// Function:"):
                n += 1
    return n

def ported_refs():
    """كل عناوين FUN_ المذكورة في كود البورت (الفريدة)."""
    refs = {}
    for d in PORT_DIRS:
        for p in glob.glob(os.path.join(d, "**", "*.cpp"), recursive=True):
            try:
                s = open(p, "r", errors="ignore").read()
            except OSError:
                continue
            for m in re.findall(r"FUN_([0-9a-f]{9,12})", s):
                refs.setdefault(m.lower(), p)
    return refs

def main():
    print("=== حجم الكون المفكوك (الديكمبايل) ===")
    total = 0
    per_file = {}
    for p in sorted(glob.glob(os.path.join(DECOMP_DIR, "*.decompiled.c"))):
        base = os.path.basename(p).replace(".decompiled.c", "")
        n = count_functions(p)
        per_file[base] = n
        total += n
        print(f"  {base:28s} {n:7,d} دالة")
    print(f"  {'المجموع':28s} {total:7,d} دالة")

    refs = ported_refs()
    print(f"\n=== المنقول في الريبو ===")
    print(f"  عناوين FUN_ مرجعة في كود البورت: {len(refs):,d}")

    # نسبة لكل exe رئيسي
    for exe in ("MsgServer.exe", "NpcServer.exe", "CQCrossServer.exe"):
        if exe in per_file:
            done = len(refs)  # تقريبي عبري
            print(f"  {exe}: {per_file[exe]:,} دالة في الديكمبايل، "
                  f"البورت المباشر ~{done:,} عنوان على مستوى الريبو كله")

    print("""
ملاحظة منهجية مهمة: رقم الدوال الكلي يشمل آلاف
دوال CRT/STL المضمّنة (مكتبات مايكروسوفن) اللي
مش محتاجة نقل حرفي لأن عندنا بدائلها القياسية.
الشغل الحرفي بيتتبع بمسارات التنفيذ الفعلية
(main -> init -> accept -> dispatch -> handlers)
والفجوات تتوثق TBD في PORTING_LOG.md لكل ملف.""")

if __name__ == "__main__":
    main()
