#pragma once

#include <memory>
#include <stack>
#include "State.h"

typedef std::unique_ptr<State> StateRef;

/**
 * Class used to store states in the stack and manages them.
 */
class StateMachine
{
public:
	StateMachine() { }
	~StateMachine() { }

	/**
	 * Method which adds state to the stack and it is the latest state that is running.
	 * 
	 * \param newState - Reference to State Class
	 * \param isReplacing - used to put state on the stack and delete current state (if true)
	 */
	void addState(StateRef newState, bool isReplacing = true);

	/**
	 * Method which deletes top state on the stack.
	 * 
	 */
	void removeState();

	/**
	 * Method which runs at the start of each loop in the Game.cpp file.
	 * 
	 */
	void processStateChanges();

	/**
	 * Method which returns top state on the stack.
	 * 
	 * \return current top state reference
	 */
	StateRef& getActiveState();

private:
	std::stack<StateRef> _states;
	StateRef _newState;

	bool _isRemoving;
	bool _isAdding, _isReplacing;
};