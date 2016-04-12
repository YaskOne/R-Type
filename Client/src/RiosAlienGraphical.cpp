#include "RiosAlienGraphical.hh"

RiosAlienGraphical::RiosAlienGraphical(sf::Vector2f const& speed, sf::Vector2f const& pos, unsigned int id, float coeff)
  : RiosAlien(speed, pos, id, coeff), GraphicalItem()
{
	_sprite->setTexture(*(ac->getAlien(RIOS)));
	_sprite->setPosition(
	_pos.x / SCREENRATIO,
	_pos.y / SCREENRATIO
	);
}

bool RiosAlienGraphical::update(sf::Clock const& clock)
{
  bool	ret;

  ret = RiosAlien::update(clock);
  _sprite->setPosition(
		_pos.x,
		_pos.y
		);
	return (ret);
}

bool	RiosAlienGraphical::update(std::vector<IObject*>&, sf::Clock const&)
{
  return (true);
}
