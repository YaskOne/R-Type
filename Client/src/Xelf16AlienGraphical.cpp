#include "Xelf16AlienGraphical.hh"

Xelf16AlienGraphical::Xelf16AlienGraphical(sf::Vector2f const& speed, sf::Vector2f const& pos, unsigned int id, float coeff)
  : Xelf16Alien(speed, pos, id, coeff), GraphicalItem()
{
	_sprite->setTexture(*(ac->getAlien(XELF16)));
	_sprite->setPosition(
	_pos.x / SCREENRATIO,
	_pos.y / SCREENRATIO
	);
}

bool Xelf16AlienGraphical::update(sf::Clock const& clock)
{
  bool	ret;

  ret = Xelf16Alien::update(clock);
  _sprite->setPosition(
		_pos.x,
		_pos.y
		);
	return (ret);
}

bool	Xelf16AlienGraphical::update(std::vector<IObject*>&, sf::Clock const&)
{
  return (true);
}
