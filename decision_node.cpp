#include "decision_node.h"

DecisionNode::DecisionNode(Question new_question, bool leaf, std::map<int, int> counts)
{
	_leaf = leaf;
	_question = new_question;
	_counts = counts;
	true_branch = NULL; 
	false_branch = NULL;
}

DecisionNode::DecisionNode(Question new_question,DecisionNode* new_t_branch, DecisionNode* new_f_branch)
{
	_leaf = false;
	_question = new_question;
	true_branch = new_t_branch;
	false_branch = new_f_branch;
}

bool DecisionNode::eval_question(std::pair<int,int> example)
{
	return _question.match(example);
}

int DecisionNode::get_category()
{
	return _question.get_category();
}

int DecisionNode::get_prediction()
{
	int max_count = 0;
	int max_label = -1;
	for(auto const & x: _counts)
	{
		if(x.second >= max_count)
		{
			max_count = x.second;
			max_label = x.first;
		}
	}
	return max_label;
}

DecisionNode::~DecisionNode()
{
    if(true_branch)
    {
	    delete true_branch;
	}
    if(false_branch)
    {
        delete false_branch;
    }	
}

bool DecisionNode::get_leaf()
{
	return _leaf;
}