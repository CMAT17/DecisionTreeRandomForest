#include "datasetitem.h"

/* Default Constructor */
DataSetItem::DataSetItem()
{
	_label = 0;
}

/* Construct from values */

DataSetItem::DataSetItem(int label, std::vector<std::map<int, int>> dim_maps)
{
	_label = label;
	_dim_maps = dim_maps;
}

int DataSetItem::get_label()
{
	return _label;
}

std::vector<std::map<int,int>> DataSetItem::get_dim_maps()
{
	return _dim_maps;
}

