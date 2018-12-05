.DEFAULT_GOAL := all

TREE_EXE = DecisionTree
ENSEM_EXE = RandomForest

OBJS_SHARED = datasetitem.o file_parser.o
OBJS_TREE = DecisionTree.o
OBJS_ENSEM = RandomForest.o

CXX = g++
CFLAGS = g++

WARNINGs = -pedantic -Wall -Werror -Wfatal-errors -Wextra -Wno-unused-parameter -Wno-unused-variable
CXXFLAGS = -std=c++1y -stdlib=libc++ -g -O0 $(WARNINGS) -MMD -MP -c -M
LDFLAGS = -std=c++1y -stdlib=libc++

all: $(TREE_EXE)

datasetitem.o: datasetitem.cpp datasetitem.h
	$(CXX) $(CXXFLAGS) $< -o $@ 

file_parser.o: file_parser.cpp datasetitem.h file_parser.h
	$(CXX) $(CXXFLAGS) $< -o $@

DecisionTree.o: DecisionTree.cpp datasetitem.h file_parser.h

$(TREE_EXE): $(OBJS_SHARED) $(OBJS_TREE)
	$(LD) $^ $(LDFLAGS) -o $@  

clean:
	rm -fr $(TREE_EXE) $(OBJS_SHARED) $(OBJS_TREE) 

.PHONY: all clean