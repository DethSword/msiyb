/*!
\file ithread.h "server\desktop\src\cross\ithread.h"
\authors Dmitry Zaitsev
\copyright © MSiYB 2017
\license GPL license
\version 1.0
\date 02 March 2017
*/

#pragma once
#include "../defines.h"
#include "threadsecurity.h"
#include "../tools/exceptions/threadexception.h"

/// The flags that control the creation of the thread
typedef enum
{
	RUNIMMEDIATLY,		///< The thread runs immediately after its creation
	CREATESUSPENDED,	///< The thread is created in a suspended state
	RESERVESTACK		///< Specifies the initial reserve size of the stack
} t_flags;

/*!
\class IThread ithread.h "server\desktop\src\cross\ithread.h"
\brief  The class-interface for the OS-dependent classes.
The defined methods for the threads should be realized in the OS-dependent classes.
*/
class IThread
{
public:

	/*!
	Sets up a thread before the launch.
	\param[in] threadFunc The pointer to a function to be executed by the thread.
	\param[in] threadFuncArgs The pointer to a variable to be passed to the thread.
	\param[in] threadStackSize The initial size of the stack, in bytes.
	\param[in] threadFlags The flags that control the creation of the thread.
	\param[in] threadSecurityAttributes Determines if the returned handle can be inherited by the child.
	*/
	virtual void Init(void* threadFunc, void* threadFuncArgs, size_t threadStackSize, t_flags threadFlags, t_secattr threadSecurityAttributes) = 0;
	
	/*!
	Launches a thread with set parameters.
	\param[in] threadID The ID of the thread to be launched.
	*/
	virtual void Start() = 0;

	/*!
	Returns the launched thread system ID.
	\param[in] The local thread ID.
	\return The launched thread system ID.
	*/
	virtual long GetThreadID() = 0;

	/*!
	Checks if the thread completed its work.
	\param[out] result The value returned from the thread function.
	\return TRUE if still active and FALSE otherwise.
	*/
	virtual bool CheckActive(void *result = nullptr) = 0;
};
