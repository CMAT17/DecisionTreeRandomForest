#ifndef DECISION_NODE_H_
#define DECISION_NODE_H_

#include <map>

#include "question.h"


class DecisionNode
{
	public:
		DecisionNode(Question new_question,bool leaf, std::map<int, int> counts);
		DecisionNode(Question new_question,DecisionNode* new_t_branch, DecisionNode* new_f_branch);
        int get_category();
		bool eval_question(std::pair<int,int> example);
		bool get_leaf();
		int get_prediction();
		DecisionNode* true_branch;
		DecisionNode* false_branch;
        Question _question;
        ~DecisionNode();
	private:
		bool _leaf;
		std::map<int, int> _counts; //tracks which counts of labels at leaf node -> choose majority, random for tiebreak
};

#endif 
