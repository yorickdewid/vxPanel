MODDIR = model
VALDIR = validation
FUNDIR = function
CXX_SRCS = $(wildcard *.cpp)
CXX_OBJS = ${CXX_SRCS:.cpp=.o}
CPPFLAGS += -O0 -Wall -Werror -Wno-reorder -g -std=c++14 -DSAMPLE
LDFLAGS += $(foreach library,$(LIBRARIES),-l$(library))

.PHONY: all clean distclean

all: $(CXX_OBJS)
	cd $(MODDIR); $(MAKE) $(MFLAGS)
	cd $(VALDIR); $(MAKE) $(MFLAGS)
	cd $(FUNDIR); $(MAKE) $(MFLAGS)

clean:
	@- $(RM) $(CXX_OBJS)
	cd $(MODDIR); $(MAKE) clean
	cd $(VALDIR); $(MAKE) clean
	cd $(FUNDIR); $(MAKE) clean

distclean: clean
