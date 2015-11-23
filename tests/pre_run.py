#!/usr/bin/python

import json
import MySQLdb as mdb
import sys

def open_config_file(configname):
	file = open(configname,"r")
	config = json.loads(file.read());
	return config["db"]

config = open_config_file(sys.argv[1])

def open_conn():
	global config
	con = mdb.connect('localhost', config["user"], config["password"])
	return con

def drop_db():
	try:
		global config
		con = open_conn()
		cur = con.cursor()
    		cur.execute("drop database "+config["database"]+";")
	except mdb.Error, e:
	    print "Error %d: %s" % (e.args[0],e.args[1])
	    sys.exit(1)
	finally:
	    if con:    
	        con.close()
	    print "database vxpanel deleted"

def create_db():
	try:	
		global config
		sql = open_sql_file()
		con = open_conn()
		cur = con.cursor()
    		cur.execute(sql)
	except mdb.Error, e:
	    print "Error %d: %s" % (e.args[0],e.args[1])
	    sys.exit(1)
	finally:
	    if con:    
	        con.close()
	    print "database vxpanel created"

def open_sql_file():
	file = open("scheme/create.sql","r")
	return file.read()

# drop and create to have clean tests
drop_db()
create_db()