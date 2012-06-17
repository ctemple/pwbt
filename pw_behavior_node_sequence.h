#ifndef _pw_behavior_node_sequence_
#define _pw_behavior_node_sequence_

#include "pw_behavior_tree.h"

namespace pwngs
{
	class BehaviorSequenceNode : public BehaviorNode
	{

	};

	class BehaviorSequenceNode_Liner : public BehaviorSequenceNode
	{
	public:
		virtual int Evaluation(BehaviorEnvriment& env);
	};

	class BehaviorSequenceNode_Random : public BehaviorSequenceNode
	{
	public:
		virtual int Evaluation(BehaviorEnvriment& env);
	};
}

#endif // _pw_behavior_node_sequence_