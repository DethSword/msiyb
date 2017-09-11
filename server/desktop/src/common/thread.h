/*!
\file thread.h "server\desktop\src\common\thread.h"
\authors Dmitry Zaitsev
\copyright © MSiYB 2017
\license GPL license
\version 2.0
\date 02 March 2017
*/

#pragma once

#ifdef _WIN32
#include "../cross/windows/winthread.h"
typedef WinThread OSThread;
#elif _unix_
#include "../cross/unix/unixthread.h"
typedef UnixThread OSThread;
#endif

/*!
\class Thread thread.h "server\desktop\src\common\thread.h"
\brief  The thread interface.
Provides an interface to a single thread structure and its action.
The factory for the unix/bsd/windows structure of the thread.
*/
class Thread
{
public:

	/*!
	Initialises the OS-dependent thread structure.
	*/
	Thread();

	/*!
	Deallocates memory of the OS-dependent object.
	*/
	~Thread();

	/*!
	Tries to start a new thread. If the number of active threads is already
	equal to the max thread count, looks for the completed threads and tries one more time.
	\param[in] threadFunc The pointer to a function to be executed by the thread.
	\param[in] threadFuncArgs The pointer to a variable to be passed to the thread.
	\param[out] result The value returned from the thread function.
	\return The thread ID if the new thread is started.
	*/
	int Start(void *threadFunc, void *threadFuncArgs, void *result = nullptr);

	void* GetResult();

	/*!
	Checks if the thread completed its work.
	\param[in] threadID The ID of the thread to be checked.
	\return TRUE if completed, FALSE otherwise.
	*/
	bool IsCompleted();

	/*!
	Returns the maximum number of the threads that can be started. Static.
	\return The maximum amount of the threads can be started.
	*/
	static int GetMaxThreadCount();

private:
	int _id;				///< The current thread ID.
	void *_result;			///< The value returned from the thread function.
	OSThread *_thread;		///< The OS-dependent thread structure.
};
