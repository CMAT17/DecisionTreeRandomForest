#include <iostream>
#include <algorithm>
#include <utility>
#include <cmath>

#include "datasetitem.h"
#include "file_parser.h"
#include "question.h"
#include "decision_node.h"

int gini_index(int split_cat, int split_val, std::vector<DataSetItem> training_data);

void partition( Question qsplit, std::vector<DataSetItem> input_set, std::vector<DataSetItem> & true_branch_set, std::vector<DataSetItem> false_branch_set);

//std::pair<float, Question> find_best_split(std::vector<DataSetItem> input_set, std::map<int, std::vector<int>> cat_vals);

//DecisionNode build_tree();


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

	//test gini_index

	//test 

	/* Build Decision Tree using GINI-index  */
			


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

int gini_index(int cat, int val, std::vector<DataSetItem> training_data)
{
	//Number of occurences of any label for a particualar (cat:val) key,value pair 
	std::map<int, int> num_occ_label;

	for(auto it = training_data.begin(); it!= training_data.end(); ++it)
	{
		DataSetItem temp_item = *it;
		int temp_label = temp_item.get_label();
		std::map<int, int> temp_dim_map = temp_item.get_dim_maps();
		
		if(temp_dim_map[cat] == val)
		{
			if(num_occ_label.find(temp_label) != num_occ_label.end())
			{
				//Already an entry for the label, increment the value
				num_occ_label[temp_label]++;
			}
			else
			{
				num_occ_label[temp_label]=1;
			}
		}
	}
	int total_items = training_data.size();
	
    float temp_val;
	float temp_gini_index = 1.0;
	for(auto const& x: num_occ_label)
	{
        temp_val= float(x.second)/float(total_items);
		temp_gini_index-= pow(temp_val,2.0);
	}
	return temp_gini_index;
}

void partition(Question qsplit, std::vector<DataSetItem> input_set, std::vector<DataSetItem> & true_branch_set, std::vector<DataSetItem> false_branch_set)
{
	int category = qsplit.get_category();
	std::pair<int, int> item_pair;
	std::map<int, int> item_map;
	for(auto it = input_set.begin(); it != input_set.end(); ++it)
	{
		item_map = it->get_dim_maps();
		if (item_map.find(category)== item_map.end())
		{
			std::cout<< "MAP DOES NOT HAVE CATEGORY";
			break;
		}
		item_pair = std::pair<int, int> (category, item_map[category]);
		if(qsplit.match(item_pair))
		{
			true_branch_set.push_back(*it);
		}
		else
		{
			false_branch_set.push_back(*it);
		}
	}
}
