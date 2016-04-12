#include "BasicAlienProjectileGraphical.h"

BasicAlienProjectileGrapical::BasicAlienProjectileGrapical(sf::Vector2f const& speed, sf::Vector2f const& pos, unsigned int id) :
	BasicAlienProjectile(speed, pos, id), GraphicalItem()
{
	_sprite->setTexture(*(ac->getShot(BASICALIENSHOT)));
	_sprite->setPosition(
    _pos.x,
    _pos.y
		);

}

bool BasicAlienProjectileGrapical::update(sf::Clock const& clock)
{
  bool	ret;

  ret = BasicAlienProjectile::update(clock);
	_sprite->setPosition(
		_pos.x,
		_pos.y
		);
	return (ret);
}
