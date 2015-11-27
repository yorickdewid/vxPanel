#!/usr/bin/env bash

# OS VERSION: Fedora 23
# ARCH: x32_64

# vxPanel Automated Installation Script
# =============================================
#
# Copyright (C) vxPanel, Inc - All Rights Reserved
# Unauthorized copying of this file, via any medium is strictly prohibited
# Proprietary and confidential
# Written by Yorick de Wid <yorick@vxpanel.com>, November 2015

# First we check if the user is 'root' before allowing installation to commence
if [ $UID -ne 0 ]; then
  echo "You must be root to run the installer"
  exit 1
fi

# ***************************************
# * LICENSE AGREEMENT                   *
# ***************************************
echo -e "##############################################################"
echo -e "#                                                            #"
echo -e "#                   LICENSE AGREEMENT                        #"
echo -e "#                                                            #"
echo -e "##############################################################"
cat LICENSE
read -e -p "I have read and agree to the Terms & Conditions (y/n)? " rsn
while true; do
  case $rsn in
    [Yy]* ) break;;
    [Nn]* ) exit;
  esac
done

# Lets check for some common control panels that we know will affect the installation/operating of vxPanel
if [ -e /usr/local/cpanel ] || [ -e /usr/local/directadmin ] || [ -e /usr/local/solusvm/www ] || [ -e /usr/local/home/admispconfig ] || [ -e /etc/zpanel ] || [ -e /usr/local/lxlabs/kloxo ] ; then
  echo "You appear to have a control panel already installed on your server; This installer"
  echo "is designed to install and configure vxPanel on a clean OS installation only!"
  echo ""
  echo "Please re-install your OS before attempting to install using this script."
  exit
fi

# Ensure the installer is launched and can only be launched on Fedora 23
BITS=$(uname -m | sed 's/x86_//;s/i[3-6]86/32/')
if [ $BITS == 64 ]; then
  OS=$(cat /etc/redhat-release | head -n1 |  cut -d " " -f1)
  VER=$(cat /etc/redhat-release | grep '\(([A-Z][a-z]*\ [A-Z][a-z]*)\)' -o)
else
  OS=$(uname -s)
  VER=$(uname -r)
fi
echo "Detected $OS $VER $BITS"
if [ "$OS" == "Fedora" ] && [ "$VER" == "(Twenty Three)" ]; then
  echo "Ok."
else
  echo "Sorry, this installer only supports the installation of VXpanel on Fedora 23."
  exit 1;
fi

# Set custom logging methods so we create a log file in the current working directory
logfile=$$.log
touch $$.log
exec > >(tee $logfile)
exec 2>&1

# ***************************************
# * Common installer functions          *
# ***************************************

# Needed by the installer
dnf -y update
dnf -y install curl expect

# Generates random passwords
passwordgen() {
	l=$1
	[ "$l" == "" ] && l=20
	tr -dc A-Za-z0-9 < /dev/urandom | head -c ${l} | xargs
}

# Display the 'welcome' splash/user warning info..
echo -e ""
echo -e "##############################################################"
echo -e "# Welcome to the vxPanel Installer for Fedora x86_64         #"
echo -e "#                                                            #"
echo -e "# Please make sure your VPS provider hasn't pre-installed    #"
echo -e "# any packages required by vxPanel.                          #"
echo -e "#                                                            #"
echo -e "# If you selected additional options during the Fedora       #"
echo -e "# install please consider reinstalling without them.         #"
echo -e "#                                                            #"
echo -e "##############################################################"
echo -e ""

# Set some installation defaults/auto assignments
fqdn=`/bin/hostname -f`
publicip=`curl -s http://whatismijnip.nl | cut -d " " -f 5`

# We need to disable SElinux
sed -i 's/SELINUX=enforcing/SELINUX=disabled/g' /etc/selinux/config
setenforce 0

# Installer options
while true; do
	tz=`tzselect | tail -n1`
	export TZ=$tz
	echo -e "Enter the FQDN you will use to access vxPanel on your server."
	echo -e "- It MUST be a sub-domain of you main domain, it MUST NOT be your main domain only. Example: panel.yourdomain.com"
	echo -e "- Remember that the sub-domain ('panel' in the example) MUST be setup in your DNS nameserver."
	read -e -p "FQDN for VXpanel: " -i $fqdn fqdn
	read -e -p "Enter the public (external) server IP: " -i $publicip publicip
	break;
done

# Start log creation.
echo -e ""
echo -e "# Generating installation log and debug info..."
uname -a
echo -e ""

mkdir -p /usr/local/vxpanel
cp -R . /usr/local/vxpanel
cd /usr/local/vxpanel

# Install required software and dependencies required by vxPanel
dnf install -y mariadb mariadb-server httpd firewalld php php-common php-cli php-mysql php-gd php-mcrypt php-curl php-pear php-imap php-xmlrpc php-xsl php-soap libdb-utils dovecot dovecot-pigeonhole dovecot-mysql postfix cyrus-sasl-lib proftpd-mysql phpmyadmin

# At least start the database and firewall
systemctl start mariadb
systemctl start firewalld

# Add exception to firewall
echo -e "Add exceptions to firewall"
firewall-cmd --set-default-zone=public
firewall-cmd --permanent --zone=public --add-service=http
firewall-cmd --permanent --zone=public --add-service=https
firewall-cmd --permanent --zone=public --add-service=ftp
firewall-cmd --permanent --zone=public --add-service=smtp
firewall-cmd --permanent --zone=public --add-service=mysql
firewall-cmd --reload

# Generation of random passwords
db_passwd=`passwordgen`;
mail_passwd=`passwordgen`;
admin_passwd=`passwordgen`;

# Set-up vxPanel directories and configure directory permissions as required
mkdir /var/vxpanel
mkdir /var/vxpanel/logs
mkdir /var/vxpanel/logs/proftpd
mkdir /var/vxpanel/logs/apache
mkdir /var/vxpanel/backups
mkdir /var/vxpanel/tmp

chmod -R 777 /var/vxpanel/
chmod +x /usr/local/vxpanel/bin/vxd

ln -s /usr/local/vxpanel/bin/vxd /usr/bin/vxd
ln -s /usr/local/vxpanel/etc/config.json /etc/vxpanel.conf

# MariaDB specific installation tasks...
MYSQL_ROOT_PASSWORD=$db_passwd
SECURE_MYSQL=$(expect -c "
set timeout 10
spawn mysql_secure_installation
expect \"Enter current password for root (enter for none):\"
send \"\r\"
expect \"Change the root password?\"
send \"y\r\"
expect \"New password:\"
send \"$db_passwd\r\"
expect \"Re-enter new password:\"
send \"$db_passwd\r\"
expect \"Remove anonymous users?\"
send \"y\r\"
expect \"Disallow root login remotely?\"
send \"y\r\"
expect \"Remove test database and access to it?\"
send \"y\r\"
expect \"Reload privilege tables now?\"
send \"y\r\"
expect eof
")
echo "$SECURE_MYSQL"
mysql -u root -p$db_passwd -e "DELETE FROM mysql.user WHERE User = 'root' AND Host != 'localhost'";
mysql -u root -p$db_passwd -e "DELETE FROM mysql.user WHERE User = ''";
mysql -u root -p$db_passwd -e "DELETE FROM mysql.user WHERE User != 'root'";
mysql -u root -p$db_passwd -e "FLUSH PRIVILEGES";
# mysql -u root -p$db_passwd -e "CREATE SCHEMA vxpanel_roundcube";
cat /usr/local/vxpanel/create.sql | mysql -u root -p$db_passwd
# mysql -u root -p$db_passwd -e "UPDATE mysql.user SET Password=PASSWORD('$postfixpassword') WHERE User='postfix' AND Host='localhost';";
# mysql -u root -p$db_passwd -e "FLUSH PRIVILEGES";

# Set some vxPanel custom configuration settings (using. setso and setzadmin)
# vxadmin --set "$admin_passwd";
# /etc/vxpanel/panel/bin/setso --set vxpanel_domain $fqdn
# /etc/vxpanel/panel/bin/setso --set server_ip $publicip
# /etc/vxpanel/panel/bin/setso --set apache_changed "true"

# We'll store the passwords so that users can review them later if required.
echo "Store settings in vxconfig.txt"
touch /root/vxconfig.txt;
echo "Admin Password: $admin_passwd" >> /root/vxconfig.txt;
echo "MariaDB Root Password: $password" >> /root/vxconfig.txt
echo "MariaDB Postfix Password: $postfixpassword" >> /root/vxconfig.txt
echo "IP Address: $publicip" >> /root/vxconfig.txt
echo "Panel Domain: $fqdn" >> /root/vxconfig.txt
chmod 600 /root/vxconfig.txt

# PHP specific installation tasks...
echo "Reconfigure PHP settings"
sed -i "s|;date.timezone =|date.timezone = $tz|" /etc/php.ini
sed -i "s|;upload_tmp_dir =|upload_tmp_dir = /var/vxpanel/tmp/|" /etc/php.ini
sed -i "s|upload_max_filesize = 2M|upload_max_filesize = 500M|" /etc/php.ini
sed -i "s|post_max_size = 8M|post_max_size = 1G|" /etc/php.ini
sed -i "s|memory_limit = 128M|memory_limit = 256M|" /etc/php.ini
sed -i "s|expose_php = On|expose_php = Off|" /etc/php.ini
sed -i "s|session.gc_maxlifetime = 1440|session.gc_maxlifetime = 7200|" /etc/php.ini
sed -i "s|session.name = PHPSESSID|session.name = _UMTAUTHS|" /etc/php.ini
sed -i "s|session.hash_function = 0|session.hash_function = 1|" /etc/php.ini

# TODO and further.....#

# Postfix specific installation tasks...
echo "Setup SMTP"
mkdir -p /var/zpanel/vmail
chmod -R 770 /var/zpanel/vmail
useradd -r -u 150 -g mail -d /var/zpanel/vmail -s /sbin/nologin -c "Virtual maildir" vmail
chown -R vmail:mail /var/zpanel/vmail
mkdir -p /var/spool/vacation
useradd -r -d /var/spool/vacation -s /sbin/nologin -c "Virtual vacation" vacation
chmod -R 770 /var/spool/vacation
ln -s /etc/zpanel/configs/postfix/vacation.pl /var/spool/vacation/vacation.pl
postmap /etc/postfix/transport
chown -R vacation:vacation /var/spool/vacation
if ! grep -q "127.0.0.1 autoreply.$fqdn" /etc/hosts; then echo "127.0.0.1 autoreply.$fqdn" >> /etc/hosts; fi
sed -i "s|myhostname = control.yourdomain.com|myhostname = $fqdn|" /etc/zpanel/configs/postfix/main.cf
sed -i "s|mydomain = control.yourdomain.com|mydomain   = $fqdn|" /etc/zpanel/configs/postfix/main.cf
rm -rf /etc/postfix/main.cf /etc/postfix/master.cf
ln -s /etc/zpanel/configs/postfix/master.cf /etc/postfix/master.cf
ln -s /etc/zpanel/configs/postfix/main.cf /etc/postfix/main.cf
sed -i "s|password \= postfix|password \= $postfixpassword|" /etc/zpanel/configs/postfix/mysql-relay_domains_maps.cf
sed -i "s|password \= postfix|password \= $postfixpassword|" /etc/zpanel/configs/postfix/mysql-virtual_alias_maps.cf
sed -i "s|password \= postfix|password \= $postfixpassword|" /etc/zpanel/configs/postfix/mysql-virtual_domains_maps.cf
sed -i "s|password \= postfix|password \= $postfixpassword|" /etc/zpanel/configs/postfix/mysql-virtual_mailbox_limit_maps.cf
sed -i "s|password \= postfix|password \= $postfixpassword|" /etc/zpanel/configs/postfix/mysql-virtual_mailbox_maps.cf
sed -i "s|\$db_password \= 'postfix';|\$db_password \= '$postfixpassword';|" /etc/zpanel/configs/postfix/vacation.conf

# Dovecot specific installation tasks (includes Sieve)
echo "Setup IMAP/POP"
mkdir -p /var/zpanel/sieve
chown -R vmail:mail /var/zpanel/sieve
mkdir -p /var/lib/dovecot/sieve/
touch /var/lib/dovecot/sieve/default.sieve
ln -s /etc/zpanel/configs/dovecot2/globalfilter.sieve /var/zpanel/sieve/globalfilter.sieve
rm -rf /etc/dovecot/dovecot.conf
ln -s /etc/zpanel/configs/dovecot2/dovecot.conf /etc/dovecot/dovecot.conf
sed -i "s|postmaster_address = postmaster@your-domain.tld|postmaster_address = postmaster@$fqdn|" /etc/dovecot/dovecot.conf
sed -i "s|password=postfix|password=$postfixpassword|" /etc/zpanel/configs/dovecot2/dovecot-dict-quota.conf
sed -i "s|password=postfix|password=$postfixpassword|" /etc/zpanel/configs/dovecot2/dovecot-mysql.conf
touch /var/log/dovecot.log
touch /var/log/dovecot-info.log
touch /var/log/dovecot-debug.log
chown vmail:mail /var/log/dovecot*
chmod 660 /var/log/dovecot*

# ProFTPD specific installation tasks
echo "Setup FTP"
groupadd -g 2001 ftpgroup
useradd -u 2001 -s /bin/false -d /bin/null -c "proftpd user" -g ftpgroup ftpuser
sed -i "s|zpanel_proftpd@localhost root z|zpanel_proftpd@localhost root $password|" /etc/zpanel/configs/proftpd/proftpd-mysql.conf
rm -rf /etc/proftpd.conf
touch /etc/proftpd.conf
rm -rf /etc/proftpd.conf
ln -s /etc/zpanel/configs/proftpd/proftpd-mysql.conf /etc/proftpd.conf
chmod -R 644 /var/zpanel/logs/proftpd
serverhost=`hostname`

# Apache HTTPD specific installation tasks...
echo "Reconfigure Apache"
rm -rf /etc/httpd/conf/httpd.conf
ln -s /etc/zpanel/configs/apache/httpd.conf /etc/httpd/conf/httpd.conf
if ! grep -q "127.0.0.1 "$fqdn /etc/hosts; then echo "127.0.0.1 "$fqdn >> /etc/hosts; fi
if ! grep -q "apache ALL=NOPASSWD: /etc/zpanel/panel/bin/zsudo" /etc/sudoers; then echo "apache ALL=NOPASSWD: /etc/zpanel/panel/bin/zsudo" >> /etc/sudoers; fi
chown -R apache:apache /var/zpanel/temp/

# Permissions fix for Apache and ProFTPD (to enable them to play nicely together!)
if ! grep -q "umask 002" /etc/sysconfig/httpd; then echo "umask 002" >> /etc/sysconfig/httpd; fi
if ! grep -q "127.0.0.1 $serverhost" /etc/hosts; then echo "127.0.0.1 $serverhost" >> /etc/hosts; fi
usermod -a -G apache ftpuser
usermod -a -G ftpgroup apache

# CRON specific installation tasks...
echo "Setting up cron tasks"
mkdir -p /var/spool/cron/
mkdir -p /etc/cron.d/
touch /var/spool/cron/apache
touch /etc/cron.d/apache
crontab -u apache /var/spool/cron/apache
cp /etc/zpanel/configs/cron/zdaemon /etc/cron.d/zdaemon
chmod 744 /var/spool/cron
chmod 644 /var/spool/cron/apache
chmod -R 644 /etc/cron.d/
chown -R apache:apache /var/spool/cron/

# Webalizer specific installation tasks...
# echo "Configure webstatistics"
# rm -rf /etc/webalizer.conf

# phpMyAdmin config
salt=`passwordgen`;
echo "Configure phpMyAdmin"
rm -rf /etc/phpMyAdmin/config.inc.php
ln -s /etc/zpanel/configs/phpmyadmin/config.inc.php /etc/phpMyAdmin/config.inc.php
sed -i "s|CHANGE_ME|$salt|" /etc/phpMyAdmin/config.inc.php

# Roundcube specific installation tasks...
echo "Configure RoundCube"
sed -i "s|YOUR_MYSQL_ROOT_PASSWORD|$password|" /etc/zpanel/configs/roundcube/db.inc.php
sed -i "s|#||" /etc/zpanel/configs/roundcube/db.inc.php
rm -rf /etc/zpanel/panel/etc/apps/webmail/config/main.inc.php
ln -s /etc/zpanel/configs/roundcube/main.inc.php /etc/zpanel/panel/etc/apps/webmail/config/main.inc.php
ln -s /etc/zpanel/configs/roundcube/config.inc.php /etc/zpanel/panel/etc/apps/webmail/plugins/managesieve/config.inc.php
ln -s /etc/zpanel/configs/roundcube/db.inc.php /etc/zpanel/panel/etc/apps/webmail/config/db.inc.php

# Enable system services and start/restart them as required.
echo "Enable services"
systemctl enable mariadb
systemctl enable httpd
systemctl enable postfix
systemctl enable dovecot
systemctl enable proftpd
systemctl enable firewalld
systemctl enable atd

echo "Starting services"
systemctl start httpd
systemctl restart postfix
systemctl start dovecot
systemctl reload crond
systemctl restart mariadb
systemctl start proftpd
systemctl restart atd

# We'll now remove the temporary install cache.
echo "Cleanup..."
dnf -y autoremove

# Advise the user that VXpanel is now installed and accessible.
echo -e "##############################################################" &>/dev/tty
echo -e "# Congratulations vxPanel has now been installed on your     #" &>/dev/tty
echo -e "# server. Please review the log file for any errors          #" &>/dev/tty
echo -e "# encountered during installation.                           #" &>/dev/tty
echo -e "#                                                            #" &>/dev/tty
echo -e "# Save the following information somewhere safe:             #" &>/dev/tty
echo -e "# MariaDB Root Password    : $db_passwd" &>/dev/tty
echo -e "# MariaDB Postfix Password : $mail_passwd" &>/dev/tty
echo -e "# vxPanel Username        : admin                            #" &>/dev/tty
echo -e "# vxPanel Password        : $admin_passwd" &>/dev/tty
echo -e "#                                                            #" &>/dev/tty
echo -e "# vxPanel Web login can be accessed using your server IP      #" &>/dev/tty
echo -e "# inside your web browser.                                   #" &>/dev/tty
echo -e "#                                                            #" &>/dev/tty
echo -e "#                !!! A REBOOT IS REQUIRED !!!                #" &>/dev/tty
echo -e "#                                                            #" &>/dev/tty
echo -e "##############################################################" &>/dev/tty
echo -e "" &>/dev/tty

# We now request that the user restarts their server...
read -e -p "Restart your server now to complete the install (RECOMMENDED) (y/n)? " rsn
while true; do
	case $rsn in
		[Yy]* ) break;;
		[Nn]* ) exit;
	esac
done
shutdown -r now
