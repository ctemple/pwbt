#ifndef _pw_behavior_node_
#define _pw_behavior_node_

#include "pw_behavior_tree.h"

namespace pwngs
{
	class BehaviorSelectorNode : public BehaviorNode
	{
	};

	class BehaviorSelectorNode_Liner : public BehaviorSelectorNode
	{
	public:
		virtual int Evaluation(BehaviorEnvriment& env);
	};


	class BehaviorSelectorNode_Random: public BehaviorSelectorNode
	{
	public:
		virtual int Evaluation(BehaviorEnvriment& env);
	};


	/*
	

	class BehaviorParallelNode : public BehaviorNode
	{

	};

	class BehaviorDecoratorNode : public BehaviorNode
	{

	};

	class BehaviorConditionNode : public BehaviorNode
	{

	};
	*/
}

#endif // _pw_behavior_node_