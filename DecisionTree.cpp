#include <iostream>
#include <algorithm>
#include <utility>
#include <cmath>

#include "datasetitem.h"
#include "file_parser.h"
#include "question.h"
#include "decision_node.h"

float gini_index(int split_cat, int split_val, std::vector<DataSetItem> training_data);

void partition( Question qsplit, std::vector<DataSetItem> input_set, std::vector<DataSetItem> & true_branch_set, std::vector<DataSetItem> & false_branch_set);

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
	for(auto const& x: cat_vals)
	{
		for (auto it = x.second.begin(); it!= x.second.end(); ++it)
		{
			std::cout << gini_index(x.first, *it, training_data) << "\n";
		}
	}
	//test partition

	std::vector<DataSetItem> true_branch;
	std::vector<DataSetItem> false_branch;
	Question testq(1,1);
	partition(testq, training_data, true_branch, false_branch);

	for (auto it = true_branch.begin(); it != true_branch.end(); ++it)
	{
		it->print_dataset_item();
	}

	for (auto it = false_branch.begin(); it!= false_branch.end(); ++it)
	{
		it->print_dataset_item();
	}
    std::cout << false_branch.size() + true_branch.size() << " " <<training_data.size();
	
	//testing 	

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

float gini_index(int cat, int val, std::vector<DataSetItem> training_data)
{
	//Number of occurences of any label for a particualar (cat:val) key,value pair 
	std::map<int, int> num_occ_label;

	//Number of occurences of any label for all other pairs involving the same category
	std::map<int, int> num_occ_other_label;

    int total_items_t = 0;
    int total_items_f = 0;
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
            total_items_t++;
		}
		else
		{
			if(num_occ_other_label.find(temp_label) == num_occ_other_label.end())
			{
				num_occ_other_label[temp_label] = 0;
			}
			num_occ_other_label[temp_label]++;
			total_items_f++;
		}

	}

	int total_items = training_data.size();
	
    float temp_val1;
	float temp_gini_index_t = 1.0;
	for(auto const& x: num_occ_label)
	{
        temp_val1= float(x.second)/float(total_items_t);
		temp_gini_index_t-= pow(temp_val1,2.0);
	}

	float temp_val2;
	float temp_gini_index_f = 1.0;
	for(auto const& x: num_occ_other_label)
	{
        temp_val2= float(x.second)/float(total_items_f);
		temp_gini_index_f-= pow(temp_val2,2.0);
	}

	float temp_gini_index = float(total_items_t)/float(total_items) * temp_gini_index_t
							+float(total_items_f)/float(total_items) * temp_gini_index_f;
	return temp_gini_index;
}

void partition(Question qsplit, std::vector<DataSetItem> input_set, std::vector<DataSetItem> & true_branch_set, std::vector<DataSetItem> & false_branch_set)
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
/*
std::pair<float, Question> find_best_split(std::vector<DataSetItem> input_set, std::map<int, std::vector<int>> cat_vals)
{
	float best_gini = 1.0;
	float gini_val;
	Question best_question;

	for(auto const & x: cat_vals)
	{
		for(auto it = x.second.begin(); it != x.second.end(); ++it)
		{
			Question cand_q (x.first, *it);
			gini_val = gini_index(x.first, *it, input_set);

			if gini_val <= 
		}
	}	
}
*/
