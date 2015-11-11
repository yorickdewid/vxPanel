LIBS=-lcppcms


all: vxpanel

vxpanel: vxpanel.cpp
	$(CXX) $(CXXFLAGS) -O3 -Wall -g vxpanel.cpp -o vxd ${LIBS}

clean:
	rm -fr vxd
