#pragma once

#include "Classes.h"

#include <map>
#include <string>
#include <thread>
#include <vector>

namespace iron
{

class Iron
{
public:

	bool runSubtick();

	void runScript(const StateID& sid);
	void runScriptImpl(State& state, Script& script);

	bool propagate(const WireID& wid);
	bool propagateImpl(Wire& wire);

private:
	std::vector<std::thread> m_threads;
	std::map<BehaviorID, Behavior> m_behaviors;
	

};

}