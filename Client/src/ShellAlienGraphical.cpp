#include "ShellAlienGraphical.hh"

ShellAlienGraphical::ShellAlienGraphical(sf::Vector2f speed, sf::Vector2f pos, unsigned int id, float coeff)
  : ShellAlien(speed, pos, id, coeff), GraphicalItem()
{
	_sprite->setTexture(*(ac->getAlien(SHELL)));
	_sprite->setPosition(
	_pos.x / SCREENRATIO,
	_pos.y / SCREENRATIO
	);
}

bool ShellAlienGraphical::update(sf::Clock const& clock)
{
  bool	ret;

  ret = ShellAlien::update(clock);
  _sprite->setPosition(
		_pos.x,
		_pos.y
		);
	return (ret);
}

bool	ShellAlienGraphical::update(std::vector<IObject*>&, sf::Clock const&)
{
  return (true);
}