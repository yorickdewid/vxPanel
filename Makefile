LIBS=-lcppcms -lcppdb

all: vxpanel

vxpanel: vxpanel.cpp
	$(CXX) $(CXXFLAGS) -O0 -Wall -g master.cpp vxpanel.cpp -o vxd ${LIBS}

clean:
	rm -fr vxd
