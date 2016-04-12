#ifndef UMUTEX_H_
# define UMUTEX_H_

# include <mutex>
# include "IMutex.h"

class CUMutex : public IMutex
{
public:
	CUMutex();
	~CUMutex();

private:
	std::mutex			_mutex;

public:
	void				InitMutex();
	void				DestroyMutex();
	void				LockMutex();
	bool				TrylockMutex();
	void				UnlockMutex();
};

#endif
