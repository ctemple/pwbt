#include "pw_behavior_selector.h"

namespace pwngs
{
	EBehaviorResult BehaviorSelectorLiner::ExecutionBegan( BehaviorEnvriment& env )
	{
		if(m_vtNodes.empty())
			return BEHAVIOR_RESULT_FAILURE;
		m_nCurrentNode = 0;
		return BehaviorNode::ExecutionBegan(env);
	}

	EBehaviorResult BehaviorSelectorLiner::Execute(BehaviorEnvriment& env)
	{
		assert(m_nCurrentNode < m_vtNodes.size());

		BehaviorNode* node = m_vtNodes[m_nCurrentNode];
		assert(node);

		EBehaviorResult result = node->Evaluation(env);

		switch(result)
		{
		case BEHAVIOR_RESULT_FINISHED:
			{
				m_nCurrentNode += 1;
				if(m_nCurrentNode >= m_vtNodes.size())
					result =  BEHAVIOR_RESULT_FINISHED;
				else
					result =  BEHAVIOR_RESULT_RUNNING;
			}
			break;
		}
		return result;
	}

	EBehaviorResult BehaviorSelectorLiner::ExecutionEnded( BehaviorEnvriment& env )
	{
		m_nCurrentNode = std::string::npos;
		return BehaviorNode::ExecutionEnded(env);
	}

	// -------------------------------------------------------------------------

	EBehaviorResult BehaviorSelectorRandom::ExecutionBegan( BehaviorEnvriment& env )
	{
		EBehaviorResult result = BehaviorSelectorLiner::ExecutionBegan(env);
		if( result == BEHAVIOR_RESULT_RUNNING)
		{
			std::random_shuffle(m_vtNodes.begin(),m_vtNodes.end());
		}
		return result;
	}
}