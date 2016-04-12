#ifndef UTHREAD_H_
# define UTHREAD_H_


# include <thread>
# include <string>
# include "IThread.h"
# include "UMutex.h"

class UThread : public IThread
{
 public:
  UThread(std::string const& port, std::string const& ip, CUMutex*, bool*);
  ~UThread();

 private:
  std::string		_port;
  std::string		_ip;
  CUMutex*		_mutex;
  bool*			_endGame;
  std::thread*		_thread;
  void			(*_routine)(std::string const& port, std::string const& ip, CUMutex*, bool*);

 public:
  bool			InitThread(void routine(std::string const& port, std::string const& ip, CUMutex*, bool*));
  bool			StartThread();
  bool			WaitThread();
  void			DestroyThread();
};

#endif
