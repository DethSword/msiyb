/*!
\file ilocker.h "server\desktop\src\cross\ilocker.h"
\authors Dmitry Zaitsev
\copyright © MSiYB 2017
\license GPL license
\version 2.0
\date 05 July 2017
*/

#pragma once

#include "../defines.h"
#include "threadsecurity.h"
#include "../tools/exceptions/lockerexception.h"

namespace MSIYBCore
{
	/*!
	\class ILocker ilocker.h "server\desktop\src\cross\ilocker.h"
	\brief  The class-interface for the OS-dependent classes.
	The defined methods for the locker should be realized in the OS-dependent classes.
	*/
	class ILocker
	{
	public:

		/*!
		Locks the locker object. An exclusive lock.
		If another thread has already locked the locker,
		a call to lock will block the execution until the lock is acquired.
		\return TRUE if the state of the specified object is signaled(changed?) and FALSE otherwise (ex. timeout).
		*/
		virtual bool Lock() = 0;

		/*!
		Locks the locker object in shared mode so another reader thread can use it as well.
		\return TRUE if the shared mode(?) is available and FALSE otherwise (use Lock or TryLock).
		*/
		virtual bool LockShared() = 0;

		/*!
		Tries to lock the locker object.
		If another thread has already locked the locker, the function returns FALSE immediately.
		\return TRUE if the state of the specified object is signaled and FALSE if the object is already locked.
		*/
		virtual bool TryLock() = 0;

		/*!
		Tries to lock the locker object in the shared mode.
		If the call is successful, the thread calling takes the ownership of the lock and the function returns FALSE immediately.
		\return TRUE if the state of the specified object is signaled and FALSE if the object is already locked.
		*/
		virtual bool TryLockShared() = 0;

		/*!
		Unlocks the locker.
		\return TRUE if the unlock is successful, FALSE otherwise.
		*/
		virtual bool Unlock() = 0;

	};

}
