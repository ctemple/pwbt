#ifndef _pw_behavior_facade_
#define _pw_behavior_facade_


#include "pw_behavior_tree.h"
#include "pw_behavior_board.h"
#include "pw_behavior_node_selector.h"
#include "pw_behavior_node_decorator.h"
#include "pw_behavior_node_sequence.h"
#include "pw_behavior_node_condition.h"
#include "pw_behavior_node_action.h"

#include <stdarg.h>

namespace pwngs
{
	class BehaviorFacade
	{
	public:
		template<class T> static BehaviorNode* Create()
		{
			BehaviorNode* result = new T();
			return result;
		}
	};
}

#endif // _pw_behavior_facade_