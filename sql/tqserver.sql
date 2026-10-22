-- TQServer-CPP MySQL schema (compatible with MariaDB / MySQL)
CREATE DATABASE IF NOT EXISTS tqserver;
USE tqserver;
CREATE TABLE IF NOT EXISTS cq_account (
  id INT UNSIGNED AUTO_INCREMENT PRIMARY KEY,
  name VARCHAR(32) UNIQUE NOT NULL,
  password VARCHAR(128) NOT NULL,          -- 'salt$sha256(salt+password)'
  created_date DATETIME DEFAULT CURRENT_TIMESTAMP
);
CREATE TABLE IF NOT EXISTS cq_user (       -- character sync lands in the next sprint
  id INT UNSIGNED AUTO_INCREMENT PRIMARY KEY,
  account_id INT UNSIGNED NOT NULL UNIQUE,
  name VARCHAR(32) UNIQUE NOT NULL,
  level INT DEFAULT 1,
  money BIGINT DEFAULT 0,
  cp BIGINT DEFAULT 0,
  bank BIGINT DEFAULT 0,
  pk_points INT DEFAULT 0,
  experience BIGINT DEFAULT 0,
  stat_points INT DEFAULT 0,
  strength INT DEFAULT 0,
  vitality INT DEFAULT 0,
  reborn_count INT DEFAULT 0,
  last_reward_day VARCHAR(10) NOT NULL DEFAULT '',
  spouse_name VARCHAR(64) NOT NULL DEFAULT '',
  fish_caught INT NOT NULL DEFAULT 0,
  ore_mined INT NOT NULL DEFAULT 0,
  recordmap_id INT DEFAULT 1002,
  recordx INT DEFAULT 315,
  recordy INT DEFAULT 275,
  updated_date DATETIME DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP
);
CREATE USER IF NOT EXISTS 'tqserver'@'localhost' IDENTIFIED BY 'tqpass123';
GRANT ALL ON tqserver.* TO 'tqserver'@'localhost';
FLUSH PRIVILEGES;

-- original 6159 data model (as loaded from MySQL by NpcServer.exe)
-- dialog trees: option rows reference their parent node; npc.action_id = greeting node
CREATE TABLE IF NOT EXISTS cq_action (
  id INT PRIMARY KEY,
  parent_id INT NOT NULL DEFAULT 0,
  id_next INT NOT NULL DEFAULT 0,
  type INT NOT NULL DEFAULT 0,     -- 1=say, 2=accept task, 3=turn-in task, 4=teleport, 0=option
  param VARCHAR(255) NOT NULL DEFAULT '',
  text VARCHAR(255) NOT NULL DEFAULT ''
);
CREATE TABLE IF NOT EXISTS cq_task (
  id INT PRIMARY KEY,
  name VARCHAR(64) NOT NULL,
  npc_id INT NOT NULL,
  monster_type INT NOT NULL DEFAULT 0,
  count INT NOT NULL DEFAULT 1,
  money INT NOT NULL DEFAULT 0,
  cp INT NOT NULL DEFAULT 0,
  min_level INT NOT NULL DEFAULT 1
);
CREATE TABLE IF NOT EXISTS cq_npc (
  id INT PRIMARY KEY,
  name VARCHAR(64) NOT NULL,
  type INT NOT NULL DEFAULT 0,
  map_id INT NOT NULL DEFAULT 1002,
  x INT NOT NULL DEFAULT 0,
  y INT NOT NULL DEFAULT 0,
  lookface INT NOT NULL DEFAULT 0,
  action_id INT NOT NULL DEFAULT 0   -- cq_action greeting node
);

-- monster world (as loaded by NpcServer.exe: "SELECT * FROM cq_monstertype" / "cq_generator")
CREATE TABLE IF NOT EXISTS cq_monstertype (
  id INT PRIMARY KEY,
  name VARCHAR(64) NOT NULL,
  level INT NOT NULL DEFAULT 1,
  life INT NOT NULL DEFAULT 100
);
CREATE TABLE IF NOT EXISTS cq_generator (
  id INT PRIMARY KEY,
  type_id INT NOT NULL,
  map_id INT NOT NULL,
  count INT NOT NULL DEFAULT 1,
  x0 INT NOT NULL DEFAULT 0,
  y0 INT NOT NULL DEFAULT 0,
  x1 INT NOT NULL DEFAULT 0,
  y1 INT NOT NULL DEFAULT 0
);

-- item type library (as loaded by NpcServer: "SELECT * FROM cq_itemtype")
CREATE TABLE IF NOT EXISTS cq_itemtype (
  id INT PRIMARY KEY,
  name VARCHAR(64) NOT NULL,
  sort INT NOT NULL DEFAULT 0,   -- 0=consumable, 1=weapon, 2=armor
  price INT NOT NULL DEFAULT 0
);

-- per-character inventory (original cq_item model; one row per item stack)
CREATE TABLE IF NOT EXISTS cq_item (
  id INT AUTO_INCREMENT PRIMARY KEY,
  account_id INT UNSIGNED NOT NULL,
  item_type INT NOT NULL,
  sort INT NOT NULL DEFAULT 0,
  amount INT NOT NULL DEFAULT 1,
  position INT NOT NULL DEFAULT 255,
  plus INT NOT NULL DEFAULT 0,
  name VARCHAR(64) NOT NULL DEFAULT ''
  durability SMALLINT NOT NULL DEFAULT 1000,
);

-- equipment stat bonuses (original cq_itemaddition model)
CREATE TABLE IF NOT EXISTS cq_itemaddition (
  item_type INT NOT NULL,
  plus INT NOT NULL,              -- bonus granted AT this plus level (totals are cumulative)
  life INT NOT NULL DEFAULT 0,
  attack INT NOT NULL DEFAULT 0,
  PRIMARY KEY (item_type, plus)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

-- monster loot tables (original cq_dropitemrule model)
CREATE TABLE IF NOT EXISTS cq_dropitemrule (
  monster_type INT NOT NULL,
  item_type INT NOT NULL,
  chance INT NOT NULL DEFAULT 100,  -- percent
  PRIMARY KEY (monster_type, item_type)
);

-- offline mail: delivered on the recipient's next login
CREATE TABLE IF NOT EXISTS cq_mail (
  id INT AUTO_INCREMENT PRIMARY KEY,
  to_name VARCHAR(64) NOT NULL,
  from_name VARCHAR(64) NOT NULL,
  body VARCHAR(255) NOT NULL,
  is_read TINYINT NOT NULL DEFAULT 0,
  created_date TIMESTAMP DEFAULT CURRENT_TIMESTAMP
);

-- PvP arena ladder
CREATE TABLE IF NOT EXISTS cq_arena (
  id INT AUTO_INCREMENT PRIMARY KEY,
  name VARCHAR(64) NOT NULL UNIQUE,
  kills INT NOT NULL DEFAULT 0,
  deaths INT NOT NULL DEFAULT 0,
  updated_date TIMESTAMP DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP
);

-- player market: offline item offers, atomic purchase (is_sold 0 -> 1)
CREATE TABLE IF NOT EXISTS cq_market (
  id INT AUTO_INCREMENT PRIMARY KEY,
  seller_name VARCHAR(64) NOT NULL,
  item_type INT NOT NULL,
  item_name VARCHAR(64) NOT NULL,
  sort SMALLINT NOT NULL DEFAULT 255,
  amount INT NOT NULL DEFAULT 1,
  plus TINYINT NOT NULL DEFAULT 0,
  enchant SMALLINT NOT NULL DEFAULT 0,
  price INT NOT NULL,
  is_sold TINYINT NOT NULL DEFAULT 0,
  created_date DATETIME DEFAULT CURRENT_TIMESTAMP,
  INDEX idx_sold (is_sold)
) ENGINE=InnoDB;

-- cross-server realm definitions (server group identity; the game server
-- with SERVER_ID=N in data/cross.ini carries realm N's name on the hub)
CREATE TABLE IF NOT EXISTS cq_realm (
  id INT NOT NULL,
  name VARCHAR(24) NOT NULL,
  description VARCHAR(128) NOT NULL DEFAULT '',
  PRIMARY KEY (id)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

-- cross-realm monsters: spawned by the owning game server; the kill is
-- announced on every game server linked to the cross hub
CREATE TABLE IF NOT EXISTS cq_cross_monster (
  id INT NOT NULL AUTO_INCREMENT,
  type_id INT NOT NULL,               -- cq_monstertype.id
  map_id INT NOT NULL,
  count INT NOT NULL DEFAULT 1,
  x INT NOT NULL,
  y INT NOT NULL,
  respawn_secs INT NOT NULL DEFAULT 60,
  cp_reward INT NOT NULL DEFAULT 25,  -- CP bounty for the killer
  PRIMARY KEY (id)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

-- scheduled server activities (original event model): the activity manager
-- checks this schedule every 30s and drives xp multipliers, boss rushes,
-- drop boosts and peace hours
CREATE TABLE IF NOT EXISTS cq_activity (
  id INT NOT NULL AUTO_INCREMENT,
  name VARCHAR(32) NOT NULL,
  type INT NOT NULL,              -- 1=double xp, 2=boss rush, 3=lucky drops, 4=peace (no pk points)
  days VARCHAR(16) NOT NULL DEFAULT 'daily',  -- 'daily' | 'weekend' | 'weekday'
  start_hour INT NOT NULL,
  end_hour INT NOT NULL,
  param1 INT NOT NULL DEFAULT 1,  -- xp/drop multiplier or boss count
  message VARCHAR(128) NOT NULL DEFAULT '',
  enabled INT NOT NULL DEFAULT 1,
  PRIMARY KEY (id)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;
