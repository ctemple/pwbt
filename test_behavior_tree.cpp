// test_behavior_tree.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <Windows.h>
#include "pw_behavior_tree.h"
#include "pw_behavior_board.h"
#include "pw_behavior_selector.h"
#include "pw_behavior_decorator.h"
#include "pw_behavior_sequence.h"
#include "pw_behavior_condition.h"
#include "pw_behavior_action.h"
#include <iostream>
#include <time.h>

using namespace pwngs;

class TestActionNode : public pwngs::BehaviorAction
{
public:
	TestActionNode(const char* text)
	{
		mText = text;
	}

	virtual EBehaviorResult Execute(BehaviorEnvriment& env)
	{
		std::cout << "TestActionNode Evaluation:"  << mText << std::endl;

		return BEHAVIOR_RESULT_FINISHED;
	}
private:
	std::string mText;
};

int _tmain(int argc, _TCHAR* argv[])
{

	BehaviorBoard board;
	BehaviorCharacter main;
	BehaviorEnvriment env;
	BehaviorTree tree;

	env.board = &board;
	env.main = &main;

	int count = 1;

	BehaviorVariable* v1 = new BehaviorVariableConst<double>(3221.121213f);
	BehaviorVariable* v2 = new BehaviorVariableConst<double>(3221.121213f);

	assert(v1->Equal(v2));

	delete v1;
	delete v2;

	// env.board->AddVariable("count",new BehaviorVariableConst<int32>(10));
	BehaviorVariable* varCount = env.board->AddVariable("count",new BehaviorVariablePointer<int32>(&count));

	srand(time(NULL));

	BehaviorNode* node = (new BehaviorDecoratorRepeatAlways())->InsertNodes
		( 
			(new BehaviorDecoratorIf())->InsertNodes
			(
				(new BehaviorDecoratorNot())->InsertNodes
				(
					(new BehaviorCondition()),
					NULL
				),
				new TestActionNode("began"),
				NULL
			),
			

			(new BehaviorDecoratorWait(3000))->InsertNodes
			(
				new TestActionNode("action"),
				NULL
			),
			
			new TestActionNode("ended"),
			NULL
		);
	tree.SetStateNode(0,node);


	int result = tree.Evaluation(env);
	while(result == BEHAVIOR_RESULT_RUNNING)
		result = tree.Evaluation(env);


	return 0;
}

