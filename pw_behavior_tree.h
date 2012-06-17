#ifndef _pw_behavior_tree_
#define _pw_behavior_tree_


#include "pw_behavior_def.h"

namespace pwngs
{
	class BehaviorNode
	{
	public:
		BehaviorNode();
		virtual ~BehaviorNode();
	public:
		virtual BehaviorNode* GetPreCondition();
		virtual int SetPreCondition(BehaviorNode* node);
	public:
		BehaviorNode* InsertNodes(BehaviorNode* node,...);
	public:
		BehaviorNode* Insert(BehaviorNode* node,size_t pos = std::string::npos);
		BehaviorNode* Remove(BehaviorNode* node);
	protected:
		virtual EBehaviorResult ExecutionBegan(BehaviorEnvriment& env);
		virtual EBehaviorResult Execute(BehaviorEnvriment& env);
		virtual EBehaviorResult ExecutionEnded(BehaviorEnvriment& env);
	public:
		virtual EBehaviorResult Evaluation(BehaviorEnvriment& env);
	protected:
		virtual EBehaviorResult EvaluationPreCondition(BehaviorEnvriment& env);
	public:
		typedef std::vector<BehaviorNode*> CollectionNodesT;
	protected:
		CollectionNodesT m_vtNodes;
		BehaviorNode* m_pParent;
		BehaviorNode* m_pPreCondition;
		EBehaviorStatus m_nStatus;
	};

	// ---------------------------------------------------------------------------------

	const size_t cst_max_state_num = 20;

	// ---------------------------------------------------------------------------------

	class BehaviorTree : protected BehaviorNode
	{
	public:
		BehaviorTree(size_t numberOfStates = cst_max_state_num);
	public:
		inline void SetStateNode(size_t state,BehaviorNode* node)
		{
			assert(m_vtNodes.size() > state);
			assert(m_vtNodes[state] == NULL);

			m_vtNodes[state] = node;
		}

		inline void SetState(size_t state)
		{
			assert(m_vtNodes.size() > state);
			assert(m_vtNodes[state] != NULL);


			if(m_nCurrentState == state)
				return ;

			OnLeaveState(m_nCurrentState);
			m_nCurrentState = state;
			OnEnterState(m_nCurrentState);
		}
	protected:
		virtual void OnLeaveState(size_t state)
		{

		}

		virtual void OnEnterState(size_t state)
		{

		}
	public:
		virtual EBehaviorResult Evaluation(BehaviorEnvriment& env);
	protected:
		size_t m_nCurrentState;
	};
}

#endif // _pw_behavior_tree_