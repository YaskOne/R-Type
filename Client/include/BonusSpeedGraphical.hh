#ifndef BONUSSPEEDGRAPHICAL_H_
# define BONUSSPEEDGRAPHICAL_H_

#include "AssetsController.hh"
#include "ViewController.hh"
#include "BonusSpeed.hh"
#include "GraphicalItem.h"

class                   BonusSpeedGraphical : public BonusSpeed, public GraphicalItem
{
public:
  BonusSpeedGraphical(
		      sf::Vector2f const&,
		      sf::Vector2f const&,
		      unsigned int,
		      float);

  ~BonusSpeedGraphical();

public:
  bool		update(sf::Clock const&);

private:
  sf::Time	_referential;
  sf::Time	_lastUpdate;
  bool		_incr;
  float		_angle;

};

#endif /* !BONUSSPEEDGRAPHICAL_H_ */
