#include "pw_behavior_node_condition.h"

namespace pwngs
{


	BehaviorConditionNode::BehaviorConditionNode( BehaviorVariable* lvar,BehaviorVariable* rvar,BehaviorVariableOp op )
		: m_pLVar(lvar)
		, m_pRVar(rvar)
		, m_Op(op)
	{

	}

	int BehaviorConditionNode::Evaluation( BehaviorEnvriment& env )
	{
		int result = 0;

		switch(m_Op)
		{
		case BEHAVIOR_VARIABLE_OP_NOT_EQUAL:
			result = m_pLVar->NotEqual(m_pRVar);
			break;
		case BEHAVIOR_VARIABLE_OP_EQUAL:
			result = m_pLVar->Equal(m_pRVar);
			break;
		case BEHAVIOR_VARIABLE_OP_LESS:
			result = m_pLVar->Less(m_pRVar);
			break;
		case BEHAVIOR_VARIABLE_OP_LESS_EQUAL:
			result = m_pLVar->LessOrEqual(m_pRVar);
			break;
		case BEHAVIOR_VARIABLE_OP_GREAT:
			result = m_pLVar->Great(m_pRVar);
			break;
		case BEHAVIOR_VARIABLE_OP_GREAT_EQUAL:
			result = m_pLVar->GreatOrEqual(m_pRVar);
			break;
		default:
			assert(false && "invalid oper");
			break;
		}

		if(result == 1)
			return BEHAVIOR_RESULT_TRUE;
		return BEHAVIOR_RESULT_FALSE;

	}
}