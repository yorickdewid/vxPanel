LIBS=-lcppcms -lcppdb
SRCDIR=src

all: vxpanel

vxpanel:
	$(CXX) $(CXXFLAGS) -O0 -Wall -g -std=c++11 -std=gnu++11 $(SRCDIR)/backend.cpp \
									$(SRCDIR)/sha1.cpp \
									$(SRCDIR)/user.cpp \
									$(SRCDIR)/domain.cpp \
									$(SRCDIR)/dns.cpp \
									$(SRCDIR)/ftp_account.cpp \
									$(SRCDIR)/vhost.cpp \
									$(SRCDIR)/mailbox.cpp \
									$(SRCDIR)/subdomain.cpp \
									$(SRCDIR)/master.cpp \
									$(SRCDIR)/vxpanel.cpp -o vxd ${LIBS}

test: all
	./vxd -c config.json &
	python tests/pre_run.py config.json &
	python tests/basic_call.py
	killall vxd

clean:
	rm -rf vxd
