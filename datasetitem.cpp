#include <fstream>
#include <string>
#include <iterator>
#include <algorithm>
#include <sstream>

/* Construct from values */

DataSetItem::DataSetItem(int label, std::vector<std::map<int, int>> dim_maps)
{
	_label = label;
	_dim_maps = dim_maps;
}

/* Copy Constructor */ //Is this needed?


/* Move Constructor */ //Is this needed?

