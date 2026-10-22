-- Demo cq_action dialog tree for the TaskMaster (NPC 1000005)
-- Mirrors the original 6159 NpcServer data model: option rows hang off their
-- parent node; type 2 = accept task (param = cq_task.id), 3 = turn-in, 4 = teleport (param = "map,x,y")
USE tqserver;
DELETE FROM cq_action WHERE id BETWEEN 5000 AND 5999;
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
DELETE FROM cq_task;
INSERT INTO cq_task VALUES
 (1001, 'RatRumble',   1000005, 0,    5, 500,  2,  1),
 (1002, 'BanditBounty',1000005, 1001, 10, 5000, 25, 20);
-- full v1 NPC world in the original data model
-- type: 0=generic(dialog-driven), 1=healer, 2=warehouse, 3=teleporter
DELETE FROM cq_npc;
INSERT INTO cq_npc (id, name, type, map_id, x, y, lookface, action_id) VALUES
 (1000001, 'Pharmacist',   1, 1002, 310, 265, 8301, 5100),
 (1000002, 'WarehouseMan', 2, 1002, 300, 270, 8302, 0),
 (1000003, 'CityGuard',    3, 1002, 320, 270, 8303, 5200),
 (1000004, 'DesertGuard',  3, 1000, 505, 605, 8304, 5210),
 (1000005, 'TaskMaster',   0, 1002, 315, 260, 8305, 5000),
 (1000006, 'ShopKeeper',   0, 1002, 300, 255, 8306, 5300);

-- Pharmacist dialog tree (v1 keeps its built-in heal; tree adds flavor)
INSERT INTO cq_action VALUES
 (5100, 0,    0, 1, '', 'Welcome! I can restore your health, free of charge.'),
 (5101, 5100, 0, 0, '', 'Heal me, please.'),
 (5102, 5100, 0, 0, '', 'I am fine, thanks.'),
 (5110, 5101, 0, 1, '', 'There you go - healthy as an ox. Come back any time.'),
 (5111, 5102, 0, 1, '', 'Stay safe out there.');

-- gate trees: type 4 = teleport, param = "map,x,y"
INSERT INTO cq_action VALUES
 (5200, 0,    0, 1, '', 'Need a lift? My gates reach every land.'),
 (5201, 5200, 0, 4, '1000,500,600', 'To the Desert'),
 (5202, 5200, 0, 4, '1001,400,400', 'To Ape Mountain'),
 (5203, 5200, 0, 4, '1002,315,275', 'Back to Twin City'),
 (5204, 5200, 0, 0, '', 'Not now.'),
 (5210, 0,    0, 1, '', 'The city gates never close. Where to?'),
 (5211, 5210, 0, 4, '1002,315,275', 'Back to Twin City'),
 (5212, 5210, 0, 0, '', 'Stay in the desert.');

-- monster world mirroring the built-in v1 spawn table
DELETE FROM cq_monstertype;
INSERT INTO cq_monstertype VALUES (1, 'Pheasant', 1, 30), (2, 'RoamingRat', 2, 50),
                                   (10, 'SandMonk', 12, 400), (20, 'Bandit', 15, 500);
DELETE FROM cq_generator;
INSERT INTO cq_generator VALUES (1, 1, 1002, 2, 650, 320, 700, 380),
                                (2, 2, 1002, 2, 560, 400, 620, 450),
                                (3, 10, 1000, 1, 500, 300, 500, 300),
                                (4, 20, 1001, 1, 400, 400, 400, 400);

-- starter-kit item types
DELETE FROM cq_itemtype;
INSERT INTO cq_itemtype VALUES (410011, 'Sword', 1, 1000), (900020, 'Armor', 2, 800),
                                (100020, 'HealingPotion', 0, 50);

-- ShopKeeper tree: type 5 = shop (wares+prices come from cq_itemtype)
INSERT INTO cq_action VALUES
 (5300, 0,    0, 1, '', 'Welcome to my store! Finest goods in Twin City.'),
 (5301, 5300, 0, 5, '', 'Browse wares'),
 (5302, 5300, 0, 0, '', 'Just looking');

-- equipment bonuses: sword adds attack, armor adds life
DELETE FROM cq_itemaddition;
INSERT INTO cq_itemaddition VALUES (410011, 0, 25), (900020, 300, 0);

-- loot: rats carry potions, bandits carry swords
DELETE FROM cq_dropitemrule;
INSERT INTO cq_dropitemrule VALUES
 (2, 100020, 30),   -- RoamingRat: HealingPotion 30%
 (20, 100020, 20),  -- Bandit: HealingPotion 20%
 (20, 410011, 8);   -- Bandit: Sword 8%
