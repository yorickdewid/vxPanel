-- --------------------------------------------------------
-- Host:                         192.168.1.73
-- Server versie:                5.5.5-10.0.20-MariaDB - MariaDB Server
-- Server OS:                    Linux
-- HeidiSQL Versie:              8.3.0.4694
-- --------------------------------------------------------

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET NAMES utf8 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;

-- Databasestructuur van vxpanel wordt geschreven
CREATE DATABASE IF NOT EXISTS `vxpanel` /*!40100 DEFAULT CHARACTER SET latin1 */;
USE `vxpanel`;


-- Structuur van  tabel vxpanel.dns wordt geschreven
CREATE TABLE IF NOT EXISTS `dns` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `address` varchar(500) NOT NULL,
  `created` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP,
  `domain_name` varchar(100) NOT NULL,
  PRIMARY KEY (`id`),
  KEY `FK_domain` (`domain_name`),
  CONSTRAINT `FK_domain` FOREIGN KEY (`domain_name`) REFERENCES `domain` (`name`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

-- Data exporteren was gedeselecteerd


-- Structuur van  tabel vxpanel.domain wordt geschreven
CREATE TABLE IF NOT EXISTS `domain` (
  `name` varchar(100) NOT NULL,
  `status` varchar(50) NOT NULL,
  `registrar` varchar(50) NOT NULL,
  `created` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP,
  `uid` int(11) unsigned NOT NULL,
  `vhost_id` int(11) unsigned DEFAULT NULL,
  PRIMARY KEY (`name`),
  KEY `FK_domain_user` (`uid`),
  KEY `FK_domain_vhost` (`vhost_id`),
  CONSTRAINT `FK_domain_user` FOREIGN KEY (`uid`) REFERENCES `user` (`uid`) ON DELETE CASCADE ON UPDATE CASCADE,
  CONSTRAINT `FK_domain_vhost` FOREIGN KEY (`vhost_id`) REFERENCES `vhost` (`id`) ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

-- Data exporteren was gedeselecteerd


-- Structuur van  tabel vxpanel.ftp_account wordt geschreven
CREATE TABLE IF NOT EXISTS `ftp_account` (
  `username` varchar(50) NOT NULL,
  `password` varchar(100) NOT NULL,
  `permissions` char(2) NOT NULL,
  `created` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP,
  `domain_name` varchar(50) DEFAULT NULL,
  `uid` int(11) unsigned NOT NULL,
  PRIMARY KEY (`username`),
  KEY `FK_ftp_account_domain` (`domain_name`),
  KEY `FK_ftp_account_user` (`uid`),
  CONSTRAINT `FK_ftp_account_domain` FOREIGN KEY (`domain_name`) REFERENCES `domain` (`name`) ON DELETE CASCADE ON UPDATE CASCADE,
  CONSTRAINT `FK_ftp_account_user` FOREIGN KEY (`uid`) REFERENCES `user` (`uid`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

-- Data exporteren was gedeselecteerd


-- Structuur van  tabel vxpanel.mailbox wordt geschreven
CREATE TABLE IF NOT EXISTS `mailbox` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `address` varchar(200) NOT NULL,
  `created` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP,
  `domain_name` varchar(100) NOT NULL,
  PRIMARY KEY (`id`),
  KEY `FK_mailbox_domain` (`domain_name`),
  CONSTRAINT `FK_mailbox_domain` FOREIGN KEY (`domain_name`) REFERENCES `domain` (`name`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

-- Data exporteren was gedeselecteerd


-- Structuur van  tabel vxpanel.settings wordt geschreven
CREATE TABLE IF NOT EXISTS `settings` (
  `key` varchar(100) NOT NULL,
  `value` varchar(100) NOT NULL,
  `default` tinyint(1) NOT NULL,
  `description` varchar(250) NOT NULL,
  `updated` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,
  `created` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP,
  PRIMARY KEY (`key`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

-- Data exporteren was gedeselecteerd


-- Structuur van  tabel vxpanel.shell wordt geschreven
CREATE TABLE IF NOT EXISTS `shell` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `created` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP,
  `uid` int(11) unsigned NOT NULL,
  PRIMARY KEY (`id`),
  KEY `FK_shell_user` (`uid`),
  CONSTRAINT `FK_shell_user` FOREIGN KEY (`uid`) REFERENCES `user` (`uid`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

-- Data exporteren was gedeselecteerd


-- Structuur van  tabel vxpanel.subdomain wordt geschreven
CREATE TABLE IF NOT EXISTS `subdomain` (
  `name` varchar(50) NOT NULL,
  `created` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP,
  `domain_name` varchar(100) NOT NULL,
  `vhost_id` int(11) unsigned DEFAULT NULL,
  PRIMARY KEY (`name`),
  KEY `FK_subdomain_domain` (`domain_name`),
  KEY `FK_subdomain_vhost` (`vhost_id`),
  CONSTRAINT `FK_subdomain_domain` FOREIGN KEY (`domain_name`) REFERENCES `domain` (`name`) ON DELETE CASCADE ON UPDATE CASCADE,
  CONSTRAINT `FK_subdomain_vhost` FOREIGN KEY (`vhost_id`) REFERENCES `vhost` (`id`) ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

-- Data exporteren was gedeselecteerd


-- Structuur van  tabel vxpanel.user wordt geschreven
CREATE TABLE IF NOT EXISTS `user` (
  `uid` int(11) unsigned NOT NULL AUTO_INCREMENT,
  `username` varchar(30) NOT NULL,
  `password` char(40) NOT NULL,
  `email` varchar(100) NOT NULL,
  `firstname` varchar(50) DEFAULT NULL,
  `lastname` varchar(100) DEFAULT NULL,
  `country` varchar(100) DEFAULT NULL,
  `city` varchar(50) DEFAULT NULL,
  `address` varchar(100) DEFAULT NULL,
  `address_number` smallint(6) DEFAULT NULL,
  `postal` varchar(15) DEFAULT NULL,
  `note` text,
  `user_type` enum('administrator','reseller','user') NOT NULL DEFAULT 'user',
  `active` tinyint(1) NOT NULL DEFAULT '1',
  `created` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP,
  `lastlogin` timestamp NULL DEFAULT NULL,
  PRIMARY KEY (`uid`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

-- Data exporteren was gedeselecteerd


-- Structuur van  tabel vxpanel.user_db wordt geschreven
CREATE TABLE IF NOT EXISTS `user_db` (
  `name` varchar(100) NOT NULL,
  `created` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP,
  `uid` int(11) unsigned NOT NULL,
  `db_type` varchar(50) NOT NULL,
  PRIMARY KEY (`name`),
  KEY `FK_database_user` (`uid`),
  KEY `FK_database_database_type` (`db_type`),
  CONSTRAINT `FK_database_database_type` FOREIGN KEY (`db_type`) REFERENCES `user_db_type` (`name`) ON UPDATE CASCADE,
  CONSTRAINT `FK_database_user` FOREIGN KEY (`uid`) REFERENCES `user` (`uid`) ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

-- Data exporteren was gedeselecteerd


-- Structuur van  tabel vxpanel.user_dbuser_db wordt geschreven
CREATE TABLE IF NOT EXISTS `user_dbuser_db` (
  `dbuser_name` varchar(50) NOT NULL,
  `db_name` varchar(100) NOT NULL,
  PRIMARY KEY (`dbuser_name`,`db_name`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

-- Data exporteren was gedeselecteerd


-- Structuur van  tabel vxpanel.user_db_type wordt geschreven
CREATE TABLE IF NOT EXISTS `user_db_type` (
  `name` varchar(50) NOT NULL,
  PRIMARY KEY (`name`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

/*!40000 ALTER TABLE `user_db_type` DISABLE KEYS */;
INSERT INTO `user_db_type` (`name`) VALUES
  ('mysql'),
  ('postgresql');
/*!40000 ALTER TABLE `user_db_type` ENABLE KEYS */;

-- Structuur van  tabel vxpanel.user_db_user wordt geschreven
CREATE TABLE IF NOT EXISTS `user_db_user` (
  `name` varchar(50) NOT NULL,
  `password` varchar(50) NOT NULL,
  `permissions` varchar(100) NOT NULL,
  `created` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP,
  `uid` int(11) unsigned NOT NULL,
  PRIMARY KEY (`name`),
  KEY `FK_database_user_user` (`uid`),
  CONSTRAINT `FK_database_user_user` FOREIGN KEY (`uid`) REFERENCES `user` (`uid`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

-- Data exporteren was gedeselecteerd


-- Structuur van  tabel vxpanel.vhost wordt geschreven
CREATE TABLE IF NOT EXISTS `vhost` (
  `id` int(11) unsigned NOT NULL AUTO_INCREMENT,
  `name` varchar(100) NOT NULL,
  `custom_config` text,
  `created` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

-- Data exporteren was gedeselecteerd
/*!40101 SET SQL_MODE=IFNULL(@OLD_SQL_MODE, '') */;
/*!40014 SET FOREIGN_KEY_CHECKS=IF(@OLD_FOREIGN_KEY_CHECKS IS NULL, 1, @OLD_FOREIGN_KEY_CHECKS) */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
