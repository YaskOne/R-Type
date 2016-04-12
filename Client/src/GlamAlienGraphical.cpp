#include "GlamAlienGraphical.hh"

GlamAlienGraphical::GlamAlienGraphical(sf::Vector2f const& speed, sf::Vector2f const& pos, unsigned int id, float coeff)
  : GlamAlien(speed, pos, id, coeff), GraphicalItem()
{
	_sprite->setTexture(*(ac->getAlien(GLAM)));
	_sprite->setPosition(
	_pos.x / SCREENRATIO,
	_pos.y / SCREENRATIO
	);
}

bool GlamAlienGraphical::update(sf::Clock const& clock)
{
  bool	ret;

  ret = GlamAlien::update(clock);
  _sprite->setPosition(
		_pos.x,
		_pos.y
		);
	return (ret);
}

bool	GlamAlienGraphical::update(std::vector<IObject*>&, sf::Clock const&)
{
  return (true);
}
