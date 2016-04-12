#ifndef IMUTEX_H_
# define IMUTEX_H_

class IMutex
{
  public:
  virtual ~IMutex() {};

  public:
  virtual void                    InitMutex() = 0;
  virtual void                    DestroyMutex() = 0;
  virtual void                    LockMutex() = 0;
  virtual bool                    TrylockMutex() = 0;
  virtual void                    UnlockMutex() = 0;
};

IMutex*                                         getMutexInstance();

#endif
