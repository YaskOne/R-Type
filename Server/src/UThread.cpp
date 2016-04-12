#include "UThread.h"

UThread::UThread(std::string const& port, std::string const& ip, CUMutex* mutex, bool* endGame)
  : _port(port),
    _ip(ip),
    _mutex(mutex),
    _endGame(endGame)
{
}


UThread::~UThread()
{
  DestroyThread();
}

bool UThread::InitThread(void routine(std::string const& port, std::string const& ip, CUMutex* mutex, bool* endGame))
{
  _routine = routine;
  return true;
}

bool UThread::StartThread()
{
  _thread = new std::thread(_routine, _port, _ip, _mutex, _endGame);
  return true;
}

bool UThread::WaitThread()
{
  _thread->join();
  return true;
}

void UThread::DestroyThread()
{
  delete _thread;
}
