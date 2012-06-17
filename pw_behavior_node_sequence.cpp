#include "pw_behavior_node_sequence.h"

namespace pwngs
{
	

	int BehaviorSequenceNode_Liner::Evaluation( BehaviorEnvriment& env )
	{
		for(CollectionNodesT::iterator iter = m_vtNodes.begin(); iter != m_vtNodes.end(); ++iter)
		{
			BehaviorNode* node = *iter;
			if(node->EvaluationPreCondition(env) != BEHAVIOR_RESULT_TRUE)
				continue;

			int result = node->Evaluation(env);
			if( result == BEHAVIOR_RESULT_FALSE)
				return BEHAVIOR_RESULT_FALSE;
		}

		return BEHAVIOR_RESULT_TRUE;
	}

	int BehaviorSequenceNode_Random::Evaluation( BehaviorEnvriment& env )
	{
		std::random_shuffle(m_vtNodes.begin(),m_vtNodes.end());

		for(CollectionNodesT::iterator iter = m_vtNodes.begin(); iter != m_vtNodes.end(); ++iter)
		{
			BehaviorNode* node = *iter;
			if(node->EvaluationPreCondition(env) != BEHAVIOR_RESULT_TRUE)
				continue;

			int result = node->Evaluation(env);
			if( result == BEHAVIOR_RESULT_FALSE)
				return BEHAVIOR_RESULT_FALSE;
		}

		return BEHAVIOR_RESULT_TRUE;
	}
}