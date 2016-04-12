#include "WallGraphical.hh"

WallGraphical::WallGraphical(sf::Vector2f speed, sf::Vector2f pos, unsigned int id, float coeff)
  : Obstacle(speed, pos, id, coeff), GraphicalItem()
{
  _sprite->setTexture(*(ac->getAlien(WALL1)));
  _sprite->setPosition(
		       _pos.x / SCREENRATIO,
		       _pos.y / SCREENRATIO
		       );
  if (pos.y > (RES_Y /2))
    {
      _sprite->setOrigin(_size.x / 2, _size.y / 2);
      _sprite->rotate(180);
      _sprite->setOrigin(_size.x, _size.y);
    }
}

WallGraphical::~WallGraphical()
{

}

bool WallGraphical::update(sf::Clock const& clock)
{
  bool	ret;

  ret = Obstacle::update(clock);
  _sprite->setPosition(
		_pos.x,
		_pos.y
		);
	return (ret);
}

bool	WallGraphical::update(std::vector<IObject*>&, sf::Clock const&)
{
  return (true);
}
