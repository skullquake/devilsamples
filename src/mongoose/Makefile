#todo: filter list and cflags...
JSONCPP=OFF
YAML=OFF
CPR=ON
CURSES=OFF
CACA=OFF
FILTER_OUT = $(foreach v,$(2),$(if $(findstring $(1),$(v)),,$(v)))
CXX=g++
CC=gcc
BUILDDIR=bin
SOURCEDIR=./src
MACHINE=$(shell $(CXX) -dumpmachine)
ifneq (,$(findstring mingw,$(MACHINE)))
	BINEXT=exe
else
	BINEXT=out
endif
#todo: filter list and cflags...
ifeq ($(JSONCPP),ON)
	SOURCES=$(shell find $(SOURCEDIR) -name "*.cpp" -o -name "*.c" )
else
	SOURCES=$(call FILTER_OUT,jsoncpp,$(shell find $(SOURCEDIR) -name "*.cpp" -o -name "*.c" ))
endif
OBJECTS=$(addprefix $(BUILDDIR)/,$(patsubst %.c,%.o ,$(patsubst %.cpp,%.o,$(SOURCES))))
CXXFLAGS=\
	-I./include\
	-I./include/mongoose-cpp\
	-I./include/mongoose\
	-I./include/mongoose/sqlite3\
	-I./include/mongoose/SQLiteCpp\
	-DNO_WEBSOCKET\
	-fpermissive\
	`pkg-config --cflags jsoncpp`\
	`pkg-config --cflags IL`\
	`pkg-config --cflags ILU`\
	`pkg-config --cflags ILUT`
#todo: filter list and cflags...
ifeq ($(JSONCPP),ON)
	CXXFLAGS+=\
		-I./include/jsoncpp
else
	CXXFLAGS+=\
		-DNO_JSONCPP
endif
CFLAGS=$(CXXFLAGS)
LDFLAGS=\
	-lcurl\
	`pkg-config --libs IL`\
	`pkg-config --libs ILU`\
	`pkg-config --libs ILUT`
ifneq (,$(findstring mingw,$(MACHINE)))
LDFLAGS+=\
	-ldl\
	-lws2_32\
	-lstdc++
else
LDFLAGS+=\
	-lpthread\
	-lc\
	-ldl
endif
LDFLAGS+=\
	`pkg-config --libs jsoncpp`
BIN=./bin/a.$(BINEXT)
default:all
all: $(BIN) $(BUILD_NUMBER_FILE)
$(BIN): $(OBJECTS) 
	@mkdir -p $(@D)
	@printf "generating $@...\n"
	$(CXX)\
		$(CXXFLAGS)\
		$(OBJECTS)\
		$(LDFLAGS)\
		-o $(BIN)
$(BUILDDIR)/%.o: %.cpp
	@printf "generating $@...\n"
	@mkdir -p $(@D)
	$(CXX)\
		$(CXXFLAGS)\
		-I$(HEADERDIR)\
		-I$(dir $<)\
		-c $<\
		-o $@
$(BUILDDIR)/%.o: %.c
	@printf "generating $@...\n"
	@mkdir -p $(@D)
	$(CC)\
		$(CFLAGS)\
		-I$(HEADERDIR)\
		-I$(dir $<)\
		-c $<\
		-o $@
.phony:\
	run\
	clean\
	test
run: $(BIN)
	$(BIN)
clean:
	rm -r $(BIN) ./bin/src
test:
	@echo $(OBJECTS)
