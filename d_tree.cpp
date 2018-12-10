#include "d_tree"

d_tree::d_tree(DecisionNode* root)
{
	this.root = root;
}

d_tree::~d_tree()
{
	if(root!= NULL)
	{
		delete root;
	}
}