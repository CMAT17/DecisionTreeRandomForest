#include "decision_node.h"

DecisionNode::DecisionNode(Question new_question, bool leaf = false)
{
	_leaf = leaf;
	_question = new_question;
	true_branch, false_branch = NULL;
}

DecisionNode::DecisionNode(Question new_question,DecisionNode* new_t_branch, Decision* new_f_branch)
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

DecisionNode::~DecisionNode()
{
	delete true_branch;
	delete false_branch;	
}