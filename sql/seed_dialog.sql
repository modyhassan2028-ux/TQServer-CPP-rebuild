-- Demo cq_action dialog tree for the TaskMaster (NPC 1000005)
-- Mirrors the original 6159 NpcServer data model: option rows hang off their
-- parent node; type 2 = accept task (param = cq_task.id), 3 = turn-in, 4 = teleport (param = "map,x,y")
USE tqserver;
INSERT INTO cq_action VALUES
 (5000, 0,    0, 1, '', 'Adventurer! The legion has work for hunters.'),
 (5001, 5000, 0, 0, '', 'Tell me about the available hunts'),
 (5002, 5000, 0, 0, '', 'About the TaskMaster'),
 (5003, 5000, 0, 0, '', 'Never mind'),
 (5004, 5000, 0, 3, '', 'I finished my task - pay me!'),
 (5010, 5001, 0, 1, '', 'Two bounties stand today: pick your poison.'),
 (5011, 5010, 0, 2, '1001', 'Accept RatRumble (5 kills, 500 money + 2 CP)'),
 (5012, 5010, 0, 2, '1002', 'Accept BanditBounty (10 bandits, 5000 money + 25 CP)'),
 (5013, 5010, 0, 0, '', 'Back'),
 (5020, 5003, 0, 1, '', 'Come back when your blade is ready.');
INSERT INTO cq_task VALUES
 (1001, 'RatRumble',   1000005, 0,    5, 500,  2,  1),
 (1002, 'BanditBounty',1000005, 1001, 10, 5000, 25, 20);
-- bind the TaskMaster NPC to the tree root
UPDATE cq_npc SET action_id = 5000 WHERE id = 1000005;
INSERT INTO cq_npc (id, name, type, map_id, x, y, lookface, action_id) VALUES
 (1000005, 'TaskMaster', 0, 1002, 315, 260, 8305, 5000)
ON DUPLICATE KEY UPDATE action_id = 5000;

-- monster world mirroring the built-in v1 spawn table
INSERT INTO cq_monstertype VALUES (1, 'Pheasant', 1, 30), (2, 'RoamingRat', 2, 50),
                                   (10, 'SandMonk', 12, 400), (20, 'Bandit', 15, 500);
INSERT INTO cq_generator VALUES (1, 1, 1002, 2, 650, 320, 700, 380),
                                (2, 2, 1002, 2, 560, 400, 620, 450),
                                (3, 10, 1000, 1, 500, 300, 500, 300),
                                (4, 20, 1001, 1, 400, 400, 400, 400);
