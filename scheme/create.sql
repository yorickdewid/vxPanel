/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET NAMES utf8 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;

DROP DATABASE IF EXISTS `vxpanel`;

CREATE DATABASE IF NOT EXISTS `vxpanel` /*!40100 DEFAULT CHARACTER SET latin1 */;
USE `vxpanel`;

CREATE TABLE IF NOT EXISTS `dns` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `name` VARCHAR(500) NOT NULL,
  `created` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP,
  `domain_name` varchar(100) NOT NULL,
  `active` tinyint(1) NOT NULL DEFAULT '1',
  PRIMARY KEY (`id`),
  KEY `FK_domain` (`domain_name`),
  CONSTRAINT `FK_domain` FOREIGN KEY (`domain_name`) REFERENCES `domain` (`name`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=latin1;


CREATE TABLE IF NOT EXISTS `domain` (
  `name` varchar(100) NOT NULL,
  `status` varchar(50) NOT NULL,
  `registrar` varchar(50) NOT NULL,
  `created` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP,
  `uid` int(11) unsigned NOT NULL,
  `vhost_id` int(11) unsigned DEFAULT NULL,
  `active` tinyint(1) NOT NULL DEFAULT '1',
  PRIMARY KEY (`name`),
  KEY `FK_domain_user` (`uid`),
  KEY `FK_domain_vhost` (`vhost_id`),
  CONSTRAINT `FK_domain_user` FOREIGN KEY (`uid`) REFERENCES `user` (`uid`) ON DELETE CASCADE ON UPDATE CASCADE,
  CONSTRAINT `FK_domain_vhost` FOREIGN KEY (`vhost_id`) REFERENCES `vhost` (`id`) ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=latin1;


CREATE TABLE IF NOT EXISTS `domain_alias` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `domain_name` varchar(50) DEFAULT NULL,
  `source` varchar(100) NOT NULL,
  `destination` varchar(100) NOT NULL,
  `created` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP,
  `active` tinyint(1) NOT NULL DEFAULT '1',
  PRIMARY KEY (`id`),
  KEY `FK_domain_alias_domain` (`domain_name`),
  CONSTRAINT `FK_domain_alias_domain` FOREIGN KEY (`domain_name`) REFERENCES `domain` (`name`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=latin1;


CREATE TABLE IF NOT EXISTS `ftpgroup` (
  `groupname` varchar(16) NOT NULL DEFAULT '',
  `gid` smallint(6) NOT NULL DEFAULT '5500',
  `members` varchar(16) NOT NULL DEFAULT '',
  KEY `groupname` (`groupname`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

INSERT INTO `ftpgroup` (`groupname`, `gid`, `members`) VALUES
('ftpgroup', 2001, 'ftpuser');


CREATE TABLE IF NOT EXISTS `ftpquotalimits` (
  `name` varchar(30) DEFAULT NULL,
  `quota_type` enum('user','group','class','all') NOT NULL DEFAULT 'user',
  `per_session` enum('false','true') NOT NULL DEFAULT 'false',
  `limit_type` enum('soft','hard') NOT NULL DEFAULT 'soft',
  `bytes_in_avail` int(10) unsigned NOT NULL DEFAULT '0',
  `bytes_out_avail` int(10) unsigned NOT NULL DEFAULT '0',
  `bytes_xfer_avail` int(10) unsigned NOT NULL DEFAULT '0',
  `files_in_avail` int(10) unsigned NOT NULL DEFAULT '0',
  `files_out_avail` int(10) unsigned NOT NULL DEFAULT '0',
  `files_xfer_avail` int(10) unsigned NOT NULL DEFAULT '0'
) ENGINE=InnoDB DEFAULT CHARSET=latin1;


CREATE TABLE IF NOT EXISTS `ftpquotatallies` (
  `name` varchar(30) NOT NULL DEFAULT '',
  `quota_type` enum('user','group','class','all') NOT NULL DEFAULT 'user',
  `bytes_in_used` int(10) unsigned NOT NULL DEFAULT '0',
  `bytes_out_used` int(10) unsigned NOT NULL DEFAULT '0',
  `bytes_xfer_used` int(10) unsigned NOT NULL DEFAULT '0',
  `files_in_used` int(10) unsigned NOT NULL DEFAULT '0',
  `files_out_used` int(10) unsigned NOT NULL DEFAULT '0',
  `files_xfer_used` int(10) unsigned NOT NULL DEFAULT '0'
) ENGINE=InnoDB DEFAULT CHARSET=latin1;


CREATE TABLE IF NOT EXISTS `ftpuser` (
  `id` int(10) unsigned NOT NULL AUTO_INCREMENT,
  `name` varchar(32) NOT NULL DEFAULT '',
  `password` varchar(32) NOT NULL DEFAULT '',
  `uid` smallint(6) NOT NULL DEFAULT '33',
  `gid` smallint(6) NOT NULL DEFAULT '33',
  `homedir` varchar(255) NOT NULL DEFAULT '',
  `shell` varchar(16) NOT NULL DEFAULT '/sbin/nologin',
  `count` int(11) NOT NULL DEFAULT '0',
  `userid` int(11) unsigned NOT NULL,
  `created` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP,
  `accessed` datetime NOT NULL DEFAULT '0000-00-00 00:00:00',
  `modified` datetime NOT NULL DEFAULT '0000-00-00 00:00:00',
  PRIMARY KEY (`id`),
  KEY `FK_ftpuser_user` (`userid`),
  UNIQUE KEY `name` (`name`),
  CONSTRAINT `FK_ftpuser_user` FOREIGN KEY (`userid`) REFERENCES `user` (`uid`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=latin1;


CREATE TABLE IF NOT EXISTS `mailbox` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `email` varchar(200) NOT NULL,
  `password` varchar(106) NOT NULL,
  `maildir` varchar(255) NOT NULL,
  `quota` bigint(20) NOT NULL DEFAULT '0',
  `created` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP,
  `domain_name` varchar(100) NOT NULL,
  `bytes` bigint(20) NOT NULL DEFAULT '0',
  `messages` int(11) NOT NULL DEFAULT '0',
  `active` tinyint(1) NOT NULL DEFAULT '1',
  PRIMARY KEY (`id`),
  KEY `FK_mailbox_domain` (`domain_name`),
  CONSTRAINT `FK_mailbox_domain` FOREIGN KEY (`domain_name`) REFERENCES `domain` (`name`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=latin1;


CREATE TABLE IF NOT EXISTS `settings` (
  `key` varchar(100) NOT NULL,
  `value` varchar(100) NOT NULL,
  `default` tinyint(1) NOT NULL,
  `description` varchar(250) NOT NULL,
  `updated` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,
  `created` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP,
  PRIMARY KEY (`key`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;


CREATE TABLE IF NOT EXISTS `shell` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `created` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP,
  `uid` int(11) unsigned NOT NULL,
  `active` tinyint(1) NOT NULL DEFAULT '1',
  PRIMARY KEY (`id`),
  KEY `FK_shell_user` (`uid`),
  CONSTRAINT `FK_shell_user` FOREIGN KEY (`uid`) REFERENCES `user` (`uid`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=latin1;


CREATE TABLE IF NOT EXISTS `subdomain` (
  `name` varchar(50) NOT NULL,
  `created` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP,
  `domain_name` varchar(100) NOT NULL,
  `vhost_id` int(11) unsigned DEFAULT NULL,
  `active` tinyint(1) NOT NULL DEFAULT '1',
  PRIMARY KEY (`name`,`domain_name`),
  KEY `FK_subdomain_domain` (`domain_name`),
  KEY `FK_subdomain_vhost` (`vhost_id`),
  CONSTRAINT `FK_subdomain_domain` FOREIGN KEY (`domain_name`) REFERENCES `domain` (`name`) ON DELETE CASCADE ON UPDATE CASCADE,
  CONSTRAINT `FK_subdomain_vhost` FOREIGN KEY (`vhost_id`) REFERENCES `vhost` (`id`) ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=latin1;


CREATE TABLE IF NOT EXISTS `user` (
  `uid` int(11) unsigned NOT NULL AUTO_INCREMENT,
  `username` varchar(30) NOT NULL,
  `password` varchar(106) NOT NULL,
  `email` varchar(100) NOT NULL,
  `firstname` varchar(50) DEFAULT NULL,
  `lastname` varchar(100) DEFAULT NULL,
  `country` varchar(100) DEFAULT NULL,
  `city` varchar(50) DEFAULT NULL,
  `address` varchar(100) DEFAULT NULL,
  `address_number` smallint(6) DEFAULT NULL,
  `postal` varchar(15) DEFAULT NULL,
  `note` text,
  `remote` VARBINARY(16) DEFAULT NULL,
  `user_type` enum('administrator','reseller','user') NOT NULL DEFAULT 'user',
  `active` tinyint(1) NOT NULL DEFAULT '1',
  `created` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP,
  `lastlogin` timestamp NULL DEFAULT NULL,
  PRIMARY KEY (`uid`),
  UNIQUE INDEX `username` (`username`),
  UNIQUE INDEX `email` (`email`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1 AUTO_INCREMENT=1000;

INSERT INTO `user` (`username`, `password`, `email`, `firstname`, `note`, `remote`, `user_type`) VALUES
('admin', 'CHANGEME', 'info@localhost', 'admin', 'Administrator', INET6_ATON('::1'), 'administrator');


CREATE TABLE IF NOT EXISTS `user_db` (
  `name` varchar(100) NOT NULL,
  `created` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP,
  `uid` int(11) unsigned NOT NULL,
  `db_type` varchar(50) NOT NULL,
  PRIMARY KEY (`name`),
  KEY `FK_database_user` (`uid`),
  KEY `FK_database_database_type` (`db_type`),
  CONSTRAINT `FK_database_database_type` FOREIGN KEY (`db_type`) REFERENCES `user_db_type` (`name`) ON UPDATE CASCADE,
  CONSTRAINT `FK_database_user` FOREIGN KEY (`uid`) REFERENCES `user` (`uid`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=latin1;


CREATE TABLE IF NOT EXISTS `user_db_user` (
  `name` varchar(50) NOT NULL,
  `password` CHAR(40) NOT NULL,
  `permissions` varchar(100) NOT NULL,
  `created` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP,
  `uid` int(11) unsigned NOT NULL,
  PRIMARY KEY (`name`),
  KEY `FK_database_user_user` (`uid`),
  CONSTRAINT `FK_database_user_user` FOREIGN KEY (`uid`) REFERENCES `user` (`uid`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=latin1;



CREATE TABLE IF NOT EXISTS `user_dbuser_db` (
  `db_username` varchar(50) NOT NULL,
  `db_name` varchar(100) NOT NULL,
  PRIMARY KEY (`db_username`,`db_name`),
  KEY `FK_db_username` (`db_username`),
  KEY `FK_db_name` (`db_name`),
  CONSTRAINT `FK_db_username` FOREIGN KEY (`db_username`) REFERENCES `user_db_user` (`name`) ON UPDATE CASCADE,
  CONSTRAINT `FK_db_name` FOREIGN KEY (`db_name`) REFERENCES `user_db` (`name`) ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=latin1;


CREATE TABLE IF NOT EXISTS `user_db_type` (
  `name` varchar(50) NOT NULL,
  PRIMARY KEY (`name`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

INSERT INTO `user_db_type` (`name`) VALUES
  ('mysql'),
  ('postgresql');


CREATE TABLE IF NOT EXISTS `vhost` (
  `id` int(11) unsigned NOT NULL AUTO_INCREMENT,
  `name` varchar(100) NOT NULL,
  `custom_config` text,
  `created` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP,
  `active` tinyint(1) NOT NULL DEFAULT '1',
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;


CREATE TABLE `queue` (
  `qid` INT(11) NOT NULL AUTO_INCREMENT,
  `action` VARCHAR(50) NOT NULL,
  `params` VARCHAR(255) NULL DEFAULT NULL,
  `created` TIMESTAMP NOT NULL DEFAULT CURRENT_TIMESTAMP,
  `started` TIMESTAMP NULL DEFAULT NULL,
  `finished` TIMESTAMP NULL DEFAULT NULL,
  `uid` INT(11) UNSIGNED NOT NULL,
  `status` ENUM('SUBMITTED','PENDING','DONE','FAILED','REJECTED') NULL DEFAULT 'SUBMITTED',
  `result` TEXT NULL,
  PRIMARY KEY (`qid`),
  KEY `FK_queue_user` (`uid`),
  CONSTRAINT `FK_queue_user` FOREIGN KEY (`uid`) REFERENCES `user` (`uid`) ON DELETE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=latin1;


CREATE TABLE `auth_token` (
  `sessionid` CHAR(40) NOT NULL,
  `remote` VARBINARY(16) NOT NULL,
  `uid` INT(10) UNSIGNED NOT NULL,
  `refresh` CHAR(40) NOT NULL,
  `created` TIMESTAMP NOT NULL DEFAULT CURRENT_TIMESTAMP,
  `valid` TIMESTAMP NULL DEFAULT NULL,
  PRIMARY KEY (`sessionid`, `remote`),
  UNIQUE INDEX `refresh` (`refresh`),
  INDEX `FK_auth_token_user` (`uid`),
  CONSTRAINT `FK_auth_token_user` FOREIGN KEY (`uid`) REFERENCES `user` (`uid`) ON UPDATE CASCADE ON DELETE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=latin1;


/* ROUNDCUBE TABLES */

CREATE TABLE `users` (
  `user_id` INT(10) UNSIGNED NOT NULL AUTO_INCREMENT,
  `username` VARCHAR(128) NOT NULL COLLATE 'utf8_bin',
  `mail_host` VARCHAR(128) NOT NULL,
  `created` DATETIME NOT NULL DEFAULT '1000-01-01 00:00:00',
  `last_login` DATETIME NULL DEFAULT NULL,
  `language` VARCHAR(5) NULL DEFAULT NULL,
  `preferences` LONGTEXT NULL,
  PRIMARY KEY (`user_id`),
  UNIQUE INDEX `username` (`username`, `mail_host`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;


CREATE TABLE `cache` (
  `user_id` INT(10) UNSIGNED NOT NULL,
  `cache_key` VARCHAR(128) NOT NULL COLLATE 'ascii_general_ci',
  `created` DATETIME NOT NULL DEFAULT '1000-01-01 00:00:00',
  `expires` DATETIME NULL DEFAULT NULL,
  `data` LONGTEXT NOT NULL,
  INDEX `expires_index` (`expires`),
  INDEX `user_cache_index` (`user_id`, `cache_key`),
  CONSTRAINT `user_id_fk_cache` FOREIGN KEY (`user_id`) REFERENCES `users` (`user_id`) ON UPDATE CASCADE ON DELETE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=latin1;


CREATE TABLE `cache_index` (
  `user_id` INT(10) UNSIGNED NOT NULL,
  `mailbox` VARCHAR(255) NOT NULL COLLATE 'utf8_bin',
  `expires` DATETIME NULL DEFAULT NULL,
  `valid` TINYINT(1) NOT NULL DEFAULT '0',
  `data` LONGTEXT NOT NULL,
  PRIMARY KEY (`user_id`, `mailbox`),
  INDEX `expires_index` (`expires`),
  CONSTRAINT `user_id_fk_cache_index` FOREIGN KEY (`user_id`) REFERENCES `users` (`user_id`) ON UPDATE CASCADE ON DELETE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

CREATE TABLE `cache_messages` (
  `user_id` INT(10) UNSIGNED NOT NULL,
  `mailbox` VARCHAR(255) NOT NULL COLLATE 'utf8_bin',
  `uid` INT(11) UNSIGNED NOT NULL DEFAULT '0',
  `expires` DATETIME NULL DEFAULT NULL,
  `data` LONGTEXT NOT NULL,
  `flags` INT(11) NOT NULL DEFAULT '0',
  PRIMARY KEY (`user_id`, `mailbox`, `uid`),
  INDEX `expires_index` (`expires`),
  CONSTRAINT `user_id_fk_cache_messages` FOREIGN KEY (`user_id`) REFERENCES `users` (`user_id`) ON UPDATE CASCADE ON DELETE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

CREATE TABLE `cache_shared` (
  `cache_key` VARCHAR(255) NOT NULL COLLATE 'ascii_general_ci',
  `created` DATETIME NOT NULL DEFAULT '1000-01-01 00:00:00',
  `expires` DATETIME NULL DEFAULT NULL,
  `data` LONGTEXT NOT NULL,
  INDEX `expires_index` (`expires`),
  INDEX `cache_key_index` (`cache_key`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;


CREATE TABLE `cache_thread` (
  `user_id` INT(10) UNSIGNED NOT NULL,
  `mailbox` VARCHAR(255) NOT NULL COLLATE 'utf8_bin',
  `expires` DATETIME NULL DEFAULT NULL,
  `data` LONGTEXT NOT NULL,
  PRIMARY KEY (`user_id`, `mailbox`),
  INDEX `expires_index` (`expires`),
  CONSTRAINT `user_id_fk_cache_thread` FOREIGN KEY (`user_id`) REFERENCES `users` (`user_id`) ON UPDATE CASCADE ON DELETE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=latin1;


CREATE TABLE `contacts` (
  `contact_id` INT(10) UNSIGNED NOT NULL AUTO_INCREMENT,
  `changed` DATETIME NOT NULL DEFAULT '1000-01-01 00:00:00',
  `del` TINYINT(1) NOT NULL DEFAULT '0',
  `name` VARCHAR(128) NOT NULL DEFAULT '',
  `email` TEXT NOT NULL,
  `firstname` VARCHAR(128) NOT NULL DEFAULT '',
  `surname` VARCHAR(128) NOT NULL DEFAULT '',
  `vcard` LONGTEXT NULL,
  `words` TEXT NULL,
  `user_id` INT(10) UNSIGNED NOT NULL,
  PRIMARY KEY (`contact_id`),
  INDEX `user_contacts_index` (`user_id`, `del`),
  CONSTRAINT `user_id_fk_contacts` FOREIGN KEY (`user_id`) REFERENCES `users` (`user_id`) ON UPDATE CASCADE ON DELETE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=latin1;


CREATE TABLE `contactgroups` (
  `contactgroup_id` INT(10) UNSIGNED NOT NULL AUTO_INCREMENT,
  `user_id` INT(10) UNSIGNED NOT NULL,
  `changed` DATETIME NOT NULL DEFAULT '1000-01-01 00:00:00',
  `del` TINYINT(1) NOT NULL DEFAULT '0',
  `name` VARCHAR(128) NOT NULL DEFAULT '',
  PRIMARY KEY (`contactgroup_id`),
  INDEX `contactgroups_user_index` (`user_id`, `del`),
  CONSTRAINT `user_id_fk_contactgroups` FOREIGN KEY (`user_id`) REFERENCES `users` (`user_id`) ON UPDATE CASCADE ON DELETE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=latin1;


CREATE TABLE `contactgroupmembers` (
  `contactgroup_id` INT(10) UNSIGNED NOT NULL,
  `contact_id` INT(10) UNSIGNED NOT NULL,
  `created` DATETIME NOT NULL DEFAULT '1000-01-01 00:00:00',
  PRIMARY KEY (`contactgroup_id`, `contact_id`),
  INDEX `contactgroupmembers_contact_index` (`contact_id`),
  CONSTRAINT `contact_id_fk_contacts` FOREIGN KEY (`contact_id`) REFERENCES `contacts` (`contact_id`) ON UPDATE CASCADE ON DELETE CASCADE,
  CONSTRAINT `contactgroup_id_fk_contactgroups` FOREIGN KEY (`contactgroup_id`) REFERENCES `contactgroups` (`contactgroup_id`) ON UPDATE CASCADE ON DELETE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=latin1;


CREATE TABLE `dictionary` (
  `user_id` INT(10) UNSIGNED NULL DEFAULT NULL,
  `language` VARCHAR(5) NOT NULL,
  `data` LONGTEXT NOT NULL,
  UNIQUE INDEX `uniqueness` (`user_id`, `language`),
  CONSTRAINT `user_id_fk_dictionary` FOREIGN KEY (`user_id`) REFERENCES `users` (`user_id`) ON UPDATE CASCADE ON DELETE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=latin1;


CREATE TABLE `identities` (
  `identity_id` INT(10) UNSIGNED NOT NULL AUTO_INCREMENT,
  `user_id` INT(10) UNSIGNED NOT NULL,
  `changed` DATETIME NOT NULL DEFAULT '1000-01-01 00:00:00',
  `del` TINYINT(1) NOT NULL DEFAULT '0',
  `standard` TINYINT(1) NOT NULL DEFAULT '0',
  `name` VARCHAR(128) NOT NULL,
  `organization` VARCHAR(128) NOT NULL DEFAULT '',
  `email` VARCHAR(128) NOT NULL,
  `reply-to` VARCHAR(128) NOT NULL DEFAULT '',
  `bcc` VARCHAR(128) NOT NULL DEFAULT '',
  `signature` LONGTEXT NULL,
  `html_signature` TINYINT(1) NOT NULL DEFAULT '0',
  PRIMARY KEY (`identity_id`),
  INDEX `user_identities_index` (`user_id`, `del`),
  INDEX `email_identities_index` (`email`, `del`),
  CONSTRAINT `user_id_fk_identities` FOREIGN KEY (`user_id`) REFERENCES `users` (`user_id`) ON UPDATE CASCADE ON DELETE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=latin1;


CREATE TABLE `searches` (
  `search_id` INT(10) UNSIGNED NOT NULL AUTO_INCREMENT,
  `user_id` INT(10) UNSIGNED NOT NULL,
  `type` INT(3) NOT NULL DEFAULT '0',
  `name` VARCHAR(128) NOT NULL,
  `data` TEXT NULL,
  PRIMARY KEY (`search_id`),
  UNIQUE INDEX `uniqueness` (`user_id`, `type`, `name`),
  CONSTRAINT `user_id_fk_searches` FOREIGN KEY (`user_id`) REFERENCES `users` (`user_id`) ON UPDATE CASCADE ON DELETE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=latin1;


CREATE TABLE `session` (
  `sess_id` VARCHAR(128) NOT NULL,
  `created` DATETIME NOT NULL DEFAULT '1000-01-01 00:00:00',
  `changed` DATETIME NOT NULL DEFAULT '1000-01-01 00:00:00',
  `ip` VARCHAR(40) NOT NULL,
  `vars` MEDIUMTEXT NOT NULL,
  PRIMARY KEY (`sess_id`),
  INDEX `changed_index` (`changed`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;


CREATE TABLE `system` (
  `name` VARCHAR(64) NOT NULL,
  `value` MEDIUMTEXT NULL,
  PRIMARY KEY (`name`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

/*!40101 SET SQL_MODE=IFNULL(@OLD_SQL_MODE, '') */;
/*!40014 SET FOREIGN_KEY_CHECKS=IF(@OLD_FOREIGN_KEY_CHECKS IS NULL, 1, @OLD_FOREIGN_KEY_CHECKS) */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
