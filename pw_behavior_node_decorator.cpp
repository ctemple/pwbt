#include "pw_behavior_node_decorator.h"
#include "pw_behavior_board.h"

namespace pwngs
{
	BehaviorDecoratorNode::BehaviorDecoratorNode()
	{

	}


	int BehaviorDecoratorNode_Not::Evaluation( BehaviorEnvriment& env )
	{
		assert(m_vtNodes.size() == 1);
		
		BehaviorNode* node = *m_vtNodes.begin();

		int result = node->EvaluationPreCondition(env);
		if( result != BEHAVIOR_RESULT_TRUE)
			return BEHAVIOR_RESULT_IGNORE;

		result = node->Evaluation(env);
		switch(result)
		{
		case BEHAVIOR_RESULT_TRUE:
			return BEHAVIOR_RESULT_FALSE;
		case BEHAVIOR_RESULT_FALSE:
			return BEHAVIOR_RESULT_TRUE;
		case BEHAVIOR_RESULT_IGNORE:
			return BEHAVIOR_RESULT_IGNORE;
		default:
			assert(false && "invalid result");
			break;
		}
		return BEHAVIOR_RESULT_IGNORE;
	}

	int BehaviorDecoratorNode_FailUtil::Evaluation( BehaviorEnvriment& env )
	{
		assert(m_vtNodes.size() == 1);

		BehaviorNode* node = *m_vtNodes.begin();

		int result = BEHAVIOR_RESULT_TRUE;
		while(result == BEHAVIOR_RESULT_TRUE)
		{
			result = node->EvaluationPreCondition(env);
			if( result == BEHAVIOR_RESULT_TRUE)
				result = node->Evaluation(env);
		}
		return BEHAVIOR_RESULT_TRUE;
	}


	BehaviorDecoratorNode_Counter::BehaviorDecoratorNode_Counter(BehaviorVariable* variable )
		: m_pVariable(variable)
	{

	}


	int BehaviorDecoratorNode_Counter::Evaluation( BehaviorEnvriment& env )
	{
		assert(m_pVariable != NULL);
		assert(m_vtNodes.size() == 1);

		int result = -1;

		BehaviorNode* node = *m_vtNodes.begin();
		
		for(int i = 0; i < m_pVariable->AsInt32(); ++i)
		{
			result = node->EvaluationPreCondition(env);
			if( result != BEHAVIOR_RESULT_TRUE)
				break;

			result = node->Evaluation(env);
			if(result == BEHAVIOR_RESULT_FALSE)
				break;	
		}

		return result;
	}

	BehaviorDecoratorNode_Time::BehaviorDecoratorNode_Time( BehaviorVariable* variable )
		: m_pVariable(variable)
		, m_nLastEvaluationTime(0)
	{

	}

	int BehaviorDecoratorNode_Time::Evaluation( BehaviorEnvriment& env )
	{
		if(m_nLastEvaluationTime != 0 && (env.currentTimeMS - m_nLastEvaluationTime) < m_pVariable->AsInt64())
			return BEHAVIOR_RESULT_IGNORE;

		assert(m_pVariable != NULL);
		assert(m_vtNodes.size() == 1);

		int result = -1;

		BehaviorNode* node = *m_vtNodes.begin();

		result = node->EvaluationPreCondition(env);
		if( result != BEHAVIOR_RESULT_TRUE)
			return BEHAVIOR_RESULT_IGNORE;

		return node->Evaluation(env);
	}
}