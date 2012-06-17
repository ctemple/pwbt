#include "pw_behavior_sequence.h"

namespace pwngs
{
	EBehaviorResult BehaviorSequence::ExecutionBegan( BehaviorEnvriment& env )
	{
		m_nCurrentNode = 0;
		return BehaviorNode::ExecutionBegan(env);
	}

	EBehaviorResult BehaviorSequence::Execute(BehaviorEnvriment& env)
	{
		if(m_nCurrentNode >= m_vtNodes.size())
			return BEHAVIOR_RESULT_FINISHED;

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
					result = BEHAVIOR_RESULT_RUNNING;
			}
			break;
		}
		return result;
	}

	EBehaviorResult BehaviorSequence::ExecutionEnded( BehaviorEnvriment& env )
	{
		m_nCurrentNode = std::string::npos;
		return BehaviorNode::ExecutionEnded(env);
	}
}