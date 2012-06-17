#ifndef _pw_behavior_node_decorator_
#define _pw_behavior_node_decorator_


#include "pw_behavior_tree.h"

namespace pwngs
{
	class BehaviorDecoratorNode : public BehaviorNode
	{
	public:
		BehaviorDecoratorNode();
	};

	class BehaviorDecoratorNode_Not : public BehaviorDecoratorNode
	{
	public:
		virtual int Evaluation(BehaviorEnvriment& env);
	};

	class BehaviorDecoratorNode_FailUtil : public BehaviorDecoratorNode
	{
	public:
		virtual int Evaluation(BehaviorEnvriment& env);
	};

	class BehaviorDecoratorNode_Counter : public BehaviorDecoratorNode
	{
	public:
		BehaviorDecoratorNode_Counter(BehaviorVariable* variable);
	public:
		virtual int Evaluation(BehaviorEnvriment& env);
	protected:
		BehaviorVariable* m_pVariable;
	};

	class BehaviorDecoratorNode_Time : public BehaviorDecoratorNode
	{
	public:
		BehaviorDecoratorNode_Time(BehaviorVariable* variable);
	public:
		virtual int Evaluation(BehaviorEnvriment& env);
	protected:
		BehaviorVariable* m_pVariable;
		sint64 m_nLastEvaluationTime;
	};
}

#endif // _pw_behavior_node_decorator_