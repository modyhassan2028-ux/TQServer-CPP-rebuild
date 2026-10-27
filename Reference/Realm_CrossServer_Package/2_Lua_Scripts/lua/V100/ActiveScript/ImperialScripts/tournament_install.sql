-- Imperial Tournament Core: production arenas and NPCs.
-- Last Man Standing is the only remaining tournament.
-- Run this while MsgServer is stopped so its in-memory map/NPC tables cannot
-- retain deleted tournament objects.

-- Uses the currently selected database; no hard-coded schema name is required.
DELETE FROM cq_map WHERE id BETWEEN 9100 AND 9111;

INSERT INTO cq_map
    (id, name, describe_text, mapdoc, type, owner_id, mapgroup, idxserver,
     weather, bgmusic, bgmusic_show, portal0_x, portal0_y, reborn_map,
     reborn_portal, res_lev, owner_type, link_map, link_x, link_y,
     del_flag, color)
SELECT 9100, 'ImpLMS', 'Imperial Last Man Standing', mapdoc, 51539869703,
       0, 0, -1, weather, bgmusic, bgmusic_show, 50, 50, 1002,
       0, res_lev, 0, 0, 0, 0, 0, color
FROM cq_map WHERE id=1005;

DELETE FROM cq_npc WHERE id = 10088 OR id BETWEEN 191000 AND 191011;

INSERT INTO cq_npc
    (id, ownerid, playerid, name, type, lookface, idxserver, mapid,
     cellx, celly, task0, task1, task2, task3, task4, task5, task6, task7,
     data0, data1, data2, data3, datastr, linkid, life, maxlife, base, sort)
VALUES
    (191000,0,0,'LMS Manager',    2,310,-1,1002,326,258,94418000,0,0,0,0,0,0,0,0,0,0,0,'None',0,0,0,0,0);
