#ifndef _pw_behavior_node_
#define _pw_behavior_node_

#include "pw_behavior_tree.h"

namespace pwngs
{
	class BehaviorSelector : public BehaviorNode
	{
	};

	// ֻҪ��һ���ڵ�Finish,������selector Finish
	class BehaviorSelectorLiner : public BehaviorSelector
	{
	protected:
		virtual EBehaviorResult ExecutionBegan(BehaviorEnvriment& env);
		virtual EBehaviorResult Execute(BehaviorEnvriment& env);
		virtual EBehaviorResult ExecutionEnded(BehaviorEnvriment& env);
	protected:
		size_t m_nCurrentNode;
	};

	// ÿ�ο�ʼʱ,����˳��
	class BehaviorSelectorRandom: public BehaviorSelectorLiner
	{
	protected:
		virtual EBehaviorResult ExecutionBegan(BehaviorEnvriment& env);
	};

}

#endif // _pw_behavior_node_