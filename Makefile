NAMECNF = config.json
NAME = vxd
SRCDIR = src
BINDIR = bin
MODDIR = $(SRCDIR)/model
CXX_OBJS = $(wildcard $(MODDIR)/*.o) $(wildcard $(SRCDIR)/*.o)
GRINDFLAGS = --leak-check=full --track-origins=yes
GRIND = valgrind
CPPCHECKFLAGS = --quiet --std=c++11
CPPCHECK = cppcheck
INCLUDE_DIRS = .
LIBRARY_DIRS = /usr/local/lib /usr/lib64 /usr/lib
LIBRARIES = cppcms cppdb
CPPFLAGS += -O0 -Wall -Werror -g -std=c++11
CPPFLAGS += $(foreach includedir,$(INCLUDE_DIRS),-I$(includedir))
LDFLAGS += $(foreach librarydir,$(LIBRARY_DIRS),-L$(librarydir))
LDFLAGS += $(foreach library,$(LIBRARIES),-l$(library))

.PHONY: all link test clean distclean

all: $(NAME) link

$(NAME):
	cd $(SRCDIR); $(MAKE) $(MFLAGS)

link:
	$(LINK.cc) $(CXX_OBJS) -o $(BINDIR)/$(NAME)

test: all
	$(BINDIR)/$(NAME) -c $(NAMECNF) &
	python tests/pre_run.py $(NAMECNF)
	python tests/basic_call.py
	killall $(NAME)

clean:
	@- $(RM) $(BINDIR)/$(NAME)
	@- $(RM) $(LD_CXX_OBJS)
	cd $(SRCDIR); $(MAKE) clean

memcheck: all
	$(GRIND) $(GRINDFLAGS) $(BINDIR)/$(NAME) -c $(NAMECNF)

cov: all
	$(CPPCHECK) $(CPPCHECKFLAGS) $(MODDIR) $(SRCDIR)

distclean: clean
	@- $(RM) dist*.tar.gz
	@- $(RM) -rf dist
