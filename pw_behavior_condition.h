#ifndef _pw_behavior_node_condition_
#define _pw_behavior_node_condition_

#include "pw_behavior_tree.h"
#include "pw_behavior_board.h"

namespace pwngs
{
	class BehaviorCondition : public BehaviorNode
	{
	public:
		virtual EBehaviorResult Evaluation(BehaviorEnvriment& env);
	};
}

#endif // _pw_behavior_node_condition_