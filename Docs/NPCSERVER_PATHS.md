# NpcServer.exe — the embedded source paths

Extracted from the binary itself: **50** paths, **50** of them scaffolded under `modules/npcserver/src`.

| path |
|---|
| `google/protobuf/io/coded_stream.h` |
| `version/cqserver-78.0.11-1204/comm/i_messageport.h` |
| `version/cqserver-78.0.11-1204/comm/source/messageport.cpp` |
| `version/cqserver-78.0.11-1204/include/basecode/autolink.h` |
| `version/cqserver-78.0.11-1204/include/basecode/autoptr.h` |
| `version/cqserver-78.0.11-1204/include/basecode/gameobjset.h` |
| `version/cqserver-78.0.11-1204/include/basecode/mycom.h` |
| `version/cqserver-78.0.11-1204/include/basecode/t_singlemap.h` |
| `version/cqserver-78.0.11-1204/include/db/gamedata.h` |
| `version/cqserver-78.0.11-1204/include/db/idb.h` |
| `version/cqserver-78.0.11-1204/mapdata/i_mapdata.h` |
| `version/cqserver-78.0.11-1204/mapdata/source/mapdata.cpp` |
| `version/cqserver-78.0.11-1204/npcserver/clientsocket.cpp` |
| `version/cqserver-78.0.11-1204/npcserver/i_shell.h` |
| `version/cqserver-78.0.11-1204/npcserver/kernelthread.cpp` |
| `version/cqserver-78.0.11-1204/npcserver/npckernel/emptynpcgen.cpp` |
| `version/cqserver-78.0.11-1204/npcserver/npckernel/gamemap.cpp` |
| `version/cqserver-78.0.11-1204/npcserver/npckernel/gamemap.h` |
| `version/cqserver-78.0.11-1204/npcserver/npckernel/i_role.h` |
| `version/cqserver-78.0.11-1204/npcserver/npckernel/instance.cpp` |
| `version/cqserver-78.0.11-1204/npcserver/npckernel/instancemgr.cpp` |
| `version/cqserver-78.0.11-1204/npcserver/npckernel/itemtype.cpp` |
| `version/cqserver-78.0.11-1204/npcserver/npckernel/mapmanager.cpp` |
| `version/cqserver-78.0.11-1204/npcserver/npckernel/mapmanager.h` |
| `version/cqserver-78.0.11-1204/npcserver/npckernel/network/msgaction.cpp` |
| `version/cqserver-78.0.11-1204/npcserver/npckernel/network/msgainpcinfo.cpp` |
| `version/cqserver-78.0.11-1204/npcserver/npckernel/network/msginteract.cpp` |
| `version/cqserver-78.0.11-1204/npcserver/npckernel/network/msglogin.cpp` |
| `version/cqserver-78.0.11-1204/npcserver/npckernel/network/msgmagiceffect.cpp` |
| `version/cqserver-78.0.11-1204/npcserver/npckernel/network/msgnpcpath.cpp` |
| `version/cqserver-78.0.11-1204/npcserver/npckernel/network/msgplayer.cpp` |
| `version/cqserver-78.0.11-1204/npcserver/npckernel/network/msgsyncaction.cpp` |
| `version/cqserver-78.0.11-1204/npcserver/npckernel/network/msgtalk.cpp` |
| `version/cqserver-78.0.11-1204/npcserver/npckernel/network/msguserattrib.cpp` |
| `version/cqserver-78.0.11-1204/npcserver/npckernel/network/msgwalk.cpp` |
| `version/cqserver-78.0.11-1204/npcserver/npckernel/network/netmsg.cpp` |
| `version/cqserver-78.0.11-1204/npcserver/npckernel/neuralaistrategy.cpp` |
| `version/cqserver-78.0.11-1204/npcserver/npckernel/npc.cpp` |
| `version/cqserver-78.0.11-1204/npcserver/npckernel/npcgenerator.cpp` |
| `version/cqserver-78.0.11-1204/npcserver/npckernel/npcmanager.cpp` |
| `version/cqserver-78.0.11-1204/npcserver/npckernel/npcpath.cpp` |
| `version/cqserver-78.0.11-1204/npcserver/npckernel/npcpathmanager.cpp` |
| `version/cqserver-78.0.11-1204/npcserver/npckernel/npcpathtask.cpp` |
| `version/cqserver-78.0.11-1204/npcserver/npckernel/npctype.cpp` |
| `version/cqserver-78.0.11-1204/npcserver/npckernel/npcworld.cpp` |
| `version/cqserver-78.0.11-1204/npcserver/npckernel/t_singlemap2.h` |
| `version/cqserver-78.0.11-1204/npcserver/npckernel/user.cpp` |
| `version/cqserver-78.0.11-1204/npcserver/npckernel/usermanager.cpp` |
| `version/cqserver-78.0.11-1204/npcserver/npckernel/usermanager.h` |
| `version/cqserver-78.0.11-1204/npcserver/npcserverdlg.cpp` |

## Layout rule

The paths above are **nestings**, not names: `version/cqserver-78.0.11-1204/npcserver/npckernel/npc.cpp` is the
folder `npc.cpp` inside `npckernel`, inside `npcserver`, inside `cqserver-78.0.11-1204`, inside `version`. No folder
in the tree is named with a slash in it.

GitHub's file browser compresses a chain of single-child folders into one row, so `src/` shows `google/protobuf/io`
and `version/cqserver-78.0.11-...` as if those were names. On disk `modules/npcserver/src` holds exactly three
entries: `google`, `version` and nothing else.

`tools/check_npcserver_paths.py` enforces this: it fails when a listed path has no file, when a folder is not a
prefix of a listed path (invented), or when a single name contains a separator. D221 removed one leftover empty
folder, `src/npckernel`, that the check caught.

## Attribution note (corrected in D167)

The 50 paths above are the ones the image carries, and they are dead data: nothing in `.text`
references any of their addresses. A body therefore cannot be attributed to a file from the binary,
and no placement is claimed. Bodies without evidence stay in `modules/npcserver/unattributed/`,
outside `src/`. A body moves into one of the paths above only when the evidence exists.
