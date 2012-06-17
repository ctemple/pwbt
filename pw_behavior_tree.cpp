#include "pw_behavior_tree.h"
#include <stdarg.h>


namespace pwngs
{
	BehaviorNode::BehaviorNode()
		: m_pParent(NULL)
		, m_pPreCondition(NULL)
		, m_nStatus(BEHAVIOR_STATUS_READY)
	{		
	}

	BehaviorNode::~BehaviorNode()
	{
		for(CollectionNodesT::iterator iter = m_vtNodes.begin(); iter != m_vtNodes.end(); ++iter)	
			delete (*iter);
		m_vtNodes.clear();

		if(m_pPreCondition != NULL)
		{
			delete m_pPreCondition;
			m_pPreCondition = NULL;
		}
	}

	BehaviorNode* BehaviorNode::Insert( BehaviorNode* node,size_t pos /*= std::string::npos*/ )
	{
		if(pos == std::string::npos)
			m_vtNodes.push_back(node);
		else
			m_vtNodes.insert(m_vtNodes.begin() + pos,node);

		node->m_pParent = this;

		return this;
	}

	BehaviorNode* BehaviorNode::Remove( BehaviorNode* node )
	{
		CollectionNodesT::iterator iter = std::remove(m_vtNodes.begin(),m_vtNodes.end(),node);
		if(iter == m_vtNodes.end())
			return this;

		delete (*iter);
		m_vtNodes.erase(iter);
		return this;
	}


	BehaviorNode* BehaviorNode::GetPreCondition()
	{
		return m_pPreCondition;
	}

	int BehaviorNode::SetPreCondition( BehaviorNode* node )
	{
		if(m_pPreCondition != NULL && m_pPreCondition != node)
			delete m_pPreCondition;
		m_pPreCondition = node;
		return 0;
	}

	EBehaviorResult BehaviorNode::EvaluationPreCondition( BehaviorEnvriment& env )
	{
		if(m_pPreCondition != NULL)
			return m_pPreCondition->Evaluation(env);
		return BEHAVIOR_RESULT_SUCCESSFUL;
	}

	EBehaviorResult BehaviorNode::Evaluation( BehaviorEnvriment& env )
	{
		EBehaviorResult result = BEHAVIOR_RESULT_FAILURE;

		switch(m_nStatus)
		{
		case BEHAVIOR_STATUS_READY:
			{
				if(EvaluationPreCondition(env) == BEHAVIOR_RESULT_SUCCESSFUL)
				{
					result = ExecutionBegan(env);
				}
			}
			break;
		case BEHAVIOR_STATUS_RUNNING:
			{
				result = Execute(env);
				if(result == BEHAVIOR_RESULT_FINISHED)
				{
					ExecutionEnded(env);
				}
			}
			break;
		}
		return result;
	}

	BehaviorNode* BehaviorNode::InsertNodes( BehaviorNode* node,... )
	{
		va_list vl;
		va_start(vl,node);

		while(node != NULL)
		{
			Insert(node);
			node = va_arg(vl,BehaviorNode*);
		}
		va_end(vl);

		return this;
	}

	EBehaviorResult BehaviorNode::ExecutionBegan( BehaviorEnvriment& env )
	{
		m_nStatus = BEHAVIOR_STATUS_RUNNING;

		return BEHAVIOR_RESULT_RUNNING;
	}

	EBehaviorResult BehaviorNode::Execute(BehaviorEnvriment& env)
	{
		return BEHAVIOR_RESULT_FINISHED;
	}

	EBehaviorResult BehaviorNode::ExecutionEnded( BehaviorEnvriment& env )
	{
		m_nStatus = BEHAVIOR_STATUS_READY;
		return BEHAVIOR_RESULT_SUCCESSFUL;
	}
	// ----------------------------------------------------------------------------

	BehaviorTree::BehaviorTree(size_t numberOfStates)
		: m_nCurrentState(0)
	{
		m_vtNodes.resize(numberOfStates);
	}

	EBehaviorResult BehaviorTree::Evaluation( BehaviorEnvriment& env )
	{
		BehaviorNode* node = m_vtNodes[m_nCurrentState];
		if( node != NULL)
			return node->Evaluation(env);
		return BEHAVIOR_RESULT_FAILURE;
	}
}