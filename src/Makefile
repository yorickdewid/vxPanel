MODDIR = model
CXX_SRCS = $(wildcard *.cpp)
CXX_OBJS = ${CXX_SRCS:.cpp=.o}
CPPFLAGS += -O0 -Wall -Werror -g -std=c++11
LDFLAGS += $(foreach library,$(LIBRARIES),-l$(library))

.PHONY: all clean distclean

all: $(CXX_OBJS)
	cd $(MODDIR); $(MAKE) $(MFLAGS)

clean:
	@- $(RM) $(CXX_OBJS)
	cd $(MODDIR); $(MAKE) clean

distclean: clean