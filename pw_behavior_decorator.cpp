#include "pw_behavior_decorator.h"
#include "pw_behavior_board.h"
#include <Windows.h>
#include <iostream>

namespace pwngs
{

	BehaviorDecoratorWait::BehaviorDecoratorWait( int64 time )
		: m_nWaitTime(time)
	{
	}

	EBehaviorResult BehaviorDecoratorWait::ExecutionBegan( BehaviorEnvriment& env )
	{
		m_nStartTime = GetTickCount64();
		return BehaviorSequence::ExecutionBegan(env);
	}

	EBehaviorResult BehaviorDecoratorWait::Execute( BehaviorEnvriment& env )
	{
		if(m_nStartTime != 0)
		{
			if((GetTickCount64() - m_nStartTime) < m_nWaitTime)
				return BEHAVIOR_RESULT_RUNNING;
			m_nStartTime = 0;
		}
		
		return BehaviorSequence::Execute(env);
	}

	EBehaviorResult BehaviorDecoratorRepeatAlways::Evaluation( BehaviorEnvriment& env )
	{
		EBehaviorResult result = BehaviorSequence::Evaluation(env);
		if( result == BEHAVIOR_RESULT_FINISHED)
		{
			result = this->Evaluation(env);
		}
		return result;
	}

	EBehaviorResult BehaviorDecoratorNot::Evaluation( BehaviorEnvriment& env )
	{
		assert(m_vtNodes.size() == 1);

		BehaviorNode* node = m_vtNodes[0];
		assert(node);

		EBehaviorResult result = node->Evaluation(env);
		switch(result)
		{
		case BEHAVIOR_RESULT_FAILURE:
			result = BEHAVIOR_RESULT_SUCCESSFUL;
			break;
		case BEHAVIOR_RESULT_SUCCESSFUL:
			result = BEHAVIOR_RESULT_FAILURE;
			break;
		default:
			assert(false && "invalid result");
			break;
		}
		return result;
	}

	EBehaviorResult BehaviorDecoratorIf::Evaluation( BehaviorEnvriment& env )
	{
		assert(m_vtNodes.size() == 2);

		BehaviorNode* nodeCondition = m_vtNodes[0];
		assert(nodeCondition);

		BehaviorNode* nodeBody = m_vtNodes[1];
		assert(nodeBody);

		if( nodeCondition->Evaluation(env) == BEHAVIOR_RESULT_SUCCESSFUL)
			return nodeBody->Evaluation(env);
		return BEHAVIOR_RESULT_FAILURE;
	}

	EBehaviorResult BehaviorDecoratorWhile::Evaluation( BehaviorEnvriment& env )
	{
		assert(m_vtNodes.size() == 2);

		BehaviorNode* nodeCondition = m_vtNodes[0];
		assert(nodeCondition);

		BehaviorNode* nodeBody = m_vtNodes[1];
		assert(nodeBody);

		while( nodeCondition->Evaluation(env) == BEHAVIOR_RESULT_SUCCESSFUL)
			nodeBody->Evaluation(env);
		return BEHAVIOR_RESULT_SUCCESSFUL;
	}
}