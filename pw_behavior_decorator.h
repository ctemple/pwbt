#ifndef _pw_behavior_node_decorator_
#define _pw_behavior_node_decorator_

#include "pw_behavior_tree.h"
#include "pw_behavior_sequence.h"

namespace pwngs
{
	// 等待一段时间后执行
	class BehaviorDecoratorWait : public BehaviorSequence
	{
	public:
		BehaviorDecoratorWait(int64 time);
	protected:
		virtual EBehaviorResult ExecutionBegan(BehaviorEnvriment& env);
		virtual EBehaviorResult Execute(BehaviorEnvriment& env);
	protected:
		int64 m_nStartTime;
		int64 m_nWaitTime;
	};

	// 不断循环执行
	class BehaviorDecoratorRepeatAlways : public BehaviorSequence
	{
	public:
		virtual EBehaviorResult Evaluation(BehaviorEnvriment& env);
	};

	// 取反
	class BehaviorDecoratorNot : public BehaviorNode
	{
	public:
		virtual EBehaviorResult Evaluation(BehaviorEnvriment& env);
	};

	// If
	class BehaviorDecoratorIf : public BehaviorNode
	{
	public:
		virtual EBehaviorResult Evaluation(BehaviorEnvriment& env);
	};

	// While
	class BehaviorDecoratorWhile : public BehaviorNode
	{
	public:
		virtual EBehaviorResult Evaluation(BehaviorEnvriment& env);
	};
}

#endif // _pw_behavior_node_decorator_