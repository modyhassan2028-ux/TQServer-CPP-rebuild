import re,sys,glob,json
DEC="/app/co_decomp/Native-Decompiled"
src=open(DEC+"/Flower.dll.decompiled.c",encoding="utf-8",errors="ignore").read()
bodies={}
for m in re.finditer(r"// Function: (\S+) @ ([0-9a-f]+)\n// =+\n\n(.*?)\n\n\n", src, re.S):
    bodies[m.group(2).lower()]=m.group(3)
port=""
for f in glob.glob("modules/**/*.*",recursive=True)+glob.glob("tests/*"):
    port+=open(f,encoding="utf-8",errors="ignore").read()
port=port.lower()
def norm(b):
    b=re.sub(r"FUN_140d[0-9a-f]{4}","CALLEE",b)
    b=re.sub(r"LAB_140d[0-9a-f]{4}","LAB",b)
    b=re.sub(r"@ 140d[0-9a-f]{4}","@A",b)
    b=re.sub(r"0x140d[0-9a-f]{4,5}","ADDR",b)
    b=re.sub(r"&DAT_140d[0-9a-f]{4}","DAT",b)
    b=re.sub(r"&DAT_140da[0-9a-f]{4}","TDAT",b)
    b=re.sub(r"\(undefined[0-9] \*\)","(P*)",b)
    b=re.sub(r"\s+"," ",b).strip()
    return b
left=[a for a in sorted(bodies) if a not in port]
clusters={}
for a in left:
    clusters.setdefault(norm(bodies[a]),[]).append(a)
print("remaining",len(left),"distinct shapes",len(clusters))
thin=[a for a in sorted(bodies) if a not in port and "Treating indirect jump as call" in bodies[a]]
print("thunks",len(thin))
out=[]
for k,v in sorted(clusters.items(),key=lambda kv:-len(kv[1])):
    out.append({"members":v,"len":len(v),"text":bodies[v[0]]})
json.dump(out,open("/tmp/clusters.json","w"),indent=0)
for i,c in enumerate(out):
    print(i,len(c["members"]),c["members"][:6],len(c["text"]))
