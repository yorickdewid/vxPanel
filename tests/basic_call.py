#!/usr/bin/python

import urllib
import urllib2
import json

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

def rpc_call(data):
	req = urllib2.Request(url, data, headers)
	response = urllib2.urlopen(req)
	return response.read()

def result_test(result, expected):
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

# Call the testcases
test_rpc_sum()
test_rpc_uptime()
test_rpc_version()
test_rpc_db_version()
