DROP TABLE IF EXISTS `accounts`;
accounts`;
CREATE TABLE `accounts`  (
  `id` int(255) NOT NULL AUTO_INCREMENT,
  `name` varchar(255) CHARACTER SET latin1 COLLATE latin1_swedish_ci NULL DEFAULT NULL,
  `password` varchar(255) CHARACTER SET latin1 COLLATE latin1_swedish_ci NULL DEFAULT NULL,
  `email` varchar(255) CHARACTER SET latin1 COLLATE latin1_swedish_ci NULL DEFAULT NULL,
  `enabled` bit(1) NULL DEFAULT b'0',
  `netbar_ip` varchar(255) CHARACTER SET latin1 COLLATE latin1_swedish_ci NULL DEFAULT '127.0.0.1',
  `macaddr` varchar(255) CHARACTER SET latin1 COLLATE latin1_swedish_ci NULL DEFAULT '00:00:00:00:00:00',
  `banned` bit(1) NULL DEFAULT b'0',
  `vip` int(1) NULL DEFAULT 0,
  `online_eu` tinyint(1) NULL DEFAULT 0,
  `online_us` tinyint(1) NULL DEFAULT 0,
  `ip_mask` varchar(255) CHARACTER SET latin1 COLLATE latin1_swedish_ci NULL DEFAULT '255.255.255.255',
  `type` int(255) UNSIGNED NULL DEFAULT 2,
  `point` int(4) UNSIGNED NULL DEFAULT 100000,
  `pointtime` int(4) UNSIGNED NULL DEFAULT 20021231,
  `vip_start` varchar(255) CHARACTER SET latin1 COLLATE latin1_swedish_ci NULL DEFAULT NULL,
  PRIMARY KEY (`id`) USING BTREE,
  UNIQUE INDEX `name`(`name`) USING BTREE
) ENGINE = InnoDB AUTO_INCREMENT = 713 CHARACTER SET = latin1 COLLATE = latin1_swedish_ci ROW_FORMAT = DYNAMIC;

DROP TABLE IF EXISTS `ad_log`;
ad_log`;
CREATE TABLE `ad_log`  (
  `id` int(10) UNSIGNED NOT NULL AUTO_INCREMENT,
  `user_id` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `user_name` varbinary(15) NOT NULL DEFAULT '',
  `time` int(4) NOT NULL DEFAULT 0,
  `addition` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `words` char(100) CHARACTER SET latin1 COLLATE latin1_bin NOT NULL DEFAULT '',
  PRIMARY KEY (`id`) USING BTREE
) ENGINE = MyISAM AUTO_INCREMENT = 3 CHARACTER SET = latin1 COLLATE = latin1_bin ROW_FORMAT = DYNAMIC;

DROP TABLE IF EXISTS `ad_queue`;
ad_queue`;
CREATE TABLE `ad_queue`  (
  `id` int(10) UNSIGNED NOT NULL AUTO_INCREMENT,
  `idnext` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `user_id` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `user_name` varbinary(15) NOT NULL DEFAULT '',
  `addition` smallint(6) UNSIGNED NOT NULL DEFAULT 0,
  `words` char(100) CHARACTER SET latin1 COLLATE latin1_bin NOT NULL DEFAULT '',
  PRIMARY KEY (`id`) USING BTREE
) ENGINE = MyISAM AUTO_INCREMENT = 1 CHARACTER SET = latin1 COLLATE = latin1_bin ROW_FORMAT = DYNAMIC;

DROP TABLE IF EXISTS `cardbalance`;
cardbalance`;
CREATE TABLE `cardbalance`  (
  `countDate` date NOT NULL DEFAULT '0000-00-00',
  `cardlastbalance` int(11) NULL DEFAULT 0,
  `card2lastbalance` int(11) NULL DEFAULT 0,
  `cardin` int(11) NULL DEFAULT 0,
  `card2in` int(11) NULL DEFAULT 0,
  `cardout` int(11) NULL DEFAULT 0,
  `card2out` int(11) NULL DEFAULT 0,
  `cardbalance` int(11) NULL DEFAULT 0,
  `card2balance` int(11) NULL DEFAULT 0,
  PRIMARY KEY (`countDate`) USING BTREE
) ENGINE = MyISAM CHARACTER SET = latin1 COLLATE = latin1_bin ROW_FORMAT = FIXED;

DROP TABLE IF EXISTS `cardlastid`;
cardlastid`;
CREATE TABLE `cardlastid`  (
  `id` int(4) NOT NULL DEFAULT 0,
  `cardnumber` int(4) NULL DEFAULT 0,
  `card2number` int(4) NULL DEFAULT 0,
  PRIMARY KEY (`id`) USING BTREE
) ENGINE = MyISAM CHARACTER SET = latin1 COLLATE = latin1_bin ROW_FORMAT = FIXED;

DROP TABLE IF EXISTS `city`;
city`;
CREATE TABLE `city`  (
  `ID` int(11) NOT NULL AUTO_INCREMENT,
  `Name` char(35) CHARACTER SET latin1 COLLATE latin1_swedish_ci NOT NULL DEFAULT '',
  `CountryCode` char(3) CHARACTER SET latin1 COLLATE latin1_swedish_ci NOT NULL DEFAULT '',
  `District` char(20) CHARACTER SET latin1 COLLATE latin1_swedish_ci NOT NULL DEFAULT '',
  `Population` int(11) NOT NULL DEFAULT 0,
  PRIMARY KEY (`ID`) USING BTREE
) ENGINE = MyISAM AUTO_INCREMENT = 4080 CHARACTER SET = latin1 COLLATE = latin1_swedish_ci ROW_FORMAT = FIXED;

DROP TABLE IF EXISTS `country`;
country`;
CREATE TABLE `country`  (
  `Code` char(3) CHARACTER SET latin1 COLLATE latin1_swedish_ci NOT NULL DEFAULT '',
  `Name` char(52) CHARACTER SET latin1 COLLATE latin1_swedish_ci NOT NULL DEFAULT '',
  `Continent` enum('Asia','Europe','North America','Africa','Oceania','Antarctica','South America') CHARACTER SET latin1 COLLATE latin1_swedish_ci NOT NULL DEFAULT 'Asia',
  `Region` char(26) CHARACTER SET latin1 COLLATE latin1_swedish_ci NOT NULL DEFAULT '',
  `SurfaceArea` float(10, 2) NOT NULL DEFAULT 0.00,
  `IndepYear` smallint(6) NULL DEFAULT NULL,
  `Population` int(11) NOT NULL DEFAULT 0,
  `LifeExpectancy` float(3, 1) NULL DEFAULT NULL,
  `GNP` float(10, 2) NULL DEFAULT NULL,
  `GNPOld` float(10, 2) NULL DEFAULT NULL,
  `LocalName` char(45) CHARACTER SET latin1 COLLATE latin1_swedish_ci NOT NULL DEFAULT '',
  `GovernmentForm` char(45) CHARACTER SET latin1 COLLATE latin1_swedish_ci NOT NULL DEFAULT '',
  `HeadOfState` char(60) CHARACTER SET latin1 COLLATE latin1_swedish_ci NULL DEFAULT NULL,
  `Capital` int(11) NULL DEFAULT NULL,
  `Code2` char(2) CHARACTER SET latin1 COLLATE latin1_swedish_ci NOT NULL DEFAULT '',
  PRIMARY KEY (`Code`) USING BTREE
) ENGINE = MyISAM CHARACTER SET = latin1 COLLATE = latin1_swedish_ci ROW_FORMAT = FIXED;

DROP TABLE IF EXISTS `countrylanguage`;
countrylanguage`;
CREATE TABLE `countrylanguage`  (
  `CountryCode` char(3) CHARACTER SET latin1 COLLATE latin1_swedish_ci NOT NULL DEFAULT '',
  `Language` char(30) CHARACTER SET latin1 COLLATE latin1_swedish_ci NOT NULL DEFAULT '',
  `IsOfficial` enum('T','F') CHARACTER SET latin1 COLLATE latin1_swedish_ci NOT NULL DEFAULT 'F',
  `Percentage` float(4, 1) NOT NULL DEFAULT 0.0,
  PRIMARY KEY (`CountryCode`, `Language`) USING BTREE
) ENGINE = MyISAM CHARACTER SET = latin1 COLLATE = latin1_swedish_ci ROW_FORMAT = FIXED;

DROP TABLE IF EXISTS `cq_achievement`;
cq_achievement`;
CREATE TABLE `cq_achievement`  (
  `userid` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `point` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `achieve1` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `achieve2` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `achieve3` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `achieve4` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `achieve5` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `achieve6` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `achieve7` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `achieve8` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `achieve9` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `achieve10` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `achieve11` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `achieve12` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `achieve13` int(4) UNSIGNED NOT NULL DEFAULT 0,
  PRIMARY KEY (`userid`) USING BTREE
) ENGINE = MyISAM CHARACTER SET = latin1 COLLATE = latin1_bin ROW_FORMAT = FIXED;

DROP TABLE IF EXISTS `cq_achievementtype`;
cq_achievementtype`;
CREATE TABLE `cq_achievementtype`  (
  `id` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `name` varchar(16) CHARACTER SET latin1 COLLATE latin1_bin NOT NULL DEFAULT '',
  `position` smallint(4) UNSIGNED NOT NULL DEFAULT 0,
  `point` tinyint(3) UNSIGNED NOT NULL DEFAULT 0,
  `facebook` tinyint(3) UNSIGNED NOT NULL DEFAULT 0,
  PRIMARY KEY (`id`) USING BTREE,
  UNIQUE INDEX `u_position`(`position`) USING BTREE
) ENGINE = MyISAM CHARACTER SET = latin1 COLLATE = latin1_bin ROW_FORMAT = DYNAMIC;

DROP TABLE IF EXISTS `cq_action`;
cq_action`;
CREATE TABLE `cq_action`  (
  `id` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `id_next` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `id_nextfail` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `type` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `data` int(4) NOT NULL DEFAULT 0,
  `param` varbinary(255) NULL DEFAULT NULL,
  PRIMARY KEY (`id`) USING BTREE
) ENGINE = MyISAM CHARACTER SET = latin1 COLLATE = latin1_bin ROW_FORMAT = DYNAMIC;

DROP TABLE IF EXISTS `cq_action_total`;
cq_action_total`;
CREATE TABLE `cq_action_total`  (
  `id` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `id_next` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `id_nextfail` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `type` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `data` int(4) NOT NULL DEFAULT 0,
  `param` varbinary(255) NULL DEFAULT NULL,
  PRIMARY KEY (`id`) USING BTREE
) ENGINE = MyISAM CHARACTER SET = latin1 COLLATE = latin1_bin ROW_FORMAT = DYNAMIC;

DROP TABLE IF EXISTS `cq_activity_reward_type`;
cq_activity_reward_type`;
CREATE TABLE `cq_activity_reward_type`  (
  `id` int(4) UNSIGNED ZEROFILL NOT NULL AUTO_INCREMENT,
  `metempsychosis` tinyint(1) UNSIGNED ZEROFILL NOT NULL DEFAULT 0,
  `reward_grade` tinyint(1) UNSIGNED ZEROFILL NOT NULL DEFAULT 0,
  `activity_req` smallint(2) UNSIGNED ZEROFILL NOT NULL DEFAULT 00,
  `reward1` int(4) UNSIGNED ZEROFILL NOT NULL DEFAULT 0000,
  `reward1_num` int(4) UNSIGNED ZEROFILL NOT NULL DEFAULT 0000,
  `reward1_mono` tinyint(1) UNSIGNED ZEROFILL NOT NULL DEFAULT 0,
  `reward2` int(4) UNSIGNED ZEROFILL NOT NULL DEFAULT 0000,
  `reward2_num` int(4) UNSIGNED ZEROFILL NOT NULL DEFAULT 0000,
  `reward2_mono` tinyint(1) UNSIGNED ZEROFILL NOT NULL DEFAULT 0,
  `reward3` int(4) UNSIGNED ZEROFILL NOT NULL DEFAULT 0000,
  `reward3_num` int(4) UNSIGNED ZEROFILL NOT NULL DEFAULT 0000,
  `reward3_mono` tinyint(1) UNSIGNED ZEROFILL NOT NULL DEFAULT 0,
  PRIMARY KEY (`id`) USING BTREE
) ENGINE = MyISAM AUTO_INCREMENT = 16 CHARACTER SET = latin1 COLLATE = latin1_bin ROW_FORMAT = FIXED;

DROP TABLE IF EXISTS `cq_activity_task_type`;
cq_activity_task_type`;
CREATE TABLE `cq_activity_task_type`  (
  `id` int(4) UNSIGNED ZEROFILL NOT NULL DEFAULT 0000,
  `open_lev` int(4) UNSIGNED ZEROFILL NOT NULL DEFAULT 0000,
  `close_lev` int(4) UNSIGNED ZEROFILL NOT NULL DEFAULT 0000,
  `type` tinyint(1) UNSIGNED ZEROFILL NOT NULL DEFAULT 0,
  `max_num` tinyint(1) UNSIGNED ZEROFILL NOT NULL DEFAULT 0,
  `activity` tinyint(1) UNSIGNED ZEROFILL NOT NULL DEFAULT 0,
  PRIMARY KEY (`id`) USING BTREE
) ENGINE = MyISAM CHARACTER SET = latin1 COLLATE = latin1_bin ROW_FORMAT = FIXED;

DROP TABLE IF EXISTS `cq_activity_user_task`;
cq_activity_user_task`;
CREATE TABLE `cq_activity_user_task`  (
  `id` int(4) UNSIGNED ZEROFILL NOT NULL AUTO_INCREMENT,
  `user_id` int(4) UNSIGNED ZEROFILL NOT NULL DEFAULT 0000,
  `activity_id` int(4) UNSIGNED ZEROFILL NOT NULL DEFAULT 0000,
  `complete_flag` tinyint(1) UNSIGNED ZEROFILL NOT NULL DEFAULT 0,
  `schedule` tinyint(1) UNSIGNED ZEROFILL NOT NULL DEFAULT 0,
  PRIMARY KEY (`id`) USING BTREE,
  UNIQUE INDEX `user_activity`(`user_id`, `activity_id`) USING BTREE
) ENGINE = MyISAM AUTO_INCREMENT = 583 CHARACTER SET = latin1 COLLATE = latin1_bin ROW_FORMAT = FIXED;

DROP TABLE IF EXISTS `cq_appointment_account`;
cq_appointment_account`;
CREATE TABLE `cq_appointment_account`  (
  `account` varchar(64) CHARACTER SET gbk COLLATE gbk_bin NOT NULL DEFAULT '',
  PRIMARY KEY (`account`) USING BTREE
) ENGINE = MyISAM CHARACTER SET = latin1 COLLATE = latin1_bin ROW_FORMAT = DYNAMIC;

DROP TABLE IF EXISTS `cq_arenic`;
cq_arenic`;
CREATE TABLE `cq_arenic`  (
  `id` int(4) UNSIGNED NOT NULL AUTO_INCREMENT,
  `type` tinyint(3) UNSIGNED NOT NULL DEFAULT 0,
  `date` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `user_id` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `athlete_point` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `cur_honor` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `history_honor` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `day_wins` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `day_loses` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `asyn` smallint(1) UNSIGNED NOT NULL DEFAULT 0,
  PRIMARY KEY (`id`) USING BTREE
) ENGINE = MyISAM AUTO_INCREMENT = 5 CHARACTER SET = latin1 COLLATE = latin1_bin ROW_FORMAT = FIXED;

DROP TABLE IF EXISTS `cq_arenic_bonus`;
cq_arenic_bonus`;
CREATE TABLE `cq_arenic_bonus`  (
  `id` int(10) UNSIGNED NOT NULL AUTO_INCREMENT,
  `type` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `subtype` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `rank` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `user_id` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `date` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `status` int(10) UNSIGNED NOT NULL DEFAULT 1,
  PRIMARY KEY (`id`) USING BTREE
) ENGINE = MyISAM AUTO_INCREMENT = 65 CHARACTER SET = latin1 COLLATE = latin1_bin ROW_FORMAT = FIXED;

DROP TABLE IF EXISTS `cq_arenic_honor`;
cq_arenic_honor`;
CREATE TABLE `cq_arenic_honor`  (
  `id` int(4) UNSIGNED NOT NULL AUTO_INCREMENT,
  `type` tinyint(3) UNSIGNED NOT NULL DEFAULT 0,
  `day_prise` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `month_prise` int(10) UNSIGNED NOT NULL DEFAULT 0,
  PRIMARY KEY (`id`) USING BTREE
) ENGINE = MyISAM AUTO_INCREMENT = 10101 CHARACTER SET = latin1 COLLATE = latin1_bin ROW_FORMAT = FIXED;

DROP TABLE IF EXISTS `cq_ast_prof_inauguration_condition`;
cq_ast_prof_inauguration_condition`;
CREATE TABLE `cq_ast_prof_inauguration_condition`  (
  `id` int(10) UNSIGNED NOT NULL AUTO_INCREMENT,
  `ast_prof_type` tinyint(3) UNSIGNED NOT NULL DEFAULT 0,
  `metempsychosis` tinyint(3) UNSIGNED NULL DEFAULT 0,
  `user_level` tinyint(3) UNSIGNED NULL DEFAULT 0,
  `itemtype1` int(10) UNSIGNED NULL DEFAULT 0,
  `itemtype1_num` int(10) UNSIGNED NULL DEFAULT 0,
  `itemtype2` int(10) UNSIGNED NULL DEFAULT 0,
  `itemtype2_num` int(10) UNSIGNED NULL DEFAULT 0,
  PRIMARY KEY (`id`) USING BTREE
) ENGINE = MyISAM AUTO_INCREMENT = 8 CHARACTER SET = latin1 COLLATE = latin1_bin ROW_FORMAT = FIXED;

DROP TABLE IF EXISTS `cq_ast_prof_level`;
cq_ast_prof_level`;
CREATE TABLE `cq_ast_prof_level`  (
  `id` int(10) UNSIGNED NOT NULL AUTO_INCREMENT,
  `user_id` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `ast_prof` tinyint(3) UNSIGNED NOT NULL DEFAULT 0,
  `level` tinyint(3) UNSIGNED NOT NULL DEFAULT 1,
  PRIMARY KEY (`id`) USING BTREE,
  INDEX `user_id`(`user_id`) USING BTREE
) ENGINE = MyISAM AUTO_INCREMENT = 15 CHARACTER SET = latin1 COLLATE = latin1_bin ROW_FORMAT = FIXED;

DROP TABLE IF EXISTS `cq_ast_prof_level_timeout`;
cq_ast_prof_level_timeout`;
CREATE TABLE `cq_ast_prof_level_timeout`  (
  `id` int(10) UNSIGNED NOT NULL AUTO_INCREMENT,
  `user_id` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `ast_prof` tinyint(3) UNSIGNED NOT NULL DEFAULT 0,
  `level` tinyint(3) UNSIGNED NOT NULL DEFAULT 1,
  PRIMARY KEY (`id`) USING BTREE,
  INDEX `user_id`(`user_id`) USING BTREE
) ENGINE = MyISAM AUTO_INCREMENT = 1 CHARACTER SET = latin1 COLLATE = latin1_bin ROW_FORMAT = FIXED;

DROP TABLE IF EXISTS `cq_ast_prof_promote_condition`;
cq_ast_prof_promote_condition`;
CREATE TABLE `cq_ast_prof_promote_condition`  (
  `id` int(10) UNSIGNED NOT NULL AUTO_INCREMENT,
  `ast_prof_type` tinyint(3) UNSIGNED NOT NULL DEFAULT 0,
  `ast_prof_rank` tinyint(3) UNSIGNED NOT NULL DEFAULT 0,
  `metempsychosis` tinyint(3) UNSIGNED NULL DEFAULT 0,
  `user_level` tinyint(3) UNSIGNED NULL DEFAULT 0,
  `ast_prof_level` tinyint(3) UNSIGNED NULL DEFAULT 0,
  PRIMARY KEY (`id`) USING BTREE
) ENGINE = MyISAM AUTO_INCREMENT = 57 CHARACTER SET = latin1 COLLATE = latin1_bin ROW_FORMAT = FIXED;

DROP TABLE IF EXISTS `cq_auction`;
cq_auction`;
CREATE TABLE `cq_auction`  (
  `id` int(10) NOT NULL AUTO_INCREMENT,
  `class` smallint(4) UNSIGNED NOT NULL DEFAULT 0,
  `seller` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `seller_name` varbinary(15) NOT NULL DEFAULT '',
  `item_id` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `money_type` tinyint(4) UNSIGNED NOT NULL DEFAULT 0,
  `price` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `fix_price` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `deposit` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `time_out` varchar(12) CHARACTER SET latin1 COLLATE latin1_bin NOT NULL DEFAULT '',
  `bider` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `bider_name` varbinary(15) NOT NULL DEFAULT '',
  PRIMARY KEY (`id`) USING BTREE
) ENGINE = MyISAM AUTO_INCREMENT = 1 CHARACTER SET = latin1 COLLATE = latin1_bin ROW_FORMAT = DYNAMIC;

DROP TABLE IF EXISTS `cq_award_config`;
cq_award_config`;
CREATE TABLE `cq_award_config`  (
  `id` int(4) NOT NULL AUTO_INCREMENT,
  `type` int(4) NOT NULL DEFAULT 0,
  `data1` int(4) NOT NULL DEFAULT 0,
  `data2` int(4) NOT NULL DEFAULT 0,
  `data3` int(4) NOT NULL DEFAULT 0,
  `data4` int(4) NOT NULL DEFAULT 0,
  `data5` int(4) NOT NULL DEFAULT 0,
  `describ` varchar(255) CHARACTER SET latin1 COLLATE latin1_bin NOT NULL DEFAULT '',
  PRIMARY KEY (`id`) USING BTREE
) ENGINE = MyISAM AUTO_INCREMENT = 172 CHARACTER SET = latin1 COLLATE = latin1_bin ROW_FORMAT = DYNAMIC;

DROP TABLE IF EXISTS `cq_bonus`;
cq_bonus`;
CREATE TABLE `cq_bonus`  (
  `action` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `id` int(4) UNSIGNED NOT NULL AUTO_INCREMENT,
  `id_account` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `flag` tinyint(3) UNSIGNED NOT NULL DEFAULT 0,
  `ref_id` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `time` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `ordernumber` varchar(50) CHARACTER SET latin1 COLLATE latin1_bin NOT NULL DEFAULT '',
  `bonus_in_time` int(11) NOT NULL DEFAULT 0,
  `number` int(4) UNSIGNED NOT NULL DEFAULT 1,
  PRIMARY KEY (`id`) USING BTREE,
  INDEX `ordernumber`(`ordernumber`) USING BTREE,
  INDEX `bonus_in_time`(`bonus_in_time`) USING BTREE,
  INDEX `number`(`number`) USING BTREE,
  INDEX `index_refid`(`ref_id`) USING BTREE,
  INDEX `index_ordernumber`(`ordernumber`) USING BTREE,
  INDEX `idx_id_account_flag`(`id_account`, `flag`) USING BTREE
) ENGINE = MyISAM AUTO_INCREMENT = 1 CHARACTER SET = latin1 COLLATE = latin1_bin ROW_FORMAT = DYNAMIC;

DROP TABLE IF EXISTS `cq_business`;
cq_business`;
CREATE TABLE `cq_business`  (
  `id` int(4) UNSIGNED NOT NULL AUTO_INCREMENT,
  `userid` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `business` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `date` int(4) UNSIGNED NOT NULL DEFAULT 0,
  PRIMARY KEY (`id`) USING BTREE,
  INDEX `idx_userid`(`userid`) USING BTREE,
  INDEX `business`(`business`) USING BTREE
) ENGINE = MyISAM AUTO_INCREMENT = 1 CHARACTER SET = latin1 COLLATE = latin1_bin ROW_FORMAT = FIXED;

DROP TABLE IF EXISTS `cq_card`;
cq_card`;
CREATE TABLE `cq_card`  (
  `id` int(4) UNSIGNED NOT NULL AUTO_INCREMENT,
  `type` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `account_id` int(4) UNSIGNED NOT NULL DEFAULT 0,
  PRIMARY KEY (`id`) USING BTREE,
  INDEX `index_account_id`(`account_id`) USING BTREE
) ENGINE = MyISAM AUTO_INCREMENT = 1 CHARACTER SET = latin1 COLLATE = latin1_bin ROW_FORMAT = FIXED;

DROP TABLE IF EXISTS `cq_card2`;
cq_card2`;
CREATE TABLE `cq_card2`  (
  `id` int(4) UNSIGNED NOT NULL AUTO_INCREMENT,
  `type` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `account_id` int(4) UNSIGNED NOT NULL DEFAULT 0,
  PRIMARY KEY (`id`) USING BTREE,
  INDEX `account_id`(`account_id`) USING BTREE
) ENGINE = MyISAM AUTO_INCREMENT = 1 CHARACTER SET = latin1 COLLATE = latin1_bin ROW_FORMAT = FIXED;

DROP TABLE IF EXISTS `cq_card3`;
cq_card3`;
CREATE TABLE `cq_card3`  (
  `id` int(4) UNSIGNED NOT NULL AUTO_INCREMENT,
  `type` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `account_id` int(4) UNSIGNED NOT NULL DEFAULT 0,
  PRIMARY KEY (`id`) USING BTREE,
  INDEX `account_id`(`account_id`) USING BTREE
) ENGINE = MyISAM AUTO_INCREMENT = 1 CHARACTER SET = latin1 COLLATE = latin1_bin ROW_FORMAT = FIXED;

DROP TABLE IF EXISTS `cq_card4`;
cq_card4`;
CREATE TABLE `cq_card4`  (
  `id` int(4) UNSIGNED NOT NULL AUTO_INCREMENT,
  `type` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `account_id` int(4) UNSIGNED NOT NULL DEFAULT 0,
  PRIMARY KEY (`id`) USING BTREE,
  INDEX `account_id`(`account_id`) USING BTREE
) ENGINE = MyISAM AUTO_INCREMENT = 1 CHARACTER SET = latin1 COLLATE = latin1_bin ROW_FORMAT = FIXED;

DROP TABLE IF EXISTS `cq_changename_backup`;
cq_changename_backup`;
CREATE TABLE `cq_changename_backup`  (
  `id` int(4) UNSIGNED NOT NULL AUTO_INCREMENT,
  `iduser` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `oldname` varbinary(15) NOT NULL DEFAULT '',
  `newname` varbinary(15) NOT NULL DEFAULT '',
  PRIMARY KEY (`id`) USING BTREE
) ENGINE = MyISAM AUTO_INCREMENT = 1 CHARACTER SET = latin1 COLLATE = latin1_bin ROW_FORMAT = DYNAMIC;

DROP TABLE IF EXISTS `cq_client_config`;
cq_client_config`;
CREATE TABLE `cq_client_config`  (
  `id` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `server_name` varbinary(50) NOT NULL DEFAULT '',
  `cross_server` varbinary(50) NOT NULL DEFAULT '',
  `map_id` int(4) UNSIGNED ZEROFILL NOT NULL DEFAULT 0000,
  `pos_x` int(4) UNSIGNED ZEROFILL NOT NULL DEFAULT 0000,
  `pos_y` int(4) UNSIGNED ZEROFILL NOT NULL DEFAULT 0000,
  `range` int(4) UNSIGNED ZEROFILL NOT NULL DEFAULT 0000,
  `npc_id` int(4) UNSIGNED ZEROFILL NOT NULL DEFAULT 0000,
  `attribute` int(4) UNSIGNED ZEROFILL NOT NULL DEFAULT 0000,
  PRIMARY KEY (`id`) USING BTREE,
  UNIQUE INDEX `server_name`(`server_name`) USING BTREE
) ENGINE = MyISAM CHARACTER SET = latin1 COLLATE = latin1_bin ROW_FORMAT = DYNAMIC;

DROP TABLE IF EXISTS `cq_competesponsor`;
cq_competesponsor`;
CREATE TABLE `cq_competesponsor`  (
  `id` int(4) UNSIGNED NOT NULL AUTO_INCREMENT,
  `competetype` tinyint(4) NOT NULL DEFAULT 0,
  `idsponsoruser` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `idtarget` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `idoppnent` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `sponsormoney` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `starttime` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `nomal` tinyint(3) UNSIGNED NOT NULL DEFAULT 0,
  PRIMARY KEY (`id`) USING BTREE
) ENGINE = MyISAM AUTO_INCREMENT = 1621 CHARACTER SET = latin1 COLLATE = latin1_bin ROW_FORMAT = FIXED;

DROP TABLE IF EXISTS `cq_config`;
cq_config`;
CREATE TABLE `cq_config`  (
  `id` int(4) NOT NULL AUTO_INCREMENT,
  `type` int(4) NOT NULL DEFAULT 0,
  `data1` int(4) NOT NULL DEFAULT 0,
  `data2` int(4) NOT NULL DEFAULT 0,
  `data3` int(4) NOT NULL DEFAULT 0,
  `data4` int(4) NOT NULL DEFAULT 0,
  `data5` int(4) NOT NULL DEFAULT 0,
  `describ` varbinary(255) NOT NULL DEFAULT '',
  PRIMARY KEY (`id`) USING BTREE,
  INDEX `idx_type`(`type`) USING BTREE
) ENGINE = MyISAM AUTO_INCREMENT = 80243 CHARACTER SET = latin1 COLLATE = latin1_bin ROW_FORMAT = DYNAMIC;

DROP TABLE IF EXISTS `cq_country_info`;
cq_country_info`;
CREATE TABLE `cq_country_info`  (
  `ID` int(11) NOT NULL AUTO_INCREMENT,
  `na` int(11) NULL DEFAULT NULL,
  PRIMARY KEY (`ID`) USING BTREE
) ENGINE = InnoDB AUTO_INCREMENT = 5 CHARACTER SET = latin1 COLLATE = latin1_bin ROW_FORMAT = COMPACT;

DROP TABLE IF EXISTS `cq_cross_merit`;
cq_cross_merit`;
CREATE TABLE `cq_cross_merit`  (
  `id` int(10) UNSIGNED NOT NULL AUTO_INCREMENT,
  `date` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `rank` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `user_id` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `merit` int(10) UNSIGNED NOT NULL DEFAULT 0,
  PRIMARY KEY (`id`) USING BTREE,
  INDEX `id`(`id`) USING BTREE
) ENGINE = MyISAM AUTO_INCREMENT = 1 CHARACTER SET = latin1 COLLATE = latin1_bin ROW_FORMAT = FIXED;

DROP TABLE IF EXISTS `cq_cross_vexillum`;
cq_cross_vexillum`;
CREATE TABLE `cq_cross_vexillum`  (
  `id` int(4) UNSIGNED NOT NULL AUTO_INCREMENT,
  `rank` smallint(4) UNSIGNED NOT NULL DEFAULT 0,
  `synid` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `server_name` varbinary(15) NULL DEFAULT '',
  `syn_name` varbinary(35) NULL DEFAULT '',
  `is_self` smallint(4) UNSIGNED NOT NULL DEFAULT 0,
  `usercount` smallint(4) UNSIGNED NOT NULL DEFAULT 0,
  `score` int(4) UNSIGNED NOT NULL DEFAULT 0,
  PRIMARY KEY (`id`) USING BTREE,
  INDEX `idx_rank`(`rank`) USING BTREE
) ENGINE = MyISAM AUTO_INCREMENT = 1 CHARACTER SET = latin1 COLLATE = latin1_bin ROW_FORMAT = DYNAMIC;

DROP TABLE IF EXISTS `cq_db`;
cq_db`;
CREATE TABLE `cq_db`  (
  `id` int(16) UNSIGNED NOT NULL AUTO_INCREMENT,
  `type` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `account_id` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `ref_id` int(4) UNSIGNED NULL DEFAULT 0,
  `chk_sum` int(4) UNSIGNED NULL DEFAULT 0,
  `time_stamp` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `used` tinyint(3) UNSIGNED NOT NULL DEFAULT 0,
  PRIMARY KEY (`id`) USING BTREE,
  INDEX `idx_accountid_chksum`(`account_id`, `chk_sum`) USING BTREE
) ENGINE = MyISAM AUTO_INCREMENT = 1 CHARACTER SET = latin1 COLLATE = latin1_bin ROW_FORMAT = FIXED;

DROP TABLE IF EXISTS `cq_db2`;
cq_db2`;
CREATE TABLE `cq_db2`  (
  `id` int(16) UNSIGNED NOT NULL AUTO_INCREMENT,
  `type` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `account_id` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `ref_id` int(4) UNSIGNED NULL DEFAULT 0,
  `chk_sum` int(4) UNSIGNED NULL DEFAULT 0,
  `time_stamp` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `used` tinyint(3) UNSIGNED NOT NULL DEFAULT 0,
  PRIMARY KEY (`id`) USING BTREE,
  INDEX `idx_accountid_chksum`(`account_id`, `chk_sum`) USING BTREE
) ENGINE = MyISAM AUTO_INCREMENT = 1 CHARACTER SET = latin1 COLLATE = latin1_bin ROW_FORMAT = FIXED;

DROP TABLE IF EXISTS `cq_deluser`;
cq_deluser`;
CREATE TABLE `cq_deluser`  (
  `name` varbinary(15) NOT NULL DEFAULT '',
  `lastname` varbinary(15) NOT NULL DEFAULT '',
  `mateid` int(4) UNSIGNED NULL DEFAULT 0,
  `lookface` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `hair` smallint(2) UNSIGNED NOT NULL DEFAULT 0,
  `money` bigint(4) UNSIGNED NOT NULL DEFAULT 0,
  `money_saved` bigint(4) UNSIGNED NOT NULL DEFAULT 0,
  `coin_money` int(3) UNSIGNED NOT NULL DEFAULT 0,
  `level` tinyint(1) UNSIGNED NOT NULL DEFAULT 1,
  `exp` bigint(4) NOT NULL DEFAULT 0,
  `strength` smallint(2) UNSIGNED NOT NULL DEFAULT 0,
  `old_prof` tinyint(2) UNSIGNED NOT NULL DEFAULT 0,
  `Speed` smallint(2) UNSIGNED NOT NULL DEFAULT 0,
  `health` smallint(2) UNSIGNED NOT NULL DEFAULT 0,
  `soul` smallint(2) UNSIGNED NOT NULL DEFAULT 0,
  `additional_point` smallint(2) UNSIGNED NOT NULL DEFAULT 0,
  `auto_allot` tinyint(1) UNSIGNED NOT NULL DEFAULT 1,
  `life` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `mana` smallint(2) UNSIGNED NOT NULL DEFAULT 0,
  `profession` tinyint(2) UNSIGNED NOT NULL DEFAULT 0,
  `deed` int(4) NOT NULL DEFAULT 0,
  `pk` smallint(2) NOT NULL DEFAULT 0,
  `nobility` tinyint(1) UNSIGNED NOT NULL DEFAULT 0,
  `medal` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `medal_select` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `metempsychosis` tinyint(1) UNSIGNED NOT NULL DEFAULT 0,
  `recordmap_id` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `recordx` smallint(2) UNSIGNED NOT NULL DEFAULT 0,
  `recordy` smallint(2) UNSIGNED NOT NULL DEFAULT 0,
  `account_id` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `id` int(4) UNSIGNED NOT NULL AUTO_INCREMENT,
  `last_login` int(8) UNSIGNED NOT NULL DEFAULT 0,
  `first_login` int(8) UNSIGNED NOT NULL DEFAULT 0,
  `account` varchar(15) CHARACTER SET latin1 COLLATE latin1_bin NOT NULL DEFAULT 'None',
  `password` varchar(15) CHARACTER SET latin1 COLLATE latin1_bin NOT NULL DEFAULT 'None',
  `task_mask` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `time_of_life` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `virtue` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `home_id` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `lock_key` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `lock_cls` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `emoney` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `chk_sum` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `god_status` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `exp_ball_usage` smallint(2) UNSIGNED NOT NULL DEFAULT 0,
  `online_time` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `auto_exercise` tinyint(2) UNSIGNED NOT NULL DEFAULT 0,
  `last_logout` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `big_prize_fails` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `small_prize_fails` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `mete_lev` int(4) NOT NULL DEFAULT 0,
  `current_layout_type` tinyint(1) NOT NULL DEFAULT 0,
  `flower` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `online_time2` tinyint(4) UNSIGNED NOT NULL DEFAULT 0,
  `offline_time` tinyint(4) UNSIGNED NOT NULL DEFAULT 0,
  `last_logout2` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `donation` bigint(20) UNSIGNED NOT NULL DEFAULT 0,
  `business` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `send_flower_date` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `flower_r` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `flower_w` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `flower_lily` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `flower_tulip` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `quiz_point` int(4) UNSIGNED NULL DEFAULT 0,
  `vip_value` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `flag` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `first_prof` tinyint(2) UNSIGNED NOT NULL DEFAULT 0,
  `online_god_exptime` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `battle_god_exptime` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `mentor_opportunity` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `mentor_uplev_time` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `mentor_achieve` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `mentor_day` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `title` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `title_select` tinyint(3) UNSIGNED NOT NULL DEFAULT 0,
  `athlete_point` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `athlete_history_wins` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `athlete_history_loses` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `athlete_day_wins` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `athlete_day_loses` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `athlete_cur_honor_point` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `athlete_hisorty_honor_point` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `last_logout_3` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `emoney_mono` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `ridepet_point` int(4) UNSIGNED NULL DEFAULT 0,
  `current_ast_prof` tinyint(3) UNSIGNED NOT NULL DEFAULT 0,
  `ast_prof_rank` bigint(20) UNSIGNED NOT NULL DEFAULT 0,
  `cultivation` bigint(20) UNSIGNED NOT NULL DEFAULT 0,
  `changenamerecord` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `pkprotocol` tinyint(4) UNSIGNED NOT NULL DEFAULT 0,
  `family_arenic` tinyint(3) UNSIGNED NOT NULL DEFAULT 0,
  `uin` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `team_athlete_point` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `team_athlete_win` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `team_athlete_lost` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `team_athlete_season_win` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `team_athlete_season_lost` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `mete_lev2` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `strength_value` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `showtype` tinyint(3) UNSIGNED NOT NULL DEFAULT 0,
  `nationality` smallint(2) UNSIGNED NOT NULL DEFAULT 0,
  `pk_setting` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `culture_value` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `texasmatch_win` bigint(20) UNSIGNED NOT NULL DEFAULT 0,
  `texasmatch_lose` bigint(20) UNSIGNED NOT NULL DEFAULT 0,
  `chestpackage_size` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `league_contribution` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `shielded_times` smallint(4) UNSIGNED NOT NULL DEFAULT 0,
  `channel_account` varchar(74) CHARACTER SET latin1 COLLATE latin1_bin NOT NULL DEFAULT '',
  PRIMARY KEY (`id`) USING BTREE,
  INDEX `index_name`(`name`) USING BTREE,
  INDEX `index_account`(`account_id`) USING BTREE
) ENGINE = MyISAM AUTO_INCREMENT = 1 CHARACTER SET = latin1 COLLATE = latin1_bin ROW_FORMAT = DYNAMIC;

DROP TABLE IF EXISTS `cq_deluser_timeout`;
cq_deluser_timeout`;
CREATE TABLE `cq_deluser_timeout`  (
  `name` varbinary(15) NOT NULL DEFAULT '',
  `lastname` varbinary(15) NOT NULL DEFAULT '',
  `mateid` int(4) UNSIGNED NULL DEFAULT 0,
  `lookface` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `hair` smallint(2) UNSIGNED NOT NULL DEFAULT 0,
  `money` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `money_saved` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `coin_money` int(3) UNSIGNED NOT NULL DEFAULT 0,
  `level` tinyint(1) UNSIGNED NOT NULL DEFAULT 1,
  `exp` bigint(4) NOT NULL DEFAULT 0,
  `strength` smallint(2) UNSIGNED NOT NULL DEFAULT 0,
  `old_prof` tinyint(2) UNSIGNED NOT NULL DEFAULT 0,
  `Speed` smallint(2) UNSIGNED NOT NULL DEFAULT 0,
  `health` smallint(2) UNSIGNED NOT NULL DEFAULT 0,
  `soul` smallint(2) UNSIGNED NOT NULL DEFAULT 0,
  `additional_point` smallint(2) UNSIGNED NOT NULL DEFAULT 0,
  `auto_allot` tinyint(1) UNSIGNED NOT NULL DEFAULT 1,
  `life` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `mana` smallint(2) UNSIGNED NOT NULL DEFAULT 0,
  `profession` tinyint(2) UNSIGNED NOT NULL DEFAULT 0,
  `deed` int(4) NOT NULL DEFAULT 0,
  `pk` smallint(2) NOT NULL DEFAULT 0,
  `nobility` tinyint(1) UNSIGNED NOT NULL DEFAULT 0,
  `medal` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `medal_select` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `metempsychosis` tinyint(1) UNSIGNED NOT NULL DEFAULT 0,
  `recordmap_id` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `recordx` smallint(2) UNSIGNED NOT NULL DEFAULT 0,
  `recordy` smallint(2) UNSIGNED NOT NULL DEFAULT 0,
  `account_id` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `id` int(4) UNSIGNED NOT NULL AUTO_INCREMENT,
  `last_login` int(8) UNSIGNED NOT NULL DEFAULT 0,
  `first_login` int(8) UNSIGNED NOT NULL DEFAULT 0,
  `account` varchar(15) CHARACTER SET latin1 COLLATE latin1_bin NOT NULL DEFAULT 'None',
  `password` varchar(15) CHARACTER SET latin1 COLLATE latin1_bin NOT NULL DEFAULT 'None',
  `task_mask` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `time_of_life` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `virtue` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `home_id` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `lock_key` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `lock_cls` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `emoney` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `chk_sum` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `god_status` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `exp_ball_usage` smallint(2) UNSIGNED NOT NULL DEFAULT 0,
  `online_time` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `auto_exercise` tinyint(2) UNSIGNED NOT NULL DEFAULT 0,
  `last_logout` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `big_prize_fails` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `small_prize_fails` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `mete_lev` int(4) NOT NULL DEFAULT 0,
  `current_layout_type` tinyint(1) NOT NULL DEFAULT 0,
  `flower` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `online_time2` tinyint(4) UNSIGNED NOT NULL DEFAULT 0,
  `offline_time` tinyint(4) UNSIGNED NOT NULL DEFAULT 0,
  `last_logout2` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `donation` bigint(20) UNSIGNED NOT NULL DEFAULT 0,
  `business` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `send_flower_date` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `flower_r` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `flower_w` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `flower_lily` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `flower_tulip` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `quiz_point` int(4) UNSIGNED NULL DEFAULT 0,
  `vip_value` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `flag` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `first_prof` tinyint(2) UNSIGNED NOT NULL DEFAULT 0,
  `online_god_exptime` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `battle_god_exptime` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `mentor_opportunity` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `mentor_uplev_time` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `mentor_achieve` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `mentor_day` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `title` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `title_select` tinyint(3) UNSIGNED NOT NULL DEFAULT 0,
  `athlete_point` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `athlete_history_wins` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `athlete_history_loses` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `athlete_day_wins` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `athlete_day_loses` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `athlete_cur_honor_point` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `athlete_hisorty_honor_point` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `last_logout_3` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `emoney_mono` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `ridepet_point` int(4) UNSIGNED NULL DEFAULT 0,
  `current_ast_prof` tinyint(3) UNSIGNED NOT NULL DEFAULT 0,
  `ast_prof_rank` bigint(20) UNSIGNED NOT NULL DEFAULT 0,
  `cultivation` bigint(20) UNSIGNED NOT NULL DEFAULT 0,
  `changenamerecord` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `pkprotocol` tinyint(4) UNSIGNED NOT NULL DEFAULT 0,
  `family_arenic` tinyint(3) UNSIGNED NOT NULL DEFAULT 0,
  `uin` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `team_athlete_point` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `team_athlete_win` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `team_athlete_lost` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `team_athlete_season_win` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `team_athlete_season_lost` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `mete_lev2` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `strength_value` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `showtype` tinyint(3) UNSIGNED NOT NULL DEFAULT 0,
  `nationality` smallint(2) UNSIGNED NOT NULL DEFAULT 0,
  `pk_setting` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `culture_value` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `texasmatch_win` bigint(20) UNSIGNED NOT NULL DEFAULT 0,
  `texasmatch_lose` bigint(20) UNSIGNED NOT NULL DEFAULT 0,
  `chestpackage_size` tinyint(2) UNSIGNED NOT NULL DEFAULT 0,
  `league_contribution` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `shielded_times` smallint(4) UNSIGNED NOT NULL DEFAULT 0,
  `channel_account` varchar(74) CHARACTER SET latin1 COLLATE latin1_bin NOT NULL DEFAULT '',
  PRIMARY KEY (`id`) USING BTREE,
  INDEX `index_name`(`name`) USING BTREE,
  INDEX `index_account`(`account_id`) USING BTREE
) ENGINE = MyISAM AUTO_INCREMENT = 1 CHARACTER SET = latin1 COLLATE = latin1_bin ROW_FORMAT = DYNAMIC;

DROP TABLE IF EXISTS `cq_depot`;
cq_depot`;
CREATE TABLE `cq_depot`  (
  `id` int(4) UNSIGNED NOT NULL AUTO_INCREMENT,
  `ownerid` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `playerid` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `level` tinyint(4) UNSIGNED NOT NULL DEFAULT 0,
  `pwd` varbinary(32) NULL DEFAULT NULL,
  PRIMARY KEY (`id`) USING BTREE,
  UNIQUE INDEX `id`(`id`) USING BTREE,
  INDEX `id_2`(`id`) USING BTREE
) ENGINE = MyISAM AUTO_INCREMENT = 1 CHARACTER SET = latin1 COLLATE = latin1_bin ROW_FORMAT = DYNAMIC;

DROP TABLE IF EXISTS `cq_disdain`;
cq_disdain`;
CREATE TABLE `cq_disdain`  (
  `id` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `type` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `delta_lev` int(4) NOT NULL DEFAULT 0,
  `usr_atk_mst` int(4) NOT NULL DEFAULT 0,
  `mst_atk` int(4) NOT NULL DEFAULT 0,
  `max_atk` int(4) NOT NULL DEFAULT 0,
  `max_xp_atk` int(4) NOT NULL DEFAULT 0,
  `exp_factor` int(4) NOT NULL DEFAULT 0,
  `xp_exp_factor` int(4) NOT NULL DEFAULT 0,
  `usr_atk_usr_min` int(4) NOT NULL DEFAULT 0,
  `usr_atk_usr_max` int(4) NOT NULL DEFAULT 0,
  `usr_atk_usr_overadj` int(4) NOT NULL DEFAULT 0,
  `usr_atk_usrx_min` int(4) NOT NULL DEFAULT 0,
  `usr_atk_usrx_max` int(4) NOT NULL DEFAULT 0,
  `usr_atk_usrx_overadj` int(4) NOT NULL DEFAULT 0,
  `usrx_atk_usr_min` int(4) NOT NULL DEFAULT 0,
  `usrx_atk_usr_max` int(4) NOT NULL DEFAULT 0,
  `usrx_atk_usr_overadj` int(4) NOT NULL DEFAULT 0,
  `usrx_atk_usrx_min` int(4) NOT NULL DEFAULT 0,
  `usrx_atk_usrx_max` int(4) NOT NULL DEFAULT 0,
  `usrx_atk_usrx_overadj` int(4) NOT NULL DEFAULT 0,
  PRIMARY KEY (`id`) USING BTREE
) ENGINE = MyISAM CHARACTER SET = latin1 COLLATE = latin1_bin ROW_FORMAT = FIXED;

DROP TABLE IF EXISTS `cq_dropitemrule`;
cq_dropitemrule`;
CREATE TABLE `cq_dropitemrule`  (
  `id` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `RuleId` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `Chance` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `Item0` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `Item1` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `Item2` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `Item3` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `Item4` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `Item5` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `Item6` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `Item7` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `Item8` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `Item9` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `Item10` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `Item11` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `Item12` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `Item13` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `Item14` int(10) UNSIGNED NOT NULL DEFAULT 0,
  PRIMARY KEY (`id`, `RuleId`) USING BTREE
) ENGINE = MyISAM CHARACTER SET = latin1 COLLATE = latin1_bin ROW_FORMAT = FIXED;

DROP TABLE IF EXISTS `cq_dyna_global_data`;
cq_dyna_global_data`;
CREATE TABLE `cq_dyna_global_data`  (
  `id` int(4) UNSIGNED NOT NULL AUTO_INCREMENT,
  `data0` int(4) NOT NULL DEFAULT 0,
  `data1` int(4) NOT NULL DEFAULT 0,
  `data2` int(4) NOT NULL DEFAULT 0,
  `data3` int(4) NOT NULL DEFAULT 0,
  `data4` int(4) NOT NULL DEFAULT 0,
  `data5` int(4) NOT NULL DEFAULT 0,
  `datastr0` varbinary(35) NOT NULL DEFAULT '',
  `datastr1` varbinary(35) NOT NULL DEFAULT '',
  `datastr2` varbinary(35) NOT NULL DEFAULT '',
  `datastr3` varbinary(35) NOT NULL DEFAULT '',
  `datastr4` varbinary(35) NOT NULL DEFAULT '',
  `datastr5` varbinary(35) NOT NULL DEFAULT '',
  `time0` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `time1` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `time2` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `time3` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `time4` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `time5` int(4) UNSIGNED NOT NULL DEFAULT 0,
  PRIMARY KEY (`id`) USING BTREE
) ENGINE = MyISAM AUTO_INCREMENT = 80162 CHARACTER SET = latin1 COLLATE = latin1_bin ROW_FORMAT = DYNAMIC;

DROP TABLE IF EXISTS `cq_dyna_rank_rec`;
cq_dyna_rank_rec`;
CREATE TABLE `cq_dyna_rank_rec`  (
  `id` int(4) UNSIGNED NOT NULL AUTO_INCREMENT,
  `Rank_type` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `Value` bigint(4) NOT NULL DEFAULT 0,
  `Obj_id` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `user_id` int(4) UNSIGNED NOT NULL DEFAULT 0,
  PRIMARY KEY (`id`) USING BTREE,
  UNIQUE INDEX `id`(`id`) USING BTREE,
  INDEX `Rank_type`(`Rank_type`) USING BTREE,
  INDEX `user_id`(`user_id`) USING BTREE,
  INDEX `Obj_id`(`Obj_id`) USING BTREE
) ENGINE = MyISAM AUTO_INCREMENT = 34 CHARACTER SET = latin1 COLLATE = latin1_bin ROW_FORMAT = FIXED;

DROP TABLE IF EXISTS `cq_dyna_rank_type`;
cq_dyna_rank_type`;
CREATE TABLE `cq_dyna_rank_type`  (
  `id` int(4) UNSIGNED NOT NULL AUTO_INCREMENT,
  `Rank_type` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `Rank_num` smallint(4) UNSIGNED NOT NULL DEFAULT 0,
  `Rank_date_min` int(4) UNSIGNED NOT NULL DEFAULT 0,
  PRIMARY KEY (`id`) USING BTREE,
  UNIQUE INDEX `id`(`id`) USING BTREE,
  INDEX `Rank_type`(`Rank_type`) USING BTREE
) ENGINE = MyISAM AUTO_INCREMENT = 26 CHARACTER SET = latin1 COLLATE = latin1_bin ROW_FORMAT = FIXED;

DROP TABLE IF EXISTS `cq_dynamap`;
cq_dynamap`;
CREATE TABLE `cq_dynamap`  (
  `id` int(4) UNSIGNED NOT NULL AUTO_INCREMENT,
  `name` varbinary(35) NOT NULL DEFAULT 'undefined',
  `describe_text` varchar(127) CHARACTER SET latin1 COLLATE latin1_bin NOT NULL DEFAULT '',
  `mapdoc` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `type` bigint(4) UNSIGNED NOT NULL DEFAULT 0,
  `owner_id` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `mapgroup` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `idxserver` int(4) NOT NULL DEFAULT -1,
  `weather` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `bgmusic` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `bgmusic_show` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `portal0_x` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `portal0_y` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `reborn_mapid` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `reborn_portal` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `res_lev` tinyint(3) UNSIGNED NOT NULL DEFAULT 0,
  `owner_type` tinyint(3) UNSIGNED NOT NULL DEFAULT 0,
  `link_map` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `link_x` smallint(2) UNSIGNED NOT NULL DEFAULT 0,
  `link_y` smallint(2) UNSIGNED NOT NULL DEFAULT 0,
  `del_flag` tinyint(1) UNSIGNED NOT NULL DEFAULT 0,
  `color` int(4) UNSIGNED NULL DEFAULT 4294967295,
  PRIMARY KEY (`id`) USING BTREE,
  INDEX `idx`(`idxserver`, `mapgroup`) USING BTREE
) ENGINE = MyISAM AUTO_INCREMENT = 1000002 CHARACTER SET = latin1 COLLATE = latin1_bin ROW_FORMAT = DYNAMIC;

DROP TABLE IF EXISTS `cq_dynanpc`;
cq_dynanpc`;
CREATE TABLE `cq_dynanpc`  (
  `id` int(4) UNSIGNED NOT NULL AUTO_INCREMENT,
  `ownerid` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `ownertype` tinyint(3) UNSIGNED NOT NULL DEFAULT 0,
  `name` varbinary(35) NOT NULL DEFAULT 'undefined',
  `type` smallint(2) UNSIGNED NOT NULL DEFAULT 0,
  `lookface` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `idxserver` tinyint(3) NOT NULL DEFAULT -1,
  `mapid` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `cellx` smallint(2) UNSIGNED NOT NULL DEFAULT 0,
  `celly` smallint(2) UNSIGNED NOT NULL DEFAULT 0,
  `task0` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `task1` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `task2` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `task3` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `task4` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `task5` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `task6` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `task7` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `data0` int(4) NOT NULL DEFAULT 0,
  `data1` int(4) NOT NULL DEFAULT 0,
  `data2` int(4) NOT NULL DEFAULT 0,
  `data3` int(4) NOT NULL DEFAULT 0,
  `datastr` varbinary(255) NOT NULL DEFAULT 'None',
  `linkid` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `life` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `maxlife` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `base` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `sort` smallint(2) UNSIGNED NOT NULL DEFAULT 0,
  `itemid` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `owner_name` varchar(35) CHARACTER SET latin1 COLLATE latin1_bin NULL DEFAULT '',
  `default_owner_name` varbinary(15) NULL DEFAULT '',
  `defence` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `magic_def` smallint(2) UNSIGNED NOT NULL DEFAULT 0,
  `harvest_date` int(10) UNSIGNED NOT NULL DEFAULT 0,
  PRIMARY KEY (`id`) USING BTREE,
  INDEX `idx_mapid`(`mapid`) USING BTREE
) ENGINE = MyISAM AUTO_INCREMENT = 18554753 CHARACTER SET = latin1 COLLATE = latin1_bin ROW_FORMAT = DYNAMIC;

DROP TABLE IF EXISTS `cq_enemy`;
cq_enemy`;
CREATE TABLE `cq_enemy`  (
  `id` int(4) UNSIGNED NOT NULL AUTO_INCREMENT,
  `userid` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `enemy` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `time` int(4) UNSIGNED NOT NULL DEFAULT 0,
  PRIMARY KEY (`id`) USING BTREE,
  UNIQUE INDEX `u_userid_enemy`(`userid`, `enemy`) USING BTREE
) ENGINE = MyISAM AUTO_INCREMENT = 2 CHARACTER SET = latin1 COLLATE = latin1_bin ROW_FORMAT = FIXED;

DROP TABLE IF EXISTS `cq_enemy_timeout`;
cq_enemy_timeout`;
CREATE TABLE `cq_enemy_timeout`  (
  `id` int(4) UNSIGNED NOT NULL AUTO_INCREMENT,
  `userid` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `enemy` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `time` int(4) UNSIGNED NOT NULL DEFAULT 0,
  PRIMARY KEY (`id`) USING BTREE
) ENGINE = MyISAM AUTO_INCREMENT = 1 CHARACTER SET = latin1 COLLATE = latin1_bin ROW_FORMAT = FIXED;

DROP TABLE IF EXISTS `cq_exchange_buy`;
cq_exchange_buy`;
CREATE TABLE `cq_exchange_buy`  (
  `id` int(4) UNSIGNED NOT NULL AUTO_INCREMENT,
  `price` int(4) UNSIGNED NOT NULL DEFAULT 0,
  PRIMARY KEY (`id`) USING BTREE
) ENGINE = MyISAM AUTO_INCREMENT = 191406 CHARACTER SET = latin1 COLLATE = latin1_bin ROW_FORMAT = FIXED;

DROP TABLE IF EXISTS `cq_facebook`;
cq_facebook`;
CREATE TABLE `cq_facebook`  (
  `id` int(10) UNSIGNED NOT NULL AUTO_INCREMENT,
  `user_id` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `facebook_id` varchar(32) CHARACTER SET latin1 COLLATE latin1_bin NOT NULL DEFAULT 'None',
  PRIMARY KEY (`id`) USING BTREE
) ENGINE = MyISAM AUTO_INCREMENT = 1 CHARACTER SET = latin1 COLLATE = latin1_bin ROW_FORMAT = DYNAMIC;

DROP TABLE IF EXISTS `cq_fact`;
cq_fact`;
CREATE TABLE `cq_fact`  (
  `id` int(4) UNSIGNED NOT NULL AUTO_INCREMENT,
  `owner_id` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `type` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `priority` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `datetime` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `durable` int(4) UNSIGNED NOT NULL DEFAULT 0,
  PRIMARY KEY (`id`) USING BTREE,
  INDEX `owner_id`(`owner_id`) USING BTREE
) ENGINE = MyISAM AUTO_INCREMENT = 1 CHARACTER SET = latin1 COLLATE = latin1_bin ROW_FORMAT = FIXED;

DROP TABLE IF EXISTS `cq_fate_player`;
cq_fate_player`;
CREATE TABLE `cq_fate_player`  (
  `id` int(10) UNSIGNED NOT NULL AUTO_INCREMENT,
  `player_id` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `fate1_attrib1` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `fate1_attrib2` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `fate1_attrib3` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `fate1_attrib4` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `fate2_attrib1` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `fate2_attrib2` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `fate2_attrib3` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `fate2_attrib4` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `fate3_attrib1` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `fate3_attrib2` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `fate3_attrib3` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `fate3_attrib4` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `fate4_attrib1` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `fate4_attrib2` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `fate4_attrib3` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `fate4_attrib4` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `attrib_lock_info` int(10) UNSIGNED NOT NULL DEFAULT 0,
  PRIMARY KEY (`id`) USING BTREE,
  UNIQUE INDEX `u_player_id`(`player_id`) USING BTREE
) ENGINE = MyISAM AUTO_INCREMENT = 5 CHARACTER SET = latin1 COLLATE = latin1_bin ROW_FORMAT = FIXED;

DROP TABLE IF EXISTS `cq_fate_protect`;
cq_fate_protect`;
CREATE TABLE `cq_fate_protect`  (
  `id` int(10) UNSIGNED NOT NULL AUTO_INCREMENT,
  `player_id` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `fate_no` tinyint(3) UNSIGNED NOT NULL DEFAULT 0,
  `expiry_date` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `attrib_no1` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `attrib_no2` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `attrib_no3` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `attrib_no4` int(10) UNSIGNED NOT NULL DEFAULT 0,
  PRIMARY KEY (`id`) USING BTREE,
  INDEX `player_id`(`player_id`) USING BTREE
) ENGINE = MyISAM AUTO_INCREMENT = 5 CHARACTER SET = latin1 COLLATE = latin1_bin ROW_FORMAT = FIXED;

DROP TABLE IF EXISTS `cq_fate_rand`;
cq_fate_rand`;
CREATE TABLE `cq_fate_rand`  (
  `fate_no` tinyint(3) UNSIGNED NOT NULL DEFAULT 0,
  `range_no` tinyint(3) UNSIGNED NOT NULL DEFAULT 0,
  `range_rate` int(10) UNSIGNED NOT NULL DEFAULT 0,
  PRIMARY KEY (`fate_no`, `range_no`) USING BTREE
) ENGINE = MyISAM CHARACTER SET = latin1 COLLATE = latin1_bin ROW_FORMAT = FIXED;

DROP TABLE IF EXISTS `cq_fate_rank`;
cq_fate_rank`;
CREATE TABLE `cq_fate_rank`  (
  `id` int(10) UNSIGNED NOT NULL AUTO_INCREMENT,
  `fate_no` tinyint(3) UNSIGNED NOT NULL DEFAULT 0,
  `sort` tinyint(3) UNSIGNED NOT NULL DEFAULT 0,
  `attrib1` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `attrib2` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `attrib3` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `attrib4` int(10) UNSIGNED NOT NULL DEFAULT 0,
  PRIMARY KEY (`id`) USING BTREE,
  UNIQUE INDEX `u_fate_rank`(`fate_no`, `sort`) USING BTREE
) ENGINE = MyISAM AUTO_INCREMENT = 201 CHARACTER SET = latin1 COLLATE = latin1_bin ROW_FORMAT = FIXED;

DROP TABLE IF EXISTS `cq_fate_rule`;
cq_fate_rule`;
CREATE TABLE `cq_fate_rule`  (
  `id` int(10) UNSIGNED NOT NULL AUTO_INCREMENT,
  `fate_no` tinyint(3) UNSIGNED NOT NULL DEFAULT 0,
  `attib_type` tinyint(3) UNSIGNED NOT NULL DEFAULT 0,
  `appear_weight` tinyint(3) UNSIGNED NOT NULL DEFAULT 0,
  `attrib_value_min` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `attrib_value_max` int(10) UNSIGNED NOT NULL DEFAULT 0,
  PRIMARY KEY (`id`) USING BTREE,
  UNIQUE INDEX `idx_fate_rule`(`fate_no`, `attib_type`) USING BTREE
) ENGINE = MyISAM AUTO_INCREMENT = 53 CHARACTER SET = latin1 COLLATE = latin1_bin ROW_FORMAT = FIXED;

DROP TABLE IF EXISTS `cq_flag_war`;
cq_flag_war`;
CREATE TABLE `cq_flag_war`  (
  `id` int(10) UNSIGNED NOT NULL AUTO_INCREMENT,
  `syndicate_id` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `old_syn_id` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `syndicate_name` char(50) CHARACTER SET latin1 COLLATE latin1_bin NOT NULL DEFAULT '\"\"',
  `server_id` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `type` tinyint(10) UNSIGNED NOT NULL DEFAULT 0,
  `score` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `member_count` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `rank` tinyint(3) UNSIGNED NOT NULL DEFAULT 0,
  `date` int(10) UNSIGNED NOT NULL DEFAULT 0,
  PRIMARY KEY (`id`) USING BTREE
) ENGINE = MyISAM AUTO_INCREMENT = 1 CHARACTER SET = latin1 COLLATE = latin1_bin COMMENT = 'cross flag war' ROW_FORMAT = FIXED;

DROP TABLE IF EXISTS `cq_flag_war_user`;
cq_flag_war_user`;
CREATE TABLE `cq_flag_war_user`  (
  `id` int(10) UNSIGNED NOT NULL AUTO_INCREMENT,
  `date` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `server_id` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `syndicate_id` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `user_id` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `merit` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `name` varbinary(15) NOT NULL DEFAULT 0,
  PRIMARY KEY (`id`) USING BTREE
) ENGINE = MyISAM AUTO_INCREMENT = 1 CHARACTER SET = latin1 COLLATE = latin1_bin ROW_FORMAT = DYNAMIC;

DROP TABLE IF EXISTS `cq_forbidname`;
cq_forbidname`;
CREATE TABLE `cq_forbidname`  (
  `id` int(4) UNSIGNED NOT NULL AUTO_INCREMENT,
  `check` varbinary(16) NULL DEFAULT NULL,
  PRIMARY KEY (`id`) USING BTREE
) ENGINE = MyISAM AUTO_INCREMENT = 35 CHARACTER SET = latin1 COLLATE = latin1_bin ROW_FORMAT = DYNAMIC;

DROP TABLE IF EXISTS `cq_friend`;
cq_friend`;
CREATE TABLE `cq_friend`  (
  `id` int(4) UNSIGNED NOT NULL AUTO_INCREMENT,
  `userid` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `friend` int(4) UNSIGNED NOT NULL DEFAULT 0,
  PRIMARY KEY (`id`) USING BTREE,
  UNIQUE INDEX `u_userid_friend`(`userid`, `friend`) USING BTREE
) ENGINE = MyISAM AUTO_INCREMENT = 1 CHARACTER SET = latin1 COLLATE = latin1_bin ROW_FORMAT = FIXED;

DROP TABLE IF EXISTS `cq_friend_timeout`;
cq_friend_timeout`;
CREATE TABLE `cq_friend_timeout`  (
  `id` int(4) UNSIGNED NOT NULL AUTO_INCREMENT,
  `userid` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `friend` int(4) UNSIGNED NOT NULL DEFAULT 0,
  PRIMARY KEY (`id`) USING BTREE
) ENGINE = MyISAM AUTO_INCREMENT = 1 CHARACTER SET = latin1 COLLATE = latin1_bin ROW_FORMAT = FIXED;

DROP TABLE IF EXISTS `cq_fuse`;
cq_fuse`;
CREATE TABLE `cq_fuse`  (
  `id` int(10) UNSIGNED NOT NULL AUTO_INCREMENT,
  `sort` tinyint(2) UNSIGNED NOT NULL DEFAULT 0,
  `type` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `lev` tinyint(2) UNSIGNED NOT NULL DEFAULT 0,
  `quality` tinyint(2) UNSIGNED NOT NULL DEFAULT 0,
  `chance` smallint(4) UNSIGNED NOT NULL DEFAULT 0,
  PRIMARY KEY (`id`) USING BTREE
) ENGINE = MyISAM AUTO_INCREMENT = 15519 CHARACTER SET = latin1 COLLATE = latin1_bin ROW_FORMAT = FIXED;

DROP TABLE IF EXISTS `cq_generator`;
cq_generator`;
CREATE TABLE `cq_generator`  (
  `id` int(4) UNSIGNED NOT NULL AUTO_INCREMENT,
  `mapid` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `bound_x` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `bound_y` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `bound_cx` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `bound_cy` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `maxnpc` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `rest_secs` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `max_per_gen` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `npctype` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `timer_begin` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `timer_end` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `born_x` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `born_y` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `mask` tinyint(3) UNSIGNED NOT NULL DEFAULT 0,
  `path` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `return_mode` tinyint(3) UNSIGNED NOT NULL DEFAULT 1,
  `cluster_type` tinyint(3) UNSIGNED NOT NULL DEFAULT 0,
  `attribute` int(3) UNSIGNED NOT NULL DEFAULT 0,
  PRIMARY KEY (`id`) USING BTREE,
  INDEX `mapid`(`mapid`) USING BTREE
) ENGINE = MyISAM AUTO_INCREMENT = 2140001 CHARACTER SET = latin1 COLLATE = latin1_bin ROW_FORMAT = FIXED;

DROP TABLE IF EXISTS `cq_globalvariable`;
cq_globalvariable`;
CREATE TABLE `cq_globalvariable`  (
  `id` int(10) UNSIGNED NOT NULL AUTO_INCREMENT,
  `type` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `data1` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `data2` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `data3` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `data4` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `data5` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `str` varchar(225) CHARACTER SET latin1 COLLATE latin1_bin NULL DEFAULT NULL,
  `desc` varchar(255) CHARACTER SET latin1 COLLATE latin1_bin NULL DEFAULT NULL,
  PRIMARY KEY (`id`) USING BTREE,
  INDEX `idx_type`(`type`) USING BTREE
) ENGINE = MyISAM AUTO_INCREMENT = 27 CHARACTER SET = latin1 COLLATE = latin1_bin ROW_FORMAT = DYNAMIC;

DROP TABLE IF EXISTS `cq_golden_league_data`;
cq_golden_league_data`;
CREATE TABLE `cq_golden_league_data`  (
  `id` int(10) UNSIGNED NOT NULL AUTO_INCREMENT,
  `rank` tinyint(3) UNSIGNED NULL DEFAULT 0,
  `user_id` int(10) UNSIGNED NULL DEFAULT 0,
  `current_point` int(10) UNSIGNED NULL DEFAULT 0,
  `total_point` int(10) UNSIGNED NULL DEFAULT 0,
  PRIMARY KEY (`id`) USING BTREE,
  UNIQUE INDEX `u_user_id`(`user_id`) USING BTREE,
  INDEX `idx_rank`(`rank`) USING BTREE
) ENGINE = MyISAM AUTO_INCREMENT = 5134 CHARACTER SET = latin1 COLLATE = latin1_bin ROW_FORMAT = FIXED;

DROP TABLE IF EXISTS `cq_golden_league_limit`;
cq_golden_league_limit`;
CREATE TABLE `cq_golden_league_limit`  (
  `id` int(10) UNSIGNED NOT NULL AUTO_INCREMENT,
  `rank` tinyint(3) UNSIGNED NULL DEFAULT 0,
  `additional` tinyint(3) UNSIGNED NULL DEFAULT 0,
  `reduce_damage` tinyint(3) UNSIGNED NULL DEFAULT 0,
  `hole` tinyint(3) UNSIGNED NULL DEFAULT 0,
  `gem` tinyint(3) UNSIGNED NULL DEFAULT 0,
  `quench` tinyint(3) UNSIGNED NULL DEFAULT 0,
  `god_soul` tinyint(3) UNSIGNED NULL DEFAULT 0,
  `enhance` smallint(3) UNSIGNED NULL DEFAULT 0,
  `training_vitality` tinyint(3) UNSIGNED NULL DEFAULT 0,
  `peerager` tinyint(3) UNSIGNED NULL DEFAULT 0,
  `ast_prf` tinyint(3) UNSIGNED NULL DEFAULT 0,
  `gong_fu` tinyint(3) UNSIGNED NULL DEFAULT 0,
  PRIMARY KEY (`id`) USING BTREE
) ENGINE = MyISAM AUTO_INCREMENT = 8 CHARACTER SET = latin1 COLLATE = latin1_bin ROW_FORMAT = FIXED;

DROP TABLE IF EXISTS `cq_golden_league_point`;
cq_golden_league_point`;
CREATE TABLE `cq_golden_league_point`  (
  `id` int(10) UNSIGNED NOT NULL AUTO_INCREMENT,
  `rank` tinyint(3) UNSIGNED NULL DEFAULT 0,
  `up_rank` int(10) UNSIGNED NULL DEFAULT 0,
  `lose` int(10) UNSIGNED NULL DEFAULT 0,
  `win` int(10) UNSIGNED NULL DEFAULT 0,
  `wins2` int(10) UNSIGNED NULL DEFAULT 0,
  `wins3` int(10) UNSIGNED NULL DEFAULT 0,
  `wins4` int(10) UNSIGNED NULL DEFAULT 0,
  `wins5` int(10) UNSIGNED NULL DEFAULT 0,
  PRIMARY KEY (`id`) USING BTREE
) ENGINE = MyISAM AUTO_INCREMENT = 8 CHARACTER SET = latin1 COLLATE = latin1_bin ROW_FORMAT = FIXED;

DROP TABLE IF EXISTS `cq_goods`;
cq_goods`;
CREATE TABLE `cq_goods`  (
  `id` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `ownerid` int(4) UNSIGNED NULL DEFAULT 0,
  `itemtype` int(4) UNSIGNED NULL DEFAULT 0,
  `moneytype` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `honor_price` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `compete_place` smallint(5) UNSIGNED NOT NULL DEFAULT 0,
  `riding_price` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `goldenleague_price` int(4) UNSIGNED NOT NULL DEFAULT 0,
  PRIMARY KEY (`id`) USING BTREE,
  INDEX `idx_ownerid`(`ownerid`) USING BTREE
) ENGINE = MyISAM CHARACTER SET = latin1 COLLATE = latin1_bin ROW_FORMAT = FIXED;

DROP TABLE IF EXISTS `cq_greatevent`;
cq_greatevent`;
CREATE TABLE `cq_greatevent`  (
  `id` int(4) UNSIGNED NOT NULL AUTO_INCREMENT,
  `greateventid` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `userid` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `name` varchar(15) CHARACTER SET latin1 COLLATE latin1_bin NOT NULL DEFAULT '',
  `date` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `prize` tinyint(4) UNSIGNED NOT NULL DEFAULT 0,
  PRIMARY KEY (`id`) USING BTREE,
  UNIQUE INDEX `greateventid_userid`(`greateventid`, `userid`) USING BTREE
) ENGINE = MyISAM AUTO_INCREMENT = 1 CHARACTER SET = latin1 COLLATE = latin1_bin ROW_FORMAT = DYNAMIC;

DROP TABLE IF EXISTS `cq_greatevent_timeout`;
cq_greatevent_timeout`;
CREATE TABLE `cq_greatevent_timeout`  (
  `id` int(4) UNSIGNED NOT NULL AUTO_INCREMENT,
  `greateventid` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `userid` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `name` varchar(15) CHARACTER SET latin1 COLLATE latin1_bin NOT NULL DEFAULT '',
  `date` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `prize` tinyint(4) UNSIGNED NOT NULL DEFAULT 0,
  PRIMARY KEY (`id`) USING BTREE,
  UNIQUE INDEX `greateventid_userid`(`greateventid`, `userid`) USING BTREE
) ENGINE = MyISAM AUTO_INCREMENT = 1 CHARACTER SET = latin1 COLLATE = latin1_bin ROW_FORMAT = DYNAMIC;

DROP TABLE IF EXISTS `cq_greateventprize`;
cq_greateventprize`;
CREATE TABLE `cq_greateventprize`  (
  `id` int(4) UNSIGNED NOT NULL AUTO_INCREMENT,
  `rank` smallint(4) UNSIGNED NOT NULL DEFAULT 0,
  `item_type` int(4) UNSIGNED NOT NULL DEFAULT 0,
  PRIMARY KEY (`id`) USING BTREE
) ENGINE = MyISAM AUTO_INCREMENT = 17 CHARACTER SET = latin1 COLLATE = latin1_bin ROW_FORMAT = FIXED;

DROP TABLE IF EXISTS `cq_greateventtype`;
cq_greateventtype`;
CREATE TABLE `cq_greateventtype`  (
  `id` int(4) UNSIGNED NOT NULL AUTO_INCREMENT,
  `type` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `name` varchar(255) CHARACTER SET latin1 COLLATE latin1_bin NOT NULL DEFAULT '',
  `maxcount` smallint(4) UNSIGNED NOT NULL DEFAULT 0,
  `begin` int(3) UNSIGNED NOT NULL DEFAULT 0,
  `end` int(3) UNSIGNED NOT NULL DEFAULT 0,
  PRIMARY KEY (`id`) USING BTREE
) ENGINE = MyISAM AUTO_INCREMENT = 17 CHARACTER SET = latin1 COLLATE = latin1_bin ROW_FORMAT = DYNAMIC;

DROP TABLE IF EXISTS `cq_inner_strength_player`;
cq_inner_strength_player`;
CREATE TABLE `cq_inner_strength_player`  (
  `id` int(10) UNSIGNED NOT NULL AUTO_INCREMENT,
  `player_id` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `type` smallint(5) UNSIGNED NOT NULL DEFAULT 0,
  `level` tinyint(3) UNSIGNED NOT NULL DEFAULT 0,
  `value` tinyint(3) UNSIGNED NOT NULL DEFAULT 0,
  `finish_value` tinyint(3) UNSIGNED NOT NULL DEFAULT 0,
  `status` tinyint(3) UNSIGNED NOT NULL DEFAULT 0,
  `abolish_num` tinyint(3) UNSIGNED NOT NULL DEFAULT 0,
  `max_life` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `physic_attack_new` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `magic_attack` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `physic_defense_new` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `magic_defense` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `final_physic_add` smallint(4) UNSIGNED NOT NULL DEFAULT 0,
  `final_magic_add` smallint(4) UNSIGNED NOT NULL DEFAULT 0,
  `final_physic_reduce` smallint(4) UNSIGNED NOT NULL DEFAULT 0,
  `final_magic_reduce` smallint(4) UNSIGNED NOT NULL DEFAULT 0,
  `physic_crit` smallint(4) UNSIGNED NOT NULL DEFAULT 0,
  `magic_crit` smallint(4) UNSIGNED NOT NULL DEFAULT 0,
  `defense_crit` smallint(4) UNSIGNED NOT NULL DEFAULT 0,
  `smash_rate` smallint(4) UNSIGNED NOT NULL DEFAULT 0,
  `firm_defense_rate` smallint(4) UNSIGNED NOT NULL DEFAULT 0,
  PRIMARY KEY (`id`) USING BTREE
) ENGINE = MyISAM AUTO_INCREMENT = 2 CHARACTER SET = latin1 COLLATE = latin1_bin ROW_FORMAT = FIXED;

DROP TABLE IF EXISTS `cq_inner_strength_rand`;
cq_inner_strength_rand`;
CREATE TABLE `cq_inner_strength_rand`  (
  `inner_strength_no` tinyint(3) UNSIGNED NOT NULL DEFAULT 0,
  `range_no` tinyint(3) UNSIGNED NOT NULL DEFAULT 0,
  `range_rate` int(10) UNSIGNED NOT NULL DEFAULT 0
) ENGINE = MyISAM CHARACTER SET = latin1 COLLATE = latin1_bin ROW_FORMAT = FIXED;

DROP TABLE IF EXISTS `cq_inner_strength_secret`;
cq_inner_strength_secret`;
CREATE TABLE `cq_inner_strength_secret`  (
  `id` int(10) UNSIGNED NOT NULL AUTO_INCREMENT,
  `player_id` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `secret_type` tinyint(3) UNSIGNED NOT NULL DEFAULT 0,
  PRIMARY KEY (`id`) USING BTREE
) ENGINE = MyISAM AUTO_INCREMENT = 1 CHARACTER SET = latin1 COLLATE = latin1_bin ROW_FORMAT = FIXED;

DROP TABLE IF EXISTS `cq_inner_strength_secret_type`;
cq_inner_strength_secret_type`;
CREATE TABLE `cq_inner_strength_secret_type`  (
  `id` tinyint(3) UNSIGNED NOT NULL AUTO_INCREMENT,
  `max_life` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `physic_attack_new` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `magic_attack` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `physic_defense_new` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `magic_defense` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `final_physic_add` smallint(4) UNSIGNED NOT NULL DEFAULT 0,
  `final_magic_add` smallint(4) UNSIGNED NOT NULL DEFAULT 0,
  `final_physic_reduce` smallint(4) UNSIGNED NOT NULL DEFAULT 0,
  `final_magic_reduce` smallint(4) UNSIGNED NOT NULL DEFAULT 0,
  `physic_crit` smallint(4) UNSIGNED NOT NULL DEFAULT 0,
  `magic_crit` smallint(4) UNSIGNED NOT NULL DEFAULT 0,
  `defense_crit` smallint(4) UNSIGNED NOT NULL DEFAULT 0,
  `smash_rate` smallint(4) UNSIGNED NOT NULL DEFAULT 0,
  `firm_defense_rate` smallint(4) UNSIGNED NOT NULL DEFAULT 0,
  PRIMARY KEY (`id`) USING BTREE
) ENGINE = MyISAM AUTO_INCREMENT = 8 CHARACTER SET = latin1 COLLATE = latin1_bin ROW_FORMAT = FIXED;

DROP TABLE IF EXISTS `cq_inner_strength_type_info`;
cq_inner_strength_type_info`;
CREATE TABLE `cq_inner_strength_type_info`  (
  `id` smallint(5) UNSIGNED NOT NULL AUTO_INCREMENT,
  `name` varchar(35) CHARACTER SET latin1 COLLATE latin1_bin NOT NULL DEFAULT '',
  `secret_type` tinyint(3) UNSIGNED NOT NULL DEFAULT 0,
  `abolish_culture` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `rand_type1` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `rand_type2` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `rand_type3` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `max_life` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `physic_attack_new` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `magic_attack` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `physic_defense_new` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `magic_defense` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `final_physic_add` smallint(4) UNSIGNED NOT NULL DEFAULT 0,
  `final_magic_add` smallint(4) UNSIGNED NOT NULL DEFAULT 0,
  `final_physic_reduce` smallint(4) UNSIGNED NOT NULL DEFAULT 0,
  `final_magic_reduce` smallint(4) UNSIGNED NOT NULL DEFAULT 0,
  `physic_crit` smallint(4) UNSIGNED NOT NULL DEFAULT 0,
  `magic_crit` smallint(4) UNSIGNED NOT NULL DEFAULT 0,
  `defense_crit` smallint(4) UNSIGNED NOT NULL DEFAULT 0,
  `smash_rate` smallint(4) UNSIGNED NOT NULL DEFAULT 0,
  `firm_defense_rate` smallint(4) UNSIGNED NOT NULL DEFAULT 0,
  PRIMARY KEY (`id`) USING BTREE
) ENGINE = MyISAM AUTO_INCREMENT = 18 CHARACTER SET = latin1 COLLATE = latin1_bin ROW_FORMAT = DYNAMIC;

DROP TABLE IF EXISTS `cq_inner_strength_type_lev_info`;
cq_inner_strength_type_lev_info`;
CREATE TABLE `cq_inner_strength_type_lev_info`  (
  `id` int(10) UNSIGNED NOT NULL AUTO_INCREMENT,
  `type` smallint(5) UNSIGNED NULL DEFAULT 0,
  `level` tinyint(3) UNSIGNED NULL DEFAULT 0,
  `culture_value` int(10) UNSIGNED NULL DEFAULT 0,
  `max_life` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `physic_attack_new` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `magic_attack` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `physic_defense_new` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `magic_defense` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `final_physic_add` smallint(4) UNSIGNED NOT NULL DEFAULT 0,
  `final_magic_add` smallint(4) UNSIGNED NOT NULL DEFAULT 0,
  `final_physic_reduce` smallint(4) UNSIGNED NOT NULL DEFAULT 0,
  `final_magic_reduce` smallint(4) UNSIGNED NOT NULL DEFAULT 0,
  `physic_crit` smallint(4) UNSIGNED NOT NULL DEFAULT 0,
  `magic_crit` smallint(4) UNSIGNED NOT NULL DEFAULT 0,
  `defense_crit` smallint(4) UNSIGNED NOT NULL DEFAULT 0,
  `smash_rate` smallint(4) UNSIGNED NOT NULL DEFAULT 0,
  `firm_defense_rate` smallint(4) UNSIGNED NOT NULL DEFAULT 0,
  PRIMARY KEY (`id`) USING BTREE,
  UNIQUE INDEX `type_level`(`type`, `level`) USING BTREE
) ENGINE = MyISAM AUTO_INCREMENT = 130 CHARACTER SET = latin1 COLLATE = latin1_bin ROW_FORMAT = FIXED;

DROP TABLE IF EXISTS `cq_instancetype`;
cq_instancetype`;
CREATE TABLE `cq_instancetype`  (
  `id` int(4) UNSIGNED NOT NULL AUTO_INCREMENT,
  `name` varchar(31) CHARACTER SET latin1 COLLATE latin1_bin NOT NULL DEFAULT '',
  `mapid` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `type` tinyint(4) UNSIGNED NOT NULL DEFAULT 0,
  `lev_min` tinyint(4) UNSIGNED NOT NULL DEFAULT 0,
  `lev_max` tinyint(4) UNSIGNED NOT NULL DEFAULT 0,
  `battle_min` smallint(4) UNSIGNED NOT NULL DEFAULT 0,
  `time_limit` smallint(4) UNSIGNED NOT NULL DEFAULT 0,
  `action` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `mapid_return` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `posx_return` smallint(4) UNSIGNED NOT NULL DEFAULT 0,
  `posy_return` smallint(4) UNSIGNED NOT NULL DEFAULT 0,
  PRIMARY KEY (`id`) USING BTREE
) ENGINE = MyISAM AUTO_INCREMENT = 32 CHARACTER SET = latin1 COLLATE = latin1_bin ROW_FORMAT = DYNAMIC;

DROP TABLE IF EXISTS `cq_ippointrecord`;
cq_ippointrecord`;
CREATE TABLE `cq_ippointrecord`  (
  `id` int(4) UNSIGNED NOT NULL AUTO_INCREMENT,
  `account_id` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `ip1` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `ipcode1` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `ippoint1` int(4) NOT NULL DEFAULT 0,
  `iplogintime1` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `ip2` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `ipcode2` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `ippoint2` int(4) NOT NULL DEFAULT 0,
  `iplogintime2` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `ip3` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `ipcode3` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `ippoint3` int(4) NOT NULL DEFAULT 0,
  `iplogintime3` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `ip4` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `ipcode4` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `ippoint4` int(4) NOT NULL DEFAULT 0,
  `iplogintime4` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `ip5` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `ipcode5` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `ippoint5` int(4) NOT NULL DEFAULT 0,
  `iplogintime5` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `lastloginip` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `lastlogintime` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `initialip` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `initialipcode` int(4) UNSIGNED NOT NULL DEFAULT 0,
  PRIMARY KEY (`id`) USING BTREE,
  INDEX `index_account_id`(`account_id`) USING BTREE
) ENGINE = MyISAM AUTO_INCREMENT = 14 CHARACTER SET = latin1 COLLATE = latin1_bin ROW_FORMAT = FIXED;

DROP TABLE IF EXISTS `cq_iptoaddrconfig`;
cq_iptoaddrconfig`;
CREATE TABLE `cq_iptoaddrconfig`  (
  `id` int(4) UNSIGNED NOT NULL AUTO_INCREMENT,
  `ipcode` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `ipbegin` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `ipend` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `country` varchar(24) CHARACTER SET latin1 COLLATE latin1_bin NULL DEFAULT NULL,
  `city` varchar(82) CHARACTER SET latin1 COLLATE latin1_bin NULL DEFAULT NULL,
  PRIMARY KEY (`id`) USING BTREE
) ENGINE = MyISAM AUTO_INCREMENT = 1 CHARACTER SET = latin1 COLLATE = latin1_bin ROW_FORMAT = DYNAMIC;

DROP TABLE IF EXISTS `cq_item`;
cq_item`;
CREATE TABLE `cq_item`  (
  `id` int(4) UNSIGNED NOT NULL AUTO_INCREMENT,
  `type` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `owner_id` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `player_id` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `amount` smallint(2) UNSIGNED NOT NULL DEFAULT 100,
  `amount_limit` smallint(2) UNSIGNED NOT NULL DEFAULT 100,
  `ident` tinyint(1) UNSIGNED NOT NULL DEFAULT 0,
  `position` tinyint(1) UNSIGNED NOT NULL DEFAULT 0,
  `gem1` tinyint(1) UNSIGNED NOT NULL DEFAULT 0,
  `gem2` tinyint(1) UNSIGNED NOT NULL DEFAULT 0,
  `magic1` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `magic2` tinyint(1) UNSIGNED NOT NULL DEFAULT 0,
  `magic3` tinyint(1) UNSIGNED NOT NULL DEFAULT 0,
  `data` int(4) NOT NULL DEFAULT 0,
  `reduce_dmg` tinyint(1) UNSIGNED NOT NULL DEFAULT 0,
  `add_life` tinyint(1) UNSIGNED NOT NULL DEFAULT 0,
  `anti_monster` tinyint(1) UNSIGNED NOT NULL DEFAULT 0,
  `chk_sum` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `plunder` smallint(2) UNSIGNED NOT NULL DEFAULT 0,
  `SpecialFlag` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `color` tinyint(1) UNSIGNED NULL DEFAULT 0,
  `Addlevel_exp` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `monopoly` tinyint(1) NOT NULL DEFAULT 0,
  `syndicate` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `del_time` bigint(4) NOT NULL DEFAULT 0,
  `save_time` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `accumulate_num` int(4) UNSIGNED NOT NULL DEFAULT 1,
  PRIMARY KEY (`id`) USING BTREE,
  INDEX `idx_player_id`(`player_id`) USING BTREE
) ENGINE = MyISAM AUTO_INCREMENT = 5540 CHARACTER SET = latin1 COLLATE = latin1_bin ROW_FORMAT = FIXED;

DROP TABLE IF EXISTS `cq_item_cross`;
cq_item_cross`;
CREATE TABLE `cq_item_cross`  (
  `id` int(10) UNSIGNED NOT NULL AUTO_INCREMENT,
  `item_type_id` int(4) UNSIGNED NOT NULL DEFAULT 0,
  PRIMARY KEY (`id`) USING BTREE
) ENGINE = MyISAM AUTO_INCREMENT = 31 CHARACTER SET = latin1 COLLATE = latin1_bin ROW_FORMAT = FIXED;

DROP TABLE IF EXISTS `cq_item_drop_rule`;
cq_item_drop_rule`;
CREATE TABLE `cq_item_drop_rule`  (
  `id` int(10) UNSIGNED NOT NULL AUTO_INCREMENT,
  `rule_id` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `drop_rate` smallint(10) UNSIGNED NOT NULL DEFAULT 0,
  `equp_type` smallint(10) UNSIGNED NOT NULL DEFAULT 0,
  `min_lv` tinyint(10) UNSIGNED NOT NULL DEFAULT 0,
  `max_lv` tinyint(10) UNSIGNED NOT NULL DEFAULT 0,
  `rate_hole1` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `rate_hole2` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `rate_hole3` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `min_durability` tinyint(10) UNSIGNED NOT NULL DEFAULT 0,
  `max_durability` tinyint(10) UNSIGNED NOT NULL DEFAULT 0,
  PRIMARY KEY (`id`) USING BTREE
) ENGINE = MyISAM AUTO_INCREMENT = 1 CHARACTER SET = latin1 COLLATE = latin1_bin ROW_FORMAT = FIXED;

DROP TABLE IF EXISTS `cq_item_limit`;
cq_item_limit`;
CREATE TABLE `cq_item_limit`  (
  `id` int(10) UNSIGNED NOT NULL AUTO_INCREMENT,
  `type` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `limit_level` int(4) UNSIGNED NOT NULL DEFAULT 0,
  PRIMARY KEY (`id`) USING BTREE
) ENGINE = MyISAM AUTO_INCREMENT = 57 CHARACTER SET = latin1 COLLATE = latin1_bin ROW_FORMAT = FIXED;

DROP TABLE IF EXISTS `cq_item_os_limit`;
cq_item_os_limit`;
CREATE TABLE `cq_item_os_limit`  (
  `id` int(10) UNSIGNED NOT NULL AUTO_INCREMENT,
  `item_type` int(4) UNSIGNED NOT NULL DEFAULT 0,
  PRIMARY KEY (`id`) USING BTREE
) ENGINE = MyISAM AUTO_INCREMENT = 35 CHARACTER SET = latin1 COLLATE = latin1_bin ROW_FORMAT = FIXED;

DROP TABLE IF EXISTS `cq_item_timeout`;
cq_item_timeout`;
CREATE TABLE `cq_item_timeout`  (
  `id` int(4) UNSIGNED NOT NULL AUTO_INCREMENT,
  `type` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `owner_id` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `player_id` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `amount` smallint(2) UNSIGNED NOT NULL DEFAULT 100,
  `amount_limit` smallint(2) UNSIGNED NOT NULL DEFAULT 100,
  `ident` tinyint(1) UNSIGNED NOT NULL DEFAULT 0,
  `position` tinyint(1) UNSIGNED NOT NULL DEFAULT 0,
  `gem1` tinyint(1) UNSIGNED NOT NULL DEFAULT 0,
  `gem2` tinyint(1) UNSIGNED NOT NULL DEFAULT 0,
  `magic1` tinyint(1) UNSIGNED NOT NULL DEFAULT 0,
  `magic2` tinyint(1) UNSIGNED NOT NULL DEFAULT 0,
  `magic3` tinyint(1) UNSIGNED NOT NULL DEFAULT 0,
  `data` int(4) NOT NULL DEFAULT 0,
  `reduce_dmg` tinyint(1) UNSIGNED NOT NULL DEFAULT 0,
  `add_life` tinyint(1) UNSIGNED NOT NULL DEFAULT 0,
  `anti_monster` tinyint(1) UNSIGNED NOT NULL DEFAULT 0,
  `chk_sum` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `plunder` smallint(2) UNSIGNED NOT NULL DEFAULT 0,
  `SpecialFlag` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `color` tinyint(1) UNSIGNED NULL DEFAULT 0,
  `Addlevel_exp` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `monopoly` tinyint(1) NOT NULL DEFAULT 0,
  `syndicate` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `del_time` bigint(4) NOT NULL DEFAULT 0,
  `save_time` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `accumulate_num` int(4) UNSIGNED NOT NULL DEFAULT 0,
  PRIMARY KEY (`id`) USING BTREE,
  INDEX `idx_player_id`(`player_id`) USING BTREE
) ENGINE = MyISAM AUTO_INCREMENT = 1 CHARACTER SET = latin1 COLLATE = latin1_bin ROW_FORMAT = FIXED;

DROP TABLE IF EXISTS `cq_item_value_type`;
cq_item_value_type`;
CREATE TABLE `cq_item_value_type`  (
  `id` int(4) UNSIGNED NOT NULL AUTO_INCREMENT,
  `type` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `data1` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `value1` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `value2` int(4) UNSIGNED NOT NULL DEFAULT 0,
  PRIMARY KEY (`id`) USING BTREE
) ENGINE = MyISAM AUTO_INCREMENT = 2923 CHARACTER SET = latin1 COLLATE = latin1_bin ROW_FORMAT = FIXED;

DROP TABLE IF EXISTS `cq_itemaddition`;
cq_itemaddition`;
CREATE TABLE `cq_itemaddition`  (
  `id` int(10) UNSIGNED NOT NULL AUTO_INCREMENT,
  `typeid` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `level` tinyint(3) UNSIGNED NOT NULL DEFAULT 0,
  `life` smallint(6) NOT NULL DEFAULT 0,
  `attack_max` smallint(6) NOT NULL DEFAULT 0,
  `attack_min` smallint(6) NOT NULL DEFAULT 0,
  `defense` smallint(6) NOT NULL DEFAULT 0,
  `magic_atk` smallint(6) NOT NULL DEFAULT 0,
  `magic_def` smallint(6) NOT NULL DEFAULT 0,
  `dexterity` smallint(6) NOT NULL DEFAULT 0,
  `dodge` smallint(6) NOT NULL DEFAULT 0,
  PRIMARY KEY (`id`) USING BTREE,
  UNIQUE INDEX `typeid`(`typeid`, `level`) USING BTREE
) ENGINE = MyISAM AUTO_INCREMENT = 17998 CHARACTER SET = latin1 COLLATE = latin1_bin ROW_FORMAT = FIXED;

DROP TABLE IF EXISTS `cq_itemstatus`;
cq_itemstatus`;
CREATE TABLE `cq_itemstatus`  (
  `id` int(4) UNSIGNED NOT NULL AUTO_INCREMENT,
  `iditem` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `userid` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `statu` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `lev` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `power1` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `power2` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `realsecs` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `data` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `position` tinyint(3) UNSIGNED NOT NULL DEFAULT 0,
  PRIMARY KEY (`id`) USING BTREE,
  INDEX `idx_iditem`(`iditem`) USING BTREE,
  INDEX `idx_position_userid`(`position`, `userid`) USING BTREE
) ENGINE = MyISAM AUTO_INCREMENT = 31 CHARACTER SET = latin1 COLLATE = latin1_bin ROW_FORMAT = FIXED;

DROP TABLE IF EXISTS `cq_itemstatus_timeout`;
cq_itemstatus_timeout`;
CREATE TABLE `cq_itemstatus_timeout`  (
  `id` int(4) UNSIGNED NOT NULL AUTO_INCREMENT,
  `iditem` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `userid` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `statu` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `lev` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `power1` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `power2` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `realsecs` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `data` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `position` tinyint(3) UNSIGNED NOT NULL DEFAULT 0,
  PRIMARY KEY (`id`) USING BTREE,
  INDEX `idx_iditem`(`iditem`) USING BTREE,
  INDEX `idx_position_userid`(`position`, `userid`) USING BTREE
) ENGINE = MyISAM AUTO_INCREMENT = 1 CHARACTER SET = latin1 COLLATE = latin1_bin ROW_FORMAT = FIXED;

DROP TABLE IF EXISTS `cq_itemtype`;
cq_itemtype`;
CREATE TABLE `cq_itemtype`  (
  `id` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `name` varbinary(35) NOT NULL DEFAULT '',
  `req_profession` tinyint(1) UNSIGNED NOT NULL DEFAULT 0,
  `req_weaponskill` tinyint(1) UNSIGNED NOT NULL DEFAULT 0,
  `req_level` tinyint(1) UNSIGNED NOT NULL DEFAULT 0,
  `req_sex` tinyint(1) UNSIGNED NOT NULL DEFAULT 0,
  `req_force` smallint(2) UNSIGNED NOT NULL DEFAULT 0,
  `req_speed` smallint(2) UNSIGNED NOT NULL DEFAULT 0,
  `req_health` smallint(2) UNSIGNED NOT NULL DEFAULT 0,
  `req_soul` smallint(2) UNSIGNED NOT NULL DEFAULT 0,
  `monopoly` tinyint(1) UNSIGNED NOT NULL DEFAULT 0,
  `weight` smallint(2) UNSIGNED NOT NULL DEFAULT 100,
  `price` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `id_action` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `attack_max` smallint(2) UNSIGNED NOT NULL DEFAULT 0,
  `attack_min` smallint(2) UNSIGNED NOT NULL DEFAULT 0,
  `defense` smallint(2) NOT NULL DEFAULT 0,
  `dexterity` smallint(2) NOT NULL DEFAULT 0,
  `dodge` smallint(2) NOT NULL DEFAULT 0,
  `life` smallint(2) NOT NULL DEFAULT 0,
  `mana` smallint(2) NOT NULL DEFAULT 0,
  `amount` smallint(2) UNSIGNED NOT NULL DEFAULT 1,
  `amount_limit` smallint(2) UNSIGNED NOT NULL DEFAULT 1,
  `ident` tinyint(1) UNSIGNED NOT NULL DEFAULT 0,
  `gem1` tinyint(1) UNSIGNED NOT NULL DEFAULT 0,
  `gem2` tinyint(1) UNSIGNED NOT NULL DEFAULT 0,
  `magic1` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `magic2` tinyint(1) UNSIGNED NOT NULL DEFAULT 0,
  `magic3` tinyint(1) UNSIGNED NOT NULL DEFAULT 0,
  `data` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `magic_atk` smallint(2) UNSIGNED NOT NULL DEFAULT 0,
  `magic_def` smallint(2) UNSIGNED NOT NULL DEFAULT 0,
  `atk_range` smallint(2) UNSIGNED NOT NULL DEFAULT 1,
  `atk_speed` smallint(2) UNSIGNED NOT NULL DEFAULT 800,
  `fray_mode` tinyint(1) UNSIGNED NOT NULL DEFAULT 0,
  `repair_mode` tinyint(1) UNSIGNED NOT NULL DEFAULT 0,
  `type_mask` tinyint(2) UNSIGNED NOT NULL DEFAULT 0,
  `emoney_price` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `emoney_mono_price` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `save_time` int(4) NOT NULL DEFAULT 0,
  `critical_rate` smallint(4) UNSIGNED NOT NULL DEFAULT 0,
  `magic_critical_rate` smallint(4) UNSIGNED NOT NULL DEFAULT 0,
  `anti_critical_rate` smallint(4) UNSIGNED NOT NULL DEFAULT 0,
  `magic_penetration` smallint(2) UNSIGNED NOT NULL DEFAULT 0,
  `shield_block` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `crash_attack` smallint(4) UNSIGNED NOT NULL DEFAULT 0,
  `stable_defence` smallint(4) UNSIGNED NOT NULL DEFAULT 0,
  `accumulate_limit` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `attr_metal` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `attr_wood` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `attr_water` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `attr_fire` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `attr_earth` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `type_desc` varbinary(50) NULL DEFAULT NULL,
  `item_desc` varbinary(200) NULL DEFAULT NULL,
  `color_index` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `godsoullev` tinyint(1) UNSIGNED NOT NULL DEFAULT 0,
  `meteor_count` tinyint(1) UNSIGNED NOT NULL DEFAULT 0,
  `recover_energy` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `auction_class` smallint(4) UNSIGNED NOT NULL DEFAULT 0,
  `auction_deposit` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `final_dmg_add` smallint(5) UNSIGNED NOT NULL DEFAULT 0,
  `final_dmg_add_mgc` smallint(5) UNSIGNED NOT NULL DEFAULT 0,
  `final_dmg_reduce` smallint(5) UNSIGNED NOT NULL DEFAULT 0,
  `final_dmg_reduce_mgc` smallint(5) UNSIGNED NOT NULL DEFAULT 0,
  `sort` int(4) UNSIGNED NOT NULL DEFAULT 0,
  PRIMARY KEY (`id`) USING BTREE
) ENGINE = MyISAM CHARACTER SET = latin1 COLLATE = latin1_bin ROW_FORMAT = DYNAMIC;

DROP TABLE IF EXISTS `cq_jail_log`;
cq_jail_log`;
CREATE TABLE `cq_jail_log`  (
  `id` int(4) UNSIGNED NOT NULL AUTO_INCREMENT,
  `user_name` varbinary(15) NOT NULL DEFAULT '',
  `time` int(8) UNSIGNED NOT NULL DEFAULT 0,
  `reason` varbinary(31) NOT NULL DEFAULT '',
  PRIMARY KEY (`id`) USING BTREE
) ENGINE = MyISAM AUTO_INCREMENT = 1 CHARACTER SET = latin1 COLLATE = latin1_bin ROW_FORMAT = DYNAMIC;

DROP TABLE IF EXISTS `cq_jianghu_attrib_rand`;
cq_jianghu_attrib_rand`;
CREATE TABLE `cq_jianghu_attrib_rand`  (
  `id` int(10) UNSIGNED NOT NULL AUTO_INCREMENT,
  `power_level` tinyint(3) UNSIGNED NOT NULL DEFAULT 0,
  `power_attrib` tinyint(3) UNSIGNED NOT NULL DEFAULT 0,
  `rate` smallint(5) UNSIGNED NOT NULL DEFAULT 0,
  PRIMARY KEY (`id`) USING BTREE
) ENGINE = MyISAM AUTO_INCREMENT = 68 CHARACTER SET = latin1 COLLATE = latin1_bin ROW_FORMAT = FIXED;

DROP TABLE IF EXISTS `cq_jianghu_caltivate_condition`;
cq_jianghu_caltivate_condition`;
CREATE TABLE `cq_jianghu_caltivate_condition`  (
  `id` int(10) UNSIGNED NOT NULL AUTO_INCREMENT,
  `power_level` tinyint(4) UNSIGNED NULL DEFAULT 0,
  `need_power_value` smallint(6) UNSIGNED NULL DEFAULT 0,
  `need_caltivate_value` int(11) UNSIGNED NULL DEFAULT 0,
  `crit_cost` int(11) UNSIGNED NULL DEFAULT 0,
  `high_crit_cost` int(11) UNSIGNED NULL DEFAULT 0,
  `keep_cost` smallint(4) UNSIGNED NULL DEFAULT 0,
  PRIMARY KEY (`id`) USING BTREE
) ENGINE = MyISAM AUTO_INCREMENT = 10 CHARACTER SET = latin1 COLLATE = latin1_bin ROW_FORMAT = FIXED;

DROP TABLE IF EXISTS `cq_jianghu_caltivate_times`;
cq_jianghu_caltivate_times`;
CREATE TABLE `cq_jianghu_caltivate_times`  (
  `id` int(10) UNSIGNED NOT NULL AUTO_INCREMENT,
  `player_id` int(10) UNSIGNED NULL DEFAULT 0,
  `free_times` tinyint(4) UNSIGNED NULL DEFAULT 0,
  `paid_times` int(4) UNSIGNED NULL DEFAULT 0,
  PRIMARY KEY (`id`) USING BTREE,
  UNIQUE INDEX `u_player_id`(`player_id`) USING BTREE
) ENGINE = MyISAM AUTO_INCREMENT = 5 CHARACTER SET = latin1 COLLATE = latin1_bin ROW_FORMAT = FIXED;

DROP TABLE IF EXISTS `cq_jianghu_player`;
cq_jianghu_player`;
CREATE TABLE `cq_jianghu_player`  (
  `id` int(10) UNSIGNED NOT NULL AUTO_INCREMENT,
  `player_id` int(10) UNSIGNED NULL DEFAULT 0,
  `enter_jianghu_flag` tinyint(3) UNSIGNED NULL DEFAULT 0,
  `gongfu_name` varbinary(50) NULL DEFAULT 0,
  `power_level` tinyint(3) UNSIGNED NULL DEFAULT 0,
  `genuine_qi_level` tinyint(3) UNSIGNED NULL DEFAULT 0,
  `free_caltivate_param` int(10) UNSIGNED NULL DEFAULT 0,
  `total_power_value` int(10) UNSIGNED NULL DEFAULT 0,
  PRIMARY KEY (`id`) USING BTREE,
  UNIQUE INDEX `u_player_id`(`player_id`) USING BTREE
) ENGINE = MyISAM AUTO_INCREMENT = 3 CHARACTER SET = latin1 COLLATE = latin1_bin ROW_FORMAT = DYNAMIC;

DROP TABLE IF EXISTS `cq_jianghu_player_power`;
cq_jianghu_player_power`;
CREATE TABLE `cq_jianghu_player_power`  (
  `id` int(10) UNSIGNED NOT NULL AUTO_INCREMENT,
  `player_id` int(10) UNSIGNED NULL DEFAULT 0,
  `level` tinyint(10) UNSIGNED NULL DEFAULT 0,
  `type1` tinyint(4) UNSIGNED NULL DEFAULT 0,
  `quality1` tinyint(4) UNSIGNED NULL DEFAULT 0,
  `type2` tinyint(4) UNSIGNED NULL DEFAULT 0,
  `quality2` tinyint(4) UNSIGNED NULL DEFAULT 0,
  `type3` tinyint(4) UNSIGNED NULL DEFAULT 0,
  `quality3` tinyint(4) UNSIGNED NULL DEFAULT 0,
  `type4` tinyint(4) UNSIGNED NULL DEFAULT 0,
  `quality4` tinyint(4) UNSIGNED NULL DEFAULT 0,
  `type5` tinyint(4) UNSIGNED NULL DEFAULT 0,
  `quality5` tinyint(4) UNSIGNED NULL DEFAULT 0,
  `type6` tinyint(4) UNSIGNED NULL DEFAULT 0,
  `quality6` tinyint(4) UNSIGNED NULL DEFAULT 0,
  `type7` tinyint(4) UNSIGNED NULL DEFAULT 0,
  `quality7` tinyint(4) UNSIGNED NULL DEFAULT 0,
  `type8` tinyint(4) UNSIGNED NULL DEFAULT 0,
  `quality8` tinyint(4) UNSIGNED NULL DEFAULT 0,
  `type9` tinyint(4) UNSIGNED NULL DEFAULT 0,
  `quality9` tinyint(4) UNSIGNED NULL DEFAULT 0,
  PRIMARY KEY (`id`) USING BTREE,
  INDEX `idx_player_level`(`player_id`, `level`) USING BTREE
) ENGINE = MyISAM AUTO_INCREMENT = 30 CHARACTER SET = latin1 COLLATE = latin1_bin ROW_FORMAT = FIXED;

DROP TABLE IF EXISTS `cq_jianghu_power_effect`;
cq_jianghu_power_effect`;
CREATE TABLE `cq_jianghu_power_effect`  (
  `id` int(10) UNSIGNED NOT NULL AUTO_INCREMENT,
  `type` tinyint(3) UNSIGNED NULL DEFAULT 0,
  `quality` tinyint(3) UNSIGNED NULL DEFAULT 0,
  `attrib_value` smallint(5) UNSIGNED NULL DEFAULT 0,
  PRIMARY KEY (`id`) USING BTREE
) ENGINE = MyISAM AUTO_INCREMENT = 91 CHARACTER SET = latin1 COLLATE = latin1_bin ROW_FORMAT = FIXED;

DROP TABLE IF EXISTS `cq_jianghu_quality_rand`;
cq_jianghu_quality_rand`;
CREATE TABLE `cq_jianghu_quality_rand`  (
  `id` int(10) UNSIGNED NOT NULL AUTO_INCREMENT,
  `power_level` tinyint(4) UNSIGNED NULL DEFAULT 0,
  `power_quality` tinyint(4) UNSIGNED NULL DEFAULT 0,
  `common_rate` smallint(6) UNSIGNED NULL DEFAULT 0,
  `crit_rate` smallint(6) UNSIGNED NULL DEFAULT 0,
  `high_crit_rate` smallint(6) UNSIGNED NULL DEFAULT 0,
  PRIMARY KEY (`id`) USING BTREE
) ENGINE = MyISAM AUTO_INCREMENT = 55 CHARACTER SET = latin1 COLLATE = latin1_bin ROW_FORMAT = FIXED;

DROP TABLE IF EXISTS `cq_killmonster`;
cq_killmonster`;
CREATE TABLE `cq_killmonster`  (
  `id` int(10) UNSIGNED ZEROFILL NOT NULL AUTO_INCREMENT,
  `player_id` int(4) UNSIGNED ZEROFILL NOT NULL DEFAULT 0000,
  `event_type` int(4) UNSIGNED ZEROFILL NOT NULL DEFAULT 0000,
  `data_type` int(4) UNSIGNED ZEROFILL NOT NULL DEFAULT 0000,
  `data` int(4) UNSIGNED ZEROFILL NOT NULL DEFAULT 0000,
  `timestamp` int(4) UNSIGNED NOT NULL DEFAULT 0,
  PRIMARY KEY (`id`) USING BTREE,
  INDEX `player_id`(`player_id`) USING BTREE
) ENGINE = MyISAM AUTO_INCREMENT = 163 CHARACTER SET = latin1 COLLATE = latin1_bin ROW_FORMAT = FIXED;

DROP TABLE IF EXISTS `cq_league`;
cq_league`;
CREATE TABLE `cq_league`  (
  `id` int(10) UNSIGNED NOT NULL AUTO_INCREMENT,
  `name` varchar(50) CHARACTER SET latin1 COLLATE latin1_bin NULL DEFAULT NULL,
  `leader_syn` int(10) UNSIGNED NULL DEFAULT 0,
  `country_date` int(10) UNSIGNED NULL DEFAULT 0,
  `title` varchar(10) CHARACTER SET latin1 COLLATE latin1_bin NULL DEFAULT NULL,
  `money` bigint(10) UNSIGNED NULL DEFAULT 0,
  `announcement` varchar(257) CHARACTER SET latin1 COLLATE latin1_bin NULL DEFAULT NULL,
  `declaration` varchar(257) CHARACTER SET latin1 COLLATE latin1_bin NULL DEFAULT NULL,
  `name_flag` tinyint(4) UNSIGNED NULL DEFAULT 0,
  `brick` int(10) UNSIGNED NOT NULL DEFAULT 0,
  PRIMARY KEY (`id`) USING BTREE
) ENGINE = MyISAM AUTO_INCREMENT = 1 CHARACTER SET = latin1 COLLATE = latin1_bin ROW_FORMAT = DYNAMIC;

DROP TABLE IF EXISTS `cq_league_contribute`;
cq_league_contribute`;
CREATE TABLE `cq_league_contribute`  (
  `level` int(4) UNSIGNED NOT NULL,
  `need_contribute` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `official_name` varchar(15) CHARACTER SET latin1 COLLATE latin1_bin NOT NULL,
  PRIMARY KEY (`level`) USING BTREE
) ENGINE = MyISAM CHARACTER SET = latin1 COLLATE = latin1_bin ROW_FORMAT = DYNAMIC;

DROP TABLE IF EXISTS `cq_league_info`;
cq_league_info`;
CREATE TABLE `cq_league_info`  (
  `id` int(10) NOT NULL AUTO_INCREMENT,
  `idserver` int(10) NOT NULL DEFAULT 0,
  `idleague` int(10) NOT NULL DEFAULT 0,
  `amount` int(10) NOT NULL DEFAULT 0,
  `country_date` int(10) NOT NULL DEFAULT 0,
  `league_name` varchar(50) CHARACTER SET latin1 COLLATE latin1_bin NULL DEFAULT NULL,
  `leader_name` varchar(50) CHARACTER SET latin1 COLLATE latin1_bin NULL DEFAULT NULL,
  `title` varchar(50) CHARACTER SET latin1 COLLATE latin1_bin NULL DEFAULT NULL,
  PRIMARY KEY (`id`) USING BTREE
) ENGINE = MyISAM AUTO_INCREMENT = 1 CHARACTER SET = latin1 COLLATE = latin1_bin ROW_FORMAT = DYNAMIC;

DROP TABLE IF EXISTS `cq_league_member`;
cq_league_member`;
CREATE TABLE `cq_league_member`  (
  `id` int(10) NOT NULL AUTO_INCREMENT,
  `user_id` int(10) NULL DEFAULT 0,
  `league_id` int(10) NULL DEFAULT 0,
  `salary_flag` tinyint(4) NULL DEFAULT 0,
  PRIMARY KEY (`id`) USING BTREE
) ENGINE = MyISAM AUTO_INCREMENT = 1 CHARACTER SET = latin1 COLLATE = latin1_bin ROW_FORMAT = FIXED;

DROP TABLE IF EXISTS `cq_league_token`;
cq_league_token`;
CREATE TABLE `cq_league_token`  (
  `id` int(10) UNSIGNED NOT NULL AUTO_INCREMENT,
  `league_id` int(10) UNSIGNED NULL DEFAULT 0,
  `token_type` int(10) NULL DEFAULT 0,
  `times` tinyint(4) UNSIGNED NULL DEFAULT 0,
  `last_use_time` int(10) UNSIGNED NULL DEFAULT 0,
  PRIMARY KEY (`id`) USING BTREE
) ENGINE = MyISAM AUTO_INCREMENT = 1 CHARACTER SET = latin1 COLLATE = latin1_bin ROW_FORMAT = FIXED;

DROP TABLE IF EXISTS `cq_leaveword`;
cq_leaveword`;
CREATE TABLE `cq_leaveword`  (
  `id` int(4) UNSIGNED NOT NULL AUTO_INCREMENT,
  `recv_id` int(4) UNSIGNED NULL DEFAULT 0,
  `send_name` varbinary(15) NOT NULL DEFAULT 'unknown',
  `time` varchar(15) CHARACTER SET latin1 COLLATE latin1_bin NOT NULL DEFAULT '00000000000000',
  `words` varbinary(255) NOT NULL DEFAULT 'undefined',
  `lookface` int(6) UNSIGNED NOT NULL DEFAULT 0,
  `type` tinyint(1) UNSIGNED NOT NULL DEFAULT 0,
  PRIMARY KEY (`id`) USING BTREE,
  INDEX `idx_time`(`time`) USING BTREE,
  INDEX `idx_recv_id`(`recv_id`) USING BTREE
) ENGINE = MyISAM AUTO_INCREMENT = 1 CHARACTER SET = latin1 COLLATE = latin1_bin ROW_FORMAT = DYNAMIC;

DROP TABLE IF EXISTS `cq_levexp`;
cq_levexp`;
CREATE TABLE `cq_levexp`  (
  `level` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `exp` bigint(4) NOT NULL DEFAULT 0,
  `up_lev_time` int(4) NOT NULL DEFAULT 0,
  `mentor_uplev_time` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `id` int(4) UNSIGNED NOT NULL AUTO_INCREMENT,
  `type` tinyint(3) UNSIGNED NOT NULL DEFAULT 0,
  PRIMARY KEY (`id`) USING BTREE
) ENGINE = MyISAM AUTO_INCREMENT = 196 CHARACTER SET = latin1 COLLATE = latin1_bin ROW_FORMAT = FIXED;

DROP TABLE IF EXISTS `cq_log`;
cq_log`;
CREATE TABLE `cq_log`  (
  `id` int(4) UNSIGNED NOT NULL AUTO_INCREMENT,
  `user_id` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `task_id` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `profession` tinyint(1) UNSIGNED NOT NULL DEFAULT 0,
  `level` tinyint(1) UNSIGNED NOT NULL DEFAULT 0,
  `time` int(4) UNSIGNED NOT NULL DEFAULT 0,
  PRIMARY KEY (`id`) USING BTREE
) ENGINE = MyISAM AUTO_INCREMENT = 49 CHARACTER SET = latin1 COLLATE = latin1_bin ROW_FORMAT = FIXED;

DROP TABLE IF EXISTS `cq_lottery`;
cq_lottery`;
CREATE TABLE `cq_lottery`  (
  `id` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `type` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `rank` tinyint(1) UNSIGNED NOT NULL DEFAULT 0,
  `chance` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `prize_name` char(32) CHARACTER SET latin1 COLLATE latin1_bin NOT NULL DEFAULT '',
  `prize_item` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `color` tinyint(1) UNSIGNED NOT NULL DEFAULT 0,
  `hole_num` tinyint(1) UNSIGNED NOT NULL DEFAULT 0,
  `addition_lev` tinyint(1) UNSIGNED NOT NULL DEFAULT 0,
  PRIMARY KEY (`id`) USING BTREE
) ENGINE = MyISAM CHARACTER SET = latin1 COLLATE = latin1_bin ROW_FORMAT = FIXED;

DROP TABLE IF EXISTS `cq_magic`;
cq_magic`;
CREATE TABLE `cq_magic`  (
  `id` int(4) UNSIGNED NOT NULL AUTO_INCREMENT,
  `ownerid` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `type` smallint(4) UNSIGNED NOT NULL DEFAULT 0,
  `level` smallint(4) UNSIGNED NOT NULL DEFAULT 0,
  `exp` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `unlearn` tinyint(1) UNSIGNED NOT NULL DEFAULT 0,
  `old_level` smallint(4) UNSIGNED NOT NULL DEFAULT 0,
  `current_effect_type` tinyint(3) UNSIGNED NOT NULL DEFAULT 0,
  `available_effect_type` int(10) UNSIGNED NOT NULL DEFAULT 1,
  `effect_monopoly` int(10) UNSIGNED ZEROFILL NOT NULL DEFAULT 0000000000,
  `effect_exorbitant` int(10) UNSIGNED ZEROFILL NOT NULL DEFAULT 0000000000,
  PRIMARY KEY (`id`) USING BTREE,
  INDEX `user_magic`(`ownerid`) USING BTREE
) ENGINE = MyISAM AUTO_INCREMENT = 681 CHARACTER SET = latin1 COLLATE = latin1_bin ROW_FORMAT = FIXED;

DROP TABLE IF EXISTS `cq_magic_20030516`;
cq_magic_20030516`;
CREATE TABLE `cq_magic_20030516`  (
  `id` int(4) UNSIGNED NOT NULL AUTO_INCREMENT,
  `ownerid` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `type` smallint(4) UNSIGNED NOT NULL DEFAULT 0,
  `level` smallint(4) UNSIGNED NOT NULL DEFAULT 0,
  `exp` int(4) UNSIGNED NOT NULL DEFAULT 0,
  PRIMARY KEY (`id`) USING BTREE,
  INDEX `user_magic`(`ownerid`) USING BTREE
) ENGINE = MyISAM AUTO_INCREMENT = 1 CHARACTER SET = latin1 COLLATE = latin1_bin ROW_FORMAT = FIXED;

DROP TABLE IF EXISTS `cq_magic_timeout`;
cq_magic_timeout`;
CREATE TABLE `cq_magic_timeout`  (
  `id` int(4) UNSIGNED NOT NULL AUTO_INCREMENT,
  `ownerid` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `type` smallint(4) UNSIGNED NOT NULL DEFAULT 0,
  `level` smallint(4) UNSIGNED NOT NULL DEFAULT 0,
  `exp` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `unlearn` tinyint(1) UNSIGNED NOT NULL DEFAULT 0,
  `old_level` smallint(4) UNSIGNED NOT NULL DEFAULT 0,
  `current_effect_type` tinyint(3) UNSIGNED NOT NULL DEFAULT 0,
  `available_effect_type` int(10) UNSIGNED NOT NULL DEFAULT 1,
  `effect_monopoly` int(10) UNSIGNED ZEROFILL NOT NULL DEFAULT 0000000000,
  `effect_exorbitant` int(10) UNSIGNED ZEROFILL NOT NULL DEFAULT 0000000000,
  PRIMARY KEY (`id`) USING BTREE,
  INDEX `user_magic`(`ownerid`) USING BTREE
) ENGINE = MyISAM AUTO_INCREMENT = 1 CHARACTER SET = latin1 COLLATE = latin1_bin ROW_FORMAT = FIXED;

DROP TABLE IF EXISTS `cq_magictype`;
cq_magictype`;
CREATE TABLE `cq_magictype`  (
  `id` int(4) UNSIGNED NOT NULL AUTO_INCREMENT,
  `type` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `sort` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `name` varchar(35) CHARACTER SET latin1 COLLATE latin1_bin NOT NULL DEFAULT '',
  `crime` tinyint(1) UNSIGNED NOT NULL DEFAULT 0,
  `ground` tinyint(1) UNSIGNED NOT NULL DEFAULT 0,
  `multi` tinyint(1) UNSIGNED NOT NULL DEFAULT 0,
  `target` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `level` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `use_mp` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `power` int(4) NOT NULL DEFAULT 0,
  `intone_speed` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `percent` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `step_secs` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `range` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `distance` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `status` int(4) NOT NULL DEFAULT 0,
  `need_prof` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `need_exp` int(4) NOT NULL DEFAULT 0,
  `need_time` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `need_level` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `use_xp` tinyint(1) UNSIGNED NOT NULL DEFAULT 0,
  `weapon_subtype` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `active_times` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `auto_active` tinyint(1) UNSIGNED NOT NULL DEFAULT 0,
  `floor_attr` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `auto_learn` tinyint(1) UNSIGNED NOT NULL DEFAULT 0,
  `learn_level` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `drop_weapon` tinyint(1) UNSIGNED NOT NULL DEFAULT 0,
  `use_ep` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `weapon_hit` tinyint(1) UNSIGNED NOT NULL DEFAULT 0,
  `use_item` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `next_magic` int(4) UNSIGNED NULL DEFAULT 0,
  `delay_ms` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `use_item_num` int(4) UNSIGNED NOT NULL DEFAULT 1,
  `status_data0` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `status_data1` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `status_data2` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `attr_type` tinyint(3) UNSIGNED NOT NULL DEFAULT 0,
  `attr_power` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `target_num` tinyint(3) UNSIGNED NOT NULL DEFAULT 0,
  `need_ast_prof` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `need_ast_prof_rank` tinyint(3) UNSIGNED NOT NULL DEFAULT 0,
  `width` int(4) UNSIGNED NULL DEFAULT 0,
  `data` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `dur_time` int(10) UNSIGNED NULL DEFAULT 0,
  `atk_interval` int(10) UNSIGNED NULL DEFAULT 0,
  `coldtime` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `req_uplevtime` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `first_magic` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `combo_delay` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `combo_timeout` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `magictypeex_id` int(4) UNSIGNED NOT NULL DEFAULT 0,
  PRIMARY KEY (`id`) USING BTREE
) ENGINE = MyISAM AUTO_INCREMENT = 12481 CHARACTER SET = latin1 COLLATE = latin1_bin ROW_FORMAT = DYNAMIC;

DROP TABLE IF EXISTS `cq_magictype_ex`;
cq_magictype_ex`;
CREATE TABLE `cq_magictype_ex`  (
  `id` int(4) NOT NULL AUTO_INCREMENT,
  `type` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `data1` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `data2` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `data3` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `data4` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `data5` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `data6` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `data7` int(4) UNSIGNED NOT NULL DEFAULT 0,
  PRIMARY KEY (`id`) USING BTREE
) ENGINE = MyISAM AUTO_INCREMENT = 5 CHARACTER SET = latin1 COLLATE = latin1_bin ROW_FORMAT = FIXED;

DROP TABLE IF EXISTS `cq_magictypeop`;
cq_magictypeop`;
CREATE TABLE `cq_magictypeop`  (
  `id` int(4) NOT NULL AUTO_INCREMENT,
  `rebirth_time` int(1) NOT NULL DEFAULT 0,
  `profession_ago` int(2) NOT NULL DEFAULT 0,
  `profession_now` int(2) NOT NULL DEFAULT 0,
  `magictype_op` int(1) NOT NULL DEFAULT 0,
  `skill_1` int(4) NOT NULL DEFAULT 0,
  `skill_2` int(4) NOT NULL DEFAULT 0,
  `skill_3` int(4) NOT NULL DEFAULT 0,
  `skill_4` int(4) NOT NULL DEFAULT 0,
  `skill_5` int(4) NOT NULL DEFAULT 0,
  `skill_6` int(4) NOT NULL DEFAULT 0,
  `skill_7` int(4) NOT NULL DEFAULT 0,
  `skill_8` int(4) NOT NULL DEFAULT 0,
  `skill_9` int(4) NOT NULL DEFAULT 0,
  `skill_10` int(4) NOT NULL DEFAULT 0,
  `skill_11` int(4) NOT NULL DEFAULT 0,
  `skill_12` int(4) NOT NULL DEFAULT 0,
  `skill_13` int(4) NOT NULL DEFAULT 0,
  `skill_14` int(4) NOT NULL DEFAULT 0,
  `skill_15` int(4) NOT NULL DEFAULT 0,
  `skill_16` int(4) NOT NULL DEFAULT 0,
  `skill_17` int(4) NOT NULL DEFAULT 0,
  `skill_18` int(4) NOT NULL DEFAULT 0,
  `skill_19` int(4) NOT NULL DEFAULT 0,
  `skill_20` int(4) NOT NULL DEFAULT 0,
  `skill_21` int(4) NOT NULL DEFAULT 0,
  `skill_22` int(4) NOT NULL DEFAULT 0,
  `skill_23` int(4) NOT NULL DEFAULT 0,
  `skill_24` int(4) NOT NULL DEFAULT 0,
  `skill_25` int(4) NOT NULL DEFAULT 0,
  `skill_26` int(4) NOT NULL DEFAULT 0,
  `skill_27` int(4) NOT NULL DEFAULT 0,
  `skill_28` int(4) NOT NULL DEFAULT 0,
  `skill_29` int(4) NOT NULL DEFAULT 0,
  `skill_30` int(4) NOT NULL DEFAULT 0,
  `skill_31` int(4) NOT NULL DEFAULT 0,
  `skill_32` int(4) NOT NULL DEFAULT 0,
  `skill_33` int(4) NOT NULL DEFAULT 0,
  `skill_34` int(4) NOT NULL DEFAULT 0,
  `skill_35` int(4) NOT NULL DEFAULT 0,
  `skill_36` int(4) NOT NULL DEFAULT 0,
  `skill_37` int(4) NOT NULL DEFAULT 0,
  `skill_38` int(4) NOT NULL DEFAULT 0,
  `skill_39` int(4) NOT NULL DEFAULT 0,
  `skill_40` int(4) NOT NULL DEFAULT 0,
  `skill_41` int(4) NOT NULL DEFAULT 0,
  `skill_42` int(4) NOT NULL DEFAULT 0,
  `skill_43` int(4) NOT NULL DEFAULT 0,
  `skill_44` int(4) NOT NULL DEFAULT 0,
  `skill_45` int(4) NOT NULL DEFAULT 0,
  `skill_46` int(4) NOT NULL DEFAULT 0,
  `skill_47` int(4) NOT NULL DEFAULT 0,
  `skill_48` int(4) NOT NULL DEFAULT 0,
  `skill_49` int(4) NOT NULL DEFAULT 0,
  `skill_50` int(4) NOT NULL DEFAULT 0,
  `skill_51` int(4) NOT NULL DEFAULT 0,
  `skill_52` int(4) NOT NULL DEFAULT 0,
  `skill_53` int(4) NOT NULL DEFAULT 0,
  `skill_54` int(4) NOT NULL DEFAULT 0,
  `skill_55` int(4) NOT NULL DEFAULT 0,
  `skill_56` int(4) NOT NULL DEFAULT 0,
  `skill_57` int(4) NOT NULL DEFAULT 0,
  `skill_58` int(4) NOT NULL DEFAULT 0,
  `skill_59` int(4) NOT NULL DEFAULT 0,
  `skill_60` int(4) NOT NULL DEFAULT 0,
  PRIMARY KEY (`id`) USING BTREE
) ENGINE = MyISAM AUTO_INCREMENT = 648 CHARACTER SET = latin1 COLLATE = latin1_bin ROW_FORMAT = FIXED;

DROP TABLE IF EXISTS `cq_mail`;
cq_mail`;
CREATE TABLE `cq_mail`  (
  `id` int(4) UNSIGNED NOT NULL AUTO_INCREMENT,
  `receiver_id` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `Sender_name` varbinary(32) NOT NULL DEFAULT '',
  `title` varbinary(32) NULL DEFAULT NULL,
  `content` varbinary(255) NULL DEFAULT NULL,
  `money` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `emoney` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `action` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `expiration_date` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `item_id` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `emoney_record_type` tinyint(1) UNSIGNED NOT NULL DEFAULT 0,
  PRIMARY KEY (`id`) USING BTREE,
  INDEX `idx_receiver_id`(`receiver_id`) USING BTREE
) ENGINE = MyISAM AUTO_INCREMENT = 24 CHARACTER SET = latin1 COLLATE = latin1_bin ROW_FORMAT = DYNAMIC;

DROP TABLE IF EXISTS `cq_map`;
cq_map`;
CREATE TABLE `cq_map`  (
  `id` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `name` varchar(35) CHARACTER SET latin1 COLLATE latin1_bin NULL DEFAULT 'undefined',
  `describe_text` varchar(127) CHARACTER SET latin1 COLLATE latin1_bin NULL DEFAULT NULL,
  `mapdoc` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `type` bigint(4) UNSIGNED NOT NULL DEFAULT 0,
  `owner_id` int(4) UNSIGNED NULL DEFAULT 0,
  `mapgroup` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `idxserver` int(4) NULL DEFAULT -1,
  `weather` int(4) UNSIGNED NULL DEFAULT 0,
  `bgmusic` int(4) UNSIGNED NULL DEFAULT 0,
  `bgmusic_show` int(4) UNSIGNED NULL DEFAULT 0,
  `portal0_x` int(4) UNSIGNED NULL DEFAULT 0,
  `portal0_y` int(4) UNSIGNED NULL DEFAULT 0,
  `reborn_map` int(4) UNSIGNED NULL DEFAULT 0,
  `reborn_portal` int(4) UNSIGNED NULL DEFAULT 0,
  `res_lev` tinyint(3) UNSIGNED NOT NULL DEFAULT 0,
  `owner_type` tinyint(3) UNSIGNED NOT NULL DEFAULT 0,
  `link_map` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `link_x` smallint(4) UNSIGNED NOT NULL DEFAULT 0,
  `link_y` smallint(4) UNSIGNED NOT NULL DEFAULT 0,
  `del_flag` tinyint(3) UNSIGNED NOT NULL DEFAULT 0,
  `color` int(4) UNSIGNED NULL DEFAULT 4294967295,
  PRIMARY KEY (`id`) USING BTREE
) ENGINE = MyISAM CHARACTER SET = latin1 COLLATE = latin1_bin ROW_FORMAT = DYNAMIC;

DROP TABLE IF EXISTS `cq_meedrecord`;
cq_meedrecord`;
CREATE TABLE `cq_meedrecord`  (
  `id` int(4) UNSIGNED NOT NULL AUTO_INCREMENT,
  `synid` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `userid` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `type` tinyint(4) UNSIGNED NOT NULL DEFAULT 0,
  `point` smallint(4) UNSIGNED NULL DEFAULT 0,
  `money` int(4) UNSIGNED NULL DEFAULT 0,
  `emoney` int(4) UNSIGNED NULL DEFAULT 0,
  PRIMARY KEY (`id`) USING BTREE,
  INDEX `idx_synid`(`synid`) USING BTREE
) ENGINE = MyISAM AUTO_INCREMENT = 1 CHARACTER SET = latin1 COLLATE = latin1_bin ROW_FORMAT = FIXED;

DROP TABLE IF EXISTS `cq_minectrl`;
cq_minectrl`;
CREATE TABLE `cq_minectrl`  (
  `id` int(10) UNSIGNED NOT NULL AUTO_INCREMENT,
  `map_id` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `item_id` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `percent` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `interval` smallint(5) UNSIGNED NOT NULL DEFAULT 0,
  `amount_limit` smallint(5) UNSIGNED NOT NULL DEFAULT 0,
  PRIMARY KEY (`id`) USING BTREE
) ENGINE = MyISAM AUTO_INCREMENT = 504 CHARACTER SET = latin1 COLLATE = latin1_bin ROW_FORMAT = FIXED;

DROP TABLE IF EXISTS `cq_monitor_keyword`;
cq_monitor_keyword`;
CREATE TABLE `cq_monitor_keyword`  (
  `id` int(10) UNSIGNED NOT NULL AUTO_INCREMENT,
  `keyword` varchar(16) CHARACTER SET latin1 COLLATE latin1_bin NOT NULL DEFAULT '',
  PRIMARY KEY (`id`) USING BTREE
) ENGINE = MyISAM AUTO_INCREMENT = 1 CHARACTER SET = latin1 COLLATE = latin1_bin ROW_FORMAT = DYNAMIC;

DROP TABLE IF EXISTS `cq_monster_cluster`;
cq_monster_cluster`;
CREATE TABLE `cq_monster_cluster`  (
  `id` int(10) UNSIGNED NOT NULL AUTO_INCREMENT,
  `monster0` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `ratio0` tinyint(3) UNSIGNED NOT NULL DEFAULT 0,
  `monster1` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `ratio1` tinyint(3) UNSIGNED NOT NULL DEFAULT 0,
  `monster2` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `ratio2` tinyint(3) UNSIGNED NOT NULL DEFAULT 0,
  `monster3` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `ratio3` tinyint(3) UNSIGNED NOT NULL DEFAULT 0,
  `monster4` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `ratio4` tinyint(3) UNSIGNED NOT NULL DEFAULT 0,
  `monster5` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `ratio5` tinyint(3) UNSIGNED NOT NULL DEFAULT 0,
  `monster6` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `ratio6` tinyint(3) UNSIGNED NOT NULL DEFAULT 0,
  `monster7` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `ratio7` tinyint(3) UNSIGNED NOT NULL DEFAULT 0,
  `monster8` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `ratio8` tinyint(3) UNSIGNED NOT NULL DEFAULT 0,
  `monster9` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `ratio9` tinyint(3) UNSIGNED NOT NULL DEFAULT 0,
  PRIMARY KEY (`id`) USING BTREE
) ENGINE = MyISAM AUTO_INCREMENT = 5 CHARACTER SET = latin1 COLLATE = latin1_bin ROW_FORMAT = FIXED;

DROP TABLE IF EXISTS `cq_monster_type_magic`;
cq_monster_type_magic`;
CREATE TABLE `cq_monster_type_magic`  (
  `id` int(10) UNSIGNED NOT NULL AUTO_INCREMENT,
  `monstertype` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `attack_interval` tinyint(3) UNSIGNED NOT NULL DEFAULT 0,
  `magic_type1` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `trigger_type1` tinyint(3) UNSIGNED NOT NULL DEFAULT 0,
  `trigger_param1` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `cold_time1` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `warning_time1` smallint(5) UNSIGNED NOT NULL DEFAULT 0,
  `magic_type2` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `trigger_type2` tinyint(3) UNSIGNED NOT NULL DEFAULT 0,
  `trigger_param2` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `cold_time2` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `warning_time2` smallint(5) UNSIGNED NOT NULL DEFAULT 0,
  `magic_type3` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `trigger_type3` tinyint(3) UNSIGNED NOT NULL DEFAULT 0,
  `trigger_param3` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `cold_time3` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `warning_time3` smallint(5) UNSIGNED NOT NULL DEFAULT 0,
  `magic_type4` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `trigger_type4` tinyint(3) UNSIGNED NOT NULL DEFAULT 0,
  `trigger_param4` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `cold_time4` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `warning_time4` smallint(5) UNSIGNED NOT NULL DEFAULT 0,
  `magic_type5` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `trigger_type5` tinyint(3) UNSIGNED NOT NULL DEFAULT 0,
  `trigger_param5` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `cold_time5` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `warning_time5` smallint(5) UNSIGNED NOT NULL DEFAULT 0,
  `magic_type6` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `trigger_type6` tinyint(3) UNSIGNED NOT NULL DEFAULT 0,
  `trigger_param6` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `cold_time6` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `warning_time6` smallint(5) UNSIGNED NOT NULL DEFAULT 0,
  `magic_type7` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `trigger_type7` tinyint(3) UNSIGNED NOT NULL DEFAULT 0,
  `trigger_param7` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `cold_time7` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `warning_time7` smallint(5) UNSIGNED NOT NULL DEFAULT 0,
  `magic_type8` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `trigger_type8` tinyint(3) UNSIGNED NOT NULL DEFAULT 0,
  `trigger_param8` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `cold_time8` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `warning_time8` smallint(5) UNSIGNED NOT NULL DEFAULT 0,
  `magic_type9` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `trigger_type9` tinyint(3) UNSIGNED NOT NULL DEFAULT 0,
  `trigger_param9` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `cold_time9` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `warning_time9` smallint(5) UNSIGNED NOT NULL DEFAULT 0,
  `magic_type10` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `trigger_type10` tinyint(3) UNSIGNED NOT NULL DEFAULT 0,
  `trigger_param10` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `cold_time10` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `warning_time10` smallint(5) UNSIGNED NOT NULL DEFAULT 0,
  PRIMARY KEY (`id`) USING BTREE
) ENGINE = MyISAM AUTO_INCREMENT = 155 CHARACTER SET = latin1 COLLATE = latin1_bin ROW_FORMAT = FIXED;

DROP TABLE IF EXISTS `cq_monstertype`;
cq_monstertype`;
CREATE TABLE `cq_monstertype`  (
  `id` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `name` char(35) CHARACTER SET latin1 COLLATE latin1_bin NOT NULL DEFAULT 'None',
  `type` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `lookface` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `life` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `mana` smallint(2) UNSIGNED NOT NULL DEFAULT 0,
  `attack_max` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `attack_min` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `defence` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `dexterity` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `dodge` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `helmet_type` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `armor_type` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `weaponr_type` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `weaponl_type` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `attack_range` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `view_range` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `escape_life` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `attack_speed` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `move_speed` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `level` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `attack_user` int(1) UNSIGNED NOT NULL DEFAULT 3,
  `drop_money` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `drop_itemtype` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `size_add` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `action` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `run_speed` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `drop_armet` tinyint(3) UNSIGNED NOT NULL DEFAULT 0,
  `drop_necklace` tinyint(3) UNSIGNED NOT NULL DEFAULT 0,
  `drop_armor` tinyint(3) UNSIGNED NOT NULL DEFAULT 0,
  `drop_ring` tinyint(3) UNSIGNED NOT NULL DEFAULT 0,
  `drop_weapon` tinyint(3) UNSIGNED NOT NULL DEFAULT 0,
  `drop_shield` tinyint(3) UNSIGNED NOT NULL DEFAULT 0,
  `drop_shoes` tinyint(3) UNSIGNED NOT NULL DEFAULT 0,
  `drop_hp` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `drop_mp` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `magic_type` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `magic_def` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `magic_hitrate` int(4) UNSIGNED NOT NULL DEFAULT 100,
  `ai_type` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `defence2` int(4) UNSIGNED NOT NULL DEFAULT 10000,
  `stc_type` smallint(2) UNSIGNED NOT NULL DEFAULT 0,
  `anti_monster` tinyint(1) UNSIGNED NOT NULL DEFAULT 0,
  `extra_battlelev` smallint(2) UNSIGNED NOT NULL DEFAULT 0,
  `extra_exp` smallint(2) NOT NULL DEFAULT 0,
  `extra_damage` smallint(2) NOT NULL DEFAULT 0,
  `species_type` tinyint(3) UNSIGNED NULL DEFAULT 0,
  `attr_metal` tinyint(3) UNSIGNED NOT NULL DEFAULT 0,
  `attr_wood` tinyint(3) UNSIGNED NOT NULL DEFAULT 0,
  `attr_water` tinyint(3) UNSIGNED NOT NULL DEFAULT 0,
  `attr_fire` tinyint(3) UNSIGNED NOT NULL DEFAULT 0,
  `attr_earth` tinyint(3) UNSIGNED NOT NULL DEFAULT 0,
  `vs_callpet` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `transform_flag` tinyint(3) UNSIGNED NOT NULL DEFAULT 0,
  `transform_condition` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `transform_monster` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `attack_new` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `defence_new` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `stable_defence` smallint(2) UNSIGNED NOT NULL DEFAULT 0,
  `critical_rate` smallint(2) UNSIGNED NOT NULL DEFAULT 0,
  `magic_critical_rate` smallint(2) UNSIGNED NOT NULL DEFAULT 0,
  `anti_critical_rate` smallint(2) UNSIGNED NOT NULL DEFAULT 0,
  `final_dmg_add` smallint(2) UNSIGNED NOT NULL DEFAULT 0,
  `final_dmg_add_mgc` smallint(2) UNSIGNED NOT NULL DEFAULT 0,
  `final_dmg_reduce` smallint(2) UNSIGNED NOT NULL DEFAULT 0,
  `final_dmg_reduce_mgc` smallint(2) UNSIGNED NOT NULL DEFAULT 0,
  `item_drop_rule1` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `item_drop_rule2` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `item_drop_rule3` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `item_drop_rule4` int(10) UNSIGNED NOT NULL DEFAULT 0,
  PRIMARY KEY (`id`) USING BTREE
) ENGINE = MyISAM CHARACTER SET = latin1 COLLATE = latin1_bin ROW_FORMAT = FIXED;

DROP TABLE IF EXISTS `cq_ndsdk_account`;
cq_ndsdk_account`;
CREATE TABLE `cq_ndsdk_account`  (
  `id` int(4) UNSIGNED NOT NULL AUTO_INCREMENT,
  `platform` int(4) UNSIGNED NULL DEFAULT 0,
  `app` varchar(128) CHARACTER SET latin1 COLLATE latin1_bin NOT NULL DEFAULT '',
  `account` varchar(64) CHARACTER SET latin1 COLLATE latin1_bin NOT NULL DEFAULT '',
  PRIMARY KEY (`id`) USING BTREE,
  UNIQUE INDEX `platform_app_account`(`platform`, `app`, `account`) USING BTREE
) ENGINE = MyISAM AUTO_INCREMENT = 1 CHARACTER SET = latin1 COLLATE = latin1_bin ROW_FORMAT = DYNAMIC;

DROP TABLE IF EXISTS `cq_newaction`;
cq_newaction`;
CREATE TABLE `cq_newaction`  (
  `id` int(4) UNSIGNED NOT NULL DEFAULT 90000000,
  `id_next` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `id_nextfail` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `type` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `data` int(4) NOT NULL DEFAULT 0,
  `param` varbinary(255) NULL DEFAULT '',
  PRIMARY KEY (`id`) USING BTREE
) ENGINE = MyISAM CHARACTER SET = latin1 COLLATE = latin1_bin ROW_FORMAT = DYNAMIC;

DROP TABLE IF EXISTS `cq_newbie_info`;
cq_newbie_info`;
CREATE TABLE `cq_newbie_info`  (
  `id` int(10) UNSIGNED NOT NULL AUTO_INCREMENT,
  `profession` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `lweapon` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `rweapon` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `head` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `boot` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `neck` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `ring` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `armor` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `item0` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `number0` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `item1` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `number1` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `item2` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `number2` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `item3` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `number3` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `item4` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `number4` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `item5` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `number5` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `item6` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `number6` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `item7` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `number7` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `item8` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `number8` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `item9` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `number9` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `magic0` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `magic1` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `magic2` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `magic3` int(10) UNSIGNED NOT NULL DEFAULT 0,
  PRIMARY KEY (`id`) USING BTREE,
  UNIQUE INDEX `u_profession`(`profession`) USING BTREE
) ENGINE = MyISAM AUTO_INCREMENT = 9 CHARACTER SET = latin1 COLLATE = latin1_bin ROW_FORMAT = FIXED;

DROP TABLE IF EXISTS `cq_npc`;
cq_npc`;
CREATE TABLE `cq_npc`  (
  `id` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `ownerid` int(4) UNSIGNED NULL DEFAULT 0,
  `playerid` int(4) UNSIGNED NULL DEFAULT 0,
  `name` varchar(35) CHARACTER SET latin1 COLLATE latin1_bin NULL DEFAULT 'undefined',
  `type` int(4) UNSIGNED NULL DEFAULT 0,
  `lookface` int(4) UNSIGNED NULL DEFAULT 0,
  `idxserver` int(4) NULL DEFAULT -1,
  `mapid` int(4) UNSIGNED NULL DEFAULT 0,
  `cellx` int(4) UNSIGNED NULL DEFAULT 0,
  `celly` int(4) UNSIGNED NULL DEFAULT 0,
  `task0` int(4) UNSIGNED NULL DEFAULT 0,
  `task1` int(4) UNSIGNED NULL DEFAULT 0,
  `task2` int(4) UNSIGNED NULL DEFAULT 0,
  `task3` int(4) UNSIGNED NULL DEFAULT 0,
  `task4` int(4) UNSIGNED NULL DEFAULT 0,
  `task5` int(4) UNSIGNED NULL DEFAULT 0,
  `task6` int(4) UNSIGNED NULL DEFAULT 0,
  `task7` int(4) UNSIGNED NULL DEFAULT 0,
  `data0` int(4) NOT NULL DEFAULT 0,
  `data1` int(4) NOT NULL DEFAULT 0,
  `data2` int(4) NOT NULL DEFAULT 0,
  `data3` int(4) NOT NULL DEFAULT 0,
  `datastr` char(15) CHARACTER SET latin1 COLLATE latin1_bin NULL DEFAULT 'None',
  `linkid` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `life` smallint(2) UNSIGNED NOT NULL DEFAULT 0,
  `maxlife` smallint(2) UNSIGNED NOT NULL DEFAULT 0,
  `base` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `sort` smallint(2) UNSIGNED NOT NULL DEFAULT 0,
  `itemid` int(4) UNSIGNED NULL DEFAULT NULL,
  PRIMARY KEY (`id`) USING BTREE,
  INDEX `idx_mapid`(`mapid`) USING BTREE
) ENGINE = MyISAM CHARACTER SET = latin1 COLLATE = latin1_bin ROW_FORMAT = DYNAMIC;

DROP TABLE IF EXISTS `cq_npc_income`;
cq_npc_income`;
CREATE TABLE `cq_npc_income`  (
  `id` int(4) UNSIGNED NOT NULL AUTO_INCREMENT,
  `npc_id` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `owner_id` int(3) UNSIGNED NOT NULL DEFAULT 0,
  `owner_type` tinyint(2) UNSIGNED NOT NULL DEFAULT 0,
  `income_money` bigint(20) UNSIGNED NOT NULL DEFAULT 0,
  PRIMARY KEY (`id`) USING BTREE
) ENGINE = MyISAM AUTO_INCREMENT = 47 CHARACTER SET = latin1 COLLATE = latin1_bin ROW_FORMAT = FIXED;

DROP TABLE IF EXISTS `cq_official_position`;
cq_official_position`;
CREATE TABLE `cq_official_position`  (
  `id` int(4) UNSIGNED NOT NULL AUTO_INCREMENT,
  `player_id` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `league_id` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `official_type` smallint(4) UNSIGNED NOT NULL DEFAULT 0,
  `salary_time` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `official_time` int(10) UNSIGNED NOT NULL DEFAULT 0,
  PRIMARY KEY (`id`) USING BTREE
) ENGINE = MyISAM AUTO_INCREMENT = 1 CHARACTER SET = latin1 COLLATE = latin1_bin ROW_FORMAT = FIXED;

DROP TABLE IF EXISTS `cq_official_type`;
cq_official_type`;
CREATE TABLE `cq_official_type`  (
  `id` smallint(4) UNSIGNED NOT NULL,
  `setup_num` tinyint(4) UNSIGNED NOT NULL DEFAULT 0,
  `speaker_num` tinyint(4) UNSIGNED NOT NULL DEFAULT 0,
  `official_name` char(32) CHARACTER SET latin1 COLLATE latin1_bin NOT NULL,
  `official_name_ex` char(32) CHARACTER SET latin1 COLLATE latin1_bin NOT NULL,
  `fee` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `award_id` int(10) UNSIGNED NOT NULL DEFAULT 0,
  PRIMARY KEY (`id`) USING BTREE
) ENGINE = MyISAM CHARACTER SET = latin1 COLLATE = latin1_bin ROW_FORMAT = FIXED;

DROP TABLE IF EXISTS `cq_online_payments`;
cq_online_payments`;
CREATE TABLE `cq_online_payments`  (
  `id` int(10) UNSIGNED NOT NULL AUTO_INCREMENT,
  `type` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `playerid` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `accountid` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `serverid` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `transactionid` varchar(33) CHARACTER SET latin1 COLLATE latin1_bin NOT NULL DEFAULT '0',
  `paymentsinfo` varchar(1024) CHARACTER SET latin1 COLLATE latin1_bin NOT NULL DEFAULT '0',
  `date` int(10) UNSIGNED NOT NULL DEFAULT 0,
  PRIMARY KEY (`id`) USING BTREE
) ENGINE = MyISAM AUTO_INCREMENT = 1 CHARACTER SET = latin1 COLLATE = latin1_bin ROW_FORMAT = DYNAMIC;

DROP TABLE IF EXISTS `cq_operating_act`;
cq_operating_act`;
CREATE TABLE `cq_operating_act`  (
  `id` int(4) UNSIGNED NOT NULL AUTO_INCREMENT,
  `type` tinyint(4) UNSIGNED NOT NULL DEFAULT 0,
  `min_demand` smallint(4) UNSIGNED NOT NULL DEFAULT 0,
  `max_demand` smallint(4) UNSIGNED NOT NULL DEFAULT 0,
  `start_time` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `end_time` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `status` tinyint(4) UNSIGNED NOT NULL DEFAULT 0,
  `drop_time` int(4) UNSIGNED NOT NULL DEFAULT 0,
  PRIMARY KEY (`id`) USING BTREE
) ENGINE = MyISAM AUTO_INCREMENT = 109 CHARACTER SET = latin1 COLLATE = latin1_bin ROW_FORMAT = FIXED;

DROP TABLE IF EXISTS `cq_operating_mail_record`;
cq_operating_mail_record`;
CREATE TABLE `cq_operating_mail_record`  (
  `id` int(4) NOT NULL AUTO_INCREMENT,
  `player_id` int(4) NOT NULL DEFAULT 0,
  `operating_mail_type` int(4) NOT NULL DEFAULT 0,
  PRIMARY KEY (`id`) USING BTREE,
  INDEX `idx_player_id`(`player_id`) USING BTREE
) ENGINE = MyISAM AUTO_INCREMENT = 3 CHARACTER SET = latin1 COLLATE = latin1_bin ROW_FORMAT = FIXED;

DROP TABLE IF EXISTS `cq_operating_mail_type`;
cq_operating_mail_type`;
CREATE TABLE `cq_operating_mail_type`  (
  `id` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `start_time` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `end_time` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `vip_flag` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `min_demand` smallint(4) UNSIGNED NOT NULL DEFAULT 0,
  `max_demand` smallint(4) UNSIGNED NOT NULL DEFAULT 0,
  `first_pay` tinyint(4) UNSIGNED NOT NULL DEFAULT 0,
  `sender_name` varbinary(32) NOT NULL DEFAULT '',
  `title` varbinary(32) NOT NULL DEFAULT '',
  `content` varbinary(255) NOT NULL DEFAULT '',
  `expiration_date` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `money` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `emoney` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `action` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `item_type` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `item_mono` tinyint(4) UNSIGNED NOT NULL DEFAULT 0,
  PRIMARY KEY (`id`) USING BTREE,
  INDEX `idx_start_end`(`start_time`, `end_time`) USING BTREE
) ENGINE = MyISAM CHARACTER SET = latin1 COLLATE = latin1_bin ROW_FORMAT = DYNAMIC;

DROP TABLE IF EXISTS `cq_operating_prize`;
cq_operating_prize`;
CREATE TABLE `cq_operating_prize`  (
  `id` int(4) UNSIGNED NOT NULL AUTO_INCREMENT,
  `activity_id` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `reward_grade` tinyint(4) UNSIGNED NOT NULL DEFAULT 0,
  `progress_value` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `item_type` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `monopoly` tinyint(4) UNSIGNED NOT NULL DEFAULT 0,
  PRIMARY KEY (`id`) USING BTREE
) ENGINE = MyISAM AUTO_INCREMENT = 1091 CHARACTER SET = latin1 COLLATE = latin1_bin ROW_FORMAT = FIXED;

DROP TABLE IF EXISTS `cq_operating_user_info`;
cq_operating_user_info`;
CREATE TABLE `cq_operating_user_info`  (
  `id` int(4) UNSIGNED NOT NULL AUTO_INCREMENT,
  `player_id` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `activity_id` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `activity_type` tinyint(4) UNSIGNED NOT NULL DEFAULT 0,
  `progress_value` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `reward_grade` tinyint(4) UNSIGNED NOT NULL DEFAULT 0,
  `delete_flag` tinyint(4) UNSIGNED NOT NULL DEFAULT 0,
  PRIMARY KEY (`id`) USING BTREE,
  UNIQUE INDEX `u_player_activity`(`player_id`, `activity_id`) USING BTREE
) ENGINE = MyISAM AUTO_INCREMENT = 1 CHARACTER SET = latin1 COLLATE = latin1_bin ROW_FORMAT = FIXED;

DROP TABLE IF EXISTS `cq_order_award`;
cq_order_award`;
CREATE TABLE `cq_order_award`  (
  `contribution_lev` smallint(10) UNSIGNED NOT NULL DEFAULT 0,
  `order_gift_itemtype` int(10) UNSIGNED NULL DEFAULT 0,
  `order_gift_action` int(10) UNSIGNED NULL DEFAULT 0,
  `order_salary_itemtype` int(10) UNSIGNED NULL DEFAULT 0,
  `order_salary_action` int(10) UNSIGNED NULL DEFAULT 0,
  PRIMARY KEY (`contribution_lev`) USING BTREE
) ENGINE = MyISAM CHARACTER SET = latin1 COLLATE = latin1_bin ROW_FORMAT = FIXED;

DROP TABLE IF EXISTS `cq_passway`;
cq_passway`;
CREATE TABLE `cq_passway`  (
  `id` int(4) UNSIGNED NOT NULL AUTO_INCREMENT,
  `mapid` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `passway_idx` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `passway_mapid` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `passway_mapportal` int(4) UNSIGNED NOT NULL DEFAULT 0,
  PRIMARY KEY (`id`) USING BTREE
) ENGINE = MyISAM AUTO_INCREMENT = 172322 CHARACTER SET = latin1 COLLATE = latin1_bin ROW_FORMAT = FIXED;

DROP TABLE IF EXISTS `cq_pet`;
cq_pet`;
CREATE TABLE `cq_pet`  (
  `id` int(8) UNSIGNED NOT NULL AUTO_INCREMENT,
  `ownerid` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `ownertype` tinyint(3) UNSIGNED NOT NULL DEFAULT 0,
  `generatorid` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `name` varbinary(15) NOT NULL DEFAULT 'None',
  `typeid` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `life` smallint(2) UNSIGNED NOT NULL DEFAULT 0,
  `mana` smallint(2) UNSIGNED NOT NULL DEFAULT 0,
  `recordmap_id` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `recordx` smallint(2) UNSIGNED NOT NULL DEFAULT 0,
  `recordy` smallint(2) UNSIGNED NOT NULL DEFAULT 0,
  `data` int(4) UNSIGNED NOT NULL DEFAULT 0,
  PRIMARY KEY (`id`) USING BTREE,
  INDEX `idx_recordmap_id`(`recordmap_id`) USING BTREE
) ENGINE = MyISAM AUTO_INCREMENT = 1 CHARACTER SET = latin1 COLLATE = latin1_bin ROW_FORMAT = DYNAMIC;

DROP TABLE IF EXISTS `cq_petpoint`;
cq_petpoint`;
CREATE TABLE `cq_petpoint`  (
  `id` int(4) UNSIGNED NOT NULL AUTO_INCREMENT,
  `mapid` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `rank` smallint(4) UNSIGNED NOT NULL DEFAULT 0,
  `ridepet_point` smallint(4) UNSIGNED NOT NULL DEFAULT 0,
  PRIMARY KEY (`id`) USING BTREE,
  INDEX `idx_mapid`(`mapid`) USING BTREE
) ENGINE = MyISAM AUTO_INCREMENT = 801 CHARACTER SET = latin1 COLLATE = latin1_bin ROW_FORMAT = FIXED;

DROP TABLE IF EXISTS `cq_pk_bonus`;
cq_pk_bonus`;
CREATE TABLE `cq_pk_bonus`  (
  `id` int(4) UNSIGNED NOT NULL AUTO_INCREMENT,
  `Target` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `Target_name` varbinary(15) NULL DEFAULT NULL,
  `Hunter` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `Hunter_name` varbinary(15) NULL DEFAULT NULL,
  `B_type` tinyint(2) UNSIGNED NOT NULL DEFAULT 0,
  `Bonus` int(4) UNSIGNED NOT NULL DEFAULT 0,
  PRIMARY KEY (`id`) USING BTREE,
  INDEX `index_target`(`Target`) USING BTREE,
  INDEX `index_hunter`(`Hunter`) USING BTREE
) ENGINE = MyISAM AUTO_INCREMENT = 1 CHARACTER SET = latin1 COLLATE = latin1_bin ROW_FORMAT = DYNAMIC;

DROP TABLE IF EXISTS `cq_pk_info`;
cq_pk_info`;
CREATE TABLE `cq_pk_info`  (
  `id` int(10) UNSIGNED NOT NULL AUTO_INCREMENT,
  `type` smallint(5) UNSIGNED NOT NULL DEFAULT 0,
  `subtype` smallint(5) UNSIGNED NOT NULL DEFAULT 0,
  `time` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `pk1` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `pk1_name` varbinary(31) NOT NULL DEFAULT '',
  `pk2` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `pk2_name` varbinary(31) NOT NULL DEFAULT '',
  `pk3` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `pk3_name` varbinary(31) NOT NULL DEFAULT '',
  `pk4` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `pk4_name` varbinary(31) NOT NULL DEFAULT '',
  `pk5` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `pk5_name` varbinary(31) NOT NULL DEFAULT '',
  `pk6` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `pk6_name` varbinary(31) NOT NULL DEFAULT '',
  `pk7` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `pk7_name` varbinary(31) NOT NULL DEFAULT '',
  `pk8` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `pk8_name` varbinary(31) NOT NULL DEFAULT '',
  PRIMARY KEY (`id`) USING BTREE,
  UNIQUE INDEX `u_type_subtype`(`type`, `subtype`) USING BTREE
) ENGINE = MyISAM AUTO_INCREMENT = 13 CHARACTER SET = latin1 COLLATE = latin1_bin ROW_FORMAT = DYNAMIC;

DROP TABLE IF EXISTS `cq_pk_item`;
cq_pk_item`;
CREATE TABLE `cq_pk_item`  (
  `id` int(4) NOT NULL AUTO_INCREMENT,
  `item` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `target` int(4) NOT NULL DEFAULT 0,
  `target_name` varbinary(15) NOT NULL DEFAULT '',
  `hunter` int(4) NOT NULL DEFAULT 0,
  `hunter_name` varbinary(15) NOT NULL DEFAULT '',
  `manhunt_time` int(4) NOT NULL DEFAULT 0,
  `bonus` smallint(2) NOT NULL DEFAULT 0,
  PRIMARY KEY (`id`) USING BTREE,
  INDEX `idx_hunter_item`(`hunter`, `item`) USING BTREE
) ENGINE = MyISAM AUTO_INCREMENT = 1 CHARACTER SET = latin1 COLLATE = latin1_bin ROW_FORMAT = DYNAMIC;

DROP TABLE IF EXISTS `cq_pk_item_timeout`;
cq_pk_item_timeout`;
CREATE TABLE `cq_pk_item_timeout`  (
  `id` int(4) NOT NULL AUTO_INCREMENT,
  `item` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `target` int(4) NOT NULL DEFAULT 0,
  `target_name` varbinary(15) NOT NULL DEFAULT '',
  `hunter` int(4) NOT NULL DEFAULT 0,
  `hunter_name` varbinary(15) NOT NULL DEFAULT '',
  `manhunt_time` int(4) NOT NULL DEFAULT 0,
  `bonus` smallint(2) NOT NULL DEFAULT 0,
  PRIMARY KEY (`id`) USING BTREE,
  INDEX `idx_hunter_item`(`hunter`, `item`) USING BTREE
) ENGINE = MyISAM AUTO_INCREMENT = 1 CHARACTER SET = latin1 COLLATE = latin1_bin ROW_FORMAT = DYNAMIC;

DROP TABLE IF EXISTS `cq_pk_mapgroup`;
cq_pk_mapgroup`;
CREATE TABLE `cq_pk_mapgroup`  (
  `id` int(10) UNSIGNED NOT NULL AUTO_INCREMENT,
  `type` tinyint(3) UNSIGNED NULL DEFAULT 0,
  `name` varchar(50) CHARACTER SET latin1 COLLATE latin1_bin NULL DEFAULT NULL,
  `map_id1` int(10) UNSIGNED NULL DEFAULT 0,
  `map_id2` int(10) UNSIGNED NULL DEFAULT 0,
  `map_id3` int(10) UNSIGNED NULL DEFAULT 0,
  `map_id4` int(10) UNSIGNED NULL DEFAULT 0,
  `map_id5` int(10) UNSIGNED NULL DEFAULT 0,
  PRIMARY KEY (`id`) USING BTREE,
  UNIQUE INDEX `type`(`type`) USING BTREE
) ENGINE = MyISAM AUTO_INCREMENT = 1 CHARACTER SET = latin1 COLLATE = latin1_bin ROW_FORMAT = DYNAMIC;

DROP TABLE IF EXISTS `cq_pk_statistic`;
cq_pk_statistic`;
CREATE TABLE `cq_pk_statistic`  (
  `id` int(10) UNSIGNED NOT NULL AUTO_INCREMENT,
  `killer_id` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `target_id` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `pk_time` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `map_id` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `target_battle_effect` smallint(5) UNSIGNED NOT NULL DEFAULT 0,
  `kill_times` int(10) UNSIGNED NOT NULL DEFAULT 0,
  PRIMARY KEY (`id`) USING BTREE,
  INDEX `index_killer_id`(`killer_id`) USING BTREE
) ENGINE = MyISAM AUTO_INCREMENT = 52 CHARACTER SET = latin1 COLLATE = latin1_bin ROW_FORMAT = FIXED;

DROP TABLE IF EXISTS `cq_player_process_goal`;
cq_player_process_goal`;
CREATE TABLE `cq_player_process_goal`  (
  `id` int(10) UNSIGNED NOT NULL AUTO_INCREMENT,
  `user_id` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `goal_id` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `task_complete_state` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `task_award_state` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `process_award` tinyint(4) UNSIGNED NOT NULL DEFAULT 0,
  PRIMARY KEY (`id`) USING BTREE,
  INDEX `user_id_goal_id`(`user_id`, `goal_id`) USING BTREE
) ENGINE = MyISAM AUTO_INCREMENT = 129 CHARACTER SET = latin1 COLLATE = latin1_bin ROW_FORMAT = FIXED;

DROP TABLE IF EXISTS `cq_player_process_task`;
cq_player_process_task`;
CREATE TABLE `cq_player_process_task`  (
  `id` int(10) UNSIGNED NOT NULL AUTO_INCREMENT,
  `user_id` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `task_id` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `schedule` int(10) UNSIGNED NOT NULL DEFAULT 0,
  PRIMARY KEY (`id`) USING BTREE,
  UNIQUE INDEX `user_id_task_id`(`user_id`, `task_id`) USING BTREE
) ENGINE = MyISAM AUTO_INCREMENT = 25 CHARACTER SET = latin1 COLLATE = latin1_bin ROW_FORMAT = FIXED;

DROP TABLE IF EXISTS `cq_plunder_war`;
cq_plunder_war`;
CREATE TABLE `cq_plunder_war`  (
  `id` int(10) UNSIGNED NOT NULL AUTO_INCREMENT,
  `apply_date` tinyint(3) UNSIGNED NOT NULL DEFAULT 0,
  `apply_id` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `target_id_1` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `target_id_2` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `target_id_3` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `target_id_4` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `target_id_5` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `target_id_6` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `target_id_7` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `target_id_8` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `target_id_9` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `target_id_10` int(10) UNSIGNED NOT NULL DEFAULT 0,
  PRIMARY KEY (`id`) USING BTREE
) ENGINE = MyISAM AUTO_INCREMENT = 1 CHARACTER SET = latin1 COLLATE = latin1_bin ROW_FORMAT = FIXED;

DROP TABLE IF EXISTS `cq_point_allot`;
cq_point_allot`;
CREATE TABLE `cq_point_allot`  (
  `id` int(4) UNSIGNED NOT NULL AUTO_INCREMENT,
  `profession` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `level` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `force` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `Speed` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `health` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `soul` int(4) UNSIGNED NOT NULL DEFAULT 0,
  PRIMARY KEY (`id`) USING BTREE,
  UNIQUE INDEX `idx`(`profession`, `level`) USING BTREE
) ENGINE = MyISAM AUTO_INCREMENT = 963 CHARACTER SET = latin1 COLLATE = latin1_bin ROW_FORMAT = FIXED;

DROP TABLE IF EXISTS `cq_pointrecord`;
cq_pointrecord`;
CREATE TABLE `cq_pointrecord`  (
  `id` int(4) UNSIGNED NOT NULL AUTO_INCREMENT,
  `userid` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `money` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `emoney` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `type` tinyint(4) UNSIGNED NOT NULL DEFAULT 0,
  PRIMARY KEY (`id`) USING BTREE,
  INDEX `idx_userid`(`userid`) USING BTREE
) ENGINE = MyISAM AUTO_INCREMENT = 1 CHARACTER SET = latin1 COLLATE = latin1_bin ROW_FORMAT = FIXED;

DROP TABLE IF EXISTS `cq_pool_record_cfg`;
cq_pool_record_cfg`;
CREATE TABLE `cq_pool_record_cfg`  (
  `id` int(10) UNSIGNED NOT NULL AUTO_INCREMENT,
  `table_name` varchar(50) CHARACTER SET latin1 COLLATE latin1_bin NULL DEFAULT NULL,
  `precreate_num` int(10) UNSIGNED NOT NULL DEFAULT 0,
  PRIMARY KEY (`id`) USING BTREE,
  UNIQUE INDEX `table_name`(`table_name`) USING BTREE
) ENGINE = MyISAM AUTO_INCREMENT = 9 CHARACTER SET = latin1 COLLATE = latin1_bin ROW_FORMAT = DYNAMIC;

DROP TABLE IF EXISTS `cq_portal`;
cq_portal`;
CREATE TABLE `cq_portal`  (
  `id` int(4) UNSIGNED NOT NULL AUTO_INCREMENT,
  `mapid` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `portal_idx` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `portal_x` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `portal_y` int(4) UNSIGNED NOT NULL DEFAULT 0,
  PRIMARY KEY (`id`) USING BTREE
) ENGINE = MyISAM AUTO_INCREMENT = 1056 CHARACTER SET = latin1 COLLATE = latin1_bin ROW_FORMAT = FIXED;

DROP TABLE IF EXISTS `cq_process_goal`;
cq_process_goal`;
CREATE TABLE `cq_process_goal`  (
  `id` int(10) UNSIGNED NOT NULL AUTO_INCREMENT,
  `task_num` smallint(6) UNSIGNED NULL DEFAULT 0,
  `open_lv` int(10) UNSIGNED NULL DEFAULT 0,
  `itemtype1` int(10) UNSIGNED NULL DEFAULT 0,
  `number1` smallint(6) UNSIGNED NULL DEFAULT 0,
  `monoply1` tinyint(4) UNSIGNED NULL DEFAULT 0,
  `itemtype2` int(10) UNSIGNED NULL DEFAULT 0,
  `number2` smallint(6) UNSIGNED NULL DEFAULT 0,
  `monoply2` tinyint(4) UNSIGNED NULL DEFAULT 0,
  `itemtype3` int(10) UNSIGNED NULL DEFAULT 0,
  `number3` smallint(6) UNSIGNED NULL DEFAULT 0,
  `monoply3` tinyint(4) UNSIGNED NULL DEFAULT 0,
  PRIMARY KEY (`id`) USING BTREE
) ENGINE = MyISAM AUTO_INCREMENT = 11 CHARACTER SET = latin1 COLLATE = latin1_bin ROW_FORMAT = FIXED;

DROP TABLE IF EXISTS `cq_process_task`;
cq_process_task`;
CREATE TABLE `cq_process_task`  (
  `id` int(10) UNSIGNED NOT NULL AUTO_INCREMENT,
  `type` smallint(6) UNSIGNED NULL DEFAULT 0,
  `sort` tinyint(4) UNSIGNED NULL DEFAULT 0,
  `condition` int(10) UNSIGNED NULL DEFAULT 0,
  `schedule` int(10) UNSIGNED NULL DEFAULT 0,
  `itemtype` int(10) UNSIGNED NULL DEFAULT 0,
  `number` smallint(6) UNSIGNED NULL DEFAULT 0,
  `monoply` tinyint(4) UNSIGNED NULL DEFAULT 0,
  PRIMARY KEY (`id`) USING BTREE
) ENGINE = MyISAM AUTO_INCREMENT = 1009 CHARACTER SET = latin1 COLLATE = latin1_bin ROW_FORMAT = FIXED;

DROP TABLE IF EXISTS `cq_promotion_activity`;
cq_promotion_activity`;
CREATE TABLE `cq_promotion_activity`  (
  `id` int(4) UNSIGNED NOT NULL AUTO_INCREMENT,
  `type` tinyint(4) UNSIGNED NOT NULL DEFAULT 0,
  `start_time` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `end_time` int(4) UNSIGNED NOT NULL DEFAULT 0,
  PRIMARY KEY (`id`) USING BTREE
) ENGINE = MyISAM AUTO_INCREMENT = 1 CHARACTER SET = latin1 COLLATE = latin1_bin ROW_FORMAT = FIXED;

DROP TABLE IF EXISTS `cq_promotion_goods`;
cq_promotion_goods`;
CREATE TABLE `cq_promotion_goods`  (
  `id` int(4) UNSIGNED NOT NULL AUTO_INCREMENT,
  `activity_id` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `item_type` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `old_emoney_price` smallint(4) UNSIGNED NOT NULL DEFAULT 0,
  `new_emoney_price` smallint(4) UNSIGNED NOT NULL DEFAULT 0,
  `demand_number` smallint(4) UNSIGNED NOT NULL DEFAULT 0,
  PRIMARY KEY (`id`) USING BTREE
) ENGINE = MyISAM AUTO_INCREMENT = 1 CHARACTER SET = latin1 COLLATE = latin1_bin ROW_FORMAT = FIXED;

DROP TABLE IF EXISTS `cq_promotion_info`;
cq_promotion_info`;
CREATE TABLE `cq_promotion_info`  (
  `id` int(4) UNSIGNED NOT NULL AUTO_INCREMENT,
  `activity_id` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `goods_id` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `actor_num` smallint(4) UNSIGNED NOT NULL DEFAULT 0,
  `status` smallint(4) UNSIGNED NOT NULL DEFAULT 0,
  PRIMARY KEY (`id`) USING BTREE
) ENGINE = MyISAM AUTO_INCREMENT = 1 CHARACTER SET = latin1 COLLATE = latin1_bin ROW_FORMAT = FIXED;

DROP TABLE IF EXISTS `cq_props`;
cq_props`;
CREATE TABLE `cq_props`  (
  `id` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `targettype` tinyint(2) UNSIGNED NOT NULL DEFAULT 0,
  `validrange` tinyint(2) UNSIGNED NOT NULL DEFAULT 0,
  `use_range` tinyint(2) UNSIGNED NOT NULL DEFAULT 0,
  `status_id` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `data0` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `data1` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `data2` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `action` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `maxtimes` tinyint(2) UNSIGNED NOT NULL DEFAULT 0,
  PRIMARY KEY (`id`) USING BTREE
) ENGINE = MyISAM CHARACTER SET = latin1 COLLATE = latin1_bin ROW_FORMAT = FIXED;

DROP TABLE IF EXISTS `cq_protect_path`;
cq_protect_path`;
CREATE TABLE `cq_protect_path`  (
  `id` int(10) UNSIGNED NOT NULL AUTO_INCREMENT,
  `next_path` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `destination_x` smallint(6) NOT NULL DEFAULT 0,
  `destination_y` int(11) NOT NULL DEFAULT 0,
  `action` int(11) NOT NULL DEFAULT 0,
  `param` varbinary(128) NULL DEFAULT NULL,
  `wait_time` smallint(5) UNSIGNED NOT NULL DEFAULT 0,
  PRIMARY KEY (`id`) USING BTREE
) ENGINE = MyISAM AUTO_INCREMENT = 44 CHARACTER SET = latin1 COLLATE = latin1_bin ROW_FORMAT = DYNAMIC;

DROP TABLE IF EXISTS `cq_quiz`;
cq_quiz`;
CREATE TABLE `cq_quiz`  (
  `id` int(4) UNSIGNED NOT NULL AUTO_INCREMENT,
  `type` tinyint(4) UNSIGNED NULL DEFAULT NULL,
  `level` tinyint(4) UNSIGNED NULL DEFAULT NULL,
  `term` tinyint(4) UNSIGNED NULL DEFAULT NULL,
  `question` varbinary(255) NULL DEFAULT NULL,
  `answer1` varbinary(100) NULL DEFAULT NULL,
  `answer2` varbinary(100) NULL DEFAULT NULL,
  `answer3` varbinary(100) NULL DEFAULT NULL,
  `answer4` varbinary(100) NULL DEFAULT NULL,
  `result` tinyint(4) UNSIGNED NULL DEFAULT NULL,
  PRIMARY KEY (`id`) USING BTREE
) ENGINE = MyISAM AUTO_INCREMENT = 2173 CHARACTER SET = latin1 COLLATE = latin1_bin ROW_FORMAT = DYNAMIC;

DROP TABLE IF EXISTS `cq_rebirth`;
cq_rebirth`;
CREATE TABLE `cq_rebirth`  (
  `id` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `need_prof` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `new_prof` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `need_level` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `new_level` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `metepsychosis` tinyint(2) UNSIGNED NOT NULL DEFAULT 0,
  PRIMARY KEY (`id`) USING BTREE
) ENGINE = MyISAM CHARACTER SET = latin1 COLLATE = latin1_bin ROW_FORMAT = FIXED;

DROP TABLE IF EXISTS `cq_region`;
cq_region`;
CREATE TABLE `cq_region`  (
  `id` int(4) UNSIGNED NOT NULL AUTO_INCREMENT,
  `mapid` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `type` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `bound_x` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `bound_y` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `bound_cx` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `bound_cy` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `datastr` varchar(15) CHARACTER SET latin1 COLLATE latin1_bin NOT NULL DEFAULT '',
  `data0` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `data1` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `data2` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `data3` int(4) UNSIGNED NOT NULL DEFAULT 0,
  PRIMARY KEY (`id`) USING BTREE,
  INDEX `idx_type`(`type`) USING BTREE
) ENGINE = MyISAM AUTO_INCREMENT = 252 CHARACTER SET = latin1 COLLATE = latin1_bin ROW_FORMAT = DYNAMIC;

DROP TABLE IF EXISTS `cq_roulette_chip_info`;
cq_roulette_chip_info`;
CREATE TABLE `cq_roulette_chip_info`  (
  `id` int(10) UNSIGNED NOT NULL AUTO_INCREMENT,
  `wager_type` tinyint(3) UNSIGNED NULL DEFAULT 0,
  `chip1` int(10) UNSIGNED NULL DEFAULT 0,
  `chip2` int(10) UNSIGNED NULL DEFAULT 0,
  `chip3` int(10) UNSIGNED NULL DEFAULT 0,
  `chip4` int(10) UNSIGNED NULL DEFAULT 0,
  `chip5` int(10) UNSIGNED NULL DEFAULT 0,
  PRIMARY KEY (`id`) USING BTREE
) ENGINE = MyISAM AUTO_INCREMENT = 3 CHARACTER SET = latin1 COLLATE = latin1_bin ROW_FORMAT = FIXED;

DROP TABLE IF EXISTS `cq_rule`;
cq_rule`;
CREATE TABLE `cq_rule`  (
  `id` int(4) UNSIGNED NOT NULL AUTO_INCREMENT,
  `owner_id` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `mode` varbinary(15) NOT NULL DEFAULT '',
  `condition` varbinary(255) NOT NULL DEFAULT '',
  `result` varbinary(255) NOT NULL DEFAULT '',
  `possible` tinyint(3) UNSIGNED NOT NULL DEFAULT 50,
  PRIMARY KEY (`id`) USING BTREE
) ENGINE = MyISAM AUTO_INCREMENT = 1 CHARACTER SET = latin1 COLLATE = latin1_bin ROW_FORMAT = DYNAMIC;

DROP TABLE IF EXISTS `cq_serverinfo`;
cq_serverinfo`;
CREATE TABLE `cq_serverinfo`  (
  `id` int(4) UNSIGNED NOT NULL AUTO_INCREMENT,
  `server_name` varchar(31) CHARACTER SET latin1 COLLATE latin1_bin NOT NULL DEFAULT '',
  `db_name` varchar(31) CHARACTER SET latin1 COLLATE latin1_bin NOT NULL DEFAULT '',
  PRIMARY KEY (`id`) USING BTREE
) ENGINE = MyISAM AUTO_INCREMENT = 1 CHARACTER SET = latin1 COLLATE = latin1_bin ROW_FORMAT = DYNAMIC;

DROP TABLE IF EXISTS `cq_setmeed`;
cq_setmeed`;
CREATE TABLE `cq_setmeed`  (
  `id` int(4) UNSIGNED NOT NULL AUTO_INCREMENT,
  `type` tinyint(4) UNSIGNED NOT NULL DEFAULT 0,
  `synid` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `money` int(4) UNSIGNED NULL DEFAULT 0,
  `emoney` int(4) UNSIGNED NULL DEFAULT 0,
  PRIMARY KEY (`id`) USING BTREE
) ENGINE = MyISAM AUTO_INCREMENT = 1 CHARACTER SET = latin1 COLLATE = latin1_bin ROW_FORMAT = FIXED;

DROP TABLE IF EXISTS `cq_skilled_level_despise`;
cq_skilled_level_despise`;
CREATE TABLE `cq_skilled_level_despise`  (
  `id` int(4) UNSIGNED NOT NULL AUTO_INCREMENT,
  `skilled_level_diff` int(4) NOT NULL DEFAULT 0,
  `percentage` int(4) NOT NULL DEFAULT 0,
  PRIMARY KEY (`id`) USING BTREE
) ENGINE = MyISAM AUTO_INCREMENT = 1 CHARACTER SET = latin1 COLLATE = latin1_bin ROW_FORMAT = FIXED;

DROP TABLE IF EXISTS `cq_slot_winning_rule`;
cq_slot_winning_rule`;
CREATE TABLE `cq_slot_winning_rule`  (
  `id` int(10) UNSIGNED NOT NULL AUTO_INCREMENT,
  `type` tinyint(3) UNSIGNED NULL DEFAULT 0,
  `pattern` smallint(5) UNSIGNED NULL DEFAULT 0,
  `weight` int(10) UNSIGNED NULL DEFAULT 0,
  `multiple` int(10) UNSIGNED NULL DEFAULT 0,
  PRIMARY KEY (`id`) USING BTREE
) ENGINE = MyISAM AUTO_INCREMENT = 687 CHARACTER SET = latin1 COLLATE = latin1_bin ROW_FORMAT = FIXED;

DROP TABLE IF EXISTS `cq_sponsor`;
cq_sponsor`;
CREATE TABLE `cq_sponsor`  (
  `id` int(4) UNSIGNED NOT NULL AUTO_INCREMENT,
  `param` varchar(255) CHARACTER SET latin1 COLLATE latin1_bin NULL DEFAULT NULL,
  `sponsor` varchar(255) CHARACTER SET latin1 COLLATE latin1_bin NULL DEFAULT NULL,
  `showtime_begin` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `showtime_over` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `mod` tinyint(1) UNSIGNED NOT NULL DEFAULT 1,
  PRIMARY KEY (`id`) USING BTREE
) ENGINE = MyISAM AUTO_INCREMENT = 1 CHARACTER SET = latin1 COLLATE = latin1_bin ROW_FORMAT = DYNAMIC;

DROP TABLE IF EXISTS `cq_statistic`;
cq_statistic`;
CREATE TABLE `cq_statistic`  (
  `id` int(10) UNSIGNED ZEROFILL NOT NULL AUTO_INCREMENT,
  `player_id` int(4) UNSIGNED ZEROFILL NOT NULL DEFAULT 0000,
  `event_type` int(4) UNSIGNED ZEROFILL NOT NULL DEFAULT 0000,
  `data_type` int(4) UNSIGNED ZEROFILL NOT NULL DEFAULT 0000,
  `data` int(4) UNSIGNED ZEROFILL NOT NULL DEFAULT 0000,
  `timestamp` int(4) UNSIGNED NOT NULL DEFAULT 0,
  PRIMARY KEY (`id`) USING BTREE,
  INDEX `player_id`(`player_id`) USING BTREE
) ENGINE = MyISAM AUTO_INCREMENT = 736 CHARACTER SET = latin1 COLLATE = latin1_bin ROW_FORMAT = FIXED;

DROP TABLE IF EXISTS `cq_statistic_daily`;
cq_statistic_daily`;
CREATE TABLE `cq_statistic_daily`  (
  `id` int(10) UNSIGNED NOT NULL AUTO_INCREMENT,
  `player_id` int(10) UNSIGNED NULL DEFAULT 0,
  `type` int(10) UNSIGNED NULL DEFAULT 0,
  `subtype` int(10) UNSIGNED NULL DEFAULT 0,
  `data` int(10) NULL DEFAULT 0,
  PRIMARY KEY (`id`) USING BTREE,
  INDEX `idx_player_id`(`player_id`) USING BTREE
) ENGINE = MyISAM AUTO_INCREMENT = 59 CHARACTER SET = latin1 COLLATE = latin1_bin ROW_FORMAT = FIXED;

DROP TABLE IF EXISTS `cq_statistic_timeout`;
cq_statistic_timeout`;
CREATE TABLE `cq_statistic_timeout`  (
  `id` int(10) UNSIGNED NOT NULL AUTO_INCREMENT,
  `player_id` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `event_type` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `data_type` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `data` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `timestamp` int(4) UNSIGNED NOT NULL DEFAULT 0,
  PRIMARY KEY (`id`) USING BTREE,
  INDEX `player_id`(`player_id`) USING BTREE
) ENGINE = MyISAM AUTO_INCREMENT = 1 CHARACTER SET = latin1 COLLATE = latin1_bin ROW_FORMAT = FIXED;

DROP TABLE IF EXISTS `cq_status`;
cq_status`;
CREATE TABLE `cq_status`  (
  `id` int(4) UNSIGNED NOT NULL AUTO_INCREMENT,
  `owner_id` int(4) NOT NULL DEFAULT 0,
  `status` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `power` int(4) NOT NULL DEFAULT 0,
  `sort` tinyint(1) UNSIGNED NOT NULL DEFAULT 0,
  `leave_times` tinyint(2) UNSIGNED NOT NULL DEFAULT 0,
  `remain_time` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `end_time` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `interval_time` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `data` int(4) UNSIGNED NOT NULL DEFAULT 0,
  PRIMARY KEY (`id`) USING BTREE,
  INDEX `idx_owner_id`(`owner_id`) USING BTREE
) ENGINE = MyISAM AUTO_INCREMENT = 2 CHARACTER SET = latin1 COLLATE = latin1_bin ROW_FORMAT = FIXED;

DROP TABLE IF EXISTS `cq_status_timeout`;
cq_status_timeout`;
CREATE TABLE `cq_status_timeout`  (
  `id` int(4) UNSIGNED NOT NULL AUTO_INCREMENT,
  `owner_id` int(4) NOT NULL DEFAULT 0,
  `status` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `power` int(4) NOT NULL DEFAULT 0,
  `sort` tinyint(1) UNSIGNED NOT NULL DEFAULT 0,
  `leave_times` tinyint(2) UNSIGNED NOT NULL DEFAULT 0,
  `remain_time` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `end_time` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `interval_time` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `data` int(4) UNSIGNED NOT NULL DEFAULT 0,
  PRIMARY KEY (`id`) USING BTREE,
  INDEX `idx_owner_id`(`owner_id`) USING BTREE
) ENGINE = MyISAM AUTO_INCREMENT = 1 CHARACTER SET = latin1 COLLATE = latin1_bin ROW_FORMAT = FIXED;

DROP TABLE IF EXISTS `cq_statustype`;
cq_statustype`;
CREATE TABLE `cq_statustype`  (
  `id` int(4) NOT NULL DEFAULT 0,
  `name` varchar(15) CHARACTER SET latin1 COLLATE latin1_bin NOT NULL DEFAULT '',
  `type` tinyint(2) UNSIGNED NOT NULL DEFAULT 0,
  `priorty` tinyint(2) UNSIGNED NOT NULL DEFAULT 0,
  PRIMARY KEY (`id`) USING BTREE
) ENGINE = MyISAM CHARACTER SET = latin1 COLLATE = latin1_bin ROW_FORMAT = DYNAMIC;

DROP TABLE IF EXISTS `cq_student_type`;
cq_student_type`;
CREATE TABLE `cq_student_type`  (
  `id` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `Student_lev` tinyint(3) UNSIGNED NOT NULL DEFAULT 0,
  `Type` tinyint(3) UNSIGNED NOT NULL DEFAULT 0,
  `User_lev_min` tinyint(3) UNSIGNED NOT NULL DEFAULT 0,
  `User_lev_max` tinyint(3) UNSIGNED NOT NULL DEFAULT 0,
  `Uplevtime` tinyint(3) UNSIGNED NOT NULL DEFAULT 0,
  `God_time` tinyint(3) UNSIGNED NOT NULL DEFAULT 0,
  `Addlevel` tinyint(3) UNSIGNED NOT NULL DEFAULT 0,
  PRIMARY KEY (`id`) USING BTREE
) ENGINE = MyISAM CHARACTER SET = latin1 COLLATE = latin1_bin ROW_FORMAT = FIXED;

DROP TABLE IF EXISTS `cq_super_flag`;
cq_super_flag`;
CREATE TABLE `cq_super_flag`  (
  `id` int(10) UNSIGNED NOT NULL AUTO_INCREMENT,
  `item_id` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `posindex` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `map_id` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `pos_x` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `pos_y` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `name` varbinary(31) NOT NULL DEFAULT '',
  PRIMARY KEY (`id`) USING BTREE,
  INDEX `index_item_id`(`item_id`) USING BTREE
) ENGINE = MyISAM AUTO_INCREMENT = 1 CHARACTER SET = latin1 COLLATE = latin1_bin ROW_FORMAT = DYNAMIC;

DROP TABLE IF EXISTS `cq_superman`;
cq_superman`;
CREATE TABLE `cq_superman`  (
  `id` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `number` int(4) UNSIGNED NOT NULL DEFAULT 0,
  PRIMARY KEY (`id`) USING BTREE
) ENGINE = MyISAM CHARACTER SET = latin1 COLLATE = latin1_bin ROW_FORMAT = FIXED;

DROP TABLE IF EXISTS `cq_syn_advertising_info`;
cq_syn_advertising_info`;
CREATE TABLE `cq_syn_advertising_info`  (
  `id` int(4) UNSIGNED NOT NULL AUTO_INCREMENT,
  `idsyn` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `content` varbinary(255) NULL DEFAULT NULL,
  `expense` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `end_date` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `auto_recruit` tinyint(1) UNSIGNED NOT NULL DEFAULT 0,
  `condition_level` tinyint(2) UNSIGNED NOT NULL DEFAULT 1,
  `condition_metem` tinyint(1) UNSIGNED NOT NULL DEFAULT 0,
  `condition_prof` tinyint(2) UNSIGNED NOT NULL DEFAULT 0,
  `condition_sex` tinyint(2) UNSIGNED NOT NULL DEFAULT 0,
  `condition_battle` smallint(2) UNSIGNED NOT NULL DEFAULT 0,
  PRIMARY KEY (`id`) USING BTREE
) ENGINE = MyISAM AUTO_INCREMENT = 1 CHARACTER SET = latin1 COLLATE = latin1_bin ROW_FORMAT = DYNAMIC;

DROP TABLE IF EXISTS `cq_syn_his`;
cq_syn_his`;
CREATE TABLE `cq_syn_his`  (
  `id` int(4) UNSIGNED NOT NULL AUTO_INCREMENT,
  `player_id` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `syn_id` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `proffer_his` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `proffer_emoney_his` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `proffer_edu_his` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `proffer_pk_his` int(4) UNSIGNED NOT NULL DEFAULT 0,
  PRIMARY KEY (`id`) USING BTREE
) ENGINE = MyISAM AUTO_INCREMENT = 1 CHARACTER SET = latin1 COLLATE = latin1_bin ROW_FORMAT = FIXED;

DROP TABLE IF EXISTS `cq_synattr`;
cq_synattr`;
CREATE TABLE `cq_synattr`  (
  `id` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `syn_id` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `rank` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `proffer` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `proffer_emoney` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `proffer_edu` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `proffer_pk` int(4) NOT NULL DEFAULT 0,
  `proffer_totem` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `proffer_his` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `proffer_emoney_his` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `proffer_edu_his` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `proffer_pk_his` int(4) NOT NULL DEFAULT 0,
  `flower` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `flower_w` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `flower_lily` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `flower_tulip` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `duty_time_limit` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `assistant_id` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `master_id` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `proffer_merit` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `join_date` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `proffer_plant` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `proffer_cultivation` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `proffer_fish` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `proffer_build` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `profession` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `last_logout` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `salary_flag` int(10) UNSIGNED NOT NULL DEFAULT 0,
  PRIMARY KEY (`id`) USING BTREE,
  INDEX `idx_syn_id`(`syn_id`) USING BTREE
) ENGINE = MyISAM CHARACTER SET = latin1 COLLATE = latin1_bin ROW_FORMAT = FIXED;

DROP TABLE IF EXISTS `cq_syncompeterank`;
cq_syncompeterank`;
CREATE TABLE `cq_syncompeterank`  (
  `id` int(4) UNSIGNED NOT NULL AUTO_INCREMENT,
  `rank` tinyint(4) UNSIGNED NOT NULL DEFAULT 0,
  `synid` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `relation` smallint(4) UNSIGNED NOT NULL DEFAULT 0,
  `point` int(4) UNSIGNED NOT NULL DEFAULT 0,
  PRIMARY KEY (`id`) USING BTREE
) ENGINE = MyISAM AUTO_INCREMENT = 9 CHARACTER SET = latin1 COLLATE = latin1_bin ROW_FORMAT = FIXED;

DROP TABLE IF EXISTS `cq_syndicate`;
cq_syndicate`;
CREATE TABLE `cq_syndicate`  (
  `id` int(4) UNSIGNED NOT NULL AUTO_INCREMENT,
  `name` varbinary(35) NOT NULL DEFAULT '',
  `announce` varbinary(255) NOT NULL DEFAULT '',
  `leader_title` varbinary(15) NOT NULL DEFAULT 'guildleader',
  `member_title` tinyint(1) NOT NULL DEFAULT 0,
  `leader_id` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `money` bigint(4) NOT NULL DEFAULT 0,
  `emoney` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `fealty_syn` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `del_flag` tinyint(1) UNSIGNED NOT NULL DEFAULT 0,
  `enemy0` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `enemy1` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `enemy2` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `enemy3` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `enemy4` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `enemy5` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `enemy6` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `enemy7` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `enemy8` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `enemy9` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `enemy10` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `enemy11` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `enemy12` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `enemy13` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `enemy14` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `ally0` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `ally1` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `ally2` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `ally3` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `ally4` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `ally5` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `ally6` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `ally7` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `ally8` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `ally9` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `ally10` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `ally11` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `ally12` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `ally13` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `ally14` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `condition_level` tinyint(2) UNSIGNED NOT NULL DEFAULT 1,
  `condition_metem` tinyint(1) UNSIGNED NOT NULL DEFAULT 0,
  `condition_prof` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `Publish_time` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `totem_pole` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `synrank` tinyint(1) UNSIGNED NOT NULL DEFAULT 0,
  `copper` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `iron` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `silver` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `gold` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `mulberry_wood` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `oak_wood` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `pear_wood` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `league_id` int(4) UNSIGNED NOT NULL DEFAULT 0,
  PRIMARY KEY (`id`) USING BTREE,
  UNIQUE INDEX `name`(`name`) USING BTREE
) ENGINE = MyISAM AUTO_INCREMENT = 4 CHARACTER SET = latin1 COLLATE = latin1_bin ROW_FORMAT = DYNAMIC;

DROP TABLE IF EXISTS `cq_syndomain`;
cq_syndomain`;
CREATE TABLE `cq_syndomain`  (
  `id` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `name` varchar(15) CHARACTER SET latin1 COLLATE latin1_bin NOT NULL DEFAULT 'undefined',
  `map_id` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `enter_x` int(4) NOT NULL DEFAULT 0,
  `enter_y` int(4) NOT NULL DEFAULT 0,
  `enter_cx` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `enter_cy` int(4) UNSIGNED NOT NULL DEFAULT 0,
  PRIMARY KEY (`id`) USING BTREE
) ENGINE = MyISAM CHARACTER SET = latin1 COLLATE = latin1_bin ROW_FORMAT = DYNAMIC;

DROP TABLE IF EXISTS `cq_synfacility`;
cq_synfacility`;
CREATE TABLE `cq_synfacility`  (
  `id` int(4) UNSIGNED NOT NULL AUTO_INCREMENT,
  `syn_id` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `type` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `pos_x` int(4) NOT NULL DEFAULT 0,
  `pos_y` int(4) NOT NULL DEFAULT 0,
  `dir` tinyint(1) UNSIGNED NOT NULL DEFAULT 0,
  `durable` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `data0` int(4) NOT NULL DEFAULT 0,
  `data1` int(4) NOT NULL DEFAULT 0,
  PRIMARY KEY (`id`) USING BTREE
) ENGINE = MyISAM AUTO_INCREMENT = 1 CHARACTER SET = latin1 COLLATE = latin1_bin ROW_FORMAT = FIXED;

DROP TABLE IF EXISTS `cq_synfacilitybuild`;
cq_synfacilitybuild`;
CREATE TABLE `cq_synfacilitybuild`  (
  `id` int(4) UNSIGNED NOT NULL AUTO_INCREMENT,
  `money` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `emoney` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `copper` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `iron` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `silver` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `gold` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `mulberry_wood` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `oak_wood` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `pear_wood` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `facility_req0` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `facility_req1` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `facility_req2` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `amount` tinyint(1) UNSIGNED NOT NULL DEFAULT 0,
  `region_limit` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `customize` tinyint(1) UNSIGNED NOT NULL DEFAULT 0,
  PRIMARY KEY (`id`) USING BTREE
) ENGINE = MyISAM AUTO_INCREMENT = 1 CHARACTER SET = latin1 COLLATE = latin1_bin ROW_FORMAT = FIXED;

DROP TABLE IF EXISTS `cq_synfacilitytype`;
cq_synfacilitytype`;
CREATE TABLE `cq_synfacilitytype`  (
  `id` int(4) UNSIGNED NOT NULL AUTO_INCREMENT,
  `sort` tinyint(1) UNSIGNED NOT NULL DEFAULT 0,
  `effect_sort` tinyint(1) UNSIGNED NOT NULL DEFAULT 0,
  `lev` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `effect0` int(4) NOT NULL DEFAULT 0,
  `effect1` int(4) NOT NULL DEFAULT 0,
  `effect2` int(4) NOT NULL DEFAULT 0,
  `task_id` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `durable_req` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `durable_limit` int(4) UNSIGNED NOT NULL DEFAULT 0,
  PRIMARY KEY (`id`) USING BTREE
) ENGINE = MyISAM AUTO_INCREMENT = 1 CHARACTER SET = latin1 COLLATE = latin1_bin ROW_FORMAT = FIXED;

DROP TABLE IF EXISTS `cq_synfood`;
cq_synfood`;
CREATE TABLE `cq_synfood`  (
  `id` int(4) UNSIGNED NOT NULL AUTO_INCREMENT,
  `syn_id` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `sort` tinyint(1) UNSIGNED NOT NULL DEFAULT 0,
  `itemtype_id` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `amount` int(4) UNSIGNED NOT NULL DEFAULT 0,
  PRIMARY KEY (`id`) USING BTREE
) ENGINE = MyISAM AUTO_INCREMENT = 1 CHARACTER SET = latin1 COLLATE = latin1_bin ROW_FORMAT = FIXED;

DROP TABLE IF EXISTS `cq_sys_leaveword`;
cq_sys_leaveword`;
CREATE TABLE `cq_sys_leaveword`  (
  `Id` int(10) UNSIGNED NOT NULL AUTO_INCREMENT,
  `type` smallint(5) UNSIGNED NOT NULL DEFAULT 1,
  `user_id` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `send_name` varbinary(15) NOT NULL DEFAULT 'unknown',
  `time` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `words` varbinary(255) NOT NULL DEFAULT 'undefined',
  `item_id` int(10) UNSIGNED NOT NULL DEFAULT 0,
  PRIMARY KEY (`Id`) USING BTREE,
  INDEX `index_userid`(`user_id`) USING BTREE
) ENGINE = MyISAM AUTO_INCREMENT = 1 CHARACTER SET = latin1 COLLATE = latin1_bin ROW_FORMAT = DYNAMIC;

DROP TABLE IF EXISTS `cq_sysbuyer`;
cq_sysbuyer`;
CREATE TABLE `cq_sysbuyer`  (
  `id` int(10) UNSIGNED NOT NULL AUTO_INCREMENT,
  `target_type` int(10) UNSIGNED NULL DEFAULT NULL,
  `buy_interval` int(10) UNSIGNED NULL DEFAULT NULL,
  `min_price` bigint(10) UNSIGNED ZEROFILL NULL DEFAULT NULL,
  `max_price` bigint(10) UNSIGNED ZEROFILL NULL DEFAULT NULL,
  PRIMARY KEY (`id`) USING BTREE
) ENGINE = MyISAM AUTO_INCREMENT = 2 CHARACTER SET = latin1 COLLATE = latin1_bin ROW_FORMAT = FIXED;

DROP TABLE IF EXISTS `cq_sysnpc`;
cq_sysnpc`;
CREATE TABLE `cq_sysnpc`  (
  `id` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `ownerid` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `playerid` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `name` varbinary(35) NOT NULL DEFAULT 'undefined',
  `type` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `lookface` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `idxserver` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `mapid` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `cellx` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `celly` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `task0` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `task1` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `task2` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `task3` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `task4` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `task5` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `task6` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `task7` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `data0` int(4) NOT NULL DEFAULT 0,
  `data1` int(4) NOT NULL DEFAULT 0,
  `data2` int(4) NOT NULL DEFAULT 0,
  `data3` int(4) NOT NULL DEFAULT 0,
  `datastr` varbinary(15) NULL DEFAULT 'None',
  `linkid` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `life` smallint(2) UNSIGNED NOT NULL DEFAULT 0,
  `maxlife` smallint(2) UNSIGNED NOT NULL DEFAULT 0,
  `base` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `sort` smallint(2) UNSIGNED NOT NULL DEFAULT 0,
  `itemid` int(4) UNSIGNED NOT NULL DEFAULT 0,
  PRIMARY KEY (`id`) USING BTREE
) ENGINE = MyISAM CHARACTER SET = latin1 COLLATE = latin1_bin ROW_FORMAT = DYNAMIC;

DROP TABLE IF EXISTS `cq_talkfromgm`;
cq_talkfromgm`;
CREATE TABLE `cq_talkfromgm`  (
  `id` int(4) UNSIGNED ZEROFILL NOT NULL AUTO_INCREMENT,
  `user_id` int(4) UNSIGNED ZEROFILL NOT NULL DEFAULT 0000,
  `content` varchar(512) CHARACTER SET latin1 COLLATE latin1_bin NOT NULL DEFAULT '',
  `time` int(4) UNSIGNED ZEROFILL NOT NULL DEFAULT 0000,
  PRIMARY KEY (`id`) USING BTREE
) ENGINE = MyISAM AUTO_INCREMENT = 6423 CHARACTER SET = latin1 COLLATE = latin1_bin ROW_FORMAT = DYNAMIC;

DROP TABLE IF EXISTS `cq_talktogm`;
cq_talktogm`;
CREATE TABLE `cq_talktogm`  (
  `id` int(4) UNSIGNED ZEROFILL NOT NULL AUTO_INCREMENT,
  `user_id` int(4) UNSIGNED ZEROFILL NOT NULL DEFAULT 0000,
  `vip` int(1) UNSIGNED ZEROFILL NOT NULL DEFAULT 0,
  `content` varchar(512) CHARACTER SET latin1 COLLATE latin1_bin NOT NULL DEFAULT '',
  `time` int(4) UNSIGNED ZEROFILL NOT NULL DEFAULT 0000,
  `status` int(4) UNSIGNED NOT NULL DEFAULT 0,
  PRIMARY KEY (`id`) USING BTREE
) ENGINE = MyISAM AUTO_INCREMENT = 6340 CHARACTER SET = latin1 COLLATE = latin1_bin ROW_FORMAT = DYNAMIC;

DROP TABLE IF EXISTS `cq_task`;
cq_task`;
CREATE TABLE `cq_task`  (
  `id` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `id_next` int(4) UNSIGNED NULL DEFAULT 0,
  `id_nextfail` int(4) UNSIGNED NULL DEFAULT 0,
  `itemname1` char(15) CHARACTER SET latin1 COLLATE latin1_bin NULL DEFAULT 'None',
  `itemname2` char(15) CHARACTER SET latin1 COLLATE latin1_bin NULL DEFAULT 'None',
  `money` int(4) UNSIGNED NULL DEFAULT 0,
  `profession` int(4) UNSIGNED NULL DEFAULT 0,
  `sex` int(4) UNSIGNED NULL DEFAULT 0,
  `min_pk` int(4) NULL DEFAULT 0,
  `max_pk` int(4) NULL DEFAULT 0,
  `team` int(4) UNSIGNED NULL DEFAULT 0,
  `metempsychosis` int(4) UNSIGNED NULL DEFAULT 0,
  `query` tinyint(1) UNSIGNED NOT NULL DEFAULT 0,
  `marriage` tinyint(4) NOT NULL DEFAULT -1,
  `client_active` tinyint(1) UNSIGNED NOT NULL DEFAULT 0,
  `remote_transfer` tinyint(1) UNSIGNED NOT NULL DEFAULT 0,
  PRIMARY KEY (`id`) USING BTREE
) ENGINE = MyISAM CHARACTER SET = latin1 COLLATE = latin1_bin ROW_FORMAT = FIXED;

DROP TABLE IF EXISTS `cq_task_reward_type`;
cq_task_reward_type`;
CREATE TABLE `cq_task_reward_type`  (
  `id` int(4) UNSIGNED ZEROFILL NOT NULL DEFAULT 0000,
  `type` tinyint(1) UNSIGNED ZEROFILL NOT NULL DEFAULT 0,
  `attribute` tinyint(1) UNSIGNED ZEROFILL NOT NULL DEFAULT 0,
  `value_base` int(4) UNSIGNED ZEROFILL NOT NULL DEFAULT 0000,
  `value_inc` int(4) UNSIGNED ZEROFILL NOT NULL DEFAULT 0000,
  `value_limit` int(4) UNSIGNED ZEROFILL NOT NULL DEFAULT 0000,
  `reward_type1` tinyint(1) UNSIGNED ZEROFILL NOT NULL DEFAULT 0,
  `reward_type2` tinyint(1) UNSIGNED ZEROFILL NOT NULL DEFAULT 0,
  `reward_type3` tinyint(1) UNSIGNED ZEROFILL NOT NULL DEFAULT 0,
  `reward_type4` tinyint(1) UNSIGNED ZEROFILL NOT NULL DEFAULT 0,
  `reward_type5` tinyint(1) UNSIGNED ZEROFILL NOT NULL DEFAULT 0,
  `reward_type6` tinyint(1) UNSIGNED ZEROFILL NOT NULL DEFAULT 0,
  `reward_type7` tinyint(1) UNSIGNED ZEROFILL NOT NULL DEFAULT 0,
  `reward_type8` tinyint(1) UNSIGNED ZEROFILL NOT NULL DEFAULT 0,
  `reward_value1` int(4) UNSIGNED ZEROFILL NOT NULL DEFAULT 0000,
  `reward_value2` int(4) UNSIGNED ZEROFILL NOT NULL DEFAULT 0000,
  `reward_value3` int(4) UNSIGNED ZEROFILL NOT NULL DEFAULT 0000,
  `reward_value4` int(4) UNSIGNED ZEROFILL NOT NULL DEFAULT 0000,
  `reward_value5` int(4) UNSIGNED ZEROFILL NOT NULL DEFAULT 0000,
  `reward_value6` int(4) UNSIGNED ZEROFILL NOT NULL DEFAULT 0000,
  `reward_value7` int(4) UNSIGNED ZEROFILL NOT NULL DEFAULT 0000,
  `reward_value8` int(4) UNSIGNED ZEROFILL NOT NULL DEFAULT 0000,
  `reward_type1_rate` smallint(2) UNSIGNED ZEROFILL NOT NULL DEFAULT 00,
  `reward_type2_rate` smallint(2) UNSIGNED ZEROFILL NOT NULL DEFAULT 00,
  `reward_type3_rate` smallint(2) UNSIGNED ZEROFILL NOT NULL DEFAULT 00,
  `reward_type4_rate` smallint(2) UNSIGNED ZEROFILL NOT NULL DEFAULT 00,
  `reward_type5_rate` smallint(2) UNSIGNED ZEROFILL NOT NULL DEFAULT 00,
  `reward_type6_rate` smallint(2) UNSIGNED ZEROFILL NOT NULL DEFAULT 00,
  `reward_type7_rate` smallint(2) UNSIGNED ZEROFILL NOT NULL DEFAULT 00,
  `reward_type8_rate` smallint(2) UNSIGNED ZEROFILL NOT NULL DEFAULT 00,
  `action_id` int(4) UNSIGNED ZEROFILL NOT NULL DEFAULT 0000,
  PRIMARY KEY (`id`) USING BTREE
) ENGINE = MyISAM CHARACTER SET = latin1 COLLATE = latin1_bin ROW_FORMAT = FIXED;

DROP TABLE IF EXISTS `cq_texas_table`;
cq_texas_table`;
CREATE TABLE `cq_texas_table`  (
  `id` int(4) UNSIGNED NOT NULL AUTO_INCREMENT,
  `table_type` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `chip_type` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `big_blind` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `min_card` tinyint(2) UNSIGNED NULL DEFAULT 0,
  PRIMARY KEY (`id`) USING BTREE,
  UNIQUE INDEX `money_limit_blinds`(`chip_type`, `table_type`, `big_blind`) USING BTREE
) ENGINE = MyISAM AUTO_INCREMENT = 2 CHARACTER SET = latin1 COLLATE = latin1_bin ROW_FORMAT = FIXED;

DROP TABLE IF EXISTS `cq_token_type`;
cq_token_type`;
CREATE TABLE `cq_token_type`  (
  `token_id` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `day_times` tinyint(4) NULL DEFAULT 0,
  `use_time` int(10) UNSIGNED NULL DEFAULT 0,
  `cd` int(10) UNSIGNED NULL DEFAULT 0,
  `fee` int(10) UNSIGNED NULL DEFAULT 0,
  `user1` int(10) NULL DEFAULT 0,
  `user2` int(10) NULL DEFAULT 0,
  `user3` int(10) NULL DEFAULT 0,
  `clean_cd` tinyint(4) UNSIGNED NULL DEFAULT 0,
  PRIMARY KEY (`token_id`) USING BTREE
) ENGINE = MyISAM CHARACTER SET = latin1 COLLATE = latin1_bin ROW_FORMAT = FIXED;

DROP TABLE IF EXISTS `cq_totem_add`;
cq_totem_add`;
CREATE TABLE `cq_totem_add`  (
  `id` int(4) UNSIGNED NOT NULL AUTO_INCREMENT,
  `totem_type` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `owner_id` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `battle_add` tinyint(1) UNSIGNED NOT NULL DEFAULT 0,
  `time_limit` int(8) UNSIGNED NOT NULL DEFAULT 0,
  PRIMARY KEY (`id`) USING BTREE
) ENGINE = MyISAM AUTO_INCREMENT = 2 CHARACTER SET = latin1 COLLATE = latin1_bin ROW_FORMAT = FIXED;

DROP TABLE IF EXISTS `cq_trap`;
cq_trap`;
CREATE TABLE `cq_trap`  (
  `id` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `type` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `look` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `owner_id` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `map_id` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `pos_x` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `pos_y` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `data` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `bound_cx` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `bound_cy` int(4) UNSIGNED NOT NULL DEFAULT 0,
  PRIMARY KEY (`id`) USING BTREE,
  INDEX `idx_map_id`(`map_id`) USING BTREE
) ENGINE = MyISAM CHARACTER SET = latin1 COLLATE = latin1_bin ROW_FORMAT = FIXED;

DROP TABLE IF EXISTS `cq_traptype`;
cq_traptype`;
CREATE TABLE `cq_traptype`  (
  `id` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `sort` tinyint(3) UNSIGNED NOT NULL DEFAULT 0,
  `look` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `action_id` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `level` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `attack_max` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `attack_min` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `dexterity` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `attack_speed` int(4) UNSIGNED NOT NULL DEFAULT 1000,
  `active_times` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `magic_type` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `magic_hitrate` int(4) UNSIGNED NOT NULL DEFAULT 100,
  `size` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `atk_mode` int(3) UNSIGNED NOT NULL DEFAULT 1,
  `life_max` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `name` varchar(15) CHARACTER SET latin1 COLLATE latin1_bin NOT NULL DEFAULT 'trap',
  PRIMARY KEY (`id`) USING BTREE
) ENGINE = MyISAM CHARACTER SET = latin1 COLLATE = latin1_bin ROW_FORMAT = DYNAMIC;

DROP TABLE IF EXISTS `cq_tutor`;
cq_tutor`;
CREATE TABLE `cq_tutor`  (
  `id` int(10) UNSIGNED NOT NULL AUTO_INCREMENT,
  `tutor_id` int(4) UNSIGNED NULL DEFAULT 0,
  `Student_id` int(4) UNSIGNED NULL DEFAULT 0,
  `Betrayal_flag` int(4) UNSIGNED NULL DEFAULT 0,
  `Date` int(4) UNSIGNED NULL DEFAULT NULL,
  PRIMARY KEY (`id`) USING BTREE,
  UNIQUE INDEX `u_student_id`(`Student_id`) USING BTREE,
  INDEX `index_tutor`(`tutor_id`) USING BTREE
) ENGINE = MyISAM AUTO_INCREMENT = 1 CHARACTER SET = latin1 COLLATE = latin1_bin ROW_FORMAT = FIXED;

DROP TABLE IF EXISTS `cq_tutor_access`;
cq_tutor_access`;
CREATE TABLE `cq_tutor_access`  (
  `id` int(10) UNSIGNED NOT NULL AUTO_INCREMENT,
  `tutor_id` int(4) UNSIGNED NULL DEFAULT 0,
  `Exp` bigint(4) UNSIGNED NULL DEFAULT 0,
  `God_time` smallint(2) UNSIGNED NULL DEFAULT 0,
  `Addlevel` smallint(2) UNSIGNED NULL DEFAULT 0,
  PRIMARY KEY (`id`) USING BTREE,
  UNIQUE INDEX `u_tutor_id`(`tutor_id`) USING BTREE
) ENGINE = MyISAM AUTO_INCREMENT = 1 CHARACTER SET = latin1 COLLATE = latin1_bin ROW_FORMAT = FIXED;

DROP TABLE IF EXISTS `cq_tutor_access_timeout`;
cq_tutor_access_timeout`;
CREATE TABLE `cq_tutor_access_timeout`  (
  `id` int(10) UNSIGNED NOT NULL AUTO_INCREMENT,
  `tutor_id` int(4) UNSIGNED NULL DEFAULT 0,
  `Exp` bigint(4) UNSIGNED NULL DEFAULT 0,
  `God_time` smallint(2) UNSIGNED NULL DEFAULT 0,
  `Addlevel` smallint(2) UNSIGNED NULL DEFAULT 0,
  PRIMARY KEY (`id`) USING BTREE,
  INDEX `index_tutor`(`tutor_id`) USING BTREE
) ENGINE = MyISAM AUTO_INCREMENT = 1 CHARACTER SET = latin1 COLLATE = latin1_bin ROW_FORMAT = FIXED;

DROP TABLE IF EXISTS `cq_tutor_battle_limit_type`;
cq_tutor_battle_limit_type`;
CREATE TABLE `cq_tutor_battle_limit_type`  (
  `id` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `Battle_lev_limit` smallint(2) UNSIGNED NOT NULL DEFAULT 0,
  PRIMARY KEY (`id`) USING BTREE
) ENGINE = MyISAM CHARACTER SET = latin1 COLLATE = latin1_bin ROW_FORMAT = FIXED;

DROP TABLE IF EXISTS `cq_tutor_contributions`;
cq_tutor_contributions`;
CREATE TABLE `cq_tutor_contributions`  (
  `id` int(10) UNSIGNED NOT NULL AUTO_INCREMENT,
  `tutor_id` int(4) UNSIGNED NULL DEFAULT 0,
  `Student_id` int(4) UNSIGNED NULL DEFAULT 0,
  `God_time` smallint(2) UNSIGNED NULL DEFAULT 0,
  `Exp` bigint(4) UNSIGNED NULL DEFAULT 0,
  `Addlevel` smallint(2) UNSIGNED NULL DEFAULT 0,
  PRIMARY KEY (`id`) USING BTREE,
  UNIQUE INDEX `u_student_id`(`Student_id`) USING BTREE
) ENGINE = MyISAM AUTO_INCREMENT = 1 CHARACTER SET = latin1 COLLATE = latin1_bin ROW_FORMAT = FIXED;

DROP TABLE IF EXISTS `cq_tutor_contributions2`;
cq_tutor_contributions2`;
CREATE TABLE `cq_tutor_contributions2`  (
  `id` int(10) UNSIGNED NOT NULL AUTO_INCREMENT,
  `tutor_id` int(4) UNSIGNED NULL DEFAULT 0,
  `Student_id` int(4) UNSIGNED NULL DEFAULT 0,
  `God_time` smallint(2) UNSIGNED NULL DEFAULT 0,
  `Exp` bigint(4) UNSIGNED NULL DEFAULT 0,
  `Addlevel` smallint(2) UNSIGNED NULL DEFAULT 0,
  PRIMARY KEY (`id`) USING BTREE,
  UNIQUE INDEX `u_student_id`(`Student_id`) USING BTREE
) ENGINE = MyISAM AUTO_INCREMENT = 1 CHARACTER SET = latin1 COLLATE = latin1_bin ROW_FORMAT = FIXED;

DROP TABLE IF EXISTS `cq_tutor_type`;
cq_tutor_type`;
CREATE TABLE `cq_tutor_type`  (
  `id` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `User_lev_min` tinyint(3) UNSIGNED NOT NULL DEFAULT 0,
  `User_lev_max` tinyint(3) UNSIGNED NOT NULL DEFAULT 0,
  `Student_num` tinyint(3) UNSIGNED NOT NULL DEFAULT 0,
  `Battle_lev_share` tinyint(3) UNSIGNED NOT NULL DEFAULT 0,
  PRIMARY KEY (`id`) USING BTREE
) ENGINE = MyISAM CHARACTER SET = latin1 COLLATE = latin1_bin ROW_FORMAT = FIXED;

DROP TABLE IF EXISTS `cq_unlawful`;
cq_unlawful`;
CREATE TABLE `cq_unlawful`  (
  `id` int(4) NOT NULL AUTO_INCREMENT,
  `word` varbinary(16) NOT NULL DEFAULT '',
  PRIMARY KEY (`id`) USING BTREE
) ENGINE = MyISAM AUTO_INCREMENT = 92 CHARACTER SET = latin1 COLLATE = latin1_bin ROW_FORMAT = DYNAMIC;

DROP TABLE IF EXISTS `cq_user`;
cq_user`;
CREATE TABLE `cq_user`  (
  `name` varbinary(15) NOT NULL DEFAULT '',
  `lastname` varbinary(15) NOT NULL DEFAULT '',
  `mateid` int(4) UNSIGNED NULL DEFAULT 0,
  `lookface` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `hair` smallint(2) UNSIGNED NOT NULL DEFAULT 0,
  `money` bigint(4) UNSIGNED NOT NULL DEFAULT 0,
  `money_saved` bigint(4) UNSIGNED NOT NULL DEFAULT 0,
  `coin_money` int(3) UNSIGNED NOT NULL DEFAULT 0,
  `level` tinyint(1) UNSIGNED NOT NULL DEFAULT 1,
  `exp` bigint(4) NOT NULL DEFAULT 0,
  `strength` smallint(2) UNSIGNED NOT NULL DEFAULT 0,
  `old_prof` tinyint(2) UNSIGNED NOT NULL DEFAULT 0,
  `Speed` smallint(2) UNSIGNED NOT NULL DEFAULT 0,
  `health` smallint(2) UNSIGNED NOT NULL DEFAULT 0,
  `soul` smallint(2) UNSIGNED NOT NULL DEFAULT 0,
  `additional_point` smallint(2) UNSIGNED NOT NULL DEFAULT 0,
  `auto_allot` tinyint(1) UNSIGNED NOT NULL DEFAULT 1,
  `life` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `mana` smallint(2) UNSIGNED NOT NULL DEFAULT 0,
  `profession` tinyint(2) UNSIGNED NOT NULL DEFAULT 0,
  `deed` int(4) NOT NULL DEFAULT 0,
  `pk` smallint(2) NOT NULL DEFAULT 0,
  `nobility` tinyint(1) UNSIGNED NOT NULL DEFAULT 0,
  `medal` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `medal_select` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `metempsychosis` tinyint(1) UNSIGNED NOT NULL DEFAULT 0,
  `recordmap_id` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `recordx` smallint(2) UNSIGNED NOT NULL DEFAULT 0,
  `recordy` smallint(2) UNSIGNED NOT NULL DEFAULT 0,
  `account_id` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `id` int(4) UNSIGNED NOT NULL AUTO_INCREMENT,
  `last_login` int(8) UNSIGNED NOT NULL DEFAULT 0,
  `first_login` int(8) UNSIGNED NOT NULL DEFAULT 0,
  `account` varchar(15) CHARACTER SET latin1 COLLATE latin1_bin NOT NULL DEFAULT 'None',
  `password` varchar(15) CHARACTER SET latin1 COLLATE latin1_bin NOT NULL DEFAULT 'None',
  `task_mask` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `time_of_life` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `virtue` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `home_id` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `lock_key` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `lock_cls` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `emoney` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `chk_sum` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `god_status` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `exp_ball_usage` smallint(2) UNSIGNED NOT NULL DEFAULT 0,
  `online_time` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `auto_exercise` tinyint(2) UNSIGNED NOT NULL DEFAULT 0,
  `last_logout` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `big_prize_fails` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `small_prize_fails` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `mete_lev` int(4) NOT NULL DEFAULT 0,
  `current_layout_type` tinyint(1) NOT NULL DEFAULT 0,
  `flower` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `online_time2` tinyint(4) UNSIGNED NOT NULL DEFAULT 0,
  `offline_time` tinyint(4) UNSIGNED NOT NULL DEFAULT 0,
  `last_logout2` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `donation` bigint(20) UNSIGNED NOT NULL DEFAULT 0,
  `business` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `send_flower_date` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `flower_r` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `flower_w` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `flower_lily` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `flower_tulip` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `quiz_point` int(4) UNSIGNED NULL DEFAULT 0,
  `vip_value` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `flag` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `first_prof` tinyint(2) UNSIGNED NOT NULL DEFAULT 0,
  `online_god_exptime` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `battle_god_exptime` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `mentor_opportunity` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `mentor_uplev_time` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `mentor_achieve` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `mentor_day` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `title` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `title_select` tinyint(3) UNSIGNED NOT NULL DEFAULT 0,
  `athlete_point` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `athlete_history_wins` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `athlete_history_loses` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `athlete_day_wins` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `athlete_day_loses` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `athlete_cur_honor_point` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `athlete_hisorty_honor_point` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `last_logout_3` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `emoney_mono` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `ridepet_point` int(4) UNSIGNED NULL DEFAULT 0,
  `current_ast_prof` tinyint(3) UNSIGNED NOT NULL DEFAULT 0,
  `ast_prof_rank` bigint(20) UNSIGNED NOT NULL DEFAULT 0,
  `cultivation` bigint(20) UNSIGNED NOT NULL DEFAULT 0,
  `changenamerecord` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `pkprotocol` tinyint(4) UNSIGNED NOT NULL DEFAULT 0,
  `family_arenic` tinyint(3) UNSIGNED NOT NULL DEFAULT 0,
  `uin` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `team_athlete_point` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `team_athlete_win` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `team_athlete_lost` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `team_athlete_season_win` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `team_athlete_season_lost` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `mete_lev2` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `strength_value` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `showtype` tinyint(3) UNSIGNED NOT NULL DEFAULT 0,
  `nationality` smallint(2) UNSIGNED NOT NULL DEFAULT 0,
  `pk_setting` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `culture_value` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `texasmatch_win` bigint(20) UNSIGNED NOT NULL DEFAULT 0,
  `texasmatch_lose` bigint(20) UNSIGNED NOT NULL DEFAULT 0,
  `chestpackage_size` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `league_contribution` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `shielded_times` smallint(4) UNSIGNED NOT NULL DEFAULT 0,
  `channel_account` varchar(74) CHARACTER SET latin1 COLLATE latin1_bin NOT NULL DEFAULT '',
  `bank_gold` bigint(20) NOT NULL DEFAULT 0,
  PRIMARY KEY (`id`) USING BTREE,
  UNIQUE INDEX `index_name`(`name`) USING BTREE,
  INDEX `index_account`(`account_id`) USING BTREE,
  INDEX `index_money`(`money_saved`) USING BTREE,
  INDEX `index_pk`(`pk`) USING BTREE,
  INDEX `index_level`(`level`, `profession`) USING BTREE,
  INDEX `tim`(`last_login`) USING BTREE,
  INDEX `index_profession`(`profession`) USING BTREE
) ENGINE = MyISAM AUTO_INCREMENT = 1000020 CHARACTER SET = latin1 COLLATE = latin1_bin ROW_FORMAT = DYNAMIC;

DROP TABLE IF EXISTS `cq_user_timeout`;
cq_user_timeout`;
CREATE TABLE `cq_user_timeout`  (
  `name` varbinary(15) NOT NULL DEFAULT '',
  `lastname` varbinary(15) NOT NULL DEFAULT '',
  `mateid` int(4) UNSIGNED NULL DEFAULT 0,
  `lookface` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `hair` smallint(2) UNSIGNED NOT NULL DEFAULT 0,
  `money` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `money_saved` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `coin_money` int(3) UNSIGNED NOT NULL DEFAULT 0,
  `level` tinyint(1) UNSIGNED NOT NULL DEFAULT 1,
  `exp` bigint(4) NOT NULL DEFAULT 0,
  `strength` smallint(2) UNSIGNED NOT NULL DEFAULT 0,
  `old_prof` tinyint(2) UNSIGNED NOT NULL DEFAULT 0,
  `Speed` smallint(2) UNSIGNED NOT NULL DEFAULT 0,
  `health` smallint(2) UNSIGNED NOT NULL DEFAULT 0,
  `soul` smallint(2) UNSIGNED NOT NULL DEFAULT 0,
  `additional_point` smallint(2) UNSIGNED NOT NULL DEFAULT 0,
  `auto_allot` tinyint(1) UNSIGNED NOT NULL DEFAULT 1,
  `life` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `mana` smallint(2) UNSIGNED NOT NULL DEFAULT 0,
  `profession` tinyint(2) UNSIGNED NOT NULL DEFAULT 0,
  `deed` int(4) NOT NULL DEFAULT 0,
  `pk` smallint(2) NOT NULL DEFAULT 0,
  `nobility` tinyint(1) UNSIGNED NOT NULL DEFAULT 0,
  `medal` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `medal_select` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `metempsychosis` tinyint(1) UNSIGNED NOT NULL DEFAULT 0,
  `recordmap_id` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `recordx` smallint(2) UNSIGNED NOT NULL DEFAULT 0,
  `recordy` smallint(2) UNSIGNED NOT NULL DEFAULT 0,
  `account_id` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `id` int(4) UNSIGNED NOT NULL AUTO_INCREMENT,
  `last_login` int(8) UNSIGNED NOT NULL DEFAULT 0,
  `first_login` int(8) UNSIGNED NOT NULL DEFAULT 0,
  `account` varchar(15) CHARACTER SET latin1 COLLATE latin1_bin NOT NULL DEFAULT 'None',
  `password` varchar(15) CHARACTER SET latin1 COLLATE latin1_bin NOT NULL DEFAULT 'None',
  `task_mask` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `time_of_life` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `virtue` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `home_id` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `lock_key` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `lock_cls` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `emoney` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `chk_sum` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `god_status` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `exp_ball_usage` smallint(2) UNSIGNED NOT NULL DEFAULT 0,
  `online_time` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `auto_exercise` tinyint(2) UNSIGNED NOT NULL DEFAULT 0,
  `last_logout` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `big_prize_fails` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `small_prize_fails` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `mete_lev` int(4) NOT NULL DEFAULT 0,
  `current_layout_type` tinyint(1) NOT NULL DEFAULT 0,
  `flower` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `online_time2` tinyint(4) UNSIGNED NOT NULL DEFAULT 0,
  `offline_time` tinyint(4) UNSIGNED NOT NULL DEFAULT 0,
  `last_logout2` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `donation` bigint(20) UNSIGNED NOT NULL DEFAULT 0,
  `business` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `send_flower_date` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `flower_r` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `flower_w` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `flower_lily` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `flower_tulip` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `quiz_point` int(4) UNSIGNED NULL DEFAULT 0,
  `vip_value` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `flag` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `first_prof` tinyint(2) UNSIGNED NOT NULL DEFAULT 0,
  `online_god_exptime` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `battle_god_exptime` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `mentor_opportunity` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `mentor_uplev_time` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `mentor_achieve` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `mentor_day` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `title` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `title_select` tinyint(3) UNSIGNED NOT NULL DEFAULT 0,
  `athlete_point` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `athlete_history_wins` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `athlete_history_loses` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `athlete_day_wins` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `athlete_day_loses` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `athlete_cur_honor_point` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `athlete_hisorty_honor_point` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `last_logout_3` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `emoney_mono` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `ridepet_point` int(4) UNSIGNED NULL DEFAULT 0,
  `current_ast_prof` tinyint(3) UNSIGNED NOT NULL DEFAULT 0,
  `ast_prof_rank` bigint(20) UNSIGNED NOT NULL DEFAULT 0,
  `cultivation` bigint(20) UNSIGNED NOT NULL DEFAULT 0,
  `changenamerecord` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `pkprotocol` tinyint(4) UNSIGNED NOT NULL DEFAULT 0,
  `family_arenic` tinyint(3) UNSIGNED NOT NULL DEFAULT 0,
  `uin` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `team_athlete_point` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `team_athlete_win` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `team_athlete_lost` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `team_athlete_season_win` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `team_athlete_season_lost` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `mete_lev2` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `strength_value` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `showtype` tinyint(3) UNSIGNED NOT NULL DEFAULT 0,
  `nationality` smallint(2) UNSIGNED NOT NULL DEFAULT 0,
  `pk_setting` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `culture_value` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `texasmatch_win` bigint(20) UNSIGNED NOT NULL DEFAULT 0,
  `texasmatch_lose` bigint(20) UNSIGNED NOT NULL DEFAULT 0,
  `chestpackage_size` tinyint(2) UNSIGNED NOT NULL DEFAULT 0,
  `league_contribution` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `shielded_times` smallint(4) UNSIGNED NOT NULL DEFAULT 0,
  `channel_account` varchar(74) CHARACTER SET latin1 COLLATE latin1_bin NOT NULL DEFAULT '',
  PRIMARY KEY (`id`) USING BTREE,
  UNIQUE INDEX `index_name`(`name`) USING BTREE,
  INDEX `index_account`(`account_id`) USING BTREE,
  INDEX `index_money`(`money_saved`) USING BTREE,
  INDEX `index_pk`(`pk`) USING BTREE,
  INDEX `index_level`(`level`, `profession`) USING BTREE,
  INDEX `tim`(`last_login`) USING BTREE,
  INDEX `index_profession`(`profession`) USING BTREE
) ENGINE = MyISAM AUTO_INCREMENT = 1000000 CHARACTER SET = latin1 COLLATE = latin1_bin ROW_FORMAT = DYNAMIC;

DROP TABLE IF EXISTS `cq_user_timeout1`;
cq_user_timeout1`;
CREATE TABLE `cq_user_timeout1`  (
  `name` varbinary(15) NOT NULL DEFAULT '',
  `mate` varbinary(15) NOT NULL DEFAULT 'None',
  `lookface` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `hair` smallint(2) UNSIGNED NOT NULL DEFAULT 0,
  `money` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `money_saved` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `coin_money` int(3) UNSIGNED NOT NULL DEFAULT 0,
  `level` tinyint(1) UNSIGNED NOT NULL DEFAULT 1,
  `exp` bigint(4) NOT NULL DEFAULT 0,
  `strength` smallint(2) UNSIGNED NOT NULL DEFAULT 0,
  `old_prof` smallint(2) UNSIGNED NOT NULL DEFAULT 0,
  `Speed` smallint(2) UNSIGNED NOT NULL DEFAULT 0,
  `health` smallint(2) UNSIGNED NOT NULL DEFAULT 0,
  `soul` smallint(2) UNSIGNED NOT NULL DEFAULT 0,
  `additional_point` smallint(2) UNSIGNED NOT NULL DEFAULT 0,
  `auto_allot` tinyint(1) UNSIGNED NOT NULL DEFAULT 1,
  `life` smallint(2) UNSIGNED NOT NULL DEFAULT 0,
  `mana` smallint(2) UNSIGNED NOT NULL DEFAULT 0,
  `profession` tinyint(2) UNSIGNED NOT NULL DEFAULT 0,
  `deed` int(4) NOT NULL DEFAULT 0,
  `pk` smallint(2) NOT NULL DEFAULT 0,
  `nobility` tinyint(1) UNSIGNED NOT NULL DEFAULT 0,
  `medal` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `medal_select` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `metempsychosis` tinyint(1) UNSIGNED NOT NULL DEFAULT 0,
  `syndicate_id` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `recordmap_id` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `recordx` smallint(2) UNSIGNED NOT NULL DEFAULT 0,
  `recordy` smallint(2) UNSIGNED NOT NULL DEFAULT 0,
  `account_id` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `id` int(4) UNSIGNED NOT NULL AUTO_INCREMENT,
  `last_login` int(8) UNSIGNED NOT NULL DEFAULT 0,
  `account` varchar(15) CHARACTER SET latin1 COLLATE latin1_bin NOT NULL DEFAULT 'None',
  `password` varchar(15) CHARACTER SET latin1 COLLATE latin1_bin NOT NULL DEFAULT 'None',
  `task_mask` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `time_of_life` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `virtue` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `home_id` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `lock_key` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `lock_cls` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `emoney` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `chk_sum` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `god_status` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `exp_ball_usage` smallint(2) UNSIGNED NOT NULL DEFAULT 0,
  `online_time` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `auto_exercise` tinyint(2) UNSIGNED NOT NULL DEFAULT 0,
  `last_logout` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `big_prize_fails` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `small_prize_fails` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `mete_lev` int(4) NOT NULL DEFAULT 0,
  `current_layout_type` tinyint(1) NOT NULL DEFAULT 0,
  `flower` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `online_time2` tinyint(4) UNSIGNED NOT NULL DEFAULT 0,
  `offline_time` tinyint(4) UNSIGNED NOT NULL DEFAULT 0,
  `last_logout2` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `donation` bigint(20) UNSIGNED NOT NULL DEFAULT 0,
  `business` int(4) UNSIGNED NOT NULL DEFAULT 0,
  PRIMARY KEY (`id`) USING BTREE,
  UNIQUE INDEX `index_name`(`name`) USING BTREE,
  INDEX `index_account`(`account_id`) USING BTREE,
  INDEX `index_money`(`money_saved`) USING BTREE,
  INDEX `index_pk`(`pk`) USING BTREE,
  INDEX `index_level`(`level`, `profession`) USING BTREE,
  INDEX `tim`(`last_login`) USING BTREE,
  INDEX `index_profession`(`profession`) USING BTREE,
  INDEX `index_mate`(`mate`) USING BTREE,
  INDEX `idx_mate`(`mate`) USING BTREE,
  INDEX `idx_syndicate_id`(`syndicate_id`) USING BTREE
) ENGINE = MyISAM AUTO_INCREMENT = 1 CHARACTER SET = latin1 COLLATE = latin1_bin ROW_FORMAT = DYNAMIC;

DROP TABLE IF EXISTS `cq_valid_user`;
cq_valid_user`;
CREATE TABLE `cq_valid_user`  (
  `id` int(10) UNSIGNED NOT NULL DEFAULT 0,
  PRIMARY KEY (`id`) USING BTREE
) ENGINE = MyISAM CHARACTER SET = latin1 COLLATE = latin1_bin ROW_FORMAT = FIXED;

DROP TABLE IF EXISTS `cq_vexillum`;
cq_vexillum`;
CREATE TABLE `cq_vexillum`  (
  `id` int(4) UNSIGNED NOT NULL AUTO_INCREMENT,
  `synid` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `type` tinyint(3) UNSIGNED NOT NULL DEFAULT 0,
  `score` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `usercount` smallint(4) UNSIGNED NOT NULL DEFAULT 0,
  `lastmeedmoney` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `lastmeedemoney` int(4) UNSIGNED NOT NULL DEFAULT 0,
  PRIMARY KEY (`id`) USING BTREE
) ENGINE = MyISAM AUTO_INCREMENT = 1 CHARACTER SET = latin1 COLLATE = latin1_bin ROW_FORMAT = FIXED;

DROP TABLE IF EXISTS `cq_vipminetime`;
cq_vipminetime`;
CREATE TABLE `cq_vipminetime`  (
  `iduser` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `lastentertime` int(4) UNSIGNED NOT NULL DEFAULT 0,
  PRIMARY KEY (`iduser`) USING BTREE
) ENGINE = MyISAM CHARACTER SET = latin1 COLLATE = latin1_bin ROW_FORMAT = FIXED;

DROP TABLE IF EXISTS `cq_viptranspoint`;
cq_viptranspoint`;
CREATE TABLE `cq_viptranspoint`  (
  `id` int(4) UNSIGNED NOT NULL AUTO_INCREMENT,
  `type` tinyint(3) UNSIGNED NOT NULL DEFAULT 0,
  `map_id` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `map_x` smallint(5) UNSIGNED NOT NULL DEFAULT 0,
  `map_y` smallint(5) UNSIGNED NOT NULL DEFAULT 0,
  `point_name` char(35) CHARACTER SET latin1 COLLATE latin1_bin NOT NULL DEFAULT '',
  PRIMARY KEY (`id`) USING BTREE
) ENGINE = MyISAM AUTO_INCREMENT = 32 CHARACTER SET = latin1 COLLATE = latin1_bin ROW_FORMAT = FIXED;

DROP TABLE IF EXISTS `cq_virtual_gm`;
cq_virtual_gm`;
CREATE TABLE `cq_virtual_gm`  (
  `id` int(10) UNSIGNED NOT NULL AUTO_INCREMENT,
  `name` varbinary(15) NOT NULL DEFAULT '',
  `password` varbinary(50) NOT NULL DEFAULT '',
  PRIMARY KEY (`id`) USING BTREE
) ENGINE = MyISAM AUTO_INCREMENT = 2 CHARACTER SET = latin1 COLLATE = latin1_bin ROW_FORMAT = DYNAMIC;

DROP TABLE IF EXISTS `cq_wanted`;
cq_wanted`;
CREATE TABLE `cq_wanted`  (
  `id` int(4) UNSIGNED NOT NULL AUTO_INCREMENT,
  `target_name` varbinary(15) NULL DEFAULT NULL,
  `target_lev` tinyint(3) UNSIGNED NOT NULL DEFAULT 0,
  `target_pro` tinyint(3) UNSIGNED NOT NULL DEFAULT 0,
  `target_syn` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `payer` varbinary(15) NULL DEFAULT NULL,
  `bounty` int(4) UNSIGNED NULL DEFAULT NULL,
  `order_time` int(4) UNSIGNED NULL DEFAULT NULL,
  `hunter` varbinary(15) NULL DEFAULT NULL,
  `finish_time` int(4) UNSIGNED NULL DEFAULT NULL,
  PRIMARY KEY (`id`) USING BTREE
) ENGINE = MyISAM AUTO_INCREMENT = 1 CHARACTER SET = latin1 COLLATE = latin1_bin ROW_FORMAT = DYNAMIC;

DROP TABLE IF EXISTS `cq_weapon_skill`;
cq_weapon_skill`;
CREATE TABLE `cq_weapon_skill`  (
  `type` int(4) UNSIGNED NULL DEFAULT 0,
  `level` tinyint(2) UNSIGNED NULL DEFAULT 0,
  `exp` int(4) UNSIGNED NULL DEFAULT 0,
  `old_level` tinyint(2) UNSIGNED NULL DEFAULT 0,
  `owner_id` int(4) UNSIGNED NULL DEFAULT 0,
  `id` int(4) UNSIGNED NOT NULL AUTO_INCREMENT,
  `unlearn` tinyint(1) UNSIGNED NOT NULL DEFAULT 0,
  PRIMARY KEY (`id`) USING BTREE,
  INDEX `idx_ownerid_type`(`owner_id`, `type`) USING BTREE
) ENGINE = MyISAM AUTO_INCREMENT = 70 CHARACTER SET = latin1 COLLATE = latin1_bin ROW_FORMAT = FIXED;

DROP TABLE IF EXISTS `cq_weapon_skill_timeout`;
cq_weapon_skill_timeout`;
CREATE TABLE `cq_weapon_skill_timeout`  (
  `type` int(4) UNSIGNED NULL DEFAULT 0,
  `level` tinyint(2) UNSIGNED NULL DEFAULT 0,
  `exp` int(4) UNSIGNED NULL DEFAULT 0,
  `old_level` tinyint(2) UNSIGNED NULL DEFAULT 0,
  `owner_id` int(4) UNSIGNED NULL DEFAULT 0,
  `id` int(4) UNSIGNED NOT NULL AUTO_INCREMENT,
  `unlearn` tinyint(1) UNSIGNED NOT NULL DEFAULT 0,
  PRIMARY KEY (`id`) USING BTREE,
  INDEX `owner_id`(`owner_id`) USING BTREE
) ENGINE = MyISAM AUTO_INCREMENT = 1 CHARACTER SET = latin1 COLLATE = latin1_bin ROW_FORMAT = FIXED;

DROP TABLE IF EXISTS `cq_weapon_skill_up`;
cq_weapon_skill_up`;
CREATE TABLE `cq_weapon_skill_up`  (
  `id` int(4) UNSIGNED NOT NULL AUTO_INCREMENT,
  `weapontype` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `level` tinyint(4) UNSIGNED NOT NULL DEFAULT 0,
  `req_exp` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `req_uplevtime` int(4) UNSIGNED NOT NULL DEFAULT 0,
  PRIMARY KEY (`id`) USING BTREE,
  INDEX `idx_orderby`(`weapontype`, `level`) USING BTREE
) ENGINE = MyISAM AUTO_INCREMENT = 652 CHARACTER SET = latin1 COLLATE = latin1_bin ROW_FORMAT = FIXED;

DROP TABLE IF EXISTS `dbbrushlog`;
dbbrushlog`;
CREATE TABLE `dbbrushlog`  (
  `LogID` bigint(20) NOT NULL AUTO_INCREMENT,
  `RecordDate` bigint(20) NULL DEFAULT 0,
  `Module` int(11) NULL DEFAULT 0,
  `GameClass` int(11) NULL DEFAULT 0,
  `GameID` int(11) NULL DEFAULT 0,
  `RunThread` blob NULL,
  `Level` varchar(50) CHARACTER SET latin1 COLLATE latin1_bin NULL DEFAULT NULL,
  `LoggerMsg` blob NULL,
  `Sqlsmt` blob NULL,
  `ServerConn` blob NULL,
  `ServerID` int(11) NULL DEFAULT 0,
  `RetryTimes` bigint(20) NULL DEFAULT 0,
  PRIMARY KEY (`LogID`) USING BTREE,
  UNIQUE INDEX `LogID`(`LogID`) USING BTREE
) ENGINE = MyISAM AUTO_INCREMENT = 1 CHARACTER SET = latin1 COLLATE = latin1_bin ROW_FORMAT = DYNAMIC;

DROP TABLE IF EXISTS `dyna_rank_rec`;
dyna_rank_rec`;
CREATE TABLE `dyna_rank_rec`  (
  `id` int(4) UNSIGNED NOT NULL AUTO_INCREMENT,
  `rank_type` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `value` bigint(4) NOT NULL DEFAULT 0,
  `user_id` int(4) UNSIGNED NOT NULL DEFAULT 0,
  PRIMARY KEY (`id`) USING BTREE,
  UNIQUE INDEX `id`(`id`) USING BTREE,
  INDEX `sort`(`rank_type`, `value`) USING BTREE
) ENGINE = MyISAM AUTO_INCREMENT = 6 CHARACTER SET = latin1 COLLATE = latin1_bin ROW_FORMAT = FIXED;

DROP TABLE IF EXISTS `dyna_rank_type`;
dyna_rank_type`;
CREATE TABLE `dyna_rank_type`  (
  `id` int(4) UNSIGNED NOT NULL AUTO_INCREMENT,
  `rank_type` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `rank_num` smallint(2) UNSIGNED NOT NULL DEFAULT 0,
  `rank_data_min` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `reset_time_type` tinyint(1) UNSIGNED NOT NULL DEFAULT 0,
  `comment` varchar(20) CHARACTER SET latin1 COLLATE latin1_bin NOT NULL DEFAULT '',
  PRIMARY KEY (`id`) USING BTREE,
  UNIQUE INDEX `id`(`id`, `rank_type`) USING BTREE
) ENGINE = MyISAM AUTO_INCREMENT = 2 CHARACTER SET = latin1 COLLATE = latin1_bin ROW_FORMAT = DYNAMIC;

DROP TABLE IF EXISTS `e_money`;
e_money`;
CREATE TABLE `e_money`  (
  `id` int(4) UNSIGNED NOT NULL AUTO_INCREMENT,
  `type` tinyint(1) UNSIGNED NOT NULL DEFAULT 0,
  `id_source` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `id_target` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `number` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `chk_sum` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `time_stamp` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `source_balance` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `target_balance` int(4) UNSIGNED NOT NULL DEFAULT 0,
  PRIMARY KEY (`id`) USING BTREE,
  INDEX `idx_time_stamp`(`time_stamp`) USING BTREE,
  INDEX `idx_id_source`(`id_source`) USING BTREE,
  INDEX `idx_id_target`(`id_target`) USING BTREE,
  INDEX `idx_type`(`type`) USING BTREE
) ENGINE = MyISAM AUTO_INCREMENT = 23450 CHARACTER SET = latin1 COLLATE = latin1_bin ROW_FORMAT = FIXED;

DROP TABLE IF EXISTS `e_money_mono`;
e_money_mono`;
CREATE TABLE `e_money_mono`  (
  `id` int(4) UNSIGNED NOT NULL AUTO_INCREMENT,
  `type` tinyint(1) UNSIGNED NOT NULL DEFAULT 0,
  `id_source` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `id_target` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `number` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `chk_sum` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `time_stamp` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `source_balance` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `target_balance` int(4) UNSIGNED NOT NULL DEFAULT 0,
  PRIMARY KEY (`id`) USING BTREE
) ENGINE = MyISAM AUTO_INCREMENT = 47 CHARACTER SET = latin1 COLLATE = latin1_bin ROW_FORMAT = FIXED;

DROP TABLE IF EXISTS `e_money_month`;
e_money_month`;
CREATE TABLE `e_money_month`  (
  `id` int(4) UNSIGNED NOT NULL AUTO_INCREMENT,
  `type` tinyint(1) UNSIGNED NOT NULL DEFAULT 0,
  `id_source` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `id_target` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `number` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `chk_sum` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `time_stamp` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `source_emoney` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `target_emoney` int(4) UNSIGNED NOT NULL DEFAULT 0,
  PRIMARY KEY (`id`) USING BTREE,
  INDEX `index_type`(`type`) USING BTREE,
  INDEX `index_source`(`id_source`) USING BTREE,
  INDEX `index_time`(`time_stamp`) USING BTREE,
  INDEX `idx_id_source_target`(`id_source`, `id_target`) USING BTREE,
  INDEX `idx_target`(`id_target`) USING BTREE
) ENGINE = MyISAM AUTO_INCREMENT = 1 CHARACTER SET = latin1 COLLATE = latin1_bin ROW_FORMAT = FIXED;

DROP TABLE IF EXISTS `emoney_card`;
emoney_card`;
CREATE TABLE `emoney_card`  (
  `id` int(4) UNSIGNED NOT NULL AUTO_INCREMENT,
  `type` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `account_id` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `ref_id` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `chk_sum` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `time_stamp` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `used` tinyint(2) UNSIGNED NOT NULL DEFAULT 1,
  `ordernumber` varchar(50) CHARACTER SET latin1 COLLATE latin1_bin NULL DEFAULT NULL,
  `flag` tinyint(2) UNSIGNED NULL DEFAULT 0,
  `card_in_time` int(11) NOT NULL DEFAULT 0,
  PRIMARY KEY (`id`) USING BTREE,
  INDEX `account_id`(`account_id`) USING BTREE,
  INDEX `condition`(`account_id`, `used`, `chk_sum`) USING BTREE,
  INDEX `idx_time_stamp`(`time_stamp`) USING BTREE,
  INDEX `card_in_time`(`card_in_time`) USING BTREE
) ENGINE = MyISAM AUTO_INCREMENT = 1 CHARACTER SET = latin1 COLLATE = latin1_bin ROW_FORMAT = DYNAMIC;

DROP TABLE IF EXISTS `emoney_card_google`;
emoney_card_google`;
CREATE TABLE `emoney_card_google`  (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `type` int(11) NULL DEFAULT 0,
  `account_id` int(11) NULL DEFAULT 0,
  `chk_sum` int(11) NULL DEFAULT 0,
  `time_stamp` int(11) NULL DEFAULT 0,
  `used` int(11) NULL DEFAULT 0,
  `ordernumber` varchar(50) CHARACTER SET latin1 COLLATE latin1_bin NULL DEFAULT '',
  `flag` int(11) NULL DEFAULT 0,
  `card_in_time` int(11) NULL DEFAULT 0,
  `itemcount` int(11) NULL DEFAULT 0,
  `systemtype` int(11) NULL DEFAULT 0,
  `ref_id` int(11) NULL DEFAULT 0,
  `roleid` int(11) NULL DEFAULT 0,
  `producer_order` varchar(50) CHARACTER SET latin1 COLLATE latin1_bin NULL DEFAULT '',
  PRIMARY KEY (`id`) USING BTREE,
  INDEX `used`(`used`) USING BTREE
) ENGINE = MyISAM AUTO_INCREMENT = 1 CHARACTER SET = latin1 COLLATE = latin1_bin ROW_FORMAT = DYNAMIC;

DROP TABLE IF EXISTS `emoney_card_ndsdk`;
emoney_card_ndsdk`;
CREATE TABLE `emoney_card_ndsdk`  (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `type` int(11) NULL DEFAULT 0,
  `account_id` varchar(64) CHARACTER SET latin1 COLLATE latin1_bin NOT NULL DEFAULT '',
  `chk_sum` int(11) NULL DEFAULT 0,
  `time_stamp` int(11) NULL DEFAULT 0,
  `used` int(11) NULL DEFAULT 0,
  `ordernumber` varchar(50) CHARACTER SET latin1 COLLATE latin1_bin NULL DEFAULT '',
  `flag` int(11) NULL DEFAULT 0,
  `card_in_time` int(11) NULL DEFAULT 0,
  `itemcount` int(11) NULL DEFAULT 0,
  `systemtype` int(11) NULL DEFAULT 0,
  `ref_id` int(11) NULL DEFAULT 0,
  `roleid` int(11) NULL DEFAULT 0,
  `producer_order` varchar(50) CHARACTER SET latin1 COLLATE latin1_bin NULL DEFAULT '',
  `account_systemtype` int(11) UNSIGNED NOT NULL DEFAULT 0,
  `exchange_type` int(11) UNSIGNED NOT NULL DEFAULT 0,
  PRIMARY KEY (`id`) USING BTREE,
  INDEX `used`(`used`) USING BTREE,
  INDEX `userid_used`(`used`, `roleid`) USING BTREE
) ENGINE = MyISAM AUTO_INCREMENT = 1 CHARACTER SET = latin1 COLLATE = latin1_bin ROW_FORMAT = DYNAMIC;

DROP TABLE IF EXISTS `emoney_card2`;
emoney_card2`;
CREATE TABLE `emoney_card2`  (
  `id` int(4) UNSIGNED NOT NULL AUTO_INCREMENT,
  `type` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `account_id` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `ref_id` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `chk_sum` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `time_stamp` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `used` tinyint(2) UNSIGNED NOT NULL DEFAULT 1,
  `ordernumber` varchar(50) CHARACTER SET latin1 COLLATE latin1_bin NULL DEFAULT NULL,
  `flag` tinyint(2) UNSIGNED NULL DEFAULT 0,
  `card_in_time` int(11) NOT NULL DEFAULT 0,
  PRIMARY KEY (`id`) USING BTREE,
  INDEX `account_id`(`account_id`) USING BTREE,
  INDEX `condition`(`account_id`, `used`, `chk_sum`) USING BTREE,
  INDEX `idx_time_stamp`(`time_stamp`) USING BTREE,
  INDEX `card_in_time`(`card_in_time`) USING BTREE,
  INDEX `idx_ordnum`(`ordernumber`) USING BTREE
) ENGINE = MyISAM AUTO_INCREMENT = 1 CHARACTER SET = latin1 COLLATE = latin1_bin ROW_FORMAT = DYNAMIC;

DROP TABLE IF EXISTS `emoney_card3`;
emoney_card3`;
CREATE TABLE `emoney_card3`  (
  `id` int(4) UNSIGNED NOT NULL AUTO_INCREMENT,
  `type` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `account_id` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `ref_id` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `chk_sum` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `time_stamp` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `used` tinyint(2) UNSIGNED NOT NULL DEFAULT 1,
  `ordernumber` varchar(40) CHARACTER SET latin1 COLLATE latin1_bin NULL DEFAULT NULL,
  `flag` tinyint(2) UNSIGNED NULL DEFAULT 0,
  `card_in_time` int(10) UNSIGNED NULL DEFAULT NULL,
  PRIMARY KEY (`id`) USING BTREE,
  INDEX `idx_account_id`(`account_id`) USING BTREE
) ENGINE = MyISAM AUTO_INCREMENT = 1 CHARACTER SET = latin1 COLLATE = latin1_bin ROW_FORMAT = DYNAMIC;

DROP TABLE IF EXISTS `emoney_card4`;
emoney_card4`;
CREATE TABLE `emoney_card4`  (
  `id` int(4) UNSIGNED NOT NULL AUTO_INCREMENT,
  `type` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `account_id` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `ref_id` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `chk_sum` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `time_stamp` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `used` tinyint(2) UNSIGNED NOT NULL DEFAULT 1,
  `ordernumber` varchar(40) CHARACTER SET latin1 COLLATE latin1_bin NULL DEFAULT NULL,
  `flag` tinyint(2) UNSIGNED NULL DEFAULT 0,
  `card_in_time` int(10) UNSIGNED NULL DEFAULT NULL,
  PRIMARY KEY (`id`) USING BTREE,
  INDEX `idx_account_id`(`account_id`) USING BTREE
) ENGINE = MyISAM AUTO_INCREMENT = 1 CHARACTER SET = latin1 COLLATE = latin1_bin ROW_FORMAT = DYNAMIC;

DROP TABLE IF EXISTS `emoney_card91`;
emoney_card91`;
CREATE TABLE `emoney_card91`  (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `type` int(11) NULL DEFAULT 0,
  `account_id` int(11) NULL DEFAULT 0,
  `chk_sum` int(11) NULL DEFAULT 0,
  `time_stamp` int(11) NULL DEFAULT 0,
  `used` int(11) NULL DEFAULT 0,
  `ordernumber` varchar(50) CHARACTER SET latin1 COLLATE latin1_bin NULL DEFAULT '',
  `flag` int(11) NULL DEFAULT 0,
  `card_in_time` int(11) NULL DEFAULT 0,
  `itemcount` int(11) NULL DEFAULT 0,
  `systemtype` int(11) NULL DEFAULT 0,
  `ref_id` int(11) NULL DEFAULT 0,
  `roleid` int(11) NULL DEFAULT 0,
  `producer_order` varchar(50) CHARACTER SET latin1 COLLATE latin1_bin NULL DEFAULT '',
  PRIMARY KEY (`id`) USING BTREE,
  INDEX `idx_account_id`(`account_id`) USING BTREE
) ENGINE = MyISAM AUTO_INCREMENT = 1 CHARACTER SET = latin1 COLLATE = latin1_bin ROW_FORMAT = DYNAMIC;

DROP TABLE IF EXISTS `emoneybak`;
emoneybak`;
CREATE TABLE `emoneybak`  (
  `number` int(4) NULL DEFAULT NULL,
  `type` int(4) NULL DEFAULT NULL,
  `id_target` int(4) NULL DEFAULT NULL,
  `Id` int(11) NOT NULL DEFAULT 0,
  `id_source` int(4) NULL DEFAULT 0,
  `nationsymbol` int(4) NULL DEFAULT NULL,
  INDEX `type`(`type`, `id_target`) USING BTREE
) ENGINE = MyISAM CHARACTER SET = latin1 COLLATE = latin1_bin ROW_FORMAT = FIXED;

DROP TABLE IF EXISTS `emoneycount`;
emoneycount`;
CREATE TABLE `emoneycount`  (
  `number` int(4) NULL DEFAULT NULL,
  `type` int(4) NULL DEFAULT NULL,
  `id_target` int(4) NULL DEFAULT NULL,
  INDEX `type`(`type`, `id_target`) USING BTREE
) ENGINE = MyISAM CHARACTER SET = latin1 COLLATE = latin1_bin ROW_FORMAT = FIXED;

DROP TABLE IF EXISTS `emoneylastid`;
emoneylastid`;
CREATE TABLE `emoneylastid`  (
  `id` int(4) NOT NULL DEFAULT 0,
  `number` int(4) NULL DEFAULT 0,
  PRIMARY KEY (`id`) USING BTREE
) ENGINE = MyISAM CHARACTER SET = latin1 COLLATE = latin1_bin ROW_FORMAT = FIXED;

DROP TABLE IF EXISTS `emoneysum`;
emoneysum`;
CREATE TABLE `emoneysum`  (
  `id` int(4) NOT NULL DEFAULT 0,
  `oldNumber` int(4) NULL DEFAULT 0,
  `newNumber` int(4) NULL DEFAULT 0,
  PRIMARY KEY (`id`) USING BTREE
) ENGINE = MyISAM CHARACTER SET = latin1 COLLATE = latin1_bin ROW_FORMAT = FIXED;

DROP TABLE IF EXISTS `family`;
family`;
CREATE TABLE `family`  (
  `id` int(4) UNSIGNED NOT NULL AUTO_INCREMENT,
  `family_name` varbinary(35) NULL DEFAULT 0,
  `rank` tinyint(1) UNSIGNED NULL DEFAULT 0,
  `lead_id` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `annouce` varbinary(255) NULL DEFAULT NULL,
  `money` bigint(4) UNSIGNED NULL DEFAULT 0,
  `repute` int(4) UNSIGNED NULL DEFAULT 0,
  `amount` tinyint(3) UNSIGNED NULL DEFAULT 0,
  `enemy_family_0_id` int(4) UNSIGNED NULL DEFAULT 0,
  `enemy_family_1_id` int(4) UNSIGNED NULL DEFAULT 0,
  `enemy_family_2_id` int(4) UNSIGNED NULL DEFAULT 0,
  `enemy_family_3_id` int(4) UNSIGNED NULL DEFAULT 0,
  `enemy_family_4_id` int(4) UNSIGNED NULL DEFAULT 0,
  `ally_family_0_id` int(4) UNSIGNED NULL DEFAULT 0,
  `ally_family_1_id` int(4) UNSIGNED NULL DEFAULT 0,
  `ally_family_2_id` int(4) UNSIGNED NULL DEFAULT 0,
  `ally_family_3_id` int(4) UNSIGNED NULL DEFAULT 0,
  `ally_family_4_id` int(4) UNSIGNED NULL DEFAULT 0,
  `create_date` int(4) UNSIGNED NULL DEFAULT 0,
  `create_name` varbinary(15) NULL DEFAULT 0,
  `challenge_map` int(4) UNSIGNED NULL DEFAULT 0,
  `family_map` int(4) UNSIGNED NULL DEFAULT 0,
  `star_tower` tinyint(1) UNSIGNED NULL DEFAULT 0,
  `challenge` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `occupy` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `del_flag` tinyint(1) UNSIGNED NULL DEFAULT 0,
  PRIMARY KEY (`id`) USING BTREE,
  UNIQUE INDEX `name`(`family_name`) USING BTREE
) ENGINE = MyISAM AUTO_INCREMENT = 1 CHARACTER SET = latin1 COLLATE = latin1_bin ROW_FORMAT = DYNAMIC;

DROP TABLE IF EXISTS `family_attr`;
family_attr`;
CREATE TABLE `family_attr`  (
  `id` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `family_id` int(4) UNSIGNED NULL DEFAULT 0,
  `rank` tinyint(1) UNSIGNED NULL DEFAULT 0,
  `proffer` int(4) UNSIGNED NULL DEFAULT 0,
  `join_date` int(4) UNSIGNED NULL DEFAULT 0,
  `auto_exercise` tinyint(1) UNSIGNED NULL DEFAULT 0,
  `exp_date` int(10) UNSIGNED NOT NULL DEFAULT 0,
  PRIMARY KEY (`id`) USING BTREE,
  INDEX `family_id`(`family_id`) USING BTREE
) ENGINE = MyISAM CHARACTER SET = latin1 COLLATE = latin1_bin ROW_FORMAT = FIXED;

DROP TABLE IF EXISTS `family_battle_effect_share_limit`;
family_battle_effect_share_limit`;
CREATE TABLE `family_battle_effect_share_limit`  (
  `id` int(4) UNSIGNED NOT NULL AUTO_INCREMENT,
  `share_limit` smallint(4) UNSIGNED NOT NULL DEFAULT 0,
  PRIMARY KEY (`id`) USING BTREE
) ENGINE = MyISAM AUTO_INCREMENT = 401 CHARACTER SET = latin1 COLLATE = latin1_bin ROW_FORMAT = FIXED;

DROP TABLE IF EXISTS `flower`;
flower`;
CREATE TABLE `flower`  (
  `id` int(4) UNSIGNED NOT NULL AUTO_INCREMENT,
  `player_id` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `flower_r` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `flower_w` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `flower_lily` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `flower_tulip` int(4) UNSIGNED NOT NULL DEFAULT 0,
  PRIMARY KEY (`id`) USING BTREE,
  INDEX `idx_player_id`(`player_id`) USING BTREE
) ENGINE = MyISAM AUTO_INCREMENT = 4 CHARACTER SET = latin1 COLLATE = latin1_bin ROW_FORMAT = FIXED;

DROP TABLE IF EXISTS `game_endtime`;
game_endtime`;
CREATE TABLE `game_endtime`  (
  `bak_flag` varchar(30) CHARACTER SET latin1 COLLATE latin1_bin NOT NULL,
  `end_time` datetime NOT NULL
) ENGINE = MyISAM CHARACTER SET = latin1 COLLATE = latin1_bin ROW_FORMAT = DYNAMIC;

DROP TABLE IF EXISTS `ghostcontract`;
ghostcontract`;
CREATE TABLE `ghostcontract`  (
  `id` int(10) UNSIGNED NOT NULL AUTO_INCREMENT,
  `Item_id` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `owner_id` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `timeout` int(4) UNSIGNED NOT NULL DEFAULT 0,
  PRIMARY KEY (`id`) USING BTREE,
  INDEX `idx_item_id`(`Item_id`) USING BTREE,
  INDEX `idx_owner_id`(`owner_id`) USING BTREE
) ENGINE = MyISAM AUTO_INCREMENT = 1 CHARACTER SET = latin1 COLLATE = latin1_bin ROW_FORMAT = FIXED;

DROP TABLE IF EXISTS `item_log`;
item_log`;
CREATE TABLE `item_log`  (
  `id` int(4) UNSIGNED NOT NULL AUTO_INCREMENT,
  `time` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `item_id` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `item_type` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `owner_id` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `event` tinyint(1) UNSIGNED NOT NULL DEFAULT 0,
  PRIMARY KEY (`id`) USING BTREE
) ENGINE = MyISAM AUTO_INCREMENT = 10 CHARACTER SET = latin1 COLLATE = latin1_bin ROW_FORMAT = FIXED;

DROP TABLE IF EXISTS `login_rcd`;
login_rcd`;
CREATE TABLE `login_rcd`  (
  `id` int(4) UNSIGNED NOT NULL AUTO_INCREMENT,
  `account_id` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `login_time` bigint(15) UNSIGNED ZEROFILL NULL DEFAULT NULL,
  `online_second` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `mac_adr` char(12) CHARACTER SET latin1 COLLATE latin1_bin NOT NULL DEFAULT '',
  `ip_adr` char(15) CHARACTER SET latin1 COLLATE latin1_bin NOT NULL DEFAULT '\"\"',
  `res_src` int(4) UNSIGNED NOT NULL DEFAULT 0,
  PRIMARY KEY (`id`) USING BTREE
) ENGINE = MyISAM AUTO_INCREMENT = 363 CHARACTER SET = latin1 COLLATE = latin1_bin ROW_FORMAT = FIXED;

DROP TABLE IF EXISTS `m_datamonitor`;
m_datamonitor`;
CREATE TABLE `m_datamonitor`  (
  `Id` int(11) NOT NULL AUTO_INCREMENT,
  `Type` varchar(255) CHARACTER SET latin1 COLLATE latin1_bin NULL DEFAULT NULL,
  `Value` bigint(20) NULL DEFAULT NULL,
  `InnerType` int(11) NULL DEFAULT NULL,
  `ExecDate` datetime NULL DEFAULT NULL,
  `nationsymbol` int(4) NULL DEFAULT NULL,
  `version` varchar(50) CHARACTER SET latin1 COLLATE latin1_bin NULL DEFAULT NULL,
  PRIMARY KEY (`Id`) USING BTREE
) ENGINE = MyISAM AUTO_INCREMENT = 1 CHARACTER SET = latin1 COLLATE = latin1_bin ROW_FORMAT = DYNAMIC;

DROP TABLE IF EXISTS `m_datamonitorbak`;
m_datamonitorbak`;
CREATE TABLE `m_datamonitorbak`  (
  `id` int(11) NULL DEFAULT NULL,
  `Type` varchar(255) CHARACTER SET latin1 COLLATE latin1_bin NULL DEFAULT NULL,
  `Value` bigint(20) NULL DEFAULT NULL,
  `InnerType` int(11) NULL DEFAULT NULL,
  `ExecDate` datetime NULL DEFAULT NULL,
  `nationsymbol` int(4) NULL DEFAULT NULL,
  `version` varchar(50) CHARACTER SET latin1 COLLATE latin1_bin NULL DEFAULT NULL
) ENGINE = MyISAM CHARACTER SET = latin1 COLLATE = latin1_bin ROW_FORMAT = DYNAMIC;

DROP TABLE IF EXISTS `points`;
points`;
CREATE TABLE `points`  (
  `name` varbinary(240) NULL DEFAULT NULL,
  `point` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `sortType` smallint(5) UNSIGNED NULL DEFAULT NULL,
  `level` smallint(5) UNSIGNED NULL DEFAULT NULL,
  `profession` smallint(5) UNSIGNED NULL DEFAULT NULL,
  `lastlogin` int(10) UNSIGNED NULL DEFAULT NULL,
  `amount` int(11) UNSIGNED NULL DEFAULT NULL,
  `money` bigint(20) NULL DEFAULT NULL,
  `leader_name` varbinary(50) NULL DEFAULT NULL
) ENGINE = MyISAM CHARACTER SET = latin1 COLLATE = latin1_bin ROW_FORMAT = DYNAMIC;

DROP TABLE IF EXISTS `poker_refund_logs`;
poker_refund_logs`;
CREATE TABLE `poker_refund_logs`  (
  `log_timestamp` varchar(50) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NOT NULL,
  `user_id` int(11) NULL DEFAULT NULL,
  `user_name` varchar(50) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL,
  `amount` bigint(20) NULL DEFAULT NULL,
  `added_date` date NOT NULL,
  PRIMARY KEY (`log_timestamp`) USING BTREE
) ENGINE = MyISAM CHARACTER SET = utf8mb4 COLLATE = utf8mb4_general_ci ROW_FORMAT = DYNAMIC;

DROP TABLE IF EXISTS `profession`;
profession`;
CREATE TABLE `profession`  (
  `name` varbinary(240) NULL DEFAULT NULL,
  `level` smallint(5) UNSIGNED NULL DEFAULT NULL,
  `exp` bigint(10) UNSIGNED NULL DEFAULT NULL,
  `mate` varbinary(240) NULL DEFAULT NULL,
  `syndicate` varbinary(240) NULL DEFAULT NULL,
  `sortType` smallint(5) UNSIGNED NULL DEFAULT NULL,
  `pro` smallint(5) UNSIGNED NULL DEFAULT NULL,
  `lastlogin` int(10) UNSIGNED NULL DEFAULT NULL
) ENGINE = MyISAM CHARACTER SET = latin1 COLLATE = latin1_bin ROW_FORMAT = DYNAMIC;

DROP TABLE IF EXISTS `split`;
split`;
CREATE TABLE `split`  (
  `account_id` int(12) NULL DEFAULT NULL,
  `split_date` datetime NULL DEFAULT NULL,
  UNIQUE INDEX `index_account`(`account_id`) USING BTREE
) ENGINE = MyISAM CHARACTER SET = latin1 COLLATE = latin1_bin ROW_FORMAT = FIXED;

DROP TABLE IF EXISTS `st_dbbrushtimestamp`;
st_dbbrushtimestamp`;
CREATE TABLE `st_dbbrushtimestamp`  (
  `timestamp` bigint(20) UNSIGNED NULL DEFAULT 0
) ENGINE = MyISAM CHARACTER SET = latin1 COLLATE = latin1_bin ROW_FORMAT = FIXED;

DROP TABLE IF EXISTS `st_ko`;
st_ko`;
CREATE TABLE `st_ko`  (
  `rowid` int(11) UNSIGNED NOT NULL AUTO_INCREMENT,
  `number` int(11) UNSIGNED NULL DEFAULT NULL,
  `name` varbinary(50) NULL DEFAULT NULL,
  `level` int(11) UNSIGNED NULL DEFAULT NULL,
  PRIMARY KEY (`rowid`) USING BTREE,
  UNIQUE INDEX `rowid`(`rowid`) USING BTREE
) ENGINE = MyISAM AUTO_INCREMENT = 1 CHARACTER SET = latin1 COLLATE = latin1_bin ROW_FORMAT = DYNAMIC;

DROP TABLE IF EXISTS `st_ko1`;
st_ko1`;
CREATE TABLE `st_ko1`  (
  `sortid` int(11) UNSIGNED NOT NULL AUTO_INCREMENT,
  `number` int(11) UNSIGNED NULL DEFAULT NULL,
  `name` varbinary(50) NULL DEFAULT NULL,
  `level` int(11) UNSIGNED NULL DEFAULT NULL,
  PRIMARY KEY (`sortid`) USING BTREE,
  UNIQUE INDEX `sortid`(`sortid`) USING BTREE
) ENGINE = MyISAM AUTO_INCREMENT = 1 CHARACTER SET = latin1 COLLATE = latin1_bin ROW_FORMAT = DYNAMIC;

DROP TABLE IF EXISTS `st_points`;
st_points`;
CREATE TABLE `st_points`  (
  `sortid` bigint(20) NOT NULL AUTO_INCREMENT,
  `name` varbinary(240) NULL DEFAULT NULL,
  `point` bigint(20) NULL DEFAULT NULL,
  `sortType` smallint(5) UNSIGNED NULL DEFAULT NULL,
  `level` smallint(5) UNSIGNED NULL DEFAULT NULL,
  `profession` smallint(5) UNSIGNED NULL DEFAULT NULL,
  `lastlogin` int(10) UNSIGNED NULL DEFAULT NULL,
  `amount` bigint(20) NULL DEFAULT NULL,
  `money` bigint(20) NULL DEFAULT NULL,
  `leader_name` varbinary(50) NULL DEFAULT NULL,
  PRIMARY KEY (`sortid`) USING BTREE,
  UNIQUE INDEX `sortid`(`sortid`) USING BTREE,
  INDEX `sortTypeIndex`(`sortType`) USING BTREE
) ENGINE = MyISAM AUTO_INCREMENT = 1 CHARACTER SET = latin1 COLLATE = latin1_bin ROW_FORMAT = DYNAMIC;

DROP TABLE IF EXISTS `st_profession`;
st_profession`;
CREATE TABLE `st_profession`  (
  `sortid` bigint(20) NOT NULL AUTO_INCREMENT,
  `name` varbinary(240) NULL DEFAULT NULL,
  `level` smallint(5) UNSIGNED NULL DEFAULT NULL,
  `exp` bigint(10) UNSIGNED NULL DEFAULT NULL,
  `mate` varbinary(240) NULL DEFAULT NULL,
  `syndicate` varbinary(240) NULL DEFAULT NULL,
  `sortType` smallint(5) UNSIGNED NULL DEFAULT NULL,
  `pro` smallint(5) UNSIGNED NULL DEFAULT NULL,
  `lastlogin` int(10) UNSIGNED NULL DEFAULT NULL,
  PRIMARY KEY (`sortid`) USING BTREE,
  UNIQUE INDEX `sortid`(`sortid`) USING BTREE,
  INDEX `sortTypeIndex`(`sortType`) USING BTREE
) ENGINE = MyISAM AUTO_INCREMENT = 1 CHARACTER SET = latin1 COLLATE = latin1_bin ROW_FORMAT = DYNAMIC;

DROP TABLE IF EXISTS `st_winsyn`;
st_winsyn`;
CREATE TABLE `st_winsyn`  (
  `rowid` int(11) NOT NULL AUTO_INCREMENT,
  `name` varbinary(50) NULL DEFAULT NULL,
  `leader_name` varbinary(50) NULL DEFAULT NULL,
  `amount` int(11) UNSIGNED NULL DEFAULT NULL,
  `money` bigint(20) NULL DEFAULT NULL,
  `synlevel` int(11) UNSIGNED NULL DEFAULT NULL,
  PRIMARY KEY (`rowid`) USING BTREE,
  UNIQUE INDEX `rowid`(`rowid`) USING BTREE
) ENGINE = MyISAM AUTO_INCREMENT = 1 CHARACTER SET = latin1 COLLATE = latin1_bin ROW_FORMAT = DYNAMIC;

DROP TABLE IF EXISTS `st_winsyn1`;
st_winsyn1`;
CREATE TABLE `st_winsyn1`  (
  `sortid` int(11) NOT NULL AUTO_INCREMENT,
  `name` varbinary(50) NULL DEFAULT NULL,
  `leader_name` varbinary(50) NULL DEFAULT NULL,
  `amount` int(11) UNSIGNED NULL DEFAULT NULL,
  `money` bigint(20) NULL DEFAULT NULL,
  `synrank` int(11) UNSIGNED NULL DEFAULT NULL,
  PRIMARY KEY (`sortid`) USING BTREE,
  UNIQUE INDEX `rowid`(`sortid`) USING BTREE
) ENGINE = MyISAM AUTO_INCREMENT = 1 CHARACTER SET = latin1 COLLATE = latin1_bin ROW_FORMAT = DYNAMIC;

DROP TABLE IF EXISTS `task_detail`;
task_detail`;
CREATE TABLE `task_detail`  (
  `id` int(4) UNSIGNED NOT NULL AUTO_INCREMENT,
  `user_id` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `task_id` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `complete_flag` smallint(1) UNSIGNED NOT NULL DEFAULT 0,
  `notify_flag` tinyint(1) UNSIGNED NOT NULL DEFAULT 0,
  `data1` int(4) NOT NULL DEFAULT 0,
  `data2` int(4) NOT NULL DEFAULT 0,
  `data3` int(4) NOT NULL DEFAULT 0,
  `data4` int(4) NOT NULL DEFAULT 0,
  `data5` int(4) NOT NULL DEFAULT 0,
  `data6` int(4) NOT NULL DEFAULT 0,
  `data7` int(4) NOT NULL DEFAULT 0,
  `task_overtime` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `type` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `max_accumulate_times` int(4) UNSIGNED NOT NULL DEFAULT 0,
  PRIMARY KEY (`id`) USING BTREE,
  INDEX `user_id`(`user_id`) USING BTREE
) ENGINE = MyISAM AUTO_INCREMENT = 440 CHARACTER SET = latin1 COLLATE = latin1_bin ROW_FORMAT = FIXED;

DROP TABLE IF EXISTS `task_detail_timeout`;
task_detail_timeout`;
CREATE TABLE `task_detail_timeout`  (
  `id` int(4) UNSIGNED NOT NULL AUTO_INCREMENT,
  `user_id` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `task_id` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `complete_flag` smallint(1) UNSIGNED NOT NULL DEFAULT 0,
  `notify_flag` tinyint(1) UNSIGNED NOT NULL DEFAULT 0,
  `data1` int(4) NOT NULL DEFAULT 0,
  `data2` int(4) NOT NULL DEFAULT 0,
  `data3` int(4) NOT NULL DEFAULT 0,
  `data4` int(4) NOT NULL DEFAULT 0,
  `data5` int(4) NOT NULL DEFAULT 0,
  `data6` int(4) NOT NULL DEFAULT 0,
  `data7` int(4) NOT NULL DEFAULT 0,
  `task_overtime` int(4) UNSIGNED NOT NULL DEFAULT 0,
  `type` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `max_accumulate_times` int(4) UNSIGNED NOT NULL DEFAULT 0,
  PRIMARY KEY (`id`) USING BTREE,
  INDEX `user_id`(`user_id`) USING BTREE
) ENGINE = MyISAM AUTO_INCREMENT = 1 CHARACTER SET = latin1 COLLATE = latin1_bin ROW_FORMAT = FIXED;

DROP TABLE IF EXISTS `winsyndicate`;
winsyndicate`;
CREATE TABLE `winsyndicate`  (
  `ID` int(11) NOT NULL AUTO_INCREMENT,
  `Date` date NULL DEFAULT NULL,
  `SyndicateID` int(11) NULL DEFAULT NULL,
  `SyndicateName` varbinary(50) NULL DEFAULT NULL,
  `LeaderID` int(11) NULL DEFAULT NULL,
  `LeaderName` varbinary(50) NULL DEFAULT NULL,
  `MemberCount` int(11) NULL DEFAULT NULL,
  `Fund` bigint(20) NULL DEFAULT NULL,
  PRIMARY KEY (`ID`) USING BTREE,
  INDEX `idx_leadername`(`LeaderName`) USING BTREE
) ENGINE = MyISAM AUTO_INCREMENT = 1 CHARACTER SET = latin1 COLLATE = latin1_bin ROW_FORMAT = DYNAMIC;
