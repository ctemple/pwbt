// test_behavior_tree.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "pw_behavior_tree.h"
#include "pw_behavior_board.h"
#include "pw_behavior_node_selector.h"
#include "pw_behavior_node_decorator.h"
#include "pw_behavior_node_sequence.h"
#include "pw_behavior_node_condition.h"
#include "pw_behavior_node_action.h"
#include <iostream>
#include "pw_behavior_facade.h"
#include <time.h>

using namespace pwngs;

class TestActionNode : public pwngs::BehaviorActionNode
{
public:
	TestActionNode(const char* text)
	{
		mText = text;
	}

	virtual int Evaluation(BehaviorEnvriment& env)
	{
		std::cout << "TestActionNode Evaluation:"  << mText << std::endl;

		return BEHAVIOR_RESULT_TRUE;
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

	BehaviorNode* node = (new BehaviorSelectorNode_Random())->InsertNodes
		( 
			new TestActionNode("111"),
			new TestActionNode("222"),

			(new BehaviorDecoratorNode_Counter(varCount))->InsertNodes
			(
				new TestActionNode("333"),
				NULL
			),
			
			NULL
		);
	tree.SetStateNode(0,node);


	for(int i = 0; i < 10; ++i)
		tree.Evaluation(env);


	return 0;
}

