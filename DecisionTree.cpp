#include <iostream>
#include <algorithm>
#include <utility>
#include <cmath>

#include "datasetitem.h"
#include "file_parser.h"
#include "question.h"
#include "decision_node.h"
#include "d_tree.h"




int main(int argc, char ** argv){
    std::cout << argc;
	/* Populate training data vector */
	std::vector<DataSetItem> training_data;
	training_data = file_parser(argv[1]);		
	
	/* obtain the values possible for each category */
	std::map<int, std::vector<int> > cat_vals;
	/* obtain all possible labels */
	std::vector<int> all_labels;
    int temp_label;
	for(auto it1 = training_data.begin(); it1!=training_data.end();++it1)
	{
		temp_label = it1->get_label();
		if(std::find(all_labels.begin(), all_labels.end(),temp_label) == all_labels.end())
		{
			all_labels.push_back(temp_label);
		}
		std::map<int, int> context_dim_maps = it1->get_dim_maps();
		for (auto const& x: context_dim_maps)
		{
			/* code */
			if(cat_vals.find(x.first) != cat_vals.end())
			{
                if(std::find(cat_vals[x.first].begin(),cat_vals[x.first].end(),x.second)== cat_vals[x.first].end())
                {
                    //Specific value for category not found, append it into the vector
                    cat_vals[x.first].push_back(x.second);
                }
			}
			else
			{
				std::vector<int> temp;
				temp.push_back(x.second);
				cat_vals[x.first] = temp;
			}
		}
	}

	/* Build Decision Tree using GINI-index  */
	
    d_tree* decision_tree = new d_tree(training_data,cat_vals);
    std::cout << decision_tree->root->get_category();
	/* Populate test data vector */
	//std::vector<DataSetItem> test_data;
	//test_data = file_parser(argv[2]);

	/* Classify test set */
	

	/* Confusion matrix */
	/**
	 * First index determines row (which label it was actually). Second index determines col (which one it was predicted)
	 */
	
	std::vector<std::vector<int>> confusion_mtx(all_labels.size(), std::vector<int>(all_labels.size(),0));
	return 0;
}

