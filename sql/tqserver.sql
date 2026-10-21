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
  account_id INT UNSIGNED NOT NULL,
  name VARCHAR(32) UNIQUE NOT NULL,
  level INT DEFAULT 1,
  money BIGINT DEFAULT 0,
  cp BIGINT DEFAULT 0,
  pk_points INT DEFAULT 0,
  recordmap_id INT DEFAULT 1002,
  recordx INT DEFAULT 315,
  recordy INT DEFAULT 275,
  updated_date DATETIME DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP
);
CREATE USER IF NOT EXISTS 'tqserver'@'localhost' IDENTIFIED BY 'tqpass123';
GRANT ALL ON tqserver.* TO 'tqserver'@'localhost';
FLUSH PRIVILEGES;
