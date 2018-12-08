#ifndef DATASET_ITEM_H_
#define DATASET_ITEM_H_

#include <vector>
#include <map>

class DataSetItem
{
	public:
		DataSetItem();
		DataSetItem(int label, std::map<int, int> dim_maps);
		int get_label();
		std::map<int, int>  get_dim_maps();
	private:
		int _label;
		std::map<int, int> _dim_maps;
};

#endif
