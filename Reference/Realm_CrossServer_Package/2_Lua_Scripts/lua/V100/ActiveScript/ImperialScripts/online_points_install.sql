-- Imperial Online Points NPC.
-- The point balance itself is created lazily in cq_statistic (event 9001,
-- data_type 1), so no player-table migration is required.

-- Uses the currently selected database; no hard-coded schema name is required.
INSERT INTO cq_npc
    (id, ownerid, playerid, name, type, lookface, idxserver, mapid,
     cellx, celly, task0, task1, task2, task3, task4, task5, task6, task7,
     data0, data1, data2, data3, datastr, linkid, life, maxlife, base, sort)
VALUES
    (191020,0,0,'Online Points',2,310,-1,1002,317,248,94418000,0,0,0,0,0,0,0,0,0,0,0,'None',0,0,0,0,0)
ON DUPLICATE KEY UPDATE
    name=VALUES(name), type=VALUES(type), lookface=VALUES(lookface),
    idxserver=VALUES(idxserver), mapid=VALUES(mapid), cellx=VALUES(cellx),
    celly=VALUES(celly), task0=VALUES(task0);
