#include "question.h"

Question::Question(int category, int value)
{
	_category = category;
	_value = value;	
}

Question::~Question()
{
	/* DO NOTHING. Nothing dynamically allocated */
}

bool Question::match(std::pair<int,int> example)
{
	if(example.first!=_category)
	{
		return false;
	}
	else
	{
		return example.second == _value;
	}
}