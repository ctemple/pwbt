#include "pw_behavior_board.h"

namespace pwngs
{
	BehaviorBoard::~BehaviorBoard()
	{
		for(CollectionVariablesT::iterator iter = m_mapVariables.begin(); iter != m_mapVariables.end(); ++iter)
			delete iter->second;
		m_mapVariables.clear();
	}

	BehaviorVariable* BehaviorBoard::GetVariable( const char* name )
	{
		CollectionVariablesT::iterator iter = m_mapVariables.find(name);
		if(iter != m_mapVariables.end())
			return iter->second;
		return NULL;
	}

	BehaviorVariable* BehaviorBoard::AddVariable( const char* name,BehaviorVariable* variable )
	{
		CollectionVariablesT::iterator iter = m_mapVariables.find(name);
		assert(iter == m_mapVariables.end() && "variable exists");

		iter = m_mapVariables.insert(std::make_pair(name,variable)).first;

		return iter->second;
	}

	BehaviorVariable* BehaviorBoard::DelVariable( const char* name )
	{
		CollectionVariablesT::iterator iter = m_mapVariables.find(name);
		if(iter == m_mapVariables.end())
			return NULL;

		BehaviorVariable* result = iter->second;

		m_mapVariables.erase(iter);

		return result;
	}
}