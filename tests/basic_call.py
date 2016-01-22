#!/usr/bin/python

import urllib
import urllib2
import json
import time
import sys
import os

class bcolors:
	HEADER = '\033[95m'
	OKBLUE = '\033[94m'
	OKGREEN = '\033[92m'
	WARNING = '\033[93m'
	FAIL = '\033[91m'
	ENDC = '\033[0m'
	BOLD = '\033[1m'
	UNDERLINE = '\033[4m'

# Default settings
url = 'http://localhost:8080/rpc'
headers = { 'Content-Type' : 'application/json; charset=UTF-8' }
auth_header = 'X_AUTH_TOKEN'

def open_config_file(configname):
	file = open(configname,"r")
	config = json.loads(file.read());
	return config["db"]

def rpc_call(data, extra_header = None):
	if extra_header is None:
		req = urllib2.Request(url, data, headers)
	else:
		headers_merge = headers.copy()
		headers_merge.update(extra_header)
		req = urllib2.Request(url, data, headers_merge)
	response = urllib2.urlopen(req)
	return response.read()

def result_test(result, expected):
	if not result:
		return
	try:
		print result
		rs = json.loads(result)
		if rs['error']:
			print bcolors.FAIL + "Testcase: failed" + bcolors.ENDC
			return
		if expected:
			if rs['result'] != expected:
				print bcolors.FAIL + "Testcase: failed" + bcolors.ENDC
				return
		print bcolors.OKGREEN + "Testcase: passed" + bcolors.ENDC
	except ValueError:
		print "Json parsing failed"	

def test_rpc_sum():
	print bcolors.OKBLUE + "Testcase: Sum two integers" + bcolors.ENDC
	data = '{"id":0,"method":"sum","params":[7,2]}'
	result_test(rpc_call(data), 9)

def test_rpc_uptime():
	print bcolors.OKBLUE + "Testcase: Retrieve system uptime" + bcolors.ENDC
	data = '{"id":0,"method":"uptime","params":[]}'
	result_test(rpc_call(data), None)

def test_rpc_version():
	print bcolors.OKBLUE + "Testcase: Daemon version" + bcolors.ENDC
	data = '{"id":0,"method":"version","params":[]}'
	result_test(rpc_call(data), "VxPanel version 0.1")

def test_rpc_db_version():
	print bcolors.OKBLUE + "Testcase: Database version" + bcolors.ENDC
	data = '{"id":0,"method":"db_version","params":[]}'
	result_test(rpc_call(data), None)

def get_token(username, password):
	data = '{"id":0,"method":"authenticate","params":["'+username+'","'+password+'"]}'
	req = urllib2.Request(url, data, headers)
	response = urllib2.urlopen(req)
	rs = json.loads(response.read())
	result = rs['result']['auth']['token']
	return result
	# rs = json.loads(result)
	# auth = rs['auth']
	# print auth

### create ###
def test_rpc_create_user():
	print bcolors.OKBLUE + "Testcase: Create new user" + bcolors.ENDC
	data = '{"id":0,"method":"create_user","params":[{"required_list":{"username":"kaasie","email":"kaas@trol.com","password":"ABC@123"}, "optional_list":{}}]}'
	result_test(rpc_call(data), None)

def test_rpc_create_domain(token):
	print bcolors.OKBLUE + "Testcase: Create new domain" + bcolors.ENDC
	data = '{"id":0,"method":"create_domain","params":[{"required_list":{"name":"trol.com","uid":1001,"status":"waiting","registrar":"transip"}, "optional_list":{}}]}'
	result_test(rpc_call(data,{auth_header : token}), None)

def test_rpc_create_dns():
	print bcolors.OKBLUE + "Testcase: Create dns" + bcolors.ENDC
	data = '{"id":0,"method":"create_dns","params":[{"required_list":{"name":"A www trol.com","domain_name":"trol.com"}, "optional_list":{}}]}'
	result_test(rpc_call(data,{auth_header : token}), None)

def test_rpc_create_ftp_account():
	print bcolors.OKBLUE + "Testcase: Create ftp account" + bcolors.ENDC
	data = '{"id":0,"method":"create_ftp_account","params":[{"required_list":{"name":"kaasje","password":"hehjajejkhe","userid":1001,"homedir":"/kaasie"}, "optional_list":{}}]}'
	result_test(rpc_call(data,{auth_header : token}), None)

def test_rpc_create_vhost():
	print bcolors.OKBLUE + "Testcase: Create vhost" + bcolors.ENDC
	data = '{"id":0,"method":"create_vhost","params":[{"required_list":{"name":"trol.com","custom_config":"kaas"}, "optional_list":{}}]}'
	result_test(rpc_call(data,{auth_header : token}), None)

def test_rpc_create_mailbox():
	print bcolors.OKBLUE + "Testcase: Create mailbox" + bcolors.ENDC
	data = '{"id":0,"method":"create_mailbox","params":[{"required_list":{"email":"arie@trol.com","password":"kaas","maildir":"/usr/kaas","domain_name":"trol.com"}, "optional_list":{}}]}'
	result_test(rpc_call(data,{auth_header : token}), None)

def test_rpc_create_shell():
	print bcolors.OKBLUE + "Testcase: Create shell" + bcolors.ENDC
	data = '{"id":0,"method":"create_shell","params":[{"required_list":{"uid":1001}, "optional_list":{"active":false}}]}'
	result_test(rpc_call(data,{auth_header : token}), None)

def test_rpc_create_subdomain():
	print bcolors.OKBLUE + "Testcase: Create subdomain" + bcolors.ENDC
	data = '{"id":0,"method":"create_subdomain","params":[{"required_list":{"name":"kaas.", "domain_name":"trol.com"}, "optional_list":{"active":false}}]}'
	result_test(rpc_call(data,{auth_header : token}), None)

def test_rpc_create_setting():
	print bcolors.OKBLUE + "Testcase: Create setting" + bcolors.ENDC
	data = '{"id":0,"method":"create_setting","params":[{"required_list":{"key":"reboot","value":"23:00:00","default":"true","description":"reboot time"}, "optional_list":{}}]}'
	result_test(rpc_call(data,{auth_header : token}), None)

def test_rpc_create_db_user():
	print bcolors.OKBLUE + "Testcase: Create db user" + bcolors.ENDC
	data = '{"id":0,"method":"create_database_user","params":[{"required_list":{"name":"arie","password":"ae4834ejs","permissions":"RO","uid":1001}, "optional_list":{}}]}'
	result_test(rpc_call(data,{auth_header : token}), None)

def test_rpc_create_database():
	print bcolors.OKBLUE + "Testcase: Create database" + bcolors.ENDC
	data = '{"id":0,"method":"create_database","params":[{"required_list":{"name":"kaas","uid":1001,"db_type":"mysql"}, "optional_list":{}, "username":"arie"}]}'
	result_test(rpc_call(data,{auth_header : token}), None)

def test_rpc_create_queue():
	print bcolors.OKBLUE + "Testcase: Create queue" + bcolors.ENDC
	data = '{"id":0,"method":"create_queue","params":[{"required_list":{"action":"USERADD","uid":1000}, "optional_list":{"params":"kaas"}}]}'
	result_test(rpc_call(data,{auth_header : token}), None)

def test_rpc_create_domain_alias():
	print bcolors.OKBLUE + "Testcase: Create domain alias" + bcolors.ENDC
	data = '{"id":0,"method":"create_domain_alias","params":[{"required_list":{"source":"","destination":"","domain_name":"trol.com"}, "optional_list":{}}]}'
	result_test(rpc_call(data,{auth_header : token}), None)


### get ###
def test_rpc_get_user():
	print bcolors.OKBLUE + "Testcase: Get user" + bcolors.ENDC
	data = '{"id":0,"method":"get_user","params":[]}'
	result_test(rpc_call(data,{auth_header : token}), None)

def test_rpc_get_domain():
	print bcolors.OKBLUE + "Testcase: Get domain" + bcolors.ENDC
	data = '{"id":0,"method":"get_domain","params":["trol.com"]}'
	result_test(rpc_call(data,{auth_header : token}), None)

def test_rpc_get_dns():
	print bcolors.OKBLUE + "Testcase: Get dns" + bcolors.ENDC
	data = '{"id":0,"method":"get_dns","params":["trol.com"]}'
	result_test(rpc_call(data,{auth_header : token}), None)

def test_rpc_get_ftp_account():
	print bcolors.OKBLUE + "Testcase: Get ftp account" + bcolors.ENDC
	data = '{"id":0,"method":"get_ftp_account","params":["kaasje"]}'
	result_test(rpc_call(data,{auth_header : token}), None)

def test_rpc_get_vhost():
	print bcolors.OKBLUE + "Testcase: Get vhost" + bcolors.ENDC
	data = '{"id":0,"method":"get_vhost","params":["trol.com",1]}'
	result_test(rpc_call(data,{auth_header : token}), None)

def test_rpc_get_mailbox():
	print bcolors.OKBLUE + "Testcase: Get mailbox" + bcolors.ENDC
	data = '{"id":0,"method":"get_mailbox","params":["trol.com"]}'
	result_test(rpc_call(data,{auth_header : token}), None)

def test_rpc_get_shell():
	print bcolors.OKBLUE + "Testcase: Get shell" + bcolors.ENDC
	data = '{"id":0,"method":"get_shell","params":[1]}'
	result_test(rpc_call(data,{auth_header : token}), None)

def test_rpc_get_subdomain():
	print bcolors.OKBLUE + "Testcase: Get subdomain" + bcolors.ENDC
	data = '{"id":0,"method":"get_subdomain","params":["kaas.","trol.com"]}'
	result_test(rpc_call(data,{auth_header : token}), None)

def test_rpc_get_setting():
	print bcolors.OKBLUE + "Testcase: Get setting" + bcolors.ENDC
	data = '{"id":0,"method":"get_setting","params":["reboot"]}'
	result_test(rpc_call(data,{auth_header : token}), None)

def test_rpc_get_database_types():
	print bcolors.OKBLUE + "Testcase: Get database options" + bcolors.ENDC
	data = '{"id":0,"method":"get_database_types","params":[]}'
	result_test(rpc_call(data,{auth_header : token}), None)

def test_rpc_get_database_user():
	print bcolors.OKBLUE + "Testcase: Get database user" + bcolors.ENDC
	data = '{"id":0,"method":"get_database_user","params":["arie"]}'
	result_test(rpc_call(data,{auth_header : token}), None)

def test_rpc_get_database():
	print bcolors.OKBLUE + "Testcase: Get database" + bcolors.ENDC
	data = '{"id":0,"method":"get_database","params":["kaas"]}'
	result_test(rpc_call(data,{auth_header : token}), None)

def test_rpc_get_queue():
	print bcolors.OKBLUE + "Testcase: Get queue" + bcolors.ENDC
	data = '{"id":0,"method":"get_queue","params":[1]}'
	result_test(rpc_call(data,{auth_header : token}), None)

def test_rpc_get_domain_alias():
	print bcolors.OKBLUE + "Testcase: Get domain_alias" + bcolors.ENDC
	data = '{"id":0,"method":"get_domain_alias","params":[1]}'
	result_test(rpc_call(data,{auth_header : token}), None)


## get multiple
def test_rpc_get_users():
	print bcolors.OKBLUE + "Testcase: Get users" + bcolors.ENDC
	data = '{"id":0,"method":"get_users","params":[{"options":{}}]}'
	result_test(rpc_call(data,{auth_header : token}), None)

def test_rpc_get_domains():
	print bcolors.OKBLUE + "Testcase: Get domains" + bcolors.ENDC
	data = '{"id":0,"method":"get_domains","params":[{"options":{}}]}'
	result_test(rpc_call(data,{auth_header : token}), None)

def test_rpc_get_dns_records():
	print bcolors.OKBLUE + "Testcase: Get dns records" + bcolors.ENDC
	data = '{"id":0,"method":"get_dns_records","params":[{"options":{"domain_name":"trol.com"}}]}'
	result_test(rpc_call(data,{auth_header : token}), None)

def test_rpc_get_ftp_accounts():
	print bcolors.OKBLUE + "Testcase: Get ftp accounts" + bcolors.ENDC
	data = '{"id":0,"method":"get_ftp_accounts","params":[{"options":{}}]}'
	result_test(rpc_call(data,{auth_header : token}), None)

def test_rpc_get_vhosts():
	print bcolors.OKBLUE + "Testcase: Get vhosts" + bcolors.ENDC
	data = '{"id":0,"method":"get_vhosts","params":[{"options":{"domain_name":"trol.com"}}]}'
	result_test(rpc_call(data,{auth_header : token}), None)

def test_rpc_get_mailboxes():
	print bcolors.OKBLUE + "Testcase: Get mailboxes" + bcolors.ENDC
	data = '{"id":0,"method":"get_mailboxes","params":[{"options":{}}]}'
	result_test(rpc_call(data,{auth_header : token}), None)

def test_rpc_get_shells():
	print bcolors.OKBLUE + "Testcase: Get shells" + bcolors.ENDC
	data = '{"id":0,"method":"get_shells","params":[{"options":{}}]}'
	result_test(rpc_call(data,{auth_header : token}), None)

def test_rpc_get_subdomains():
	print bcolors.OKBLUE + "Testcase: Get subdomains" + bcolors.ENDC
	data = '{"id":0,"method":"get_subdomains","params":[{"options":{"domain_name":"trol.com"}}]}'
	result_test(rpc_call(data,{auth_header : token}), None)

def test_rpc_get_settings():
	print bcolors.OKBLUE + "Testcase: Get settings" + bcolors.ENDC
	data = '{"id":0,"method":"get_settings","params":[{"options":{}}]}'
	result_test(rpc_call(data,{auth_header : token}), None)

def test_rpc_get_database_users():
	print bcolors.OKBLUE + "Testcase: Get database users" + bcolors.ENDC
	data = '{"id":0,"method":"get_database_users","params":[{"options":{}}]}'
	result_test(rpc_call(data,{auth_header : token}), None)

def test_rpc_get_databases():
	print bcolors.OKBLUE + "Testcase: Get databases" + bcolors.ENDC
	data = '{"id":0,"method":"get_databases","params":[{"options":{}}]}'
	result_test(rpc_call(data,{auth_header : token}), None)

def test_rpc_get_queues():
	print bcolors.OKBLUE + "Testcase: Get queues" + bcolors.ENDC
	data = '{"id":0,"method":"get_queues","params":[{"options":{}}]}'
	result_test(rpc_call(data,{auth_header : token}), None)

### update ###

def test_rpc_update_user():
	print bcolors.OKBLUE + "Testcase: Update user" + bcolors.ENDC
	data = '{"id":0,"method":"update_user","params":[{"update_list":{"uid":1000,"address_number":255,"address":"kaassstraat"}}]}'
	result_test(rpc_call(data,{auth_header : token}), None)

def test_rpc_update_domain():
	print bcolors.OKBLUE + "Testcase: Update domain" + bcolors.ENDC
	data = '{"id":0,"method":"update_domain","params":[{"update_list":{"name":"trol.com","status":"kaas","active":0}}]}'
	result_test(rpc_call(data,{auth_header : token}), None)

def test_rpc_update_dns():
	print bcolors.OKBLUE + "Testcase: Update dns" + bcolors.ENDC
	data = '{"id":0,"method":"update_dns","params":[{"update_list":{"id":1,"name":"A www2.trol.com","active":0}}]}'
	result_test(rpc_call(data,{auth_header : token}), None)

def test_rpc_update_ftp_account():
	print bcolors.OKBLUE + "Testcase: Update ftp_account" + bcolors.ENDC
	data = '{"id":0,"method":"update_ftp_account","params":[{"update_list":{"name":"kaasje","homedir":"/usr/kaasie","count":1}}]}'
	result_test(rpc_call(data,{auth_header : token}), None)

def test_rpc_update_vhost():
	print bcolors.OKBLUE + "Testcase: Update vhost" + bcolors.ENDC
	data = '{"id":0,"method":"update_vhost","params":[{"update_list":{"id":1,"name":"trol.com","custom_config":"enable_write:true"}}]}'
	result_test(rpc_call(data,{auth_header : token}), None)

def test_rpc_update_mailbox():
	print bcolors.OKBLUE + "Testcase: Update mailbox" + bcolors.ENDC
	data = '{"id":0,"method":"update_mailbox","params":[{"update_list":{"id":1,"maildir":"/usr/kaasie","messages":10}}]}'
	result_test(rpc_call(data,{auth_header : token}), None)

def test_rpc_update_subdomain():
	print bcolors.OKBLUE + "Testcase: Update subdomain" + bcolors.ENDC
	data = '{"id":0,"method":"update_subdomain","params":[{"update_list":{"name":"kaas.","domain_name":"trol.com","active":0}}]}'
	result_test(rpc_call(data,{auth_header : token}), None)

def test_rpc_update_setting():
	print bcolors.OKBLUE + "Testcase: Update setting" + bcolors.ENDC
	data = '{"id":0,"method":"update_setting","params":[{"update_list":{"key":"reboot","value":"off"}}]}'
	result_test(rpc_call(data,{auth_header : token}), None)

def test_rpc_update_database_user():
	print bcolors.OKBLUE + "Testcase: Update database_user" + bcolors.ENDC
	data = '{"id":0,"method":"update_database_user","params":[{"update_list":{"name":"arie","permissions":"RWXR"}}]}'
	result_test(rpc_call(data,{auth_header : token}), None)

def test_rpc_update_database():
	print bcolors.OKBLUE + "Testcase: Update database" + bcolors.ENDC
	data = '{"id":0,"method":"update_database","params":[{"update_list":{"name":"kaas","db_type":"postgresql"}}]}'
	result_test(rpc_call(data,{auth_header : token}), None)

def test_rpc_update_domain_alias():
	print bcolors.OKBLUE + "Testcase: Update domain_alias" + bcolors.ENDC
	data = '{"id":0,"method":"update_domain_alias","params":[{"update_list":{"source":"trol.com","id":1}}]}'
	result_test(rpc_call(data,{auth_header : token}), None)



### delete ###

def test_rpc_delete_user():
	print bcolors.OKBLUE + "Testcase: Delete user" + bcolors.ENDC
	data = '{"id":0,"method":"delete_user","params":["kaasie"]}'
	result_test(rpc_call(data,{auth_header : token}), None)

def test_rpc_delete_domain():
	print bcolors.OKBLUE + "Testcase: Delete domain" + bcolors.ENDC
	data = '{"id":0,"method":"delete_domain","params":["trol.com"]}'
	result_test(rpc_call(data,{auth_header : token}), None)

def test_rpc_delete_dns():
	print bcolors.OKBLUE + "Testcase: Delete dns" + bcolors.ENDC
	data = '{"id":0,"method":"delete_dns","params":[1]}'
	result_test(rpc_call(data,{auth_header : token}), None)

def test_rpc_delete_ftp_account():
	print bcolors.OKBLUE + "Testcase: Delete ftp account" + bcolors.ENDC
	data = '{"id":0,"method":"delete_ftp_account","params":["kaasje"]}'
	result_test(rpc_call(data,{auth_header : token}), None)

def test_rpc_delete_vhost():
	print bcolors.OKBLUE + "Testcase: Delete vhost" + bcolors.ENDC
	data = '{"id":0,"method":"delete_vhost","params":[1]}'
	result_test(rpc_call(data,{auth_header : token}), None)

def test_rpc_delete_mailbox():
	print bcolors.OKBLUE + "Testcase: Delete mailbox" + bcolors.ENDC
	data = '{"id":0,"method":"delete_mailbox","params":[1]}'
	result_test(rpc_call(data,{auth_header : token}), None)

def test_rpc_delete_shell():
	print bcolors.OKBLUE + "Testcase: Delete shell" + bcolors.ENDC
	data = '{"id":0,"method":"delete_shell","params":[1]}'
	result_test(rpc_call(data,{auth_header : token}), None)

def test_rpc_delete_subdomain():
	print bcolors.OKBLUE + "Testcase: Delete subdomain" + bcolors.ENDC
	data = '{"id":0,"method":"delete_subdomain","params":["kaas.","trol.com"]}'
	result_test(rpc_call(data,{auth_header : token}), None)

def test_rpc_delete_setting():
	print bcolors.OKBLUE + "Testcase: Delete setting" + bcolors.ENDC
	data = '{"id":0,"method":"delete_setting","params":["reboot"]}'
	result_test(rpc_call(data,{auth_header : token}), None)

def test_rpc_delete_database_type():
	print bcolors.OKBLUE + "Testcase: Delete database options" + bcolors.ENDC
	data = '{"id":0,"method":"delete_database_type","params":["mysql"]}'
	result_test(rpc_call(data,{auth_header : token}), None)

def test_rpc_delete_database_user():
	print bcolors.OKBLUE + "Testcase: Delete database user" + bcolors.ENDC
	data = '{"id":0,"method":"delete_database_user","params":["arie"]}'
	result_test(rpc_call(data,{auth_header : token}), None)

def test_rpc_delete_database():
	print bcolors.OKBLUE + "Testcase: Delete database" + bcolors.ENDC
	data = '{"id":0,"method":"delete_database","params":["kaas","arie"]}'
	result_test(rpc_call(data,{auth_header : token}), None)

def test_rpc_delete_domain_alias():
	print bcolors.OKBLUE + "Testcase: Delete domain alias" + bcolors.ENDC
	data = '{"id":0,"method":"delete_domain_alias","params":[1]}'
	result_test(rpc_call(data,{auth_header : token}), None)


config = open_config_file(sys.argv[1])
os.system('mysql -u' + config['user'] +' -p' + config['password'] +' -e "DROP DATABASE IF EXISTS ' + config['database'] +'"')
if os.system('mysql -u' + config['user'] +' -p' + config['password'] +' < scheme/create.sql') is not 0:
	sys.exit(1)




# Call the testcases
# test_rpc_sum()
# test_rpc_uptime()
# test_rpc_version()
# test_rpc_db_version()

# # ## all 'perfect' scenarios ##

test_rpc_create_user()

#token
token = get_token("kaasie","ABC@123") # user_type user
# admin_token = get_token("admin","ABC@123") # user_type admin

test_rpc_create_domain(token)
test_rpc_create_dns()
test_rpc_create_ftp_account()
test_rpc_create_vhost()
test_rpc_create_mailbox()
test_rpc_create_shell()
test_rpc_create_subdomain()
test_rpc_create_setting()
test_rpc_create_db_user()
test_rpc_create_database()
test_rpc_create_queue()
test_rpc_create_domain_alias()

test_rpc_get_user()
test_rpc_get_domain()
test_rpc_get_dns()
test_rpc_get_ftp_account()
test_rpc_get_vhost()
test_rpc_get_mailbox()
test_rpc_get_shell()
test_rpc_get_subdomain()
test_rpc_get_setting()
test_rpc_get_database_user()
test_rpc_get_database()
test_rpc_get_queue()
test_rpc_get_domain_alias()

test_rpc_get_users()
test_rpc_get_domains()
test_rpc_get_dns_records()
test_rpc_get_ftp_accounts()
test_rpc_get_vhosts()
test_rpc_get_mailboxes()
test_rpc_get_shells()
test_rpc_get_subdomains()
test_rpc_get_settings()
test_rpc_get_database_types()
test_rpc_get_database_users()
test_rpc_get_databases()
test_rpc_get_queues()

# test_rpc_update_user()
# test_rpc_update_domain()
# test_rpc_update_dns()
# test_rpc_update_ftp_account()
# test_rpc_update_vhost()
# test_rpc_update_mailbox()
# test_rpc_update_subdomain()
# test_rpc_update_setting()
# test_rpc_update_database_user()
# test_rpc_update_database()
# test_rpc_update_domain_alias()

# test_rpc_delete_dns()
# test_rpc_delete_ftp_account()
# test_rpc_delete_vhost()
# test_rpc_delete_mailbox()
# test_rpc_delete_shell()
# test_rpc_delete_subdomain()
# test_rpc_delete_domain_alias()
# test_rpc_delete_setting()
# test_rpc_delete_database()
# test_rpc_delete_database_user() ## DELETE LAST (foreign key)
# test_rpc_delete_database_type() ## DELETE LAST (foreign key)
# test_rpc_delete_domain() ## DELETE LAST (foreign key)
# test_rpc_delete_user() ## DELETE LAST (foreign key)
## all 'perfect' scenarios ##