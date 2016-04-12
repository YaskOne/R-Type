#ifndef BONUSMULTISHOOTGRAPHICAL_H_
# define BONUSMULTISHOOTGRAPHICAL_H_

#include "AssetsController.hh"
#include "ViewController.hh"
#include "MultiShoot.hh"
#include "GraphicalItem.h"

class                   MultiShootGraphical : public MultiShoot, public GraphicalItem
{
public:
  MultiShootGraphical(
			   sf::Vector2f const&,
			   sf::Vector2f const&,
			   unsigned int,
			   float);

  ~MultiShootGraphical();

public:
  bool		update(sf::Clock const&);

private:
  sf::Time	_referential;
  sf::Time	_lastUpdate;
  bool		_incr;
  float		_angle;

};

#endif /* !BONUSMULTISHOOTGRAPHICAL_H_ */
