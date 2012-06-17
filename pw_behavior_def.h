#ifndef _pw_behavior_def_
#define _pw_behavior_def_

#include <vector>
#include <string>
#include <algorithm>
#include <cassert>
#include <map>


namespace pwngs
{

#ifdef _WIN32
	typedef signed char sint8;
	typedef unsigned char uint8;
	typedef signed short sint16;
	typedef unsigned short uint16;
	typedef __int32 sint32;
	typedef unsigned __int32 uint32;
	typedef __int64 sint64;
	typedef unsigned __int64 uint64;
#else
	typedef signed char sint8;
	typedef unsigned char uint8;
	typedef signed short sint16;
	typedef unsigned short uint16;
	typedef int32_t sint32;
	typedef uint32_t uint32;
	typedef long long sint64;
	typedef unsigned long long uint64;
#endif

	typedef sint32 int32;
	typedef sint64 int64;

	class BehaviorTree;
	class BehaviorNode;
	class BehaviorBoard;
	class BehaviorVariable;
	class BehaviorCharacter;

	class BehaviorSelectorNode;
	class BehaviorSequenceNode;
	class BehaviorParallelNode;
	class BehaviorDecoratorNode;

	class BehaviorConditionNode;
	class BehaviorActionNode;


	class BehaviorEnvriment
	{
	public:
		BehaviorBoard* board;
		BehaviorCharacter* main;
		sint64 currentTimeMS;

		BehaviorEnvriment()
			: board(NULL)
			, main(NULL)
			, currentTimeMS(0)
		{

		}
	};

	class BehaviorCharacter
	{

	};

	enum EBehaviorResult
	{
		BEHAVIOR_RESULT_TRUE,
		BEHAVIOR_RESULT_FALSE,
		BEHAVIOR_RESULT_IGNORE,
	};	
}

#endif // _pw_behavior_def_