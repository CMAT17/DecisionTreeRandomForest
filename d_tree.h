#ifndef DECISION_TREE_H_
#define DECISION_TREE_H_

#include "decision_node.h"

class d_tree
{
	public:
		d_tree(DecisionNode* root);
		~d_tree();
		DecisionNode* root;
};

#endif