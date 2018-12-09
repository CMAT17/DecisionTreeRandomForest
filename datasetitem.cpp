#include "datasetitem.h"
#include <iostream>

/* Default Constructor */
DataSetItem::DataSetItem()
{
	_label = 0;
}

/* Construct from values */

DataSetItem::DataSetItem(int label, std::map<int, int> dim_maps)
{
	_label = label;
	_dim_maps = dim_maps;
}

int DataSetItem::get_label()
{
	return _label;
}

std::map<int,int> DataSetItem::get_dim_maps()
{
	return _dim_maps;
}

void DataSetItem::print_dataset_item()
{
	std::cout << "label: " <<_label <<"\n";
	for(auto const & x: _dim_maps)
	{
		std::cout << x.first <<":" <<x.second << " ";
	}
	std::cout << "\n";
}