-- Imperial Realm1 bootstrap for the current 6137-compatible database.
-- Run once from Navicat using the local root connection.
-- Safety: refuses to run if a database named realm1 already exists.

DELIMITER $$

DROP PROCEDURE IF EXISTS cq.bootstrap_imperial_realm1$$
CREATE PROCEDURE cq.bootstrap_imperial_realm1()
BEGIN
    DECLARE finished INT DEFAULT 0;
    DECLARE source_table VARCHAR(64);
    DECLARE existing_schema INT DEFAULT 0;
    DECLARE table_cursor CURSOR FOR
        SELECT TABLE_NAME
          FROM information_schema.TABLES
         WHERE TABLE_SCHEMA = 'cq'
           AND TABLE_TYPE = 'BASE TABLE'
         ORDER BY TABLE_NAME;
    DECLARE CONTINUE HANDLER FOR NOT FOUND SET finished = 1;

    SELECT COUNT(*)
      INTO existing_schema
      FROM information_schema.SCHEMATA
     WHERE SCHEMA_NAME = 'realm1';

    IF existing_schema <> 0 THEN
        SIGNAL SQLSTATE '45000'
            SET MESSAGE_TEXT = 'Safety stop: database realm1 already exists';
    END IF;

    CREATE DATABASE realm1
        DEFAULT CHARACTER SET latin1
        DEFAULT COLLATE latin1_bin;

    OPEN table_cursor;
    copy_tables: LOOP
        FETCH table_cursor INTO source_table;
        IF finished = 1 THEN
            LEAVE copy_tables;
        END IF;

        SET @create_sql = CONCAT(
            'CREATE TABLE `realm1`.`',
            REPLACE(source_table, '`', '``'),
            '` LIKE `cq`.`',
            REPLACE(source_table, '`', '``'),
            '`'
        );
        PREPARE create_statement FROM @create_sql;
        EXECUTE create_statement;
        DEALLOCATE PREPARE create_statement;

        SET @copy_sql = CONCAT(
            'INSERT INTO `realm1`.`',
            REPLACE(source_table, '`', '``'),
            '` SELECT * FROM `cq`.`',
            REPLACE(source_table, '`', '``'),
            '`'
        );
        PREPARE copy_statement FROM @copy_sql;
        EXECUTE copy_statement;
        DEALLOCATE PREPARE copy_statement;
    END LOOP;
    CLOSE table_cursor;
END$$

DELIMITER ;

CALL cq.bootstrap_imperial_realm1();
DROP PROCEDURE cq.bootstrap_imperial_realm1;

GRANT ALL PRIVILEGES ON `realm1`.* TO `cquser`@`127.0.0.1`;
FLUSH PRIVILEGES;

SELECT
    (SELECT COUNT(*)
       FROM information_schema.TABLES
      WHERE TABLE_SCHEMA = 'cq'
        AND TABLE_TYPE = 'BASE TABLE') AS cq_tables,
    (SELECT COUNT(*)
       FROM information_schema.TABLES
      WHERE TABLE_SCHEMA = 'realm1'
        AND TABLE_TYPE = 'BASE TABLE') AS realm1_tables;

SELECT id, server_name, cross_server, map_id, pos_x, pos_y, npc_id, attribute
  FROM realm1.cq_client_config
 WHERE server_name IN ('SnowWhite', 'Realm1')
 ORDER BY id;
