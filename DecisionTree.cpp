#include <iostream>

#include "datasetitem.h"
#include "file_parser.h"
#include "decision_tree.h"


DecisionTree train(std::vector<DataSetItem> training_set);



int main(int argc, char ** argv){
	/* Populate training data vector */
	std::vector<DataSetItem> training_data;
	training_data = file_parser(argv[1]);		
	
	/* obtain the values possilbe for each category */
	std::map<int, std::vector<int> > cat_vals;
	for(auto it1 = training_data.begin(); it!=training_data.end();++it)
	{
		std::map<int, int> context_dim_maps;
		for (auto const& x: context_dim_maps)
		{
			/* code */
			if(cat_vals.find(x.first) != cat_vals.end())
			{
				cat_vals[x.first].push_back(x.second)
			}
			else
			{
				std::vector<int> temp = x.second;
				cat_vals[x.first] = temp;
			}
		}
	}

	for(auto const& y: cat_vals)
	{
		std::cout << y.first;
		for(auto it = y.second.begin(); it != y.second.end(); ++it)
		{
			std::cout<< it;
		}
		std::cout <<"\n" 
	}
	/* Evaluate all splits with gini-index */
	

	/* Populate test data vector */
	std::vector<DataSetItem> test_data;
	test_data = file_parser(argv[2]);

	return 0;
}