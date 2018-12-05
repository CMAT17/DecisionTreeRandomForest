#ifndef DATASET_ITEM_H_
#define DATASET_ITEM_H_

#include <vector>
#include <string>
#include <map>

class DataSetItem
{
	public:
		DataSetItem();
		DataSetItem(int label, std::vector<std::map<int, int>> dim_maps);
		~DataSetItem();


	private:
		int _label;
		std::vector<std::map<int, int>> _dim_maps;
};

#endif