#include <iostream>

#include "datasetitem.h"
#include "file_parser.h"


int main(int argc, char ** argv){
	std::vector<DataSetItem> v;
	v = file_parser(argv[0]);
	std::cout << v;		
	return 0;
}