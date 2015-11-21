LIBS=-lcppcms -lcppdb
SRCDIR=src

all: vxpanel

vxpanel:
	$(CXX) $(CXXFLAGS) -O0 -Wall -g $(SRCDIR)/backend.cpp \
									$(SRCDIR)/sha1.cpp \
									$(SRCDIR)/user.cpp \
									$(SRCDIR)/master.cpp \
									$(SRCDIR)/vxpanel.cpp -o vxd ${LIBS}

test: all
	./vxd -c config.json &
	python tests/basic_call.py
	killall vxd

clean:
	rm -rf vxd
