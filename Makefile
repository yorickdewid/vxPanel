LIBS=-lcppcms -lcppdb

all: vxpanel

vxpanel: vxpanel.cpp
	$(CXX) $(CXXFLAGS) -O0 -Wall -g master.cpp vxpanel.cpp -o vxd ${LIBS}

test:
	./vxd -c config.json &
	python tests/basic_call.py
	killall vxd

clean:
	rm -fr vxd
