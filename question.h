#ifndef QUESTION_H_
#define QUESTION_H_

#include <utility>

class Question
{
	public:
		Question();	
		Question(int category, int value);
		/* Check if value matches the question's value */
		int get_category();
		bool match(std::pair<int,int> example);
		~Question();
	private:
		int _category, _value;
};

#endif