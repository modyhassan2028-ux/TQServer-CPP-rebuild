# NpcServer.exe — the embedded source paths

Extracted from the image with `strings`: **56** `__FILE__` paths (the `57`th string is the PDB name, not a source file, and is left out). The tree under `modules/npcserver/src` mirrors these exactly.

| path |
|---|
| `cq/64/develop/protobuf/src/google/protobuf/io/coded_stream.cc` |
| `cq/64/develop/protobuf/src/google/protobuf/io/zero_copy_stream.cc` |
| `cq/64/develop/protobuf/src/google/protobuf/io/zero_copy_stream_impl_lite.cc` |
| `cq/64/develop/protobuf/src/google/protobuf/message_lite.cc` |
| `cq/64/develop/protobuf/src/google/protobuf/stubs/common.cc` |
| `cq/64/develop/protobuf/src/google/protobuf/wire_format_lite.cc` |
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
| `version/cqserver-78.0.11-1204/protobuf/msgwalk.pb.cc` |

## What was wrong before D228

The earlier table held 50 paths and mis-split the protobuf ones: it recorded `google/protobuf/io/coded_stream.h`,
but the image says `cq/64/develop/protobuf/src/google/protobuf/io/coded_stream.cc` — a different folder chain and a
`.cc`, not a `.h`. Five more protobuf translation units (`zero_copy_stream.cc`, `zero_copy_stream_impl_lite.cc`,
`message_lite.cc`, `stubs/common.cc`, `wire_format_lite.cc`) and `version/cqserver-78.0.11-1204/protobuf/msgwalk.pb.cc`
were missing altogether. D228 rebuilt the tree from the strings, so `src/` now holds `cq/` and `version/` with every
prefix of the table below.

## Layout rule

The paths are **nestings**, not names: `version/cqserver-78.0.11-1204/npcserver/npckernel/npc.cpp` is the folder
`npc.cpp` inside `npckernel`, inside `npcserver`, inside `cqserver-78.0.11-1204`, inside `version`. No folder in the
tree is named with a slash in it.

GitHub compresses a chain of single-child folders into one row, so `src/` shows `cq/64/develop/...` and
`version/cqserver-78.0.11-1204/...` as if those were single names. On disk `src` holds exactly two entries: `cq` and
`version`.

`tools/check_npcserver_paths.py` enforces this: it fails when a listed path has no file, when a folder is not a
prefix of a listed path (invented), or when a single name contains a separator.

## Attribution note

The paths are dead data: nothing in `.text` references their addresses, so a body cannot be attributed to a file from
the binary and no placement is claimed. Bodies without evidence stay in `modules/npcserver/unattributed/`, outside
`src/`. A body moves into one of the paths above only when the evidence exists.
