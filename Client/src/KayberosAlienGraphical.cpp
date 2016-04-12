#include "KayberosAlienGraphical.hh"

KayberosAlienGraphical::KayberosAlienGraphical(sf::Vector2f const& speed, sf::Vector2f const& pos, unsigned int id, float coeff)
  : KayberosAlien(speed, pos, id, coeff), GraphicalItem()
{
	_sprite->setTexture(*(ac->getAlien(KAYBEROS)));
	_sprite->setPosition(
	_pos.x / SCREENRATIO,
	_pos.y / SCREENRATIO
	);
}

bool KayberosAlienGraphical::update(sf::Clock const& clock)
{
  bool	ret;

  ret = KayberosAlien::update(clock);
  _sprite->setPosition(
		_pos.x,
		_pos.y
		);
	return (ret);
}

bool	KayberosAlienGraphical::update(std::vector<IObject*>&, sf::Clock const&)
{
  return (true);
}
