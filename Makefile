.DEFAULT_GOAL := all

TREE_EXE = DecisionTree
ENSEM_EXE = RandomForest

OBJS_SHARED = datasetitem.o file_parser.o question.o decision_node.o decision_node.o d_tree.o
OBJS_TREE = DecisionTree.o
OBJS_ENSEM = RandomForest.o

CXX = g++
LD = g++

WARNINGS = -pedantic -Wall -Werror -Wfatal-errors -Wextra -Wunused-parameter -Wunused-variable
CXXFLAGS = -std=c++0x -g -O0 $(WARNINGS)  -c -ggdb3
LDFLAGS = -std=c++0x 

all: $(TREE_EXE) $(ENSEM_EXE)

d_tree.o: d_tree.cpp d_tree.h
	$(CXX) $(CXXFLAGS) $< -o $@

decision_node.o : decision_node.cpp decision_node.h
	$(CXX) $(CXXFLAGS) $< -o $@

question.o: question.cpp question.h
	$(CXX) $(CXXFLAGS) $< -o $@ 

datasetitem.o: datasetitem.cpp datasetitem.h
	$(CXX) $(CXXFLAGS) $< -o $@ 

file_parser.o: file_parser.cpp datasetitem.h file_parser.h
	$(CXX) $(CXXFLAGS) $< -o $@

DecisionTree.o: DecisionTree.cpp datasetitem.h file_parser.h
	$(CXX) $(CXXFLAGS) $< -o $@

$(OBJS_ENSEM): RandomForest.cpp datasetitem.h file_parser.h
	$(CXX) $(CXXFLAGS) $< -o $@

$(TREE_EXE): $(OBJS_SHARED) $(OBJS_TREE)
	$(LD) $^ $(LDFLAGS) -o $@  

$(ENSEM_EXE): $(OBJS_SHARED) $(OBJS_ENSEM)

clean:
	rm -fr *.o DecisionTree

.PHONY: all clean
