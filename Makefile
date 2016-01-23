NAMECNF = config.json
NAME = vxd
SRCDIR = src
BINDIR = bin
MODDIR = $(SRCDIR)/model
VALDIR = $(SRCDIR)/validation
CXX_OBJS = $(wildcard $(VALDIR)/*.o) $(wildcard $(MODDIR)/*.o) $(wildcard $(SRCDIR)/*.o) 
GRINDFLAGS = --leak-check=full --track-origins=yes
GRIND = valgrind
CPPCHECKFLAGS = --quiet --std=c++11
CPPCHECK = cppcheck
INCLUDE_DIRS = .
LIBRARY_DIRS = /usr/local/lib /usr/lib64 /usr/lib
LIBRARIES = cppcms cppdb
CPPFLAGS += -O0 -Wall -Werror -g -DSAMPLE -std=c++11
CPPFLAGS += $(foreach includedir,$(INCLUDE_DIRS),-I$(includedir))
LDFLAGS += $(foreach librarydir,$(LIBRARY_DIRS),-L$(librarydir))
LDFLAGS += $(foreach library,$(LIBRARIES),-l$(library))

.PHONY: all link test clean distclean

all: $(NAME) link

$(NAME):
	$(MAKE) -C $(SRCDIR) $(MFLAGS)

link:
	$(LINK.cc) $(CXX_OBJS) -o $(BINDIR)/$(NAME)

test: all
	$(BINDIR)/$(NAME) -c $(NAMECNF) &
	python tests/basic_call.py $(NAMECNF)
	killall $(NAME)

clean:
	@- $(RM) $(BINDIR)/$(NAME)
	@- $(RM) $(LD_CXX_OBJS)
	$(MAKE) -C $(SRCDIR) clean

memcheck: all
	$(GRIND) $(GRINDFLAGS) $(BINDIR)/$(NAME) -c $(NAMECNF)

cov: all
	$(CPPCHECK) $(CPPCHECKFLAGS) $(MODDIR) $(SRCDIR)

distclean: clean
	@- $(RM) dist*.tar.gz
	@- $(RM) -rf dist
