#ifndef _pw_behavior_node_condition_
#define _pw_behavior_node_condition_

#include "pw_behavior_tree.h"
#include "pw_behavior_board.h"

namespace pwngs
{
	class BehaviorConditionNode : public BehaviorNode
	{
	public:
		BehaviorConditionNode(BehaviorVariable* lvar,BehaviorVariable* rvar,BehaviorVariableOp op);
	public:
		virtual int Evaluation(BehaviorEnvriment& env);
	protected:
		BehaviorVariable* m_pLVar;
		BehaviorVariable* m_pRVar;
		BehaviorVariableOp m_Op;
	};
}

#endif // _pw_behavior_node_condition_