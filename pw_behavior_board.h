#ifndef _pw_behavior_board_
#define _pw_behavior_board_


#include "pw_behavior_def.h"

namespace pwngs
{

	enum BehaviorVariableOp
	{
		BEHAVIOR_VARIABLE_OP_LESS,
		BEHAVIOR_VARIABLE_OP_LESS_EQUAL,
		BEHAVIOR_VARIABLE_OP_EQUAL,
		BEHAVIOR_VARIABLE_OP_NOT_EQUAL,
		BEHAVIOR_VARIABLE_OP_GREAT,
		BEHAVIOR_VARIABLE_OP_GREAT_EQUAL,
	};

	class BehaviorVariable
	{
	public:
		virtual int32 AsInt32()
		{
			return 0;
		}

		virtual int64 AsInt64()
		{
			return 0;
		}

		virtual double AsDouble()
		{
			return 0.0f;
		}
	public:
		int NotEqual(BehaviorVariable* other)
		{
			return AsDouble() != other->AsDouble();
		}
		int Equal(BehaviorVariable* other)
		{
			return AsDouble() == other->AsDouble();
		}
		int Less(BehaviorVariable* other)
		{
			return AsDouble() < other->AsDouble();
		}
		int LessOrEqual(BehaviorVariable* other)
		{
			return AsDouble() <= other->AsDouble();
		}
		int Great(BehaviorVariable* other)
		{
			return AsDouble() > other->AsDouble();
		}
		int GreatOrEqual(BehaviorVariable* other)
		{
			return AsDouble() >= other->AsDouble();
		}
	};

	template<class T> class BehaviorVariableConst: public BehaviorVariable
	{
	public:
		BehaviorVariableConst(T val)
			: m_nValue(val)
		{
		}
	public:
		virtual int32 AsInt32()
		{
			return (int32)m_nValue;
		}

		virtual int64 AsInt64()
		{
			return (int64)m_nValue;
		}

		virtual double AsDouble()
		{
			return (double)m_nValue;
		}
	protected:
		T m_nValue;
	};

	template<class T> class BehaviorVariablePointer: public BehaviorVariable
	{
	public:
		BehaviorVariablePointer(T* valuePtr)
			: m_pValuePtr(valuePtr)
		{
		}
	public:
		virtual int32 AsInt32()
		{
			return (int32)(*m_pValuePtr);
		}

		virtual int64 AsInt64()
		{
			return (int64)(*m_pValuePtr);
		}

		virtual double AsDouble()
		{
			return (*m_pValuePtr);
		}
	protected:
		T* m_pValuePtr;
	};


	class BehaviorBoard
	{
	public:
		~BehaviorBoard();
	public:
		BehaviorVariable* GetVariable(const char* name);
		BehaviorVariable* AddVariable(const char* name,BehaviorVariable* variable);
		BehaviorVariable* DelVariable(const char* name);
	protected:
		typedef std::map<std::string,BehaviorVariable*> CollectionVariablesT;
	protected:
		CollectionVariablesT m_mapVariables;
	};
}

#endif // _pw_behavior_board_