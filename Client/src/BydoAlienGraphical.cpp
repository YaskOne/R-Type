#include "BydoAlienGraphical.hh"

BydoAlienGraphical::BydoAlienGraphical(sf::Vector2f const& speed, sf::Vector2f const& pos, unsigned int id, float coeff)
  : BydoAlien(speed, pos, id, coeff), GraphicalItem()
{
	_sprite->setTexture(*(ac->getAlien(BYDO)));
	_sprite->setPosition(
	_pos.x / SCREENRATIO,
	_pos.y / SCREENRATIO
	);
}

bool BydoAlienGraphical::update(sf::Clock const& clock)
{
  bool	ret;

  ret = BydoAlien::update(clock);
  _sprite->setPosition(
		_pos.x,
		_pos.y
		);
	return (ret);
}

bool	BydoAlienGraphical::update(std::vector<IObject*>&, sf::Clock const&)
{
  return (true);
}
