#ifndef DECISION_TREE_H_
#define DECISION_TREE_H_
#include <cmath>

#include "decision_node.h"
#include "datasetitem.h"

class d_tree
{
	public:
		d_tree(std::vector<DataSetItem> input_set, std::map<int, std::vector<int>> cat_vals, std::vector<int> all_labels);
		void print_tree(void);
		//output k*k confusion matrix
		std::vector<std::vector<int>> classify(std::vector<DataSetItem> test_data);
		~d_tree();
	private:
		std::vector<int> _all_labels;
		DecisionNode* root;
		DecisionNode* _build_tree(std::vector<DataSetItem> input_set, std::map<int, std::vector<int>> cat_vals);
		Question _find_best_split(std::vector<DataSetItem> input_set, std::map<int, std::vector<int>> cat_vals);
		void _partition( Question qsplit, std::vector<DataSetItem> input_set, std::vector<DataSetItem> & true_branch_set, std::vector<DataSetItem> & false_branch_set);
		float _gini_index(int split_cat, int split_val, std::vector<DataSetItem> training_data);	
		void _blow_up_tree(DecisionNode* root);
		void _print_tree(DecisionNode* root);
};

#endif
