/*!
\file locker.h "server\desktop\src\common\locker.h"
\authors Dmitry Zaitsev
\copyright © MSiYB 2017
\license GPL license
\version 1.0
\date 08 July 2017
*/

#pragma once

#ifdef _WIN32
#include "../cross/windows/winlocker.h"
#elif _unix_
#include "../cross/unix/unixlocker.h"
#endif

namespace MSIYBCore {

	typedef enum
	{
		ELOCKDEFAULT,
		ELOCKTRY,
		ELOCKSHARED,
		ELOCKTRYSHARED
	} LockMethod;

	/*!
	\class Locker locker.h "server\desktop\src\common\locker.h"
	\brief  RAII for mutex, spinlock, SRWlock, critical etc.
	*/
	class Locker
	{
	public:
		/*!
		Locks the object.
		\param[in] locker The locker (of the?) object.
		*/
		Locker(ILocker& locker, LockMethod lockMethod = LockMethod::ELOCKDEFAULT);

		/*!
		Unlocks the object.
		*/
		~Locker();

		/*!
		Checks the success of the lock.
		\return TRUE if the state of the specified object is signaled(changed?) and FALSE otherwise.
		*/
		bool WasLocked();

	private:
		ILocker& _locker;	///< The locker object
		bool _state;		/// TRUE if the lock succeeded and FALSE otherwise
	};
}
