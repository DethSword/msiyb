#include "wincriticalsection.h"

using MSIYBCore::WinCriticalSection;

WinCriticalSection::WinCriticalSection(unsigned long spinLockCount)
{
	_spinLockCount = spinLockCount;
	_ready = false;
	_inUse = 0;
}

WinCriticalSection::WinCriticalSection(const WinCriticalSection &other)
{
	_spinLockCount = other._spinLockCount;
	_critical = other._critical;
	_ready = other._ready;
}

WinCriticalSection::WinCriticalSection(WinCriticalSection&& other)
{
	_spinLockCount = other._spinLockCount;
	_critical = other._critical;
	_ready = other._ready;
}

WinCriticalSection& WinCriticalSection::operator=(const WinCriticalSection& other)
{
	_spinLockCount = other._spinLockCount;
	_critical = other._critical;
	_ready = other._ready;
	return *this;
}

WinCriticalSection::~WinCriticalSection()
{
	if (_ready)
	{
		DeleteCriticalSection(&_critical);
		_ready = false;
	}
}

void WinCriticalSection::Init(unsigned long spinLockCount)
{
	if (!_ready)
	{
		InitializeCriticalSectionAndSpinCount(&_critical, spinLockCount);
		_ready = true;
	}
}

bool WinCriticalSection::Lock()
{
	Init(_spinLockCount);
	EnterCriticalSection(&_critical);
	_inUse++;
	return true;
}

bool WinCriticalSection::LockShared()
{
	return false;
}

bool WinCriticalSection::TryLock()
{
	Init();
	if (TryEnterCriticalSection(&_critical))
	{
		_inUse++;
		return true;
	}
	return false;
}

bool WinCriticalSection::TryLockShared()
{
	return false;
}

bool WinCriticalSection::Unlock()
{
	if (_inUse > 0)
	{
		_inUse--;
		LeaveCriticalSection(&_critical);
		return true;
	}
	return false;
}

