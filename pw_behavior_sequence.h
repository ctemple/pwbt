#ifndef _pw_behavior_node_sequence_
#define _pw_behavior_node_sequence_

#include "pw_behavior_tree.h"

namespace pwngs
{
	// 按顺序执行所有Node
	class BehaviorSequence : public BehaviorNode
	{
	protected:
		virtual EBehaviorResult ExecutionBegan(BehaviorEnvriment& env);
		virtual EBehaviorResult Execute(BehaviorEnvriment& env);
		virtual EBehaviorResult ExecutionEnded(BehaviorEnvriment& env);
	protected:
		size_t m_nCurrentNode;
	};
}
#endif // _pw_behavior_node_sequence_