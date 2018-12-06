#include <iostream>

#include "datasetitem.h"
#include "file_parser.h"

int main(int argc, char ** argv){
	std::vector<DataSetItem> v;
	v = file_parser(argv[0]);
	for (auto it = v.begin(); it!= v.end(); ++it)
	{
		std::cout << it->get_label << it->get_dim_maps;	
	}
	return 0;
}