CC := g++
MYDIR := $(dir $(realpath $(firstword $(MAKEFILE_LIST))))
SRCDIR := src
BIN := bin
BUILDDIR := build
TARGET := main

SRCEXT := cpp
CFLAGS := --coverage -g -Wall -Wno-unknown-pragmas -fno-strict-overflow -O3 -std=c++11
T_CFLAGS := --coverage -g -Wall -O3
INC := -I third-party -I $(MYDIR)


MODULES = lista curso candidato
SOURCES = $(addsuffix .cpp,$(MODULES))
OBJECTS = $(patsubst %.cpp, %.o, $(SOURCES))
TESTS = $(addprefix test_,$(SOURCES))
TESTSEXE = $(addsuffix .exe,$(TESTS))
TESTSEXEDIR = $(addprefix bin/,$(TESTSEXE))
COVER = $(addsuffix .gcov,$(SOURCES))

SOURCEDIR = $(addprefix $(MYDIR),$(SOURCES))
OBJDIR = $(addprefix build/,$(OBJECTS))
TSTDIR = $(addprefix tests/test_,$(SOURCES))
TGTDIR = $(TARGET)

all: $(TGTDIR)

$(OBJDIR): build/%.o : %.cpp
	@echo ""
	@echo OBJETO: $@
	$(shell mkdir -p build)
	#@mkdir -p ../build
	$(CC) $(INC) $(CFLAGS) -c $(patsubst build/%.o,%.cpp,$@) -o $@

$(TGTDIR): $(OBJDIR)
	@echo ""
	@echo COMPILANDO MAIN
	$(CC) $(INC) $(CFLAGS) $(OBJDIR) $(TARGET).cpp -o $(TGTDIR)
	$(RM) $(MYDIR)/main.gcno


tester: $(TESTS)
$(TESTS): tests/test_%.o : tests/test_%.cpp
	$(shell mkdir -p tests)
	@echo ""
	@echo TESTE: $@
	$(CC) $(INC) $(T_CFLAGS) tests/$@ $(OBJDIR) -o tests/$@.exe
	tests/$@.exe
	$(RM) $(MYDIR)/test_*.gcno $(MYDIR)/test_*.gcda

comp: $(TGTDIR)
	$(CC) $(INC) $(CFLAGS) $(OBJDIR) $(TARGET).cpp -o $(TGTDIR)
	#@bin/main.exe
	$(RM) $(MYDIR)/main.gcno
	$(RM) $(MYDIR)/main.gcda

run:
	@./main
	$(RM) $(MYDIR)/main.gcno
	$(RM) $(MYDIR)/main.gcda

debug:
	@gdb $(MYDIR)/main

coverage: $(COVER)
$(COVER): %.gcov : %.cpp
	@echo ""
	@echo POSIÇAO: $@
	@gcov $(patsubst %.cpp.gcov,%.cpp,$@) -l -p -o build
	
	$(RM) #$(patsubst %.cpp.gcov,%.cpp,$@)#*.gcov
	$(RM) #usr#lib*.gcov
	$(RM) *.gcda *.gcno

clean:
	$(RM) -r build/* coverage/* *.gcda *.gcno *.gcov *.exe *.o bin/* tests/*.exe main

.PHONY: clean coverage
