#include "decision_node.h"

DecisionNode::DecisionNode(Question new_question, bool leaf = false)
{
	_leaf = leaf;
	_question = new_question;
}

bool DecisionNode::eval_question(std::pair<int,int> example)
{
	return _question.match(example);
}

int DecisionNode::get_category()
{
	return _question.get_category();
}
