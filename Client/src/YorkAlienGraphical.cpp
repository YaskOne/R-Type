#include "YorkAlienGraphical.hh"

YorkAlienGraphical::YorkAlienGraphical(sf::Vector2f const& speed, sf::Vector2f const& pos, unsigned int id, float coeff)
  : YorkAlien(speed, pos, id, coeff), GraphicalItem()
{
	_sprite->setTexture(*(ac->getAlien(YORK)));
	_sprite->setPosition(
	_pos.x / SCREENRATIO,
	_pos.y / SCREENRATIO
	);
}

bool YorkAlienGraphical::update(sf::Clock const& clock)
{
  bool	ret;

  ret = YorkAlien::update(clock);
  _sprite->setPosition(
		_pos.x,
		_pos.y
		);
	return (ret);
}

bool	YorkAlienGraphical::update(std::vector<IObject*>&, sf::Clock const&)
{
  return (true);
}
