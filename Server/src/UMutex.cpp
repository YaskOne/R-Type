# include "UMutex.h"

CUMutex::CUMutex()
{
}

CUMutex::~CUMutex()
{
}

void CUMutex::InitMutex()
{
}

void CUMutex::DestroyMutex()
{
}

void CUMutex::LockMutex()
{
  _mutex.lock();
}

bool CUMutex::TrylockMutex()
{
  return _mutex.try_lock();
}

void CUMutex::UnlockMutex()
{
  _mutex.unlock();
}
