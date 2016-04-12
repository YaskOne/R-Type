#ifndef SAFEQUEUE_H_
# define SAFEQUEUE_H_

# include <deque>
# include <string>
# include "IMutex.h"
# include "IObject.hh"

class SafeQueue
{
public:
	SafeQueue();
	virtual ~SafeQueue();

private:
	IMutex*					_mutex;
	std::deque<IObject*>*			_list;

public:
	IObject*	popList();
	void		fillList(IObject* const data);
	bool		isEmpty();
};

//# include "SafeQueue.tpp"

#endif
