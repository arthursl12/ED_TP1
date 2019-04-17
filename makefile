CC := g++
MYDIR := $(dir $(realpath $(firstword $(MAKEFILE_LIST))))
SRCDIR := src
BIN := bin
BUILDDIR := build
TARGET := main

SRCEXT := cpp
CFLAGS := --coverage -g -Wall -Wno-unknown-pragmas -fno-strict-overflow -O3 -std=c++11
T_CFLAGS := --coverage -g -Wall -O3
INC := -I include -I third-party


MODULES = lista listacurso curso candidato
SOURCES = $(addsuffix .cpp,$(MODULES))
OBJECTS = $(patsubst %.cpp, %.o, $(SOURCES))
TESTS = $(addprefix test_,$(SOURCES))
TESTSEXE = $(addsuffix .exe,$(TESTS))
TESTSEXEDIR = $(addprefix bin/,$(TESTSEXE))
COVER = $(addsuffix .gcov,$(SOURCES))

SOURCEDIR = $(addprefix $(MYDIR)src/,$(SOURCES))
OBJDIR = $(addprefix build/,$(OBJECTS))
TSTDIR = $(addprefix tests/test_,$(SOURCES))
TGTDIR = $(BIN)/$(TARGET)

all: $(TGTDIR)

$(OBJDIR): build/%.o : src/%.cpp
	@echo ""
	@echo OBJETO: $@
	$(shell mkdir -p build)
	#@mkdir -p ../build
	$(CC) $(INC) $(CFLAGS) -c $(patsubst build/%.o,src/%.cpp,$@) -o $@

$(TGTDIR): $(OBJDIR)
	@echo ""
	@echo COMPILANDO MAIN
	@mkdir -p bin
	$(CC) $(INC) $(CFLAGS) $(OBJDIR) program/$(TARGET).cpp -o $(TGTDIR)


tester: $(TESTS)
$(TESTS): tests/test_%.o : tests/test_%.cpp
	$(shell mkdir -p tests)
	@echo ""
	@echo TESTE: $@
	$(CC) $(INC) $(T_CFLAGS) tests/$@ $(OBJDIR) -o bin/$@.exe
	bin/$@.exe
	$(RM) test_*.gcno

comp: $(TGTDIR)
	$(CC) $(INC) $(CFLAGS) $(OBJDIR) program/$(TARGET).cpp -o $(TGTDIR)
	@bin/main.exe
	$(RM) main.gcno
	$(RM) main.gcda

run:
	@bin/main.exe
	$(RM) main.gcno
	$(RM) main.gcda

debug:
	@gdb $(BIN)/main.exe

coverage: $(COVER)
$(COVER): src/%.gcov : src/%.cpp
	@echo ""
	@echo POSIÇAO: $@
	@gcov src/$(patsubst %.cpp.gcov,%.cpp,$@) -l -p -o build
	
	$(RM) src#$(patsubst %.cpp.gcov,%.cpp,$@)#*.gcov
	$(RM) #usr#lib*.gcov
	$(RM) *.gcda *.gcno

clean:
	$(RM) -r build/* coverage/* *.gcda *.gcno *.gcov *.exe *.o bin/*

.PHONY: clean coverage
