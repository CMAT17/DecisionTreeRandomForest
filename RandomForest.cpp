#include <iostream>
#include <algorithm>
#include <utility>
#include <cmath>
#include <cstdlib>
#include <ctime>

#include "datasetitem.h"
#include "file_parser.h"
#include "question.h"
#include "decision_node.h"
#include "d_tree.h"



int main(int argc, char ** argv){
    if (argc<2)
    {
    	return -1;
    }
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
	int num_cat = cat_vals.size();

	int cat_per_tree = num_cat/4 +2;

	std::map<int, std::vector<int>> cat_vals_1;	
	std::map<int, std::vector<int>> cat_vals_2;	
	std::map<int, std::vector<int>> cat_vals_3;	
	std::map<int, std::vector<int>> cat_vals_4;
	int output_rand;
	for(int i=0; i<cat_per_tree; ++i)
	{
		output_rand =  rand()%(127);
		if(cat_vals_1.find(output_rand)!= cat_vals_1.end())
			cat_vals_1[output_rand] = cat_vals[output_rand];
		output_rand =  rand()%(127);
		if(cat_vals_2.find(output_rand)!= cat_vals_2.end())
			cat_vals_1[output_rand] = cat_vals[output_rand];
		output_rand =  rand()%(127);
		if(cat_vals_3.find(output_rand)!= cat_vals_3.end())
			cat_vals_3[output_rand] = cat_vals[output_rand];
		output_rand =  rand()%(127);
		if(cat_vals_4.find(output_rand)!= cat_vals_4.end())
			cat_vals_4[output_rand] = cat_vals[output_rand];
	}

    d_tree rand_tree1(training_data,cat_vals_1, all_labels);
    d_tree rand_tree2(training_data,cat_vals_2, all_labels);
    d_tree rand_tree3(training_data,cat_vals_3, all_labels);
    d_tree rand_tree4(training_data,cat_vals_4, all_labels);

/* Populate test data vector */
	std::vector<DataSetItem> test_data;
	test_data = file_parser(argv[2]);
	
	int temp;
	std::vector<std::vector<int>> confusion_mtx(all_labels.size(),std::vector<int>(all_labels.size(),0));
	/* Classify test set */
	for(auto it = test_data.begin(); it!= test_data.end(); ++it)
	{
		std::map<int, int> label_map;
		temp = rand_tree1.classify_single(*it);
		if(temp < all_labels.size())
		{
			if(label_map.find(temp)==label_map.end())
				label_map[temp] = 0;
			label_map[temp]++;
		}
		temp = rand_tree1.classify_single(*it);
		if(temp < all_labels.size())
		{
			if(label_map.find(temp)==label_map.end())
				label_map[temp] = 0;
			label_map[temp]++;
		}
		temp = rand_tree1.classify_single(*it);
		if(temp < all_labels.size())
		{
			if(label_map.find(temp)==label_map.end())
				label_map[temp] = 0;
			label_map[temp]++;
		}
		temp = rand_tree1.classify_single(*it);
		if(temp < all_labels.size())
		{
			if(label_map.find(temp)==label_map.end())
				label_map[temp] = 0;
			label_map[temp]++;
		}
		int max=0;
		int mode = -1;
		for (auto const & x: label_map)
		{
			if(x.second>=max)
			{
				max = x.second;
				mode = x.first;
			}
		}
		confusion_mtx[it->get_label][mode]++;
	}

	/* Confusion matrix */
	/**
	 * First index determines row (which label it was actually). Second index determines col (which one it was predicted)
	 */
	for(auto const & inner: confusion_mtx)
	{
		for(auto const & item: inner)
		{
			std::cout << item << " ";
		}
		std::cout << std::endl;
	}

	return 0;
}

