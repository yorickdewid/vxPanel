CXX_SRCS = $(wildcard *.cpp)
CXX_OBJS = ${CXX_SRCS:.cpp=.o}
CPPFLAGS += -O0 -Wall -Werror -Wno-reorder -g -std=c++14

.PHONY: all clean distclean

all: $(CXX_OBJS)

clean:
	@- $(RM) $(CXX_OBJS)

distclean: clean
