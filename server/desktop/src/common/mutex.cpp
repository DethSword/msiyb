#include "mutex.h"

Mutex::Mutex()
{
	_mutex = new OSMutex();
	if (!_mutex)
	{
		ThrowMutexExceptionWithCode("Can't allocate memory for OS mutex!", GetLastError());
	}
}

Mutex::~Mutex()
{
	delete _mutex;
}