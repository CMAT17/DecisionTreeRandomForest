#ifndef DECISION_NODE_H_
#define DECISION_NODE_H_

#include <map>

#include "question.h"


class DecisionNode
{
	public:
		DecisionNode(Question new_question,bool leaf);
		bool eval_question(std::pair<int,int> example);
		DecisionNode * true_branch;
		DecisionNode * false_branch;
	private:
		Question _question;
		bool _leaf;
		std::map<int, int> counts; //tracks which counts of labels at leaf node -> choose majority, random for tiebreak
};

#endif 
