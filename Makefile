LIBS=-lcppcms -lcppdb
SRCDIR=src
MDIR=model/

all: vxpanel

vxpanel:
	$(CXX) $(CXXFLAGS) -O0 -Wall -g -std=c++11 -std=gnu++11 $(SRCDIR)/backend.cpp \
									$(SRCDIR)/sha1.cpp \
									$(SRCDIR)/$(MDIR)user.cpp \
									$(SRCDIR)/$(MDIR)domain.cpp \
									$(SRCDIR)/$(MDIR)dns.cpp \
									$(SRCDIR)/$(MDIR)ftp_account.cpp \
									$(SRCDIR)/$(MDIR)vhost.cpp \
									$(SRCDIR)/$(MDIR)mailbox.cpp \
									$(SRCDIR)/$(MDIR)subdomain.cpp \
									$(SRCDIR)/$(MDIR)shell.cpp \
									$(SRCDIR)/$(MDIR)app_settings.cpp \
									$(SRCDIR)/$(MDIR)database_type.cpp \
									$(SRCDIR)/$(MDIR)database_user.cpp \
									$(SRCDIR)/$(MDIR)database.cpp \
									$(SRCDIR)/$(MDIR)user_dbuser_db.cpp \
									$(SRCDIR)/master.cpp \
									$(SRCDIR)/vxpanel.cpp -o vxd ${LIBS}

test: all
	./vxd -c config.json &
	python tests/pre_run.py config.json &
	python tests/basic_call.py
	killall vxd

clean:
	rm -rf vxd
