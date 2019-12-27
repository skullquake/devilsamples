OS=$(shell $(CXX) -dumpmachine)
ifneq (,$(findstring mingw,$(OS)))
SOEXT?=dll
BINEXT?=exe
else
SOEXT?=so
BINEXT?=out
endif
ifeq ($(PREFIX),)
PREFIX := /usr/local
endif
CC=gcc
CXX=g++
AR=ar
BUILDDIR=./bin/build
BIN=./bin/a.$(BINEXT)
SRCDIR=src
SRC:=$(shell find $(SRCDIR) -name '*.cpp')
OBJS:=$(addprefix $(BUILDDIR)/,$(SRC:%.cpp=%.o))
CFLAGS=\
	-I./include\
	`pkg-config --cflags IL`\
	`pkg-config --cflags ILU`\
	`pkg-config --cflags ILUT`
LDFLAGS=\
	`pkg-config --libs IL`\
	`pkg-config --libs ILU`\
	`pkg-config --libs ILUT`
all:\
	$(BIN)
$(BIN):$(OBJS)
	@$(CXX)\
		$(CFLAGS)\
		$(OBJS)\
		$(LDFLAGS)\
		-o $(BIN)
$(BUILDDIR)/%.o: %.cpp
	@printf "generating $@...\n"
	@mkdir -p $(@D)
	@$(CXX)\
		$(CFLAGS)\
		-c $<\
		$(LDFLAGS)\
		-o $@
.phony:\
	run\
	clean\
	lsvar
clean:
	@rm -r ./bin
	@rm ./out/*
run: $(BIN)
	@$(BIN)\
		../res/b.jpg\
		../out/a.jpg
	http-server ../out
