#ifndef _IALIEN_FACTORY_HH_
# define _IALIEN_FACTORY_HH_

# include <SFML/System/Clock.hpp>
# include "IObject.hh"
# include "ObjectInfo.hpp"
# include "Waves.hh"

class IAlienFactory
{
public:
  virtual ~IAlienFactory() {};
  virtual std::vector<IObject*>		   *getNextEnemy(const sf::Clock&) = 0;
  virtual const ObjectInfo::WaveType	   &getType() const = 0;
  virtual bool				   isOver() = 0;
  virtual void				   setWave(Waves*) = 0;
};

#endif
