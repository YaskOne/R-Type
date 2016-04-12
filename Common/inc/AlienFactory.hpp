#ifndef _ALIENFACTORY_HH_
# define _ALIENFACTORY_HH_

# include <cstddef>
# include <deque>
# include "IAlienFactory.hh"
# include "MapController.hh"
# include "Waves.hh"

extern unsigned int _maxId;

template <class T>
class	AlienFactory : public IAlienFactory
{
public:
  AlienFactory(ObjectInfo::WaveType type) : _type(type){};
  ~AlienFactory() {};

public:
  std::vector<IObject*>		*getNextEnemy(const sf::Clock &clock)
  {
    std::vector<IObject*>	*obj = new std::vector<IObject*>;

    for (auto it = _order.begin(); it != _order.end(); it++)
      {
	if ((*it) != NULL)
	  if (clock.getElapsedTime() >= (*it)->getTime())
	    {
	      obj->push_back(new T((*it)->getSpeed(), (*it)->getPos(), _maxId++, (*it)->getCoeff()));
	      (*it)->pop();
	    }
	  else
	    obj->push_back(NULL);
	if ((*it)->getCount() <= 0)
	  {
	    it = _order.erase(it);
	  }
	if (it == _order.end())
	  break;
      }
    return (obj);
  }

  const ObjectInfo::WaveType	&getType() const
  {
    return _type;
  }

  void			setWave(Waves *wave)
  {
    if (wave != NULL)
      _order.push_back(wave);
  }

  bool			isOver()
  {
    return (_order.size() == 0);
  }

public:
  std::deque<Waves*>	_order;
  ObjectInfo::WaveType	_type;
};

#endif
