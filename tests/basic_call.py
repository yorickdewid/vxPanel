#!/usr/bin/python

import urllib
import urllib2
import json
import time
import MySQLdb as mdb

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

time.sleep(1)

def rpc_call(data):
	req = urllib2.Request(url, data, headers)
	response = urllib2.urlopen(req)
	return response.read()

def result_test(result, expected):
	if not result:
		return
	rs = json.loads(result)
	if rs['error']:
		print bcolors.FAIL + "Testcase: failed" + bcolors.ENDC
		return
	if expected:
		if rs['result'] != expected:
			print bcolors.FAIL + "Testcase: failed" + bcolors.ENDC
			return
	print bcolors.OKGREEN + "Testcase: passed" + bcolors.ENDC

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

def test_rpc_create_user():
	print bcolors.OKBLUE + "Testcase: Create new user" + bcolors.ENDC
	data = '{"id":0,"method":"create_user","params":["kaasie"]}'
	result_test(rpc_call(data), None)

def test_rpc_create_domain():
	print bcolors.OKBLUE + "Testcase: Create new domain" + bcolors.ENDC
	data = '{"id":0,"method":"create_domain","params":["trol.com",1]}'
	result_test(rpc_call(data), None)

def test_rpc_create_dns():
	print bcolors.OKBLUE + "Testcase: Create dns" + bcolors.ENDC
	data = '{"id":0,"method":"create_dns","params":["A www trol.com","trol.com"]}'
	result_test(rpc_call(data), None); 

def test_rpc_create_db_user():
	print bcolors.OKBLUE + "Testcase: Create db user" + bcolors.ENDC
	data = '{"id":0,"method":"create_database_user","params":["arie","ae4834ejs","RO",1]}'
	result_test(rpc_call(data), None); 

def test_rpc_create_database():
	print bcolors.OKBLUE + "Testcase: Create database" + bcolors.ENDC
	data = '{"id":0,"method":"create_database","params":["kaas","mysql",1]}'
	result_test(rpc_call(data), None);

def test_rpc_get_user():
	print bcolors.OKBLUE + "Testcase: Get user" + bcolors.ENDC
	data = '{"id":0,"method":"get_user","params":[1]}'
	result_test(rpc_call(data), None); #TODO json object comparison

def test_rpc_get_domain():
	print bcolors.OKBLUE + "Testcase: Get domain" + bcolors.ENDC
	data = '{"id":0,"method":"get_domain","params":["trol.com",1]}'
	result_test(rpc_call(data), None); #TODO json object comparison



# Call the testcases
test_rpc_sum()
test_rpc_uptime()
test_rpc_version()
test_rpc_db_version()
test_rpc_create_user()
test_rpc_create_domain()
test_rpc_create_dns();
test_rpc_create_db_user();
test_rpc_create_database();

test_rpc_get_user()
test_rpc_get_domain()