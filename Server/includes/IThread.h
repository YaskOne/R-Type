#ifndef ITHREAD_H_
# define ITHREAD_H_

# include "UMutex.h"

class IThread
{
 public:
  virtual ~IThread() {}

 public:
  virtual bool	InitThread(void routine(std::string const&, std::string const&, CUMutex*, bool*)) = 0;
  virtual bool	StartThread() = 0;
  virtual bool	WaitThread() = 0;
  virtual void	DestroyThread() = 0;
};

IThread*				getThreadInstance();

#endif
