NAME = vxd
SRCDIR = src
MODDIR = $(SRCDIR)/model
CXX_OBJS = $(wildcard src/model/*.o) $(wildcard src/*.o)
INCLUDE_DIRS = .
LIBRARY_DIRS = .
LIBRARIES = cppcms cppdb
CPPFLAGS += -O0 -Wall -Werror -g -std=c++11
CPPFLAGS += $(foreach includedir,$(INCLUDE_DIRS),-I$(includedir))
LDFLAGS += $(foreach librarydir,$(LIBRARY_DIRS),-L$(librarydir))
LDFLAGS += $(foreach library,$(LIBRARIES),-l$(library))

.PHONY: all clean distclean

all: $(NAME) link

$(NAME):
	cd $(SRCDIR); $(MAKE) $(MFLAGS)

link:
	$(LINK.cc) $(CXX_OBJS) -o $(NAME)

test: all
	$(NAME) -c config.json &
	python tests/pre_run.py config.json
	python tests/basic_call.py
	killall $(NAME)

clean:
	@- $(RM) $(NAME)
	@- $(RM) $(LD_CXX_OBJS)
	cd $(SRCDIR); $(MAKE) clean

distclean: clean
