#include "MultiShootGraphical.hh"

MultiShootGraphical::MultiShootGraphical(sf::Vector2f const& speed,
						   sf::Vector2f const& pos,
						   unsigned int id,
						   float f) :
  MultiShoot(speed, pos, id, f), GraphicalItem()
{
  _sprite->setTexture(*(ac->getBonus(MULTISHOOT)));
  _sprite->setPosition(
		       _pos.x,
		       _pos.y
		       );
  _referential = sf::milliseconds(100);
  _lastUpdate = sf::seconds(0);
  _incr = false;
  _angle = 0;
}

MultiShootGraphical::~MultiShootGraphical()
{
}

bool                MultiShootGraphical::update(sf::Clock const& clock)
{
  bool ret = MultiShoot::update(clock);

  _sprite->setPosition(
		       _pos.x,
		       _pos.y
		       );
  if ((clock.getElapsedTime() - _lastUpdate) > _referential)
    {
      if (_incr)
        {
            if (_angle >= 30)
	      _incr = !_incr;
            _angle++;
        }
      else
        {
	  if (_angle <= -30)
                _incr = !_incr;
	  _angle--;
        }
      _sprite->setRotation(_angle);
      _lastUpdate = clock.getElapsedTime();
    }
  return ret;
}
